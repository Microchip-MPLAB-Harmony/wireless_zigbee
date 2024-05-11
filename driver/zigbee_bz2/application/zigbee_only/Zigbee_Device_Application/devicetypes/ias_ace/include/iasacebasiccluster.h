/*******************************************************************************
  IAS ACE Basic cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACEBasicCluster.h

  Summary:
    This file contains the IAS ACE Basic cluster interface.

  Description:
    This file contains the IAS ACE Basic cluster interface.
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

#ifndef _IASACEBASICCLUSTER_H
#define _IASACEBASICCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zclZllBasicCluster.h>
/******************************************************************************
                    Defines section
******************************************************************************/
/******************************************************************************
                    External variables section
******************************************************************************/
extern ZCL_BasicClusterServerAttributes_t iasACEBasicClusterServerAttributes;
extern PROGMEM_DECLARE (ZCL_BasicClusterServerCommands_t iasACEBasicClusterServerCommands);
extern ZCL_BasicClusterClientAttributes_t iasACEBasicClusterClientAttributes;
/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void iasBasicClusterInit(void);

#endif // _IASACEBASICCLUSTER_H

// eof iasACEBasicCluster.h
