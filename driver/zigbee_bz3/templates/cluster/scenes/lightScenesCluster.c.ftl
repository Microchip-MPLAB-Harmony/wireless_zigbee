/*******************************************************************************
  Light Scenes cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    lightScenesCluster.c

  Summary:
    This file contains the Light Scenes cluster interface.

  Description:
    This file contains the Light Scenes cluster interface.
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

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>
#include <z3device/light/include/lightScenesCluster.h>
#include <zcl/clusters/include/scenes.h>
#include <z3device/light/include/lightOnOffCluster.h>
#include <z3device/light/include/lightLevelControlCluster.h>
#include <z3device/light/include/lightColorControlCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/light/include/light.h>
#include <z3device/clusters/include/scenesCluster.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/app_zigbee_handler.h>
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
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_SceneClusterServerAttributes_t lightScenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};
PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t        lightScenesCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd, removeAllScenesInd,
                                     storeSceneInd, recallSceneInd, getSceneMembershipInd,
                                     enhancedAddSceneInd, enhancedViewSceneInd, copySceneInd)

};

Scene_t lightSceneTable[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void lightScenesClusterInit(void)
{
  (void)memset(lightSceneTable, 0, sizeof(Scene_t) * MAX_SCENES_AMOUNT);

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
      lightSceneTable[i].free = true;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENECOUNT == true) >
  lightScenesClusterServerAttributes.sceneCount.value   = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_CURRENTSCENE == true) >
  lightScenesClusterServerAttributes.currentScene.value = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_CURRENTGROUP == true) >
  lightScenesClusterServerAttributes.currentGroup.value = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEVALID == true) >
  lightScenesClusterServerAttributes.sceneValid.value   = true;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SSNAMESUPPORT == true) >
  lightScenesClusterServerAttributes.nameSupport.value  = 0;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SCS_CLUSTERREVISION == true) >
  lightScenesClusterServerAttributes.clusterVersion.value = SCENES_CLUSTER_VERSION;
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENECOUNT == true) >
  /* Allocate space for global scene*/
  {
    Scene_t *scene = allocateScene(lightSceneTable, &lightScenesClusterServerAttributes.sceneCount.value);

    scene->sceneId = GLOBAL_SCENE_SCENE_ID;
    scene->groupId = GLOBAL_SCENE_GROUP_ID;
    lightScenesClusterServerAttributes.sceneCount.value--; // to pass the certification
  }
</#if>
}

/**************************************************************************//**
\brief Invalidates scene
******************************************************************************/
void lightScenesInvalidate(void)
{
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEVALID == true) >
  lightScenesClusterServerAttributes.sceneValid.value = false;
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

  status = processAddSceneCommand(false, addressing, payloadLength, payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes.sceneCount.value);
  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
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

  status = processViewSceneCommand(false, addressing, payload, APP_ENDPOINT_LIGHT, lightSceneTable);

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
  status =  processAddSceneCommand(true, addressing, payloadLength,(ZCL_AddScene_t *)payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
     (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
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
  status = processViewSceneCommand(true, addressing, (ZCL_ViewScene_t *)payload,  APP_ENDPOINT_LIGHT, lightSceneTable);
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

  status = processRemoveSceneCommand(addressing, payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes.sceneCount.value);

  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
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
  status = processRemoveAllScenesCommand(addressing, payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes.sceneCount.value);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
  }
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
  status = processStoreSceneCommand(addressing, payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
  }
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
  ZCL_Status_t status;
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_RECALL_SCENE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  status = recallScene(payload, APP_ENDPOINT_LIGHT, lightSceneTable, &lightScenesClusterServerAttributes);
  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
  }
  APP_Zigbee_Handler(event);
  return status;
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

  status = processGetSceneMembershipCommand(addressing, payload, APP_ENDPOINT_LIGHT, lightSceneTable, lightScenesClusterServerAttributes.sceneCount.value);
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
ZCL_Status_t storeScene(ZCL_StoreScene_t *storeSceneReq, Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  ZCL_Status_t status;

  if (groupsIsValidGroup(storeSceneReq->groupId, srcEp))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(storeSceneReq->groupId, storeSceneReq->sceneId, scenePool);

    if (scene == NULL)
    {
      scene = allocateScene(scenePool, &scenesAttributes->sceneCount.value);
    }
    if (scene != NULL)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = storeSceneReq->sceneId;
      scene->groupId = storeSceneReq->groupId;

      scene->onOff = onOffState();
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
      scene->currentLevel = levelControlCurrentLevel();
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
      /* NEED TO BE IMPLEMNETD*/

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >
      scene->colorMode = (ZCL_ZllEnhancedColorMode_t)lightColorControlClusterServerAttributes.colorMode.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
      scene->currentX = lightColorControlClusterServerAttributes.currentX.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
      scene->currentY = lightColorControlClusterServerAttributes.currentY.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
      scene->enhancedCurrentHue = lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
      scene->currentSaturation = lightColorControlClusterServerAttributes.currentSaturation.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >
      scene->colorLoopActive = lightColorControlClusterServerAttributes.colorLoopActive.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
      scene->colorLoopDirection = lightColorControlClusterServerAttributes.colorLoopDirection.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
      scene->colorLoopTime = lightColorControlClusterServerAttributes.colorLoopTime.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
      scene->colorTemperature = lightColorControlClusterServerAttributes.colorTemperature.value;
</#if>
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
      scenesAttributes->currentGroup.value = scene->groupId;
      scenesAttributes->currentScene.value = scene->sceneId;
      scenesAttributes->sceneValid.value = true;
    }
    else
    {
      status = ZCL_INSUFFICIENT_SPACE_STATUS;
    }
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
  status = processCopySceneCommand(addressing, payload, APP_ENDPOINT_LIGHT,
                                   lightSceneTable, &lightScenesClusterServerAttributes);

  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
  {
    (void)PDS_Store(APP_LIGHT_SCENES_MEM_ID);
  }
  APP_Zigbee_Handler(event);
  return status;
}
</#if>

#endif // #if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
//eof lightScenesCluster.c
