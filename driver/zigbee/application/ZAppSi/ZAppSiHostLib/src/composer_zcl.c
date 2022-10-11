/*****************************************************************************
  \file composer_zcl.c

  \brief Composer module (ZCL part).

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    24/12/09 A. Kostyukov - Created
*******************************************************************************/

#ifdef _ZCL_SUPPORT_ 
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiHost.h>
#include <ZAppSiSerialManager.h>
#include <ZAppSiIdentifiers.h>
#include <bufferallocator.h>
#include <parser.h>
#include <sysUtils.h>
#include <zcl.h>
#include <zclIdentifyCluster.h>
#include <zclPriceCluster.h>
#include <zclDemandResponseCluster.h>
#include <zclMessagingCluster.h>
#include <zcltools.h>
#include <composer.h>
/***************************************************************************//**
                    Types Sections
*******************************************************************************/
/***************************************************************************//**
Type defines common parameters for zcl commands
*******************************************************************************/
BEGIN_PACK
// Probably the structure was depricated.
// Data is duplicated with zsZclCommandRequest_t
// Smart energy commands are not used still.
// Home aotomation is not used this structure.
typedef struct PACK
{
  uint8_t endpoint;
  uint16_t clusterId;
  uint8_t defaultResponse;
  uint8_t direction;
  uint8_t commandId;
  uint8_t recordsCount;
} zsZclCommandHeader_t;

/***************************************************************************//**
Type defines general zcl command options
*******************************************************************************/
typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(4,(
    uint8_t direction : 1,
    uint8_t generalCommand : 1,
    uint8_t ackRequest : 1,
    uint8_t reserved : 5
  ))
} CommandOptions_t;

/***************************************************************************//**
Type defines common parameters for zcl commands Req
*******************************************************************************/
typedef struct PACK
{
  uint8_t addrMode;
  ShortAddr_t shortAddress;
  ExtAddr_t extAddress;
  ProfileId_t profileId;
  uint8_t srcEndpoint;
  uint8_t dstEndpoint;
  ClusterId_t clusterId;
  uint8_t defaultResponse;
  uint8_t sequenceNumber;
  CommandOptions_t commandOptions;
  uint8_t commandId;
  uint8_t recordsCount;
} zsZclCommandRequest_t;
END_PACK

/******************************************************************************
                   Prototypes section
******************************************************************************/
static void fillCommonPartOfZclReq(uint16_t clusterId,
                                   uint8_t defaultResponse,
                                   uint8_t sequenceNumber,
                                   uint8_t commandId,
                                   uint8_t srcEndpoint,
                                   uint8_t dstEndpoint,
                                   ZS_CommandFrame_t *commandFrame,
                                   uint8_t payloadSize);

/******************************************************************************
                              Implementations section
 ******************************************************************************/
/***************************************************************************//**
\brief Requests to read the values of one or more attributes located on another
device. Each attribute identifier field shall contain the identifier of the
attribute to be read.

\param[in] req - Holds parameters of request.
See ZS_ZclReadAttributeReq_t for details.

\return
*******************************************************************************/
void ZS_ZclReadAttributeReq(const ZS_ZclReadAttributeReq_t *req,
                            void (*resp)(const ZS_ZclReadAttributeResp_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  const uint8_t options = 0x02;
  const uint8_t commandId = ZCL_READ_ATTRIBUTES_COMMAND_ID;

  commandFrame->commandId = R_ZCL_ATTRIBUTE_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->endpoint);
  commandFrame->length += sizeof(req->clusterId);
  commandFrame->length += sizeof(req->defaultResponse);
  commandFrame->length += sizeof(options);
  commandFrame->length += sizeof(commandId);
  commandFrame->length += sizeof(req->recordsCount);
  commandFrame->length += req->recordsCount * sizeof(uint16_t);

  uint8_t *ptr = commandFrame->payload;

  SYS_BYTE_MEMCPY(ptr, &req->endpoint, sizeof(req->endpoint));
  ptr += sizeof(req->endpoint);

  SYS_BYTE_MEMCPY(ptr, GET_FIELD_PTR(req, ZS_ZclReadAttributeReq_t, clusterId),
                  sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->defaultResponse, sizeof(req->defaultResponse));
  ptr += sizeof(req->defaultResponse);

  SYS_BYTE_MEMCPY(ptr, &options, sizeof(options));
  ptr += sizeof(options);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &req->recordsCount, sizeof(req->recordsCount));
  ptr += sizeof(req->recordsCount);

  SYS_BYTE_MEMCPY(ptr, req->attributes, sizeof(uint16_t) * req->recordsCount);

  setAwaitingReq(R_ZCL_ATTRIBUTE_RESPONSE, (void*)resp);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to write the values of one or more attributes located on another
device. Each write attribute record shall contain the identifier and the actual
value of the attribute to be written.

\param[in] req - Holds parameters of request.
See ZS_ZclWriteAttributeReq_t for details.

\return
*******************************************************************************/
void ZS_ZclWriteAttributeReq(const ZS_ZclWriteAttributeReq_t *req,
                             void (*resp)(const ZS_ZclWriteAttributeResp_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  const uint8_t options = 0x02;
  const uint8_t commandId = ZCL_WRITE_ATTRIBUTES_COMMAND_ID;

  commandFrame->commandId = R_ZCL_ATTRIBUTE_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->endpoint);
  commandFrame->length += sizeof(req->clusterId);
  commandFrame->length += sizeof(req->defaultResponse);
  commandFrame->length += sizeof(options);
  commandFrame->length += sizeof(commandId);
  commandFrame->length += sizeof(req->recordsCount);

  uint8_t *ptr = commandFrame->payload;

  SYS_BYTE_MEMCPY(ptr, &req->endpoint, sizeof(req->endpoint));
  ptr += sizeof(req->endpoint);

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(req, ZS_ZclWriteAttributeReq_t, clusterId),
    sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->defaultResponse, sizeof(req->defaultResponse));
  ptr += sizeof(req->defaultResponse);

  SYS_BYTE_MEMCPY(ptr, &options, sizeof(options));
  ptr += sizeof(options);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &req->recordsCount, sizeof(req->recordsCount));
  ptr += sizeof(req->recordsCount);


  int i = 0;
  int typeSize;
  ZS_ZclWriteAttributeRecord_t* record = req->records;
  for (i = 0; i < req->recordsCount; ++i)
  {
    SYS_BYTE_MEMCPY(ptr,
      GET_FIELD_PTR(record, ZS_ZclWriteAttributeRecord_t, attributeId),
      sizeof(req->records[i].attributeId));
    ptr += sizeof(record->attributeId);
    commandFrame->length += sizeof(record->attributeId);

    SYS_BYTE_MEMCPY(ptr, &record->typeValue.type, sizeof(record->typeValue.type));
    ptr += sizeof(record->typeValue.type);
    commandFrame->length += sizeof(record->typeValue.type);

    typeSize = zsSizeofAttributeType(record->typeValue.type);
    SYS_BYTE_MEMCPY(ptr, record->typeValue.value, typeSize);
    ptr += typeSize;
    commandFrame->length += typeSize;
    record++;
  }

  setAwaitingReq(R_ZCL_ATTRIBUTE_RESPONSE, (void*)resp);
  serialManager.write(buffer);
}

/*
void ZS_ZclWriteAttributesUndividedReq()
{

}

void ZS_ZclWriteAttributesNoResponseReq()
{

}
*/
/***************************************************************************//**
\brief Requests to configure a device to automatically report the values of one
or more of its attributes, or to receive such reports.

\param[in] req - Holds parameters of request.
See ZS_ZclConfigureReportingReq_t for details.

\return
*******************************************************************************/
void ZS_ZclConfigureReportingReq(const ZS_ZclConfigureReportingReq_t *req,
                          void (*resp)(const ZS_ZclConfigureReportingResp_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  uint8_t commandId = ZCL_CONFIGURE_REPORTING_COMMAND_ID;
  uint8_t options = 0x02;

  commandFrame->commandId = R_ZCL_ATTRIBUTE_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->endpoint);
  commandFrame->length += sizeof(req->clusterId);
  commandFrame->length += sizeof(req->defaultResponse);
  commandFrame->length += sizeof(options);
  commandFrame->length += sizeof(commandId);
  commandFrame->length += sizeof(req->recordsCount);

  uint8_t *ptr = commandFrame->payload;

  SYS_BYTE_MEMCPY(ptr, &req->endpoint, sizeof(req->endpoint));
  ptr += sizeof(req->endpoint);

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(req, ZS_ZclConfigureReportingReq_t, clusterId),
    sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->defaultResponse, sizeof(req->defaultResponse));
  ptr += sizeof(req->defaultResponse);

  SYS_BYTE_MEMCPY(ptr, &options, sizeof(options));
  ptr += sizeof(options);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &req->recordsCount, sizeof(req->recordsCount));
  ptr += sizeof(req->recordsCount);

  int i = 0;
  uint8_t typeSize = 0;
  ZS_ZclConfigureReportingReqRecord_t* record =
    (ZS_ZclConfigureReportingReqRecord_t*)GET_FIELD_PTR(req,
                                      ZS_ZclConfigureReportingReq_t, records);
  for (i = 0; i < req->recordsCount; ++i)
  {
    SYS_BYTE_MEMCPY(ptr, &record->direction, sizeof(record->direction));
    commandFrame->length += sizeof(record->direction);
    ptr += sizeof(record->direction);

    SYS_BYTE_MEMCPY(ptr,
      GET_FIELD_PTR(record, ZS_ZclConfigureReportingReqRecord_t, attributeId),
      sizeof(record->attributeId));
    commandFrame->length += sizeof(record->attributeId);
    ptr += sizeof(record->attributeId);

    SYS_BYTE_MEMCPY(ptr, &record->attributeType, sizeof(record->attributeType));
    commandFrame->length += sizeof(record->attributeType);
    ptr += sizeof(record->attributeType);

    SYS_BYTE_MEMCPY(ptr,
      GET_FIELD_PTR(record, ZS_ZclConfigureReportingReqRecord_t, minReportingInterval),
      sizeof(record->minReportingInterval));
    commandFrame->length += sizeof(record->minReportingInterval);
    ptr += sizeof(record->minReportingInterval);

    SYS_BYTE_MEMCPY(ptr,
      GET_FIELD_PTR(record, ZS_ZclConfigureReportingReqRecord_t, maxReportingInterval),
      sizeof(record->maxReportingInterval));

    commandFrame->length += sizeof(record->maxReportingInterval);
    ptr += sizeof(record->maxReportingInterval);

    typeSize = zsSizeofAttributeType(record->attributeType);
    SYS_BYTE_MEMCPY(ptr, record->reportableChange, typeSize);
    commandFrame->length += typeSize;
    ptr += typeSize;
    record++;
  }

  setAwaitingReq(R_ZCL_ATTRIBUTE_RESPONSE, (void*)resp);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to discover the identifiers and types of the attributes
on a device which are supported within the cluster to which this command is
directed.

\param[in] req - Holds parameters of request.
See ZS_ZclDiscoverAttributesReq_t for details.

\return
*******************************************************************************/
void ZS_ZclDiscoverAttributesReq(const ZS_ZclDiscoverAttributesReq_t *req,
                          void (*resp)(const ZS_ZclDiscoverAttributesResp_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  uint8_t commandId = ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID;
  uint8_t options = 0x02;
  uint8_t recordsCount = 1;
  commandFrame->commandId = R_ZCL_ATTRIBUTE_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->endpoint);
  commandFrame->length += sizeof(req->clusterId);
  commandFrame->length += sizeof(req->defaultResponse);
  commandFrame->length += sizeof(options);
  commandFrame->length += sizeof(commandId);
  commandFrame->length += sizeof(recordsCount);
  commandFrame->length += sizeof(req->startAttributeId);
  commandFrame->length += sizeof(req->maxAttributeIds);

  uint8_t *ptr = commandFrame->payload;

  SYS_BYTE_MEMCPY(ptr, &req->endpoint, sizeof(req->endpoint));
  ptr += sizeof(req->endpoint);

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(req, ZS_ZclDiscoverAttributesReq_t, clusterId),
    sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->defaultResponse, sizeof(req->defaultResponse));
  ptr += sizeof(req->defaultResponse);

  SYS_BYTE_MEMCPY(ptr, &options, sizeof(options));
  ptr += sizeof(options);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &recordsCount, sizeof(recordsCount));
  ptr += sizeof(recordsCount);

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(req, ZS_ZclDiscoverAttributesReq_t, startAttributeId),
    sizeof(req->startAttributeId));
  ptr += sizeof(req->startAttributeId);

  SYS_BYTE_MEMCPY(ptr, &req->maxAttributeIds, sizeof(req->maxAttributeIds));
  ptr += sizeof(req->maxAttributeIds);

  setAwaitingReq(R_ZCL_ATTRIBUTE_RESPONSE, (void*)resp);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to read the configuration details of the reporting mechanism
for one or more of the attributes of a cluster.

\param[in] req - Holds parameters of request.
See ZS_ZclReadReportingConfigReq_t for details.

\return
*******************************************************************************/
void ZS_ZclReadReportingConfigReq(const ZS_ZclReadReportingConfigReq_t *req,
                         void (*resp)(const ZS_ZclReadReportingConfigResp_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  uint8_t commandId = ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID;
  uint8_t options = 0x02;

  commandFrame->commandId = R_ZCL_ATTRIBUTE_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->endpoint);
  commandFrame->length += sizeof(req->clusterId);
  commandFrame->length += sizeof(req->defaultResponse);
  commandFrame->length += sizeof(options);
  commandFrame->length += sizeof(commandId);
  commandFrame->length += sizeof(req->recordsCount);

  uint8_t *ptr = commandFrame->payload;

  SYS_BYTE_MEMCPY(ptr, &req->endpoint, sizeof(req->endpoint));
  ptr += sizeof(req->endpoint);

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(req, ZS_ZclReadReportingConfigReq_t, clusterId),
    sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->defaultResponse, sizeof(req->defaultResponse));
  ptr += sizeof(req->defaultResponse);

  SYS_BYTE_MEMCPY(ptr, &options, sizeof(options));
  ptr += sizeof(options);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &req->recordsCount, sizeof(req->recordsCount));
  ptr += sizeof(req->recordsCount);

  SYS_BYTE_MEMCPY(ptr, req->records, req->recordsCount * sizeof(ZS_ZclReadReportingConigReqRecord_t));
  commandFrame->length += req->recordsCount * sizeof(ZS_ZclReadReportingConigReqRecord_t);

  setAwaitingReq(R_ZCL_ATTRIBUTE_RESPONSE, (void*)resp);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Request to start Smart Energy profile.

It should called before using ZCL functions. This command also initiates key
establishment.

\param[in] req - Determines the request parameters.
See description of ZS_ZclStartRequest_t for details.

\return
*******************************************************************************/
void ZS_ZclStartReq(ZS_ZclStartRequest_t* req,
                    void (*conf)(RZclStartConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;
  ptr->commandId = R_ZCL_START_REQUEST;
  ptr->length = sizeof(ZS_ZclStartRequest_t) + sizeof(ptr->commandId)
        - sizeof(req->inClustersList) - sizeof(req->outClustersList)
        + sizeof(ClusterId_t) * (req->inClustersCount + req->outClustersCount);

  uint8_t* pos = ptr->payload;
  SYS_BYTE_MEMCPY( pos,
      req,
      offsetof(ZS_ZclStartRequest_t, inClustersList));
  pos += offsetof(ZS_ZclStartRequest_t, inClustersList);
  SYS_BYTE_MEMCPY( pos,
      req->inClustersList,
      req->inClustersCount * sizeof(ClusterId_t));
  pos += req->inClustersCount * sizeof(ClusterId_t);
  SYS_BYTE_MEMCPY( pos,
      req->outClustersList,
      req->outClustersCount * sizeof(ClusterId_t));

  setAwaitingReq(R_ZCL_START_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
//copy structure with changing last pointer field to actual value
uint16_t copy_with_ptr_subs(uint8_t* psrc, uint8_t offset, uint8_t* pdst, uint8_t len)
{
  void *ptr = 0;

  SYS_BYTE_MEMCPY(pdst, psrc, offset);
  // copy pointer
  SYS_BYTE_MEMCPY(&ptr, psrc + offset, sizeof(void*));
  SYS_BYTE_MEMCPY(pdst + offset, (uint8_t*)ptr, len);

  //SYS_BYTE_MEMCPY(pdst + offset,*(uint8_t **)(psrc + offset), len);
  return offset + len;
}
/***************************************************************************//**
\brief Request to read Smart Energy profile options for local device.

This function allows to get profile options for local device (certificates,
keys, endpoints and so on)

\param[in] req - Determines the request parameters.
See description of ZS_ZclGetRequest_t for details.

\return
*******************************************************************************/
void ZS_ZclGetReq(ZS_ZclGetRequest_t* req,
                  void (*conf)(ZS_ZclGetConfirm_t*))
{
  generateSimpleFrame(R_ZCL_GET_REQUEST, req, sizeof(*req),
                      R_ZCL_GET_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request to set Smart Energy profile options for local device.

This function allows to set profile options for local device (certificates,
keys, endpoints and so on)

\param[in] req - Determines the request parameters.
See description of ZS_ZclSetRequest_t for details.

\return
*******************************************************************************/
void ZS_ZclSetReq(ZS_ZclSetRequest_t* req,
                  void (*conf)(RZclSetConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;
  ptr->commandId = R_ZCL_SET_REQUEST;
  ptr->length = copy_with_ptr_subs((uint8_t*)req,
                                   offsetof(ZS_ZclSetRequest_t, value),
                                   ptr->payload, req->length)
                + sizeof(ptr->commandId);
  setAwaitingReq(R_ZCL_SET_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Request to read attributes values for local device.

Use this functions to read values of attributes in Smart Energy cluster.

\param[in] req - Determines the request parameters.
See description of ZS_ZclReadAttributeValue_t for details.

\return
*******************************************************************************/
void ZS_ZclReadAttributeValueReq(ZS_ZclReadAttributeValue_t* req,
                              void (*conf)(ZS_ZclReadAttributeValueConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;
  uint8_t *pos = ptr->payload;
  ClusterId_t clusterId = req->clusterId;
  uint16_t attributeId = req->attributeId;

  ptr->commandId = R_ZCL_ATTRIBUTE_VALUE;
  ptr->length = sizeof(ptr->commandId) + sizeof(ZS_ZclReadAttributeValue_t);

  SYS_BYTE_MEMCPY(pos, &req->endpoint, sizeof(req->endpoint));
  pos += sizeof(req->endpoint);
  SYS_BYTE_MEMCPY(pos, &clusterId, sizeof(req->clusterId));
  pos += sizeof(req->clusterId);
  SYS_BYTE_MEMCPY(pos, &req->direction, sizeof(req->direction));
  pos += sizeof(req->direction);
  SYS_BYTE_MEMCPY(pos, &req->commandId, sizeof(req->commandId));
  pos += sizeof(req->commandId);
  SYS_BYTE_MEMCPY(pos, &attributeId, sizeof(req->attributeId));

  setAwaitingReq(R_ZCL_ATTRIBUTE_VALUE_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Request to write attributes values for local device.

Use this functions to write values of attributes in Smart Energy cluster.

\param[in] req - Determines the request parameters.
See description of ZS_ZclReadAttributeValue_t for details.

\return
*******************************************************************************/
void ZS_ZclWriteAttributeValueReq(ZS_ZclWriteAttributeValue_t* req,
                             void (*conf)(ZS_ZclWriteAttributeValueConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;
  uint8_t *pos = ptr->payload;
  ClusterId_t clusterId = req->clusterId;
  uint16_t attributeId = req->attributeId;

  ptr->commandId = R_ZCL_ATTRIBUTE_VALUE;
  ptr->length = sizeof(ptr->commandId) + sizeof(ZS_ZclWriteAttributeValue_t)
  - sizeof(req->value) + zsSizeofAttributeType(req->type);

  SYS_BYTE_MEMCPY(pos, &req->endpoint, sizeof(req->endpoint));
  pos += sizeof(req->endpoint);
  SYS_BYTE_MEMCPY(pos, &clusterId, sizeof(req->clusterId));
  pos += sizeof(req->clusterId);
  SYS_BYTE_MEMCPY(pos, &req->direction, sizeof(req->direction));
  pos += sizeof(req->direction);
  SYS_BYTE_MEMCPY(pos, &req->commandId, sizeof(req->commandId));
  pos += sizeof(req->commandId);
  SYS_BYTE_MEMCPY(pos, &attributeId, sizeof(req->attributeId));
  pos += sizeof(req->attributeId);
  SYS_BYTE_MEMCPY(pos, &req->type, sizeof(req->type));
  pos += sizeof(req->type);
  SYS_BYTE_MEMCPY(pos, req->value, zsSizeofAttributeType(req->type));

  setAwaitingReq(R_ZCL_ATTRIBUTE_VALUE_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send an Identify command. The Identify command starts or stops
the receiving device identifying itself.

\param[in] req - Holds parameters of request.
See ZS_ZclIdentifyReq_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyReq(const ZS_ZclIdentifyReq_t *req,
                       void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = IDENTIFY_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclIdentifyReq_t) - offsetof(ZS_ZclIdentifyReq_t, identify.identifyTime);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->identify, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send an Identify Query command. The Identify Query command
allows the sending device to request the target or targets to respond
if they are currently identifying themselves.

\param[in] req - Holds parameters of request.
See ZS_ZclIdentifyQueryReq_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryReq(const ZS_ZclIdentifyQueryReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = IDENTIFY_CLUSTER_ID;
  header.defaultResponse = req->defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->srcEndpoint;
  header.commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_COMMAND_ID;
  header.recordsCount = 0;

  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);

  SYS_BYTE_MEMCPY(commandFrame->payload, &header, sizeof(header));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send an Identify Qurey Response command.The Identify Query
Response command is generated in response to receiving an
Identify Query command, in the case that the device is currently
identifying itself.

\param[in] req - Holds parameters of request.
See ZS_ZclIdentifyQueryResponseReq_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryResponseReq(const ZS_ZclIdentifyQueryResponseReq_t *req,
                                    void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = IDENTIFY_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclIdentifyQueryResponseReq_t) - offsetof(ZS_ZclIdentifyQueryResponseReq_t, identifyQueryResponse.timeout);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->identifyQueryResponse, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Get Current Price command. This command is generated
when the client device wishes to verify the available Price Events or after
a loss of power/reset occurs and the client device needs to recover currently
active or scheduled Price Events.

\param[in]
See ZS_ZclGetCurrentPriceReq_t for details.

\return
*******************************************************************************/
void ZS_ZclGetCurrentPriceReq(const ZS_ZclGetCurrentPriceReq_t *req,
                              void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = PRICE_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = GET_CURRENT_PRICE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclGetCurrentPriceReq_t) - offsetof(ZS_ZclGetCurrentPriceReq_t, getCurrentPrice);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->getCurrentPrice, sizeof(req->getCurrentPrice));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Publish Price command. The Publish Price command is
generated in response to receiving a Get Current Price command,
a Get Scheduled Prices command or when an update to the pricing information is
available from the commodity provider.

\param[in] req - Holds parameters of request.
See ZS_ZclPublishPriceReq_t for details.

\return
*******************************************************************************/
void ZS_ZclPublishPriceReq(const ZS_ZclPublishPriceReq_t *req,
                           void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = PRICE_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = PUBLISH_PRICE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t sizeOfConstSizeData = sizeof(ZS_ZclPublishPriceReq_t);
  sizeOfConstSizeData -= sizeof(req->command.srcEndpoint);
  sizeOfConstSizeData -= sizeof(req->command.defaultResponse);
  sizeOfConstSizeData -= sizeof(req->publishPrice.providerId);
  sizeOfConstSizeData -= sizeof(req->publishPrice.rateLabelLength);
  sizeOfConstSizeData -= sizeof(req->publishPrice.rateLabel);

  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += sizeof(req->publishPrice.providerId);
  commandFrame->length += sizeof(req->publishPrice.rateLabelLength);
  commandFrame->length += req->publishPrice.rateLabelLength;
  commandFrame->length += sizeOfConstSizeData;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->publishPrice, sizeof(req->publishPrice.providerId));
  ptr += sizeof(req->publishPrice.providerId);

  SYS_BYTE_MEMCPY(ptr, &req->publishPrice.rateLabelLength, sizeof(req->publishPrice.rateLabelLength));
  ptr += sizeof(req->publishPrice.rateLabelLength);

  SYS_BYTE_MEMCPY(ptr, req->publishPrice.rateLabel, req->publishPrice.rateLabelLength);
  ptr += req->publishPrice.rateLabelLength;

  SYS_BYTE_MEMCPY(ptr,
    GET_FIELD_PTR(&req->publishPrice, ZS_ZclPublishPrice_t, issuerEventId),
    sizeOfConstSizeData);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Report Event Status command. This command is generated
when the client device detects a change of state for an active
Load Control event.

\param[in] req - Holds parameters of request.
See ZS_ZclReportEventStatusReq_t for details.

\return
*******************************************************************************/
void ZS_ZclReportEventStatusReq(const ZS_ZclReportEventStatusReq_t *req,
                                void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = REPORT_EVENT_STATUS_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclReportEventStatusReq_t) - offsetof(ZS_ZclReportEventStatusReq_t, reportEventStatus.issuerEventId);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->reportEventStatus, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Get Scheduled Events command. This command is generated
when the client device wishes to verify the available Load Control Events or
after a loss of power/reset occurs and the client device needs to recover
currently active or scheduled Load Control Events.

\param[in] req - Holds parameters of request.
See ZS_ZclGetScheduledEventsReq_t for details.

\return
*******************************************************************************/
void ZS_ZclGetScheduledEventsReq(const ZS_ZclGetScheduledEventsReq_t *req,
                                 void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = GET_SCHEDULED_EVENTS_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclGetScheduledEventsReq_t) - offsetof(ZS_ZclGetScheduledEventsReq_t, getScheduledEvents.startTime);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->getScheduledEvents, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Load Control Event command. This command is generated
when the ESP wants to control one or more load control device(s), usually as
the result of an energy curtailment command from the Smart Energy network.

\param[in] req - Holds parameters of request.
See ZS_ZclLoadControlEventReq_t for details.

\return
*******************************************************************************/
void ZS_ZclLoadControlEventReq(const ZS_ZclLoadControlEventReq_t *req,
                               void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = LOAD_CONTROL_EVENT_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclLoadControlEventReq_t) - offsetof(ZS_ZclLoadControlEventReq_t, loadControlEvent.issuerEventId);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->loadControlEvent, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Cancel Load Control Event command. This command is
generated when the ESP wants to cancel previously scheduled control of one or
more load control device(s), usually as the result of an energy curtailment
command from the Smart Energy network.

\param[in] req - Holds parameters of request.
See ZS_ZclCancelLoadControlEventReq_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelLoadControlEventReq(const ZS_ZclCancelLoadControlEventReq_t *req,
                                     void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclCancelLoadControlEventReq_t) - offsetof(ZS_ZclCancelLoadControlEventReq_t, cancelLoadControlEvent.issuerEventId);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->cancelLoadControlEvent, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Cancel All Load Control Events. This command is
generated when the ESP wants to cancel all events for control device(s).

\param[in] req - Holds parameters of request.
See ZS_ZclCancelAllLoadControlEventsReq_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelAllLoadControlEventsReq(const ZS_ZclCancelAllLoadControlEventsReq_t *req,
                                         void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclCancelAllLoadControlEventsReq_t) - offsetof(ZS_ZclCancelAllLoadControlEventsReq_t, cancelAllLoadControlEvents.cancelControl);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->cancelAllLoadControlEvents.cancelControl, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Get Last Message command. This command causes
the recepient to generate a Display Message command.

\param[in] req - Holds parameters of request.
See ZS_ZclGetLastMessageReq_t for details.

\return
*******************************************************************************/
void ZS_ZclGetLastMessageReq(const ZS_ZclGetLastMessageReq_t *req,
                             void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = MESSAGE_CLUSTER_ID;
  header.defaultResponse = req->defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->srcEndpoint;
  header.commandId = GET_LAST_MESSAGE_COMMAND_ID;
  header.recordsCount = 0;

  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);

  SYS_BYTE_MEMCPY(commandFrame->payload, &header, sizeof(header));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Message Confirmation command. The Message Confirmation
command provides the ability to acknowledge a previously sent message.

\param[in] req - Holds parameters of request.
See ZS_ZclMessageConfirmationReq_t for details.

\return
*******************************************************************************/
void ZS_ZclMessageConfirmationReq(const ZS_ZclMessageConfirmationReq_t *req,
                                  void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = MESSAGE_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = CONFIRM_MESSAGE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclMessageConfirmationReq_t) - offsetof(ZS_ZclMessageConfirmationReq_t, messageConfirmation.messageId);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr,&req->messageConfirmation, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Display Message command.

\param[in] req - Holds parameters of request.
See ZS_ZclDisplayMessageReq_t for details.

\return
*******************************************************************************/
void ZS_ZclDisplayMessageReq(const ZS_ZclDisplayMessageReq_t *req,
                             void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = MESSAGE_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = DISPLAY_MESSAGE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t fieldsSize = offsetof(ZS_ZclDisplayMessageReq_t, displayMessage.message) -
                       offsetof(ZS_ZclDisplayMessageReq_t, displayMessage.messageId);

  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += fieldsSize;
  commandFrame->length += req->displayMessage.messageLength;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->displayMessage, fieldsSize);
  ptr += fieldsSize;

  SYS_BYTE_MEMCPY(ptr, req->displayMessage.message, req->displayMessage.messageLength);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Cancel Message command. The Cancel Message command
provides the ability to cancel the sending or acceptance of previously sent
messages.

\param[in] req - Holds parameters of request.
See ZS_ZclCancelMessageReq_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelMessageReq(const ZS_ZclCancelMessageReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  zsZclCommandHeader_t header;

  header.clusterId = MESSAGE_CLUSTER_ID;
  header.defaultResponse = req->command.defaultResponse;
  header.direction = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT;
  header.endpoint = req->command.srcEndpoint;
  header.commandId = CANCEL_MESSAGE_COMMAND_ID;
  header.recordsCount = 0;

  uint8_t payloadSize = sizeof(ZS_ZclCancelMessageReq_t) - offsetof(ZS_ZclCancelMessageReq_t, cancelMessage);
  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(header);
  commandFrame->length += payloadSize;

  uint8_t *ptr = commandFrame->payload;
  SYS_BYTE_MEMCPY(ptr, &header, sizeof(header));
  ptr += sizeof(header);

  SYS_BYTE_MEMCPY(ptr, &req->cancelMessage, payloadSize);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);

}

/***************************************************************************//**
\brief Requests to send a Add Group command.

\param[in] req - Holds parameters of the request.
See ZS_ZclAddGroupReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclAddGroupReq(const ZS_ZclAddGroupReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(GROUPS_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZS_ZclAddGroup_t) + req->addGroup.groupNameLen - 4);

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->addGroup, sizeof(ZS_ZclAddGroup_t) - 4);
  ptr += sizeof(ZS_ZclAddGroup_t) - 4;
  SYS_BYTE_MEMCPY(ptr, req->addGroup.name, req->addGroup.groupNameLen);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Add Scene command.

\param[in] req - Holds parameters of the request.
See ZS_ZclAddSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclAddSceneReq(const ZS_ZclAddSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZS_ZclAddScene_t) + req->addScene.sceneNameLen - sizeof(uintptr_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->addScene, sizeof(ZS_ZclAddScene_t) - sizeof(uintptr_t) - sizeof(extFields_t));
  ptr += sizeof(ZS_ZclAddScene_t) - sizeof(uintptr_t) - sizeof(extFields_t);
  SYS_BYTE_MEMCPY(ptr, req->addScene.name, req->addScene.sceneNameLen);
  ptr += req->addScene.sceneNameLen;
  SYS_BYTE_MEMCPY(ptr, &req->addScene.extField, sizeof(extFields_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a View Group command.

\param[in] req - Holds parameters of the request.
See ZS_ZclViewGroupReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclViewGroupReq(const ZS_ZclViewGroupReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(GROUPS_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_ViewGroup_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->viewGroup, sizeof(ZCL_ViewGroup_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a View Scene command.

\param[in] req - Holds parameters of the request.
See ZS_ZclViewSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclViewSceneReq(const ZS_ZclViewSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_ViewScene_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->viewScene, sizeof(ZCL_ViewScene_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Get Group Membership command.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetGroupMembershipReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetGroupMembershipReq(const ZS_ZclGetGroupMembershipReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(GROUPS_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZS_ZclGetGroupMembership_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->groupMembership, sizeof(ZS_ZclGetGroupMembership_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Get Scene Membership command.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetSceneMembershipReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetSceneMembershipReq(const ZS_ZclGetSceneMembershipReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_GetSceneMembership_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->sceneMembership, sizeof(ZCL_GetSceneMembership_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a On command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclOnReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(ONOFF_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_ONOFF_CLUSTER_ON_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         0);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Off command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclOffReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(ONOFF_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_ONOFF_CLUSTER_OFF_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         0);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Toggle command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclToggleReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(ONOFF_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_ONOFF_CLUSTER_TOGGLE_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         0);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Store Scene command.

\param[in] req - Holds parameters of the request.
See ZS_ZclStoreSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStoreSceneReq(const ZS_ZclStoreSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_StoreScene_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->storeScene, sizeof(ZCL_StoreScene_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Move To Level command.

\param[in] req - Holds parameters of the request.
See ZS_ZclMoveToLevelReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclMoveToLevelReq(const ZS_ZclMoveToLevelReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(LEVEL_CONTROL_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         req->affectOnOff ?  ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_W_ONOFF_COMMAND_ID : ZCL_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_MoveToLevel_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->moveToLevel, sizeof(ZCL_MoveToLevel_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Move command.

\param[in] req - Holds parameters of the request.
See ZS_ZclMoveReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclMoveReq(const ZS_ZclMoveReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

 fillCommonPartOfZclReq(LEVEL_CONTROL_CLUSTER_ID,
                        req->command.defaultResponse,
                        req->command.sequenceNumber,
                        req->affectOnOff ?  ZCL_LEVEL_CONTROL_CLUSTER_MOVE_W_ONOFF_COMMAND_ID : ZCL_LEVEL_CONTROL_CLUSTER_MOVE_COMMAND_ID,
                        req->command.srcEndpoint,
                        req->command.dstEndpoint,
                        commandFrame,
                        sizeof(ZCL_Move_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);

  SYS_BYTE_MEMCPY(ptr, &req->move, sizeof(ZCL_Move_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);

}
/***************************************************************************//**
\brief Requests to send a Step command.

\param[in] req - Holds parameters of the request.
See ZS_ZclStepReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStepReq(const ZS_ZclStepReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(LEVEL_CONTROL_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         req->affectOnOff ?  ZCL_LEVEL_CONTROL_CLUSTER_STEP_W_ONOFF_COMMAND_ID : ZCL_LEVEL_CONTROL_CLUSTER_STEP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_Step_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->step, sizeof(ZCL_Step_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Stop command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStopReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(LEVEL_CONTROL_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         req->affectOnOff ?  ZCL_LEVEL_CONTROL_CLUSTER_STOP_W_ONOFF_COMMAND_ID : ZCL_LEVEL_CONTROL_CLUSTER_STOP_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         0);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}

/***************************************************************************//**
\brief Requests to send a Recall Scenes command.

\param[in] req - Holds parameters of the request.
See ZS_ZclRecallSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/

void ZS_ZclRecallSceneReq(const ZS_ZclRecallSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_RecallScene_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->recallScene, sizeof(ZCL_RecallScene_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Remove All Scenes command.

\param[in] req - Holds parameters of the request.
See ZS_ZclRemoveAllScenesReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclRemoveAllScenesReq(const ZS_ZclRemoveAllScenesReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(SCENES_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         sizeof(ZCL_RemoveAllScenes_t));

  uint8_t *ptr = commandFrame->payload;
  ptr += sizeof(zsZclCommandRequest_t);
  SYS_BYTE_MEMCPY(ptr, &req->removeScenes, sizeof(ZCL_RemoveAllScenes_t));

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);

  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to send a Remove All Groups command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclRemoveAllGroupsReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;

  fillCommonPartOfZclReq(GROUPS_CLUSTER_ID,
                         req->command.defaultResponse,
                         req->command.sequenceNumber,
                         ZCL_GROUPS_CLUSTER_REMOVE_ALL_GROUPS_COMMAND_ID,
                         req->command.srcEndpoint,
                         req->command.dstEndpoint,
                         commandFrame,
                         0);

  setAwaitingReq(R_ZCL_COMMAND_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}

/**************************************************************************//**
\brief Sends next sequence number request
******************************************************************************/
void ZS_ZclNextSeqNumberReq(void)
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();

  buffer->commandFrame.commandId = R_ZCL_NEXT_SEQUENCE_NUMBER_REQ;
  buffer->commandFrame.length = R_COMMAND_ID_SIZE;

  serialManager.write(buffer);
}

/***************************************************************************//**
\brief This function fills the common part of each ZCL Request

\param[in] clusterId - Holds ID of cluser.
\param[in] defaultResponse - Holds defaultResponse.
\param[in] sequenceNumber - sequence number of the zcl transaction.
\param[in] commandId - Holds ID of commands.
\param[in] srcEndpoint - Holds Sorce End Point.
\param[in] dstEndpoint - Holds Destination End Point.
\param[in] commandFrame - Holds the buffer of type ZS_CommandFrame_t.
\param[in] payloadSize - command' payload size.

\return
*******************************************************************************/
static void fillCommonPartOfZclReq(uint16_t clusterId,
                                   uint8_t defaultResponse,
                                   uint8_t sequenceNumber,
                                   uint8_t commandId,
                                   uint8_t srcEndpoint,
                                   uint8_t dstEndpoint,
                                   ZS_CommandFrame_t *commandFrame,
                                   uint8_t payloadSize)
{
  zsZclCommandRequest_t head;

  head.addrMode = APS_NO_ADDRESS;
  head.clusterId = clusterId;
  head.defaultResponse = defaultResponse;
  head.sequenceNumber = sequenceNumber;
  head.commandId = commandId;
  head.commandOptions.direction = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER;
  head.commandOptions.generalCommand = 0;
  head.srcEndpoint = srcEndpoint;
  head.dstEndpoint = dstEndpoint;
  head.profileId = PROFILE_ID_HOME_AUTOMATION;
  head.recordsCount = 0;

  commandFrame->commandId = R_ZCL_COMMAND_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(zsZclCommandRequest_t);
  commandFrame->length += payloadSize;

  SYS_BYTE_MEMCPY(commandFrame->payload, &head, sizeof(zsZclCommandRequest_t));
}

#endif //ZCL_SUPPORT == 1

