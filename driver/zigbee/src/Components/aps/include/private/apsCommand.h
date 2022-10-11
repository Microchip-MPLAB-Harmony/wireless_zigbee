/*******************************************************************************
  APS Command Header File

  Company
    Microchip Technology Inc.

  File Name
    apsCommand.h

  Summary
    Internal interface of APS command transmission.

  Description
    This header file defines the internal interface to the APS command transmission.
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

#if !defined _APS_COMMAND_H
#define _APS_COMMAND_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwk.h>
#include <apsCommon.h>
#include <private/apsFrames.h>
#include <apsAIB.h>

/******************************************************************************
                               Definitions section
 ******************************************************************************/
/** Returns pointer to command payload */
#define APS_GET_COMMAND_PAYLOAD(req) \
  ((req)->service.allocateReq.confirm.nwkDataReq->nsdu)
/** Returns pointer to NWK_DataReq, associated with command */
#define APS_GET_ALLOCATED_COMMAND_BUFFER(req) \
  ((req)->service.allocateReq.confirm.nwkDataReq)
/** Returns command payload length */
#define APS_GET_COMMAND_PAYLOAD_LENGTH(req) \
  ((req)->service.allocateReq.nsduLength)

#ifdef _LINK_SECURITY_
/** APS command auxiliary header length */
#define APS_COMMAND_AUXILIARY_HEADER_LENGTH \
  (SSP_SECURITY_CONTROL_FIELD_LENGTH + SSP_FRAME_COUNTER_FIELD_LENGTH)
/** APS command security fields size */
#define APS_COMMAND_SECURITY_FIELDS_SIZE \
  (APS_COMMAND_AUXILIARY_HEADER_LENGTH + APS_MAX_DATA_FRAME_FOOTER_LENGTH)
#endif /* _LINK_SECURITY_ */


/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Indicated command descriptor */
typedef struct _ApsCommandInd_t
{
  /** Pointer to first octet of unaligned source extended address. */
  const ExtAddr_t *srcExtAddr;
  /** Pointer to NLDE-DATA.indication parameters of the received command. */
  NWK_DataInd_t *nwkDataInd;
#ifdef _SECURITY_
  /* Type of key and link key handle (if used) with which the received command
     was secured. */
  ApsSecurityStatusDescriptor_t securityStatusDescriptor;
#endif /* _SECURITY_ */
} ApsCommandInd_t;

/* Command identifier values are shown in Table 4.34 of ZigBee spec r19. */
typedef enum _ApsCommandId_t
{
  APS_CMD_MIN_ID              = 1,
#if defined(_LINK_SECURITY_) && defined (_R20_LEGACY_)
  APS_CMD_SKKE_1_ID           = APS_CMD_MIN_ID,
  APS_CMD_SKKE_2_ID           = 2,
  APS_CMD_SKKE_3_ID           = 3,
  APS_CMD_SKKE_4_ID           = 4,
#endif
  APS_CMD_TRANSPORT_KEY_ID    = 5,
  APS_CMD_UPDATE_DEVICE_ID    = 6,
  APS_CMD_REMOVE_DEVICE_ID    = 7,
  APS_CMD_REQUEST_KEY_ID      = 8,
  APS_CMD_SWITCH_KEY_ID       = 9,
  APS_CMD_EA_INIT_CHLNG_ID    = 10,
  APS_CMD_EA_RSP_CHLNG_ID     = 11,
  APS_CMD_EA_INIT_MAC_DATA_ID = 12,
  APS_CMD_EA_RSP_MAC_DATA_ID  = 13,
  APS_CMD_TUNNEL_ID           = 14,
  APS_CMD_VERIFY_KEY_ID       = 15,
  APS_CMD_CONFIRM_KEY_ID      = 16,
  APS_CMD_MAX_ID              = APS_CMD_CONFIRM_KEY_ID,
} ApsCommandId_t;

BEGIN_PACK
typedef struct PACK _ApduCommandBaseHeader_t
{
  ApduFrameControlField_t frameControl;
  uint8_t apsCounter;
} ApduCommandBaseHeader_t;

typedef struct PACK _ApduCommandHeader_t
{
  ApduFrameControlField_t frameControl;
  uint8_t apsCounter;
  uint8_t commandId;
} ApduCommandHeader_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _SECURITY_
/**************************************************************************//**
  \brief Initialization of ApsCommandReq_t structure by default values.

   Following fields will be initialized:
    \li nwkSecurity and apsSecurity to true
    \li keyIdentifier to SSP_DATA_KEY_ID
    \li extendedNonce to false
    \li other fields to zero.

  \param[in] commandReq - pointer to request's parameters to APS command trasmission.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsSetCommandReqToDefault(ApsCommandReq_t *const commandReq);

/**************************************************************************//**
  \brief Module reset routine.

  \return None.
 ******************************************************************************/
APS_PRIVATE void apsCommandReset(void);

/**************************************************************************//**
  \brief Prepare command frame header.

  \param[out] header - pointer to memory to place header in.
  \param[in] commandId - command identifier.

  \return None.
 ******************************************************************************/
APS_PRIVATE
void apsCommandMakeHeader(ApduCommandHeader_t *header, ApsCommandId_t commandId);

/**************************************************************************//**
  \brief APS Command task handler.
 ******************************************************************************/
APS_PRIVATE void apsCommandReqTaskHandler(void);

/**************************************************************************//**
  \brief Request to allocate memory for APS command and send it.

  \param[in] commandReq - pointer to request's parameters to APS command trasmission.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsCommandReq(ApsCommandReq_t *const commandReq);

/**************************************************************************//**
  \brief Process an incoming command frame.

  \param[in] ind - pointer to NWK data indication structure.
  \param[in] securityStatus - security status descriptor structure.

  \return True, if memory buffer can be released; false - otherwise.
 ******************************************************************************/
APS_PRIVATE bool apsCommandInd(NWK_DataInd_t *ind, ApsSecurityStatusDescriptor_t securityStatus);

/**************************************************************************//**
  \brief Handler of decrypted or unsecured incoming commands.

  \param[in] ind - pointer to data indication structure.
  \param[in] securityStatusDescriptor - type of key and link key handle (if used)
             with the transport key command was secured.

  \return True, if memory buffer can be released; false - otherwise.
 ******************************************************************************/
APS_PRIVATE bool apsUnsecuredNwkDataIndHandler(NWK_DataInd_t *const ind,
  const ExtAddr_t *srcExtAddr, const ApsSecurityStatusDescriptor_t securityStatusDescriptor);

/**************************************************************************//**
  \brief Prepared command transmission routine.

  \param[in] req - command request pointer.

  \return None.
 ******************************************************************************/
APS_PRIVATE void apsCommandNwkDataReq(ApsCommandReq_t *const req);

#if defined _LINK_SECURITY_
/**************************************************************************//**
  \brief Consult with the security policy and check the incoming command.

  \param[in] srcExtAddr - pointer to an extended address of a device from which
                          the APS command was received. Extended address may
                          be unaligned.
  \param[in] spid - the security policy identifier of the incoming APS command.
  \param[in] securityStatusDescriptor - type of key and link key handle (if used)
             with the APS incoming command was secured.

  \return true, if the command is allowed for processing otherwise false.
 ******************************************************************************/
bool apsIsAllowedCommand(const void *const srcExtAddr,
  const APS_SecurityPolicyId_t spid,
  const ApsSecurityStatusDescriptor_t securityStatusDescriptor);
#endif /* _LINK_SECURITY_ */
#else
#define apsCommandReqTaskHandler NULL
#endif /* _SECURITY_ */
#endif /* _APS_COMMAND_H */
/** eof apsCommand.h */
