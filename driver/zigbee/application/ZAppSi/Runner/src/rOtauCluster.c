/**************************************************************************//**
  \file  rOtauCluster.c

  \brief Otau Cluster Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
 ******************************************************************************/
#if defined(_ZCL_SUPPORT_) 
/*******************************************************************************
                             Includes section
 ******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclOTAUCluster.h>
#include <rZcl.h>
#include <rTypes.h>
#include <pds/include/wlPdsMemIds.h>
//#include <resetReason.h>

/******************************************************************************
                          Prototypes section
******************************************************************************/
static ZCL_Status_t queryNextImageReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauQueryNextImageReq_t *payload);
static ZCL_Status_t imageBlockReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauImageBlockReq_t *payload);
static ZCL_Status_t imagePageReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauImagePageReq_t *payload);
static ZCL_Status_t upgradeEndReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauUpgradeEndReq_t *payload);
#if APP_USE_OTAU == 1
static void meterOtauClusterIndication(ZCL_OtauAction_t action);
#endif // APP_USE_OTAU == 1

/*******************************************************************************
                   Global variables section
*******************************************************************************/
static ZCL_OtauClusterCommands_t otauServerCommands =
{
  OTAU_COMMANDS(NULL, queryNextImageReqInd, NULL, imageBlockReqInd, imagePageReqInd, NULL, \
                upgradeEndReqInd, NULL)
};
/***************************************************************************//**
\brief Query next image request indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer.

\return status of indication routine
*******************************************************************************/
static ZCL_Status_t queryNextImageReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauQueryNextImageReq_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *)payload);
}
/***************************************************************************//**
\brief Image block request indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer.

\return status of indication routine
*******************************************************************************/
static ZCL_Status_t imageBlockReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauImageBlockReq_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *)payload);
}
/***************************************************************************//**
\brief Image page request indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer.

\return status of indication routine
*******************************************************************************/
static ZCL_Status_t imagePageReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauImagePageReq_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *)payload);
}
/***************************************************************************//**
\brief Upgrade end request indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer.

\return status of indication routine
*******************************************************************************/
static ZCL_Status_t upgradeEndReqInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OtauUpgradeEndReq_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *)payload);
}
/***************************************************************************//**
\brief Gets Otau's cluster

\param[out] returns Otau's server cluster
*******************************************************************************/
ZCL_Cluster_t rGetOtauServerCluster(void)
{
  ZCL_Cluster_t cluster = DEFINE_OTAU_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, NULL, &otauServerCommands);

#if (defined(ATXMEGA256A3) || defined(ATXMEGA128A1) || defined(ATXMEGA256D3)) && defined(_ENABLE_PERSISTENT_SERVER_)
// stop pds to avoid usart overrrun when mcu sleeps to avoid xmega bug with eeprom saving.
  PDS_Stop();
#endif

  return cluster;
}

#if APP_USE_OTAU == 1
/***************************************************************************//**
\brief Starts otau discovery

\param[in] pointer to data buffer
*******************************************************************************/
void rOtauClientStart(ZS_CommandBuffer_t *commandBuffer)
{
  ZCL_OtauInitParams_t initParam;
  OtauInitParams_t *receivedData = (OtauInitParams_t *) commandBuffer->commandFrame.payload;

  initParam.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  initParam.otauEndpoint = receivedData->otauEndpoint;
  initParam.profileId = receivedData->profileId;
  initParam.firmwareVersion = receivedData->firmwareVersion;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, meterOtauClusterIndication))
  {
    /* failed to start otau service. Check for param validity */
  }
}

/***************************************************************************//**
\brief Get indication about all otau cluster actions.

\param[in] action - current action
*******************************************************************************/
static void meterOtauClusterIndication(ZCL_OtauAction_t action)
{
  if  (OTAU_DEVICE_SHALL_CHANGE_IMAGE == action) // client is ready to change image
    HAL_WarmReset();
}
#endif // APP_USE_OTAU

/***************************************************************************//**
 \brief Gets Otau Cluster commands.

 \param

 \return - Otau cluster commands.
******************************************************************************/
ZCL_OtauClusterCommands_t *getOtauServerClusterCommands(void)
{
  return &otauServerCommands;
}
#endif // ZCL_SUPPORT == 1
