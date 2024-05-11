/*******************************************************************************
  NWK Data Request Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkDataReq.h

  Summary:
    This file comprises the Interface of the NWK data request component.

  Description:
    This file comprises the Interface of the NWK data request component.
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

#if !defined _NWK_DATA_REQ_H
#define _NWK_DATA_REQ_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nwkCommon.h>
#include <nldeData.h>

/******************************************************************************
                               Define(s) section
 ******************************************************************************/
/** Transmission parameters of data packets. */
#define NWK_UNICAST_DATA_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_DATA, NULL, nwkConfirmDataTx, false}
#define NWK_BROADCAST_DATA_TX_PARAMETERS \
  {NWK_TX_DELAY_INITIAL_BROADCAST, NULL, nwkConfirmDataTx, false}
#define NWK_MULTICAST_MEMBER_TX_PARAMETERS \
  {NWK_TX_DELAY_INITIAL_MULTICAST, NULL, nwkConfirmDataTx, false}

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Internal states of data confirmation. */
typedef enum _NwkDataConfState_t
{
  NWK_DATA_CONF_IDLE_STATE = 0x41,
  NWK_DATA_CONF_FIRST_STATE = 0x03,
  NWK_DATA_CONF_PROCESS_STATE = NWK_DATA_CONF_FIRST_STATE,
  NWK_DATA_CONF_LAST_STATE
} NwkDataConfState_t;

/** Internal variables of this component. */
typedef struct _NwkDataConf_t
{
  QueueDescriptor_t queue;
  NwkDataConfState_t state;
} NwkDataConf_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the data request component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetDataConf(void);

/**************************************************************************//**
  \brief Main task handler of the data request component.
 ******************************************************************************/
NWK_PRIVATE void nwkDataConfTaskHandler(void);

/**************************************************************************//**
  \brief Confirmation of data transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] status - network status of data transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkConfirmDataTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

/******************************************************************************
  \brief nwkDataReq idle checking.

  \return true, if nwkDataReq performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkDataReqIsIdle(void);

#endif /* _NWK_DATA_REQ_H */
/** eof nwkDataReq.h */

