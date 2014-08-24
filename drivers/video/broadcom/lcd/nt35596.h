/*******************************************************************************
* Copyright 2013 Broadcom Corporation.	All rights reserved.
*
* @file drivers/video/broadcom/lcd/nt35596.h
*
* Unless you and Broadcom execute a separate written software license agreement
* governing use of this software, this software is licensed to you under the
* terms of the GNU General Public License version 2, available at
* http://www.gnu.org/copyleft/gpl.html (the "GPL").
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a license
* other than the GPL, without Broadcom's express prior written consent.
*******************************************************************************/

#ifndef __NT35596_H__
#define __NT35596_H__

#include "display_drv.h"
#include "lcd.h"

#define NT35596_CMD_SLPIN	0x10
#define NT35596_CMD_SLPOUT	0x11
#define NT35596_CMD_DISPOFF	0x28
#define NT35596_CMD_DISPON	0x29
#define NT35596_CMD_DSTBON	0x4F
#define NT35596_CMD_RDID1      0xDA
#define NT35596_CMD_RDID2      0xDB
#define NT35596_CMD_RDID3      0xDC


__initdata struct DSI_COUNTER nt35596_timing[] = {
	/* LP Data Symbol Rate Calc - MUST BE FIRST RECORD */
	{"ESC2LP_RATIO", DSI_C_TIME_ESC2LPDT, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0x0000003F, 1, 1, 0},
	/* SPEC:  min =  100[us] + 0[UI] */
	/* SET:   min = 1000[us] + 0[UI]                             <= */
	{"HS_INIT", DSI_C_TIME_HS, 0,
		0, 100000, 0, 0, 0, 0, 0, 0, 0x00FFFFFF, 0, 0, 0},
	/* SPEC:  min = 1[ms] + 0[UI] */
	/* SET:   min = 1[ms] + 0[UI] */
	{"HS_WAKEUP", DSI_C_TIME_HS, 0,
		0, 1000000, 0, 0, 0, 0, 0, 0, 0x00FFFFFF, 0, 0, 0},
	/* SPEC:  min = 1[ms] + 0[UI] */
	/* SET:   min = 1[ms] + 0[UI] */
	{"LP_WAKEUP", DSI_C_TIME_ESC, 0,
		0, 1000000, 0, 0, 0, 0, 0, 0, 0x00FFFFFF, 1, 1, 0},
	/* SPEC:  min = 0[ns] +  8[UI] */
	/* SET:   min = 0[ns] + 12[UI]                               <= */
	{"HS_CLK_PRE", DSI_C_TIME_HS, 0,
		0, 0, 12, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = 38[ns] + 0[UI]   max= 95[ns] + 0[UI] */
	/* SET:   min = 48[ns] + 0[UI]   max= 95[ns] + 0[UI]         <= */
	{"HS_CLK_PREPARE", DSI_C_TIME_HS, DSI_C_HAS_MAX,
		0, 48, 0, 0, 0, 95, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = 262[ns] + 0[UI] */
	/* SET:   min = 262[ns] + 0[UI]                              <= */
	{"HS_CLK_ZERO", DSI_C_TIME_HS, 0,
		0, 262, 0, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min =  60[ns] + 52[UI] */
	/* SET:   min =  70[ns] + 52[UI]                             <= */
	{"HS_CLK_POST", DSI_C_TIME_HS, 0,
		0, 70, 52, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min =  60[ns] + 0[UI] */
	/* SET:   min =  70[ns] + 0[UI]                              <= */
	{"HS_CLK_TRAIL", DSI_C_TIME_HS, 0,
		0, 70, 0, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min =  50[ns] + 0[UI] */
	/* SET:   min =  60[ns] + 0[UI]                              <= */
	{"HS_LPX", DSI_C_TIME_HS, 0,
		0, 60, 0, 0, 0, 75, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = 40[ns] + 4[UI]      max= 85[ns] + 6[UI] */
	/* SET:   min = 50[ns] + 4[UI]      max= 85[ns] + 6[UI]      <= */
	{"HS_PRE", DSI_C_TIME_HS, DSI_C_HAS_MAX,
		0, 50, 4, 0, 0, 85, 6, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = 105[ns] + 6[UI] */
	/* SET:   min = 105[ns] + 6[UI]                              <= */
	{"HS_ZERO", DSI_C_TIME_HS, 0,
		0, 105, 6, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = max(0[ns]+32[UI],60[ns]+16[UI])  n=4 */
	/* SET:   min = max(0[ns]+32[UI],60[ns]+16[UI])  n=4 */
	{"HS_TRAIL", DSI_C_TIME_HS, DSI_C_MIN_MAX_OF_2,
		0, 0, 32, 60, 16, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* SPEC:  min = 100[ns] + 0[UI] */
	/* SET:   min = 110[ns] + 0[UI]                              <= */
	{"HS_EXIT", DSI_C_TIME_HS, 0,
		0, 110, 0, 0, 0, 0, 0, 0, 0x000001FF, 0, 0, 0},
	/* min = 50[ns] + 0[UI] */
	/* LP esc counters are speced in LP LPX units.
	   LP_LPX is calculated by chal_dsi_set_timing
	   and equals LP data clock */
	{"LPX", DSI_C_TIME_ESC, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0x000000FF, 1, 1, 0},
	/* min = 4*[Tlpx]  max = 4[Tlpx], set to 4 */
	{"LP-TA-GO", DSI_C_TIME_ESC, 0,
		4, 0, 0, 0, 0, 0, 0, 0, 0x000000FF, 1, 1, 0},
	/* min = 1*[Tlpx]  max = 2[Tlpx], set to 2 */
	{"LP-TA-SURE", DSI_C_TIME_ESC, 0,
		2, 0, 0, 0, 0, 0, 0, 0, 0x000000FF, 1, 1, 0},
	/* min = 5*[Tlpx]  max = 5[Tlpx], set to 5 */
	{"LP-TA-GET", DSI_C_TIME_ESC, 0,
		5, 0, 0, 0, 0, 0, 0, 0, 0x000000FF, 1, 1, 0},
};

__initdata DISPCTRL_REC_T nt35596_scrn_on[] = {
	{DISPCTRL_WR_CMND, 0x13},
	{DISPCTRL_WR_CMND, NT35596_CMD_DISPON},
	{DISPCTRL_LIST_END, 0}
};

__initdata DISPCTRL_REC_T nt35596_scrn_off[] = {
	{DISPCTRL_WR_CMND, 0x22},
	/* Commenting this since it results in a white screen
	{DISPCTRL_WR_CMND, NT35596_CMD_DISPOFF}, */
	{DISPCTRL_LIST_END, 0}
};

__initdata DISPCTRL_REC_T nt35596_id[] = {
	{DISPCTRL_WR_CMND, NT35596_CMD_RDID1},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, NT35596_CMD_RDID2},
	{DISPCTRL_WR_DATA, 0x80},
	{DISPCTRL_WR_CMND, NT35596_CMD_RDID3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_LIST_END, 0}
};

__initdata DISPCTRL_REC_T nt35596_slp_in[] = {
	{DISPCTRL_WR_CMND, NT35596_CMD_DISPOFF},
	{DISPCTRL_WR_CMND, NT35596_CMD_SLPIN},
	{DISPCTRL_SLEEP_MS, 120},
	{DISPCTRL_WR_CMND, NT35596_CMD_DSTBON},
	{DISPCTRL_WR_DATA, 1},
	{DISPCTRL_LIST_END, 0}
};

__initdata DISPCTRL_REC_T nt35596_slp_out[] = {
	{DISPCTRL_WR_CMND, NT35596_CMD_SLPOUT},
	{DISPCTRL_SLEEP_MS, 120},
	{DISPCTRL_LIST_END, 0}
};

__initdata DISPCTRL_REC_T nt35596_init_panel_vid[] = {
	{DISPCTRL_WR_CMND, 0xFF},
	{DISPCTRL_WR_DATA, 0x05},/*CMD2 P4*/
	{DISPCTRL_SLEEP_MS, 5},
	{DISPCTRL_WR_CMND, 0x90},
	{DISPCTRL_WR_DATA, 0x00},/*Resolution 1080RGBx1920*/
	{DISPCTRL_WR_CMND, 0x93},
	{DISPCTRL_WR_DATA, 0x04},/*FP/BP  LTPS_CTRL3*/
	{DISPCTRL_WR_CMND, 0x94},
	{DISPCTRL_WR_DATA, 0x04},/*LTPS_CTRL4*/
	{DISPCTRL_WR_CMND, 0x9B},
	{DISPCTRL_WR_DATA, 0x0F},/*SOURCE CTRL4  Inversion Type Column*/
	/*LTPS_CTRL1	Frame rate control in full colors normal mode*/
	{DISPCTRL_WR_CMND, 0x91},
	{DISPCTRL_WR_DATA, 0x44},
	{DISPCTRL_WR_CMND, 0x92},
	{DISPCTRL_WR_DATA, 0x79},
	{DISPCTRL_WR_CMND, 0x00},
	{DISPCTRL_WR_DATA, 0x0F},/*CGOUT Mapping*/
	{DISPCTRL_WR_CMND, 0x01},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x02},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x03},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x04},
	{DISPCTRL_WR_DATA, 0x0B},
	{DISPCTRL_WR_CMND, 0x05},
	{DISPCTRL_WR_DATA, 0x0C},
	{DISPCTRL_WR_CMND, 0x06},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x07},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x08},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x09},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x0A},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x0B},
	{DISPCTRL_WR_DATA, 0x04},
	{DISPCTRL_WR_CMND, 0x0C},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x0D},
	{DISPCTRL_WR_DATA, 0x13},
	{DISPCTRL_WR_CMND, 0x0E},
	{DISPCTRL_WR_DATA, 0x15},
	{DISPCTRL_WR_CMND, 0x0F},
	{DISPCTRL_WR_DATA, 0x17},
	{DISPCTRL_WR_CMND, 0x10},
	{DISPCTRL_WR_DATA, 0x0F},
	{DISPCTRL_WR_CMND, 0x11},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x12},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x13},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x14},
	{DISPCTRL_WR_DATA, 0x0B},
	{DISPCTRL_WR_CMND, 0x15},
	{DISPCTRL_WR_DATA, 0x0C},
	{DISPCTRL_WR_CMND, 0x16},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x17},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x18},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x19},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x1A},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x1B},
	{DISPCTRL_WR_DATA, 0x04},
	{DISPCTRL_WR_CMND, 0x1C},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x1D},
	{DISPCTRL_WR_DATA, 0x13},
	{DISPCTRL_WR_CMND, 0x1E},
	{DISPCTRL_WR_DATA, 0x15},
	{DISPCTRL_WR_CMND, 0x1F},
	{DISPCTRL_WR_DATA, 0x17},
	{DISPCTRL_WR_CMND, 0x20},
	{DISPCTRL_WR_DATA, 0x09},/*GVST*/
	{DISPCTRL_WR_CMND, 0x21},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x22},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x23},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x24},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x25},
	{DISPCTRL_WR_DATA, 0xED},
	{DISPCTRL_WR_CMND, 0x2F},
	{DISPCTRL_WR_DATA, 0x02},/*GCLK 1/2*/
	{DISPCTRL_WR_CMND, 0x30},
	{DISPCTRL_WR_DATA, 0x04},
	{DISPCTRL_WR_CMND, 0x31},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0x32},
	{DISPCTRL_WR_DATA, 0x23},
	{DISPCTRL_WR_CMND, 0x33},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x34},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x35},
	{DISPCTRL_WR_DATA, 0x69},
	{DISPCTRL_WR_CMND, 0x36},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x37},
	{DISPCTRL_WR_DATA, 0x2D},
	{DISPCTRL_WR_CMND, 0x38},
	{DISPCTRL_WR_DATA, 0x18},
	{DISPCTRL_WR_CMND, 0x29},
	{DISPCTRL_WR_DATA, 0x58},/*UD*/
	{DISPCTRL_WR_CMND, 0x2A},
	{DISPCTRL_WR_DATA, 0x16},
	{DISPCTRL_WR_CMND, 0x2B},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0x5B},
	{DISPCTRL_WR_DATA, 0x00},/*APO*/
	{DISPCTRL_WR_CMND, 0x5F},
	{DISPCTRL_WR_DATA, 0x75},
	{DISPCTRL_WR_CMND, 0x63},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x67},
	{DISPCTRL_WR_DATA, 0x04},
	{DISPCTRL_WR_CMND, 0x6C},
	{DISPCTRL_WR_DATA, 0x00},
	/*{DISPCTRL_WR_CMND, 0x7A},
	{DISPCTRL_WR_DATA, 0x01},*/ /*MUX*/
	{DISPCTRL_WR_CMND, 0x7B},
	{DISPCTRL_WR_DATA, 0x80},
	{DISPCTRL_WR_CMND, 0x7C},
	{DISPCTRL_WR_DATA, 0xD8},
	{DISPCTRL_WR_CMND, 0x7D},
	{DISPCTRL_WR_DATA, 0x60},
	{DISPCTRL_WR_CMND, 0x7E},
	{DISPCTRL_WR_DATA, 0x0B},
	{DISPCTRL_WR_CMND, 0x7F},
	{DISPCTRL_WR_DATA, 0x17},
	{DISPCTRL_WR_CMND, 0x80},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x81},
	{DISPCTRL_WR_DATA, 0x06},
	{DISPCTRL_WR_CMND, 0x82},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x83},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x84},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x85},
	{DISPCTRL_WR_DATA, 0x07},
	{DISPCTRL_WR_CMND, 0x86},
	{DISPCTRL_WR_DATA, 0x1B},
	{DISPCTRL_WR_CMND, 0x87},
	{DISPCTRL_WR_DATA, 0x39},
	{DISPCTRL_WR_CMND, 0x88},
	{DISPCTRL_WR_DATA, 0x1B},
	{DISPCTRL_WR_CMND, 0x89},
	{DISPCTRL_WR_DATA, 0x39},
	{DISPCTRL_WR_CMND, 0x8A},
	{DISPCTRL_WR_DATA, 0x33},
	/*{DISPCTRL_WR_CMND, 0x8B},
	{DISPCTRL_WR_DATA, 0x00},*/
	{DISPCTRL_WR_CMND, 0xA4},
	{DISPCTRL_WR_DATA, 0x0F},
	{DISPCTRL_WR_CMND, 0x8C},
	{DISPCTRL_WR_DATA, 0x01},
	/*{DISPCTRL_WR_CMND, 0x73},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0x74},
	{DISPCTRL_WR_DATA, 0x0B},
	{DISPCTRL_WR_CMND, 0x75},
	{DISPCTRL_WR_DATA, 0x17},
	{DISPCTRL_WR_CMND, 0x76},
	{DISPCTRL_WR_DATA, 0x0B},*/
	{DISPCTRL_WR_CMND, 0x99},
	{DISPCTRL_WR_DATA, 0x33},/*SOURCE_CTRL1~3*/
	/*{DISPCTRL_WR_CMND, 0x98},
	{DISPCTRL_WR_DATA, 0x00},*/
	{DISPCTRL_WR_CMND, 0xB5},
	{DISPCTRL_WR_DATA, 0x20},
	/*******************************************************************/

	/*Power Related*/
	{DISPCTRL_WR_CMND, 0xFF},
	{DISPCTRL_WR_DATA, 0x01},/*CMD2 P0*/

	{DISPCTRL_SLEEP_MS, 5},

	{DISPCTRL_WR_CMND, 0x00},
	{DISPCTRL_WR_DATA, 0x01},/*Normal Black Panel*/
	/*01 02 VGH/ VGL Step-up Frequency   VCL Step-up Frequency*/

	/*{DISPCTRL_WR_CMND, 0x01},
	{DISPCTRL_WR_DATA, 0x57},*/

	/*PUMP VGH=2xAVDD},{DISPCTRL_WR_DATA,  VGL=2AVEE	 */
	{DISPCTRL_WR_CMND, 0x05},
	{DISPCTRL_WR_DATA, 0x50},
	/*EN_PRE_REG enable the VGH clamp voltage function  vgh_reg=9.2v*/
	{DISPCTRL_WR_CMND, 0x06},
	{DISPCTRL_WR_DATA, 0xA0},
	{DISPCTRL_WR_CMND, 0x14},
	{DISPCTRL_WR_DATA, 0xA8},
	{DISPCTRL_WR_CMND, 0x07},
	{DISPCTRL_WR_DATA, 0xB2},/*set the VGL clamp voltage level*/
	{DISPCTRL_WR_CMND, 0x0E},
	{DISPCTRL_WR_DATA, 0xBF},/*adjust the VGHO voltage*/
	{DISPCTRL_WR_CMND, 0x0F},
	{DISPCTRL_WR_DATA, 0xC2},/*adjust the VGLO voltage*/
	{DISPCTRL_WR_CMND, 0x0B},
	{DISPCTRL_WR_DATA, 0xB3},/*Gamma Voltage Setting GVDDP*/
	{DISPCTRL_WR_CMND, 0x0C},
	{DISPCTRL_WR_DATA, 0xB3},/*GVDDN=-4.64*/
	{DISPCTRL_WR_CMND, 0x11},
	{DISPCTRL_WR_DATA, 0x28},/*VCOM setting VCOM=-0.4V*/
	{DISPCTRL_WR_CMND, 0x12},
	{DISPCTRL_WR_DATA, 0x28},
	{DISPCTRL_WR_CMND, 0x08},
	{DISPCTRL_WR_DATA, 0x0C},
	{DISPCTRL_WR_CMND, 0x15},
	{DISPCTRL_WR_DATA, 0x15},
	{DISPCTRL_WR_CMND, 0x16},
	{DISPCTRL_WR_DATA, 0x15},


	/*# R+*/

	{DISPCTRL_WR_CMND, 0x75},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x76},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x77},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x78},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0x79},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7A},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0x7B},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7C},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0x7D},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7E},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0x7F},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x80},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0x81},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x82},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0x83},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x84},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0x85},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x86},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0x87},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x88},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0x89},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x8A},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0x8B},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x8C},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0x8D},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x8E},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0x8F},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x90},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0x91},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x92},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x93},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x94},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0x95},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x96},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0x97},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x98},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0x99},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x9A},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0x9B},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x9C},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0x9D},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x9E},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0x9F},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA0},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0xA2},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA3},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0xA4},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA5},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0xA6},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA7},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0xA9},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAA},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0xAB},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAC},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0xAD},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAE},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0xAF},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xB0},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0xB1},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xB2},
	{DISPCTRL_WR_DATA, 0xFF},

	/*# R-*/

	{DISPCTRL_WR_CMND, 0xB3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB4},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xB5},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB6},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0xB7},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB8},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0xB9},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBA},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0xBB},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBC},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0xBD},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBE},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0xBF},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC0},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0xC1},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC2},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0xC3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC4},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0xC5},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC6},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0xC7},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC8},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0xC9},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xCA},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0xCB},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xCC},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0xCD},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xCE},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0xCF},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD0},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xD1},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD2},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0xD3},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD4},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0xD5},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD6},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0xD7},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD8},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0xD9},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xDA},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0xDB},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xDC},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0xDD},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xDE},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0xDF},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE0},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0xE1},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE2},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0xE3},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE4},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0xE5},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE6},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0xE7},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE8},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0xE9},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xEA},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0xEB},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xEC},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0xED},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xEE},
	{DISPCTRL_WR_DATA, 0xFF},

	/*# G+*/
	{DISPCTRL_WR_CMND, 0xEF},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xF0},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xF1},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xF2},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0xF3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xF4},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0xF5},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xF6},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0xF7},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xF8},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0xF9},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xFA},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0xFF},
	{DISPCTRL_WR_DATA, 0x02},/*# Page 0 power-related setting*/

	{DISPCTRL_SLEEP_MS, 5},
	{DISPCTRL_WR_CMND, 0x00},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x01},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0x02},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x03},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0x04},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x05},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0x06},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x07},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0x08},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x09},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0x0A},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x0B},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0x0C},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x0D},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0x0E},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x0F},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0x10},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x11},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x12},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x13},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0x14},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x15},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0x16},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x17},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0x18},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x19},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0x1A},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x1B},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0x1C},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x1D},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0x1E},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x1F},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0x20},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x21},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0x22},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x23},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0x24},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x25},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0x26},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x27},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0x28},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x29},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0x2A},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x2B},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0x2D},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x2F},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0x30},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x31},
	{DISPCTRL_WR_DATA, 0xFF},
	/*# G-*/
	{DISPCTRL_WR_CMND, 0x32},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x33},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x34},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x35},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0x36},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x37},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0x38},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x39},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0x3A},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x3B},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0x3D},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x3F},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0x40},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x41},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0x42},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x43},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0x44},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x45},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0x46},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x47},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0x48},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x49},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0x4A},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x4B},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0x4C},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x4D},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0x4E},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x4F},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0x50},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x51},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x52},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x53},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0x54},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x55},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0x56},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x58},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0x59},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x5A},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0x5B},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x5C},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0x5D},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x5E},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0x5F},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x60},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0x61},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x62},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0x63},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x64},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0x65},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x66},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0x67},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x68},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0x69},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x6A},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0x6B},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x6C},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0x6D},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x6E},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0x6F},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x70},
	{DISPCTRL_WR_DATA, 0xFF},
	/*# B+*/
	{DISPCTRL_WR_CMND, 0x71},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x72},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x73},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x74},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0x75},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x76},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0x77},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x78},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0x79},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7A},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0x7B},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7C},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0x7D},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x7E},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0x7F},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x80},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0x81},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x82},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0x83},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x84},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0x85},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0x86},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0x87},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x88},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0x89},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x8A},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0x8B},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0x8C},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0x8D},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x8E},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x8F},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x90},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0x91},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x92},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0x93},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x94},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0x95},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x96},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0x97},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0x98},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0x99},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x9A},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0x9B},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x9C},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0x9D},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0x9E},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0x9F},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA0},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0xA2},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA3},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0xA4},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA5},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0xA6},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xA7},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0xA9},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAA},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0xAB},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAC},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0xAD},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xAE},
	{DISPCTRL_WR_DATA, 0xFF},
	/*# B-*/
	{DISPCTRL_WR_CMND, 0xAF},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB0},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xB1},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB2},
	{DISPCTRL_WR_DATA, 0x0E},
	{DISPCTRL_WR_CMND, 0xB3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB4},
	{DISPCTRL_WR_DATA, 0x25},
	{DISPCTRL_WR_CMND, 0xB5},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB6},
	{DISPCTRL_WR_DATA, 0x38},
	{DISPCTRL_WR_CMND, 0xB7},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xB8},
	{DISPCTRL_WR_DATA, 0x49},
	{DISPCTRL_WR_CMND, 0xB9},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBA},
	{DISPCTRL_WR_DATA, 0x59},
	{DISPCTRL_WR_CMND, 0xBB},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBC},
	{DISPCTRL_WR_DATA, 0x6A},
	{DISPCTRL_WR_CMND, 0xBD},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xBE},
	{DISPCTRL_WR_DATA, 0x76},
	{DISPCTRL_WR_CMND, 0xBF},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC0},
	{DISPCTRL_WR_DATA, 0x83},
	{DISPCTRL_WR_CMND, 0xC1},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC2},
	{DISPCTRL_WR_DATA, 0xB2},
	{DISPCTRL_WR_CMND, 0xC3},
	{DISPCTRL_WR_DATA, 0x00},
	{DISPCTRL_WR_CMND, 0xC4},
	{DISPCTRL_WR_DATA, 0xDB},
	{DISPCTRL_WR_CMND, 0xC5},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xC6},
	{DISPCTRL_WR_DATA, 0x1F},
	{DISPCTRL_WR_CMND, 0xC7},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xC8},
	{DISPCTRL_WR_DATA, 0x58},
	{DISPCTRL_WR_CMND, 0xC9},
	{DISPCTRL_WR_DATA, 0x01},
	{DISPCTRL_WR_CMND, 0xCA},
	{DISPCTRL_WR_DATA, 0xB6},
	{DISPCTRL_WR_CMND, 0xCB},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xCC},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xCD},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xCE},
	{DISPCTRL_WR_DATA, 0x05},
	{DISPCTRL_WR_CMND, 0xCF},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD0},
	{DISPCTRL_WR_DATA, 0x46},
	{DISPCTRL_WR_CMND, 0xD1},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD2},
	{DISPCTRL_WR_DATA, 0x90},
	{DISPCTRL_WR_CMND, 0xD3},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD4},
	{DISPCTRL_WR_DATA, 0xB5},
	{DISPCTRL_WR_CMND, 0xD5},
	{DISPCTRL_WR_DATA, 0x02},
	{DISPCTRL_WR_CMND, 0xD6},
	{DISPCTRL_WR_DATA, 0xF1},
	{DISPCTRL_WR_CMND, 0xD7},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xD8},
	{DISPCTRL_WR_DATA, 0x1D},
	{DISPCTRL_WR_CMND, 0xD9},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xDA},
	{DISPCTRL_WR_DATA, 0x5E},
	{DISPCTRL_WR_CMND, 0xDB},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xDC},
	{DISPCTRL_WR_DATA, 0x70},
	{DISPCTRL_WR_CMND, 0xDD},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xDE},
	{DISPCTRL_WR_DATA, 0x7B},
	{DISPCTRL_WR_CMND, 0xDF},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE0},
	{DISPCTRL_WR_DATA, 0x8B},
	{DISPCTRL_WR_CMND, 0xE1},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE2},
	{DISPCTRL_WR_DATA, 0x9A},
	{DISPCTRL_WR_CMND, 0xE3},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE4},
	{DISPCTRL_WR_DATA, 0xAB},
	{DISPCTRL_WR_CMND, 0xE5},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE6},
	{DISPCTRL_WR_DATA, 0xBB},
	{DISPCTRL_WR_CMND, 0xE7},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xE8},
	{DISPCTRL_WR_DATA, 0xD0},
	{DISPCTRL_WR_CMND, 0xE9},
	{DISPCTRL_WR_DATA, 0x03},
	{DISPCTRL_WR_CMND, 0xEA},
	{DISPCTRL_WR_DATA, 0xFF},

	{DISPCTRL_WR_CMND, 0xFF},
	{DISPCTRL_WR_DATA, 0x00},
	/*delay 1mS*/
	{DISPCTRL_SLEEP_MS, 5},
	/*CMD1 VBP=9,VFP=3*/
	{DISPCTRL_WR_CMND, 0xD3},
	{DISPCTRL_WR_DATA, 0x09},
	{DISPCTRL_WR_CMND, 0xD4},
	{DISPCTRL_WR_DATA, 0x03},

	{DISPCTRL_WR_CMND, 0x11},
	/*delay 120mS*/
	{DISPCTRL_SLEEP_MS, 200},
	{DISPCTRL_WR_CMND, 0x29},

};

void nt35596_winset(char *msgData, DISPDRV_WIN_t *p_win)
{
	return;
}

__initdata struct lcd_config nt35596_cfg = {
	.name = "NT35596",
	.mode_supp = LCD_VID_ONLY,
	.phy_timing = &nt35596_timing[0],
	.max_lanes = 4,
	.max_hs_bps = 1000000000,
	.max_lp_bps = 8000000,
	.phys_width = 62,
	.phys_height = 110,
	.init_cmd_seq = NULL,
	.init_vid_seq = &nt35596_init_panel_vid[0],
	.slp_in_seq = &nt35596_slp_in[0],
	.slp_out_seq = &nt35596_slp_out[0],
	.scrn_on_seq = &nt35596_scrn_on[0],
	.scrn_off_seq = &nt35596_scrn_off[0],
	.id_seq = &nt35596_id[0],
	.verify_id = false,
	.updt_win_fn = nt35596_winset,
	.updt_win_seq_len = 0,
	.vid_cmnds = false,
	.vburst = true,
	.cont_clk = false,
	.hs = 22,
	.hbp = 22,
	.hfp = 22,
	.vs = 2,
	.vbp = 8,
	.vfp = 8,
};

#endif
