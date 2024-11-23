/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPUART_FLEXIO
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file   Lpuart_Lin_Ip_PBcfg.c
*   @implements Lpuart_Lin_Ip_PBcfg.c_Artifact
*
*   @addtogroup LPUART_LIN
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Lpuart_Lin_Ip_Cfg.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_LIN_IP_SA_PBCFG_VENDOR_ID_C           43
#define LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define LPUART_LIN_IP_SA_PBCFG_SW_MAJOR_VERSION_C    3
#define LPUART_LIN_IP_SA_PBCFG_SW_MINOR_VERSION_C    0
#define LPUART_LIN_IP_SA_PBCFG_SW_PATCH_VERSION_C    0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Lpuart_Lin_Ip_Cfg.h */
#if (LPUART_LIN_IP_SA_PBCFG_VENDOR_ID_C != LPUART_LIN_IP_CFG_VENDOR_ID)
    #error "Lpuart_Lin_Ip_Sa_PBcfg.c and Lpuart_Lin_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Lpuart_Lin_Ip_Cfg header file are of the same Autosar version */
#if ((LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != LPUART_LIN_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_MINOR_VERSION_C    != LPUART_LIN_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_LIN_IP_SA_PBCFG_AR_RELEASE_REVISION_VERSION_C != LPUART_LIN_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Lpuart_Lin_Ip_Sa_PBcfg.c and Lpuart_Lin_Ip_Cfg.h are different"
#endif
/* Check if current file and Lpuart_Lin_Ip_Cfg header file are of the same Software version */
#if ((LPUART_LIN_IP_SA_PBCFG_SW_MAJOR_VERSION_C != LPUART_LIN_IP_CFG_SW_MAJOR_VERSION) || \
     (LPUART_LIN_IP_SA_PBCFG_SW_MINOR_VERSION_C != LPUART_LIN_IP_CFG_SW_MINOR_VERSION) || \
     (LPUART_LIN_IP_SA_PBCFG_SW_PATCH_VERSION_C != LPUART_LIN_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lpuart_Lin_Ip_Sa_PBcfg.c and Lpuart_Lin_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

extern void LpuartSlaveCallback(uint8 Instance, Lpuart_Lin_Ip_StateStructType *LpuartStateStruct);
/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

extern Lpuart_Lin_Ip_StateStructType Lpuart_Lin_Ip_axStateStructure[LPUART_LIN_IP_NUMBER_OF_INSTANCES];

#define LIN_43_LPUART_FLEXIO_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

#define LIN_43_LPUART_FLEXIO_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"

/**
* @brief          Hardware configuration for Lin Hardware Instance LPUART_IP_0 - Configuration:
*
*
*/
const Lpuart_Lin_Ip_UserConfigType Lpuart_Lin_Ip_Sa_pHwConfigPB_0 =
{

    0U, /*!< Hardware instance */

    0x208, /*!< Baudrate divisor */

    16U, /*!< Baudrate OSR */

    (boolean)LPUART_LIN_IP_MASTER, /*!< Master node */

    LPUART_LIN_IP_BREAK_CHAR_13_BIT_MINIMUM_U8,     /*!< Break character length is transmitted */

    (uint8)1U,     /*!< Length of break character can be detected */
#if (LPUART_LIN_IP_AUTO_BAUD == STD_ON)
    (boolean)FALSE, /*!<  Autobaudrate feature */
#endif
    (Lpuart_Lin_Ip_CallbackType)NULL_PTR, /*!< Callback function to invoke after receiving a byte or transmitting a byte. */

    &Lpuart_Lin_Ip_axStateStructure[0U], /*!< Runtime state structure referrence */
#if (LPUART_LIN_IP_FRAME_TIMEOUT_DISABLE == STD_OFF)
#ifdef LPUART_LIN_IP_START_TIMER_NOTIFICATION
    4584U,           /*!< HeaderTimeoutValue in microseconds */

    146U,         /*!< ResponseTimeoutValue in microseconds for 1 byte */
#endif
#endif /* (LPUART_LIN_IP_START_TIMER_NOTIFICATION == STD_OFF) */
    (uint8)248, /*!< Wakeup byte */

    80000000U           /*!< Channel clock */
};
/**
* @brief          Hardware configuration for Lin Hardware Instance LPUART_IP_1 - Configuration:
*
*
*/
const Lpuart_Lin_Ip_UserConfigType Lpuart_Lin_Ip_Sa_pHwConfigPB_1 =
{

    1U, /*!< Hardware instance */

    0x104, /*!< Baudrate divisor */

    16U, /*!< Baudrate OSR */

    (boolean)LPUART_LIN_IP_SLAVE,  /*!< Slave node */

    LPUART_LIN_IP_BREAK_CHAR_13_BIT_MINIMUM_U8,     /*!< Break character length is transmitted */

    (uint8)1U,     /*!< Length of break character can be detected */
#if (LPUART_LIN_IP_AUTO_BAUD == STD_ON)
    (boolean)FALSE, /*!<  Autobaudrate feature */
#endif
    (Lpuart_Lin_Ip_CallbackType)LpuartSlaveCallback, /*!< Callback function to invoke after receiving a byte or transmitting a byte. */

    &Lpuart_Lin_Ip_axStateStructure[1U], /*!< Runtime state structure referrence */
#if (LPUART_LIN_IP_FRAME_TIMEOUT_DISABLE == STD_OFF)
#ifdef LPUART_LIN_IP_START_TIMER_NOTIFICATION
    4584U,           /*!< HeaderTimeoutValue in microseconds */

    146U,         /*!< ResponseTimeoutValue in microseconds for 1 byte */
#endif
#endif /* (LPUART_LIN_IP_START_TIMER_NOTIFICATION == STD_OFF) */
    (uint8)248, /*!< Wakeup byte */

    40000000U           /*!< Channel clock */
};
#define LIN_43_LPUART_FLEXIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LPUART_FLEXIO_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

