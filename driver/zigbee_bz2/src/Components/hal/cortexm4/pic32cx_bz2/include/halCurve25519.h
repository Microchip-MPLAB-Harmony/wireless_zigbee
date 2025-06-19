/*******************************************************************************
  HAL Curve25519 Header File

  Company:
    Microchip Technology Inc.

  File Name:
    halCurve25519.h

  Summary:
    This file contains the implementation of Bitcloud HAL Curve25519 for pic32cx.

  Description:
    This file contains the implementation of Bitcloud HAL Curve25519 for pic32cx.
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

// DOM-IGNORE-BEGIN
#ifndef HAL_CURVE25519_H
#define HAL_CURVE25519_H
// DOM-IGNORE-END

/******************************************************************************
                                    Includes section
 ******************************************************************************/
#include <crypto.h>
#include <systemenvironment/include/sysTypes.h>
#include <halAssert.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
                                Defines section
 ******************************************************************************/
#define DRIVER_VERSION 0x00000001u
#define ERR_NONE 0
#define ERR_INVALID_DATA -1

/******************************************************************************
                                Types section
 ******************************************************************************/
 
/** Defines HAL Curve25519 commands such as init, generate private key/
 *  public key/Shared secret etc */
typedef enum
{
  /** Initialize and Generate private key */
  SM_INIT_COMMAND = 0, 
  /** Generate public key */
  SM_GENERATE_PUBLIC_KEY_COMMAND, 
  /** Generate shared secret */
  SM_GENERATE_SHARED_SECRET_COMMAND, 
  /** Remove all keys */
  SM_FREE_KEY 
} HAL_Curve25519Cmd_t;

/** Struct for Init req */
typedef struct
{
  /** Curve25519 command. */
  HAL_Curve25519Cmd_t cmd;
  /** Byte Size of privateKey. */
  int privateKeySize;
  unsigned char* privateKey;
  /** Byte Size of publicKey. */
  int publicKeySize;
  unsigned char* publicKey;
  /** Byte Size of basePoint. */
  int basePointSize;
  unsigned char* basePoint;
  /** confirmation callback */
  void (*curve25519Conf)(void);
} HAL_Curve25519_Req_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/

/**************************************************************************//**
\brief Initiates Curve25519 Private/Public key as per request parameters

\param[in] reqParams_s - pointer to request parameters.
\return None.
 ******************************************************************************/
void HAL_CURVE25519_KeyReq(HAL_Curve25519_Req_t *reqParams_s);

/**************************************************************************//**
\brief Resets the Curve25519 security module

\param[in] None
\return None.
 ******************************************************************************/
void HAL_CURVE25519_SmReset(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_CURVE25519_H_INCLUDED */