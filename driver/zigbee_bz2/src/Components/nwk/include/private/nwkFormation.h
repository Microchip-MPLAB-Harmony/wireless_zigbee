/*******************************************************************************
  NWK Formation Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkFormation.h

  Summary:
    This file contains the defines and constants for NWK Formation.

  Description:
    This file contains the defines and constants for NWK Formation.
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

#if !defined _NWK_FORMATION_H
#define _NWK_FORMATION_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysTypes.h>
#include <sysQueue.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Internal states of NLME-NETWORK-FORMATION component */
typedef enum _NwkFormationState_t
{
  NWK_FORMATION_IDLE_STATE = 0xB7,
  NWK_FORMATION_FIRST_STATE = 0x54,
  NWK_FORMATION_BEGIN_STATE = NWK_FORMATION_FIRST_STATE,
  NWK_FORMATION_MAC_REALIGNMENT_STATE = 0x55,
  NWK_FORMATION_MAC_ACTIVE_SCAN_STATE = 0x56,
  NWK_FORMATION_MAC_ED_SCAN_STATE = 0x57,
  NWK_FORMATION_CONFIRM_STATE = 0x58,
  NWK_FORMATION_SET_SHORT_ADDR_STATE = 0x59,
  NWK_FORMATION_SET_BEACON_PAYLOAD_LEN_STATE = 0x5A,
  NWK_FORMATION_SET_BEACON_PAYLOAD_STATE = 0x5B,
  NWK_FORMATION_SET_RX_ON_WHEN_IDLE_STATE = 0x5C,
  NWK_FORMATION_MAC_START_STATE = 0x5D,
  NWK_FORMATION_RX_ENABLE_STATE = 0x5E,
  NWK_FORMATION_SET_TRANSACTION_TIME_STATE = 0x5F,
  NWK_FORMATION_SET_EXT_ADDR_STATE = 0x60,
  NWK_FORMATION_LAST_STATE
} NwkFormationState_t;

/** Internal parameters of NLME-NETWORK-FORMATION component. */
typedef struct _NwkFormation_t
{
  QueueDescriptor_t queue; /**< Queue of requests from upper layer. */
  NwkFormationState_t state; /**< finite-state machine. */
  bool coordRealignment;
} NwkFormation_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _COORDINATOR_  || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_))
/**************************************************************************//**
  \brief Main task handler of NLME-NETWORK-FORMATION component.
 ******************************************************************************/
NWK_PRIVATE void nwkFormationTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-NETWORK-FORMATION component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetFormation(void);

/******************************************************************************
  \brief nwkFormation idle checking.

  \return true, if nwkFormation performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkFormationIsIdle(void);

#else /* not defined (_COORDINATOR_) || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_)) */

#define nwkFormationTaskHandler NULL
#define nwkFormationIsIdle NULL
#define nwkResetFormation() (void)0

#endif /* #if defined(_COORDINATOR_) || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_)) */
#endif /* _NWK_FORMATION_H */
/** eof nwkFormation.h */

