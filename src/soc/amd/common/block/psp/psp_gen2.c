/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootstate.h>
#include <console/console.h>
#include <cpu/amd/msr.h>
#include <cpu/x86/msr.h>
#include <device/mmio.h>
#include <timer.h>
#include <amdblocks/psp.h>
#include <soc/iomap.h>
#include "psp_def.h"

#define PSP_MAILBOX_OFFSET		0x10570

static uintptr_t soc_get_psp_base_address(void)
{
	uintptr_t psp_mmio = rdmsr(PSP_ADDR_MSR).lo;
	if (!psp_mmio)
		printk(BIOS_ERR, "PSP: PSP_ADDR_MSR uninitialized\n");
	return psp_mmio;
}

static void *soc_get_mbox_address(void)
{
	uintptr_t psp_mmio = soc_get_psp_base_address();
	if (!psp_mmio)
		return 0;
	return (void *)(psp_mmio + PSP_MAILBOX_OFFSET);
}

static u16 rd_mbox_sts(struct pspv2_mbox *mbox)
{
	union {
		u32 val;
		struct pspv2_mbox_cmd_fields fields;
	} tmp = { 0 };

	tmp.val = read32(&mbox->val);
	return tmp.fields.mbox_status;
}

static void wr_mbox_cmd(struct pspv2_mbox *mbox, u8 cmd)
{
	union {
		u32 val;
		struct pspv2_mbox_cmd_fields fields;
	} tmp = { 0 };

	/* Write entire 32-bit area to begin command execution */
	tmp.fields.mbox_command = cmd;
	write32(&mbox->val, tmp.val);
}

static u8 rd_mbox_recovery(struct pspv2_mbox *mbox)
{
	union {
		u32 val;
		struct pspv2_mbox_cmd_fields fields;
	} tmp = { 0 };

	tmp.val = read32(&mbox->val);
	return !!tmp.fields.recovery;
}

static void wr_mbox_cmd_resp(struct pspv2_mbox *mbox, void *buffer)
{
	write64(&mbox->cmd_response, (uintptr_t)buffer);
}

static int wait_command(struct pspv2_mbox *mbox, bool wait_for_ready)
{
	struct pspv2_mbox and_mask = { .val = ~0 };
	struct pspv2_mbox expected = { .val = 0 };
	struct stopwatch sw;
	u32 tmp;

	/* Zero fields from and_mask that should be kept */
	and_mask.fields.mbox_command = 0;
	and_mask.fields.ready = wait_for_ready ? 0 : 1;

	/* Expect mbox_cmd == 0 but ready depends */
	if (wait_for_ready)
		expected.fields.ready = 1;

	stopwatch_init_msecs_expire(&sw, PSP_CMD_TIMEOUT);

	do {
		tmp = read32(&mbox->val);
		tmp &= ~and_mask.val;
		if (tmp == expected.val)
			return 0;
	} while (!stopwatch_expired(&sw));

	return -PSPSTS_CMD_TIMEOUT;
}

int send_psp_command(u32 command, void *buffer)
{
	struct pspv2_mbox *mbox = soc_get_mbox_address();
	if (!mbox)
		return -PSPSTS_NOBASE;

	if (rd_mbox_recovery(mbox))
		return -PSPSTS_RECOVERY;

	if (wait_command(mbox, true))
		return -PSPSTS_CMD_TIMEOUT;

	/* set address of command-response buffer and write command register */
	wr_mbox_cmd_resp(mbox, buffer);
	wr_mbox_cmd(mbox, command);

	/* PSP clears command register when complete.  All commands except
	 * SxInfo set the Ready bit. */
	if (wait_command(mbox, command != MBOX_BIOS_CMD_SX_INFO))
		return -PSPSTS_CMD_TIMEOUT;

	/* check delivery status */
	if (rd_mbox_sts(mbox))
		return -PSPSTS_SEND_ERROR;

	return 0;
}

enum cb_err soc_read_c2p38(uint32_t *msg_38_value)
{
	uintptr_t psp_mmio = soc_get_psp_base_address();

	if (!psp_mmio) {
		printk(BIOS_WARNING, "PSP: PSP_ADDR_MSR uninitialized\n");
		return CB_ERR;
	}
	*msg_38_value = read32((void *)psp_mmio + CORE_2_PSP_MSG_38_OFFSET);
	return CB_SUCCESS;
}

static void psp_set_spl_fuse(void *unused)
{
	if (!CONFIG(SOC_AMD_COMMON_BLOCK_PSP_FUSE_SPL))
		return;

	uint32_t msg_38_value = 0;
	int cmd_status = 0;
	struct mbox_cmd_late_spl_buffer buffer = {
		.header = {
			.size = sizeof(buffer)
		}
	};

	if (soc_read_c2p38(&msg_38_value) != CB_SUCCESS) {
		printk(BIOS_ERR, "PSP: Failed to read psp base address.\n");
		return;
	}

	if (msg_38_value & CORE_2_PSP_MSG_38_FUSE_SPL) {
		printk(BIOS_DEBUG, "PSP: Fuse SPL requested\n");
		cmd_status = send_psp_command(MBOX_BIOS_CMD_SET_SPL_FUSE, &buffer);
		psp_print_cmd_status(cmd_status, NULL);
	} else {
		printk(BIOS_DEBUG, "PSP: Fuse SPL not requested\n");
	}
}

BOOT_STATE_INIT_ENTRY(BS_PAYLOAD_BOOT, BS_ON_ENTRY, psp_set_spl_fuse, NULL);
