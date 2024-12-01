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

#include "pFlsCtrl.h"

#define NEED_JUMP_APP (1U)
#define NOTNEED_JUMP_APP (0U)

#define APP_START_ADDRESS (0x00500800)

#define	STDBYRAM_START		0x20400000
#define	STDBYRAM_END		0x20407FFF
#define STDBYRAM_SIZE		(STDBYRAM_END - STDBYRAM_START)

void init_ram(void)
{
	uint32_t	cnt;
	uint64_t	*pDest;

    cnt = (( uint32_t)(STDBYRAM_SIZE)) / 8U;
    pDest = (uint64_t *)(STDBYRAM_START);
    while (cnt--)
    {
		*pDest = (uint64_t)0x00;
		pDest++;
    }
}

void jump_to_application(unsigned int appEntry, unsigned int appStack)
{
    static void (*jump_to_application)(void);
    static uint32_t stack_pointer;
    /*把应用程序入口地址赋值给函数指针*/
    jump_to_application = (void (*)(void))appEntry;
    stack_pointer = appStack;
    /* 重新定向中断向量表 */
    S32_SCB->VTOR = (uint32_t)APP_START_ADDRESS;
    /* 设置栈指针  */
    __asm volatile ("MSR msp, %0\n" : : "r" (stack_pointer) : "sp");
    __asm volatile ("MSR psp, %0\n" : : "r" (stack_pointer) : "sp");
    /*跳转*/
    jump_to_application();
}

typedef void (*AppAddr)(void);
void Boot_JumpToApp(void)
{
	AppAddr resetHandle = (AppAddr)(*(uint32*)(0x00500800 + 4));

	(resetHandle)();
}

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
//	// CAN init
	main_can_init();
//	// SPI init
	main_spi_init();
//	// ADC init
	main_adc_init();
//	// PWM init
	main_pwm_init();
//	// PIT init
	main_pit_init();

	unsigned char Need2App = NEED_JUMP_APP;

	 if (PFLASH_SUCCESS == PflsIint()) {
	 	LOG_DEBUG("[%d] FLS Init Success!\r\n", Get_SysTicks());

	 	if (PFLASH_SUCCESS != clearLock()) {
	 		LOG_ERROR("[%d] FLS Clear Lock Failed!\r\n", Get_SysTicks());
	 	}
	 	LOG_DEBUG("[%d] FLS Clear Lock Success!\r\n", Get_SysTicks());

	 	UPDATE_STATE CurrState = checkUpdateFlag();
	 	LOG_DEBUG("[%d] Update CurrState = %d\r\n", Get_SysTicks(), CurrState);

	 	if (UPDATE_SUCESS_JUST_A == CurrState) {
	 		Need2App = NEED_JUMP_APP;
	 		LOG_DEBUG("[%d] Need Jump APP!\r\n", Get_SysTicks());
	 	}
     }

	uint32_t appEntry, appStack;

    if (NEED_JUMP_APP == Need2App) {
		/* 清空ECC */
		init_ram();

		/* 执行跳转 */
//		SuspendAllInterrupts();
		Pit_Ip_DisableChannelInterrupt(0, 0);
        appStack = *(uint32_t*)(APP_START_ADDRESS);
        appEntry = *(uint32_t*)(APP_START_ADDRESS + 4);
        jump_to_application(appEntry, appStack);
    }

	while( 1 ){

    }
}

/* END main */
/*!
** @}
*/
