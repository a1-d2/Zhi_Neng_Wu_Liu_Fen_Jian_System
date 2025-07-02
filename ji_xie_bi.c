/*
 * duo_ji_cao_zuo.c
 *
 *  Created on: 2025年6月17日
 *      Author: ZhuanZ（无密码）
 */
#include "hal_data.h"
#include "bsp_gpt.h"
#include "ji_xie_bi.h"

void ji_xie_bi_Init(void)
{
/*****************************初始状态**********************************************************/
//机械臂一号舵机：3-8(3是最上面，8是最下面).二号舵机：4-8(4是最下面，8是最上面)，三号舵机：没有限制。四号舵机：8-5（8完全开，6夹住，5完整闭合）。
    Gpt_Pwm_Setduty_2(3);//机械臂一号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_4(4);//机械臂二号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_7(8);//机械臂三号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_8(8);//机械臂四号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
}

void ji_xie_bi_cao_zhuo(uint8_t a,uint8_t b,uint8_t c,uint8_t d)
{
//机械臂一号舵机：3-8(3是最上面，8是最下面).二号舵机：4-8(4是最下面，8是最上面)，三号舵机：没有限制。四号舵机：8-5（8完全开，6夹住，5完整闭合）。
    Gpt_Pwm_Setduty_2(a);//机械臂一号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_4(b);//机械臂二号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_7(c);//机械臂三号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
    Gpt_Pwm_Setduty_8(d);//机械臂四号舵机
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MICROSECONDS);
}

void jia_qu(void)
{
     //机械臂一号舵机：3-8(3是最上面，8是最下面).二号舵机：4-8(4是最下面，8是最上面)，
    //三号舵机：8->12向左.四号舵机：8-5（8完全开，6夹住，5完整闭合）。
    ji_xie_bi_cao_zhuo(3,6,8,8);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(4,6,8,8);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(5,6,8,8);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(5,6,8,5);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(3,6,8,5);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(3,8,8,5);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(3,8,6,5);
    R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(3,8,5,5);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(3,6,5,5);
    R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(4,4,5,5);
    R_BSP_SoftwareDelay(700,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(4,4,5,8);
    R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(4,4,6,8);
    R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_cao_zhuo(4,4,7,8);
    R_BSP_SoftwareDelay(300,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
    ji_xie_bi_Init();
}


