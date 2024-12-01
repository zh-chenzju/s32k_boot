#ifndef __PFLSCTRL_H__
#define __PFLSCTRL_H__

typedef unsigned char uint8;
typedef unsigned short uint16;

#define DO_START do {
#define DO_ASSERT(ex) if(ex) {break;}
#define DO_ASSERT_ASSIGNMENT(ex, exp) if(ex) {exp; break;}
#define DO_END } while(0);

///接口使用说明
///先擦后写，擦之前需要检查扇区是否写保护

#ifndef PFLASH_SUCCESS
    #define PFLASH_SUCCESS (1U)
#endif

#ifndef PFLASH_FAIL
    #define PFLASH_FAIL (0U)
#endif

#ifndef FLS_MASTER_ID
    #define FLS_MASTER_ID (0U)
#endif

#ifndef UPTADE_A
    #define UPTADE_A (0U)
#endif

#ifndef UPTADE_B
    #define UPTADE_B (1U)
#endif
///
#define MCU_APP_A_ADDR (0x00500000U)
// #define MCU_APP_B_ADDR (0x00600000U)
#define MCU_APP_B_ADDR (0x00480000U)
///
#define WAIT_TIMEOUT_NUM (5U)
///
#define UPDATEINFO_LEN (8U)

///
#define UPDATE_FLAG_INDEX (0U)
#define UPDATE_SECTOR_NUM_INDEX (1U)
///
#define UPDATE_SECTOR_NUM_EMPTY (0U)
#define UPDATE_SECTOR_NUM_INIT (255U)
///
#define DELAY_TIME (100U)
///
#define PFLASH_CTRL_SUCCESS (1U)
#define PFLASH_CTRL_FAIL (0U)
///
#define PFLASH_DATA_LEN (8192U)
///
#define FLAG_NEED_CTRL (1U)
#define FLAG_NOT_NEED_CTRL (0U)
#define FLAG_NEED_CTRL_INIT (2U)
///
#define FLAG_NOT_CTRL (0U)
#define FLAG_CTRL_END (1U)
///
#define FLAG_STATE_NUM (4U)
#define ERASE_INDEX (0U)
#define CLEAR_LOCK_INDEX (1U)
#define SET_LOCK_INDEX (2U)
#define WRITE_INDEX (3U)
///
#define SECTOR_PAGE_SIZE (64U)
#define MCU_UPDATE_MAX_SIZE (1024U)
#define MCU_UPDATE_NUM_MAX (MCU_UPDATE_MAX_SIZE / SECTOR_PAGE_SIZE)

#pragma pack(1)

typedef enum {
    PFLASH_BUSY = 0U,
    PFLASH_ERROR,
    PFLASH_IDLE,
    PFLASH_MAX
} PFLASH_STATE;

typedef enum
{
    UPDATE_JUMP_ERASE = 255,
    UPDATE_WRITE_SUCCESS = 127,
    UPDATE_NEED_SWITCH = 63,
    UPDATE_SWITCH_SUCESS = 31,
    UPDATE_SUCESS_JUST_A = 30,
    UPDATE_COPY_SUCESS = 15,
    UPDATE_WRITE_FAIL = 7,
    UPDATE_WRITE_START = 1,
    UPDATE_ERROR = 0
} UPDATE_STATE;
#pragma pack ()

extern uint8 PflsIint(void);

extern UPDATE_STATE checkUpdateFlag(void);

extern uint8 appDataUpdate(void);

extern uint8 writeUpdateFlag(UPDATE_STATE UpdateFlag);

extern uint8 appSourceSecErase(void);

extern uint8 clearLock(void);
#endif /* __PFLSCTRL_H__ */
