/*******************************************************************************
  IAS ACE Groups cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACEGroupsCluster.c

  Summary:
    This file contains the IAS ACE Groups cluster interface.

  Description:
    This file contains the IAS ACE Groups cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_IAS_ACE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/ias_ace/include/iasACEGroupsCluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <app_zigbee/zigbee_console/console.h>
#include <zcl/include/zclCommandManager.h>
#include <zcl/clusters/include/scenes.h>
#include <pds/include/wlPdsMemIds.h>
#include <nwk/include/nwkGroup.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <z3device/common/include/appConsts.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload);
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload);
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload);
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload);
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
static ZCL_Status_t addGroupIfIdentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload);

static ZCL_Status_t addGroupIfIdentifying(uint16_t group);

static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterServerAttributes_t iasACEgroupsClusterServerAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_GroupsClusterClientAttributes_t iasACEgroupsClusterClientAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_CLIENT_ATTRIBUTES()
};
  
PROGMEM_DECLARE(ZCL_GroupsClusterCommands_t         iasACEGroupsCommands) =
{
      ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(addGroupInd, viewGroupInd, getGroupMembershipInd,
                                     removeGroupInd, removeAllGroupsInd, addGroupIfIdentifyingInd,
                                     addGroupResponseInd, viewGroupResponseInd, getGroupMembershipResponseInd, removeGroupResponseInd)
};
extern QueueDescriptor_t groupsSubscribers;
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void iasGroupsClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, GROUPS_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  iasACEgroupsClusterServerAttributes.nameSupport.value = 0;
  iasACEgroupsClusterServerAttributes.clusterVersion.value = GROUPS_CLUSTER_VERSION;
  iasACEgroupsClusterClientAttributes.clusterVersion.value = GROUPS_CLUSTER_VERSION;
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool iasIdentifyIsIdentifying(void)
{
  return iasACEIdentifyClusterServerAttributes.identifyTime.value > 0;
}
/**************************************************************************//**
\brief Callback on receiving Add Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload)
{
  ZCL_Request_t *req;
  uint8_t status;

  appSnprintf("addGroupInd(): 0x%04x\r\n", payload->groupId);

  status = addGroup(payload->groupId, APP_ENDPOINT_IAS_ACE);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_AddGroupResponse_t), APP_ENDPOINT_IAS_ACE);
  fillAddGroupResponsePayload((ZCL_AddGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving View Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload)

{
  ZCL_Request_t *req;
  appSnprintf("viewGroupInd(): 0x%04x\r\n", payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_ViewGroupResponse_t), APP_ENDPOINT_IAS_ACE);
  fillViewGroupResponsePayload((ZCL_ViewGroupResponse_t *)req->requestPayload, payload->groupId, APP_ENDPOINT_IAS_ACE);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Get Group Membership command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload)
{
  ZCL_Request_t *req;
  uint8_t size;

  appSnprintf("getGroupMembershipInd()\r\n");

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  size = fillGetGroupMembershipRespPayload((ZCL_GetGroupMembershipResponse_t *)req->requestPayload, payload, APP_ENDPOINT_IAS_ACE);
  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID,
                       size, APP_ENDPOINT_IAS_ACE);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Remove Group command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload)
{
  ZCL_Request_t *req;
  uint8_t status;

  appSnprintf("removeGroupInd(): 0x%04x\r\n", payload->groupId);

  if (NWK_RemoveGroup(payload->groupId, APP_ENDPOINT_IAS_ACE))
  {
     status =  ZCL_SUCCESS_STATUS;
  }
  else
    status =  ZCL_NOT_FOUND_STATUS;
  
  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveGroupResponse_t), APP_ENDPOINT_IAS_ACE);
  fillRemoveGroupResponsePayload((ZCL_RemoveGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Remove All Groups command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  appSnprintf("removeAllGroupsInd()\r\n");

  NWK_RemoveAllGroups(APP_ENDPOINT_IAS_ACE);  
  
  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Add Group If Identifying command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupIfIdentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload)
{
  ZCL_Status_t  status;
  appSnprintf("addGroupIfIdentifyingInd(): 0x%04x\r\n", payload->groupId);
  
  status = addGroupIfIdentifying(payload->groupId);

  (void)addressing, (void)payloadLength;
  return status;
}
/**************************************************************************//**
\brief Callback on receiving Add Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  appSnprintf("addGroupResponseInd()\r\n");

  RAISE_CALLBACKS_TO_GROUPS_SUBSCIBERS(groupsSubscribers, addGroupResponse);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving View Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
{
  appSnprintf("viewGroupResponse(): status = 0x%02x\r\n", payload->status);
  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Group Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload)
{
  appSnprintf("getGroupMembershipResponse()\r\n");
  appSnprintf("groupCount = %d\r\n", payload->groupCount);

  for (uint8_t i = 0; i < payload->groupCount; i++)
    appSnprintf("groupId = 0x%04x\r\n", payload->groupList[i]);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Remove Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
  appSnprintf( "removeGroupResponseInd()\r\n");

  appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Adds group to group table if device is in identifying state

\param[in] group - group id
******************************************************************************/
static ZCL_Status_t addGroupIfIdentifying(uint16_t group)
{
  ZCL_Status_t  status;
  if (iasIdentifyIsIdentifying())
  {
    status = addGroup(group, APP_ENDPOINT_IAS_ACE);
    return status;
  }
  // If received via multicast or broadcast service no response shall be given
  else
    return ZCL_SUCCESS_STATUS;
}

#endif // #if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_IAS_ACE
// eof iasAceGroupsCluster.c
