#include "bsp_gpt.h"

void Gpt_Init(void)
{
   R_GPT_Open(&g_timer0_ctrl,&g_timer0_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer1_ctrl,&g_timer1_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer3_ctrl,&g_timer3_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer2_ctrl,&g_timer2_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer4_ctrl,&g_timer4_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer7_ctrl,&g_timer7_cfg);//初始化定时器模块，并应用相关配置
   R_GPT_Open(&g_timer8_ctrl,&g_timer8_cfg);//初始化定时器模块，并应用相关配置

   R_GPT_Start(&g_timer0_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer1_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer3_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer2_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer4_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer7_ctrl);//定时器开始工作
   R_GPT_Start(&g_timer8_ctrl);//定时器开始工作
}

void Gpt_Pwm_Setduty_0(uint8_t duty_0)//调节占空比
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_0 > 100)
        duty_0 = 100;
    R_GPT_InfoGet(&g_timer0_ctrl,&info);

    duty_count = (info.period_counts * duty_0) / 100;

    R_GPT_DutyCycleSet(&g_timer0_ctrl,duty_count,GPT_IO_PIN_GTIOCB);
}

void Gpt_Pwm_Setduty_1(uint8_t duty_1)//调节占空比
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_1 > 100)
        duty_1 = 100;
    R_GPT_InfoGet(&g_timer1_ctrl,&info);

    duty_count = (info.period_counts * duty_1) / 100;

    R_GPT_DutyCycleSet(&g_timer1_ctrl,duty_count,GPT_IO_PIN_GTIOCB);
}

void Gpt_Pwm_Setduty_3(uint8_t duty_3)//调节占空比
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_3 > 100)
        duty_3 = 100;
    R_GPT_InfoGet(&g_timer3_ctrl,&info);

    duty_count = (info.period_counts * duty_3) / 100;

    R_GPT_DutyCycleSet(&g_timer3_ctrl,duty_count,GPT_IO_PIN_GTIOCB);
}

//机械臂一号舵机：3-8.二号舵机：，三号舵机：没有限制。四号舵机：8-5（8完全开，6夹住，5完整闭合）。
void Gpt_Pwm_Setduty_2(uint8_t duty_2)//一号机械臂舵机连接至P103，已连接
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_2 > 100)
        duty_2 = 100;
    R_GPT_InfoGet(&g_timer2_ctrl,&info);

    duty_count = (info.period_counts * duty_2) / 100;

    R_GPT_DutyCycleSet(&g_timer2_ctrl,duty_count,GPT_IO_PIN_GTIOCA);
}

void Gpt_Pwm_Setduty_4(uint8_t duty_4)//二号机械臂舵机连接至P115，已连接
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_4 > 100)
        duty_4 = 100;
    R_GPT_InfoGet(&g_timer4_ctrl,&info);

    duty_count = (info.period_counts * duty_4) / 100;

    R_GPT_DutyCycleSet(&g_timer4_ctrl,duty_count,GPT_IO_PIN_GTIOCA);
}

void Gpt_Pwm_Setduty_7(uint8_t duty_7)//三号机械臂舵机连接至P303，未连接
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_7 > 100)
        duty_7 = 100;
    R_GPT_InfoGet(&g_timer7_ctrl,&info);

    duty_count = (info.period_counts * duty_7) / 100;

    R_GPT_DutyCycleSet(&g_timer7_ctrl,duty_count,GPT_IO_PIN_GTIOCB);
}


void Gpt_Pwm_Setduty_8(uint8_t duty_8)//四号机械臂舵机连接至P106，未连接
{
    timer_info_t info;
    uint32_t duty_count;
    if(duty_8 > 100)
        duty_8 = 100;
    R_GPT_InfoGet(&g_timer8_ctrl,&info);

    duty_count = (info.period_counts * duty_8) / 100;

    R_GPT_DutyCycleSet(&g_timer8_ctrl,duty_count,GPT_IO_PIN_GTIOCB);
}
