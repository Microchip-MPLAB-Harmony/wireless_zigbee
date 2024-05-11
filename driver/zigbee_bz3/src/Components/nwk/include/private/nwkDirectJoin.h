/*******************************************************************************
  NWK DirectJoin Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkDirectJoin.h

  Summary:
    This file comprises the NWK layer Interface of direct join mechanism in a Zigbee Network.

  Description:
    This file comprises the NWK layer Interface of direct join mechanism in a Zigbee Network.
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

#if !defined _NWK_DIRECT_JOIN_H
#define _NWKDIRECTJOIN_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Direct join memory */
typedef struct _NwkDirectJoin_t
{
  /** Request queue */
  QueueDescriptor_t queue;
} NwkDirectJoin_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if (defined(_ROUTER_) || defined(_COORDINATOR_)) && defined(_NWK_DIRECT_JOIN_)
/**************************************************************************//**
  \brief Reseting of the direct join module.
 ******************************************************************************/
NWK_PRIVATE void nwkResetDirectJoin(void);

/**************************************************************************//**
  \brief task handler of diret join module
 ******************************************************************************/
NWK_PRIVATE void nwkDirectJoinTaskHandler(void);
#else

#define nwkResetDirectJoin() (void)0
#define nwkDirectJoinTaskHandler NULL

#endif /* _NWK_DIRECT_JOIN_ and (_ROUTER_ or _COORDINATOR_) */
#endif /* _NWK_DIRECT_JOIN_H */
/** eof nwkDirectJoin.h */

