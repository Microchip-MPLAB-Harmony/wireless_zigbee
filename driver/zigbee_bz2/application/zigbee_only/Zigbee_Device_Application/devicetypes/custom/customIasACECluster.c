/*******************************************************************************
  Custom IAS Ace cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customIasACECluster.c

  Summary:
    This file contains the Custom Ias Ace Cluster implementation.

  Description:
    This file contains the Custom Ias Ace Cluster implementation.
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
/******************************************************************************
                    Includes section
******************************************************************************/
#include <appConsts.h>
#include <custom/include/customIasACECluster.h>
#include <custom/include/customIasZoneCluster.h>
#include <zclCommandManager.h>
#include <haClusters.h>
#include <console.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
//ByPass Table
bypassTable_t byPassList;

//Arm Table with a maximum entry of 3
ZCL_ACEArm_t armTable[ZONE_TABLE_ENTRIES];

//Panel Status Timer
static uint8_t panelStatusTimer = 0;
static uint16_t clientNwkAddr = 0xffff;
static ZCL_PanelStatus_t panel_Status;
/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload);
static ZCL_Status_t aceGetZoneStatusCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload);
static ZCL_Status_t aceByPassCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t aceArmCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload);
static void iasACEFillGetZoneInformationCommand(ZCL_GetZoneInformationResp_t *zonepayload, uint8_t zoneId );
static ZCL_Status_t aceEmergencyCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceFireCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t acePanicCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceGetZoneIdMapCommandInd(ZCL_Addressing_t *addressing);
static ZCL_Status_t aceGetPanelStatusCommandInd(ZCL_Addressing_t *addressing);
static void getPanelStatusChangeCmdTimerCallback();
static ZCL_Status_t  aceGetByPassedZoneListCommandInd(ZCL_Addressing_t *addressing);
static HAL_AppTimer_t getZoneStatusChangeCmdTimer;
static void getPanelStatusChangeCmdTimerFired(void);
static void setPanelStatus(ZCL_PanelStatus_t panelStatus);

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

/*****************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
PROGMEM_DECLARE (ZCL_IasACEClusterCommands_t customIasAceClusterServerCommands) =
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

PROGMEM_DECLARE (ZCL_IasACEClusterCommands_t customIasAceClusterClientCommands) =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(aceArmCommandInd,\
                    NULL,\
                    aceByPassCommandInd,\
                    aceEmergencyCommandInd,\
                    aceFireCommandInd,\
                    acePanicCommandInd,\
                    aceGetZoneIdMapCommandInd,\
                    NULL,\
                    aceGetZoneInformationCommandInd,\
                    NULL,\
                    aceGetPanelStatusCommandInd,\
                    NULL,\
                    aceGetZoneStatusCommandInd,\
                    NULL,\
                    NULL,\
                    NULL,\
                    aceGetByPassedZoneListCommandInd,\
                    NULL,\
                    NULL
                    )\
};

ZCL_IasAceClusterServerAttributes_t customIasAceClusterServerAttributes =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IasAceClusterClientAttributes_t customIasAceClusterClientAttributes =
{
  ZCL_DEFINE_IAS_ACE_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes IAS ACE cluster
******************************************************************************/
void customIasACEClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, IAS_ACE_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  //Initializes the byPass Table entries
  byPassList.totalZones = DEFAULT_VAL;
  
  for(uint8_t bypassArmEntry= DEFAULT_VAL; bypassArmEntry < ZONE_TABLE_ENTRIES; bypassArmEntry++)
  {
    //Initializes the byPass Table entries
    byPassList.bypassTable[bypassArmEntry].zoneId = 0xFF;
    byPassList.bypassTable[bypassArmEntry].armDisarmCode[0] = DEFAULT_VAL;

    //Initializes the Arm Table entries
    armTable[bypassArmEntry].zoneId= 0xFF;
    armTable[bypassArmEntry].armMode= (ZCL_ArmMode_t)0xFF;
    armTable[bypassArmEntry].lengthArmMode = 0xFF;
    armTable[bypassArmEntry].armDisarmCode[0] = DEFAULT_VAL;
  }
  if (cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  setPanelStatus(ARMED_STAY);

  customIasAceClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
  //Initialization of the list of attributes to their default values of IAS Zones 
  customIasAceClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
}
/**************************************************************************//**
\brief Sends ACEGetPanelStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep  -  Endpoint of the device;
\param[in] srcEp- source endpoint;
\param[in] panel_status - Panel status value;
\param[in] seconds_remaining  - seconds remaining for the panel status;
\param[in] audible_noti - audible notificaiton;
\param[in] alarmstatus   - alarm status;
******************************************************************************/
void acePanelStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,Endpoint_t srcEp, ZCL_PanelStatus_t panelStatus,
                              uint8_t secondsRemaining, ZCL_AudibleNotification_t audibleNoti,ZCL_AlarmStatus_t alarmStatus)
{
  ZCL_Request_t *req;
  ZCL_ACEPanelStatusChangedCommand_t *resp;
  clientNwkAddr = addr;

  if (!(req = getFreeCommand()))
    return;

  //Forming the command payload to be sent
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEPanelStatusChangedCommand_t), srcEp);
  resp = (ZCL_ACEPanelStatusChangedCommand_t *) req->requestPayload;

  //Filling the response structure with the input parameters
  resp-> panel_status= panelStatus;
  resp->seconds_remaining = secondsRemaining;
  resp->audible_noti = audibleNoti;
  resp->alarmstatus = alarmStatus;

  //To start the timer only when the state of the panel is of Exit and Entry Delay
  if((panelStatus == EXIT_DELAY || panelStatus == ENTRY_DELAY) && (secondsRemaining > DEFAULT_VAL))
  {
      panelStatusTimer = secondsRemaining;
      getZoneStatusChangeCmdTimer.interval = PANEL_STAUS_TIMER;
      getZoneStatusChangeCmdTimer.mode     = TIMER_ONE_SHOT_MODE;
      getZoneStatusChangeCmdTimer.callback = getPanelStatusChangeCmdTimerFired;
      HAL_StartAppTimer(&getZoneStatusChangeCmdTimer);
  }
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEPanelStatusChangedCommand Sent\r\n");
#endif
  return;
}
/**************************************************************************//**
\brief ACEGetPanelStatus Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetPanelStatusCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  ZCL_ACEGetPanelStatusCommandResp_t *resp;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID, sizeof(ZCL_ACEGetPanelStatusCommandResp_t), APP_ENDPOINT_COMBINED_INTERFACE);
  resp = (ZCL_ACEGetPanelStatusCommandResp_t *)req->requestPayload;
  
  resp->panel_status = (ZCL_PanelStatus_t)panel_Status;
  //To check whether the timer is already started or not
  if(panelStatusTimer > DEFAULT_VAL)
  {
    resp->seconds_remain = getZoneStatusChangeCmdTimer.interval;
  }
  else
  {
    resp->seconds_remain = TIME_REMAINING_DEFAULT;
  }
  resp->audible_noti = (ZCL_AudibleNotification_t)DEFAULT_SOUND;
  resp->alarmstatus = NO_ALARM;
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1    
    appSnprintf(" ->ACEGetPanelStatusCommandInd Received\r\n");
#endif    
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEGetZoneStatus Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneStatusCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload)
{
  ZCL_Request_t *req;
  uint8_t payloadResponse[PAYLOAD_SIZE];
  uint8_t payloadZoneResponseIndex = DEFAULT_VAL;
  uint8_t resp_count = DEFAULT_VAL;
  uint8_t zoneIdOffset = DEFAULT_VAL;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  payloadResponse[payloadZoneResponseIndex] = 1;
  payloadZoneResponseIndex++;
  payloadResponse[payloadZoneResponseIndex] = payload->max_number_zoneids;
  payloadZoneResponseIndex++;
  uint8_t maxZoneNumber = payload->max_number_zoneids;
  for(uint8_t zone_check = payload->starting_zone_id; zone_check < ZONE_TABLE_ENTRIES; zone_check++)
  {
    if(maxZoneNumber >0 && zoneTables[zone_check].zoneId != 0xFF)
    {
      if((!payload->zonestatus_maskflag))
      {
        payloadResponse[payloadZoneResponseIndex] = zoneTables[zone_check].zoneId;
        payloadZoneResponseIndex++;
        uint16_t zoneStatus = zoneTables[zone_check].zoneStatus;
        memcpy(&payloadResponse[payloadZoneResponseIndex],&zoneStatus, 2);
        payloadZoneResponseIndex +=2;
        maxZoneNumber--;
        resp_count++;
      }
      else
      {
        uint16_t zoneStatus = zoneTables[zone_check].zoneStatus;
        if(payload->zonestatus_mask & zoneStatus)
        {
          payloadResponse[payloadZoneResponseIndex] = zoneTables[zone_check].zoneId;
          payloadZoneResponseIndex++;
          memcpy(&payloadResponse[payloadZoneResponseIndex],&zoneStatus, 2);
          payloadZoneResponseIndex +=2;
          maxZoneNumber--;
          resp_count++;
        }
      }
    }
  }

  if(resp_count != payload->max_number_zoneids)
  {
    payloadResponse[zoneIdOffset] = DEFAULT_VAL;
    zoneIdOffset++;
    payloadResponse[zoneIdOffset] =resp_count;
  }

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID, payloadZoneResponseIndex, APP_ENDPOINT_COMBINED_INTERFACE);
  memcpy(req->requestPayload , &payloadResponse[0],payloadZoneResponseIndex);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
    appSnprintf(" ->ACEGetZoneStatusCommandInd Received\r\n");
#endif
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Sends ACEGetZoneStatusChanged Command

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep  -  Endpoint of the device;
\param[in] srcEp- source endpoint;
\param[in] zoneId - zoneId which changed the status;
\param[in] zoneStatus  - status of the zoneId which changed;
\param[in] audible_sound - audible sound;
\param[in] zone_label   - zone label;
******************************************************************************/
void aceZoneStatusChangedCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
                                        uint8_t zoneId, uint8_t zoneStatus, ZCL_AudibleNotification_t audibleSound, char *zoneLabel)
{
  ZCL_Request_t *req;
  ZCL_ACEZoneStatusChangedCommand_t *resp;

  if (!(req = getFreeCommand()))
    return;

  //Memory Allocation
  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEZoneStatusChangedCommand_t), srcEp);
  resp = (ZCL_ACEZoneStatusChangedCommand_t *) req->requestPayload;

  //Response filling
  resp->zoneid = zoneId;
  resp->zoneStatus = zoneStatus;
  resp->audible_noti = audibleSound;
  resp->zoneLength = strlen(zoneLabel);
  memcpy(&resp->zoneLabel[0], zoneLabel, resp->zoneLength);

  //Address Allocation
  fillDstAddressingServer(&req->dstAddressing, mode, addr, ep, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEZoneStatusChangedCommand Sent\r\n");
#endif

  return;
}
/**************************************************************************//**
\brief ACEArm Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceArmCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload)
{
  ZCL_Request_t *req;
  ZCL_ACEResponseArm_t arm_response;
  uint8_t armAction = DEFAULT_VAL;
  uint8_t armSeqCheck = DEFAULT_VAL;
  uint64_t tempCieAddr;
  const ExtAddr_t *extAddr = NWK_GetExtByShortAddress(addressing->addr.shortAddress);
  
  if(*extAddr != 0)
    COPY_64BIT_VALUE_A(&tempCieAddr,extAddr);
  //Assigning default value
  arm_response.armNotify = ALL_ZONE_DISARMED;

  //Arm Payload extraction and action
  if(payload->zoneId < ZONE_TABLE_ENTRIES)
  {
    if(armTable[payload->zoneId].zoneId == payload->zoneId)
    {
      //Compare the disarm_code Code
      for (uint8_t byteCheck = DEFAULT_VAL ; byteCheck < 8; byteCheck++)
      {
        if(armTable[payload->zoneId].armDisarmCode[byteCheck] == payload->armDisarmCode[byteCheck])
          armSeqCheck++;
       }
      if(armSeqCheck == ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE)
      {
        armAction = 1;
        if(payload->armMode == DISARM && armTable[payload->zoneId].armMode == DISARM)
        {
          armTable[payload->zoneId].armMode = DISARM;
          arm_response.armNotify = ALREADY_DISARMED;
        }
      }
      else
        arm_response.armNotify = INVALID_ARMCODE;
    }
    else if((payload->zoneId == zoneTables[payload->zoneId].zoneId) && (tempCieAddr = zoneTables[payload->zoneId].zoneAddress))
    {
      armTable[payload->zoneId].armMode = payload->armMode;
      armTable[payload->zoneId].zoneId = payload->zoneId;
      armTable[payload->zoneId].lengthArmMode = payload->lengthArmMode;
      memcpy(&armTable[payload->zoneId].armDisarmCode,payload->armDisarmCode,ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
      armAction = 1;
    }
    else
    {
      arm_response.armNotify = NOT_READY_TO_ARM_STATE;
    }
    if((armAction))
    {
      if(payload->armMode == ARM_ALL_ZONES)
      {
        armTable[payload->zoneId].armMode = ARM_ALL_ZONES;
        arm_response.armNotify = ALL_ZONE_ARMED;
      }
      else if(payload->armMode == DISARM)
      {
        armTable[payload->zoneId].armMode = DISARM;
        arm_response.armNotify = ALL_ZONE_DISARMED;
      }
      else if(payload->armMode == ARM_DAY_HOME_ZONES_ONLY)
      {
        armTable[payload->zoneId].armMode = ARM_DAY_HOME_ZONES_ONLY;
        arm_response.armNotify = ONLY_DAY_HOME_ZONES_ARMED;
      }
      else if(payload->armMode == ARM_NIGHT_SLEEP_ZONES_ONLY)
      {
        armTable[payload->zoneId].armMode =  ARM_NIGHT_SLEEP_ZONES_ONLY;
        arm_response.armNotify = ONLY_NIGHT_SLEEP_ZONES_ARMED;
      }
      else
      {
        arm_response.armNotify = (ZCL_ArmNotification_t)armTable[payload->zoneId].armMode;
      }
    }
  }
  //Allocating Memory for the response
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID, sizeof(ZCL_ACEResponseArm_t), APP_ENDPOINT_COMBINED_INTERFACE);
  memcpy(req->requestPayload, &arm_response, sizeof(ZCL_ACEResponseArm_t));
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS; 
}
/**************************************************************************//**
\brief Fills iasACEFillGetZoneInformation Command

\param[in] zonepayload - pointer to payload for filling;
\param[in] zoneId - zoneId base to get relevant informationh;

\return none
******************************************************************************/
static void iasACEFillGetZoneInformationCommand(ZCL_GetZoneInformationResp_t *zonepayload, uint8_t zoneId)
{
  if((zoneId < ZONE_TABLE_ENTRIES) && (zoneTables[zoneId].zoneId != 0xFF))
  {
    zonepayload->zoneId      = zoneTables[zoneId].zoneId;
    zonepayload->zoneType    = zoneTables[zoneId].zoneType;
    zonepayload->zoneAddress = zoneTables[zoneId].zoneAddress;
  }
  else
  {
    zonepayload->zoneId = 0xFF;
    zonepayload->zoneType = 0xFFFF;
    zonepayload->zoneAddress = DEFAULT_EXT_ADDR;
  }
  zonepayload->length    = sizeof(ZONE_LABEL);
  memcpy(&zonepayload->zoneLabel[0], (char *)ZONE_LABEL, zonepayload->length);
}

/**************************************************************************//**
\brief ACEGetZoneInformation Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID, sizeof(ZCL_GetZoneInformationResp_t), APP_ENDPOINT_COMBINED_INTERFACE);
  iasACEFillGetZoneInformationCommand((ZCL_GetZoneInformationResp_t *)req->requestPayload ,payload->zoneId);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
  (void) payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEGetZoneIdMap Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceGetZoneIdMapCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  ZCL_GetZoneIdMapResponse_t *payload;
  uint8_t responsePayload = DEFAULT_VAL;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID, sizeof(ZCL_GetZoneIdMapResponse_t), APP_ENDPOINT_COMBINED_INTERFACE);
  payload = (ZCL_GetZoneIdMapResponse_t *) req->requestPayload;

  //Initializing the response payload
  for(uint8_t zoneEntry = 0 ; zoneEntry < ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE ; zoneEntry++)
  {
    payload->getZoneIdMapResponse[zoneEntry] = DEFAULT_VAL;
  }

  //Framing response packets and typically 256 zoneIds are allowed
  for(uint8_t zoneIdEntry = DEFAULT_VAL; zoneIdEntry < ZONE_TABLE_ENTRIES; zoneIdEntry++)
  {
    if(zoneTables[zoneIdEntry].zoneId != 0xFF)
    {
      if(responsePayload < ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE)
      {
        payload->getZoneIdMapResponse[responsePayload] |= (1 << (zoneIdEntry%16));
      }
      if((zoneIdEntry>0) && (zoneIdEntry % ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE == 0))
      {
        responsePayload++;
      }
    }
  }

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEByPass Command Indication

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceByPassCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Request_t *req;
  uint8_t payloadExtractLength = DEFAULT_VAL;
  uint8_t payloadZoneResponseIndex = DEFAULT_VAL;
  uint8_t zoneIdOffset = 1;

  //Extract Payload
  uint8_t payload_extract[PAYLOAD_SIZE];
  uint8_t payloadResponse[PAYLOAD_SIZE];
  memcpy(&payload_extract[payloadExtractLength], payload,payloadLength);
  uint8_t totalZones = payload_extract[payloadExtractLength];
  payloadExtractLength++;
  zoneIdOffset = payload_extract[payloadExtractLength];
  payloadExtractLength++;

  //Total Number of Zones in the response
  payloadResponse[payloadZoneResponseIndex] = totalZones;
  payloadZoneResponseIndex++;

  for( uint8_t zonesearch = DEFAULT_VAL ;zonesearch < totalZones ;zonesearch++)
  {
    if(zoneIdOffset >= ZONE_TABLE_ENTRIES)
    {
      payloadResponse[payloadZoneResponseIndex]  = INVALID_ZONE_ID; /*Suitale would be Invalid*/
    }
    else
    {
      if(zoneTables[zoneIdOffset].zoneId == zoneIdOffset)
      {
        if(byPassList.bypassTable[zoneIdOffset].zoneId != zoneIdOffset)
        {
          byPassList.bypassTable[zoneIdOffset].zoneId = zoneIdOffset;

          //Compare the disarm_code Code
          if((byPassList.bypassTable[zoneIdOffset].armDisarmCode == DEFAULT_VAL) ||
               (memcmp(byPassList.bypassTable[zoneIdOffset].armDisarmCode,&payload_extract[totalZones+2],ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE)))
          {
            memcpy(&byPassList.bypassTable[zoneIdOffset].armDisarmCode[0], &payload_extract[totalZones+2],ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE);
            byPassList.totalZones++;
            payloadResponse[payloadZoneResponseIndex] = ZONE_BYPASSED;
          }
          else
          {
            payloadResponse[payloadZoneResponseIndex] = INVALID_ARM_DISARM_CODE;
          }
        }
        else if(byPassList.bypassTable[zoneIdOffset].zoneId == zoneIdOffset)
        {
          uint8_t compareSeqCheck = DEFAULT_VAL;
          //Compare the disarm_code Code
          for (uint8_t byteCheck = DEFAULT_VAL ; byteCheck < 8; byteCheck++)
          {
            if(byPassList.bypassTable[zoneIdOffset].armDisarmCode[byteCheck] == payload_extract[totalZones+2+byteCheck])
              compareSeqCheck++;
          }
          if(compareSeqCheck == 0x08)
            payloadResponse[payloadZoneResponseIndex] = ZONE_BYPASSED;
          else
            payloadResponse[payloadZoneResponseIndex] = INVALID_ARM_DISARM_CODE;
        }
        else
        {
          payloadResponse[payloadZoneResponseIndex] = NOT_ALLOWED;
        }
      }
      else
      {
        payloadResponse[payloadZoneResponseIndex] = UNKNOWN_ZONE_ID;
      }
    }
    zoneIdOffset = payload_extract[payloadExtractLength++];
    payloadZoneResponseIndex++;
  }

  //Allocating Memory for the response
  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID, payloadZoneResponseIndex, APP_ENDPOINT_COMBINED_INTERFACE);

   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payloadResponse[0],payloadZoneResponseIndex);
   
  //fillCommandRequest(req, BYPASS_RESP, sizeof(ZCL_AceByPassResponseCommand_t));
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEGetByPassesZoneList Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static  ZCL_Status_t  aceGetByPassedZoneListCommandInd(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;
  uint8_t payloadSetResponseListIndex = DEFAULT_VAL;
  uint8_t payloadResponse[PAYLOAD_SIZE];

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  payloadResponse[payloadSetResponseListIndex] = byPassList.totalZones;
  payloadSetResponseListIndex++;

  for (uint8_t zonelist = DEFAULT_VAL; zonelist < byPassList.totalZones ; zonelist++)
  {
    if(byPassList.bypassTable[zonelist].zoneId < ZONE_TABLE_ENTRIES)
    {
      payloadResponse[payloadSetResponseListIndex] = byPassList.bypassTable[zonelist].zoneId;
      payloadSetResponseListIndex++;
    }
  }

   //Allocating Buffer Space for the Command
   fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID, payloadSetResponseListIndex--, APP_ENDPOINT_COMBINED_INTERFACE);

   //Payload Copy into the request Payload.
   memcpy(req->requestPayload, &payloadResponse[0],payloadSetResponseListIndex--);

  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  ZCL_CommandManagerSendCommand(req);
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEEmergency Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t aceEmergencyCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Emergency Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief ACEFire Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static  ZCL_Status_t aceFireCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Fire Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief  ACEPanic Command Indication

\param[in] addressing - pointer to addressing information;

\return status of indication routine
******************************************************************************/
static ZCL_Status_t acePanicCommandInd(ZCL_Addressing_t *addressing)
{
  (void)addressing;
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACE Panic Command Received\r\n");
#endif
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
 \brief getPanelStatusChangeCmdTimerCallback
 \param none
 \return none
******************************************************************************/
void getPanelStatusChangeCmdTimerCallback()
{
  ZCL_Request_t *req;
  ZCL_ACEGetPanelStatusCommandResp_t *resp;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID, sizeof(ZCL_ACEGetPanelStatusCommandResp_t), APP_ENDPOINT_COMBINED_INTERFACE);
  resp = (ZCL_ACEGetPanelStatusCommandResp_t *) req->requestPayload;
  
  resp->panel_status = panel_Status;
  resp->seconds_remain = panelStatusTimer;
  resp->audible_noti = DEFAULT_SOUND;
  resp->alarmstatus = NO_ALARM;
  
  fillDstAddressingServer(&req->dstAddressing, APS_SHORT_ADDRESS, clientNwkAddr, ACE_ENDPT, IAS_ACE_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
  
  //To Send periodic panel status change update of One second
  if(panelStatusTimer > DEFAULT_VAL)
  {
    HAL_StartAppTimer(&getZoneStatusChangeCmdTimer);
  }
  else
  {
    //To reset the timer count
    panelStatusTimer = 0;
  }
#if APP_ENABLE_CONSOLE == 1
    appSnprintf(" ->ACEGetPanelStatusCommandInd Received\r\n");
#endif
    
}

/*********************************************************************************************************************//**
 \brief getPanelStatusChangeCmdTimerFired
***********************************************************************************************************************/
static void getPanelStatusChangeCmdTimerFired(void)
{
  HAL_StopAppTimer(&getZoneStatusChangeCmdTimer);
  panelStatusTimer--;
  getPanelStatusChangeCmdTimerCallback();
}
/*********************************************************************************************************************//**
 \brief setsthePanelStatus
***********************************************************************************************************************/
static void setPanelStatus(ZCL_PanelStatus_t panelStatus)
{
  panel_Status = panelStatus;
}
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
/**************************************************************************//**
\brief ACEArm Response Command
\param addressing - Arm Command Response 
\param payloadLength  -  Payload lengeth
\param payload -  Arm payload
\return ZCL_Status_t
******************************************************************************/
static ZCL_Status_t aceArmResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload)
{
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACEArmResponseCommand Received\r\n");
#endif
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
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
/**************************************************************************//**
\brief ACEGetZoneIdMapResponse Command Indication
\param addressing - ACEGetZoneIdMapResponse Address details 
\param payloadLength  - Payload lengeth
\param payload -  ZOne MapId Response pointer
\return none
******************************************************************************/
static ZCL_Status_t aceGetZoneIdMapResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload)
{
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ZoneIdMapResponseCommand Received \r\n");
#endif
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
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
/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetPanelStatusCommandResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetPanelStatusCommandRespInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload)
{
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->aceGetPanelStatusRespReceived\r\n");
#endif
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;  
}
/**************************************************************************//**
 \brief ACEGetZoneStatus Command
 \param addressing - ACEGetZoneStatusRespAddress details 
 \param payloadLength  - Payload lengeth
 \param payload - Zone Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneStatusRespCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->aceGetZoneStatusRespReceived\r\n");
#endif
  (void)payload;
  (void)payloadLength;
  (void)addressing;  
  return ZCL_SUCCESS_STATUS;   
}
/**************************************************************************//**
 \brief ACE Panel Status Command
 \param addressing - ACEPanelStatusChanged Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t acePanelStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload; 
  return ZCL_SUCCESS_STATUS;  
}
/**************************************************************************//**
 \brief ACE Zone Status Command
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Panel Status Status Details
 \return none
******************************************************************************/
static ZCL_Status_t aceZoneStatusChangedCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload; 
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
 \brief ACEGetZoneInformationResponse Command Indication
 \param addressing - ACEGetZoneIdMapResponse Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Zone table details
 \return none
******************************************************************************/
static ZCL_Status_t aceGetZoneInformationResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
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
/**************************************************************************//**
 \brief aceSetByPassesZoneList Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceSetByPassedZoneListCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
#if APP_ENABLE_CONSOLE == 1
  appSnprintf(" ->ACESetByPassesZoneListCommandIndReceived\r\n");
#endif
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
 \brief aceByPassResponse Command Indication
 \param addressing - Address details 
 \param payloadLength  - Payload lengeth
 \param payload -  Payload pointer
 \return none
******************************************************************************/
static ZCL_Status_t aceByPassResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength,uint8_t * payload)
{
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
// eof customIasACECluster.c
