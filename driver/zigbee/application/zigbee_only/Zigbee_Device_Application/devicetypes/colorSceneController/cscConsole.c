/*******************************************************************************
  Color Scene Controller console Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cscConsole.c

  Summary:
    This file contains the Color Scene Controller console implementation.

  Description:
    This file contains the Color Scene Controller console implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/zigbee_console/consoleCmds.h>
#include <z3device/colorSceneController/include/cscOnOffCluster.h>
#include <z3device/colorSceneController/include/cscLevelControlCluster.h>
#include <z3device/colorSceneController/include/cscBasicCluster.h>
#include <z3device/colorSceneController/include/cscIdentifyCluster.h>
#include <z3device/colorSceneController/include/cscGroupsCluster.h>
#include <z3device/colorSceneController/include/cscScenesCluster.h>
#include <z3device/colorSceneController/include/cscCommissioningCluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <bdb/include/bdb.h>
#include <bdb/include/bdbInstallCode.h>
#include <zcl/clusters/include/groupsCluster.h>
#include <z3device/clusters/include/scenesCluster.h>
#include <z3device/clusters/include/onOffCluster.h>
#include <z3device/clusters/include/levelControlCluster.h>
#include <z3device/clusters/include/colorControlCluster.h>
#include <z3device/clusters/include/commissioningCluster.h>
#include <z3device/common/include/z3Device.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);

// Common On/Off command
static void processOnOffToggleCmd(const ScanValue_t *args);

#if BDB_COMMANDS_IN_CONSOLE == 1
static void processSetbdbJoinUsesInstallCodeKey(const ScanValue_t *args);
static void processSetInstallCodeDeviceCmd(const ScanValue_t *args);
#endif // BDB_COMMANDS_IN_CONSOLE == 1

// GROUPS CLUSTER
static void processAddGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);

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
static void processEnhancedAddSceneCmd(const ScanValue_t *args);
static void processEnhancedViewSceneCmd(const ScanValue_t *args);
static void processCopySceneCmd(const ScanValue_t *args);

// TOUCHLINK COMMISSIONING CLUSTER
static void processGetEndpointListCmd(const ScanValue_t *args);
static void processGetGroupIdentifiersCmd(const ScanValue_t *args);
static void processSendEndpointInfoCmd(const ScanValue_t *args);

// COLOR CONTROL CLUSTER
static void processMoveToHueCmd(const ScanValue_t *args);
static void processMoveHueCmd(const ScanValue_t *args);
static void processStepHueCmd(const ScanValue_t *args);
static void processMoveToSaturationCmd(const ScanValue_t *args);
static void processMoveSaturationCmd(const ScanValue_t *args);
static void processStepSaturationCmd(const ScanValue_t *args);
static void processMoveToHueAndSaturationCmd(const ScanValue_t *args);
static void processMoveToColorCmd(const ScanValue_t *args);
static void processMoveColorCmd(const ScanValue_t *args);
static void processStepColorCmd(const ScanValue_t *args);
static void processMoveToColorTemperatureCmd(const ScanValue_t *args);
static void processEnhancedMoveToHueCmd(const ScanValue_t *args);
static void processEnhancedMoveHueCmd(const ScanValue_t *args);
static void processEnhancedStepHueCmd(const ScanValue_t *args);
static void processEnhancedMoveToHueAndSaturationCmd(const ScanValue_t *args);
static void processColorLoopSetCmd(const ScanValue_t *args);
static void processStopMoveStepCmd(const ScanValue_t *args);
static void processMoveColorTemperatureCmd(const ScanValue_t *args);
static void processStepColorTemperatureCmd(const ScanValue_t *args);
#endif // ZCL_COMMANDS_IN_CONSOLE == 1

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
  {"otauHelp", "",processOtauHelpCmd, "->Show OTAU help you're reading now:  help\r\n"},
#endif
   {0,0,0,0},
};

const ConsoleCommand_t commissioningHelpCmds[]=
{
  {"invokeCommissioning", "dd", processInvokeCommissioningCmd, "[mode: 1-Touchlink: 2-Steering: 4-Formation: 8-F&B][gid]Invoke one Commissioning method at a time\r\n"}, 
  {"getAppDeviceType", "", processGetAppDeviceTypeCmd, ""},
  {"getDeviceType", "", processGetDeviceTypeCmd, ""},
  {"getExtAddr", "", processGetExtAddrCmd, ""},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, ""},
  {"getChannel", "", processGetChannelCmd, ""},
  {"setExtAddr", "dd",processSetExtAddr, "[upper][lower]\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "[mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "[mask]\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, ""},  
  {"reset", "", processResetCmd, ""},
  {"resetToFN", "", processResetToFactoryFreshCmd, ""},
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"formAndSteer", "", processFormAndSteerCmd, ""},
  {"formSteerAndFB", "", processFormSteerAndFBCmd, ""},
  {"setAllowSteal", "d", processSetAllowStealCmd, "<type>\r\n"},
#if BDB_TOUCHLINK_SUPPORT == 1
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, "<type>\r\n"},
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1
  {"SetTLRole", "d", processSetTLRole, "Touchlink Role:1-Initiator,0-Target [initiator]\r\n"},
#endif
#endif
#if ZB_COMMISSIONING_ON_STARTUP == 0
  {"SetFBRole", "d", processSetFBRole, "FindingAndBinding Role 1-Initiator,0-Target [initiator]\r\n"},
#endif
  {"setGlobalKey", "d", processsetGlobalKeyCmd, "[Option]\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "[dur]\r\n"},
#endif
   {0,0,0,0},
};

const ConsoleCommand_t zclHelpCmds[]=
{
  {"readAttribute", "sdddd", processReadAttrCmd, "[addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "[addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"writeAttributeNoResp", "sddddddd", processWriteAttrNoRespCmd, "[addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd, "[addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"configureReportingWRC", "sdddddddd", processConfigureReportingWithReportableChangeCmd, "With Reportable Change [addrMode][addr][ep][clusterId][attrId][type][min][max][repChange]\r\n"},
  {"readReporting", "sdddd", processReadReportingCmd, "[addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"sendEndpointInfo", "dd"  , processSendEndpointInfoCmd, "[shortAddr][ep]\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
#if BDB_TOUCHLINK_SUPPORT == 1 
#if BDB_TOUCHLINK_INITIATOR_SUPPORT == 1 
  {"resetTargetToFN", "", processTargetToFnCmd, ""},
#endif
  {"setTargetType", "d", processSetTargetTypeCmd, " <type>\r\n"},
#endif  
  {"SetbdbJoinUsesInstallCodeKey", "d", processSetbdbJoinUsesInstallCodeKey, "[value]\r\n"},
  {"SetInstallCodeDevice", "s", processSetInstallCodeDeviceCmd, "->[code]\r\n"},
#endif
#if ZCL_COMMANDS_IN_CONSOLE == 1
  // BASIC CLUSTER
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "-> reset all cluster attributes to factory defaults command: [addrMode][addr][ep]\r\n"},
#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  // Group Clusters
  {"addGroup", "sddd", processAddGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd,  "[addrMode][addr][ep][gid]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd, "[addrMode][addr][ep][count][gid]*5\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd,"[addrMode][addr][ep]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"getGroupIdentifiers", "ddd" , processGetGroupIdentifiersCmd, "[shortAddr][ep][startIndex]\r\n"},
  // IDENTIFY CLUSTER
  {"identify", "sddd", processIdentifyCmd, "[addrMode][addr][ep][idTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd, "[addrMode][addr][ep]\r\n"},
  {"triggerEffect", "sdddd", processTriggerEffectCmd, "[addrMode][addr][ep][eftId][eftVar]"},
  {"getEndpointList", "ddd" , processGetEndpointListCmd, "[shortAddr][ep][startIndex]\r\n"},
  {"disableDefaultResp", "d",  processDisableDefaultResponseBitCmd, "[value - 0 for enable or 1 for disable]\r\n"},
  // SCENES CLUSTER
  {"addSceneToDL", "sddddddd", processAddSceneToDimmableLightCmd, "[addrMode][addr][ep][groupId][sceneId][transitionTime][onOff][level]\r\n"},
  {"viewScene", "sdddd", processViewSceneCmd, "[addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"removeScene", "sdddd", processRemoveSceneCmd, "[addrMode][addr][ep][gid][sid]\r\n"},
  {"removeAllScenes", "sddd", processRemoveAllScenesCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"storeScene", "sdddd", processStoreSceneCmd, "[addrMode][addr][ep][gid][sid]\r\n"},
  {"recallScene", "sddddd", processRecallSceneCmd, "[addrMode][addr][ep][gid][sid][transitionTime]\r\n"},
  {"getSceneMembership", "sddd", processGetSceneMembershipCmd, "[addrMode][addr][ep][gid]\r\n"},
  {"enhancedAddScene", "sddddddddddddddd", processEnhancedAddSceneCmd, "[addrMode][addr][ep][group][scene][trTime][onOff][level][X][Y][enHue][sat][colorLoopActv][colorLoopDir][colorLoopTime][colorTemp]\r\n"},
  {"enhancedViewScene", "sdddd", processEnhancedViewSceneCmd, "[addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"copyScene", "sddddddd", processCopySceneCmd, "[addrMode][addr][ep][mode][groupFrom][sceneFrom][groupTo][sceneTo]\r\n"},

  // ON/OFF CLUSTER
  {"onOff", "sdds", processOnOffToggleCmd, "[addrMode][addr][ep][onOff]: -on for On, -off for Off]\r\n"},
  {"offWithEffect", "sdddd", processOffWithEffectCmd,  "[addrMode][addr][ep][effectId][effectVariant]\r\n"},
  {"onWithRecallGlobalScene", "sdd", processOnWithRecallGlobalSceneCmd,  "[addrMode][addr][ep]\r\n"},
  {"onWithTimedOff", "sddddd", processOnWithTimedOffCmd, "[addrMode][mode][ep][onOffCtrl][onTime][offWaitTime]\r\n"},

  // LEVEL CONTROL CLUSTER
  {"moveToLevel", "sddddddd", processMoveToLevelCmd, "[addrMode][addr][ep][lvl][trTime][onOff][optMask][optOvrd]\r\n"},
  {"move", "sddddddd", processMoveCmd, "[addrMode][addr][ep][mode][rate][onOff][optMask][optOvrd]\r\n"},
  {"step", "sdddddddd", processStepCmd, "[addrMode][addr][ep][mode][sz][trTime][onOff][optMask][optOvrd]\r\n"},
  {"stop", "sddddd", processStopCmd, "[addrMode][addr][ep][onOff][optMask][optOvrd]\r\n"},

   // Color Control cluster commands
  {"moveToHue", "sddddddd", processMoveToHueCmd,"[addrMode][addr][ep][hue][direction][transitTime][optMask][optOvrd]\r\n"},
  {"moveHue", "sdddddd", processMoveHueCmd,"[addrMode][addr][ep][moveMode][rate][optMask][optOvrd]\r\n"},
  {"stepHue", "sddddddd", processStepHueCmd, "[addrMode][addr][ep][stepMode][stepSize][transitTime][optMask][optOvrd]\r\n"},
  {"moveToSaturation", "sdddddd", processMoveToSaturationCmd, "[addrMode][addr][ep][saturation][transitTime][optMask][optOvrd]\r\n"},
  {"moveSaturation", "sdddddd", processMoveSaturationCmd, "[addrMode][addr][ep][moveMode][rate][optMask][optOvrd]\r\n"},
  {"stepSaturation", "sddddddd", processStepSaturationCmd, "[addrMode][addr][ep][stepMode][stepSize][transitTime][optMask][optOvrd]\r\n"},
  {"moveToHueAndSaturation", "sddddddd",   processMoveToHueAndSaturationCmd, "[addrMode][addr][ep][hue][saturation][transitTime][optMask][optOvrd]\r\n"},
  {"moveToColor", "sddddddd", processMoveToColorCmd, "[addrMode][addr][ep][colorX][colorY][transitTime][optMask][optOvrd]\r\n"},
  {"moveColor", "sdddddd", processMoveColorCmd, "[addrMode][addr][ep][rateX][rateY][optMask][optOvrd]\r\n"},
  {"stepColor", "sddddddd", processStepColorCmd, "[addrMode][addr][ep][stepX][stepY][transitTime][optMask][optOvrd]\r\n"},
  {"moveToColorTemperature", "sdddddd", processMoveToColorTemperatureCmd, "[addrMode][addr][ep][colorTemp][transitTime][optMask][optOvrd]\r\n"},
  {"enhancedMoveToHue", "sddddddd", processEnhancedMoveToHueCmd, "[addrMode][addr][ep][enhancedHue][direction][transitTime][optMask][optOvrd]\r\n"},
  {"enhancedMoveHue", "sdddddd", processEnhancedMoveHueCmd, "[addrMode][addr][ep][moveMode][rate][optMask][optOvrd]\r\n"},
  {"enhancedStepHue", "sddddddd", processEnhancedStepHueCmd, "[addrMode][addr][ep][stepMode][stepSize][transitTime][optMask][optOvrd]\r\n"},
  {"enhancedMoveToHueAndSaturation", "sddddddd", processEnhancedMoveToHueAndSaturationCmd, "[addrMode][addr][ep][enhancedHue][saturation][transitTime][optMask][optOvrd]\r\n"},
  {"colorLoopSet", "sddddddddd", processColorLoopSetCmd, "[addrMode][addr][ep][updateFlags][action][direction][time][startHue][optMask][optOvrd]\r\n"},
  {"stopMoveStep", "sdddd",processStopMoveStepCmd, "[addrMode][addr][ep][optMask][optOvrd]\r\n"},
  {"moveColorTemperature", "sdddddddd", processMoveColorTemperatureCmd, "[addrMode][addr][ep][moveMode][rate][colorTempMin][colorTempMax][optMask][optOvrd]\r\n"},
  {"stepColorTemperature", "sddddddddd", processStepColorTemperatureCmd, "[addrMode][addr][ep][stepMode][stepSize][transitTime][colorTempMin][colorTempMax][optMask][optOvrd]\r\n"},

#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1
  {0,0,0,0},
};

/******************************************************************************
                   Global variables section
******************************************************************************/
ScanValue_t local;
bool fbRole = true;
uint8_t srcEp = APP_ENDPOINT_COLOR_SCENE_CONTROLLER;
/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Processes request for HA device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("Z3DeviceType = 0x%04x\r\n", APP_Z3DEVICE_ID);
  (void)args;
}

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
\brief Processes bdbJoinUses InstallCode command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetbdbJoinUsesInstallCodeKey(const ScanValue_t *args)
{
  BDB_SetInstallCodeUsage(args[0].uint8);
  (void)args;
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
  {
    groupList[i] = args[i+4].uint16;
  }

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
  onOffSendOnWithRecallGlobalScene(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp);
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
  levelControlSendMoveToLevel(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint8, args[4].uint16, args[5].uint8, args[6].uint8, args[7].uint8);
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
  scenesSendViewScene(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
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
    args[3].uint16, args[4].uint8, args[5].uint16);
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


/**************************************************************************//**
\brief Processes EnhancedAddScene command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedAddSceneCmd(const ScanValue_t *args)
{
  ZCL_ColorControlClusterExtensionFieldSet_t ccExt;

  ccExt.currentX           = args[8].uint16;
  ccExt.currentY           = args[9].uint16;
  ccExt.enhancedCurrentHue = args[10].uint16;
  ccExt.currentSaturation  = args[11].uint8;
  ccExt.colorLoopActive    = args[12].uint8;
  ccExt.colorLoopDirection = args[13].uint8;
  ccExt.colorLoopTime      = args[14].uint16;
  ccExt.colorTemperature   = args[15].uint16;

  scenesSendEnhancedAddSceneToExtendedColorLightWithExtFields(
    determineAddressMode(args),
    args[1].uint16, //  addr
    args[2].uint8,  //  destination endpoint
    srcEp,          //  source endpoint
    args[3].uint16, //  groupId
    args[4].uint16, //  sceneId
    args[5].uint16, //  transitionTime
    args[6].uint8,  //  onOff
    args[7].uint8,  //  level
    &ccExt
  );
}

/**************************************************************************//**
\brief Processes EnhancedViewScene command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedViewSceneCmd(const ScanValue_t *args)
{
  scenesSendEnhancedViewScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    srcEp, args[3].uint16, args[4].uint16);
}

/**************************************************************************//**
\brief Processes CopyScene command

\param[in] args - array of command arguments
******************************************************************************/
static void processCopySceneCmd(const ScanValue_t *args)
{
  SceneMode_t mode;
  mode.copyAllScenes = args[3].uint8;
  scenesSendCopyScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    srcEp, mode, args[4].uint16, args[5].uint16, args[6].uint16, args[7].uint16);
}

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

  onOffSendOnOffToggle(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp, (OnOffToggle_t)command);
}
/**************************************************************************//**
\brief Processes sendEndpointInfo command

\param[in] args - array of command arguments
******************************************************************************/
static void processSendEndpointInfoCmd(const ScanValue_t *args)
{
  commissioningSendEndpointInformation(args[0].uint16, /* dst short address */
                                         args[1].uint8, srcEp  /* dst endpoint */
                                        );
}

/**************************************************************************//**
\brief Processes getGroupIdentifiers command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetGroupIdentifiersCmd(const ScanValue_t *args)
{
  commissioningSendGetGroupIdentifiers(args[0].uint16, /* dst short address */
                                         args[1].uint8, srcEp,  /* dst endpoint */
                                         args[2].uint8   /* start index */
                                        );
}

/**************************************************************************//**
\brief Processes getEndpointList command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetEndpointListCmd(const ScanValue_t *args)
{
  commissioningGetEndpointList(args[0].uint16, /* dst short address */
                                 args[1].uint8, srcEp,  /* dst endpoint */
                                 args[2].uint8   /* start index */
                                );
}

/**************************************************************************//**
\brief Processes Color Control: MoveToHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToHueCmd(const ScanValue_t *args)
{
  colorControlSendMoveToHueCommand(determineAddressMode(args),
                                     args[1].uint16,
                                     args[2].uint8,
                                     /* Payload arguments */
                                     srcEp,
                                     args[3].uint8,
                                     args[4].uint8,
                                     args[5].uint16,
                                     args[6].uint8,
                                     args[7].uint8
                                    );
}

/**************************************************************************//**
\brief Processes Color Control: MoveHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveHueCmd(const ScanValue_t *args)
{
  colorControlSendMoveHueCommand(determineAddressMode(args),
                                   args[1].uint16,
                                   args[2].uint8,
                                   srcEp,
                                     /* Payload arguments */
                                   args[3].uint8,
                                   args[4].uint8,
                                   args[5].uint8,
                                   args[6].uint8
                                  );
}

/**************************************************************************//**
\brief Processes Color Control: StepHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepHueCmd(const ScanValue_t *args)
{
  colorControlSendStepHueCommand(determineAddressMode(args),
                                   args[1].uint16,
                                   args[2].uint8,
                                   srcEp,
                                     /* Payload arguments */
                                   args[3].uint8,
                                   args[4].uint8,
                                   args[5].uint8,
                                   args[6].uint8,
                                   args[7].uint8
                                  );
}

/**************************************************************************//**
\brief Processes Color Control: MoveToSaturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToSaturationCmd(const ScanValue_t *args)
{
  colorControlSendMoveToSaturationCommand(determineAddressMode(args),
                                            args[1].uint16,
                                            args[2].uint8,
                                            srcEp,
                                     /* Payload arguments */
                                            args[3].uint8,
                                            args[4].uint16,
                                            args[5].uint8, 
                                            args[6].uint8
                                           );
}

/**************************************************************************//**
\brief Processes Color Control: MoveSaturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveSaturationCmd(const ScanValue_t *args)
{
  colorControlSendMoveSaturationCommand(determineAddressMode(args),
                                          args[1].uint16,
                                          args[2].uint8,
                                          srcEp,
                                     /* Payload arguments */
                                          args[3].uint8,
                                          args[4].uint8,
                                          args[5].uint8,
                                          args[6].uint8
                                         );
}

/**************************************************************************//**
\brief Processes Color Control: StepSaturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepSaturationCmd(const ScanValue_t *args)
{
  colorControlSendStepSaturationCommand(determineAddressMode(args),
                                          args[1].uint16,
                                          args[2].uint8,
                                          srcEp,
                                     /* Payload arguments */
                                          args[3].uint8,
                                          args[4].uint8,
                                          args[5].uint16,
                                          args[6].uint8,
                                          args[7].uint8
                                         );
}

/**************************************************************************//**
\brief Processes Color Control: MoveToHueAndSaturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToHueAndSaturationCmd(const ScanValue_t *args)
{
  colorControlSendMoveToHueAndSaturationCommand(determineAddressMode(args),
                                                  args[1].uint16,
                                                  args[2].uint8,
                                                  srcEp,
                                     /* Payload arguments */
                                                  args[3].uint8,
                                                  args[4].uint8,
                                                  args[5].uint16,
                                                  args[6].uint8,
                                                  args[7].uint8
                                                 );
}

/**************************************************************************//**
\brief Processes Color Control: MoveToColor command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToColorCmd(const ScanValue_t *args)
{
  colorControlSendMoveToColorCommand(determineAddressMode(args),
                                       args[1].uint16,
                                       args[2].uint8,
                                       srcEp,
                                     /* Payload arguments */
                                       args[3].uint16,
                                       args[4].uint16,
                                       args[5].uint16,
                                       args[6].uint8, 
                                       args[7].uint8
                                      );
}

/**************************************************************************//**
\brief Processes Color Control: MoveColor command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveColorCmd(const ScanValue_t *args)
{
  colorControlSendMoveColorCommand(determineAddressMode(args),
                                     args[1].uint16,
                                     args[2].uint8,
                                     srcEp,
                                     /* Payload arguments */
                                     args[3].int16,
                                     args[4].int16,
                                     args[5].uint8,
                                     args[6].uint8
                                    );
}

/**************************************************************************//**
\brief Processes Color Control: StepColor command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepColorCmd(const ScanValue_t *args)
{
  colorControlSendStepColorCommand(determineAddressMode(args),
                                     args[1].uint16,
                                     args[2].uint8,
                                     srcEp,
                                     /* Payload arguments */
                                     args[3].int16,
                                     args[4].int16,
                                     args[5].int16,
                                     args[6].uint8,
                                     args[7].uint8
                                    );
}

/**************************************************************************//**
\brief Processes Color Control: MoveToColorTemperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveToColorTemperatureCmd(const ScanValue_t *args)
{
  colorControlSendMoveToColorTemperatureCommand(determineAddressMode(args),
                                                  args[1].uint16,
                                                  args[2].uint8,
                                                  srcEp,
                                                  /* Payload arguments */
                                                  args[3].uint16,
                                                  args[4].uint16,
                                                  args[5].uint8,
                                                  args[6].uint8
                                                 );
}

/**************************************************************************//**
\brief Processes Color Control: EnhancedMoveToHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveToHueCmd(const ScanValue_t *args)
{
  colorControlSendEnhancedMoveToHueCommand(determineAddressMode(args),
                                             args[1].uint16,
                                             args[2].uint8,
                                             srcEp,
                                             /* Payload arguments */
                                             args[3].uint16,
                                             args[4].uint8,
                                             args[5].uint16,
                                             args[6].uint8,
                                             args[7].uint8
                                            );
}

/**************************************************************************//**
\brief Processes Color Control: EnhancedMoveHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveHueCmd(const ScanValue_t *args)
{
  colorControlSendEnhancedMoveHueCommand(determineAddressMode(args),
                                           args[1].uint16,
                                           args[2].uint8,
                                           srcEp,
                                           /* Payload arguments */
                                           args[3].uint8,
                                           args[4].uint16,
                                           args[5].uint8, 
                                           args[6].uint8
                                          );
}

/**************************************************************************//**
\brief Processes Color Control: EnhancedStepHue command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedStepHueCmd(const ScanValue_t *args)
{
  colorControlSendEnhancedStepHueCommand(determineAddressMode(args),
                                           args[1].uint16,
                                           args[2].uint8,
                                           srcEp,
                                           /* Payload arguments */
                                           args[3].uint8,
                                           args[4].uint16,
                                           args[5].uint16,
                                           args[6].uint8,
                                           args[7].uint8
                                          );
}

/**************************************************************************//**
\brief Processes Color Control: EnhancedMoveToHueAndSaturation command

\param[in] args - array of command arguments
******************************************************************************/
static void processEnhancedMoveToHueAndSaturationCmd(const ScanValue_t *args)
{
  colorControlSendEnhancedMoveToHueAndSaturationCommand(determineAddressMode(args),
                                                          args[1].uint16,
                                                          args[2].uint8,
                                                          srcEp,
                                                          /* Payload arguments */
                                                          args[3].uint16,
                                                          args[4].uint8,
                                                          args[5].uint16,
                                                          args[6].uint8,
                                                          args[7].uint8
                                                         );
}

/**************************************************************************//**
\brief Processes Color Control: ColorLoopSet command

\param[in] args - array of command arguments
******************************************************************************/
static void processColorLoopSetCmd(const ScanValue_t *args)
{
  colorControlSendColorLoopSetCommand(determineAddressMode(args),
                                        args[1].uint16,
                                        args[2].uint8,
                                        srcEp,
                                        /* Payload arguments */
                                        args[3].uint8,
                                        args[4].uint8,
                                        args[5].uint8,
                                        args[6].uint16,
                                        args[7].uint16,
                                        args[8].uint8,
                                        args[9].uint8
                                       );
}

/**************************************************************************//**
\brief Processes Color Control: StopMoveStep command

\param[in] args - array of command arguments
******************************************************************************/
static void processStopMoveStepCmd(const ScanValue_t *args)
{
  colorControlSendStopMoveStepCommand(determineAddressMode(args),
                                        args[1].uint16,
                                        args[2].uint8,
                                        srcEp,
                                        args[3].uint8,
                                        args[4].uint8
                                       );
}

/**************************************************************************//**
\brief Processes Color Control: MoveColorTemperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processMoveColorTemperatureCmd(const ScanValue_t *args)
{
  colorControlSendMoveColorTemperatureCommand(determineAddressMode(args),
                                                args[1].uint16,
                                                args[2].uint8,
                                                srcEp,
                                                /* Payload arguments */
                                                args[3].uint8,
                                                args[4].uint16,
                                                args[5].uint16,
                                                args[6].uint16,
                                                args[7].uint8,
                                                args[8].uint8
                                               );
}

/**************************************************************************//**
\brief Processes Color Control: StepColorTemperature command

\param[in] args - array of command arguments
******************************************************************************/
static void processStepColorTemperatureCmd(const ScanValue_t *args)
{
  colorControlSendStepColorTemperatureCommand(determineAddressMode(args),
                                                args[1].uint16,
                                                args[2].uint8,
                                                srcEp,
                                                /* Payload arguments */
                                                args[3].uint8,
                                                args[4].uint16,
                                                args[5].uint16,
                                                args[6].uint16,
                                                args[7].uint16,
                                                args[8].uint8,
                                                args[9].uint8
                                               );
}

#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1

#endif // APP_ENABLE_CONSOLE == 1

#endif // APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER


// eof cscConsole.c
