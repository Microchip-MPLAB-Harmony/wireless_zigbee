/*******************************************************************************
  APS Relay Command Header File

  Company
    Microchip Technology Inc.

  File Name
    apsRelayCommand.h

  Summary
    APS Relay Command header file.

  Description
    This header file handles the APS Relay command functionalities.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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
#ifndef _APS_RELAY_COMMAND_H_
#define _APS_RELAY_COMMAND_H_

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                   Includes section
******************************************************************************/
#include <aps.h>
#include <apsRelayCommand.h>
#include <apsCommandReq.h>
#include <private/apsCommand.h>

/******************************************************************************
                   Types section
******************************************************************************/

/** APS relay command request payload */
typedef struct _apsRelayCommandPayload_t
{
  /** Tag Id  */
  uint8_t tagId;
  /** Length  */
  uint8_t length;
  /** Device Address  */
  APS_Address_t address;
} ApsRelayCommandPayload_t;

BEGIN_PACK

/** This is the frame of APS relay command request */
typedef struct PACK _apsRelayCommandFrame_t
{
  /** An APS header, which comprises frame control and addressing information and APS command Id. */
  ApduCommandHeader_t header;
  /** Tag Id  */
  uint8_t tagId;
  /** Length  */
  uint8_t length;
  /** Device Address  */
  APS_Address_t address;
} ApsRelayCommandFrame_t;
END_PACK

/******************************************************************************
                Prototypes section
 ******************************************************************************/

/**************************************************************************//**
  \brief Process and validate an incoming APS Relay Downstream Command frame.
         This function decides whether to relayed the frame to the child or to send it to upper layer for further processing.
  
  \param[in] commandInd - Pointer to received command descriptor.

  \return True, if memory buffer can be released; false - otherwise.
 ******************************************************************************/
bool apsRelayDownStreamCommandInd(const ApsCommandInd_t *const commandInd);

/**************************************************************************//**
  \brief Process and validate an incoming APS Relay Up stream Command frame.
         This function decides whether to relayed the frame to the coordinator or to send it to upper layer for further processing.
  
  \param[in] commandInd - Pointer to received command descriptor.

  \return True, if memory buffer can be released; false - otherwise.
 ******************************************************************************/
bool apsRelayUpStreamCommandInd(const ApsCommandInd_t *const commandInd);

/**************************************************************************//**
  \brief Forward the APS Relay Command.

  \param[in] commandInd - Pointer to received command descriptor.
  \param[in] dstExtAddr - Pointer to raw extended address from received frame.

  \return 'true' if NWK_DataInd_t structure is not used otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsForwardRelayCommand(const ApsCommandInd_t *const commandInd);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /* _APS_RELAY_COMMAND_H_ */
