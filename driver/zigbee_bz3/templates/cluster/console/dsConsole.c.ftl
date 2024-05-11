/*******************************************************************************
  Dimmer Switch console Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dsConsole.c

  Summary:
    This file contains the Dimmer Switch console implementation.

  Description:
    This file contains the Dimmer Switch console implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMER_SWITCH)
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <console.h>
#include <consoleCmds.h>
#include <haClusters.h>
#include <dsOnOffCluster.h>
#include <dsLevelControlCluster.h>
#include <dsBasicCluster.h>
#include <dsIdentifyCluster.h>
#include <dsGroupsCluster.h>
#include <dsScenesCluster.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <resetReason.h>
#include <z3Device.h>
#include <pdsDataServer.h>
#include <zcl.h>
#include <bdb.h>
#include <zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget_Bindings.h>
#include <zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget.h>
#include <bdbInstallCode.h>
#include <groupsCluster.h>
#include <scenesCluster.h>
#include <onOffCluster.h>
#include <levelControlCluster.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);

// Common On/Off command
static void processOnOffToggleCmd(const ScanValue_t *args);

// GROUPS CLUSTER
static void processAddGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);


#if BDB_COMMANDS_IN_CONSOLE == 1
static void processSetInstallCodeCmd(const ScanValue_t *args);
static void processSetInstallCodeDeviceCmd(const ScanValue_t *args);
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1

// BASIC CLUSTER
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args);
#endif // ZLO_EXTRA_CLUSTERS_SUPPORT == 1

// IDENTIFY CLUSTER
static void processIdentifyCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processTriggerEffectCmd(const ScanValue_t *args);

// ON/OFF CLUSTER
static void processOffWithEffectCmd(const ScanValue_t *args);
static void processOnWithRecallGlobalSceneCmd(const ScanValue_t *args);
static void processOnWithTimedOffCmd(const ScanValue_t *args);

// LEVEL CONTROL CLUSTER
static void processMoveToLevelCmd(const ScanValue_t *args);
static void processMoveCmd(const ScanValue_t *args);
static void processStepCmd(const ScanValue_t *args);
static void processStopCmd(const ScanValue_t *args);

// SCENES CLUSTER
static void processAddSceneToDimmableLightCmd(const ScanValue_t *args);
static void processViewSceneCmd(const ScanValue_t *args);
static void processRemoveSceneCmd(const ScanValue_t *args);
static void processRemoveAllScenesCmd(const ScanValue_t *args);
static void processStoreSceneCmd(const ScanValue_t *args);
static void processRecallSceneCmd(const ScanValue_t *args);
static void processGetSceneMembershipCmd(const ScanValue_t *args);

#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

/******************************************************************************
                    Local variables section
******************************************************************************/
const ConsoleCommand_t helpCmds[] =
{
  {"help", "",processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"zdoHelp", "",processZdoHelpCmd, "->Show zdo help you're reading now:  help\r\n"},
  {"commissioningHelp", "",processCommissioningHelpCmd, "->Show commissioning help you're reading now:  help\r\n"},
  {"zclHelp", "",processZclHelpCmd, "->Show zcl help you're reading now:  help\r\n"},
   {0,0,0,0},
};

const ConsoleCommand_t commissioningHelpCmds[]=
{
  {"invokeCommissioning", "dd", processInvokeCommissioningCmd, "-> invokes commissioning [mode][gid]\r\n"},
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
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"setAllowSteal", "d", processSetAllowStealCmd, "-> Sets setAllowSteal: 0 or 1 <type>\r\n"},
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, "-> Sets setAllowTLResetToFN: 0 or 1 <type>\r\n"},
  {"SetInstallCodeDevice", "s", processSetInstallCodeDeviceCmd, "-> Sets IC [code]\r\n"},
  {"SetInstallCode", "dds", processSetInstallCodeCmd, "-> Sets IC [extAddr][code]\r\n"},
#if BDB_TOUCHLINK_SUPPORT == 1
  {"SetTLRole", "d", processSetTLRole, "-> Sets TouchLink Role [initiator]\r\n"},
#endif
#if BDB_FINDINGBINDING_INITIATOR_TARGET_PARALLEL_EXECUTION == 0
  {"SetFBRole", "d", processSetFBRole, "-> Sets FB Role [initiator]\r\n"},
#endif
  {"setTCLKExchangeMethod", "d", processSetTCLKExchangeMethodCmd, "-> Sets TCLK Exchange Method [method]\r\n"},
  {"setTCLKMaxRetryAttempts", "d", processSetTCLKMaxRetryAttemptsCmd, "-> Sets TCLK Max Retry Attempts [attempt]\r\n"},
#endif
   {0,0,0,0},
};

const ConsoleCommand_t zclHelpCmds[]=
{
    // GROUPS CLUSTER
  {"onOff", "sdds", processOnOffToggleCmd, "->Sends On/Off command: onOff [addrMode][addr][ep][onOff]: -on for On, -off for Off]\r\n"},
  {"readAttribute", "sdddd", processReadAttrCmd, "->Read Attribute for specified cluster: readAttribute [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "->Write Attribute for specified cluster: writeAttribute [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"writeAttributeNoResp", "sddddddd", processWriteAttrNoRespCmd, "->Write Attribute No response for specified cluster: writeAttributeNoResp [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd, "->Sends configure reporting to specified cluster server: configureReporting [addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"configureReportingWRC", "sdddddddd", processConfigureReportingWithReportableChangeCmd, "->Sends configure reporting with reportable Change to specified cluster server: configureReportingWRC [addrMode][addr][ep][clusterId][attrId][type][min][max][repChange]\r\n"},
  {"readReporting", "sdddd", processReadReportingCmd, "->Sends Read reporting to specified cluster server: readReporting [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "->Send Add Group command: addGroup [addrMode][addr][ep][gid]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd,  "->Send Add Group If Identifying command:addGroupIfIdentifying [addrMode][addr][ep][gid]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd, "->Send Get Group Membership command: getGroupMembership [addrMode][addr][ep][count][gid]*5\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd,"->Send Remove All Group command: removeAllGroup[addrMode][addr][ep]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "->Send Remove Group command: removeGroup [addrMode][addr][ep][gid]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "->Send View Group command: viewGroup [addrMode][addr][ep][gid]\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
#if BDB_TOUCHLINK_SUPPORT == 1
  {"resetTargetToFN", "", processTargetToFnCmd, "Reset device to FN: resetDeviceToFN\r\n"},
#endif
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
#endif
#if ZCL_COMMANDS_IN_CONSOLE == 1
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "-> reset all cluster attributes to factory defaults command:resetToFactoryDefaults [addrMode][addr][ep]\r\n"},
#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

  // BASIC CLUSTER

  // IDENTIFY CLUSTER
  {"identify", "sddd", processIdentifyCmd, "->Send Identify command: identify [addrMode][addr][ep][idTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd, "->Send Identify Query command: identifyQuery [addrMode][addr][ep]\r\n"},
  {"triggerEffect", "sdddd", processTriggerEffectCmd, "-> Sends trigger effect command: triggerEffect [addrMode][addr][ep][eftId][eftVar]"},

  // ON/OFF CLUSTER
  {"offWithEffect", "sdddd", processOffWithEffectCmd,  "->Sends off with effect command: offWithEffect [addrMode][addr][ep][effectId][effectVariant]\r\n"},
  {"onWithRecallGlobalScene", "sdd", processOnWithRecallGlobalSceneCmd,  "->Sends on with Recall Global scene command: onWithRecallGlobalScene [addrMode][addr][ep]\r\n"},
  {"onWithTimedOff", "sddddd", processOnWithTimedOffCmd, "->Sends on with Timed off command: [addrMode][mode][ep][onOffCtrl][onTime][offWaitTime]\r\n"},

  // LEVEL CONTROL CLUSTER
  {"moveToLevel", "sddddddd", processMoveToLevelCmd, "->Send Move To Level (with On/Off) command: moveToLevel [addrMode][addr][ep][lvl][trTime][onOff][optMask][optOvrd]\r\n"},
  {"move", "sddddddd", processMoveCmd, "->Send Move (with On/Off) command: move [addrMode][addr][ep][mode][rate][onOff][optMask][optOvrd]\r\n"},
  {"step", "sdddddddd", processStepCmd, "->Send Step (with On/Off) command: step [addrMode][addr][ep][mode][sz][trTime][onOff][optMask][optOvrd]\r\n"},
  {"stop", "sddddd", processStopCmd, "->Send Stop (with On/Off) command: stop [addrMode][addr][ep][onOff][optMask][optOvrd]\r\n"},

  // SCENES CLUSTER
  {"addSceneToDL", "sddddddd", processAddSceneToDimmableLightCmd, "->Send Add Scene command to Dimmable Light: addScene [addrMode][addr][ep][gid][sid][trTime][onOff][level]\r\n"},
  {"getSceneMembership", "sddd", processGetSceneMembershipCmd, "->Send Get Scene Membership command: getSceneMembership [addrMode][addr][ep][gid]\r\n"},
  {"recallScene", "sdddd", processRecallSceneCmd, "->Send Recall Scene command: recallScene [addrMode][addr][ep][gid][sid]\r\n"},
  {"removeAllScenes", "sddd", processRemoveAllScenesCmd, "->Send Remove All Scenes command: removeAllScenes [addrMode][addr][ep][gid]\r\n"},
  {"removeScene", "sdddd", processRemoveSceneCmd, "->Send Remove Scene command: removeScene [addrMode][addr][ep][gid][sid]\r\n"},
  {"storeScene", "sdddd", processStoreSceneCmd, "->Send Store Scene command: storeScene [addrMode][addr][ep][gid][sid]\r\n"},
  {"viewScene", "sdddd", processViewSceneCmd, "->Send View Scene command: viewScene [addrMode][addr][ep][gid][sid]\r\n"},
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1
  {0,0,0,0},
};

/******************************************************************************
                   Global variables section
******************************************************************************/
bool fbRole = true;
uint8_t srcEp = APP_ENDPOINT_DIMMER_SWITCH;

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Processes On/Off/Toggle command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnOffToggleCmd(const ScanValue_t *args)
{
  uint8_t command;

  if (!memcmp("-on", args[3].str, 3))
    command = 1;
  else if (!memcmp("-toggle", args[3].str, 7))
    command = 2;
  else
    command = 0;

  onOffSendOnOffToggle(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, command);
}

/*****************************************************************************/
//                      GROUPS CLUSTER COMMANDS
/*****************************************************************************/

/**************************************************************************//**
\brief Processes Add group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupCmd(const ScanValue_t *args)
{
  groupsSendAddGroup(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes View group command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewGroupCmd(const ScanValue_t *args)
{
  groupsSendViewGroup(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Get group membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupMembershipCmd(const ScanValue_t *args)
{
  uint16_t groupList[5];

  for (uint8_t i = 0; i < 5; i++)
  {
    groupList[i] = args[i+4].uint16;
  }

  groupsSendGetGroupMembership(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, groupList);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  groupsSendRemoveGroup(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
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

#if BDB_COMMANDS_IN_CONSOLE == 1
/**************************************************************************//**
\brief InstallCode callback

\param[in] status - status of action
******************************************************************************/
void myICCallback(InstallCode_Configuration_Status_t status)
{
  LOG_STRING(cStr, "Status = %d\r\n");
  appSnprintf(cStr, status);
}

/**************************************************************************//**
\brief Processes InstallCode command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetInstallCodeCmd(const ScanValue_t *args)
{
  uint8_t icode[18];
  ExtAddr_t extAddr = ((uint64_t)args[0].uint32 << 32);
  extAddr |= args[1].uint32;
  hexStrTouint8array(args[2].str, icode, 18U);
  BDB_ConfigureInstallCode(extAddr, icode, myICCallback);
  (void)args;
}

/**************************************************************************//**
\brief Processes InstallCode command

\param[in] args - array of command arguments
******************************************************************************/
void processSetInstallCodeDeviceCmd(const ScanValue_t *args)
{
  ExtAddr_t devAddr = 0xFFFFFFFFFFFFFFFF;
  uint8_t icode[18];
  hexStrTouint8array(args[0].str, icode, 18U);
  BDB_ConfigureInstallCode(devAddr, icode, myICCallback);
  (void)args;
}

#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

/**************************************************************************//**
\brief Processes request for HA device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "Z3DeviceType = 0x%04x\r\n");
  appSnprintf(deviceFnStatusStr, APP_Z3DEVICE_ID);
  (void)args;
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  LOG_STRING(deviceFnStatusStr, "DeviceType = %d\r\n");
  appSnprintf(deviceFnStatusStr, TEST_DEVICE_TYPE_ZIGBEE_END_DEVICE);
  (void)args;
}

#if ZCL_COMMANDS_IN_CONSOLE == 1
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
  basicResetToFactoryDefaultsCommand(determineAddressMode(args),args[1].uint16,
    args[2].uint8, srcEp);
}

#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

/*****************************************************************************/
//                      IDENTIFY CLUSTER COMMANDS
/*****************************************************************************/
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
  identifySendIdentifyQuery(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
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

/*****************************************************************************/
//                      ON/OFF CLUSTER COMMANDS
/*****************************************************************************/
/**************************************************************************//**
\brief Processes Off with Effect command

\param[in] args - array of command arguments
******************************************************************************/
static void processOffWithEffectCmd(const ScanValue_t *args)
{
  onOffSendOffWithEffect(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint8);
}

/**************************************************************************//**
\brief Processes On with recall global scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnWithRecallGlobalSceneCmd(const ScanValue_t *args)
{
  onOffSendOnWithRecallGlobalScene(determineAddressMode(args), args[1].uint16,
    args[2].uint8, srcEp);
}

/**************************************************************************//**
\brief Processes On with timed off command

\param[in] args - array of command arguments
******************************************************************************/
static void processOnWithTimedOffCmd(const ScanValue_t *args)
{
  onOffSendOnWithTimedOff(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint16, args[5].uint16);
}

/*****************************************************************************/
//                      LEVEL CONTROL CLUSTER COMMANDS
/*****************************************************************************/
/**************************************************************************//**
\brief Processes Move to level command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToLevelCmd(const ScanValue_t *args)
{
  levelControlSendMoveToLevel(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
                              args[3].uint8, args[4].uint16, args[5].uint8, args[6].uint8, args[7].uint8);
}

/**************************************************************************//**
\brief Processes Move command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveCmd(const ScanValue_t *args)
{
  levelControlSendMove(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint8, args[5].uint8, args[6].uint8, args[7].uint8);
}

/**************************************************************************//**
\brief Processes Step command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepCmd(const ScanValue_t *args)
{
  levelControlSendStep(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint8, args[5].uint16, args[6].uint8, args[7].uint8, args[8].uint8);
}

/**************************************************************************//**
\brief Processes Stop command

\param[in] args - array of command arguments
******************************************************************************/
static void processStopCmd(const ScanValue_t *args)
{
  levelControlSendStop(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint8, args[5].uint8);
}

/*****************************************************************************/
//                      SCENES CLUSTER COMMANDS
/*****************************************************************************/
/**************************************************************************//**
\brief Processes Add Scene command to DL

\param[in] args - array of command arguments
******************************************************************************/
static void processAddSceneToDimmableLightCmd(const ScanValue_t *args)
{
  scenesSendAddSceneToDimmableLight(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
                                    args[3].uint16, args[4].uint8, args[5].uint16, args[6].uint8, args[7].uint8);
}

/**************************************************************************//**
\brief Processes View Scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewSceneCmd(const ScanValue_t *args)
{
  scenesSendViewScene(determineAddressMode(args), args[1].uint16, args[2].uint8,  srcEp,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveSceneCmd(const ScanValue_t *args)
{
  scenesSendRemoveScene(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Remove all scenes command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllScenesCmd(const ScanValue_t *args)
{
  scenesSendRemoveAllScenes(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Store scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processStoreSceneCmd(const ScanValue_t *args)
{
  scenesSendStoreScene(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Recall scene command

\param[in] args - array of command arguments
******************************************************************************/
static void processRecallSceneCmd(const ScanValue_t *args)
{
  scenesSendRecallScene(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16, args[4].uint8);
}

/**************************************************************************//**
\brief Processes Get scene membership command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetSceneMembershipCmd(const ScanValue_t *args)
{
  scenesSendGetSceneMembership(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16);
}

#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

#endif // APP_ENABLE_CONSOLE == 1

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH


// eof dsConsole.c
