/*******************************************************************************
  IAS-Zone Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   iasACEZoneCluster.c

  Summary:
    This file contains the IAS-Zone Cluster interface.

  Description:
    This file contains the IAS-Zone Cluster interface.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_IAS_ACE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/ias_ace/include/iasACEZoneCluster.h>
#include <z3device/common/include/appConsts.h>
#if APP_ENABLE_CONSOLE == 1
#include <app_zigbee/zigbee_console/console.h>
#endif
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/ias_ace/include/iasACECluster.h>
#include <zcl/include/zclIasZoneCluster.h>
#include <zcl/include/zclIasACECluster.h>
#include <zcl/include/zclZllBasicCluster.h>
#include <zcl/include/zclZllIdentifyCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclCommandManager.h>
#include <zcl/include/zclAttributes.h>
#include <pds/include/wlPdsMemIds.h>
#include <app_zigbee/app_zigbee_handler.h>
/*******************************************************************************
                             Types section
*******************************************************************************/
typedef struct PACK
{
  uint16_t zoneStatus;
  uint8_t  extendedStatus;
} zoneStatusChangeNot_t;

typedef struct PACK
{
  uint16_t zoneType;
  uint16_t manufacturerCode;
} zoneEnrollReq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t zoneEnrollResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneEnrollResCommand_t * payload);
static void iasZoneFillZoneZoneEnrollRequest(ZCL_ZoneEnrollRequest_t *payload, uint16_t zoneType, uint16_t manufCode);
static void zoneStatusChangeNotificationCommandCallback();
static void iasACEAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static ZCL_Status_t zoneInitiateNormalOperatingModeInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t zoneInitiateTestModeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZoneInitiateTestMode_t * payload);
static void zoneChangeNotiCmdTimerFired(void);
static void zoneTestModeOperationTimerFired(void);
static void zoneClusterEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
static bool zoneCieAddressFiltering(ZCL_Addressing_t *addressing);

static uint8_t currentZoneSensitivityLevelValue = DEFAULT_VAL;
/******************************************************************************
                    Global variables
******************************************************************************/
static HAL_AppTimer_t zoneChangeNotiCmdTimer;
static HAL_AppTimer_t zoneTestModeOperationTimer;

//IAS Zone Server Attributes
ZCL_IasZoneClusterServerAttributes_t iasACEZoneClusterServerAttributes =
{
  ZCL_DEFINE_IAS_ZONE_CLUSTER_SERVER_ATTRIBUTES()
};

//IAS Zone Server Commands
PROGMEM_DECLARE (ZCL_IasZoneClusterCommands_t iasACEZoneClusterServerCommands) =
{
  ZCL_DEFINE_IAS_ZONE_CLUSTER_COMMANDS(NULL, NULL, zoneEnrollResponseInd, zoneInitiateNormalOperatingModeInd, zoneInitiateTestModeInd)
};

static SYS_EventReceiver_t iasZoneEventReceiver = {.func = zoneClusterEventListener};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
 \brief iasZoneClusterInit
 \param none
 \return none
******************************************************************************/
void iasZoneClusterInit(void)
{
  ZCL_Cluster_t *zoneServercluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IAS_ZONE_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *zoneClientCluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IAS_ZONE_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  if (zoneServercluster)
  {
    zoneServercluster->ZCL_AttributeEventInd = iasACEAttrEventInd;
  }
  if (zoneClientCluster)
  {
    zoneClientCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  }
  
  //Initialization of the list of attributes to their default values of IAS Zones
  <#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CLUSTERREVISION == true) >
  iasACEZoneClusterServerAttributes.clusterVersion.value = ZONE_CLUSTER_VERSION;
  </#if>
  <#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATE == true) >
  iasACEZoneClusterServerAttributes.iaszoneState.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_STATE_ATTRIBUTE_ID_DEFAULT;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONETYPE == true) >
  iasACEZoneClusterServerAttributes.iaszoneType.value = APP_IAS_ZONE_TYPE_ATTRIBUTE_VALUE;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
  iasACEZoneClusterServerAttributes.iaszoneStatus.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_STATUS_ATTRIBUTE_ID_DEFAULT;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_IASCIEADDRESS == true) >
  iasACEZoneClusterServerAttributes.iasCieAddress.value = APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEID == true) >
  iasACEZoneClusterServerAttributes.iasZoneId.value = ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_ID_ATTRIBUTE_ID_DEFAULT;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_NUMOFZONESENSLEVELSUPPORTED == true) >
  iasACEZoneClusterServerAttributes.iasZoneNumberOfZoneSensitivityLevelsSupported.value =ZCL_IAS_ZONE_CLUSTER_SERVER_NUMBEROFZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
  </#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value =ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
  currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
  </#if>
   SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &iasZoneEventReceiver);

  //PDS store for Attributes - IAS Zones
  if (PDS_IsAbleToRestore(APP_IAS_ACE_ZONE_MEM_ID))
    PDS_Restore(APP_IAS_ACE_ZONE_MEM_ID);

<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
  if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) & ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
  {
    zoneChangeNotiCmdTimer.interval = ZONE_NOTI_PERIOD;
    zoneChangeNotiCmdTimer.mode     = TIMER_ONE_SHOT_MODE;
    zoneChangeNotiCmdTimer.callback = zoneChangeNotiCmdTimerFired;
    HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
  }
</#if>
}

/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void zoneClusterEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
   //To take action: Avoid configuring IAS_CIE_ADDRESS when its value is other than default
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;

  if (BC_ZCL_EVENT_ACTION_REQUEST == eventId && ZCL_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
  {
     ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
     if((IAS_ZONE_CLUSTER_ID != zclWriteAttrReq->clusterId) || 
              (ZCL_CLUSTER_SIDE_SERVER != zclWriteAttrReq->clusterSide))
     {
       return;
     }

     switch(zclWriteAttrReq->attrId)
     {
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_IASCIEADDRESS == true) >       
       case ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_IAS_CIE_ADDRESS_ATTRIBUTE_ID:
       {
         uint64_t requestedValue = 0; 
         memcpy(&requestedValue, ((uint64_t*)(zclWriteAttrReq->attrValue)), sizeof(uint64_t));
         actionReq->denied = 0U;
         if(requestedValue == APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE)
         {
           actionReq->denied = 1U;
           ((ZCLActionWriteAttrReq_t *)actionReq->context)->status = ZCL_INVALID_VALUE_STATUS;
         }
         else if(iasACEZoneClusterServerAttributes.iasCieAddress.value != APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE)
         {
           actionReq->denied = 1U;
           ((ZCLActionWriteAttrReq_t *)actionReq->context)->status = ZCL_SUCCESS_STATUS;
         }
       }
         break;
</#if>         

     default:
         break;
      }
    } 
}
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUSCHANGENOTIFICATION == true) >
/**************************************************************************//**
 \brief iasZoneFillZoneStatusChangeNotification
 \param payload - ZOne status change notification payload
 \param zoneStatus  - device /zone statu attribute value
 \param extendedStatus - extended status as part of payload
 \return none
******************************************************************************/
static void iasZoneFillZoneStatusChangeNotification(ZCL_ZoneStatusChangeNot_t *payload, uint16_t zoneStatus, uint8_t extendedStatus)
{
  payload->zoneStatus          = zoneStatus;
  payload->extendedStatus      = extendedStatus;
  payload->zoneId              = iasACEZoneClusterServerAttributes.iasZoneId.value;
  payload->delayTime           = ZONE_NOTI_PERIOD; 
}

/**************************************************************************//**
 \brief iasZoneFillZoneStatusChangeNotification Callback
 \param payload - ZOne status change notification payload
 \return none
******************************************************************************/
static void iasZoneFillZoneStatusChangeNotificationCallback(ZCL_ZoneStatusChangeNot_t *payload)
{
  payload->zoneStatus          = iasACEZoneClusterServerAttributes.iaszoneStatus.value;
  payload->extendedStatus      = EXTENDED_STATE_DEFAULT;
  payload->zoneId              = iasACEZoneClusterServerAttributes.iasZoneId.value;
  payload->delayTime           = ZONE_NOTI_PERIOD; 
}
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEENROLLREQ == true) >
/**************************************************************************//**
 \brief iasZoneFillZoneZoneEnrollRequest
 \param payload - Enroll request payload to be filled
 \param zoneType  - type of the zone
 \param manufCode - manufacturer code
 \return none
******************************************************************************/
static void iasZoneFillZoneZoneEnrollRequest(ZCL_ZoneEnrollRequest_t *payload, uint16_t zoneType, uint16_t manufCode)
{
  payload->zoneType          = zoneType;
  payload->manufacturerCode  = manufCode;
}
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUSCHANGENOTIFICATION == true) >
/**************************************************************************//**
 \brief zoneStatusChangeNotification Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param zoneStatus - status of the zone
 \param extendedStatus - extended status of the zone
 \return none
******************************************************************************/
void zoneStatusChangeNotificationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint16_t zoneStatus, uint8_t extendedStatus)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFY_COMMAND_ID, sizeof(ZCL_ZoneStatusChangeNot_t), srcEp);
  iasZoneFillZoneStatusChangeNotification((ZCL_ZoneStatusChangeNot_t *)req->requestPayload,zoneStatus,extendedStatus);
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}

/**************************************************************************//**
 \brief zoneStatusChangeNotification Command
 \return none
******************************************************************************/
void zoneStatusChangeNotificationCommandCallback()
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_CHANGE_NOTIFY_COMMAND_ID, sizeof(ZCL_ZoneStatusChangeNot_t), APP_ENDPOINT_IAS_ACE);
  iasZoneFillZoneStatusChangeNotificationCallback((ZCL_ZoneStatusChangeNot_t *)req->requestPayload);
  fillDstAddressingServer(&req->dstAddressing, (APS_AddrMode_t)ADRESS_MODE, CIE_ADDR, CIE_ENDPT, IAS_ZONE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEENROLLREQ == true) >
/**************************************************************************//**
 \brief zoneEnrollRequest Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param zoneType -  type of the zone
 \param manufCode  -  manufacturer code
 \return none
******************************************************************************/
void zoneEnrollRequestCommand(APS_AddrMode_t mode, APS_Address_t addr, Endpoint_t ep, Endpoint_t srcEp, uint16_t manufCode)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  //check added to initiate enroll request only when cie Address attribute is configured
  if(iasACEZoneClusterServerAttributes.iasCieAddress.value != APP_IAS_ZONE_CIE_ADDRESS_ATTRIBUTE_VALUE)
  {
    fillCommandRequest(req, ZCL_IAS_ZONE_CLUSTER_ZONE_ENROLL_REQUEST_COMMAND_ID, sizeof(ZCL_ZoneEnrollRequest_t), srcEp);
    iasZoneFillZoneZoneEnrollRequest((ZCL_ZoneEnrollRequest_t *)req->requestPayload,iasACEZoneClusterServerAttributes.iaszoneType.value, manufCode);
    fillDstAddressingServerWithAddrMode(&req->dstAddressing, mode, addr, ep, IAS_ZONE_CLUSTER_ID);
    ZCL_CommandManagerSendCommand(req);
  }
}

/**************************************************************************//**
\brief Fills zcl addressing structure

\param[out] addressing - pointer to the structure to be filled;
\param[in]  mode       - addressing mode;
\param[in]  addr       - short address of destination mode;
\param[in]  ep         - endpoint number of destination node;
\param[in]  cluster    - cluster id
******************************************************************************/
void fillDstAddressingServerWithAddrMode(ZCL_Addressing_t *addressing, APS_AddrMode_t mode, APS_Address_t addr, Endpoint_t ep, ClusterId_t cluster)
{
  addressing->addrMode             = mode;
  memcpy(&addressing->addr, &addr, sizeof(addr));
  addressing->profileId            = PROFILE_ID_HOME_AUTOMATION;
  addressing->endpointId           = ep;
  addressing->clusterId            = cluster;
  addressing->clusterSide          = ZCL_CLUSTER_SIDE_CLIENT;
  addressing->manufacturerSpecCode = 0;
  addressing->sequenceNumber       = ZCL_GetNextSeqNumber();
}
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEENROLLRESP == true) >
/**************************************************************************//**
 \brief ZoneEnrollResponseInd Command
 \param addressing - source info
 \param reportLength  - length of data in reportPayload
 \param payload - payload data
 \return none
******************************************************************************/
static ZCL_Status_t zoneEnrollResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneEnrollResCommand_t * payload)
{
  
   bool cieValid = zoneCieAddressFiltering(addressing);
   APP_Zigbee_Event_t event;
   event.eventGroup = EVENT_CLUSTER;
   event.eventId = CMD_ZCL_ZONE_ENROLL_RESP;
   event.eventData.zclEventData.addressing = addressing;
   event.eventData.zclEventData.payloadLength = payloadLength;
   event.eventData.zclEventData.payload = (uint8_t*)payload;

   if(!cieValid)
     return ZCL_SUCCESS_STATUS;
 
  switch(payload->enrollResponseCode)
  {
    case ENROLL_RESP_SUCCESS:
    {
      uint64_t tempCieAddr;
#if APP_ENABLE_CONSOLE != 1
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
      iasACEZoneClusterServerAttributes.iaszoneStatus.value = SUPERVISION_REPORT_STATE;
</#if><#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONETYPE == true) >
      iasACEZoneClusterServerAttributes.iaszoneType.value = ZCL_IAS_ZONE_CLUSTER_ZONE_TYPE_ATTRIBUTE_MOTION_SENSOR;
</#if>      
#endif
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATE == true) >
      if(!iasACEZoneClusterServerAttributes.iaszoneState.value)
      {
        iasACEZoneClusterServerAttributes.iaszoneState.value = ZCL_IAS_ZONE_CLUSTER_ZONE_STATE_ATTRIBUTE_ENROLLED;
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEID == true) >        
        iasACEZoneClusterServerAttributes.iasZoneId.value = payload->zoneId;
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_IASCIEADDRESS == true) >
        const ExtAddr_t *extAddr = ZDO_FindExtByShort(addressing->addr.shortAddress);

        COPY_64BIT_VALUE_A(&tempCieAddr,extAddr);
        iasACEZoneClusterServerAttributes.iasCieAddress.value = tempCieAddr;
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >        
        if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) && ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
        {
          zoneChangeNotiCmdTimer.interval = ZONE_NOTI_PERIOD;
          zoneChangeNotiCmdTimer.mode     = TIMER_REPEAT_MODE;
          zoneChangeNotiCmdTimer.callback = zoneChangeNotiCmdTimerFired;
          HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
        }
</#if>
       }
</#if>       
      }
      break;
    case ENROLL_RESP_NOT_SUPPORTED:
    case ENROLL_RESP_NOT_ENROLL_PERMIT:
    case ENROLL_RESP_TOO_MANY_ZONES:
      break;
    default:
      break;
   }
  PDS_Store(APP_IAS_ACE_ZONE_MEM_ID);
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>

/**************************************************************************//**
 \brief zoneCieAddressfiltering Command
 \param addressing - source info
 \return none
******************************************************************************/
static bool zoneCieAddressFiltering(ZCL_Addressing_t *addressing)
{
  uint64_t tempCieAddr;
  bool isAddressMatching = true;
  const ExtAddr_t *extAddr = ZDO_FindExtByShort(addressing->addr.shortAddress);
  if(!extAddr)
    return false;
  COPY_64BIT_VALUE_A(&tempCieAddr,extAddr);
  
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_IASCIEADDRESS == true) >
  if(tempCieAddr != iasACEZoneClusterServerAttributes.iasCieAddress.value)
    isAddressMatching = false;
</#if>    
  
  return isAddressMatching;
}

<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATENORMALOPMODE == true) >
/**************************************************************************//**
 \brief ZoneInitiateNormalOperatingModeInd Command
 \param addressing - source info
 \return none
******************************************************************************/
static ZCL_Status_t zoneInitiateNormalOperatingModeInd(ZCL_Addressing_t *addressing)
{
  
   bool cieValid = zoneCieAddressFiltering(addressing);
   APP_Zigbee_Event_t event;

   if(!cieValid)
     return ZCL_SUCCESS_STATUS;

<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >   
  //To retain the default value of CurrentZoneSensitivitylevel
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value =ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_DEFAULT;
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
  //To bring it back to the normal mode of the zone status value
  iasACEZoneClusterServerAttributes.iaszoneStatus.value &= ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE_TO_OPERATION_MODE;
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >
  //To bring it back to the normal mode of the zone status value
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = currentZoneSensitivityLevelValue;
</#if>  

  //Stop the timer, if already initiated by the test mode operation
  HAL_StopAppTimer(&zoneTestModeOperationTimer);

  //Send notification to the IAS Zone Client
  zoneStatusChangeNotificationCommandCallback();

  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ZONE_INITIATE_NORMAL_OPERATING_MODE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = 0;
  event.eventData.zclEventData.payload = NULL;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATETESTMODE == true) >
/**************************************************************************//**
 \brief ZoneInitiateTestModeInd Command
 \param addressing - source info
 \param payloadLength  - length of data in reportPayload
 \param payload - payload data
 \return none
******************************************************************************/
static ZCL_Status_t zoneInitiateTestModeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,ZCL_ZoneInitiateTestMode_t * payload)
{
  
   bool cieValid = zoneCieAddressFiltering(addressing);
   APP_Zigbee_Event_t event;

   if(!cieValid)
     return ZCL_SUCCESS_STATUS;
 
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
  //To Set the Zone Status to test Mode
  iasACEZoneClusterServerAttributes.iaszoneStatus.value |= (1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE);
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >
  //To retain the default value of CurrentZoneSensitivitylevel
  currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
  //To set the test mode zone sensitivty level value
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = payload->currentZoneSensitivityLevel;
</#if>
  //Timer to be in the test mode emulation for the Server  
  zoneTestModeOperationTimer.interval = (payload->testmodeDuration) * TIME_IN_SECONDS;
  zoneTestModeOperationTimer.mode     = TIMER_ONE_SHOT_MODE;
  zoneTestModeOperationTimer.callback = zoneTestModeOperationTimerFired;
  HAL_StartAppTimer(&zoneTestModeOperationTimer);

  //Send notification to the IAS Zone Client
  zoneStatusChangeNotificationCommandCallback();

  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ZONE_INITIATE_TEST_MODE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
/***************************************************************************//**
 \brief zoneTestModeOperationTimerFired
*******************************************************************************/
static void zoneTestModeOperationTimerFired(void)
{
  //Stop the timer
  HAL_StopAppTimer(&zoneTestModeOperationTimer);
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
  //Update the Test Bit to Zero
  iasACEZoneClusterServerAttributes.iaszoneStatus.value &= ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_TEST_MODE_TO_OPERATION_MODE;
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >
  //Update the CurrentZone Sensitivity level to the default value
  iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value = currentZoneSensitivityLevelValue;
</#if>
  //Send notification to the client and resume normal mode operation
  zoneStatusChangeNotificationCommandCallback();
}

<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
/***************************************************************************//**
 \brief zoneChangeNotiCmdTimerFired
*******************************************************************************/
static void zoneChangeNotiCmdTimerFired(void)
{
  HAL_StopAppTimer(&zoneChangeNotiCmdTimer);
  
  //To check whether we need periodic reports or not
  if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) & ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
  {
    HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
  }
  //Callback for the Zone notification
  zoneStatusChangeNotificationCommandCallback();
}
</#if>

/**************************************************************************//**
 \brief Attribute Event indication handler(to indicate when attr values have
        read or written)
 \param[in] addressing - pointer to addressing information;
 \param[in] attributeId - Id of the attribute;
 \param[in] event - event details
 \return none
******************************************************************************/
static void iasACEAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  //To take action for Current Zone Sensitivity level attribute
  if(event == ZCL_WRITE_ATTRIBUTE_EVENT)
  {
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_CURRENTZONESENSITIVITYLEVEL == true) >
    if (attributeId == ZCL_IAS_ZONE_CLUSTER_SERVER_CURRENTZONESENSITIVITY_LEVEL_SUPP_ID)         
    {
      currentZoneSensitivityLevelValue = iasACEZoneClusterServerAttributes.iasZoneCurrentZoneSensitivityLevel.value;
    }
</#if>
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_IASCIEADDRESS == true) >
    // To store the IAS_CIE Address attribute on PDS
    if (attributeId == ZCL_IAS_ZONE_CLUSTER_SERVER_ZONE_IAS_CIE_ADDRESS_ATTRIBUTE_ID)        
    {
<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATE == true) >      
      if(!iasACEZoneClusterServerAttributes.iaszoneState.value)
      {
#ifdef IAS_ZONE_AUTO_ENROLL_REQUEST_ENABLE 
       APS_Address_t apsAddr;
       uint64_t cieAddr = iasACEZoneClusterServerAttributes.iasCieAddress.value;
       memcpy(&apsAddr.extAddress[0], &cieAddr, sizeof(uint64_t));
       zoneEnrollRequestCommand(APS_EXT_ADDRESS, apsAddr, addressing->endpointId, APP_ENDPOINT_IAS_ACE, CS_MANUFACTURER_CODE);
#endif    
      }
</#if>
    }
</#if>    
    PDS_Store(APP_IAS_ACE_ZONE_MEM_ID);
  }

  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_IASZONE;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
  APP_Zigbee_Handler(eventItem);
}

<#if (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONESTATUS == true) >
/***************************************************************************//**
 \brief zoneChange change to send out the notification to CIE
 \param[in] addressing - pointer to addressing information;
 \return none
*******************************************************************************/
void zoneStatusChangeCommand(uint16_t zoneStatusChangeValue)
{
  if(zoneStatusChangeValue <= ZONE_MAXIMUM_LIMIT_VALUE)
  {
    iasACEZoneClusterServerAttributes.iaszoneStatus.value = zoneStatusChangeValue;
    zoneStatusChangeNotificationCommandCallback();
    if((iasACEZoneClusterServerAttributes.iaszoneStatus.value) & ( 1<< ZCL_IAS_ZONE_CLUSTER_ZONE_STATUS_ATTRIBUTE_SUPERVISION_REPORTS))
    {
      zoneChangeNotiCmdTimer.interval = ZONE_NOTI_PERIOD;
      zoneChangeNotiCmdTimer.mode     = TIMER_ONE_SHOT_MODE;
      zoneChangeNotiCmdTimer.callback = zoneChangeNotiCmdTimerFired;
      HAL_StartAppTimer(&zoneChangeNotiCmdTimer);
    }
     PDS_Store(APP_IAS_ACE_ZONE_MEM_ID);
  }
}
</#if>

#endif // APP_DEVICE_TYPE_IAS_ACE
// eof iasZoneCluster.c
