/**************************************************************************//**
  \file  rEvents.c

  \brief Stack's Events functions implementations

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <rTypes.h>
#include <rMem.h>
#include <rParser.h>
#include <rAps.h>
#include <rSys.h>
#include <rDebug.h>
#include <ZAppSiIdentifiers.h>
#include <consts.h>
#include <systemenvironment/include/sysUtils.h>
//#include <resetReason.h>
#include <bufferallocator.h>
#include <rDebug.h>
#if CERTICOM_SUPPORT == 1
  #include <zcl/include/zclKeyEstablishmentCluster.h>
#endif

/******************************************************************************
                              Definitions section.
******************************************************************************/
#define R_SYS_EVENT_MGMT_SUBSCRIBE_TO_EVENT         0x01
#define R_SYS_EVENT_MGMT_UNSUBSCRIBE_FROM_EVENT     0x02

/******************************************************************************
                                 Types section
******************************************************************************/
BEGIN_PACK
typedef struct PACK _RSysEventMgmtRequest_t
{
  uint8_t reqType;
  SYS_EventId_t eventId;
  uint8_t singleCapture;
} RSysEventMgmtRequest_t;
END_PACK

/******************************************************************************
                        Static functions prototypes section.
******************************************************************************/
static void rSysEventListener(SYS_EventId_t ev, SYS_EventData_t data);

/*****************************************************************************
                              Static variables section
******************************************************************************/
static void APS_DataIndEndpoint_0x01(APS_DataInd_t *ind);
static void APS_DataIndEndpoint_0xf0(APS_DataInd_t *ind);
static void APS_DataIndEndpoint_0xef(APS_DataInd_t *ind);
static void rInitEndpointDescriptor(SimpleDescriptor_t *descriptor, Endpoint_t endpoint,
  ProfileId_t profileId);

static ClusterId_t endpointInClusterList[] = {CID_TRANSMIT_COUNTED_PACKETS, /**/
  CID_RESET_PACKET_COUNT, /**/
  CID_RETRIEVE_PACKET_COUNT, /**/
  CID_BUFFER_TEST_REQUEST, /**/
  CID_BUFFER_TEST_GROUP_REQUEST, /**/
  CID_ROUTE_DISCOVERY_REQUEST, /**/
  CID_FREEFORM_REQUEST, /**/
  CID_BROADCAST_REQUEST, /**/
  CID_BUFFER_TEST_RESPONSE
};

static ClusterId_t endpointOutClusterList[] = {CID_PACKET_COUNT_RESPONSE, /**/
  CID_BUFFER_TEST_RESPONSE, /**/
  CID_BUFFER_TEST_GROUP_RESPONSE, /**/
  CID_ROUTE_DISCOVERY_CONFIRM, /**/
  CID_FREEFORM_RESPONSE, /**/
  CID_FREEFORM_NO_DATA_RESPONSE, /**/
  CID_BROADCAST_TO_ALL_DEVICES_RESPONSE, /**/
  CID_BROADCAST_TO_ALL_RX_ON_WHEN_IDLE_DEVICES_RESPONSE, /**/
  CID_BROADCAST_TO_ALL_ROUTERS_AND_COORDINATOR_RESPONSE /**/};

static SimpleDescriptor_t simpleDescriptorEndpoint_0x01;
static SimpleDescriptor_t simpleDescriptorEndpoint_0xf0;
static SimpleDescriptor_t simpleDescriptorEndpoint_0xef;

static APS_RegisterEndpointReq_t apsRegisterEndpointReq_0x01 = {
  .simpleDescriptor = &simpleDescriptorEndpoint_0x01,
  .APS_DataInd = APS_DataIndEndpoint_0x01
};

static APS_RegisterEndpointReq_t apsRegisterEndpointReq_0xf0 = {
  .simpleDescriptor = &simpleDescriptorEndpoint_0xf0,
  .APS_DataInd = APS_DataIndEndpoint_0xf0
};

static APS_RegisterEndpointReq_t apsRegisterEndpointReq_0xef = {
  .simpleDescriptor = &simpleDescriptorEndpoint_0xef,
  .APS_DataInd = APS_DataIndEndpoint_0xef
};

static SYS_EventReceiver_t rSysEventReceiver = { .func = rSysEventListener};
static uint16_t singleCaptureMask;

/******************************************************************************
                   Implementations section
 ******************************************************************************/
void rInitEvents(void)
{
  // Endpoint descriptors initialization
  rInitEndpointDescriptor(&simpleDescriptorEndpoint_0x01, 0x01, R_TEST_PROFILE_1);
  rInitEndpointDescriptor(&simpleDescriptorEndpoint_0xf0, 0xf0, R_TEST_PROFILE_DEFAULT);
  rInitEndpointDescriptor(&simpleDescriptorEndpoint_0xef, 0xef, R_TEST_PROFILE_2);

  //Active endpoints register
  APS_RegisterEndpointReq(&apsRegisterEndpointReq_0x01); //Endpoint 0x01
  APS_RegisterEndpointReq(&apsRegisterEndpointReq_0xf0); //Endpoint 0xf0
  APS_RegisterEndpointReq(&apsRegisterEndpointReq_0xef); //Endpoint 0xef

//  if (WARM_RESET == HAL_ReadResetReason())
//  {
//    lastCommandId = 0;
//    rSysResetConfirm(NULL);
//  }
    rSysResetConfirm(NULL);
}

static void rInitEndpointDescriptor(SimpleDescriptor_t *descriptor, Endpoint_t endpoint,
  ProfileId_t profileId)
{
  rAssert(descriptor, R_DBG_REVENTS_NULL_POINTER);

  descriptor->endpoint = endpoint;
  descriptor->AppProfileId = profileId;
  descriptor->AppDeviceId = R_APP_DEVICE_ID;
  descriptor->AppDeviceVersion = 0;
  descriptor->Reserved = 0;
  descriptor->AppInClustersCount = ARRAY_SIZE(endpointInClusterList);
  descriptor->AppInClustersList = endpointInClusterList;
  descriptor->AppOutClustersCount = ARRAY_SIZE(endpointOutClusterList);
  descriptor->AppOutClustersList = endpointOutClusterList;
}

static void APS_DataIndEndpoint_0x01(APS_DataInd_t *ind)
{
  rApsDataInd(ind, 0x01);
}

static void APS_DataIndEndpoint_0xf0(APS_DataInd_t *ind)
{
  rApsDataInd(ind, 0xf0);
}

static void APS_DataIndEndpoint_0xef(APS_DataInd_t *ind)
{
  rApsDataInd(ind, 0xef);
}

#ifdef _BINDING_
/***********************************************************************************
  Stub for ZDO Binding Indication

  Parameters:
    bindInd - indication

  Return:
    none

 ***********************************************************************************/
void ZDO_BindIndication_CB(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/***********************************************************************************
  Stub for ZDO Unbinding Indication

  Parameters:
    unbindInd - indication

  Return:
    none

 ***********************************************************************************/
void ZDO_UnbindIndication_CB(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif /* _BINDING_ */

void ZDO_WakeUpInd_CB(void)
{
  ZS_CommandBuffer_t *commandBuffer = (ZS_CommandBuffer_t*) bufferAllocator.allocate();

  commandBuffer->commandFrame.commandId = R_ZDO_WAKEUP_INDICATION;
  commandBuffer->state = R_BUFFER_FREE_STATE;

  incomingFrameHandler(commandBuffer);
}

void ZDO_WakeUpConf(void)
{

}

void ZDO_MgmtNwkUpdateNotf_CB(ZDO_MgmtNwkUpdateNotf_t *ind)
{
  ZS_CommandBuffer_t *commandBuffer = (ZS_CommandBuffer_t*) bufferAllocator.allocate();

  commandBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_UPDATE_NOTIFY;
  commandBuffer->state = R_BUFFER_FREE_STATE;

  memcpy((uint8_t *)commandBuffer->commandFrame.payload,
    (uint8_t *)&ind->status, sizeof(ZDO_MgmtNwkUpdateNotf_t));

  incomingFrameHandler(commandBuffer);
}

/**************************************************************************//**
  \brief System events management request handler.
  \param[in] commandBuffer - data to process
  \return None.
******************************************************************************/
void rSysEventMgmtProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RSysEventMgmtRequest_t *pRequest = (RSysEventMgmtRequest_t *)commandBuffer->commandFrame.payload;

  if (R_SYS_EVENT_MGMT_SUBSCRIBE_TO_EVENT == pRequest->reqType)
  {
    if (pRequest->singleCapture)
    {
      rAssert(pRequest->eventId < sizeof(singleCaptureMask) * 8, R_DBG_EVENT_MGMT_ILL_REQ_ID_0);
      singleCaptureMask |= (1 << pRequest->eventId);
    }
    SYS_SubscribeToEvent(pRequest->eventId, &rSysEventReceiver);
  }
  else
  {
    rAssert(R_SYS_EVENT_MGMT_UNSUBSCRIBE_FROM_EVENT == pRequest->reqType, R_DBG_EVENT_MGMT_ILL_REQ_ID_1);
    SYS_UnsubscribeFromEvent(pRequest->eventId, &rSysEventReceiver);
  }
}

/**************************************************************************//**
  \brief Listener for system events.
  \param[in] ev - event id
  \param[in] data - data
  \return None.
******************************************************************************/
static void rSysEventListener(SYS_EventId_t ev, SYS_EventData_t data)
{
  ZS_CommandBuffer_t *commandBuffer = (ZS_CommandBuffer_t*) bufferAllocator.allocate();
  uint8_t length = 0;
  uint8_t *outBuf = commandBuffer->commandFrame.payload;

  commandBuffer->commandFrame.commandId = R_SYS_EVENT_NOTIFY;
  memcpy(outBuf, &ev, sizeof(SYS_EventId_t));
  length += sizeof(SYS_EventId_t);
  outBuf += sizeof(SYS_EventId_t);

  switch (ev)
  {
    case BC_EVENT_DEVICE_LEFT:
      memcpy(outBuf, (uint8_t *)data, sizeof(ExtAddr_t));
      length += sizeof(ExtAddr_t);
      outBuf += sizeof(ExtAddr_t);
    break;

    case BC_EVENT_BAD_FRAME_COUNTER:
    {
      memcpy(outBuf, (uint8_t *)&data, sizeof(ShortAddr_t));
      length += sizeof(ShortAddr_t);
      outBuf += sizeof(ShortAddr_t);
    }
    break;

#if CERTICOM_SUPPORT == 1
    case BC_EVENT_KE_CLUSTER_MATCH_DESC_RESP:
    {
      ZDO_MatchDescResp_t *zdpResp = &((ZDO_ZdpResp_t *)data)->respPayload.matchDescResp;
      ZS_ZdpMatchDescConf_t *rConf = (ZS_ZdpMatchDescConf_t *) outBuf;

      rConf->status = ((ZDO_ZdpResp_t *)data)->respPayload.status;
      rConf->resp = *zdpResp;
      length += offsetof (ZS_ZdpMatchDescConf_t, resp.matchList) + zdpResp->matchLength;
      outBuf += offsetof (ZS_ZdpMatchDescConf_t, resp.matchList) + zdpResp->matchLength;
    } 
    break;

    case BC_EVENT_KE_CLUSTER_INITIATE_KE_REQ:
    case BC_EVENT_KE_CLUSTER_INITIATE_KE_RESP:
      memcpy(outBuf, (uint8_t *)data, sizeof(ZCL_InitiateKeyEstablishmentCommand_t));
      length += sizeof(ZCL_InitiateKeyEstablishmentCommand_t);
      outBuf += sizeof(ZCL_InitiateKeyEstablishmentCommand_t);
    break;

    case BC_EVENT_KE_CLUSTER_EPH_DATA_REQ:
    case BC_EVENT_KE_CLUSTER_EPH_DATA_RESP:
      memcpy(outBuf, (uint8_t *)data, sizeof(ZCL_EphemeralDataCommand_t));
      length += sizeof(ZCL_EphemeralDataCommand_t);
      outBuf += sizeof(ZCL_EphemeralDataCommand_t);
    break;

    case BC_EVENT_KE_CLUSTER_CONF_KEY_REQ:
    case BC_EVENT_KE_CLUSTER_CONF_KEY_RESP:
      memcpy(outBuf, (uint8_t *)data, sizeof(ZCL_ConfirmKeyCommand_t));
      length += sizeof(ZCL_ConfirmKeyCommand_t);
      outBuf += sizeof(ZCL_ConfirmKeyCommand_t);
    break;
    
    case BC_EVENT_KE_CLUSTER_TERMINATE_CMD:
      *outBuf++ = *(uint8_t *)data;
      length++;
    break;
#endif // CERTICOM_SUPPORT == 1

    default:
      break;
  }

  commandBuffer->commandFrame.length = R_COMMAND_ID_SIZE + length;

  if (singleCaptureMask & (1 << ev))
  {
    singleCaptureMask ^= (1 << ev);
    SYS_UnsubscribeFromEvent(ev, &rSysEventReceiver);
  }

  serialManager.write(commandBuffer);
}

/* eof rEvents.c */
