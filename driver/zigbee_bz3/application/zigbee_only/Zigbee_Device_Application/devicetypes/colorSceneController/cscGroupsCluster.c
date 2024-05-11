/*******************************************************************************
  Color Scene Controller Groups cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cscGroupsCluster.c

  Summary:
    This file contains the Color Scene Controller device Groups cluster interface.

  Description:
    This file contains the Color Scene Controller device Groups cluster interface.
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
                    Includes
******************************************************************************/
#include <zcl/include/clusters.h>
#include <z3device/common/include/appConsts.h>
#include <zcl/include/zclCommandManager.h>
#include <zcl/include/zclZllGroupsCluster.h>
#include <z3device/colorSceneController/include/cscGroupsCluster.h>
#include <z3device/colorSceneController/include/cscClusters.h>
#include <nwk/include/nwkGroup.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <app_zigbee/zigbee_console/console.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
AddGroupResponseCsc_t serviceCallback = NULL;

/******************************************************************************
                    Global variables section
******************************************************************************/
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterClientAttributes_t  cscGroupsClusterClientAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_CLIENT_ATTRIBUTES()
};

ZCL_GroupsClusterCommands_t cscGroupsClusterCommands =
{

  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
    addGroupResponseInd, viewGroupResponseInd, 
    getGroupMembershipResponseInd, removeGroupResponseInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void cscGroupsClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, GROUPS_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  cscGroupsClusterClientAttributes.clusterVersion.value = GROUPS_CLUSTER_VERSION;
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Callback on receive of AddGroupResponse command; it is a stub
\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  if (serviceCallback)
  {
    serviceCallback(payload->status, payload->groupId);
    serviceCallback = NULL;
  }
  appSnprintf("addGroupResponseInd()\r\n");
  
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief View Group Response indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
{
  appSnprintf("viewGroupResponse(): status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Get Group Membership Response indication
\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload)
{
  appSnprintf("getGroupMembershipResponse()\r\n");
  appSnprintf( "groupCount = %d\r\n", payload->groupCount);

  for (uint8_t i = 0; i < payload->groupCount; i++)
    appSnprintf("groupId = 0x%04x\r\n", payload->groupList[i]);

  (void)addressing;(void)payloadLength;(void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of RemoveGroupResponse command; it is a stub

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
  appSnprintf("removeGroupResponseInd()\r\n");

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
#endif // #if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

// eof cscGroupsCluster.c
