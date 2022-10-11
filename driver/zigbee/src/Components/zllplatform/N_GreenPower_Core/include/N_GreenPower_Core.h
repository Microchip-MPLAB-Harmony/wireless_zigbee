/** \file

$Id: N_GreenPower_Core.h 8165 2013-09-02 08:34:07Z gertjan.maas@philips.com $

Copyright (c) 2011 Koninklijke Philips N.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Koninklijke Philips N.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Koninklijke Philips N.V.
*/

#ifndef N_GREENPOWER_CORE_H
#define N_GREENPOWER_CORE_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Address/include/N_Address.h"
#include "ZLL/N_Security/include/N_Security.h"
#include "infrastructure/N_Types/include/N_Types.h"
#include "ZLL/N_Zcl_Framework/include/N_Zcl_Framework.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/

#define N_GREENPOWER_CORE_ZGP_PROFILE_ID                0xA1E0u
#define N_GREENPOWER_CORE_ZGP_ENDPOINT                  242u

#define N_GREENPOWER_CORE_ZGP_NONCE_LEN                 13u

// List of ZigBee GreenPower command IDs
#define N_GREENPOWER_COMMISSIONING_COMMANDID            0xE0u
#define N_GREENPOWER_DECOMMISSIONING_COMMANDID          0xE1u

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/

typedef uint8_t N_GreenPower_Core_Nonce_t[N_GREENPOWER_CORE_ZGP_NONCE_LEN];

/** Completion callback for N_GreenPower_Core_AuthenticateMessage.
    \param success TRUE if the authentication is succesfull, otherwise FALSE.
*/
typedef void (*N_GreenPower_Core_AuthenticateDoneCallback_t)(bool success);

/** Completion callback for N_GreenPower_Core_DecryptSecurityKey.
    \param success TRUE if the decryption and authentication is succesfull, otherwise FALSE.
    \param securityKey the decrypted securityKey, NULL if success is FALSE.
*/
typedef void (*N_GreenPower_Core_DecryptKeyDoneCallback_t)(bool success, N_Security_Key_t securityKey);

typedef struct N_GreenPower_Core_Callback_t
{
    /** Callback to indicate that we have received a commissioning frame from a ZGP device.
        \param macSequenceNumber The sequence number from the mac layer.
        \param pSourceIeeeAddress Pointer to the sourceIeeeAddress of the ZGP message. Can be NULL if not available.
        \param dataLength The length of the data argument.
        \param data The data from the green power data frame (including network header).
    */
    void (*DataIndication)(uint8_t macSequenceNumber, N_Address_Extended_t* pSourceIeeeAddress, uint8_t dataLength, uint8_t* data);

    int8_t endOfList; // guard, must be initialized to -1
} N_GreenPower_Core_Callback_t;

typedef enum N_GreenPower_SendStatus_t
{
    N_GreenPower_Core_SendStatus_Ok = 0x00u,
    N_GreenPower_Core_SendStatus_Failure = 0x01u,
    N_GreenPower_Core_SendStatus_OutOfMemory = 0x89u,

} N_GreenPower_Core_SendStatus_t;

/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/
/**************************************************************************//**
  \brief Subscribes for N_GreenPower_Core callbacks.

  \param[in] pCallback The callback from subscriber

  \return none
 ******************************************************************************/

void N_GreenPower_Core_Subscribe(const N_GreenPower_Core_Callback_t* pCallback);

/**************************************************************************//**
  \brief Send a ZCL command as if it came from a ZigBee GreenPower Device.

  \param[in] aliasSourceAddress The aliased source address.
  \param[in] aliasSequenceNumber The network sequence number to fake (use securityFrameCounter from the callback).
  \param[in] pRequest Pointer to the ZCL command to send.
  \param[in] pdestinationAddress The address to send the command to. Only groupcast and broadcast are currently supported.
  \param[in] forwardingRadius number of hops the alias frame is allowed to travel through the network.

  \return Status of the sent message
 ******************************************************************************/
N_GreenPower_Core_SendStatus_t N_GreenPower_Core_SendAliased(uint16_t aliasSourceAddress, uint8_t aliasSequenceNumber, N_Zcl_Control_t* pRequest, N_Address_t* pdestinationAddress, uint8_t forwardingRadius);

/**************************************************************************//**
  \brief Authenticate the ZigBee GreenPower message

  \param[in] messageLength The length of the message in *message.
  \param[in] message The message.
  \param[in] micLength The length of the mic in *mic.
  \param[in] mic The mic.
  \param[in] key The security key to authenticate the mic with.
  \param[in] nonce The nonce to authenticate the mic with. See Green Power Spec A.1.5.4.3.1.
  \param[in] done The callback with the result to be called when the message is authenticated.

  \return None
 ******************************************************************************/
void N_GreenPower_Core_AuthenticateMessage(uint8_t messageLength, uint8_t* message, uint8_t micLength, uint8_t* mic, N_Security_Key_t key, N_GreenPower_Core_Nonce_t nonce, N_GreenPower_Core_AuthenticateDoneCallback_t done);

/**************************************************************************//**
  \brief Decrypt and authenticate the ZigBee GreenPower security key.

  \param[in] gpdSourceId The GPD source ID.
  \param[in] encryptedKey The encrypted security key that needs to be decrypted.
  \param[in] key The key to decrypt the encryptedKey.
  \param[in] nonce The nonce used for decrypting the security key. See Green Power Spec A.1.5.4.3.1.
  \param[in] mic The mic used for authenticating the decrypted security key.
  \param[in] done The callback with the result to be called when the key is decrypted and authenticated.

  \return None
 ******************************************************************************/
void N_GreenPower_Core_DecryptSecurityKey(uint32_t gpdSourceId, N_Security_Key_t encryptedKey, N_Security_Key_t key, N_GreenPower_Core_Nonce_t nonce, uint32_t mic, N_GreenPower_Core_DecryptKeyDoneCallback_t done);

/**************************************************************************//**
  \brief Send a device announce for a GreenPower device.

  \param[in] aliasSourceAddress The aliased source address.
  \param[in] securityCapable TRUE if the device is security capable, otherwise FALSE.

  \return Status of the sent message.
 ******************************************************************************/
N_GreenPower_Core_SendStatus_t N_GreenPower_Core_SendAliasedDeviceAnnounce(uint16_t aliasSourceAddress, bool securityCapable);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_GREENPOWER_CORE_H
