/*******************************************************************************
  MAC HwdRegister Access Header File

  Company:
    Microchip Technology Inc.

  File Name:
    machwdRegAccess.h

  Summary:
    This file provides the Radio registers access interface.

  Description:
    This file provides the Radio registers access interface.
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

#if !defined _MACHWDREGACCESS_H
#define _MACHWDREGACCESS_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <rfRegAccess.h>

/******************************************************************************
                               Definitions section
 ******************************************************************************/
/** Redefenition of RF register write request function name. **/
#define MACHWD_RegWriteReq RF_RegWriteReq

/** Redefenition of RF register read request function name. **/
#define MACHWD_RegReadReq RF_RegReadReq

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Redefenition of register access request structure. **/
typedef RF_RegAccessReq_t MACHWD_RegAccessReq_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Request to perform writing to the radio module memory.

  \param[in] reqParams - pointer to register access parameters - callback and
                         confirmation status.
  \return None.
 ******************************************************************************/
void MACHWD_RegWriteReq(MACHWD_RegAccessReq_t *reqParams);

/**************************************************************************//**
  \brief Request to perform reading from radio module memory.

  \param[in] reqParams - pointer to register access parameters - callback and
                         confirmation status.
  \return None.
 ******************************************************************************/
void MACHWD_RegReadReq(MACHWD_RegAccessReq_t *reqParams);

#endif /* _MACHWDREGACCESS_H */
/** eof machwdRegAccess.h */
