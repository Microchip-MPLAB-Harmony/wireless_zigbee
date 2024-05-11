/*******************************************************************************
  Dimmer Switch Scenes cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dsScenesCluster.c

  Summary:
    This file contains the Dimmer Switch Scenes cluster interface.

  Description:
    This file contains the Dimmer Switch Scenes cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMER_SWITCH)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <dsScenesCluster.h>
#include <zclZllOnOffCluster.h>
#include <zclZllLevelControlCluster.h>
#include <zclThermostatCluster.h>
#include <zclCommandManager.h>
#include <console.h>
#include <dimmerSwitch.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
PROGMEM_DECLARE(ZCL_ScenesClusterCommands_t dsScenesCommands) =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_COMMANDS(addSceneResponseInd, viewSceneResponseInd, removeSceneResponseInd,
                                     removeAllScenesResponseInd, storeSceneResponseInd, getSceneMembershipResponseInd,
                                     NULL,NULL,NULL)
};

ZCL_SceneClusterClientAttributes_t dsScenesClusterClientAttributes =
{
  ZCL_DEFINE_SCENES_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Scenes cluster
******************************************************************************/
void dsScenesClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_DIMMER_SWITCH, SCENES_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  dsScenesClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Callback on receiving Add Scene Response command

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

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving View Scene Response command

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

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove Scene Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  appSnprintf("Remove scene response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
  appSnprintf("sceneId = 0x%02x\r\n", payload->sceneId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Remove All Scenes Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  appSnprintf("Remove all scenes response: status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Store Scene Response command

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
\brief Callback on receiving Get Scene Membership Response command

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
    appSnprintf("sceneId = 0x%02x\r\n", payload->sceneList[i]);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMER_SWITCH)
//eof dsScenesCluster.c