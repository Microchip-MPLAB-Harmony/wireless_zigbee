/*******************************************************************************
  APS TransportKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsTransportKey.h

  Summary
    Private interface of transport key implementation.

  Description
    This header file defines the interface to the APS transport key implementation.
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

#if !defined _APS_TRANSPORT_KEY_H
#define _APS_TRANSPORT_KEY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/apsCommand.h>
#include <apsmeTransportKey.h>

#if defined _SECURITY_
/******************************************************************************
                               Definitions section
 ******************************************************************************/
/* The macro checks the source is trusted - himself or Trust Center. */
#define IS_SOURCE_TRUSTED(commandInd) ((commandInd)->nwkDataInd->boomerang \
  || (APS_SECURED_HASH_OF_TRUST_CENTER_LINK_KEY_STATUS == \
     (commandInd)->securityStatusDescriptor.status) \
  || (APS_SECURED_TRUST_CENTER_LINK_KEY_STATUS == \
     (commandInd)->securityStatusDescriptor.status))

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Type of function for preparing and sending a transport key command. */
typedef void (* ApsTransportKeyCommand_t)(APS_TransportKeyReq_t *const req);
BEGIN_PACK
/* Type of common part of APS Transport Key command. */
typedef struct PACK _ApsTransportKeyCommonFrame_t
{
  /** An APS header, which comprises frame control and addressing information. */
  ApduCommandHeader_t header;
  /** This field describes the type of key being transported. The different
   * types of keys are enumerated in Table 4.12 of ZigBee spec r19. */
  uint8_t keyType;
} ApsTransportKeyCommonFrame_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of APS Transport Key component.
 ******************************************************************************/
APS_PRIVATE void apsTransportKeyTaskHandler(void);

#if defined _TRUST_CENTRE_
/**************************************************************************//**
  \brief Process confirmation of APS transport key command transmission.

  \param[in] commandReq - pointer to APS command request.
  \param[in] status - command transmission status.

  \return None.
 ******************************************************************************/
APS_PRIVATE void apsConfirmTransportKeyCommand(ApsCommandReq_t *const commandReq,
  const APS_Status_t status);

/**************************************************************************//**
  \brief Initialization of common fields of APS Transport key command frame.

  \param[in] commonFields - common sub-frame of transport key frame.
  \param[in] keyType - type of key in the transport key command frame.

  \return None.
 ******************************************************************************/
APS_PRIVATE void
apsInitCommonTransportKeyFields(ApsTransportKeyCommonFrame_t *const commonFields,
  const APS_TransportKeyType_t keyType);
#endif /* _TRUST_CENTRE_ */

/**************************************************************************//**
  \brief Process an incoming transport key command frame.

  \param[in] commandInd - pointer to received command descriptor.
  \return 'true' if NWK_DataInd_t structure is not used otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsTransportKeyInd(const ApsCommandInd_t *const commandInd);

/**************************************************************************//**
  \brief Forward a transport key command to unauthenticated child.

  \param[in] commandInd - pointer to received command descriptor.
  \param[in] dstExtAddr - pointer to raw extended address from received frame.
  \param[in] apsSendKeyToChildConf - NLDE-DATA confirm callback function's pointer.

  \return 'true' if NWK_DataInd_t structure is not used otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsForwardKeyToChild(const ApsCommandInd_t *const commandInd,
  const uint8_t *const dstExtAddr,
  void (* apsSendKeyToChildConf)(NWK_DataConf_t *conf));

/**************************************************************************//**
  \brief Reset the internal queue and variables of Transport Key component.
 ******************************************************************************/
APS_PRIVATE void apsTransportKeyReset(void);

#else
#define apsTransportKeyTaskHandler NULL
#define apsTransportKeyReset() (void)0
#endif /* _SECURITY_ */
#endif /* _APS_TRANSPORT_KEY_H */
/** eof apsTransportKey.h */
