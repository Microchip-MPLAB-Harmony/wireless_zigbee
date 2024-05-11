/*******************************************************************************
  NWK Concentratror Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkConcentrator.h

  Summary:
    This file comprises the Interface of network Concentrator.

  Description:
    This file comprises the Interface of network Concentrator.
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

#if !defined _NWK_CONCENTRATOR_H
#define _NWK_CONCENTRATOR_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <appTimer.h>
#include <nlmeRouteDiscovery.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Internal states of the network concentrator. */
typedef enum _NwkConcentratorState_t
{
  NWK_CONCENTRATOR_IDLE_STATE = 0x89,
  NWK_CONCENTRATOR_FIRST_STATE = 0x8A,
  NWK_CONCENTRATOR_START_TIMER_STATE = NWK_CONCENTRATOR_FIRST_STATE,
  NWK_CONCENTRATOR_ROUTE_DISCOVERY_STATE = 0x8B,
  NWK_CONCENTRATOR_LAST_STATE
} NwkConcentratorState_t;

/** State and parameters of the network concentrator. */
typedef struct _NwkConcentrator_t
{
  NwkConcentratorState_t state;
  union
  {
    HAL_AppTimer_t timer;
    NWK_RouteDiscoveryReq_t routeDiscovery;
  } req;
} NwkConcentrator_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _NWK_CONCENTRATOR_
/**************************************************************************//**
  \brief Start the network concentrator.

    Periodic sending of route discovery commands.
 ******************************************************************************/
NWK_PRIVATE void nwkStartConcentrator(void);

/**************************************************************************//**
  \brief nwkReset module call this function when network layer is reseting.
 ******************************************************************************/
NWK_PRIVATE void nwkResetConcentrator(void);

/**************************************************************************//**
  \brief Check state of the concentrator and stop timer.
 ******************************************************************************/
NWK_PRIVATE void nwkStopConcentratorTimer(void);

#else /* _NWK_CONCENTRATOR_ */

#define nwkStartConcentrator() (void)0
#define nwkStopConcentratorTimer()  (void)0
#define nwkResetConcentrator() (void)0

#endif /* _NWK_CONCENTRATOR_ */
#endif /* _NWK_CONCENTRATOR_H */
/** eof nwkConcentrator.h */

