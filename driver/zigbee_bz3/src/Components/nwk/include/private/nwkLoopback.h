/*******************************************************************************
  NWK Loop Back Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkLoopback.h

  Summary:
    This file contains the Interface of network loopback.

  Description:
    This file contains the Interface of network loopback.
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

#if !defined _NWK_LOOPBACK_H
#define _NWK_LOOPBACK_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nldeData.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Internal states of the loopback component. */
typedef enum _NwkLoopbackState_t
{
  NWK_LOOPBACK_UNKNOWN_STATE = 0x00,
  NWK_LOOPBACK_FIRST_STATE = 0x8e,
  NWK_LOOPBACK_IDLE_STATE = NWK_LOOPBACK_FIRST_STATE,
  NWK_LOOPBACK_REQUEST_PROCESSING_STATE = 0x8f,
  NWK_LOOPBACK_WAIT_PACKET_STATE = 0x90,
  NWK_LOOPBACK_SECOND_REQUEST_PROCESSING_STATE = 0x91,
  NWK_LOOPBACK_LAST_STATE
} NwkLoopbackState_t;

/** Internal parameters of the loopback component. */
typedef struct _NwkLoopback_t
{
  QueueDescriptor_t queue; /**< Queue of requests from upper layer */
  NwkLoopbackState_t state; /**< Finite-state machine */
} NwkLoopback_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/

/**************************************************************************//**
  \brief The main task handler of the network loopback component.
 ******************************************************************************/
NWK_PRIVATE void nwkLoopbackTaskHandler(void);

/**************************************************************************//**
  \brief Handler of free packet indication.
 ******************************************************************************/
NWK_PRIVATE void nwkLoopbackFreePacketInd(void);

/**************************************************************************//**
  \brief Reset the network loopback component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetLoopback(void);

/******************************************************************************
  \brief nwkLoopback idle checking.

  \return true, if nwkLoopback performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkLoopbackIsIdle(void);

/**************************************************************************//**
  \brief Checks, if outgoing packet should be indicated to the next upper layer.

  \param[in] req - pointer to NLDE-DATA.request parameter's structure.

  \return True, if indication required, false - otherwise
 ******************************************************************************/
NWK_PRIVATE bool nwkLoopbackRequired(const NWK_DataReq_t *const req);

#endif /* _NWK_LOOPBACK_H */
/** nwkLoopback.h */

