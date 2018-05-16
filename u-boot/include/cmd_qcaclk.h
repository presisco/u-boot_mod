/*
 * Commands related with PLL/clocks settings
 * for Qualcomm/Atheros WiSoCs
 *
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _CMD_QCACLK_H_
#define _CMD_QCACLK_H_

#include <soc/qca_soc_common.h>
#if (SOC_TYPE & QCA_AR933X_SOC)
	#include <soc/ar933x_pll_init.h>
#else
	#include <soc/qca95xx_pll_init.h>
#endif

#ifdef CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET

	#ifndef CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET
		#error "Missing definition for CONFIG_QCA_PLL_IN_FLASH_BLOCK_OFFSET"
	#endif

	#ifndef CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE
		#error "Missing definition for CONFIG_QCA_PLL_IN_FLASH_BLOCK_SIZE"
	#endif

	#if (SOC_TYPE & QCA_AR933X_SOC)
typedef struct {
	u32 cpu_pll_cfg;
	u32 cpu_clk_ctrl;
	u32 cpu_pll_dit;
} pll_regs;
	#else
typedef struct {
	u32 cpu_pll_cfg;
	u32 ddr_pll_cfg;
	u32 cpu_ddr_clk_ctrl;
	u32 cpu_pll_dit;
	u32 ddr_pll_dit;
} pll_regs;
	#endif /* SOC_TYPE & QCA_AR933X_SOC */

typedef struct {
	u32 spi_ctrl;
	pll_regs regs;
} clk_cfg_flash;

/*
 * Contains:
 * 1. CPU, RAM, AHB and SPI clocks [MHz]
 * 2. Target SPI_CONTROL register value
 * 3. Target PLL related register values,
 *    for 25 and 40 MHz XTAL types
 */
typedef struct {
	u16 cpu_clk;
	u16 ddr_clk;
	u16 ahb_clk;
	u8  spi_clk;

	u32 spi_ctrl;

	pll_regs xtal_25mhz;
	pll_regs xtal_40mhz;
} clk_profile;

static const clk_profile clk_profiles[] = {
	#if (SOC_TYPE & QCA_AR933X_SOC)
	{
		/* Tested! */
		400, 400, 200, 25,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(32, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(20, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	}, {
		/* Tested! */
		450, 450, 225, 28,
		_ar933x_spi_ctrl_addr_reg_val(8, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(36, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(45, 2, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	}, {
		/* Tested! */
		500, 500, 250, 25,
		_ar933x_spi_ctrl_addr_reg_val(10, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(40, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(25, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 1, 2),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 275, 137, 22,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(44, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(27, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(512)
		},
	}, {
		/* Tested! */
		580, 290, 145, 24,
		_ar933x_spi_ctrl_addr_reg_val(6, 1, 0),
		{
			_ar933x_cpu_pll_cfg_reg_val(46, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(410)
		}, {
			_ar933x_cpu_pll_cfg_reg_val(29, 1, 0, 1),
			_ar933x_cpu_clk_ctrl_reg_val(1, 2, 4),
			_ar933x_cpu_pll_dither_frac_reg_val(0)
		},
	},
	#else
	{
		/* Tested! */
		400, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		550, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(13, 1, 1, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(48),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 400, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(16, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(10, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Tested! */
		650, 600, 216, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Untested! */
		650, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(26, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(16, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(0)
		},
	}, {
		/* Overclock! */
		750, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(30, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(19, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		750, 600, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(30, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(19, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		750, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(30, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(19, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		800, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(32, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		800, 600, 266, 24,
		_qca95xx_spi_ctrl_addr_reg_val(11, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(32, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		800, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(32, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(20, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		900, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(36, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		900, 600, 240, 24,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(36, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(48, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(30, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 2, 5, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		900, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(36, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(22, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		1000, 600, 200, 25,
		_qca95xx_spi_ctrl_addr_reg_val(8, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(40, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 3, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		1000, 600, 250, 25,
		_qca95xx_spi_ctrl_addr_reg_val(10, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(40, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 4, 1, 1, 0),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	}, {
		/* Overclock! */
		1000, 600, 300, 25,
		_qca95xx_spi_ctrl_addr_reg_val(12, 1, 0, 2),
		{
			_qca95xx_cpu_pll_cfg_reg_val(40, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(24, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(0),
			_qca95xx_ddr_pll_dither_reg_val(0)
		}, {
			_qca95xx_cpu_pll_cfg_reg_val(25, 1, 0, 0, 0),
			_qca95xx_ddr_pll_cfg_reg_val(15, 1, 1, 0, 0),
			_qca95xx_cpu_ddr_clk_ctrl_reg_val(1, 1, 2, 1, 1, 1),
			_qca95xx_cpu_pll_dither_reg_val(16),
			_qca95xx_ddr_pll_dither_reg_val(256)
		},
	},
	#endif /* SOC_TYPE & QCA_AR933X_SOC */
};

/* Number of all profiles */
static u32 clk_profiles_cnt = sizeof(clk_profiles) / sizeof(clk_profile);

#endif /* CONFIG_QCA_PLL_IN_FLASH_MAGIC_OFFSET */

#endif /* _CMD_QCACLK_H_ */
