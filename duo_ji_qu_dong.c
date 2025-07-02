#include "hal_data.h"
#include "bsp_gpt.h"
#include "duo_ji_qu_dong.h"
#include "OLED_xian_shi.h"
#include "ji_xie_bi.h"
#include "oled.h"


extern uint8_t fal_1;//串口数据接收变量
extern uint8_t fal_2;//串口数据接收变量
extern uint8_t fal_3;//串口数据接收变量
extern uint8_t fal_4;//串口数据接收变量

extern uint8_t fen;//OLED显示变量
extern uint8_t cheng;//OLED显示变量
extern uint8_t lan;//OLED显示变量
extern uint8_t hong;

void duo_ji_qu_dong(void)
{
    //机械臂一号舵机：3-8(3是最上面，8是最下面).二号舵机：4-8(4是最下面，8是最上面)，
    //三号舵机：8->12向左.四号舵机：8-5（8完全开，6夹住，5完整闭合）。
    //ji_xie_bi_cao_zhuo(4,4,5,6);
    //根据串口接收到的编号，控制3个舵机
    if(fal_1 == '1')//一号舵机
    {
        bsp_io_level_t hong_wai1;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_09, &hong_wai1);
         if(hong_wai1)//红外检测：有物体经过是高电平
         {
             Gpt_Pwm_Setduty_0(12);//3是收回，12是推动
             fal_1 = '5';
             cheng++;
             OLED_ShowNum(48,3,cheng,2,16);//橙色的个数
             R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);
             Gpt_Pwm_Setduty_0(3);
         }
         else
         {
             Gpt_Pwm_Setduty_0(3);//更改占空比：3/90度，5/45度，8/0度，10/-45度，12/-90度

         }
    }
    if(fal_2 == '2')//二号舵机
    {
        bsp_io_level_t hong_wai1;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_13, &hong_wai1);
         if(hong_wai1)//有物体经过是高电平
         {
             Gpt_Pwm_Setduty_1(12);//3是收回，12是推动
             fal_2 = '5';
             lan++;
             OLED_ShowNum(48,6,lan,2,16);//蓝色的个数
             R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
             Gpt_Pwm_Setduty_1(3);
         }
         else
         {
             Gpt_Pwm_Setduty_1(3);//更改占空比：3/90度，5/45度，8/0度，10/-45度，12/-90度

         }
    }
    if(fal_3 == '3')//三号舵机
    {
        bsp_io_level_t hong_wai1;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, &hong_wai1);
         if(hong_wai1)//有物体经过是高电平
         {
             Gpt_Pwm_Setduty_3(12);//3是收回，12是推动
             fal_3 = '5';
             fen++;
             OLED_ShowNum(48,0,fen,2,16);//粉色的个数
             R_BSP_SoftwareDelay(500,BSP_DELAY_UNITS_MILLISECONDS);//毫秒
             Gpt_Pwm_Setduty_3(3);
         }
         else
         {
             Gpt_Pwm_Setduty_3(2);//更改占空比：3/90度，5/45度，8/0度，10/-45度，12/-90度

         }
    }
    if(fal_4 == '4')//机械臂控制
    {
        bsp_io_level_t hong_wai1;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, &hong_wai1);//415这个红外是有物体经过是低电平
         if(hong_wai1)
         {
             //低电平启动
             R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_05, BSP_IO_LEVEL_LOW);
         }
         else
         {
             //高电平停止
             R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_05, BSP_IO_LEVEL_HIGH);
             fal_4 = '5';
             hong++;
             OLED_ShowNum(96,6,hong,2,16);//红色的个数
             jia_qu();//机械臂夹取函数
         }
    }
}
