/*******************************************************************************
  NWK Start Router Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkStartRouter.h

  Summary:
    This file contains the paramters and defines for NWK start Procedure.

  Description:
    This file contains the paramters and defines for NWK start Procedure of a Router Device.
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

#if !defined _NWK_START_ROUTER_H
#define _NWK_START_ROUTER_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Internal states of NLME-START-ROUTER component */
typedef enum _NwkStartRouterState_t
{
  NWK_START_ROUTER_IDLE_STATE = 0x9A,
  NWK_START_ROUTER_FIRST_STATE = 0x45,
  NWK_START_ROUTER_BEGIN_STATE = NWK_START_ROUTER_FIRST_STATE,
  NWK_START_ROUTER_MAC_REQ_STATE = 0x46,
  NWK_START_ROUTER_CONFIRM_STATE = 0x47,
  NWK_START_ROUTER_LAST_STATE
} NwkStartRouterState_t;

/** Internal parameters of NLME-START-ROUTER */
typedef struct _NwkStartRouter_t
{
  QueueDescriptor_t queue; /**< Queue of requests from upper layer */
  NwkStartRouterState_t state; /**< Finite-state machine */
  bool coordRealignment;
} NwkStartRouter_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
#if defined _ROUTER_
/**************************************************************************//**
  \brief Main task handler of NLME-START-ROUTER component
 ******************************************************************************/
NWK_PRIVATE void nwkStartRouterTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-START-ROUTER component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetStartRouter(void);

/******************************************************************************
  \brief nwkStartRouter idle checking.

  \return true, if nwkStartRouter performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkStartRouterIsIdle(void);

#if defined NWK_COORD_REALIGNMENT
/**************************************************************************//**
  \brief Is network configuration realignment allowed or not?
 ******************************************************************************/
NWK_PRIVATE bool nwkRealignmentIsAllowed(void);
#endif /* NWK_COORD_REALIGNMENT */

#else /* _ROUTER_ */

#define nwkStartRouterTaskHandler NULL
#define nwkStartRouterIsIdle NULL
#define nwkResetStartRouter() (void)0

#endif /* _ROUTER_ */
#endif /* _NWKSTARTROUTER_H */
/** eof nwkStartRouter.h */

