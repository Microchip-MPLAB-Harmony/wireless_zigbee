/**************************************************************************//**
  \file  rDebug.c

  \brief Debug functions defenitions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
 ******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <rTypes.h>
#include <rDebug.h>
#include <ZAppSiIdentifiers.h>

#if APP_REDUCED_OTAU_SERVER == 0

/******************************************************************************
                   Static variables section
******************************************************************************/
static ZS_AssertCommandBuffer_t debugMessage;
/******************************************************************************
                   Implementations section
******************************************************************************/
void rAssert(bool condition, RDbgMsgId_t messageId)
{
  if ((false == condition) && (debugMessage.state == R_BUFFER_FREE_STATE))
  {
    debugMessage.commandFrame.length = sizeof(uint16_t) + 1;
    debugMessage.commandFrame.commandId = R_SYS_DEBUG_INFORMATION;
    debugMessage.commandFrame.assertCode = messageId;

    serialManager.write((ZS_CommandBuffer_t *)&debugMessage);
  }
}

#endif /* APP_REDUCED_OTAU_SERVER == 0 */
/* eof rDebug.c */
