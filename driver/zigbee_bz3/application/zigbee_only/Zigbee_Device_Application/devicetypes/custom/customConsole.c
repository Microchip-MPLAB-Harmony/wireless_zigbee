/*******************************************************************************
  Custom Console cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customConsole.c

  Summary:
    This file contains the Custom Console Cluster implementation.

  Description:
    This file contains the Custom Console Cluster implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE)
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <console.h>
#include <consoleCmds.h>
#include <haClusters.h>
#include <z3Device.h>
#include <sysUtils.h>
#include <wlPdsMemIds.h>
#include <zdo.h>
#include <z3Device.h>
#include <custom/include/custom.h>
#include <zcl.h>
#include <bdb.h>
#include <ZLL/N_LinkTarget/include/N_LinkTarget_Bindings.h>
#include <zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget.h>
#include <bdbInstallCode.h>
#include <basicCluster.h>
#include <custom/include/customBasicCluster.h>
#include <custom/include/customGroupsCluster.h>
#include <custom/include/customIdentifyCluster.h>
#include <custom/include/customOnOffCluster.h>
#include <custom/include/customLevelControlCluster.h>
#include <custom/include/customCommissioningCluster.h>
#include <groupsCluster.h>
#include <identifyCluster.h>
#include <onOffCluster.h>
#include <z3device/clusters/include/commissioningCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
extern BDB_InvokeCommissioningReq_t AppbdbCommissioningreq;
/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);

// groups cluster commands
static void processAddGroupCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
#if BDB_COMMANDS_IN_CONSOLE == 1
static void processFormAndSteerCmd(const ScanValue_t *args);
static void processFormSteerAndFBCmd(const ScanValue_t *args);
static void processSetInstallCodeCmd(const ScanValue_t *args);
static void processSetInstallCodeDeviceCmd(const ScanValue_t *args);
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args);
#endif // ZLO_EXTRA_CLUSTERS_SUPPORT == 1

static void processReadOnOffAttrVal(const ScanValue_t *args);
static void processReadCurrentLevelAttrVal(const ScanValue_t *args);
static void processIdentifyCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processReadOnOffAttrVal(const ScanValue_t *args);

static void processSendEndpointInfoCmd(const ScanValue_t *args);
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

/******************************************************************************
                    Local variables section
******************************************************************************/
const ConsoleCommand_t helpCmds[] =
{
  {"help", "",processHelpCmd, ""},
  {"zdoHelp", "",processZdoHelpCmd, ""},
  {"commissioningHelp", "",processCommissioningHelpCmd, ""},
  {"zclHelp", "",processZclHelpCmd, ""},
#ifdef OTAU_CLIENT
  {"otauHelp", "",processOtauHelpCmd, ""},
#endif
#if APP_ZGP_DEVICE_TYPE == APP_ZGP_DEVICE_TYPE_COMBO_BASIC
  {"zgpHelp", "",processZgpHelpCmd, ""},
#endif
  {0,0,0,0},
};

PROGMEM_DECLARE(ConsoleCommand_t commissioningHelpCmds)[]=
{
  {"invokeCommissioning", "dd", processInvokeCommissioningCmd, ""},
  {"getAppDeviceType", "", processGetAppDeviceTypeCmd, ""},
  {"getDeviceType", "", processGetDeviceTypeCmd, ""},
  {"getExtAddr", "", processGetExtAddrCmd, ""},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, ""},
  {"getChannel", "", processGetChannelCmd, ""},
  {"powerOff", "", processPseudoPowerOffCmd, ""},
  {"reset", "", processResetCmd, ""},
  {"resetToFN", "", processResetToFactoryFreshCmd, ""},
  {"setExtAddr", "dd",processSetExtAddr, "[upper][lower]\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "[mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "[mask]\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"formAndSteer", "", processFormAndSteerCmd, ""},
  {"formSteerAndFB", "", processFormSteerAndFBCmd, ""},
  {"setAllowSteal", "d", processSetAllowStealCmd, "-> Set 0 or 1 <type>\r\n"},
  {"SetInstallCodeDevice", "s", processSetInstallCodeDeviceCmd, "[code]\r\n"},
  {"SetInstallCode", "dds", processSetInstallCodeCmd, "[extAddr][code]\r\n"},
#if BDB_TOUCHLINK_SUPPORT == 1
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, ""},
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1
  {"SetTLRole", "d", processSetTLRole, "Touchlink Role:1-Initiator,0-Target[initiator]"},
#endif
#endif
#if ZB_COMMISSIONING_ON_STARTUP == 0
  {"SetFBRole", "d", processSetFBRole, "FindingAndBinding Role 1-Initiator,0-Target[initiator]\r\n"},
#endif
  {"setTCLKExchangeMethod", "d", processSetTCLKExchangeMethodCmd, "[method]\r\n"},
  {"setTCLKMaxRetryAttempts", "d", processSetTCLKMaxRetryAttemptsCmd, "[attempt]\r\n"},
  {"setGlobalKey", "d", processsetGlobalKeyCmd, "[Option]\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "[dur]\r\n"},
#endif
   {0,0,0,0},
};

PROGMEM_DECLARE(ConsoleCommand_t zclHelpCmds)[]=
{
  {"readAttribute", "sdddd", processReadAttrCmd, "[addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "[addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"writeAttributeNoResp", "sddddddd", processWriteAttrNoRespCmd, "[addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd, "[addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"configureReportingWRC", "sdddddddd", processConfigureReportingWithReportableChangeCmd, "With Reportable Change [addrMode][addr][ep][clusterId][attrId][type][min][max][repChange]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd,  "[addrMode][addr][ep][gid]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd, "[addrMode][addr][ep][count][gid]*5\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd,"[addrMode][addr][ep]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "[addrMode][addr][ep][gid]\r\n"},

#if BDB_COMMANDS_IN_CONSOLE == 1
#if BDB_TOUCHLINK_SUPPORT == 1
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1
  {"resetTargetToFN", "", processTargetToFnCmd, ""},
#endif
  {"setTargetType", "d", processSetTargetTypeCmd, ""},
#endif
#endif
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "[addrMode][addr][ep]\r\n"},
#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  #if ZCL_COMMANDS_IN_CONSOLE == 1
  {"onOffQ", "", processReadOnOffAttrVal, ""},
  {"currentLevelQ", "", processReadCurrentLevelAttrVal, ""},
  {"identify", "sddd", processIdentifyCmd, "[addrMode][addr][ep][idTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd, "[addrMode][addr][ep]\r\n"},
  {"sendEndpointInfo", "dd", processSendEndpointInfoCmd, "[shortAddr][dstEp]\r\n"},
  #endif // #if ZCL_COMMANDS_IN_CONSOLE == 1
  {0,0,0,0},
};

#if BDB_COMMANDS_IN_CONSOLE == 1
static HAL_AppTimer_t aTimer;
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

/******************************************************************************
                   Global variables section
******************************************************************************/
bool doFindAndBind = false;
bool fbRole = false;
ScanValue_t local;
uint8_t srcEp = APP_ENDPOINT_CUSTOM;

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
#if (APP_ZGP_DEVICE_TYPE == APP_ZGP_DEVICE_TYPE_COMBO_BASIC)
#if (APP_ENABLE_ZGP_CERTIFICATION_EXTENSION == 1)
  appSnprintf("DeviceType = %d\r\n", TEST_DEVICE_TYPE_ZGP_TH);
#else
  appSnprintf("DeviceType = %d\r\n", TEST_DEVICE_TYPE_ZGP_COMBO_BASIC);
#endif
#else
  appSnprintf("DeviceType = %d\r\n", TEST_DEVICE_TYPE_ZIGBEE_ROUTER);
#endif
  (void)args;
}

/**************************************************************************//**
\brief Processes request for HA device type obtaining

\param[in] args - array of command arguments
+******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("Z3DeviceType = 0x%04x\r\n", APP_Z3DEVICE_ID);
  (void)args;
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
  groupsSendViewGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
   srcEp,args[3].uint16);
}

/**************************************************************************//**
\brief Processes Get group membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupMembershipCmd(const ScanValue_t *args)
{
  uint16_t groupList[5];

  for (uint8_t i = 0; i < 5; i++)
    groupList[i] = args[i+4].uint16;

  groupsSendGetGroupMembership(determineAddressMode(args), args[1].uint16, args[2].uint8,
   srcEp, args[3].uint8, groupList);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  groupsSendRemoveGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Remove all groups command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllGroupsCmd(const ScanValue_t *args)
{
  (void)args;
  groupsSendRemoveAllGroups(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
}

/**************************************************************************//**
\brief Processes Add group if identifying command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args)
{
  groupsSendAddGroupIfIdentifying(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

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

#if BDB_COMMANDS_IN_CONSOLE == 1

/**************************************************************************//**
\brief Form And Steer1 callback

\param[in] conf - pointer to confirmation structure
******************************************************************************/
static void Callback_FormAndSteer1(BDB_InvokeCommissioningConf_t *conf)
{
  appSnprintf("CommissioningStatus = %d\r\n", conf->status);
}

/**************************************************************************//**
\brief Timer callback
******************************************************************************/
void aTimerFired(void)
{
  if (doFindAndBind)
  {
    local.uint8 = 10;
  }
  else
  {
    local.uint8 = 2;
  }
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(local.uint8);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer1;
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}

/**************************************************************************//**
\brief Form And Steer callback

\param[in] conf - pointer to confirmation structure
******************************************************************************/
static void Callback_FormAndSteer(BDB_InvokeCommissioningConf_t *conf)
{
  aTimer.interval = 5;
  aTimer.mode     = TIMER_ONE_SHOT_MODE;
  aTimer.callback = aTimerFired;
  HAL_StartAppTimer(&aTimer);
}

/**************************************************************************//**
\brief Process Form And Steer command

\param[in] args - array of command arguments
******************************************************************************/
static void processFormAndSteerCmd(const ScanValue_t *args)
{
  doFindAndBind = false;
  local.uint8 = 4;
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(local.uint8);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer;
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}

/**************************************************************************//**
\brief Process Form And Steer and FB command

\param[in] args - array of command arguments
******************************************************************************/
static void processFormSteerAndFBCmd(const ScanValue_t *args)
{
  doFindAndBind = true;
  local.uint8 = 4;
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(local.uint8);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer;
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}

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

/**************************************************************************//**
\brief Processes InstallCode command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetInstallCodeDeviceCmd(const ScanValue_t *args)
{
  ExtAddr_t devAddr = 0xFFFFFFFFFFFFFFFF;
  uint8_t icode[18];
  hexStrTouint8array(args[0].str, icode, 18U);
  BDB_ConfigureInstallCode(devAddr, icode, myICCallback);
  (void)args;
}

#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1
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
\brief Processes Read OnOff Attr Val command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadOnOffAttrVal(const ScanValue_t *args)
{
  appSnprintf("%d\r\n", customOnOffClusterServerAttributes.onOff.value);
}
/**************************************************************************//**
\brief Processes Read Current Level Attr Val command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadCurrentLevelAttrVal(const ScanValue_t *args)
{
  appSnprintf("%d\r\n", customLevelControlClusterServerAttributes.currentLevel.value);
}

/**************************************************************************//**
\brief Processes Send Endpoint Info command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendEndpointInfoCmd(const ScanValue_t *args)
{
  commissioningSendEndpointInformation(args[0].uint16, args[1].uint8, srcEp);
}
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

#endif // APP_ENABLE_CONSOLE == 1

#endif // #if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE

// eof customConsole.c
