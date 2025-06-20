/*******************************************************************************
  Security Service Provider Sha256 Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspSha256Handler.h

  Summary:
    This file contains the Sha256 functions' declarations.

  Description:
    This file contains the Sha256 functions' declarations.
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


#ifndef _SSPSHA256HANDLER_H
#define _SSPSHA256HANDLER_H

#include <systemenvironment/include/sysTypes.h>
#include <security/serviceprovider/include/sspCommon.h>
#include <halSha256.h>

/******************************************************************************
                        Definitions section.
******************************************************************************/
/* All size in bytes */
#define SHA256_BLOCK_SIZE 64U
#define CRYPT_SHA256_DIGEST_SIZE 32U /* Keep in sync with crypto.h */
#define CRYPT_SHA256_INIT_REQ     CRYPT_SHA256_Initialize
#define CRYPT_SHA256_DATAADD_REQ  CRYPT_SHA256_DataAdd
#define CRYPT_SHA256_FINALIZE_REQ CRYPT_SHA256_Finalize

typedef enum
{
  SHA256_STATE_IDLE,
  SHA256_STATE_DATAADD,
  SHA256_STATE_FINALIZE,
} SspSha256HashHandlerState_t;

/******************************************************************************
                        Types definition section.
******************************************************************************/

/** Defines all variables required for geneating Sha256 */
typedef struct
{
  /** Sha256 command. */
  HAL_SHA256Cmd_t cmd;
  /** Pointer to input data for Sha256 command. */
  uint8_t *message;
  /** Size of input/output data in bytes */
  uint8_t messageSize;
  /** Hash(digest) data */
  uint8_t *hash;
  /** confirmation callback */
  void (*sha256Conf)(void);
} SspSha256HashReq_t;

/** Defines all variables required for geneating Sha256 */
typedef struct
{
  //! Service field - for internal needs.
  SSP_Service_t service;  

  SspSha256HashReq_t      *currentSha256HashReq;
  SspSha256HashHandlerState_t sha256hashHandlerState;
} SspSha256HashHandlerMem_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/**************************************************************************//**
\brief Curve25519 Generate Link Key request handler

\param[in] sspSha256HashReq - request containing all parameters for Sha256 request.
\return none.
******************************************************************************/
void sspSha256HashReq(SspSha256HashReq_t *sspSha256HashReq);

#endif // _SSPSHA256HANDLER_H

//eof sspSha256Handler.h

