/*******************************************************************************
  NWK Energy Detection Scan Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkEDScan.h

  Summary:
    This file provides the interface to the NWK layer Energy Detection Mechanism.

  Description:
    This file provides the interface to the NWK layer Energy Detection Mechanism.
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

#if !defined _NWK_EDSCAN_H
#define _NWK_EDSCAN_H

/*****************************************************************************
                              Includes section
 *****************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nwkCommon.h>

/*****************************************************************************
                              Types section
 *****************************************************************************/
/** Internal states of NLME-ED-SCAN component */
typedef enum _NwkEDScanState_t
{
  NWK_EDSCAN_IDLE_STATE = 0x13,
  NWK_EDSCAN_FIRST_STATE = 0xE7,
  NWK_EDSCAN_BEGIN_STATE = NWK_EDSCAN_FIRST_STATE,
  NWK_EDSCAN_MAC_SCAN_STATE = 0xE8,
  NWK_EDSCAN_CONFIRM_STATE = 0xE9,
  NWK_EDSCAN_LAST_STATE
} NwkEDScanState_t;

/** Internal parameters of NLME-ED-SCAN */
typedef struct _NwkEDScan_t
{
  QueueDescriptor_t queue; /**< Queue of requests from upper layer */
  NwkEDScanState_t state; /**< finite-state machine */
  NwkState_t savedStateMachine;
} NwkEDScan_t;

/*****************************************************************************
                             Prototypes section
 *****************************************************************************/
/*************************************************************************//**
  \brief Reset NLME-ED-SCAN component.
 *****************************************************************************/
NWK_PRIVATE void nwkResetEDScan(void);

/******************************************************************************
  \brief nwkEDScan idle checking.

  \return true, if nwkEDScan performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkEDScanIsIdle(void);

/*************************************************************************//**
  \brief Main task handler of NLME-ED-SCAN
 *****************************************************************************/
NWK_PRIVATE void nwkEDScanTaskHandler(void);

#endif /* _NWK_EDSCAN_H */
/** eof nwkEDScan.h */

