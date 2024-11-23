/*!
** Copyright 2019 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */

/* Including necessary configuration files. */
#include "Mcal.h"
#include "Clock_Ip.h"
#include "Lpspi_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "bsp_can.h"
#include "bsp_lin.h"
#include "bsp_spi.h"
#include "bsp_adc.h"
#include "bsp_pwm.h"
#include "bsp_pit.h"
#include "Pit_Ip.h"
#include "Dma_Ip.h"
#include "Cache_Ip.h"
#include "CDD_Rm.h"
#include "string.h"

#include "Lpuart_Lin_IP.h"
#include "Adc_Sar_Ip.h"

#include "SEGGER_RTT.h"
#include "rtt_log.h"

#define FXOSC_CLOCK_FREQ   16000000U

uint8 gpio_state;

int main(void)
{
	Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);  //初始化时钟配置

	/*Initial Pin */
	Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);  //初始化引脚配置

	/*Initial ISR*/
    IntCtrl_Ip_Init(&IntCtrlConfig_0);	//初始化中断向量表

	SEGGER_RTT_Init();
	LOG_INFO("Hello World from SEGGER RTT!\r\n");

	/* Initialize Dma */
//	Dma_Ip_Init(&Dma_Ip_xDmaInitPB);

	/* Initialize Rm driver for using DmaMux*/
//	Rm_Init(&Rm_Config);

	// Power Enable
	Siul2_Dio_Ip_WritePin(VBAT_12V_CTR_PORT, VBAT_12V_CTR_PIN, 1U);
	Siul2_Dio_Ip_WritePin(VCC_5V_CTR_PORT, VCC_5V_CTR_PIN, 1U);
	Siul2_Dio_Ip_WritePin(Sen_CTR_PORT, Sen_CTR_PIN, 1U);
	Siul2_Dio_Ip_WritePin(VOUT_EN_PORT, VOUT_EN_PIN, 1U);

	// LIN init
	main_lin_init();
	// CAN init
	main_can_init();
	// SPI init
	main_spi_init();
	// ADC init
	main_adc_init();
	// PWM init
	main_pwm_init();
	// PIT init
	main_pit_init();

    while( 1 ){

    }
}

/* END main */
/*!
** @}
*/
