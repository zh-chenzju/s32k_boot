/*
 * bsp_pit.c
 *
 *  Created on: 2024Äê11ÔÂ3ÈÕ
 *      Author: Mr. Chen
 */

#include "Pit_Ip.h"
#include "IntCtrl_Ip.h"
#include "app_task.h"
#include "bsp_pit.h"

/* PIT instance used - 0 */
#define PIT_INST 0U
/* PIT Channel used - 0 */
#define CH_0 0U

uint64 pit_1_ms_counter = 0;
uint32 pit_5_ms_counter = 0;
uint32 pit_10_ms_counter = 0;
uint32 pit_100_ms_counter = 0;
uint32 pit_500_ms_counter = 0;

void PIT0_IRQHandler(void){
	pit_1_ms_counter++;

	pit_5_ms_counter++;
	if (pit_5_ms_counter == 5){
		pit_5_ms_task();
		pit_5_ms_counter = 0;
	}

	pit_500_ms_counter++;
		if (pit_500_ms_counter == 500){
			pit_500_ms_task();
			pit_500_ms_counter = 0;
		}

}

uint64 Get_SysTicks(void){
	return pit_1_ms_counter;
}

void main_pit_init(void){

	/*PIT*/
	Pit_Ip_Init(PIT_INST, &PIT_0_InitConfig_PB);
	Pit_Ip_InitChannel(PIT_INST, PIT_0_CH_0);
	Pit_Ip_EnableChannelInterrupt(PIT_INST, CH_0);
	Pit_Ip_StartChannel(PIT_INST, CH_0, 40000);//40MHz->1KHz IRQ
}
