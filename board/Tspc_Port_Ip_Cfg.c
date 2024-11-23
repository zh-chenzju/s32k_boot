/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7 
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_AUTOSAR_4_4_-_R21-11_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
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
*   @file      Tspc_Port_Ip_Cfg.h
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Tspc_Port_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define TSPC_PORT_IP_VENDOR_ID_CFG_C                       43
#define TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C        7
#define TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_C                3
#define TSPC_PORT_IP_SW_MINOR_VERSION_CFG_C                0
#define TSPC_PORT_IP_SW_PATCH_VERSION_CFG_C                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same vendor */
#if (TSPC_PORT_IP_VENDOR_ID_CFG_C != TSPC_PORT_IP_VENDOR_ID_CFG_H)
    #error "Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are different"
#endif
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_C != TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_SW_MINOR_VERSION_CFG_C != TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_SW_PATCH_VERSION_CFG_C != TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are different"
#endif

/*==================================================================================================
                             LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                             LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                            LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL VARIABLES
==================================================================================================*/

/* clang-format off */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: M7_0}
- pin_list:
  - {pin_num: '89', peripheral: SIUL2, signal: 'gpio, 89', pin_signal: PTC25, direction: OUTPUT}
  - {pin_num: '95', peripheral: CAN0, signal: can0_rx, pin_signal: PTB0}
  - {pin_num: '94', peripheral: CAN0, signal: can0_tx, pin_signal: PTB1}
  - {pin_num: '130', peripheral: LPUART9, signal: lpuart9_rx, pin_signal: PTB9}
  - {pin_num: '76', peripheral: LPUART5, signal: lpuart5_rx, pin_signal: PTB28}
  - {pin_num: '6', peripheral: LPSPI1, signal: lpspi1_pcs0, pin_signal: PTA21, direction: OUTPUT}
  - {pin_num: '146', peripheral: SIUL2, signal: 'gpio, 134', pin_signal: PTE6, direction: OUTPUT}
  - {pin_num: '143', peripheral: SIUL2, signal: 'gpio, 16', pin_signal: PTA16, direction: INPUT}
  - {pin_num: '144', peripheral: SIUL2, signal: 'gpio, 146', pin_signal: PTE18, direction: OUTPUT}
  - {pin_num: '156', peripheral: ADC2, signal: adc2_p5, pin_signal: PTE23}
  - {pin_num: '131', peripheral: LPSPI5, signal: lpspi5_sck, pin_signal: PTD26, direction: INPUT}
  - {pin_num: '134', peripheral: LPSPI5, signal: lpspi5_sin, pin_signal: PTD28, direction: INPUT}
  - {pin_num: '132', peripheral: LPSPI5, signal: lpspi5_sout, pin_signal: PTD27, direction: OUTPUT}
  - {pin_num: '145', peripheral: LPSPI5, signal: lpspi5_pcs0, pin_signal: PTA15, direction: INPUT}
  - {pin_num: '104', peripheral: eMIOS_0, signal: emios_0_ch_7_g, pin_signal: PTE7, direction: OUTPUT}
  - {pin_num: '117', peripheral: eMIOS_0, signal: emios_0_ch_0_x, pin_signal: PTB12, direction: OUTPUT}
  - {pin_num: '130', peripheral: LPSPI4, signal: lpspi4_sout, pin_signal: PTB9, direction: OUTPUT, pullSelect: pullUp}
  - {pin_num: '133', peripheral: LPSPI4, signal: lpspi4_pcs0, pin_signal: PTB8, direction: OUTPUT}
  - {pin_num: '129', peripheral: LPSPI4, signal: lpspi4_sck, pin_signal: PTB10, direction: OUTPUT}
  - {pin_num: '80', peripheral: LPSPI2, signal: lpspi2_sck, pin_signal: PTB29, direction: OUTPUT}
  - {pin_num: '72', peripheral: LPSPI2, signal: lpspi2_pcs0, pin_signal: PTB25, direction: OUTPUT}
  - {pin_num: '75', peripheral: LPSPI2, signal: lpspi2_sout, pin_signal: PTB27, direction: OUTPUT}
  - {pin_num: '36', peripheral: SIUL2, signal: 'gpio, 137', pin_signal: PTE9, direction: OUTPUT}
  - {pin_num: '35', peripheral: SIUL2, signal: 'gpio, 111', pin_signal: PTD15, direction: OUTPUT}
  - {pin_num: '31', peripheral: SIUL2, signal: 'gpio, 113', pin_signal: PTD17, direction: OUTPUT}
  - {pin_num: '61', peripheral: SIUL2, signal: 'gpio, 65', pin_signal: PTC1, direction: OUTPUT}
  - {pin_num: '28', peripheral: LPUART0, signal: lpuart0_tx, pin_signal: PTA27, direction: OUTPUT}
  - {pin_num: '30', peripheral: LPUART0, signal: lpuart0_rx, pin_signal: PTA28}
  - {pin_num: '1', peripheral: LPUART1, signal: lpuart1_tx, pin_signal: PTA18, direction: OUTPUT}
  - {pin_num: '2', peripheral: LPUART1, signal: lpuart1_rx, pin_signal: PTA19}
  - {pin_num: '32', peripheral: LPUART2, signal: lpuart2_tx, pin_signal: PTA29, direction: OUTPUT}
  - {pin_num: '33', peripheral: LPUART2, signal: lpuart2_rx, pin_signal: PTA30}
  - {pin_num: '102', peripheral: LPUART3, signal: lpuart3_rx, pin_signal: PTA6}
  - {pin_num: '100', peripheral: LPUART3, signal: lpuart3_tx, pin_signal: PTA7, direction: OUTPUT}
  - {pin_num: '135', peripheral: SIUL2, signal: 'gpio, 1', pin_signal: PTA1, direction: OUTPUT}
  - {pin_num: '12', peripheral: SIUL2, signal: 'gpio, 133', pin_signal: PTE5, identifier: KL15_INPUT, direction: INPUT}
  - {pin_num: '62', peripheral: SIUL2, signal: 'gpio, 64', pin_signal: PTC0, direction: OUTPUT}
  - {pin_num: '34', peripheral: LPSPI0, signal: lpspi0_sin, pin_signal: PTD16, direction: INPUT}
  - {pin_num: '55', peripheral: LPSPI0, signal: lpspi0_sck, pin_signal: PTD11, direction: OUTPUT}
  - {pin_num: '137', peripheral: SIUL2, signal: 'gpio, 0', pin_signal: PTA0, direction: OUTPUT}
  - {pin_num: '13', peripheral: LPSPI0, signal: lpspi0_pcs0, pin_signal: PTE4, direction: OUTPUT}
  - {pin_num: '39', peripheral: LPSPI0, signal: lpspi0_pcs1, pin_signal: PTA31, direction: OUTPUT}
  - {pin_num: '160', peripheral: ADC1, signal: adc1_s10, pin_signal: PTA11}
  - {pin_num: '121', peripheral: ADC0, signal: adc0_s16, pin_signal: PTD2}
  - {pin_num: '48', peripheral: LPSPI0, signal: lpspi0_sout, pin_signal: PTB4, direction: OUTPUT}
  - {pin_num: '93', peripheral: eMIOS_1, signal: emios_1_ch_4_h, pin_signal: PTC27, direction: OUTPUT}
  - {pin_num: '66', peripheral: eMIOS_1, signal: emios_1_ch_9_h, pin_signal: PTC16, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* No registers that support TSPC were configured*/

/*==================================================================================================
                                      LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                           LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
