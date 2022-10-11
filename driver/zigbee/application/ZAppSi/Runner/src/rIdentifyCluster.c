/**************************************************************************//**
  \file  rIdentifyCluster.c

  \brief Identify Cluster Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#if defined(_ZCL_SUPPORT_) && (APP_REDUCED_OTAU_SERVER == 0)
/*******************************************************************************
                             Includes section
 ******************************************************************************/
#include <stdbool.h>
#include <zcl/include/zcl.h>
#include <zcl/include/zclIdentifyCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                             Prototypes section
 ******************************************************************************/
static ZCL_Status_t identifyCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_Identify_t *message);
static ZCL_Status_t identifyQueryCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, uint8_t *message);
static ZCL_Status_t identifyQueryResponseCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
/*******************************************************************************
                             Static Variables section
 ******************************************************************************/
static ZCL_IdentifyClusterAttributes_t identifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

static ZCL_IdentifyClusterCommands_t identifyClusterServerCommands =
{
   IDENTIFY_CLUSTER_COMMANDS(identifyCommandInd, identifyQueryCommandInd, identifyQueryResponseCommandInd)
};
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/*******************************************************************************
 Identify command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t identifyCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_Identify_t *message)
{
#ifdef ZSE_ESP_CLUSTERS_LOGIC
  identifyClusterServerAttributes.identifyTime.value = message->identifyTime;
  return ZCL_SUCCESS_STATUS;
#else
  return commandInd(addr, payloadLength, (uint8_t *) message);
#endif /* _ZSE_ESP_CLUSTERS_LOGIC_ */
}
/*******************************************************************************
Identify Command is received.
*******************************************************************************/
/*******************************************************************************
 Identify Query command handler. Creates and sends Identify Query Response
 command.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t identifyQueryCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, uint8_t *message)
{
#ifdef ZSE_ESP_CLUSTERS_LOGIC
  if (identifyClusterServerAttributes.identifyTime.value != 0)
  {
    ZCL_Request_t *request = getZclRequest();
    ZCL_IdentifyQueryResponse_t *identifyQueryResponse = (ZCL_IdentifyQueryResponse_t*)request->requestPayload;

    request->id = ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID;
    request->defaultResponse = ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE;
    request->ZCL_Notify = NULL;
    request->dstAddressing = *addr;
    request->requestLength = sizeof(ZCL_IdentifyQueryResponse_t);
    identifyQueryResponse->timeout = identifyClusterServerAttributes.identifyTime.value;
    ZCL_CommandReq(request);
  }
  return ZCL_SUCCESS_STATUS;
#else
  return commandInd(addr, payloadLength, (uint8_t *)message);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
}
/*******************************************************************************
 Identify Query Response command handler.
 command.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    payload - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t identifyQueryResponseCommandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  return commandInd(addr, payloadLength, (uint8_t*)payload);
}
/***************************************************************************//**
\brief Timer callback function

\param

\return
******************************************************************************/
void identifyClusterTimerFired(void)
{
  if (identifyClusterServerAttributes.identifyTime.value != 0)
    identifyClusterServerAttributes.identifyTime.value--;
}
/***************************************************************************//**
 \brief Gets Identify Cluster Server Attributes.

 \param

 \return - Idetnfiy cluster attributes.
******************************************************************************/
ZCL_IdentifyClusterAttributes_t *getIdentifyClusterServerAttributes(void)
{
  return &identifyClusterServerAttributes;
}
/***************************************************************************//**
\brief Gets Identify Cluster Server Commands.

\param

\return - Identify cluster commands.
******************************************************************************/
ZCL_IdentifyClusterCommands_t *getIdentifyClusterServerCommands(void)
{
  return &identifyClusterServerCommands;
}

#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rIdentifyCluster.c */
