/*******************************************************************************
  Security Service Provider Curve25519 Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspCurve25519Handler.h

  Summary:
    This file contains the Curve25519 functions' declarations.

  Description:
    This file contains the Curve25519 functions' declarations.
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


#ifndef _SSPCURVE25519HANDLER_H
#define _SSPCURVE25519HANDLER_H

#include <configserver/include/csDefaults.h>
#include <systemenvironment/include/sysTypes.h>
#include <security/serviceprovider/include/sspCommon.h>
#include <halCurve25519.h>
#include <security/serviceprovider/include/private/sspHashHandler.h>
#include <security/serviceprovider/include/sspSha256Handler.h>

/******************************************************************************
                        Definitions section.
******************************************************************************/
/* All size in bytes */
#define CURVE25519_GENERATOR_SIZE 32U
#define CURVE25519_PRIVATE_KEYSIZE 32U
#define SHA256_BLOCK_SIZE 64U
#define MAX_CURVE25519_SHARED_SECRET_POINT_SIZE 32U
#define SHA256_PRESHARED_SECURITY_KEY_SIZE SHA256_BLOCK_SIZE
#define AESMMO128_PRESHARED_SECURITY_KEY_SIZE 16U
#define LINK_KEY_SIZE 16U
#define ADDRESS_SIZE 8U
#define APSC_PASSCODE_SIZE   (0x10U) /* This parameter is used in generating public key */

#define CURVE25519_REQ_T HAL_Curve25519_Req_t
#define CURVE25519_REQ   HAL_CURVE25519_KeyReq
#define HARDCODE_BYTE_TO_NINE 0x09
typedef enum
{
  CURVE25519_STATE_IDLE,
  /* Init Random no generatoar and wolfcrypt */
  CURVE25519_STATE_INIT, 
  /* Calculate Base point*/           
  CURVE25519_STATE_GENERATE_BASE_POINT,
  CURVE25519_STATE_GENERATE_PUBLIC_KEY,
  /* Local Public Key is generated*/
  CURVE25519_STATE_LOCAL_PUBLIC_KEY_GENERATED,
  /* Remote device punlic key is received */
  CURVE25519_STATE_PUBLIC_KEY_RECEIVED,
  CURVE25519_STATE_GENERATE_SHARED_SECRET_POINT,
  /* calculate AES Hash if key is 32 byte */
  CURVE25519_STATE_HMAC_0, 
  /* calculate AES Hash of right-concatenating the bit string Key1 with the bit string M*/
  CURVE25519_STATE_HMAC_1, 
  /* calculate AES Hash of right-concatenating the bit string Key2 with the bit string Hash1 */
  CURVE25519_STATE_HMAC_2, 
  /* Link key is generated*/
  CURVE25519_STATE_GENERATE_APS_LINK_KEY,
  CURVE25519_STATE_ERROR,
} SspCurve25519State_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/** Defines all variables required for geneating link key */

#define TEST_MSG_MAX_SIZE 237
typedef struct
{
  BEGIN_PACK
  uint8_t hash[SECURITY_KEY_SIZE];
  uint8_t textSize;
  struct PACK
  {
    uint8_t msg[TEST_MSG_MAX_SIZE];
    volatile uint8_t bitsExpander[SECURITY_KEY_SIZE];
  };
  END_PACK
} SspAesMmoMem_t;

typedef struct
{
  uint8_t status;
} SspCurve25519Conf_t;

/** Defines all variables required for geneating link key */
typedef struct
{
  //! Service field - for internal needs.
  SSP_Service_t service;  

  uint8_t generator[CURVE25519_GENERATOR_SIZE];
  int sizeOfGenerator;
  uint8_t publicKey[CURVE25519_PUBLIC_KEY_SIZE];
  int sizeOfPublicKey;
  uint8_t remotePublicKey[CURVE25519_PUBLIC_KEY_SIZE];
  int sizeOfRemotePublicKey;
  uint8_t addressLocal[ADDRESS_SIZE];
  int sizeOfAddress;
  uint8_t addressRemote[ADDRESS_SIZE];
  int sizeOfAddressRemote;
  int sizeOfPrivateKey;
  uint8_t sharedECDHSecretPoint[MAX_CURVE25519_SHARED_SECRET_POINT_SIZE];
  int sizeOfSharedECDHSecretPoint;
  uint8_t preSharedKey[SHA256_PRESHARED_SECURITY_KEY_SIZE];
  int sizeOfPreSharedKey;
  uint8_t linkKey[LINK_KEY_SIZE];
  int sizeOfLinkKey;

  //! 1: AES-MMO, 0: SHA-256
  uint8_t hashSet:1; 
  //! 1: Co-ordinator, 0: end-device
  uint8_t isCoordinator:1; 
  //! Security Service Provider SspCurve25519 confirm parameters' structure.
  void (*SSP_Curve25519Conf)(SspCurve25519Conf_t *);
  SspCurve25519Conf_t confirm;
  
  //! SSP AES-MMO hash request
  SspBcbHashReq_t bcbHashReqMmo;
  SspCurve25519State_t curve25519State;
  SspAesMmoMem_t aesMmoMem;

  //! SHA-256 variables
  uint8_t shaSum[CRYPT_SHA256_DIGEST_SIZE];

  //! HMAC variables
  //! if HMAC is SHA-256 based then 32 else 16
  uint8_t koWithOpad[SHA256_PRESHARED_SECURITY_KEY_SIZE]; 

  uint8_t errorCode;

  //! Input for Link-Key generation
  uint8_t presharedsecret[16];
  uint8_t size;
  uint8_t apscPasscodeMsg[APSC_PASSCODE_SIZE];

  uint8_t hashInput[TEST_MSG_MAX_SIZE];
  SspSha256HashReq_t sha256HashReq;
} SspCurve25519GenerateLinkKeyReq_t;

/** Defines Memory required for request */
typedef struct
{
  union
  {
    SspCurve25519GenerateLinkKeyReq_t  linkKeyReq;
  };
} SspCurve25519Mem_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/**************************************************************************//**
\brief Curve25519 Generate Link Key request handler

\param[in] none.
\return none.
******************************************************************************/
void sspCurve25519ReqHandler(void);

/**************************************************************************//**
\brief Performs Public Key and Link key generation operation based on incoming parameters.

\param[in] req - Curve25519 request parameters (for detailed description look at
             SspCurve25519GenerateLinkKeyReq_t declaration).
\return none.
******************************************************************************/
void SSP_Curve25519GeneratePublicKeyLinkKeyReq(SspCurve25519GenerateLinkKeyReq_t *req);

#endif // _SSPCURVE25519HANDLER_H

//eof sspCurve25519Handler.h

