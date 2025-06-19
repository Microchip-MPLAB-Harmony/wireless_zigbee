/*******************************************************************************
  HAL SHA-256 Header File

  Company:
    Microchip Technology Inc.

  File Name:
    halSha256.h

  Summary:
    This file contains the implementation of Bitcloud HAL SHA-256 for pic32cx.

  Description:
    This file contains the implementation of Bitcloud HAL SHA-256 for pic32cx.
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
#ifndef HAL_SHA256_H
#define HAL_SHA256_H
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
 
/** Defines HAL SHA256 commands such as init, dataadd,
 *  and finalize */
typedef enum
{
  /** Initialize */
  SM_SHA256_INIT_COMMAND = 0, 
  /** Updates HASH with data provided */
  SM_SHA256_DATA_ADD_COMMAND, 
  /** Finalizes the hash and puts the result into digest */
  SM_SHA256_FINALIZE_COMMAND,
} HAL_SHA256Cmd_t;

typedef struct
{
  uint8_t status;
} Sha256Conf_t;


/** Struct for Init req */
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
} HAL_SHA256_Req_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/

/**************************************************************************//**
\brief Initiates Sha256 calculation as per request parameters

\param[in] reqParams_s - pointer to request parameters.
\return none.
 ******************************************************************************/
void HAL_SHA256_Req(HAL_SHA256_Req_t *reqParams_s);

/**************************************************************************//**
\brief Resets the Sha256 security module

\param[in] none.
\return none.
 ******************************************************************************/
void HAL_SHA256_SmReset(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_SHA256_H */