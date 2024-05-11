/**************************************************************************//**
  \file  rNwk.h

  \brief Nwk Related commands handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
  Last change:
    $Id: rNwk.h 32972 2019-04-22 12:48:49Z I41773 $
 ******************************************************************************/
#ifndef _RNWK_H
#define _RNWK_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
void rNwkAddrResolvRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkResetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkDirectJoinRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkLeaveRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkSetShortAddressRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
void rNwkJoinRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif // defined(_ROUTER_) || defined(_ENDDEVICE_)
#if defined(_ROUTER_)
void rNwkStartRouterRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif // defined(_ROUTER_)
#if defined(_ROUTER_) || defined(_COORDINATOR_)
void rNwkPermitJoiningRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkGetNextHopRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _CERTIFICATION_
#if defined _NWK_MESH_ROUTING_
void rNwkSetNextHopRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
#endif //#ifdef _CERTIFICATION_
#if defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_
void rNwkRemotelyInitiatedRouteDiscoveryRequestProcess(APS_DataInd_t *ind, uint8_t endpoint);
void rNwkRouteDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkSetRouteFailOrderProcess(ZS_CommandBuffer_t *commandBuffer);
#if defined _CERTIFICATION_ && defined _NWK_FAST_ROUTE_DISCOVERY_
void rNwkSetFastRouteDiscoveryProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _CERTIFICATION_ and _NWK_FAST_ROUTE_DISCOVERY_ */
#endif /* _NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* defined(_ROUTER_) || defined(_COORDINATOR_) */
#if defined _PROFILER_
void rNwkProfilerRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
#ifdef _SECURITY_
void rNwkGetOutSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkSetOutgoingSecFrameCounter(ZS_CommandBuffer_t *commandBuffer);
void rNwkGetActiveKeySeqNum(ZS_CommandBuffer_t *commandBuffer);
#ifdef _NWK_IN_FRAME_COUNTERS_
void rNwkSetInSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkGetInSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _NWK_IN_FRAME_COUNTERS_ */
#if defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
void rTCPolicySetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif //#if defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
#endif /* _SECURITY_ */
#ifdef _CHILD_MANAGEMENT_
void rNwkEndDeviceTimeoutRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkSetEDTimeoutByParentProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _CHILD_MANAGEMENT_ */
void rNwkAddAddressMapReqProcess(ZS_CommandBuffer_t *commandBuffer);
void rNwkRemoveNeighborEntryProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _RNWK_H */
/* eof  rNwk.h */
