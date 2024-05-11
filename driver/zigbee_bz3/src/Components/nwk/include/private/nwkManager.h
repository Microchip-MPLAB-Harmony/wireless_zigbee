/*******************************************************************************
  NWK Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkManager.h

  Summary:
    This file provides the Interface of the network manager.

  Description:
    This file provides the Interface of the network manager.
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

#if !defined _NWK_MANAGER_H
#define _NWK_MANAGER_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <appFramework.h>
#include <mac.h>
#include <nldeData.h>
#include <private/nwkFrame.h>

/******************************************************************************
                              Define(s) section
 ******************************************************************************/
#define NWK_UPDATE_TX_PARAMETERS \
  {NWK_TX_DELAY_BROADCAST, nwkPrepareUpdateTx, nwkConfirmUpdateTx, true}

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Internal states of the report command component */
typedef enum _NwkManagerState_t
{
  NWK_MANAGER_IDLE_STATE = 0xFB,
  NWK_MANAGER_FIRST_STATE = 0x83,
  NWK_MANAGER_MAC_SCAN_STATE = NWK_MANAGER_FIRST_STATE,
  NWK_MANAGER_PREPARE_MAC_DATA_STATE = 0x84,
  NWK_MANAGER_SEND_UPDATE_CMD_STATE = 0x85,
  NWK_MANAGER_SET_PAN_ID_STATE = 0x86,
  NWK_MANAGER_LAST_STATE
} NwkManagerState_t;

/** Internal variables of the network manager component. */
typedef struct _NwkManager_t
{
  /** Finite-state machine */
  NwkManagerState_t state;
  PanId_t newPanId; /* New non conflicted panId. */
  /* Range non conflicted panId from newPanId field. */
  PanId_t nonConflictRange;
  /** MLME-SCAN request primitive's parameters. */
  MAC_ScanReq_t macScan;
} NwkManager_t;

/******************************************************************************
                                Prototypes section
 ******************************************************************************/
#if defined _RESOLVE_PANID_CONFLICT_ && defined _NETWORK_MANAGER_
/**************************************************************************//**
  \brief Processing a conflict of panId by the network manager.
 ******************************************************************************/
NWK_PRIVATE void nwkDetectPanIdConflictByNwkManager(void);

/**************************************************************************//**
  \brief Reset the report command component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetNetworkManager(void);

/**************************************************************************//**
  \brief Action when a report command is received.

  \param[in] payload - pointer to NPDU of NWK report command.
  \param[in] header  - nwk header.
  \param[in] parse   - parsed header fields.
  \return 'true' - continue command processing otherwise 'false'.
******************************************************************************/
NWK_PRIVATE bool nwkReportFrameInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Prepare header and payload of the update command.

  \param[in] outPkt - pointer to output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareUpdateTx(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Confirmation of the update command transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] status - network status of the update command transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkConfirmUpdateTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

/******************************************************************************
  \brief nwkNetworkManager idle checking.

  \return true, if nwkNetworkManager performs no activity, false - otherwise.
 ******************************************************************************/
NWK_PRIVATE bool nwkNetworkManagerIsIdle(void);

#else /* _RESOLVE_PANID_CONFLICT_ and _NETWORK_MANAGER_ */

/* Interface of the network manager is disabled. */
INLINE void nwkDetectPanIdConflictByNwkManager(void) {}
#define nwkResetNetworkManager() (void)0
#define nwkReportFrameInd NULL
#define nwkPrepareUpdateTx NULL
#define nwkConfirmUpdateTx NULL
#define nwkNetworkManagerIsIdle NULL

#endif /* _RESOLVE_PANID_CONFLICT_ and _NETWORK_MANAGER_ */
#endif /* _NWK_MANAGER_H */
/* eof nwkManager.h */

