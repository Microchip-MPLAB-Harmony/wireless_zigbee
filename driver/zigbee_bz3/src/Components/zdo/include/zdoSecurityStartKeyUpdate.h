// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee device object security key update method Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoSecurityStartKeyUpdate.h

  Summary:

  Description:

 *******************************************************************************/


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

#ifndef  _ZDO_SECURITY_START_KEY_UPDATE_H_
#define  _ZDO_SECURITY_START_KEY_UPDATE_H_

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                                Types section
 ******************************************************************************/

/* Selected Key Negotiation Protocol Enumeration. */
typedef enum
{
  SEL_KEY_STATIC = 0U,                   //!< Static key (Zigbee 3.0 Mechanism)
  SEL_KEY_SPEKE_CURVE25519_AES_MMO_128,  //!< SPEKE using Curve25519 with Hash AES-MMO-128
  SEL_KEY_SPEKE_CURVE25519_SHA_256,      //!< SPEKE using Curve25519 with Hash SHA-256
  SEL_KEY_RESERVED                       //!< Reserved
} SelectedKeyNegotiationProtocol_t;

/* Selected Pre-shared Secret Enumeration. */
typedef enum
{
  SEL_SECRET_SYMMETRIC_AUTH_TOKEN = 0U,               //!< Symmetric Authentication Token
  SEL_SECRET_INSTALL_CODE_PRE_CONFIG_LINK_KEY,        //!< Pre-configured link-key derived from installation code
  SEL_SECRET_VARIABLE_LENGTH_PASSCODE,                //!< Variable-length pass code (for PAKE protocols)
  SEL_SECRET_BASIC_AUTH_KEY,                          //!< Basic Authorization Key
  SEL_SECRET_ADMINISTRATIVE_AUTH_KEY,                 //!< Administrative Authorization Key
  SEL_SECRET_RESERVED,                                //!< Reserved
  SEL_SECRET_ANONYMOUS = 255U,                        //!< Anonymous Well-Known Secret
} SelectedPreSharedSecret_t;

typedef struct
{
  /* Start Key Update request data. */
  uint8_t reqData[APS_MAX_NON_SECURITY_ASDU_SIZE - ZDP_REQ_HEADER_SIZE];
  /* Length. */
  uint8_t dataLen;
  /* Flag for Relay Command. */
  uint8_t relayCmd;
  /* Destination Address Mode. */
  APS_AddrMode_t destAddressMode;
  /* Destination Address. */
  APS_Address_t destAddress;
  /* Unauthorized Device. */
  ExtAddr_t unAuthDevExtAdd;
  /* Response callback to notify the upper layer */
  void (*callback)(uint8_t status, ExtAddr_t deviceExtAddr);
} SecurityServiceStartKeyUpdate_t;

/*****************************************************************************************************************
                                Prototypes section
 ****************************************************************************************************************/
/**************************************************************************//**
\brief Sends the Security Service Start Key Update Request

\param[in] relay            - command relay true or false
\param[in] unAuthDevExtAdd  - Extended Address of Device to Authorise;
\param[in] addressMode      - Destination node address Mode;
\param[in] destAddr         - short address of destination node;
\param[in] keyNegoMethod    - Key negotiation protocol method;
\param[in] preSharedSecret  - Pre-shared secret;
\param[in] callback         - Callback function;
******************************************************************************/
void ZDO_StartKeyUpdateReq(bool relay, ExtAddr_t unAuthDevExtAdd, APS_AddrMode_t addressMode,
                           uint64_t destAddr, uint8_t keyNegoMethod, uint8_t preSharedSecret, void (*callback)(uint8_t status, ExtAddr_t deviceExtAddr));

/*************************************************************************************************************//**
  \brief Get selected key negotiation protocol enum for the bit mask value from KeyNegotiationTlv

  \param[in] keyNegotiationBitMask - Key negotiation protocol bit mask value.

  \return - the enum value of the input bit mask.
 ****************************************************************************************************************/
SelectedKeyNegotiationProtocol_t ZDO_GetSelectedKeyNegotiationProtocolEnum(KeyNegotiationProtocolBitmask_t keyNegotiationBitMask);

/*************************************************************************************************************//**
  \brief Get selected pre shared secret enum for the bit mask value from KeyNegotiationTlv

  \param[in] preSharedSecretBitMask - pre shared secret bit mask value.

  \return - the enum value of the input bit mask.
 ****************************************************************************************************************/
SelectedPreSharedSecret_t ZDO_GetSelectedPreSharedSecretEnum(PreSharedSecretBitmask_t preSharedSecretBitMask);

/**************************************************************************/ /**
   \brief Start Key Update request Wait Timer
   This timer should be stopped once Start Key Update request received

   \param[in] None.

   \return None.
 ******************************************************************************/
void ZDO_StartKeyUpdateReqWaitTimer(void);

/**************************************************************************/ /**
   \brief Stop Key Update request Wait Timer

   \param[in] None.

   \return None.
 ******************************************************************************/
void ZDO_StopKeyUpdateReqWaitTimer(void);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /*  _ZDO_SECURITY_START_KEY_UPDATE_H_  */
