/*******************************************************************************
  Bitcloud Preinclude Configuration Header File

  Company:
    Microchip Technology Inc.

  File Name:
    bitcloudPreInclude.h

  Summary:
    This file contains the Bitcloud Preinclude configurations.

  Description:
    This file contains the Bitcloud Preinclude configurations.
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

#ifndef BIT_CLOUD_CONFIG_H
#define BIT_CLOUD_CONFIG_H

#define BDB_SUPPORT 1

//Sys Task Defines
#ifndef _SYS_MAC_PHY_HWD_TASK_
#define   _SYS_MAC_PHY_HWD_TASK_
#endif

#ifndef _SYS_HAL_TASK_
#define   _SYS_HAL_TASK_
#endif

#ifndef _SYS_MAC_HWI_TASK_
#define   _SYS_MAC_HWI_TASK_
#endif

#ifndef _SYS_NWK_TASK_
#define   _SYS_NWK_TASK_
#endif

#ifndef _SYS_APS_TASK_
#define   _SYS_APS_TASK_
#endif

#ifndef _SYS_ZCL_TASK_
#define   _SYS_ZCL_TASK_
#endif

#ifndef _SYS_SSP_TASK_
#define   _SYS_SSP_TASK_
#endif

#ifndef _SYS_TC_TASK_
#define   _SYS_TC_TASK_
#endif

#ifndef _SYS_ZDO_TASK_
#define   _SYS_ZDO_TASK_
#endif

#ifndef _SYS_ZLL_TASK_
#define   _SYS_ZLL_TASK_
#endif

#ifndef _COORDINATOR_
#define _COORDINATOR_
#endif

#ifndef _ROUTER_
#define _ROUTER_
#endif

#ifndef _ENDDEVICE_
#define _ENDDEVICE_
#endif

#ifndef _HAL_HW_AES_
#define _HAL_HW_AES_
#endif

#ifndef _SYS_ASSERT_ON_
#define _SYS_ASSERT_ON_
#endif

#ifndef _FFD_
#define   _FFD_
#endif

#ifndef _SECURITY_
#define   _SECURITY_
#endif

#ifndef _LINK_SECURITY_
#define   _LINK_SECURITY_
#endif

#ifndef _DISTRIBUTED_SECURITY_
#define   _DISTRIBUTED_SECURITY_
#endif

#ifndef _IEEE_ZIGBEE_COMPLIANCE_
#define   _IEEE_ZIGBEE_COMPLIANCE_
#endif

#ifndef _TRUST_CENTRE_
#define   _TRUST_CENTRE_
#endif

#ifndef _DISTRIBUTED_TRUST_CENTER_
#define   _DISTRIBUTED_TRUST_CENTER_
#endif

#ifndef _RESOLVE_ADDR_CONFLICT_
#define   _RESOLVE_ADDR_CONFLICT_
#endif

#ifndef _COMMISSIONING_
#define   _COMMISSIONING_
#endif

#ifndef _ZIGBEE_REV_21_SUPPORT_
#define   _ZIGBEE_REV_21_SUPPORT_
#endif

#ifndef _PARENT_ANNCE_
#define   _PARENT_ANNCE_
#endif

#ifndef _GROUP_TABLE_
#define   _GROUP_TABLE_
#endif

#ifndef _INTERPAN_
#define   _INTERPAN_
#endif

// Network layer defines
#ifndef _CHILD_MANAGEMENT_
#define   _CHILD_MANAGEMENT_
#endif

#ifndef _NWK_IN_FRAME_COUNTERS_
#define   _NWK_IN_FRAME_COUNTERS_
#endif

#ifndef _NWK_ALLOCATOR_
#define   _NWK_ALLOCATOR_
#endif

#ifndef _NWK_NONSTANDARD_BEACON_FILTER_
#define   _NWK_NONSTANDARD_BEACON_FILTER_
#endif

#ifndef _NWK_GROUP_
#define   _NWK_GROUP_
#endif

#ifndef _NWK_CHECK_OUT_BROADCAST_
#define   _NWK_CHECK_OUT_BROADCAST_
#endif

#ifndef _NWK_STOCHASTIC_ADDRESSING_
#define   _NWK_STOCHASTIC_ADDRESSING_
#endif

#ifndef _NWK_FAST_ROUTE_DISCOVERY_
#define _NWK_FAST_ROUTE_DISCOVERY_
#endif

#ifndef _NWK_MESH_ROUTING_
#define   _NWK_MESH_ROUTING_
#endif

#ifndef _NWK_ORPHAN_JOIN_
#define   _NWK_ORPHAN_JOIN_
#endif

#ifndef _NWK_PASSIVE_ACK_
#define   _NWK_PASSIVE_ACK_
#endif

#ifndef _NWK_NEIGHBOR_ENTRY_ADDITION_UPON_RX_FRAME_
#define   _NWK_NEIGHBOR_ENTRY_ADDITION_UPON_RX_FRAME_
#endif

#ifndef _MAC_BAN_NODE_
#define  _MAC_BAN_NODE_
#endif

#ifndef _NWK_ROUTE_REQUEST_RETRIES_BASED_ON_MAC_CONF_
#define   _NWK_ROUTE_REQUEST_RETRIES_BASED_ON_MAC_CONF_
#endif

#ifndef _ZCL_SUPPORT_
#define   _ZCL_SUPPORT_
#endif

#ifndef _ZCL_REPORTING_SUPPORT_
#define _ZCL_REPORTING_SUPPORT_
#endif

#ifndef _ZCL_ATTRIBUTE_EXTENSION_
#define _ZCL_ATTRIBUTE_EXTENSION_
#endif

#ifndef _APS_MULTICAST_
#define   _APS_MULTICAST_
#endif

#ifndef _BINDING_
#define   _BINDING_
#endif


#if defined(ZIGBEE_COORDINATOR)
  #define BDB_TOUCHLINK_SUPPORT 0
#else
  #define BDB_TOUCHLINK_SUPPORT 1
#endif

#if (BDB_TOUCHLINK_SUPPORT == 1)
//#define BDB_TOUCHLINK_INITIATOR_SUPPORT 0
#define BDB_TOUCHLINK_INITIATOR_SUPPORT 1
#endif


#define BDB_NWKFORMATION_SUPPORT       1
#define BDB_FINDINGANDBINDING_SUPPORT  1

//Max no. of matched clusters supported between the devices.
#define BDB_INITIATOR_MAX_MATCHED_SERVER_CLUSTER_COUNT         15
#define BDB_INITIATOR_MAX_MATCHED_CLIENT_CLUSTER_COUNT         15

//Max no. of Nodes to be stored in Trust Center node table
//Increase it to accommodate more nodes in Centralized network
#define BDB_NODE_JOIN_INFO_ENTRIES_AMOUNT  2

#define DISTRIBUTED_NETWORK_ADDRESS 0xBEE

#define CS_NWK_UNIQUE_ADDR 0

#if defined (ZIGBEE_END_DEVICE)
//#define _SLEEP_WHEN_IDLE_
#endif

#ifndef _NWK_ROUTING_OPTIMIZATION_
//#define _NWK_ROUTING_OPTIMIZATION_    0   // LOW
//#define _NWK_ROUTING_OPTIMIZATION_    1
#define _NWK_ROUTING_OPTIMIZATION_      2    // HIGH
#endif

// Configures the maximum S_NV items to be supported. Minimum should be 58.
#define S_NV_MAX_ITEM_COUNT 60

// Configures the maximum buffers for interpan data request. Minimum should be 2
#define INTERPAN_BUFFERS_AMOUNT 2

#ifdef ZIGBEE_END_DEVICE
#define _SLEEP_WHEN_IDLE_
#endif

#define NWK_PRIVATE
#define APS_PRIVATE
#define ZDO_PRIVATE
#define _RF_REG_ACCESS_
/* RF random way of generating random number*/
#ifndef _RF_RND_
#define _RF_RND_
#endif
#define _CONTROL_FRAME_PENDING_BIT_
#define _PENDING_EMPTY_DATA_FRAME_

#define _CUSTOM_PASSIVE_ACK_THRESHOLD_
#define _SILENT_LEAVE_WITHOUT_NETWORK_LEFT_

#define _TEMP_CHANGES_FOR_ZIG_TEST_

#define _LEAVE_NETWORK_IMMEDIATE_WITH_NO_TANSACTIONS_LEFT_


#include <stackConfig.h>

#endif // BIT_CLOUD_CONFIG_H
