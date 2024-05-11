/*******************************************************************************
  Custom Scenes Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customScenesCluster.c

  Summary:
    This file contains the Custom Scenes Cluster implementation.

  Description:
    This file contains the Custom Scenes Cluster implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <custom/include/customScenesCluster.h>
#include <scenes.h>
#include <custom/include/customOnOffCluster.h>
#include <custom/include/customLevelControlCluster.h>
#include <custom/include/customColorControlCluster.h>
#include <zclCommandManager.h>
#include <wlPdsMemIds.h>
#include <custom/include/custom.h>
#include <scenesCluster.h>
#include <groupsCluster.h>
#include <console.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define GLOBAL_SCENE_SCENE_ID 0u
#define GLOBAL_SCENE_GROUP_ID 0u

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload);
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload);
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload);
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload);
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload);
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload);
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload);
static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload);
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload);
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopyScene_t *payload);
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload);
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload);
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload);
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_SceneClusterServerAttributes_t customScenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_SceneClusterClientAttributes_t customScenesClusterClientAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t        customScenesCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd, removeAllScenesInd,
                                     storeSceneInd, recallSceneInd, getSceneMembershipInd,
                                     enhancedAddSceneInd, enhancedViewSceneInd, copySceneInd)                                  
};

PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t        customScenesClientCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_COMMANDS(addSceneResponseInd, viewSceneResponseInd,
      removeSceneResponseInd, removeAllScenesResponseInd, storeSceneResponseInd,
      getSceneMembershipResponseInd, enhancedAddSceneResponseInd,
      enhancedViewSceneResponseInd, copySceneResponseInd)                                     

};

Scene_t customSceneTable[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void customScenesClusterInit(void)
{
  memset(customSceneTable, 0, sizeof(Scene_t) * MAX_SCENES_AMOUNT);

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
      customSceneTable[i].free = true;

  customScenesClusterServerAttributes.sceneCount.value   = 0;
  customScenesClusterServerAttributes.currentScene.value = 0;
  customScenesClusterServerAttributes.currentGroup.value = 0;
  customScenesClusterServerAttributes.sceneValid.value   = true;
  customScenesClusterServerAttributes.nameSupport.value  = 0;
  customScenesClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
  /* Allocate space for global scene*/
  {
    Scene_t *scene = allocateScene(customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

    scene->sceneId = GLOBAL_SCENE_SCENE_ID;
    scene->groupId = GLOBAL_SCENE_GROUP_ID;
    customScenesClusterServerAttributes.sceneCount.value--; // to pass the certification
  }
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, SCENES_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  customScenesClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Invalidates scene
******************************************************************************/
void customScenesInvalidate(void)
{
  customScenesClusterServerAttributes.sceneValid.value = false;
}

/**************************************************************************//**
\brief Callback on receiving Add Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t *payload)
{
  ZCL_Status_t status;


  appSnprintf("addSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);

  status = processAddSceneCommand(false, addressing, payloadLength, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);
  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }

  return status;
}

/**************************************************************************//**
\brief Callback on receiving View Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  ZCL_Status_t status;

  appSnprintf("viewSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);

  status = processViewSceneCommand(false, addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable);

  (void)payloadLength;
  return status;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload)
{
  ZCL_Status_t status;


  appSnprintf("enhancedAddSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);
  status =  processAddSceneCommand(true, addressing, payloadLength,(ZCL_AddScene_t *)payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
     PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }

  return status;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload)
{

  appSnprintf("enhancedViewSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);
  return processViewSceneCommand(true, addressing, (ZCL_ViewScene_t *)payload,  APP_ENDPOINT_CUSTOM, customSceneTable);
}

/**************************************************************************//**
\brief Callback on receiving Remove Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload)
{
  ZCL_Status_t status;

  appSnprintf("removeSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);

  status = processRemoveSceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }

  (void)payloadLength;
  return status;
}

/**************************************************************************//**
\brief Callback on receiving Remove All Scenes command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload)
{
  ZCL_Status_t status;

  appSnprintf("removeAllScenesInd(): 0x%04x\r\n", payload->groupId);

  status = processRemoveAllScenesCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  return status;
}

/**************************************************************************//**
\brief Callback on receiving Store Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload)
{
  ZCL_Status_t status;

  appSnprintf("storeSceneInd(): 0x%04x, %d\r\n", payload->groupId, payload->sceneId);

  status = processStoreSceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  return status;
}

/**************************************************************************//**
\brief Callback on receiving Recall Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload)
{
  appSnprintf("recallSceneInd(): 0x%04x, %d\r\n", payload->groupId, payload->sceneId);

  if (recallScene(payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes))
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Get Scenes Membership command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload)
{

  appSnprintf("getSceneMembershipInd(): 0x%04x\r\n", payload->groupId);

  return processGetSceneMembershipCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, customScenesClusterServerAttributes.sceneCount.value);
}

/**************************************************************************//**
\brief Stores scene to scene table

\param[in] storeScene - the pointer to Store Scene request

\returns status of scene storing
******************************************************************************/
ZCL_Status_t storeScene(ZCL_StoreScene_t *storeScene, Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  ZCL_Status_t status;

  if (groupsIsValidGroup(storeScene->groupId, srcEp))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(storeScene->groupId, storeScene->sceneId, scenePool);

    if (!scene)
      scene = allocateScene(scenePool, &scenesAttributes->sceneCount.value);

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = storeScene->sceneId;
      scene->groupId = storeScene->groupId;

      scene->onOff = onOffState();
      scene->currentLevel = levelControlCurrentLevel();
      /* NEED TO BE IMPLEMNETD*/


      scene->colorMode = (ZCL_ZllEnhancedColorMode_t)customColorControlClusterServerAttributes.colorMode.value;
      scene->currentX = customColorControlClusterServerAttributes.currentX.value;
      scene->currentY = customColorControlClusterServerAttributes.currentY.value;
      scene->enhancedCurrentHue = customColorControlClusterServerAttributes.enhancedCurrentHue.value;
      scene->currentSaturation = customColorControlClusterServerAttributes.currentSaturation.value;
      scene->colorLoopActive = customColorControlClusterServerAttributes.colorLoopActive.value;
      scene->colorLoopDirection = customColorControlClusterServerAttributes.colorLoopDirection.value;
      scene->colorLoopTime = customColorControlClusterServerAttributes.colorLoopTime.value;
      scene->colorTemperature = customColorControlClusterServerAttributes.colorTemperature.value;

      scenesAttributes->currentGroup.value = scene->groupId;
      scenesAttributes->currentScene.value = scene->sceneId;
      scenesAttributes->sceneValid.value = true;
    }
    else
      status = ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  return status;
}

/**************************************************************************//**
\brief Callback on receive of Copy Scene command
******************************************************************************/
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,
                                 ZCL_CopyScene_t *payload)
{
  ZCL_Status_t status;

  appSnprintf("copySceneInd()\r\n");

  status = processCopySceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM,
                                   customSceneTable, &customScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  return status;
}
/**************************************************************************//**
\brief Callback on receive of Add Scene Response command
\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
  appSnprintf("Add scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of View Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload)
{
  appSnprintf("View scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);
  appSnprintf("transitionTime = 0x%04x\r\n", payload->transitionTime);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Remove Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  appSnprintf( "Remove scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Remove All Scenes Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  appSnprintf("Remove all scenes response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Store Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload)
{
  appSnprintf("Store scene response: status = 0x%02x\r\n", payload->status);

  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload)
{
  appSnprintf("Get scene membership response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneCount = 0x%02x\r\n", payload->sceneCount);

  for (uint8_t i = 0; i < payload->sceneCount; i++)
  {
    appSnprintf("sceneId = 0x%02x\r\n", payload->sceneList[i]);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload)
{
  appSnprintf("Add scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload)
{
  appSnprintf("View scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);
  appSnprintf("transitionTime = 0x%04x\r\n", payload->transitionTime);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of Copy Scene Response command
******************************************************************************/
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload)
{
  appSnprintf("Copy scene response: status = 0x%02x\r\n", payload->status);
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
#endif // #if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE
//eof customScenesCluster.c