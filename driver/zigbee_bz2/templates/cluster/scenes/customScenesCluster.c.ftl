/*******************************************************************************
  Custom Scenes Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customScenesCluster.c

  Summary:
    This file contains Custom Scenes Cluster Implementation.

  Description:
    This file contains Custom Scenes Cluster Implementation.
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
#include <z3device/clusters/include/haClusters.h>
#include <z3device/custom/include/customScenesCluster.h>
#include <zcl/clusters/include/scenes.h>
#include <z3device/custom/include/customOnOffCluster.h>
#include <z3device/custom/include/customLevelControlCluster.h>
#include <z3device/custom/include/customColorControlCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/custom/include/custom.h>
#include <z3device/clusters/include/scenesCluster.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/app_zigbee_handler.h>
/******************************************************************************
                    Definitions section
******************************************************************************/
<#if (SCENES_CLUSTER_CS != "CLIENT")>
#define GLOBAL_SCENE_SCENE_ID 0u
#define GLOBAL_SCENE_GROUP_ID 0u
</#if>

/******************************************************************************
                    Prototypes section
******************************************************************************/
<#if (SCENES_CLUSTER_CS != "CLIENT")>
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
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")>
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload);
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload);
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload);
</#if>
/******************************************************************************
                    Global variables section
******************************************************************************/
<#if (SCENES_CLUSTER_CS != "CLIENT")>
ZCL_SceneClusterServerAttributes_t customScenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")>
ZCL_SceneClusterClientAttributes_t customScenesClusterClientAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_ATTRIBUTES()
};
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")>
PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t        customScenesCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd, removeAllScenesInd,
                                     storeSceneInd, recallSceneInd, getSceneMembershipInd,
                                     enhancedAddSceneInd, enhancedViewSceneInd, copySceneInd)                                  
};
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")>
PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t        customScenesClientCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_COMMANDS(addSceneResponseInd, viewSceneResponseInd,
      removeSceneResponseInd, removeAllScenesResponseInd, storeSceneResponseInd,
      getSceneMembershipResponseInd, enhancedAddSceneResponseInd,
      enhancedViewSceneResponseInd, copySceneResponseInd)                                     

};
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")>
Scene_t customSceneTable[MAX_SCENES_AMOUNT];
</#if>

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void customScenesClusterInit(void)
{
<#if (SCENES_CLUSTER_CS != "CLIENT")>
  memset(customSceneTable, 0, sizeof(Scene_t) * MAX_SCENES_AMOUNT);

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
      customSceneTable[i].free = true;

<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENECOUNT == true) >
  customScenesClusterServerAttributes.sceneCount.value   = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_CURRENTSCENE == true) >
  customScenesClusterServerAttributes.currentScene.value = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_CURRENTGROUP == true) >
  customScenesClusterServerAttributes.currentGroup.value = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEVALID == true) >
  customScenesClusterServerAttributes.sceneValid.value   = true;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SSNAMESUPPORT == true) >
  customScenesClusterServerAttributes.nameSupport.value  = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SCS_CLUSTERREVISION == true) >
  customScenesClusterServerAttributes.clusterVersion.value = SCENES_CLUSTER_VERSION;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENECOUNT == true) >
  /* Allocate space for global scene*/
  {
    Scene_t *scene = allocateScene(customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

    scene->sceneId = GLOBAL_SCENE_SCENE_ID;
    scene->groupId = GLOBAL_SCENE_GROUP_ID;
    customScenesClusterServerAttributes.sceneCount.value--; // to pass the certification
  }
</#if>
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, SCENES_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_CLUSTERREVISION == true) >
  customScenesClusterClientAttributes.clusterVersion.value = SCENES_CLUSTER_VERSION;
</#if>
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
</#if>
}

<#if (SCENES_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Invalidates scene
******************************************************************************/
void customScenesInvalidate(void)
{
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEVALID == true) >
  customScenesClusterServerAttributes.sceneValid.value = false;
</#if>
}

<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ADDSCENE == true) >
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
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ADD_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  status = processAddSceneCommand(false, addressing, payloadLength, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);
  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }
  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_VIEWSCENE == true) >
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
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_VIEW_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processViewSceneCommand(false, addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable);

  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload)
{
  ZCL_Status_t status;
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_ADD_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status =  processAddSceneCommand(true, addressing, payloadLength,(ZCL_AddScene_t *)payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
     PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }
  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload)
{
  ZCL_Status_t status;
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_VIEW_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processViewSceneCommand(true, addressing, (ZCL_ViewScene_t *)payload,  APP_ENDPOINT_CUSTOM, customSceneTable);
  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENE == true) >
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
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REMOVE_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processRemoveSceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);
  }

  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENEALL == true) >
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
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REMOVE_ALL_SCENES;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processRemoveAllScenesCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes.sceneCount.value);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true) >
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
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STORE_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processStoreSceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_RECALLSCENE == true) >
/**************************************************************************//**
\brief Callback on receiving Recall Scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_RECALL_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  if (recallScene(payload, APP_ENDPOINT_CUSTOM, customSceneTable, &customScenesClusterServerAttributes))
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEM == true) >
/**************************************************************************//**
\brief Callback on receiving Get Scenes Membership command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload)
{
  ZCL_Status_t status;
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_GET_SCENE_MEMBERSHIP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  status = processGetSceneMembershipCommand(addressing, payload, APP_ENDPOINT_CUSTOM, customSceneTable, customScenesClusterServerAttributes.sceneCount.value);
  APP_Zigbee_Handler(event);
  return status;
}

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true) >
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
<#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")>
      scene->onOff = onOffState();
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")>
      scene->currentLevel = levelControlCurrentLevel();
<#else>
      scene->currentLevel = 0;
</#if>
      /* NEED TO BE IMPLEMNETD*/


<#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >
      scene->colorMode = (ZCL_ZllEnhancedColorMode_t)customColorControlClusterServerAttributes.colorMode.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
      scene->currentX = customColorControlClusterServerAttributes.currentX.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
      scene->currentY = customColorControlClusterServerAttributes.currentY.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
      scene->enhancedCurrentHue = customColorControlClusterServerAttributes.enhancedCurrentHue.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
      scene->currentSaturation = customColorControlClusterServerAttributes.currentSaturation.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >
      scene->colorLoopActive = customColorControlClusterServerAttributes.colorLoopActive.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
      scene->colorLoopDirection = customColorControlClusterServerAttributes.colorLoopDirection.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
      scene->colorLoopTime = customColorControlClusterServerAttributes.colorLoopTime.value;
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
      scene->colorTemperature = customColorControlClusterServerAttributes.colorTemperature.value;
</#if>

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

</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENE == true) >
/**************************************************************************//**
\brief Callback on receive of Copy Scene command
******************************************************************************/
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,
                                 ZCL_CopyScene_t *payload)
{
  ZCL_Status_t status;
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_COPY_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  status = processCopySceneCommand(addressing, payload, APP_ENDPOINT_CUSTOM,
                                   customSceneTable, &customScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(APP_CUSTOM_SCENES_MEM_ID);

  APP_Zigbee_Handler(event);
  return status;
}
</#if>
</#if>

<#if (SCENES_CLUSTER_CS != "SERVER")>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENERESP == true) >
/**************************************************************************//**
\brief Callback on receive of Add Scene Response command
\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ADD_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_VIEWSCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of View Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_VIEW_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of Remove Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REMOVE_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENEALLRES == true) >
/**************************************************************************//**
\brief Callback on receive of Remove All Scenes Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REMOVE_ALL_SCENES_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_STORESCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of Store Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STORE_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_SCENEMEMRES == true) >
/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_GET_SCENE_MEMBERSHIP_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDADDSCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_ADD_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDVIEWSCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene Response command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewSceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_VIEW_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_COPYSCENERES == true) >
/**************************************************************************//**
\brief Callback on receive of Copy Scene Response command
******************************************************************************/
static ZCL_Status_t copySceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopySceneResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_COPY_SCENE_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
</#if>
#endif // #if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE
//eof customScenesCluster.c
