/**************************************************************************//**
  \file  rScenesCluster.c

  \brief Scenes Cluster Implementation

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
#include <zcl/include/zclScenesCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                             Prototypes section
 ******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddSceneResponse_t *payload);
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload);
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload);
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload);
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload);
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload);

/*******************************************************************************
                             Static Variables section
 ******************************************************************************/
// Scenes Cluster commands
static ZCL_ScenesClusterCommands_t scenesClusterCommands =
{
  ZCL_DEFINE_SCENES_CLUSTER_COMMANDS(NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    addSceneResponseInd, viewSceneResponseInd,
    removeSceneResponseInd, removeAllScenesResponseInd,
    storeSceneResponseInd, getSceneMembershipResponseInd)
};


/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/***************************************************************************//**
\brief Gets Scenes Cluster commands.

\return Scenes Cluster commands.
******************************************************************************/
ZCL_ScenesClusterCommands_t *getScenesClusterCommands(void)
{
  return &scenesClusterCommands;
}

/**************************************************************************//**
\brief Callback on receive of Add Scene Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t addSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_AddSceneResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of View Scene Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t viewSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_ViewSceneResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of Remove Scene Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t removeSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveSceneResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of Remove All Scenes Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t removeAllScenesResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of Store Scene Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t storeSceneResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_StoreSceneResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

/**************************************************************************//**
\brief Callback on receive of Get Scene Membership Response

\param[in] addressing - addressing info
\param[in] payloadLength - length of payload
\param[in] payload - pointer to payload

\return operation status
******************************************************************************/
static ZCL_Status_t getSceneMembershipResponseInd(ZCL_Addressing_t *addressing,
  uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t*)payload);
}

#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rScenesCluster.c */
