/*******************************************************************************
  NWK Discovery Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkDiscovery.h

  Summary:
    This file contains the declaration and defines for NWK Discovery mechanism.

  Description:
    This file contains the declaration and defines for NWK Discovery mechanism.
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

#if !defined _NWK_DISCOVERY_H
#define _NWK_DISCOVERY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Internal states of NLME-NETWORK-DISCOVERY component */
typedef enum _NwkDiscoveryState_t
{
  NWK_DISCOVERY_IDLE_STATE = 0xD6,
  NWK_DISCOVERY_FIRST_STATE = 0x70,
  NWK_DISCOVERY_BEGIN_STATE = NWK_DISCOVERY_FIRST_STATE,
  NWK_DISCOVERY_MAC_SCAN_STATE = 0x71,
  NWK_DISCOVERY_CONFIRM_STATE = 0x72,
  NWK_DISCOVERY_LAST_STATE
} NwkDiscoveryState_t;

/** Internal parameters of NLME-NETWORK-DISCOVERY */
typedef struct _NwkDiscovery_t
{
  QueueDescriptor_t queue; /**< Queue of requests from upper layer */
  NwkDiscoveryState_t state; /**< finite-state machine */
} NwkDiscovery_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of NLME-NETWORK-DISCOVERY component
 ******************************************************************************/
NWK_PRIVATE void nwkDiscoveryTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-NETWORK-DISCOVERY component
 ******************************************************************************/
NWK_PRIVATE void nwkResetDiscovery(void);

/******************************************************************************
  \brief nwkDiscovery idle checking.

  \return true, if nwkDiscovery performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkDiscoveryIsIdle(void);

#endif /* _NWK_DISCOVERY_H */
/** eof nwkDiscovery.h */

