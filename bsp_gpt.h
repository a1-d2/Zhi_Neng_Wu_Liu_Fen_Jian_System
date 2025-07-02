#ifndef __BSP_GPT_H
#define __BSP_GPT_H

#include "hal_data.h"

/*初始化GPT函数*/
void Gpt_Init(void);
void Gpt_Pwm_Setduty_0(uint8_t duty_0);
void Gpt_Pwm_Setduty_1(uint8_t duty_1);
void Gpt_Pwm_Setduty_3(uint8_t duty_3);
void Gpt_Pwm_Setduty_2(uint8_t duty_2);//机械臂一号舵机
void Gpt_Pwm_Setduty_4(uint8_t duty_4);//机械臂二号舵机
void Gpt_Pwm_Setduty_7(uint8_t duty_7);//机械臂三号舵机
void Gpt_Pwm_Setduty_8(uint8_t duty_8);//机械臂四号舵机

#endif

