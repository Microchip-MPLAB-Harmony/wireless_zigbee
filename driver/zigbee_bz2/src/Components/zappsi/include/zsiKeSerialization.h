/*******************************************************************************
  ZAppSI KE Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiKeSerialization.h

  Summary:
    This file contains the ZAppSI Certicom primitives serialization interface.

  Description:
    This file contains the ZAppSI Certicom primitives serialization interface.
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


#ifndef ZSIKESERIALIZATION_H
#define ZSIKESERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <aps.h>
#include <zsiFrames.h>
#include <zsiDriver.h>
#include <sspCommon.h>
#include <genericEcc.h>
#include <include/zgpCommon.h>
#include <sspHash.h>
/******************************************************************************
                    Defines section
******************************************************************************/
#define ZSI_KE_ADDITIONAL_MESSAGE_COMPONENT_SIZE sizeof(uint8_t)
#define ZSI_KE_MAC_DATA_SIZE ((2 * SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE) + \
                              (2 * sizeof(ExtAddr_t)) + \
                               ZSI_KE_ADDITIONAL_MESSAGE_COMPONENT_SIZE) // 61 bytes
/******************************************************************************
                    Types section
******************************************************************************/
#if CERTICOM_SUPPORT == 1
typedef struct _ZsiEccKeyBitGenerateAllocator_t
{
  uint8_t privateKey[SECT163K1_PRIVATE_KEY_SIZE];
  uint8_t localEphemeralPrivateKey[SECT163K1_PRIVATE_KEY_SIZE];
  uint8_t localEphemeralPublicKey[SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE];
  uint8_t remoteCertificate[SECT163K1_CERTIFICATE_SIZE];
  uint8_t remoteEphemeralPublicKey[SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE];
  uint8_t publicKey[SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE];
  uint8_t localKeyBits[SECT163K1_SHARED_SECRET_SIZE];
} ZsiEccKeyBitGenerate_t;

typedef struct _ZsiEccGenerateKey_t
{
  ExtAddr_t zsiKeRemoteExtAddr;
  uint8_t privateKey[SECT163K1_PRIVATE_KEY_SIZE];
  uint8_t publicKey[SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE];
} ZsiEccGenerateKey_t;

typedef union _ZsiCerticomMem_t
{
  ZsiEccKeyBitGenerate_t zsiEccKeyBitGenerate;
  ZsiEccGenerateKey_t zsiEccGenerateKey;
} ZsiCerticomMem_t;
#endif //#if CERTICOM_SUPPORT == 1
BEGIN_PACK
typedef struct PACK _ZsiKeMacBuffer_t
{
  volatile uint8_t keyExpander[SECURITY_KEY_SIZE];
  uint8_t macData[ZSI_KE_MAC_DATA_SIZE];
  volatile uint8_t bitsExpander[AES_MMO_HASH_SIZE];

  uint8_t digest[AES_MMO_HASH_SIZE];
  uint8_t hash[AES_MMO_HASH_SIZE];
} ZsiKeMacBuffer_t;
END_PACK

typedef struct _ZsiSspBcbHash_t
{
  uint32_t size;
  uint8_t *data;
} ZsiSspBcbHash_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for KE commands deserialization.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiKeFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
#if CERTICOM_SUPPORT == 1
/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKeyReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-ZSE_ECCGenerateKeyReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZSE_ECCGenerateKeyReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}

/**************************************************************************//**
  \brief KE-ZSE_ECCKeyBitGenerateReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-ZSE_ECCKeyBitGenerateReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZSE_ECCKeyBitGenerateReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + SECT163K1_PRIVATE_KEY_SIZE +
         SECT163K1_PRIVATE_KEY_SIZE + SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE +
         SECT163K1_CERTIFICATE_SIZE + SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE +
         SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE;
}
/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKey primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZSE_ECCGenerateKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief KE-ZSE_ECCKeyBitGenerate primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZSE_ECCKeyBitGenerateReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKey confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZSE_ECCGenerateKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief KE-ZSE_ECCKeyBitGenerate confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZSE_ECCKeyBitGenerateConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif //#if CERTICOM_SUPPORT == 1
/**************************************************************************//**
  \brief KE-SSP_KeyedHashMacReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_KeyedHashMacReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
 \brief KE-SSP_KeyedHashMacReq frame size calculation routine.
        SOF and LENGTH fields are dismissed.

 \param[in] req - request parameters.

 \return KE-SSP_KeyedHashMacReq request frame size.
******************************************************************************/
INLINE uint16_t zsiSSP_KeyedHashMacReq(const void *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t) +
         ((SSP_KeyedHashMacReq_t *)req)->textSize + AES_MMO_HASH_SIZE;
}
/**************************************************************************//**
  \brief KE-SSP_KeyedHashMacConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_KeyedHashMacConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief SSP_KeyedHashMacReq.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
 ******************************************************************************/
void zsiSSP_KeyedHashMacConfCallback(void *const req);
/**************************************************************************//**
  \brief KE-SSP_BcbHashReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-SSP_BcbHashReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiSSP_BcbHashReq(const void *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint32_t) +
         ((ZsiSspBcbHash_t *)req)->size;
}

/**************************************************************************//**
  \brief KE-SSP_BcbHashReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_BcbHashReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief KE-SSP_BcbHash confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_BcbHashConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpEncryptFrame primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_ZgpEncryptFrameReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpEncryptFrame frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-SSP_ZgpEncryptFrame request frame size.
 ******************************************************************************/
INLINE uint16_t zsiSSP_ZgpEncryptFrameReqLength(uint8_t headerLen, uint8_t payloadLen, uint8_t MicFrameCtrLen)
{
  SSP_ZgpEncryptFrameReq_t zgpEncFrameReq;
  uint16_t length;
  length = ZSI_COMMAND_FRAME_OVERHEAD + ZGP_SECURITY_KEY_LENGTH + sizeof(zgpEncFrameReq.securityFrameCounter) + sizeof(zgpEncFrameReq.securityLevel)
           + sizeof(zgpEncFrameReq.appId)+ sizeof(zgpEncFrameReq.srcID) + sizeof(zgpEncFrameReq.extAddr)
           + sizeof(zgpEncFrameReq.dir) + sizeof(uint32_t) + sizeof(zgpEncFrameReq.headerLength)
           + sizeof(zgpEncFrameReq.payloadLength) + headerLen + payloadLen + MicFrameCtrLen;
  return length;
}
/**************************************************************************//**
  \brief KE-SSP_ZgpEncryptFrame confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_ZgpEncryptFrameConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief ZgpEncrypt.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
 ******************************************************************************/
void zsiZgpEncryptConfCallback(void *const req);
/**************************************************************************//**
  \brief KE-SSP_ZgpDecryptFrame primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_ZgpDecryptFrameReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpDecryptFrame frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-SSP_ZgpDecryptFrame request frame size.
 ******************************************************************************/
INLINE uint16_t zsiSSP_ZgpDecryptFrameReqLength(uint8_t headerLen, uint8_t payloadLen, uint8_t MicFrameCtrLen)
{
  SSP_ZgpDecryptFrameReq_t zgpDecFrameReq;
  uint16_t length;
  length = ZSI_COMMAND_FRAME_OVERHEAD + ZGP_SECURITY_KEY_LENGTH + sizeof(zgpDecFrameReq.securityFrameCounter) + sizeof(zgpDecFrameReq.securityLevel)
           + sizeof(zgpDecFrameReq.appId)+ sizeof(zgpDecFrameReq.srcID) + sizeof(zgpDecFrameReq.extAddr)
           + sizeof(zgpDecFrameReq.dir) + sizeof(uint32_t) + sizeof(zgpDecFrameReq.headerLength)
           + sizeof(zgpDecFrameReq.payloadLength) + headerLen + payloadLen + MicFrameCtrLen;
  return length;
}
/**************************************************************************//**
  \brief KE-SSP_ZgpDecryptFrame confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_ZgpDecryptFrameConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief ZgpDecrypt.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
 ******************************************************************************/
void zsiZgpDecryptConfCallback(void *const req);
#elif defined(ZAPPSI_NP)
#if CERTICOM_SUPPORT == 1
/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKeyConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-ZSE_ECCGenerateKeyConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZSE_ECCGenerateKeyConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + SECT163K1_PRIVATE_KEY_SIZE +
         SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE;
}

/**************************************************************************//**
  \brief KE-ZSE_ECCKeyBitGenerateConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-ZSE_ECCGenerateKeyConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZSE_ECCKeyBitGenerateConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + SECT163K1_SHARED_SECRET_SIZE;
}
/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKeyReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZSE_ECCGenerateKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief KE-ZSE_ECCGenerateKeyConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZSE_ECCGenerateKeyConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief KE-ZSE_ECCKeyBitGenerateReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZSE_ECCKeyBitGenerateReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif //CERTICOM_SUPPORT == 1
/**************************************************************************//**
  \brief KE-SSP_KeyedHashMacConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_KeyedHashMacConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_KeyedHashMacConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-SSP_KeyedHashMacConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiSSP_KeyedHashMacConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + AES_MMO_HASH_SIZE + sizeof(uint8_t) /*status*/;
}
/**************************************************************************//**
  \brief SSP_KeyedHashMacReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_KeyedHashMacReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
\brief Confirm for SSP_KeyedHashMacReq.
******************************************************************************/
void zsiKeyedHashMacConf(SSP_KeyedHashMacConf_t *conf);
/**************************************************************************//**
  \brief KE-SSP_BcbHashConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return KE-SSP_BcbHashConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiSSP_BcbHashConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + AES_MMO_HASH_SIZE;
}
/**************************************************************************//**
  \brief KE-SSP_BcbHashReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_BcbHashReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpEncryptFrame request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_ZgpEncryptFrameReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpEncryptFrameConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_ZgpEncryptFrameConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
\brief Confirm for SSP_ZgpEncryptFrameReq.
******************************************************************************/
void zsiZgpEncryptFrameConf(SSP_ZgpEncryptFrameConf_t *conf);
/**************************************************************************//**
  \brief KE-SSP_ZgpDecryptFrame request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSSP_ZgpDecryptFrameReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief KE-SSP_ZgpDecryptFrameConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSSP_ZgpDecryptFrameConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
\brief Confirm for SSP_ZgpDecryptFrameReq.
******************************************************************************/
void zsiZgpDecryptFrameConf(SSP_ZgpDecryptFrameConf_t *conf);
#endif /* ZAPPSI_NP */


#ifdef ZAPPSI_HOST

#if CERTICOM_SUPPORT == 1
#define zsiDeserializeZSE_ECCGenerateKeyReq          NULL
#define zsiDeserializeZSE_ECCKeyBitGenerateReq       NULL
#endif //#if CERTICOM_SUPPORT == 1
#define zsiDeserializeSSP_KeyedHashMacReq            NULL
#define zsiDeserializeSSP_BcbHashReq                 NULL
#define zsiDeserializeSSP_ZgpEncryptFrameReq         NULL
#define zsiSerializeSSP_ZgpEncryptFrameConf          NULL
#define zsiDeserializeSSP_ZgpDecryptFrameReq         NULL
#define zsiSerializeSSP_ZgpDecryptFrameConf          NULL
#elif defined(ZAPPSI_NP)

#if CERTICOM_SUPPORT == 1
#define zsiDeserializeZSE_ECCGenerateKeyConf         NULL
#define zsiDeserializeZSE_ECCKeyBitGenerateConf      NULL
#endif //#if CERTICOM_SUPPORT == 1
#define zsiDeserializeSSP_KeyedHashMacConf           NULL
#define zsiDeserializeSSP_BcbHashConf                NULL
#define zsiDeserializeSSP_ZgpEncryptFrameConf        NULL
#define zsiDeserializeSSP_ZgpDecryptFrameConf        NULL
#endif /* ZAPPSI_NP */

#endif /* ZSIKESERIALIZATION_H */
