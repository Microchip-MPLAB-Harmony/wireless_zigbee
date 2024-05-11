/**************************************************************************//**
  \file  rGroupsCluster.c

  \brief Groups Cluster Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/08/2011  A. Razinkov - Created.
 ******************************************************************************/

#if defined(_ZCL_SUPPORT_) && (APP_REDUCED_OTAU_SERVER == 0)
/*******************************************************************************
                             Includes section
 ******************************************************************************/
#include <stdbool.h>
#include <zcl/include/zcl.h>
#include <zcl/include/zclGroupsCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                             Prototypes section
 ******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddGroupResponse_t *payload);
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload);
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload);
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload);

/*******************************************************************************
                             Static Variables section
 ******************************************************************************/
/* Groups cluster commands */
static ZCL_GroupsClusterCommands_t groupsClusterCommands =
{
  ZCL_DEFINE_GROUPS_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL,
    addGroupResponseInd, viewGroupResponseInd,
    getGroupMembershipResponseInd, removeGroupResponseInd)
};


/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/***************************************************************************//**
\brief Gets Groups Cluster commands.

\return Groups Cluster commands.
******************************************************************************/
ZCL_GroupsClusterCommands_t *getGroupsClusterCommands(void)
{
  return &groupsClusterCommands;
}

/**************************************************************************//**
\brief Callback on receive of Add Group Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t addGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddGroupResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of View Group Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t viewGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_ViewGroupResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of View Group Membership Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t getGroupMembershipResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_GetGroupMembershipResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of Remove Group Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t removeGroupResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveGroupResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rGroupsCluster.c */
