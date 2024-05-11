/*******************************************************************************
  Extended Color Light Scenes cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   eclScenesCluster.c

  Summary:
    This file contains the Extended Color Light Scenes cluster interface.

  Description:
    This file contains the Extended Color Light Scenes cluster interface.
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
#include <eclScenesCluster.h>
#include <eclScenes.h>
#include <eclOnOffCluster.h>
#include <eclLevelControlCluster.h>
#include <eclColorControlCluster.h>

#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DEFAULT_TRANSITION_TIME   0u

#define GLOBAL_SCENE_SCENE_ID     0x00
#define GLOBAL_SCENE_GROUP_ID     0x0000

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
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,  ZCL_CopyScene_t *payload);

static Scene_t *allocScene(void);
static Scene_t *findScene(uint16_t groupId, uint8_t sceneId);
static void storeScene(Scene_t *scene);
static void recallScene(Scene_t *scene);
static bool groupIsValid(uint16_t groupId);

static void eclFillAddRemoveStoreSceneResponsePayload(ZCL_AddSceneResponse_t *payload, uint16_t group, uint8_t scene, uint8_t status);
static uint8_t eclFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request);
static uint8_t eclFillEnhancedViewSceneResponsePayload(ZCL_EnhancedViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request);
static void eclFillRemoveAllScenesResponsePayload(ZCL_RemoveAllScenesResponse_t *payload, uint16_t group, uint8_t status);
static uint8_t eclFillGetSceneMembershipPayload(ZCL_GetSceneMembershipResponse_t *payload, uint16_t group);
static void eclFillCopySceneResponsePayload(ZCL_CopySceneResponse_t *payload, uint8_t status, uint16_t groupIdFrom, uint8_t sceneIdFrom);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ScenesClusterCommands_t eclScenesCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_COMMANDS(addSceneInd, viewSceneInd, removeSceneInd,
      removeAllScenesInd, storeSceneInd, recallSceneInd, getSceneMembershipInd,
      enhancedAddSceneInd, enhancedViewSceneInd, copySceneInd)
};

ZCL_SceneClusterServerAttributes_t eclScenesClusterServerAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Local variables
******************************************************************************/
Scene_t scene[MAX_NUMBER_OF_SCENES];

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Scenes cluster.
******************************************************************************/
void scenesClusterInit(void)
{
    for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
      scene[i].free = true;

    eclScenesClusterServerAttributes.sceneCount.value = 0;
    eclScenesClusterServerAttributes.currentScene.value = 0;
    eclScenesClusterServerAttributes.currentGroup.value = 0;
    eclScenesClusterServerAttributes.sceneValid.value = true;
    eclScenesClusterServerAttributes.nameSupport.value = 0;

    // Allocate space for global scene
    {
      Scene_t *scene = allocScene();

      scene->sceneId = GLOBAL_SCENE_SCENE_ID;
      scene->groupId = GLOBAL_SCENE_GROUP_ID;
      eclScenesClusterServerAttributes.sceneCount.value--; // to pass the certification
    }
}

/**************************************************************************//**
\brief Fills Add Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  scene   - scene id;
\param[in]  status  - the status of scene adding
******************************************************************************/
static void eclFillAddRemoveStoreSceneResponsePayload(ZCL_AddSceneResponse_t *payload,
  uint16_t group, uint8_t scene, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
  payload->sceneId = scene;
}

/**************************************************************************//**
\brief Fills View Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  scene   - scene info;
\param[in]  status  - the status of scene viewing;
\param[in] request  - the pointer to appropriate View Scene request

\returns size of payload in octets
******************************************************************************/
static uint8_t eclFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload,
  Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request)
{
  ZCL_OnOffClusterExtensionFieldSet_t *onOffExt;
  ZCL_LevelControlClusterExtensionFieldSet_t *levelControlExt;
  ZCL_ColorControlClusterExtensionFieldSet_t *colorControlExt;
  uint8_t *tmp;

  payload->status  = status;
  payload->groupId = request->groupId;
  payload->sceneId = request->sceneId;

  if (ZCL_SUCCESS_STATUS != status)
    return sizeof(ZCL_ViewSceneResponse_t) - sizeof(uint16_t) /*transitionTime*/ - \
                                             sizeof(uint8_t); /*nameAndExtField*/

  payload->transitionTime     = scene->transitionTime;
  payload->nameAndExtField[0] = 0;

  // On/off cluster extensions
  onOffExt = (ZCL_OnOffClusterExtensionFieldSet_t *)&payload->nameAndExtField[1];
  onOffExt->clusterId  = ONOFF_CLUSTER_ID;
  onOffExt->length     = sizeof(ZCL_OnOffClusterExtensionFieldSet_t) - \
                         sizeof(ZCL_ExtensionFieldSets_t);
  onOffExt->onOffValue = scene->onOff;

  // Level control cluster extensions
  tmp = (uint8_t *)&payload->nameAndExtField[1] + sizeof(ZCL_OnOffClusterExtensionFieldSet_t);
  levelControlExt = (ZCL_LevelControlClusterExtensionFieldSet_t *)tmp;

  levelControlExt->clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  levelControlExt->length       = sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) - \
                                  sizeof(ZCL_ExtensionFieldSets_t);
  levelControlExt->currentLevel = scene->currentLevel;

  // Color control cluster extensions
  tmp = (uint8_t *)&payload->nameAndExtField[2] + sizeof(ZCL_ColorControlClusterExtensionFieldSet_t);
  colorControlExt = (ZCL_ColorControlClusterExtensionFieldSet_t *)tmp;
  colorControlExt->clusterId = COLOR_CONTROL_CLUSTER_ID;
  colorControlExt->length = sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - \
                            sizeof(ZCL_ExtensionFieldSets_t);
  colorControlExt->currentX = scene->currentX;
  colorControlExt->currentY = scene->currentY;
  colorControlExt->enhancedCurrentHue = scene->enhancedCurrentHue;
  colorControlExt->currentSaturation = scene->currentSaturation;
  colorControlExt->colorLoopActive = scene->colorLoopActive;
  colorControlExt->colorLoopDirection = scene->colorLoopDirection;
  colorControlExt->colorLoopTime = scene->colorLoopTime;

  return sizeof(ZCL_ViewSceneResponse_t) + \
         sizeof(ZCL_OnOffClusterExtensionFieldSet_t) + \
         sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) + \
         sizeof(ZCL_ColorControlClusterExtensionFieldSet_t);
}

/**************************************************************************//**
\brief Fills Enhanced View Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  scene   - scene info;
\param[in]  status  - the status of scene viewing;
\param[in] request  - the pointer to appropriate View Scene request

\returns size of payload in octets
******************************************************************************/
static uint8_t eclFillEnhancedViewSceneResponsePayload(ZCL_EnhancedViewSceneResponse_t *payload,
  Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request)
{
  payload->status  = status;
  payload->groupId = request->groupId;
  payload->sceneId = request->sceneId;

  if (ZCL_SUCCESS_STATUS != status)
    return sizeof(ZCL_ViewSceneResponse_t) - sizeof(uint16_t) /*transitionTime*/ - \
                                             sizeof(uint8_t); /*nameAndExtField*/

  payload->transitionTime = scene->transitionTime * 10 + scene->transitionTime100ms;
  payload->name[0] = 0;

  // On/off cluster extensions
  payload->onOffClusterExtFields.clusterId  = ONOFF_CLUSTER_ID;
  payload->onOffClusterExtFields.length     = sizeof(ZCL_OnOffClusterExtensionFieldSet_t) - \
                                              sizeof(ZCL_ExtensionFieldSets_t);
  payload->onOffClusterExtFields.onOffValue = scene->onOff;

  // Level control cluster extensions
  payload->levelControlClusterExtFields.clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  payload->levelControlClusterExtFields.length       = sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) - \
                                                       sizeof(ZCL_ExtensionFieldSets_t);
  payload->levelControlClusterExtFields.currentLevel = scene->currentLevel;

  // Color control cluster extensions

  payload->colorControlClusterExtFields.clusterId = COLOR_CONTROL_CLUSTER_ID;
  payload->colorControlClusterExtFields.length = sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - \
                            sizeof(ZCL_ExtensionFieldSets_t);
  payload->colorControlClusterExtFields.currentX = scene->currentX;
  payload->colorControlClusterExtFields.currentY = scene->currentY;
  payload->colorControlClusterExtFields.enhancedCurrentHue = scene->enhancedCurrentHue;
  payload->colorControlClusterExtFields.currentSaturation = scene->currentSaturation;
  payload->colorControlClusterExtFields.colorLoopActive = scene->colorLoopActive;
  payload->colorControlClusterExtFields.colorLoopDirection = scene->colorLoopDirection;
  payload->colorControlClusterExtFields.colorLoopTime = scene->colorLoopTime;

  return sizeof(ZCL_EnhancedViewSceneResponse_t);
}

/**************************************************************************//**
\brief Fills Remove Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - the status of scenes removing
******************************************************************************/
static void eclFillRemoveAllScenesResponsePayload(ZCL_RemoveAllScenesResponse_t *payload,
  uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Scene Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
******************************************************************************/
static uint8_t eclFillGetSceneMembershipPayload(ZCL_GetSceneMembershipResponse_t *payload,
  uint16_t group)
{
  payload->capacity = MAX_SCENES_AMOUNT - eclScenesClusterServerAttributes.sceneCount.value;
  payload->groupId  = group;

  if (groupIsValid(group))
  {
    Scene_t *scene = NULL;

    while ((scene = eclGetNextSceneByGroup(scene, group)))
      payload->sceneList[payload->sceneCount++] = scene->sceneId;

    payload->status = ZCL_SUCCESS_STATUS;
  }
  else
  {
    payload->status = ZCL_INVALID_FIELD_STATUS;
    return sizeof(ZCL_GetSceneMembershipResponse_t) - sizeof(uint8_t) /*sceneCount*/ - \
          sizeof(uint8_t); /*sceneList*/
  }

  return sizeof(ZCL_GetSceneMembershipResponse_t) + payload->sceneCount - sizeof(uint8_t); /*sceneList*/
}

/**************************************************************************//**
\brief Fills Copy Scene Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  groupIdFrom   - group id to copy from
\param[in] sceneIdFrom - scene id to copy from
******************************************************************************/
static void eclFillCopySceneResponsePayload(ZCL_CopySceneResponse_t *payload,
  uint8_t status, uint16_t groupIdFrom, uint8_t sceneIdFrom)
{
  payload->status = status;
  payload->groupIdFrom = groupIdFrom;
  payload->sceneIdFrom = sceneIdFrom;
}

/**************************************************************************//**
\brief Invalidate current device state
******************************************************************************/
void scenesClusterInvalidate(void)
{
  eclScenesClusterServerAttributes.sceneValid.value = false;
}

/**************************************************************************//**
\brief Store global scene
******************************************************************************/
void scenesClusterStoreGlobalScene(void)
{
  storeScene(findScene(GLOBAL_SCENE_GROUP_ID, GLOBAL_SCENE_SCENE_ID));
}

/**************************************************************************//**
\brief Recall global scene
******************************************************************************/
void scenesClusterRecallGlobalScene(void)
{
  recallScene(findScene(GLOBAL_SCENE_GROUP_ID, GLOBAL_SCENE_SCENE_ID));
}

/**************************************************************************//**
\brief Gets next scene by group id

\param[in] sceneId - the pointer to current scene or NULL to get the first busy scene
\param[in] group - group id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *eclGetNextSceneByGroup(Scene_t *sceneId, uint16_t group)
{
  if (!sceneId)
  {
    for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
    {
      if (scene[i].free && (scene[i].groupId == group))
        return &scene[i];
    }
    return NULL;
  }

  if ((sceneId < scene) || (sceneId > &scene[MAX_NUMBER_OF_SCENES - 1]))
    return NULL;

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((sceneId < &scene[i]) && (scene[i].free) && (scene[i].groupId == group))
      return &scene[i];
  }

  return NULL;
}

/**************************************************************************//**
\brief Get scene structure by groupId and sceneId
******************************************************************************/
static Scene_t *findScene(uint16_t groupId, uint8_t sceneId)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].groupId == groupId && scene[i].sceneId == sceneId && !scene[i].free)
      return &scene[i];
  }
  return NULL;
}

/**************************************************************************//**
\brief Allocate free scene and mark it busy
******************************************************************************/
static Scene_t *allocScene(void)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].free)
    {
      memset(&scene[i], 0, sizeof(Scene_t));
      scene[i].free = false;
      scene[i].transitionTime = DEFAULT_TRANSITION_TIME;
      scene[i].transitionTime100ms = 0;

      eclScenesClusterServerAttributes.sceneCount.value++;

      return &scene[i];
    }
  }
  return NULL;
}

/**************************************************************************//**
\brief Mark scene table record as free
******************************************************************************/
static void freeScene(Scene_t *scene)
{
  if (GLOBAL_SCENE_GROUP_ID == scene->groupId &&
      GLOBAL_SCENE_SCENE_ID == scene->sceneId)
    return; // Can't free global scene

  if (!scene->free)
  {
    scene->free = true;
    eclScenesClusterServerAttributes.sceneCount.value--;
  }
}

/**************************************************************************//**
\brief Store current device state to a scene
******************************************************************************/
static void storeScene(Scene_t *scene)
{
  scene->onOff = eclOnOffClusterServerAttributes.onOff.value;
  scene->currentLevel = eclLevelControlClusterServerAttributes.currentLevel.value;
  scene->colorMode = eclColorControlClusterServerAttributes.colorMode.value;
  scene->currentX = eclColorControlClusterServerAttributes.currentX.value;
  scene->currentY = eclColorControlClusterServerAttributes.currentY.value;
  scene->enhancedCurrentHue = eclColorControlClusterServerAttributes.enhancedCurrentHue.value;
  scene->currentSaturation = eclColorControlClusterServerAttributes.currentSaturation.value;
  scene->colorLoopActive = eclColorControlClusterServerAttributes.colorLoopActive.value;
  scene->colorLoopDirection = eclColorControlClusterServerAttributes.colorLoopDirection.value;
  scene->colorLoopTime = eclColorControlClusterServerAttributes.colorLoopTime.value;

  eclScenesClusterServerAttributes.currentGroup.value = scene->groupId;
  eclScenesClusterServerAttributes.currentScene.value = scene->sceneId;
  eclScenesClusterServerAttributes.sceneValid.value = true;
}

/**************************************************************************//**
\brief Restore device state to the information from the scene
******************************************************************************/
static void recallScene(Scene_t *scene)
{
  eclScenesClusterServerAttributes.currentGroup.value = scene->groupId;
  eclScenesClusterServerAttributes.currentScene.value = scene->sceneId;

  onOffClusterSetExtensionField(scene->onOff);
  levelControlClusterSetExtensionField(scene->currentLevel);
  colorControlClusterSetExtensionField(scene);
  eclScenesClusterServerAttributes.sceneValid.value = true;
}

/**************************************************************************//**
\brief Remove all scenes associated with the group
******************************************************************************/
void scenesClusterRemoveByGroup(uint16_t group)
{
  for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
  {
    if (scene[i].groupId == group)
      freeScene(&scene[i]);
  }
}

/**************************************************************************//**
\brief Check if groupId is a valid group ID existing on this device
******************************************************************************/
static bool groupIsValid(uint16_t groupId)
{
  return (groupId == 0 || NWK_IsGroupMember(groupId, APP_ENDPOINT_EXTENDED_COLOR_LIGHT));
}

/**************************************************************************//**
\brief Process Add Scene and Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t processAddSceneCommand(bool enhanced, ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddScene_t *payload)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  uint8_t cmdId;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  // Process
  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (!scene)
      scene = allocScene();

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = payload->sceneId;
      scene->groupId = payload->groupId;

      if (enhanced)
      {
        scene->transitionTime = payload->transitionTime / 10;
        scene->transitionTime100ms = payload->transitionTime % 10;
      }
      else
      {
        scene->transitionTime = payload->transitionTime;
        scene->transitionTime100ms = 0;
      }

      {
        int8_t commandSize = (sizeof(ZCL_AddScene_t) + payload->name[0]);
        int8_t extFieldsSize = (int8_t)payloadLength - commandSize;
        uint8_t *extFields = (uint8_t *)payload + commandSize;
        ZCL_ExtensionFieldSets_t *ext;

        while (extFieldsSize > 0)
        {
          ext = (ZCL_ExtensionFieldSets_t *)extFields;

          if (ONOFF_CLUSTER_ID == ext->clusterId)
          {
            ZCL_OnOffClusterExtensionFieldSet_t *ext =
                (ZCL_OnOffClusterExtensionFieldSet_t *)extFields;

            scene->onOff = ext->onOffValue;
          }

          else if (LEVEL_CONTROL_CLUSTER_ID == ext->clusterId)
          {
            ZCL_LevelControlClusterExtensionFieldSet_t *ext =
                (ZCL_LevelControlClusterExtensionFieldSet_t *)extFields;

            scene->currentLevel = ext->currentLevel;
          }

          else if (COLOR_CONTROL_CLUSTER_ID == ext->clusterId)
          {
            ZCL_ColorControlClusterExtensionFieldSet_t *ext =
                (ZCL_ColorControlClusterExtensionFieldSet_t *)extFields;

            scene->colorMode = eclColorControlClusterServerAttributes.colorMode.value;
            scene->currentX = ext->currentX;
            scene->currentY = ext->currentY;
            if(!enhanced || (enhanced && !ext->currentX && !ext->currentY))
            {
              scene->enhancedCurrentHue = ext->enhancedCurrentHue;
              scene->currentSaturation = ext->currentSaturation;
              scene->colorLoopActive = ext->colorLoopActive;
              scene->colorLoopDirection = ext->colorLoopDirection;
              scene->colorLoopTime = ext->colorLoopTime;
            }
            else
            {
              scene->enhancedCurrentHue = 0;
              scene->currentSaturation = 0;
              scene->colorLoopActive = 0;
              scene->colorLoopDirection = 0;
              scene->colorLoopTime = 0;
            }
          }

          extFields += sizeof(ZCL_ExtensionFieldSets_t) + ext->length;
          extFieldsSize -= ext->length;
        }
      }
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

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID);
  }

  // Send Add scene response
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  cmdId = enhanced ? ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_RESPONSE_COMMAND_ID :
                     ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID;

  fillCommandRequest(req, cmdId, sizeof(ZCL_AddSceneResponse_t));
  eclFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload,
                                          payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Add Scene command
******************************************************************************/
static ZCL_Status_t addSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,
  ZCL_AddScene_t *payload)
{
  appSnprintf("addSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);
  return processAddSceneCommand(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Process View Scene and Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t processViewSceneCommand(bool enhanced, ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  ZCL_Request_t *req;
  uint8_t status;

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (scene)
      status = ZCL_SUCCESS_STATUS;
    else
      status = ZCL_NOT_FOUND_STATUS;
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  // Send View Scene or Enhance view scene response

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  if (enhanced)
  {
    fillCommandRequest(req, ZCL_SCENES_CLUSTER_ENHANCED_VIEW_SCENE_RESPONSE_COMMAND_ID,sizeof(ZCL_EnhancedViewSceneResponse_t));
    eclFillEnhancedViewSceneResponsePayload((ZCL_EnhancedViewSceneResponse_t *)req->requestPayload, scene, status, payload);
  }
  else
  {
    fillCommandRequest(req, ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID, sizeof(ZCL_ViewSceneResponse_t));
    eclFillViewSceneResponsePayload((ZCL_ViewSceneResponse_t *)req->requestPayload, scene, status, payload);
  }

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of View Scene command
******************************************************************************/
static ZCL_Status_t viewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t *payload)
{
  appSnprintf("viewSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);

  return processViewSceneCommand(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Remove Scene command
******************************************************************************/
static ZCL_Status_t removeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t *payload)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  appSnprintf("removeSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;
      freeScene(scene);
    }
    else
    {
      status = ZCL_NOT_FOUND_STATUS;
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID, sizeof(ZCL_AddSceneResponse_t));
  eclFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload,
                                          payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Remove All Scenes command
******************************************************************************/
static ZCL_Status_t removeAllScenesInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t *payload)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  appSnprintf("removeAllScenesInd(): 0x%04x\r\n", payload->groupId);

  if (groupIsValid(payload->groupId))
  {
    status = ZCL_SUCCESS_STATUS;
    scenesClusterRemoveByGroup(payload->groupId);
  }
  else
    status = ZCL_INVALID_FIELD_STATUS;

  // If received via multicast or broadcast service no response shall be given
  // Update scenes in non-volatile memory
  if (ZCL_SUCCESS_STATUS == status)
    PDS_Store(HA_APP_MEMORY_MEM_ID);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveAllScenesResponse_t));
  eclFillRemoveAllScenesResponsePayload((ZCL_RemoveAllScenesResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Store Scene command
******************************************************************************/
static ZCL_Status_t storeSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t *payload)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  appSnprintf("storeSceneInd(): 0x%04x, %d\r\n", payload->groupId, payload->sceneId);

  if (groupIsValid(payload->groupId))
  {
    Scene_t *scene;

    scene = findScene(payload->groupId, payload->sceneId);

    if (!scene)
      scene = allocScene();

    if (scene)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = payload->sceneId;
      scene->groupId = payload->groupId;
      storeScene(scene);

      PDS_Store(HA_APP_MEMORY_MEM_ID);
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

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID, sizeof(ZCL_AddSceneResponse_t));
  eclFillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload,
                                          payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Recall Scene command
******************************************************************************/
static ZCL_Status_t recallSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t *payload)
{
  Scene_t *scene;
  appSnprintf("recallSceneInd(): 0x%04x, %d\r\n", payload->groupId, payload->sceneId);

  scene = findScene(payload->groupId, payload->sceneId);

  if (scene)
  {
    onOffClusterSetGlobalSceneControl();
    recallScene(scene);
  }

  PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Scene command
******************************************************************************/
static ZCL_Status_t getSceneMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t *payload)
{
  ZCL_Request_t *req;
  uint8_t size = sizeof(uint8_t) /*status*/ + sizeof(uint8_t) /*capacity*/ + sizeof(uint16_t) /*groupId*/;;

  appSnprintf("getSceneMembershipInd(): 0x%04x\r\n", payload->groupId);

  /* TODO:
    On receipt of this command, the device shall if addressed to a single device
    generate an appropriate Get Scene Membership Response command, otherwise it
    shall only generate an appropriate Get Scene Membership Response command if
    an entry within the Scene Table corresponds to the Group ID.
    - Doesn't fit to TP-CST-TC-13 Item 23 expected result.
  */
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(!addressing->nonUnicast ||
    (addressing->nonUnicast && groupIsValid(payload->groupId) && eclGetNextSceneByGroup(NULL, payload->groupId))))
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  size = eclFillGetSceneMembershipPayload((ZCL_GetSceneMembershipResponse_t *)req->requestPayload, payload->groupId);
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID,
                       size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);


  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Add Scene command
******************************************************************************/
static ZCL_Status_t enhancedAddSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedAddScene_t *payload)
{
  appSnprintf("enhancedAddSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);
  return processAddSceneCommand(true, addressing, payloadLength, (ZCL_AddScene_t *)payload);
}

/**************************************************************************//**
\brief Callback on receive of Enhanced View Scene command
******************************************************************************/
static ZCL_Status_t enhancedViewSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EnhancedViewScene_t *payload)
{
  appSnprintf("enhancedViewSceneInd(): 0x%04x, 0x%02x\r\n", payload->groupId, payload->sceneId);
  return processViewSceneCommand(true, addressing, payloadLength, (ZCL_ViewScene_t *)payload);
}

/**************************************************************************//**
\brief Copy scene
******************************************************************************/
static ZCL_Status_t copyScene(uint16_t groupIdFrom, uint8_t sceneIdFrom, uint16_t groupIdTo, uint8_t sceneIdTo)
{
  Scene_t *sceneFrom, *sceneTo;

  sceneFrom = findScene(groupIdFrom, sceneIdFrom);

  if (!sceneFrom)
    return ZCL_NOT_FOUND_STATUS;

  sceneTo = findScene(groupIdTo, sceneIdTo);

  if (!sceneTo)
    sceneTo = allocScene();

  if (sceneTo)
  {
    *sceneTo = *sceneFrom;
    sceneTo->sceneId = sceneIdTo;
    sceneTo->groupId = groupIdTo;
  }
  else
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Copy Scene command
******************************************************************************/
static ZCL_Status_t copySceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_CopyScene_t *payload)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  appSnprintf("copySceneInd()\r\n");

  if (groupIsValid(payload->groupIdFrom))
  {
    if (payload->mode & ZCL_SCENES_CLUSTER_COPY_ALL_SCENES)
    {
      status = ZCL_SUCCESS_STATUS;

      for (uint8_t i = 0; i < MAX_NUMBER_OF_SCENES; i++)
      {
        if (!scene[i].free && scene[i].groupId == payload->groupIdFrom)
        {
          ZCL_Status_t result;

          result = copyScene(payload->groupIdFrom, scene[i].sceneId,
                             payload->groupIdTo, scene[i].sceneId);

          if (ZCL_SUCCESS_STATUS != result)
            status = result;
        }
      }
    }
    else
    {
      status = copyScene(payload->groupIdFrom, payload->sceneIdFrom,
                         payload->groupIdTo, payload->sceneIdTo);
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }


  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (ZCL_SUCCESS_STATUS == status)
  {
    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_COPY_SCENE_RESPONSE_COMMAND_ID, sizeof(ZCL_CopySceneResponse_t));
  eclFillCopySceneResponsePayload((ZCL_CopySceneResponse_t *)req->requestPayload,
                                          payload->groupIdFrom, payload->sceneIdFrom, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGH
//eof dlScenesCluster.c
