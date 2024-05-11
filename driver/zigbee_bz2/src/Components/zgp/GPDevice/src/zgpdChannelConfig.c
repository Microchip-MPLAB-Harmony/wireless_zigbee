/*******************************************************************************
  Zigbee green power channel config Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdChannelConfig.c

  Summary:
    This file contains the implementation of zgpd channel configuration procedure.

  Description:
    This file contains the implementation of zgpd channel configuration procedure.
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

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdChannelConfig.h>
#include <zgp/GPDevice/include/zgpdMemAccess.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySet.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#include <zgp/include/zgpDbg.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include/macHwdZgpCommon.h>
/******************************************************************************
                    Defines section.
******************************************************************************/
#define ZGP_CHREQ_SECOND_CH_POS    4
/******************************************************************************
                    Globals
******************************************************************************/
/* Device sleeps in between successive calls */
HAL_AppTimer_t channelConfigTimer;
/* Number of channel request sent */
static uint8_t channelReqCount = 0;
/******************************************************************************
                    Prototypes section.
******************************************************************************/
static void zgpBuildAndSendChannelReq(void);
static void zgpChannelReqTxConfirm(MAC_DataConf_t *confirm);
static void zgpBuildChannelReqHeader(void);
static void zgpBuildChannelReqPayload(uint8_t *msduLength, uint8_t *payload);
static void zgpChannelReqTimeout(void);
static bool zgpMoveToNextChannel(void);
static void zgpChannelConfigWaitTimeout(void);
/******************************************************************************
                    Implementation section
******************************************************************************/
/******************************************************************************
  \brief    This will initiate the channel request command
  \param    firstRxChannel - Gpd will open rxWindow in this channel after one or more 
                             channel requests
  \param    secondRxChannel - Gpd will open rxWindow in this channel after firstRxChannel
                             between the two rxWindows, there can be channel requests
  \param    ZGP_ChannelReqConf - commissioning confirmation callback
  \param    confirm - confirmation status
  \return   ZGP_Status_t.
******************************************************************************/
ZGP_Status_t ZGP_ChannelReq(ZGP_ChannelReq_t *zgpChannelReq)
{
  if (NULL == zgpChannelReq->ZGP_ChannelReqConf)
  {
    return(ZGP_INVALID_PARAMETER);
  }
  zgpChannelReq->service.requestId = ZGP_CHANNEL_REQ_ID;
  zgpChannelReq->service.presenceInQueue = zgpPutReqInQueue((void *)zgpChannelReq);
  
  // if TX queue is full, return error status, post the corresponding task otherwise
  if(zgpChannelReq->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_CHANNEL_REQ_ID);
  }
  else
  {
    return(ZGP_TX_QUEUE_FULL);
  }
  return ZGP_SUCCESS_STATUS;
}
/******************************************************************************
  \brief    Handles the channel request and config procedure. Two Channel requests
            are sent in each channel, device opens rxWindow in every second request 
            and waits for channel config. Once the operating channel is fixed, 
            commissioning shall happen.
  \param    none.
  \return   none.
******************************************************************************/
void zgpChannelReqHandler(void)
{
  ZGP_Service_t *service = (ZGP_Service_t *)zgpGetReqParams();
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();

  if (ZGP_CHANNEL_REQ_ID == service->requestId)
  {
    MACHWDZGP_ResetRxAfterTx();
    if (sCommDone != getCommissioningState())
    {
      // start with the first channel enabled in channel mask
      zgpGetStackParams()->Channel = channelReq->firstRxChannel;
      if(true != zgpMoveToNextChannel())
      {
         zgpGetStackParams()->Channel = ZGP_CHANNEL_START - 1;
         zgpMoveToNextChannel();
      }
    }
    else
    {
      channelReq->firstRxChannel = zgpGetStackParams()->Channel;
      channelReq->secondRxChannel = zgpGetStackParams()->Channel;
    }
    setOneShotTimer(channelConfigTimer, zgpChannelReqTimeout, CS_ZGP_CHANNEL_REQUEST_DELAY);
    HAL_StartAppTimer(&channelConfigTimer);
    zgpBuildAndSendChannelReq();
  }
}
/******************************************************************************
  \brief   build and send channel request
  \param   confirm - confirmation status from MAC
  \return  none.
******************************************************************************/
static void zgpBuildAndSendChannelReq(void)
{
  ZGP_Mem_t* zgpReqMem = zgpGetMem();
  // channel request confirmation callback
  zgpReqMem->macReq.data.MAC_DataConf = zgpChannelReqTxConfirm;
  // fill parameters of Mac data request 
  zgpSetMacDataReqParams(&zgpReqMem->macReq.data, ZGP_CHANNEL_REQUEST_CMD_ID);
  //Fill the channel request header
  zgpBuildChannelReqHeader();
  // build payload for channel Request command
  zgpBuildChannelReqPayload(&zgpReqMem->macReq.data.msduLength, &zgpReqMem->zgpPacket.payload[0]);
}
/******************************************************************************
  \brief   send channel request confirmation to application
  \param   confirm - confirmation status from MAC
  \return  none.
******************************************************************************/
static void zgpChannelReqTxConfirm(MAC_DataConf_t *confirm)
{
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();
  uint8_t zgpChannel = zgpGetStackParams()->Channel;
  uint32_t channelMask;
  channelReqCount++;
  if(confirm->status == MAC_SUCCESS_STATUS)
  {
    // after first channel req rxWindow is opened for further requests
    if(channelReqCount > 1)
    {
      setChannelConfigState(sChannelConfigWaiting);
    }
    else
    {
      setChannelConfigState(sChannelReqTxDone);
    }
  }
  if(channelReqCount < CS_ZGP_NUM_OF_CHANNEL_REQ_CMD && 
     (zgpGetStackParams()->Channel == channelReq->firstRxChannel || zgpGetStackParams()->Channel == channelReq->secondRxChannel))
  {
    // Start a timer for next channel Request in the same channel
    setOneShotTimer(channelConfigTimer, zgpChannelReqTimeout, CS_ZGP_CHANNEL_REQUEST_DELAY);
    HAL_StartAppTimer(&channelConfigTimer);
  }
  else
  {
    channelReqCount = 0;
    CS_ReadParameter(CS_CHANNEL_MASK_ID, &channelMask);
    //move to next channel
    if(zgpGetStackParams()->Channel == channelReq->firstRxChannel)
    {
     // last transmitted channel is rx channel
     if(getChannelConfigState()!= sChannelConfigDone)
     {
        // Start a timer to check whether channel config is received
        setOneShotTimer(channelConfigTimer, zgpChannelConfigWaitTimeout, ZGP_CHANNEL_CONFIG_WAIT_DELAY);
     }
    }
    else if(true == findNextSupportedChannel(&zgpChannel,channelMask))
    {
      if(channelReq->firstRxChannel >= zgpChannel)
      {
        // Start a timer to send channel Request in next channel
        setOneShotTimer(channelConfigTimer, zgpChannelReqTimeout, ZGP_CHREQ_NXT_CHANNEL_DELAY);
      }
    }
    else
    {
      zgpChannel = ZGP_CHANNEL_START - 1;
      findNextSupportedChannel(&zgpChannel,channelMask);
      if(channelReq->firstRxChannel >= zgpChannel)
      {
        zgpGetStackParams()->Channel = zgpChannel - 1;
        // Start a timer to send channel Request in next channel
        setOneShotTimer(channelConfigTimer, zgpChannelReqTimeout, ZGP_CHREQ_NXT_CHANNEL_DELAY);
      }
    }
    HAL_StartAppTimer(&channelConfigTimer);
  }
}
/******************************************************************************
  \brief   This will fill the command header for channel request
  \param   cmd - command ID
  \return  none.
******************************************************************************/
static void zgpBuildChannelReqHeader(void)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  uint8_t *currFieldPtr = zgp_Mem->zgpPacket.payload;
  ZGP_NwkFrameControl_t nwkFcf = {0}; 

  // Construct the nwk fcf and ext nwk fcf pour les trames de type
  // commissioning, that is to say the GPD is at least not in autocommissioning mode
  nwkFcf.frametype = ZGP_FRAME_MAINTENANCE;
  nwkFcf.zigbeeProtVersion = GREENPOWER_PROTOCOL_VERSION;

  if (nwkFcf.frametype == ZGP_FRAME_MAINTENANCE)
  {
    // gpd is does not do autocommissioning, and it sends maintenance frame 
    // with rxWindow after transmission
    if (MACHWDZGP_GetRxAfterTx())
    {
      nwkFcf.autoCommissioning = false;
    }
    else
    {
      // gpd is not autocommissiong, and it sends maintenance frame 
      // without a Rx Windows after it
      nwkFcf.autoCommissioning = true;
    }
  }

  // fill nwk frame control field
  currFieldPtr -= ZGP_NWK_FCF_LENGTH;
  *currFieldPtr = *((uint8_t*)&(nwkFcf));
  zgp_Mem->macReq.data.msduLength += ZGP_NWK_FCF_LENGTH;

  zgp_Mem->macReq.data.msdu = currFieldPtr;  
}
/******************************************************************************
  \brief    This will fill the ChannelReq payload
  \param    msduLength - length of command payload
  \param    payload - pointer to command payload
  \return  none.
******************************************************************************/
static void zgpBuildChannelReqPayload(uint8_t *msduLength, uint8_t *payload)
{
  uint8_t firstRxChannel = 0;
  uint8_t secondRxChannel = 0;
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();
  *payload = ZGP_CHANNEL_REQUEST_CMD_ID;

  if(channelReqCount == CS_ZGP_NUM_OF_CHANNEL_REQ_CMD - 1)
  {
    if(channelReq->firstRxChannel == zgpGetStackParams()->Channel)
    {
      firstRxChannel = channelReq->secondRxChannel - ZGP_CHANNEL_START;
      secondRxChannel = channelReq->firstRxChannel - ZGP_CHANNEL_START;
    }
    else if(channelReq->secondRxChannel == zgpGetStackParams()->Channel)
    {
      firstRxChannel= channelReq->firstRxChannel - ZGP_CHANNEL_START; 
      secondRxChannel = channelReq->secondRxChannel - ZGP_CHANNEL_START;
    }
  }
  else
  {
     if(channelReq->firstRxChannel == zgpGetStackParams()->Channel)  
     {
       firstRxChannel = channelReq->firstRxChannel - ZGP_CHANNEL_START;
       secondRxChannel = channelReq->secondRxChannel - ZGP_CHANNEL_START;
     }
     else if(channelReq->secondRxChannel == zgpGetStackParams()->Channel)
     {
       firstRxChannel = channelReq->secondRxChannel - ZGP_CHANNEL_START;
       secondRxChannel = channelReq->firstRxChannel - ZGP_CHANNEL_START;
     }
     else
     {
       firstRxChannel = channelReq->secondRxChannel - ZGP_CHANNEL_START;
       secondRxChannel = channelReq->firstRxChannel - ZGP_CHANNEL_START;
     }
  }

  *(payload + ZGP_CHANNELREQ_CMD_PAYLOAD_START) = firstRxChannel | (secondRxChannel << ZGP_CHREQ_SECOND_CH_POS);
  *msduLength += ZGP_CHANNELREQ_PAYLOAD_LEN;
  setChannelConfigState(sChannelReqTx);
  zgpTxReq(&zgpGetMem()->macReq.data);
}
/******************************************************************************
  \brief    handles channel request timeout
  \param    none.
  \return   none.
******************************************************************************/
static void zgpChannelReqTimeout(void)
{
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();
  //Initiate channel req only if channel config was not received in timeout period
  if(getChannelConfigState() == sChannelConfigDone)
  {
    return;
  }
  // if no of channel request is 0 and channnelreq timer is initiated
  // move to next channel
  if(channelReqCount == 0)
  {
    MACHWDZGP_ResetRxAfterTx();
    // if there is no new channel to move next
    if(true != zgpMoveToNextChannel())
      return;
  }
  else if(channelReqCount >= 1)
  {
    if(getChannelConfigState() == sChannelReqTxDone || 
       getChannelConfigState() == sChannelConfigWaiting)
    {
      if(zgpGetStackParams()->Channel == channelReq->firstRxChannel ||
         zgpGetStackParams()->Channel == channelReq->secondRxChannel)
      {
        // after first channel request rx window shall be present after tx
        MACHWDZGP_SetRxAfterTx();
      }
      else
      {
        MACHWDZGP_ResetRxAfterTx();  
      }
    }
  }
  zgpBuildAndSendChannelReq();
}
/******************************************************************************
  \brief    handles channel config wait timeout
  \param    none.
  \return   none.
******************************************************************************/
static void zgpChannelConfigWaitTimeout(void)
{
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();
  if(getChannelConfigState()!= sChannelConfigDone)
  {
    setChannelConfigState(sChannelConfigIdle);
    channelReq->confirm.status = ZGP_NO_CHANNEL_CONFIG_REPLY;
    zgpSendConfToUpperLayer((void *)channelReq);
  }
}
/******************************************************************************
  \brief    handles received channel config command
  \param    none.
  \return   none.
******************************************************************************/
void zgpChannelConfigInd(ZGP_DataInd_t *zgpChannelConfigInd)
{
  ZGP_ChannelReq_t *channelReq = (ZGP_ChannelReq_t *)zgpGetReqParams();
  PHY_SetReq_t  phySetReq;
  uint8_t zgpConfigChannel = (zgpChannelConfigInd->zgpAsdu[1] & ZGP_CHANNEL_CONFIG_OPERCH_MASK) + ZGP_CHANNEL_START;
  if(zgpConfigChannel >= ZGP_CHANNEL_START &&
     zgpConfigChannel <= ZGP_CHANNEL_END)
  {
    HAL_StopAppTimer(&channelConfigTimer);
    MACHWDZGP_SetTrxOffState();
    channelReqCount = 0;
    zgpGetStackParams()->Channel = zgpConfigChannel;
    phySetReq.attr.phyPib.channel = zgpConfigChannel;
    phySetReq.id = PHY_PIB_CURRENT_CHANNEL_ID;
    PHY_SetReq(&phySetReq);
    setChannelConfigState(sChannelConfigDone);
    channelReq->confirm.status = ZGP_SUCCESS_STATUS;
    zgpSendConfToUpperLayer((void *)channelReq);
  }
}
/**************************************************************************//**
  \brief move to next channel enabled in the channelMask from
         the current channel in stackparams.
  \param none.
  \return true  - moved to next channel in channel mask
          false - next channel is not enabled in channel mask
******************************************************************************/
static bool zgpMoveToNextChannel(void)
{
  PHY_SetReq_t  phySetReq;
  uint32_t channelMask;
  CS_ReadParameter(CS_CHANNEL_MASK_ID, &channelMask);
  if(true == findNextSupportedChannel(&zgpGetStackParams()->Channel,channelMask))
  {
    phySetReq.attr.phyPib.channel = zgpGetStackParams()->Channel;
    phySetReq.id = PHY_PIB_CURRENT_CHANNEL_ID;
    PHY_SetReq(&phySetReq);
    return true;
  }
  else
    return false;
}
//eof zgpChannelConfig.c
