/**************************************************************************//**
  \file  rAux.c

  \brief Auxiliary commands implementation (commands that are not directly
    mapped to BitCloud API)

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    19.01.2010  A. Taradov - Created.
******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <aps/include/aps.h>
#include <rMem.h>
#include <rTypes.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <bufferallocator.h>

#if defined(_SECURITY_) && defined _LINK_SECURITY_
#include <security/serviceprovider/include/sspHash.h>
#include <zcl/include/eccAux.h>
#endif

/******************************************************************************
                   Defines section
******************************************************************************/

/******************************************************************************
                   Implementations section
******************************************************************************/

#if defined(_SECURITY_) && defined _LINK_SECURITY_
void rAuxGetLinkKeyHashRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_AuxGetLinkKeyHashReq_t *req = (ZS_AuxGetLinkKeyHashReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_AuxGetLinkKeyHashConf_t *conf = (ZS_AuxGetLinkKeyHashConf_t *)confirmBuffer->commandFrame.payload;
  const ExtAddr_t extAddr = req->extAddr;
  const APS_KeyHandle_t keyHandle = APS_FindKeys(&extAddr);
  uint8_t *linkKey;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_AuxGetLinkKeyHashConf_t);
  confirmBuffer->commandFrame.commandId = R_AUX_GET_LINK_KEY_HASH_CONFIRM;

  if (APS_KEYS_FOUND(keyHandle) && (linkKey = APS_GetLinkKey(keyHandle)))
  {
    SSP_BcbHash((uint8_t *)&conf->linkKeyHash, SECURITY_KEY_SIZE, linkKey);
  }
  else
  {
    memset(&conf->linkKeyHash, 0, SECURITY_KEY_SIZE);
  }

  serialManager.write(confirmBuffer);

}
#endif // defined(_SECURITY_) && defined _LINK_SECURITY_

// eof rAux.c
