/*******************************************************************************
  Light device Color Control cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    eclColorControlCluster.h

  Summary:
    This file contains the Light device Color Control cluster interface.

  Description:
    This file contains the Light device Color Control cluster interface.
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

#ifndef _LIGHTCOLORCONTROLCLUSTER_H
#define _LIGHTCOLORCONTROLCLUSTER_H

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <zclZllColorControlCluster.h>
#include <eclScenes.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ColorControlClusterServerAttributes_t eclColorControlClusterServerAttributes;
extern ZCL_ColorControlClusterCommands_t eclColorControlClusterServerCommands;

/******************************************************************************
                    Prototypes
******************************************************************************/
void colorControlClusterInit(void);
void colorControlClusterSetExtensionField(Scene_t *scene);
void colorControlClusterStop(void);

/**************************************************************************//**
\brief Show identify effect.

\param[in] enhancedHue - enhanced hue to move to.
******************************************************************************/
void colorControlShowIdentifyEffect(uint16_t enhancedHue);

/**************************************************************************//**
\brief Stop showing identify effect and return to previous state.
******************************************************************************/
void colorControlStopIdentifyEffect(void);

#endif // _LIGHTCOLORCONTROLCLUSTER_H

// eof lightColorControlCluster.h
