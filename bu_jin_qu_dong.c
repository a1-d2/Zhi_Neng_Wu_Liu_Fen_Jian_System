/*
 * bu_jin_qu_dong.c
 *
 *  Created on: 2025年6月11日
 *      Author: ZhuanZ（无密码）
 */
#include "hal_data.h"
#include "bu_jin_qu_dong.h"
#include "duo_ji_qu_dong.h"



void bu_jin_qu_dong(void)
{
     /*步进电机一
     * 步进方向--P400
     * 步进脉冲--P412
     * 步进使能--P105
     * 红外--P104
     */
    bsp_io_level_t hong_wai;//这个变量用于存储接收的电平信号
    bsp_io_level_t yu_ying;
    bsp_io_level_t yu_ying_2;
    bsp_io_level_t an_jian1;
    bsp_io_level_t an_jian2;
    uint8_t start = 0;

    while(1)
    {
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, &an_jian1);
        if(an_jian1 == 0)
        {
            start = 1;
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_14, BSP_IO_LEVEL_LOW);
        }
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &an_jian2);
        if(an_jian2 == 0)
        {
            start = 0;
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_14, BSP_IO_LEVEL_HIGH);
        }
        if(start)
        {
           //一号步进电机旋转方向，高电平向左转,P400
           R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_LOW);
           //红外检测
           R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, &yu_ying);
           if(yu_ying)
           {
              //一号步进电机使能，高为停止
              R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_05, BSP_IO_LEVEL_HIGH);
           }
           else
           {
                //检测红外管是否有物体经过,输入检测，检测引脚有没有来自红外管的输入电平。默认是高电平，有物经过是低电平。
                //R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, &hong_wai);
                //有物体经过是低电平
               // if(hong_wai)
                //{
                    //一号电机使能，高电平没有物体经过，电机继续转动。设置成使能低电平，低使能是启动
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_05, BSP_IO_LEVEL_LOW);
                    //一号电机信号脉冲，高低电平来回切换，形成脉冲。
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_12, BSP_IO_LEVEL_HIGH);
                    //延时,50us一个脉冲
                    R_BSP_SoftwareDelay(50,BSP_DELAY_UNITS_MICROSECONDS);//BSP_DELAY_UNITS_MILLISECONDS毫秒
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_12, BSP_IO_LEVEL_LOW);
                    //等待50us进行下一次脉冲
                    R_BSP_SoftwareDelay(50,BSP_DELAY_UNITS_MICROSECONDS);
               // }
                //else
                //{
                    //低电平有物体经过，电机停止转动。设置成使能高电平，高使能是停止
                //    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_05, BSP_IO_LEVEL_HIGH);
                //}
            }
            /*
             * 步进电机二
             * 步进方向--P400
             * 步进脉冲--P411
             * 步进使能--P410
             * 红外--P409
             */

            //接收语音助手的引脚电平信号
            R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_09, &yu_ying_2);
            //语音电平信号默认为低
            if(yu_ying_2)
            {
                //二号电机使能
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_10, BSP_IO_LEVEL_HIGH);
            }
            else
            {
                    //二号电机使能，低电平为启动，高电平为停止
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_10, BSP_IO_LEVEL_LOW);
                    //二号步进电机旋转方向
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_LOW);
                    //二号电机信号脉冲，高低电平来回切换，形成脉冲。
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_11, BSP_IO_LEVEL_HIGH);
                    //延时,50us一个脉冲
                    R_BSP_SoftwareDelay(50,BSP_DELAY_UNITS_MICROSECONDS);
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_11, BSP_IO_LEVEL_LOW);
                    //等待50us进行下一次脉冲
                    R_BSP_SoftwareDelay(50,BSP_DELAY_UNITS_MICROSECONDS);
            }
        }
        duo_ji_qu_dong();
    }

}
