/*******************************************************************************
  MAC HwdRandom Header File

  Company:
    Microchip Technology Inc.

  File Name:
    machwdRnd.h

  Summary:
    This file contains the MACHWD random generation types and function prototypes.

  Description:
    This file contains the MACHWD random generation types and function prototypes.
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

#ifndef _MACHWDRND_H
#define _MACHWDRND_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <rfRandom.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
//! Redefenition of random generation request function name.
#define MACHWD_RndReq RF_RandomReq
//! Redefenition of random seq generation request function name .
#define MACHWD_RndSeqReq RF_RandomSeqReq
/******************************************************************************
                    Types section
******************************************************************************/
//! Redefenition of random generation request structure.
typedef RF_RandomReq_t MACHWD_RndReq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Requests random value.
  \param reqParams - request parameters structure pointer.
  \return none.
******************************************************************************/
void MACHWD_RndReq(MACHWD_RndReq_t *reqParams);

/**************************************************************************//**
  \brief Requests random seq.
  \param reqParams - request parameters structure pointer.
  \return none.
******************************************************************************/
void MACHWD_RndSeqReq(MACHWD_RndReq_t *reqParams);

#endif /*_MACHWDRND_H*/

// eof machwdRnd.h
