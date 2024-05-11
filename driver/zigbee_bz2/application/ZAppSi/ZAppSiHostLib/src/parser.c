/*****************************************************************************
  \file parser.c

  \brief Parser module. Contains functions that process incoming frames.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 D. Kasyanov - Created
*******************************************************************************/
/******************************************************************************
 Includes section
 ******************************************************************************/
#include <ZAppSiHost.h>
#include <consts.h>
#include <ZAppSiIdentifiers.h>
#include <parser.h>
#include <sysUtils.h>
#include <ZAppSiDataTemplates.h>
#include <zcltools.h>
#include <bufferallocator.h>
/*****************************************************************************
 Define(s) section
******************************************************************************/
#define GET_AND_MOVE(type, ptr) *(type*)ptr; ptr += sizeof(type)

/**************************************************************************//**
Global variables section
******************************************************************************/
static struct
{
  CommandID_t id;
  void* cb;
} awaitingReq = {0, NULL};

/***************************************************************************//**
Implementations section
******************************************************************************/
/***************************************************************************//**
\brief Set parameters for incoming confirmation identification

This function allows to composer define what type of confirm parser should
wait.

\param[in] id - expected confirmation id
\param[in] cb - confirmation callback

\return nothing
******************************************************************************/
void setAwaitingReq(CommandID_t id, void *conf)
{
  awaitingReq.id = id;
  awaitingReq.cb = conf;
}
/***************************************************************************//**
\brief Make awaiting callback and return status.

This function is called after preparing incoming data to call according
callback.

\param[in] cmdId - required command id
\param[in] presult - prepared data

\return TRUE if callback calling is success, FALSE otherwise
******************************************************************************/
bool makeAwaitingCb(CommandID_t cmdId, void *presult)
{
  if ( awaitingReq.id == cmdId )
  {
    if ( NULL != awaitingReq.cb ) //if user send NULL as callback
    {
      ((void(*)(void*))awaitingReq.cb)(presult);
      return true;
    }
    else
    {
//      sysAssert(0);
    }
  }
  return false;
}

/***************************************************************************//**
 \brief This function is intended for confirms which should preprocesed before
    calling

 \param[in] commandFrame - pointer to incoming frame
 \return true if frame was preprocesed, false if its required further processing
 ******************************************************************************/
bool preprocessFrame(ZS_CommandBuffer_t *buffer)
{
  uint8_t processed = 0;
  ZS_CommandFrame_t* commandFrame = &buffer->commandFrame;
  CommandID_t cmdId = commandFrame->commandId;

  if (cmdId == R_ZDO_GET_NEIB_TABLE_CONFIRM)
  {
    uint8_t recordsAmount = *(uint8_t *) commandFrame->payload;
    ZS_ZdoGetNeibTableRecord_t records[CS_NEIB_TABLE_SIZE];
    ZS_ZdoGetNeibTableConf_t conf = {recordsAmount, records};
    SYS_BYTE_MEMCPY(&records, commandFrame->payload + 1,
                    sizeof(ZS_ZdoGetNeibTableRecord_t) * recordsAmount);
    processed += makeAwaitingCb(cmdId, (uint8_t*)&conf);
  }
  else if (cmdId == R_ZDO_SIMPLE_DESC_CONFIRM)
  {
    ZS_ZdpSimpleDescConf_t dconf;
    uint8_t* ptr = commandFrame->payload;

    //uncompress out clusters
    dconf.status = GET_AND_MOVE(uint8_t, ptr);
    dconf.nwkAddrOfInterest = GET_AND_MOVE(uint16_t, ptr);
    ptr++;
    dconf.endpoint = GET_AND_MOVE(uint8_t, ptr);
    dconf.AppProfileId = GET_AND_MOVE(uint16_t, ptr);
    dconf.AppDeviceId = GET_AND_MOVE(uint16_t, ptr);
    dconf.AppDeviceVersion = GET_AND_MOVE(uint8_t, ptr);
    dconf.AppInClustersCount = GET_AND_MOVE(uint8_t, ptr);
    dconf.AppInClustersList = (uint16_t*)ptr;
    ptr += (dconf.AppInClustersCount * sizeof(ClusterId_t));
    dconf.AppOutClustersCount = GET_AND_MOVE(uint8_t, ptr);
    dconf.AppOutClustersList = (uint16_t*)ptr;
    processed += makeAwaitingCb(cmdId, (uint8_t*)&dconf);
  }

#ifdef _ZCL_SUPPORT_ 
  else if (cmdId == R_ZCL_GET_CONFIRM)
  {
    ZS_ZclGetConfirm_t conf;
    SYS_BYTE_MEMCPY(&conf,
           commandFrame->payload,
           offsetof(ZS_ZclGetConfirm_t, value));
    conf.value = commandFrame->payload + offsetof(ZS_ZclGetConfirm_t, value);
    processed += makeAwaitingCb(cmdId, (uint8_t*)&conf);
  }
  else if (cmdId == R_ZCL_ATTRIBUTE_VALUE_CONFIRM)
  {
    if (0/*READ*/ == commandFrame->payload[1])
    {
      ZS_ZclReadAttributeValueConfirm_t dconf;
      dconf.status = commandFrame->payload[0];
      SYS_BYTE_MEMCPY((uint8_t*)&dconf+1,
          &commandFrame->payload[2],
          offsetof(ZS_ZclReadAttributeValueConfirm_t, value)-1);
      dconf.value = commandFrame->payload + offsetof(ZS_ZclReadAttributeValueConfirm_t, value)+1;
      processed += makeAwaitingCb(cmdId, (uint8_t*)&dconf);
    }
    else
    {
      ZS_ZclWriteAttributeValueConfirm_t conf ;
      conf.status = commandFrame->payload[0];
      processed += makeAwaitingCb(cmdId, (uint8_t*)&conf);
    }
  }
  else if (cmdId == R_ZCL_ATTRIBUTE_RESPONSE)
  {
    uint8_t *ptr = commandFrame->payload;
    uint8_t status = *(uint8_t*)ptr;
    ptr += sizeof(status);

    uint8_t commandId = *(uint8_t*)(ptr);
    ptr += sizeof(commandId);

    if (commandId == ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID)
    {
      ZS_ZclReadAttributeResp_t resp;
      ZS_ZclReadAttributeRespRecord_t  values[3]; // = allocate(); // allocate memory
      ZS_ZclTypeValue_t typeValues[3]; // = allocate(); // allocate memory

      resp.records = values;

      resp.status = status;
      resp.recordsCount = *(uint8_t*)ptr;
      ptr += sizeof(resp.recordsCount);

      int i = 0;
      uint8_t typeSize = 0;
      for (i = 0; i < resp.recordsCount; ++i)
      {
        values[i].attributeId = *(uint16_t*)ptr;
        ptr += sizeof(uint16_t);

        values[i].status = *(uint8_t*)ptr;
        ptr += sizeof(uint8_t);

        if (values[i].status == ZS_SUCCESS_STATUS)
        {
          values[i].attribute = &typeValues[i];
          values[i].attribute->type = *(uint8_t*)ptr;
          ptr += sizeof(uint8_t);
          values[i].attribute->value = ptr;

          typeSize = zsSizeofAttributeType(values[i].attribute->type);
          ptr += typeSize;
        }
        else
        {
          values[i].attribute = 0;
        }
      }

      processed += makeAwaitingCb(cmdId, (uint8_t*)&resp);

    //  free(values);
    // free(typeValues);
    }
    else if (commandId == ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID)
    {
      ZS_ZclWriteAttributeResp_t resp;

      resp.status = status;
      resp.recordsCount = *(uint8_t*)ptr;
      ptr += sizeof(uint8_t);
      resp.records = (ZS_ZclWriteAttributeRespRecord_t*)ptr;

      processed += makeAwaitingCb(cmdId, (uint8_t*)&resp);
    }
    else if (commandId == ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID)
    {
      ZS_ZclConfigureReportingResp_t resp;

      resp.status = status;
      resp.recordsCount = *(uint8_t*)ptr;
      ptr += sizeof(uint8_t);
      resp.records = (ZS_ZclConfigureReportingRespRecord_t*)ptr;

      processed += makeAwaitingCb(cmdId, (uint8_t*)&resp);
    }
    else if (commandId == ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID)
    {
      ZS_ZclDiscoverAttributesResp_t resp;

      resp.discoveryComplete = *(uint8_t*)ptr;
      ptr += sizeof(uint8_t);
      resp.status = status;
      resp.recordsCount = *(uint8_t*)ptr;
      ptr += sizeof(uint8_t);
      resp.records = (ZS_ZclDiscoverAttributesRespRecord_t*)ptr;

      processed += makeAwaitingCb(cmdId, (uint8_t*)&resp);
    }
    else if (commandId == ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID)
    {
      ZS_ZclReadReportingConfigResp_t resp;
      ZS_ZclReadReportingConfigRespRecord_t respRecords[3]; // memory should be allocated

      resp.status = status;
      resp.recordsCount = *(uint8_t*)ptr;
      ptr += sizeof(uint8_t);

      resp.records = respRecords;
      int i = 0;
      uint8_t size = 0;
      ZS_ZclReadReportingConfigRespRecord_t* record = resp.records;

      for (i = 0; i < resp.recordsCount; ++i)
      {
        SYS_BYTE_MEMCPY(&record->status, ptr, sizeof(record->status));
        ptr += sizeof(record->status);

        SYS_BYTE_MEMCPY(&record->direction, ptr, sizeof(record->direction));
        ptr += sizeof(record->direction);

        SYS_BYTE_MEMCPY(GET_FIELD_PTR(record,  ZS_ZclReadReportingConfigRespRecord_t, attributeId),
	  ptr,
	  sizeof(record->attributeId));
        ptr += sizeof(record->attributeId);

        SYS_BYTE_MEMCPY(&record->attributeType, ptr, sizeof(record->attributeType));
        ptr += sizeof(record->attributeType);

        SYS_BYTE_MEMCPY(GET_FIELD_PTR(record, ZS_ZclReadReportingConfigRespRecord_t, minReportingInterval),
	  ptr,
	  sizeof(record->minReportingInterval));
        ptr += sizeof(record->minReportingInterval);

        SYS_BYTE_MEMCPY(GET_FIELD_PTR(record, ZS_ZclReadReportingConfigRespRecord_t, maxReportingInterval),
	  ptr,
	  sizeof(record->maxReportingInterval));
        ptr += sizeof(record->maxReportingInterval);

        record->reportableChange = ptr;
        size = zsSizeofAttributeType(record->attributeType);

        ptr += size;
	record++;
      }

      processed += makeAwaitingCb(cmdId, (uint8_t*)&resp);
    }
  }
#endif// ZCL_SUPPORT == 1
  return processed;
}
/***************************************************************************//**
 \brief This function is intended for possible indication process

 \param[in] commandFrame - pointer to incoming frame
 \return none
******************************************************************************/
void postprocessFrame(ZS_CommandBuffer_t *buffer)
{
  ZS_CommandFrame_t* commandFrame = &buffer->commandFrame;
  CommandID_t cmdId = commandFrame->commandId;

  if (cmdId == R_ZDO_MGMT_NWK_UPDATE_NOTIFY)
  {
    ZS_MgmtNwkUpdateNotf_t conf;

    SYS_BYTE_MEMCPY(&conf, commandFrame->payload, sizeof(ZS_MgmtNwkUpdateNotf_t));
    ZS_ZdoMgmtNwkUpdateNotify(&conf);
  }
  else if (cmdId == R_APSDE_DATA_INDICATION)
  {
    ZS_ApsDataInd_t ind;
    uint8_t *ptr = commandFrame->payload;

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, dstAddrMode),
	            ptr,
	            sizeof(ind.dstAddrMode));
    ptr += sizeof(ind.dstAddrMode);

    if (ind.dstAddrMode == ZS_EXTENDED_ADDRESS_MODE)
    {
      SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, dstAddr),
	              ptr,
		      sizeof(ind.dstAddr.extAddr));
      ptr += sizeof(ind.dstAddr.extAddr);
    }
    else if (ind.dstAddrMode == ZS_SHORT_ADDRESS_MODE)
    {
      SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, dstAddr),
	              ptr,
		      sizeof(ind.dstAddr.shortAddr));
      ptr += sizeof(ind.dstAddr.shortAddr);
    }

    if (ind.dstAddrMode != ZS_GROUP_ADDRESS_MODE)
    {
      SYS_BYTE_MEMCPY(&ind.dstEndpoint, ptr, sizeof(ind.dstEndpoint));
      ptr += sizeof(ind.dstEndpoint);
    }

    SYS_BYTE_MEMCPY(&ind.srcAddrMode, ptr, sizeof(ind.srcAddrMode));
    ptr += sizeof(ind.srcAddrMode);

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, srcAddr),
	            ptr,
		    sizeof(ind.srcAddr.shortAddr));
    ptr += sizeof(ind.srcAddr.shortAddr);

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, srcAddr),
	            ptr,
		    sizeof(ind.srcAddr.extAddr));
    ptr += sizeof(ind.srcAddr.extAddr);

    SYS_BYTE_MEMCPY(&ind.srcEndpoint, ptr, sizeof(ind.srcEndpoint));
    ptr += sizeof(ind.srcEndpoint);

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, profileId),
	            ptr, sizeof(ind.profileId));
    ptr += sizeof(ind.profileId);

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(&ind, ZS_ApsDataInd_t, clusterId),
	            ptr, sizeof(ind.clusterId));
    ptr += sizeof(ind.clusterId);

    SYS_BYTE_MEMCPY(&ind.asduLength, ptr, sizeof(ind.asduLength));
    ptr += sizeof(ind.asduLength);

    ind.asdu = ptr;

    ptr += ind.asduLength;

    SYS_BYTE_MEMCPY(&ind.status, ptr, sizeof(ind.status));
    ptr += sizeof(ind.status);

    SYS_BYTE_MEMCPY(&ind.securityStatus, ptr, sizeof(ind.securityStatus));

    ZS_ApsDataInd(&ind);
  }
#ifdef _ZCL_SUPPORT_ 
  else if (cmdId == R_ZCL_REPORT_INDICATION)
  {
    ZS_ZclReportInd_t conf;
    SYS_BYTE_MEMCPY(&conf,
           commandFrame->payload,
           offsetof(ZS_ZclReportInd_t, report));
    conf.report = commandFrame->payload + offsetof(ZS_ZclReportInd_t, report);
    ZS_ZclReportInd(&conf);
  }
  else if (cmdId == R_ZCL_ATTRIBUTE_EVENT_IND)
  {
    ZS_ZclAttributeEventInd_t *ind = (ZS_ZclAttributeEventInd_t*)commandFrame->payload;

    ZS_ZclAttributeEventInd(ind);
  }
  else if (cmdId == R_ZCL_DEFAULT_RESPONSE)
  {
    RZclDefaultResponseInd_t *ind = (RZclDefaultResponseInd_t *)commandFrame->payload;

    ZS_ZclDefaultResponseInd(ind);
  }
  else if (cmdId == R_ZCL_NEXT_SEQUENCE_NUMBER_RESP)
  {
    RZclNextSequenceNumberResp_t *ind = (RZclNextSequenceNumberResp_t *)commandFrame->payload;

    ZS_ZclNextSeqNumberRespInd(ind);
  }
  else if (cmdId == R_ZCL_COMMAND_INDICATION)
  {
    RZclCommandIndication_t *commandInd = (RZclCommandIndication_t*)commandFrame->payload;
    ZS_ZclCommandInd_t zclCommandInd;

    zclCommandInd.clusterId = commandInd->clusterId;
    zclCommandInd.direction = commandInd->direction;
    zclCommandInd.srcAddrMode = commandInd->srcAddrMode;
    zclCommandInd.srcClusterId = commandInd->srcClusterId;
    zclCommandInd.srcEndpointId = commandInd->srcEndpointId;
    zclCommandInd.srcExtAddress = commandInd->srcExtAddress;
    zclCommandInd.srcProfileId = commandInd->srcProfileId;
    zclCommandInd.srcShortAddress = commandInd->srcShortAddress;

    if (commandInd->clusterId == IDENTIFY_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {
        if (commandInd->commandId == ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID)
        {
          ZS_ZclIdentifyInd_t identifyInd;
          identifyInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&identifyInd.identify, &commandInd->payload, sizeof(ZCL_Identify_t));

          ZS_ZclIdentifyInd(&identifyInd);
        }
        else if (commandInd->commandId == ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_COMMAND_ID)
        {
          ZS_ZclIdentifyQueryInd_t identifyQueryInd;

          identifyQueryInd = zclCommandInd;

          ZS_ZclIdentifyQueryInd(&identifyQueryInd);
        }
      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID)
        {
          ZS_ZclIdentifyQueryResponseInd_t identifyQueryResponseInd;

          identifyQueryResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&identifyQueryResponseInd.identifyQueryResponse, &commandInd->payload, sizeof(ZCL_IdentifyQueryResponse_t));

          ZS_ZclIdentifyQueryResponseInd(&identifyQueryResponseInd);
        }
      }
    }
    else if (commandInd->clusterId == PRICE_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {
        if (commandInd->commandId == GET_CURRENT_PRICE_COMMAND_ID)
        {
          ZS_ZclGetCurrentPriceInd_t getCurrentPriceInd;

          getCurrentPriceInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&getCurrentPriceInd.getCurrentPrice, &commandInd->payload, sizeof(ZCL_GetCurrentPrice_t));

          ZS_ZclGetCurrentPriceInd(&getCurrentPriceInd);
        }
      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == PUBLISH_PRICE_COMMAND_ID)
        {
          ZS_ZclPublishPriceInd_t publishPriceInd;

          publishPriceInd.command = zclCommandInd;

          uint8_t *ptr = (uint8_t*)&commandInd->payload;
          publishPriceInd.publishPrice.providerId = *(uint32_t*)ptr;
          ptr += sizeof(uint32_t);

          publishPriceInd.publishPrice.rateLabelLength = *(uint8_t*)ptr;
          ptr += sizeof(uint8_t);

          publishPriceInd.publishPrice.rateLabel = ptr;
          ptr += publishPriceInd.publishPrice.rateLabelLength;

          SYS_BYTE_MEMCPY(GET_FIELD_PTR(&publishPriceInd.publishPrice, ZS_ZclPublishPrice_t, issuerEventId),
	    ptr,
	    sizeof(ZCL_PublishPrice_t) - offsetof(ZCL_PublishPrice_t, issuerEventId));

          ZS_ZclPublishPriceInd(&publishPriceInd);
        }
      }
    }
    else if (commandInd->clusterId == DEMAND_RESPONSE_AND_LOAD_CONTROL_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {
        if (commandInd->commandId == REPORT_EVENT_STATUS_COMMAND_ID)
        {
          ZS_ZclReportEventStatusInd_t reportEventStatusInd;

          reportEventStatusInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&reportEventStatusInd.reportEventStatus, &commandInd->payload, sizeof(ZCL_ReportEventStatus_t));

          ZS_ZclReportEventStatusInd(&reportEventStatusInd);
        }
        else if (commandInd->commandId == GET_SCHEDULED_EVENTS_COMMAND_ID)
        {
          ZS_ZclGetScheduledEventsInd_t getScheduledEventsInd;

          getScheduledEventsInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&getScheduledEventsInd.getScheduledEvents, &commandInd->payload, sizeof(ZCL_GetScheduledEvents_t));

          ZS_ZclGetScheduledEventsInd(&getScheduledEventsInd);
        }
      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == LOAD_CONTROL_EVENT_COMMAND_ID)
        {
          ZS_ZclLoadControlEventInd_t loadControlEventInd;

          loadControlEventInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&loadControlEventInd.loadControlEvent, &commandInd->payload, sizeof(ZCL_LoadControlEvent_t));

          ZS_ZclLoadControlEventInd(&loadControlEventInd);
        }
        else if (commandInd->commandId == CANCEL_LOAD_CONTROL_EVENT_COMMAND_ID)
        {
          ZS_ZclCancelLoadControlEventInd_t cancelLoadControlInd;

          cancelLoadControlInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&cancelLoadControlInd.cancelLoadControlEvent, &commandInd->payload, sizeof(ZCL_CancelLoadControlEvent_t));

          ZS_ZclCancelLoadControlEventInd(&cancelLoadControlInd);
        }
        else if (commandInd->commandId == CANCEL_ALL_LOAD_CONTROL_EVENTS_COMMAND_ID)
        {
          ZS_ZclCancelAllLoadControlEventsInd_t cancelAllLoadControlInd;

          cancelAllLoadControlInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&cancelAllLoadControlInd.cancelAllLoadControlEvents, &commandInd->payload, sizeof(ZCL_CancelAllLoadControlEvents_t));

          ZS_ZclCancelAllLoadControlEventsInd(&cancelAllLoadControlInd);
        }
      }
    }
    else if (commandInd->clusterId == MESSAGE_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {
        if (commandInd->commandId == GET_LAST_MESSAGE_COMMAND_ID)
        {
          ZS_ZclGetLastMessageInd_t getLastMessageInd;

          getLastMessageInd = zclCommandInd;

          ZS_ZclGetLastMessageInd(&getLastMessageInd);
        }
        else if(commandInd->commandId == CONFIRM_MESSAGE_COMMAND_ID)
        {
          ZS_ZclMessageConfirmationInd_t messageConfirmationInd;

          messageConfirmationInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&messageConfirmationInd.messageConfirmation, &commandInd->payload, sizeof(MessageConfirmation_t));

          ZS_ZclMessageConfirmationInd(&messageConfirmationInd);
        }
      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == DISPLAY_MESSAGE_COMMAND_ID)
        {
          ZS_ZclDisplayMessageInd_t displayMessage;

          displayMessage.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&displayMessage.displayMessage, &commandInd->payload, sizeof(ZS_ZclDisplayMessage_t) - sizeof(char*));

          displayMessage.displayMessage.message = (char*)&commandInd->payload[offsetof(ZS_ZclDisplayMessage_t, message)];

          ZS_ZclDisplayMessageInd(&displayMessage);
        }
        else if(commandInd->commandId == CANCEL_MESSAGE_COMMAND_ID)
        {
          ZS_ZclCancelMessageInd_t cancelMessage;

          cancelMessage.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&cancelMessage.cancelMessage, &commandInd->payload, sizeof(ZS_ZclCancelMessageInd_t));

          ZS_ZclCancelMessageInd(&cancelMessage);
        }
      }
    }
    else if (commandInd->clusterId == GROUPS_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {

      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == ZCL_GROUPS_CLUSTER_ADD_GROUP_COMMAND_ID)
        {
          ZS_ZclAddGroupResponseInd_t addGroupResponseInd;

          addGroupResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&addGroupResponseInd.addGroupResponse, &commandInd->payload, sizeof(ZCL_AddGroupResponse_t));

          ZS_ZclAddGroupResponseInd(&addGroupResponseInd);
        }
        else if (commandInd->commandId == ZCL_GROUPS_CLUSTER_VIEW_GROUP_COMMAND_ID)
        {
          ZS_ZclViewGroupResponseInd_t viewGroupResponseInd;

          viewGroupResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&viewGroupResponseInd.viewGroup, &commandInd->payload, sizeof(ZCL_ViewGroupResponse_t));

          ZS_ZclViewGroupResponseInd(&viewGroupResponseInd);
        }
        else if (commandInd->commandId == ZCL_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP_COMMAND_ID)
        {
          ZS_ZclGetGroupMembershipResponseInd_t getGroupMembershipResponseInd;

          getGroupMembershipResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&getGroupMembershipResponseInd.groupMembership, &commandInd->payload, sizeof(ZCL_GetGroupMembershipResponse_t));

          ZS_ZclGetGroupMembershipResponseInd(&getGroupMembershipResponseInd);
        }
      }
    }
    else if (commandInd->clusterId == SCENES_CLUSTER_ID)
    {
      if (commandInd->direction == ZS_DIRECTION_FROM_CLIENT_TO_SERVER)
      {

      }
      else if (commandInd->direction == ZS_DIRECTION_FROM_SERVER_TO_CLIENT)
      {
        if (commandInd->commandId == ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID)
        {
          ZS_ZclAddSceneResponseInd_t addSceneResponseInd;

          addSceneResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&addSceneResponseInd.addScene, &commandInd->payload, sizeof(ZCL_AddSceneResponse_t));

          ZS_ZclAddSceneResponseInd(&addSceneResponseInd);
        }
        else if (commandInd->commandId == ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID)
        {
          ZS_ZclViewSceneResponseInd_t viewSceneResponseInd;

          viewSceneResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&viewSceneResponseInd.viewScene, &commandInd->payload, sizeof(ZCL_ViewSceneResponse_t));

          ZS_ZclViewSceneResponseInd(&viewSceneResponseInd);
        }
        else if (commandInd->commandId == ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID)
        {
          ZS_ZclGetSceneMembershipResponseInd_t getSceneMembershipResponseInd;

          getSceneMembershipResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&getSceneMembershipResponseInd.sceneMembership, &commandInd->payload, sizeof(ZCL_GetSceneMembershipResponse_t));

          ZS_ZclGetSceneMembershipResponseInd(&getSceneMembershipResponseInd);
        }
        else if (commandInd->commandId == ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID)
        {
          ZS_ZclRemoveAllScenesResponseInd_t removeAllScenesResponseInd;

          removeAllScenesResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&removeAllScenesResponseInd.removeScenes, &commandInd->payload, sizeof(ZCL_RemoveAllScenesResponse_t));

          ZS_ZclRemoveAllScenesResponseInd(&removeAllScenesResponseInd);
        }
        else if (commandInd->commandId == ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID)
        {
          ZS_ZclStoreSceneResponseInd_t storeSceneResponseInd;

          storeSceneResponseInd.command = zclCommandInd;

          SYS_BYTE_MEMCPY(&storeSceneResponseInd.storeScene, &commandInd->payload, sizeof(ZCL_StoreSceneResponse_t));

          ZS_ZclStoreSceneResponseInd(&storeSceneResponseInd);
        }
      }
    }
  }
#endif //ZCL_SUPPORT == 1
}

/***************************************************************************//**
 \brief Incoming frames parsing function
 The main parse function. Function parses the commandFrame parameter and
 invokes the corresponding function.

 \param[in] commandFrame - pointer to incoming frame
 \return nothing
 ******************************************************************************/
void parse(ZS_CommandBuffer_t *buffer)
{
  if (!preprocessFrame(buffer))
  {
    //if frame wasn't be processed try to call ordinary handler callback
    //which was last commited
    if (!makeAwaitingCb(buffer->commandFrame.commandId, buffer->commandFrame.payload))
    {
      //if no awaiting callback was called then treat with frame as indication
      postprocessFrame(buffer);
    }
  }
  bufferAllocator.free(buffer);
}
/***************************************************************************//**
\brief This function prepare lib for working. It should be called before using
commands.

\param[in] interfaceID - Holds command's parameters and payload.

\return none
*******************************************************************************/
void ZS_Open(uint8_t interfaceID)
{
  openSerialManager(interfaceID, parse);
}


