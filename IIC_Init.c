/*
 * IIC_Init.c
 *
 *  Created on: 2025年6月11日
 *      Author: ZhuanZ（无密码）
 */
#include "hal_data.h"
#include "IIC_Init.h"

extern fsp_err_t err;

void IIC_Init(void)
{
    err =R_IIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);
    assert(FSP_SUCCESS == err);
}
