#include "pFlsCtrl.h"
#include "C40_Ip.h"
#include <string.h>
uint8 CtrlFlag[FLAG_STATE_NUM] = { FLAG_NEED_CTRL_INIT };
uint8 CtrlState[FLAG_STATE_NUM] = { FLAG_NOT_CTRL };
volatile unsigned int EraseNum = C40_CODE_ARRAY_0_BLOCK_2_S256;
volatile unsigned int UpdateBaseAddr = MCU_APP_B_ADDR + PFLASH_DATA_LEN;
PFLASH_STATE PflashEraseState = PFLASH_MAX;
PFLASH_STATE PflashWriteState = PFLASH_MAX;
volatile uint8 CurrUpdateNum = 0;
volatile unsigned int CurrAddr = MCU_APP_B_ADDR + PFLASH_DATA_LEN;
uint8 NeedUpdateMax = MCU_UPDATE_NUM_MAX;
volatile unsigned int CurrEraseNum = C40_CODE_ARRAY_0_BLOCK_2_S257;
uint8 EraseFlag = 0;

static uint8 clearFlashLock(unsigned int SectorNum)
{
    uint8 Ret = PFLASH_FAIL; //error
    C40_Ip_StatusType C40Status = STATUS_C40_IP_ERROR;

    C40Status = C40_Ip_GetLock(SectorNum);
    if (STATUS_C40_IP_SECTOR_PROTECTED == C40Status) {
        if (STATUS_C40_IP_SUCCESS == C40_Ip_ClearLock(SectorNum, FLS_MASTER_ID)) {
            Ret = PFLASH_SUCCESS;
        }
    } else if (STATUS_C40_IP_SECTOR_UNPROTECTED == C40Status) {
        Ret = PFLASH_SUCCESS;
    } else {
        //empty
    }

    return Ret;
}

static inline uint8 setFlashLock(unsigned int SectorNum)
{
    uint8 Ret = PFLASH_FAIL; //error

    C40_Ip_StatusType C40Status = STATUS_C40_IP_ERROR;

    C40Status = C40_Ip_GetLock(SectorNum);
    if (STATUS_C40_IP_SECTOR_UNPROTECTED == C40Status) {
        if (STATUS_C40_IP_SUCCESS == C40_Ip_SetLock(SectorNum, FLS_MASTER_ID)) {
            Ret = PFLASH_SUCCESS;
        }
    } else if (STATUS_C40_IP_SECTOR_PROTECTED == C40Status) {
        Ret = PFLASH_SUCCESS;
    } else {
        //empty
    }

    return Ret;
}

PFLASH_STATE checkPflashEraseState(void)
{
    C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceSectorEraseStatus();

    if (STATUS_C40_IP_BUSY == InitStatus) {
        PflashEraseState = PFLASH_BUSY;
    } else if (STATUS_C40_IP_SUCCESS == InitStatus) {
        PflashEraseState = PFLASH_IDLE;
    } else {
        PflashEraseState = PFLASH_ERROR;
    }

    return PflashEraseState;
}

PFLASH_STATE checkPflashWriteState(void)
{
    C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceWriteStatus();

    if (STATUS_C40_IP_BUSY == InitStatus) {
        PflashWriteState = PFLASH_BUSY;
    } else if (STATUS_C40_IP_SUCCESS == InitStatus) {
        PflashWriteState = PFLASH_IDLE;
    } else {
        PflashWriteState = PFLASH_ERROR;
    }

    return PflashWriteState;
}



__attribute__((always_inline)) static inline void Os_Hal_WriteBasepri(uint32 NewBasepri)
{
  __asm volatile ("MSR basepri, %0" : : "r" (NewBasepri) );                                                            /* COMP_WARN_OS_HAL_UNINITIALIZED_VAR */
}

__attribute__((always_inline)) static inline uint32 Os_Hal_ReadBasepri(void)
{
  uint32 result;

  __asm volatile ("MRS %0, basepri_max" : "=r" (result) );
  return(result);
}

void lsSuspendAllInterrupts(void)
{
	Os_Hal_WriteBasepri(16); //关中断
}

void lsResumeAllInterrupts(void)
{
	Os_Hal_WriteBasepri(0); //开中断
}

void Suspend_Interrupts(void)
{
    ASM_KEYWORD("push {r0}");
    ASM_KEYWORD("mov   r0, #0x10");
    ASM_KEYWORD("msr BASEPRI, r0");
    ASM_KEYWORD("pop {r0}");
}

void Resume_Interrupts(void)
{
    ASM_KEYWORD("push {r0}");
    ASM_KEYWORD("mov   r0, #0x0");
    ASM_KEYWORD("msr BASEPRI, r0");
    ASM_KEYWORD("pop {r0}");
}

C40_ConfigType FlsConfigSet_InitCfg2={NULL,NULL};
uint8 PflsIint(void)
{
    uint8 Ret = PFLASH_FAIL;

    if (STATUS_C40_IP_SUCCESS == C40_Ip_Init(&FlsConfigSet_InitCfg2)) {
        Ret = PFLASH_SUCCESS;
    }

    return Ret;
}

uint8 PflsErase(unsigned int SectorNum)
{
    uint8 Ret = PFLASH_SUCCESS;
    PFLASH_STATE CtrlState = PFLASH_MAX;
    // uint8 WaitNum = 5;
    Suspend_Interrupts();
    C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceSectorErase(SectorNum, FLS_MASTER_ID);

    if (STATUS_C40_IP_SUCCESS != InitStatus) {
    	Resume_Interrupts();
    	 Ret = PFLASH_FAIL;
         return Ret;
    }

    for (;;) {
        CtrlState = checkPflashEraseState();
        if (PFLASH_BUSY != CtrlState) {
            break;
        }
    }
    Resume_Interrupts();

    if (CtrlState != PFLASH_IDLE) {
        Ret = PFLASH_FAIL;
    }
    return Ret;
}

uint8 PflsWrite(unsigned int SourceAddr, uint8 * WriteData, uint16 DataLen)
{
    // uint8 WaitNum = 5;
    PFLASH_STATE CtrlState = PFLASH_MAX;
    uint8 Ret = PFLASH_SUCCESS;

    Suspend_Interrupts();
    if (STATUS_C40_IP_SUCCESS != C40_Ip_MainInterfaceWrite(SourceAddr, DataLen, WriteData, FLS_MASTER_ID)) {

    	Ret = PFLASH_FAIL;
    	Resume_Interrupts();
        return Ret;
    }
    for (;;) {
        CtrlState = checkPflashWriteState();
        if (PFLASH_BUSY != CtrlState) {
            break;
        }
    }
    Resume_Interrupts();
    if (CtrlState != PFLASH_IDLE) {
        Ret = PFLASH_FAIL;
    }
    return Ret;
}

uint8 PflsWriteJump(unsigned int SourceAddr, uint8 * WriteData, uint16 DataLen)
{
    // uint8 WaitNum = 5;
    PFLASH_STATE CtrlState = PFLASH_MAX;
    uint8 Ret = PFLASH_SUCCESS;

   // Suspend_Interrupts();
    if (STATUS_C40_IP_SUCCESS != C40_Ip_MainInterfaceWrite(SourceAddr, DataLen, WriteData, FLS_MASTER_ID)) {
    	Ret = PFLASH_FAIL;
    	//Resume_Interrupts();
        return Ret;
    }
    for (;;) {
        CtrlState = checkPflashWriteState();
        if (PFLASH_BUSY != CtrlState) {
            break;
        }
    }
    //Resume_Interrupts();
    if (CtrlState != PFLASH_IDLE) {
        Ret = PFLASH_FAIL;
    }
    return Ret;
}

uint8 PflsRead(unsigned int SourceAddr, uint8* ReadData, uint16 ReadLen)
{
    uint8 Ret = PFLASH_SUCCESS;

    DO_START;

    DO_ASSERT_ASSIGNMENT(STATUS_C40_IP_SUCCESS != C40_Ip_Read(SourceAddr, ReadLen, ReadData), Ret = PFLASH_FAIL);
    DO_ASSERT_ASSIGNMENT(STATUS_C40_IP_SUCCESS != C40_Ip_Compare(SourceAddr, ReadLen, ReadData), Ret = PFLASH_FAIL);

    DO_END;

    return Ret;
}

uint8 clearAppSourceSecLock(void)
{
    // done
    // Upgrade INFO Address: 0x00480000-0x00481FFF
    uint8 Ret = PFLASH_SUCCESS;
    // unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_2_S256;
    unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_0_S064;

    for (BaseSec; BaseSec < C40_CODE_ARRAY_0_BLOCK_1_S128; BaseSec++) {
        if (PFLASH_SUCCESS != clearFlashLock(BaseSec)) {
            Ret = PFLASH_FAIL;
            break;
        }
    }

    return Ret;
}

uint8 clearAppStartSecLock(void)
{
    // APP Address: 0x00500000-0x007FFFFF
    uint8 Ret = PFLASH_SUCCESS;
    unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_1_S128;

    for (BaseSec; BaseSec < C40_CODE_ARRAY_0_BLOCK_2_S256; BaseSec++) {
        if (PFLASH_SUCCESS != clearFlashLock(BaseSec)) {
            Ret = PFLASH_FAIL;
            break;
        }
    }

    return Ret;
}

uint8 setAppSourceSecLock(void)
{
    // done
    uint8 Ret = PFLASH_SUCCESS;
    // unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_2_S256;
    unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_0_S064;

    for (BaseSec; BaseSec < C40_CODE_ARRAY_0_BLOCK_1_S128; BaseSec++) {
        if (PFLASH_SUCCESS != setFlashLock(BaseSec)) {
            Ret = PFLASH_FAIL;
            break;
        }
    }

    return Ret;
}

uint8 appSourceSecErase(void)
{
    // done
	uint8 Ret = PFLASH_FAIL;

	// if (PFLASH_SUCCESS == PflsErase(C40_CODE_ARRAY_0_BLOCK_2_S256)) {
	// 	Ret = PFLASH_SUCCESS;
	// }
    // Upgrade INFO only 1 sector
    if (PFLASH_SUCCESS == PflsErase(C40_CODE_ARRAY_0_BLOCK_0_S064)) {
		Ret = PFLASH_SUCCESS;
	}

	return Ret;
}

uint8 appSourceFlagErase(void)
{
    uint8 Ret = PFLASH_FAIL;
    PFLASH_STATE CtrlState = PFLASH_MAX;

    C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceSectorErase(C40_CODE_ARRAY_0_BLOCK_1_S128, FLS_MASTER_ID);


    if (STATUS_C40_IP_SUCCESS != InitStatus) {

    	Ret = PFLASH_FAIL;
        return Ret;
    }
        for (;;) {
            CtrlState = checkPflashEraseState();
            if (PFLASH_BUSY != CtrlState) {
                break;
            }
        }
        if(PFLASH_IDLE == CtrlState){
        	Ret = PFLASH_SUCCESS;
        }

    return Ret;
}

uint8 appSourceFlagErase2(void)
{
    uint8 Ret = PFLASH_FAIL;
    PFLASH_STATE CtrlState = PFLASH_MAX;

    // C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceSectorErase(C40_CODE_ARRAY_0_BLOCK_2_S256, FLS_MASTER_ID);
    C40_Ip_StatusType InitStatus = C40_Ip_MainInterfaceSectorErase(C40_CODE_ARRAY_0_BLOCK_0_S064, FLS_MASTER_ID);

    if (STATUS_C40_IP_SUCCESS != InitStatus) {
    	Ret = PFLASH_FAIL;
        return Ret;
    }
    for (;;) {
    	CtrlState = checkPflashEraseState();
        if (PFLASH_BUSY != CtrlState) {
        	break;
        }
    }
    if(PFLASH_IDLE == CtrlState){
    	Ret = PFLASH_SUCCESS;
    }

    return Ret;
}

uint8 appStartSecErase(void)
{
    uint8 Ret = PFLASH_SUCCESS;
    unsigned int BaseSec = C40_CODE_ARRAY_0_BLOCK_1_S128;

    for (BaseSec; BaseSec < C40_CODE_ARRAY_0_BLOCK_2_S256; BaseSec++) {
        if (PFLASH_SUCCESS != PflsErase(BaseSec)) {
            Ret = PFLASH_FAIL;
            break;
        }
    }

    return Ret;
}

uint8 secDataCopy(void)
{
    uint8 Ret = PFLASH_SUCCESS;
    uint8 ReadData[128] = { 0 };
    unsigned int ReadBase = MCU_APP_B_ADDR + PFLASH_DATA_LEN;
    unsigned int WriteBase = MCU_APP_A_ADDR;

    for (uint8 CurrNum = 0; CurrNum < 8192; CurrNum++) {
        (void)memset(ReadData, 0, 128);
        if (PFLASH_SUCCESS == PflsRead(ReadBase, ReadData, 128)) {
            if (ReadBase > 0x6FFF00){
            	break;
            }

            if (PFLASH_SUCCESS != PflsWrite(WriteBase, ReadData, 128)) {
                Ret = PFLASH_FAIL;
                break;
            }
        } else {
            Ret = PFLASH_FAIL;
            break;
        }
        ReadBase += 128;
        WriteBase += 128;
    }

    return Ret;
}

UPDATE_STATE checkUpdateFlag(void)
{
    uint8 UpdateFlag = UPDATE_ERROR;
    uint8 UpdateInfo[UPDATEINFO_LEN] = { 0 };

    DO_START;

    // DO_ASSERT(PFLASH_SUCCESS != clearFlashLock(C40_CODE_ARRAY_0_BLOCK_2_S256));
    DO_ASSERT(PFLASH_SUCCESS != clearFlashLock(C40_CODE_ARRAY_0_BLOCK_0_S064));

    (void)memset(UpdateInfo, 0, UPDATEINFO_LEN);

    DO_ASSERT(PFLASH_SUCCESS != PflsRead(MCU_APP_B_ADDR, UpdateInfo, UPDATEINFO_LEN));

    UpdateFlag = UpdateInfo[0];
    DO_END;

    return UpdateFlag;
}

UPDATE_STATE checkUpdateSourceFlag(void)
{
    uint8 UpdateFlag = UPDATE_ERROR;
    uint8 UpdateInfo[UPDATEINFO_LEN] = { 0 };

    DO_START;

    DO_ASSERT(PFLASH_SUCCESS != clearFlashLock(C40_CODE_ARRAY_0_BLOCK_1_S128));

    (void)memset(UpdateInfo, 0, UPDATEINFO_LEN);

    DO_ASSERT(PFLASH_SUCCESS != PflsRead(MCU_APP_A_ADDR, UpdateInfo, UPDATEINFO_LEN));

    UpdateFlag = UpdateInfo[0];
    DO_END;

    return UpdateFlag;
}

uint8 checkUpdateData(void)
{
	uint8 Ret = PFLASH_FAIL;
    uint8 UpdateInfo[UPDATEINFO_LEN] = { 0 };

    DO_START;

    DO_ASSERT(PFLASH_SUCCESS != clearFlashLock(C40_CODE_ARRAY_0_BLOCK_2_S257));

    (void)memset(UpdateInfo, 0, UPDATEINFO_LEN);

    DO_ASSERT(PFLASH_SUCCESS != PflsRead(MCU_APP_B_ADDR + 8192, UpdateInfo, UPDATEINFO_LEN));

    if(255 != UpdateInfo[0]){
    	Ret = PFLASH_SUCCESS;
    }
    DO_END;

    return Ret;
}

uint8 appDataUpdate(void)
{
    uint8 Ret = PFLASH_FAIL;

    if (PFLASH_SUCCESS == appStartSecErase()) {
        if (PFLASH_SUCCESS == secDataCopy()) {
            Ret = PFLASH_SUCCESS;
        }
    }

    return Ret;
}

uint8 clearLock(void)
{
	uint8 Ret = PFLASH_FAIL;

	if((PFLASH_SUCCESS == clearAppSourceSecLock()) &&
	    (PFLASH_SUCCESS == clearAppStartSecLock())){
		Ret = PFLASH_SUCCESS;
	}

	return Ret;
}

uint8 writeUpdateFlag(UPDATE_STATE UpdateFlag)
{
    uint8 Ret = PFLASH_FAIL;
    uint8 UpdateInfo[UPDATEINFO_LEN] = { 0 };
    uint8 WriteReadInfo[UPDATEINFO_LEN] = { 0 };
    uint8 WriteAddr = MCU_APP_B_ADDR;

    if (UpdateFlag < UPDATE_NEED_SWITCH) {
    	WriteAddr += 8;
    }

    if (PFLASH_SUCCESS == appSourceSecErase()) {
    	UpdateInfo[0] = UpdateFlag;
    	if (PFLASH_SUCCESS == PflsWrite(MCU_APP_B_ADDR, UpdateInfo, UPDATEINFO_LEN)) {
    		if (PFLASH_SUCCESS == PflsRead(MCU_APP_B_ADDR, WriteReadInfo, UPDATEINFO_LEN)) {
    			if(UpdateInfo[0] == WriteReadInfo[0]) {
    				Ret = PFLASH_SUCCESS;
    			}
    		}
    	}
    }

    return Ret;
}

uint8 writeUpdateFlagNotInterrupts(UPDATE_STATE UpdateFlag)
{
	uint8 Ret = PFLASH_FAIL;
	uint8 UpdateInfo[UPDATEINFO_LEN] = { 0 };
	uint8 WriteReadInfo[UPDATEINFO_LEN] = { 0 };
	uint8 WriteAddr = MCU_APP_B_ADDR;

	if (UpdateFlag < UPDATE_NEED_SWITCH) {
		WriteAddr += 8;
	}

	if (PFLASH_SUCCESS == appSourceFlagErase2()) {
		UpdateInfo[0] = UpdateFlag;
	    if (PFLASH_SUCCESS == PflsWriteJump(MCU_APP_B_ADDR, UpdateInfo, UPDATEINFO_LEN)) {
	    	Ret = PFLASH_SUCCESS;
	    }
	}

	return Ret;
}

void setEraseFlag(uint8 Flag)
{
    CtrlFlag[ERASE_INDEX] = Flag;
}

uint8 getEraseFlag(void)
{
    return CtrlFlag[ERASE_INDEX];
}

void setEraseState(uint8 State)
{
    CtrlState[ERASE_INDEX] = State;
}

uint8 getEraseState(void)
{
    return CtrlState[ERASE_INDEX];
}

void setWriteFlag(uint8 Flag)
{
    CtrlFlag[WRITE_INDEX] = Flag;
}

uint8 getWriteFlag(void)
{
    return CtrlFlag[WRITE_INDEX];
}

void setWriteState(uint8 State)
{
    CtrlFlag[WRITE_INDEX] = State;
}

uint8 getWriteState(void)
{
    return CtrlFlag[WRITE_INDEX];
}

void setClearLockFlag(uint8 Flag)
{
    CtrlFlag[CLEAR_LOCK_INDEX] = Flag;
}

uint8 getClearLockFlag()
{
    return CtrlFlag[CLEAR_LOCK_INDEX];
}

void setClearLockState(uint8 State)
{
    CtrlState[CLEAR_LOCK_INDEX] = State;
}

uint8 getClearLockState()
{
    return CtrlState[CLEAR_LOCK_INDEX];
}

void setSetLockFlag(uint8 Flag)
{
    CtrlFlag[SET_LOCK_INDEX] = Flag;
}

uint8 getSetLockFlag()
{
    return CtrlFlag[SET_LOCK_INDEX];
}
