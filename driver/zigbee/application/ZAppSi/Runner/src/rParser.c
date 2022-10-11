/**************************************************************************//**
  \file  rParser.c

  \brief Command parser implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
  Last change:
    $Id: rParser.c 33020 2019-05-08 13:31:28Z I41611 $

 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysUtils.h>
#include <aps/include/aps.h>
#include <systemenvironment/include/sysQueue.h>
//#include <leds.h>
#include <rMac.h>
#include <rAps.h>
#include <rNwk.h>
#include <rZcl.h>
#include <rZdo.h>
#include <rSys.h>
#include <rTc.h>
#include <rExtensions.h>
#include <rAux.h>
#include <ZAppSiSerialManager.h>
#include <rDebug.h>
#include <rEvents.h>
#include <bufferallocator.h>
#include <rHal.h>
#include <zigbee/ZAppSi/z3commonfiles/include/console.h>
#if APP_USE_OTAU == 1
#include <rOtauCluster.h>
#endif // APP_USE_OTAU
#ifdef ZSE_ESP_CLUSTERS_LOGIC
#include <rPriceCluster.h>
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
#include <ZAppSiIdentifiers.h>

#ifdef _ENABLE_PERSISTENT_SERVER_
#include <pds/include/wlPdsMemIds.h>
#endif // _ENABLE_PERSISTENT_SERVER_

#ifdef _INTERPAN_
#include <rInterpan.h>
#endif //_INTERPAN_

#if (BDB_SUPPORT == 1)
#include <rBdb.h>
#endif
/******************************************************************************
                   Static functions prototypes section
 ******************************************************************************/
void rApsDataInd(APS_DataInd_t *ind, uint8_t endpoint);

#ifdef ZSE_ESP_CLUSTERS_LOGIC
static void keepNextFrameConf(ZS_CommandBuffer_t *commandBuffer);
static void rKeepNextFrame(ZS_CommandBuffer_t *commandBuffer);
#endif

static void rSendUnsupportedCommandId(uint16_t unsupId);

#ifdef _USE_RTOS_
void APP_UartEvtUpload(ZS_CommandBuffer_t* cmdBuf);
#endif
/******************************************************************************
                   Global variables section
 ******************************************************************************/
uint16_t lastCommandId;
ZS_CommandBuffer_t *currentCommand = NULL;
#ifdef ZSE_ESP_CLUSTERS_LOGIC
uint8_t keepNextFrame = 0;
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
/******************************************************************************
                   Static variables section
 ******************************************************************************/
static DECLARE_QUEUE(rParserInCmdQueue);

static PROGMEM_DECLARE(CommandRecord_t commandHandlers[]) = {
#ifdef _MAC_BAN_NODE_
  {R_MAC_BAN_REQUEST, rMacBanRequestProcess},
  {R_MAC_BAN_ALL_REQUEST, rMacBanAllRequestProcess},
#endif /* _MAC_BAN_NODE_ */
  {R_MAC_MCPS_DATA_REQUEST, rMacDataRequestProcess},
  {R_MAC_WRITE_REGISTER_REQUEST, rMacAccessRegisterRequestProcess},
  {R_SYS_RESET_REQUEST, rSysResetRequestProcess},
  {R_SYS_POWER_OFF_REQUEST, rSysPowerOffRequestProcess},
  {R_SYS_SET_REQUEST, rSysSetRequestProcess},
  {R_SYS_GET_REQUEST, rSysGetRequestProcess},
  {R_SYS_START_REQUEST, rSysStartRequestProcess},
#if (BDB_SUPPORT == 1)  
  {R_BDB_INVOKE_COMMISSIONING_REQ, rBdbInvokeCommissioningProcess},
  {R_BDB_SET_INSTALL_CODE_REQ, rBdbSetInstallCodeProcess},
#endif  
  {R_SYS_SET_DEVICE_TYPE_REQUEST, rSysSetDeviceTypeRequestProcess},
  {R_SYS_SLEEP_WHEN_IDLE_REQUEST, rSysSleepWhenIdleProcess},
  {R_ZDO_SLEEP_REQUEST, rZdoSleepRequestProcess},
  {R_ZDO_WAKEUP_INDICATION, rZdoWakeupIndicationProcess},
  {R_ZDO_MGMT_NWK_UPDATE_NOTIFY, rZdoMgmtNwkUpdateNotifyProcess},
  {R_NWK_SET_SHORT_ADDRESS_REQUEST, rNwkSetShortAddressRequestProcess},
#if defined _PROFILER_
  {R_NWK_PROFILER_REQUEST, rNwkProfilerRequestProcess},
#endif // _PROFILER_
#if defined(_NWK_DIRECT_JOIN_) && defined(_FFD_)
  {R_NLME_DIRECT_JOIN_REQUEST, rNwkDirectJoinRequestProcess},
#endif //_NWK_DIRECT_JOIN_ && _FFD_
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
  {R_NLME_JOIN_REQUEST, rNwkJoinRequestProcess},
#endif // defined(_ROUTER_) || defined(_ENDDEVICE_)
#if defined(_ROUTER_)
  {R_NLME_START_ROUTER_REQUEST, rNwkStartRouterRequestProcess},
#endif // defined(_ROUTER_)
  {R_NLME_RESET_REQUEST, rNwkResetRequestProcess },
  {R_NLME_NETWORK_DISCOVERY_REQUEST, rNwkDiscoveryRequestProcess },
  {R_NWK_ADDR_RESOLV_REQUEST, rNwkAddrResolvRequestProcess},
  {R_NWK_LEAVE_REQUEST, rNwkLeaveRequestProcess},
#if defined(_ROUTER_) || defined(_COORDINATOR_)
  {R_NLME_PERMIT_JOINING_REQUEST, rNwkPermitJoiningRequestProcess},
  {R_NWK_GET_NEXT_HOP_REQUEST, rNwkGetNextHopRequestProcess},
#if defined _NWK_MESH_ROUTING_
#ifdef _CERTIFICATION_
  {R_NWK_SET_NEXT_HOP_REQUEST, rNwkSetNextHopRequestProcess},
#endif //#ifdef _CERTIFICATION_
#endif //#if defined _NWK_MESH_ROUTING_ 
#if defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_
  {R_NLME_ROUTE_DISCOVERY_REQUEST, rNwkRouteDiscoveryRequestProcess},
  {R_NWK_SET_ROUTE_FAIL_ORDER_REQUEST, rNwkSetRouteFailOrderProcess},
#if defined _CERTIFICATION_ && defined _NWK_FAST_ROUTE_DISCOVERY_
  {R_NWK_SET_FAST_ROUTE_DISCOVERY_REQUEST, rNwkSetFastRouteDiscoveryProcess},
#endif /* _CERTIFICATION_ and _NWK_FAST_ROUTE_DISCOVERY_ */
#endif /* _NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_ */
#endif //defined(_ROUTER_) || defined(_COORDINATOR_)
#ifdef _SECURITY_
  {R_NWK_GET_OUT_SEC_COUNTER_REQUEST, rNwkGetOutSecurityCounterRequestProcess},
#ifdef _NWK_IN_FRAME_COUNTERS_
  {R_NWK_SET_IN_SEC_COUNTER_REQUEST, rNwkSetInSecurityCounterRequestProcess},
  {R_NWK_GET_IN_SEC_COUNTER_REQUEST, rNwkGetInSecurityCounterRequestProcess},
#endif // _NWK_IN_FRAME_COUNTERS_
  {R_APSME_TRANSPORT_KEY_REQUEST, rApsTransportKeyRequestProcess},
  {R_APSME_UPDATE_DEVICE_REQUEST, rTcKeyUpdateRequestProcess},
  {R_APSME_REMOVE_DEVICE_REQUEST, rTcRemoveDeviceRequestProcess},
  {R_APSME_SWITCH_KEY_REQUEST, rApsSwitchKeyRequestProcess},
#ifdef _LINK_SECURITY_
  {R_APS_GET_OUT_SEC_COUNTER_REQUEST, rApsGetOutSecurityCounterRequestProcess},
  {R_APSME_REQUEST_KEY_REQUEST, rApsRequestKeyRequestProcess},
#endif // _LINK_SECURITY_
#endif //_SECURITY_
  {R_APSME_RESET_REQ, rApsResetRequestProcess},
  {R_APSME_START_REQ, rApsStartRequestProcess},
  {R_APSDE_DATA_REQUEST, rApsDataRequestProcess},
  {R_APSME_GET_REQUEST, rApsGetRequestProcess},
  {R_APSME_SET_REQUEST, rApsSetRequestProcess},
  {R_ZDO_NWK_ADDR_REQUEST, rZdoNwkAddrRequestProcess},
  {R_ZDO_MGMT_LEAVE_REQUEST, rZdoMgmtLeaveRequestProcess},
  {R_ZDO_MGMT_PERMIT_JOINING_REQUEST, rZdoMgmtPermitJoiningRequestProcess},
#ifdef _ENDDEVICE_
  {R_ZDO_START_SYNC_REQUEST, rZdoStartSyncReqProcess},
  {R_ZDO_STOP_SYNC_REQUEST, rZdoStopSyncReqProcess},
#endif //_ENDDEVICE_
  {R_ZDO_GET_NEIB_AMOUNT_REQUEST, rZdoGetNeibAmountProcess},
  {R_ZDO_GET_NEIB_TABLE_REQUEST, rZdoGetNeibTableProcess},

#if APP_ZDP_REQUESTS
  {R_ZDO_IEEE_ADDR_REQUEST, rZdoIeeeAddrRequestProcess},
  {R_ZDO_NODE_DESC_REQUEST, rZdoNodeDescRequestProcess},
  {R_ZDO_POWER_DESC_REQUEST, rZdpPowerDescRequestProcess},
  {R_ZDO_SIMPLE_DESC_REQUEST, rZdpSimpleDescRequestProcess},
  {R_ZDO_ACTIVE_EP_DESC_REQUEST, rZdpActiveEPRequestProcess},
  {R_ZDO_COMPLEX_DESC_REQUEST, rZdpComplexDescRequestProcess},
#ifdef _PARENT_ANNCE_  
  {R_ZDO_PARENT_ANNOUNCE_REQUEST, rZdpParentAnnceRequestProcess},  
#endif
  {R_ZDO_USER_DESC_REQUEST, rZdpUserDescRequestProcess},
  {R_ZDO_END_DEVICE_ANNCE_REQUEST, rZdpEndDeviceAnnceRequestProcess},
  {R_ZDO_MGMT_LQI_REQUEST, rZdpLqiRequestProcess},
  {R_ZDO_USER_DESC_SET_REQUEST, rZdpUserDescSetRequestProcess},
  {R_ZDO_MGMT_NWK_UPDATE_REQUEST, rZdoNwkUpdateRequestProcess},
  {R_ZDP_SYSTEM_DISCOVERY_REQUEST, rZdpSystemServerDiscoveryRequestProcess},
  {R_ZDO_MGMT_RTG_REQUEST, rZdpRtgRequestProcess},

#ifdef _BINDING_
  {R_APSME_BIND_REQUEST, rApsBindRequestProcess},
  {R_APSME_UNBIND_REQUEST, rApsUnbindRequestProcess},
  {R_ZDO_MATCH_DESC_REQUEST, rZdpMatchDescRequestProcess},
  {R_ZDO_BIND_REQUEST, rZdpBindRequestProcess},
  {R_ZDO_UNBIND_REQUEST, rZdpUnbindRequestProcess},
#ifdef _END_DEVICE_BINDING_
  {R_ZDO_END_DEVICE_BIND_REQUEST, rZdpEndDeviceBindRequestProcess},
#endif // _END_DEVICE_BINDING_
  {R_ZDO_MGMT_BIND_REQUEST, rZdpMgmtBindRequestProcess},
#endif // _BINDING_
#endif // APP_ZDP_REQUESTS

#ifdef _APS_MULTICAST_
  {R_AF_INDIRECT_REQUEST, rAfIndirectRequestProcess},
  {R_AF_DIRECT_REQUEST, rAfDirectRequestProcess},
  {R_AF_GROUP_REQUEST, rAfGroupRequestProcess},
  {R_APSME_ADD_GROUP_REQUEST, rApsAddGroupRequestProcess},
  {R_APSME_REMOVE_GROUP_REQUEST, rApsRemoveGroupRequestProcess},
  {R_APSME_REMOVE_ALL_GROUPS_REQUEST, rApsRemoveAllGroupsRequestProcess},
#endif

#ifdef _ZCL_SUPPORT_ 
  {R_ZCL_START_REQUEST, rZclStartRequestProcess},
  {R_ZCL_ATTRIBUTE_REQUEST, rZclAttributeRequestProcess},
  {R_ZCL_COMMAND_REQUEST, rZclCommandRequestProcess},
  {R_ZCL_ATTRIBUTE_VALUE, rZclAttributeValueProcess},
  {R_ZCL_SET_CLUSTER_SECURITY_REQUEST, rZclClusterSecurityProcess},
  {R_ZCL_NEXT_SEQUENCE_NUMBER_REQ, rZclNextSequenceNumberReqProcess},
  {R_ZCL_START_REPORTING_REQUEST, rZclStartReportingRequestProcess},
#if (defined _LINK_SECURITY_) && (!defined _LIGHT_LINK_PROFILE_)
  {R_ZCL_GET_REQUEST, rZclCommandGetProcess},
  {R_ZCL_SET_REQUEST, rZclCommandSetProcess},
#if (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
  {R_ZSE_SET_KE_TIMEOUTS_REQUEST, rZclSetKETimeoutsProcess},
  {R_ZSE_PASS_BAD_CERTIFS_REQUEST, rZclPassBadCertificatesProcessing},
  {R_ZSE_KE_OUT_OF_ORDER_REQUEST, rZclKeOutOfOrderProcessing},
#endif // (CERTICOM_SUPPORT == 1) && (defined _ZSE_CERTIFICATION_)
#endif // #if (defined _LINK_SECURITY_) && (!defined _LIGHT_LINK_PROFILE_)
  {R_ZCL_START_SECURITY_REQUEST, rZclStartSecurityRequestProcess},
#endif // ZCL_SUPPORT

  {R_ZDO_SET_TX_POWER_REQUEST, rZdoSetTxPowerRequestProcess},

#ifdef ZSE_ESP_CLUSTERS_LOGIC
  {R_KEEP_NEXT_FRAME, rKeepNextFrame},
#endif

#ifdef _INTERPAN_
  {R_INTRP_DATA_REQ, rIntrpDataReq},
#endif //_INTERPAN_

#if APP_USE_OTAU == 1
  {R_OTAU_CLIENT_START, rOtauClientStart},
#endif // APP_USE_OTAU

#if defined(_SECURITY_) && defined _LINK_SECURITY_
  {R_AUX_GET_LINK_KEY_HASH_REQUEST, rAuxGetLinkKeyHashRequestProcess},
#endif

#if defined _CERTIFICATION_ && defined _LINK_SECURITY_
  {R_APS_UPDATE_SECURITY_POLICY_REQUEST, rApsUpdateSecurityPolicyProcess},
#endif /* _CERTIFICATION_ and _LINK_SECURITY_ */
  {R_HAL_START_APP_TIMER_REQ, rHalStartAppTimerProcess},
  {R_SYS_EVENT_MGMT_REQUEST, rSysEventMgmtProcess},

#ifdef _ZSE_CERTIFICATION_
  {R_APS_SET_FRAME_COUNTER_REQUEST, rApsSetFrameCounterRequest},
  {R_ZCL_KE_SEND_TOO_LONG_CERTIFICATE_REQUEST, rZclKeSecSendTooLongCertificate},
#endif  // _ZSE_CERTIFICATION_
  
  {R_SYS_ASSERT_INDICATION, rSysAssertNotifyProcess},  


#ifdef _CHILD_MANAGEMENT_
  {R_NWK_END_DEVICE_TIMEOUT_REQUEST, rNwkEndDeviceTimeoutRequestProcess},
#if defined(_ROUTER_) || defined(_COORDINATOR_)
  {R_NWK_SET_ED_TIMEOUT_BY_PARENT_REQ, rNwkSetEDTimeoutByParentProcess},
#endif
#endif /* _CHILD_MANAGEMENT_ */
#ifdef _SECURITY_
  {R_NWK_SET_OUT_SEC_COUNTER_REQUEST, rNwkSetOutgoingSecFrameCounter},
  {R_NWK_SET_ACTIVE_KEY_SEQ_NUM_REQUEST, rNwkGetActiveKeySeqNum},
#ifdef _LINK_SECURITY_
  {R_ZDO_VERIFY_KEY_REQUEST, rZdoVerifyKeyRequestProcess},
#endif //#ifdef _LINK_SECURITY_
#endif // _SECURITY_
  {R_NWK_ADD_ADDRESSMAP_ENTRY_REQ, rNwkAddAddressMapReqProcess},
  {R_NWK_REMOVE_NEIGHBOR_ENTRY_REQ, rNwkRemoveNeighborEntryProcess},
#if defined (_SECURITY_) && defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
  {R_TC_POLICY_REQUEST_REQ, rTCPolicySetRequestProcess},
#endif //#if defined (_SECURITY_) && defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
#ifdef _GREENPOWER_SUPPORT_
  {R_APSDE_DATA_ALIAS_REQUEST, rApsDataRequestWithAliasProcess}
#endif  //_GREENPOWER_SUPPORT_

};
/******************************************************************************
                   Implementations section
 ******************************************************************************/
void rParserTaskHandler(void)
{
  ZS_CommandBuffer_t *commandBuffer;
  //Next variable was made static for IAR ARM Compiler bug prevention
  static CommandRecord_t cmdRecord;
  uint8_t i;

  while (NULL != (commandBuffer = (ZS_CommandBuffer_t *) getQueueElem(&rParserInCmdQueue)))
  {
    deleteHeadQueueElem(&rParserInCmdQueue);
    lastCommandId = commandBuffer->commandFrame.commandId;
    currentCommand = commandBuffer;

    //BSP_OffLed(LED_YELLOW);

    for (i = 0; i < ARRAY_SIZE(commandHandlers); i++)
    {
      memcpy_P(&cmdRecord, &commandHandlers[i], sizeof (CommandRecord_t));

      if (cmdRecord.id == lastCommandId)
      {
#ifdef ZSE_ESP_CLUSTERS_LOGIC
        if (0 != keepNextFrame)
        {
          keepNextFrameConf(commandBuffer);
        }
        else
        {
          cmdRecord.handler(commandBuffer);
        }
#else
        cmdRecord.handler(commandBuffer);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
        cmdRecord.id = (CommandID_t)0;
        break;
      }
    }

    if (cmdRecord.id) // Handler was not called
    {
      //BSP_OffLed(LED_GREEN);
      rSendUnsupportedCommandId(lastCommandId);
      currentCommand = NULL;
    }
    bufferAllocator.free(commandBuffer);
  }
}

/***************************************************************************//**
\brief Assigned handler for incoming frames.
\param[in] commandBuffer - incoming buffer
\return none
******************************************************************************/
void incomingFrameHandler(ZS_CommandBuffer_t *commandBuffer)
{
  if(!putQueueElem(&rParserInCmdQueue, commandBuffer))
  {
    /* failed to queue */
  }

   APP_UartEvtUpload(commandBuffer);

}

/***************************************************************************//**
\brief Generates and sends "unsupported command id"
\param[in] unsupId - unsupported command id
******************************************************************************/
static void rSendUnsupportedCommandId(uint16_t unsupId)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

  confBuffer->commandFrame.commandId = R_SYS_UNSUPPORTED_COMMAND;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RSysUnsupCommand_t);
  confBuffer->commandFrame.payload[0] = (uint8_t)(unsupId);
  confBuffer->commandFrame.payload[1] = (uint8_t)(unsupId>>8);
  serialManager.write(confBuffer);
}

#ifdef ZSE_ESP_CLUSTERS_LOGIC
/**//**
 brief Frame saving confirmation

This function is used for following: \n
1. to notify cluster about new configuration frame \n
2. send confirmation about configuration frame receiving \n

\param commandBuffer[in]  input bufer to save frame
\return none
 */
static void keepNextFrameConf(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

  setPriceAutoResponse(&commandBuffer->commandFrame);
  keepNextFrame = 0;


  confBuffer->commandFrame.commandId = R_KEEP_NEXT_FRAME_CONF;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE;
  serialManager.write(confBuffer);
}
/**//**
 brief Indicate to Runner to keep next payload and not sent to air

It is used to set parameters for autoresponse.

\param commandBuffer[in] not used
\return none
 */
static void rKeepNextFrame(ZS_CommandBuffer_t *commandBuffer)
{
  keepNextFrame = 1;
}
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
/* eof rParser.c */
