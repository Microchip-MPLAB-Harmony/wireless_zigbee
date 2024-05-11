/*******************************************************************************
  NWK Permit Joining Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkPermitJoining.h

  Summary:
    This file contains declaration and defines for NWK Permit Joining.

  Description:
    This file contains declaration and defines for NWK Permit Joining.
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

#if !defined _NWK_PERMIT_JOINING_H
#define _NWK_PERMIT_JOINING_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <mac.h>
#include <nlmePermitJoining.h>
#include <appTimer.h>

/******************************************************************************
                               Types section
 ******************************************************************************/
/** Internal states of NLME-PERMIT_JOINING component */
typedef enum _NwkPermitJoiningStates_t
{
  NWK_PERMIT_JOINING_IDLE_STATE = 0x48,
  NWK_PERMIT_JOINING_FIRST_STATE = 0x4A,
  NWK_PERMIT_JOINING_WAIT_TIMER_FIRED_STATE = NWK_PERMIT_JOINING_FIRST_STATE,
  NWK_PERMIT_JOINING_BEGIN_STATE = 0x5D,
  NWK_PERMIT_JOINING_CONFIRM_STATE = 0x5E,
  NWK_PERMIT_JOINING_TIMER_FIRED_STATE = 0x5F,
  NWK_PERMIT_JOINING_SET_ASSOC_PERMIT_STATE = 0x60,
  NWK_PERMIT_JOINING_LAST_STATE
} NwkPermitJoiningState_t;

/** Internal parameters of NLME-PERMIT-JOINING component. */
typedef struct _NwkPermitJoining_t
{
  NwkPermitJoiningState_t state;
  QueueDescriptor_t       queue;
  MAC_SetReq_t            macReq;
  HAL_AppTimer_t          timer;
} NwkPermitJoining_t;

/******************************************************************************
                         Inline functions section
 ******************************************************************************/
#if defined _ROUTER_ || defined _COORDINATOR_
/*************************************************************************//**
  \brief Task handler of the NLME-PERMIT-JOINING component.
 *****************************************************************************/
NWK_PRIVATE void nwkPermitJoiningTaskHandler(void);

/*************************************************************************//**
  \brief Reset the NLME-PERMIT-JOINING component.
 *****************************************************************************/
NWK_PRIVATE void nwkResetPermitJoining(void);

/******************************************************************************
  \brief nwkPermitJoining idle checking.

  \return true, if nwkPermitJoining performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkPermitJoiningIsIdle(void);

#else /* _ROUTER_ or _COORDINATOR_ */

#define nwkPermitJoiningTaskHandler NULL
#define nwkPermitJoiningIsIdle NULL
#define nwkResetPermitJoining() (void)0

#endif /* _ROUTER_ or _COORDINATOR_ */
#endif /* _NWK_PERMIT_JOINING_H */
/** eof nwkPermitJoining.h */

