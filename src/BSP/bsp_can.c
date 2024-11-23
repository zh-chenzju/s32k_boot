/*
 * BSP_CAN.c
 *
 *  Created on: 2023年8月23日
 *      Author: 姚山建
 */

#include "Mcal.h"
#include "Clock_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "bsp_adc.h"
#include "bsp_can.h"

//volatile int exit_code = 0;
/* User includes */
uint8 dummyData[8] = {1,2,3,4,5,6,7,8};
Flexcan_Ip_MsgBuffType rxData, rxFifoData;
Flexcan_Ip_DataInfoType rx_info = {
            .msg_id_type = FLEXCAN_MSG_ID_STD,
            .data_length = 8u,
            .is_polling = FALSE,
            .is_remote = FALSE
    };

Flexcan_Ip_DataInfoType tx_info = {
		.msg_id_type = FLEXCAN_MSG_ID_STD,
		.data_length = 8u,
		.is_polling = FALSE,
		.is_remote = FALSE
	};

uint8 byte_0 = 0;

//static Flexcan_Ip_StatusType status = FLEXCAN_STATUS_ERROR;
static Flexcan_Ip_StatusType Sendstatus1 = FLEXCAN_STATUS_ERROR;
//static Flexcan_Ip_StatusType Sendstatus2 = FLEXCAN_STATUS_ERROR;
//static Flexcan_Ip_StatusType Sendstatus3 = FLEXCAN_STATUS_ERROR;
//static Flexcan_Ip_StatusType Sendstatus4 = FLEXCAN_STATUS_ERROR;
//static Flexcan_Ip_StatusType Sendstatus5 = FLEXCAN_STATUS_ERROR;
//static Flexcan_Ip_StatusType Sendstatus6 = FLEXCAN_STATUS_ERROR;

extern float adc_voltage;

// DMA error call back
void flexcan0_Callback_dma_error(void)
{
	__asm volatile ("nop");
}

void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx,
		const Flexcan_Ip_StateType *flexcanState)
{
	(void)flexcanState;
	(void)instance;

	switch(eventType)
	{
	case FLEXCAN_EVENT_RX_COMPLETE:

		if(buffIdx==RX_MB_IDX) // MB10 received
		{
			FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
		}

//		if(buffIdx==RX_1_MB_IDX) // MB10 received
//		{
//			FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
//		}

		break;
	case FLEXCAN_EVENT_RXFIFO_COMPLETE:

		/* Start receiving data in RX_RXFIFO. */
		FlexCAN_Ip_RxFifo(INST_FLEXCAN_0,&rxFifoData);

		break;
	case FLEXCAN_EVENT_DMA_COMPLETE:

		 /* Start receiving data in RX_RXFIFO. */
		 FlexCAN_Ip_RxFifo(INST_FLEXCAN_0,&rxFifoData);

		  break;
	case FLEXCAN_EVENT_TX_COMPLETE:

		if(buffIdx==TX_MB_IDX) // MB12 transmitted
		{
			//dummyData[0]++;
		//	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, CAN1_ID, (uint8 *)&dummyData);
		}
		break;
	default:
		break;
	}
}

void main_can_init(void){

	Siul2_Dio_Ip_WritePin(CAN_STB_PORT, CAN_STB_PIN, 1U);

	IntCtrl_Ip_EnableIrq(FlexCAN0_0_IRQn);
	IntCtrl_Ip_InstallHandler(FlexCAN0_0_IRQn, CAN0_ORED_IRQHandler, NULL_PTR);

	IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
	IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);

	IntCtrl_Ip_EnableIrq(FlexCAN0_2_IRQn);
	IntCtrl_Ip_InstallHandler(FlexCAN0_2_IRQn, CAN0_ORED_32_63_MB_IRQHandler, NULL_PTR);

	//Flexcan_Ip_MsgBuffType rxData;
	setupCan();
}

//uint16_t id_counter;
//Flexcan_Ip_IdTableType CAN0_FIFO_IdFilterTable[16];

 void setupCan( void )
{
	/* can init */
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);

	/* enter the freeze mode */
	FlexCAN_Ip_EnterFreezeMode(INST_FLEXCAN_0);

	/**********************************************************/



	 // ====================================== FIFO ==================================
	 // Fill id filter table,

	 const Flexcan_Ip_IdTableType CAN0_FIFO_IdFilterTable[16] =	{
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,},
		  {.id = 0x55u,.isRemoteFrame = false,.isExtendedFrame = false,}
		};
//	 for(id_counter=0;id_counter<16;id_counter++)
//	 {
//		 CAN0_FIFO_IdFilterTable[id_counter].isRemoteFrame = false;
//		 CAN0_FIFO_IdFilterTable[id_counter].isExtendedFrame = false; //(id_counter % 2); //conflict
//		 CAN0_FIFO_IdFilterTable[id_counter].id = id_counter +1 ;
//	 }

	 /* Configure RX FIFO ID filter table elements based on filter table defined above*/
	 FlexCAN_Ip_ConfigRxFifo(INST_FLEXCAN_0, FLEXCAN_RX_FIFO_ID_FORMAT_A, CAN0_FIFO_IdFilterTable);
	 /* set individual masking type */
	 FlexCAN_Ip_SetRxMaskType(INST_FLEXCAN_0,FLEXCAN_RX_MASK_INDIVIDUAL);
	 FlexCAN_Ip_SetRxIndividualMask(INST_FLEXCAN_0,RX_MB_IDX,0x7FF<<18);  //---> only recv 0x40


	 FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, 0x40); // MB = 0 : ID = 0x60 : STANDARD ID
//	 FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_1_MB_IDX, &rx_info, 0x61); // MB = 0 : ID = 0x61 : STANDARD ID

	 /* first 10 filter items are masked with RXIMR0-RXIMR9 */
	 for(uint8_t id_counter=0;id_counter<10;id_counter++){
		 FlexCAN_Ip_SetRxIndividualMask(INST_FLEXCAN_0,id_counter, 0x7FF<<18);
	  }
//	 FlexCAN_Ip_SetRxFifoGlobalMask(INST_FLEXCAN_0, 0x1FFFFFFF);

	 /* Exit the freeze mode */
	 FlexCAN_Ip_ExitFreezeMode(INST_FLEXCAN_0);

	 /* Start receiving data in RX_RXFIFO. */
	 FlexCAN_Ip_RxFifo(INST_FLEXCAN_0,&rxFifoData);
	 FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, false);
//	 FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_1_MB_IDX, &rxData, false);
	 /***********************************************************/

	 FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}
void can_senddata(void)
{
	uint8 ADC_data1 = ((int)(adc_voltage * 100) & 0xFF00) >> 8;
	uint8 ADC_data0 = ((int)(adc_voltage * 100) & 0x00FF);
	dummyData[1] = ADC_data1;
	dummyData[0] = ADC_data0;
	Sendstatus1 = FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, CAN1_ID, (uint8 *)&dummyData);
}

void can_set_mode(void)
{

	FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
	FlexCAN_Ip_Deinit(INST_FLEXCAN_0);
}
