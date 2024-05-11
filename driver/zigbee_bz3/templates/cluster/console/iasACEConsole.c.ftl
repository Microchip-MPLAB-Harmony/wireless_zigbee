/*******************************************************************************
  IAS ACE console Source File

  Company:
    Microchip Technology Inc.

  File Name:
   iasACEConsole.c

  Summary:
    This file contains the IAS ACE console implementation.

  Description:
    This file contains the IAS ACE console implementation.
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
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <app_zigbee/zigbee_console/console.h>
#include <bdb/include/bdb.h>
#include <bdb/include/bdbInstallCode.h>
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/zigbee_console/consoleCmds.h>
#include <z3device/ias_ace/include/iasACEZoneCluster.h>
#include <z3device/ias_ace/include/iasACEAceCluster.h>
#include <z3device/common/include/z3Device.h>
#include <systemenvironment/include/sysUtils.h>
#include <pds/include/wlPdsMemIds.h>
#include <zdo/include/zdo.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <z3device/clusters/include/scenesCluster.h>
#include <z3device/clusters/include/onOffCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
/* This value used in ZLL tests to identify non-ZLL Router */
#define TEST_DEVICE_TYPE_HA_ROUTER 0x03U
#define TEMPERATURE_SCALE 100
/******************************************************************************
                    Types section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/
#if COMMISSIONING_COMMANDS_IN_CONSOLE == 1
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
#endif

#if ZCL_COMMANDS_IN_CONSOLE == 1
#if BDB_COMMANDS_IN_CONSOLE == 1
static void processSetInstallCodeCmd(const ScanValue_t *args);
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args);
#endif // ZLO_EXTRA_CLUSTERS_SUPPORT == 1

static void processIdentifyCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processTriggerEffectCmd(const ScanValue_t *args);

static void processIasAceArmCommand(const ScanValue_t *args);
static void processIasAceBypassCommand(const ScanValue_t *args);
static void processIasAceEmergencyommand(const ScanValue_t *args);
static void processIasAceFireCommand(const ScanValue_t *args);
static void processIasAcePanicCommand(const ScanValue_t *args);
static void processIasAceGetZoneIdMapCommand(const ScanValue_t *args);
static void processIasAceGetZoneIdInformationCommand(const ScanValue_t *args);
static void processZoneEnrollRequestCommand(const ScanValue_t *args);
static void processZoneStatusChangeNotificationCommand(const ScanValue_t *args);
static void processZoneStatusChangeCommand(const ScanValue_t *args);
static void processIasAceGetPanelStatusCommand(const ScanValue_t *args);
static void processIasAceGetZoneStatusCommand(const ScanValue_t *args);
static void processGetByPassZoneListCommand(const ScanValue_t *args);

// groups cluster commands
static void processAddGroupCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

/******************************************************************************
                    Local variables section
******************************************************************************/
const ConsoleCommand_t helpCmds[] =
{
  {"help", "",processHelpCmd, "->Show help you're reading now:  help\r\n"},
#if ZDO_COMMANDS_IN_CONSOLE == 1  
  {"zdoHelp", "",processZdoHelpCmd, ""},
#endif
#if COMMISSIONING_COMMANDS_IN_CONSOLE == 1
  {"commissioningHelp", "",processCommissioningHelpCmd, "->Show commissioning help you're reading now:  help\r\n"},
#endif
#if ZCL_COMMANDS_IN_CONSOLE == 1 
  {"zclHelp", "",processZclHelpCmd, "->Show zcl help you're reading now:  help\r\n"},
#endif
#ifdef OTAU_CLIENT
  {"otauHelp", "",processOtauHelpCmd, "->Show OTAU help you're reading now:  help\r\n"},
#endif 
   {0,0,0,0},
};

const ConsoleCommand_t commissioningHelpCmds[]=
{
#if COMMISSIONING_COMMANDS_IN_CONSOLE == 1
  {"invokeCommissioning", "dd", processInvokeCommissioningCmd, "-> invokes commissioning [mode: 1-Touchlink: 2-Steering: 4-Formation: 8-F&B][gid]Invoke one Commissioning method at a time\r\n"},
  {"getAppDeviceType", "", processGetAppDeviceTypeCmd, "-> Request for device type: getAppDeviceType\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"getExtAddr", "", processGetExtAddrCmd, "-> Gets ExtAddr: GetExtAddr\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"getChannel", "", processGetChannelCmd, "-> Returns current channel: getChannel\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"setExtAddr", "dd",processSetExtAddr, "->Set Ext Address:[upper][lower]\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "-> Sets primary channel mask: setPrimaryChannelMask [mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "-> Sets secondary channel mask: setSecondaryChannelMask [mask]\r\n"},
  {"setcca", "dd", processSetCCAModeAndThresholdCmd, "-> Sets CCA Mode and Threshold [cca mode] [threshold]\r\n"},
  {"getcca", "", processGetCCAModeAndThresholdCmd, "-> Gets CCA Mode and Threshold\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"setAllowSteal", "d", processSetAllowStealCmd, "-> Sets setAllowSteal: 0 or 1 <type>\r\n"},
#if BDB_TOUCHLINK_SUPPORT == 1
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, "-> Sets setAllowTLResetToFN: 0 or 1 <type>\r\n"},
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1
  {"SetTLRole", "d", processSetTLRole, "-> Sets TouchLink Role [initiator]\r\n"},
#endif
#endif
#if ZB_COMMISSIONING_ON_STARTUP == 0  
  {"SetFBRole", "d", processSetFBRole, "-> Sets FB Role [initiator]\r\n"},
#endif  
  {"setTCLKExchangeMethod", "d", processSetTCLKExchangeMethodCmd, "-> Sets TCLK Exchange Method [method]\r\n"},
  {"setTCLKMaxRetryAttempts", "d", processSetTCLKMaxRetryAttemptsCmd, "-> Sets TCLK Max Retry Attempts [attempt]\r\n"},
  {"setGlobalKey", "d", processsetGlobalKeyCmd, "-> Sets Key for negative testing[Option]\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
#endif
#endif
   {0,0,0,0},
};

const ConsoleCommand_t zclHelpCmds[]=
{
#if ZCL_COMMANDS_IN_CONSOLE == 1 
  {"readAttribute", "sdddd", processReadAttrCmd, "->Read Attribute for specified cluster: readAttribute [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "->Write Attribute for specified cluster: writeAttribute [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"writeAttributeNoResp", "sddddddd", processWriteAttrNoRespCmd, "->Write Attribute No response for specified cluster: writeAttributeNoResp [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd, "->Sends configure reporting to specified cluster server: configureReporting [addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"configureReportingWRC", "sdddddddd", processConfigureReportingWithReportableChangeCmd, "->Sends configure reporting with reportable Change to specified cluster server: configureReportingWRC [addrMode][addr][ep][clusterId][attrId][type][min][max][repChange]\r\n"},
  {"IasAceArmCommand", "sdddsd", processIasAceArmCommand, "->Sends IASACEAlarmCommand: [addrMode][addr][ep][ArmMode][Arm/Code][ZoneId]\r\n"},
  {"IasAceBypassCommand", "sdddddds", processIasAceBypassCommand, "->Sends IASACEBypassCommand: [addrMode][addr][ep][zone_numbers][zone_ids (cnt<=3)][arm_code_code]\r\n"},
  {"IasAceEmergencyCommand", "sdd", processIasAceEmergencyommand, "->Sends IASACEEmergencyCommand: [addrMode][addr][ep]\r\n"},
  {"IasAceFireCommand", "sdd", processIasAceFireCommand, "->Sends IASACEFireCommand: [addrMode][addr][ep]\r\n"},
  {"IasAcePanicCommand", "sdd", processIasAcePanicCommand, "->Sends IASACEPanicCommand: [addrMode][addr][ep]\r\n"},
  {"IasAceGetZoneIdMapCommand", "sdd", processIasAceGetZoneIdMapCommand, "->Sends IASACEGetZoneIdMapCommand: [addrMode][addr][ep]\r\n"},
  {"IasAceGetZoneIdInformationCommand", "sddd", processIasAceGetZoneIdInformationCommand, "->Sends IASACEGetZoneIdInformationCommand: [addrMode][addr][ep][zone_id]\r\n"},
  {"IasAceGetPanelStatusCommand", "sdd", processIasAceGetPanelStatusCommand, "->Sends IASACEIASACEPanelStatusChangeCommand: [addrMode][addr][ep]\r\n"},
  {"IasAceGetZoneStatusCommand", "sdddddd", processIasAceGetZoneStatusCommand, "->Sends IASACEZoneStatusChangeCommand: [addrMode][addr][ep][starting_zone_id][max_number_zoneids][zonestatus_maskflag][zonestatus_mask]\r\n"},
  {"ZoneEnrollReqCmd", "sddd", processZoneEnrollRequestCommand, "->Sends ZoneEnrollRequestCommand: [addrMode][addr][ep][manuf_code]\r\n"},
  {"ZoneStatusChangeNotifiCmd", "sdddd", processZoneStatusChangeNotificationCommand, "->Sends ZoneStatusChangeNotification Command: [addrMode][addr][ep][zonestatus][ext_status]\r\n"},
  {"ZoneStatusChange", "d", processZoneStatusChangeCommand, "->Chnges Internal Zone Status to Initiate Notifications: [Device_Spec_Bits]\r\n"},
  {"GetByPassZoneList", "sdd", processGetByPassZoneListCommand, "->To get the list of bypass zones: [addrMode][addr][ep]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd,  "[addrMode][addr][ep][gid]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd, "[addrMode][addr][ep][count][gid]*5\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd,"[addrMode][addr][ep]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
#if BDB_TOUCHLINK_SUPPORT == 1  
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1
  {"resetTargetToFN", "", processTargetToFnCmd, "Reset device to FN: resetDeviceToFN\r\n"},
#endif
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
#endif  
  {"SetInstallCodeDevice", "s", processSetInstallCodeCmd, "-> Sets IC [code]\r\n"},
#endif
  #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "-> reset all cluster attributes to factory defaults command:resetToFactoryDefaults [addrMode][addr][ep]\r\n"},
  #endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  {"identify", "sddd", processIdentifyCmd, "->Send Identify command: identify [addrMode][addr][ep][idTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd, "->Send Identify Query command: identifyQuery [addrMode][addr][ep]\r\n"},
  {"triggerEffect", "sdddd", processTriggerEffectCmd, "->Send TriggerEffect command: triggerEffect [addrMode][addr][ep][effectId][effectVariant]"},
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1
  {0,0,0,0},
};

/******************************************************************************
                   Global variables section
******************************************************************************/
bool fbRole = false;
uint8_t srcEp = APP_ENDPOINT_IAS_ACE;

/******************************************************************************
                    Implementation section
******************************************************************************/
#if COMMISSIONING_COMMANDS_IN_CONSOLE == 1
/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("DeviceType = %d\r\n", TEST_DEVICE_TYPE_ZIGBEE_END_DEVICE);
  (void)args;
}

/**************************************************************************//**
\brief Processes request for HA device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("Z3DeviceType = 0x%04x\r\n", APP_Z3DEVICE_ID);
  (void)args;
}
#endif //#if COMMISSIONING_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1 
/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneEnrollRequestCommand(const ScanValue_t *args)
{
  APS_Address_t apsAddr;
  memcpy(&apsAddr.extAddress[0], &args[1].uint64, sizeof(uint64_t));
  zoneEnrollRequestCommand(determineAddressMode(args), apsAddr, args[2].uint8, srcEp, args[3].uint16);
}

/**************************************************************************//**
\brief Processes Restart Network command

\param[in] args - array of command arguments
******************************************************************************/
static void processZoneStatusChangeNotificationCommand(const ScanValue_t *args)
{
  zoneStatusChangeNotificationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceArmCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARM == true) >    
  aceArmCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, args[3].uint8, args[4].str, args[5].uint8);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceBypassCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASS == true) >
  uint8_t zoneId[3] = {0};
  for(uint8_t i = 0; i < args[3].uint8; i++)
    zoneId[i] = args[i+4].uint8;
  aceByPassCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, args[3].uint8, zoneId, args[7].str);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceEmergencyommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_EMERGENCY == true) >
  aceEmergencyCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceFireCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_FIRE == true) >
  aceFireCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}
/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAcePanicCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANIC == true) >
  acePanicCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>   
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceGetZoneIdMapCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAP == true) >
  aceGetZoneIdMapCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceGetZoneIdInformationCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFO == true) >
  aceGetZoneInformationCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, args[3].uint8);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processZoneStatusChangeCommand(const ScanValue_t *args)
{
  zoneStatusChangeCommand(args[0].uint16);
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceGetPanelStatusCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETPANELSTATUS == true) >
  aceGetPanelStatusCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>   
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processIasAceGetZoneStatusCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUS == true) >
  aceGetZoneStatusCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, args[3].uint8, args[4].uint8, args[5].uint8, args[6].uint16);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>  
}

/**************************************************************************//**
\brief ACE Client Commands

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static void processGetByPassZoneListCommand(const ScanValue_t *args)
{
<#if (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETBYPASSZONELIST == true) >
  getByPassZoneListCommand(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>   
}

/**************************************************************************//**
\brief Processes Add group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupCmd(const ScanValue_t *args)
{
  groupsSendAddGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes View group command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewGroupCmd(const ScanValue_t *args)
{
<#if (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_VIEWGROUP == true) >  
  groupsSendViewGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
   srcEp,args[4].uint16);
<#else>
   appSnprintf("Cmd Not Supported\r\n");
</#if>
}

/**************************************************************************//**
\brief Processes Get group membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupMembershipCmd(const ScanValue_t *args)
{
<#if (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_GROUPMEM == true) >  
  uint16_t groupList[5];

  for (uint8_t i = 0; i < 5; i++)
    groupList[i] = args[i+4].uint16;

  groupsSendGetGroupMembership(determineAddressMode(args), args[1].uint16, args[2].uint8,
   srcEp, args[4].uint8, groupList);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
<#if (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_REMOVEGROUP == true) > 
  groupsSendRemoveGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,srcEp,
    args[4].uint16);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>
}

/**************************************************************************//**
\brief Processes Remove all groups command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllGroupsCmd(const ScanValue_t *args)
{
  (void)args;
<#if (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_REMOVEGROUPALL == true) >  
  groupsSendRemoveAllGroups(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>
}

/**************************************************************************//**
\brief Processes Add group if identifying command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args)
{
<#if (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_ADDGROUPIF == true) >  
  groupsSendAddGroupIfIdentifying(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[4].uint16);
<#else>
  appSnprintf("Cmd Not Supported\r\n");
</#if>
}


#if BDB_COMMANDS_IN_CONSOLE == 1
/**************************************************************************//**
\brief InstallCode callback

\param[in] status - status of action
******************************************************************************/
void myICCallback(InstallCode_Configuration_Status_t status)
{
  appSnprintf("Status = %d\r\n", status);
}

/**************************************************************************//**
\brief Processes InstallCode command

\param[in] args - array of command arguments
******************************************************************************/
void processSetInstallCodeCmd(const ScanValue_t *args)
{
  ExtAddr_t devAddr = 0xFFFFFFFFFFFFFFFF;
  uint8_t icode[18];
  hexStrTouint8array(args[0].str, icode, 18U);
  BDB_ConfigureInstallCode(devAddr, icode, myICCallback);
  (void)args;
}
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

/*****************************************************************************/
//                      BASIC CLUSTER COMMANDS
/*****************************************************************************/
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

/**************************************************************************//**
\brief Processes reset To factory defaults command

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args)
{
  basicResetToFactoryDefaultsCommand(determineAddressMode(args), args[1].uint16,
    args[2].uint8, srcEp);
}

#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

/**************************************************************************//**
\brief Processes Identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  identifySendIdentify(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Identify Query command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyQueryCmd(const ScanValue_t *args)
{
  identifySendIdentifyQuery(determineAddressMode(args), args[1].uint16,
    args[2].uint8, srcEp);
}

/**************************************************************************//**
\brief Processes Trigger Effect command

\param[in] args - array of command arguments
******************************************************************************/
static void processTriggerEffectCmd(const ScanValue_t *args)
{
  identifySendTriggerEffect(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint8);
}

#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

#endif // APP_ENABLE_CONSOLE == 1

#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasAceConsole.c
