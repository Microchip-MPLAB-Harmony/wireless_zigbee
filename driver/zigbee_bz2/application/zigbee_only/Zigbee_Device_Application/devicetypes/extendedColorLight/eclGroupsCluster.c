/*******************************************************************************
  Extended Color Light Groups cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclGroupsCluster.c

  Summary:
    This file contains the Extended Color Light Groups cluster interface.

  Description:
    This file contains the Extended Color Light Groups cluster interface.
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
#include <eclGroupsCluster.h>
#include <eclIdentifyCluster.h>
#include <eclScenesCluster.h>
#include <haClusters.h>
#include <uartManager.h>
#include <commandManager.h>
#include <eclScenes.h>
#include <pdsDataServer.h>
#define _GROUP_TABLE_
#include <nwkGroup.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroup_t *payload);
static ZCL_Status_t viewGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroup_t *payload);
static ZCL_Status_t getGroupMembershipInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembership_t *payload);
static ZCL_Status_t removeGroupInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroup_t *payload);
static ZCL_Status_t removeAllGroupsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
static ZCL_Status_t addGroupIfidentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload);

static void eclFillAddGroupResponsePayload(ZCL_AddGroupResponse_t *payload, uint16_t group, uint8_t status);
static void eclFillViewGroupResponsePayload(ZCL_ViewGroupResponse_t *payload, uint16_t group);
static uint8_t eclFillGetGroupMembershipPayload(ZCL_GetGroupMembershipResponse_t *payload, ZCL_GetGroupMembership_t *req);
static void eclFillRemoveGroupResponsePayload(ZCL_RemoveGroupResponse_t *payload, uint16_t group, uint8_t status);

static ZCL_Status_t addGroup(uint16_t group);
static ZCL_Status_t removeGroup(uint16_t group);
static void removeAllGroups(void);
static void addGroupIfIdentifying(uint16_t group);

//static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
//static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
//static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
//static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

//static void fillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group);
//static void fillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group);
//static uint8_t fillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list);

NWK_GroupTableEntry_t* NWK_NextGroup(NWK_GroupTableEntry_t *entry);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterServerAttributes_t eclGroupsClusterServerAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_GroupsClusterClientAttributes_t eclGroupsClusterClientAttributes =
{
  ZCL_DEFINE_GROUPS_CLUSTER_CLIENT_ATTRIBUTES()
};

ZCL_GroupsClusterCommands_t         eclGroupsCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(addGroupInd, viewGroupInd, getGroupMembershipInd,
                                     removeGroupInd, removeAllGroupsInd, addGroupIfidentifyingInd,
                                     NULL, NULL, NULL, NULL)
};

AddGroupResponseCb_t serviceCallback = NULL;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Groups cluster
******************************************************************************/
void groupsClusterInit(void)
{
  eclGroupsClusterServerAttributes.nameSupport.value = 0;
  eclGroupsClusterServerAttributes.clusterVersion.value = 0x0001u;
  eclGroupsClusterClientAttributes.clusterVersion.value = 0x0001u;
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

  status = addGroup(payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_AddGroupResponse_t));
  eclFillAddGroupResponsePayload((ZCL_AddGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  appSnprintf("addGroupInd(): 0x%04x\r\n", payload->groupId);

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

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_ViewGroupResponse_t));
  eclFillViewGroupResponsePayload((ZCL_ViewGroupResponse_t *)req->requestPayload, payload->groupId);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  appSnprintf("viewGroupInd(): 0x%04x\r\n", payload->groupId);

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

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  size = eclFillGetGroupMembershipPayload((ZCL_GetGroupMembershipResponse_t *)req->requestPayload, payload);
  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID,
                       size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  appSnprintf("getGroupMembershipInd()\r\n");

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

  status = removeGroup(payload->groupId);

  // If received via multicast or broadcast service no response shall be given
  if (addressing->nonUnicast)
    return ZCL_SUCCESS_STATUS;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_RemoveGroupResponse_t));
  eclFillRemoveGroupResponsePayload((ZCL_RemoveGroupResponse_t *)req->requestPayload, payload->groupId, status);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  appSnprintf("removeGroupInd(): 0x%04x\r\n", payload->groupId);

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
  removeAllGroups();

  appSnprintf("removeAllGroupsInd()\r\n");

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
static ZCL_Status_t addGroupIfidentifyingInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupIfIdentifying_t * payload)
{
  addGroupIfIdentifying(payload->groupId);

  appSnprintf("addGroupIfIdentifyingInd(): 0x%04x\r\n", payload->groupId);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - status of group adding
******************************************************************************/
static void eclFillAddGroupResponsePayload(ZCL_AddGroupResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills View Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void eclFillViewGroupResponsePayload(ZCL_ViewGroupResponse_t *payload, uint16_t group)
{
  if (NWK_IsGroupMember(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
    payload->status = ZCL_SUCCESS_STATUS;
  else
    payload->status = ZCL_NOT_FOUND_STATUS;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Group Membership Response command structure

\param[out] payload - pointer to command structure;
\param[in]  req     - pointer to appropriate request

\returns the amount of group ids in reponse
******************************************************************************/
static uint8_t eclFillGetGroupMembershipPayload(ZCL_GetGroupMembershipResponse_t *payload, ZCL_GetGroupMembership_t *req)
{
  payload->capacity   = NWK_GroupCapacity();
  payload->groupCount = 0;

  if (req->groupCount)
    for (uint8_t i = 0; i < req->groupCount; i++)
    {
      if (NWK_IsGroupMember(req->groupList[i], APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
        payload->groupList[payload->groupCount++] = req->groupList[i];
    }
  else
  {
    NWK_GroupTableEntry_t *group = NULL;

    while ((group = NWK_NextGroup(group)))
      payload->groupList[payload->groupCount++] = group->addr;
  }

  return sizeof(ZCL_GetGroupMembershipResponse_t) + sizeof(uint16_t) * payload->groupCount - sizeof(uint16_t);
}

/**************************************************************************//**
\brief Fills Remove Group Response command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id;
\param[in]  status  - status of group adding
******************************************************************************/
static void eclFillRemoveGroupResponsePayload(ZCL_RemoveGroupResponse_t *payload, uint16_t group, uint8_t status)
{
  payload->status  = status;
  payload->groupId = group;
}

/**************************************************************************//**
\brief Adds group to group table

\param[in] group - group id

\returns status of group adding
******************************************************************************/
static ZCL_Status_t addGroup(uint16_t group)
{
  if (!NWK_IsGroupMember(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
  {
    if (NWK_AddGroup(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
      return ZCL_SUCCESS_STATUS;
    else
      return ZCL_INSUFFICIENT_SPACE_STATUS;
  }

  return ZCL_DUPLICATE_EXISTS_STATUS;
}

/**************************************************************************//**
\brief Removes group from group table

\param[in] group - group id

\returns status of group removing
******************************************************************************/
static ZCL_Status_t removeGroup(uint16_t group)
{
  if (NWK_RemoveGroup(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
  {
    scenesClusterRemoveByGroup(group);
    PDS_Store(HA_APP_MEMORY_MEM_ID);
    return ZCL_SUCCESS_STATUS;
  }
  else
    return ZCL_NOT_FOUND_STATUS;
}

/**************************************************************************//**
\brief Removes all groups from group table
******************************************************************************/
static void removeAllGroups(void)
{
  NWK_GroupTableEntry_t *group = NULL;

  while (NULL != (group = NWK_NextGroup(group)))
    scenesClusterRemoveByGroup(group->addr);

  NWK_RemoveAllGroups(APP_ENDPOINT_EXTENDED_COLOR_LIGHT);
  PDS_Store(APP_DL_SCENES_MEM_ID);
}

/**************************************************************************//**
\brief Adds group to group table if device is in identifying state

\param[in] group - group id
******************************************************************************/
static void addGroupIfIdentifying(uint16_t group)
{
  if (identifyIsIdentifying())
    if (!NWK_IsGroupMember(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT))
      NWK_AddGroup(group, APP_ENDPOINT_EXTENDED_COLOR_LIGHT);
}


/**************************************************************************//**
\brief Callback on receiving Add Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
// static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
// {
//   LOG_STRING(addGroupRespStr, "addGroupResponseInd()\r\n");
//
//   if (serviceCallback)
//   {
//     serviceCallback(payload->status, payload->groupId);
//     serviceCallback = NULL;
//   }
//
//   appSnprintf(addGroupRespStr);
//   (void)addressing, (void)payloadLength, (void)payload;
//   return ZCL_SUCCESS_STATUS;
// }

/**************************************************************************//**
\brief Callback on receiving View Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
// static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
// {
//   appSnprintf(respStr, payload->status);
//   appSnprintf(groupStr, payload->groupId);
//
//   LOG_STRING(respStr, "viewGroupResponse(): status = 0x%02x\r\n");
//   LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
//
//   (void)addressing, (void)payloadLength, (void)payload;
//   return ZCL_SUCCESS_STATUS;
// }

/**************************************************************************//**
\brief Callback on receiving Group Membership Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
// static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload)
// {
//   appSnprintf(respStr);
//   appSnprintf(groupCountStr, payload->groupCount);
//
//   for (uint8_t i = 0; i < payload->groupCount; i++)
//     appSnprintf(groupStr, payload->groupList[i]);
//
//   LOG_STRING(respStr, "getGroupMembershipResponse()\r\n");
//   LOG_STRING(groupCountStr, "groupCount = %d\r\n");
//   LOG_STRING(groupStr, "groupId = 0x%04x\r\n");
//
//   (void)addressing, (void)payloadLength, (void)payload;
//   return ZCL_SUCCESS_STATUS;
// }

/**************************************************************************//**
\brief Callback on receiving Remove Group Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
// static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
// {
//   LOG_STRING(removeGroupRespStr, "removeGroupResponseInd()\r\n");
//   appSnprintf(removeGroupRespStr);
//
//   (void)addressing, (void)payloadLength, (void)payload;
//   return ZCL_SUCCESS_STATUS;
// }

/**************************************************************************//**
\brief Fills Add Group and Add Group If Identifying command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
// static void fillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group)
// {
//   payload->groupId      = group;
//   payload->groupName[0] = 0;
// }

/**************************************************************************//**
\brief Fills View Group and Remove Group command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
// static void fillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group)
// {
//   payload->groupId = group;
// }

/**************************************************************************//**
\brief Fills Get Group Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
// static uint8_t fillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list)
// {
//   payload->groupCount = count;
//
//   if (!count)
//     return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t); /*groupList[1]*/
//
//   for (uint8_t i = 0; i < count; i++)
//     payload->groupList[i] = list[i];
//
//   return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t) /*groupList[1]*/ + count * sizeof(uint16_t);
// }


/**************************************************************************//**
\brief Sends Add Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
// void groupsSendAddGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
//   uint16_t group, AddGroupResponseCb_t cb)
// {
//   ZCL_Request_t *req;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   serviceCallback = cb;
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
//   fillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

/**************************************************************************//**
\brief Sends View Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
// void groupsSendViewGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
//   uint16_t group)
// {
//   ZCL_Request_t *req;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID, sizeof(ZCL_ViewGroup_t));
//   fillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

/**************************************************************************//**
\brief Sends Get Group Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] count - group count;
\param[in] list  - group list;
******************************************************************************/
// void groupsSendGetGroupMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
//   uint8_t count, uint16_t *list)
// {
//   ZCL_Request_t *req;
//   uint8_t size;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   size = fillGetGroupMembershipPayload((ZCL_GetGroupMembership_t *)req->requestPayload, count, list);
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID, size);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

/**************************************************************************//**
\brief Sends Remove Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
// void groupsSendRemoveGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
//   uint16_t group)
// {
//   ZCL_Request_t *req;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID, sizeof(ZCL_RemoveGroup_t));
//   fillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

/**************************************************************************//**
\brief Sends Remove All Groups command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
// void groupsSendRemoveAllGroups(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
// {
//   ZCL_Request_t *req;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_ALL_GROUPS_COMMAND_ID, 0);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

/**************************************************************************//**
\brief Sends Add Group If Identifying command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
// void groupsSendAddGroupIfIdentifying(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
//   uint16_t group)
// {
//   ZCL_Request_t *req;
//
//   if (!(req = getFreeCommand()))
//     return;
//
//   fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
//   fillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
//   fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
//   commandManagerSendCommand(req);
// }

#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
// eof dlGroupsCluster.c
