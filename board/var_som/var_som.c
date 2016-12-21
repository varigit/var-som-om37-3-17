/*
 * Maintainer : Leonid Segal <leonid.s@variscite.com>
 *
 * Derived from Beagle Board, 3430 SDP, and OMAP3EVM code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *	Sunil Kumar <sunilsaini05@gmail.com>
 *	Shashi Ranjan <shashiranjanmca05@gmail.com>
 *
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <dm.h>
#include <ns16550.h>
#include <netdev.h>
#include <twl4030.h>
#include <linux/mtd/nand.h>
#include <asm/io.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/mux.h>
#include <asm/arch/mem.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/mach-types.h>
#include <asm/arch/dss.h>
#include <spi.h>
#include "var_som.h"
#include "bootsplash.h"


#ifdef CONFIG_USB_EHCI
#include <usb.h>
#include <asm/ehci-omap.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define TWL4030_I2C_BUS			0

static const struct ns16550_platdata var_som_serial = {
	OMAP34XX_UART3,
	2,
	V_NS16550_CLK
};

U_BOOT_DEVICE(var_som_uart) = {
	"serial_omap",
	&var_som_serial
};

/*
 * Routine: get_sdio2_config
 * Description: Return information about the wifi module connection
 *              Returns 0 if the module connects though a level translator
 *              Returns 1 if the module connects directly
 */
int get_sdio2_config(void)
{
	int sdio_direct;

	if (!gpio_request(130, "") && !gpio_request(139, "")) {

		gpio_direction_output(130, 0);
		gpio_direction_input(139);

		sdio_direct = 1;
		gpio_set_value(130, 0);
		if (gpio_get_value(139) == 0) {
			gpio_set_value(130, 1);
			if (gpio_get_value(139) == 1)
				sdio_direct = 0;
		}

		gpio_direction_input(130);
	} else {
		puts("Error: unable to acquire sdio2 clk GPIOs\n");
		sdio_direct = -1;
	}

	return sdio_direct;
}

static int lcd_spi_init(void)
{
	int i;
	int ret = 0;
	struct spi_slave *slave;
	uchar dout[2];
	uchar din[2];
	int init_messages[21]={	0x0207,0x0600,0x0A03,0x0ECC,
				0x1246,0x160D,0x1A00,0x1E00,
				0x2208,0x2640,0x2A88,0x2E88,
				0x3220,0x3620,0x3A6B,0x3E24,
				0x4204,0x4624,0x4A24,0x7A00,
				0x8200};


	slave = spi_setup_slave(1, 0, 1000000, 0);
	if (!slave) {
		printf("Invalid device %d:%d\n", 2, 0);
		return -EINVAL;
	}

	ret = spi_claim_bus(slave);
	if (ret)
		goto done;
	
	for(i=0;i<21;i++)
	{
		dout[0]=(uchar)(init_messages[i]>>8);
		dout[1]=(uchar)(init_messages[i]&0xff);
		ret = spi_xfer(slave, 16, dout, din, SPI_XFER_BEGIN | SPI_XFER_END);
		if (ret) {
			printf("Error %d during SPI transaction\n", ret);
		}
	}
done:
	spi_release_bus(slave);
	return ret;
}

/*
 * Routine: misc_init_r
 * Description: Configure board specific parts
 */
#define BACKLIGHT	55
static struct panel_config lcd_cfg = {
	.timing_h       = PANEL_TIMING_H(38, 18, 30),
	.timing_v       = PANEL_TIMING_V(11, 10, 2),
	.pol_freq       = DSS_IHS | DSS_IVS | DSS_IPC,
	.divisor        = 12 | (1 << 16),
	.panel_type     = ACTIVE_DISPLAY,
	.data_lines     = LCD_INTERFACE_24_BIT,
	.load_mode      = 0x02, /* Frame Mode */
	.panel_color    = 0,
	.gfx_format     = GFXFORMAT_RGB16,
	.frame_buffer	= (void*)gimp_image,
	.lcd_size       = PANEL_LCD_SIZE(320, 240),
};

int misc_init_r(void)
{
	twl4030_power_init();

	puts("Direct connection on mmc2\n");
	MUX_VAR_SOM_SDIO2_DIRECT();
	MUX_VAR_SOM();

	lcd_spi_init();

        omap3_dss_panel_config(&lcd_cfg);
        omap3_dss_enable();

        gpio_request(BACKLIGHT, "Backlight");
        gpio_direction_output(BACKLIGHT, 0);

	return 0;
}

#if defined(CONFIG_CMD_NET)
/* GPMC definitions for LAN9221 chips on Tobi expansion boards */
static const u32 gpmc_lan_config[] = {
	NET_LAN9221_GPMC_CONFIG1,
	NET_LAN9221_GPMC_CONFIG2,
	NET_LAN9221_GPMC_CONFIG3,
	NET_LAN9221_GPMC_CONFIG4,
	NET_LAN9221_GPMC_CONFIG5,
	NET_LAN9221_GPMC_CONFIG6,
	/*CONFIG7- computed as params */
};

/*
 * Routine: setup_net_chip
 * Description: Setting up the configuration GPMC registers specific to the
 *	      Ethernet hardware.
 */
static void setup_net_chip(void)
{
	struct ctrl *ctrl_base = (struct ctrl *)OMAP34XX_CTRL_BASE;

	/* Enable off mode for NWE in PADCONF_GPMC_NWE register */
	writew(readw(&ctrl_base ->gpmc_nwe) | 0x0E00, &ctrl_base->gpmc_nwe);
	/* Enable off mode for NOE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_noe) | 0x0E00, &ctrl_base->gpmc_noe);
	/* Enable off mode for ALE in PADCONF_GPMC_NADV_ALE register */
	writew(readw(&ctrl_base->gpmc_nadv_ale) | 0x0E00,
		&ctrl_base->gpmc_nadv_ale);
}

/*
 * Routine: reset_net_chip
 * Description: Reset the Ethernet hardware.
 */
static void reset_net_chip(void)
{
	/* Make GPIO 64 as output pin and send a magic pulse through it */
	if (!gpio_request(64, "")) {
		gpio_direction_output(64, 0);
		gpio_set_value(64, 1);
		udelay(1);
		gpio_set_value(64, 0);
		udelay(1);
		gpio_set_value(64, 1);
	}
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;

#ifdef CONFIG_SMC911X
	enable_gpmc_cs_config(gpmc_lan_config, &gpmc_cfg->cs[5],
				      0x2C000000, GPMC_SIZE_16M);
	setup_net_chip();
	reset_net_chip();
	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);
#endif

	return rc;
}
#endif

#if defined(CONFIG_GENERIC_MMC)
int board_mmc_init(bd_t *bis)
{
	return omap_mmc_init(0, 0, 0, -1, -1);
}
#endif

#if defined(CONFIG_GENERIC_MMC)
void board_mmc_power_init(void)
{
	twl4030_power_mmc_init(0);
}
#endif

#if defined(CONFIG_USB_EHCI)
static struct omap_usbhs_board_data usbhs_bdata = {
	.port_mode[0] = OMAP_USBHS_PORT_MODE_UNUSED,
	.port_mode[1] = OMAP_EHCI_PORT_MODE_PHY,
	.port_mode[2] = OMAP_USBHS_PORT_MODE_UNUSED
};

#define VAR_SOM_GPIO_USBH_CPEN		168
int ehci_hcd_init(int index, enum usb_init_type init,
		  struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
	/* Enable USB power */
	if (!gpio_request(VAR_SOM_GPIO_USBH_CPEN, "usbh_cpen"))
		gpio_direction_output(VAR_SOM_GPIO_USBH_CPEN, 1);

	return omap_ehci_hcd_init(index, &usbhs_bdata, hccr, hcor);
}

int ehci_hcd_stop(void)
{
	/* Disable USB power */
	gpio_set_value(VAR_SOM_GPIO_USBH_CPEN, 0);
	gpio_free(VAR_SOM_GPIO_USBH_CPEN);

	return omap_ehci_hcd_stop();
}

#endif /* CONFIG_USB_EHCI */
