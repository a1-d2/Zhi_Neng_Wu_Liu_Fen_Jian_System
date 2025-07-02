#include "bsp_debug_uart.h"
#include <stdio.h>

uint8_t fal_1 = '5';
uint8_t fal_2 = '5';
uint8_t fal_3 = '5';
uint8_t fal_4 = '5';

//串口调试初始化UART6
void Debug_UART6_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart6_ctrl, &g_uart6_cfg);
    assert(FSP_SUCCESS == err);
}

volatile bool uart_send_complete_flag =false;//发送串口之后的标记位

void debug_uart6_callback(uart_callback_args_t *p_args)
{
    switch(p_args -> event)//括号里面判断通信之后是什么事件，然后在进行以下对比选择
    {
        case UART_EVENT_RX_CHAR://串口接收到一个字符进入
        {
            switch(p_args -> data)//读取p_args变量里面的串口数据
            {
                case '1':{fal_1 = '1';}break;
                case '2':{fal_2 = '2';}break;
                case '3':{fal_3 = '3';}break;
                case '4':{fal_4 = '4';}break;
                default:
                {
                    fal_1 = '5';
                    fal_2 = '5';
                    fal_3 = '5';
                    fal_4 = '5';
                }break;
            }
            break;
        }
        default: break;
    }
}
