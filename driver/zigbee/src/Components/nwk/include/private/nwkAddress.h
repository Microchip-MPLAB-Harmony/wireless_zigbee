/*******************************************************************************
  NWK Address Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkAddress.h

  Summary:
    This file contains the declarations and prototypes for NWK addessing parameters.

  Description:
    This file contains the declarations and prototypes for NWK addessing parameters.
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

#if !defined _NWK_ADDRESS_H
#define _NWK_ADDRESS_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysTypes.h>
#include <mac.h>
#include <nwkCommon.h>
#include <private/nwkSystem.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _COORDINATOR_ || defined _ROUTER_
/**************************************************************************//**
  \brief Allocate short address.

  \param[in] router - parameters is used if tree addressing is active.
  \param[in] addrRequested - if rejoin is used, it is address device selects for
     itself otherwise NWK_NO_SHORT_ADDR.
  \param[in] extAddr - IEEE extended address of node.
  \return Allocated address. addrRequested - is possible,
          or address allocated in little endian.
 ******************************************************************************/
NWK_PRIVATE ShortAddr_t nwkAllocateShortAddr(const bool router,
  const ShortAddr_t addrRequested, const ExtAddr_t extAddr);
#endif /* _COORDINATOR_ or _ROUTER_ */

#if defined _NWK_DISTRIBUTED_ADDRESSING_
/**************************************************************************//**
  \brief Computing the size of the address sub-block.

  \param[in] depth - current depth of node in network tree topology.
  \return cskip block in big endian format.
 ******************************************************************************/
NWK_PRIVATE NwkAddrRange_t nwkCSkip(const NwkDepth_t depth);
#endif /* _NWK_DISTRIBUTED_ADDRESSING_ */

/**************************************************************************//**
  \brief Allocate non-conflict short address

  \param[in] shortAddr - initial value of short address.
  \param[in] extAddr - pointer to IEEE extended address of node for which is
                       allocated a short address.
  \return Valid short address in little endian format.
 ******************************************************************************/
NWK_PRIVATE ShortAddr_t nwkAllocNonConflAddr(ShortAddr_t shortAddr,
  const ExtAddr_t *const extAddr);

/**************************************************************************//**
  \brief Is received broadcast packet for this device or not?

  \param[in] dstAddr - destination broadcast address.

  \return 'true' if broadcast packet can be handled by this device
          otherwise return 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkBroadcastForMe(const ShortAddr_t dstAddr);

#endif /* _NWK_ADDRESS_H */
/** eof nwkAddress.h */

