/*******************************************************************************
  Color Scene Controller Color Control cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cscColorControlCluster.h

  Summary:
    This file contains the Color Scene Controller device Color Control cluster interface.

  Description:
    This file contains the Color Scene Controller device Color Control cluster interface.
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

#ifndef _COLORSCENERCONTROLLER_COLORCONTROLCLUSTER_H
#define _COLORSCENERCONTROLLER_COLORCONTROLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zclZllColorControlCluster.h>
#include <z3device/clusters/include/colorControlCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_ColorControlClusterCommands_t cscColorControlClusterCommands;
extern ZCL_ColorControlClusterClientAttributes_t cscColorControlClusterClientAttributes;

///******************************************************************************
//                    Prototypes section
//******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void cscColorControlClusterInit(void);

#endif // _COLORSCENECONTROLLER_COLORCONTROLCLUSTER_H

// eof cscColorControlCluster.h
