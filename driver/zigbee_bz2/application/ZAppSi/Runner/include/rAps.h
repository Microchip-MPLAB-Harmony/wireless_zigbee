/**************************************************************************//**
  \file  rAps.h

  \brief Aps releated command handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RAPS_H
#define _RAPS_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
#ifdef _ZSE_CERTIFICATION_
void rApsSetFrameCounterRequest(ZS_CommandBuffer_t *commandBuffer);
#endif // _ZSE_CERTIFICATION_
void rApsResetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsStartRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsDataInd(APS_DataInd_t *ind, uint8_t endpoint);
void rApsDataRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsGetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsSetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _APS_MULTICAST_
void rApsAddGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsRemoveGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsRemoveAllGroupsRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _APS_MULTICAST_ */
#ifdef _BINDING_
void rApsBindRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsUnbindRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _BINDING_ */
#ifdef _GREENPOWER_SUPPORT_
void rApsDataRequestWithAliasProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
#ifdef _SECURITY_
void rApsTransportKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsSwitchKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#ifdef _LINK_SECURITY_
void rApsRequestKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rApsGetOutSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#if defined _CERTIFICATION_
void rApsUpdateSecurityPolicyProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
#endif /* _LINK_SECURITY_ */

#endif /* _SECURITY_ */

#endif /* _RAPS_H */

/* eof rAps.h */
