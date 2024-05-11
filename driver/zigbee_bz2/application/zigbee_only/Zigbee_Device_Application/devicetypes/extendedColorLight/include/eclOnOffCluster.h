/*******************************************************************************
  Extended Color Light On/Off cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
   eclOnOffCluster.h

  Summary:
    This file contains the Extended Color Light On/Off cluster interface.

  Description:
    This file contains the Extended Color Light On/Off cluster interface.
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

#ifndef DLONOFFCLUSTER_H
#define DLONOFFCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllOnOffCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ONOFF_VAL_MIN_REPORT_PERIOD 30
#define ONOFF_VAL_MAX_REPORT_PERIOD 60

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_OnOffClusterServerAttributes_t eclOnOffClusterServerAttributes;
extern ZCL_OnOffClusterCommands_t         eclOnOffCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
bool isDeviceOn(void);
void stopDeviceUpdate(void);
void onOffClusterSetGlobalSceneControl(void);
void onOffClusterSetExtensionField(bool onOff);

/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void);

/**************************************************************************//**
\brief Sets on/off state
******************************************************************************/
void eclOnOffSetOnOffState(bool state);

/**************************************************************************//**
\brief gets on/off state

\return on/off state
******************************************************************************/
bool onOffState(void);

#endif // DLONOFFCLUSTER_H

// eof dlOnOffCluster.h
