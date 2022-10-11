/*******************************************************************************
  NWK Commands Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkCommands.h

  Summary:
    This file provides the Interface to the NWK layer Commands.

  Description:
    This file provides the Interface to the NWK layer Commands..
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

#if !defined _NWK_COMMANDS_H
#define _NWK_COMMANDS_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysTypes.h>
#include <private/nwkFrame.h>
#include <private/nwkTx.h>

/******************************************************************************
                               Definition section
 ******************************************************************************/
/* Total number of command requests. */
#define NWK_COMMAND_REQ_AMOUNT (NWK_MAX_COMMAND_TX_ID + 1U)

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Type of command request counter. */
typedef uint8_t NwkCommandCount_t;

/** Internal variables of the commands component. */
typedef struct _NwkCommands_t
{
  NwkCommandCount_t reqCount[NWK_COMMAND_REQ_AMOUNT];
} NwkCommands_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Request to perform outgoing command allocated in data buffer.

  \param[in] txId - the transmission identifier of a command
                    which is requested to send.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkCommandReq(const NwkTxId_t txId);

/**************************************************************************//**
  \brief Action when any command received.

  \param[in] payload - command payload (with ID)
  \param[in] header  - pointer to network frame header.
  \param[in] parse   - parsed header fields
  \return 'true' if continue command processing otherwise 'false'.
******************************************************************************/
NWK_PRIVATE bool nwkCommandInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief The packet for NWK command has been released.

  \return 'true' if free packet has been allocated otherwise return 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkCommandFreePacketInd(void);

/**************************************************************************//**
  \brief Reset the commands component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetCommands(void);

#endif /* _NWK_COMMANDS_H */
/** eof nwkCommands.h */

