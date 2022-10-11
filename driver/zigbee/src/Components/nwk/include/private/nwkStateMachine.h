/*******************************************************************************
  NWK State Machine Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkStateMachine.h

  Summary:
    This file contains the NWK State Machine Handling.

  Description:
    This file contains the NWK State Machine Handling.
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

#if !defined _NWK_STATE_MACHINE_H
#define _NWK_STATE_MACHINE_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkCommon.h>
#include <private/nwkMem.h>

/******************************************************************************
                                Define(s) section
 ******************************************************************************/
/* Identifiers of modules, packed to groups. A combination of modules, which
   activity is accepted, forms global NWK layer state. All modules in group
   change their status simultaneously by some event, so if the activity
   permission politics changes, perform corrsponding changes. */

#define NWK_MODULE_ID_DATA_REQ        (1U << 0)
#define NWK_MODULE_ID_SYNC            (1U << 0)
#define NWK_MODULE_ID_LINK_STATUS     (1U << 0)
#define NWK_MODULE_ID_NETWORK_COMMAND (1U << 0)
#define NWK_MODULE_ID_LEAVE           (1U << 0)
#define NWK_MODULE_ID_DATA_IND        (1U << 0)
#define NWK_MODULE_ID_EDSCAN          (1U << 0)
#define NWK_MODULE_ID_ROUTE_DISCOVERY (1U << 0)
#define NWK_MODULE_ID_PERMIT_JOINING  (1U << 0)

#define NWK_MODULE_ID_FORMATION       (1U << 1)
#define NWK_MODULE_ID_START_ROUTER    (1U << 2)
#define NWK_MODULE_ID_JOIN_IND        (1U << 3)
#define NWK_MODULE_ID_ENDDEVICE_TIMEOUT_IND (1U << 3)

#define NWK_MODULE_ID_JOIN_REQ        (1U << 4)
#define NWK_MODULE_ID_COMMAND_REQ     (1U << 4)
#define NWK_MODULE_ID_ENDDEVICE_TIMEOUT_REQ (1U << 4)

#define NWK_MODULE_ID_COMMAND_IND     (1U << 5)
#define NWK_MODULE_ID_DISCOVERY       (1U << 5)

#define NWK_MODULE_ID_PANID_CONFLICT  (1U << 6)
#define NWK_MODULE_ID_ADDR_CONFLICT   (1U << 6)

/** Reserved bit is set until NWK reset process completed. */
#define NWK_MODULE_ID_RESERVED        (1U << 7)

/* Module permissions */
#define NWK_MODULE_NONE               0U

#define NWK_EVENT_RESET_REQ \
  (NWK_MODULE_ID_DISCOVERY | NWK_MODULE_ID_FORMATION \
  | NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ \
  | NWK_MODULE_ID_COMMAND_IND | NWK_MODULE_ID_START_ROUTER)

#define NWK_EVENT_FORMATION_SUCCESS \
  ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_FORMATION))

#define NWK_EVENT_AWAITING_ANNCE \
  ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_FORMATION \
                          & ~NWK_MODULE_ID_PANID_CONFLICT \
                          & ~NWK_MODULE_ID_ADDR_CONFLICT))

#define NWK_EVENT_LEAVE_ALL_CHILDREN \
  ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_JOIN_IND\
                          & ~NWK_MODULE_ID_FORMATION \
                          & ~NWK_MODULE_ID_START_ROUTER))

#define NWK_EVENT_LEAVE_SUCCESS \
  (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ \
  | NWK_MODULE_ID_FORMATION)

#define NWK_EVENT_REJOIN_REQ \
  (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ \
  | NWK_MODULE_ID_COMMAND_IND | NWK_MODULE_ID_DISCOVERY | NWK_MODULE_ID_FORMATION)

#define NWK_EVENT_AWAITING_RESET      (NWK_MODULE_ID_RESERVED)
#define NWK_EVENT_REJOIN_SUCCESS      (NWK_EVENT_FORMATION_SUCCESS)
#define NWK_EVENT_POWER_FAILURE_RESET (NWK_EVENT_FORMATION_SUCCESS)
#define NWK_EVENT_JOIN_SUCCESS        (NWK_EVENT_FORMATION_SUCCESS)
#define NWK_EVENT_LEAVE_FAIL          (NWK_EVENT_FORMATION_SUCCESS)

#define NWK_EVENT_EDSCAN NWK_MODULE_NONE /* Disable all NWK modules */

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Type of identifier of module. */
typedef uint8_t NwkStateMachineModuleID_t;

/** Type of NWK event. */
typedef NwkState_t NwkStateMachineEvent_t;
typedef enum
{
  NWK_IN_STATUS = 0,
  NWK_OUT_STATUS,
}NwkInOutState_t;

/******************************************************************************
                            Inline functions section
 *****************************************************************************/
/**************************************************************************//**
  \brief this function return true, if module with moduleID is allowed to work.
 ******************************************************************************/
INLINE bool nwkCheckStateMachine(NwkStateMachineModuleID_t moduleID)
{
  return (nwkMem.state & moduleID);
}

/**************************************************************************//**
  \brief Modules that can switch state machine shall send events.

  \param[in] event - id of event.
  \return None.
 ******************************************************************************/
INLINE void nwkSwitchStateMachine(NwkStateMachineEvent_t event)
{
  nwkMem.state = event;
}

/**************************************************************************//**
  \brief This function return the current state of network layer.

  \return Current global state of NWK-layer.
 ******************************************************************************/
INLINE NwkState_t nwkGetStateMachine(void)
{
  return nwkMem.state;
}

/**************************************************************************//**
 \brief Set new the network layer state.

 \param[in] state - new state.
 \return current state
 ******************************************************************************/
INLINE void nwkRestoreStateMachine(NwkState_t state)
{
  nwkMem.state = state;
}

/**************************************************************************//**
 \brief State machine reset routine.
 ******************************************************************************/
NWK_PRIVATE void nwkResetStateMachine(void);

/**************************************************************************//**
\brief Subscribe to stack events and reset nwkState 
******************************************************************************/
NWK_PRIVATE void nwkResetNwkStatus(void);

/**************************************************************************//**
\brief gets current Nwk State
\return NWK_OUT_STATUS if not in network
        NWK_IN_STATUS if in network  

******************************************************************************/
NWK_PRIVATE NwkInOutState_t nwkGetNwkState(void);

#endif /* _NWK_STATE_MACHINE_H */
/** eof nwkStateMachine.h */

