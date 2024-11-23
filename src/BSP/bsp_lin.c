/*
 * bsp_lin.c
 *
 *  Created on: 2024Äê7ÔÂ28ÈÕ
 *      Author: Mr. Chen
 */

#include "Mcal.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "Pit_Ip.h"
#include "bsp_lin.h"
#include "Lpuart_Lin_IP.h"


/* LIN */
/* Global Macros */
#define BUFFER_SIZE             (3U)
#define T_LIN_TIME_OUT          (400000U)
#define LPUART_PID              (0x1A)
#define MASTER_ROLE             (0U)
#define SLAVE_ROLE              (1U)

/* PIT instance used - 0 */
#define PIT_INST_0              0U
/* PIT channel used - 0 */
#define PIT_CH_0                0U

#define PIT_PERIOD              0xFFFFFFFFU

/* PIT clock in MHz */
#define PIT_CLK                 40U

/* Siul2 Icu instance used - 0 */
#define SIUL2_ICU_INST_0        0U
/* Siul2 Icu channel used - 15 */
#define SIUL2_ICU_CHN_15        15U

volatile uint64 TmpCountValue = 0;
volatile uint64 CountValue = 0;
volatile uint32 BitTimeNs = 0;
volatile uint8 Count = 0;

uint8 LpuartTxBuff[BUFFER_SIZE] = {0x04, 0x05, 0x06};
//uint8 SduBuf[3U];

//Lpuart_Lin_Ip_UserConfigType Lpuart_Lin_Ip_Sa_pHwConfigPB_0_VS_0;
//Lpuart_Lin_Ip_UserConfigType Lpuart_Lin_Ip_Sa_pHwConfigPB_1_VS_0;

Lpuart_Lin_Ip_PduType LinLpuartPdu[] =
{
    {
                .Pid = (uint8)LPUART_PID,
                .Cs = LPUART_LIN_IP_CLASSIC_CS,
                .SduPtr = LpuartTxBuff,
                .Drc = LPUART_LIN_IP_FRAMERESPONSE_TX,
                .Dl = (uint8)BUFFER_SIZE
    },
    {
                .Pid = (uint8)LPUART_PID,
                .Cs = LPUART_LIN_IP_CLASSIC_CS,
                .SduPtr = NULL_PTR,
                .Drc = LPUART_LIN_IP_FRAMERESPONSE_RX,
                .Dl = (uint8)BUFFER_SIZE
    }
};

boolean CheckReceiveBuffer(uint8 *OriginalBuffer, uint8 * ReceiveBuffer)
{
    uint8 Index;
    volatile boolean RetVal = TRUE;
    for (Index = 0; Index < BUFFER_SIZE; Index++)
    {
        if (OriginalBuffer[Index] != *(ReceiveBuffer + Index))
        {
            RetVal = FALSE;
        }
    }
    return RetVal;
}

void AutobaudCallback(const uint8 Instance, uint32 *NanoSeconds)
{
    (void)Instance;
    *NanoSeconds = BitTimeNs;
}

void LpuartSlaveCallback (uint8 Instance, const  Lpuart_Lin_Ip_StateStructType *LpuartStateStruct)
{
    switch (LpuartStateStruct->CurrentEventId)
    {
        /* Baudrate adjusted */
        case LPUART_LIN_IP_BAUDRATE_ADJUSTED:

//            (void)Siul2_Icu_Ip_DeInit(SIUL2_ICU_INST_0);
            /* Re-configure PTB9 as LPUART_RX */
            Siul2_Port_Ip_SetInputBuffer(PORTB_L_HALF, 9, FALSE, 31, PORT_INPUT_MUX_ALT0);
            Siul2_Port_Ip_SetInputBuffer(PORTB_L_HALF, 9, TRUE, 196, PORT_INPUT_MUX_ALT1);
            Pit_Ip_StopChannel(PIT_INST_0, PIT_CH_0);
            Count = 0;
            break;

        /* Header transmission ok */
        case LPUART_LIN_IP_RECV_HEADER_OK:
            if (LpuartStateStruct->CurrentPid == LinLpuartPdu[SLAVE_ROLE].Pid)
            {
                /* Master start send header */
                (void)Lpuart_Lin_Ip_SendFrame(Instance, (const Lpuart_Lin_Ip_PduType *)&LinLpuartPdu[SLAVE_ROLE]);
            }
            break;
        default:
            /* do nothing */
            break;
    }
}

void main_lin_init(void){

	//LIN SLP Enable
	Siul2_Dio_Ip_WritePin(LIN_SLP_PORT, LIN_SLP_PIN, 1U);

	/*LIN */
	uint8 *RecvBuffer[2];
	uint8 *DummyBuffer;
	uint32 TimeoutValue = 0u;
	volatile boolean LpuartCheckData;
	volatile Lpuart_Lin_Ip_TransferStatusType LpuartSlaveStatus = LPUART_LIN_IP_STATUS_OPERATIONAL;
	volatile Lpuart_Lin_Ip_TransferStatusType LpuartMasterStatus = LPUART_LIN_IP_STATUS_OPERATIONAL;

	/* Wait for the transmission done */
	TimeoutValue = 4*T_LIN_TIME_OUT;

	/*Intialize Lin */
	Lpuart_Lin_Ip_Init(Lpuart_Lin_Ip_Sa_pHwConfigPB_0.Instance, &Lpuart_Lin_Ip_Sa_pHwConfigPB_0);
	Lpuart_Lin_Ip_Init(Lpuart_Lin_Ip_Sa_pHwConfigPB_1.Instance, &Lpuart_Lin_Ip_Sa_pHwConfigPB_1);
	/* Start of the sending frame from Lpuart Master*/
	(void)Lpuart_Lin_Ip_SendFrame(Lpuart_Lin_Ip_Sa_pHwConfigPB_0.Instance, &LinLpuartPdu[MASTER_ROLE]);

	/*Wait for the transmission done */
	do
	{
		LpuartMasterStatus = Lpuart_Lin_Ip_GetStatus(Lpuart_Lin_Ip_Sa_pHwConfigPB_0.Instance, (const uint8 **)&DummyBuffer);
	}
	while ((LPUART_LIN_IP_STATUS_TX_OK != LpuartMasterStatus) && (TimeoutValue-- > 1));

	/*Wait for the transmission done */
	do
	{
		LpuartSlaveStatus = Lpuart_Lin_Ip_GetStatus(Lpuart_Lin_Ip_Sa_pHwConfigPB_1.Instance, (const uint8 **)&RecvBuffer[1]);
	}
	while ((LPUART_LIN_IP_STATUS_RX_OK != LpuartSlaveStatus) && (TimeoutValue-- > 1));

	LpuartCheckData = CheckReceiveBuffer(LinLpuartPdu[MASTER_ROLE].SduPtr, RecvBuffer[1]);

	/* Lpuart over Lin driver de-initialization*/
	Lpuart_Lin_Ip_Deinit(Lpuart_Lin_Ip_Sa_pHwConfigPB_0.Instance);
	Lpuart_Lin_Ip_Deinit(Lpuart_Lin_Ip_Sa_pHwConfigPB_1.Instance);
}
