/**************************************************************************//**
  \file  rSys.c

  \brief Systme related commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
    19/05/2014  karthik.p_u     - Modified
  Last Change:  
    $Id: rSys.c 33164 2019-09-13 11:36:44Z I41664 $
 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
//#include <leds.h>
#include <rDebug.h>
#include <rTypes.h>
#include <rMem.h>
#include <rParser.h>
//#include <resetReason.h>
#include <rZcl.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <systemenvironment/include/sysUtils.h>
#include <pds/include/wlPdsMemIds.h>
#include <bufferallocator.h>
#include <ZAppSiSerialManager.h>
#include <mac_phy/include/macBanNode.h>
#include <zdo/include/zdoPermissions.h>
#include <nwk/include/nwkNeighbor.h>
#include <systemenvironment/include/sysIdleHandler.h>
#include <aps/include/apsAIB.h>
#include <nwk/include/nwkEndDeviceTimeout.h>
#include <zigbee/ZAppSi/z3commonfiles/include/errH.h>
#include <pds/include/bcPDS.h>

/******************************************************************************
                   Defines section
 ******************************************************************************/
#define R_SYS_ZDO_REQ_FRAME_TESTING  1
#define R_SYS_ZDO_RESP_FRAME_TESTING  2
/******************************************************************************
                              External variables section
******************************************************************************/
extern ZS_CommandBuffer_t *currentCommand;
extern 	void nwkSetEndDeviceDefaultTimeout(NwkEndDeviceTimeout_t value);
extern uint32_t APS_GetParentAnnounceTimer(void);
#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
extern SYS_EventReceiver_t zdoReqCmdRxdReceiver;
extern SYS_EventReceiver_t zdoReqCmdValidation;
extern SYS_EventReceiver_t zdoRspCmdValidation;
#endif
/******************************************************************************
                              Prototype section
******************************************************************************/
static uint32_t getUsedFeatures(void);


#if (APP_INTERFACE == APP_INTERFACE_VCP)
static void rResetStackConf(ZDO_Status_t status);
static void rResetStack(void);
#endif /* APP_INTERFACE == APP_INTERFACE_VCP */
/******************************************************************************
                   Implementations section
 ******************************************************************************/
void rSysGetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t status = ZS_SUCCESS_STATUS;
  bool withContextSwitch = false;

  sysAssert(commandBuffer, R_DBG_RSYS_NULL_POINTER);

  ZS_SysGetReq_t *req = (ZS_SysGetReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_SysGetConf_t *conf = (ZS_SysGetConf_t *) confirmBuffer->commandFrame.payload;
  uint32_t usedFeature, leUsedFeature;
  uint16_t parentInfo, leParentInfo;
  uint16_t parentAnnounceTimer, leParentAnnounceTimer;
  uint8_t frameLength = R_COMMAND_ID_SIZE;
  frameLength += sizeof(conf->attributeId);
  frameLength += sizeof(conf->status);
  frameLength += sizeof(conf->attributeLength);

  union
  {
    uint64_t u64;
#ifdef _SECURITY_
    RTcSetDeviceKeyRequest_t tcSetDeviceKeyReq;
#endif /* _SECURITY_ */
  } attributeValue;

  switch (req->attributeId)
  {
    case ZS_CHANNEL_MASK_ATTR_ID:
      {
        uint32_t cpuChannelMask;
        uint32_t leChannelMask;
        CS_ReadParameter(CS_CHANNEL_MASK_ID, &cpuChannelMask);
        leChannelMask = CPU_TO_LE32(cpuChannelMask);
        memcpy(&attributeValue, &leChannelMask, sizeof(uint32_t));
        frameLength += sizeof (uint32_t);
        break;
      }

    case ZS_CHANNEL_PAGE_ATTR_ID:
      {
        uint8_t channelPage;
        CS_ReadParameter(CS_CHANNEL_PAGE_ID, &channelPage);
        memcpy(&attributeValue, &channelPage, sizeof(uint8_t));
        frameLength += sizeof (uint8_t);
        break;
      }

    case ZS_END_DEVICE_TIMEOUT_ATTR_ID:
      {
        frameLength += sizeof (uint8_t);        
        CS_ReadParameter(CS_END_DEVICE_TIMEOUT_ID, &attributeValue);
      }
      break;

    case ZS_EXTENDED_PANID_ATTR_ID:
      frameLength += sizeof (uint64_t);
      CS_ReadParameter(CS_EXT_PANID_ID, &attributeValue);
      break;

    case ZS_ADDRESS_ASSIGNMENT_METHOD_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_ADDRESS_ASSIGNMENT_METHOD_ID, &attributeValue);
      break;

    case ZS_PROTOCOL_VERSION_ATTR_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_PROTOCOL_VERSION_ID, &attributeValue);
      break;

    case ZS_STACK_PROFILE_ATTR_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_STACK_PROFILE_ID, &attributeValue);
      break;

    case ZS_PERMIT_DURATION_ATTR_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_PERMIT_DURATION_ID, &attributeValue);
      break;

    case ZS_INDIRECT_POLL_RATE_ATTR_ID:
      frameLength += sizeof (uint32_t);
      CS_ReadParameter(CS_INDIRECT_POLL_RATE_ID, &attributeValue);
      break;

    case ZS_END_DEVICE_SLEEP_PERIOD_ATTR_ID:
      frameLength += sizeof (uint32_t);
      CS_ReadParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &attributeValue);
      break;
#ifdef _NWK_CONCENTRATOR_
    case ZS_CONCENTRATOR_DISCOVERY_TIME_ATTR_ID:
      frameLength += sizeof (uint32_t);
      CS_ReadParameter(CS_CONCENTRATOR_DISCOVERY_TIME_ID, &attributeValue);
      break;
#endif /* _NWK_CONCENTRATOR_ */
#ifdef _SECURITY_
    case ZS_ZDO_SECURITY_STATUS_ATTR_ID:
      frameLength += sizeof (bool);
      CS_ReadParameter(CS_ZDO_SECURITY_STATUS_ID, &attributeValue);
      break;

    case ZS_NETWORK_KEY_ATTR_ID:
      frameLength += sizeof (uint8_t) * SECURITY_KEY_SIZE;
      CS_ReadParameter(CS_NETWORK_KEY_ID, &attributeValue);
      break;

    case ZS_TRUST_CENTER_ADDRESS_ATTR_ID:
      frameLength += sizeof (uint64_t);
      CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &attributeValue);
      break;
#endif /* _SECURITY_ */

    case ZS_RF_TX_POWER_ATTR_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_RF_TX_POWER_ID, &attributeValue);
      break;

    case ZS_RX_ON_WHEN_IDLE_ATTR_ID:
      frameLength += sizeof (bool);
      CS_ReadParameter(CS_RX_ON_WHEN_IDLE_ID, &attributeValue);
      break;

    case ZS_EXTENDED_ADDRESS_ATTR_ID:
      frameLength += sizeof (uint64_t);
      CS_ReadParameter(CS_UID_ID, &attributeValue);
      break;

    case ZS_NWK_USE_MULTICAST_ATTR_ID:
      frameLength += sizeof (bool);
      CS_ReadParameter(CS_NWK_USE_MULTICAST_ID, &attributeValue);
      break;

    case ZS_NWK_EXTENDED_PANID_ATTR_ID:
      frameLength += sizeof (uint64_t);
      CS_ReadParameter(CS_NWK_EXT_PANID_ID, &attributeValue);
      break;

    case ZS_NETWORK_ADDRESS_ATTR_ID:
      frameLength += sizeof (uint16_t);
      CS_ReadParameter(CS_NWK_ADDR_ID, &attributeValue);
      break;

    case ZS_NWK_PANID_ATTR_ID:
    case ZS_PANID_ATTR_ID:
      frameLength += sizeof (uint16_t);
      CS_ReadParameter(CS_NWK_PANID_ID, &attributeValue);
      break;

    case ZS_APS_MAX_FRAME_RETRIES_ATTR_ID:
      frameLength += sizeof (uint8_t);
      CS_ReadParameter(CS_APS_MAX_FRAME_RETRIES_ID, &attributeValue);
      break;

    case ZS_USED_FEATURES_ATTR_ID:
      frameLength += sizeof (uint32_t);
      usedFeature = getUsedFeatures();
      leUsedFeature = CPU_TO_LE32(usedFeature);
      memcpy(&attributeValue, &leUsedFeature, sizeof(uint32_t));
      break;

#ifdef _CHILD_MANAGEMENT_
        case ZS_NWK_PARENT_INFO_REQUEST:
          frameLength += sizeof (uint16_t);
          parentInfo = NWK_GetParentInformation();
          leParentInfo = CPU_TO_LE16(parentInfo);
          memcpy(&attributeValue, &leParentInfo, sizeof(uint16_t));
          break;

#ifdef _PARENT_ANNCE_
        case ZS_APS_PARENT_ANNOUNCE_TIMER_ID:
          frameLength += sizeof (uint16_t);
          parentAnnounceTimer = APS_GetParentAnnounceTimer();
          leParentAnnounceTimer = CPU_TO_LE16(parentAnnounceTimer);
          memcpy(&attributeValue, &leParentAnnounceTimer, sizeof(uint16_t));
          break;
#endif // _PARENT_ANNCE_
#endif //#ifdef _CHILD_MANAGEMENT_

    default:
      status = ZS_UNSUPPORTED_ATTRIBUTE_STATUS;
      frameLength += 1;
      break;
  }

  SYS_BYTE_MEMCPY(&conf->attributeValue, &attributeValue,
                    frameLength - (R_COMMAND_ID_SIZE + sizeof(conf->status) + sizeof(conf->attributeId) + sizeof(conf->attributeLength)));

  if (false == withContextSwitch)
  {
    //Prepare confirm
    confirmBuffer->commandFrame.length = frameLength;
    confirmBuffer->commandFrame.commandId = R_SYS_GET_CONFIRM;
    conf->status = status;
    conf->attributeId = req->attributeId;
    conf->attributeLength = frameLength - (R_COMMAND_ID_SIZE + sizeof(conf->status) + sizeof(conf->attributeId) + sizeof(conf->attributeLength));
    serialManager.write(confirmBuffer);
  }

  if (false == withContextSwitch)
  {
    //free buffer
    currentCommand = NULL;

  }
}

void rSysSetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t status = ZS_SUCCESS_STATUS;
  uint8_t frameLength = commandBuffer->commandFrame.length;
  uint8_t predictedFrameLength;

  ZS_SysSetReq_t *req = (ZS_SysSetReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_SysSetConf_t *conf = (ZS_SysSetConf_t *) confirmBuffer->commandFrame.payload;

  union
  {
    bool bl;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    bool boolean;
    RJoinControl_t joinCtrl;
#ifdef _SECURITY_
    RTcSetDeviceKeyRequest_t tcSetDeviceKeyReq;
#endif
#ifdef _PERMISSIONS_
    ExtAddr_t extAddr;
#endif /* _PERMISSIONS_ */
  } attributeValue;

  SYS_BYTE_MEMCPY(&attributeValue, &req->attributeValue, req->attributeLength);

#ifdef _LINK_SECURITY_
  TC_SetDeviceKey_t tcSetDeviceKeyReq;
#if defined _CERTIFICATION_
  ExtAddr_t universalExtAddress = 0xFFFFFFFFFFFFFFFF;
#endif
#endif

  predictedFrameLength = R_COMMAND_ID_SIZE;
  predictedFrameLength += sizeof(req->attributeId);
  predictedFrameLength += sizeof(req->attributeLength);

  switch (req->attributeId)
  {
    case ZS_CHANNEL_MASK_ATTR_ID:
      predictedFrameLength += sizeof (uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_CHANNEL_MASK_ID, &(uint32_t){LE32_TO_CPU(attributeValue.u32)});
      }
      break;
#if (BDB_SUPPORT == 1)
    case ZS_BDB_TC_LINK_KEY_EXCHANGE_METHOD:
      predictedFrameLength += sizeof(uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetTCLKExchangeMethod((uint8_t){attributeValue.u8});
      }
      break;
    case ZS_BDB_TRUST_CENTER_REQUIRE_KEY_EXCHANGE:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetTCRequireKeyExchange((uint8_t){attributeValue.u8});
      }
      break;
    case ZS_BDB_JOIN_USES_INSTALL_CODE_KEY:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetInstallCodeUsage((uint8_t){attributeValue.u8});
      }
      break;
    case ZS_BDB_TRUST_CENTER_NODE_JOIN_TIMEOUT:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetNodeJoinTimeout((uint8_t){attributeValue.u8});
      }
      break;
    case ZS_BDB_PRIMARY_CHANNEL_MASK:
      predictedFrameLength += sizeof(uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetChannelMask(PRIMARY_CHANNEL_MASK, (uint32_t){attributeValue.u32});
      }
      break;
    case ZS_BDB_SECONDARY_CHANNEL_MASK:
      predictedFrameLength += sizeof(uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetChannelMask(SECONDARY_CHANNEL_MASK, (uint32_t){attributeValue.u32});
      }
      break;
    case ZS_BDB_TRUST_CENTER_LINK_KEY_EXCHANGE_ATTEMPTS_MAX:
      predictedFrameLength += sizeof(uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        BDB_SetTCLKRetryMaxAttempts((uint8_t){attributeValue.u8});
      }
      break;
#endif // (BDB_SUPPORT == 1)
    case ZS_CHANNEL_PAGE_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_CHANNEL_PAGE_ID, &(uint8_t){attributeValue.u8});
      }
      break;
    case ZS_END_DEVICE_TIMEOUT_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_END_DEVICE_TIMEOUT_ID, &(uint8_t){attributeValue.u8});
		nwkSetEndDeviceDefaultTimeout((NwkEndDeviceTimeout_t)(attributeValue.u8));
      }
      break;
  
    case ZS_PROTOCOL_VERSION_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_PROTOCOL_VERSION_ID, &attributeValue);
      };
      break;

    case ZS_STACK_PROFILE_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_STACK_PROFILE_ID, &attributeValue);
      };
      break;

    case ZS_PERMIT_DURATION_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_PERMIT_DURATION_ID, &attributeValue);
      };
      break;

#ifdef _FFD_
    case ZS_PERMIT_REJOIN_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        NWK_SetRejoinPermit(attributeValue.u8);
      };
      break;
#endif /* _FFD_ */

    case ZS_INDIRECT_POLL_RATE_ATTR_ID:
      predictedFrameLength += sizeof (uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_INDIRECT_POLL_RATE_ID, &attributeValue);
      };
      break;


    case ZS_END_DEVICE_SLEEP_PERIOD_ATTR_ID:
      predictedFrameLength += sizeof (uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &attributeValue);
      };
      break;

    case ZS_RF_TX_POWER_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_RF_TX_POWER_ID, &attributeValue);
      };
      break;


    case ZS_RX_ON_WHEN_IDLE_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &attributeValue);
      }
      break;

    case ZS_EXTENDED_ADDRESS_ATTR_ID:
      predictedFrameLength += sizeof (uint64_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_UID_ID, &attributeValue);
      }
      break;


    case ZS_NWK_USE_MULTICAST_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_USE_MULTICAST_ID, &attributeValue);
      }
      break;

    case ZS_EXTENDED_PANID_ATTR_ID:
      predictedFrameLength += sizeof (uint64_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_EXT_PANID_ID, &attributeValue);
      };
      break;

    case ZS_NWK_EXTENDED_PANID_ATTR_ID:
      predictedFrameLength += sizeof (uint64_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_EXT_PANID_ID, &attributeValue);
      }
      break;

    case ZS_NIB_SYM_LINK_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        NWK_SetSymLink(attributeValue.bl);
      }
      break;

    case ZS_INIT_LOGICAL_CHANNEL_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_LOGICAL_CHANNEL_ID, &attributeValue);
      }
      break;

    case ZS_NWK_PANID_ATTR_ID:
    case ZS_PANID_ATTR_ID:
      predictedFrameLength += sizeof (uint16_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_PANID_ID, &attributeValue);
      }
      break;
      
#if defined(_DISTRIBUTED_SECURITY_) && defined(_ROUTER_)
    case ZS_DISTRIBUTED_SECURITY_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_DISTRIBUTED_SECURITY_ID, &attributeValue);
      }
      break;
#endif /* #if defined(_DISTRIBUTED_SECURITY_) && defined(_ROUTER_) */

    case ZS_NETWORK_ADDRESS_ATTR_ID:
      predictedFrameLength += sizeof (uint16_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        NWK_SetShortAddr(attributeValue.u16, false);
      }
      break;
    case ZS_UNIQUE_ADDR_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_UNIQUE_ADDR_ID, &attributeValue);
      }
      break;
#if defined _CERTIFICATION_
    case ZS_LEAVE_REQ_ALLOWED_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_LEAVE_REQ_ALLOWED_ID, &attributeValue);
      }
      break;
#endif
    case ZS_CERTIFICATION_CTRL_ATTR_ID:
      predictedFrameLength += sizeof (bool);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_CERTIFICATION_FLAG_ID, &attributeValue);
      }
      break;
    case ZS_APS_MAX_FRAME_RETRIES_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_APS_MAX_FRAME_RETRIES_ID, &attributeValue.u8);
      }
      break;
    case ZS_MAX_NEIGHBOR_ROUTE_COST_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_MAX_NEIGHBOR_ROUTE_COST_ID, &attributeValue.u8);
      }
      break;
#ifdef _NWK_CONCENTRATOR_
    case ZS_CONCENTRATOR_DISCOVERY_TIME_ATTR_ID:
      predictedFrameLength += sizeof (uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_CONCENTRATOR_DISCOVERY_TIME_ID, &attributeValue.u32);
      }
      break;
#endif /* _NWK_CONCENTRATOR_ */
    case ZS_PREDEFINED_PANID_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_NWK_PREDEFINED_PANID_ID, &attributeValue.u8);
      }
      break;

    case ZS_ADDRESS_ASSIGNMENT_METHOD_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_ADDRESS_ASSIGNMENT_METHOD_ID, &attributeValue.u8);
      }
      break;

#ifdef _LINK_SECURITY_
    case ZS_SECURITY_KEY_ATTR_ID:
      predictedFrameLength += sizeof (RTcSetDeviceKeyRequest_t);
      if (predictedFrameLength != frameLength)
        status = ZS_INVALID_PARAMETER_STATUS;
      else
      {
        tcSetDeviceKeyReq.deviceAddr = (ExtAddr_t*)GET_FIELD_PTR(
                             &attributeValue.tcSetDeviceKeyReq,
                             RTcSetDeviceKeyRequest_t,
                             extAddr);
#if defined _CERTIFICATION_
        if(universalExtAddress == attributeValue.tcSetDeviceKeyReq.extAddr)
           APS_DeleteKeyPair(&universalExtAddress,false);
#endif
        tcSetDeviceKeyReq.key = (uint8_t(*)[SECURITY_KEY_SIZE]) & attributeValue.tcSetDeviceKeyReq.key;
        tcSetDeviceKeyReq.keyType = (TC_KeyType_t) attributeValue.tcSetDeviceKeyReq.keyType;

        if (true == TC_SetDeviceKey(&tcSetDeviceKeyReq))
          status = ZS_SUCCESS_STATUS;
        else
          status = ZS_FAIL_STATUS;
      }
      break;
#endif /* _LINK_SECURITY_ */


#ifdef _SECURITY_
    case ZS_SECURITY_ON_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_SECURITY_ON_ID, &attributeValue);
      }
      break;

    case ZS_SEC_AUTH_TIMEOUT_REQUEST_ID:
      predictedFrameLength += sizeof (uint32_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_APS_SECURITY_TIMEOUT_PERIOD_ID, &attributeValue);
      }
      break;

    case ZS_ZDO_SECURITY_STATUS_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_ZDO_SECURITY_STATUS_ID, &attributeValue);
      }
      if(NOT_PRECONFIGURED == attributeValue.u8)
      {
        if(NWK_IsAnyKeyActivated())
          NWK_DeactivateKey();
      }
      break;
#if defined _CERTIFICATION_
    case ZS_NETWORK_KEY_AMOUNT_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t);
      status = ZS_INVALID_PARAMETER_STATUS;
      if (predictedFrameLength == frameLength)
        if (NWK_SUCCESS_STATUS == NWK_SetKeyAmount(attributeValue.u8))
          status = ZS_SUCCESS_STATUS;
      break;
#endif /* _CERTIFICATION_ */
    case ZS_NETWORK_KEY_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t) * SECURITY_KEY_SIZE;
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        if(SSP_IsKeyValid(&attributeValue.u8))
        {
          NWK_SetKey(&attributeValue.u8, 0);
          NWK_ActivateKey(0);
        }
      }
      break;
  case ZS_NETWORK_KEY2_ATTR_ID:
      predictedFrameLength += sizeof (uint8_t) * SECURITY_KEY_SIZE;
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        if(SSP_IsKeyValid(&attributeValue.u8))
        {
          NWK_SetKey(&attributeValue.u8, 1);
          NWK_ActivateKey(1);
        }
      }
      break;
    case ZS_TRUST_CENTER_ADDRESS_ATTR_ID:
      predictedFrameLength += sizeof (uint64_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &attributeValue);
      }
      break;

#ifdef _PERMISSIONS_
      case ZS_ADD_DEVICE_TO_PERMISSION_TABLE_ATTR_ID:
        predictedFrameLength += sizeof(ExtAddr_t);
        if (predictedFrameLength != frameLength)
          status = ZS_INVALID_PARAMETER_STATUS;
        else
        {
          if (TC_AddDeviceToPermissionTable(&attributeValue.extAddr))
            status = ZS_SUCCESS_STATUS;
          else
            status = ZS_FAIL_STATUS;
        }
        break;

      case ZS_REMOVE_DEVICE_FROM_PERMISSION_TABLE_ATTR_ID:
        predictedFrameLength += sizeof(ExtAddr_t);
        if (predictedFrameLength != frameLength)
          status = ZS_INVALID_PARAMETER_STATUS;
        else
        {
          if (TC_RemoveDeviceFromPermissionTable(&attributeValue.extAddr))
            status = ZS_SUCCESS_STATUS;
          else
            status = ZS_FAIL_STATUS;
        }
        break;
      case ZS_DEFAULT_PERMISSIONS_ATTR_ID:
        predictedFrameLength += sizeof(uint16_t);
        if (predictedFrameLength != frameLength)
          status = ZS_INVALID_PARAMETER_STATUS;
        else
          ZDO_SetDefaultPermissions(attributeValue.u16);
        break;
#endif /* _PERMISSIONS_ */
#endif /* _SECURITY_ */
#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
      case ZS_ZDO_ENABLE_INTERNAL_HANDLING_ATTR_ID:
        predictedFrameLength += sizeof (uint8_t);
        if (predictedFrameLength != frameLength)
        {
          status = ZS_INVALID_PARAMETER_STATUS;
        }      
        else if (attributeValue.u8 == R_SYS_ZDO_REQ_FRAME_TESTING)
        {
          // Disabling internal stack handling for zdo request received
          SYS_SubscribeToEvent( BC_EVENT_VALIDATE_ZDP_REQUEST, &zdoReqCmdValidation);
          SYS_UnsubscribeFromEvent(BC_ZDP_REQUEST_RECEIVED, &zdoReqCmdRxdReceiver);
          SYS_UnsubscribeFromEvent(BC_EVENT_VALIDATE_ZDP_RESPONSE , &zdoRspCmdValidation);
        }
        else if(attributeValue.u8 == R_SYS_ZDO_RESP_FRAME_TESTING)
        {
          SYS_SubscribeToEvent(BC_ZDP_REQUEST_RECEIVED, &zdoReqCmdRxdReceiver);
          SYS_SubscribeToEvent(BC_EVENT_VALIDATE_ZDP_RESPONSE , &zdoRspCmdValidation);
          SYS_UnsubscribeFromEvent( BC_EVENT_VALIDATE_ZDP_REQUEST, &zdoReqCmdValidation);
        }
        else
        {
          SYS_UnsubscribeFromEvent(BC_ZDP_REQUEST_RECEIVED, &zdoReqCmdRxdReceiver);
          SYS_UnsubscribeFromEvent( BC_EVENT_VALIDATE_ZDP_REQUEST, &zdoReqCmdValidation);
          SYS_UnsubscribeFromEvent(BC_EVENT_VALIDATE_ZDP_RESPONSE, &zdoRspCmdValidation);
        }
        break;
#endif // _STACK_INTERNAL_TEST_FRAMEWORK_
      case ZS_JOIN_CONTROL_ATTR_ID:
        predictedFrameLength += sizeof(RJoinControl_t);
        if (predictedFrameLength != frameLength)
          status = ZS_INVALID_PARAMETER_STATUS;
        else
        {
          NWK_JoinControl_t joinCtrl;

          joinCtrl.method = (NWK_JoinMethod_t)attributeValue.joinCtrl.method;
          joinCtrl.secured = attributeValue.joinCtrl.secured? true: false;
          joinCtrl.discoverNetworks = attributeValue.joinCtrl.discoverNetworks? true: false;
          joinCtrl.annce = attributeValue.joinCtrl.annce? true: false;
          joinCtrl.clearNeighborTable = attributeValue.joinCtrl.clearNeighborTable? true: false;
          CS_WriteParameter(CS_JOIN_CONTROL_ID, &joinCtrl);
        }
      break;
#ifdef _ZCL_SUPPORT_ 
    case ZS_GET_LAST_MESSAGE_RETURN_VALUE_ATTR_ID:
      rSetGetLastMessageReturnValue(attributeValue.u8);
      break;
#if APP_USE_OTAU == 1
    case ZS_OTAU_SERVER_EXT_ADDR_ID:
      predictedFrameLength += sizeof(ExtAddr_t);
      if (predictedFrameLength != frameLength)
      {
        status = ZS_INVALID_PARAMETER_STATUS;
      }
      else
      {
        CS_WriteParameter(CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS_ID, &attributeValue);
      }
      break;
#endif /* APP_USE_OTAU == 1 */
#endif /* ZCL_SUPPORT == 1 */

#ifdef _CHILD_MANAGEMENT_
    case ZS_NWK_PARENT_INFO_REQUEST:
      NWK_SetParentInformation((uint8_t)attributeValue.u8);
      break;
#endif //#ifdef _CHILD_MANAGEMENT_

    default:
      status = ZS_UNSUPPORTED_ATTRIBUTE_STATUS;
      break;
    }

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_SysSetConf_t);
  confirmBuffer->commandFrame.commandId = R_SYS_SET_CONFIRM;
  conf->status = status;
  conf->attributeId = req->attributeId;
  serialManager.write(confirmBuffer);

}

#pragma optimize = none
void rSysResetConfirm(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_SysResetConf_t *conf = (ZS_SysResetConf_t *) confirmBuffer->commandFrame.payload;

  (void)commandBuffer;
#if defined _MAC_BAN_NODE_
  MAC_ResetBanTable();
#endif

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_SysResetConf_t);
  confirmBuffer->commandFrame.commandId = R_SYS_RESET_CONFIRM;
  conf->status = ZS_SUCCESS_STATUS;

  serialManager.write(confirmBuffer);
}

#if (APP_INTERFACE == APP_INTERFACE_VCP)
/**************************************************************************//**
\brief Confirmation on software reset of stack

\param[in] conf - confirmation parameters
******************************************************************************/
static void rResetStackConf(ZDO_Status_t status)
{
  (void)status;
  rSysResetConfirm(NULL);
  currentCommand = NULL;
  lastCommandId = 0;
#ifdef _ENABLE_PERSISTENT_SERVER_
  PDS_Run();
#endif /* _ENABLE_PERSISTENT_SERVER_ */
  BSP_OffLed(LED_RED);
}

/**************************************************************************//**
\brief Software reset of stack (network)
******************************************************************************/
static void rResetStack(void)
{
  static ZDO_SoftwareResetReq_t req;
  req.ZDO_SoftwareResetConf = rResetStackConf;
#ifdef _ENABLE_PERSISTENT_SERVER_
  PDS_Stop();
#endif /* _ENABLE_PERSISTENT_SERVER_ */
  CS_Init();
  ZDO_SoftwareResetReq(&req);
}
#endif /* APP_INTERFACE == APP_INTERFACE_VCP */

/**************************************************************************//**
\brief Enable/disable sleep when idle
******************************************************************************/
void rSysSleepWhenIdleProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_SysSleepWhenIdleReq_t *sleepReq = (ZS_SysSleepWhenIdleReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_SysSleepWhenIdleConf_t *conf = (ZS_SysSleepWhenIdleConf_t *)confirmBuffer->commandFrame.payload;

  conf->status = 0;
#ifndef _SLEEP_WHEN_IDLE_
  (void)sleepReq;
#else
  if (0 == sleepReq->action)
    SYS_DisableSleepWhenIdle();
  else if (1 == sleepReq->action)
    SYS_EnableSleepWhenIdle();
  else
#endif
    conf->status = 1;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_SysSleepWhenIdleConf_t);
  confirmBuffer->commandFrame.commandId = R_SYS_SLEEP_WHEN_IDLE_CONFIRM;
  serialManager.write(confirmBuffer);
}

void rSysResetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_SysResetReq_t *resetReq = (ZS_SysResetReq_t *)commandBuffer->commandFrame.payload;

  //BSP_OnLed(LED_RED);

  if (R_RESET_TYPE_HARD_RESET == (RResetType_t)resetReq->resetType)
  {
#ifdef _ENABLE_PERSISTENT_SERVER_
    PDS_Delete(BC_ALL_MEMORY_MEM_ID);
#endif /* _ENABLE_PERSISTENT_SERVER_ */
  }
  else if (R_RESET_TYPE_FN_RESET == (RResetType_t)resetReq->resetType)
  {
#ifdef _ENABLE_PERSISTENT_SERVER_
    PDS_DeleteAll(false);
#endif /* _ENABLE_PERSISTENT_SERVER_ */
  }

#if (APP_INTERFACE == APP_INTERFACE_VCP)
  rResetStack();
#else
  serialManager.close();

#if (defined(__ICCARM__) && (defined(ATSAMR21G18A) || defined(ATSAMR21E18A)|| defined(ATSAMR21E19A)))
 {
   NVIC_SystemReset();
 }
#elif (defined(__GNUC__) && defined(_PIC32CX_))
 {
   SystemReset(); 
 }
#endif
  while (1);
#endif /* APP_INTERFACE == APP_INTERFACE_VCP */
}

void rSysPowerOffRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RSysPowerOffConfirm_t *conf = (RSysPowerOffConfirm_t*) confirmBuffer->commandFrame.payload;

  SYS_ClearEvents();
  //SYS_DisableTask(ZLL_TASK_ID);
  //SYS_DisableTask(ZCL_TASK_ID);
  SYS_DisableTask(ZDO_TASK_ID);
  SYS_DisableTask(APS_TASK_ID);
  SYS_DisableTask(NWK_TASK_ID);
  SYS_DisableTask(MAC_PHY_HWD_TASK_ID);

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RSysPowerOffConfirm_t);
  confirmBuffer->commandFrame.commandId = R_SYS_POWER_OFF_CONFIRM;
  conf->status = ZS_SUCCESS_STATUS;
  serialManager.write(confirmBuffer);

  rFreeMem(conf);
}
#if (BDB_SUPPORT == 1)
static void bdbInitCompleted(void)
{
    
}
#endif
void rSysSetDeviceTypeRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t status = ZS_SUCCESS_STATUS;
  DeviceType_t deviceType;

  ZS_SysSetDeviceTypeReq_t *req = (ZS_SysSetDeviceTypeReq_t*) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_SysSetDeviceTypeConf_t *conf = (ZS_SysSetDeviceTypeConf_t*) confirmBuffer->commandFrame.payload;

  if ((deviceType = (DeviceType_t) req->deviceType) > 0x02)
    status = ZS_INVALID_PARAMETER_STATUS;
  else
    //Set to ConfigServer
    CS_WriteParameter(CS_DEVICE_TYPE_ID, &deviceType);
#if (BDB_SUPPORT == 1)
  //BDB devcielevel Initialization
  BDB_DeviceInit();
#endif
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_SysSetDeviceTypeConf_t);
  confirmBuffer->commandFrame.commandId = R_SYS_SET_DEVICE_TYPE_CONFIRM;
  conf->deviceType = deviceType;
  conf->status = status;
  serialManager.write(confirmBuffer);
}

static void rSysStartConfirm(ZDO_StartNetworkConf_t *zdoConf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RSysStartConfirm_t *confirm = (RSysStartConfirm_t *) confirmBuffer->commandFrame.payload;

  /* Set extPANID to be equal to the extPANID of the joined PAN
    after entering into the network */
  if (ZDO_SUCCESS_STATUS == zdoConf->status)
  {
    ExtPanId_t extPanId;
    CS_ReadParameter(CS_NWK_EXT_PANID_ID,&extPanId);
    CS_WriteParameter(CS_EXT_PANID_ID, &extPanId);
  }

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RSysStartConfirm_t);
  confirmBuffer->commandFrame.commandId = R_SYS_START_CONFIRM;
  confirm->status = zdoConf->status;
  confirm->shortAddr = zdoConf->shortAddr;
  serialManager.write(confirmBuffer);

  rFreeMem(zdoConf);
}

void rSysStartRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_StartNetworkReq_t *req = (ZDO_StartNetworkReq_t *) rGetMem();
  ZS_StartReq_t *rStartReq = (ZS_StartReq_t*)commandBuffer->commandFrame.payload;
#ifdef _R_DEBUG_
  DeviceType_t deviceType;
  uint64_t uid = APP_COORD_UID;
#ifdef _LINK_SECURITY_
  uint8_t key[] = CS_MASTER_KEY;
#endif /* _LINK_SECURITY_ */
#endif /* _R_DEBUG_ */

#ifdef _R_DEBUG_
#ifdef _LINK_SECURITY_
  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);

  if (DEVICE_TYPE_COORDINATOR == deviceType)
    uid = APP_COORD_UID;
  else if (DEVICE_TYPE_ROUTER == deviceType)
    uid = APP_ROUTER_UID;

  CS_WriteParameter(CS_UID_ID, &uid);
  APS_SetMasterKey(&uid, key);
#endif /* _LINK_SECURITY_ */
#endif /* _R_DEBUG_ */

#ifdef _ENABLE_PERSISTENT_SERVER_
  if (rStartReq->powerFailureProtection)
    PDS_StoreByEvents(BC_ALL_MEMORY_MEM_ID);
#endif /* _ENABLE_PERSISTENT_SERVER_ */

  req->ZDO_StartNetworkConf = rSysStartConfirm;

  ZDO_StartNetworkReq(req);

  (void)rStartReq;
}

static uint32_t getUsedFeatures(void)
{
  uint32_t tempUsedFeatures = 0ul;
  //Security
#if !defined(_SECURITY_) && !defined _LINK_SECURITY_
  tempUsedFeatures = 0;
#endif
#if defined(_SECURITY_)
  tempUsedFeatures = 1;
#endif
#if defined _LINK_SECURITY_
  tempUsedFeatures = 2;
#endif
#if CERTICOM_SUPPORT == 1
  tempUsedFeatures = 3;
#endif
  //Radio
#if defined(AT86RF230)
  tempUsedFeatures |= (1<<4);
#endif
#if defined(AT86RF230B)
  tempUsedFeatures |= (2<<4);
#endif
#if defined(AT86RF231)
  tempUsedFeatures |= (3<<4);
#endif
#if defined(AT86RF212)
  tempUsedFeatures |= (4<<4);
#endif
#if defined(CUSTOMRF3)
  tempUsedFeatures |= (5<<4);
#endif
  //CPU
#if defined(ATMEGA1281)
  tempUsedFeatures |= (1<<8);
#endif
#if defined(ATMEGA2561)
  tempUsedFeatures |= (2<<8);
#endif
#if defined(ATMEGA1284)
  tempUsedFeatures |= (3<<8);
#endif
#if defined(AT90USB1287)
  tempUsedFeatures |= (4<<8);
#endif
#if defined(ATXMEGA128A1)
  tempUsedFeatures |= (5<<8);
#endif
#if defined(ATXMEGA256A3)
  tempUsedFeatures |= (6<<8);
#endif
#if defined(AT91SAM7X256)
  tempUsedFeatures |= (7<<8);
#endif
#if defined(AT91SAM3S4C)
  tempUsedFeatures |= (8<<8);
#endif
#if defined(ATMEGA128RFA1)
  tempUsedFeatures |= (9<<8);
#endif
#if defined(AT32UC3A0512)
  tempUsedFeatures |= (10<<8);
#endif
#if defined(ATXMEGA256D3)
  tempUsedFeatures |= (11<<8);
#endif
  return tempUsedFeatures;
}

void rSysAssertNotifyProcess(ZS_CommandBuffer_t *commandBuffer)
{
#if (APP_ENABLE_SYSASSERT == 1)
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RSysAssertNotify_t *confirm = (RSysAssertNotify_t *) confirmBuffer->commandFrame.payload;
  RSysAssertNotify_t *rStartReq = (RSysAssertNotify_t *)commandBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RSysAssertNotify_t);
  confirmBuffer->commandFrame.commandId = R_SYS_ASSERT_INDICATION;
  confirm->level = rStartReq->level;
  confirm->code = rStartReq->code;
  serialManager.write(confirmBuffer);
#endif
  rFreeMem(commandBuffer);
}

/* eof rSys.c */
