/*******************************************************************************
  Color scene controller Commissioning cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cscCommissioningCluster.h

  Summary:
    This file contains the Color scene controller Commissioning cluster interface.

  Description:
    This file contains the Color scene controller Commissioning cluster interface.
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

#ifndef COLORSCENECONTROLLER_COMMISSIONINGCLUSTER_H
#define COLORSCENECONTROLLER_COMMISSIONINGCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclZllCommissioningCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_CommissioningClusterServerAttributes_t cscCommissioningClusterServerAttributes;
extern ZCL_CommissioningClusterCommands_t         cscCommissioningClusterCommands;

extern ZCL_CommissioningClusterClientAttributes_t cscCommissioningClusterClientAttributes;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize Commissioning cluster.
******************************************************************************/
void cscCommissioningServerClusterInit(void);

/**************************************************************************//**
\brief Initialize Commissioning cluster client.
******************************************************************************/
void cscCommissioningClientClusterInit(void);
#endif // COLORSCENECONTROLLER_COMMISSIONINGCLUSTER_H

// eof cscCommissioningCluster.h
