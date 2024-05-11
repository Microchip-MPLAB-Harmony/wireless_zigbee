/*******************************************************************************
  ZLL Device Diagnostics Header File

  Company:
    Microchip Technology Inc.

  File Name:
    N_Diagnostics.h

  Summary:
    This file contains the ZLL Device Diagnostics functions.

  Description:
    This file contains the ZLL Device Diagnostics functions.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END


#ifndef N_DIAGNOSTICS_H
#define N_DIAGNOSTICS_H

/*******************************************************************************
* INCLUDE FILES
*******************************************************************************/
#include <sysTypes.h>

/*******************************************************************************
* C++ DECLARATION WRAPPER
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* EXPORTED TYPES
*******************************************************************************/


/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/
#define N_DIAGNOSTICS_MAC_RX_BCAST_ID                                 CCPU_TO_LE16(0x0100)
#define N_DIAGNOSTICS_MAC_TX_BCAST_ID                                 CCPU_TO_LE16(0x0101)
#define N_DIAGNOSTICS_MAC_RX_UCAST_ID                                 CCPU_TO_LE16(0x0102)
#define N_DIAGNOSTICS_MAC_TX_UCAST_ID                                 CCPU_TO_LE16(0x0103)
#define N_DIAGNOSTICS_MAC_TX_UCAST_FAIL_ID                            CCPU_TO_LE16(0x0105)
#define N_DIAGNOSTICS_APS_RX_BCAST_ATTRIBUTE_ID                       CCPU_TO_LE16(0x0106)
#define N_DIAGNOSTICS_APS_TX_BCAST_ATTRIBUTE_ID                       CCPU_TO_LE16(0x0107)
#define N_DIAGNOSTICS_APS_RX_UCAST_ID                                 CCPU_TO_LE16(0x0108)
#define N_DIAGNOSTICS_APS_TX_UCAST_SUCCESS_ID                         CCPU_TO_LE16(0x0109)
#define N_DIAGNOSTICS_APS_TX_UCAST_RETRY_ATTRIBUTE_ID                 CCPU_TO_LE16(0x010a)
#define N_DIAGNOSTICS_ROUTE_DISC_INITIATED_ATTRIBUTE_ID               CCPU_TO_LE16(0x010c)
#define N_DIAGNOSTICS_NEIGHBOR_ADDED_ATTRIBUTE_ID                     CCPU_TO_LE16(0x010d)
#define N_DIAGNOSTICS_NEIGHBOR_REMOVED_ATTRIBUTE_ID                   CCPU_TO_LE16(0x010e)
#define N_DIAGNOSTICS_NEIGHBOR_STALE_ATTRIBUTE_ID                     CCPU_TO_LE16(0x010f)
#define N_DIAGNOSTICS_PACKET_BUFFER_ALLOCATE_FAILURE_ATTRIBUTE_ID     CCPU_TO_LE16(0x0117)
#define N_DIAGNOSTICS_AVG_MAC_RETRY_APS_MSG_SENT_ATTRIBUTE_ID         CCPU_TO_LE16(0x011b)
#define N_DIAGNOSTICS_LAST_MSG_LQI_ATTRIBUTE_ID                       CCPU_TO_LE16(0x011c)
#define N_DIAGNOSTICS_LAST_MSG_RSSI_ATTRIBUTE_ID                      CCPU_TO_LE16(0x011d)
#define N_DIAGNOSTICS_MAC_TX_UCAST_CH_ACC_FAIL_ID                     CCPU_TO_LE16(0xf000)
#define N_DIAGNOSTICS_MAC_TX_BCAST_CH_ACC_FAIL_ID                     CCPU_TO_LE16(0xf001)
#define N_DIAGNOSTICS_MAC_TX_UCAST_NO_ACK_ID                          CCPU_TO_LE16(0xf002)

/*******************************************************************************
* EXPORTED CONSTANTS
*******************************************************************************/
typedef uint16_t N_Diagnostics_AttributeId_t; //!< The type for holding attribute IDs

/*******************************************************************************
* EXPORTED FUNCTIONS
*******************************************************************************/

/***************************************************************************/
/**
\brief Initializatises the attributes and subscribes to required events
*******************************************************************************/
void N_Diagnostics_Init(void);

/** Get Diagnostics  of an attribute.
    \param attributeId The diagnostics attribute ID
  *@retvals The attribute's  value if the ID is found, 0xffffffff if not found    
*/
uint32_t N_Diagnostics_GetValue(N_Diagnostics_AttributeId_t attributeId);

/*******************************************************************************
* END OF C++ DECLARATION WRAPPER
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_DIAGNOSTICS_H
