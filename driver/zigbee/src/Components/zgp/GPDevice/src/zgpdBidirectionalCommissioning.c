/*******************************************************************************
  Zigbee green power device bidirectional commissioning Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdBidirectionalCommissioning.c

  Summary:
    This file contains the zgpd bidirectional commissioning core functionalities.

  Description:
    This file contains the zgpd bidirectional commissioning core functionalities.
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
#include <zgp/GPDevice/include/zgpdMemAccess.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#include <zgp/GPDevice/include/zgpdCommissioning.h>
#include <zgp/GPDevice/include/zgpdCommissioningHandler.h>
#include <zgp/GPDevice/include/zgpdIb.h>
#include <zgp/include/zgpDbg.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySet.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h>
#include <systemenvironment/include/sysIdleHandler.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include/macHwdZgpCommon.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define ZGP_COMM_SUCCESS_GPDF_RETRY_TIME_WINDOW 100u

#if (CS_ZGP_COMMISSIONING_AUTOMATION == true)
/******************************************************************************
                    Prototypes
******************************************************************************/
/******************************************************************************
  \brief    initiates the commissioning request command
  \param    none.
  \return   none.
******************************************************************************/
static void zgpBiCommCommandTx(void);

/******************************************************************************
  \brief    handles commissioning confirmation
  \param    none.
  \return   none.
******************************************************************************/
static void zgpCommissionCmdConf(MAC_DataConf_t *confirm);

/******************************************************************************
  \brief    initiates success GPDF
  \param    conf - confirmation status
  \return   none.
******************************************************************************/
static void zgpBiCommSuccessTimeout(void);

/******************************************************************************
  \brief    processes commissioning reply
  \param    zgpInd - zgp indication
  \return   none.
******************************************************************************/
static void zgpCommissioningInd(ZGP_DataInd_t *zgpInd);

/******************************************************************************
  \brief    parse the commissioning reply
  \param    none.
  \return   none.
******************************************************************************/
static void zgpCommReplyParse(void);

/******************************************************************************
  \brief    send Decommissioning confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpDecommissioningConfirm(MAC_DataConf_t *confirm);

/******************************************************************************
  \brief    resets counters and timers
  \param    none.
  \return   none.
******************************************************************************/
static void zgpResetCommissioning(void);

/******************************************************************************
  \brief    handles commissioning command timeout
  \param    none.
  \return   none.
******************************************************************************/
static void zgpBiCommCommandTimeout(void);

/******************************************************************************
  \brief    include the necessary info for decryption
  \param    pdu - the key that needs to be decrypted.
  \return   none.
******************************************************************************/
static void zgpFillDecryptKeyReq(uint8_t *pdu);

/******************************************************************************
  \brief    confirmation callbeck for ssp decryption
  \param    conf - confirmation status.
  \return   none.
******************************************************************************/
static void SSP_ZgpDecryptFrameConf(SSP_ZgpDecryptFrameConf_t *conf);

/******************************************************************************
  \brief    send Success GPDF confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpSuccessGpdfConfirm(MAC_DataConf_t *confirm);


/******************************************************************************
                    Globals
******************************************************************************/
/* Device sleeps in between successive calls */
HAL_AppTimer_t bidirectionalCommTimer;

/* Previous state of commissioning process */
zgpCommissionState_t bidirectionalCommPrevState = sCommIdle;

/* Number of commissioning request sent */
static uint8_t commissioningReqCount = 0;

/* Indicates whether confirmation for commissioning command is received or not */
static bool gotCommCmdConfirm = false;

/* NWK PanID */
static uint16_t panID = 0xFFFF;

/* Key that needs to be decrypted */
static uint8_t *decKey;

/* Sink's key type */
static uint8_t keyType;

/* Is security parameters needs to be updated in PDS? */
static bool isPdsSecUpdateRequired;

/******************************************************************************
  \brief    Handles the bidirectional commissioning request from application.
              Will send commissioning command in specified channels, till find
              the sink or last channel. Once get commissioning reply it send
              Success GPDF and completes commissioning. Commissioning states
              will be handled internally.
  \param    none.
  \return   none.
******************************************************************************/
void zgpBiCommissioningHandler(void)
{
  ZGP_SubscribeCommissioning(zgpCommissioningInd);

  if (sCommIdle != getCommissioningState())
  {
    ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();

    commissioningReqCount = 0;
    ZGP_UnsubscribeCommissioning();
    commissioningReq->confirm.status = ZGP_BAD_STATE;
    zgpSendConfToUpperLayer((void *)commissioningReq);
    return;
  }

  // choose the channel from channel config
  if(sCommIdle == getCommissioningState() &&
      sChannelConfigDone == getChannelConfigState())
  {
#if (defined(_ZGPD_SPECIFIC_) && defined(_SLEEP_WHEN_IDLE_))
    SYS_DisableSleepWhenIdle();
#endif /* _ENDDEVICE_ && _SLEEP_WHEN_IDLE_ */
    // rx after tx is disabled for first Bidirectional commissioning command
    MACHWDZGP_ResetRxAfterTx();
    // Initiate timer for next commissioning command
    setOneShotTimer(bidirectionalCommTimer, zgpBiCommCommandTimeout, CS_ZGP_COMMISSIONING_COMMAND_DELAY);
    HAL_StartAppTimer(&bidirectionalCommTimer);
    // initiate commissioning command
    zgpBiCommCommandTx();
    }
    else
    {
      ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
      setCommissioningState(sCommIdle);
      commissioningReqCount = 0;
      ZGP_UnsubscribeCommissioning();
      commissioningReq->confirm.status = ZGP_NO_COMMISSIONING_REPLY;
      zgpSendConfToUpperLayer((void *)commissioningReq);
      return;
    }
}

/******************************************************************************
  \brief    automated decommissioning handler
  \param    none.
  \return   none.
******************************************************************************/
void zgpDecommissioningHandler(void)
{
  if (sCommDone != getCommissioningState())
  {
    ZGP_DecommissioningReq_t *decommissioningReq = (ZGP_DecommissioningReq_t *)zgpGetReqParams();
    decommissioningReq->confirm.status = ZGP_BAD_STATE;
    zgpSendConfToUpperLayer(decommissioningReq);
    return;
  }
  MACHWDZGP_ResetRxAfterTx();
  zgpSendDecommissioning(zgpDecommissioningConfirm);
}

/******************************************************************************
  \brief    send Decommissioning confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpDecommissioningConfirm(MAC_DataConf_t *confirm)
{
  ZGP_DecommissioningReq_t *decommissioningReq = (ZGP_DecommissioningReq_t *)zgpGetReqParams();
  ZB_CS_SYS_IBData_t zgbIBdata = {0};

  if (MAC_SUCCESS_STATUS == confirm->status)
  {
    ZGP_UnsubscribeCommissioning();
#ifdef _COMMISSIONING_
    setFactoryNew(true);
#endif
    csSetToDefault(&zgbIBdata);
  }

  decommissioningReq->confirm.status = confirm->status;
  zgpSendConfToUpperLayer(decommissioningReq);
}

/******************************************************************************
  \brief    processes commissioning reply
  \param    zgpInd - zgp indication
  \return   none.
******************************************************************************/
static void zgpCommissioningInd(ZGP_DataInd_t *zgpInd)
{

  if (sReplyWaiting == getCommissioningState() || sCommCommandTx == getCommissioningState())
  {
    MACHWDZGP_SetTrxOffState();
    HAL_StopRtimer();
    HAL_StopAppTimer(&bidirectionalCommTimer);
    setOneShotTimer(bidirectionalCommTimer, zgpBiCommSuccessTimeout, CS_ZGP_COMM_SUCCESS_GPDF_WAIT_TIME);
    HAL_StartAppTimer(&bidirectionalCommTimer);
    setCommissioningState(sCommReplyRx);
    zgpCommReplyParse();
#if (defined(_ZGPD_SPECIFIC_) && defined(_SLEEP_WHEN_IDLE_))
    SYS_EnableSleepWhenIdle();
#endif /* _ENDDEVICE_ && _SLEEP_WHEN_IDLE_ */
  }

  //To make Compiler happy
  zgpInd = zgpInd;
}

/******************************************************************************
  \brief    handles commissioning command timeout
  \param    none.
  \return   none.
******************************************************************************/
static void zgpBiCommCommandTimeout(void)
{
#if (defined(_ZGPD_SPECIFIC_) && defined(_SLEEP_WHEN_IDLE_))
  SYS_DisableSleepWhenIdle();
#endif /* _ENDDEVICE_ && _SLEEP_WHEN_IDLE_ */
  if (commissioningReqCount < CS_ZGP_NUM_OF_COMMISSIONING_CMD)
  {
    if (true == gotCommCmdConfirm)
    {
      // rx after tx is enabled for Bidirectional commissioning commands, other than first one
      MACHWDZGP_SetRxAfterTx();
      // Initiate timer for next commissioning command
      setOneShotTimer(bidirectionalCommTimer, zgpBiCommCommandTimeout, CS_ZGP_COMMISSIONING_COMMAND_DELAY);
      HAL_StartAppTimer(&bidirectionalCommTimer);
      // initiate commissioning command
      zgpBiCommCommandTx();
    }
    else
    {
      ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
      zgpResetCommissioning();
      gotCommCmdConfirm = false;
      MACHWDZGP_ResetRxAfterTx();
      commissioningReq->confirm.status = ZGP_COMMISSIONING_TIMEOUT;
      zgpSendConfToUpperLayer((void *)commissioningReq);
    }
  }
  else
  {
    if (sCommCommandTx == getCommissioningState() || (sReplyWaiting == getCommissioningState()))
    {
      HAL_StopAppTimer(&bidirectionalCommTimer);
      MACHWDZGP_ResetRxAfterTx();
      setCommissioningState(sCommIdle);
      commissioningReqCount = 0;
      //zgpBiCommissioningHandler();
    }
  }
}

/******************************************************************************
  \brief    initiates the commissioning request command
  \param    none.
  \return   none.
******************************************************************************/
static void zgpBiCommCommandTx(void)
{
  if (commissioningReqCount < CS_ZGP_NUM_OF_COMMISSIONING_CMD)
  {
    // transmit state
    setCommissioningState(sCommCommandTx);
    commissioningReqCount++;
    gotCommCmdConfirm = false;
    //Send commissioning command out
    zgpSendCommissioningReq(zgpCommissionCmdConf);
  }
}

/******************************************************************************
  \brief    handles commissioning confirmation
  \param    none.
  \return   none.
******************************************************************************/
static void zgpCommissionCmdConf(MAC_DataConf_t *confirm)
{
  gotCommCmdConfirm = true;

  if (commissioningReqCount < CS_ZGP_NUM_OF_COMMISSIONING_CMD)
  {
#if (defined(_ZGPD_SPECIFIC_) && defined(_SLEEP_WHEN_IDLE_))
    SYS_EnableSleepWhenIdle();
#endif /* _ENDDEVICE_ && _SLEEP_WHEN_IDLE_ */
    setCommissioningState(sReplyWaiting);
  }
  else
  {
    if (sCommCommandTx == getCommissioningState() || (sReplyWaiting == getCommissioningState()))
    {
      commissioningReqCount = 0;
      HAL_StopAppTimer(&bidirectionalCommTimer);

      /* Initiate timer to send out success GPDF. In timeout, again check the
          state. If commissioning reply is received and processed then the success GPDF
          will be sent*/
      setOneShotTimer(bidirectionalCommTimer, zgpBiCommSuccessTimeout, CS_ZGP_COMM_SUCCESS_TX_DELAY);
      HAL_StartAppTimer(&bidirectionalCommTimer);
    }
  }
  //To make Compiler happy
  confirm = confirm;
}


/******************************************************************************
  \brief    handles success GPDF timeout
  \param    none.
  \return   none.
******************************************************************************/
static void zgpBiCommSuccessTimeout(void)
{
  ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
  if (sCommReplyOk == getCommissioningState())
  {
    zgpSendSuccessGpdf(zgpSuccessGpdfConfirm);
  }
  else if (sCommReplyRx == getCommissioningState())
  {
    /* wait for another 25 ms to conclude on the commissioning reply */
    setOneShotTimer(bidirectionalCommTimer, zgpBiCommSuccessTimeout, 25);
    HAL_StartAppTimer(&bidirectionalCommTimer);
  }
  else
  {
    HAL_StopAppTimer(&bidirectionalCommTimer);
    setCommissioningState(sCommIdle);
    commissioningReqCount = 0;
    ZGP_UnsubscribeCommissioning();
    commissioningReq->confirm.status = ZGP_NO_COMMISSIONING_REPLY;
    zgpSendConfToUpperLayer((void *)commissioningReq);
    return;
  }
}

/******************************************************************************
  \brief    send Success GPDF confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpSuccessGpdfConfirm(MAC_DataConf_t *confirm)
{
  ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();

#if APP_ENABLE_CERTIFICATION_EXTENSION == 1
  static bool retryDone = false;
  if (!retryDone)
  {
    HAL_StopAppTimer(&bidirectionalCommTimer);
    setOneShotTimer(bidirectionalCommTimer, zgpBiCommSuccessTimeout, ZGP_COMM_SUCCESS_GPDF_RETRY_TIME_WINDOW);
    HAL_StartAppTimer(&bidirectionalCommTimer);
    retryDone = true;
    return;
  }
  retryDone = false;
#endif
  if (MAC_SUCCESS_STATUS == confirm->status)
  {
    setCommissioningState(sCommDone);
    isFactoryNew = false;
#ifdef _COMMISSIONING_
    if (true == isPdsSecUpdateRequired)
    {
      PDS_Store(ZGP_SECURITY_COMMISSIONING_MEM_ID);
    }
    else
      PDS_Store(ZGP_COMMISSIONING_MEM_ID);
#endif

    commissioningReqCount = 0;
    HAL_StopAppTimer(&bidirectionalCommTimer);
  }
  else
  {
    zgpResetCommissioning();
    return;
  }

  ZGP_UnsubscribeCommissioning();
  commissioningReq->confirm.status = confirm->status;
  zgpSendConfToUpperLayer((void *)commissioningReq);
#if (defined(_ZGPD_SPECIFIC_) && defined(_SLEEP_WHEN_IDLE_))
  SYS_EnableSleepWhenIdle();
#endif /* _ENDDEVICE_ && _SLEEP_WHEN_IDLE_ */
}
/******************************************************************************
  \brief    parse the commissioning reply
  \param    none.
  \return   none.
******************************************************************************/
static void zgpCommReplyParse(void)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  zgpDeviceParams_t *deviceParams = zgpGetDeviceParams();
  zgpdSecMaterialSet_t *zgpSecMaterial = zgpGetSecParams();
  uint8_t *pdu = (zgp_Mem->zgpDataIndParams.zgpAsdu + ZGP_COMM_REPLY_OPTIONS_START);

  ZgpCommissionReplyOptions_t commReplyOption = *(ZgpCommissionReplyOptions_t *)pdu;
  pdu += ZGP_COMM_REPLY_OPTIONS_LEN;

  if ((ZGP_SecLevel_t)commReplyOption.securityLevel !=  deviceParams->secLevel)
  {
    ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
    zgpResetCommissioning();
    commissioningReq->confirm.status = ZGP_SECURITY_LEVEL_NOT_MATCHED;
    zgpSendConfToUpperLayer((void *)commissioningReq);
    return;
  }


  if (commReplyOption.panIdPresent)
  {
    memcpy(&panID,pdu,sizeof(uint16_t));
    pdu += ZGP_COMM_REPLY_PANID_LEN;
    //PanID will be stored in PDS along with CommissioningState once Commissioning succeeds
//    isPdsStackUpdateRequired = true;
  }
#ifdef ZGP_SECURITY_ENABLE
  if (commReplyOption.GPDKeyPresent)
  {
    if(commReplyOption.GPDKeyEncryption)
    {
      if ((ZGP_SECURITY_LEVEL_0 < zgpGetDeviceParams()->secLevel) &&
          (zgpSecMaterial->secKey.gpLinkKeyIsSet))
      {
        decKey = pdu;
        keyType = commReplyOption.securityKeyType;
        zgpGetSecParams()->secKey.keyType = keyType;
        zgpFillDecryptKeyReq(zgp_Mem->zgpDataIndParams.zgpAsdu);
        return;
      }
      else
      {
        ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
        zgpResetCommissioning();
        commissioningReq->confirm.status = ZGP_COMMISSIONING_REPLY_FAILURE;
        zgpSendConfToUpperLayer((void *)commissioningReq);
        return;
      }
    }
    else //If key is not protected
    {
      //If key is valid then store it in IB and set the key type
      if (zgpIsValidKey(pdu))
      {
        if (zgpSetSecurityKey(pdu))
        {
          zgpGetSecParams()->secKey.keyIsSet = true;
          zgpGetSecParams()->secKey.keyType = commReplyOption.securityKeyType;
          zgpGetStackParams()->panId = panID;
          macenvSetPanId(panID);
          panID = ZGP_BROADCAST_PANID;
          commissioningReqCount = 0;
          setCommissioningState(sCommReplyOk);
          return;
        }
      }
      else
      {
        ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
        zgpResetCommissioning();
        commissioningReq->confirm.status = ZGP_COMMISSIONING_REPLY_FAILURE;
        zgpSendConfToUpperLayer((void *)commissioningReq);
        return;
      }
    }
  }
  else
#endif //#ifdef ZGP_SECURITY_ENABLE
  //If no key present
  {
    ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
#ifdef ZGP_SECURITY_ENABLE
    zgpdSecMaterialSet_t *zgpSecMaterial = zgpGetSecParams();
    uint8_t gpdKeyPresent = false;
#endif
    commissioningReqCount = 0;
    // OOB is already present and if no key present, it is accepted by the infrastructure device
    gpdKeyPresent = (zgpSecMaterial->secKey.keyIsSet && 
                                        zgpIsValidKey(zgpSecMaterial->secKey.key) && 
                                          zgpSecMaterial->secKey.keyType);
    if(true == gpdKeyPresent)
    {
      isPdsSecUpdateRequired = true;
      setCommissioningState(sCommReplyOk);
      zgpGetStackParams()->panId = panID;
      panID = ZGP_BROADCAST_PANID;
      return;      
    }
    else if (true == commissioningReq->keyReq)
    {
      ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
      zgpResetCommissioning();
      commissioningReq->confirm.status = ZGP_COMMISSIONING_REPLY_FAILURE;
      zgpSendConfToUpperLayer((void *)commissioningReq);
      return;
    }
  }
}

#ifdef ZGP_SECURITY_ENABLE
/******************************************************************************
  \brief    include the necessary info for decryption
  \param    pdu - the key that needs to be decrypted.
  \return   none.
******************************************************************************/
void zgpFillDecryptKeyReq(uint8_t *pdu)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  ZgpCommissionReplyOptions_t commReplyOption;
  
  zgp_Mem->zgpDecryptReq.key = zgpGetSecParams()->secKey.gpLinkKey;
  // key encryption
  zgp_Mem->zgpDecryptReq.securityLevel = 3;
  zgp_Mem->zgpDecryptReq.appId = zgpGetDeviceParams()->appId;
  zgp_Mem->zgpDecryptReq.srcID = zgpGetDeviceParams()->srcID;
  
  if (ZGP_SRC_APPID == zgp_Mem->zgpDecryptReq.appId)
  {
    zgpMakeIEEEAddrFromSrcAddr(&zgp_Mem->zgpDecryptReq.extAddr, &zgp_Mem->zgpDecryptReq.srcID, &zgp_Mem->zgpDecryptReq.srcID);
    //zgp_Mem->zgpDecryptReq.securityFrameCounter = zgp_Mem->zgpDecryptReq.srcID;
    zgp_Mem->zgpDecryptReq.securityFrameCounter = zgpGetSecParams()->outFrmCntr;
  }
  else if (ZGP_IEEE_ADDR_APPID == zgp_Mem->zgpDecryptReq.appId)
  {
    zgp_Mem->zgpDecryptReq.extAddr = zgpGetDeviceParams()->ieeeAddr;
    zgp_Mem->zgpDecryptReq.securityFrameCounter = zgpGetSecParams()->outFrmCntr;
  }
  pdu += ZGP_COMM_REPLY_CMD_ID_LEN;
  commReplyOption = *(ZgpCommissionReplyOptions_t *)pdu;
  if(commReplyOption.panIdPresent)
  {
    pdu += ZGP_COMM_REPLY_PANID_LEN;
  }
  // to accomodate header - not sure whether this memory can be used in this way
  // todo change the memory
  pdu = pdu + ZGP_COMM_PAYLOAD_OPTIONS_LEN - ZGP_COMM_KEY_HEADER_LEN;
  /*Header info. This will not transmit over-the-air.
  Refer ZGP spec: 095499r24 Section A.1.5.3.3.3 */
  if (ZGP_SRC_APPID == zgpGetDeviceParams()->appId)
  {
    memcpy(pdu, &zgpGetDeviceParams()->srcID, ZGP_COMM_KEY_HEADER_LEN);
  }
  else if (ZGP_IEEE_ADDR_APPID == zgpGetDeviceParams()->appId)
  {
    memcpy(pdu, &zgpGetDeviceParams()->ieeeAddr, ZGP_COMM_KEY_HEADER_LEN);
  }

  zgp_Mem->zgpDecryptReq.dir = ZGP_TX_TO_ZGPD;
  zgp_Mem->zgpDecryptReq.pdu = pdu;
  zgp_Mem->zgpDecryptReq.headerLength = ZGP_COMM_KEY_HEADER_LEN;
  zgp_Mem->zgpDecryptReq.payloadLength = ZGP_COMM_PAYLOAD_SEC_KEY_LEN + ZGP_COMM_PAYLOAD_KEY_MIC_LEN;
  zgp_Mem->zgpDecryptReq.SSP_ZgpDecryptFrameConf = SSP_ZgpDecryptFrameConf;
  
  SSP_ZgpDecryptFrameReq(&zgp_Mem->zgpDecryptReq);
}

/******************************************************************************
  \brief    confirmation callbeck for ssp decryption
  \param    conf - confirmation status.
  \return   none.
******************************************************************************/
void SSP_ZgpDecryptFrameConf(SSP_ZgpDecryptFrameConf_t *conf)
{
  commissioningReqCount = 0;
  if (SSP_SUCCESS_STATUS == conf->status)
  {
    if (zgpIsValidKey(decKey))
    {
      if (zgpSetSecurityKey(decKey))
      {
        zgpGetSecParams()->secKey.keyIsSet = true;
      }
    }
    else
    {
      ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
      zgpResetCommissioning();
      commissioningReq->confirm.status = ZGP_COMMISSIONING_REPLY_FAILURE;
      zgpSendConfToUpperLayer((void *)commissioningReq);
      return;
    }

    zgpGetSecParams()->secKey.keyType = keyType;
    isPdsSecUpdateRequired = true;
    zgpGetStackParams()->panId = panID;
    panID = ZGP_BROADCAST_PANID;
    setCommissioningState(sCommReplyOk);
    return;
  }
  else
  {
    ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
    zgpResetCommissioning();
    commissioningReq->confirm.status = ZGP_COMMISSIONING_REPLY_FAILURE;
    zgpSendConfToUpperLayer((void *)commissioningReq);
  }
}
#endif //#ifdef ZGP_SECURITY_ENABLE

/******************************************************************************
  \brief    resets counters and timers
  \param    none.
  \return   none.
******************************************************************************/
static void zgpResetCommissioning(void)
{
  HAL_StopAppTimer(&bidirectionalCommTimer);
  setCommissioningState(sCommIdle);
  commissioningReqCount = 0;
}
#endif //#if (CS_ZGP_COMMISSIONING_AUTOMATION == true)

//eof zgpBidirectionalCommissioning.c
