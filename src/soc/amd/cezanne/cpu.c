/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/cpu.h>
#include <amdblocks/mca.h>
#include <amdblocks/reset.h>
#include <amdblocks/smm.h>
#include <assert.h>
#include <console/console.h>
#include <cpu/amd/microcode.h>
#include <cpu/cpu.h>
#include <cpu/x86/mp.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/smm.h>
#include <device/device.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <types.h>

_Static_assert(CONFIG_MAX_CPUS == 16, "Do not override MAX_CPUS. To reduce the number of "
	"available cores, use the downcore_mode and disable_smt devicetree settings instead.");

/* MP and SMM loading initialization */

/*
 * Do essential initialization tasks before APs can be fired up -
 *
 *  1. Prevent race condition in MTRR solution. Enable MTRRs on the BSP. This
 *  creates the MTRR solution that the APs will use. Otherwise APs will try to
 *  apply the incomplete solution as the BSP is calculating it.
 */
static void pre_mp_init(void)
{
	x86_setup_mtrrs_with_detect_no_above_4gb();
	x86_mtrr_check();
}

static void post_mp_init(void)
{
	global_smi_enable();
	apm_control(APM_CNT_SMMINFO);
}

static const struct mp_ops mp_ops = {
	.pre_mp_init = pre_mp_init,
	.get_cpu_count = get_cpu_count,
	.get_smm_info = get_smm_info,
	.relocation_handler = smm_relocation_handler,
	.post_mp_init = post_mp_init,
};

void mp_init_cpus(struct bus *cpu_bus)
{
	if (mp_init_with_smm(cpu_bus, &mp_ops) != CB_SUCCESS)
		die_with_post_code(POST_HW_INIT_FAILURE,
				"mp_init_with_smm failed. Halting.\n");

	/* pre_mp_init made the flash not cacheable. Reset to WP for performance. */
	mtrr_use_temp_range(FLASH_BASE_ADDR, CONFIG_ROM_SIZE, MTRR_TYPE_WRPROT);
}

static void zen_2_3_init(struct device *dev)
{
	check_mca();
	set_cstate_io_addr();

	amd_update_microcode_from_cbfs();
}

static struct device_operations cpu_dev_ops = {
	.init = zen_2_3_init,
};

static struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_AMD, CEZANNE_A0_CPUID},
	{ 0, 0 },
};

static const struct cpu_driver zen_2_3 __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
