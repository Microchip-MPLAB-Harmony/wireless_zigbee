/*******************************************************************************
  Extended Color Light Level Control cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    eclLevelControlCluster.h

  Summary:
    This file contains the Extended Color Light Level Control cluster interface.

  Description:
    This file contains the Extended Color Light Level Control cluster interface.
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

#ifndef _DLLEVELCONTROLCLUSTER_H
#define _DLLEVELCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllLevelControlCluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD  10
#define LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD  20

#define UPDATE_TIMER_INTERVAL                100 // 1/10th of a second per spec
#define MIN_LIGHT_LEVEL                      1
#define MAX_LIGHT_LEVEL                      254
#define MIN_TRANSITION_TIME                  1

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_LevelControlClusterServerAttributes_t eclLevelControlClusterServerAttributes;
extern ZCL_LevelControlClusterCommands_t         eclLevelControlCommands;

/******************************************************************************
                    Prototypes section
******************************************************************************/
void levelControlClusterInit(void);
void levelControlClusterSetExtensionField(uint16_t currentLevel);
void levelControlDisplayLevel(void);
void levelControlClusterStop(void);
#endif // _DLLEVELCONTROLCLUSTER_H

// eof dlLevelControlCluster.h
