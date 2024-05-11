/*******************************************************************************
  NWK Synchronisation Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkSyncLoss.h

  Summary:
    This file defines the interface to NWK synchronisation loss handling.

  Description:
    This file defines the interface to NWK synchronisation loss handling.
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

#if !defined _NWKSYNCLOSS_H
#define _NWKSYNCLOSS_H

/******************************************************************************
                                 Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nlmeStartRouter.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
/** Internal states of SyncLoss component */
typedef enum _NwkSyncLossState_t
{
  NWK_SYNC_LOSS_IDLE_STATE = 0x00,
  NWK_REALIGNMENT_START_STATE = 0x01
} NwkSyncLossState_t;

/** Internal parameters of SyncLoss */
typedef struct _NwkSyncLoss_t
{
  NwkSyncLossState_t state;
  NWK_StartRouterReq_t startRouter;
} NwkSyncLoss_t;

/******************************************************************************
                                Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) && defined(NWK_COORD_REALIGNMENT)
/******************************************************************************
  \brief Reset SyncLoss component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetSyncLoss(void);

#else /* _ROUTER_ && NWK_COORD_REALIGNMENT */

#define nwkResetSyncLoss() (void)0

#endif /* _ROUTER_ && NWK_COORD_REALIGNMENT */
#endif /* _NWKSYNCLOSS_H */
/** eof nwkSyncLoss.h */

