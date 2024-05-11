/**************************************************************************//**
  \file  rZdo.h

  \brief Zdo related functions declarations

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RZDO_H
#define _RZDO_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
void rZdoGetNeibAmountProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoGetNeibTableProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoMgmtLeaveRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoMgmtNwkUpdateNotifyProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoNwkAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoMgmtPermitJoiningRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoSetTxPowerRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoWakeupIndicationProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoSleepRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _ENDDEVICE_
void rZdoStartSyncReqProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoStopSyncReqProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _ENDDEVICE_ */
#if APP_ZDP_REQUESTS
void rZdoIeeeAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoNodeDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpPowerDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpComplexDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _PARENT_ANNCE_  
void rZdpParentAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
void rZdpUserDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpEndDeviceAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpLqiRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpRtgRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpUserDescSetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdoNwkUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpSystemServerDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _BINDING_
void rZdpMatchDescRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpBindRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rZdpUnbindRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _END_DEVICE_BINDING_
void rZdpEndDeviceBindRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _END_DEVICE_BINDING_ */

void rZdpMgmtBindRequestProcess(ZS_CommandBuffer_t *commandBuffer);

#endif /* _BINDING_ */
#endif /* APP_ZDP_REQUESTS */

#if defined _SECURITY_ && defined _LINK_SECURITY_
void rZdoVerifyKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif //#if defined _SECURITY_ && defined _LINK_SECURITY_

#endif /* _RZDO_H */

/* eof rZdo.h */
