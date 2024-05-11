/*******************************************************************************
  APS Remove Device Header File

  Company
    Microchip Technology Inc.

  File Name
    apsRemoveDevice.h

  Summary
    Private interface of APS Remove Device.

  Description
    This header file defines the interface to the remove device indication function of APS.
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

#ifndef _APS_REMOVE_DEVICE_H
#define _APS_REMOVE_DEVICE_H

#ifdef _SECURITY_
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/apsCommand.h>
#include <nwk.h>
#include <private/apsFrames.h>
#include <apsmeRemoveDevice.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
BEGIN_PACK
/** Type of APS remove device command frame. */
typedef struct PACK _ApsRemoveDeviceFrame_t
{
  /** An APS header, which comprises frame control and addressing information. */
  ApduCommandHeader_t header;
  /** the 64-bit extended address of the device that is requested to be removed
   *  from the network. */
  ExtAddr_t targetAddress;
} ApsRemoveDeviceFrame_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Remove device indication handler.

  \param[in] commandInd - pointer to received command descriptor.

  \return 'true' if NWK buffer with the command frame must be freed
          otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsRemoveDeviceInd(const ApsCommandInd_t *const commandInd);

#endif /* _SECURITY_ */
#endif /* _APS_REMOVE_DEVICE_H */
/** eof apsRemoveDevice.h */
