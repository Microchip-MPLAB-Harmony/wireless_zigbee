/**************************************************************************//**
  \file  rExtensions.h

  \brief QA Specific commands

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _REXTENSIONS_H
#define _REXTENSIONS_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
#ifdef _APS_MULTICAST_
void rAfDirectRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rAfIndirectRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rAfGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _APS_MULTICAST_ */
void rCountedPacketReceivedProcess(APS_DataInd_t *ind, uint8_t endpoint);
void rResetPacketCountProcess(APS_DataInd_t *ind, uint8_t endpoint);
void rRetrievePacketCountProcess(APS_DataInd_t *ind, uint8_t endpoint);
void rBufferTestRequestProcess(APS_DataInd_t *ind, uint8_t endpoint);
void rBufferTestGroupRequestProcess(APS_DataInd_t *ind, uint8_t endpoint);
APS_DataReq_t *rMakeDataReqBasedOnInd(APS_DataInd_t *ind, ClusterId_t clusterId, uint8_t asduLength, uint8_t srcEndpoint);

#endif /* _REXTENSIONS_H */

/* eof  rExtensions.h */
