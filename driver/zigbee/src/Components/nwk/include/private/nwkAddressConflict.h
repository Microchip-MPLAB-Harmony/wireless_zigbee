/*******************************************************************************
  NWK Address Conflict Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkAddressConflict.h

  Summary:
    This file includes the Interface of address conflict resolver.

  Description:
    This file includes the Interface of network address conflict resolver.
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

#if !defined _NWK_ADDRESS_CONFLICT_H
#define _NWK_ADDRESS_CONFLICT_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysTypes.h>
#include <sysQueue.h>
#include <mac.h>
#include <nwkCommon.h>
#include <nlmeJoin.h>
#include <private/nwkStatusReq.h>

/******************************************************************************
                               Types section
 ******************************************************************************/
/** Internal states of the address conflict component. */
typedef enum _NwkAddrConflictState_t
{
  NWK_ADDR_CONFLICT_IDLE_STATE = 0xAA,
  NWK_ADDR_CONFLICT_FIRST_STATE = 0x43,
  NWK_ADDR_CONFLICT_BEGIN_STATE = NWK_ADDR_CONFLICT_FIRST_STATE,
  NWK_ADDR_CONFLICT_MAC_SET_STATE = 0x44,
  NWK_ADDR_CONFLICT_REJOIN_STATE = 0x45,
  NWK_ADDR_CONFLICT_SEND_STATUS_STATE = 0x46,
  NWK_ADDR_CONFLICT_RESOLVING_STATE = 0x47,
  NWK_ADDR_CONFLICT_LAST_STATE
} NwkAddrConflictState_t;

/** Internal variables of the network manager component. */
typedef struct _NwkAddrConflict_t
{
  union
  {
    MAC_SetReq_t macSet;
    NWK_JoinReq_t rejoin;
    NwkStatusReq_t nwkStatus;
  } req;
  /** Current conflict address. */
  ShortAddr_t shortAddr;
  /** Finite-state machine */
  NwkAddrConflictState_t state;
  /** To track the same address conflict detection by other device*/
  bool alreadyAnnounced;
  bool sendNwkStatus;
} NwkAddrConflict_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
#if defined _RESOLVE_ADDR_CONFLICT_
/**************************************************************************//**
  \brief Reset address conflict component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetAddressConflict(void);

/**************************************************************************//**
  \brief Main task handler of address conflict component.
 ******************************************************************************/
NWK_PRIVATE void nwkAddressConflictTaskHandler(void);

/**************************************************************************//**
  \brief Resolve address conflict for given short address.

  \param[in] shortAddr - conflicted short address.
  \return None.
******************************************************************************/
NWK_PRIVATE void nwkResolveAddressConflict(const ShortAddr_t shortAddr,
  const bool sendNwkStatus);

/******************************************************************************
  \brief nwkAddressConflict idle checking.

  \return true, if nwkAddressConflict performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkAddressConflictIsIdle(void);

#else /* _RESOLVE_ADDR_CONFLICT_ */

#define nwkResetAddressConflict() (void)0
#define nwkAddressConflictTaskHandler NULL
#define nwkAddressConflictIsIdle NULL
#define nwkResolveAddressConflict(shortAddr, sendNwkStatus) ((void)0)

#endif /* _RESOLVE_ADDR_CONFLICT_ */
#endif /* _NWK_ADDRESS_CONFLICT_H */
/** eof nwkAddressConflict.h */

