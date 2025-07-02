/*
 * OLED_xian_shi.c
 *
 *  Created on: 2025年6月11日
 *      Author: ZhuanZ（无密码）
 */
#include "hal_data.h"
#include "oled.h"
#include "OLED_xian_shi.h"
#include "bmp.h"

uint8_t fen = 0;
uint8_t cheng = 0;
uint8_t lan = 0;
uint8_t hong = 0;
void OLED_xian_shi(void)
{
    /*  IIC接线
     * SCK--P408
     * SDA--P407
     * VDD--3.3V
     * GND--GND
     */

    OLED_Init();//初始化OLED
    OLED_Clear();//清空OLED屏幕

    //显示汉字
    //列，8个位一行 字体为16*16，第几个字
    OLED_ShowCHinese(0,0,0);//粉
    OLED_ShowCHinese(16,0,1);//色
    OLED_ShowCHinese(32,0,2);//：
    OLED_ShowCHinese(0,3,3);//橙
    OLED_ShowCHinese(16,3,4);//色
    OLED_ShowCHinese(32,3,5);//：
    OLED_ShowCHinese(0,6,6);//蓝
    OLED_ShowCHinese(16,6,7);//色
    OLED_ShowCHinese(32,6,8);//：
    OLED_ShowCHinese(96,0,10);//红
    OLED_ShowCHinese(96,3,11);//色
    OLED_ShowCHinese(112,3,12);//：
    OLED_ShowCHinese(64,0,9);//个
    OLED_ShowCHinese(64,3,9);//个
    OLED_ShowCHinese(64,6,9);//个
    OLED_ShowCHinese(112,6,13);//个

    //列，行，数字，字宽，字号
    OLED_ShowNum(48,0,fen,2,16);//粉色的个数
    OLED_ShowNum(48,3,cheng,2,16);//橙色的个数
    OLED_ShowNum(48,6,lan,2,16);//蓝色的个数
    OLED_ShowNum(96,6,hong,2,16);//红色的个数
    //延时2秒
    R_BSP_SoftwareDelay(2,BSP_DELAY_UNITS_SECONDS);
}
