/*******************************************************************************
  APS Reject Duplicate Header File

  Company
    Microchip Technology Inc.

  File Name
    apsRejectDuplicate.h

  Summary
    Private interface of the duplicate rejection table.

  Description
    This header file defines the interface to the APS duplicate rejection table.
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

#if !defined _APS_REJECT_DUPLICATE_H
#define _APS_REJECT_DUPLICATE_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <apsCommon.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/*****************************************************************************
  \brief Is incoming packet is dublicate or not? Checks in the rejection table.

  \param[in] srcAddr - short address of source node.
  \param[in] counter - APS counter of incoming packet.

  \return true - if incoming packet is duplicate otherwise return false.
*****************************************************************************/
APS_PRIVATE bool apsIsDuplicatePacket(const ShortAddr_t srcAddr,
  const uint8_t counter);

/******************************************************************************
  \brief Reset the duplicate rejection table ana reinit timeouts.
 ******************************************************************************/
APS_PRIVATE void apsResetDuplicateRejectionTable(void);

#endif /* _APS_REJECT_DUPLICATE_H */
/** eof apsRejectDuplicate.h */

