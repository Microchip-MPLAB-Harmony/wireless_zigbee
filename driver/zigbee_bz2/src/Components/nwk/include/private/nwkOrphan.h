/*******************************************************************************
  NWK Orphan Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkOrphan.h

  Summary:
    This file provides the Interface to the NWK orphan join functionality.

  Description:
    This file provides the Interface to the NWK orphan join functionality.
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

#if !defined _NWK_ORPHAN_H
#define _NWK_ORPHAN_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nlmeJoin.h>
#include <macOrphan.h>
#include <macScan.h>
#include <macSetGet.h>
#include <macRxEnable.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
typedef enum
{
  NWK_ORPHAN_STATE_MIN = 0x65,
  NWK_ORPHAN_STATE_IDLE,

  /* child */
  NWK_ORPHAN_STATE_REQUEST_QUEUED,
  NWK_ORPHAN_STATE_SET_EXT_ADDR,
  NWK_ORPHAN_STATE_WAIT_SCAN_CONFIRM,
  NWK_ORPHAN_STATE_SET_PARAMS,
  NWK_ORPHAN_STATE_GET_PARAMS,

  /* parent */
  NWK_ORPHAN_STATE_WAIT_RESPONSE_CONFIRM,

  NWK_ORPHAN_STATE_MAX
} NwkOrphanState_t ;

/** Orphan memory */
typedef struct _NwkOrphan_t
{
  NwkOrphanState_t state;

#if defined _ROUTER_ || defined _ENDDEVICE_
  /** Request queue */
  QueueDescriptor_t queue;
  /** joinReq currently in processing */
  NWK_JoinReq_t *current;
  /** Memory for mac requests */
#endif
  union
  {
#if defined _ROUTER_ || defined _COORDINATOR_
    MAC_OrphanResp_t resp;
#endif
#if defined _ROUTER_ || defined _ENDDEVICE_
    MAC_ScanReq_t scan;
    MAC_GetReq_t get;
    MAC_SetReq_t set;
    MAC_RxEnableReq_t rxEnable;
#endif
  } req ;
} NwkOrphan_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
#if (defined(_ROUTER_) || defined(_ENDDEVICE_)) && defined(_NWK_ORPHAN_JOIN_)
/**************************************************************************//**
  \brief Reseting of the orphan module.
 ******************************************************************************/
NWK_PRIVATE void nwkResetOrphan(void);

/**************************************************************************//**
  \brief Main task handler of orphan module.
 ******************************************************************************/
NWK_PRIVATE void nwkOrphanTaskHandler(void);

/**************************************************************************//**
  \brief Process orphan join requests.

  \param[in] req - NLME-JOIN request parameters' structure pointer.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkOrphanReq(NWK_JoinReq_t *req);

#else

#define nwkResetOrphan() (void)0
#define nwkOrphanTaskHandler NULL

#endif /* (_ROUTER_ or _ENDDEVICE_) and _NWK_ORPHAN_JOIN_ */
#endif /* _NWK_ORPHAN_H */
/** eof nwkOrphan.h */

