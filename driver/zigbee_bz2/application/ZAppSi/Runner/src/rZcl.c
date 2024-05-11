/**************************************************************************//**
  \file  rZcl.c

  \brief Zcl commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifdef _ZCL_SUPPORT_ 
/******************************************************************************
                   Includes section
******************************************************************************/
#ifdef _LINK_SECURITY_
#if CERTICOM_SUPPORT == 1
#include <genericEcc.h>
#include <zcl/include/eccAux.h>
#endif /* CERTICOM_SUPPORT == 1 */

#include <security/serviceprovider/include/sspHash.h>
#endif /* _LINK_SECURITY_ */
#include <zcl/include/zcl.h>
#if APP_REDUCED_OTAU_SERVER == 0
#include <zcl/include/zclMessagingCluster.h>
#include <zcl/include/zclPriceCluster.h>
#include <zcl/include/zclDemandResponseCluster.h>
#include <zcl/include/zclIdentifyCluster.h>
#include <zcl/include/zclGenericTunnelCluster.h>
#include <zcl/include/zclBACnetProtocolTunnelCluster.h>
#include <zcl/include/zclKeyEstablishmentCluster.h>
#include <rGenericTunnelCluster.h>
#include <rBACnetProtocolTunnelCluster.h>
#include <rGroupsCluster.h>
#include <rScenesCluster.h>
#endif /* APP_REDUCED_OTAU_SERVER == 0 */
#if APP_USE_OTAU == 1
#include <zcl/include/zclOTAUCluster.h>
#endif
#include <rOtauCluster.h>
#include <zcl/include/clusters.h>
#include <rTimer.h>
#include <rMem.h>
#include <rDebug.h>
#include <rZcl.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <ZAppSiDataTemplates.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
/*****************************************************************************
                               Definitions section
******************************************************************************/
#define READ_ATTRIBUTE_VALUE 0x00
#define WRITE_ATTRIBUTE_VALUE 0x01
#define MAX_SIZEOF_ATTRIBUTE_TYPE 8

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  ZCL_Request_t req;
  uint8_t       requestBuf[ZCL_REQUEST_BUF_SIZE];
  bool busy;
} ZclRequestElem_t;

/******************************************************************************
                   Global variables section
******************************************************************************/
ZCL_DeviceEndpoint_t appZclEndpoint;

/******************************************************************************
                   Static variables section
******************************************************************************/
#if APP_REDUCED_OTAU_SERVER == 0
static SimpleMeteringServerClusterAttributes_t meterAttributes =
{
  DEFINE_SIMPLE_METERING_SERVER_ATTRIBUTES(0, 0)
};

static ZCL_LevelControlClusterServerAttributes_t lcAttrs =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(4, 5)
};

static ZCL_DemandResponseAndLoadControlClusterCommands_t drlcCommands =
{
  DEFINE_DRLC_CLUSTER_COMMANDS(loadControlEventInd, cancelLoadControlEventInd,
                               cancelAllLoadControlEventsInd, reportEventStatusInd, getScheduledEventsInd)
};

ZCL_LevelControlClusterCommands_t levelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(moveToLevelInd, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL)
};

static ZCL_DemandResponseClientClusterAttributes_t drlcAttributes =
{
  DEFINE_DRLC_CLUSTER_CLIENT_ATTRIBUTES()
};

static ZCL_BasicClusterServerAttributes_t basicAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

static ZCL_OnOffSwitchConfigurationClusterServerAttributes_t switchServerAttributes =
{
  ZCL_DEFINE_ONOFF_SWITCH_CONFIGURATION_CLUSTER_SERVER_ATTRIBUTES()
};


#endif /* APP_REDUCED_OTAU_SERVER == 0 */
static ZCL_Cluster_t inOutClusters[MAX_CLUSTERS_AMOUNT];
static ClusterId_t inOutClusterIds[MAX_CLUSTERS_AMOUNT];

static ZclRequestElem_t zclReqPool[APP_ZCL_REQ_POOL_SIZE];

#ifdef ZSE_ESP_CLUSTERS_LOGIC
static RAppTimer_t clustersUtilityTimer;
#endif /* ZSE_ESP_CLUSTERS_LOGIC */

uint8_t getLastMessageReturnValue = ZCL_NOT_FOUND_STATUS;

#ifdef _LINK_SECURITY_
#if CERTICOM_SUPPORT == 1
  static ZCL_CertificateDesc_t  rCertificateDescriptor;
#endif /* CERTICOM_SUPPORT == 1 */
#endif /* _LINK_SECURITY_ */


#ifdef _LINK_SECURITY_
ZCL_StartSecurityReq_t zclStartSecurityReq;
#endif /* _LINK_SECURITY_ */

/******************************************************************************
                   Static functions prototypes section
******************************************************************************/
static inline void commandRequestAdditionalActions(const ZCL_Request_t *command, uint8_t direction);
static inline bool verifySignature(ZCL_Addressing_t *addr, ZCL_ReportEventStatus_t* payload);
static void rZclDefaultResponse(ZCL_Request_t *req, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZclRequestElem_t* getZclRequest(void);
#ifdef ZSE_ESP_CLUSTERS_LOGIC
static void timerFired(void);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
#if CERTICOM_SUPPORT == 1
#ifdef APP_ECDSA_SIGNATURE
static inline ZCL_Status_t getCertificateDescriptor(ZCL_CertificateDesc_t *certificateDesc);
#endif /* APP_ECDSA_SIGNATURE */
#endif /* CERTICOM_SUPPORT == 1 */

/******************************************************************************
                   Prototypes section
******************************************************************************/
void zclReset(void);
void timeClusterTimerFired(void);
ZCL_TimeClusterServerAttributes_t *getTimeAttributes(void);
ZCL_PriceClusterCommands_t* getPriceCommands(void);
MessagingClusterCommands_t *getMessagingCommands(void);
ZCL_IdentifyClusterAttributes_t *getIdentifyClusterServerAttributes(void);
ZCL_IdentifyClusterCommands_t *getIdentifyClusterServerCommands(void);
void saveMessageCommand(ZCL_Request_t *request);
void cancelMessageCommand(ZCL_Request_t *request);
void setPriceAutoResponse(ZS_CommandFrame_t* frame);
void identifyClusterTimerFired(void);

#ifdef _ZSE_CERTIFICATION_
extern void ZCL_KeSendTooLongCertificate(int8_t addLen);
#endif // _ZSE_CERTIFICATION_

/******************************************************************************
                   Implementations section
******************************************************************************/
#ifdef _ZSE_CERTIFICATION_
void rZclKeSecSendTooLongCertificate(ZS_CommandBuffer_t *commandBuffer)
{
  ZCL_KeSendTooLongCertificate(*commandBuffer->commandFrame.payload);
}
#endif // _ZSE_CERTIFICATION_

/***************************************************************************//**
\brief Returns free zcl request structure

\return Returns free zcl request structure if any, NULL otherwise
******************************************************************************/
static ZclRequestElem_t* getZclRequest(void)
{
  for (uint8_t i = 0; i < APP_ZCL_REQ_POOL_SIZE; i++)
    if (!zclReqPool[i].busy)
    {
      zclReqPool[i].busy = true;
      return &zclReqPool[i];
    }

  return NULL;
}
#if APP_REDUCED_OTAU_SERVER == 0
static void basicClusterInit(void)
{
  memcpy(basicAttributes.manufacturerName.value, "\x1f Atmel",sizeof(basicAttributes.manufacturerName.value));
  memcpy(basicAttributes.modelIdentifier.value, "\x1f Smart Energy Meter", sizeof(basicAttributes.modelIdentifier.value));
  memcpy(basicAttributes.dateCode.value, "\x0f 2016060300000", sizeof(basicAttributes.dateCode.value));
  memcpy(basicAttributes.swBuildId.value,"\x0f 0000000000000", sizeof(basicAttributes.swBuildId.value));
}
#endif
// **
// ** Function performs ZCL reset.
// **
void zclReset(void)
{
#ifdef ZSE_ESP_CLUSTERS_LOGIC
  rInitAppTimer(&clustersUtilityTimer, TIMER_REPEAT_MODE, 1000, timerFired);
  rStartAppTimer(&clustersUtilityTimer);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
#ifdef _LINK_SECURITY_
  ZCL_ResetSecurity();
#endif // _LINK_SECURITY_
#if APP_REDUCED_OTAU_SERVER == 0
  basicClusterInit();
#endif
}

static int countRecords(ZCL_GeneralCommandId_t id, uint8_t length, uint8_t *payload)
{
  ZCL_NextElement_t element;
  ZCL_Status_t status;
  int count = 0;

  element.id = id;
  element.payloadLength = length;
  element.payload = payload;

  do
  {
    ++count;
    element.content = NULL;
    status = ZCL_GetNextElement(&element);
  } while (ZCL_SUCCESS_STATUS == status);

  return ZCL_END_PAYLOAD_REACHED_STATUS == status ? count: 0;
}

/***************************************************************************//**
\brief Common ZCL command indication handler

\param addr - address the command came from.
\param payloadLength - the length of payload
\param payload - payload.

\return Status of operation.
******************************************************************************/
ZCL_Status_t commandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, uint8_t *payload)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclCommandIndication_t *rConf = (RZclCommandIndication_t *) confBuffer->commandFrame.payload;
  ZCL_Status_t result = ZCL_SUCCESS_STATUS;

  rConf->clusterId       = addr->clusterId;
  rConf->commandId       = *(payload - 1);
  rConf->srcAddrMode     = addr->addrMode;
  rConf->srcShortAddress = addr->addr.shortAddress;
  ExtAddr_t tempExtAddr;
  COPY_EXT_ADDR_A(&tempExtAddr,addr->addr.extAddress);
  rConf->srcExtAddress = tempExtAddr;
  rConf->srcProfileId    = addr->profileId;
  rConf->srcEndpointId   = addr->endpointId;
  rConf->srcClusterId    = addr->clusterId;
  rConf->sequenceNumber  = addr->sequenceNumber;
  rConf->direction       = ZCL_GetIncomingCommandDirectionBySrcClusterSide(addr->clusterSide);


  SYS_BYTE_MEMCPY(rConf->payload, payload, payloadLength);

  confBuffer->commandFrame.commandId = R_ZCL_COMMAND_INDICATION;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + sizeof(RZclCommandIndication_t) +
    payloadLength - sizeof(uint8_t);

  serialManager.write(confBuffer);
  return result;
}

ZCL_Status_t loadControlEventInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_LoadControlEvent_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}

ZCL_Status_t cancelLoadControlEventInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_CancelLoadControlEvent_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}

ZCL_Status_t cancelAllLoadControlEventsInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_CancelAllLoadControlEvents_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}

ZCL_Status_t reportEventStatusInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_ReportEventStatus_t *message)
{
  if (verifySignature(addr, message))
    return commandInd(addr, payloadLength, (uint8_t *)message);
  return ZCL_SUCCESS_STATUS;
}

ZCL_Status_t getScheduledEventsInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_GetScheduledEvents_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}

ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_MoveToLevel_t *message)
{
#if APP_REDUCED_OTAU_SERVER == 0
  lcAttrs.currentLevel.value = message->level;
  ZCL_ReportOnChangeIfNeeded(&lcAttrs.currentLevel);
#endif
  return commandInd(addr, payloadLength, (uint8_t *)message);
}

/*
static void rAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZclAttributeEventInd_t *rConf = (ZS_ZclAttributeEventInd_t*)confBuffer->commandFrame.payload;

  rConf->clusterId = addressing->clusterId;
  rConf->event = event;
  rConf->srcAddrMode = addressing->addrMode;
  rConf->srcEndpointId = addressing->endpointId;
  rConf->srcExtAddress = addressing->addr.extAddress;
  rConf->srcShortAddress = addressing->addr.shortAddress;
  rConf->profileId = addressing->profileId;
  rConf->attributeId = attributeId;

  confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_EVENT_IND;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZclAttributeEventInd_t);

  serialManager.write(confBuffer);

}
*/

static void rZclReportInd(ZCL_Addressing_t *addr, uint8_t reportLength, uint8_t *report)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclReportIndication_t *rConf = (RZclReportIndication_t *) confBuffer->commandFrame.payload;

  rConf->clusterId       = addr->clusterId;
  rConf->srcAddrMode     = addr->addrMode;
  rConf->srcShortAddress = addr->addr.shortAddress;
  ExtAddr_t tempExtAddr;
  COPY_EXT_ADDR_A(&tempExtAddr, addr->addr.extAddress);
  rConf->srcExtAddress = tempExtAddr;
  rConf->srcProfileId    = addr->profileId;
  rConf->srcEndpointId   = addr->endpointId;
  rConf->srcClusterId    = addr->clusterId;

  rConf->attributesCount = countRecords(ZCL_REPORT_ATTRIBUTES_COMMAND_ID, reportLength, report);
  rConf->reportLength = reportLength;
  SYS_BYTE_MEMCPY(rConf->report, report, reportLength);

  confBuffer->commandFrame.commandId = R_ZCL_REPORT_INDICATION;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + sizeof(RZclReportIndication_t) +
    reportLength - sizeof(uint8_t);

  serialManager.write(confBuffer);
}

#ifdef _LINK_SECURITY_
void rZclStartSecurityConfirm(ZCL_StartSecurityConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclStartSecurityConfirm_t *confirm = (RZclStartSecurityConfirm_t *) confBuffer->commandFrame.payload;

  confirm->status = conf->status;
  confBuffer->commandFrame.commandId = R_ZCL_START_SECURITY_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclStartSecurityConfirm_t);
  serialManager.write(confBuffer);
}
#endif /* _LINK_SECURITY_ */

/**************************************************************************//**
  \brief If ZCL security is used starts Key Establishment procedure, otherwise
         immediately returns confirm.

  \param[in] commandBuffer - pointer to the incoming string.

  \return None.
******************************************************************************/
void rZclStartSecurityRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
#ifndef _LINK_SECURITY_
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclStartConfirm_t *conf = (RZclStartConfirm_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclStartSecurityConfirm_t);
  confBuffer->commandFrame.commandId = R_ZCL_START_SECURITY_CONFIRM;
  conf->status = ZCL_SUCCESS_STATUS;
  serialManager.write(confBuffer);
#else
  RZclStartSecurityRequest_t *rReq = (RZclStartSecurityRequest_t *) commandBuffer->commandFrame.payload;

  if (rReq->useSpecialRemoteAddress)
    COPY_EXT_ADDR(zclStartSecurityReq.remoteAddress, rReq->remoteAddress);
  else
    COPY_EXT_ADDR(zclStartSecurityReq.remoteAddress, *APS_GetTrustCenterAddress());

  zclStartSecurityReq.ZCL_StartSecurityConf = rZclStartSecurityConfirm;
  ZCL_StartSecurityReq(&zclStartSecurityReq);
#endif // _LINK_SECURITY_
   // to kill compiler warning
  (void)commandBuffer;
}

// **
// ** Common Cluster Initializing function on User Request
// **
// Note: to add the parameters checking
void rZclStartRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclStartRequest_t *rReq = (RZclStartRequest_t *) commandBuffer->commandFrame.payload;

  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclStartConfirm_t *conf = (RZclStartConfirm_t *) confBuffer->commandFrame.payload;

  uint8_t totalClustersCount = rReq->inClustersCount + rReq->outClustersCount;

  if (MAX_CLUSTERS_AMOUNT >= totalClustersCount)
  {
    //SYS_BYTE_MEMCPY(&inOutClusterIds[0], &rReq->inOutClusterIds[0], totalClustersCount * sizeof(ClusterId_t));
    for (uint8_t i = 0; i < totalClustersCount; ++i)
      inOutClusterIds[i] = rReq->inOutClusterIds[i];
  }
  else
  {
    ;// TODO: indicate error
  }

  // Fill cluster parameters
  for (uint8_t i = 0; i < totalClustersCount; ++i)
  {
    bool server = (i < rReq->inClustersCount);
    inOutClusters[i].id = inOutClusterIds[i];

    if (server)
      inOutClusters[i].options.type = ZCL_SERVER_CLUSTER_TYPE;
    else
      inOutClusters[i].options.type = ZCL_CLIENT_CLUSTER_TYPE;

    inOutClusters[i].options.security = ZCL_NETWORK_KEY_CLUSTER_SECURITY;
    inOutClusters[i].options.reserved = 0;

    inOutClusters[i].attributesAmount = 0;
    inOutClusters[i].commandsAmount = 0;
    inOutClusters[i].ZCL_ReportInd = rZclReportInd;
    inOutClusters[i].ZCL_DefaultRespInd = rZclDefaultResponse;
    inOutClusters[i].ZCL_AttributeEventInd = NULL; //rAttributeEventInd;

    switch (inOutClusterIds[i])
    {
#if APP_REDUCED_OTAU_SERVER == 0
      case IDENTIFY_CLUSTER_ID:
      {
        if (server)
        {
          inOutClusters[i].attributesAmount = ZCL_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)getIdentifyClusterServerAttributes();

          inOutClusters[i].commandsAmount = ZCL_IDENTIFY_CLUSTER_COMMANDS_AMOUNT;
          inOutClusters[i].commands = (uint8_t *)getIdentifyClusterServerCommands();
        }
        else
        {
          inOutClusters[i].commandsAmount = ZCL_IDENTIFY_CLUSTER_COMMANDS_AMOUNT;
          inOutClusters[i].commands = (uint8_t *)getIdentifyClusterServerCommands();
        }
      }
      break;

      case SIMPLE_METERING_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (server)
        {
          inOutClusters[i].attributesAmount = SIMPLE_METERING_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)&meterAttributes;
        };
      }
      break;

      case MESSAGE_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        inOutClusters[i].commandsAmount = MESSAGE_CLUSTER_COMMANDS_AMOUNT;
        inOutClusters[i].commands = (uint8_t *)getMessagingCommands();
      }
      break;

      case PRICE_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        inOutClusters[i].commandsAmount = PRICE_CLUSTER_COMMANDS_AMOUNT;
        inOutClusters[i].commands = (uint8_t *)getPriceCommands();
      }
      break;

      case DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (!server)
        {
          inOutClusters[i].attributesAmount = DRLC_CLUSTER_CLIENT_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)&drlcAttributes;
        };

        inOutClusters[i].commandsAmount = DRLC_CLUSTER_COMMANDS_AMOUNT;
        inOutClusters[i].commands = (uint8_t *)&drlcCommands;
      }
      break;

      case BASIC_CLUSTER_ID:
      {
        if (server)
        {
          inOutClusters[i].attributesAmount = ZCL_BASIC_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)&basicAttributes;
        };
      }
      break;

      case TIME_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (server)
        {
          inOutClusters[i].attributesAmount = ZCL_TIME_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)getTimeAttributes();
        };
      }
      break;
#if CERTICOM_SUPPORT == 1
      case ZCL_KEY_ESTABLISHMENT_CLUSTER_ID:
      {
        inOutClusters[i] = *keGetClusterDescriptor(server);
      }
      break;
#endif /* CERTICOM_SUPPORT == 1 */

      case GENERIC_TUNNEL_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (server)
        {
          inOutClusters[i].attributesAmount = ZCL_GENERIC_TUNNEL_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t*)getGenericTunnelClusterServerAttributes();
        }

        inOutClusters[i].commandsAmount = ZCL_GENERIC_TUNNEL_COMMANDS_AMOUNT;
        inOutClusters[i].commands = (uint8_t *)getGenericTunnelClusterCommands();
      }
      break;

      case BACNET_PROTOCOL_TUNNEL_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;

        if (server)
        {
          inOutClusters[i].commandsAmount = ZCL_BACNET_PROTOCOL_TUNNEL_COMMANDS_AMOUNT;
          inOutClusters[i].commands = (uint8_t *)getBACNetProtocolTunnelCommands();
        }
      }
      break;

      case ONOFF_SWITCH_CONFIGURATION_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (server)
        {
          inOutClusters[i].commandsAmount = ZCL_ONOFF_SWITCH_CONFIGURATION_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].commands = (uint8_t *)&switchServerAttributes;
        }
      }
      break;

      case GROUPS_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (!server)
        {
          inOutClusters[i].commandsAmount = ZCL_GROUPS_CLUSTER_COMMANDS_AMOUNT;
          inOutClusters[i].commands = (uint8_t*)getGroupsClusterCommands();
        }
      }
      break;

      case SCENES_CLUSTER_ID:
      {
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (!server)
        {
          inOutClusters[i].commandsAmount = ZCL_SCENES_CLUSTER_COMMANDS_AMOUNT;
          inOutClusters[i].commands = (uint8_t*)getScenesClusterCommands();
        }
      }
      break;

      case ONOFF_CLUSTER_ID:
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        break;
      case LEVEL_CONTROL_CLUSTER_ID:
        inOutClusters[i].options.security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY;
        if (server)
        {
          inOutClusters[i].attributesAmount = ZCL_LEVEL_CONTROL_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
          inOutClusters[i].attributes = (uint8_t *)&lcAttrs;
        };
        inOutClusters[i].commandsAmount = ZCL_LEVEL_CONTROL_CLUSTER_COMMANDS_AMOUNT;
        inOutClusters[i].commands = (uint8_t *)&levelControlCommands;
      break;
#endif /* APP_REDUCED_OTAU_SERVER == 0 */

      case OTAU_CLUSTER_ID:
      {
        if (server)
          inOutClusters[i] = rGetOtauServerCluster();
#if APP_USE_OTAU == 1
        else
          inOutClusters[i] = ZCL_GetOtauClientCluster();
#endif // APP_USE_OTAU
        inOutClusters[i].ZCL_ReportInd = rZclReportInd;
        inOutClusters[i].ZCL_DefaultRespInd = rZclDefaultResponse;
      }
      break;

      default:
        // TODO: indicate error
      break;
    }
  }

  appZclEndpoint.simpleDescriptor.endpoint = rReq->endpoint;
  appZclEndpoint.simpleDescriptor.AppProfileId = rReq->appProfileId;
  appZclEndpoint.simpleDescriptor.AppDeviceId = rReq->appDeviceId;
  appZclEndpoint.simpleDescriptor.AppInClustersCount = rReq->inClustersCount;
  appZclEndpoint.simpleDescriptor.AppInClustersList = &inOutClusterIds[0];
  appZclEndpoint.simpleDescriptor.AppOutClustersCount = rReq->outClustersCount;
  appZclEndpoint.simpleDescriptor.AppOutClustersList = &inOutClusterIds[rReq->inClustersCount];
  appZclEndpoint.serverCluster = &inOutClusters[0];
  appZclEndpoint.clientCluster = &inOutClusters[rReq->inClustersCount];

  ZCL_RegisterEndpoint(&appZclEndpoint);

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclStartConfirm_t);
  confBuffer->commandFrame.commandId = R_ZCL_START_CONFIRM;
  conf->status = ZCL_SUCCESS_STATUS;
  serialManager.write(confBuffer);

  // initialize generic tunnel cluster attributes
#if APP_REDUCED_OTAU_SERVER == 0
  ZCL_GenericTunnelClusterServerAttributes_t *attributes = getGenericTunnelClusterServerAttributes();
  uint8_t *localhost = (uint8_t*)"localhost";

  attributes->protocolAddress.value[0] = 9; // the size of localhost string
  SYS_BYTE_MEMCPY(&attributes->protocolAddress.value[1], localhost, 9);
#endif /* APP_REDUCED_OTAU_SERVER == 0 */
}

/********************************************************************//**
// ** Starts the reporting 
***********************************************************************/
void rZclStartReportingRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZCL_StartReporting();
  (void)commandBuffer; 
}

void rZclClusterSecurityProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclSetClusterSecurityRequest_t *rReq = (RZclSetClusterSecurityRequest_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclSetClusterSecurityConfirm_t rConf = {.status = 0};
  uint8_t clustersCount = appZclEndpoint.simpleDescriptor.AppInClustersCount + appZclEndpoint.simpleDescriptor.AppOutClustersCount;

  for (uint8_t i = 0; i < clustersCount; i++)
    if (inOutClusters[i].id == rReq->clusterId)
    {
      inOutClusters[i].options.security = rReq->security;
      rConf.status = 1;
    }

  confBuffer->commandFrame.commandId = R_ZCL_SET_CLUSTER_SECURITY_CONFIRM;
  SYS_BYTE_MEMCPY(confBuffer->commandFrame.payload, &rConf.status, sizeof(uint8_t));
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclSetClusterSecurityConfirm_t);

  serialManager.write(confBuffer);
}

//The response of ZLC Read Attributes & Write Attributes like commands
// Also Report group commands supported
//
static void rZclAttributeResponse(ZCL_Notify_t *ntfy)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclAttributeResponse_t *rConf = (RZclAttributeResponse_t *) confBuffer->commandFrame.payload;
  uint8_t commandId = GET_PARENT_BY_FIELD(ZCL_Request_t, notify, ntfy)->id;
  ZclRequestElem_t *reqElem = GET_PARENT_BY_FIELD(ZclRequestElem_t, req.notify, ntfy);

  reqElem->busy = false;
  rConf->status = ntfy->status;

  SYS_BYTE_MEMCPY(rConf->records, ntfy->responsePayload, ntfy->responseLength);

  // Determine type of records in response
  if (ZCL_READ_ATTRIBUTES_COMMAND_ID == commandId)
  {
    commandId = ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID;
  }
  else if (ZCL_WRITE_ATTRIBUTES_COMMAND_ID == commandId)
  {
    commandId = ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID;
  }
  else if (ZCL_CONFIGURE_REPORTING_COMMAND_ID == commandId)
  {
    commandId = ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID;
  }
  else if (ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID == commandId)
  {
    commandId = ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID;
  }
  else if (ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID == commandId)
  {
    // this is woraround because discovery complete value is omitted
    commandId = ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID;
    uint8_t *ptr = confBuffer->commandFrame.payload;

    SYS_BYTE_MEMCPY(ptr, &ntfy->status, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
    ptr += sizeof(commandId);

    // copy discovery complete value
    SYS_BYTE_MEMCPY(ptr, ntfy->responsePayload, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    // copy records count
    uint8_t recordsCount = countRecords((ZCL_GeneralCommandId_t)commandId,
            (ntfy->responseLength - sizeof(uint8_t)),
            (ntfy->responsePayload + sizeof(uint8_t)));

    SYS_BYTE_MEMCPY(ptr, &recordsCount, sizeof(recordsCount));
    ptr += sizeof(recordsCount);

    SYS_BYTE_MEMCPY(ptr, (ntfy->responsePayload + sizeof(uint8_t)), (ntfy->responseLength - sizeof(uint8_t)));

    confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_RESPONSE;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + ntfy->responseLength + sizeof(RZclAttributeResponse_t) - 1;

    serialManager.write(confBuffer);

    return;
  }
  else if ((ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID == commandId) || (ZCL_DISCOVER_COMMANDS_GENERATED_COMMAND_ID == commandId))
  {
    if (ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID == commandId)
      commandId = ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE_COMMAND_ID;
    else
      commandId = ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE_COMMAND_ID;

    uint8_t *ptr = confBuffer->commandFrame.payload;

    SYS_BYTE_MEMCPY(ptr, &ntfy->status, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
    ptr += sizeof(commandId);

    // copy discovery complete value
    SYS_BYTE_MEMCPY(ptr, ntfy->responsePayload, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    // copy records count
    uint8_t recordsCount = countRecords((ZCL_GeneralCommandId_t)commandId,
            (ntfy->responseLength - sizeof(uint8_t)),
            (ntfy->responsePayload + sizeof(uint8_t)));

    SYS_BYTE_MEMCPY(ptr, &recordsCount, sizeof(recordsCount));
    ptr += sizeof(recordsCount);

    SYS_BYTE_MEMCPY(ptr, (ntfy->responsePayload + sizeof(uint8_t)), (ntfy->responseLength - sizeof(uint8_t)));

    confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_RESPONSE;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + ntfy->responseLength + sizeof(RZclAttributeResponse_t) - 1;

    serialManager.write(confBuffer);
    return;

  }
  else if (ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID == commandId)
  {
    commandId = ZCL_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE_COMMAND_ID;
    uint8_t *ptr = confBuffer->commandFrame.payload;

    SYS_BYTE_MEMCPY(ptr, &ntfy->status, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
    ptr += sizeof(commandId);

    // copy discovery complete value
    SYS_BYTE_MEMCPY(ptr, ntfy->responsePayload, sizeof(uint8_t));
    ptr += sizeof(uint8_t);

    // copy records count
    uint8_t recordsCount = countRecords((ZCL_GeneralCommandId_t)commandId,
            (ntfy->responseLength - sizeof(uint8_t)),
            (ntfy->responsePayload + sizeof(uint8_t)));

    SYS_BYTE_MEMCPY(ptr, &recordsCount, sizeof(recordsCount));
    ptr += sizeof(recordsCount);

    SYS_BYTE_MEMCPY(ptr, (ntfy->responsePayload + sizeof(uint8_t)), (ntfy->responseLength - sizeof(uint8_t)));

    confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_RESPONSE;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + ntfy->responseLength + sizeof(RZclAttributeResponse_t) - 1;

    serialManager.write(confBuffer);

    return;
  }

  rConf->recordsCount = countRecords((ZCL_GeneralCommandId_t) commandId, ntfy->responseLength, ntfy->responsePayload);
  rConf->id = commandId;

  confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + ntfy->responseLength + sizeof(RZclAttributeResponse_t) - 1;

  serialManager.write(confBuffer);
}

//The confirm handler of cluster specific command requests
static void rZclCommandConfirm(ZCL_Notify_t *ntfy)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclCommandConfirm_t *rConf = (RZclCommandConfirm_t *) confBuffer->commandFrame.payload;
  ZclRequestElem_t *reqElem = GET_PARENT_BY_FIELD(ZclRequestElem_t, req.notify, ntfy);

  reqElem->busy = false;
  rConf->status = ntfy->status;

  confBuffer->commandFrame.commandId = R_ZCL_COMMAND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + sizeof(RZclCommandConfirm_t);

  serialManager.write(confBuffer);
}

//The default response handler
static void rZclDefaultResponse(ZCL_Request_t *req, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclDefaultResponseInd_t *rInd = (RZclDefaultResponseInd_t*)confBuffer->commandFrame.payload;

  SYS_BYTE_MEMCPY(rInd, payload, payloadLength);

  confBuffer->commandFrame.commandId = R_ZCL_DEFAULT_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE  + sizeof(RZclDefaultResponseInd_t);
  serialManager.write(confBuffer);

  (void)addressing;
  (void)req;
}

void rZclNextSequenceNumberReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  uint8_t *seqNum = confBuffer->commandFrame.payload;
  *seqNum = ZCL_GetNextSeqNumber();

  confBuffer->commandFrame.commandId = R_ZCL_NEXT_SEQUENCE_NUMBER_RESP;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclNextSequenceNumberResp_t);

  serialManager.write(confBuffer);
  (void)commandBuffer;
}

void rZclAttributeRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclAttributeRequest_t *rReq = (RZclAttributeRequest_t *) commandBuffer->commandFrame.payload;
  int length = commandBuffer->commandFrame.length - sizeof(RZclAttributeRequest_t) -
               sizeof(uint16_t) + sizeof(rReq->request);
  ZclRequestElem_t *reqElem = getZclRequest();

  if (!reqElem)
    return;

  reqElem->req.id                        = rReq->commandId;
  reqElem->req.dstAddressing.addrMode    = (APS_AddrMode_t)rReq->addrMode;
  if (APS_SHORT_ADDRESS == rReq->addrMode)
    reqElem->req.dstAddressing.addr.shortAddress = rReq->shortAddress;
  else if (APS_EXT_ADDRESS == rReq->addrMode)
  {
    ExtAddr_t tempExtAddr = rReq->extAddress;
    COPY_EXT_ADDR_A(reqElem->req.dstAddressing.addr.extAddress, &tempExtAddr);
  }

  reqElem->req.dstAddressing.clusterId   = rReq->clusterId;
  reqElem->req.dstAddressing.clusterSide = getDstClusterSideByOutgoingCommandDirection(rReq->commandOptions.direction);
  reqElem->req.dstAddressing.endpointId  = rReq->dstEndpoint;
  reqElem->req.dstAddressing.profileId   = rReq->profileId;
  reqElem->req.endpointId                = rReq->endpoint;
  reqElem->req.requestLength             = length;
  reqElem->req.requestPayload            = reqElem->requestBuf;
  reqElem->req.defaultResponse           = rReq->defaultResponse;

  SYS_BYTE_MEMCPY(reqElem->requestBuf, rReq->request, length);

  reqElem->req.ZCL_Notify = rZclAttributeResponse;
  ZCL_AttributeReq(&reqElem->req);
}

void rZclCommandRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclCommandRequest_t *rReq = (RZclCommandRequest_t *) commandBuffer->commandFrame.payload;
  int length = commandBuffer->commandFrame.length - sizeof(RZclCommandRequest_t) -
               sizeof(uint16_t) + sizeof(rReq->request);
#if APP_REDUCED_OTAU_SERVER == 1
  ZCL_OtauClusterCommands_t *otauServerCommands = getOtauServerClusterCommands();
#endif // APP_REDUCED_OTAU_SERVER
  ZclRequestElem_t *reqElem = getZclRequest();

  if (!reqElem)
    return;

  reqElem->req.id                        = rReq->commandId;
  reqElem->req.dstAddressing.addrMode    = (APS_AddrMode_t)rReq->addrMode;
  if (APS_SHORT_ADDRESS == rReq->addrMode)
    reqElem->req.dstAddressing.addr.shortAddress = rReq->shortAddress;
  else if (APS_EXT_ADDRESS == rReq->addrMode)
  {
    ExtAddr_t tempExtAddr;
    tempExtAddr = rReq->extAddress;
    COPY_EXT_ADDR_A(reqElem->req.dstAddressing.addr.extAddress, &tempExtAddr);
  }

  reqElem->req.dstAddressing.clusterId   = rReq->clusterId;
  reqElem->req.dstAddressing.clusterSide = getDstClusterSideByOutgoingCommandDirection(rReq->commandOptions.direction);
  reqElem->req.dstAddressing.endpointId  = rReq->dstEndpoint;
  reqElem->req.dstAddressing.profileId   = rReq->profileId;
  reqElem->req.dstAddressing.sequenceNumber = rReq->sequenceNumber;
  reqElem->req.endpointId                = rReq->endpoint;
  reqElem->req.requestLength             = length;
  reqElem->req.requestPayload            = reqElem->requestBuf;
  reqElem->req.defaultResponse           = rReq->defaultResponse;

  SYS_BYTE_MEMCPY(reqElem->requestBuf, rReq->request, length);

#ifdef ZSE_ESP_CLUSTERS_LOGIC
  if (MESSAGE_CLUSTER_ID == reqElem->req.dstAddressing.clusterId)
  {
    if (ZCL_DIRECTION_FROM_SERVER == rReq->commandOptions.direction)
    {
      if (DISPLAY_MESSAGE_COMMAND_ID == reqElem->req.id)
      {
        saveMessageCommand(&zclRequest);
      }
      else if (CANCEL_MESSAGE_COMMAND_ID == reqElem->req.id)
      {
        cancelMessageCommand(&zclRequest);
      }
    }
  }
  setPriceAutoResponse(&commandBuffer->commandFrame);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
  commandRequestAdditionalActions(&reqElem->req, (uint8_t)rReq->commandOptions.direction);
  reqElem->req.ZCL_Notify = rZclCommandConfirm;
#if APP_REDUCED_OTAU_SERVER == 1
  if (ZCL_COMMAND_NO_ACK == rReq->commandOptions.ackRequest)
    otauServerCommands->imageBlockResp.options.ackRequest = ZCL_COMMAND_NO_ACK;
  else
    otauServerCommands->imageBlockResp.options.ackRequest = ZCL_COMMAND_ACK;
#endif // APP_REDUCED_OTAU_SERVER
  ZCL_CommandReq(&reqElem->req);
}

void rZclAttributeValueProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclReadAttributeValue_t *readAttributeValue =
          (RZclReadAttributeValue_t*)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

  if (READ_ATTRIBUTE_VALUE == readAttributeValue->commandId) // read
  {
    uint8_t attrType;
    RZclReadAttributeValueConfirm_t *confirm =
            (RZclReadAttributeValueConfirm_t*)confBuffer->commandFrame.payload;

    ZCL_Status_t status = ZCL_ReadAttributeValue(readAttributeValue->endpoint,
                            readAttributeValue->clusterId,
                            readAttributeValue->direction,
                            readAttributeValue->attributeId,
                            &attrType,
                            confirm->value
                            );

    confirm->status = status;
    confirm->commandId = READ_ATTRIBUTE_VALUE;
    confirm->type = attrType;

    confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_VALUE_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE +
      sizeof(RZclReadAttributeValueConfirm_t) +
        ZCL_GetAttributeLength(attrType, confirm->value);
  }
  else if (WRITE_ATTRIBUTE_VALUE == readAttributeValue->commandId) // write
  {
    RZclWriteAttributeValue_t *writeAttributeValue =
            (RZclWriteAttributeValue_t*)commandBuffer->commandFrame.payload;

    ZCL_Status_t status = ZCL_WriteAttributeValue(writeAttributeValue->endpoint,
                            writeAttributeValue->clusterId,
                            writeAttributeValue->direction,
                            writeAttributeValue->attributeId,
                            writeAttributeValue->type,
                            writeAttributeValue->value);

    RZclWriteAttributeValueConfirm_t *confirm =
            (RZclWriteAttributeValueConfirm_t*)confBuffer->commandFrame.payload;

    confirm->status = status;
    confirm->commandId = WRITE_ATTRIBUTE_VALUE;

    confBuffer->commandFrame.commandId = R_ZCL_ATTRIBUTE_VALUE_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclWriteAttributeValueConfirm_t);
  }

  serialManager.write(confBuffer);

}

#ifdef _LINK_SECURITY_
void rZclCommandGetProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclGetConfirm_t *confirm = (RZclGetConfirm_t *) confBuffer->commandFrame.payload;
  ZS_ZclGetRequest_t *req = (ZS_ZclGetRequest_t*)commandBuffer->commandFrame.payload;

  ZCL_Get_t zclGet;
  ZCL_LinkKeyDesc_t linkKeyDesc;
#if CERTICOM_SUPPORT == 1
  ZCL_CertificateDesc_t keCertificateDesc;
#endif /* CERTICOM_SUPPORT == 1 */

  //ZCL_Get primitive prepare
  zclGet.attr.id = (ZCL_SecurityAttrId_t) req->id;

  if (ZCL_LINK_KEY_DESC_ID == zclGet.attr.id)
  {
    linkKeyDesc.addr = req->addr;
    zclGet.attr.value.linkKeyDesc = &linkKeyDesc;
  }
#if CERTICOM_SUPPORT == 1
  else if (ZCL_CERTIFICATE_DESC_ID == zclGet.attr.id)
  {
    zclGet.attr.value.certificateDesc = &keCertificateDesc;
  }
#endif /* CERTICOM_SUPPORT == 1 */

  ZCL_Get(&zclGet);

  //Confirm prepare
  confirm->status = zclGet.status;
  confirm->id = zclGet.attr.id;
  confirm->length = zclGet.attr.length;

  //Attribute value
#if CERTICOM_SUPPORT == 1
  if (ZCL_KE_ACTIVE_ENDPOINT_ID == zclGet.attr.id)
  {
    confirm->value.endpoint = zclGet.attr.value.endpoint;
  }
  else
#endif /* CERTICOM_SUPPORT == 1 */

  if (ZCL_NETWORK_KEY_ID == zclGet.attr.id)
  {
    SYS_BYTE_MEMCPY(&confirm->value.networkKey, zclGet.attr.value.networkKey, zclGet.attr.length);
  }
  else if (ZCL_LINK_KEY_DESC_ID == zclGet.attr.id)
  {
    confirm->value.linkKeyDesc.addr = linkKeyDesc.addr;
    SYS_BYTE_MEMCPY(confirm->value.linkKeyDesc.key, linkKeyDesc.key, 16);
  }
  confBuffer->commandFrame.commandId = R_ZCL_GET_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t) /*status*/ + sizeof(uint8_t) /*id*/ +
                                    sizeof(uint8_t) /*length*/ + confirm->length /*value*/;
  serialManager.write(confBuffer);

}

void rZclCommandSetProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZclSetConfirm_t *confirm = (RZclSetConfirm_t *) confBuffer->commandFrame.payload;
  RZclSetRequest_t *req = (RZclSetRequest_t*) commandBuffer->commandFrame.payload;
  ZCL_Set_t zclSet;
  ZCL_LinkKeyDesc_t zclLinkKeyDesc;

  zclSet.status = ZCL_SUCCESS_STATUS;

  zclSet.attr.id = (ZCL_SecurityAttrId_t) req->id;
  zclSet.attr.length = req->length;
#if CERTICOM_SUPPORT == 1
  if (ZCL_KE_ACTIVE_ENDPOINT_ID == zclSet.attr.id)
  {
    zclSet.attr.value.endpoint = req->value.endpoint;
  }
  else if (ZCL_CERTIFICATE_DESC_ID == req->id)
  {
    if (sizeof(ZCL_CertificateDesc_t) == req->length)
    {
      SYS_BYTE_MEMCPY(&rCertificateDescriptor, &req->value.certificateDesc, sizeof(ZCL_CertificateDesc_t));
      zclSet.attr.value.certificateDesc = &rCertificateDescriptor;
    }
    else
    {
      zclSet.status = ZCL_INVALID_ATTRIBUTE_VALUE_STATUS;
    }
  }
  else
#endif /* CERTICOM_SUPPORT == 1 */

  if (ZCL_LINK_KEY_DESC_ID == req->id)
  {
    //SYS_BYTE_MEMCPY(&zclLinkKeyDesc, &req->value.linkKeyDesc, sizeof(ZCL_LinkKeyDesc_t));
    zclLinkKeyDesc.addr = req->value.linkKeyDesc.addr;
    SYS_BYTE_MEMCPY(zclLinkKeyDesc.key, req->value.linkKeyDesc.key, 16);
    zclSet.attr.value.linkKeyDesc = &zclLinkKeyDesc;
  }
  else
  {
    zclSet.attr.value.networkKey = req->value.networkKey;
  }

  if (ZCL_SUCCESS_STATUS == zclSet.status)
    ZCL_Set(&zclSet);

  //Confirm prepare
  confirm->status = zclSet.status;
  confirm->id = zclSet.attr.id;

  confBuffer->commandFrame.commandId = R_ZCL_SET_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZclSetConfirm_t);
  serialManager.write(confBuffer);

}

#if (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
void rZclSetKETimeoutsProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RZclSetKETimeouts_t *req = (RZclSetKETimeouts_t*)commandBuffer->commandFrame.payload;

  setKETimeouts(req->ephemeralTimeout, req->confirmTimeout, req->ephemeralDelay, req->confirmDelay);
}

void rZclPassBadCertificatesProcessing(ZS_CommandBuffer_t *commandBuffer)
{
  setBadCertificatesProcessing();
}

void rZclKeOutOfOrderProcessing(ZS_CommandBuffer_t *commandBuffer)
{
  setOutOfOrderResponse();
}
#endif // (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)

#endif /* _LINK_SECURITY_ */

/**************************************************************************//**
  \brief Gets certificate descriptor.

  \param Certificate descriptor structure pointer to be filled.

  \return void.
******************************************************************************/
#if CERTICOM_SUPPORT == 1
#ifdef APP_ECDSA_SIGNATURE
static inline ZCL_Status_t getCertificateDescriptor(ZCL_CertificateDesc_t *certificateDesc)
{
  ZCL_Get_t getReq;

  getReq.attr.id = ZCL_CERTIFICATE_DESC_ID;
  getReq.attr.value.certificateDesc = certificateDesc;
  ZCL_Get(&getReq);
  return getReq.status;
}
#endif /* APP_ECDSA_SIGNATURE */
#endif /* CERTICOM_SUPPORT == 1 */

/**************************************************************************//**
  \brief Performs additional actions with commands comming from the serial interface.
    1). In case if command is report event status command: genertae signature.
    2). ...

  \param command - ZCL command descriptor pointer.

  \return none.
******************************************************************************/
static inline void commandRequestAdditionalActions(const ZCL_Request_t *command, uint8_t direction)
{

  if (ZCL_DIRECTION_FROM_CLIENT == direction &&
      REPORT_EVENT_STATUS_COMMAND_ID == command->id)
  {
#ifdef _LINK_SECURITY_
#if CERTICOM_SUPPORT == 1
#ifdef APP_ECDSA_SIGNATURE
    ZCL_CertificateDesc_t certificateDesc;
    ZCL_ReportEventStatus_t *reportEventStatus;
    uint8_t msgDigest[AES_MMO_HASH_SIZE];

    reportEventStatus = (ZCL_ReportEventStatus_t *)command->requestPayload;
    getCertificateDescriptor(&certificateDesc);
    rAssert(MCE_SUCCESS == SSP_BcbHash(msgDigest, sizeof(ZCL_ReportEventStatus_t) - REPORT_EVENT_STATUS_SIGNATURE_LENGTH, (uint8_t *)command->requestPayload), R_DBG_COMMANDREQUESTADDITIONALACTIONS_0);
    rAssert(MCE_SUCCESS == ZSE_ECDSASign(certificateDesc.privateKey,
                                         msgDigest,
                                         SYS_GetRandomSequence,
                                         reportEventStatus->signature,
                                         reportEventStatus->signature + SECT163K1_POINT_ORDER_SIZE,
                                         yield,
                                         YIELD_LEVEL),
    R_DBG_COMMANDREQUESTADDITIONALACTIONS_1);
#endif /* APP_ECDSA_SIGNATURE */
#endif /* CERTICOM_SUPPORT == 1 */

#endif /* _LINK_SECURITY_ */
  }
}
/**************************************************************************//**
  \brief Performs signature verifying.
    1). In case if command is report event status command: verify signature.
    2). ...

  \param addr - ZCL addressing structure pointer.
         payloadLength - report event status command length.
         payload - report event status paylod pointer.

  \return true - if command shall be indicated, false otherwise.
******************************************************************************/
static inline bool verifySignature(ZCL_Addressing_t *addr, ZCL_ReportEventStatus_t *reportEventStatus)
{
  bool status = true;

#ifdef _LINK_SECURITY_
#if CERTICOM_SUPPORT == 1
#ifdef APP_ECDSA_SIGNATURE
  uint8_t msgDigest[AES_MMO_HASH_SIZE];
  ZCL_CertificateDesc_t ownCertificateDesc;
  ZclCertificate_t *remoteCertificate;
  uint8_t recoveredPublicKey[SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE];
  uint8_t ecdsaStatus;

  // Get own certificate.
  rAssert(ZCL_SUCCESS_STATUS == getCertificateDescriptor(&ownCertificateDesc), R_DBG_VERIFYSIGNATURE_5);
  // Get remote device certificate.
  rAssert(APS_EXT_ADDRESS == addr->addrMode/*srcAddrMode*/, R_DBG_VERIFYSIGNATURE_3);
  remoteCertificate = keGetCertificate(addr->addr.extAddress/*srcExtAddress*/);
  rAssert(NULL != remoteCertificate, R_DBG_VERIFYSIGNATURE_4);
  // Calculate message hash.
  rAssert(MCE_SUCCESS == SSP_BcbHash(msgDigest, sizeof(ZCL_ReportEventStatus_t) - 42, (uint8_t *)reportEventStatus), R_DBG_VERIFYSIGNATURE_0);
  // Reconstruct public key.
  rAssert(MCE_SUCCESS == ZSE_ECQVReconstructPublicKey((uint8_t *)remoteCertificate, ownCertificateDesc.publicKey, recoveredPublicKey, SSP_BcbHash, NULL, 0), R_DBG_VERIFYSIGNATURE_1);
  // Verify signature.
  ecdsaStatus = ZSE_ECDSAVerify(recoveredPublicKey,
                                msgDigest,
                                reportEventStatus->signature,
                                reportEventStatus->signature + SECT163K1_POINT_ORDER_SIZE,
                                yield,
                                YIELD_LEVEL);
  switch (ecdsaStatus)
  {
    case MCE_SUCCESS:
      break;
    case MCE_ERR_FAIL_VERIFY:
      status = false;
      break;
    case MCE_ERR_NULL_PUBLIC_KEY:
    case MCE_ERR_NULL_INPUT_BUF:
    case MCE_ERR_NULL_FUNC_PTR:
    case MCE_ERR_BAD_INPUT:
    default:
      rAssert(false, R_DBG_VERIFYSIGNATURE_2);
      status = false;
      break;
  }
#endif /* APP_ECDSA_SIGNATURE */
#endif /* CERTICOM_SUPPORT == 1 */

#endif /* _LINK_SECURITY_ */
  (void)reportEventStatus;
  (void)addr;
  return status;
}
/**************************************************************************//**
\brief Cluster utility timer fired event.

\param none.

\return none.
******************************************************************************/
#ifdef ZSE_ESP_CLUSTERS_LOGIC
static void timerFired(void)
{
  timeClusterTimerFired();
  identifyClusterTimerFired();
}
#endif /* ZSE_ESP_CLUSTERS_LOGIC */

#endif /* ZCL_SUPPORT == 1 */

/* eof rZcl.c */
