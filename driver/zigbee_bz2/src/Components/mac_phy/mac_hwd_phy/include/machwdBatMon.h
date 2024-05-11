/*******************************************************************************
  MAC Hardware Battery Monitor Header File

  Company:
    Microchip Technology Inc.

  File Name:
    machwdBatMon.h

  Summary:
    This file contains the Prototypes of battery monitor functions and corresponding types.

  Description:
    This file contains the Prototypes of battery monitor functions and corresponding types.
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

#ifndef _MACHWDBATMON_H
#define _MACHWDBATMON_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <rfBattery.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
//! Redefenition of battery request function name.
#define MACHWD_BatMonReq RF_BatteryMonReq

/******************************************************************************
                    Types section
******************************************************************************/
//! Redefenition of battery request structure.
typedef RF_BatteryMonReq_t MACHWD_BatMonReq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Sets battery monitor voltage.
  \param reqParams - request parameters structure pointer.
  \return none.
******************************************************************************/
void MACHWD_BatMonReq(MACHWD_BatMonReq_t *reqParams);

#endif /*_MACHWDBATMON_H*/

// eof machwdBatMon.h
