/*
 * bsp_spi.c
 *
 *  Created on: 2024Äê8ÔÂ18ÈÕ
 *      Author: Mr. Chen
 */

#include "Mcal.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "Pit_Ip.h"
#include "bsp_spi.h"
#include "Lpspi_Ip.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Time to transfer all frame data */
#define TIMEOUT             ((uint32)1000000UL)
#define NUMBER_OF_BYTES     (1)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define MASTER_EXTERNAL_DEVICE           (Lpspi_Ip_DeviceAttributes_SpiExternalDevice_0_Instance_0)
#define SLAVE_EXTERNAL_DEVICE          	 (Lpspi_Ip_DeviceAttributes_SpiExternalDevice_1_Instance_5)

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Spi_MemMap.h"
static uint8 TxMasterBuffer[NUMBER_OF_BYTES] = {0x00};
static uint8 RxMasterBuffer[NUMBER_OF_BYTES];
//static uint8 TxSlaveBuffer[NUMBER_OF_BYTES] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
//static uint8 RxSlaveBuffer[NUMBER_OF_BYTES];
#define SPI_STOP_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Spi_MemMap.h"

void main_spi_init(void){

	Siul2_Dio_Ip_WritePin(SPI_nRES_PORT, SPI_nRES_PIN, 1U);
	//	Siul2_Dio_Ip_WritePin(SPI_NCS1_PORT, SPI_NCS1_PIN, 0U);
	//	Siul2_Dio_Ip_WritePin(SPI_NCS2_PORT, SPI_NCS2_PIN, 1U);

	/*SPI*/
//	uint8 Index;
//	uint32 Counter = 0xFFFFFF;
//	Lpspi_Ip_HwStatusType Status;
//	boolean Passed = TRUE;

	/* Initalized spi*/
	Lpspi_Ip_Init(&Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_0_Instance_0);
//	Lpspi_Ip_Init(&Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_1_Instance_5);

	/*Master Config*/
	/* Update Transfer Mode */
	Lpspi_Ip_UpdateTransferMode(MASTER_EXTERNAL_DEVICE.Instance, LPSPI_IP_INTERRUPT);
	/* Master transmits data in half-duplex mode by sync method */
//	Lpspi_Ip_SyncTransmitHalfDuplex(&MASTER_EXTERNAL_DEVICE, TxMasterBuffer, NUMBER_OF_BYTES, LPSPI_IP_HALF_DUPLEX_MODE_SUPPORT, TIMEOUT);
	Lpspi_Ip_SyncTransmit(&MASTER_EXTERNAL_DEVICE, TxMasterBuffer, RxMasterBuffer, NUMBER_OF_BYTES, TIMEOUT);

	/*Slave Config*/
	/* Update Transfer Mode */
//	Lpspi_Ip_UpdateTransferMode(SLAVE_EXTERNAL_DEVICE.Instance, LPSPI_IP_INTERRUPT);
//	/* Slave set up and waiting active signal of Cs from master to process data reception */
////	Lpspi_Ip_AsyncTransmitHalfDuplex(&SLAVE_EXTERNAL_DEVICE, RxSlaveBuffer, NUMBER_OF_BYTES, LPSPI_IP_HALF_DUPLEX_RECEIVE, NULL_PTR);
//	Lpspi_Ip_SyncTransmit(&SLAVE_EXTERNAL_DEVICE, TxSlaveBuffer, RxSlaveBuffer, NUMBER_OF_BYTES, TIMEOUT);
//
//	do
//	{
//		Counter --;
//		Status = Lpspi_Ip_GetStatus(SLAVE_EXTERNAL_DEVICE.Instance);
//	}
//	while ( (Counter > 0UL) && (Status != LPSPI_IP_IDLE) );
//
//	if (0UL != Counter)
//	{
//		/* Checking data */
//		for (Index = 0; Index < NUMBER_OF_BYTES; Index++)
//		{
//			if (TxMasterBuffer[Index] != RxSlaveBuffer[Index])
//			{
//				Passed = FALSE;
//				break;
//			}
//		}
//	}
//	else
//	{
//		Passed = FALSE;
//	}
}
