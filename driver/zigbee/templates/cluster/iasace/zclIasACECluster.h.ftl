/*******************************************************************************
  Zigbee Cluster Library IAS ACE Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclIasAceCluster.h

  Summary:
    The file describes the types and interface of the
    Relative Humidity Measurement cluster.

  Description:
    The file describes the types and interface of the
    Relative Humidity Measurement cluster.
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




#ifndef _ZCLIASACECLUSTER_H_
#define _ZCLIASACECLUSTER_H_

/*******************************************************************************
                   Includes section
*******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <zcl/include/zclIasZoneCluster.h>
#include <zcl/include/clusters.h>

/*******************************************************************************
                   Define(s) section
*******************************************************************************/
/**
 * \brief Request commands
*/

#ifndef ZONE_LABEL
#define ZONE_LABEL                                                              "ZONE"
#endif

#define ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID                                      0x00
#define ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID                                   0x01
#define ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID                                0x02
#define ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID                                     0x03
#define ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID                                    0x04
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID                          0x05
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID                     0x06
#define ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID                         0x07
#define ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID                   0x08
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID                          0x09

/**
 * \brief server response commands
*/
#define ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID                             0x00
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID                 0x01
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID            0x02
#define ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID                      0x03
#define ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID                     0x04
#define ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID                0x05
#define ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID                   0x06
#define ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID                          0x07
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID                 0x08

//Total of 19 Commands
#define ZCL_IAS_ACE_SERVER_CLUSTER_COMMANDS_AMOUNT                              ${IAC_SERVERCOMMANDCOUNT}
#define ZCL_IAS_ACE_CLIENT_CLUSTER_COMMANDS_AMOUNT                              ${IACC_CLIENTCOMMANDCOUNT}

#define ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE                                        0x08
#define ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE                                        0x10
#define ZCL_IAS_ACE_ZONE_LABEL_SIZE                                             0x02

/**
 * \brief cluster attributes amount
*/
#define ZCL_IAS_ACE_SERVER_CLUSTER_ATTRIBUTES_AMOUNT                            ${IAC_SERVERATTRIBUTECOUNT}
#define ZCL_IAS_ACE_CLIENT_CLUSTER_ATTRIBUTES_AMOUNT                            ${IACC_CLIENTATTRIBUTECOUNT}
/**
 * \brief Identify ClusterVersion attribute identifier (for both server and client)
*/
#define ZCL_IAS_ACE_CLUSTER_GLOBAL_CLUSTER_VERSION_ATTRIBUTE_ID    CCPU_TO_LE16(0xfffd)
/**
 * \brief server response commands
*/
/***************************************************************************//**
\brief IAS Zone Cluster define commands macros
*******************************************************************************/
#define ZCL_DEFINE_IAS_ACE_CLUSTER_SERVER_ATTRIBUTES() <#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_CLUSTERREVISION == true) >\
  DEFINE_ATTRIBUTE(clusterVersion, ZCL_READONLY_ATTRIBUTE, ZCL_IAS_ACE_CLUSTER_GLOBAL_CLUSTER_VERSION_ATTRIBUTE_ID, ZCL_U16BIT_DATA_TYPE_ID)</#if>
    
#define IAS_ACE_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands) \
  { \
    .id = IAS_ACE_CLUSTER_ID, \
    .options = {.type = ZCL_SERVER_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
    .attributesAmount = ZCL_IAS_ACE_SERVER_CLUSTER_ATTRIBUTES_AMOUNT, \
    .attributes = (uint8_t *) clattributes, \
    .commandsAmount = ZCL_IAS_ACE_SERVER_CLUSTER_COMMANDS_AMOUNT, \
    .commands = (uint8_t *)clcommands \
  }

#define ZCL_DEFINE_IAS_ACE_CLUSTER_CLIENT_ATTRIBUTES() <#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_CLUSTERREVISION == true) >\
  DEFINE_ATTRIBUTE(clusterVersion, ZCL_READONLY_ATTRIBUTE, ZCL_IAS_ACE_CLUSTER_GLOBAL_CLUSTER_VERSION_ATTRIBUTE_ID, ZCL_U16BIT_DATA_TYPE_ID)</#if>
    
#define IAS_ACE_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands) \
  { \
    .id = IAS_ACE_CLUSTER_ID, \
    .options = {.type = ZCL_CLIENT_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
    .attributesAmount = ZCL_IAS_ACE_CLIENT_CLUSTER_ATTRIBUTES_AMOUNT, \
    .attributes = (uint8_t *) clattributes, \
    .commandsAmount = ZCL_IAS_ACE_CLIENT_CLUSTER_COMMANDS_AMOUNT, \
    .commands = (uint8_t *)clcommands \
  }

#define DEFINE_IAS_ACE_CLUSTER(cltype, clattributes, clcommands) \
    IAS_ACE_CLUSTER_##cltype(clattributes, clcommands)

/***************************************************************************//**
\brief IAS ACE Cluster define commands macros
*******************************************************************************/      
#define ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(aceArmCommandInd,\
                                            aceArmResponseCommandInd,\
                                            aceByPassCommandInd,\
                                            aceEmergencyCommandInd,\
                                            aceFireCommandInd,\
                                            acePanicCommandInd,\
                                            aceGetZoneIdMapCommandInd,\
                                            aceGetZoneIdMapResponseCommandInd,\
                                            aceGetZoneInformationCommandInd,\
                                            aceGetZoneInformationResponseCommandInd,\
                                            aceGetPanelStatusCommandInd,\
                                            aceGetPanelStatusCommandRespInd,\
                                            aceGetZoneStatusCommandInd,\
                                            aceGetZoneStatusRespCommandInd,\
                                            acePanelStatusChangedCommandInd,\
                                            aceZoneStatusChangedCommandInd,\
                                            aceGetByPassedZoneListCommandInd,\
                                            aceSetByPassedZoneListCommandInd,\
                                            aceByPassResponseCommandInd)<#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_ARM == true) >\
    DEFINE_COMMAND(aceArmCommand, ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceArmCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARMRESP == true) >\
    DEFINE_COMMAND(aceArmResponseCommand, ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     aceArmResponseCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_BYPASS == true) >\
    DEFINE_COMMAND(aceByPassCommand, ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceByPassCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_EMERGENCY == true) >\
    DEFINE_COMMAND(aceEmergencyCommand, ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceEmergencyCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_FIRE == true) >\
    DEFINE_COMMAND(aceFireCommand, ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceFireCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_PANIC == true) >\
    DEFINE_COMMAND(acePanicCommand, ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     acePanicCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEIDMAP == true) >\
    DEFINE_COMMAND(aceGetZoneIdMapCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneIdMapCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAPRESP == true) >\
    DEFINE_COMMAND(aceGetZoneIdMapResponseCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneIdMapResponseCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEINFO == true) >\
    DEFINE_COMMAND(aceGetZoneInformationCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneInformationCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFORESP == true) >\
    DEFINE_COMMAND(aceGetZoneInformationResponseCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneInformationResponseCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETPANELSTATUS == true) >\
    DEFINE_COMMAND(aceGetPanelStatusCommand, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetPanelStatusCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true) >\
    DEFINE_COMMAND(aceGetPanelStatusCommandResp, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetPanelStatusCommandRespInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONESTATUS == true) >\
    DEFINE_COMMAND(aceGetZoneStatusCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneStatusCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUS == true) >\
    DEFINE_COMMAND(aceGetZoneStatusRespCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneStatusRespCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANELSTATUSCHANGED == true) >\
    DEFINE_COMMAND(acePanelStatusChangedCommand, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     acePanelStatusChangedCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ZONESTATUSCHANGED == true) >\
    DEFINE_COMMAND(aceZoneStatusChangedCommand, ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceZoneStatusChangedCommandInd),</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETBYPASSZONELIST == true) >\
    DEFINE_COMMAND(aceGetByPassedZoneListCommand, ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetByPassedZoneListCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_SETBYPASSEDZONELIST == true) >\
    DEFINE_COMMAND(aceSetByPassesZoneListCommand, ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceSetByPassedZoneListCommandInd),</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASSRESPONSE == true) >\
    DEFINE_COMMAND(aceByPassResponseCommand, ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceByPassResponseCommandInd)</#if>
/******************************************************************************
                    Types section
******************************************************************************/
/**
 * \brief IAS Zone types
*/
typedef enum
{
  ALL_ZONE_DISARMED = 0X00,
  ONLY_DAY_HOME_ZONES_ARMED = 0X01,
  ONLY_NIGHT_SLEEP_ZONES_ARMED = 0X02,
  ALL_ZONE_ARMED  = 0X03,
  INVALID_ARMCODE = 0x04,
  NOT_READY_TO_ARM_STATE = 0x05,
  ALREADY_DISARMED = 0x06
} ZCL_ArmNotification_t;

typedef enum
{
  DISARM = 0x00,
  ARM_DAY_HOME_ZONES_ONLY = 0x01,
  ARM_NIGHT_SLEEP_ZONES_ONLY = 0x02,
  ARM_ALL_ZONES = 0x03
}ZCL_ArmMode_t;

typedef enum
{
  AUTO_ENROLL_REQUEST_ENABLE = 0x00,
  AUTO_ENROLL_REQUEST_DISABLE = 0x01
} ZCL_ZoneEnrolmentMethods_t;

typedef enum
{
  PANEL_DISARMED =0x00,
  ARMED_STAY = 0x01,
  ARMED_NIGHT = 0x02,
  ARMED_AWAY = 0x03,
  EXIT_DELAY = 0x04,
  ENTRY_DELAY = 0x05,
  NOT_READY_TO_ARM =0x06,
  IN_ALARM =0x07,
  ARMING_STAY = 0x08,
  ARMING_NIGHT = 0x09,
  ARMING_AWAY = 0x0A
}ZCL_PanelStatus_t;

typedef enum
{
  MUTE =0x00,
  DEFAULT_SOUND = 0x01
}ZCL_AudibleNotification_t;

typedef enum
{
  NO_ALARM =0x00,
  BURGLAR = 0x01,
  FIRE = 0X02,
  EMERGENCY = 0X03,
  POLICE_PANIC = 0X04,
  FIRE_PANIC = 0X05,
  EMERGENCY_PANIC = 0X06
}ZCL_AlarmStatus_t;
  
/**
 * \brief IAS ByPass Response
*/
typedef enum
{
  ZONE_BYPASSED = 0X00,
  ZONE_NOT_BYPASSED = 0X01,
  NOT_ALLOWED = 0X02,
  INVALID_ZONE_ID  = 0X03,
  UNKNOWN_ZONE_ID =0X04,
  INVALID_ARM_DISARM_CODE = 0X05
} ZCL_BypassRespType_t;

BEGIN_PACK

///**
// * \brief IAS Zone Cluster Commands/Structures.
//*/

//Arm Commands
typedef struct PACK
{
  ZCL_ArmMode_t armMode;
  uint8_t lengthArmMode;
  char armDisarmCode[ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE];
  uint8_t zoneId;  
} ZCL_ACEArm_t;

typedef struct PACK
{
  ZCL_ArmNotification_t armNotify;
} ZCL_ACEResponseArm_t;

//ByPass Command
typedef struct PACK
{
  uint16_t  getZoneIdMapResponse[ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE];
} ZCL_GetZoneIdMapResponse_t;

//ZoneId Information Commands
typedef struct PACK
{
  uint8_t  zoneId;
} ZCL_GetZoneInformationCommand_t;

typedef struct PACK
{
  uint8_t  zoneId;
  uint16_t zoneType;
  uint64_t zoneAddress;
  uint8_t length;
  uint8_t  zoneLabel[sizeof(ZONE_LABEL)];
} ZCL_GetZoneInformationResp_t;

typedef struct PACK
{
  uint8_t zoneId;
  uint8_t armDisarmCode[ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE];
}bypassList_t;

//Panel Status Commands
typedef struct PACK
{
  ZCL_PanelStatus_t panel_status;
  uint8_t seconds_remaining;
} ZCL_AcePanelStatusChangeCommand_t;

typedef struct PACK
{
 ZCL_PanelStatus_t panel_status;
 uint8_t seconds_remain;
 ZCL_AudibleNotification_t audible_noti;
 ZCL_AlarmStatus_t alarmstatus; 
}ZCL_ACEGetPanelStatusCommandResp_t;

//GetZone Status Commands
typedef struct PACK
{
  uint8_t starting_zone_id;
  uint8_t max_number_zoneids;
  uint8_t zonestatus_maskflag;
  uint16_t zonestatus_mask; 
}ZCL_ACEGetZoneStatusCommand_t;

//Get Panel Status Commands
typedef struct PACK
{
  ZCL_PanelStatus_t panel_status;
  uint8_t seconds_remaining;
  ZCL_AudibleNotification_t audible_noti;
  ZCL_AlarmStatus_t alarmstatus;   
}ZCL_ACEPanelStatusChangedCommand_t;

//Get Zone CHANGED Command
typedef struct PACK
{
  uint8_t zoneid;
  uint16_t zoneStatus;
  ZCL_AudibleNotification_t audible_noti;
  uint8_t zoneLength;
  char zoneLabel[sizeof(ZONE_LABEL)];
}ZCL_ACEZoneStatusChangedCommand_t;

END_PACK

// IAS ACE Cluster Commands
typedef struct
{
<#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_ARM == true) >  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceArmCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload);
  } aceArmCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARMRESP == true) >  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceArmResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload);
  } aceArmResponseCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_BYPASS == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceByPassCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceByPassCommand;  
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_EMERGENCY == true) >  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceEmergencyCommand)(ZCL_Addressing_t *addressing);
  } aceEmergencyCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_FIRE == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceFireCommand)(ZCL_Addressing_t *addressing);
  } aceFireCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_PANIC == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*acePanicCommand)(ZCL_Addressing_t *addressing);
  } acePanicCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEIDMAP == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceGetZoneIdMapCommand)(ZCL_Addressing_t *addressing);
  } aceGetZoneIdMapCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAPRESP == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneIdMapResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload);
  } aceGetZoneIdMapResponseCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEINFO == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceGetZoneInformationCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload);
  } aceGetZoneInformationCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFORESP == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneInformationResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload);
  } aceGetZoneInformationResponseCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETPANELSTATUS == true) >  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetPanelStatusCommand)(ZCL_Addressing_t *addressing);
  } aceGetPanelStatusCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetPanelStatusCommandResp)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload);
  } aceGetPanelStatusCommandResp;  
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONESTATUS == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneStatusCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload);
  } aceGetZoneStatusCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUS == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneStatusRespCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceGetZoneStatusRespCommand; 
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANELSTATUSCHANGED == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*acePanelStatusChangedCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload);
  } acePanelStatusChangedCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ZONESTATUSCHANGED == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceZoneStatusChangedCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload);
  } aceZoneStatusChangedCommand;
</#if><#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETBYPASSZONELIST == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetByPassedZoneListCommand)(ZCL_Addressing_t *addressing);
  } aceGetByPassedZoneListCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_SETBYPASSEDZONELIST == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceSetByPassesZoneListCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceSetByPassesZoneListCommand;
</#if><#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASSRESPONSE == true) >
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceByPassResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceByPassResponseCommand;
</#if>
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_CLIENTCOMMANDCOUNT == 0) >
   /* To Avoid linker error*/
   void *tempPtrE;
</#if>
} ZCL_IasACEClusterCommands_t;

BEGIN_PACK
typedef struct PACK
{
<#if (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_CLUSTERREVISION == true) >  
  struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint16_t            value;
  } clusterVersion;
</#if>  
} ZCL_IasAceClusterServerAttributes_t;
END_PACK

BEGIN_PACK
typedef struct PACK
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_CLUSTERREVISION == true) >  
  struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint16_t            value;
  } clusterVersion;
</#if>
} ZCL_IasAceClusterClientAttributes_t;
END_PACK

#endif /* _ZCLIASZONECLUSTER_H_ */
