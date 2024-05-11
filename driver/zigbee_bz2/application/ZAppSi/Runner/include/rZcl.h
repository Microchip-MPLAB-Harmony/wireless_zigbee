/**************************************************************************//**
  \file  rZcl.h

  \brief Zcl related functions declarations

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RZCL_H
#define _RZCL_H

#ifdef _ZCL_SUPPORT_ 
/******************************************************************************
                   Includes section
******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/clusters.h>
#include <zcl/include/zclMessagingCluster.h>
#include <zcl/include/zclSimpleMeteringCluster.h>
#include <zcl/include/zclDemandResponseCluster.h>
#include <zcl/include/zclBasicCluster.h>
#include <zcl/include/zclTimeCluster.h>
#include <zcl/include/zclIdentifyCluster.h>
#include <zcl/include/zclLevelControlCluster.h>
#include <ZAppSiSerialManager.h>
#ifdef _LINK_SECURITY_
#include <zcl/include/zclSecurityManager.h>
#endif /* _LINK_SECURITY_ */
/*****************************************************************************
                              Definitions section
******************************************************************************/
#define MAX_CLUSTERS_AMOUNT       16
#if APP_REDUCED_OTAU_SERVER == 0
  #define ZCL_REQUEST_BUF_SIZE      255
  #define ZCL_RESPONSE_BUF_SIZE     255
#else
  #define ZCL_REQUEST_BUF_SIZE      100
  #define ZCL_RESPONSE_BUF_SIZE     100
#endif
#define ZCL_DIRECTION_FROM_CLIENT 0x00
#define ZCL_DIRECTION_FROM_SERVER 0x01
#define GET_LAST_MESSAGE_RETURN_VALUE 0xff
/******************************************************************************
                   Types section
******************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  uint8_t endpoint;
  uint16_t appDeviceId;
  ProfileId_t appProfileId;
  uint8_t inClustersCount;
  uint8_t outClustersCount;
  ClusterId_t inOutClusterIds[1];
} RZclStartRequest_t;

typedef struct PACK
{
  uint8_t useSpecialRemoteAddress;
  ExtAddr_t remoteAddress;
} RZclStartSecurityRequest_t;

typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(4,(
    uint8_t direction : 1,
    uint8_t generalCommand : 1,
    uint8_t ackRequest : 1,
    uint8_t reserved : 5
  ))
} CommandOptions_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t id;
  uint8_t recordsCount;
  uint8_t records[1];
} RZclAttributeResponse_t;

typedef struct PACK
{
  uint8_t addrMode;
  ShortAddr_t shortAddress;
  ExtAddr_t extAddress;
  ProfileId_t profileId;
  uint8_t endpoint;
  uint8_t dstEndpoint;
  ClusterId_t clusterId;
  uint8_t defaultResponse;
  uint8_t sequenceNumber;
  CommandOptions_t commandOptions;
  uint8_t commandId;
  uint8_t request[1];
} RZclCommandRequest_t;

typedef struct PACK
{
  uint8_t addrMode;
  ShortAddr_t shortAddress;
  ExtAddr_t extAddress;
  ProfileId_t profileId;
  uint8_t endpoint;
  uint8_t dstEndpoint;
  ClusterId_t clusterId;
  uint8_t defaultResponse;
  CommandOptions_t commandOptions;
  uint8_t commandId;
  uint8_t recordsCount;
  uint8_t request[1];
} RZclAttributeRequest_t;

typedef struct PACK
{
  uint8_t srcAddrMode;
  ShortAddr_t srcShortAddress;
  ExtAddr_t srcExtAddress;
  ProfileId_t srcProfileId;
  Endpoint_t srcEndpointId;
  ClusterId_t srcClusterId;
  ClusterId_t clusterId;
  uint8_t attributesCount;
  uint8_t reportLength;
  uint8_t report[1];
} RZclReportIndication_t;

typedef struct PACK
{
  Endpoint_t endpoint;
  ClusterId_t clusterId;
  uint8_t direction;
  uint8_t commandId;
  uint16_t attributeId;
} RZclReadAttributeValue_t;

typedef struct PACK
{
    uint8_t status;
    uint8_t commandId;
    uint16_t attributeId;
    uint8_t type;
    uint8_t value[1];
} RZclReadAttributeValueConfirm_t;

typedef struct PACK
{
    uint8_t status;
    uint8_t commandId;
} RZclWriteAttributeValueConfirm_t;

typedef struct PACK
{
  Endpoint_t endpoint;
  ClusterId_t clusterId;
  uint8_t direction;
  uint8_t commandId;
  uint16_t attributeId;
  uint8_t type;
  uint8_t value[1];
} RZclWriteAttributeValue_t;

typedef struct PACK
{
  uint16_t clusterId;
  uint8_t security;
} RZclSetClusterSecurityRequest_t;

typedef struct PACK
{
  uint8_t status;
} RZclSetClusterSecurityConfirm_t;

#ifdef _LINK_SECURITY_
typedef struct PACK
{
  ExtAddr_t addr;           //!<Destination node 64-bit IEEE address
  uint8_t   key[SECURITY_KEY_SIZE];        //!<APS Link Key
} LinkKeyDesc_t;

typedef struct PACK
{
  uint8_t publicKey[22];      //!<CA Public Key shared between all nodes in network
  uint8_t privateKey[21];     //!<Node secret key
  uint8_t certificate[48];    //!<Node certificate derived from CA
} CertificateDesc_t;

typedef union PACK
{
  CertificateDesc_t certificateDesc;
  LinkKeyDesc_t     linkKeyDesc;
  Endpoint_t        endpoint;
  uint8_t           networkKey[SECURITY_KEY_SIZE];
} SecurityAttrValue_t;

typedef struct PACK
{
  uint8_t               id;
  uint8_t               length;
  SecurityAttrValue_t   value;
} RZclSetRequest_t;

typedef struct PACK
{
  uint8_t               status;
  uint8_t               id;
  uint8_t               length;
  SecurityAttrValue_t   value;
} RZclGetRequest_t;

typedef struct PACK
{
  uint8_t               status;
  uint8_t               id;
  uint8_t               length;
  SecurityAttrValue_t   value;
} RZclGetConfirm_t;

#if (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
typedef struct PACK
{
  uint8_t ephemeralTimeout;
  uint8_t confirmTimeout;
  uint8_t ephemeralDelay;
  uint8_t confirmDelay;
} RZclSetKETimeouts_t;
#endif //(CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
#endif //#ifdef _LINK_SECURITY_

END_PACK
/*****************************************************************************
                              External variables section
******************************************************************************/
extern uint8_t getLastMessageReturnValue;
/******************************************************************************
                   Prototypes section
******************************************************************************/
void zclReset(void);
ZCL_Status_t loadControlEventInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_LoadControlEvent_t *message);
ZCL_Status_t cancelLoadControlEventInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_CancelLoadControlEvent_t *message);
ZCL_Status_t cancelAllLoadControlEventsInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_CancelAllLoadControlEvents_t *message);
ZCL_Status_t reportEventStatusInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_ReportEventStatus_t *message);
ZCL_Status_t getScheduledEventsInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_GetScheduledEvents_t *message);
ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addr, uint8_t payloadLength, ZCL_MoveToLevel_t *message);
void rZclStartRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclCommandRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclAttributeRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclAttributeValueProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclClusterSecurityProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclNextSequenceNumberReqProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclStartReportingRequestProcess(ZS_CommandBuffer_t *commandBuffer);

#ifdef _LINK_SECURITY_
void rZclCommandGetProcess(ZS_CommandBuffer_t *commandBuffer);
void rZclCommandSetProcess(ZS_CommandBuffer_t *commandBuffer);
#if (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
void rZclSetKETimeoutsProcess(ZS_CommandBuffer_t *commandBuffer);
extern void setKETimeouts(uint8_t ephemeralTimeout, uint8_t confirmTimeout, uint8_t ephemeralDelay, uint8_t confirmDelay);
extern void setBadCertificatesProcessing(void);
extern void setOutOfOrderResponse(void);
void rZclKeOutOfOrderProcessing(ZS_CommandBuffer_t *commandBuffer);
void rZclKeSecSendTooLongCertificate(ZS_CommandBuffer_t *commandBuffer);
void rZclPassBadCertificatesProcessing(ZS_CommandBuffer_t *commandBuffer);
#endif// (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
#endif /* _LINK_SECURITY_ */
     
void rZclStartSecurityRequestProcess(ZS_CommandBuffer_t *commandBuffer);
/***************************************************************************//**
\brief Common ZCL command indication handler

\param addr - address the command came from.
\param payloadLength - the length of payload
\param payload - payload.

\return Status of operation.
******************************************************************************/
ZCL_Status_t commandInd(ZCL_Addressing_t *addr, uint8_t payloadLength, uint8_t *payload);
/*****************************************************************************
                              Inline functions section
******************************************************************************/
INLINE uint8_t rGetLastMessageReturnValue()
{
  return getLastMessageReturnValue;
}

INLINE void rSetGetLastMessageReturnValue(uint8_t value)
{
  getLastMessageReturnValue = value;
}

#endif /* ZCL_SUPPORT == 1 */
#endif /* _RZCL_H */

/* eof rZcl.h */
