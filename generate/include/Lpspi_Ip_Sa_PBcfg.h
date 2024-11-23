/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPSPI
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors NXP
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef LPSPI_IP_SAPBCFG_H
#define LPSPI_IP_SAPBCFG_H

/**   
*   @file    Lpspi_Ip_PBcfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR Spi - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup LPSPI_DRIVER_CONFIGURATION Lpspi Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* Inclusion of incompatible header files shall be avoided */
#define LPSPI_IP_SA_VENDOR_ID_PBCFG                        43
#define LPSPI_IP_SA_AR_RELEASE_MAJOR_VERSION_PBCFG         4
#define LPSPI_IP_SA_AR_RELEASE_MINOR_VERSION_PBCFG         7
#define LPSPI_IP_SA_AR_RELEASE_REVISION_VERSION_PBCFG      0
#define LPSPI_IP_SA_SW_MAJOR_VERSION_PBCFG                 3
#define LPSPI_IP_SA_SW_MINOR_VERSION_PBCFG                 0
#define LPSPI_IP_SA_SW_PATCH_VERSION_PBCFG                 0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define LPSPI_IP_SA_CONFIG_PB \
    extern const Lpspi_Ip_ExternalDeviceType Lpspi_Ip_DeviceAttributes_SpiExternalDevice_0_Instance_0; \
    extern const Lpspi_Ip_ConfigType Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_0_Instance_0; \

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

#endif 

/** @} */


