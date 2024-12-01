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

#ifndef SIUL2_PORT_IP_CFG_H
#define SIUL2_PORT_IP_CFG_H

/**
*   @file      Siul2_Port_Ip_Cfg.h
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
#include "S32K314_SIUL2.h"
#include "Siul2_Port_Ip_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_PORT_IP_VENDOR_ID_CFG_H                       43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H        7
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H     0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H                3
#define SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H                0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_CFG_H != SIUL2_PORT_IP_TYPES_VENDOR_ID_H)
    #error "Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H    != SIUL2_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H    != SIUL2_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H != SIUL2_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h are different"
#endif
/* Check if Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H != SIUL2_PORT_IP_TYPES_SW_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H != SIUL2_PORT_IP_TYPES_SW_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H != SIUL2_PORT_IP_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip_Cfg.h and Siul2_Port_Ip_Types.h are different"
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                      DEFINES AND MACROS
==================================================================================================*/
#define SIUL2_MSCR_SSS_MASK                      (0xFU)
#define SIUL2_MSCR_SSS_SHIFT                     (0U)
#define SIUL2_MSCR_SSS_WIDTH                     (4U)
#define SIUL2_MSCR_SSS(x)                        (((uint32)(((uint32)(x)) << SIUL2_MSCR_SSS_SHIFT)) & SIUL2_MSCR_SSS_MASK)

#define SIUL2_MSCR_SRE_MASK                      (0x4000U)
#define SIUL2_MSCR_SRE_SHIFT                     (14U)
#define SIUL2_MSCR_SRE_WIDTH                     (1U)
#define SIUL2_MSCR_SRE(x)                        (((uint32)(((uint32)(x)) << SIUL2_MSCR_SRE_SHIFT)) & SIUL2_MSCR_SRE_MASK)


/*! @brief Definitions for BOARD_InitPins Functional Group */

/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 47

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*! @brief User configuration structure */
extern const Siul2_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*! @brief Defines for user pin and port configurations */
#define LED_PIN                 9u
#define LED_PORT                PTC_H_HALF
#define GPO_CS0_PIN             5u
#define GPO_CS0_PORT            PTA_H_HALF
#define GPIO_O1_PIN             6u
#define GPIO_O1_PORT            PTE_L_HALF
#define GPIO_IN1_PIN            0u
#define GPIO_IN1_PORT           PTA_H_HALF
#define GPIO_O2_PIN             2u
#define GPIO_O2_PORT            PTE_H_HALF
#define VBAT_12V_CTR_PIN        9u
#define VBAT_12V_CTR_PORT       PTE_L_HALF
#define Sen_CTR_PIN             15u
#define Sen_CTR_PORT            PTD_L_HALF
#define VCC_5V_CTR_PIN          1u
#define VCC_5V_CTR_PORT         PTD_H_HALF
#define CAN_STB_PIN             1u
#define CAN_STB_PORT            PTC_L_HALF
#define LIN_SLP_PIN             1u
#define LIN_SLP_PORT            PTA_L_HALF
#define KL15_INPUT_PIN          5u
#define KL15_INPUT_PORT         PTE_L_HALF
#define VOUT_EN_PIN             0u
#define VOUT_EN_PORT            PTC_L_HALF
#define SPI_nRES_PIN            0u
#define SPI_nRES_PORT           PTA_L_HALF
#define SPI_NCS1_PIN            4u
#define SPI_NCS1_PORT           PTE_L_HALF
#define SPI_NCS2_PIN            15u
#define SPI_NCS2_PORT           PTA_H_HALF
#define Leg_Tem_Sen2_AD_PIN     11u
#define Leg_Tem_Sen2_AD_PORT    PTA_L_HALF
#define Vbat_12V_AD_PIN         2u
#define Vbat_12V_AD_PORT        PTD_L_HALF
#define Motor_PWM_CTR_PIN       11u
#define Motor_PWM_CTR_PORT      PTC_H_HALF
#define LED_CTR_PIN             1u
#define LED_CTR_PORT            PTB_H_HALF

/*==================================================================================================
                                           ENUMS
==================================================================================================*/

/*==================================================================================================
                               STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                               GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                               FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* SIUL2_PORT_IP_CFG_H */

