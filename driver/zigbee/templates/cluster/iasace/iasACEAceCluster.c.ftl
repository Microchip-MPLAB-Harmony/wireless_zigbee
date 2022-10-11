/*******************************************************************************
  IAS-ACE Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   asACECluster.c

  Summary:
    This file contains the IAS-ACE Cluster interface.

  Description:
    This file contains the IAS-ACE Cluster interface.
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
#include <z3device/ias_ace/include/iasACECluster.h>
#include <z3device/ias_ace/include/iasACEAceCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <app_zigbee/zigbee_console/console.h>
#endif
#include <z3device/ias_ace/include/iasACEZoneCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/ias_ace/include/iasACEGroupsCluster.h>
#include <zcl/include/zclIasZoneCluster.h>
#include <zcl/include/zclIasACECluster.h>
#include <zcl/include/zclZllBasicCluster.h>
#include <zcl/include/zclZllIdentifyCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <z3device/common/include/appConsts.h>
#include <zcl/include/zclCommandManager.h>
#include <app_zigbee/app_zigbee_handler.h>
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void iasACEFillGetZoneInfoCommand(ZCL_GetZoneInformationCommand_t *payload , uint8_t zone_id);
static ZCL_Status_t aceArmResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload);
static ZCL_Status_t aceGetZoneIdMapResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload);
static ZCL_Status_t aceGetZoneInformationResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload);
static ZCL_Status_t acePanelStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload);
static ZCL_Status_t aceZoneStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload);
static ZCL_Status_t aceGetZoneStatusRespCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t aceGetPanelStatusCommandRespInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload);
static ZCL_Status_t aceSetByPassedZoneListCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload);
static ZCL_Status_t aceByPassResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload);

/******************************************************************************
                    Global variables
******************************************************************************/
//IAS ACE Cluster Commands
PROGMEM_DECLARE (ZCL_IasACEClusterCommands_t iasACEClusterCommands) =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(NULL,\
                    aceArmResponseCommandInd,\
                    NULL,\
                    NULL,\
                    NULL,\
                    NULL,\
                    NULL,\
                    aceGetZoneIdMapResponseCommandInd,\
                    NULL,\
                    aceGetZoneInformationResponseCommandInd,\
                    NULL,\
                    aceGetPanelStatusCommandRespInd,\
                    NULL,\
                    aceGetZoneStatusRespCommandInd,\
                    acePanelStatusChangedCommandInd,\
                    aceZoneStatusChangedCommandInd,\
                    NULL,\
                    aceSetByPassedZoneListCommandInd,\
                    aceByPassResponseCommandInd
                    )\
};

//IAS ACE Server Attributes
ZCL_IasAceClusterServerAttributes_t iasACEAceClusterServerAttributes =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IasAceClusterClientAttributes_t iasACEAceClusterClientAttributes =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Initializes iasACE Cluster
******************************************************************************/
void iasACEClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IAS_ACE_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_Cluster_t *aceCluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IAS_ACE_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_CLUSTERREVISION == true) >
  //Initialization of the list of attributes to their default values of IAS Zones 
  iasACEAceClusterClientAttributes.clusterVersion.value = ACE_CLUSTER_VERSION;
</#if>  
  
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  //iasACEAceClusterServerAttributes.clusterVersion.value = ACE_CLUSTER_VERSION;;
}

<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARM == true) >
/**************************************************************************//**
\brief iasACEFill Arm Payload
\param[in] payload  - payload of the Arm to fill
\param[in] arm_mode  - differnent arm modes
\param[in] code  - arm diasarm code
\param[in] zoneId  - zone Id information
\return none
******************************************************************************/
static void iasACEFillArmCommand(ZCL_ACEArm_t *payload , uint8_t armMode, char *code , uint8_t zoneId)
{
  uint8_t armCodeLength = 0;
  
  armCodeLength = strlen(code);
  if((armCodeLength >= 4) && (armCodeLength <= 8))
  {
    payload->armMode       = (ZCL_ArmMode_t)armMode;
    payload->lengthArmMode = armCodeLength;
    memcpy(payload->armDisarmCode, code,armCodeLength);
    payload->zoneId        = zoneId;
  }
}
</#if>

/**************************************************************************//**
\brief iasFill GetZoneInfo Command
\param[in] payload  - payload of the GetZone Information
\param[in] zoneId  - index of the zone table
\return none
******************************************************************************/
static void iasACEFillGetZoneInfoCommand(ZCL_GetZoneInformationCommand_t *payload , uint8_t zoneId)
{
  payload->zoneId  = zoneId;
}

<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARM == true) >
/**************************************************************************//**
\brief ACEArmCommand Command
\param mode - Adress Mode
\param addr - Adress detail 
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\param[in] arm_mode  - differnent arm modes
\param[in] code  - arm diasarm code
\param[in] zoneId  - zone Id information
\return none
******************************************************************************/
void aceArmCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t arm_mode , char *code , uint8_t zoneid)
{
  ZCL_Request_t *req;
  uint8_t strLength = 0;
  uint8_t payloadLenth = 0;
  
  if (!(req = getFreeCommand()))
    return ;

  strLength = strlen(code);
  payloadLenth = sizeof(ZCL_ACEArm_t) - ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE + strLength;
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID, payloadLenth, srcEp);
  iasACEFillArmCommand((ZCL_ACEArm_t *)req->requestPayload , arm_mode, code, zoneid);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEArmCommand Sent\r\n");
#endif  
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARMRESP == true) >
/**************************************************************************//**
\brief ACEArm Response Command
\param addressing - Arm Command Response 
\param payloadLength  -  Payload lengeth
\param payload -  Arm payload
\return ZCL_Status_t
******************************************************************************/
static ZCL_Status_t aceArmResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_ARM_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASS == true) >
/**************************************************************************//**
\brief aceByPass Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\param zone_numbers -  total zones
\param zoneId(s) -  index of the zone table
\return none
******************************************************************************/
void aceByPassCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t zone_numbers, 
                      uint8_t *zone_id, char *arm_disarm_code)
{
  ZCL_Request_t *req;
  uint8_t payload[PAYLOAD_SIZE];
  uint8_t payload_length =0;
  uint8_t armCodeLen = 0;

  if (!(req = getFreeCommand()))
    return ;
 
  payload[payload_length++] = zone_numbers;

  for(uint8_t i = 0; i < zone_numbers; i++)
  {
     payload[payload_length++] = zone_id[i];
  }
   armCodeLen = strlen(arm_disarm_code);
   if((armCodeLen >= 4) && (armCodeLen <= 8))
   {
     payload[payload_length++] = armCodeLen;     
     memcpy(&payload[payload_length], arm_disarm_code, armCodeLen);
     payload_length += armCodeLen; 
   }
   else
   {
     //TBD
   }
     
   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID, payload_length, srcEp);
   
   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payload[0],payload_length);

   //Filling Destination Address.
   fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
   ZCL_CommandManagerSendCommand(req);   
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEByPassCommand Sent\r\n");
#endif   
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_EMERGENCY == true) >
/**************************************************************************//**
\brief ACEEmergency Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\return none
******************************************************************************/
void aceEmergencyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID, 0x00, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEEmergencyCommand Sent\r\n");
#endif    
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_FIRE == true) >
/**************************************************************************//**
\brief ACEFire Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\return none
******************************************************************************/
void aceFireCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID, 0x00, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEFireCommand Sent\r\n");
#endif  
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANIC == true) >
/**************************************************************************//**
\brief ACEPanic Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\return none
******************************************************************************/
void acePanicCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID, 0x00, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req); 
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEPanicCommand Sent\r\n");
#endif   
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAP == true) >
/**************************************************************************//**
\brief ACEGetZoneIdMap Command
\param mode - Adress Mode
\param addr - short addr
\param ep  -  Endpoint of the device
\param[in] srcEp- source endpoint;
\return none
******************************************************************************/
void aceGetZoneIdMapCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID, 0x00, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEGetZoneIdMapCommand Sent\r\n");
#endif
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAPRESP == true) >
/**************************************************************************//**
\brief ACEGetZoneIdMapResponse Command Indication
\param addressing - ACEGetZoneIdMapResponse Address details 
\param payloadLength  - Payload lengeth
\param payload -  ZOne MapId Response pointer
\return none
******************************************************************************/
static ZCL_Status_t aceGetZoneIdMapResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_GET_ZONE_ID_MAP_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFO == true) >
/**************************************************************************//**
 \brief aceGetZoneInformation Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param zoneId  -  zone Id base
 \return none
******************************************************************************/
void aceGetZoneInformationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t zoneId)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID, sizeof(ZCL_GetZoneInformationCommand_t), srcEp);
  iasACEFillGetZoneInfoCommand((ZCL_GetZoneInformationCommand_t *)req->requestPayload , zoneId);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEGetZoneInformationCommand Sent\r\n");
#endif    
 
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETPANELSTATUS == true) >
/**************************************************************************//**
 \brief ACEGetPanelStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void aceGetPanelStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;
  
  if (!(req = getFreeCommand()))
    return ;
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID, 0x00, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req); 
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEGetPanelStatusCommand Sent\r\n");
#endif
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUS == true) >
/**************************************************************************//**
 \brief aceGetZoneStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param startingZoneId - starting of the zoneId offset
 \param maxNumberZoneids - maximum zoneIdss
 \param zoneStatusMaskFlag - mask flag
 \param zoneStatusMask - status of the zone
 \return none
******************************************************************************/
void aceGetZoneStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t starting_zone_id, uint8_t max_number_zoneids, uint8_t zonestatus_maskflag, uint16_t zonestatus_mask)
{
  ZCL_Request_t *req;
  ZCL_ACEGetZoneStatusCommand_t *request;

  if (!(req = getFreeCommand()))
    return ;
  
  //Allocating memory and size
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID, sizeof(ZCL_ACEGetZoneStatusCommand_t), srcEp);
  request = (ZCL_ACEGetZoneStatusCommand_t *) req->requestPayload;
  
  //Filling up payload
  request->starting_zone_id = starting_zone_id;
  request->max_number_zoneids = max_number_zoneids;
  request->zonestatus_maskflag = zonestatus_maskflag;
  request->zonestatus_mask = zonestatus_mask;  
  
  //Destination Address Filling
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEGetZoneStatusCommand Sent\r\n");
#endif
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true) >
/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetPanelStatusCommandResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetPanelStatusCommandRespInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_GET_PANEL_STATUS_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;  
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUS == true) >
/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetZoneStatusRespAddress details 
 \param payloadLength  - Payload lengeth
 \param payload - Zone Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneStatusRespCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_GET_ZONE_STATUS_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);  
  return ZCL_SUCCESS_STATUS;   
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANELSTATUSCHANGED == true) >
/**************************************************************************//**
 \brief ACE Panel Status Command
 \param addressing - ACEPanelStatusChanged Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t acePanelStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_PANEL_STATUS_CHANGED;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;  
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ZONESTATUSCHANGED == true) >
/**************************************************************************//**
 \brief ACE Zone Status Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceZoneStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_ZONE_STATUS_CHANGED;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFORESP == true) >
/**************************************************************************//**
 \brief ACEGetZoneInformationResponse Command Indication
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Zone table details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_GET_ZONE_INFO_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETBYPASSZONELIST == true) >
/**************************************************************************//**
 \brief ACEGetZoneInformationResponse Command Indication
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void getByPassZoneListCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID, 0, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->GetByPassZoneListCommand Sent\r\n");
#endif
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_SETBYPASSEDZONELIST == true) >
/**************************************************************************//**
 \brief aceSetByPassesZoneList Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceSetByPassedZoneListCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_SET_BYPASSED_ZONE_LIST;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASSRESPONSE == true) >
/**************************************************************************//**
 \brief aceByPassResponse Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceByPassResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ACE_BYPASS_RESP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
#endif // APP_DEVICE_TYPE_IAS_ACE
//// eof iasACECluster.c
