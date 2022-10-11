/*******************************************************************************
  Control Bridge Groups cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cbGroupsCluster.h

  Summary:
    This file contains the Control Bridge Groups cluster interface.

  Description:
    This file contains the Control Bridge Groups cluster interface.
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

#ifndef _CBGROUPSCLUSTER_H
#define _CBGROUPSCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclZllGroupsCluster.h>

/******************************************************************************
                    Externals
******************************************************************************/
extern PROGMEM_DECLARE(ZCL_GroupsClusterCommands_t cbGroupsCommands);

extern ZCL_GroupsClusterClientAttributes_t  cbGroupsClusterClientAttributes;

typedef void (*AddGroupResponseCb_t)(uint8_t status, uint16_t groupId);

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void cbGroupsClusterInit(void);

#endif // _CBGROUPSCLUSTER_H

// eof cbGroupsCluster.h

