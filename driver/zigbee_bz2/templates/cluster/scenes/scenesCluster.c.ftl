/*******************************************************************************
  Scenes Cluster File

  Company:
    Microchip Technology Inc.

  File Name:
    scenesCluster.c

  Summary:
    This file contains Scenes Cluster Implemenation.

  Description:
   This file contains Scenes Cluster Implemenation.
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

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>
#include <zcl/clusters/include/scenes.h>
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE
#include <z3device/custom/include/customOnOffCluster.h>
#include <z3device/custom/include/customLevelControlCluster.h>
#include <z3device/custom/include/customColorControlCluster.h>
#elif APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
#include <z3device/light/include/lightOnOffCluster.h>
#include <z3device/light/include/lightLevelControlCluster.h>
#include <z3device/light/include/lightColorControlCluster.h>
#endif
#include <zcl/include/zclCommandManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/clusters/include/scenesCluster.h>
#include <zcl/include/zclThermostatCluster.h>
#include <zcl/clusters/include/groupsCluster.h>
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
#include <z3device/thermostat/include/thScenesCluster.h>
#endif
/******************************************************************************
                    Prototypes section
******************************************************************************/

static void fillViewRemoveStoreRecallScenePayload(ZCL_ViewScene_t *payload, uint16_t group, uint8_t scene);
static void fillRecallScenePayload(ZCL_RecallScene_t *payload, uint16_t group, uint8_t scene, uint16_t time);

static void fillRemoveAllScenesGetSceneMembershipPayload(ZCL_RemoveAllScenes_t *payload, uint16_t group);

static void fillAddSceneToDimmableLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level);
static void fillAddSceneToThermostatPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time,
                                              int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode);
static void fillAddSceneToExtendedColorLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint16_t scene, uint16_t time,
                                                        bool onOff, uint8_t level, ZCL_ColorControlClusterExtensionFieldSet_t *ccExt);
static void fillCopyScenePayload(ZCL_CopyScene_t *payload, SceneMode_t mode, uint16_t gidFrom, uint16_t sidFrom, uint16_t gidTo, uint16_t sidTo);

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
static uint8_t thFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request);
#else
static uint8_t lightFillViewSceneResponsePayload(bool enhanced, ZCL_EnhancedViewSceneResponse_t *enhancedViewSceneResp,
  Scene_t *scene);
#endif

/******************************************************************************
                    Global variables section
******************************************************************************/

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Removes all scenes from scene table

\param[in] group - group id

\returns status of scene removing
******************************************************************************/
ZCL_Status_t removeAllScenes(uint16_t group, Endpoint_t srcEp, Scene_t* scenePool, uint8_t* currSceneCnt)
{
  if (groupsIsValidGroup(group, srcEp))
  {
    *currSceneCnt -= removeScenesByGroup(group, scenePool);
  }
  else
  {
    return ZCL_INVALID_FIELD_STATUS;
  }
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  scene   - scene id;
\param[in]  status  - the status of scene adding
******************************************************************************/
void fillAddRemoveStoreSceneResponsePayload(ZCL_AddSceneResponse_t *payload, uint16_t group, uint8_t scene, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
  payload->sceneId = scene;
}
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_VIEWSCENERES == true) >
#if (APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_THERMOSTAT)
/**************************************************************************//**
\brief Fills View Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  scene   - scene info;
\param[in]  status  - the status of scene viewing;
\param[in] request  - the pointer to appropriate View Scene request

\returns size of payload in octets
******************************************************************************/
static uint8_t lightFillViewSceneResponsePayload(bool enhanced , ZCL_EnhancedViewSceneResponse_t *enhancedViewSceneResp,
  Scene_t *scene)
{
  uint8_t size = 0;

  enhancedViewSceneResp->name[0] = 0;

  if (enhanced)
  {/* The Transition Time (measured in tenths of a second) SHALL be calculated
    * from the standard transition time field of the scene table entry
    * (measured in seconds) and the new TransitionTime100ms field. */
    enhancedViewSceneResp->transitionTime = (uint16_t)(scene->transitionTime * 10U + scene->transitionTime100ms);
  }
  else
  {/* For View Scene Response, transitionTime is given as 1 second per unit */
    enhancedViewSceneResp->transitionTime = scene->transitionTime;
  }

  /* Add On/off cluster extension fields */
  enhancedViewSceneResp->onOffClusterExtFields.clusterId = ONOFF_CLUSTER_ID;
  enhancedViewSceneResp->onOffClusterExtFields.length = sizeof(ZCL_OnOffClusterExtensionFieldSet_t) -
                                                          sizeof(ZCL_ExtensionFieldSets_t);

  enhancedViewSceneResp->onOffClusterExtFields.onOffValue = scene->onOff;
  /* Done adding On/off cluster extension fields */

  /* Update the total payload size after On/Off extension fields addition */
  size = sizeof(ZCL_EnhancedViewSceneResponse_t)
          - sizeof(uint8_t) /* status */ - sizeof(uint16_t) /* groupId */ - sizeof(uint8_t) /* sceneId */
          - sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) /* no Level control extensions */
          - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t); /* no Color control extensions */

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
  /* Add Level control cluster extension fields */
  enhancedViewSceneResp->levelControlClusterExtFields.clusterId = LEVEL_CONTROL_CLUSTER_ID;
  enhancedViewSceneResp->levelControlClusterExtFields.length =
    sizeof(ZCL_LevelControlClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);

  enhancedViewSceneResp->levelControlClusterExtFields.currentLevel = scene->currentLevel;
  /* Done adding level control cluster extension fields */

  /* Update the total payload size after level control extension fields addition */
  size = sizeof(ZCL_EnhancedViewSceneResponse_t)
           - sizeof(uint8_t) /* status */ - sizeof(uint16_t) /* groupId */ - sizeof(uint8_t) /* sceneId */
           - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t); /* no Color control extensions */
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  enhancedViewSceneResp->colorControlClusterExtFields.clusterId = COLOR_CONTROL_CLUSTER_ID;
  enhancedViewSceneResp->colorControlClusterExtFields.length =
    sizeof(ZCL_ExtensionFieldSets_t) + 2U * sizeof(uint16_t);
  enhancedViewSceneResp->colorControlClusterExtFields.currentX = scene->currentX;
  enhancedViewSceneResp->colorControlClusterExtFields.currentY = scene->currentY;
  size = sizeof(ZCL_EnhancedViewSceneResponse_t)
         - sizeof(uint8_t) /* status */ - sizeof(uint16_t) /* groupId */ - sizeof(uint8_t) /* sceneId */
         - sizeof(ZCL_ColorControlClusterExtensionFieldSet_t)
         + sizeof(ZCL_ExtensionFieldSets_t)
         + 2U * sizeof(uint16_t);
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
  if (enhanced)
  {
    enhancedViewSceneResp->colorControlClusterExtFields.length =
      sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);
    enhancedViewSceneResp->colorControlClusterExtFields.enhancedCurrentHue = scene->enhancedCurrentHue;
    enhancedViewSceneResp->colorControlClusterExtFields.currentSaturation = scene->currentSaturation;
    enhancedViewSceneResp->colorControlClusterExtFields.colorLoopActive = scene->colorLoopActive;
    enhancedViewSceneResp->colorControlClusterExtFields.colorLoopDirection = scene->colorLoopDirection;
    enhancedViewSceneResp->colorControlClusterExtFields.colorLoopTime = scene->colorLoopTime;
    enhancedViewSceneResp->colorControlClusterExtFields.colorTemperature = scene->colorTemperature;
    size = sizeof(ZCL_EnhancedViewSceneResponse_t)
           - sizeof(uint8_t) /* status */ - sizeof(uint16_t) /* groupId */ - sizeof(uint8_t) /* sceneId */;
  }
#endif // (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)

  return size;

}
#endif


#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
/**************************************************************************//**
\brief Fills View Scene Response command structure for Thermostat

\param[out] payload - pointer to command structure;
\param[in]  scene   - scene info;
\param[in]  status  - the status of scene viewing;
\param[in] request  - the pointer to appropriate View Scene request

\returns size of payload in octets
******************************************************************************/
static uint8_t thFillViewSceneResponsePayload(ZCL_ViewSceneResponse_t *payload, Scene_t *scene, uint8_t status, ZCL_ViewScene_t *request)
{
  ZCL_ThermostatClusterExtensionFieldSet_t    *thermostatExt;

  payload->status  = status;
  payload->groupId = request->groupId;
  payload->sceneId = request->sceneId;

  if (ZCL_SUCCESS_STATUS != status)
    return sizeof(ZCL_ViewSceneResponse_t) - sizeof(uint16_t) /*transitionTime*/ - sizeof(uint8_t); /*nameAndExtField*/

  payload->transitionTime     = scene->transitionTime;
  payload->nameAndExtField[0] = 0;

  thermostatExt = (ZCL_ThermostatClusterExtensionFieldSet_t *)&payload->nameAndExtField[1];

  thermostatExt->clusterId  = THERMOSTAT_CLUSTER_ID;
  thermostatExt->length     = sizeof(ZCL_ThermostatClusterExtensionFieldSet_t) - sizeof(ZCL_ExtensionFieldSets_t);
  thermostatExt->occupiedCoolingSetpoint = scene->occupiedCoolingSetpoint;
  thermostatExt->occupiedHeatingSetpoint = scene->occupiedHeatingSetpoint;
  thermostatExt->systemMode              = scene->systemMode;

  return sizeof(ZCL_ViewSceneResponse_t) + sizeof(ZCL_ThermostatClusterExtensionFieldSet_t);
}
#endif
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENEALLRES == true) >
/**************************************************************************//**
\brief Fills Remove Scene Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - the status of scenes removing
******************************************************************************/
void fillRemoveAllScenesResponsePayload(ZCL_RemoveAllScenesResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEMRES == true) >
/**************************************************************************//**
\brief Fills Get Scene Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
******************************************************************************/
uint8_t fillGetSceneMembershipPayload(ZCL_GetSceneMembershipResponse_t *payload, Scene_t* scenePool, uint16_t group, Endpoint_t srcEp, uint8_t currSceneCnt)
{
  uint8_t size = sizeof(uint8_t) /*status*/ + sizeof(uint8_t) /*capacity*/ + sizeof(uint16_t) /*groupId*/;;
  payload->capacity = MAX_SCENES_AMOUNT - currSceneCnt;//dlScenesClusterServerAttributes.sceneCount.value;
  payload->groupId  = group;
  payload->sceneCount = 0;

  if (groupsIsValidGroup(payload->groupId, srcEp ))
  {
    payload->status = (uint8_t)ZCL_SUCCESS_STATUS;

    payload->sceneCount = 0;
    size += (uint8_t)sizeof(uint8_t) /*sceneCount*/;

    for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
    {
      if (!scenePool[i].free && scenePool[i].groupId == payload->groupId)
      {
        payload->sceneList[payload->sceneCount] = scenePool[i].sceneId;
        payload->sceneCount++;
        size += (uint8_t)sizeof(uint8_t) /*scene*/;
      }
    }
  }
  else
  {
    payload->status = (uint8_t)ZCL_INVALID_FIELD_STATUS;
  }

  return size;
}
</#if>
/**************************************************************************//**
\brief Fills Add Scene command to ECL structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] onOff - onOff extenstion filed value;
\param[in] level - currentLevel extension field value
\param[in] ccExt - pointer to color control scene extensions
******************************************************************************/
static void fillAddSceneToExtendedColorLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint16_t scene, uint16_t time,
  bool onOff, uint8_t level, ZCL_ColorControlClusterExtensionFieldSet_t *ccExt)
{
  ZCL_OnOffClusterExtensionFieldSet_t *onOffExt = (ZCL_OnOffClusterExtensionFieldSet_t *)&payload->name[1];

  uint8_t *tmp = (uint8_t *)onOffExt + sizeof(ZCL_OnOffClusterExtensionFieldSet_t);
  ZCL_LevelControlClusterExtensionFieldSet_t *levelControlExt = (ZCL_LevelControlClusterExtensionFieldSet_t *)tmp;

  tmp = (uint8_t *)levelControlExt + sizeof(ZCL_LevelControlClusterExtensionFieldSet_t);
  ZCL_ColorControlClusterExtensionFieldSet_t *colorControlExt = (ZCL_ColorControlClusterExtensionFieldSet_t *)tmp;

  payload->groupId        = group;
  payload->sceneId        = (uint8_t)scene;
  payload->transitionTime = time;
  payload->name[0]        = 0;

  onOffExt->clusterId  = ONOFF_CLUSTER_ID;
  onOffExt->length     = (uint8_t)sizeof(onOffExt->onOffValue);
  onOffExt->onOffValue = onOff;

  levelControlExt->clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  levelControlExt->length       = (uint8_t)sizeof(levelControlExt->currentLevel);
  levelControlExt->currentLevel = level;

  colorControlExt->clusterId    = COLOR_CONTROL_CLUSTER_ID;
  colorControlExt->length       = sizeof(ZCL_ColorControlClusterExtensionFieldSet_t) - sizeof(uint16_t) - sizeof(uint8_t);
  colorControlExt->currentX     = ccExt->currentX;
  colorControlExt->currentY     = ccExt->currentY;
  colorControlExt->enhancedCurrentHue = ccExt->enhancedCurrentHue;
  colorControlExt->currentSaturation  = ccExt->currentSaturation;
  colorControlExt->colorLoopActive    = ccExt->colorLoopActive;
  colorControlExt->colorLoopDirection = ccExt->colorLoopDirection;
  colorControlExt->colorLoopTime      = ccExt->colorLoopTime;
  colorControlExt->colorTemperature   = ccExt->colorTemperature;

  (void) tmp;
}

/**************************************************************************//**
\brief Fills Copy Scene command to ECL structure
******************************************************************************/
static void fillCopyScenePayload(ZCL_CopyScene_t *payload, SceneMode_t mode, uint16_t gidFrom, uint16_t sidFrom, uint16_t gidTo, uint16_t sidTo)
{
  payload->mode = mode;
  payload->groupIdFrom = gidFrom;
  payload->sceneIdFrom = (uint8_t)sidFrom;
  payload->groupIdTo = gidTo;
  payload->sceneIdTo = (uint8_t)sidTo;
}
<#if (SCENES_CLUSTER_CS != "CLIENT")  && ((SC_ADDSCENE == true) || (SC_ENHANCEDADDSCENE == true))>
/**************************************************************************//**
\brief Process Add Scene <#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true)> and Enhanced Add Scene</#if> command
******************************************************************************/
ZCL_Status_t processAddSceneCommand(bool enhanced, ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddScene_t *payload, Endpoint_t srcEp, Scene_t* scenePool, uint8_t* currSceneCount)
{
  ZCL_Request_t *req;
  ZCL_Status_t status;
  uint8_t cmdId;

<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE != true)>
  if(enhanced)
  {
    status = ZCL_UNSUP_CLUSTER_COMMAND_STATUS;/* Enhanced Add Scene Command is not supported */
    return status;
  }
</#if>

   // Process
  if (groupsIsValidGroup(payload->groupId, srcEp))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(payload->groupId, payload->sceneId, scenePool);

    if (scene == NULL)
    {
      scene = allocateScene(scenePool, currSceneCount); //incremant the device scene cluster SceneCount attribute);
    }
    if (scene != NULL)
    {
      status = ZCL_SUCCESS_STATUS;

      scene->sceneId = payload->sceneId;
      scene->groupId = payload->groupId;
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true)>
      if (enhanced)
      {
        scene->transitionTime = (uint16_t)(payload->transitionTime / 10U);
        scene->transitionTime100ms = (uint8_t)(payload->transitionTime % 10U);
      }
      else
</#if>      
      {
        scene->transitionTime = payload->transitionTime;
        scene->transitionTime100ms = 0;
      }

      {
        int8_t commandSize = (int8_t)((uint8_t)(sizeof(ZCL_AddScene_t) + payload->name[0]));
        int8_t extFieldsSize = (int8_t)payloadLength - commandSize;
        uint8_t *extFields = (uint8_t *)payload + commandSize;
        ZCL_ExtensionFieldSets_t *ext;

        while (extFieldsSize > 0)
        {
          ext = (ZCL_ExtensionFieldSets_t *)extFields;

          if ((uint16_t)ONOFF_CLUSTER_ID == ext->clusterId)
          {
            ZCL_OnOffClusterExtensionFieldSet_t *extension =
                (ZCL_OnOffClusterExtensionFieldSet_t *)extFields;

            scene->onOff = extension->onOffValue;
          }

          else if ((uint16_t)LEVEL_CONTROL_CLUSTER_ID == ext->clusterId)
          {
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
            ZCL_LevelControlClusterExtensionFieldSet_t *extension =
                (ZCL_LevelControlClusterExtensionFieldSet_t *)extFields;

            scene->currentLevel = extension->currentLevel;
#else
            status = ZCL_INVALID_FIELD_STATUS;
#endif
          }

          else if ((uint16_t)COLOR_CONTROL_CLUSTER_ID == ext->clusterId)
          {
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE
            ZCL_ColorControlClusterExtensionFieldSet_t *extension =
                (ZCL_ColorControlClusterExtensionFieldSet_t *)extFields;
<#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")>
            scene->colorMode = (ZCL_ZllEnhancedColorMode_t)customColorControlClusterServerAttributes.colorMode.value;
</#if>
            scene->currentX = extension->currentX;
            scene->currentY = extension->currentY;
#elif APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
            ZCL_ColorControlClusterExtensionFieldSet_t *extension =
                (ZCL_ColorControlClusterExtensionFieldSet_t *)extFields;

            scene->colorMode = (ZCL_ZllEnhancedColorMode_t)lightColorControlClusterServerAttributes.colorMode.value;
            scene->currentX = extension->currentX;
            scene->currentY = extension->currentY;
#else
             status = ZCL_INVALID_FIELD_STATUS;
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
            if(!enhanced <#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true)> || (enhanced && !(bool)(extension->currentX) && !(bool)(extension->currentY))</#if>)
            {
              scene->enhancedCurrentHue = extension->enhancedCurrentHue;
              scene->currentSaturation = extension->currentSaturation;
              scene->colorLoopActive = extension->colorLoopActive;
              scene->colorLoopDirection = extension->colorLoopDirection;
              scene->colorLoopTime = extension->colorLoopTime;
              scene->colorTemperature = extension->colorTemperature;
            }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true)>          
            else
            {
              scene->enhancedCurrentHue = 0;
              scene->currentSaturation = 0;
              scene->colorLoopActive = 0;
              scene->colorLoopDirection = 0;
              scene->colorLoopTime = 0;
              scene->colorTemperature = 0;
            }
</#if>            
#endif
          }
          else if ((uint16_t)THERMOSTAT_CLUSTER_ID == ext->clusterId)
          {
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
            ZCL_ThermostatClusterExtensionFieldSet_t    *thermostatExt =
              (ZCL_ThermostatClusterExtensionFieldSet_t *)extFields;

            scene->occupiedCoolingSetpoint = thermostatExt->occupiedCoolingSetpoint;
            scene->occupiedHeatingSetpoint = thermostatExt->occupiedHeatingSetpoint;
            scene->systemMode = thermostatExt->systemMode;
#endif
          }
          else
          {
              //add else for avoid misra rule 15.7
          }
          extFields += sizeof(ZCL_ExtensionFieldSets_t) + ext->length;
          extFieldsSize -= (int8_t)(ext->length);
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

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && ((SC_ADDSCENERESP == true) || (SC_ENHANCEDADDSCENERES == true))>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true) && (SC_ENHANCEDADDSCENERES != true)>
  if(enhanced)
  {
    status = ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;/* Enhanced Add Scene response command is not supported */
    return status;
  }
</#if>
  // Send Add scene response
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  cmdId = <#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true) && (SC_ENHANCEDADDSCENERES == true)> (uint8_t)(enhanced ? ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_RESPONSE_COMMAND_ID :</#if>ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID);

  fillCommandRequest(req, cmdId, (uint8_t)sizeof(ZCL_AddSceneResponse_t), srcEp);
  fillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload,
                                          payload->groupId, payload->sceneId, (uint8_t)status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  (void)payloadLength;
  return status;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && ((SC_VIEWSCENE == true) || (SC_ENHANCEDVIEWSCENE == true))>
/**************************************************************************//**
\brief Process View Scene <#if (SCENES_CLUSTER_CS != "CLIENT")  &&  (SC_ENHANCEDVIEWSCENE == true)> and Enhanced View Scene</#if> command
******************************************************************************/
ZCL_Status_t processViewSceneCommand(bool enhanced, ZCL_Addressing_t *addressing,
  ZCL_ViewScene_t *payload, Endpoint_t srcEp, Scene_t* scenePool)
{
  ZCL_Request_t *req;
  uint8_t status;
  Scene_t *scene;
  uint8_t commandId;
  ZCL_EnhancedViewSceneResponse_t* enhancedViewSceneResp;
  uint8_t size = sizeof(uint8_t) /*status*/ + sizeof(uint16_t) /*groupId*/ + sizeof(uint8_t) /*sceneId*/;

<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE != true)>
  if(enhanced)
  {
    status = ZCL_UNSUP_CLUSTER_COMMAND_STATUS;/* Enhanced Add Scene Command is not supported */
    return status;
  }
</#if>

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && ((SC_VIEWSCENERES == true) || (SC_ENHANCEDVIEWSCENERES == true))>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE == true) && (SC_ENHANCEDVIEWSCENERES != true)>
  if(enhanced)
  {
    status = ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;/* Enhanced View Scene response command is not supported */
    return status;
  }
</#if>
  // Send View Scene or Enhance view scene response
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  enhancedViewSceneResp = (ZCL_EnhancedViewSceneResponse_t*)req->requestPayload;
  enhancedViewSceneResp->groupId = payload->groupId;
  enhancedViewSceneResp->sceneId = payload->sceneId;

  if (groupsIsValidGroup(payload->groupId, srcEp))
  {
    scene = findSceneBySceneAndGroup(payload->groupId, payload->sceneId, scenePool);

    if (scene != NULL)
    {
      status = (uint8_t)ZCL_SUCCESS_STATUS;
    }
    else
    {
      status = (uint8_t)ZCL_NOT_FOUND_STATUS;
    }
  }
  else
  {
    status = (uint8_t)ZCL_INVALID_FIELD_STATUS;
  }

  enhancedViewSceneResp->status = status;

  if((uint8_t)ZCL_SUCCESS_STATUS == status)
  {
    #if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
      size = thFillViewSceneResponsePayload((ZCL_ViewSceneResponse_t *)req->requestPayload, scene, status, payload);
    #else
      size += lightFillViewSceneResponsePayload(enhanced, enhancedViewSceneResp, scene);
    #endif
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE == true) && (SC_ENHANCEDVIEWSCENERES == true)>
  if (enhanced)
  {
    commandId = ZCL_SCENES_CLUSTER_ENHANCED_VIEW_SCENE_RESPONSE_COMMAND_ID;
  }
  else
</#if>  
  {
    commandId = ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID; 
  }

  fillCommandRequest(req, commandId, size, srcEp);

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  return (ZCL_Status_t)status;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENE == true) >
/**************************************************************************//**
\brief Process Remove Scene command
******************************************************************************/
ZCL_Status_t processRemoveSceneCommand(ZCL_Addressing_t *addressing,
  ZCL_RemoveScene_t *payload, Endpoint_t srcEp, Scene_t* scenePool, uint8_t* currSceneCount)
{
  ZCL_Request_t *req;
  uint8_t status;

  if (groupsIsValidGroup(payload->groupId, srcEp))
  {
    Scene_t *scene;

    scene = findSceneBySceneAndGroup(payload->groupId, payload->sceneId, scenePool);

    if (scene != NULL)
    {
      status = (uint8_t)ZCL_SUCCESS_STATUS;
      if (freeScene(scene))
      {
        *currSceneCount -= 1U;
      }
    }
    else
    {
      status = (uint8_t)ZCL_NOT_FOUND_STATUS;
    }
  }
  else
  {
    status = (uint8_t)ZCL_INVALID_FIELD_STATUS;
  }

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENERES == true) >
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID, (uint8_t)sizeof(ZCL_AddSceneResponse_t), srcEp);
  fillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload,
                                          payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENE == true) >
/**************************************************************************//**
\brief Process Remove Scene command
******************************************************************************/
ZCL_Status_t processRemoveAllScenesCommand(ZCL_Addressing_t *addressing,
  ZCL_RemoveAllScenes_t *payload, Endpoint_t srcEp, Scene_t* scenePool, uint8_t* currSceneCount)
{
  ZCL_Status_t status;
  ZCL_Request_t *req;

  if (groupsIsValidGroup(payload->groupId, srcEp))
  {
    status = ZCL_SUCCESS_STATUS;
    *currSceneCount -= scenesClusterRemoveByGroup(payload->groupId, scenePool);
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }
  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENEALLRES == true) >
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID,
                       (uint8_t)sizeof(ZCL_RemoveAllScenesResponse_t), srcEp);
  fillRemoveAllScenesResponsePayload((ZCL_RemoveAllScenesResponse_t *)req->requestPayload, payload->groupId, (uint8_t)status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true) >
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT) ||  (APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT)
/**************************************************************************//**
\brief Process Store Scene command
******************************************************************************/
ZCL_Status_t processStoreSceneCommand(ZCL_Addressing_t *addressing,
  ZCL_StoreScene_t *payload, Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* sceneAttributes)
{
  ZCL_Request_t *req;
  uint8_t status;

  status = (uint8_t)(storeScene(payload, srcEp, scenePool, sceneAttributes));

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENERES == true) >
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID,
                       (uint8_t)sizeof(ZCL_StoreSceneResponse_t), srcEp);
  fillAddRemoveStoreSceneResponsePayload((ZCL_AddSceneResponse_t *)req->requestPayload, payload->groupId, payload->sceneId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>

  return (ZCL_Status_t)status;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENE == true) >
/**************************************************************************//**
\brief Fills Copy Scene Response command structure

\param[out] payload     - pointer to command structure;
\param[in]  status      - status of processing copy scene
\param[in]  groupIdFrom - group id to copy from
\param[in]  sceneIdFrom - scene id to copy from
******************************************************************************/
static void fillCopySceneResponsePayload(ZCL_CopySceneResponse_t *payload, ZCL_Status_t status, uint16_t groupIdFrom, uint16_t sceneIdFrom)
{
  payload->status = (uint8_t)status;
  payload->groupIdFrom = groupIdFrom;
  payload->sceneIdFrom = (uint8_t)sceneIdFrom;
}

/**************************************************************************//**
\brief Process Copy Scene command
******************************************************************************/
ZCL_Status_t processCopySceneCommand(ZCL_Addressing_t *addressing,
  ZCL_CopyScene_t *payload, Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* sceneAttributes)
{
  ZCL_Request_t *req;
  uint8_t status;

  status = (uint8_t)(copyScene(payload, srcEp, scenePool, sceneAttributes));

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENERES == true) >
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_COPY_SCENE_RESPONSE_COMMAND_ID,
                     (uint8_t)sizeof(ZCL_CopySceneResponse_t), srcEp);

  // command payload filler
  fillCopySceneResponsePayload((ZCL_CopySceneResponse_t *)req->requestPayload, (ZCL_Status_t)status, payload->groupIdFrom, payload->sceneIdFrom);

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  return (ZCL_Status_t)status;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_RECALLSCENE == true) >
/**************************************************************************//**
\brief Recalls scene from scene table

\param[in] recallScene - the pointer to Recall Scene request
******************************************************************************/
ZCL_Status_t recallScene(ZCL_RecallScene_t *recalSceneReq, Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{ 
  if ((recalSceneReq->groupId== 0x0000U) || (recalSceneReq->groupId >= 0xfff8U))
  {
    return ZCL_INVALID_VALUE_STATUS;
  }
  if (!groupsIsValidGroup(recalSceneReq->groupId, srcEp))
  {
    return ZCL_INVALID_FIELD_STATUS;
  }
  Scene_t *scene = findSceneBySceneAndGroup(recalSceneReq->groupId, recalSceneReq->sceneId, scenePool);

  if (scene != NULL)
  {
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_ON_OFF_LIGHT
<#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")>
    setOnOff(scene->onOff);
    onOffClusterSetExtensionField(scene->onOff);
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")>
    if (0xffffU == recalSceneReq->transitionTime || 0U == recalSceneReq->transitionTime)
    {
      setLevel(false, false, scene->currentLevel);
    }
    levelControlClusterSetExtensionField(scene->currentLevel, recalSceneReq->transitionTime);
</#if>
#endif
    /* Need to be done with other clusters */

<#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")>
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
    colorControlClusterSetExtensionField(scene,recalSceneReq->transitionTime);
#endif
</#if>
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT
    thermostatClusterSetExtensionField(scene);
#endif
    scenesAttributes->currentScene.value = scene->sceneId;
    scenesAttributes->currentGroup.value = scene->groupId;
    scenesAttributes->sceneValid.value   = true;

    return ZCL_SUCCESS_STATUS;
  }
  return ZCL_NOT_FOUND_STATUS;

}
/**************************************************************************//**
\brief Recall the global scene
******************************************************************************/
void recallGlobalScene(Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  ZCL_RecallScene_t globalScene;
  globalScene.groupId = 0x0000u;
  globalScene.sceneId = 0x00u;
  globalScene.transitionTime = 0x0000u;

  (void)recallScene(&globalScene, srcEp, scenePool, scenesAttributes);
}
</#if>
/**************************************************************************//**
\brief Store to global scene
******************************************************************************/
void storeGlobalScene(Endpoint_t srcEp, Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  ZCL_StoreScene_t globalScene;

  globalScene.groupId = 0x0000u;
  globalScene.sceneId = 0x00u;
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true) >
  (void)storeScene(&globalScene, srcEp, scenePool, scenesAttributes);
</#if>
}
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENE == true) >
/**************************************************************************//**
\brief Copy scene(s) in scene table

\param[in] groupIdFrom - group id to copy from
\param[in] sceneIdFrom - scene id to copy from
\param[in] groupIdTo   - group id to copy to
\param[in] sceneIdTo   - scene id to copy to

\returns status of scene storing
******************************************************************************/
ZCL_Status_t copyScenesByGroup(uint16_t groupIdFrom, uint16_t sceneIdFrom,
                                      uint16_t groupIdTo, uint16_t sceneIdTo,
                                      Scene_t* scenePool, ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  Scene_t *sceneFrom, *sceneTo;

  sceneFrom = findSceneBySceneAndGroup(groupIdFrom, (uint8_t)sceneIdFrom, scenePool);
  if (sceneFrom == NULL)
  {
    return ZCL_NOT_FOUND_STATUS;
  }

  sceneTo = findSceneBySceneAndGroup(groupIdTo, (uint8_t)sceneIdTo, scenePool);
  if (sceneTo == NULL)
  {
    sceneTo = allocateScene(scenePool, &scenesAttributes->sceneCount.value);
  }

  if (sceneTo != NULL)
  {
    (void)memcpy(sceneTo, sceneFrom, sizeof(Scene_t));
    sceneTo->sceneId = (uint8_t)sceneIdTo;
    sceneTo->groupId = groupIdTo;
  }
  else
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Copy scene(s) in scene table

\param[in] copyScene - the pointer to Copy Scene request
\param[in] srcEp     - source endpoint
\param[in] scenePool - pointer to scene table
\param[in] sceneAttributes - pointer to scene cluster attributes

\returns status of scene storing
******************************************************************************/
ZCL_Status_t copyScene(ZCL_CopyScene_t *copySceneReq, Endpoint_t srcEp, Scene_t* scenePool,
                       ZCL_SceneClusterServerAttributes_t* scenesAttributes)
{
  ZCL_Status_t status;

  if (groupsIsValidGroup(copySceneReq->groupIdFrom, srcEp))
  {
    if ((copySceneReq->mode.copyAllScenes & ZCL_SCENES_CLUSTER_COPY_ALL_SCENES) != 0U)
    {
      status = ZCL_SUCCESS_STATUS;

      for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
      {
        if (!scenePool[i].free && (scenePool[i].groupId == copySceneReq->groupIdFrom))
        {
          ZCL_Status_t result;

          result = copyScenesByGroup(copySceneReq->groupIdFrom, scenePool[i].sceneId,
                                     copySceneReq->groupIdTo, scenePool[i].sceneId,
                                     scenePool, scenesAttributes);

          if (ZCL_SUCCESS_STATUS != result)
          {
            status = result;
          }
        }
      }
    }
    else
    {
      status = copyScenesByGroup(copySceneReq->groupIdFrom, copySceneReq->sceneIdFrom,
                                 copySceneReq->groupIdTo, copySceneReq->sceneIdTo,
                                 scenePool, scenesAttributes);
    }
  }
  else
  {
    status = ZCL_INVALID_FIELD_STATUS;
  }

  return status;
}
</#if>
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEM == true) >
/**************************************************************************//**
\brief Process Get SceneMembership command

\param[in] addressing - the pointer to Store Scene request

\returns status of processing of getSceneMembership Req
**************************************************************************/
ZCL_Status_t processGetSceneMembershipCommand(ZCL_Addressing_t *addressing,
  ZCL_GetSceneMembership_t *payload, Endpoint_t srcEp, Scene_t* scenePool, uint8_t currSceneCnt )
{
  ZCL_Request_t *req;
  uint8_t size;

  /* A response should be sent if the request is unicast or (the request is broadcast
      and scene(s) for given group exist(s)) */
  if (!(!addressing->nonUnicast ||
    (addressing->nonUnicast && groupsIsValidGroup(payload->groupId, srcEp) && (getNextSceneByGroup(NULL, payload->groupId, scenePool) != NULL))))
  {
    return ZCL_SUCCESS_STATUS;
  }
<#if (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEMRES == true) >
  req = getFreeCommand();
  if (req == NULL)
  {
    return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  size = fillGetSceneMembershipPayload((ZCL_GetSceneMembershipResponse_t *)req->requestPayload, scenePool, payload->groupId, srcEp, currSceneCnt);
  fillCommandRequest(req, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID,
                       size, srcEp);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
</#if>
  return ZCL_SUCCESS_STATUS;
}
#endif
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENE == true) >
/**************************************************************************//**
\brief Sends Add Scene command to bound Dimmable Light device

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] onOff - onOff extenstion filed value;
\param[in] level - currentLevel extension field value
******************************************************************************/
void scenesSendAddSceneToDimmableLight(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
    sizeof(ZCL_AddScene_t) + sizeof(ZCL_OnOffClusterExtensionFieldSet_t) +
    sizeof(ZCL_LevelControlClusterExtensionFieldSet_t), srcEp);
  fillAddSceneToDimmableLightPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time, onOff, level);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Fills Add Scene command to DL structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] onOff - onOff extenstion filed value;
\param[in] level - currentLevel extension field value
******************************************************************************/
static void fillAddSceneToDimmableLightPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time, bool onOff, uint8_t level)
{
  ZCL_OnOffClusterExtensionFieldSet_t    *onOffExt = (ZCL_OnOffClusterExtensionFieldSet_t *)&payload->name[1];
  uint8_t                                *tmp = (uint8_t *)(&payload->name[1]) + sizeof(ZCL_OnOffClusterExtensionFieldSet_t);
  ZCL_LevelControlClusterExtensionFieldSet_t *levelControlExt = (ZCL_LevelControlClusterExtensionFieldSet_t *)tmp;

  payload->groupId        = group;
  payload->sceneId        = scene;
  payload->transitionTime = time;
  payload->name[0]        = 0;

  onOffExt->clusterId  = ONOFF_CLUSTER_ID;
  onOffExt->length     = sizeof(onOffExt->onOffValue);
  onOffExt->onOffValue = onOff;

  levelControlExt->clusterId    = LEVEL_CONTROL_CLUSTER_ID;
  levelControlExt->length       = sizeof(levelControlExt->currentLevel);
  levelControlExt->currentLevel = level;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENE == true) >
/**************************************************************************//**
\brief Sends Add Scene command to bound Thermostat device

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] occupiedCoolingSetPoint - occupiedCoolingSetPoint extenstion field value;
\param[in] occupiedHeatingSetPoint - occupiedHeatingSetPoint extension field value
\param[in] systemMode              - systemMode extension field value
******************************************************************************/
void scenesSendAddSceneToThermotstat(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene, uint16_t time, int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
    sizeof(ZCL_AddScene_t) + sizeof(ZCL_ThermostatClusterExtensionFieldSet_t), srcEp);

  fillAddSceneToThermostatPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time,
                                    occupiedCoolingSetPoint, occupiedHeatingSetPoint, systemMode);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}

</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENE == true) >
/**************************************************************************//**
\brief Fills Add Scene command TH structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id;
\param[in] time  - transition time;
\param[in] occupiedCoolingSetPoint - onOff occupiedCoolingSetPoint filed value;
\param[in] occupiedHeatingSetPoint - occupiedHeatingSetPoint extension field value
\param[in] systemMode              - systemMode extension field value
******************************************************************************/
static void fillAddSceneToThermostatPayload(ZCL_AddScene_t *payload, uint16_t group, uint8_t scene, uint16_t time,
                                              int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint, uint8_t systemMode)
{
  ZCL_ThermostatClusterExtensionFieldSet_t    *thermostatExt = (ZCL_ThermostatClusterExtensionFieldSet_t *)&payload->name[1];

  payload->groupId        = group;
  payload->sceneId        = scene;
  payload->transitionTime = time;
  payload->name[0]        = 0;

  thermostatExt->clusterId  = THERMOSTAT_CLUSTER_ID;
  thermostatExt->length     = sizeof(ZCL_ThermostatClusterExtensionFieldSet_t) - sizeof(uint8_t) - sizeof(ClusterId_t) ;
  thermostatExt->occupiedCoolingSetpoint = occupiedCoolingSetPoint;
  thermostatExt->occupiedHeatingSetpoint = occupiedHeatingSetPoint;
  thermostatExt->systemMode = systemMode;
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_VIEWSCENE == true) >
/**************************************************************************//**
\brief Sends View Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendViewScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID, sizeof(ZCL_ViewScene_t), srcEp);
  fillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENE == true) >
/**************************************************************************//**
\brief Sends Remove Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendRemoveScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID, sizeof(ZCL_RemoveScene_t), srcEp);
  fillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENEALL == true) >
/**************************************************************************//**
\brief Sends Remove All Scenes command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void scenesSendRemoveAllScenes(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID, sizeof(ZCL_RemoveAllScenes_t), srcEp);
  fillRemoveAllScenesGetSceneMembershipPayload((ZCL_RemoveAllScenes_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_STORESCENE == true) >
/**************************************************************************//**
\brief Sends Store Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendStoreScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID, sizeof(ZCL_StoreScene_t), srcEp);
  fillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_RECALLSCENE == true) >
/**************************************************************************//**
\brief Sends Recall Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendRecallScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene, uint16_t time)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID, sizeof(ZCL_RecallScene_t), srcEp);
  fillRecallScenePayload((ZCL_RecallScene_t *)req->requestPayload, group, scene, time);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_SCENEMEM == true) >
/**************************************************************************//**
\brief Sends Get Scene Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void scenesSendGetSceneMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID, sizeof(ZCL_GetSceneMembership_t), srcEp);
  fillRemoveAllScenesGetSceneMembershipPayload((ZCL_RemoveAllScenes_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
/**************************************************************************//**
\brief Fills View, Remove, Store or Recall Scene command structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void fillViewRemoveStoreRecallScenePayload(ZCL_ViewScene_t *payload, uint16_t group, uint8_t scene)
{
  payload->groupId = group;
  payload->sceneId = scene;
}

/**************************************************************************//**
\brief Fills View, Remove, Store or Recall Scene command structure

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void fillRecallScenePayload(ZCL_RecallScene_t *payload, uint16_t group, uint8_t scene, uint16_t time)
{
  payload->groupId = group;
  payload->sceneId = scene;
  payload->transitionTime = time;
}

/**************************************************************************//**
\brief Fills View, Remove, Store or Recall Scene command structure

\param[out] payload - pointer to command structure;
\param[in] group - group id
******************************************************************************/
static void fillRemoveAllScenesGetSceneMembershipPayload(ZCL_RemoveAllScenes_t *payload, uint16_t group)
{
  payload->groupId = group;
}

/**************************************************************************//**
\brief Remove all scenes associated with the group
\return returns the no. of scenes removed
******************************************************************************/
uint8_t scenesClusterRemoveByGroup(uint16_t group, Scene_t *scenePool)
{
  uint8_t sceneAmt = 0;
  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((scenePool[i].groupId == group) && freeScene(&scenePool[i]))
    {
      sceneAmt++;
    }
  }
  return sceneAmt;
}

<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDADDSCENE == true) >
/**************************************************************************//**
\brief Sends Enhanced Add Scene command to bound Extended Color Light device

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node or number of group;
\param[in] ep     - endpoint number of destination device;
\param[in] group  - group id;
\param[in] scene  - scene id;
\param[in] time   - transition time;
\param[in] onOff  - onOff extenstion filed value;
\param[in] level  - currentLevel extension field value
\param[in] ccExt  - pointer to color control extension fields values
******************************************************************************/
void scenesSendEnhancedAddSceneToExtendedColorLightWithExtFields(APS_AddrMode_t mode, ShortAddr_t addr,
  Endpoint_t ep, Endpoint_t srcEp, uint16_t group, uint16_t scene, uint16_t time, bool onOff, uint8_t level,
  ZCL_ColorControlClusterExtensionFieldSet_t *ccExt)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_COMMAND_ID, sizeof(ZCL_EnhancedAddScene_t), srcEp);

  fillAddSceneToExtendedColorLightPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time, onOff, level, ccExt);

  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);

  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDADDSCENE == true) >
/**************************************************************************//**
\brief Sends Enhanced Add Scene command to bound Thermostat device

\param[in] mode   - address mode;
\param[in] addr   - short address of destination node or number of group;
\param[in] ep     - endpoint number of destination device;
\param[in] group  - group id;
\param[in] scene  - scene id;
\param[in] time   - transition time;
\param[in] occupiedCoolingSetPoint  - occupied cooling setpoint;
\param[in] occupiedHeatingSetPoint  - occupied heating setpoint;
\param[in] systemMode               - System mode;
******************************************************************************/
void scenesSendEnhancedAddSceneToThermostat(APS_AddrMode_t mode, ShortAddr_t addr,
  Endpoint_t ep, Endpoint_t srcEp, uint16_t group, uint16_t scene, uint16_t time, int16_t occupiedCoolingSetPoint, int16_t occupiedHeatingSetPoint,
  uint8_t systemMode)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ENHANCED_ADD_SCENE_COMMAND_ID, sizeof(ZCL_AddScene_t) + sizeof(ZCL_ThermostatClusterExtensionFieldSet_t), srcEp);

  fillAddSceneToThermostatPayload((ZCL_AddScene_t *)req->requestPayload, group, scene, time, occupiedCoolingSetPoint, occupiedHeatingSetPoint, systemMode);

  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);

  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDVIEWSCENE == true) >
/**************************************************************************//**
\brief Sends Enhanced View Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
void scenesSendEnhancedViewScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  uint16_t group, uint8_t scene)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_ENHANCED_VIEW_SCENE_COMMAND_ID, sizeof(ZCL_ViewScene_t), srcEp);
  fillViewRemoveStoreRecallScenePayload((ZCL_ViewScene_t *)req->requestPayload, group, scene);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (SCENES_CLUSTER_CS != "SERVER")  && (SCC_COPYSCENE == true) >
/**************************************************************************//**
\brief Sends Copy Scene command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] *req  - pointer to ZCL_CopyScene_t command
******************************************************************************/
void scenesSendCopyScene(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  SceneMode_t copyMode, uint16_t gidFrom, uint16_t sidFrom, uint16_t gidTo, uint16_t sidTo)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_SCENES_CLUSTER_COPY_SCENE_COMMAND_ID, sizeof(ZCL_CopyScene_t), srcEp);
  fillCopyScenePayload((ZCL_CopyScene_t *)req->requestPayload, copyMode, gidFrom, sidFrom, gidTo, sidTo);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, SCENES_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
//eof scenesCluster.c
