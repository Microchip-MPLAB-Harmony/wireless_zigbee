/*******************************************************************************
  NWK Memory Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkMem.h

  Summary:
    This file defines the interface to the NWK Memory Manager.

  Description:
    This file defines the interface to the NWK Memory Manager.
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

#if !defined _NWK_MEM_H
#define _NWK_MEM_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkCommon.h>
#include <private/nwkIB.h>
#include <private/nwkTaskManager.h>
#include <private/nwkReset.h>
#include <private/nwkDiscovery.h>
#include <private/nwkTx.h>
#include <private/nwkDataReq.h>
#include <private/nwkTxDelay.h>
#include <private/nwkPacket.h>
#include <private/nwkLeave.h>
#include <private/nwkEDScan.h>
#include <private/nwkBTT.h>
#include <private/nwkAddressConflict.h>
#include <private/nwkAddressMap.h>
#include <private/nwkCommands.h>
#include <private/nwkLoopback.h>
#include <private/nwkFormation.h>
#include <private/nwkStartRouter.h>
#include <private/nwkJoinReq.h>
#include <private/nwkJoinInd.h>
#include <private/nwkPermitJoining.h>
#include <private/nwkLinkStatus.h>
#include <private/nwkRoutingTable.h>
#include <private/nwkRouteDiscovery.h>
#include <private/nwkRouteDiscoveryTable.h>
#include <private/nwkStatusInd.h>
#include <private/nwkSync.h>
#include <private/nwkSyncLoss.h>
#include <private/nwkConcentrator.h>
#include <private/nwkReportCommand.h>
#include <private/nwkUpdateCommand.h>
#include <private/nwkManager.h>
#include <private/nwkDirectJoin.h>
#include <private/nwkOrphan.h>
#include <private/nwkSilentJoin.h>
#include <private/nwkRouteRecord.h>
#include <private/nwkRouteCache.h>
#include <private/nwkManyToOne.h>
#include <nwkGroup.h>
#include <private/nwkPassiveAck.h>
#include <private/nwkKeys.h>
#include <private/nwkEndDeviceTimeoutReq.h>
#include <private/nwkEndDeviceTimeoutInd.h>

/******************************************************************************
                               Types section
 ******************************************************************************/
/** Internal variables of NWK layer. */
typedef struct _NwkMem_t
{
  /** Global NWK state. */
  NwkState_t state;
  /** State of task manager. */
  NwkTaskManager_t taskManager;
  /** Internal variables of NLME-RESET component. */
  NwkReset_t reset;
  /** Internal variables of NLME-DISCOVERY component. */
  NwkDiscovery_t discovery;
  /** States and parameters of packet transmission component. */
  NwkTx_t tx;
  NwkDataConf_t dataConf;
  NwkTxDelay_t txDelay;
  NwkPacketManager_t packetManager;
  /** Internal variables of NLME-LEAVE component. */
  NwkLeave_t leave;
  /** Internal variables of NLME-ED-SCAN component. */
  NwkEDScan_t edScan;
  /** Broadcast transaction table. Only pointer to configServer
   * and a size of table. */
  NwkBTT_t BTT;
  /** Address map table. */
  NwkAddressMap_t addressTable;
  /** Neighbor table */
  NwkNeighborTable_t neighborTable;
  /** Address conflict resolver. */
  NwkAddrConflict_t addrConflict;
  /** Requests to send command packets. */
  NwkCommands_t commands;
  /** Queue and state of loopback component. */
  NwkLoopback_t loopback;
#if defined(_COORDINATOR_) || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_))
  /** Internal variables of NLME-FORMATION component. */
  NwkFormation_t formation;
#endif /* #if defined(_COORDINATOR_) || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_)) */
#if defined _ROUTER_
  /** Internal variables of NLME-START-ROUTER component. */
  NwkStartRouter_t startRouter;
#endif /* _ROUTER_ */
#if defined _ROUTER_ || defined _ENDDEVICE_
  /** Internal state of NLME-JOIN.request primitive. */
  NwkJoinReq_t joinReq;
#endif /* _ROUTER_ or _ENDDEVICE_ */
#if defined _ROUTER_ || defined _COORDINATOR_
  /** Internal state of NLME-JOIN.indication primitive. */
  NwkJoinInd_t joinInd;
  /** Internal variables of NLME-PERMIT-JOINING component. */
  NwkPermitJoining_t permitJoining;
  /** Internal state of handler of a link status command. */
  NwkLinkStatus_t linkStatus;
  #if defined NWK_ROUTING_CAPACITY \
    && (defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_)
  /** Status and internals variables of a routing components. */
  NwkRouteDiscovery_t routeDiscovery;
  NwkRouteDiscoveryTable_t routeDiscoveryTable;
  NwkRoutingTable_t routingTable;
  #endif /* NWK_ROUTING_CAPACITY and (_NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_) */
  #if defined NWK_ROUTING_CAPACITY && defined _NWK_ROUTE_RECORD_
  /** Internal state of handler of a route record command. */
  NwkRouteRecord_t routeRecord;
  #endif /* NWK_ROUTING_CAPACITY and _NWK_ROUTE_RECORD_ */
  /** Variables of network status sender. */
  NwkStatusSender_t statusSender;
#if defined _NWK_DIRECT_JOIN_
  NwkDirectJoin_t directJoin;
#endif /* _NWK_DIRECT_JOIN_ */
#if defined _NWK_PASSIVE_ACK_
  NwkPassiveAck_t passiveAck;
#endif /* _NWK_PASSIVE_ACK_ */
#endif /* _ROUTER_ or _COORDINATOR_ */
#if defined _ENDDEVICE_
  /** Internal variables of NLME-SYNC component. */
  NwkSync_t sync;
#endif /* _ENDDEVICE_ */
#if defined _ROUTER_ && defined NWK_COORD_REALIGNMENT
  /** Internal variables of NLME-SYNC-LOSS component. */
  NwkSyncLoss_t syncLoss;
#endif /* _ROUTER_ and NWK_COORD_REALIGNMENT */
#if defined _RESOLVE_PANID_CONFLICT_
  /** Internal state of handler of a report command. */
  NwkReportCommand_t nwkReportCommand;
  /** Internal state of handler of a update command. */
  NwkUpdateCommand_t nwkUpdateCommand;
  #if defined _NETWORK_MANAGER_
  NwkManager_t manager;
  #endif /* _NETWORK_MANAGER_ */
#endif /* _RESOLVE_PANID_CONFLICT_ */
#if defined _NWK_CONCENTRATOR_
  NwkConcentrator_t concentrator;
#endif /* _NWK_CONCENTRATOR_ */
#if defined _NWK_ROUTE_CACHE_
  NwkRouteCache_t routeCache;
#endif /* _NWK_ROUTE_CACHE_ */
#if defined _NWK_ORPHAN_JOIN_
  NwkOrphan_t orphan;
#endif
#if defined _COMMISSIONING_
  NwkSilentJoin_t silentJoin;
#endif
#if defined _GROUP_TABLE_
  NWK_GroupTable_t groupTable;
#endif
#if defined _SECURITY_
  NWK_Keys_t nwkKeys;
#endif /* _SECURITY_ */
#ifdef _CHILD_MANAGEMENT_
  NwkEndDeviceTimeoutReq_t endDeviceTimeoutReq;
  NwkEndDeviceTimeoutInd_t endDeviceTimeoutInd;
#endif /* _CHILD_MANAGEMENT_ */
} NwkMem_t;

/******************************************************************************
                           External variables section
******************************************************************************/

/** nwkMem is defined in nwkMem.c */
extern NwkMem_t nwkMem;
/** csNIB is defined in configServer.c */
extern NIB_t csNIB;

/******************************************************************************
                           Inline functions section
 ******************************************************************************/
INLINE NIB_t* nwkMemNib(void)
{
  return &csNIB;
}

INLINE NwkTaskManager_t* nwkMemTaskManager(void)
{
  return &nwkMem.taskManager;
}

INLINE NwkReset_t* nwkMemReset(void)
{
  return &nwkMem.reset;
}

INLINE NwkDiscovery_t* nwkMemDiscovery(void)
{
  return &nwkMem.discovery;
}

INLINE NwkTx_t* nwkMemTx(void)
{
  return &nwkMem.tx;
}

INLINE NwkDataConf_t* nwkMemDataConf(void)
{
  return &nwkMem.dataConf;
}

INLINE NwkTxDelay_t* nwkMemTxDelay(void)
{
  return &nwkMem.txDelay;
}

INLINE NwkPacketManager_t* nwkMemPacketManager(void)
{
  return &nwkMem.packetManager;
}

INLINE NwkLeave_t* nwkMemLeave(void)
{
  return &nwkMem.leave;
}

INLINE NwkEDScan_t* nwkMemEDScan(void)
{
  return &nwkMem.edScan;
}

INLINE NwkBTT_t* nwkMemBTT(void)
{
  return &nwkMem.BTT;
}

INLINE NwkAddressMap_t* nwkMemAddressMap(void)
{
  return &nwkMem.addressTable;
}

INLINE NwkAddrConflict_t* nwkMemAddrConflict(void)
{
  return &nwkMem.addrConflict;
}

INLINE NwkCommands_t* nwkMemCommands(void)
{
  return &nwkMem.commands;
}

INLINE NwkLoopback_t* nwkMemLoopback(void)
{
  return &nwkMem.loopback;
}

#if defined _COORDINATOR_ || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_))
INLINE NwkFormation_t* nwkMemFormation(void)
{
  return &nwkMem.formation;
}
#endif /* #if defined(_COORDINATOR_) || (defined(_ROUTER_) && defined(_DISTRIBUTED_SECURITY_)) */
#if defined _ROUTER_
INLINE NwkStartRouter_t* nwkMemStartRouter(void)
{
  return &nwkMem.startRouter;
}
#endif
#if defined _ROUTER_ || defined _ENDDEVICE_
INLINE NwkJoinReq_t* nwkMemJoinReq(void)
{
  return &nwkMem.joinReq;
}
#endif
#if defined _ROUTER_ || defined _COORDINATOR_
INLINE NwkJoinInd_t* nwkMemJoinInd(void)
{
  return &nwkMem.joinInd;
}

INLINE NwkPermitJoining_t* nwkMemPermitJoining(void)
{
  return &nwkMem.permitJoining;
}

INLINE NwkLinkStatus_t* nwkMemLinkStatus(void)
{
  return &nwkMem.linkStatus;
}

#if defined NWK_ROUTING_CAPACITY \
  && (defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_)
INLINE NwkRouteDiscovery_t* nwkMemRouteDiscovery(void)
{
  return &nwkMem.routeDiscovery;
}

INLINE NwkRouteDiscoveryTable_t* nwkMemRouteDiscoveryTable(void)
{
  return &nwkMem.routeDiscoveryTable;
}

INLINE NwkRoutingTable_t* nwkMemRoutingTable(void)
{
  return &nwkMem.routingTable;
}
#endif /* NWK_ROUTING_CAPACITY and (_NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_) */
#if defined NWK_ROUTING_CAPACITY && defined _NWK_ROUTE_RECORD_
INLINE NwkRouteRecord_t* nwkMemRouteRecord(void)
{
  return &nwkMem.routeRecord;
}
#endif /* NWK_ROUTING_CAPACITY and _NWK_ROUTE_RECORD_ */

INLINE NwkStatusSender_t* nwkMemStatusSender(void)
{
  return &nwkMem.statusSender;
}

#if defined _NWK_PASSIVE_ACK_
INLINE NwkPassiveAck_t* nwkMemPassiveAck(void)
{
  return &nwkMem.passiveAck;
}
#endif /* _NWK_PASSIVE_ACK_ */
#endif /* _ROUTER_ or _COORDINATOR_ */

#if defined _ENDDEVICE_
INLINE NwkSync_t* nwkMemSync(void)
{
  return &nwkMem.sync;
}
#endif
#if defined _ROUTER_ && defined NWK_COORD_REALIGNMENT
INLINE NwkSyncLoss_t* nwkMemSyncLoss(void)
{
  return &nwkMem.syncLoss;
}
#endif /* _ROUTER_ and NWK_COORD_REALIGNMENT */

INLINE NwkNeighborTable_t* nwkMemNeighborTable(void)
{
  return &nwkMem.neighborTable;
}

#if defined _RESOLVE_PANID_CONFLICT_
INLINE NwkReportCommand_t* nwkMemReportCommand(void)
{
  return &nwkMem.nwkReportCommand;
}

INLINE NwkUpdateCommand_t* nwkMemUpdateCommand(void)
{
  return &nwkMem.nwkUpdateCommand;
}
#if defined _NETWORK_MANAGER_
INLINE NwkManager_t* nwkMemManager(void)
{
  return &nwkMem.manager;
}
#endif /* _NETWORK_MANAGER_ */
#endif /* _RESOLVE_PANID_CONFLICT_ */
#if defined _NWK_CONCENTRATOR_
INLINE NwkConcentrator_t* nwkMemConcentrator(void)
{
  return &nwkMem.concentrator;
}
#endif /* _NWK_CONCENTRATOR_ */
#if defined _NWK_ROUTE_CACHE_
INLINE NwkRouteCache_t* nwkMemRouteCache(void)
{
  return &nwkMem.routeCache;
}
#endif /* _NWK_ROUTE_CACHE_ */

#if (defined(_ROUTER_) || defined(_COORDINATOR_)) && defined(_NWK_DIRECT_JOIN_)
INLINE NwkDirectJoin_t* nwkMemDirectJoin(void)
{
  return &nwkMem.directJoin;
}
#endif

#if defined _NWK_ORPHAN_JOIN_
INLINE NwkOrphan_t* nwkMemOrphan(void)
{
  return &nwkMem.orphan;
}
#endif

#if defined _COMMISSIONING_
INLINE NwkSilentJoin_t* nwkMemSilentJoin(void)
{
  return &nwkMem.silentJoin;
}
#endif

#if defined _GROUP_TABLE_
INLINE NWK_GroupTable_t* nwkMemGroup(void)
{
  return &nwkMem.groupTable;
}
#endif

#if defined _SECURITY_
INLINE NWK_Keys_t* nwkMemKeys(void)
{
  return &nwkMem.nwkKeys;
}
#endif

#ifdef _CHILD_MANAGEMENT_
INLINE NwkEndDeviceTimeoutReq_t* nwkMemEndDeviceTimeoutReq(void)
{
  return &nwkMem.endDeviceTimeoutReq;
}

INLINE NwkEndDeviceTimeoutInd_t* nwkMemEndDeviceTimeoutInd(void)
{
  return &nwkMem.endDeviceTimeoutInd;
}
#endif /* _CHILD_MANAGEMENT_ */

#endif /* _NWK_MEM_H */
/** eof nwkMem.h */

