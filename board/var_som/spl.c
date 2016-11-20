/*
 * Maintainer : Leonid Segal <leonid.s@variscite.com>
 *
 * Derived from Beagle Board, 3430 SDP, and OMAP3EVM code by
 *      Richard Woodruff <r-woodruff2@ti.com>
 *      Syed Mohammed Khasim <khasim@ti.com>
 *      Sunil Kumar <sunilsaini05@gmail.com>
 *      Shashi Ranjan <shashiranjanmca05@gmail.com>
 *
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <asm/io.h>
#include <asm/arch/mem.h>
#include <asm/arch/sys_proto.h>
#include "var_som.h"

/*
 * Routine: get_board_mem_timings
 * Description: If we use SPL then there is no x-loader nor config header
 * so we have to setup the DDR timings ourself on both banks.
 */
void get_board_mem_timings(struct board_sdrc_timings *timings)
{
	timings->mr = MICRON_V_MR_165;
	timings->mcfg = MICRON_V_MCFG_200(256 << 20);
	timings->ctrla = MICRON_V_ACTIMA_200;
	timings->ctrlb = MICRON_V_ACTIMB_200;
	timings->rfr_ctrl = SDP_3430_SDRC_RFR_CTRL_200MHz;
}
