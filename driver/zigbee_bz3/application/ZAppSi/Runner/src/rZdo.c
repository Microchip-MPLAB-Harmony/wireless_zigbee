/**************************************************************************//**
  \file  rZdo.c

  \brief Zdo commands Implementation

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
#include <zdo/include/zdo.h>
#include <rMem.h>
#include <rDebug.h>
#include <rAps.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
#include <zdo/include/zdoSecurityManager.h>
#ifdef _ZIGBEE_REV_23_SUPPORT_
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/at86rf233.h> // Included for Obtaining RF_MAX_CHANNEL & RF_MIN_CHANNEL
#include <zdo/include/zdoSecurityStartKeyUpdate.h>
#endif
/*****************************************************************************
                               Definitions section
******************************************************************************/
#ifndef APP_EXTENDED_ZDP_REQUEST
#define APP_EXTENDED_ZDP_REQUEST   1
#endif

#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
static void zdoReqCmdRxdHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoReqCmdRxdReceiver = {  .func = zdoReqCmdRxdHandler };

static void zdoReqCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoReqCmdValidation = {  .func = zdoReqCmdValidationHandler };

static void zdoRspCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoRspCmdValidation = {  .func = zdoRspCmdValidationHandler };
#endif

#ifdef _ZIGBEE_REV_23_SUPPORT_
/***************** Definition for Security Set Configuration  - Request and Response *********/
#define SECURITY_SET_CONFIG_MAX_TLV 3   // Security set Configuration Request - TLV0 - Next PAN, TLV1 - Next Channel, TLV2 - Configuration Parameter
#define  MAX_CONFIG_PARAMS    7         // First 3 bit represents - AIB, Device - Security, NIB only in use, rest 3 to 15 reserved 

#endif
/******************************************************************************
                   Implementations section
 ******************************************************************************/
void rZdoGetNeibAmountProcess(ZS_CommandBuffer_t *commandBuffer)
{
  DeviceType_t deviceType;
  ZDO_GetNeibAmount_t zdoGetNeibAmount;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_ZdoGetNeibAmountConf_t *confirm = (ZS_ZdoGetNeibAmountConf_t *) confirmBuffer->commandFrame.payload;

  (void)commandBuffer;

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);
  ZDO_GetNeibAmount(&zdoGetNeibAmount);
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoGetNeibAmountConf_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_GET_NEIB_AMOUNT_CONFIRM;
  confirm->routersAmount = zdoGetNeibAmount.routersAmount;
  confirm->enddevicesAmount = zdoGetNeibAmount.childrenAmount;
  serialManager.write(confirmBuffer);
}

void rZdoGetNeibTableProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t i;
  ZDO_GetNeibAmount_t zdoGetNeibAmount;
  ZDO_Neib_t zdoNeib[CS_NEIB_TABLE_SIZE];
  ZS_CommandBuffer_t *confirmBuffer = (ZS_CommandBuffer_t *) bufferAllocator.allocate();
  uint8_t *recordsAmount = (uint8_t *) confirmBuffer->commandFrame.payload;
  ZS_ZdoGetNeibTableRecord_t *confirm = (ZS_ZdoGetNeibTableRecord_t *) (confirmBuffer->commandFrame.payload + sizeof (uint8_t));

  (void)commandBuffer;

  ZDO_GetNeibAmount(&zdoGetNeibAmount);
  zdoGetNeibAmount.childrenAmount += zdoGetNeibAmount.routersAmount; // Summary neibs amount
  ZDO_GetNeibTable(zdoNeib);

  *recordsAmount = zdoGetNeibAmount.childrenAmount;
  for (i = 0; i < zdoGetNeibAmount.childrenAmount; i++)
  {
    confirm[i].shortAddr = zdoNeib[i].shortAddr;
    confirm[i].extAddr = zdoNeib[i].extAddr;
    confirm[i].deviceType = zdoNeib[i].deviceType;
    confirm[i].lqi = zdoNeib[i].lqi;
    confirm[i].rssi = zdoNeib[i].rssi;
  }

  confirmBuffer->commandFrame.commandId = R_ZDO_GET_NEIB_TABLE_CONFIRM;
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t) + zdoGetNeibAmount.childrenAmount * sizeof(ZS_ZdoGetNeibTableRecord_t);

  serialManager.write(confirmBuffer);
}

static void rZdoMgmtLeaveResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoMgmtLeaveConf_t *rConf = (ZS_ZdoMgmtLeaveConf_t *) confBuffer->commandFrame.payload;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_LEAVE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoMgmtLeaveConf_t);

  SYS_BYTE_MEMCPY(&rConf->status, &conf->respPayload.status, sizeof (uint8_t));
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoMgmtLeaveRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ExtAddr_t tempDstAddr;
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtLeaveReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtLeaveReq;
  ZS_ZdoMgmtLeaveReq_t *rReq = (ZS_ZdoMgmtLeaveReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoMgmtLeaveResponse;
  zdpClientReq->reqCluster = MGMT_LEAVE_CLID;
  zdpClientReq->dstAddrMode = APS_EXT_ADDRESS;

  tempDstAddr = rReq->dstAddr;
  COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  tempDstAddr = rReq->deviceAddr;
  COPY_EXT_ADDR_A(zdpReq->deviceAddr, &tempDstAddr);
  zdpReq->rejoin = rReq->rejoin;
  zdpReq->removeChildren = rReq->removeChildren;
  zdpReq->reserved = 0;

  ZDO_ZdpReq(zdpClientReq);

}

#ifdef _ZIGBEE_REV_23_SUPPORT_
/*****************************************************************************
\brief Beacon response callback
\param[in] resp - response payload
*****************************************************************************/
static void rZdoSurveyBeaconResp(ZDO_ZdpResp_t *resp) 
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZDO_ZdoMgmtBconSurveyResp_t *rResp =  (ZS_ZDO_ZdoMgmtBconSurveyResp_t *)confBuffer->commandFrame.payload;
  
  confBuffer->commandFrame.commandId = 	R_ZDO_BEACON_SURVEY_CONFIRM;
  confBuffer->commandFrame.length = 	R_COMMAND_ID_SIZE + sizeof(ZS_ZDO_ZdoMgmtBconSurveyResp_t);
  
  SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
  SYS_BYTE_MEMCPY(&rResp->beaconResultsTlv, &resp->respPayload.asduBuffer, (sizeof(ZS_ZDO_ZdoMgmtBconSurveyResp_t) - 1));
  serialManager.write(confBuffer);
  rFreeMem(resp);
}

/*****************************************************************************
\brief Sends Management Survey Beacon request
\param[in] shortAddr        - short address / destination node;
\param[in] tlvID            - tlv ID
\parma[in] tlvlength        - tlv Length
\param[in] configBitMask  -  configBitMask
\param[in] scanChannelList  - scanChannelList
******************************************************************************/
void rZdoMgmtBeaconSurveyReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  uint8_t *tlvData = (uint8_t *)&zdpReq->req.reqPayload.asduBuffer;
  ZDO_MgmtBconSurveyReq_t surveyBeaconReq;
  ZS_ZdoMgmtBeaconReq_t *rReq = (ZS_ZdoMgmtBeaconReq_t *) commandBuffer->commandFrame.payload;
  zdpReq->ZDO_ZdpResp = rZdoSurveyBeaconResp;
  zdpReq->reqCluster = MGMT_NWK_BEACON_SURVEY_CLID;
  zdpReq->dstAddrMode = APS_SHORT_ADDRESS;

  zdpReq->dstAddress.shortAddress = rReq->dstAddr;
  surveyBeaconReq.tlvID = rReq->tlvID;
  surveyBeaconReq.tlvLength = rReq->tlvLength;
  surveyBeaconReq.configBitMask = rReq->configBitMask;
  surveyBeaconReq.scanChannelList.channelPageCount = rReq->scanChannelList.channelPageCount;
  surveyBeaconReq.scanChannelList.channelMask = rReq->scanChannelList.channelMask;
  
  (void)TLV_Encode(tlvData, &surveyBeaconReq);
  zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(surveyBeaconReq.tlvLength);
  ZDO_ZdpReq(zdpReq);  
}

/**************************************************************************//**
\brief Security set Config response callback
\param[in] resp - response payload
********************************************************************************************/
void rZDOSecuritySetConfigConf(ZDO_ZdpResp_t *resp)
{
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZDO_SecuritySetConfigResp_t *rResp = (ZDO_SecuritySetConfigResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_SECURITY_SET_CONFIG_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZDO_SecuritySetConfigResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
    serialManager.write(confBuffer);
    rFreeMem(resp);
}

/*******************************************************************************
\brief Sends the Zappsi - Security Set Configuration request process
\param[in] dstaddr - nwk address of destination node
\param[in] panIdTlvId - PAN ID TLV ID
\param[in] panId - PAN ID
\param[in] channelTlvId - Channel TLV ID
\param[in] channel - Channel
\param[in] cfgParamsTlvId - Configuration parameters TLV Id
\param[in] configParams - Configuration parameters
*****************************************************************************/
void rZdoSecuritySetConfigReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
   ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();

   NextPanIdChangeTlv_t nextPanIdTlv;
   NextChannelChangeTlv_t nextChannelChangeTlv;
   ConfigurationParametersTlv_t configParamsTlv;

   ZS_ZdoSecuritySetConfigReq_t *rReq = (ZS_ZdoSecuritySetConfigReq_t *) commandBuffer->commandFrame.payload;
   zdpReq->ZDO_ZdpResp = rZDOSecuritySetConfigConf;
   zdpReq->reqCluster  = SECURITY_SET_CONFIG_CLID;
   zdpReq->dstAddrMode = APS_SHORT_ADDRESS;
   zdpReq->dstAddress.shortAddress = rReq->dstAddr;
   zdpReq->asduPayloadLength = 0;
   
   uint8_t panIdTlvId     = rReq->nextPanIdTlv.tagId;
   uint8_t channelTlvId   = rReq->nextChannelChangeTlv.tagId;
   uint8_t cfgParamsTlvId = rReq->configParamsTlv.tagId; 
   
   uint8_t panIdTlvLength = rReq->nextPanIdTlv.length;
   uint8_t channelTlvLength = rReq->nextChannelChangeTlv.length;
   uint8_t cfgParamsTlvLength = rReq->configParamsTlv.length;
  
   PanId_t   panIdField        = rReq->nextPanIdTlv.nextPanIdChange;
   uint32_t channelField      = rReq->nextChannelChangeTlv.channelField;
   uint16_t  configParams = rReq->configParamsTlv.configurationParameters;
   
   uint8_t *tlvData = (uint8_t *)&zdpReq->req.reqPayload.asduBuffer;
   uint8_t *nextBufPtr = NULL;
   
   int tlvIndex  = 0;
   uint8_t tlvId[SECURITY_SET_CONFIG_MAX_TLV] = {panIdTlvId, channelTlvId, cfgParamsTlvId};
   for(tlvIndex =0; tlvIndex <SECURITY_SET_CONFIG_MAX_TLV; tlvIndex++)
   {
       switch(tlvId[tlvIndex])
       {
           case NEXT_PAN_ID_CHANGE:
               nextPanIdTlv.tagId           = rReq->nextPanIdTlv.tagId;
               nextPanIdTlv.length          = rReq->nextPanIdTlv.length;
               nextPanIdTlv.nextPanIdChange = panIdField;
               if(nextBufPtr == NULL)
               {
                  nextBufPtr = TLV_Encode(tlvData, &nextPanIdTlv);
                  zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(panIdTlvLength);
               }
               else
               {
                   nextBufPtr = TLV_Encode(nextBufPtr, &nextPanIdTlv);
                   zdpReq->asduPayloadLength += TOTAL_TLV_SIZE(panIdTlvLength);
               }
               break;
               
           case NEXT_CHANNEL_CHANGE:               
               if((channelField >= RF_MIN_CHANNEL)&&(channelField <= RF_MAX_CHANNEL))
               {
                  nextChannelChangeTlv.tagId        = rReq->nextChannelChangeTlv.tagId;
                  nextChannelChangeTlv.length       = rReq->nextChannelChangeTlv.length;
                  nextChannelChangeTlv.channelField = 1 << channelField;
                  if(nextBufPtr == NULL)
                  {
                      nextBufPtr = TLV_Encode(tlvData, &nextChannelChangeTlv);
                      zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(channelTlvLength);
                  }
                  else
                  {
                      nextBufPtr = TLV_Encode(nextBufPtr, &nextChannelChangeTlv);
                      zdpReq->asduPayloadLength += TOTAL_TLV_SIZE(channelTlvLength);
                              
                  }
               }
               break;
           case CONFIGURATION_PARAMETER:
               if(configParams <= MAX_CONFIG_PARAMS)
               {
                  configParamsTlv.tagId                     =  rReq->configParamsTlv.tagId;
                  configParamsTlv.length                    =  rReq->configParamsTlv.length;
                  configParamsTlv.configurationParameters   =  configParams;
                  if(nextBufPtr == NULL)
                  {
                      nextBufPtr = TLV_Encode(tlvData, &configParamsTlv);
                      zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(cfgParamsTlvLength);
                      
                  }
                  else
                  {
                      nextBufPtr = TLV_Encode(nextBufPtr, &configParamsTlv);
                      zdpReq->asduPayloadLength += TOTAL_TLV_SIZE(cfgParamsTlvLength);
                  }                  
               }
               break;
           default:
               break;    
       }
   }
    ZDO_ZdpReq(zdpReq);
}

/**************************************************************************
\brief Security Get Config response callback
\param[in] resp - response payload
****************************************************************************/
void zdpSecurityGetConfigResponse(ZDO_ZdpResp_t *resp)
{
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZDO_SecurityGetConfigResp_t *rResp = (ZDO_SecurityGetConfigResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_SECURITY_GET_CONFIG_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZDO_SecurityGetConfigResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
    serialManager.write(confBuffer);
    rFreeMem(resp);
}

/******************************************************************************************
 * Breif Sends the Security Get Configuration Request
 * param[in] dstAddr  - nwk Address of Destination Address
 * param[in] tlvCount - The number of TLV Ids (tlv counts) in the message,
 * param[in] tlvId    - The Pointer to ID of each TLV that is being Requested . 
 *****************************************************************************************/
void rZdoSecurityGetConfigReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_SecurityGetConfigReq_t *getConfigReq = &zdpReq->req.reqPayload.getConfigReq;
  ZDOSecurityGetConfigReq_t *rGetConfigReq = (ZDOSecurityGetConfigReq_t *) commandBuffer->commandFrame.payload;

  /* we assume we get pan id conflict report as first TLV ID
    Currently only one tlvId - PAN_ID_CONFLICT_REPORT Allowed in first Index, 
    Modification required in future if more TLV ids are used */
  if(rGetConfigReq->tlvIds[0U] == PAN_ID_CONFLICT_REPORT)
  {
    zdpReq->ZDO_ZdpResp              = zdpSecurityGetConfigResponse;
    zdpReq->reqCluster               = SECURITY_GET_CONFIG_CLID; 
    zdpReq->dstAddrMode              = APS_SHORT_ADDRESS; 
    zdpReq->dstAddress.shortAddress  = rGetConfigReq->dstAddr;
    zdpReq->asduPayloadLength = (rGetConfigReq->tlvCount)+1;
    getConfigReq->tlvCount = rGetConfigReq->tlvCount;
    getConfigReq->tlvIds[0U] = PAN_ID_CONFLICT_REPORT;
    ZDO_ZdpReq(zdpReq);
  }
  else
  {
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    uint8_t NotSupported = ZDO_NOT_SUPPORTED_STATUS;
    ZDO_SecurityGetConfigResp_t *rResp = (ZDO_SecurityGetConfigResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_SECURITY_GET_CONFIG_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZDO_SecurityGetConfigResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &NotSupported, sizeof(uint8_t));
    serialManager.write(confBuffer);
  }
}

/**************************************************************************//**
\brief Security Start Key Update response callback
\param[in] resp - response payload
********************************************************************************************/
void rZdoSecStartKeyUpdateResp(ZDO_ZdpResp_t *resp)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZDO_SecurityStartKeyUpdateResp_t *rResp = (ZS_ZDO_SecurityStartKeyUpdateResp_t *)confBuffer->commandFrame.payload;
  
  confBuffer->commandFrame.commandId = R_ZDO_SECURITY_START_KEY_UPDATE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZDO_SecurityStartKeyUpdateResp_t);
  SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.secStartKeyUpdateResp.status, sizeof(uint8_t));
  SYS_BYTE_MEMCPY(&rResp->seqNum, &resp->respPayload.seqNum, sizeof(uint8_t));
  serialManager.write(confBuffer);
  rFreeMem(resp);
}

/**************************************************************************//**
\zappsi serialization API Check Sends the Security Service Start Key Update Request

\param[in] relayCmd         - relay command flag;
\param[in] unAuthDevExtAdd  - Extended Address of Device to Authorise;
\param[in] addressMode      - Destination node address Mode;
\param[in] destAddr         - short address of destination node;
******************************************************************************/
void rZdoSecurityStartKeyUpdateReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *nextTlvPointer = NULL;

  ZS_ZDO_SecurityStartKeyUpdateReq_t *rReq = (ZS_ZDO_SecurityStartKeyUpdateReq_t *)commandBuffer->commandFrame.payload;
  ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  uint8_t *pReqData = &zdpReq->req.reqPayload.asduBuffer[0];

  FragmentationParametersTlv_t fragmentationTlv;
  SelectedKeyNegotiationMethodTlv_t selectedKeyNegotiationTlv;
  SecurityServiceStartKeyUpdate_t rStartKeyUpdate;

  memcpy(&selectedKeyNegotiationTlv, &(rReq->rSelectedKeyNegotiationTlv), sizeof(SelectedKeyNegotiationMethodTlv_t));
  nextTlvPointer = TLV_Encode(&rStartKeyUpdate.reqData[0], &selectedKeyNegotiationTlv);
  rStartKeyUpdate.dataLen =TOTAL_TLV_SIZE(selectedKeyNegotiationTlv.length);

  memcpy(&fragmentationTlv, &(rReq->rFragmentationTlv), sizeof(FragmentationParametersTlv_t));
  nextTlvPointer = TLV_Encode(nextTlvPointer, &fragmentationTlv);
  rStartKeyUpdate.dataLen += TOTAL_TLV_SIZE(fragmentationTlv.length);

  rStartKeyUpdate.callback = NULL;
  rStartKeyUpdate.relayCmd = rReq->relayCmd;
  rStartKeyUpdate.unAuthDevExtAdd = rReq->unAuthDevExtAdd;	
  rStartKeyUpdate.destAddressMode = rReq->addressMode;

  if(APS_EXT_ADDRESS  == rReq->addressMode)
  {
    memcpy(&rStartKeyUpdate.destAddress.extAddress, &(rReq->dstAddr), sizeof(ExtAddr_t));
  }
  else
  {
    rStartKeyUpdate.destAddress.shortAddress = (ShortAddr_t)(rReq->dstAddr);
  }
  /* Update the ZDP request */
  zdpReq->ZDO_ZdpResp = rZdoSecStartKeyUpdateResp;
  zdpReq->reqCluster  = SECURITY_START_KEY_UPDATE_CLID;
  zdpReq->dstAddrMode = rStartKeyUpdate.destAddressMode;
  zdpReq->dstAddress  = rStartKeyUpdate.destAddress;
  memcpy(pReqData, rStartKeyUpdate.reqData, rStartKeyUpdate.dataLen);
  zdpReq->asduPayloadLength = rStartKeyUpdate.dataLen;
  /* Relay command information */
  zdpReq->service.relayMsgInfo.isRelayCmd = rStartKeyUpdate.relayCmd;
  zdpReq->service.relayMsgInfo.unAuthDevExtAdd = rStartKeyUpdate.unAuthDevExtAdd;
  
  /* Place the Request */
  ZDO_ZdpReq(zdpReq);
}

/**************************************************************************//**
\brief Security Decommissioning response callback
\param[in] resp - Response payload
******************************************************************************/
void rZDOSecurityDecomissioningResponse(ZDO_ZdpResp_t *resp)
{
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZS_ZdoDeviceEUI64TlvListResp_t *rResp = (ZS_ZdoDeviceEUI64TlvListResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_SECURITY_DECOMMISSIONG_CONF;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZdoDeviceEUI64TlvListResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
    serialManager.write(confBuffer);
    rFreeMem(resp);
}

/**************************************************************************//**
\Zappsi - brief Clear All Bindings response callback
\param[in] resp - Response payload
******************************************************************************/
void rZDOClearAllBindingsResponse(ZDO_ZdpResp_t *resp)
{
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZS_ZdoDeviceEUI64TlvListResp_t *rResp = (ZS_ZdoDeviceEUI64TlvListResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_CLEAR_ALL_BINDING_CONF;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZdoDeviceEUI64TlvListResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
    serialManager.write(confBuffer);
    rFreeMem(resp);
}

/*******************************************************************************
\Zappsi - Sends the Security Decommissioning / Clear all binding request

\param[in] clusterId - command cluster id either security decommissioning
           request or clear all binding request
\param[in] dstaddr - nwk Address of Destination node
\param[in] deviceCount - total number of devices that need to decommissioned 
           or binding to be cleared
\param[in] eui64List - pointer to the list of ext address that need to be 
           decommissioned.

\returns None.
*****************************************************************************/
void rZdoDecommissioningOrClrBindingReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  DeviceEUI64ListTlv_t rdeviceEUI64ListTlv;
  ZS_ZdoDeviceEUI64TlvListReq_t *rReq = (ZS_ZdoDeviceEUI64TlvListReq_t *) commandBuffer->commandFrame.payload;

  ExtAddr_t *eui64List = (ExtAddr_t *)&rReq->extAddrList;
  uint16_t clusterId;
  uint8_t *tlvData = (uint8_t *)&zdpReq->req.reqPayload.asduBuffer;
  uint8_t argListIndex = 0U;
  uint8_t tlvListIndex = 0U;
  clusterId = rReq->clusterId;
  switch(clusterId)
  {
    case SECURITY_DECOMMISSIONING_CLID:
    {
      zdpReq->ZDO_ZdpResp = rZDOSecurityDecomissioningResponse;
      break;
    }
    case CLEAR_ALL_BINDINGS_CLID:
    {
      zdpReq->ZDO_ZdpResp = rZDOClearAllBindingsResponse;
      break;
    }
    default:
    {
      /*Default case*/
      break;
    }
  }
  zdpReq->dstAddrMode = rReq->dstAddrMode;
  zdpReq->dstAddress.shortAddress  = rReq->dstAddr;
  while(argListIndex < rReq->deviceCount)
  {
    rdeviceEUI64ListTlv.extAddrList[tlvListIndex++] = *(eui64List + argListIndex);
    argListIndex++;
  }
    zdpReq->reqCluster = rReq->clusterId;

  rdeviceEUI64ListTlv.tagId = rReq->tagId;
  rdeviceEUI64ListTlv.extAddrCount = rReq->deviceCount;
  rdeviceEUI64ListTlv.length = rReq->length;

  (void)TLV_Encode(tlvData, &rdeviceEUI64ListTlv);
  zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(rdeviceEUI64ListTlv.length);

  ZDO_ZdpReq(zdpReq);

}

/**************************************************************************//**
\brief Security Get Authentication level response callback
\param[in] resp - Response payload
******************************************************************************/
void rZdoGetAuthenticationLevelResp(ZDO_ZdpResp_t *resp)
{
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZS_ZdoAuthenticationLevelResp_t *rResp = (ZS_ZdoAuthenticationLevelResp_t *)confBuffer->commandFrame.payload;
    
    confBuffer->commandFrame.commandId = R_ZDO_SECURITY_AUTHENTICATION_LEVEL_CONFIRM;
    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZdoAuthenticationLevelResp_t);
    
    SYS_BYTE_MEMCPY(&rResp->status, &resp->respPayload.status, sizeof(uint8_t));
    serialManager.write(confBuffer);
    rFreeMem(resp);
}

/**************************************************************************//**
\brief Security Get Authentication level request function
\param[in] ZS_ZdoAuthenticationLevelReq_t req payload member contains
\Extended Address and TargetIeeeAddrTlv Variable as member
******************************************************************************/
void rZdoGetAuthenticationLevelReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
    ZDO_ZdpReq_t *zdpReq = (ZDO_ZdpReq_t *) rGetMem();
    uint8_t *tlvData = (uint8_t *)&zdpReq->req.reqPayload.asduBuffer;
    TargetIeeeAddrTlv_t apsSecurityLevelTlv = {0U};
    ZS_ZdoAuthenticationLevelReq_t *rReq = (ZS_ZdoAuthenticationLevelReq_t *)commandBuffer->commandFrame.payload;


    zdpReq->reqCluster  = SECURITY_GET_AUTHENTICATION_LEVEL_CLID;
    zdpReq->ZDO_ZdpResp  = rZdoGetAuthenticationLevelResp;
    zdpReq->dstAddrMode = APS_EXT_ADDRESS;
    // zdpReq->dstAddress.shortAddress = 0x00;
    
    memcpy(zdpReq->dstAddress.extAddress, &rReq->destAddr, sizeof(ExtAddr_t));

    apsSecurityLevelTlv.tagId = LOCAL_TLV_TAG_ID;
    apsSecurityLevelTlv.length = CALC_TLV_LENGTH_VALUE((sizeof(TargetIeeeAddrTlv_t) - (SIZE_OF_TAG + SIZE_OF_LENGTH)));
    /* Ref: R23 Spec Section 2.4.3.4.3.3 */
//    memcpy(&apsSecurityLevelTlv.targetDeviceEUI64, MAC_GetExtAddr(), sizeof(ExtAddr_t));
    memcpy(&apsSecurityLevelTlv.targetDeviceEUI64, &rReq->apsSecurityLevelTlv.targetDeviceEUI64, sizeof(ExtAddr_t));

    (void)TLV_Encode(tlvData, &apsSecurityLevelTlv);
    zdpReq->asduPayloadLength = TOTAL_TLV_SIZE(apsSecurityLevelTlv.length);

    ZDO_ZdpReq(zdpReq);
}
#endif

void rZdoMgmtNwkUpdateNotifyProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_MgmtNwkUpdateNotf_t *req = (ZDO_MgmtNwkUpdateNotf_t *) commandBuffer->commandFrame.payload;
  //ZS_MgmtNwkUpdateNotf_t *confirm = NULL; // = (RZdoMgmtNwkUpdateNotify_t *) confirmBuffer->commandFrame.payload;
  ZS_MgmtNwkUpdateNotf_t *confirm = (ZS_MgmtNwkUpdateNotf_t *) confirmBuffer->commandFrame.payload;
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(confirm->status);
  confirm->status = req->status;

  switch (req->status)
  {
    case ZDO_SUCCESS_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(EDScan_t);
      confirm->scanResult = req->scanResult;
    }
    break;

    case ZDO_CHILD_JOINED_STATUS:
    case ZDO_NO_KEY_PAIR_DESCRIPTOR_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->childInfo);
      confirm->childInfo = req->childInfo;
    }
    break;

    case ZDO_CHILD_REMOVED_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->childAddr);
      confirm->childAddr = req->childAddr;
    }
    break;

    case ZDO_NWK_UPDATE_STATUS:
    case ZDO_NETWORK_STARTED_STATUS:
    case ZDO_NETWORK_LOST_STATUS:
    case ZDO_NETWORK_LEFT_STATUS:
    {
      if (ZDO_NETWORK_LEFT_STATUS == req->status)
      {
        ExtPanId_t extPanId;
        CS_ReadParameter(CS_NWK_EXT_PANID_ID,&extPanId);
        CS_WriteParameter(CS_EXT_PANID_ID, &extPanId);
      }
      confirmBuffer->commandFrame.length += sizeof(confirm->nwkUpdateInf);
      confirm->nwkUpdateInf = req->nwkUpdateInf;
    }
    break;

    case ZDO_USER_DESCRIPTOR_UPDATE_STATUS:
    case ZDO_TC_NOT_AVAILABLE_STATUS:
    case ZDO_INVALID_REQUEST_STATUS:
      // No additional parameters
    break;

    case ZDO_STATIC_ADDRESS_CONFLICT_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->conflictAddress);
      confirm->conflictAddress = req->conflictAddress;
    }
    break;

    case ZDO_UPDATE_LINK_KEY_STATUS:
    case ZDO_UPDATE_MASTER_KEY_STATUS:
    case ZDO_DELETE_KEY_PAIR_STATUS:
    case ZDO_DELETE_LINK_KEY_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->deviceExtAddr);
      confirm->deviceExtAddr = req->deviceExtAddr;
    }
    break;

    default:
      confirmBuffer->commandFrame.length = 0;
      rAssert(false, R_DBG_USART_NO_BUFFERS);
    break;
  }
  confirmBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_UPDATE_NOTIFY;

  serialManager.write(confirmBuffer);
}

static void rZdoNwkAddrConfirm(ZDO_ZdpResp_t *conf)
{
  ZDO_NwkAddrResp_t *zdpConf = (ZDO_NwkAddrResp_t *) & conf->respPayload.nwkAddrResp;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoNwkAddrConf_t *rConf = (ZS_ZdoNwkAddrConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_NWK_ADDR_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
    + sizeof (ZS_ZdoNwkAddrConf_t)
    - sizeof(ShortAddr_t) * (ZDP_ADDR_LIST_SIZE - zdpConf->numAssocDev);

  memcpy(&rConf->status, &conf->respPayload.status, sizeof(uint8_t));
  //rConf->status = conf->respPayload.status;
  rConf->resp = *zdpConf;

  if (APP_MAX_COMMAND_PAYLOAD_SIZE >= (confBuffer->commandFrame.length - R_COMMAND_ID_SIZE))
    serialManager.write(confBuffer);
  else
    //Error1 (maximum command payload size is reached)
    confBuffer->state = R_BUFFER_FREE_STATE;

  rFreeMem(conf);
}

void rZdoNwkAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = rGetMem();
  ZDO_NwkAddrReq_t *zdpReq = &zdpClientReq->req.reqPayload.nwkAddrReq;
  ZS_ZdoNwkAddrReq_t *rReq = (ZS_ZdoNwkAddrReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdoNwkAddrConfirm;

  zdpClientReq->reqCluster = NWK_ADDR_CLID;

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoPermitJoiningResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoMgmtPermitJoiningConf_t *rConf = (ZS_ZdoMgmtPermitJoiningConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_MGMT_PERMIT_JOINING_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoMgmtPermitJoiningConf_t);

  SYS_BYTE_MEMCPY(&rConf->status, &conf->respPayload.status, sizeof (uint8_t));
  serialManager.write(confBuffer);

  rFreeMem(conf);
}

void rZdoMgmtPermitJoiningRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtPermitJoiningReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtPermitJoiningReq;
  ZS_ZdoMgmtPermitJoiningReq_t *rReq = (ZS_ZdoMgmtPermitJoiningReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoPermitJoiningResponse;
  zdpClientReq->reqCluster = MGMT_PERMIT_JOINING_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstShortAddress;

  SYS_BYTE_MEMCPY(&zdpReq->permitDuration, &rReq->permitDuration, sizeof (uint8_t));
  SYS_BYTE_MEMCPY(&zdpReq->tcSignificance, &rReq->tcSignificance, sizeof (uint8_t));

  
#ifdef _ZIGBEE_REV_23_SUPPORT_
/* Beacon appendix encapsulation is added only if the device is R23 supported Trsut centre*/
#ifdef _TRUST_CENTRE_  
  if (APS_CENTRALIZED_TRUST_CENTER == APS_GetOwnTcMode())
  {
    uint8_t *tlvData = NULL;
    uint8_t *tlvList[BEACON_APPENDIX_ENC_TLV_COUNT];
    EncapsulationTlv_t encTlv;
    KeyNegotiationTlv_t keyNegotiationTlv;
    FragmentationParametersTlv_t fragmentationTlv;
  
    zdpClientReq->asduPayloadLength = sizeof(ZDO_MgmtPermitJoiningReq_t);
    
    /* Key Negotiation TLV */
    keyNegotiationTlv.tagId  = SUPPORTED_KEY_NEGOTIATION;
    keyNegotiationTlv.length = CALC_TLV_LENGTH_VALUE(SUPPORTED_KEY_NEGOTIATION_METHODS_GLOBAL_TLV_DEFAULT_LENGTH);
    CS_ReadParameter(CS_SUPPORTED_KEY_NEGOTIATION_PROTOCOL_ID, &keyNegotiationTlv.keyNegotiationProtocolBitmask);
    CS_ReadParameter(CS_SUPPORTED_PRE_SHARED_SECRETS_ID, &keyNegotiationTlv.preSharedSecretBitmask);
    memcpy(&keyNegotiationTlv.sourceDeviceEUI64, MAC_GetExtAddr(), sizeof(ExtAddr_t));

    /* Fragmentation TLV */
    fragmentationTlv.tagId  = FRAGMENTATION_PARAMETER;
    fragmentationTlv.length = CALC_TLV_LENGTH_VALUE(FRAGMENTATION_PARAMETERS_GLOBAL_TLV_DEFAULT_LENGTH);
    fragmentationTlv.nodeId = NWK_GetShortAddr();
    CS_ReadParameter(CS_APS_DATA_FRAGMENTATION_ID, &fragmentationTlv.fragmentationOption);
    CS_ReadParameter(CS_APS_MAX_SIZE_ASDU_ID, &fragmentationTlv.incomingTransferUnits);
  
    /* Prepare Encapsulation TLV */
    tlvList[0U] = (uint8_t *)(&keyNegotiationTlv);
    tlvList[1U] = (uint8_t *)(&fragmentationTlv);
    TLV_Encapsulate((void *)&tlvList, 2U, BEACON_APPENDIX_ENCAPSULATION, &encTlv);
  
    tlvData = ((uint8_t*)zdpReq) + sizeof(ZDO_MgmtPermitJoiningReq_t);
    zdpClientReq->asduPayloadLength += TOTAL_TLV_SIZE(encTlv.length);

    TLV_Encode(tlvData, &encTlv);
  }
#endif //_TRUST_CENTRE_
#endif //_ZIGBEE_REV_23_SUPPORT_
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoSetTxPowerConfirm(ZDO_SetTxPowerConf_t *conf)
{
  ZS_CommandBuffer_t *dataBuffer = bufferAllocator.allocate();

  ZS_ZdoSetTxPowerConf_t *payload = (ZS_ZdoSetTxPowerConf_t *) dataBuffer->commandFrame.payload;

  dataBuffer->commandFrame.commandId = R_ZDO_SET_TX_POWER_CONFIRM;

  payload->status = conf->status;

  serialManager.write(dataBuffer);
  rFreeMem(conf);
  dataBuffer->state = R_BUFFER_FREE_STATE;
}

void rZdoSetTxPowerRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_SetTxPowerReq_t *setReq = (ZDO_SetTxPowerReq_t *) rGetMem();
  ZS_ZdoSetTxPowerReq_t *req = (ZS_ZdoSetTxPowerReq_t *) commandBuffer->commandFrame.payload;

  setReq->txPower = req->txPower;
  setReq->ZDO_SetTxPowerConf = rZdoSetTxPowerConfirm;

  ZDO_SetTxPowerReq(setReq);
}

void rZdoWakeupIndicationProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE;
  confirmBuffer->commandFrame.commandId = R_ZDO_WAKEUP_INDICATION;
  serialManager.write(confirmBuffer);
}

static void rZdoSleepConfirm(ZDO_SleepConf_t *conf)
{
  uint8_t status;

  status = (uint8_t) (conf->status);
  uint32_t sleepPeriod;

  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_ZdoSleepConf_t *confirm = (ZS_ZdoSleepConf_t *) confirmBuffer->commandFrame.payload;

  CS_ReadParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoSleepConf_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_SLEEP_CONFIRM;
  confirm->sleepPeriod = sleepPeriod;
  confirm->status = status;

  serialManager.write(confirmBuffer);
  rFreeMem(conf);
}

void rZdoSleepRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_ZdoSleepReq_t const *zsZdoSleepReq = (ZS_ZdoSleepReq_t*) commandBuffer->commandFrame.payload;
  uint32_t leSleepPeriod;
  uint32_t sleepPeriod;
  DeviceType_t deviceType;

  ZDO_SleepReq_t *sleepReq = (ZDO_SleepReq_t *) rGetMem();
  leSleepPeriod = zsZdoSleepReq->sleepPeriod;
  sleepPeriod = LE32_TO_CPU(leSleepPeriod);

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);
  if (DEVICE_TYPE_END_DEVICE == deviceType)
  {
    CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
  }
  else
  {
    CS_WriteParameter(CS_FFD_SLEEP_PERIOD_ID, &sleepPeriod);
  }

  sleepReq->ZDO_SleepConf = rZdoSleepConfirm;

  ZDO_SleepReq(sleepReq);

}

#ifdef _ENDDEVICE_
void rZdoStartSyncReqProcess(ZS_CommandBuffer_t *commandBuffer)
{


  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_Status_t status = ZDO_StartSyncReq();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_START_SYNC_CONFIRM;
  *(uint8_t *) (confirmBuffer->commandFrame.payload) = (uint8_t) status;

  serialManager.write(confirmBuffer);
}

void rZdoStopSyncReqProcess(ZS_CommandBuffer_t *commandBuffer)
{


  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_Status_t status = ZDO_StopSyncReq();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_STOP_SYNC_CONFIRM;
  *(uint8_t *) (confirmBuffer->commandFrame.payload) = (uint8_t) status;

  serialManager.write(confirmBuffer);
}

#endif /* _ENDDEVICE_ */
#if APP_ZDP_REQUESTS
#if APP_EXTENDED_ZDP_REQUEST == 1
static void rZdoNodeDescResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoNodeDescConf_t *rConf = (ZS_ZdoNodeDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_NodeDescResp_t *zdpRsp = &conf->respPayload.nodeDescResp;

  confBuffer->commandFrame.commandId = R_ZDO_NODE_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoNodeDescConf_t);

  //rConf->deviceAddress = 0xffffffffffffffffLL;  //FIXME!!! Workaround

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpRsp;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoNodeDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_NodeDescReq_t *zdpReq = &zdpClientReq->req.reqPayload.nodeDescReq;
  ZS_ZdoNodeDescReq_t *rReq = (ZS_ZdoNodeDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoNodeDescResponse;
  zdpClientReq->reqCluster = NODE_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->destAddr;

  zdpReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  zdpClientReq->asduPayloadLength = 2U;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpPowerDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpPowerDescConf_t *rConf = (ZS_ZdpPowerDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_PowerDescResp_t *zdpResp = &conf->respPayload.powerDescResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_POWER_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpPowerDescConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpPowerDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_PowerDescReq_t *powerDescReq = &zdpClientReq->req.reqPayload.powerDescReq;
  ZS_ZdpPowerDescReq_t *rReq = (ZS_ZdpPowerDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpPowerDescConfirm;
  zdpClientReq->reqCluster = POWER_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  powerDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpSimpleDescConfirm(ZDO_ZdpResp_t *conf)
{
  uint8_t i;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZdpSimpleDescConfirm_t *rConf = (RZdpSimpleDescConfirm_t *) confBuffer->commandFrame.payload;
  ZDO_SimpleDescResp_t *zdpResp = &conf->respPayload.simpleDescResp;
  RZdpClustersList_t *clusterList = (RZdpClustersList_t *)GET_FIELD_PTR(rConf, RZdpSimpleDescConfirm_t, simpleDescriptor.clusterLists);

  rConf->status = conf->respPayload.status;
  rConf->nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  rConf->length = zdpResp->length;

  rConf->simpleDescriptor.endpoint = zdpResp->simpleDescriptor.endpoint;
  rConf->simpleDescriptor.appProfileId = zdpResp->simpleDescriptor.AppProfileId;
  rConf->simpleDescriptor.appDeviceId = zdpResp->simpleDescriptor.AppDeviceId;
  rConf->simpleDescriptor.appDeviceVersion = zdpResp->simpleDescriptor.AppDeviceVersion;
  rConf->simpleDescriptor.reserved = zdpResp->simpleDescriptor.Reserved;

  clusterList->count = zdpResp->simpleDescriptor.AppInClustersCount;

  for (i = 0; i < zdpResp->simpleDescriptor.AppInClustersCount; i++)
  {
    clusterList->pIDs[i] = zdpResp->simpleDescriptor.AppInClustersList[i];
  }

  clusterList = (RZdpClustersList_t *)(GET_FIELD_PTR(rConf, RZdpSimpleDescConfirm_t, simpleDescriptor.clusterLists) +
                                       sizeof(RZdpClustersList_t) +
                                       sizeof(uint16_t) * zdpResp->simpleDescriptor.AppInClustersCount);

  clusterList->count = zdpResp->simpleDescriptor.AppOutClustersCount;

  for (i = 0; i < zdpResp->simpleDescriptor.AppOutClustersCount; i++)
  {
    clusterList->pIDs[i] = zdpResp->simpleDescriptor.AppOutClustersList[i];
  }

  confBuffer->commandFrame.commandId = R_ZDO_SIMPLE_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t) + sizeof(ZDO_SimpleDescResp_t);//status

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_SimpleDescReq_t *simpleDescReq = &zdpClientReq->req.reqPayload.simpleDescReq;
  ZS_ZdpSimpleDescReq_t *rReq = (ZS_ZdpSimpleDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpSimpleDescConfirm;
  zdpClientReq->reqCluster = SIMPLE_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

  simpleDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
  simpleDescReq->endpoint = rReq->endpoint;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpActiveEPConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpActiveEPConf_t *rConf = (ZS_ZdpActiveEPConf_t *) confBuffer->commandFrame.payload;
  ZDO_ActiveEPResp_t *zdpResp = &conf->respPayload.activeEPResp;

  rConf->status = conf->respPayload.status;
  rConf->resp.nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  rConf->resp.activeEPCount = zdpResp->activeEPCount;
  SYS_BYTE_MEMCPY(&rConf->resp.activeEPList, &zdpResp->activeEPList, sizeof (uint8_t) * zdpResp->activeEPCount);
  confBuffer->commandFrame.commandId = R_ZDO_ACTIVE_EP_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
    + offsetof (ZS_ZdpActiveEPConf_t, resp.activeEPList)
    + zdpResp->activeEPCount;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpActiveEPReq_t *const activeEPReq = (ZS_ZdpActiveEPReq_t *)(commandBuffer->commandFrame.payload);

  zdpClientReq->req.reqPayload.activeEPReq.nwkAddrOfInterest = activeEPReq->nwkAddrOfInterest;
  zdpClientReq->ZDO_ZdpResp = rZdpActiveEPConfirm;
  zdpClientReq->reqCluster = ACTIVE_ENDPOINTS_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
//  zdpClientReq->dstAddress.shortAddress = activeEPReq->nwkAddrOfInterest;
  zdpClientReq->dstAddress.shortAddress =  activeEPReq->dstAddr;

  ZDO_ZdpReq(zdpClientReq);
}

void rZdpComplexDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp.nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  confBuffer->commandFrame.commandId = R_ZDO_COMPLEX_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpComplexDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpComplexDescConfirm;
  zdpClientReq->reqCluster = COMPLEX_DESCRIPTOR_CLID;
  unsupportedCommandReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}
#ifdef _PARENT_ANNCE_  
void rZdpParentAnnceConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpParentAnnceResp_t *rConf = (ZS_ZdpParentAnnceResp_t *) confBuffer->commandFrame.payload;

  rConf->req.numChilds = conf->respPayload.parentAnnce.numChilds;
  for(uint8_t i = 0; i < rConf->req.numChilds; i++)
    rConf->req.childInfo[i] = conf->respPayload.parentAnnce.childInfo[i];
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_PARENT_ANNOUNCE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZdpParentAnnceResp_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpParentAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_ParentAnnceReq_t *parentAnnceReq = &zdpClientReq->req.reqPayload.parentAnnce;
  ZS_ZdpParentAnnceReq_t *rReq = (ZS_ZdpParentAnnceReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpParentAnnceConfirm;
  zdpClientReq->reqCluster = PARENT_ANNCE_CLID;
  parentAnnceReq->numChilds = rReq->req.numChilds;
  for(uint8_t i = 0; i < rReq->req.numChilds; i++)
    parentAnnceReq->childInfo[i] = rReq->req.childInfo[i];

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}
#endif // #ifdef _PARENT_ANNCE_  
static void rZdpUserDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

#ifdef _ZIGBEE_REV_23_SUPPORT_
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
#else
  ZS_ZdpUserDescConf_t *rConf = (ZS_ZdpUserDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_UserDescResp_t *zdpResp = &conf->respPayload.userDescResp;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUserDescConf_t);
#endif

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_USER_DESC_CONFIRM;
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUserDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();

#ifdef _ZIGBEE_REV_23_SUPPORT_
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  unsupportedCommandReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
#else
  ZDO_UserDescReq_t *userDescReq = &zdpClientReq->req.reqPayload.userDescReq;
  ZS_ZdpUserDescReq_t *rReq = (ZS_ZdpUserDescReq_t *) commandBuffer->commandFrame.payload;
  userDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
#endif

  zdpClientReq->ZDO_ZdpResp = rZdpUserDescConfirm;
  zdpClientReq->reqCluster = USER_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpEndDeviceAnnceConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpEndDeviceConf_t *rConf = (ZS_ZdpEndDeviceConf_t *) confBuffer->commandFrame.payload;
  ZDO_ZdpReq_t *zdpClientReq = GET_STRUCT_BY_FIELD_POINTER(ZDO_ZdpReq_t, resp, conf);
  ZDO_DeviceAnnceReq_t *deviceAnnceReq = &zdpClientReq->req.reqPayload.deviceAnnce;

  confBuffer->commandFrame.commandId = R_ZDO_END_DEVICE_ANNCE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpEndDeviceConf_t);

  rConf->status = conf->respPayload.status;
  rConf->resp = *deviceAnnceReq;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpEndDeviceAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_DeviceAnnceReq_t *deviceAnnceReq = &zdpClientReq->req.reqPayload.deviceAnnce;
  ZS_ZdpEnDeviceAnnceReq_t *rReq = (ZS_ZdpEnDeviceAnnceReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpEndDeviceAnnceConfirm;
  zdpClientReq->reqCluster = DEVICE_ANNCE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = BROADCAST_ADDR_ALL;

  *deviceAnnceReq = *rReq;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpLqiConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpLqiConf_t *rConf = (ZS_ZdpLqiConf_t *) confBuffer->commandFrame.payload;
  ZDO_MgmtLqiResp_t *zdpResp = &conf->respPayload.mgmtLqiResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_LQI_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpLqiConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

static void rZdpRtgConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpRtgConf_t *rConf = (ZS_ZdpRtgConf_t *) confBuffer->commandFrame.payload;
  ZDO_MgmtRtgResp_t *zdpResp = &conf->respPayload.mgmtRtgResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_RTG_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpRtgConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpLqiRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtLqiReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtLqiReq;
  ZS_ZdpLqiReq_t *rReq = (ZS_ZdpLqiReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpLqiConfirm;
  zdpClientReq->reqCluster = MGMT_LQI_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

void rZdpRtgRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtRtgReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtRtgReq;
  ZS_ZdpRtgReq_t *rReq = (ZS_ZdpRtgReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpRtgConfirm;
  zdpClientReq->reqCluster = MGMT_RTG_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpUserDescSetConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

#ifdef _ZIGBEE_REV_23_SUPPORT_
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
#else
  ZS_ZdpUserDescSetConf_t *rConf = (ZS_ZdpUserDescSetConf_t *) confBuffer->commandFrame.payload;
  ZDO_UserDescConfResp_t *zdpResp = &conf->respPayload.userDescConfResp;
  rConf->nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUserDescSetConf_t);
#endif

  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_USER_DESC_SET_CONFIRM;
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUserDescSetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();

#ifdef _ZIGBEE_REV_23_SUPPORT_
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
#else
  ZDO_UserDescSetReq_t *zdpReq = &zdpClientReq->req.reqPayload.userDescSetReq;
  ZS_ZdpUserDescSetReq_t *rReq = (ZS_ZdpUserDescSetReq_t *) commandBuffer->commandFrame.payload;
  *zdpReq = *rReq;
#endif

  zdpClientReq->ZDO_ZdpResp = rZdpUserDescSetConfirm;
  zdpClientReq->reqCluster = USER_DESC_CONF_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

#ifdef _ZIGBEE_REV_23_SUPPORT_

static void rZdpDiscoveryCacheConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_DISCOVERY_CACHE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpDiscoveryCacheRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpDiscoveryCacheConfirm;
  zdpClientReq->reqCluster = DISCOVERY_CASH_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpDiscoveryStoreConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_DISCOVERY_STORE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpDiscoveryStoreRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpDiscoveryStoreConfirm;
  zdpClientReq->reqCluster = DISCOVERY_STORE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpNodeDescStoreConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_NODE_DESC_STORE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpNodeDescriptorStoreRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpNodeDescStoreConfirm;
  zdpClientReq->reqCluster = NODE_DESC_STORE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpPowerDescStoreConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_POWER_DESC_STORE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpPowerDescriptorStoreRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpPowerDescStoreConfirm;
  zdpClientReq->reqCluster = POWER_DESC_STORE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpActiveEPStoreConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_ACTIVE_EP_STORE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpActiveEPStoreRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpActiveEPStoreConfirm;
  zdpClientReq->reqCluster = ACTIVE_EP_STORE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpSimpleDescStoreConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_SIMPLE_DESC_STORE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpSimpleDescStoreRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpSimpleDescStoreConfirm;
  zdpClientReq->reqCluster = SIMPLE_DESC_STORE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpRemoveNodeCacheConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_REMOVE_NODE_CACHE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpRemoveNodeCacheRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpRemoveNodeCacheConfirm;
  zdpClientReq->reqCluster = REMOVE_NODE_CACHE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpFindNodeCacheConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_FIND_NODE_CACHE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpFindNodeCacheRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpFindNodeCacheConfirm;
  zdpClientReq->reqCluster = FIND_NODE_CACHE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpExtendedSimpleDescConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_EXTENDED_SIMPLE_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpExtendedSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpExtendedSimpleDescConfirm;
  zdpClientReq->reqCluster = EXTENDED_SIMPLE_DESC_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpExtendedActiveEPConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_EXTENDED_ACTIVE_EP_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpExtendedActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpExtendedActiveEPConfirm;
  zdpClientReq->reqCluster = EXTENDED_ACTIVE_EP_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpMgmtNWKDiscConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_DISC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpMgmtNWKDiscRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpMgmtNWKDiscConfirm;
  zdpClientReq->reqCluster = MGMT_NWK_DISC_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpMgmtDirectJoinConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_DIRECT_JOIN_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpMgmtDirectJoinRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpMgmtDirectJoinConfirm;
  zdpClientReq->reqCluster = MGMT_DIRECT_JOIN_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpMgmtCacheConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDP_MGMT_CACHE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpMgmtCacheRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpMgmtCacheConfirm;
  zdpClientReq->reqCluster = MGMT_CACHE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpReservedClusterConfirm(ZDO_ZdpResp_t *conf) {
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnsupportedCommandConf_t *rConf = (ZS_ZdpUnsupportedCommandConf_t *) confBuffer->commandFrame.payload;
  ZDO_UnsupportedCommandResp_t *zdpResp = &conf->respPayload.unsupportedCommandResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_RESERVED_CLUSTER_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnsupportedCommandConf_t);
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpReservedClusterRequestProcess(ZS_CommandBuffer_t *commandBuffer) {
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UnsupportedCommandReq_t *unsupportedCommandReq = &zdpClientReq->req.reqPayload.unsupportedCommandReq;
  ZS_ZdpUnsupportedCommandReq_t *rReq = (ZS_ZdpUnsupportedCommandReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdpReservedClusterConfirm;
  zdpClientReq->reqCluster = RESERVED_CLUSTER_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  ZDO_ZdpReq(zdpClientReq);
}

#endif /* _ZIGBEE_REV_23_SUPPORT_ */

static void rZdpNwkUpdateConfirm(ZDO_ZdpResp_t *conf)
{
  if (ZDO_SUCCESS_STATUS != conf->respPayload.status)
  {
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZS_MgmtNwkUpdateNotf_t *rConf = (ZS_MgmtNwkUpdateNotf_t *) confBuffer->commandFrame.payload;

    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
    confBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_UPDATE_CONFIRM;
    rConf->status = conf->respPayload.status;
    serialManager.write(confBuffer);
  }
  rFreeMem(conf);
}

void rZdoNwkUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtNwkUpdateReq_t *nwkUpdateReq = &zdpClientReq->req.reqPayload.mgmtNwkUpdateReq;
  ZS_ZdpNwkUpdateReq_t *rReq = (ZS_ZdpNwkUpdateReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpNwkUpdateConfirm;
  zdpClientReq->reqCluster = MGMT_NWK_UPDATE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddr;

  *nwkUpdateReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpSystemServerDiscoveryConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpSystemServerDiscoveryConf_t *rConf = (ZS_ZdpSystemServerDiscoveryConf_t *) confBuffer->commandFrame.payload;
  ZDO_SystemServerDiscoveryResp_t *zdpRsp = &conf->respPayload.systemServerDiscoveryResp;

  confBuffer->commandFrame.commandId = R_ZDP_SYSTEM_DISCOVERY_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpSystemServerDiscoveryConf_t);

  rConf->status = conf->respPayload.status;
  rConf->serverMask = zdpRsp->serverMask;
  serialManager.write(confBuffer);

  rFreeMem(conf);
}

void rZdpSystemServerDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_SystemServerDiscoveryReq_t *zdpReq = &zdpClientReq->req.reqPayload.systemServerDiscoveryReq;
  ZS_ZdpSystemServerDiscoveryReq_t *rReq = (ZS_ZdpSystemServerDiscoveryReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpSystemServerDiscoveryConfirm;
  zdpClientReq->reqCluster = SYSTEM_SERVER_DISCOVERY_CLID;

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = BROADCAST_ADDR_RX_ON_WHEN_IDLE;

  zdpReq->serverMask = rReq->serverMask;

  ZDO_ZdpReq(zdpClientReq);
}

#else // #if APP_EXTENDED_ZDP_REQUEST == 1
void rZdoNodeDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpPowerDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

#ifdef _PARENT_ANNCE_  
void rZdpParentAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}
#endif

void rZdpEndDeviceAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpLqiRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpRtgRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdoNwkUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpSystemServerDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}
#endif // #if APP_EXTENDED_ZDP_REQUEST == 1

static void rZdoIeeeAddrConfirm(ZDO_ZdpResp_t *conf)
{
  ZDO_IeeeAddrResp_t *zdpConf = (ZDO_IeeeAddrResp_t *) & conf->respPayload.ieeeAddrResp;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoIeeeAddrConf_t *rConf = (ZS_ZdoIeeeAddrConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_IEEE_ADDR_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
      + sizeof (ZS_ZdoIeeeAddrConf_t)
      - sizeof (ShortAddr_t) * (ZDP_ADDR_LIST_SIZE - zdpConf->numAssocDev);

  rConf->status= conf->respPayload.status;
  rConf->resp = *zdpConf;
  if (APP_MAX_COMMAND_PAYLOAD_SIZE >= (confBuffer->commandFrame.length - R_COMMAND_ID_SIZE))
  {
    serialManager.write(confBuffer);
  }
  else
  {
    //Error (maximum command payload size is reached)
    confBuffer->state = R_BUFFER_FREE_STATE;
    rAssert(false, R_DBG_PAYLOAD_TOO_LONG);
  }
  rFreeMem(conf);
}

void rZdoIeeeAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_IeeeAddrReq_t *zdpReq = &zdpClientReq->req.reqPayload.ieeeAddrReq;
  ZS_ZdoIeeeAddrReq_t *rReq = (ZS_ZdoIeeeAddrReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoIeeeAddrConfirm;
  zdpClientReq->reqCluster = IEEE_ADDR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;
  
  *zdpReq = rReq->req;
  ZDO_ZdpReq(zdpClientReq);
}

#ifdef _BINDING_
static void rZdpMatchDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = NULL;
  ZS_ZdpMatchDescConf_t *rConf;
  ZDO_MatchDescResp_t *zdpResp = &conf->respPayload.matchDescResp;

  confBuffer = bufferAllocator.allocate();
  rConf = (ZS_ZdpMatchDescConf_t *) confBuffer->commandFrame.payload;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MATCH_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE +
    offsetof (ZS_ZdpMatchDescConf_t, resp.matchList) +
    zdpResp->matchLength;

  serialManager.write(confBuffer);
  if (ZDO_CMD_COMPLETED_STATUS == conf->respPayload.status)
    rFreeMem(conf);
}

void rZdpMatchDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MatchDescReq_t *matchDescReq = &zdpClientReq->req.reqPayload.matchDescReq;
  ZS_ZdpMatchDescReq_t *rReq = (ZS_ZdpMatchDescReq_t *) commandBuffer->commandFrame.payload;
  uint8_t *ptr = (uint8_t *) rReq;
  uint8_t i;

  if (MAX_REQUESTED_CLUSTER_NUMBER >= rReq->numInClusters)
  {
    zdpClientReq->ZDO_ZdpResp = rZdpMatchDescConfirm;
    zdpClientReq->reqCluster = MATCH_DESCRIPTOR_CLID;
    zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
    zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

    matchDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
    matchDescReq->profileId = rReq->profileId;
    matchDescReq->numInClusters = rReq->numInClusters;
    for (i = 0; i < rReq->numInClusters; i++)
      matchDescReq->inClusterList[i] = rReq->inClusterList[i];

    ptr += sizeof (uint16_t) * matchDescReq->numInClusters +
      offsetof(ZS_ZdpMatchDescReq_t, inClusterList);
    matchDescReq->numOutClusters = *ptr;
    ptr++;

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(matchDescReq,
                                  ZDO_MatchDescReq_t,
                                  outClusterList),
                    ptr,
                    sizeof (uint16_t) * matchDescReq->numOutClusters);
    ZDO_ZdpReq(zdpClientReq);
  }
  else
  {
    rFreeMem(zdpClientReq);
  }
}

static void rZdoBindConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpBindConf_t *rConf;

  rConf = (ZS_ZdpBindConf_t *) confBuffer->commandFrame.payload;
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_BIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpBindConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpBindReq_t *rReq = (ZS_ZdpBindReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->reqCluster = rReq->reqCluster;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    zdpClientReq->dstAddrMode = APS_EXT_ADDRESS;
    ExtAddr_t tempDstAddr;
    COPY_EXT_ADDR(tempDstAddr,rReq->targetExtAddr);
    COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  }
  else
  {
    zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
    zdpClientReq->dstAddress.shortAddress = rReq->targetNwkAddr;
  }

  memcpy(&zdpClientReq->req.reqPayload.bindReq,
    &rReq->payload, sizeof(zdpClientReq->req.reqPayload.bindReq));

  zdpClientReq->ZDO_ZdpResp = rZdoBindConfirm;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoUnbindConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnbindConf_t *rConf;

  rConf = (ZS_ZdpUnbindConf_t *) confBuffer->commandFrame.payload;
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_UNBIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnbindConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUnbindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpUnbindReq_t *rReq = (ZS_ZdpUnbindReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->reqCluster = rReq->reqCluster;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    ExtAddr_t tempDstAddr;
    COPY_EXT_ADDR(tempDstAddr,rReq->targetExtAddr);
    COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  }
  else
    zdpClientReq->dstAddress.shortAddress = rReq->targetNwkAddr;

  memcpy(&zdpClientReq->req.reqPayload.unbindReq,
    &rReq->payload, sizeof(zdpClientReq->req.reqPayload.unbindReq));

  zdpClientReq->ZDO_ZdpResp = rZdoUnbindConfirm;
  ZDO_ZdpReq(zdpClientReq);
}

#if defined _END_DEVICE_BINDING_
static void rZdoEndDeviceBindResp(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZdpEndDeviceBindingResp_t *rResp;

  rResp = (RZdpEndDeviceBindingResp_t *) confBuffer->commandFrame.payload;
  rResp->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_END_DEVICE_BIND_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZdpEndDeviceBindingResp_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpEndDeviceBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();

  zdpClientReq->ZDO_ZdpResp = rZdoEndDeviceBindResp;
  zdpClientReq->reqCluster = END_DEVICE_BIND_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = 0x0000;

  memcpy(&zdpClientReq->req.reqPayload.endDeviceBindReq,
    commandBuffer->commandFrame.payload,
    commandBuffer->commandFrame.length - R_COMMAND_ID_SIZE);
  ZDO_ZdpReq(zdpClientReq);
}
#endif /* _END_DEVICE_BINDING_ */

static void rZdoMgmtBindResp(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpMgmtBindResp_t *rResp;

  rResp = (ZS_ZdpMgmtBindResp_t *)confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_MGMT_BIND_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(*rResp);

  rResp->srcAddrMode = conf->srcAddrMode;
  if (APS_EXT_ADDRESS ==conf->srcAddrMode)
  {
    ExtAddr_t tempExtAddr;
    COPY_EXT_ADDR_A(&tempExtAddr, conf->srcAddress.extAddress);
    rResp->srcExtAddr = tempExtAddr;
  }
  else
    rResp->srcNwkAddr = conf->srcAddress.shortAddress;
  memcpy(&rResp->payload, &conf->respPayload, sizeof(conf->respPayload));

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpMgmtBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *const zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpMgmtBindReq_t *rReq = (ZS_ZdpMgmtBindReq_t *) commandBuffer->commandFrame.payload;

  zdpReq->reqCluster = MGMT_BIND_CLID;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    ExtAddr_t tempExtAddr;
    tempExtAddr = rReq->targetExtAddr;
    COPY_EXT_ADDR_A(zdpReq->dstAddress.extAddress, &tempExtAddr);
    zdpReq->dstAddrMode = APS_EXT_ADDRESS;
  }
  else
  {
    zdpReq->dstAddress.shortAddress = rReq->targetNwkAddr;
    zdpReq->dstAddrMode = APS_SHORT_ADDRESS;
  }

  memcpy(&zdpReq->req.reqPayload.mgmtBindReq,
    &rReq->payload, sizeof(zdpReq->req.reqPayload.mgmtBindReq));

  zdpReq->ZDO_ZdpResp = rZdoMgmtBindResp;
  ZDO_ZdpReq(zdpReq);
}
#endif /* _BINDING_ */
#endif /* APP_ZDP_REQUESTS */

#if defined _SECURITY_ && defined _LINK_SECURITY_
static void rZdoVerifyKeyConfirmProcess(APS_VerifyKeyConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoVerifyKeyConf_t *rConf = (ZS_ZdoVerifyKeyConf_t *) confBuffer->commandFrame.payload;
  rConf->status = (uint8_t)conf->status;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoVerifyKeyConf_t);
  confBuffer->commandFrame.commandId = R_ZDO_VERIFY_KEY_CONFIRM;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoVerifyKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_VerifiKeyReq_t *const verifyKey = (ZDO_VerifiKeyReq_t *) rGetMem();
  ZS_VerifyKeyReq_t *rReq = (ZS_VerifyKeyReq_t *) commandBuffer->commandFrame.payload;

  verifyKey->timeout = rReq->timeout;
#ifdef _ZIGBEE_REV_23_SUPPORT_
  verifyKey->keyType = rReq->keyType;
  verifyKey->relayCmd = rReq->relayCmd;
#endif
  verifyKey->verifyKeyConf = rZdoVerifyKeyConfirmProcess;
  ZDO_VerifyKeyReq(verifyKey);
}

#endif //#if defined _SECURITY_ && defined _LINK_SECURITY_

#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
static void zdoReqCmdRxdHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZdoZdpReqTestData_t *zdoTestData = (ZdoZdpReqTestData_t *)data;
  ClusterId_t cluster = zdoTestData->apsInd->clusterId;

  if ((cluster <= USER_DESCRIPTOR_CLID) || 
#ifdef _PARENT_ANNCE_      
      (cluster == PARENT_ANNCE_CLID) || 
#endif        
      ((cluster >= MGMT_LQI_CLID) && (cluster <= MGMT_LEAVE_CLID)) || 
        (cluster == MGMT_NWK_UPDATE_CLID) || (cluster == MGMT_PERMIT_JOINING_CLID) || 
        (cluster == BIND_CLID) || (cluster == UNBIND_CLID))
  {
    zdoTestData->internalHandlingDenied = true;
    ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);
  
    memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
    confirmBuffer->commandFrame.commandId = R_ZDO_REQ_FRAME_RECEIVED;
    memset(confirmBuffer->commandFrame.payload, 0x00, sizeof(uint8_t));
    serialManager.write(confirmBuffer);
  }
}

static void zdoReqCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);

  confirmBuffer->commandFrame.commandId = R_ZDO_REQ_FRAME_VALIDATED;
  memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
  serialManager.write(confirmBuffer);
}

static void zdoRspCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_RSP_FRAME_VALIDATED;
  memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
  serialManager.write(confirmBuffer);
}
#endif // _STACK_INTERNAL_TEST_FRAMEWORK_
/* eof rZdo.c */
