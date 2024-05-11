/*******************************************************************************
  NWK Synchronisation Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkSync.h

  Summary:
    This file provides access to the NWK Synchronisation defines.

  Description:
    This file provides access to the NWK Synchronisation defines.
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

#if !defined _NWK_SYNC_H
#define _NWK_SYNC_H

/*****************************************************************************
                               Includes section
 *****************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <mac.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
/** Maximum synchronization attempts. */
#define MAX_SYNC_FAIL_COUNTER 8U

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Internal states of NLME-SYNC component */
typedef enum _NwkSyncState_t
{
  NWK_SYNC_IDLE_STATE = 0x31,
  NWK_SYNC_FIRST_STATE = 0xA3,
  NWK_SYNC_BEGIN_STATE = NWK_SYNC_FIRST_STATE,
  NWK_SYNC_MAC_POLL_STATE = 0xA4,
  NWK_SYNC_CONFIRM_STATE = 0xA5,
  NWK_SYNC_LAST_STATE
} NwkSyncState_t;

/** Internal parameters of NLME-SYNC component. */
typedef struct _NwkSync_t
{
  /** Internal component's state*/
  NwkSyncState_t state;
  /** Counter of synchronization attempts */
  uint8_t counter;
  /** Queue of NLME-SYNC.request from an upper layer */
  QueueDescriptor_t queue;
  /** MLME-POLL request primitive's parameters */
  MAC_PollReq_t macReq; /**< macReq must be no in union */
} NwkSync_t;

/*****************************************************************************
                            Prototypes section
 *****************************************************************************/
#if defined _ENDDEVICE_
/*************************************************************************//**
  \brief Main task handler of NLME-SYNC component
 *****************************************************************************/
NWK_PRIVATE void nwkSyncTaskHandler(void);

/*************************************************************************//**
  \brief Reset NLME-SYNC component.
 *****************************************************************************/
NWK_PRIVATE void nwkResetSync(void);

/******************************************************************************
  \brief nwkSync idle checking.

  \return true, if nwkSync performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkSyncIsIdle(void);

#else /* _ENDDEVICE_ */

#define nwkSyncTaskHandler NULL
#define nwkSyncIsIdle NULL
#define nwkResetSync() (void)0

#endif /* _ENDDEVICE_ */
#endif /* _NWK_SYNC_H */
/** eof nwkSync.h */

