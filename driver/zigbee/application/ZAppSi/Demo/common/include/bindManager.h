/************************************************************************//**
  \file bindmanager.h

  \brief
    Bind manager interface declaration.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.01.09 A. Taradov - Created.
******************************************************************************/

#ifndef _BINDMANAGER_H
#define _BINDMANAGER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zdo.h>
#include <aps.h>
#include <zcl.h>
#include <ZAppSiCommands.h>
/******************************************************************************
                    Defines section
******************************************************************************/
#define BIND_DIRECTION_IN   0
#define BIND_DIRECTION_OUT  1
#define MAX_MATCH_DESC_RESP_AMOUNT 3
typedef struct
{
  void         (*callback)(bool status);
  ClusterId_t  cluster;
  uint8_t      srcEndpoint;
  uint8_t      direction;
  uint8_t      matchesReceived;
  ZDO_MatchDescResp_t matchDescResp[MAX_MATCH_DESC_RESP_AMOUNT];
} MatchBindRequest_t;

/******************************************************************************
                    Global variables section
******************************************************************************/

/******************************************************************************
                    Functions prototypes section
******************************************************************************/
void matchBindDevices(void);

void matchBindClusters(ZS_ZclStartRequest_t* cfg,
                       void (*conf)(bool status));
#endif // _BINDMANAGER_H

// eof bindManager.h
