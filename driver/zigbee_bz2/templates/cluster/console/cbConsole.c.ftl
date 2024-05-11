/*******************************************************************************
  Control Bridge console Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cbConsole.c

  Summary:
    This file contains the Control Bridge console implementation.

  Description:
    This file contains the Control Bridge console implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CONTROL_BRIDGE)
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <uartManager.h>
#include <console.h>
#include <consoleCmds.h>
#include <haClusters.h>
#include <cbBasicCluster.h>
#include <identifyCluster.h>
#include <cbColorControlCluster.h>
#include <cbCommissioningCluster.h>
#include <cbIdentifyCluster.h>
#include <cbOnOffCluster.h>
#include <cbLevelControlCluster.h>
#include <cbGroupsCluster.h>
#include <cbScenesCluster.h>
#include <cbOccupancySensingCluster.h>
#include <cbIlluminanceMeasurementCluster.h>
#include <resetReason.h>
#include <z3Device.h>
#include <pdsDataServer.h>
#include <zdo.h>
#include <nwkAttributes.h>
#include <sysTaskManager.h>
#ifdef BOARD_PC
  #include <conio.h>
#endif
#ifdef ZAPPSI_HOST
#include <zsiHalSerialization.h>
#endif
#include <bdb.h>
#include <bdbInstallCode.h>
#define N_Connection_AssociateDiscovery N_Connection_AssociateDiscovery_Impl
#include <zllplatform/ZLL/N_Connection/include/N_Connection.h>
#include <identifyCluster.h>
#include <groupsCluster.h>
#include <scenesCluster.h>
#include <onOffCluster.h>
#include <levelControlCluster.h>
#include <colorControlCluster.h>
#include <z3device/clusters/include/commissioningCluster.h>

/******************************************************************************
                    Defines section
******************************************************************************/
/* This value used in ZLL tests to identify non-ZLL Router */
#define TEST_DEVICE_TYPE_HA_TC 0x03U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);

#if BDB_COMMANDS_IN_CONSOLE == 1
static void processSetbdbJoinUsesInstallCodeKey(const ScanValue_t *args);
static void processSetInstallCodeCmd(const ScanValue_t *args);
static void processFormAndSteerCmd(const ScanValue_t *args);
static void processFormSteerAndFBCmd(const ScanValue_t *args);
#endif // BDB_COMMANDS_IN_CONSOLE == 1

// Groups cluster commands
static void processAddGroupCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);

#if ZCL_COMMANDS_IN_CONSOLE == 1

static void processDisableDefaultResponseBitCmd(const ScanValue_t *args);

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
// Basic cluster commands
static void processResetToFactoryDefaultsCmd(const ScanValue_t *args);
#endif // ZLO_EXTRA_CLUSTERS_SUPPORT == 1

// Identify cluster commands
static void processIdentifyCmd(const ScanValue_t *args);
static void processIdentifyQueryCmd(const ScanValue_t *args);
static void processTriggerEffectCmd(const ScanValue_t *args);

// On/off cluster commands
static void processOnOffToggleCmd(const ScanValue_t *args);
static void processOffWithEffectCmd(const ScanValue_t *args);
static void processOnWithRecallGlobalSceneCmd(const ScanValue_t *args);
static void processOnWithTimedOffCmd(const ScanValue_t *args);

// Level Control cluster commands
static void processMoveCmd(const ScanValue_t *args);
static void processMoveToLevelCmd(const ScanValue_t *args);
static void processStepCmd(const ScanValue_t *args);
static void processStopCmd(const ScanValue_t *args);

// Color Control cluster commands
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

// Touchlink Commissioning cluster
static void processSendEndpointInfoCmd(const ScanValue_t *args);
static void processGetGroupIdentifiersCmd(const ScanValue_t *args);
static void processGetEndpointListCmd(const ScanValue_t *args);

// Scenes cluster commands
static void processAddSceneToDimmableLightCmd(const ScanValue_t *args);
static void processAddSceneToThermostatCmd(const ScanValue_t *args);
static void processGetSceneMembershipCmd(const ScanValue_t *args);
static void processViewSceneCmd(const ScanValue_t *args);
static void processRecallSceneCmd(const ScanValue_t *args);
static void processRemoveAllScenesCmd(const ScanValue_t *args);
static void processRemoveSceneCmd(const ScanValue_t *args);
static void processStoreSceneCmd(const ScanValue_t *args);
static void processEnhancedAddSceneCmd(const ScanValue_t *args);
static void processEnhancedViewSceneCmd(const ScanValue_t *args);
static void processCopySceneCmd(const ScanValue_t *args);
#endif // ZCL_COMMANDS_IN_CONSOLE == 1

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
  {"setExtAddr", "dd",processSetExtAddr, "->Set Ext Address:[upper][lower]\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "-> Sets primary channel mask: setPrimaryChannelMask [mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "-> Sets secondary channel mask: setSecondaryChannelMask [mask]\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"formAndSteer", "", processFormAndSteerCmd, "-> forms network and steers\r\n"},
  {"formSteerAndFB", "", processFormSteerAndFBCmd, "-> forms network ,steers and FB\r\n"},
  {"setAllowSteal", "d", processSetAllowStealCmd, "-> Sets setAllowSteal: 0 or 1 <type>\r\n"},
#if BDB_TOUCHLINK_SUPPORT == 1
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, "-> Sets setAllowTLResetToFN: 0 or 1 <type>\r\n"},
  {"SetTLRole", "d", processSetTLRole, "-> Sets TouchLink Role [initiator]\r\n"},
#endif
#if BDB_FINDINGBINDING_INITIATOR_TARGET_PARALLEL_EXECUTION == 0  
  {"SetFBRole", "d", processSetFBRole, "-> Sets FB Role [initiator]\r\n"},
#endif
  {"setGlobalKey", "d", processsetGlobalKeyCmd, "-> Sets Key for negative testing[Option]\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
#endif
   {0,0,0,0},
};

const ConsoleCommand_t zclHelpCmds[]=
{
  // Foundation commands
  {"readAttribute", "sdddd", processReadAttrCmd, "->Read Attribute for specified cluster: readAttribute [addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "->Write Attribute for specified cluster: writeAttribute [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"writeAttributeNoResp", "sddddddd", processWriteAttrNoRespCmd, "->Write Attribute No response for specified cluster: writeAttributeNoResp [addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
  {"configureReporting", "sddddddd", processConfigureReportingCmd, "->Sends configure reporting to specified cluster server: configureReporting [addrMode][addr][ep][clusterId][attrId][type][min][max]\r\n"},
  {"configureReportingWRC", "sdddddddd", processConfigureReportingWithReportableChangeCmd, "->Sends configure reporting with reportable Change to specified cluster server: configureReportingWRC [addrMode][addr][ep][clusterId][attrId][type][min][max][repChange]\r\n"},
  {"readReporting", "sdddd", processReadReportingCmd, "->Sends Read reporting to specified cluster server: readReporting [addrMode][addr][ep][clusterId][attrId]\r\n"},

  // Groups cluster commands
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
  {"SetbdbJoinUsesInstallCodeKey", "d", processSetbdbJoinUsesInstallCodeKey, "-> Sets bdbJoinUsesInstallCodeKey [value]\r\n"},
  {"SetInstallCodeDevice", "s", processSetInstallCodeCmd, "-> Sets IC [code]\r\n"},
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
#endif

#if ZCL_COMMANDS_IN_CONSOLE == 1
  {"disableDefaultResp", "d",  processDisableDefaultResponseBitCmd, "->Disable/Enable default response for ZCL command: disableDefaultResp [value - 0 for enable or 1 for disable]\r\n"},

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  // Basic cluster commands
  {"resetToFactoryDefaults", "sdd", processResetToFactoryDefaultsCmd, "-> reset all cluster attributes to factory defaults command:resetToFactoryDefaults [addrMode][addr][ep]\r\n"},
#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

  // Identify cluster commands
  {"identify", "sddd", processIdentifyCmd, "->Send Identify command: identify [addrMode][addr][ep][idTime]\r\n"},
  {"identifyQuery", "sdd", processIdentifyQueryCmd, "->Send Identify Query command: identifyQuery [addrMode][addr][ep]\r\n"},
  {"triggerEffect", "sdddd", processTriggerEffectCmd, "->Send TriggerEffect command: triggerEffect [addrMode][addr][ep][effectId][effectVariant]"},

  // On/off cluster commands
  {"onOff", "sdds", processOnOffToggleCmd, "Sends On/Off command: onOff [addrMode][addr][ep][onOff: -on for On, -off for Off]\r\n"},
  {"offWithEffect", "sdddd", processOffWithEffectCmd, "->Send Off With Effect command: offWithEffect [addrMode][addr][ep][effectId][effectVariant]\r\n"},
  {"onWithRecallGlobalScene", "sdd", processOnWithRecallGlobalSceneCmd, "->Send On With Recall Global Scene command: onWithRecallGlobalScene [addrMode][addr][ep]\r\n"},
  {"onWithTimedOff", "sddddd", processOnWithTimedOffCmd, "->Send On With Timed off command: onWithTimedOff [addrMode][mode][ep][onOffCtrl][onTime][offWaitTime]\r\n"},

  // Level Control cluster commands
  {"move", "sddddddd", processMoveCmd, "->Send Move (with On/Off) command: move [addrMode][addr][ep][mode][rate][onOff][optMask][optOvrd]\r\n"},
  {"moveToLevel", "sddddddd", processMoveToLevelCmd, "->Send Move To Level (with On/Off) command: moveToLevel [addrMode][addr][ep][level][transitionTime][onOff][optMask][optOvrd]\r\n"},
  {"step", "sdddddddd", processStepCmd, "->Send Step (with On/Off) command: step [addrMode][addr][ep][mode][stepSize][transitionTime][onOff][optMask][optOvrd]\r\n"},
  {"stop", "sddddd", processStopCmd, "->Send Stop (with On/Off) command: stop [addrMode][addr][ep][onOff][optMask][optOvrd]\r\n"},

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

  // Commissioning cluster commands
  {"sendEndpointInfo", "dd"  , processSendEndpointInfoCmd, "->Send Endpoint Info command: sendEndpointInfo [shortAddr][ep]\r\n"},
  {"getGroupIdentifiers", "ddd" , processGetGroupIdentifiersCmd, "->Send getGroupsIdentifiers command: getGroupIdentifiers [shortAddr][ep][startIndex]\r\n"},
  {"getEndpointList", "ddd" , processGetEndpointListCmd, "->Send getEndpointList command: getGroupIdentifiers [shortAddr][ep][startIndex]\r\n"},

  // Scenes cluster commands
  {"addSceneToDL", "sddddddd", processAddSceneToDimmableLightCmd, "->Send Add Scene command to Dimmable Light: addScene [addrMode][addr][ep][groupId][sceneId][transitionTime][onOff][level]\r\n"},
  {"addSceneToTH", "sdddddddd", processAddSceneToThermostatCmd, "->Send Add Scene command to Thermostat: addScene [addrMode][addr][ep][groupId][sceneId][transitionTime][occupiedCoolingSetpoint][occupiedHeatingSetpoint][systemMode]\r\n"},
  {"getSceneMembership", "sddd", processGetSceneMembershipCmd, "->Send Get Scene Membership command: getSceneMembership [addrMode][addr][ep][groupId]\r\n"},
  {"recallScene", "sdddd", processRecallSceneCmd, "->Send Recall Scene command: recallScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"removeAllScenes", "sddd", processRemoveAllScenesCmd, "->Send Remove All Scenes command: removeAllScenes [addrMode][addr][ep][groupId]\r\n"},
  {"removeScene", "sdddd", processRemoveSceneCmd, "->Send Remove Scene command: removeScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"viewScene", "sdddd", processViewSceneCmd, "->Send View Scene command: viewScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"storeScene", "sdddd", processStoreSceneCmd, "->Send Store Scene command: storeScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"enhancedAddScene", "sddddddddddddddd", processEnhancedAddSceneCmd, "->Send EnhancedAddScene cmd: enhancedAddScene [addrMode][addr][ep][group][scene][trTime][onOff][level][X][Y][enHue][sat][colorLoopActv][colorLoopDir][colorLoopTime][colorTemp]\r\n"},
  {"enhancedViewScene", "sdddd", processEnhancedViewSceneCmd, "->Send EnhancedViewScene cmd: enhancedViewScene [addrMode][addr][ep][groupId][sceneId]\r\n"},
  {"copyScene", "sddddddd", processCopySceneCmd, "->Send CopyScene cmd: copyScene [addrMode][addr][ep][mode][groupFrom][sceneFrom][groupTo][sceneTo]\r\n"},
#endif // #if ZCL_COMMANDS_IN_CONSOLE == 1
  {0,0,0,0},
};

#if BDB_COMMANDS_IN_CONSOLE == 1
static HAL_AppTimer_t aTimer;
static BDB_InvokeCommissioningReq_t AppbdbCommissioningreq;
static BDB_InitiatorReq_t AppinitiatorReq;
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

/******************************************************************************
                   Global variables section
******************************************************************************/
bool fbRole = true;
ScanValue_t local;
bool doFindAndBind = true;
uint8_t srcEp = APP_ENDPOINT_CONTROL_BRIDGE;

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Processes request for HA evice type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("HADeviceType = 0x%04x\r\n", APP_Z3DEVICE_ID);
  (void)args;
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  (void)args;
  appSnprintf("DeviceType = %d\r\n", TEST_DEVICE_TYPE_ZIGBEE_ROUTER);
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
static void processSetInstallCodeCmd(const ScanValue_t *args)
{
  uint8_t icode[18];
  ExtAddr_t extAddr = ((uint64_t)args[0].uint32 << 32);
  extAddr |= args[1].uint32;
  hexStrTouint8array(args[2].str, icode, 18U);
  BDB_ConfigureInstallCode(extAddr, icode, myICCallback);
  (void)args;
}

#if BDB_COMMANDS_IN_CONSOLE == 1

/**************************************************************************//**
\brief Form And Steer1 callback

\param[in] conf - pointer to confirmation structure
******************************************************************************/
static void Callback_FormAndSteer1(BDB_InvokeCommissioningConf_t *conf)
{
  appSnprintf("CommissioningStatus = %d\r\n", conf->status);
}

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
  //memcpy(&appBindReq, getDeviceBindRequest(), sizeof(appBindReq));
  AppBindReq_t *appBindReqLocal = deviceBindReqs[0];
  AppbdbCommissioningreq.initiatorReq = &AppinitiatorReq;

  AppbdbCommissioningreq.initiatorReq->groupId = 0;
  AppbdbCommissioningreq.initiatorReq->initiatorEndpoint = appBindReqLocal->srcEndpoint;
  AppbdbCommissioningreq.initiatorReq->clientClustersCount = appBindReqLocal->remoteServersCnt;
  AppbdbCommissioningreq.initiatorReq->serverClustersCount = appBindReqLocal->remoteClientsCnt;
  AppbdbCommissioningreq.initiatorReq->clientClustersList = appBindReqLocal->remoteServers;
  AppbdbCommissioningreq.initiatorReq->serverClustersList = appBindReqLocal->remoteClients;
  AppbdbCommissioningreq.initiatorReq->callback = appBindReqLocal->callback;
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
  //memcpy(&appBindReq, getDeviceBindRequest(), sizeof(appBindReq));
  AppBindReq_t *appBindReqLocal = deviceBindReqs[0];
  AppbdbCommissioningreq.initiatorReq = &AppinitiatorReq;

  AppbdbCommissioningreq.initiatorReq->groupId = args[1].uint16;
  AppbdbCommissioningreq.initiatorReq->initiatorEndpoint = appBindReqLocal->srcEndpoint;
  AppbdbCommissioningreq.initiatorReq->clientClustersCount = appBindReqLocal->remoteServersCnt;
  AppbdbCommissioningreq.initiatorReq->serverClustersCount = appBindReqLocal->remoteClientsCnt;

  AppbdbCommissioningreq.initiatorReq->clientClustersList = appBindReqLocal->remoteServers;
  AppbdbCommissioningreq.initiatorReq->serverClustersList = appBindReqLocal->remoteClients;
  AppbdbCommissioningreq.initiatorReq->callback = appBindReqLocal->callback;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer;
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}
#endif

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
    groupList[i] = args[i+4].uint16;

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
  cbBasicResetToFactoryDefaultsCommand(determineAddressMode(args), args[1].uint16,
    args[2].uint8, srcEp);
}

#endif // #if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

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
\brief Processes Add Scene command to Thermostat

\param[in] args - array of command arguments
******************************************************************************/
static void processAddSceneToThermostatCmd(const ScanValue_t *args)
{
  scenesSendAddSceneToThermotstat(determineAddressMode(args), args[1].uint16, args[2].uint8, srcEp,
    args[3].uint16, args[4].uint8, args[5].uint16, args[6].int16, args[7].int16, args[8].uint8 );
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
  scenesSendCopyScene(determineAddressMode(args), args[1].uint16, args[2].uint8,
    srcEp, args[3].uint8, args[4].uint16, args[5].uint16, args[6].uint16, args[7].uint16);
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
\brief Processes disableDefaultResp command

\param[in] args - array of command arguments
******************************************************************************/
static void processDisableDefaultResponseBitCmd(const ScanValue_t *args)
{
  switch (args[0].uint8)
  {
    case ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE:
    case ZCL_FRAME_CONTROL_ENABLE_DEFAULT_RESPONSE:
      setZclDefaultResponseBit(args[0].uint8);
      break;
  }
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

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof cbConsole.c