/***************************************************************************//**
  \file ZAppSiCommands.h

  \brief This file defines commands structure

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

*******************************************************************************/

#ifndef _ZAPPSICOMMANDS_H
#define _ZAPPSICOMMANDS_H

/******************************************************************************
                   Includes section
 ******************************************************************************/

#include <systemenvironment/include/sysTypes.h>
#include <aps/include/aps.h>
#include <nwk/include/nlmeSetGet.h>
#include <nwk/include/nwk.h>
#include <zdo/include/zdo.h>
#include <security/TrustCentre/include/tcDeviceTableCtrl.h>

#include <stdbool.h>
#ifdef _ZCL_SUPPORT_ 

#include <zcl/include/zcl.h>
#include <zcl/include/clusters.h>
#include <zcl/include/zclIdentifyCluster.h>
#include <zcl/include/zclPriceCluster.h>
#include <zcl/include/zclOnOffCluster.h>
#include <zcl/include/zclLevelControlCluster.h>
#include <zcl/include/zclOnOffSwitchConfigurationCluster.h>
#include <zcl/include/zclGroupsCluster.h>
#include <zcl/include/zclScenesCluster.h>

#include <zcl/include/zclDemandResponseCluster.h>
#include <zcl/include/zclMessagingCluster.h>
#include <zcl/include/zclSecurityManager.h>
#endif // ZCL_SUPPORT == 1
#if (BDB_SUPPORT == 1)
#include <bdb/include/bdb.h>
#endif

BEGIN_PACK
/***************************************************************************//**
\brief Enumeration of status values.
*******************************************************************************/
typedef enum
{
  ZS_SUCCESS_STATUS = 0x00,
  ZS_INVALID_PARAMETER_STATUS,
  ZS_UNSUPPORTED_ATTRIBUTE_STATUS,
  ZS_FAIL_STATUS
} ZS_Status_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysResetReq function.
*******************************************************************************/
typedef struct PACK
{
  uint8_t resetType;
} ZS_SysResetReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysResetConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_Status_t. */
  uint8_t status;
} ZS_SysResetConf_t;
/***************************************************************************//**
\brief Enumeration of attribute identificatiors.
*******************************************************************************/
typedef enum
{
    ZS_INIT_LOGICAL_CHANNEL_ATTR_ID  = 0x00,
    ZS_NWK_PANID_ATTR_ID             = 0x01,
    ZS_RF_TX_POWER_ATTR_ID           = 0x02,
    ZS_ADD_DEVICE_TO_PERMISSION_TABLE_ATTR_ID = 0x03,
    ZS_REMOVE_DEVICE_FROM_PERMISSION_TABLE_ATTR_ID = 0x04,
    ZS_TRUST_CENTER_ADDRESS_ATTR_ID  = 0x05,
    ZS_PERMIT_REJOIN_ATTR_ID         = 0x06,
    ZS_DEFAULT_PERMISSIONS_ATTR_ID   = 0x07,
	ZS_CERTIFICATION_CTRL_ATTR_ID    = 0x08,
    ZS_JOIN_CONTROL_ATTR_ID          = 0x10,
    ZS_RX_ON_WHEN_IDLE_ATTR_ID       = 0x52,
    ZS_EXTENDED_ADDRESS_ATTR_ID      = 0x6f,
    ZS_PANID_ATTR_ID                 = 0x80,
    ZS_NIB_SYM_LINK_ATTR_ID          = 0x8E,
    ZS_NETWORK_ADDRESS_ATTR_ID       = 0x96,
    ZS_STACK_PROFILE_ATTR_ID         = 0x97,
    ZS_NWK_EXTENDED_PANID_ATTR_ID    = 0x9A,
    ZS_NWK_USE_MULTICAST_ATTR_ID     = 0x9B,
    ZS_CONCENTRATOR_DISCOVERY_TIME_ATTR_ID = 0x9F,
    ZS_NETWORK_KEY_ATTR_ID           = 0xA1,
    ZS_NETWORK_KEY2_ATTR_ID          = 0xAE,
    ZS_UNIQUE_ADDR_ATTR_ID           = 0xA8,
    ZS_LEAVE_REQ_ALLOWED_ATTR_ID     = 0xA9,
    ZS_INDIRECT_POLL_RATE_ATTR_ID    = 0xAB,
    ZS_PROTOCOL_VERSION_ATTR_ID      = 0xAC,
    ZS_DISTRIBUTED_SECURITY_ID       = 0xAD,
    ZS_NETWORK_KEY_AMOUNT_ATTR_ID    = 0xC0,
    ZS_SECURITY_KEY_ATTR_ID          = 0xC1,
    ZS_CHANNEL_MASK_ATTR_ID          = 0xC3,
    ZS_EXTENDED_PANID_ATTR_ID        = 0xC4,
    ZS_ADDRESS_ASSIGNMENT_METHOD_ID  = 0xC5,
    ZS_ZDO_SECURITY_STATUS_ATTR_ID   = 0xC7,
    ZS_END_DEVICE_SLEEP_PERIOD_ATTR_ID     = 0xC8,
    ZS_APS_PARENT_ANNOUNCE_TIMER_ID  = 0xCE,
    ZS_CHANNEL_PAGE_ATTR_ID          = 0xDD,
    ZS_END_DEVICE_TIMEOUT_ATTR_ID    = 0xE0,
    ZS_NWK_PARENT_INFO_REQUEST       = 0xE1,
    ZS_SEC_AUTH_TIMEOUT_REQUEST_ID   = 0xE2,
    ZS_ZDO_ENABLE_INTERNAL_HANDLING_ATTR_ID  = 0xE3,
    ZS_BDB_TC_LINK_KEY_EXCHANGE_METHOD = 0xE4,
    ZS_BDB_TRUST_CENTER_NODE_JOIN_TIMEOUT = 0xE5,
    ZS_BDB_TRUST_CENTER_REQUIRE_KEY_EXCHANGE = 0xE6,
    ZS_BDB_JOIN_USES_INSTALL_CODE_KEY = 0xE7,
    ZS_BDB_PRIMARY_CHANNEL_MASK       = 0xE8,
    ZS_BDB_SECONDARY_CHANNEL_MASK     = 0xE9,
    ZS_BDB_TRUST_CENTER_LINK_KEY_EXCHANGE_ATTEMPTS_MAX = 0xEA,
    ZS_OTAU_SERVER_EXT_ADDR_ID       = 0xF6,
    ZS_MAX_NEIGHBOR_ROUTE_COST_ATTR_ID     = 0xF7,
    ZS_PREDEFINED_PANID_ATTR_ID      = 0xF8,
    ZS_SECURITY_ON_ATTR_ID           = 0xF9,
    ZS_USED_FEATURES_ATTR_ID         = 0xFA,
    ZS_PERMIT_DURATION_ATTR_ID       = 0xFB,
    ZS_APS_MAX_FRAME_RETRIES_ATTR_ID = 0xFE,
    ZS_GET_LAST_MESSAGE_RETURN_VALUE_ATTR_ID = 0xFF
} ZS_SysAttributeId_t;
/***************************************************************************//**
\brief Enumeration of key types.
*******************************************************************************/
#ifdef _LINK_SECURITY_
typedef enum
{
    ZS_MASTER_KEY_TYPE = KEY_TYPE_MASTER,
    ZS_LINK_KEY_TYPE = KEY_TYPE_LINK
} ZS_KeyType_t;
#endif // _LINK_SECURITY_
/***************************************************************************//**
\brief Parameters structure for ZS_SysSetReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the attribute id of parameter to write.
     * The values are enumerated in ZS_SysAttributeId_t.
     */
    uint8_t attributeId;
    /** \brief This parameter holds the attribute length in bytes. */
    uint8_t attributeLength;
    /** \brief This parameter holds the value of attribute. */
    union PACK
    {
    /** \brief This parameter holds the 1 byte value. */
        uint8_t uint8;
    /** \brief This parameter holds the 2 bytes value. */
        uint16_t uint16;
    /** \brief This parameter holds the 4 bytes value. */
        uint32_t uint32;
    /** \brief This parameter holds the 8 bytes value. */
        uint64_t uint64;
    /** \brief This parameter holds the device keys for trust center. */
        struct PACK
        {
    /** \brief This parameter holds the device address. */
          int64_t deviceAddress;
    /** \brief This parameter holds the link key. */
          uint8_t linkKey[SECURITY_KEY_SIZE];
    /** \brief This parameter holds the key type.
     * The values are enumerated in ZS_KeyType_t.
     */
          uint8_t keyType;
        } tcDeviceKey;
    /** \brief This parameter holds the network key. */
        uint8_t nwkKey[SECURITY_KEY_SIZE];
    } attributeValue;
} ZS_SysSetReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysSetConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the status of confirm.
          The values are enumerated in ZS_Status_t. */
  uint8_t status;
  /** \brief This parameter holds the attribute identifier of parameter has been written.
   * The values are enumerated in ZS_SysAttributeId_t.
   */
  uint8_t attributeId;
} ZS_SysSetConf_t;
/***************************************************************************//**
\brief Parameters structure for SysGetReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the attribute identifier of parameter to read.
     * The values are enumerated in ZS_SysAttributeId_t.
     */
  uint8_t attributeId;
} ZS_SysGetReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysSetConf function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status of confirm.
     * The values are enumerated in ZS_Status_t.
     */
    uint8_t status;
    /** \brief This parameter holds the attribute identifier of parameter has been read.
     * The values are enumerated in ZS_SysAttributeId_t.
     */
    uint8_t attributeId;
    /** \brief This parameter holds the attribute length in bytes. */
    uint8_t attributeLength;
    /** \brief This parameter holds the value of attribute. */
    union
    {
    /** \brief This parameter holds the 1 byte value. */
        uint8_t uint8;
    /** \brief This parameter holds the 2 bytes value. */
        uint16_t uint16;
    /** \brief This parameter holds the 4 bytes value. */
        uint32_t uint32;
    /** \brief This parameter holds the 8 bytes value. */
        uint64_t uint64;
    /** \brief This parameter holds the 16 bytes value. */
        uint8_t uint128[SECURITY_KEY_SIZE];
    } attributeValue;
} ZS_SysGetConf_t;

/***************************************************************************//**
\brief Parameters structure for ZS_SysSleepWhenIdleReq function.
*******************************************************************************/
typedef struct PACK
{
  uint8_t action;
} ZS_SysSleepWhenIdleReq_t;

/***************************************************************************//**
\brief Parameters structure for ZS_SysSleepWhenIdleConf function.
*******************************************************************************/
typedef struct PACK
{
  uint8_t status;
} ZS_SysSleepWhenIdleConf_t;

/***************************************************************************//**
\brief Enumeration of device types.
*******************************************************************************/
typedef enum
{
    ZS_DEVICE_TYPE_COORDINATOR = DEVICE_TYPE_COORDINATOR,
    ZS_DEVICE_TYPE_ROUTER = DEVICE_TYPE_ROUTER,
    ZS_DEVICE_TYPE_ENDDEVICE = DEVICE_TYPE_END_DEVICE
} ZS_DeviceType_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysSetDeviceTypeReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the device type to set.
     * The values are enumerated in ZS_DeviceType_t.
     */
  uint8_t deviceType;
} ZS_SysSetDeviceTypeReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_SysSetDeviceTypeConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the device type has been set.
     * The values are enumerated in ZS_DeviceType_t.
     */
  uint8_t deviceType;
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_Status_t.
   */
  uint8_t status;
} ZS_SysSetDeviceTypeConf_t;

/***************************************************************************//**
\brief Parameters structure for ZS_StartReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief Power failure protection control. If enabled - device parameters
     * will be protected in non-volatile storage. This service is provided by
     * the PDS.
     */
  uint8_t powerFailureProtection;
} ZS_StartReq_t;

/***************************************************************************//**
\brief Enumeration of address modes.
*******************************************************************************/
typedef enum
{
    ZS_GROUP_ADDRESS_MODE = 0x01,
    ZS_SHORT_ADDRESS_MODE = 0x02,
    ZS_EXTENDED_ADDRESS_MODE = 0x03
} ZS_AddresMode_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsBindReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the source address. */
  uint64_t srcAddr;
  /** \brief This parameter holds the source endpoint number. */
  uint8_t srcEndpoint;
  /** \brief This parameter holds the cluster idnetifier. */
  uint16_t clusterId;
  /** \brief This parameter holds the destination address mode.
   * The values are enumerated in ZS_AddressMode_t. */
  uint8_t dstAddrMode;
  union PACK
  {
    struct PACK
    {
  /** \brief This parameter holds the destination exetended address. */
      uint64_t dstExtAddr;
  /** \brief This parameter holds the destination endpoint number. */
      uint8_t dstEndpoint;
    };
  /** \brief This parameter holds the destination group address. */
    uint16_t dstGroupAddr;
  };
} ZS_ApsBindReq_t;
/***************************************************************************//**
\brief Enumeration of ApsBindConf statuses.
*******************************************************************************/
typedef enum
{
    ZS_APS_BIND_CONF_SUCCESS_STATUS = APS_SUCCESS_STATUS,
    ZS_APS_BIND_CONF_TABLE_FULL_STATUS = APS_TABLE_FULL_STATUS,
    ZS_APS_BIND_CONF_ILLEGAL_REQUEST_STATUS = APS_ILLEGAL_REQUEST_STATUS,
    ZS_APS_BIND_CONF_NOT_SUPPORTED_STATUS = APS_NOT_SUPPORTED_STATUS
} ZS_ApsBindConfStatus_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsBindConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_ApsBindConfStatus_t. */
  uint8_t     status;
  /** \brief This parameter holds the source address. */
  uint64_t    srcAddr;
  /** \brief This parameter holds the source endpoint number. */
  uint8_t     srcEndpoint;
  /** \brief This parameter holds the cluster identification. */
  uint16_t    clusterId;
  /** \brief This parameter holds the destination address mode. */
  uint8_t     dstAddrMode;
  union PACK
  {
    struct PACK
    {
  /** \brief This parameter holds the destination extended address. */
      uint64_t  dstExtAddr;
  /** \brief This parameter holds the destination endpoint number. */
      uint8_t   dstEndpoint;
    };
  /** \brief This parameter holds the destination group address. */
    uint16_t    dstGroupAddr;
  };
} ZS_ApsBindConf_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsDataReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the destination address mode.
     * The values are enumerated in ZS_AddresMode_t. */
    uint8_t dstAddrMode;
    union
    {
    /** \brief This parameter holds the short address. */
        uint16_t shortAddr;
    /** \brief This parameter holds the extended address. */
        uint64_t extAddr;
    } dstAddr;
    /** \brief This parameter holds the destination endpoint number. */
    uint8_t dstEndpoint;
    /** \brief This parameter holds the profile identificatior. */
    uint16_t profileId;
    /** \brief This parameter holds the cluster identificator. */
    uint16_t clusterId;
    /** \brief This parameter holds the source endpoint number. */
    uint8_t srcEndpoint;
    /** \brief This parameter holds the asdu length. */
    uint8_t asduLength;
    /** \brief This parameter holds the pointer to asdu to send. */
    uint8_t *asdu;
    /** \brief This parameter holds the transmit options. */
    uint8_t txOptions;
    /** \brief This parameter holds the radius count. */
    uint8_t radiusCount;
} ZS_ApsDataReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsDataConf function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the destination address mode.
     * The values are enumerated in ZS_AddresMode_t. */
    uint8_t dstAddrMode;
    union
    {
    /** \brief This parameter holds the short address. */
        uint16_t shortAddr;
    /** \brief This parameter holds the extended address. */
        uint64_t extAddr;
    };
    /** \brief This parameter holds the destination endpoint number. */
    uint8_t dstEndpoint;
    /** \brief This parameter holds the source endpoint number. */
    uint8_t srcEndpoint;
    /** \brief This parameter holds the status of confirm.
     * The values are enumerated in ZS_Status_t. */
    uint8_t status;
} ZS_ApsDataConf_t;
/***************************************************************************//**
\brief Enumeration of aps security statuses.
*******************************************************************************/
typedef enum
{
  ZS_UNSECURED_STATUS = APS_UNSECURED_STATUS,
  ZS_SECURED_LINK_KEY_STATUS = APS_SECURED_LINK_KEY_STATUS,
  ZS_SECURED_NWK_KEY_STATUS = APS_SECURED_NWK_KEY_STATUS
} ZS_ApsSecurityStatus_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsDataInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the destination address mode.
     * The values are enumerated in ZS_AddresMode_t. */
    uint8_t dstAddrMode;
    /** \brief This parameter holds the destination address. */
    union
    {
    /** \brief This parameter holds the short address. */
        uint16_t shortAddr;
    /** \brief This parameter holds the extended address. */
        uint64_t extAddr;
    } dstAddr;
    /** \brief This parameter holds the destination endpoint number. */
    uint8_t dstEndpoint;
    /** \brief This parameter holds the source address mode.
     * The values are enumerated in ZS_AddresMode_t. */
    uint8_t srcAddrMode;
    /** \brief This parameter holds the source address. */
    union
    {
    /** \brief This parameter holds the short address. */
        uint16_t shortAddr;
    /** \brief This parameter holds the extended address. */
        uint64_t extAddr;
    } srcAddr;
    /** \brief This parameter holds the source endpoint number. */
    uint8_t srcEndpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the profile identifier. */
    uint16_t profileId;
    /** \brief This parameter holds the asdu length. */
    uint8_t asduLength;
    /** \brief This parameter holds the asdu. */
    uint8_t *asdu;
    /** \brief This parameter holds the status of confirm.
     * This values are enumerated in ZS_Status_t. */
    uint8_t status;
    /** \brief This parameter holds the security status.
     * The values are enumerated in ZS_ApsSecurityStatus_t. */
    uint8_t securityStatus;
} ZS_ApsDataInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsUnbindReq_t.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the source address. */
  uint64_t    srcAddr;
  /** \brief This parameter holds the source endpoint number. */
  uint8_t     srcEndpoint;
  /** \brief This parameter holds the cluster identifier. */
  uint16_t    clusterId;
  /** \brief This parameter holds the destination address mode.
   * The values are enumerated in ZS_AddresMode_t. */
  uint8_t     dstAddrMode;
  union PACK
  {
    struct PACK
    {
      /** \brief This parameter holds the destination extended address */
      uint64_t  dstExtAddr;
      /** \brief This parameter holds the destination endpoint number. */
      uint8_t   dstEndpoint;
    };
    /** \brief This parameter holds the destination group address. */
    uint16_t    dstGroupAddr;
  };
} ZS_ApsUnbindReq_t;
/***************************************************************************//**
\brief Parameters structure for
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds */
  uint8_t     status;
  /** \brief This parameter holds */
  uint64_t    srcAddr;
  /** \brief This parameter holds */
  uint8_t     srcEndpoint;
  /** \brief This parameter holds */
  uint16_t    clusterId;
  /** \brief This parameter holds */
  uint8_t     dstAddrMode;
  union PACK
  {
    struct PACK
    {
      /** \brief This parameter holds */
      uint64_t  dstExtAddr;
      /** \brief This parameter holds */
      uint8_t   dstEndpoint;
    };
    /** \brief This parameter holds */
    uint16_t    dstGroupAddr;
  };
} ZS_ApsUnbindConf_t;

typedef struct PACK
{
  uint8_t attributeId;
} ZS_ApsGetReq_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t attributeId;
  uint8_t attributeLength;
  uint8_t attributeValue[1];
} ZS_ApsGetConf_t;

typedef struct PACK
{
  uint8_t attributeId;
  uint8_t attributeLength;
  uint8_t attributeValue[1];
} ZS_ApsSetReq_t;

typedef struct PACK
{
  uint8_t status;
  uint8_t attributeId;
} ZS_ApsSetConf_t;

typedef struct PACK
{
  uint16_t groupAddress;
  uint8_t endpoint;
} ZS_ApsAddGroupReq_t;

typedef struct PACK
{
  uint8_t status;
  uint16_t groupAddress;
  uint8_t endpoint;
} ZS_ApsAddGroupConf_t;
/***************************************************************************//**
 \brief Enumeration of group operation statuses.
*******************************************************************************/
typedef enum
{
    ZS_APS_INVALID_GROUP_STATUS = APS_INVALID_GROUP_STATUS,
    ZS_APS_INVALID_PARAMETER_STATUS = APS_INVALID_PARAMETER_STATUS
} ZS_ApsGroupStatus_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsRemoveGroupReq_t
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the group address. */
  uint16_t groupAddress;
  /** \brief This parameter holds the endpoint number to remove. */
  uint8_t endpoint;
} ZS_ApsRemoveGroupReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsRemoveGroupConf_t.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the status of confirm.
     * The values are enumerated in ZS_ApsGroupStatus_t.
     * ZS_SUCCESS_STATUS if success. */
  uint8_t status;
  /** \brief This parameter holds the group address. */
  uint16_t groupAddress;
  /** \brief This parameter holds endpoint number. */
  uint8_t endpoint;
} ZS_ApsRemoveGroupConf_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsRemoveAllGroupReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the endpoint to remove from group. */
  uint8_t endpoint;
} ZS_ApsRemoveAllGroupsReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsRemoveAllGroupsConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the status of confirm.
     * The values are enumerated in ZS_ApsGroupStatus_t.
     * ZS_SUCCESS_STATUS if success. */
  uint8_t status;
  /** \brief This parameter holds the endpoint that has been removed from group. */
  uint8_t endpoint;
} ZS_ApsRemoveAllGroupsConf_t;
/***************************************************************************//**
\brief Enumeration of aps key types.
*******************************************************************************/

#ifdef _SECURITY_
typedef enum
{
   ZS_APS_APP_LINK_KEY_TYPE = APS_APP_LINK_KEY_TYPE,
   ZS_APS_APP_MASTER_KEY_TYPE = APS_APP_MASTER_KEY_TYPE,
   ZS_APS_STANDARD_NETWORK_KEY_TYPE = APS_STANDARD_NETWORK_KEY_TYPE,
   ZS_APS_HIGH_SECURITY_NETWORK_KEY_TYPE = APS_HIGH_SECURITY_NETWORK_KEY_TYPE,
   ZS_APS_TRUST_CENTER_LINK_KEY_TYPE = APS_TRUST_CENTER_LINK_KEY_TYPE,
   ZS_APS_TRUST_CENTER_MASTER_KEY_TYPE = APS_TRUST_CENTER_MASTER_KEY_TYPE
} ZS_ApsKeyType_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsTransportKeyReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This parameter holds the key type.
   * The values are enumerated in ZS_ApsKeyType_t. */
  uint8_t keyType;
  /** \brief This parameter holds the transport key data. */
  APS_ReqTransportKeyData_t transportKeyData;
} ZS_ApsTransportKeyReq_t;
/***************************************************************************//**
\brief Enumeration of statuses of aps key related operations.
*******************************************************************************/
typedef enum
{
    ZS_APS_NO_SHORT_ADDRESS = 0x01,
    ZS_APS_SECURITY_FAIL = 0x02,
    ZS_APS_NOT_SENT = 0x03
} ZS_ApsKeyConfStatus_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsTransportKeyConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This parameter holds the key type.
   * The values are enumerated in ZS_ApsKeyType_t. */
  uint8_t keyType;
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_ApsKeyConfStatus_t
   * ZS_SUCCESS if success. */
  uint8_t status;
} ZS_ApsTransportKeyConf_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsSwitchKeyReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This parameter holds the key sequence number. */
  uint8_t keySeqNumber;
} ZS_ApsSwitchKeyReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsSwitchKeyConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This property holds the key sequence number. */
  uint8_t keySeqNumber;
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_ApsKeyConfStatus_t
   * ZS_SUCCESS if success. */
  uint8_t status;
} ZS_ApsSwitchKeyConf_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ApsRequestKeyReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This parameter holds the key type.
   * The values are enumerated in ZS_ApsKeyType_t. */
  uint8_t keyType;
  /** \brief This parameter holds the partner address. */
  uint64_t partnerAddress;
} ZS_ApsRequestKeyReq_t;
/***************************************************************************//**
\brief Parameter structure for ZS_ApsRequestKeyConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the destination address. */
  uint64_t destAddress;
  /** \brief This parameter holds the key type.
   * The values are enumerated in ZS_ApsKeyType_t. */
  uint8_t keyType;
  /** \brief This parameter holds the partner address. */
  uint64_t partnerAddress;
  /** \brief This parameter holds the status of confirm.
   * The values are enumerated in ZS_ApsKeyConfStatus_t
   * ZS_SUCCESS if success. */
  uint8_t status;
} ZS_ApsRequestKeyConf_t;
#endif // _SECURITY_

/***************************************************************************//**
\brief Enumeration of attributes types
*******************************************************************************/
#ifdef _ZCL_SUPPORT_ 
typedef enum
{
  //Null
  ZS_ZCL_NO_DATA_TYPE_ID                       = ZCL_NO_DATA_TYPE_ID,

  //General data
  ZS_ZCL_8BIT_DATA_TYPE_ID                     = ZCL_8BIT_DATA_TYPE_ID,
  ZS_ZCL_16BIT_DATA_TYPE_ID                    = ZCL_16BIT_DATA_TYPE_ID,
  ZS_ZCL_24BIT_DATA_TYPE_ID                    = ZCL_24BIT_DATA_TYPE_ID,
  ZS_ZCL_32BIT_DATA_TYPE_ID                    = ZCL_32BIT_DATA_TYPE_ID,
  ZS_ZCL_40BIT_DATA_TYPE_ID                    = ZCL_40BIT_DATA_TYPE_ID,
  ZS_ZCL_48BIT_DATA_TYPE_ID                    = ZCL_48BIT_DATA_TYPE_ID,
  ZS_ZCL_56BIT_DATA_TYPE_ID                    = ZCL_56BIT_DATA_TYPE_ID,
  ZS_ZCL_64BIT_DATA_TYPE_ID                    = ZCL_64BIT_DATA_TYPE_ID,

  //Logical
  ZS_ZCL_BOOLEAN_DATA_TYPE_ID                  = ZCL_BOOLEAN_DATA_TYPE_ID,

  //Bitmap
  ZS_ZCL_8BIT_BITMAP_DATA_TYPE_ID              = ZCL_8BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_16BIT_BITMAP_DATA_TYPE_ID             = ZCL_16BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_24BIT_BITMAP_DATA_TYPE_ID             = ZCL_24BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_32BIT_BITMAP_DATA_TYPE_ID             = ZCL_32BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_40BIT_BITMAP_DATA_TYPE_ID             = ZCL_40BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_48BIT_BITMAP_DATA_TYPE_ID             = ZCL_48BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_56BIT_BITMAP_DATA_TYPE_ID             = ZCL_56BIT_BITMAP_DATA_TYPE_ID,
  ZS_ZCL_64BIT_BITMAP_DATA_TYPE_ID             = ZCL_64BIT_BITMAP_DATA_TYPE_ID,

  //Unsigned integer
  ZS_ZCL_U8BIT_DATA_TYPE_ID                    = ZCL_U8BIT_DATA_TYPE_ID,
  ZS_ZCL_U16BIT_DATA_TYPE_ID                   = ZCL_U16BIT_DATA_TYPE_ID,
  ZS_ZCL_U24BIT_DATA_TYPE_ID                   = ZCL_U24BIT_DATA_TYPE_ID,
  ZS_ZCL_U32BIT_DATA_TYPE_ID                   = ZCL_U32BIT_DATA_TYPE_ID,
  ZS_ZCL_U40BIT_DATA_TYPE_ID                   = ZCL_U40BIT_DATA_TYPE_ID,
  ZS_ZCL_U48BIT_DATA_TYPE_ID                   = ZCL_U48BIT_DATA_TYPE_ID,
  ZS_ZCL_U56BIT_DATA_TYPE_ID                   = ZCL_U56BIT_DATA_TYPE_ID,
  ZS_ZCL_U64BIT_DATA_TYPE_ID                   = ZCL_U64BIT_DATA_TYPE_ID,

  //Signed integer
  ZS_ZCL_S8BIT_DATA_TYPE_ID                    = ZCL_S8BIT_DATA_TYPE_ID,
  ZS_ZCL_S16BIT_DATA_TYPE_ID                   = ZCL_S16BIT_DATA_TYPE_ID,
  ZS_ZCL_S24BIT_DATA_TYPE_ID                   = ZCL_S24BIT_DATA_TYPE_ID,
  ZS_ZCL_S32BIT_DATA_TYPE_ID                   = ZCL_S32BIT_DATA_TYPE_ID,
  ZS_ZCL_S40BIT_DATA_TYPE_ID                   = ZCL_S40BIT_DATA_TYPE_ID,
  ZS_ZCL_S48BIT_DATA_TYPE_ID                   = ZCL_S48BIT_DATA_TYPE_ID,
  ZS_ZCL_S56BIT_DATA_TYPE_ID                   = ZCL_S56BIT_DATA_TYPE_ID,
  ZS_ZCL_S64BIT_DATA_TYPE_ID                   = ZCL_S64BIT_DATA_TYPE_ID,

  //Enumeration
  ZS_ZCL_8BIT_ENUM_DATA_TYPE_ID                = ZCL_8BIT_ENUM_DATA_TYPE_ID,
  ZS_ZCL_16BIT_ENUM_DATA_TYPE_ID               = ZCL_16BIT_ENUM_DATA_TYPE_ID,

  //Floating point
  ZS_ZCL_FSEMI_PRECISION_DATA_TYPE_ID          = ZCL_FSEMI_PRECISION_DATA_TYPE_ID,
  ZS_ZCL_FSINGLE_PRECISION_DATA_TYPE_ID        = ZCL_FSINGLE_PRECISION_DATA_TYPE_ID,
  ZS_ZCL_FDOUBLE_PRECISION_DATA_TYPE_ID        = ZCL_FDOUBLE_PRECISION_DATA_TYPE_ID,

  //String
  ZS_ZCL_OCTET_STRING_DATA_TYPE_ID             = ZCL_OCTET_STRING_DATA_TYPE_ID,
  ZS_ZCL_CHARACTER_STRING_DATA_TYPE_ID         = ZCL_CHARACTER_STRING_DATA_TYPE_ID,
  ZS_ZCL_LONG_OCTET_STRING_DATA_TYPE_ID        = ZCL_LONG_OCTET_STRING_DATA_TYPE_ID,
  ZS_ZCL_LONG_CHARACTER_STRING_DATA_TYPE_ID    = ZCL_LONG_CHARACTER_STRING_DATA_TYPE_ID,

  //Ordered sequence
  ZS_ZCL_ARRAY_DATA_TYPE_ID                    = ZCL_ARRAY_DATA_TYPE_ID,
  ZS_ZCL_STRUCTURE_DATA_TYPE_ID                = ZCL_STRUCTURE_DATA_TYPE_ID,

  //Collection
  ZS_ZCL_SET_DATA_TYPE_ID                      = ZCL_SET_DATA_TYPE_ID,
  ZS_ZCL_BAG_DATA_TYPE_ID                      = ZCL_BAG_DATA_TYPE_ID,

  //Time
  ZS_ZCL_TIME_OF_DAY_DATA_TYPE_ID              = ZCL_TIME_OF_DAY_DATA_TYPE_ID,
  ZS_ZCL_DATE_DATA_TYPE_ID                     = ZCL_DATE_DATA_TYPE_ID,
  ZS_ZCL_UTC_TIME_DATA_TYPE_ID                 = ZCL_UTC_TIME_DATA_TYPE_ID,

  //Identifier
  ZS_ZCL_CLUSTER_ID_DATA_TYPE_ID               = ZCL_CLUSTER_ID_DATA_TYPE_ID,
  ZS_ZCL_ATTRIBUTE_ID_DATA_TYPE_ID             = ZCL_ATTRIBUTE_ID_DATA_TYPE_ID,
  ZS_ZCL_BACNET_OID_DATA_TYPE_ID               = ZCL_BACNET_OID_DATA_TYPE_ID,

  //Misscellaneous
  ZS_ZCL_IEEE_ADDRESS_DATA_TYPE_ID             = ZCL_IEEE_ADDRESS_DATA_TYPE_ID,
  ZS_ZCL_128BIT_SECURITY_KEY_DATA_TYPE_ID      = ZCL_128BIT_SECURITY_KEY_DATA_TYPE_ID,
} ZS_AttributeType_t;
/***************************************************************************//**
\brief Enumeration of frame control's direction values.
*******************************************************************************/
typedef enum
{
    ZS_DIRECTION_FROM_CLIENT_TO_SERVER = ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZS_DIRECTION_FROM_SERVER_TO_CLIENT = ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT
} ZS_FrameControlDirection_t;
/***************************************************************************//**
\brief Enumeration of read/write attribute response statuses.
*******************************************************************************/
typedef enum
{
   ZS_ZCL_UNSUPPORTED_ATTRIBUTE_STATUS = ZCL_UNSUPPORTED_ATTRIBUTE_STATUS,
   ZS_ZCL_ATTRIBUTE_NOT_FOUND = 0xC4
} ZS_ZclRWAttributeResponseStatus_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReadAttributeReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the endpoint value. */
    uint8_t endpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the default response value.
     *  0 - enables default response. 1 - disables default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of atrributes identifiers. */
    uint16_t *attributes;
} ZS_ZclReadAttributeReq_t;
/***************************************************************************//**
\brief Structure defines type/value pair.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the type of value. */
    uint8_t type;
    /** \brief This parameter holds the pointer to the value. */
    void *value;
} ZS_ZclTypeValue_t;
/***************************************************************************//**
\brief Structure defines read attribute response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
    /** \brief This parameter holds the status.
     * The values are defined in ZS_ZclRWAttributeResponseStatus_t.
     * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the attribute's type and value. */
    ZS_ZclTypeValue_t *attribute;
} ZS_ZclReadAttributeRespRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReadAttributeResp function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status of response.
     * ZS_SUCCESS_STATUS if success.
     */
    uint8_t status;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclReadAttributeRespRecord_t */
    ZS_ZclReadAttributeRespRecord_t *records;
} ZS_ZclReadAttributeResp_t;
/***************************************************************************//**
 \brief Parameters structure for Structure defines write attribute
 response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
    /** \brief This parameter holds the attribute's type and value. */
    ZS_ZclTypeValue_t typeValue;
} ZS_ZclWriteAttributeRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclWriteAttributeReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the endpoint number. */
    uint8_t endpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the default response value.
     *  0 - enables default response. 1 - disables default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclWriteAttributeRecord_t */
    ZS_ZclWriteAttributeRecord_t *records;
} ZS_ZclWriteAttributeReq_t;

/***************************************************************************//**
\brief Structure defines write attribute response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status.
     * The values are defined in ZS_ZclRWAttributeResponseStatus_t.
     * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
} ZS_ZclWriteAttributeRespRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclWriteAttributeResp function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status of response.
     * ZS_SUCCESS_STATUS if success.
     */
    uint8_t status;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclWriteAttributeRespRecord_t */
    ZS_ZclWriteAttributeRespRecord_t *records;
} ZS_ZclWriteAttributeResp_t;
/***************************************************************************//**
\brief Structure defines configure reporting request record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the direction value.
     * Values are enumerated in ZS_FrameControlDirection_t.
     */
    uint8_t direction;
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
    /** \brief This parameter holds the attribute type. */
    uint8_t attributeType;
    /** \brief This parameter holds the minimum reporting interval. */
    uint16_t minReportingInterval;
    /** \brief This parameter holds the maximum reporting interval. */
    uint16_t maxReportingInterval;
    /** \brief This parameter holds the reportable chage value. */
    void *reportableChange;
   // uint16_t timeoutPeriod; // didn't find where it is used in zcl.
} ZS_ZclConfigureReportingReqRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclConfigureReportingReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the endpoint number. */
    uint8_t endpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the default response value.
     *  0 - enables default response. 1 - disables default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclConfigureReportingReqRecord_t. */
    ZS_ZclConfigureReportingReqRecord_t *records;
} ZS_ZclConfigureReportingReq_t;
/***************************************************************************//**
\brief Structure defines configure reporting response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status.
    * The values are defined in ZS_ZclRWAttributeResponseStatus_t.
    * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the direction value.
     * Values are enumerated in ZS_FrameControlDirection_t.
     */
    uint8_t direction;
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
} ZS_ZclConfigureReportingRespRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclConfigureReportingResp function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status of response.
     * ZS_SUCCESS_STATUS if success.
     */
    uint8_t status;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclConfigureReportingRespRecord_t. */
    ZS_ZclConfigureReportingRespRecord_t *records;
} ZS_ZclConfigureReportingResp_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclDiscoverAttributesReq_t function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the endpoint number */
    uint8_t endpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the default response value.
     *  0 - enables default response. 1 - disables default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the start attribute identifier. */
    uint16_t startAttributeId;
    /** \brief This parameter holds the maximum count of attribute identifiers. */
    uint8_t maxAttributeIds;
} ZS_ZclDiscoverAttributesReq_t;
/***************************************************************************//**
\brief Structure defines discover attributes response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
    /** \brief This parameter holds the type identifier. */
    uint8_t typeId;
} ZS_ZclDiscoverAttributesRespRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclDiscoverAttributesResp function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status.
    * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the discovery complete value.
     * 1 if discovery has completed.
     */
    uint8_t discoveryComplete;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclDiscoverAttributesRespRecord_t. */
    ZS_ZclDiscoverAttributesRespRecord_t *records;
} ZS_ZclDiscoverAttributesResp_t;
/***************************************************************************//**
\brief Structure defines read reporting configure request record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the direction value.
     * Values are enumerated in ZS_FrameControlDirection_t.
     */
    uint8_t direction;
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
} ZS_ZclReadReportingConigReqRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReadReportingConfigReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the endpoint number. */
    uint8_t endpoint;
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the default response value.
     *  0 - enables default response. 1 - disables default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclReadReportingConigReqRecord_t. */
    ZS_ZclReadReportingConigReqRecord_t *records;
} ZS_ZclReadReportingConfigReq_t;
/***************************************************************************//**
\brief Structure defines read reporting configure response record.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status.
    * The values are defined in ZS_ZclRWAttributeResponseStatus_t.
    * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the direction value.
     * Values are enumerated in ZS_FrameControlDirection_t.
     */
    uint8_t direction;
    /** \brief This parameter holds the attribute identifier. */
    uint16_t attributeId;
    /** \brief This parameter holds the attribute type. */
    uint8_t attributeType;
    /** \brief This parameter holds the minimum reporting interval. */
    uint16_t minReportingInterval;
    /** \brief This parameter holds the maximum reporting interval. */
    uint16_t maxReportingInterval;
    /** \brief This parameter holds the reportable chage value. */
    void *reportableChange;
} ZS_ZclReadReportingConfigRespRecord_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReadReportingConfigResp function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the status.
    * ZS_SUCCESS_STATUS if success. */
    uint8_t status;
    /** \brief This parameter holds the number of records. */
    uint8_t recordsCount;
    /** \brief This parameter holds the array of ZS_ZclReadReportingConfigRespRecord_t. */
    ZS_ZclReadReportingConfigRespRecord_t *records;
} ZS_ZclReadReportingConfigResp_t;
/***************************************************************************//**
\brief Common parameters structure for command requests.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the src endpoint number. */
    uint8_t srcEndpoint;
    /** \brief This parameter holds the dst endpoint number. */
    uint8_t dstEndpoint;
    /** \brief This parameter holds the default response. */
    uint8_t defaultResponse;
    /** \brief This parameter holds the sequence number. */
    uint8_t sequenceNumber;
} ZS_ZclCommandReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Identify command parameters. */
    ZCL_Identify_t identify;
} ZS_ZclIdentifyReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyQueryReq function.
*******************************************************************************/
typedef ZS_ZclCommandReq_t ZS_ZclIdentifyQueryReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyQueryResponseReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Identify Query Response parameters. */
    ZCL_IdentifyQueryResponse_t identifyQueryResponse;
} ZS_ZclIdentifyQueryResponseReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetCurrentPriceReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Get Current Price parameters. */
    ZCL_GetCurrentPrice_t getCurrentPrice;
} ZS_ZclGetCurrentPriceReq_t;
/***************************************************************************//**
\brief Parameters for Publish Price command.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the provider identifier. */
    uint32_t providerId;
    /** \brief This parameter holds the rate label length. */
    uint8_t rateLabelLength;
    /** \brief This parameter holds the pointer to rate label string. */
    uint8_t *rateLabel;
    /** \brief This parameter holds the issuer event identifier. */
    uint32_t issuerEventId;
    /** \brief This parameter holds the current time. */
    uint32_t currentTime;
    /** \brief This parameter holds the unit of measure. */
    uint8_t unitOfMeasure;
    /** \brief This parameter holds the currency of price. */
    uint16_t currency;
    /** \brief This parameter holds the */
    struct PACK
    {
        /** \brief This parameter holds the price tier. */
        uint8_t priceTier : 4;
        /** \brief This parameter holds the price trail digit. */
        uint8_t priceTrailDigit : 4;
    } priceTrailDigitPriceTier;
    struct PACK
    {
        /** \brief This parameter holds the register tier. */
        uint8_t registerTier : 4;
        /** \brief This parameter holds the number of price tiers. */
        uint8_t numberOfPriceTiers : 4;
    } numberOfPriceTiersRegisterTier;
    /** \brief This parameter holds the start time. */
    uint32_t startTime;
    /** \brief This parameter holds the duration in minutes. */
    uint16_t durationInMinutes;
    /** \brief This parameter holds the price. */
    uint32_t price;
    /** \brief This parameter holds the price ratio. */
    uint8_t priceRatio;
    /** \brief This parameter holds the generation price. */
    uint32_t generationPrice;
    /** \brief This parameter holds the generation price ratio. */
    uint8_t generationPriceRatio;
} ZS_ZclPublishPrice_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclPublishPriceReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Publish Price command parameters. */
    ZS_ZclPublishPrice_t publishPrice;
} ZS_ZclPublishPriceReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReportEventStatusReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Report Event Status command parameters.*/
    ZCL_ReportEventStatus_t reportEventStatus;
} ZS_ZclReportEventStatusReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetScheduledEventsReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Get Scheduled Events command parameters. */
    ZCL_GetScheduledEvents_t getScheduledEvents;
} ZS_ZclGetScheduledEventsReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclLoadControlEventReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Load Control Event command parameters. */
    ZCL_LoadControlEvent_t loadControlEvent;
} ZS_ZclLoadControlEventReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelLoadControlEventReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Cancel Load Control Event command
     * parameters.*/
    ZCL_CancelLoadControlEvent_t cancelLoadControlEvent;
} ZS_ZclCancelLoadControlEventReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelAllLoadControlEventsReq
 function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Cancel All Load Control Events
     * parameters. */
    ZCL_CancelAllLoadControlEvents_t cancelAllLoadControlEvents;
} ZS_ZclCancelAllLoadControlEventsReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetLastMessageReq function.
*******************************************************************************/
typedef ZS_ZclCommandReq_t ZS_ZclGetLastMessageReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclMessageConfirmationReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Message Confirmation command. */
    MessageConfirmation_t messageConfirmation;
} ZS_ZclMessageConfirmationReq_t;
/***************************************************************************//**
\brief Parameters Display Message command.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the message identifier. */
    uint32_t messageId;
    /** \brief This parameter holds the message control. */
    MessageControl_t messageControl;
    /** \brief This parameter holds the start time. */
    uint32_t startTime;
    /** \brief This parameter holds the duration. */
    uint16_t duration;
    /** \brief This parameter holds the message length. */
    uint8_t messageLength;
    /** \brief This parameter holds the message string. */
    char *message;
} ZS_ZclDisplayMessage_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclDisplayMessageReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Display Message command parameters. */
    ZS_ZclDisplayMessage_t displayMessage;
} ZS_ZclDisplayMessageReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelMessageReq function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandReq_t command;
    /** \brief This parameter holds the Cancel Message command. */
    CancelMessage_t cancelMessage;
} ZS_ZclCancelMessageReq_t;
/***************************************************************************//**
\brief Common parameters structure for command indications.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the source address mode.
     * The values are enumerated in ZS_AddresMode_t. */
    uint8_t srcAddrMode;
    /** \brief This parameter holds the source short address. */
    uint16_t srcShortAddress;
    /** \brief This parameter holds the source extended address. */
    uint64_t srcExtAddress;
    /** \brief This parameter holds the source profile identifier. */
    uint16_t srcProfileId;
    /** \brief This parameter holds the source endpoint identifier. */
    uint8_t srcEndpointId;
    /** \brief This parameter holds the source cluster identifier. */
    uint16_t srcClusterId; // is needed to remove ????
    /** \brief This parameter holds the cluster identifier. */
    uint16_t clusterId;
    /** \brief This parameter holds the direction value.
     * Values are enumerated in ZS_FrameControlDirection_t.
     */
    uint8_t direction;
} ZS_ZclCommandInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Identify command parameters. */
    ZCL_Identify_t identify;
} ZS_ZclIdentifyInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyQueryInd function.
*******************************************************************************/
typedef ZS_ZclCommandInd_t ZS_ZclIdentifyQueryInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclIdentifyQueryResponseInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Identify Query Response command parmeters. */
    ZCL_IdentifyQueryResponse_t identifyQueryResponse;
} ZS_ZclIdentifyQueryResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetCurrentPriceInd command.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Get Current Price command parmeters. */
    ZCL_GetCurrentPrice_t getCurrentPrice;
} ZS_ZclGetCurrentPriceInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclPublishPriceInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Publish Price command parameters. */
    ZS_ZclPublishPrice_t publishPrice;
} ZS_ZclPublishPriceInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclReportEventStatusInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Report Event Status command parameters. */
    ZCL_ReportEventStatus_t reportEventStatus;
} ZS_ZclReportEventStatusInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetScheduledEventsInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Get Scheduled Events command parameters. */
    ZCL_GetScheduledEvents_t getScheduledEvents;
} ZS_ZclGetScheduledEventsInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclLoadControlEventInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Load Control Event command parameters. */
    ZCL_LoadControlEvent_t loadControlEvent;
} ZS_ZclLoadControlEventInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelAllLoadControlEventsInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Cancel All Load Control Events
     * command parameters. */
    ZCL_CancelAllLoadControlEvents_t cancelAllLoadControlEvents;
} ZS_ZclCancelAllLoadControlEventsInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelLoadControlEventInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Cancel Load Control Event command parameters. */
    ZCL_CancelLoadControlEvent_t cancelLoadControlEvent;
} ZS_ZclCancelLoadControlEventInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetLastMessageInd function.
*******************************************************************************/
typedef ZS_ZclCommandInd_t ZS_ZclGetLastMessageInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclMessageConfirmationInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Message Confirmation command parameters. */
    MessageConfirmation_t messageConfirmation;
} ZS_ZclMessageConfirmationInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclDisplayMessageInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Display Message command parameters. */
    ZS_ZclDisplayMessage_t displayMessage;
} ZS_ZclDisplayMessageInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclCancelMessageInd function.
*******************************************************************************/
typedef struct PACK
{
    /** \brief This parameter holds the command parameters. */
    ZS_ZclCommandInd_t command;
    /** \brief This parameter holds the Cancel Message command parameters. */
    CancelMessage_t cancelMessage;
} ZS_ZclCancelMessageInd_t;
/***************************************************************************//**
\brief Add Group Command Payload format.
*******************************************************************************/
typedef struct PACK
{
  uint16_t groupId;
  uint8_t groupNameLen;
  char* name;
} ZS_ZclAddGroup_t;
/***************************************************************************//**
\brief Extension fields
*******************************************************************************/
typedef struct PACK
{
  ZCL_OnOffClusterExtensionFieldSet_t onOff;
  ZCL_LevelControlSceneExtensionFields_t levelControl;
} extFields_t;
/***************************************************************************//**
\brief Add Scene Command Payload format.
*******************************************************************************/
typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
  uint16_t transitionTime;
  uint8_t sceneNameLen;
  char* name;
  extFields_t extField;
} ZS_ZclAddScene_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclAddSceneReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Add Scene command parameters. */
  ZS_ZclAddScene_t addScene;
} ZS_ZclAddSceneReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclAddSceneInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Add Scene Response command parameters. */
  ZCL_AddSceneResponse_t addScene;
} ZS_ZclAddSceneResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclViewGroupReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the View Group command parameters. */
  ZCL_ViewGroup_t viewGroup;
} ZS_ZclViewGroupReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclViewGroupInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the View Group Response command parameters. */
  ZCL_ViewGroupResponse_t viewGroup;
} ZS_ZclViewGroupResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclViewSceneReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the View Scene command parameters. */
  ZCL_ViewScene_t viewScene;
} ZS_ZclViewSceneReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclViewSceneInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the View Scene Response command parameters. */
  ZCL_ViewSceneResponse_t viewScene;
} ZS_ZclViewSceneResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclAddGroupReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Add Group command parameters. */
  ZS_ZclAddGroup_t addGroup;
} ZS_ZclAddGroupReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclAddGroupInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Add Group Response command. */
  ZCL_AddGroupResponse_t addGroupResponse;
} ZS_ZclAddGroupResponseInd_t;
/***************************************************************************//**
\brief Get Group Membership Command Payload format.
*******************************************************************************/
typedef struct PACK
{
  uint8_t groupCount;
} ZS_ZclGetGroupMembership_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetGroupMembershipReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Get Group Membership command. */
  ZS_ZclGetGroupMembership_t groupMembership;
} ZS_ZclGetGroupMembershipReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetGroupMembershipInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Get Group Membership Response command. */
  ZCL_GetGroupMembershipResponse_t groupMembership;
} ZS_ZclGetGroupMembershipResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetSceneMembershipReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Get Scene Membership command. */
  ZCL_GetSceneMembership_t sceneMembership;
} ZS_ZclGetSceneMembershipReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclGetSceneMembershipInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Get Scene Membership Response command. */
  ZCL_GetSceneMembershipResponse_t sceneMembership;
} ZS_ZclGetSceneMembershipResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for requests with empty payload.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the flag if command affects the OnOff cluster. */
  uint8_t affectOnOff;
} ZS_ZclEmptyPayloadReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclStoreSceneReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Store Scene command. */
  ZCL_StoreScene_t storeScene;
} ZS_ZclStoreSceneReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclStoreSceneInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Store Scene Response command. */
  ZCL_StoreSceneResponse_t storeScene;
} ZS_ZclStoreSceneResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclMoveToLevelReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Move To Level command. */
  ZCL_MoveToLevel_t moveToLevel;
  /** \brief This parameter holds the flag if command affects the OnOff cluster. */
  uint8_t affectOnOff;
} ZS_ZclMoveToLevelReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclMoveReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Move command. */
  ZCL_Move_t move;
  /** \brief This parameter holds the flag if command affects the OnOff cluster. */
  uint8_t affectOnOff;
} ZS_ZclMoveReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclStepReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Step command. */
  ZCL_Step_t step;
  /** \brief This parameter holds the flag if command affects the OnOff cluster. */
  uint8_t affectOnOff;
} ZS_ZclStepReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclRecallSceneReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Recall Scene command. */
  ZCL_RecallScene_t recallScene;
} ZS_ZclRecallSceneReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclRemoveAllScenesReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Remove All Scenes command. */
  ZCL_RemoveAllScenes_t removeScenes;
} ZS_ZclRemoveAllScenesReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclRemoveAllScenesInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Remove All Scenes Response command. */
  ZCL_RemoveAllScenesResponse_t removeScenes;
} ZS_ZclRemoveAllScenesResponseInd_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclRemoveGroupReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandReq_t command;
  /** \brief This parameter holds the Remove Group command. */
  ZCL_RemoveGroup_t removeGroup;
} ZS_ZclRemoveGroupReq_t;
/***************************************************************************//**
\brief Parameters structure for ZS_ZclRemoveGroupInd function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the command parameters. */
  ZS_ZclCommandInd_t command;
  /** \brief This parameter holds the Remove Groups REsponse command. */
  ZCL_RemoveGroupResponse_t removeGroup;
} ZS_ZclRemoveGroupResponseInd_t;
#endif // ZCL_SUPPORT == 1

/***************************************************************************//**
\brief  ZDO PRIMITIVES
*******************************************************************************/
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoSetTxPowerReq function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_SetTxPowerReq_t detailed description in file zdo.h*/
  uint8_t txPower;
} ZS_ZdoSetTxPowerReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoSetTxPowerConf function
*******************************************************************************/
typedef ZDO_SetTxPowerConf_t ZS_ZdoSetTxPowerConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoSleepReq function
*******************************************************************************/
typedef struct PACK
{
  /*!Sleep period in seconds*/
  uint32_t sleepPeriod;
} ZS_ZdoSleepReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoSleepConf function
*******************************************************************************/
typedef struct PACK
{
  /*!Sleep period confirm*/
  uint32_t sleepPeriod;
  /*! Stack is ready to sleep if status is ZDO_SUCCESS_STATUS,
    stack is not ready to sleep if status is ZDO_BUSY_STATUS */
  uint8_t status;
} ZS_ZdoSleepConf_t;
/***************************************************************************//**
\brief ZDO Device discovery.
*******************************************************************************/
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoNwkAddrReq function
*******************************************************************************/
typedef struct PACK
{
  /*Address of destination remote device*/
  ShortAddr_t dstAddr;
  /*!See ZDO_MgmtNwkUpdateReq_t description in zdo.h*/
  ZDO_NwkAddrReq_t req;
}ZS_ZdoNwkAddrReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoNwkAddrConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_NwkAddrResp_t description in zdo.h*/
  ZDO_NwkAddrResp_t resp;
} ZS_ZdoNwkAddrConf_t;

#if defined _BINDING_
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtBindReq function
*******************************************************************************/
typedef struct PACK
{
  uint8_t targetAddrMode;
  uint64_t targetExtAddr;
  uint16_t targetNwkAddr;
  ZDO_MgmtBindReq_t payload;
} ZS_ZdpMgmtBindReq_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtBindResp function
*******************************************************************************/
typedef struct PACK
{
  uint8_t srcAddrMode;
  uint64_t srcExtAddr;
  uint16_t srcNwkAddr;
  ZDO_ZdpRespFrame_t payload;
} ZS_ZdpMgmtBindResp_t;
#endif /* _BINDING_ */

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtLeaveReq function
*******************************************************************************/
typedef struct PACK _ZS_ZdoMgmtLeaveReq_t
{
  ExtAddr_t dstAddr;
  ExtAddr_t deviceAddr; //!< IEEE address
  LITTLE_ENDIAN_OCTET(3, (
    uint8_t   reserved : 6, //!< Reserved; can not be changed by user.
    /*! This field shall have a value of 1 if the
    device being asked to leave the
    network is also asked to
    remove all its child devices, if any.
    Otherwise, it has a value of 0.*/
    uint8_t   removeChildren : 1,
    /*! This field shall have a value of 1 if the
    device being asked to leave from the
    current parent is requested to rejoin
    the network. Otherwise, it has a
    value of 0.*/
    uint8_t   rejoin : 1
  ))
} ZS_ZdoMgmtLeaveReq_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtLeaveConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
} ZS_ZdoMgmtLeaveConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtPermitJoiningReq function
*******************************************************************************/
typedef struct PACK
{
  /*Address of destination remote device*/
  uint16_t dstShortAddress;
  /*!See ZDO_MgmtPermitJoiningReq_t description in zdo.h*/
  uint8_t permitDuration;
  /*!See ZDO_MgmtPermitJoiningReq_t description in zdo.h*/
  uint8_t tcSignificance;
} ZS_ZdoMgmtPermitJoiningReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoMgmtPermitJoiningConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
} ZS_ZdoMgmtPermitJoiningConf_t;
//#if APP_ZDP_REQUESTS != false
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoIeeeAddrReq function
*******************************************************************************/
typedef struct PACK
{
  /*Address of destination remote device*/
  ShortAddr_t dstAddr;
  /*!See ZDO_MgmtNwkUpdateReq_t description in zdo.h*/
  ZDO_IeeeAddrReq_t req;
}ZS_ZdoIeeeAddrReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoIeeeAddrConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_IeeeAddrResp_t description in zdo.h*/
  ZDO_IeeeAddrResp_t resp;
} ZS_ZdoIeeeAddrConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoNodeDescReq function
*******************************************************************************/
typedef ZDO_NodeDescReq_t ZS_ZdoNodeDescReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoNodeDescConf function
********************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_NodeDescResp_t description in zdo.h*/
  ZDO_NodeDescResp_t resp;
} ZS_ZdoNodeDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpPowerDescReq function
*******************************************************************************/
typedef ZDO_PowerDescReq_t ZS_ZdpPowerDescReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpPowerDescConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_PowerDescResp_t description in zdo.h*/
  ZDO_PowerDescResp_t resp;
} ZS_ZdpPowerDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpSimpleDescReq function
*******************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest;  //!< NWK address for the simple descriptor request
  ShortAddr_t dstAddr;  //! dest Addr for forwarding the simple descriptor request
  Endpoint_t  endpoint; //!< The endpoint on the destination 
}ZS_ZdpSimpleDescReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpSimpleDescConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!NWK address of remote device */
  ShortAddr_t  nwkAddrOfInterest; //!< NWK address of the simple descriptor request
  /*!endpoint of remote device */
  Endpoint_t   endpoint;
  /*! The application profile identifier field of the simple descriptor is sixteen bits in
  length and specifies the profile that is supported on this endpoint. Profile
  identifiers shall be obtained from the ZigBee Alliance.*/
  ProfileId_t  AppProfileId;
  /*! The application device identifier field of the simple descriptor is sixteen bits in
  length and specifies the device description supported on this endpoint. Device
  description identifiers shall be obtained from the ZigBee Alliance.*/
  uint16_t     AppDeviceId;
  /*! The application device version field of the simple descriptor is four bits in length
  and specifies the version of the device description supported on this endpoint.*/
  uint8_t      AppDeviceVersion : 4;
  uint8_t      Reserved         : 4;
  /*! The application input cluster count field of the simple descriptor is eight bits in
  length and specifies the number of input clusters, supported on this endpoint, that
  will appear in the application input cluster list field. If the value of this field is
  zero, the application input cluster list field shall not be included.*/
  uint8_t      AppInClustersCount;
  /*! The application input cluster list of the simple descriptor is 16*i bits in length,
  where i is the value of the application input cluster count field. This field specifies
  the list of input clusters supported on this endpoint, for use during the service
  discovery and binding procedures.
  The application input cluster list field shall be included only if the value of the
  application input cluster count field is greater than zero.*/
  ClusterId_t*  AppInClustersList;
  /*! The application output cluster count field of the simple descriptor is eight bits in
  length and specifies the number of output clusters, supported on this endpoint, that
  will appear in the application output cluster list field. If the value of this field is
  zero, the application output cluster list field shall not be included.*/
  uint8_t      AppOutClustersCount;
  /*! The application output cluster list of the simple descriptor is 16*o bits in length,
  where o is the value of the application output cluster count field. This field
  specifies the list of output clusters supported on this endpoint, for use during the
  service discovery and binding procedures.
  The application output cluster list field shall be included only if the value of the
  application output cluster count field is greater than zero.*/
  ClusterId_t*  AppOutClustersList;
} ZS_ZdpSimpleDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpActiveEPReq function
*******************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest; //!< NWK address for the active endpoints request
  ShortAddr_t dstAddr;
} ZS_ZdpActiveEPReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpActiveEPConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_ActiveEPResp_t description in zdo.h*/
  ZDO_ActiveEPResp_t resp;
} ZS_ZdpActiveEPConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpComplexDescReq function
*******************************************************************************/
typedef ZDO_ComplexDescReq_t ZS_ZdpComplexDescReq_t;
#ifdef _PARENT_ANNCE_  
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpParentAnnceReq function
*******************************************************************************/
typedef struct PACK
{
  ShortAddr_t nwkAddrOfInterest;
  /*!See ZDO_ParentAnnceReq description in zdo.h*/
  ZDO_ParentAnnceReq_t req;
} ZS_ZdpParentAnnceReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpParentAnnceResp function
*******************************************************************************/
typedef struct PACK
{
  uint8_t status;
  /*!See ZDO_ParentAnnceResp description in zdo.h*/
  ZDO_ParentAnnceReq_t req;
} ZS_ZdpParentAnnceResp_t;
#endif
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpComplexDescConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_ComplexDescResp description in zdo.h*/
  ZDO_ComplexDescResp_t resp;
} ZS_ZdpComplexDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUserDescReq function
*******************************************************************************/
typedef ZDO_UserDescReq_t ZS_ZdpUserDescReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUserDescConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_UserDescResp_t description in zdo.h*/
  ZDO_UserDescResp_t resp;
} ZS_ZdpUserDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpEnDeviceAnnceReq function
*******************************************************************************/
typedef ZDO_DeviceAnnceReq_t ZS_ZdpEnDeviceAnnceReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpEndDeviceConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZS_ZdpEnDeviceAnnceReq_t description*/
  ZS_ZdpEnDeviceAnnceReq_t resp;
} ZS_ZdpEndDeviceConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpLqiReq function
*******************************************************************************/
typedef struct {
  /*!Address of requsted remote device*/
  ShortAddr_t nwkAddrOfInterest;
  /*!See ZDO_MgmtLqiReq_t description*/
  ZDO_MgmtLqiReq_t req;
}
ZS_ZdpLqiReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpLqiConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t            status;
  /*!See ZDO_MgmtLqiResp_t description*/
  ZDO_MgmtLqiResp_t  resp;
} ZS_ZdpLqiConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpRtgReq function
*******************************************************************************/
typedef struct {
  /*!Address of requsted remote device*/
  ShortAddr_t nwkAddrOfInterest;
  /*!See ZDO_MgmtLqiReq_t description*/
  ZDO_MgmtRtgReq_t req;
}ZS_ZdpRtgReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpRtgConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t            status;
  /*!See ZDO_MgmtRtgResp_t description*/
  ZDO_MgmtRtgResp_t  resp;
} ZS_ZdpRtgConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUserDescSetReq function
*******************************************************************************/
typedef ZDO_UserDescSetReq_t ZS_ZdpUserDescSetReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUserDescSetConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t   status;
  /*Address of remote device which send confirmation*/
  uint16_t  nwkAddrOfInterest;
} ZS_ZdpUserDescSetConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpNwkUpdateReq function
*******************************************************************************/
typedef struct PACK
{
  /*Address of destination remote device*/
  ShortAddr_t nwkAddr;
  /*!See ZDO_MgmtNwkUpdateReq_t description in zdo.h*/
  ZDO_MgmtNwkUpdateReq_t req;
}
ZS_ZdpNwkUpdateReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpSystemServerDiscoveryReq function
*******************************************************************************/
typedef ZDO_SystemServerDiscoveryReq_t ZS_ZdpSystemServerDiscoveryReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpSystemServerDiscoveryConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!
    Bit    Assigment
    0     Primary Trust Center
    1     Backup Trust Center
    2     Primary Binding Table Cache
    3     Backup Binding Table Cache
    4     Primary Discovery Cache
    5     Backup Discovery Cache
    6     Network Manager
    7 - 15 Reserved
    ZigBee Specification r17, 2.3.2.3.10 Server Mask Field
   */
  uint16_t serverMask;
} ZS_ZdpSystemServerDiscoveryConf_t;

#ifdef _BINDING_
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpMatchDescReq function
*******************************************************************************/
typedef struct PACK
{
  /*!Address of target device*/
  ShortAddr_t nwkAddrOfInterest;
  /*!Address of destination remote device or broadcast*/
  ShortAddr_t dstAddr;
  /*!Requested profile */
  ProfileId_t profileId;
  /*!Server cluster list amount*/
  uint8_t     numInClusters;
  /*!Pointer to list of desired server clusters*/
  ClusterId_t inClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
  /*!Client cluster list amount*/
  uint8_t     numOutClusters;
  /*!Pointer to list of desired client clusters*/
  ClusterId_t outClusterList[MAX_REQUESTED_CLUSTER_NUMBER];
}ZS_ZdpMatchDescReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpMatchDescConf function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZDO_Status_t description*/
  uint8_t status;
  /*!See ZDO_MatchDescResp_t description in zdo.h*/
  ZDO_MatchDescResp_t resp;
} ZS_ZdpMatchDescConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpBindReq function
*******************************************************************************/
typedef struct PACK
{
  uint16_t reqCluster;
  uint8_t targetAddrMode;
  uint16_t targetNwkAddr;
  uint64_t targetExtAddr;
  ZDO_BindReq_t payload;
} ZS_ZdpBindReq_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpBindConf function
*******************************************************************************/

typedef ZDO_BindResp_t ZS_ZdpBindConf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUnbindReq function
*******************************************************************************/
typedef ZS_ZdpBindReq_t ZS_ZdpUnbindReq_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdpUnbindConf function
*******************************************************************************/
typedef ZDO_UnbindResp_t ZS_ZdpUnbindConf_t;
#endif //_BINDING_

//#endif //APP_ZDP_REQUESTS
/***************************************************************************//**
\brief Describes the parameters of the ZS_MgmtNwkUpdateNotf function
*******************************************************************************/
typedef ZDO_MgmtNwkUpdateNotf_t ZS_MgmtNwkUpdateNotf_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoGetNeibAmountConf function
*******************************************************************************/
typedef struct PACK
{
  /*!Router device records amount */
  uint8_t routersAmount;
  /*!End device records amount */
  uint8_t enddevicesAmount;
} ZS_ZdoGetNeibAmountConf_t;
/***************************************************************************//**
\brief Describes the one record from neighbors table
*******************************************************************************/
typedef struct PACK
{
  /*!Device short address*/
  uint16_t shortAddr;
  /*!Device IEEE address*/
  uint64_t extAddr;
  /*!Device type - coordinator, router or end device*/
  DeviceType_t deviceType;
  /*!Line Quality Indicator*/
  uint8_t lqi;
  /*!Received Signal Strength Indicator*/
  uint8_t rssi;
} ZS_ZdoGetNeibTableRecord_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZdoGetNeibTableConf function
*******************************************************************************/
typedef struct
{
  /*!Ammount of  records in neighbours table*/
  uint8_t recordsAmount;
  /*!Pointer to the neighbours table*/
  ZS_ZdoGetNeibTableRecord_t* records;
} ZS_ZdoGetNeibTableConf_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclStartRequest function
*******************************************************************************/
#ifdef _ZCL_SUPPORT_ 
typedef struct PACK
{
  /*!The endpoint field of the simple descriptor is eight bits in length and specifies the
  endpoint within the node to which this description refers. Applications shall only
  use endpoints 1-240.
  ZigBee Specification r17 2.3.2.5.1 Endpoint Field*/
  uint8_t endpoint;
  /*!The application device identifier field of the simple descriptor is sixteen bits in
  length and specifies the device description supported on this endpoint. Device
  description identifiers shall be obtained from the ZigBee Alliance.
  ZigBee Specification r17 2.3.2.5.3 Application Device Identifier Field
  */
  uint16_t appDeviceId;
  /*! The application profile identifier field of the simple descriptor is sixteen bits in
  length and specifies the profile that is supported on this endpoint. Profile
  identifiers shall be obtained from the ZigBee Alliance.*/
  ProfileId_t  appProfileId;
  /*!
   The application input cluster count field of the simple descriptor is eight bits in
   length and specifies the number of input clusters, supported on this endpoint, that
   will appear in the application input cluster list field. If the value of this field is
   zero, the application input cluster list field shall not be included.
   ZigBee Specification r17 2.3.2.5.5 Application Input Cluster Count Field
  */
  uint8_t inClustersCount;
  /*!The application output cluster count field of the simple descriptor is eight bits in
  length and specifies the number of output clusters, supported on this endpoint, that
  will appear in the application output cluster list field. If the value of this field is
  zero, the application output cluster list field shall not be included.
  ZigBee Specification r17 2.3.2.5.7 Application Output Cluster Count Field
  */
  uint8_t outClustersCount;
  /*!The application input cluster list of the simple descriptor is 16*i bits in length,
  where i is the value of the application input cluster count field. This field specifies
  the list of input clusters supported on this endpoint, for use during the service
  discovery and binding procedures.
  The application input cluster list field shall be included only if the value of the
  application input cluster count field is greater than zero.
  ZigBee Specification r17 2.3.2.5.6 Application Input Cluster List
  */
  ClusterId_t* inClustersList;
  /*! The application output cluster list of the simple descriptor is 16*o bits in length,
  where o is the value of the application output cluster count field. This field
  specifies the list of output clusters supported on this endpoint, for use during the
  service discovery and binding procedures.
  The application output cluster list field shall be included only if the value of the
  application output cluster count field is greater than zero.
  ZigBee Specification r17 2.3.2.5.8 Application Output Cluster List
  */
  ClusterId_t* outClustersList;
} ZS_ZclStartRequest_t;

/***************************************************************************//**
\brief Describes the parameters of the ZclStartConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!
   Returns one of following statuses: \n
  ZCL_STATUS_SUCCESS when Smart Energy profile starts successfully \n
  ZCL_STATUS_FAIL when error occurred \n
  */
  uint8_t status;
} RZclStartConfirm_t;

/***************************************************************************//**
\brief Describes the parameters of the ZclStartSecurityConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!
   Returns one of following statuses: \n
  ZCL_SECURITY_STATUS_SUCCESS when Smart Energy profile starts successfully \n
  ZCL_SECURITY_STATUS_DISCOVERY_FAIL when not found devices with server Key Establishment cluster \n
  ZCL_SECURITY_STATUS_APS_BINDING_FAIL in case APS binding table problems (e.g. table overflow) \n
  ZCL_SECURITY_STATUS_TIMEOUT in case remote device performance problems \n
  ZCL_SECURITY_STATUS_TERMINATED when incorrect security material was set on local or remote device \n
  ZCL_INVALID_STATUS_SETTINGS in case incorrect start options\n
  */
  uint8_t status;
} RZclStartSecurityConfirm_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclReportIndication function
*******************************************************************************/
typedef struct PACK
{
  /*!Address mode*/
  uint8_t srcAddrMode;
  /*!If address mode is APS_SHORT_ADDRESS NWK address of sender is filled*/
  ShortAddr_t srcShortAddress;
  /*!If address mode is APS_EXT_ADDRESS IEEE address of sender is filled*/
  ExtAddr_t srcExtAddress;
  /*!Sender profile ID*/
  ProfileId_t srcProfileId;
  /*!Sender endpoint ID*/
  Endpoint_t srcEndpointId;
  /*!Sender cluster ID*/
  ClusterId_t srcClusterId;
  /*!Target cluster ID*/
  ClusterId_t clusterId;
  /*!Reported attributes amount*/
  uint8_t attributesCount;
  /*!Reported length in bytes*/
  uint8_t reportLength;
  /*!Pointer to report. Use ZCL_GetNextElement() function to decode report.*/
  uint8_t* report;
} ZS_ZclReportInd_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclAttributeEventInd function
*******************************************************************************/
typedef struct PACK
{
  /*!Address mode*/
  uint8_t srcAddrMode;
  /*!If address mode is APS_SHORT_ADDRESS NWK address of sender is filled*/
  ShortAddr_t srcShortAddress;
  /*!If address mode is APS_EXT_ADDRESS IEEE address of sender is filled*/
  ExtAddr_t srcExtAddress;
  /*!Sender profile ID*/
  ProfileId_t profileId;
  /*!Sender endpoint ID*/
  Endpoint_t srcEndpointId;
  /*!Cluster ID*/
  ClusterId_t clusterId;
  /*! Keeps an Event value*/
  uint8_t event;
  /*! Attribute idetifier*/
  uint16_t attributeId;
} ZS_ZclAttributeEventInd_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclGetRequest function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_SecurityAttrId description in file zclSecurityManager.h*/
  uint8_t    id;
  /*!The extended address associated with link key.*/
  ExtAddr_t addr;
} ZS_ZclGetRequest_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclGetConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_Status_t description in file zclSecurityManager.h*/
  uint8_t status;
  /*!See ZCL_SecurityAttrId description in file zclSecurityManager.h*/
  uint8_t id;
  /*!length in bytes for allocated read buffer*/
  uint8_t length;
  /*!allocated read buffer pointer*/
  uint8_t* value;
} ZS_ZclGetConfirm_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclSetRequest function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_SecurityAttrId description in file zclSecurityManager.h*/
  uint8_t id;
  /*!length in bytes for allocated buffer to write*/
  uint8_t               length;
  /*!pointer to allocated buffer to write*/
  uint8_t*              value;
} ZS_ZclSetRequest_t;
/***************************************************************************//**
\brief Describes the parameters of the RZclSetConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_Status_t description in file zclSecurityManager.h*/
  uint8_t status;
  uint8_t id;
} RZclSetConfirm_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclReadAttributeValue function
*******************************************************************************/
typedef struct PACK
{
  /*!target endpoint*/
  Endpoint_t endpoint;
  /*!target cluster*/
  ClusterId_t clusterId;
  /*!direction of request*/
  uint8_t direction;
  /*!command ID*/
  uint8_t commandId;
  /*!attribute to read*/
  uint16_t attributeId;
} ZS_ZclReadAttributeValue_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclReadAttributeValueConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_Status_t description in file zclSecurityManager.h*/
  uint8_t status;
  /*!attribute number to read*/
  uint16_t attributeId;
  /*Type of requested attribute. See ZCL_AttributeType_t description in zcl.h*/
  uint8_t type;
  /*Pointer to buffer with retrieved value.*/
  uint8_t* value;
} ZS_ZclReadAttributeValueConfirm_t;
/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclWriteAttributeValue function
*******************************************************************************/
typedef struct PACK
{
  /*!target endpoint*/
  Endpoint_t endpoint;
  /*!target cluster*/
  ClusterId_t clusterId;
  /*!direction of request*/
  uint8_t direction;
  /*!command ID*/
  uint8_t commandId;
  /*!attribute number to write*/
  uint16_t attributeId;
  /*Type of requested attribute. See ZCL_AttributeType_t description in zcl.h*/
  uint8_t type;
  /*Pointer to buffer with value to write*/
  uint8_t* value;
} ZS_ZclWriteAttributeValue_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclWriteAttributeValueConfirm function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_Status_t description in file zclSecurityManager.h*/
  uint8_t status;
} ZS_ZclWriteAttributeValueConfirm_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclCommandConfirm() function
*******************************************************************************/
typedef struct PACK
{
  /*!See ZCL_Status_t description in file zclSecurityManager.h*/
  uint8_t status;
} RZclCommandConfirm_t;

/***************************************************************************//**
\brief Describes the parameters of the ZS_ZclDefaultResponseInd() function
*******************************************************************************/
typedef struct PACK _RZclDefaultResponseInd_t
{
  /*! Specifies the identifier of the received command which was responsed */
  uint8_t commandId;
  /*! Received command processing status */
  uint8_t status;
} RZclDefaultResponseInd_t;

/***************************************************************************//**
\brief Describes the parameters of getting ZCL sequence number transaction
*******************************************************************************/
typedef struct PACK
{
  /*! The sequence number of the next ZCL request */
  uint8_t sequenceNumber;
} RZclNextSequenceNumberResp_t;
#endif // ZCL_SUPPORT == 1

#ifdef _INTERPAN_
/***************************************************************************//**
\brief Describes the INTRP-DATA.request primitive
ZigBee Smart Energy profile specification r15
B.3.1 The INTRP-DATA.request Primitive, page 83.
*******************************************************************************/
typedef struct PACK
{
  //Primitive fields
  /*!
   * Valid srcAddrMode is always 0x03. So this field is not necessary in this
   * structure.*/
  /*!
  The addressing mode for the destination address used in this primitive. This
  parameter can take one of the values from the following list:
  0x01 = 16-bit group address
  0x02 = 16-bit NWK address, normally  the broadcast address 0xffff
  0x03 = 64-bit extended address
  */
  uint8_t dstAddrMode;
  /*!
  The 16-bit PAN identifier of the entity or entities to which the ASDU is
  being  transferred or the broadcast PANId 0xffff.
  */
  PanId_t dstPANID;
  /*!The address of the entity or entities to which the ASDU is being
  transferred.
  */
  MAC_Addr_t dstAddress;
  /*!The identifier of the profile for which this frame is intended.*/
  ProfileId_t profileId;
  /*!
  The identifier of the cluster, within the profile specified by the ProfileId
  parameter, which defines the application semantics of the ASDU.
  */
  ClusterId_t clusterId;
  /*! An integer handle associated with the ASDU to be transmitted.*/
  uint8_t asduHandle;
  /** Transmission options for this request **/
  uint8_t txOptions;
  /*!The number of octets in the ASDU to be transmitted.
  */
  uint8_t asduLength;
  /*!The set of octets comprising the ASDU to be transferred.*/
  uint8_t asdu[0];
} ZS_IntrpDataReq_t;

/**//**
 * \brief INTRP-DATA confirm primitive's parameters structure declaration.
 * ZigBee Smart Energy profile specification r15
 * B.3.2 The The INTRP-DATA.confirm Primitive, page 85.
 */
typedef struct PACK
{
  /** An integer handle associated with the transmitted frame */
  uint8_t  asduHandle;
  /** The status of the ASDU transmission corresponding to ASDUHandle as
   * returned by the MAC.*/
  uint8_t  status;
} ZS_IntrpDataConf_t;

/**//**
 * \brief INTRP-DATA indication primitive's parameters structure declaration.
 * ZigBee Smart Energy profile specification r15
 * B.3.3 The INTRP-DATA.indication Primitive, page 86
 */
typedef struct PACK
{
  //Primitive fields
  /*!
   * Valid srcAddrMode is always 0x03. So this field is not necessary in this
   * structure.*/
  /*!
  The 16-bit PAN identifier of the entity from which the ASDU is being
  transferred
  */
  PanId_t srcPANID;
  /*! The device address of the entity from which the ASDU is being transferred
  */
  MAC_Addr_t srcAddress;
  /*!
  The addressing mode for the destination address used in this primitive. This
  parameter can take one of the values from the following list:
  0x01 = 16-bit group address
  0x02 = 16-bit NWK address, normally  the broadcast address 0xffff
  0x03 = 64-bit extended address
  */
  uint8_t dstAddrMode;
  /*!
  The 16-bit PAN identifier of the entity or entities to which the ASDU is
  being  transferred or the broadcast PANId 0xffff.
  */
  PanId_t dstPANID;
  /*!The address of the entity or entities to which the ASDU is being
  transferred.
  */
  MAC_Addr_t dstAddress;
  /*!The identifier of the profile for which this frame is intended.*/
  ProfileId_t profileId;
  /*!
  The identifier of the cluster, within the profile specified by the ProfileId
  parameter, which defines the application semantics of the ASDU.
  */
  ClusterId_t clusterId;
  /*!The link quality observed during the reception of the ASDU*/
  Lqi_t lqi;
  /*!The number of octets in the ASDU to be transmitted.
  */
  uint8_t asduLength;
} ZS_IntrpDataInd_t;


#endif //_INTERPAN_

#if defined(_SECURITY_) && defined _LINK_SECURITY_
/***************************************************************************//**
\brief Parameters structure for ZS_AuxGetLinkKeyHashReq function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds the extended device address. */
  uint64_t extAddr;
} ZS_AuxGetLinkKeyHashReq_t;

/***************************************************************************//**
\brief Parameters structure for ZS_AuxGetLinkKeyHashConf function.
*******************************************************************************/
typedef struct PACK
{
  /** \brief This parameter holds hashed link key for device. */
  uint8_t linkKeyHash[SECURITY_KEY_SIZE];
} ZS_AuxGetLinkKeyHashConf_t;

typedef struct PACK
{
  uint32_t timeout;
} ZS_VerifyKeyReq_t;

typedef struct PACK
{
 uint8_t status;
}ZS_ZdoVerifyKeyConf_t;
#endif // defined(_SECURITY_) && defined _LINK_SECURITY_

/***************************************************************************//**
\brief Parameters structure for HAL_AppStartTimer request.
*******************************************************************************/
typedef struct PACK
{
  uint32_t interval;
  TimerMode_t mode;
} ZS_HalAppTimer_t;

#if (BDB_SUPPORT == 1)
typedef struct PACK
{
  BDB_CommissioningMode_t  mode;
  uint16_t groupId;  
}ZS_BdbInvokeCommissioningReq_t;
#endif /* (BDB_SUPPORT == 1) */
END_PACK


#endif //_ZAPPSICOMMANDS_H
