/*******************************************************************************
  Zigbee Cluster Library command analyzer Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclCommandAnalyzer.h

  Summary:
    ZCL command analyzer interface.

  Description:
    This file contains ZCL command analyzer interface.
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


#ifndef _ZCLCOMMANDANALYZER_H
#define _ZCLCOMMANDANALYZER_H

/******************************************************************************
                           Includes section
******************************************************************************/
#include <zcl/include/zcl.h>

/******************************************************************************
                           Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Checks if response for command is required based on its payload

\param[in] cluster - cluster id of command
\param[in] cmd     - command id
\param[in] dir     - command direction
\param[in] payload - command payload

\returns true if resposne is required, false otherwise
******************************************************************************/
bool zclIsResponseRequiredByPayload(ClusterId_t cluster, ZCL_CommandId_t cmd, uint8_t dir, uint8_t *payload);

/***************************************************************************//**
\brief Checks whether response for command is required based on its address mode

\param[in] req - pointer to request structure

\return true - if response is required, false - otherwise.
******************************************************************************/
bool zclIsResponseRequiredByAddrMode(ZCL_Request_t *req);

#endif //_ZCLCOMMANDANALYZER_H
//eof zclCommandAnalyzer.h

