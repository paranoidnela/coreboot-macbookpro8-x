/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <soc/gpio.h>

/* Pad configuration in ramstage */
static const struct pad_config override_gpio_table[] = {
	/* A8  : WWAN_RF_DISABLE_ODL */
	PAD_NC(GPP_A8, NONE),

	/* B5  : SOC_I2C_SUB_SDA */
	PAD_NC(GPP_B5, NONE),
	/* B6  : SOC_I2C_SUB_SCL */
	PAD_NC(GPP_B6, NONE),

	/* D3  : WCAM_RST_L */
	PAD_NC(GPP_D3, NONE),
	/* D6  : WWAN_EN */
	PAD_NC(GPP_D6, NONE),
	/* D15 : EN_PP2800_WCAM_X */
	PAD_NC(GPP_D15, NONE),
	/* D16 : EN_PP1800_PP1200_WCAM_X */
	PAD_NC(GPP_D16, NONE),

	/* F12 : WWAN_RST_L */
	PAD_NC(GPP_F12, NONE),

	/* H19 : SOC_I2C_SUB_INT_ODL */
	PAD_NC(GPP_H19, NONE),
	/* H22 : WCAM_MCLK_R */
	PAD_NC(GPP_H22, NONE),
	/* H23 : WWAN_SAR_DETECT_ODL */
	PAD_NC(GPP_H23, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* A13 : GPP_A13 ==> GSC_SOC_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_A13, NONE, PLTRST, LEVEL, INVERT),
	/* E12 : THC0_SPI1_IO1 ==> SOC_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_E12, NONE, DEEP),
	/* F18 : THC1_SPI2_INT# ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_F18, NONE, DEEP),
	/* H4  : I2C0_SDA ==> SOC_I2C_GSC_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : I2C0_SCL ==> SOC_I2C_GSC_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H10 : UART0_RXD ==> UART_SOC_RX_DBG_TX */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF2),
	/* H11 : UART0_TXD ==> UART_SOC_TX_DBG_RX */
	PAD_CFG_NF(GPP_H11, NONE, DEEP, NF2),
};

const struct pad_config *variant_gpio_override_table(size_t *num)
{
	*num = ARRAY_SIZE(override_gpio_table);
	return override_gpio_table;
}

const struct pad_config *variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}
