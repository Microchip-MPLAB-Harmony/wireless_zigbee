/*******************************************************************************
  APS Relay Command Request Header File

  Company
    Microchip Technology Inc.

  File Name
    apsRelayCommandReq.h

  Summary
    APS Relay Command Request header file.

  Description
    This header file handles the APS Relay Command functionalities.
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

#ifndef _APS_RELAY_COMMAND_REQ_H_
#define _APS_RELAY_COMMAND_REQ_H_

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                   Includes section
******************************************************************************/
#include <aps/include/aps.h>
#include <aps/include/private/apsMemoryManager.h>

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                Prototypes section
 ******************************************************************************/

/**************************************************************************//**
  \brief Request to process APS relay command request and send it.

  \param[in] pApsDataBuffer    - Pointer to the APS request data buffer to send
                                 as a payload in APS relay command request.

  \return None.
 ******************************************************************************/

void apsRelayCommandRequest(ApsDataBuffer_t *pApsDataBuffer);

/**************************************************************************//**
  \brief Request to process APS relay aps command request and send it.

  \param[in] commandReq - pointer to request's parameters for
                          APS command allocator.

  \return None.
 ******************************************************************************/
void apsPrepareRelayCommandReq(ApsCommandReq_t *const commandReq);

/**************************************************************************/ /**
  \brief Get the aps and nwk security enable status

  \param[in] destExtAddr        - Destination address.
  \param[in] unAuthDevExtAdd    - Address of device to eb authorized
  \param[in] isRelayCmd         - Relay command flag
  \param[out] pApsSecurity      - Pointer to aps security
  \param[out] pNwkSecurity      - Pointer to nwk security

  \return None.
******************************************************************************/
void APS_GetSecurityEnableStatusForReq(ExtAddr_t destExtAddr, ExtAddr_t unAuthDevExtAdd, uint8_t isRelayCmd,
                                       uint8_t *pApsSecurity, uint8_t *pNwkSecurity);
#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /* _APS_RELAY_COMMAND_REQ_H_ */