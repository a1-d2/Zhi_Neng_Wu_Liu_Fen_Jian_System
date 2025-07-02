#include "hal_data.h"
#include "bu_jin_qu_dong.h"
#include "duo_ji_qu_dong.h"
#include "bsp_debug_uart.h"
#include "stdio.h"
#include "bsp_gpt.h"
#include "IIC_Init.h"
#include "OLED_xian_shi.h"
#include "ji_xie_bi.h"

/***************************系统函数部分*******************************************************************/

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/******************************IIC回调函数部分********************************************************************/

extern fsp_err_t err;
extern int  timeout_ms;
extern  i2c_master_event_t i2c_event ;
fsp_err_t err = FSP_SUCCESS;
int timeout_ms = 100;
i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

void IIC_master_callback(i2c_master_callback_args_t *p_args)
{
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    if(NULL != p_args)
    {

        i2c_event = p_args->event;
    }
}

/*******************************************************************************************************************//**
 * “main()”函数是由 RA 配置编辑器生成的，当使用实时操作系统（RTOS）时，该函数用于创建线程。
 * 若未使用 RTOS，则由“main()”函数调用此函数。
 ***********************************************************************************************************************/
void hal_entry(void)
{
      IIC_Init();//初始化IIC模块
      Debug_UART6_Init();//初始化串口6
      Gpt_Init();//初始化定时器
      OLED_xian_shi();

      Gpt_Pwm_Setduty_0(3);//舵机归位
      R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);//一毫秒
      Gpt_Pwm_Setduty_1(3);
      R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);
      Gpt_Pwm_Setduty_3(3);
      ji_xie_bi_Init();
      bu_jin_qu_dong();//步进电机驱动和红外检测

      //char ok[1] = {'A'};//存储需要发送的数据
      //R_SCI_UART_Write(&g_uart6_ctrl, (uint8_t *)&(ok[0]), 1);//串口数据发送函数
      //R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_09, BSP_IO_LEVEL_HIGH);//引脚高低电平函数

/******************************************************************************************/

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);

#if BSP_CFG_SDRAM_ENABLED

        /* Setup SDRAM and initialize it. Must configure pins first. */
        R_BSP_SdramInit(true);
#endif
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
