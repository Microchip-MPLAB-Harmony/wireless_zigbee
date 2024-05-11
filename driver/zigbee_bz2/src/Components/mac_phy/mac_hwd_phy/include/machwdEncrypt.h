/*******************************************************************************
  MAC HwdEncryption Header File

  Company:
    Microchip Technology Inc.

  File Name:
    machwdEncrypt.h

  Summary:
    This file provides a interface to the MAC encryption parameters.

  Description:
    This file contains the  Prototypes of ecnryption functions and corresponding types.
    Note that encryption is supported only for RF231 and RF212.
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

#ifndef _MACHWDENCRYPT_H
#define _MACHWDENCRYPT_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <rfEncrypt.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
//! Redefenition of encryption request function name.
#define MACHWD_EncryptReq RF_EncryptReq

/******************************************************************************
                    Types section
******************************************************************************/
//! Redefenition of encryption request structure.
typedef RF_EncryptReq_t MACHWD_EncryptReq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Executes AES command.
  \param reqParams - request parameters structure pointer.
  \return none.
******************************************************************************/
void MACHWD_EncryptReq(MACHWD_EncryptReq_t *reqParams);

#endif /*_MACHWDENCRYPT_H*/

// eof machwdEncrypt.h
