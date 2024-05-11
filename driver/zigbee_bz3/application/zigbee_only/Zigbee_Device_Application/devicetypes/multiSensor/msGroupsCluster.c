/*******************************************************************************
  Multi-Sensor Groups cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    msGroupsCluster.c

  Summary:
    This file contains Multi-Sensor Groups cluster implementation.

  Description:
    This file contains Multi-Sensor Groups cluster implementation.
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

#ifdef APP_DEVICE_TYPE_MULTI_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msGroupsCluster.h>
#include <haClusters.h>
#include <zclOnOffCluster.h>
#include <zclLevelControlCluster.h>
#include <commandManager.h>
#include <uartManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

static void msFillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group);
static void msFillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group);
static uint8_t msFillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_GroupsClusterCommands_t msGroupsCommands =
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
void groupsClusterInit(void)
{}

/**************************************************************************//**
\brief Sends Add Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
  msFillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends View Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendViewGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID, sizeof(ZCL_ViewGroup_t));
  msFillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Get Group Membership command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] count - group count;
\param[in] list  - group list;
******************************************************************************/
void groupsSendGetGroupMembership(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint8_t count, uint16_t *list)
{
  ZCL_Request_t *req;
  uint8_t size;

  if (!(req = getFreeCommand()))
    return;

  size = msFillGetGroupMembershipPayload((ZCL_GetGroupMembership_t *)req->requestPayload, count, list);
  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID, size);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove Group command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveGroup(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_GROUP_COMMAND_ID, sizeof(ZCL_RemoveGroup_t));
  msFillViewRemoveGroupPayload((ZCL_ViewGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Remove All Groups command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendRemoveAllGroups(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_REMOVE_ALL_GROUPS_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Sends Add Group If Identifying command to bound devices

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node or number of group;
\param[in] ep    - endpoint number of destination device;
\param[in] group - group id
******************************************************************************/
void groupsSendAddGroupIfIdentifying(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t group)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID, sizeof(ZCL_AddGroup_t) - sizeof(uint8_t));
  msFillAddGroupIfIdentifyingPayload((ZCL_AddGroup_t *)req->requestPayload, group);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, GROUPS_CLUSTER_ID);
  commandManagerSendCommand(req);
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
  appSnprintf("removeGroupResponseInd()\r\n");

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Add Group and Add Group If Identifying command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void msFillAddGroupIfIdentifyingPayload(ZCL_AddGroup_t *payload, uint16_t group)
{
  payload->groupId      = group;
  payload->groupName[0] = 0;
}

/**************************************************************************//**
\brief Fills View Group and Remove Group command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static void msFillViewRemoveGroupPayload(ZCL_ViewGroup_t *payload, uint16_t group)
{
  payload->groupId = group;
}

/**************************************************************************//**
\brief Fills Get Group Membership command structure

\param[out] payload - pointer to command structure;
\param[in]  group   - group id
******************************************************************************/
static uint8_t msFillGetGroupMembershipPayload(ZCL_GetGroupMembership_t *payload, uint8_t count, uint16_t *list)
{
  payload->groupCount = count;

  if (!count)
    return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t); /*groupList[1]*/

  for (uint8_t i = 0; i < count; i++)
    payload->groupList[i] = list[i];

  return sizeof(ZCL_GetGroupMembership_t) - sizeof(uint16_t) /*groupList[1]*/ + count * sizeof(uint16_t);
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR
// eof msGroupsCluster.c

