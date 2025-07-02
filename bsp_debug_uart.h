#ifndef BSP_DEBUG_UART_H_
#define BSP_DEBUG_UART_H_
#include "hal_data.h"
#include "stdio.h"

void Debug_UART6_Init(void);
void Gpt_Pwm_Setduty_0(uint8_t duty_0);
void Gpt_Pwm_Setduty_1(uint8_t duty_1);
void Gpt_Pwm_Setduty_3(uint8_t duty_3);

#endif /* BSP_DEBUG_UART_H_ */
