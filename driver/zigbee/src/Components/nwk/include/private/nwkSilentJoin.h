/*******************************************************************************
  NWK Silent Join Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkSilentJoin.h

  Summary:
    This file contains the Interface of silent join functionality.

  Description:
    This file contains the Interface of silent join functionality.
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

#if !defined _NWK_SILENT_JOIN_H
#define _NWK_SILENT_JOIN_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nlmeJoin.h>
#include <macSetGet.h>
#include <macRxEnable.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
typedef enum
{
  NWK_SILENT_JOIN_STATE_MIN = 0x15,
  NWK_SILENT_JOIN_STATE_IDLE,
  NWK_SILENT_JOIN_STATE_REQUEST_QUEUED,
  NWK_SILENT_JOIN_STATE_SET_PARAMS,
  NWK_SILENT_JOIN_STATE_MAX
} NwkSilentJoinState_t;

/** Silent join memory */
typedef struct _NwkSilentJoin_t
{
  NwkSilentJoinState_t state;

#if defined _ROUTER_ || defined _ENDDEVICE_
  /** Request queue */
  QueueDescriptor_t queue;
#endif

#if defined _ROUTER_ || defined _ENDDEVICE_
  /** Memory for mac requests */
  union
  {
    MAC_SetReq_t set;
    MAC_RxEnableReq_t rxEnable;
  } req;
#endif
} NwkSilentJoin_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
#if (defined(_ROUTER_) || defined(_ENDDEVICE_)) && defined(_COMMISSIONING_)
/**************************************************************************//**
  \brief Silent join module reset.
 ******************************************************************************/
NWK_PRIVATE void nwkResetSilentJoin(void);

/**************************************************************************//**
  \brief Main task handler of the silent join module.
 ******************************************************************************/
NWK_PRIVATE void nwkSilentJoinTaskHandler(void);

/**************************************************************************//**
  \brief Process silent join requests.

  \param[in] req - NLME-JOIN request parameters' structure pointer.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkSilentJoinReq(NWK_JoinReq_t *req);

#else

#define nwkResetSilentJoin() (void)0
#define nwkSilentJoinTaskHandler NULL

#endif /* (_ROUTER_ or _ENDDEVICE_) and _COMMISSIONING_ */
#endif /* _NWK_SILENT_JOIN_H */

/** eof nwkSilentJoin.h */

