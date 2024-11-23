/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
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
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef AXBS_IP_CFG_DEFINES_H
#define AXBS_IP_CFG_DEFINES_H

/**
*   @file Axbs_Ip_Cfg_Defines.h
*
*   @addtogroup AXBS_IP AXBS IPV Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
 * Include specific header file
 */
#include "StandardTypes.h" 
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RM_AXBS_IP_CFG_DEFINES_VENDOR_ID                    43
#define RM_AXBS_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define RM_AXBS_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     7
#define RM_AXBS_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define RM_AXBS_IP_CFG_DEFINES_SW_MAJOR_VERSION             3
#define RM_AXBS_IP_CFG_DEFINES_SW_MINOR_VERSION             0
#define RM_AXBS_IP_CFG_DEFINES_SW_PATCH_VERSION             0
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/** @brief    Macro representing of support instance AXBS */
#define AXBS_IP_INSTANCE_COUNT               AXBS_LITE_INSTANCE_COUNT
/** @brief    Array initializer of AXBS peripheral base address */
#define AXBS_IP_ARRAY_BASE_ADDRS             IP_AXBS_LITE_BASE_ADDRS

/* Definition of AXBS Instances */
#define AXBS_0                  (uint32)(0U)
#define AXBS_1                  (uint32)(1U)
#define AXBS_2                  (uint32)(2U)
#define AXBS_3                  (uint32)(3U)
#define AXBS_4                  (uint32)(4U)

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* AXBS_IP_DEVICE_REGISTERS_H */
