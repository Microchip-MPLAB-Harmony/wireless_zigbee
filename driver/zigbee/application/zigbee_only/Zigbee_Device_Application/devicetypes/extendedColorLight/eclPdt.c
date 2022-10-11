/*******************************************************************************
  Extended Color Light Persistent Data Table Source File

  Company:
    Microchip Technology Inc.

  File Name:
   eclPdt.c

  Summary:
    This file contains the Extended Color Light Persistent Data Table implementation.

  Description:
    This file contains the Extended Color Light Persistent Data Table implementation.
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

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <eclScenes.h>
#include <eclOnOffCluster.h>
#include <eclLevelControlCluster.h>
#include <eclScenesCluster.h>

/******************************************************************************
                    External variables section
******************************************************************************/
extern Scene_t scene[MAX_NUMBER_OF_SCENES];
extern ZCL_SceneClusterServerAttributes_t eclScenesClusterServerAttributes;
extern ZCL_ColorControlClusterServerAttributes_t eclColorControlClusterServerAttributes;
extern ZCL_LevelControlClusterServerAttributes_t eclLevelControlClusterServerAttributes;
extern ZCL_OnOffClusterServerAttributes_t eclOnOffClusterServerAttributes;

/******************************************************************************
                    PDT definitions
******************************************************************************/
/*******************************************
         Light application PDT
********************************************/
#ifdef _ENABLE_PERSISTENT_SERVER_
/* Light application data file descriptors.
   Shall be placed in the PDS_FF code segment. */
PDS_DECLARE_FILE(APP_LIGHT_DATA_MEM_ID,                              sizeof(Scene_t)*MAX_NUMBER_OF_SCENES,              &scene,                                 NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID,         sizeof(ZCL_SceneClusterServerAttributes_t),        &eclScenesClusterServerAttributes,       NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID,         sizeof(ZCL_OnOffClusterServerAttributes_t),        &eclOnOffClusterServerAttributes,        NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID, sizeof(ZCL_LevelControlClusterServerAttributes_t), &eclLevelControlClusterServerAttributes, NO_FILE_MARKS);
PDS_DECLARE_FILE(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID, sizeof(ZCL_ColorControlClusterServerAttributes_t), &eclColorControlClusterServerAttributes,   NO_FILE_MARKS);


/* Light application data file identifiers list.
   Will be placed in flash. */
PROGMEM_DECLARE(PDS_MemId_t appZclMemoryIdsTable[]) =
{
  APP_LIGHT_DATA_MEM_ID,
  APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID,
  APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID,
  APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID,
  APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID,
};

/* Light application directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t appZclMemoryDirDescr) =
{
  .list       = appZclMemoryIdsTable,
  .filesCount = ARRAY_SIZE(appZclMemoryIdsTable),
  .memoryId   = HA_APP_MEMORY_MEM_ID
};

#endif /* _ENABLE_PERSISTENT_SERVER_ */
#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof dlPdt.c
