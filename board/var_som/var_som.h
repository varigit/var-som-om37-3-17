/*
 * (C) Copyright 2008
 * Leonid Segal <leonid.s@variscite.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _VAR_SOM_H_
#define _VAR_SOM_H_

const omap3_sysinfo sysinfo = {
	DDR_STACKED,
	"Variscite VAR-SOM-OM37 board",
	"NAND",
};

/*
 * IEN  - Input Enable
 * IDIS - Input Disable
 * PTD  - Pull type Down
 * PTU  - Pull type Up
 * DIS  - Pull type selection is inactive
 * EN   - Pull type selection is active
 * M0   - Mode 0
 * The commented string gives the final mux configuration for that pin
 */
#define MUX_VAR_SOM() \
  /*GPMC*/\
	MUX_VAL(CP(GPMC_NCS1),		(IDIS | PTU | EN  | M0)) /*GPMC_nCS1*/\
	MUX_VAL(CP(GPMC_NCS4),		(IDIS | PTD | EN  | M4)) /*GPIO_55*/\
	MUX_VAL(CP(GPMC_NCS5),		(IDIS | PTU | EN  | M0)) /*GPMC_nCS5*/\
	MUX_VAL(CP(GPMC_NCS6),		(IEN  | PTD | DIS | M0)) /*GPMC_nCS6*/\
	MUX_VAL(CP(GPMC_WAIT1),		(IEN  | PTU | EN  | M4)) /*GPIO_63*/\
 /*Serial Interface*/\
	MUX_VAL(CP(UART3_CTS_RCTX),	(IEN  | PTD | EN  | M0)) /*UART3_CTS_RCTX*/\
	MUX_VAL(CP(HDQ_SIO),		(IDIS | PTU | EN  | M4)) /*HDQ_SIO*/\
	MUX_VAL(CP(MCSPI1_CLK),		(IEN  | PTD | DIS | M0)) /*McSPI1_CLK*/\
	MUX_VAL(CP(MCSPI1_SIMO),	(IEN  | PTD | DIS | M0)) /*McSPI1_SIMO */\
	MUX_VAL(CP(MCSPI1_SOMI),	(IEN  | PTD | DIS | M0)) /*McSPI1_SOMI */\
	MUX_VAL(CP(MCSPI1_CS0),		(IEN  | PTD | EN  | M0)) /*McSPI1_CS0*/\
	MUX_VAL(CP(MCSPI1_CS1),		(IDIS | PTD | EN  | M0)) /*McSPI1_CS1*/\
	MUX_VAL(CP(MCSPI1_CS2),		(IEN  | PTU | DIS | M4)) /*GPIO_176 */\
								 /* - LAN_INTR */\
 /*Control and debug */\
	MUX_VAL(CP(SYS_CLKOUT1),	(IEN  | PTU | EN  | M4)) /*GPIO_10*/\
	MUX_VAL(CP(SYS_CLKOUT2),	(IEN  | PTU | EN  | M4)) /*GPIO_186*/\
	MUX_VAL(CP(ETK_CLK_ES2),	(IEN  | PTU | EN  | M2)) /*MMC3_CLK*/\
	MUX_VAL(CP(ETK_CTL_ES2),	(IEN  | PTU | EN  | M2)) /*MMC3_CMD*/\
	MUX_VAL(CP(ETK_D0_ES2),		(IEN  | PTU | EN  | M4)) /*GPIO_14*/\
	MUX_VAL(CP(ETK_D3_ES2),		(IEN  | PTU | EN  | M2)) /*MMC3_DAT3*/\
	MUX_VAL(CP(ETK_D4_ES2),		(IEN  | PTU | EN  | M2)) /*MMC3_DAT0*/\
	MUX_VAL(CP(ETK_D5_ES2),		(IEN  | PTU | EN  | M2)) /*MMC3_DAT1*/\
	MUX_VAL(CP(ETK_D6_ES2),		(IEN  | PTU | EN  | M2)) /*MMC3_DAT2*/\
	MUX_VAL(CP(ETK_D7_ES2),		(IEN  | PTU | EN  | M4)) /*GPIO_21*/\
	MUX_VAL(CP(ETK_D8_ES2),		(IEN  | PTU | EN  | M4)) /*GPIO_22*/\
	MUX_VAL(CP(ETK_D9_ES2),		(IEN  | PTU | EN  | M4)) /*GPIO_23*/\
 /* DSS */\
        MUX_VAL(CP(DSS_PCLK),           (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_HSYNC),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_VSYNC),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_ACBIAS),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA0),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA1),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA2),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA3),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA4),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA5),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA6),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA7),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA8),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA9),          (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA10),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA11),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA12),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA13),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA14),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA15),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA16),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA17),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA18),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA19),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA20),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA21),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA22),         (IDIS | PTD | DIS | M0)) \
        MUX_VAL(CP(DSS_DATA23),         (IDIS | PTD | DIS | M0)) \
 /* McSPI */\
        MUX_VAL(CP(MCSPI2_CLK),         (IEN  | PTD | DIS | M0)) \
        MUX_VAL(CP(MCSPI2_SIMO),        (IEN  | PTD | DIS | M0)) \
        MUX_VAL(CP(MCSPI2_SOMI),        (IEN  | PTD | DIS | M0)) \
        MUX_VAL(CP(MCSPI2_CS0),         (IEN  | PTD | EN  | M0)) \

#define MUX_VAR_SOM_SDIO2_DIRECT() \
	MUX_VAL(CP(MMC2_CLK),		(IEN  | PTU | EN  | M0)) /*MMC2_CLK*/\
	MUX_VAL(CP(MMC2_CMD),		(IEN  | PTU | EN  | M0)) /*MMC2_CMD*/\
	MUX_VAL(CP(MMC2_DAT0),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT0*/\
	MUX_VAL(CP(MMC2_DAT1),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT1*/\
	MUX_VAL(CP(MMC2_DAT2),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT2*/\
	MUX_VAL(CP(MMC2_DAT3),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT3*/\
	MUX_VAL(CP(MMC2_DAT4),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT4*/\
	MUX_VAL(CP(MMC2_DAT5),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT5*/\
	MUX_VAL(CP(MMC2_DAT6),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT6*/\
	MUX_VAL(CP(MMC2_DAT7),		(IEN  | PTU | EN  | M0)) /*MMC2_DAT7*/\
	MUX_VAL(CP(MMC1_DAT4),		(IEN  | PTD | EN  | M4)) /*GPIO_126*/\
	MUX_VAL(CP(MMC1_DAT5),		(IEN  | PTU | EN  | M4)) /*GPIO_127*/\
	MUX_VAL(CP(MMC1_DAT6),		(IEN  | PTU | EN  | M4)) /*GPIO_128*/\
	MUX_VAL(CP(MMC1_DAT7),		(IEN  | PTU | EN  | M4)) /*GPIO_129*/
#endif
