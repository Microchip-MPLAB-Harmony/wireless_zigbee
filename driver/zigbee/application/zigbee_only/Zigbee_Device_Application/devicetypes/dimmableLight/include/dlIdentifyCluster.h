/*******************************************************************************
  Dimmable Light Identify cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dlIdentifyCluster.h

  Summary:
    This file contains the Dimmable Light Identify cluster interface.

  Description:
    This file contains the Dimmable Light Identify cluster interface.
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

#ifndef _DLIDENTIFYCLUSTER_H
#define _DLIDENTIFYCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllIdentifyCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_IdentifyClusterServerAttributes_t dlIdentifyClusterServerAttributes;
extern ZCL_IdentifyClusterClientAttributes_t dlIdentifyClusterClientAttributes;
extern ZCL_IdentifyClusterCommands_t   dlIdentifyCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
\brief Stop identify cluster
******************************************************************************/
void identifyClusterStop(void);

/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void);

/**************************************************************************//**
\brief Sends Identify request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] time - identify time
******************************************************************************/
void identifySendIdentify(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t time);
#endif // _DLIDENTIFYCLUSTER_H

// eof dlIdentifyCluster.h

