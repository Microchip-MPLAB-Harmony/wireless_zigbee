/*******************************************************************************
  Dimmable Light console Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlConsole.c

  Summary:
    This file contains the Dimmable Light console implementation..

  Description:
    This file contains the Dimmable Light console implementation.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT
#if APP_ENABLE_CONSOLE == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <console.h>
#include <resetReason.h>
#include <z3Device.h>
#include <sysUtils.h>
#include <pdsDataServer.h>
#include <zdo.h>
#include <z3Device.h>
#include <ezModeManager.h>
#include <zcl.h>
#include <bdb.h>
#include <zllplatform/ZLL/N_Connection/include/N_ConnectionRouter_Bindings.h>
#include <zllplatform/ZLL/N_Connection/include/N_Connection.h>
#include <zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget_Bindings.h>
#include <ZLL/N_LinkTarget/include/N_LinkTarget.h>
#include <bdbInstallCode.h>
#include <haClusters.h>
#include <dlGroupsCluster.h>
#include <dlIdentifyCluster.h>
#include <dlOnOffCluster.h>
#include <dlLevelControlCluster.h>
/******************************************************************************
                    Defines section
******************************************************************************/
/* This value used in ZLL tests to identify non-ZLL Router */
#define TEST_DEVICE_TYPE_HA_ROUTER 0x03U

/******************************************************************************
                    External Defines section
******************************************************************************/
extern uint8_t hexStrTouint8array(const char *str, uint8_t *out, uint8_t length);

/******************************************************************************
                    Prototypes section
******************************************************************************/
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg);
static void processHelpCmd(const ScanValue_t *args);
static void processResetCmd(const ScanValue_t *args);
static void processResetToFactoryFreshCmd(const ScanValue_t *args);
static void processGetDeviceTypeCmd(const ScanValue_t *args);
static void processGetNetworkAddressCmd(const ScanValue_t *args);
static void processGetAppDeviceTypeCmd(const ScanValue_t *args);
static void processInvokeCommissioningCmd(const ScanValue_t *args);
static void processSetPrimaryChannelMaskCmd(const ScanValue_t *args);
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args);
static void processGetExtAddrCmd(const ScanValue_t *args);
static void processSetExtAddr(const ScanValue_t *args);
// identify cluster commands
static void processIdentifyCmd(const ScanValue_t *args);
// groups cluster commands
static void processAddGroupCmd(const ScanValue_t *args);
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args);
static void processGetGroupMembershipCmd(const ScanValue_t *args);
static void processRemoveAllGroupsCmd(const ScanValue_t *args);
static void processRemoveGroupCmd(const ScanValue_t *args);
static void processViewGroupCmd(const ScanValue_t *args);

// General attribute-manipulation commands
static void processReadAttrCmd(const ScanValue_t *args);
static void processWriteAttrCmd(const ScanValue_t *args);

#if BDB_COMMANDS_IN_CONSOLE == 1
static void processSendNwkUpdateReqCmd(const ScanValue_t *args);
static void processActiveEpRequestCmd(const ScanValue_t *args);
static void processBindReqCmd(const ScanValue_t *args);
static void processBindReqCmdWithSrcAddrDestEndpoint(const ScanValue_t *args);
static void processFormAndSteerCmd(const ScanValue_t *args);
static void processFormSteerAndFBCmd(const ScanValue_t *args);
static void processIeeeAddrRequestCmd(const ScanValue_t *args);
static void processMacBanNodeCmd(const ScanValue_t *args);
static void processMacResetBanTableCmd(const ScanValue_t *args);
static void processMatchDescriptorRequestCmd(const ScanValue_t *args);
static void processMgmtSendBindReqCmd(const ScanValue_t *args);
static void processMgmtSendLeaveReqCmd(const ScanValue_t *args);
static void processMgmtSendLeaveReqCmd(const ScanValue_t *args);
static void processMgmtSendLqiReqCmd(const ScanValue_t *args);
static void processMgmtSendPermitJoinCmd(const ScanValue_t *args);
static void processMgmtSendPermitJoinCmd(const ScanValue_t *args);
static void processNodeDescriptorRequestCmd(const ScanValue_t *args);
static void processNwkAddrRequestCmd(const ScanValue_t *args);
static void processNwkLeaveReqCmd(const ScanValue_t *args);
static void processSendBeaconReqCmd(const ScanValue_t *args);
static void processSetInstallCodeCmd(const ScanValue_t *args);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void processSetPermitJoinCmd(const ScanValue_t *args);
static void processSetTargetTypeCmd(const ScanValue_t *args);
static void processSetAllowStealCmd(const ScanValue_t *args);
static void processSetAllowTLResetToFNCmd(const ScanValue_t *args);
static void processSetTCLKExchangeMethodCmd(const ScanValue_t *args);
static void processSetTCLKMaxRetryAttemptsCmd(const ScanValue_t *args);
static void processSetTLRole(const ScanValue_t *args);
static void processSimpleDescriptorRequestCmd(const ScanValue_t *args);
static void processUnBindReqCmd(const ScanValue_t *args);
static void processUnBindReqCmdWithSrcAddrDestEndpoint(const ScanValue_t *args);
static void processTargetToFnCmd(const ScanValue_t *args);
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp);
static void processsetGlobalKeyCmd(const ScanValue_t *args);
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1
static void processReadOnOffAttrVal(const ScanValue_t *args);
static void processReadCurrentLevelAttrVal(const ScanValue_t *args);
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

static void processPseudoPowerOffCmd(const ScanValue_t *args);

#ifdef UNUSED
#endif // #ifdef UNUSED

/******************************************************************************
                    Local variables section
******************************************************************************/
#if BDB_COMMANDS_IN_CONSOLE == 1
static ZDO_ZdpReq_t zdpReq;
static HAL_AppTimer_t aTimer;
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1
static uint8_t readBuffer[USART_RX_BUFFER_LENGTH];
static const ConsoleCommand_t cmds[] =
{
  {"getAppDeviceType", "", processGetAppDeviceTypeCmd, "-> Request for device type: getAppDeviceType\r\n"},
  {"getDeviceType", "", processGetDeviceTypeCmd, "-> Request for device type: getDeviceType\r\n"},
  {"getExtAddr", "", processGetExtAddrCmd, "-> Gets ExtAddr: GetExtAddr\r\n"},
  {"getNetworkAddress", "", processGetNetworkAddressCmd, "-> Returns network address: getNetworkAddress\r\n"},
  {"help",   "", processHelpCmd, "->Show help you're reading now:  help\r\n"},
  {"invokeCommissioning", "dd", processInvokeCommissioningCmd, "-> invokes commissioning [mode][groupId]\r\n"},
  {"powerOff", "", processPseudoPowerOffCmd, "-> Powers off device: powerOff\r\n"},
  {"reset", "", processResetCmd, "->Reset device\r\n"},
  {"resetToFN", "", processResetToFactoryFreshCmd, "->Reset to factory fresh settings: resetToFN\r\n"},
  {"setExtAddr", "dd",processSetExtAddr, "->Set Ext Address:[upper][lower]\r\n"},
  {"setPrimaryChannelMask", "d", processSetPrimaryChannelMaskCmd, "-> Sets primary channel mask: setPrimaryChannelMask [mask]\r\n"},
  {"setSecondaryChannelMask", "d", processSetSecondaryChannelMaskCmd, "-> Sets secondary channel mask: setSecondaryChannelMask [mask]\r\n"},
  {"addGroup", "sddd", processAddGroupCmd, "->Send Add Group command: addGroup [addrMode][addr][ep][groupId]\r\n"},
  {"addGroupIfIdentifying", "sddd", processAddGroupIfIdentifyingCmd, "->Send Add Group If Identifying command: addGroupIfIdentifying [addrMode][addr][ep][groupId]\r\n"},
  {"getGroupMembership", "sdddddddd", processGetGroupMembershipCmd, "->Send Get Group Membership command: getGroupMembership [addrMode][addr][ep][count][groupId]*5\r\n"},
  {"removeAllGroups", "sdd", processRemoveAllGroupsCmd, "->Send Remove All Groups command: removeAllGroups [addrMode][addr][ep]\r\n"},
  {"removeGroup", "sddd", processRemoveGroupCmd, "->Send Remove Group command: removeGroup [addrMode][addr][ep][groupId]\r\n"},
  {"viewGroup", "sddd", processViewGroupCmd, "->Send View Group command: viewGroup [addrMode][addr][ep][groupId]\r\n"},
  {"identify", "sddd", processIdentifyCmd, "->Send Identify command: identify [addrMode][addr][ep][identifyTime]\r\n"},
  {"readAttribute", "sdddd", processReadAttrCmd, "[addrMode][addr][ep][clusterId][attrId]\r\n"},
  {"writeAttribute", "sddddddd", processWriteAttrCmd, "[addrMode][addr][ep][clusterId][attrId][type][attrValue][attrSize]\r\n"},
#if BDB_COMMANDS_IN_CONSOLE == 1
  {"activeEpReq", "dd",processActiveEpRequestCmd, "-> Send ActiveEpRequest Command:[DstAddr] [nwkAddr]\r\n"},
  {"bindReq", "sddddd", processBindReqCmd, "-> Sends Bind Req: bindReq [addrMode][DstAddr][extAddr][ep][ClusterId]\r\n"},
  {"bindReq2", "sdddddddd", processBindReqCmdWithSrcAddrDestEndpoint, "-> Sends Bind Req With SrcAddr DestEndpoint: bindReq2 [addrMode][DstAddr][extSrcAddrHigh][extSrcAddrLow][extDstAddrHigh][extDstAddrLow/GroupID][ep_Src][ep_Dst][ClusterId]\r\n"},
  {"formAndSteer", "", processFormAndSteerCmd, "-> forms network and steers\r\n"},
  {"formSteerAndFB", "", processFormSteerAndFBCmd, "-> forms network ,steers and FB\r\n"},
  {"ieeeAddrReq", "ddd",processIeeeAddrRequestCmd, "-> Send IeeeAddrRequest Command:[dstAddr] [nwkAddOfInt] [reqType]\r\n"},
  {"macBanNode", "ddd", processMacBanNodeCmd, "-> Sets specified link cost: <extAddr> <cost>\r\n"},
  {"macResetBanTable", "", processMacResetBanTableCmd, "-> Resets mac ban table\r\n"},
  {"matchDescReq", "dd",processMatchDescriptorRequestCmd,  "-> Send MatchDescriptorRequest Command:[nwkAddr] [srcEp]\r\n"},
  {"NodeDescReq", "dd",processNodeDescriptorRequestCmd, "-> Send NodeDescriptorRequest Command:[dstnwkAddr] [nwkAddrOfInt]\r\n"},
  {"nwkAddrReq", "dddd",processNwkAddrRequestCmd, "-> Send nwkAddrRequest Command:[dstAddr][extAddrIntrHigh][extAddrIntrLow][reqType]\r\n"},
  {"nwkLeaveReq", "dddd", processNwkLeaveReqCmd, "-> Sends Nwk Leave Req: nwkLeaveReq [extAddr][rejoin][removeChild] \r\n"},
  {"resetTargetToFN", "", processTargetToFnCmd, "Reset device to FN: resetDeviceToFN\r\n"},
  {"sendBeaconReq", "", processSendBeaconReqCmd, "->SendsBeaconReq\r\n"},
  {"sendMgmtBindReq", "dd", processMgmtSendBindReqCmd, "-> Sends Mgmt Bind Req: sendMgmtBindReq [address][startIndex]\r\n"},
  {"sendMgmtLeaveReq", "ddddd", processMgmtSendLeaveReqCmd, "-> Sends Mgmt Leave Req: sendMgmtLeaveReq [dstShortAddr][devExtAddr][rejoin][removeChildren]\r\n"},
  {"sendMgmtLqiReq", "d", processMgmtSendLqiReqCmd, "-> Sends Mgmt Lqi Req: sendMgmtLqiReq [address]\r\n"},
  {"sendMgmtPermitJoin", "ddd", processMgmtSendPermitJoinCmd, "-> Sends Mgmt Permit Join: sendMgmtPermitJoin [dstAddr][dur][tcSig]\r\n"},
  {"sendNwkMgmtUpdateReq", "ddd", processSendNwkUpdateReqCmd, "-> Sends nwkMgmtUpdateReq: sendNwkMgmtUpdateReq <channel> <scanDuration> <nwkAddr>\r\n"},
  {"setGlobalKey", "d", processsetGlobalKeyCmd, "-> Sets Key for negative testing[Option]\r\n"},
  {"SetInstallCodeDevice", "s", processSetInstallCodeCmd, "-> Sets IC [code]\r\n"},
  {"setPermitJoin", "d", processSetPermitJoinCmd, "-> Sets Permit Join: setPermitJoin [dur]\r\n"},
  {"setTargetType", "d", processSetTargetTypeCmd, "-> Sets target type: setTargetType <type>\r\n"},
  {"setAllowSteal", "d", processSetAllowStealCmd, "-> Sets setAllowSteal: 0 or 1 <type>\r\n"},
  {"setAllowTLResetToFN", "d", processSetAllowTLResetToFNCmd, "-> Sets setAllowTLResetToFN: 0 or 1 <type>\r\n"},
  {"setTCLKExchangeMethod", "d", processSetTCLKExchangeMethodCmd, "-> Sets TCLK Exchange Method [method]\r\n"},
  {"setTCLKMaxRetryAttempts", "d", processSetTCLKMaxRetryAttemptsCmd, "-> Sets TCLK Max Retry Attempts [attempt]\r\n"},
  {"SetTLRole", "d", processSetTLRole, "-> Sets TouchLink Role [initiator]\r\n"},
  {"simpleDescReq", "dd",processSimpleDescriptorRequestCmd, "-> Send SimpleDescriptorRequest Command:[nwkAddr] [dstEp]\r\n"},
  {"unbindReq", "sddddd", processUnBindReqCmd, "-> Sends Un Bind Req: unbindReq [addrMode][DstAddr][extAddr][ep][ClusterId]\r\n"},
  {"unbindReq2", "sdddddddd", processUnBindReqCmdWithSrcAddrDestEndpoint, "-> Sends UnBind Req With SrcAddr DestEndpoint: unbindReq2 [addrMode][DstAddr][extSrcAddrHigh][extSrcAddrLow][extDstAddrHigh][extDstAddrLow/GroupID][ep_Src][ep_Dst][ClusterId]\r\n"},
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1
  {"onOffQ", "", processReadOnOffAttrVal, "-> Read onOff"},
  {"currentLevelQ", "", processReadCurrentLevelAttrVal, "-> Read currentLevel"},
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#ifdef UNUSED
#endif // #ifdef UNUSED
  {0,0,0,0},
};

/* Used for commissioning req*/
static BDB_InvokeCommissioningReq_t AppbdbCommissioningreq;

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Processes Read attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processReadAttrCmd(const ScanValue_t *args)
{
  switch(args[3].uint16) //cluster Id
  {
    case BASIC_CLUSTER_ID:
    case IDENTIFY_CLUSTER_ID:
    case GROUPS_CLUSTER_ID:
    case SCENES_CLUSTER_ID:
    case ONOFF_CLUSTER_ID:
    case LEVEL_CONTROL_CLUSTER_ID:
      readAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8,
        args[3].uint16, args[4].uint16, NULL);
      break;
    default:
      {
        appSnprintf("Unsupported Cluster Id \r\n");
      }
      break;
  }
}

/**************************************************************************//**
\brief Processes Write attribute command

\param[in] args - array of command arguments
******************************************************************************/
static void processWriteAttrCmd(const ScanValue_t *args)
{
  switch(args[3].uint16) //cluster Id
  {
    case BASIC_CLUSTER_ID:
    case IDENTIFY_CLUSTER_ID:
    case GROUPS_CLUSTER_ID:
    case SCENES_CLUSTER_ID:
    case ONOFF_CLUSTER_ID:
    case LEVEL_CONTROL_CLUSTER_ID:
      writeAttribute(determineAddressMode(args), args[1].uint16, args[2].uint8, args[3].uint16,
        args[5].uint8, args[4].uint16, (void *)&args[6].uint8, args[7].uint8, NULL);
      break;
    default:
      {

        appSnprintf("Unsupported Cluster Id \r\n");
      }
      break;
  }
}

/**************************************************************************//**
\brief Sends single char to serial interface
******************************************************************************/
void consoleTx(char chr)
{
  appSnprintf(&chr);
}

/**************************************************************************//**
\brief Processes single char read from serial interface

\param[in] char - read char
******************************************************************************/
void consoleTxStr(const char *str)
{
  appSnprintf(str);
}

/**************************************************************************//**
\brief Initializes console
******************************************************************************/
void initConsole(void)
{
  consoleRegisterCommands(cmds);
}

/**************************************************************************//**
\brief Processes data received by console
******************************************************************************/
void processConsole(uint16_t length)
{
  int8_t bytesRead = readDataFromUart(readBuffer, MIN(USART_RX_BUFFER_LENGTH, length));

  for (int8_t i = 0; i < bytesRead; i++)
    consoleRx(readBuffer[i]);
}

/**************************************************************************//**
\brief Determines address mode for command

\param[in] arg - pointer to command argument with address mode string

\returns address mode
******************************************************************************/
static APS_AddrMode_t determineAddressMode(const ScanValue_t *arg)
{
  if (!memcmp("-g", arg->str, 2))
    return APS_GROUP_ADDRESS;

  if (!memcmp("-b", arg->str, 2))
    return APS_NO_ADDRESS;

  if(!memcmp("-e", arg->str, 2))
    return APS_EXT_ADDRESS;

  return APS_SHORT_ADDRESS;
}

/**************************************************************************//**
\brief Processes pseudo power off command

\param[in] args - array of command arguments
******************************************************************************/
static void processPseudoPowerOffCmd(const ScanValue_t *args)
{
  /* Disable BitCloud tasks for preventing calls to the radio.
     HAL is enabled so it it allows to receive commands through UART. */
  SYS_DisableTask(ZDO_TASK_ID);
  SYS_DisableTask(APS_TASK_ID);
  SYS_DisableTask(NWK_TASK_ID);
  SYS_DisableTask(MAC_PHY_HWD_TASK_ID);
  (void)args;
}

/**************************************************************************//**
\brief Processes help command

\param[in] args - array of command arguments
******************************************************************************/
static void processHelpCmd(const ScanValue_t *args)
{
  (void)args;

  appSnprintf("Commands: \r\n");
  for (const ConsoleCommand_t *cmd = cmds; cmd->name; cmd++)
    appSnprintf("%s\r\n", cmd->name);
}

/**************************************************************************//**
\brief Processes reset command: reset device

\param[in] args - array of command arguments
******************************************************************************/
static void processResetCmd(const ScanValue_t *args)
{
  (void)args;

  HAL_WarmReset();
}


/**************************************************************************//**
\brief Processes reset to factory fresh

\param[in] args - array of command arguments
******************************************************************************/
static void processResetToFactoryFreshCmd(const ScanValue_t *args)
{
  (void)args;
  SYS_EnableTask(ZDO_TASK_ID);
  SYS_EnableTask(APS_TASK_ID);
  SYS_EnableTask(NWK_TASK_ID);
  SYS_EnableTask(MAC_PHY_HWD_TASK_ID);
  BDB_ResetToFactoryNew();
}

/**************************************************************************//**
\brief Processes request for device type obtaining

\param[in] args - array of command arguments
******************************************************************************/
static void processGetDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf( "DeviceType = %d\r\n", TEST_DEVICE_TYPE_HA_ROUTER);
  (void)args;
}

/**************************************************************************//**
\brief Processes get network address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetNetworkAddressCmd(const ScanValue_t *args)
{
  appSnprintf("%04x\r\n", NWK_GetShortAddr());
  (void)args;
}
/**************************************************************************//**
\brief Processes request for HA device type obtaining

\param[in] args - array of command arguments
+******************************************************************************/
static void processGetAppDeviceTypeCmd(const ScanValue_t *args)
{
  appSnprintf("HADeviceType = 0x%04x\r\n", HA_DIMMABLE_LIGHT_DEVICE_ID);
  (void)args;
}

static void Callback_Commissioning(BDB_InvokeCommissioningConf_t *conf)
{
  appSnprintf("CommissioningStatus = %d\r\n", conf->status);
}

static BDB_CommissioningMode_t determineCommissionMode(const ScanValue_t *arg)
{
  BDB_CommissioningMode_t tempMode;
  tempMode.touchlink = 0;
  tempMode.nwkSteering = 0;
  tempMode.nwkFormation = 0;
  tempMode.findingAndBinding = 0;
  if (arg->uint8 & 1)
  {
    tempMode.touchlink = 1;
  }
  if (arg->uint8 & 2)
  {
    tempMode.nwkSteering = 1;
  }
    if (arg->uint8 & 4)
  {
    tempMode.nwkFormation = 1;
  }
    if (arg->uint8 & 8)
  {
    tempMode.findingAndBinding = 1;
  }
  return tempMode;
}

static void processInvokeCommissioningCmd(const ScanValue_t *args)
{
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(args);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_Commissioning;   
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}

/**************************************************************************//**
\brief Processes Set Primary Channel Mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPrimaryChannelMaskCmd(const ScanValue_t *args)
{
  BDB_SetChannelMask(PRIMARY_CHANNEL_MASK, args[0].uint32);
  (void)args;
}

/**************************************************************************//**
\brief Processes Set Secondary Channel Mask command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetSecondaryChannelMaskCmd(const ScanValue_t *args)
{
  BDB_SetChannelMask(SECONDARY_CHANNEL_MASK, args[0].uint32);
  (void)args;
}


/**************************************************************************//**
\brief Processes get extended address command

\param[in] args - array of command arguments
******************************************************************************/
static void processGetExtAddrCmd(const ScanValue_t *args)
{
  const uint8_t* extAddr = (const uint8_t *)MAC_GetExtAddr();

  for (uint8_t i = 0; i < 8; i++)
  {
    appSnprintf("%02x", extAddr[i]);
  }
  appSnprintf("\r\n");
  (void)args; /*Do nothing, just to avoid compiler warning*/
  (void)extAddr; /*Do nothing, just to avoid compiler warning*/
}

/**************************************************************************//**
\brief To set a new entended address

\param[in] args - extended address
******************************************************************************/
static void processSetExtAddr(const ScanValue_t *args)
{
  ExtAddr_t changeExtAddr = ((uint64_t)args[0].uint32 << 32);
  changeExtAddr |= args[1].uint32;
  CS_WriteParameter(CS_UID_ID , &changeExtAddr);
  csPIB.macAttr.extAddr = changeExtAddr;
}

// groups cluster commands

/**************************************************************************//**
\brief Processes Add group command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupCmd(const ScanValue_t *args)
{
  groupsSendAddGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16, 0);
}

/**************************************************************************//**
\brief Processes View group command

\param[in] args - array of command arguments
******************************************************************************/
static void processViewGroupCmd(const ScanValue_t *args)
{
  groupsSendViewGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
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

  groupsSendGetGroupMembership(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint8, groupList);
}

/**************************************************************************//**
\brief Processes Remove group command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveGroupCmd(const ScanValue_t *args)
{
  groupsSendRemoveGroup(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Remove all groups command

\param[in] args - array of command arguments
******************************************************************************/
static void processRemoveAllGroupsCmd(const ScanValue_t *args)
{
  (void)args;
  groupsSendRemoveAllGroups(determineAddressMode(args), args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes Add group if identifying command

\param[in] args - array of command arguments
******************************************************************************/
static void processAddGroupIfIdentifyingCmd(const ScanValue_t *args)
{
  groupsSendAddGroupIfIdentifying(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

/**************************************************************************//**
\brief Processes Identify command

\param[in] args - array of command arguments
******************************************************************************/
static void processIdentifyCmd(const ScanValue_t *args)
{
  identifySendIdentify(determineAddressMode(args), args[1].uint16, args[2].uint8,
    args[3].uint16);
}

#if BDB_COMMANDS_IN_CONSOLE == 1
void processsetGlobalKeyCmd(const ScanValue_t *args)
{
  tempfuctionsetkey(args[0].uint8);  
}
/**************************************************************************//**
\brief Processes Set Permit Join command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetPermitJoinCmd(const ScanValue_t *args)
{
  ZDO_MgmtPermitJoiningReq_t *permit = &zdpReq.req.reqPayload.mgmtPermitJoiningReq;

  zdpReq.ZDO_ZdpResp = zdoPermitJoiningResponse;
  zdpReq.reqCluster = MGMT_PERMIT_JOINING_CLID;
  zdpReq.dstAddrMode = APS_SHORT_ADDRESS;

  zdpReq.dstAddress.shortAddress = NWK_GetShortAddr();

  permit->permitDuration = args[0].uint8;
  permit->tcSignificance = args[1].uint8;

  ZDO_ZdpReq(&zdpReq);
}

/**************************************************************************//**
\brief ZDP device announce response callback

\param[in] leaveResp - pointer to response structure
******************************************************************************/
static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp)
{
  appSnprintf("setPermitJoinRsp %d\r\n", resp->respPayload.status);
}

ScanValue_t local;
bool doFindAndBind = false;
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
  AppbdbCommissioningreq.mode = determineCommissionMode(&local);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer1;   
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}
static void Callback_FormAndSteer(BDB_InvokeCommissioningConf_t *conf)
{
  aTimer.interval = 5;
  aTimer.mode     = TIMER_ONE_SHOT_MODE;
  aTimer.callback = aTimerFired;
  HAL_StartAppTimer(&aTimer);
}

static void processFormAndSteerCmd(const ScanValue_t *args)
{
  doFindAndBind = false;
  local.uint8 = 4;
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(&local);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer;   
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);
}

static void processFormSteerAndFBCmd(const ScanValue_t *args)
{
  doFindAndBind = true;
  local.uint8 = 4;
  memset(&AppbdbCommissioningreq,0,sizeof(BDB_InvokeCommissioningReq_t));
  AppbdbCommissioningreq.mode = determineCommissionMode(&local);
  AppbdbCommissioningreq.initiatorReq = NULL;
  AppbdbCommissioningreq.BDB_InvokeCommissioningConf = Callback_FormAndSteer;   
  BDB_InvokeCommissioning(&AppbdbCommissioningreq);  
}


static void processSetTCLKExchangeMethodCmd(const ScanValue_t *args)
{
  BDB_SetTCLKExchangeMethod(args[0].uint8);
  (void)args;
}
static void processSetTCLKMaxRetryAttemptsCmd(const ScanValue_t *args)
{
  BDB_SetTCLKRetryMaxAttempts(args[0].uint8);
  (void)args;
}

static void processSetTLRole(const ScanValue_t *args)
{
  BDB_SetToulinkRole(args[0].uint8);
  (void)args;
}

void myICCallback(InstallCode_Configuration_Status_t status)
{
  appSnprintf("Status = %d\r\n", status);
}

static void processSetInstallCodeCmd(const ScanValue_t *args)
{
  ExtAddr_t devAddr = 0xFFFFFFFFFFFFFFFF;
  uint8_t icode[18];
  hexStrTouint8array(args[0].str, icode, 18U);
  BDB_ConfigureInstallCode(devAddr, icode, myICCallback);
  (void)args;
}

static void zdoupdateResponse(ZDO_ZdpResp_t *resp)
{
  appSnprintf("Update Done %d\r\n", resp->respPayload.status);
}
static void processSendNwkUpdateReqCmd(const ScanValue_t *args)
{
  ZDO_MgmtNwkUpdateReq_t *mgmtupdatereq = &zdpReq.req.reqPayload.mgmtNwkUpdateReq;

  zdpReq.ZDO_ZdpResp = zdoupdateResponse;
  zdpReq.reqCluster = MGMT_NWK_UPDATE_CLID;
  zdpReq.dstAddrMode = APS_SHORT_ADDRESS;

  zdpReq.dstAddress.shortAddress = args[2].uint16;

  mgmtupdatereq->scanChannels = 1UL << args[0].uint8;
  mgmtupdatereq->scanDuration = args[1].uint8;
  mgmtupdatereq->nwkManagerAddr = 0;
  mgmtupdatereq->nwkUpdateId = NWK_GetUpdateId() + 1;
  mgmtupdatereq->scanCount = 0;

  ZDO_ZdpReq(&zdpReq);
}

/**************************************************************************//**
\brief Processes Set Permit Join command

\param[in] args - array of command arguments
******************************************************************************/
//static void processSetPermitJoinCmd(const ScanValue_t *args)
//{
//  ZDO_MgmtPermitJoiningReq_t *permit = &zdpReq.req.reqPayload.mgmtPermitJoiningReq;
//
//  zdpReq.ZDO_ZdpResp = zdoPermitJoiningResponse;
//  zdpReq.reqCluster = MGMT_PERMIT_JOINING_CLID;
//  zdpReq.dstAddrMode = APS_SHORT_ADDRESS;
//
//  zdpReq.dstAddress.shortAddress = NWK_GetShortAddr();
//
//  permit->permitDuration = args[0].uint8;
//  permit->tcSignificance = 0x01;
//
//  ZDO_ZdpReq(&zdpReq);
//}

/**************************************************************************//**
\brief Processes Set Permit Join command

\param[in] args - array of command arguments
******************************************************************************/
static void processMgmtSendPermitJoinCmd(const ScanValue_t *args)
{
  ZDO_MgmtPermitJoiningReq_t *permit = &zdpReq.req.reqPayload.mgmtPermitJoiningReq;

  zdpReq.ZDO_ZdpResp = zdoPermitJoiningResponse;
  zdpReq.reqCluster = MGMT_PERMIT_JOINING_CLID;
  zdpReq.dstAddrMode = APS_SHORT_ADDRESS;

  zdpReq.dstAddress.shortAddress = args[0].uint16;

  permit->permitDuration = args[1].uint8;
  permit->tcSignificance = args[2].uint8;

  ZDO_ZdpReq(&zdpReq);
}

static void processMgmtSendBindReqCmd(const ScanValue_t *args)
{
  zdpMgmtBindReq(args[0].uint16, args[1].uint8);
}

static void processMgmtSendLqiReqCmd(const ScanValue_t *args)
{
  zdpMgmtLqiReq(args[0].uint16);
}

static void processMgmtSendLeaveReqCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[1].uint32 << 32);
  extAddr |= args[2].uint32;
  zdpMgmtLeaveReq(args[0].uint16, extAddr, args[3].uint8, args[4].uint8);
}
/**************************************************************************//**
\brief ZDP device announce response callback

\param[in] leaveResp - pointer to response structure
******************************************************************************/
//static void zdoPermitJoiningResponse(ZDO_ZdpResp_t *resp)
//{
//  LOG_STRING(permitJoinDoneStr, "setPermitJoinRsp %d\r\n");
//  appSnprintf(permitJoinDoneStr, resp->respPayload.status);
//}

/**************************************************************************//**
\brief Set type routine completion callback
******************************************************************************/
static void setTypeDone(void)
{
  appSnprintf("Done\r\n");
}
/**************************************************************************//**
\brief Processes Set Target Type command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetTargetTypeCmd(const ScanValue_t *args)
{
  N_LinkTarget_SetTargetType(args[0].uint8, setTypeDone);
}

/**************************************************************************//**
\brief Processes Set Allow steal command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetAllowStealCmd(const ScanValue_t *args)
{
  N_LinkTarget_AllowStealing(args[0].uint8);
}

/**************************************************************************//**
\brief Processes Set Allow steal command

\param[in] args - array of command arguments
******************************************************************************/
static void processSetAllowTLResetToFNCmd(const ScanValue_t *args)
{
  BDB_SetAllowTLResetToFN(args[0].uint8);
}
/**************************************************************************//**
\brief Processes mac ban node command

\param[in] args - array of command arguments
******************************************************************************/
static void processMacBanNodeCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[0].uint32 << 32);
  extAddr |= args[1].uint32;

  MAC_BanNode(0, extAddr, 4, args[2].uint8);
  appSnprintf("Done\r\n");
}

/**************************************************************************//**
\brief Processes mac ban node command

\param[in] args - array of command arguments
******************************************************************************/
static void processMacResetBanTableCmd(const ScanValue_t *args)
{

  MAC_ResetBanTable();
  appSnprintf("Done\r\n");
  (void)args;
}

/**************************************************************************//**
\brief Processes Simple Descriptor request command

\param[in] args - array of command arguments
******************************************************************************/
void processSimpleDescriptorRequestCmd(const ScanValue_t *args)
{
  zdpSimpleDescReq(args[0].uint16,args[1].uint8);

}
/**************************************************************************//**
\brief Processes Match Descriptor request command

\param[in] args - array of command arguments
******************************************************************************/
void processMatchDescriptorRequestCmd(const ScanValue_t *args)
{
  zdpMatchDescReq(args[0].uint16,args[1].uint8);
}

/**************************************************************************//**
\brief Processes Node Descriptor request command

\param[in] args - array of command arguments
******************************************************************************/
void processNodeDescriptorRequestCmd(const ScanValue_t *args)
{
  zdpNodeDescReq(args[0].uint16,args[1].uint16);
}

/**************************************************************************//**
\brief Processes ieee Addr request command

\param[in] args - array of command arguments
******************************************************************************/
void processIeeeAddrRequestCmd(const ScanValue_t *args)
{
  zdpIeeeAddrReq(args[0].uint16,args[1].uint16, args[2].uint8);
}

/**************************************************************************//**
\brief Processes Nwk Addr request command

\param[in] args - array of command arguments
******************************************************************************/
void processNwkAddrRequestCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[1].uint32 << 32);
  extAddr |= args[2].uint32;
  zdpNwkAddrReq(args[0].uint16,extAddr, args[3].uint8);
}

/**************************************************************************//**
\brief Processes Active EP request command

\param[in] args - array of command arguments
******************************************************************************/
void processActiveEpRequestCmd(const ScanValue_t *args)
{
  zdpActiveEpReq(args[0].uint16,args[1].uint16);
}

/**************************************************************************//**
\brief Processes BindReq command

\param[in] args - array of command arguments
******************************************************************************/
static void processBindReqCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[2].uint32 << 32);
  extAddr |= args[3].uint32; 
  zdpBindReq(determineAddressMode(args), args[1].uint16, extAddr, args[4].uint8, args[5].uint16);
}
static void processBindReqCmdWithSrcAddrDestEndpoint(const ScanValue_t *args)
{
  ExtAddr_t extAddrSrc = ((uint64_t)args[2].uint32 << 32);
  extAddrSrc |= args[3].uint32;
  ExtAddr_t extAddrDst = ((uint64_t)args[4].uint32 << 32);
  extAddrDst |= args[5].uint32;
  zdpBindReqWithSrcAddrDestEndpoint(determineAddressMode(args), args[1].uint16, extAddrSrc, extAddrDst, args[6].uint8, args[7].uint8, args[8].uint16);
}
static void processUnBindReqCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[2].uint32 << 32);
  extAddr |= args[3].uint32; 
  zdpUnBindReq(determineAddressMode(args), args[1].uint16, extAddr, args[4].uint8, args[5].uint16);  
}
static void processUnBindReqCmdWithSrcAddrDestEndpoint(const ScanValue_t *args)
{
  ExtAddr_t extAddrSrc = ((uint64_t)args[2].uint32 << 32);
  extAddrSrc |= args[3].uint32;
  ExtAddr_t extAddrDst = ((uint64_t)args[4].uint32 << 32);
  extAddrDst |= args[5].uint32;
  zdpUnBindReqWithSrcAddrDestEndpoint(determineAddressMode(args), args[1].uint16, extAddrSrc, extAddrDst, args[6].uint8, args[7].uint8, args[8].uint16);  
}
static void processNwkLeaveReqCmd(const ScanValue_t *args)
{
  ExtAddr_t extAddr = ((uint64_t)args[0].uint32 << 32);
  extAddr |= args[1].uint32;
  nwkLeaveCommand(extAddr, args[2].uint8, args[3].uint8);
}

static N_Beacon_t beacon;
static void assocDiscoveryDone(N_Connection_Result_t result)
{

}
static void processSendBeaconReqCmd(const ScanValue_t *args)
{
   N_Connection_AssociateDiscovery(&beacon, N_Connection_AssociateDiscoveryMode_AnyPan, NULL, assocDiscoveryDone);
}

void ResetTargetCallback(ResetTargetStatus_t status)
{
  appSnprintf("Status = %d\r\n", status);}


static void processTargetToFnCmd(const ScanValue_t *args)
{
  BDB_ResetVia_TouchlinkCluster(ResetTargetCallback);
}

#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#if ZCL_COMMANDS_IN_CONSOLE == 1
static void processReadOnOffAttrVal(const ScanValue_t *args)
{
  appSnprintf("%d\r\n", dlOnOffClusterServerAttributes.onOff.value);
}

static void processReadCurrentLevelAttrVal(const ScanValue_t *args)
{
  appSnprintf("%d\r\n", dlLevelControlClusterServerAttributes.currentLevel.value);
}
#endif // #if BDB_COMMANDS_IN_CONSOLE == 1

#ifdef UNUSED
#endif

#endif // APP_ENABLE_CONSOLE == 1

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlConsole.c
