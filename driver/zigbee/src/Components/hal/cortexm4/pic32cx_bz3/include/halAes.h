/*******************************************************************************
  HAL Aes Header File

  Company:
    Microchip Technology Inc.

  File Name:
    halAes.h

  Summary:
    This file contains the Implementation of Bitcloud HAL AES for pic32cx.

  Description:
    This file contains the implementation of Bitcloud HAL AES for pic32cx.
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

#ifndef HAL_AES_H_INCLUDED
#define HAL_AES_H_INCLUDED

//#include <crypto.h>
#include <systemenvironment/include/sysTypes.h>
#include <halAssert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DRIVER_VERSION 0x00000001u
#define AES_BLOCK_SIZE 16
#define AES_BLOCK_SIZE_TOTAL 64
#define AES_ENCRYPTION 0
#define AES_DECRYPTION 1
#define ERR_NONE 0
#define ERR_INVALID_DATA -1

typedef enum
{
  SM_SET_KEY_COMMAND = 0,
  SM_ECB_ENCRYPT_COMMAND,
  SM_CBC_ENCRYPT_COMMAND,
  SM_ECB_DECRYPT_COMMAND,
  SM_CBC_DECRYPT_COMMAND,
} HAL_AesCmd_t;

typedef struct
{

  //! AES command.
  HAL_AesCmd_t aesCmd;
  //! Pointer to input data for AES command.
  uint8_t *text;
  //! Size of input/output data in blocks.
  uint8_t blockCount; // Block is 128-bit data.

  void (*encryptConf)(void);
} HAL_AES_EncryptReq_t;

void HAL_AES_EncryptReq(HAL_AES_EncryptReq_t *reqParams);
void HAL_SmReset (void);
void halAesInit(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_AES_H_INCLUDED */
