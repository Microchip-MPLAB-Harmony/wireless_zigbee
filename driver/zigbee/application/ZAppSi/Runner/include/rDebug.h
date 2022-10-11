/**************************************************************************//**
  \file  rDebug.h

  \brief Debug related types and functions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RDEBUG_H
#define _RDEBUG_H
/******************************************************************************
                   Includes section
******************************************************************************/
#include <rTypes.h>
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  R_DBG_SUCCESS                           = 0x0000,
  R_DBG_FAIL                              = 0x0001,
  R_DBG_PAYLOAD_TOO_LONG                  = 0x0002,
  R_DBG_COMMAND_PAYLOAD_TOO_SHORT         = 0x0003,
  R_DBG_COMMANDREQUESTADDITIONALACTIONS_0 = 0x0004,
  R_DBG_COMMANDREQUESTADDITIONALACTIONS_1 = 0x0005,
  R_DBG_VERIFYSIGNATURE_0                 = 0x0006,
  R_DBG_VERIFYSIGNATURE_1                 = 0x0007,
  R_DBG_VERIFYSIGNATURE_2                 = 0x0008,
  R_DBG_VERIFYSIGNATURE_3                 = 0x0009,
  R_DBG_VERIFYSIGNATURE_4                 = 0x000A,
  R_DBG_VERIFYSIGNATURE_5                 = 0x000B,
  R_DBG_CONF_NO_MEMORY                    = 0x000C,
  R_DBG_REQ_NO_MEMORY                     = 0x000D,
  R_DBG_NO_STACK_REQUESTS_AVAILABLE       = 0x000F,
  R_DBG_NTFY_BAD_STATUS                   = 0x0010,
  R_DBG_REVENTS_NULL_POINTER              = 0x0011,
  R_DBG_RSYS_NULL_POINTER                 = 0x0012,
  R_DBG_EVENT_MGMT_ILL_REQ_ID_0           = 0x0013,
  R_DBG_EVENT_MGMT_ILL_REQ_ID_1           = 0x0014,
  R_DBG_USART_NO_BUFFERS                  = 0x0f00,
  R_DBG_NETWORK_LOST                      = 0xffff,
} RDbgMsgId_t;
/******************************************************************************
                   Prototypes section
******************************************************************************/
#if APP_REDUCED_OTAU_SERVER == 0
  void rAssert(bool condition, RDbgMsgId_t messageId);
#else
  #define rAssert(condition, messageId)
#endif

#endif  /* _RDEBUG_H */

/* eof rDebug.h */
