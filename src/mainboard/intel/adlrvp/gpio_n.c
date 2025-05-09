/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* ESPI_IO0_EC_R / ESPI_IO0_HDR */
	PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1),
	/* ESPI_IO1_EC_R / ESPI_IO1_HDR */
	PAD_CFG_NF(GPP_A1, NONE, DEEP, NF1),
	/* ESPI_IO2_EC_R / ESPI_IO2_HDR */
	PAD_CFG_NF(GPP_A2, NONE, DEEP, NF1),
	/* ESPI_IO3_EC_R / ESPI_IO3_HDR */
	PAD_CFG_NF(GPP_A3, NONE, DEEP, NF1),
	/* ESPI_CS0_EC_R_N / ESPI_CS0_HDR_N */
	PAD_CFG_NF(GPP_A4, NONE, DEEP, NF1),
	/* ESPI_ALERT0_EC_R_N / ESPI_ALERT0_HDR_N */
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1),
	/* ESPI_CLK_EC_R / ESPI_CLK_HDR */
	PAD_CFG_NF(GPP_A9, NONE, DEEP, NF1),
	/* ESPI_RST_EC_R_N / ESPI_RST_HDR_N */
	PAD_CFG_NF(GPP_A10, NONE, DEEP, NF1),

	/* EC_SLP_S0_CS_N */
	PAD_CFG_GPO(GPP_E4, 1, PLTRST),

	/* H15 : DDPB_CTRLCLK ==> DDIB_HDMI_CTRLCLK */
	PAD_CFG_NF(GPP_H15, NONE, DEEP, NF1),
	/* H17 : DDPB_CTRLDATA ==> DDIB_HDMI_CTRLDATA */
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),

	/* M.2_SSD_PDET_R */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* CLKREQ0_M2_SSD_N */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
	/* M2_PCH_SSD_PWREN */
	PAD_CFG_GPO(GPP_D16, 1, PLTRST),
	/* M2_SSD_RST_N */
	PAD_CFG_GPO(GPP_H0, 1, PLTRST),
	/* M2_SSD_DEVSLP */
	PAD_CFG_NF(GPP_H13, NONE, DEEP, NF5),

	/* I5  : NC */
	PAD_NC(GPP_I5, NONE),
	/* I7  : EMMC_CMD ==> EMMC_CMD */
	PAD_CFG_NF(GPP_I7, NONE, DEEP, NF1),
	/* I8  : EMMC_DATA0 ==> EMMC_D0 */
	PAD_CFG_NF(GPP_I8, NONE, DEEP, NF1),
	/* I9  : EMMC_DATA1 ==> EMMC_D1 */
	PAD_CFG_NF(GPP_I9, NONE, DEEP, NF1),
	/* I10 : EMMC_DATA2 ==> EMMC_D2 */
	PAD_CFG_NF(GPP_I10, NONE, DEEP, NF1),
	/* I11 : EMMC_DATA3 ==> EMMC_D3 */
	PAD_CFG_NF(GPP_I11, NONE, DEEP, NF1),
	/* I12 : EMMC_DATA4 ==> EMMC_D4 */
	PAD_CFG_NF(GPP_I12, NONE, DEEP, NF1),
	/* I13 : EMMC_DATA5 ==> EMMC_D5 */
	PAD_CFG_NF(GPP_I13, NONE, DEEP, NF1),
	/* I14 : EMMC_DATA6 ==> EMMC_D6 */
	PAD_CFG_NF(GPP_I14, NONE, DEEP, NF1),
	/* I15 : EMMC_DATA7 ==> EMMC_D7 */
	PAD_CFG_NF(GPP_I15, NONE, DEEP, NF1),
	/* I16 : EMMC_RCLK ==> EMMC_RCLK */
	PAD_CFG_NF(GPP_I16, NONE, DEEP, NF1),
	/* I17 : EMMC_CLK ==> EMMC_CLK */
	PAD_CFG_NF(GPP_I17, NONE, DEEP, NF1),
	/* I18 : EMMC_RESET# ==> EMMC_RST_L */
	PAD_CFG_NF(GPP_I18, NONE, DEEP, NF1),

	/* TYPEA_CONN23_USB2_P8_OC1_N */
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	/* CRD1_PWREN */
	PAD_CFG_GPO(GPP_B23, 1, PLTRST),
	/* TCP1_DISP_AUX_P_BIAS_GPIO */
	PAD_CFG_GPO(GPP_E20, 1, PLTRST),
	/* TCP1_DISP_AUX_N_BIAS_GPIO */
	PAD_CFG_GPO(GPP_E21, 0, PLTRST),
	/* TCP0_DISP_AUX_P_BIAS_GPIO */
	PAD_CFG_GPO(GPP_E22, 0, PLTRST),
	/* TCP0_DISP_AUX_N_BIAS_GPIO */
	PAD_CFG_GPO(GPP_E23, 1, PLTRST),

	/* EDP1_HPD_MIPI_PNL_RST */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),

	/* X1_SLOT_PWREN */
	PAD_CFG_GPO(GPP_A8, 0, PLTRST),
	/* SML0_CLK */
	PAD_CFG_NF(GPP_C3, NONE, DEEP, NF1),
	/* SML0_DATA */
	PAD_CFG_NF(GPP_C4, NONE, DEEP, NF1),
	/* CLKREQ3_X1PCIE_SLOT_N */
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
	/* X1_PCIE_SLOT_WAKE_N */
	PAD_CFG_GPI_IRQ_WAKE(GPP_D11, NONE, DEEP, LEVEL, INVERT),
	/* X1_Slot_RESET */
	PAD_CFG_GPO(GPP_F10, 1, PLTRST),

	/* WWAN_PERST_N */
	PAD_CFG_GPO(GPP_C5, 1, PLTRST),
	/* CLKREQ1_WWAN_N */
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
	/* GPPC_D15_M.2_WWAN_DISABLE_N */
	PAD_CFG_GPO(GPP_D15, 1, PLTRST),
	/* WWAN_PWREN */
	PAD_CFG_GPO(GPP_D17, 1, PLTRST),
	/* WWAN WAKE N */
	PAD_CFG_GPI_IRQ_WAKE(GPP_D18, NONE, DEEP, LEVEL, INVERT), //TODO SCI
	/* SRCCLK_OEB6 */
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF3),
	/* GPPC_F6_CNV_PA_BLANKING */
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
	/* WWAN_RST# */
	PAD_CFG_GPO(GPP_F14, 1, PLTRST),
	/* WWAN_FCP_OFF_N */
	PAD_CFG_GPO(GPP_F15, 1, PLTRST),
	/* CNV_MFUART2_RXD */
	PAD_CFG_NF(GPP_H8, NONE, DEEP, NF2),
	/* CNV_MFUART2_RXD */
	PAD_CFG_NF(GPP_H9, NONE, DEEP, NF2),

	/* PM_SLP_S0_N */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* PLT_RST_N */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	/* PM_SLP_DRAM_N */
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF2),
	/* CPU_C10_GATE_N_R */
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),

	/* CODEC_INT_N */
	PAD_CFG_GPI_APIC(GPP_H3, NONE, PLTRST, LEVEL, INVERT),
	/* SNDW0_CLK_HDR */
	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),
	/* SNDW0_DATA_HDR */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),
	/* SNDW1_CLK_DMIC_CLK_A_0 */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF2),
	/* SNDW1_DATA_DMIC_DATA_0 */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF2),
	/* SNDW2_CLK_R */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF1),
	/* SNDW2_DATA_R */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF1),
	/* SOC_DMIC0_SNDW3_CLK */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),
	/* SOC_DMIC0_SNDW3_DATA */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),

	/* I2C_SCL(0) */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* I2C_SDA(0) */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),

	/* DDIB_DP_HDMI_ALS_HDP */
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),

	/* 8 : M.2_BTWIFI_SUS_CLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* 9 : GPD_9_SLP_WLAN_N */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),

	/* SRCCLK_OEB7 */
	PAD_CFG_GPO(GPP_A7, 0, PLTRST),

	/* GPIO pin for PCIE SRCCLKREQB_2 */
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),

	/* H2 : WLAN_RST_N */
	PAD_CFG_GPO(GPP_H2, 1, PLTRST),
	/* I2C_SDA(1) */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* I2C_SCL(1) */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),

	/* CAM_PRIVACY_LED */
	PAD_CFG_GPO(GPP_B14, 1, PLTRST),

	/* B16 : I2C5 SDA */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF2),
	/* B17 : I2C5 SCL */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF2),

	/* CAM_STROBE */
	PAD_CFG_GPO(GPP_B18, 0, PLTRST),
	/* CAM1_RST_N */
	PAD_CFG_GPO(GPP_A21, 1, PLTRST),
	/* CAM1_PWR_EN */
	PAD_CFG_GPO(GPP_B23, 1, PLTRST),
	/* CAM2_RST */
	PAD_CFG_GPO(GPP_E15, 1, PLTRST),
	/* CAM2_PWR_EN */
	PAD_CFG_GPO(GPP_E16, 1, PLTRST),

	/* IMGCLKOUT */
	PAD_CFG_NF(GPP_D4, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H20, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H21, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H22, NONE, DEEP, NF1),

	/* BT_RF_KILL_N */
	PAD_CFG_GPO(GPP_A13, 1, PLTRST),

	/* D13 : WIFI_WAKE_N */
	PAD_CFG_NF(GPP_D13, NONE, DEEP, NF1),
	/* WIFI RF KILL */
	PAD_CFG_GPO(GPP_E3, 1, PLTRST),

	/* F0 : CNV_BRI_DT_BT_UART2_RTS_N */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	/* F1 : CNV_BRI_RSP_BT_UART2_RXD */
	PAD_CFG_NF(GPP_F1, NONE, DEEP, NF1),
	/* F2 : CNV_RGI_DT_BT_UART2_TXD */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	/* F3 : CNV_RGI_RSP_BT_UART2_CTS_N */
	PAD_CFG_NF(GPP_F3, NONE, DEEP, NF1),
	/* F4 : CNV_RF_RESET_R_N */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F5 : MODEM_CLKREQ_R */
	PAD_CFG_NF(GPP_F5, NONE, DEEP, NF2),
	/* TCH PAD Power EN */
	PAD_CFG_GPO(GPP_F7, 1, PLTRST),

	/* UART_BT_WAKE_N */
	PAD_CFG_GPI_IRQ_WAKE(GPP_E0, NONE, DEEP, LEVEL, INVERT),
};

void variant_configure_gpio_pads(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
};

const struct cros_gpio *variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
