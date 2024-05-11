/*******************************************************************************
  APS DataManager Header File

  Company
    Microchip Technology Inc.

  File Name
    apsDataManager.h

  Summary
    APS Data Manager header file.

  Description
    This header file handles the APS data manager functionalities.
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
#ifndef _APS_DATAMANAGER_H
#define _APS_DATAMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysEndian.h>
#include <aps.h>
#include <nwk.h>
#include <appTimer.h>
#include <private/apsFrames.h>
#include <private/apsMemoryManager.h>
#include <apsCommandReq.h>
#ifdef _SECURITY_
#include <private/apsSmSsp.h>
#endif

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _ApsFragmentationState_t
{
  APS_FRAG_WAITING_BLOCK_0,
  APS_FRAG_WAITING_NEXT_BLOCK,
  APS_FRAG_SENDING_ACK,
  APS_FRAG_SENDING_LAST_ACK
} ApsFragmentationState_t;

typedef enum _ApsTransmittedDataHandlerState_t
{
  START_DATA_HANDLING_STATE,
  DATA_DECRYPTION_STATE,
  SEND_DATA_TO_BOUND_DEVICES_STATE,
  FINISH_DATA_HANDLING_STATE
} ApsTransmittedDataHandlerState_t;

/******************************************************************************
                             External variables section
******************************************************************************/
extern AIB_t csAIB;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Make a reset of APS Data Manager
  Parameters: fullReset - reset all internal variables of APS-layer or not.
  Returns:    None
*****************************************************************************/
APS_PRIVATE void apsResetDataManager(const bool fullReset);


/*****************************************************************************
  APS Stop Event Handler
  Parameters: options - options field APS_StopReq value
  Returns:    None
******************************************************************************/
APS_PRIVATE void apsStopDataManager(void);

/*****************************************************************************
  APS Data Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
APS_PRIVATE void apsDataTaskHandler(void);

/*****************************************************************************
  APS Data Manager apsCounter get function
  Parameters: None
  Returns: apsCounter value
*****************************************************************************/
APS_PRIVATE uint8_t apsGetApsCounter(void);

APS_PRIVATE void apsMakeNwkDataResp(NWK_DataInd_t *ind);

APS_PRIVATE void apsDmHotReset(void);

/**************************************************************************//***
  \brief  Further processing of frame which have been indicated from NWK,
          passed initial checkings and optionally was decrypted.

  \param  nwkInd - NLDE-DATA.indication primitive pointer.
          securityStatus - securityStatus field value should be used in
          APS_DataInd primitive.
  \return true -  if the NWK Data Response needs to be executed for this
          indication, false - in other case.
*******************************************************************************/
#ifndef _SECURITY_
APS_PRIVATE bool apsContinueNwkDataIndProcessing(NWK_DataInd_t *nwkDataInd, APS_Status_t securityStatus);
#else
APS_PRIVATE bool apsContinueNwkDataIndProcessing(NWK_DataInd_t *nwkDataInd, ApsSecurityStatusDescriptor_t securityStatus);
#endif //#ifndef _SECURITY_

/*****************************************************************************
  APSDE-DATA.request with Short Addressing Mode process function
  Parameters: apsDataReq - APS_DataReq will be process
              nwkDataReqMem - buffer for NWK_DataReq
  Returns: APS_Status_t - status of operation
*****************************************************************************/
APS_PRIVATE APS_Status_t apsProcessShortAddrModeDataReq(APS_DataReq_t *apsDataReq,
  ApsDataBuffer_t *buffer);

/*****************************************************************************
  \brief Prepare and call NLDE-DATA.request primitive.

  \param[in] req - pointer to NLDE-DATA.request's parameters.
  \return None.
 *****************************************************************************/
APS_PRIVATE void apsSendNwkDataReq(NWK_DataReq_t *req);

/*****************************************************************************
  \brief Main APS Handler of NLDE-DATA.confirm.

  \param[in] conf - pointer to NLDE-DATA.confirm's parameters.
  \return None.
 *****************************************************************************/
APS_PRIVATE void apsDataManagerNwkDataConf(NWK_DataConf_t *conf);

/**************************************************************************//**
  \brief Recalculates transmission timeouts.

  \param transmission radius
  \return APS Ack timeout
 ******************************************************************************/
APS_PRIVATE uint32_t apsCalculateApsAckTimeout(uint8_t radius);

#if defined _BINDING_
/**************************************************************************//**
  \brief Address resolving callback.
  \param[in] conf - confirm pointer.
  \return None.
 ******************************************************************************/
void bindDataReqAddrResolvingConf(ZDO_ResolveAddrConf_t *conf);
#endif /* _BINDING_ */

#if defined _SECURITY_ && defined _LINK_SECURITY_
/*************************************************************************//**
  \brief Frame encryption is finished

  \param buffer - buffer wich was encrypted
  \param status - status of operation
  \return none
*****************************************************************************/
APS_PRIVATE void apsEncryptDataFrameConf(ApsDataBuffer_t *buffer, uint8_t* pdu,
   uint8_t pduLength, ApsSspeStatus_t status);

/*****************************************************************************
  Indicates that sent frame which was previously encrypted is decrypted.
  Parameters: buffer - APS memory buffer pointer.
  Returns: None
*****************************************************************************/
APS_PRIVATE void apsDecryptSentFrameConf(ApsDataBuffer_t *buffer);

#endif /* _SECURITY_ and _LINK_SECURITY_ */

/*************************************************************************//**
  \brief Constructs and sends APS acknowledgement.

  \param nwkDataInd - NLDE-DATA.indication primitive pointer.
         securityStatus - securty type to be used to generate ACK.
  \return true if ACK has been sent, false - otherwise.
*****************************************************************************/
bool apsConstructAndSendAck(NWK_DataInd_t *nwkDataInd, APS_Status_t securityStatus);

#ifdef _SECURITY_
bool apsCommandFrameIndicationHandler(NWK_DataInd_t *nwkDataInd, ApsSecurityStatusDescriptor_t securityStatus);
#endif

#endif  //#ifndef _APSDATAMANAGER_H
//eof apsDataManager.h

