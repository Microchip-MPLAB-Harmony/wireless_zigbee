/**************************************************************************//**
  \file  rTypes.h

  \brief Coomon types declaration

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
  Last change:
    $Id: rTypes.h 32965 2019-04-16 09:13:55Z I41664 $
 ******************************************************************************/
#ifndef _RTYPES_H
#define _RTYPES_H
/******************************************************************************
                   Includes section
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <systemenvironment/include/sysTaskManager.h>
#include <zdo/include/appFramework.h>
#include <aps/include/aps.h>
#include <zdo/include/zdo.h>
#ifdef _ZCL_SUPPORT_ 
#include <zcl/include/zcl.h>
#endif /* ZCL_SUPPORT == 1 */
#include <consts.h>
#include <ZAppSiSerialManager.h>
#if defined(_ZCL_SUPPORT_) && defined(_LINK_SECURITY_) && !defined(_LIGHT_LINK_PROFILE_)
#include <zcl/include/zclSecurityManager.h>
#endif /* (defined _LINK_SECURITY_) && (!defined _LIGHT_LINK_PROFILE_) */
#include <security/serviceprovider/include/sspCommon.h>
#if APP_USE_OTAU == 1
#include <zcl/include/zclOTAUCluster.h>
#endif // APP_USE_OTAU
#include <nwk/include/nwkSecurity.h>
#include <ZAppSiIdentifiers.h>
#if (BDB_SUPPORT == 1)
#include <bdb/include/bdb.h>
#include <bdb/include/bdbInstallCode.h>
#endif
/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  R_INIT_STATE,
  R_IDLE_STATE,
  R_ERROR_STATE,
  R_REQUEST_PROCESS_STATE,
  R_INDICATION_PROCESS_STATE,
} RState_t;

typedef enum _RResetType_t
{
  R_RESET_TYPE_HARD_RESET = 0x00,
  R_RESET_TYPE_SOFT_RESET = 0x01,
  R_RESET_TYPE_FN_RESET   = 0x02,
} RResetType_t;

typedef enum
{
  R_USART_MANAGER_TASK_ID = 0x00,
  R_PARSER_TASK_ID = 0x01
} RTaskId_t;

typedef struct
{
  CommandID_t id;
  void (*handler)(ZS_CommandBuffer_t *commandBuffer);
} CommandRecord_t;
/*****************************************************************************
  SYSTEM CONFIGURATION PRIMITIVES
*****************************************************************************/
BEGIN_PACK
typedef struct PACK _RSysStartConf_t
{
  uint8_t status;
  ShortAddr_t shortAddr;
} RSysStartConfirm_t;

typedef struct PACK _RSysPowerOffConf_t
{
  uint8_t status;
} RSysPowerOffConfirm_t;

typedef struct PACK
{
  uint16_t unsupCommandID;
} RSysUnsupCommand_t;

typedef struct PACK
{
  uint16_t level;
  uint16_t code;
}RSysAssertNotify_t;

/*****************************************************************************
  MAC PRIMITIVES
*****************************************************************************/
typedef struct PACK _RMacBanRequest_t
{
  ShortAddr_t  shortAddr;
  ExtAddr_t  extAddr;
  uint8_t cost;
} RMacBanRequest_t;

typedef struct PACK _RMacBanConfirm_t
{
  uint8_t status;
} RMacBanConfirm_t;

typedef struct PACK _RMacBanAllRequest_t
{
  uint8_t banAll;
} RMacBanAllRequest_t;

typedef struct PACK _RMacBanAllConfirm_t
{
  uint8_t status;
} RMacBanAllConfirm_t;

typedef struct PACK _RMacDataRequest_t
{
  uint8_t  srcAddrMode;
  uint8_t  dstAddrMode;
  uint16_t  dstPanId;
  ShortAddr_t  dstShortAddr;
  ExtAddr_t  dstExtAddr;
  uint8_t  txOptions;
  uint8_t  msduHandle;
  uint8_t  msduLength;
  uint8_t  msdu[1];
} RMacDataRequest_t;

typedef struct PACK _RMacDataConfirm_t
{
  uint8_t status;
  uint8_t msduHandle;
} RMacDataConfirm_t;

typedef struct PACK _RMacRegAccessRequest_t
{
  uint8_t  direction;
  uint16_t address;
  uint8_t  value;
} RMacRegAccessRequest_t;

typedef struct PACK _RMacRegAccessConfirm_t
{
  uint8_t status;
  uint8_t value;
} RMacRegAccessConfirm_t;

/*****************************************************************************
  NWK PRIMITIVES
*****************************************************************************/
typedef struct PACK
{
  uint16_t  shortAddr;
  uint64_t  extAddr;
} RNwkAddrResolvConf_t;

typedef struct PACK
{
  uint16_t  shortAddr;
  uint64_t  extAddr;
} RNwkAddrResolvReq_t;

typedef struct PACK
{
  uint16_t  nextHopAddr;
} RNwkNextHopConf_t;

typedef struct PACK
{
  uint16_t  dstAddr;
} RNwkNextHopReq_t;

typedef struct PACK
{
  ShortAddr_t dstAddr;
  ShortAddr_t nextHopAddr;
  NwkPathCost_t cost;
  bool isGroupId;
}RNwkSetNextHopReq_t;

typedef struct PACK
{
  uint16_t  nextHopAddr;
  uint8_t status;
}RNwkSetNextHopConf_t;

typedef struct PACK
{
  uint8_t permitDuration;
} RNwkPermitJoiningRequest_t;

typedef struct PACK
{
  uint8_t status;
} RNwkPermitJoiningConfirm_t;

typedef struct PACK
{
  NWK_NetworkDiscoveryReq_t  req;
  NWK_NetworkDescriptor_t  descr[R_MAX_NETWORK_DESCRIPTORS];
} RNwkDiscovery_t;

typedef  struct PACK
{
  uint8_t  duration;
  uint32_t channels;
  bool clearNeighborTable;
}  RNwkNetworkDiscoveryReq_t;

typedef  struct PACK
{
  uint8_t  status;
  uint8_t  networkCount;
  NWK_NetworkDescriptor_t  descr[R_MAX_NETWORK_DESCRIPTORS];
} RNwkNetworkDiscoveryConf_t;

typedef struct PACK
{
  uint8_t  powerFailure;
  MAC_CapabilityInf_t  capabilityInformation;
} RNwkResetReq_t;

typedef struct PACK
{
  uint8_t  status;
} RNwkResetConfirm_t;

typedef  struct PACK
{
    ExtAddr_t deviceAddress;
    ShortAddr_t shortAddress;
    NWK_LeaveControl_t leaveControl;
    bool removeChildren;
    bool rejoin;
    bool noExtendedAddress;
} RNwkLeaveReq_t;

typedef  struct PACK
{
  ExtAddr_t deviceAddress;
  ShortAddr_t networkAddress;
  MAC_CapabilityInf_t capabilityInformation;
} RNwkDirectJoinReq_t;

typedef struct PACK
{
  uint8_t  status;
} RNwkDirectJoinConf_t;

typedef struct PACK
{
  MAC_CapabilityInf_t  capabilityInformation;
} RApsResetReq_t;

typedef struct PACK
{
  uint8_t  status;
} RApsResetConf_t;

typedef struct PACK
{
  uint8_t  status;
} RApsStartConf_t;

typedef struct PACK
{
  uint64_t devAddr;
  uint32_t counter;
} RApsSetOutFrameCounterReq_t;

typedef struct PACK
{
  uint8_t status;
} RApsSetOutFrameCounterConf_t;

typedef struct PACK
{
  uint64_t  extendedPANId;
  uint8_t method;
  uint32_t scanChannels;
  uint8_t scanDuration;
  uint8_t securityEnable;
} RNwkJoinReq_t;

typedef struct PACK
{
  uint8_t  status;
  uint16_t  networkAddress;
  uint64_t  extendedPANId;
  uint8_t  activeChannel;
} RNwkJoinConf_t;

typedef struct PACK
{
  uint8_t  status;
} RNwkStartRouterConf_t;


typedef struct PACK
{
  NWK_Status_t  status;
  NWK_StatusIndErrorCodes_t  networkStatusCode;
  ShortAddr_t  nextHop;
} RNwkRouteDiscoveryConf_t;

typedef struct PACK
{
  NWK_DstAddrMode_t dstAddrMode;
  ShortAddr_t dstAddr;
  NwkRadius_t radius;
  bool noRouteCache;
  void (*NWK_RouteDiscoveryConf)(NWK_RouteDiscoveryConf_t *conf);
} RNwkRouteDiscoveryReq_t;

typedef struct PACK
{
  uint16_t address;
  uint8_t silent;
} RNwkSetShortAddressReq_t;

typedef struct PACK
{
  uint8_t order;
} RNwkSetRouteFailOrderReq_t;

typedef struct PACK
{
  uint8_t status;
} RNwkSetRouteFailOrderConf_t;

#if defined _CERTIFICATION_ && defined _NWK_FAST_ROUTE_DISCOVERY_
typedef struct PACK
{
  uint8_t fastRouteDiscovery;
} RNwkSetFastRouteDiscoveryReq_t;

typedef struct PACK
{
  uint8_t status;
} RNwkSetFastRouteDiscoveryConf_t;
#endif

#ifdef _SECURITY_
typedef struct PACK _RNwkGetOutSecurityCounterConf_t
{
  NwkOutFrameCounter_t outCounter;
} RNwkGetOutSecurityCounterConf_t;

typedef struct PACK _RNwkSetOutSecurityCounterReq_t
{
  uint32_t outCounter;
} RNwkSetOutSecurityCounterReq_t;

typedef struct PACK _RNwkSetOutSecurityCounterConf_t
{
  uint8_t status;
} RNwkSetOutSecurityCounterConf_t;

typedef struct PACK _RNwkGetActiveKeySeqNumConf_t
{
  uint8_t keySeqNum;
} RNwkGetActiveKeySeqNumConf_t;


#ifdef _NWK_IN_FRAME_COUNTERS_
typedef struct PACK _RNwkSetInSecurityCounterReq_t
{
  uint64_t extAddr;
  NwkInFrameCounter_t newValue;
} RNwkSetInSecurityCounterReq_t;

typedef struct PACK _RNwkSetInSecurityCounterConf_t
{
  uint8_t status;
} RNwkSetInSecurityCounterConf_t;

typedef struct PACK _RNwkGetInSecurityCounterReq_t
{
  uint64_t extAddr;
} RNwkGetInSecurityCounterReq_t;

typedef struct PACK _RNwkGetInSecurityCounterConf_t
{
  uint8_t status;
  NwkInFrameCounter_t currentValue;
} RNwkGetInSecurityCounterConf_t;
#endif /* _NWK_IN_FRAME_COUNTERS_ */

typedef struct PACK _RTcPolicySetConf_t
{
  uint8_t status;
} RTcPolicySetConf_t;

#endif /* _SECURITY_ */
#ifdef _CHILD_MANAGEMENT_
typedef struct PACK
{
  uint8_t timeout;
  uint8_t endDeviceConfiguration;
} RNwkEndDeviceTimeoutReq_t;

typedef struct PACK
{
  uint8_t status;
} RNwkEndDeviceTimeoutConf_t;

typedef struct PACK
{
  uint16_t addr;
  uint8_t timeout;
  uint8_t endDeviceConfiguration;
  uint8_t parentInformation;
} RNwkEndDeviceTimeoutReqInd_t;
#endif /* _CHILD_MANAGEMENT_ */

typedef struct PACK
{
  uint16_t shortAddr;
  uint64_t extAddr;
} RNwkAddressMapEntryReq_t;

typedef struct PACK
{
  uint8_t status;
} RNwkAddressMapEntryConf_t;

typedef struct PACK
{
  uint64_t extAddr;
  uint16_t shortAddr;
  bool useExtAddr;
} RNwkRemoveNeighborEntryReq_t;

typedef struct PACK
{
  uint8_t status;
} RNwkRemoveNeighborEntryConf_t;

typedef struct PACK
{
  uint64_t extAddr;
  uint8_t  edTimeout;
} RNwkSetEndDviceTimeout_t;

typedef struct PACK
{
  uint8_t status;
} RNwkSetEndDviceTimeoutConf_t;



/*****************************************************************************
  APS PRIMITIVES
*****************************************************************************/
#ifdef _BINDING_

typedef struct PACK
{
  uint64_t    srcAddr;
  uint8_t     srcEndpoint;
  uint16_t    clusterId;
  uint8_t     dstAddrMode;
  union PACK
  {
    struct PACK
    {
      uint64_t  dstExtAddr;
      uint8_t   dstEndpoint;
    };
    uint16_t    dstGroupAddr;
  };
} RApsUnbindRequest_t;

typedef struct PACK
{
  uint8_t     status;
  uint64_t    srcAddr;
  uint8_t     srcEndpoint;
  uint16_t    clusterId;
  uint8_t     dstAddrMode;
  union PACK
  {
    struct PACK
    {
      uint64_t  dstExtAddr;
      uint8_t   dstEndpoint;
    };
    uint16_t    dstGroupAddr;
  };
} RApsUnbindConfirm_t;

#endif /* _BINDING_ */

typedef struct PACK
{
  uint8_t attributeId;
} RApsGetRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t attributeId;
  uint8_t attributeLength;
  uint8_t attributeValue[1];
} RApsGetConfirm_t;

typedef struct PACK
{
  uint8_t attributeId;
  uint8_t attributeLength;
  uint8_t attributeValue[1];
} RApsSetRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t attributeId;
} RApsSetConfirm_t;

typedef struct PACK
{
  uint16_t groupAddress;
  uint8_t endpoint;
} RApsAddGroupRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t groupAddress;
  uint8_t endpoint;
} RApsAddGroupConfirm_t;

typedef struct PACK
{
  uint16_t groupAddress;
  uint8_t endpoint;
} RApsRemoveGroupRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t groupAddress;
  uint8_t endpoint;
} RApsRemoveGroupConfirm_t;

typedef struct PACK
{
  uint8_t endpoint;
} RApsRemoveAllGroupsRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t endpoint;
} RApsRemoveAllGroupsConfirm_t;

#ifdef _SECURITY_

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keyType;
  APS_ReqTransportKeyData_t transportKeyData;
} RApsTransportKeyRequest_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keyType;
  uint8_t status;
} RApsTransportKeyConfirm_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keySeqNumber;
} RApsSwitchKeyRequest_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keySeqNumber;
  uint8_t status;
} RApsSwitchKeyConfirm_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keyType;
  uint64_t partnerAddress;
} RApsRequestKeyRequest_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint8_t keyType;
  uint64_t partnerAddress;
  uint8_t status;
} RApsRequestKeyConfirm_t;

typedef struct PACK _RApsGetOutSecurityCounterReq_t
{
  ExtAddr_t extAddr;
} RApsGetOutSecurityCounterReq_t;

typedef struct PACK _RApsGetOutSecurityCounterConf_t
{
  ApsOutFrameCounter_t outCounter;
} RApsGetOutSecurityCounterConf_t;

#if defined _CERTIFICATION_ && defined _LINK_SECURITY_
typedef struct PACK _RApsUpdateSecurityPolicyReq_t
{
  uint16_t spid;
  uint8_t policy;
} RApsUpdateSecurityPolicyReq_t;

typedef struct PACK _RApsUpdateSecurityPolicyConf_t
{
  uint8_t status;
} RApsUpdateSecurityPolicyConf_t;

/* Type of key-pair descriptor. */
typedef struct _RApsKeyPairDescriptor_t
{
  /* Identifies the address of the entity with which this key-pair is shared. */
  ExtAddr_t deviceAddress;
  /* Bitmask of flags indicating entry status/type */
  uint8_t flags;
  /* The actual value of the initial key:
     master key for High Security and preinstalled link key for SE Security. */
  uint8_t initialKey[SECURITY_KEY_SIZE];
  /* The actual value of the link key. */
  uint8_t linkKey[SECURITY_KEY_SIZE];
} RApsKeyPairDescriptor_t;

typedef struct PACK _RApsKeyPairSetReq_t
{
  ExtAddr_t extAddr;
} RApsKeyPairSetReq_t;

typedef struct PACK _RApsKeyPairSetConf_t
{
  RApsKeyPairDescriptor_t keyPair;
  uint8_t status;
} RApsKeyPairSetConf_t;

#endif /* _CERTIFICATION_ && defined _LINK_SECURITY_ */
#endif /* _SECURITY_ */

typedef struct PACK _RJoinControl_t
{
  uint8_t method;
  uint8_t secured;
  uint8_t discoverNetworks;
  uint8_t annce;
  uint8_t clearNeighborTable;
} RJoinControl_t;

/*****************************************************************************
  ZDO PRIMITIVES
*****************************************************************************/
typedef struct PACK
{
  uint64_t deviceAddress;
  struct PACK
  {
    uint8_t rejoin : 1;
    uint8_t removeChildren : 1;
    uint8_t reserved : 6;
    };
} RZdoMgmtLeaveRequest_t;

typedef struct PACK
{
  uint8_t status;
} RZdoMgmtLeaveConfirm_t;

typedef struct PACK
{
  uint32_t sleepPeriod;
} RZdoSleepRequest_t;

typedef struct PACK
{
  uint32_t sleepPeriod;
  uint8_t status;
} RZdoSleepConfirm_t;

typedef struct PACK
{
  uint8_t routersAmount;
  uint8_t enddevicesAmount;
} RZdoGetNeibAmountConfirm_t;

typedef struct PACK
{
  uint16_t shortAddr;
  uint64_t extAddr;
  uint8_t deviceType;
  uint8_t lqi;
  uint8_t rssi;
} RZdoGetNeibTableConfirm_t;

typedef struct PACK
{
  uint8_t status;
  struct PACK
  {
    uint32_t scannedChannels;
    uint16_t totalTransmissions;
    uint16_t transmissionsFailures;
    uint8_t scannedChannelsListCount;
    uint8_t energyValues[32];
  } scanResult;
} RZdoMgmtNwkUpdateNotifyScanResult_t;

typedef struct PACK
{
  uint8_t status;
  struct PACK
  {
    uint16_t parentShortAddr;
    uint16_t panId;
    uint8_t currentChannel;
    uint16_t shortAddr;
  } nwkUpdateInf;
} RZdoMgmtNwkUpdateNotifyNwkUpdateInformation_t;

typedef struct PACK
{
  uint8_t status;
  struct PACK
  {
    uint16_t shortAddr;
    uint64_t extAddr;
    uint8_t capabilityInfo;
  } childInfo;
} RZdoMgmtNwkUpdateNotifyChildInformation_t;

typedef struct PACK
{
  uint8_t status;
  struct PACK
  {
    uint16_t shortAddr;
    uint64_t extAddr;
  } childAddr;
} RZdoMgmtNwkUpdateNotifyChildAddress_t;

typedef struct PACK
{
  uint8_t txPower;
} RZdoSetTxPowerRequest_t;

typedef struct PACK
{
  uint8_t status;
} RZdoSetTxPowerConfirm_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t shortAddr;
} RZdoMgmtNwkUpdateNotifyConflAddress_t;

typedef struct PACK
{
  uint64_t ieeeAddress;
  uint8_t requestType;
  uint8_t startIndex;
} RZdoNwkAddrRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint64_t ieeeAddrRemoteDev;
  uint16_t nwkAddrRemoteDev;
  uint8_t numAssocDev;
  uint8_t startIndex;
  uint16_t nwkAddrAssocDevList[1];
} RZdoNwkAddrConfirm_t;

typedef struct PACK
{
  uint16_t dstShortAddress;
  uint8_t permitDuration;
  uint8_t tcSignificance;
} RZdoMgmtPermitJoiningRequest_t;

typedef struct PACK
{
    uint8_t status;
} RZdoMgmtPermitJoiningConfirm_t;

#if APP_ZDP_REQUESTS

typedef struct PACK
{
  uint16_t serverMask;
} RZdpSystemServerDiscoveryRequest_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
  uint8_t requestType;
  uint8_t startIndex;
} RZdoIeeeAddrRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint64_t ieeeAddress;
  uint16_t nwkAddr;
  uint8_t numAssocDev;
  uint8_t startIndex;
  uint16_t nwkAddrAssocDevList[1];
} RZdoIeeeAddrConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
} RZdoNodeDescRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  NodeDescriptor_t nodeDescriptor;
} RZdoNodeDescConfirm_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t serverMask;
} RZdpSystemServerDiscoveryConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddr;
  uint64_t ieeeAddr;
  uint8_t capability;
} RZdpEnDeviceAnnceRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddr;
  uint64_t ieeeAddr;
  uint8_t capability;
} RZdpEndDeviceConfirm_t;

typedef struct PACK
{
  ShortAddr_t nwkAddr;
  uint32_t scanChannels;
  uint8_t scanDuration;
  union PACK
  {
    uint8_t nwkUpdateId;
    uint8_t scanCount;
  };
  uint16_t nwkManagerAddr;
} RZdpNwkUpdateRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint32_t scanChannels;
  uint8_t scannedChannelsListCount;
} RZdpNwkUpdateConfirm_t;

#ifdef _BINDING_

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
  uint16_t profileId;
  uint8_t numInClusters;
  uint16_t inClusterList[1];
  uint8_t numOutClusters;
  uint16_t outClusterList[1];
} RZdpMatchDescRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint8_t matchLength;
  uint8_t matchList[1];
} RZdpMatchDescConfirm_t;

typedef struct PACK
{
  uint64_t srcAddr;
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t dstAddrMode;
  union PACK
  {
    struct PACK
    {
      uint64_t dstExtAddr;
      uint8_t dstEndpoint;
    };
    uint16_t dstGroupAddr;
  };
} RZdpBindRequest_t;

typedef struct PACK
{
  uint8_t status;
} RZdpBindConfirm_t;

typedef struct PACK
{
  uint64_t srcAddr;
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t dstAddrMode;
  union PACK
  {
    struct PACK
    {
      uint64_t dstExtAddr;
      uint8_t dstEndpoint;
    };
    uint16_t dstGroupAddr;
  };
} RZdpUnbindRequest_t;

typedef struct PACK
{
  uint8_t status;
} RZdpUnbindConfirm_t;

typedef struct PACK
{
  uint8_t status;
} RZdpEndDeviceBindingResp_t;

#endif /* _BINDING_ */

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
} RZdpPowerDescRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint16_t powerDescriptor;
} RZdpPowerDescConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
  uint8_t endpoint;
} RZdpSimpleDescRequest_t;

typedef struct PACK
{
  uint8_t count;
  uint16_t pIDs[];

} RZdpClustersList_t;

typedef struct PACK
{
  uint8_t   endpoint;
  uint16_t  appProfileId;
  uint16_t  appDeviceId;
  LITTLE_ENDIAN_OCTET(2, (
    uint8_t      appDeviceVersion : 4,
    uint8_t      reserved         : 4
  ))

  uint16_t clusterLists;
} RZdpSimpleDesc_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint8_t length;
  RZdpSimpleDesc_t simpleDescriptor;
} RZdpSimpleDescConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
} RZdpActiveEPRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint8_t activeEPCount;
  uint8_t activeEPList[1];
} RZdpActiveEPConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
} RZdpComplexDescRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint8_t length;
  uint8_t complexDescriptor[1];
} RZdpComplexDescConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
} RZdpUserDescRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
  uint8_t length;
  uint8_t userDescriptor[ZDP_USER_DESC_FIELD_SIZE];
} RZdpUserDescConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
  uint8_t length;
  uint8_t userDescriptor[ZDP_USER_DESC_FIELD_SIZE];
} RZdpUserDescSetRequest_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t nwkAddrOfInterest;
} RZdpUserDescSetConfirm_t;

typedef struct PACK
{
  uint16_t nwkAddrOfInterest;
  ZDO_MgmtLqiReq_t mgmtLqiReq;
} RZdpLqiRequest_t;

typedef struct PACK
{
  uint8_t status;
  ZDO_MgmtLqiResp_t mgmtLqiResp;
} RZdpLqiConfirm_t;

#endif /* APP_ZDP_REQUESTS */

/*****************************************************************************
  APPLICATION LAYER PRIMITIVES
*****************************************************************************/
#ifdef _APS_MULTICAST_

typedef struct PACK _RAfIndirectRequest_t
{
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t txOptions;
  uint8_t broadcastRadius;
} RAfIndirectRequest_t;

typedef struct PACK _RAfIndirectConfirm_t
{
  uint8_t srcEndpoint;
  uint8_t status;
} RAfIndirectConfirm_t;

typedef struct PACK _RAfIndirectIndication_t
{
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t wasBroadcast;
  uint8_t securityStatus;
} RAfIndirectIndication_t;

typedef struct PACK _RAfDirectRequest_t
{
  uint16_t dstShortAddress;
  uint8_t dstEndpoint;
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t txOptions;
  uint8_t broadcastRadius;
} RAfDirectRequest_t;

typedef struct PACK _RAfDirectConfirm_t
{
  uint16_t dstShortAddress;
  uint8_t dstEndpoint;
  uint8_t srcEndpoint;
  uint8_t status;
} RAfDirectConfirm_t;

typedef struct PACK _RAfDirectIndication_t
{
  uint8_t dstEndpoint;
  uint16_t srcShortAddress;
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t wasBroadcast;
  uint8_t securityStatus;
} RAfDirectIndication_t;

typedef struct PACK _RAfGroupRequest_t
{
  uint16_t groupAddress;
  uint8_t srcEndpoint;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t txOptions;
  uint8_t broadcastRadius;
} RAfGroupRequest_t;

typedef struct PACK _RAfGroupConfirm_t
{
  uint16_t groupAddress;
  uint8_t srcEndpoint;
  uint8_t status;
  uint8_t afduHandle;
} RAfGroupConfirm_t;

typedef struct PACK _RAfGroupIndication_t
{
  uint16_t groupAddress;
  uint8_t dstEndpoint;
  uint16_t srcShortAddress;
  uint16_t clusterId;
  uint8_t afduLength;
  uint8_t afdu[1];
  uint8_t securityStatus;
} RAfGroupIndication_t;

#endif /* _APS_MULTICAST_ */
/*****************************************************************************
  TRUST CENTER PRIMITIVES
*****************************************************************************/
//Via System Set Request
typedef struct PACK
{
  uint64_t extAddr; //8
  uint8_t key[SECURITY_KEY_SIZE];
  uint8_t keyType;
} RTcSetDeviceKeyRequest_t;

//Via APSME-REMOVE-DEVICE.request
//TC_RemoveDeviceReq
typedef struct PACK
{
  uint64_t parentAddress;
  uint64_t childAddress;
} RTcRemoveDeviceRequest_t;

//TC_RemoveDeviceConf
typedef struct PACK
{
  uint64_t parentAddress;
  uint64_t childAddress;
  uint8_t status;
} RTcRemoveDeviceConfirm_t;

//Via APSME-UPDATE-DEVICE.request
//TC_KeyUpdateReq
typedef struct PACK
{
  uint64_t destAddress;
  uint64_t deviceAddress;
  uint8_t status;
  uint16_t deviceShortAddress;
} RTcKeyUpdateRequest_t;

typedef struct PACK
{
  uint64_t destAddress;
  uint64_t deviceAddress;
  uint8_t status;
  uint16_t deviceShortAddress;
  uint8_t confStatus;
} RTcKeyUpdateConfirm_t;
/*****************************************************************************
  Transmit counted packets
*****************************************************************************/
typedef struct PACK _CidTransmitCountedPackets_t
{
  uint8_t length;
  uint16_t counter;
  uint8_t octets[1];
} CidTransmitCountedPackets_t;
/*****************************************************************************
  Packet count response
*****************************************************************************/
typedef struct PACK _CidPacketCountResponse_t
{
  uint16_t packetCount;
} CidPacketCountResponse_t;
/*****************************************************************************
  Buffer test request
*****************************************************************************/
typedef struct PACK _CidBufferTestRequest_t
{
  uint8_t length;
} CidBufferTestRequest_t;
/*****************************************************************************
  Buffer test group request
*****************************************************************************/
typedef struct PACK _CidBufferTestGroupRequest_t
{
  uint8_t length;
} CidBufferTestGroupRequest_t;
/*****************************************************************************
  Buffer test response
*****************************************************************************/
typedef struct PACK _CidBufferTestResponse_t
{
  uint8_t length;
  uint8_t status;
  uint8_t octets[1];
} CidBufferTestResponse_t;
/*****************************************************************************
  Buffer test group response
*****************************************************************************/
typedef struct PACK _CidBufferTestGroupResponse_t
{
  uint8_t length;
  uint8_t status;
  uint8_t octets[1];
} CidBufferTestGroupResponse_t;
/*****************************************************************************
  Route discovery request
*****************************************************************************/
typedef struct PACK _CidRouteDiscoveryRequest_t
{
  uint8_t dstAddrMode;
  uint16_t nwkAddress;
  uint8_t radius;
} CidRouteDiscoveryRequest_t;
/*****************************************************************************
  Route discovery response
*****************************************************************************/
typedef struct PACK _CidRouteDiscoveryResponse_t
{
  uint8_t status;
} CidRouteDiscoveryResponse_t;
/*****************************************************************************
  Freeform request
*****************************************************************************/
typedef struct PACK _CidFreeformRequest_t
{
  uint8_t requestType;
} CidFreeformRequest_t;
/*****************************************************************************
  Freeform response
*****************************************************************************/
typedef struct PACK _CidFreeformResponse_t
{
  uint8_t requestType;
  uint8_t responseData[1];
} CidFreeformResponse_t;
/*****************************************************************************
  Broadcast request
*****************************************************************************/
typedef struct PACK _CidBroadcastRequest_t
{
  uint8_t requestType;
} CidBroadcastRequest_t;
/*****************************************************************************
  Broadcast to all devices response
*****************************************************************************/
typedef struct PACK _CidBroadcastToAllDevicesResponse_t
{
  uint8_t requestType;
} CidBroadcastToAllDevicesResponse_t;
/*****************************************************************************
  Broadcast to all RxOnWhenIdle devices response
*****************************************************************************/
typedef struct PACK _CidBroadcastToAllRxOnWhenIdleDevicesResponse_t
{
  uint8_t requestType;
} CidBroadcastToAllRxOnWhenIdleDevicesResponse_t;
/*****************************************************************************
  Broadcast to all routers and coordinator response
*****************************************************************************/
typedef struct PACK _CidBroadcastToAllRoutersAndCoordinatorResponse_t
{
  uint8_t requestType;
} CidBroadcastToAllRoutersAndCoordinatorResponse_t;

#if APP_USE_OTAU == 1
/*****************************************************************************
  Data for start of the otau client
*****************************************************************************/
typedef struct PACK
{
  Endpoint_t                 otauEndpoint;
  ProfileId_t                profileId;
  ZCL_OtauFirmwareVersion_t  firmwareVersion;
} OtauInitParams_t;
#endif // APP_USE_OTAU
END_PACK
/******************************************************************************
                   Constants section
******************************************************************************/
enum
{
  CID_TRANSMIT_COUNTED_PACKETS =                              CCPU_TO_LE16(0x0001),
  CID_RESET_PACKET_COUNT =                                    CCPU_TO_LE16(0x0002),
  CID_RETRIEVE_PACKET_COUNT =                                 CCPU_TO_LE16(0x0003),
  CID_PACKET_COUNT_RESPONSE =                                 CCPU_TO_LE16(0x0004),

  CID_BUFFER_TEST_REQUEST =                                   CCPU_TO_LE16(0x001c),
  CID_BUFFER_TEST_GROUP_REQUEST =                             CCPU_TO_LE16(0x001d),
  CID_BUFFER_TEST_RESPONSE =                                  CCPU_TO_LE16(0x0054),
  CID_BUFFER_TEST_GROUP_RESPONSE =                            CCPU_TO_LE16(0x0055),

  CID_ROUTE_DISCOVERY_REQUEST =                               CCPU_TO_LE16(0x1000),
  CID_ROUTE_DISCOVERY_CONFIRM =                               CCPU_TO_LE16(0x1001),

  CID_FREEFORM_REQUEST =                                      CCPU_TO_LE16(0xa0a8),

  CID_FREEFORM_RESPONSE =                                     CCPU_TO_LE16(0xe000),
  CID_FREEFORM_NO_DATA_RESPONSE =                             CCPU_TO_LE16(0xe001),

  CID_BROADCAST_REQUEST =                                     CCPU_TO_LE16(0xf000),
  CID_BROADCAST_TO_ALL_DEVICES_RESPONSE =                     CCPU_TO_LE16(0xf001),
  CID_BROADCAST_TO_ALL_RX_ON_WHEN_IDLE_DEVICES_RESPONSE =     CCPU_TO_LE16(0xf00a),
  CID_BROADCAST_TO_ALL_ROUTERS_AND_COORDINATOR_RESPONSE =     CCPU_TO_LE16(0xf00e)
};

enum
{
  R_DEVICE_TYPE_ATTR_ID,
  R_EXTADDR_ATTR_ID,
  R_CHANNEL_MASK_ATTR_ID,
  R_RX_ON_WHEN_IDLE_ATTR_ID,
  R_PANID_ATTR_ID,
  R_EXTPANID_ATTR_ID,
  R_ACTIVE_ENDPOINT_ATTR_ID
};

enum
{
  CID_SUCCESSFUL_BUFFER_TEST_STATUS =                   0x00,
  CID_TRANSMITTION_FAILURE_ON_FIRST_ATTEMPT_STATUS =    0x01
};

/*************************************************************************//**
  AIB Attribute's ID definition

  \brief
    APS Information base attributes IDs

    APS Information base attribute IDs used for AIB management with
    standard AIB maintenance primitives
*****************************************************************************/
typedef enum
{
  //AIB security attributes ID
  APS_AIB_DEVICE_KEY_PAIR_SET             = 0xaa,   //!<apsDeviceKeyPairSet
  APS_AIB_TRUST_CENTER_ADDRESS            = 0xab,   //!<apsTrustCenterAddress
  APS_AIB_SECURITY_TIME_OUT_PERIOD        = 0xac,   //!<apsSecurityTimeOutPeriod

  //AIB standard attributes
  APS_AIB_BINDING_TABLE                   = 0xc1,   //!<apsBindingTable
  APS_AIB_DESIGNATED_COORDINATOR          = 0xc2,   //!<apsDesignatedCoordinator
  APS_AIB_CHANNEL_MASK                    = 0xc3,   //!<apsChannelMask
  APS_AIB_USE_EXTENDED_PANID              = 0xc4,   //!<apsUseExtendedPANID
  APS_AIB_GROUP_TABLE                     = 0xc5,   //!<apsGroupTable
  APS_AIB_NONMEMBER_RADIUS                = 0xc6,   //!<apsNonmemberRadius
  APS_AIB_PERMISSIONS_CONFIGURATION       = 0xc7,   //!<apsPermissionsConfiguration
  APS_AIB_USE_INSECURE_JOIN               = 0xc8,   //!<apsUseInsecureJoin
  APS_AIB_INTERFRAME_DELAY                = 0xc9,   //!<apsInterframeDelay

  APS_AIB_PARENT_ANNOUNCE_TIMER           = 0xce,	//!<apsParentAnnounceTimer

  //AIB non-standard attributes
  APS_AIB_FRAG_WINDOW_SIZE                = 0xe0,
  APS_AIB_FRAG_TX_DROP_MASK               = 0xe1,
  APS_AIB_FRAG_RX_DROP_MASK               = 0xe2
} APS_AibAttributeId_t;

BEGIN_PACK
typedef struct PACK
{
  uint8_t apsHeader[APS_ASDU_OFFSET];
  uint8_t payload[APS_MAX_ASDU_SIZE];
  uint8_t apsFooter[APS_MAX_DATA_FRAME_FOOTER_LENGTH];
} RApsFrame_t;

typedef struct PACK
{
  uint8_t  macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH];
  uint8_t  macPayload[MAC_MAX_MSDU_SIZE];
} RMacFrame_t;
END_PACK

typedef union
{
  MAC_DataReq_t  macDataReq;
  RF_RegAccessReq_t rfRegAccessReq;
  RMacFrame_t  macFrame;
  ZDO_StartNetworkReq_t zdoStartNetworkReq;
#if (BDB_SUPPORT == 1)
  BDB_InvokeCommissioningReq_t bdbInvokeCommReq;
#endif
  APS_DataReq_t apsDataReq;
  RApsFrame_t apsFrame;
  //  NWK_SetReq_t nwkSetReq;
  ZDO_ZdpReq_t zdpClientReq;
  NWK_ResetReq_t  nwkResetReq;
  RNwkDiscovery_t  nwkDiscovery;
  NWK_RouteDiscoveryReq_t nwkRouteDiscoveryReq;
  ZDO_Neib_t neibTableConf[CS_NEIB_TABLE_SIZE];

#ifdef _SECURITY_
  APS_TransportKeyReq_t *apsTransportKeyReq;
#endif /* _SECURITY_ */

#ifdef _BINDING_
  APS_BindReq_t apsBindReq;
  APS_UnbindReq_t apsUnbindReq;
#endif /* _BINDING_ */

#if defined(_ZCL_SUPPORT_)&& defined(_LINK_SECURITY_) && !defined(_LIGHT_LINK_PROFILE_)
  ZCL_StartSecurityReq_t zclStartSecurityReq;
#endif /* (defined _LINK_SECURITY_) && (!defined _LIGHT_LINK_PROFILE_) */

  HAL_AppTimer_t appTimer;
#ifdef _CHILD_MANAGEMENT_
  NWK_EndDeviceTimeoutReq_t endDeviceTimeoutReq;
#endif /* _CHILD_MANAGEMENT_ */
} StackReq_t;

typedef struct
{
  bool busy;
  void *link;
  StackReq_t stackReq;
} RMemEntry_t;

typedef struct
{
  RMemEntry_t buffers[R_MAX_ACTIVE_TRANSACTIONS_AMOUNT];
} RAppMem_t;

#if (BDB_SUPPORT == 1)
typedef struct PACK
{
  uint8_t  status;
} RBdbInvokeCommConfirm_t;

typedef struct PACK
{
  BDB_CommissioningMode_t mode;
  /** \brief Power failure protection control. If enabled - device parameters
   * will be protected in non-volatile storage. This service is provided by
   * the PDS.
   */
  uint8_t powerFailureProtection;
  uint16_t groupId;
}RBdbInvokeCommReq_t;

typedef struct PACK
{
  InstallCode_Configuration_Status_t  status;
}RBdbSetInstallCodeConfirm_t;

typedef struct PACK
{
  ExtAddr_t addr;
  uint8_t installCode[18];
}RBdbSetInstallCodeReq_t;
#endif
/******************************************************************************
                   Prototypes section
******************************************************************************/
void rPostTask(RTaskId_t taskId);

#endif  /* _RTYPES_H */

/* eof rTypes.h */
