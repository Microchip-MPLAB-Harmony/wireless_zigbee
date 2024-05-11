/*******************************************************************************
  CSC Scenes Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cscScenesCluster.c

  Summary:
    This file contains the Color Scene Remote device Scenes cluster interface.

  Description:
    This file contains the Color Scene Remote device Scenes cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>
#include <z3device/common/include/appConsts.h>
#include <zcl/include/zclZllScenesCluster.h>
#include <zcl/include/zclZllOnOffCluster.h>
#include <zcl/include/zclZllLevelControlCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <z3device/colorSceneController/include/cscScenesCluster.h>
#include <z3device/colorSceneController/include/cscClusters.h>
#include <app_zigbee/zigbee_console/console.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
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
ZCL_ScenesClusterCommands_t cscScenesClusterCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_COMMANDS(addSceneResponseInd, viewSceneResponseInd,
      removeSceneResponseInd, removeAllScenesResponseInd, storeSceneResponseInd,
      getSceneMembershipResponseInd, enhancedAddSceneResponseInd,
      enhancedViewSceneResponseInd, copySceneResponseInd)
};

ZCL_SceneClusterClientAttributes_t cscScenesClusterClientAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_ATTRIBUTES()
};
/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void cscScenesClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, SCENES_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  cscScenesClusterClientAttributes.clusterVersion.value = SCENES_CLUSTER_VERSION;
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
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

#endif // (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

// eof cscScenesCluster.c
