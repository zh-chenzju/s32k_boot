/*
 * app_task.c
 *
 *  Created on: 2024年11月3日
 *      Author: Mr. Chen
 */

#include "Lpspi_Ip.h"
#include "bsp_can.h"
#include "bsp_adc.h"
#include "Adc_Sar_Ip.h"
#include "app_task.h"
#include "bsp_pit.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "rtt_log.h"

#define MASTER_EXTERNAL_DEVICE           (Lpspi_Ip_DeviceAttributes_SpiExternalDevice_0_Instance_0)
#define TIMEOUT             ((uint32)1000000UL)
#define NUMBER_OF_BYTES     (1)

uint8 spi_counter = 0;
static uint8 TxMasterBuffer[NUMBER_OF_BYTES] = {0x28};
static uint8 RxMasterBuffer[NUMBER_OF_BYTES];

void pit_5_ms_task(void){

	switch(spi_counter){
		case 0:
			TxMasterBuffer[0] = 0x30;
			break;
		case 1:
			TxMasterBuffer[0] = 0x18; //0x24 (POS)
			break;
		case 2:
			TxMasterBuffer[0] = 0x0C;
			break;
		case 3:
			TxMasterBuffer[0] = 0x24; //0x18 (POS)
			break;
		default:
			break;
	}

	spi_counter = (spi_counter < 3) ? (spi_counter + 1) : (0);
	Lpspi_Ip_SyncTransmit(&MASTER_EXTERNAL_DEVICE, TxMasterBuffer, RxMasterBuffer, NUMBER_OF_BYTES, TIMEOUT);
}


void pit_500_ms_task(void){
	// 更新AD采样值
	Adc_Sar_Ip_StartConversion(ADCHWUNIT_0_INSTANCE, ADC_SAR_IP_CONV_CHAIN_NORMAL);

	// can报文周期发送
	can_senddata();

	LOG_INFO("[%d] APP task is running!\r\n", Get_SysTicks());
}
