/*******************************************************************************
  PHY Tx Power Converter Header File

  Company:
    Microchip Technology Inc.

  File Name:
    phyTxPowerConverter.h

  Summary:
    This file contains the prototype for PHY TX power converter interface.

  Description:
    This file defines the prototype for PHY TX power converter interface.
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

#ifndef _PHYTXPOWERCONVERTER_H
#define _PHYTXPOWERCONVERTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <RF231_RF212/PHY/include/at86rf233.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
#define FCC_REGION         0
#define ETSI_REGION        1
#define ETSI_FCC_REGION    2


/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Converts tx power from dBm to predefined value of particular RF chip

\param[in] txPower - power of transmitter in dBm

\returns power of transmitter in predefined value
******************************************************************************/
uint8_t PHY_ConvertTxPowerFromDbm(int8_t txPower);

/**************************************************************************//**
\brief Converts tx power from predefined value of particular RF chip to dBm

\param[in] txPower - power of transmitter in predefined value

\returns power of transmitter in dBm
******************************************************************************/
int8_t PHY_ConvertTxPowerToDbm(uint8_t txPower);

/**************************************************************************//**
\brief Converts tx power from to a near RF chip value to dBm

\param[in] txPower - Tx power dBm

\returns power of transmitter in dBm
******************************************************************************/
int8_t PHY_StoreNearTxPowerInDbm(int8_t txPower);

#endif /* _PHYTXPOWERCONVERTER_H */

// eof phyTxPowerConverter.h
