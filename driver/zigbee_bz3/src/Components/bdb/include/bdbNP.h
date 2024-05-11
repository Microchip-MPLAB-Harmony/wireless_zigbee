// DOM-IGNORE-BEGIN
/*******************************************************************************
  BDB NP Header File

  Company
    Microchip Technology Inc.

  File Name
    bdbNP.h

  Summary
    bdb NP interface.

  Description
    This header file file defines the interface to the BDB network parameters.
 *******************************************************************************/


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

// DOM-IGNORE-BEGIN
#ifndef _BDBNP_H
#define _BDBNP_H
// DOM-IGNORE-END

/**********************************************************************************
                             INCLUDE FILES
 **********************************************************************************/

/******************************************************************************
                    Defines section
 ******************************************************************************/
 
/******************************************************************************
                    Prototypes section
 ******************************************************************************/
 
/**************************************************************************//**
  \brief Set the bdbNodeIsOnANetwork status
  
  \param bool - true if the device is on network, false - otherwise

  \return None
 ******************************************************************************/
void BDB_SetBdbNodeIsOnANetwork(bool onNetwork);

/**************************************************************************//**
  \brief Get the bdbNodeIsOnANetwork status
   
   
  \param None

  \return bool - true if the device is on network, false - otherwise
 ******************************************************************************/
bool BDB_GetBdbNodeIsOnANetwork(void);

#endif // _BDBNP_H
