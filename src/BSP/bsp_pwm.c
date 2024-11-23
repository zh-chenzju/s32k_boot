/*
 * bsp_pwm.c
 *
 *  Created on: 2024Äê9ÔÂ1ÈÕ
 *      Author: Mr. Chen
 */

#include "Mcal.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Emios_Pwm_Ip.h"
#include "Emios_Mcl_Ip.h"
#include "bsp_pwm.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define NUM_BLINK_LED     (uint32)10U
#define DELAY_TIMER       (uint32)5000000U
#define INSTANCE_1        (uint8)1U
#define CHANNEL_8         (uint8)8U
#define CHANNEL_9         (uint8)9U

void TestDelay(uint32 delay)
{
    static volatile uint32 DelayTimer = 0;
    while(DelayTimer<delay)
    {
        DelayTimer++;
    }
    DelayTimer=0;
}

void main_pwm_init(void){

	/*PWM*/
	/* Initialize Emios_Mcl driver */
	Emios_Mcl_Ip_Init(INSTANCE_1, &Emios_Mcl_Ip_1_Config_BOARD_INITPERIPHERALS);

	/* Initialize Emios_Pwm_Ip driver */
	Emios_Pwm_Ip_InitChannel(EMIOS_PWM_IP_I1_CH9_CFG, &Emios_Pwm_Ip_I1_Ch9);

	/* Set new period for the channels that used external counter bus */
	Emios_Mcl_Ip_SetCounterBusPeriod(INSTANCE_1, CHANNEL_8, 20480);

	/* Setup new duty cycle to the pin*/
	Emios_Pwm_Ip_SetDutyCycle(INSTANCE_1, CHANNEL_9, 8192);

	/* Using duty 0% and 100% to blink led */
//	while(num_blink < NUM_BLINK_LED)
//	{
//		/* Led on when duty cycle is 100% */
//		Emios_Pwm_Ip_SetDutyCycle(INSTANCE_0, CHANNEL_7, 0x5000);
//		TestDelay(DELAY_TIMER);
//
//		/* Led off when duty cycle is 0% */
//		Emios_Pwm_Ip_SetDutyCycle(INSTANCE_0, CHANNEL_7, 0U);
//		TestDelay(DELAY_TIMER);
//		num_blink++;
//	}
}
