/*******************************************************************************
  NWK EndDevice Timeout Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkEndDeviceTimeoutCommandReq.h

  Summary:
    This file contains the interface to the NWK EndDevice Timeout Handling.

  Description:
    This file contains the interface to the NWK EndDevice Timeout Handling.
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

#ifndef _NWK_END_DEVICE_TIMEOUT_COMMAND_REQ_H
#define _NWK_END_DEVICE_TIMEOUT_COMMAND_REQ_H

/******************************************************************************
                               Includes section
******************************************************************************/
#include <sysTypes.h>
#include <appTimer.h>
#include <nldeData.h>
#include <nwkCommon.h>
#include <private/nwkFrame.h>
#include <nwkAddressResolv.h>
#include <nwkEndDeviceTimeout.h>

/******************************************************************************
                              Definitions section
******************************************************************************/
/* Fields of the End Device Configuration */
#define NWK_ENDDEVICE_TIMEOUT_REQUEST_PERSISTENT_DATA 1U

/** Total size of end device timeout request - NWK header + payload */
#define TOTAL_ENDDEVICE_TIMEOUT_REQ_CMD_SIZE 27U

#define NWK_ENDDEVICE_TIMEOUT_REQ_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_COMMAND, nwkPrepareEndDeviceTimeoutReqTx, nwkConfirmEndDeviceTimeoutReqTx, true}

/******************************************************************************
                                 Types section
******************************************************************************/
/** Internal states for end device timeout request component. */
typedef enum
{
  NWK_ENDDEVICE_TIMEOUT_REQ_IDLE_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_FIRST_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_BEGIN_STATE = NWK_ENDDEVICE_TIMEOUT_REQ_FIRST_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_SEND_REQ_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_WAIT_CONFIRM_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_WAIT_RESPONSE_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_CONFIRM_STATE,
  NWK_ENDDEVICE_TIMEOUT_REQ_LAST_STATE
} NwkEndDeviceTimeoutReqState_t;

BEGIN_PACK
/** Payload of end device timeout request command. */
typedef struct PACK
{
  /** Id of end device timeout request command. ZigBee spec r17, Table 3.40
   * and Child Aging and Recovery Protocol r20, 7.2. */
  NwkCommandIdField_t commandId;
  /** The requested timeout enumeration.
   * This will be converted into actual timeout value based on
   * NwkEndDeviceTimeout_t type. */
  NwkEndDeviceTimeout_t requestedTimeoutEnumeration;
  LITTLE_ENDIAN_OCTET (2, (
    /** When this bit is set it indicates that the end device is requesting
     * that the parent store the end device data in non-volatile storage so
     * that it will survive a reboot.  If this bit is not set,
     * the parent shall not store the end device’s data in non-volatile storage and
     * the data shall be erased upon reboot.
     * In other words, the end device will be forgotten by the parent if this bit is not set. */
    NwkBitField_t endDeviceConfiguration : 1,
    NwkBitField_t reserved               : 7
  ))
} NwkEndDeviceTimeoutReqCmd_t;
END_PACK

/** Internal parameters of end device timeout request. */
typedef struct {
  /** Finite-state machine. */
  NwkEndDeviceTimeoutReqState_t state;
  /** Queue of requests from upper layer. */
  QueueDescriptor_t queue;
  /** Timer used to count down response waiting time. */
  HAL_AppTimer_t responseWaitTimer;
} NwkEndDeviceTimeoutReq_t;

/******************************************************************************
                             Prototypes section
******************************************************************************/
#ifdef _CHILD_MANAGEMENT_
#ifdef _ENDDEVICE_
/**************************************************************************//**
  \brief Reset the end device timeout request component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetEndDeviceTimeoutReq(void);

/**************************************************************************//**
  \brief Task handler of NWK end device timeout request component.
 ******************************************************************************/
NWK_PRIVATE void nwkEndDeviceTimeoutReqTaskHandler(void);

/**************************************************************************//**
  \brief Prepare header and payload of the end device timeout request command.

  \param[in] outPkt - pointer to output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareEndDeviceTimeoutReqTx(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Confirmation of end device timeout request command transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] status - network status of end device timeout request transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkConfirmEndDeviceTimeoutReqTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

/**************************************************************************//**
  \brief Action when command received.

  \param[in] payload - a payload of end device timeout response command.
  \param[in] header - pointer to raw NWK header.
  \param[in] parse - parsed header fields.

  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkEndDeviceTimeoutResponseFrameInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/******************************************************************************
 \brief nwkEndDeviceTimeoutReq idle checking.

 \return true, if nwkEndDeviceTimeoutReq performs no activity, false - otherwise.
******************************************************************************/
NWK_PRIVATE bool nwkEndDeviceTimeOutReqIsIdle(void);

#else /* _ENDDEVICE_ */
  #define nwkEndDeviceTimeoutReqTaskHandler NULL
  #define nwkEndDeviceTimeoutResponseFrameInd NULL
  #define nwkResetEndDeviceTimeoutReq() (void)NULL
  #define nwkPrepareEndDeviceTimeoutReqTx NULL
  #define nwkConfirmEndDeviceTimeoutReqTx NULL
  #define nwkEndDeviceTimeOutReqIsIdle    NULL
#endif /* _ENDDEVICE_ */
#else /* _CHILD_MANAGEMENT_ */
  #define nwkResetEndDeviceTimeoutReq() (void)NULL
  #define nwkEndDeviceTimeoutReqTaskHandler NULL
  #define nwkPrepareEndDeviceTimeoutReqTx NULL
  #define nwkConfirmEndDeviceTimeoutReqTx NULL
  #define nwkEndDeviceTimeOutReqIsIdle    NULL
#endif /* _CHILD_MANAGEMENT_ */
#endif /* _NWK_END_DEVICE_TIMEOUT_COMMAND_REQ_H */
/** eof nwkEndDeviceTimeoutCommandReq.h */
