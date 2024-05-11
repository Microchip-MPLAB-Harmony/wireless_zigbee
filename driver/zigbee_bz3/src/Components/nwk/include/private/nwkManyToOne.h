/*******************************************************************************
  NWK Many To One Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkManyToOne.h

  Summary:
    This file provides the Internal interface of the many-to-one component.

  Description:
    This file provides the Internal interface of the many-to-one component.
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

#if !defined _NWK_MANY_TO_ONE_H
#define _NWK_MANY_TO_ONE_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkCommon.h>
#include <private/nwkRoutingTable.h>
#include <sysQueue.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined NWK_ROUTING_CAPACITY && defined _NWK_MANY_TO_ONE_ROUTING_
/**************************************************************************//**
  \brief Main task handler of the many-to-one component.
 ******************************************************************************/
NWK_PRIVATE void nwkManyToOneTaskHandler(void);

/**************************************************************************//**
  \brief Reset the many-to-one component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetManyToOne(void);

/**************************************************************************//**
  \brief Many-to-one route request from concentrator has been received.

  \param[in] entry - pointer to concentrator entry in the routing table.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkNewConcentratorFound(NwkRoutingTableEntry_t *const entry);

#else

#define nwkManyToOneTaskHandler NULL
#define nwkResetManyToOne() (void)0
#define nwkNewConcentratorFound(entry) (void)0

#endif /* NWK_ROUTING_CAPACITY and _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* _NWK_MANY_TO_ONE_H */
/** eof nwkManyToOne.h */

