/*******************************************************************************
  Zigbee green power data handler Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdDataHandler.c

  Summary:
    This file contains the zgpd data primitives implementation.

  Description:
    This file contains the zgpd data primitives implementation.
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
#include <configserver/include/configserver.h>
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <zgp/GPDevice/include/zgpdMemAccess.h>
#include <zgp/GPDevice/include/zgpdIb.h>
#include <zgp/GPDevice/include/zgpdChannelConfig.h>
#ifdef ZGP_SECURITY_ENABLE
#include <security/serviceprovider/include/sspSfp.h>
#include <mac_phy/mac_env/include/macenvPib.h>
#endif 
#include <zgp/include/zgpDbg.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include/macHwdZgpCommon.h>
/******************************************************************************
                    Constants section
******************************************************************************/

/******************************************************************************
                    Defines section
******************************************************************************/
#define MANUFACTURER_ID_PRESENCE_MASK 0x02
/******************************************************************************
                    Prototypes section
******************************************************************************/
//todo move to a generic .h file
extern void ZGP_DataInd(ZGP_DataInd_t *zgpDataIndParams);
extern void ZGP_WriteAttributeInd( ZGP_WriteAttributeInd_t *zgpWriteAttributeInd);

/******************************************************************************
                    Static functions prototypes section
******************************************************************************/
static void zgpFcfConstruct(ZGP_NwkFrameControl_t *nwkFcf, ZGP_ExtNwkFrameControl_t *extNwkFcf);
static void zgpMacDataConfirm(MAC_DataConf_t *confirm);
static void zgpReadDataAndFrameInfo(MAC_DataInd_t *indParams,ZGP_DataInd_t *zgpDataIndParams);
static void zgpPrepareCommonFrame(void);
static void zgpRedirectReceivedFrame(ZGP_DataInd_t *zgpDataIndParams);
#ifdef ZGP_SECURITY_ENABLE
static void zgpSspEncryptconfirm(SSP_ZgpEncryptFrameConf_t *conf);
static void zgpSspDecryptconfirm(SSP_ZgpDecryptFrameConf_t *conf);
bool zgpFrameCounterRecovery(uint8_t receivedMacDsn, uint32_t *recoveredFrameCounter);
#endif
/******************************************************************************
                    Global variables section
******************************************************************************/
uint8_t macSeqNo;
bool isCommBusy = false;
commissioningCallback_t zgpCommissioningCallback;
extern bool rxAfterTx;
/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief Forms the nwk frame control field & extended nwk frame control field
         based on the inputs
  \param nwk_fcf - pointer to nwk frame control field structure
  \param ext_nwk_fcf -  pointer to extended nwk frame control field structure
  \return none.
******************************************************************************/
static void zgpFcfConstruct(ZGP_NwkFrameControl_t *nwkFcf, ZGP_ExtNwkFrameControl_t *extNwkFcf)
{
#ifdef ZGP_SECURITY_ENABLE
  ZGP_SecKeyType_t keyType = ZGP_KEY_TYPE_NO_KEY;
#endif 
    
#ifdef _ZGPD_SPECIFIC_
  ZGP_FrameDir_t   direction = ZGP_TX_BY_ZGPD;   
#else
  ZGP_FrameDir_t   direction = ZGP_TX_BY_ZGPP; 
#endif
  /* Filling extended nwk frame control fields.
    Extended nwk fcf is present only if appId is different from 0x00 (or) 
    For ApplicationID 0b000, it shall be present if the GPDF is protected, 
    if RxAfterTx is set, or if the GPDF is sent to the ZGPD   - ZGP spec r23, A.1.4.1.3, page 38 */
  if(ZGP_SRC_APPID !=  zgpGetDeviceParams()->appId || true == zgpGetDeviceParams()->rxAfterTx || 0x00 != zgpGetDeviceParams()->secLevel 
                                      || ZGP_TX_TO_ZGPD == direction)
  {
    extNwkFcf->appId = zgpGetDeviceParams()->appId;
#ifdef ZGP_SECURITY_ENABLE
    extNwkFcf->secLevel = zgpGetDeviceParams()->secLevel; 
    /* Extract a security key type from Zgp IBb and based on the key type set the
    Security key sub field.
    IF the key type is ZGP_KEY_TYPE_OOB_ZGPD_KEY or ZGP_KEY_TYPE_DERIVED_INDIVIDUAL_ZGPD_KEY,
    set the Security Key field as 1 (Individual key). Otherwise reset the
    security field as 0 (Shared key) */
    CS_ReadParameter(CS_ZGP_SECURITY_KEY_TYPE_ID,&keyType);
    if((keyType == ZGP_KEY_TYPE_OOB_ZGPD_KEY) || (keyType == ZGP_KEY_TYPE_DERIVED_INDIVIDUAL_ZGPD_KEY))
    {
      /* Set Security key sub-field */
      extNwkFcf->secKey = ZGP_SECURITY_KEY_INDIVIDUAL;
    }
    else
    {
      extNwkFcf->secKey = ZGP_SECURITY_KEY_SHARED;
    }
#else
    extNwkFcf->secLevel = 0;
    /* Set Security key sub-field */
    extNwkFcf->secKey = ZGP_SECURITY_KEY_NONE;
#endif       
    extNwkFcf->rxAfterTx = zgpGetDeviceParams()->rxAfterTx;
    // todo if ZGP_TX_BY_ZGPP
    extNwkFcf->direction = direction;
    nwkFcf->isExtNwkFcf = true;
  }
  else
  {
    nwkFcf->isExtNwkFcf = false;
  }
  // Filling nwk frame control fields
  nwkFcf->frametype = ZGP_FRAME_DATA;
  nwkFcf->zigbeeProtVersion = GREENPOWER_PROTOCOL_VERSION;
  if(csZGIB.deviceParams.commissioningType == ZGP_AUTO_COMMISSIONING)
    nwkFcf->autoCommissioning = true;
  else
    nwkFcf->autoCommissioning = false;
}
/******************************************************************************
  \brief Construct header and other fields which are common to all zgp frames 
  \param  none
  \return none
******************************************************************************/
static void zgpPrepareCommonFrame(void)
{    
  uint8_t *currFieldPtr = zgpMem.zgpPacket.payload;
  ZGP_NwkFrameControl_t nwkFcf;
  ZGP_ExtNwkFrameControl_t extNwkFcf;  
  
  // Construct the nwk fcf and ext nwk fcf
  zgpFcfConstruct(&nwkFcf, &extNwkFcf);
   // fill parameters for raising Mac data request
  zgpMem.macReq.data.txOptions = MAC_NO_TXOPTION;
  zgpMem.macReq.data.dstAddrMode = MAC_SHORT_ADDR_MODE;
  zgpMem.macReq.data.dstPanId = zgpGetStackParams()->panId;
  zgpMem.macReq.data.dstAddr.sh = ZGP_BROADCAST_ADDR;
  if(csZGIB.deviceParams.appId == 0x00)
      zgpMem.macReq.data.srcAddrMode = MAC_NO_ADDR_MODE;
  else if(csZGIB.deviceParams.appId == 0x02)
      zgpMem.macReq.data.srcAddrMode = MAC_EXT_ADDR_MODE;
  zgpMem.macReq.data.msduLength = ZGP_CMD_ID_LENGTH;
  zgpMem.macReq.data.performCsma = true;
  
#ifdef ZGP_SECURITY_ENABLE
// fill security frame counter 
  if (zgpGetDeviceParams()->secLevel != ZGP_SECURITY_LEVEL_0)
  {
    incAndStoreOutgngFrameCntr();
    
    if((zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_2) ||
      (zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_3))
    {
      zgpMem.macReq.data.msduLength += ZGP_SEC_FRAME_CTR_LENGTH;
      currFieldPtr -= ZGP_SEC_FRAME_CTR_LENGTH;
      memcpy(currFieldPtr, (uint8_t*)&(zgpGetSecParams()->outFrmCntr), ZGP_SEC_FRAME_CTR_LENGTH);
    }
  }
#endif //eof ZGP_SECURITY_ENABLE
//fill endpoint if present
  if(ZGP_IEEE_ADDR_APPID == zgpGetDeviceParams()->appId)
  {
    zgpMem.macReq.data.msduLength += ZGP_ENDPOINT_LENGTH;
    currFieldPtr -= ZGP_ENDPOINT_LENGTH;
    memcpy(currFieldPtr, (uint8_t*)&(zgpGetDeviceParams()->endPoint), ZGP_ENDPOINT_LENGTH);
  }    
//fill src id  if present  
  if(ZGP_SRC_APPID == zgpGetDeviceParams()->appId && nwkFcf.frametype == ZGP_FRAME_DATA)
  {
    zgpMem.macReq.data.msduLength += ZGP_SRC_ID_LENGTH;
    currFieldPtr -= ZGP_SRC_ID_LENGTH;
    memcpy(currFieldPtr, (uint8_t*)&(zgpGetDeviceParams()->srcID), ZGP_SRC_ID_LENGTH);
  }
  // fill extended nwk frame control field if present
  if(nwkFcf.isExtNwkFcf)
  {
    currFieldPtr -= ZGP_EXT_NWK_FCF_LENGTH;
    memcpy(currFieldPtr, (uint8_t*)&(extNwkFcf), ZGP_EXT_NWK_FCF_LENGTH);
    zgpMem.macReq.data.msduLength += ZGP_EXT_NWK_FCF_LENGTH;        
  }
  
  // fill nwk frame control field
  currFieldPtr -= ZGP_NWK_FCF_LENGTH;
  *currFieldPtr = *((uint8_t*)&(nwkFcf)); // takes only 3 instruction

  zgpMem.macReq.data.msduLength += ZGP_NWK_FCF_LENGTH;
      
  zgpMem.macReq.data.msdu = currFieldPtr;
  if(zgpGetDeviceParams()->rxAfterTx)
    MACHWDZGP_SetRxAfterTx();
}
/******************************************************************************
  \brief   To raise MAC data req
  \param   reqParams - address of the MAC data request parameters structure
  \return  none.
******************************************************************************/
void zgpTxReq(MAC_DataReq_t *reqParams)
{
  MAC_DataReq(reqParams);
}
/******************************************************************************
  \brief  Checks data request parameters, construct the Mac payload and raise MAC data req
  \param  none.
  \return current status of operation (success or "in progress").
******************************************************************************/
void zgpDataReqHandler(void)
{
  ZGP_DataReq_t *zgpDataReq = (ZGP_DataReq_t *)zgpGetReqParams();
  zgpDataReq->confirm.handle = zgpDataReq->eppHandle;
  //Fill the header and other fields which are common to all zgp frames 
  zgpPrepareCommonFrame();
  if ((zgpDataReq->txOptions.requireMacAck == true) &&
      (zgpMem.macReq.data.dstAddr.sh != ZGP_BROADCAST_ADDR))
  {
    zgpMem.macReq.data.txOptions = MAC_ACK_TXOPTION;
  }
  memcpy(zgpMem.zgpPacket.payload,zgpDataReq->asdu,zgpDataReq->asduLength);
  // common frame already includes command length
  zgpMem.macReq.data.msduLength += zgpDataReq->asduLength - ZGP_CMD_ID_LENGTH;
  zgpMem.macReq.data.performCsma =  zgpDataReq->txOptions.performCsma;
  zgpMem.macReq.data.MAC_DataConf= zgpMacDataConfirm;
#ifdef ZGP_SECURITY_ENABLE 
  if(zgpGetDeviceParams()->secLevel != ZGP_SECURITY_LEVEL_0)
  {
    // Inputs to ssp Encryption
    if(zgpGetSecParams()->secKey.keyIsSet)
    {
      zgpMem.zgpEncryptReq.key = zgpGetSecParams()->secKey.key;
    }
    else
    {
      //key unavailable or invalid
      zgpDataReq->confirm.status = ZGP_UNAVAILABLE_KEY_STATUS;
      zgpSendConfToUpperLayer((void *)zgpDataReq); 
      return;
    }
    zgpMem.zgpEncryptReq.securityFrameCounter = zgpGetSecParams()->outFrmCntr;
    zgpMem.zgpEncryptReq.securityLevel = zgpGetDeviceParams()->secLevel;
    zgpMem.zgpEncryptReq.appId = zgpGetDeviceParams()->appId;
    zgpMem.zgpEncryptReq.srcID = zgpGetDeviceParams()->srcID;
    zgpMem.zgpEncryptReq.dir = ZGP_TX_BY_ZGPD;

    if(zgpGetDeviceParams()->secLevel == 0x01)
    {
      zgpMem.zgpEncryptReq.macHeader[0] = (uint8_t)zgpGetStackParams()->panId;  
      zgpMem.zgpEncryptReq.macHeader[1] = (uint8_t)(zgpGetStackParams()->panId >> 8);
      zgpMem.zgpEncryptReq.macHeader[2] = (uint8_t)zgpMem.macReq.data.dstAddr.sh;
      zgpMem.zgpEncryptReq.macHeader[3] = (uint8_t)(zgpMem.macReq.data.dstAddr.sh >> 8);
    }
    if(zgpGetDeviceParams()->appId == ZGP_IEEE_ADDR_APPID)
    {
      CS_ReadParameter(CS_UID_ID, &zgpMem.zgpEncryptReq.extAddr);    
    }
    zgpMem.zgpEncryptReq.pdu = zgpMem.macReq.data.msdu;
    // header length is calculated in prepareCommonFrame() function
    zgpMem.zgpEncryptReq.headerLength =  zgpMem.macReq.data.msduLength - zgpDataReq->asduLength;
    zgpMem.zgpEncryptReq.payloadLength = zgpDataReq->asduLength;
    zgpMem.zgpEncryptReq.SSP_ZgpEncryptFrameConf = zgpSspEncryptconfirm;
    SSP_ZgpEncryptFrameReq(&zgpMem.zgpEncryptReq);
  }
  else
#endif // eof ZGP_SECURITY_ENABLE
  {
    zgpTxReq(&zgpMem.macReq.data);
  }
}
/******************************************************************************
  \brief  callback from SSP component on completion of encryption
  \param  confirm - confirm parameters of operation.
  \return none.
******************************************************************************/
#ifdef ZGP_SECURITY_ENABLE 
static void zgpSspEncryptconfirm(SSP_ZgpEncryptFrameConf_t *conf)
{
  // msdulength is incremented to accomodate MIC 
  if(zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_2 || zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_3)
  {
    zgpMem.macReq.data.msduLength += 4;
  }  
  else if(zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_1)
  {
    zgpMem.macReq.data.msduLength += 2;
  }
  zgpTxReq(&zgpMem.macReq.data);

  //To Make compiler happy
  conf = conf;	   
}
#endif // eof ZGP_SECURITY_ENABLE 
/******************************************************************************
  \brief  Indicates, that data transmition procedure was finished.
  \param   confirm - confirm parameters of operation.
  \return  none.
******************************************************************************/
static void zgpMacDataConfirm(MAC_DataConf_t *confirm)
{
  ZGP_DataReq_t *dataReq = (ZGP_DataReq_t *)zgpGetReqParams();
  // pass the status from MAC as ZGP status
  dataReq->confirm.status = confirm->status;
  zgpSendConfToUpperLayer((void *)dataReq);    
}
/******************************************************************************
  \brief To parse the received frame to extract fcf and payload
  \param   none
  \return  none.
******************************************************************************/
ZGP_Status_t zgpParseFrame(MAC_DataInd_t *indParams,ZGP_DataInd_t *zgpDataIndParams)
{
   ZGP_NwkFrameControl_t nwkFcf;
   ZGP_ExtNwkFrameControl_t extNwkFcf;
   *((uint8_t*)&(nwkFcf)) = *indParams->msdu;
   uint32_t temp = 0;
   zgpDataIndParams->autoCommissioning = nwkFcf.autoCommissioning;
   zgpDataIndParams->zgpAsduLen = indParams->msduLength - ZGP_NWK_FCF_LENGTH - ZGP_CMD_ID_LENGTH;

   if(getChannelConfigState() == sChannelConfigWaiting)
   {
     //parse channel configuration command which does nt have a external nwk FCF
     zgpReadDataAndFrameInfo(indParams,zgpDataIndParams);  
     return ZGP_SUCCESS_STATUS;
   }

   // copy extended nwk fcf if present
   if(nwkFcf.isExtNwkFcf)
   {
      *((uint8_t*)&(extNwkFcf)) = *(++indParams->msdu);
      if(extNwkFcf.direction != true)
      {
        // when the frame is sent to GPD extNwkFCF will always be present with direction bit set
        // sysassert shall be included
        return ZGP_MAC_INVALID_PARAMETER_STATUS;
      }
      if(extNwkFcf.appId != zgpGetDeviceParams()->appId)
      {
        // when the frame is sent to GPD AppId shall
        // sysassert shall be included
        return ZGP_MAC_INVALID_PARAMETER_STATUS;
      }
      zgpDataIndParams->appId = extNwkFcf.appId;
      zgpDataIndParams->rxAfterTx = extNwkFcf.rxAfterTx;
      zgpDataIndParams->gpdfSecLevel = extNwkFcf.secLevel;
      zgpDataIndParams->zgpAsduLen -= ZGP_EXT_NWK_FCF_LENGTH;
   }
   else
   {
     // when the frame is sent to GPD extNwkFCF will always be present with direction bit set
     return ZGP_MAC_INVALID_PARAMETER_STATUS;
   }
   if(zgpDataIndParams->gpdfSecLevel != ZGP_SECURITY_LEVEL_1 && 
      zgpDataIndParams->gpdfSecLevel != ZGP_SECURITY_LEVEL_0)
   {
      zgpDataIndParams->zgpAsduLen -= ZGP_SEC_FRAME_CTR_LENGTH;
   }
   // Copy srcId
    if(zgpDataIndParams->appId == ZGP_SRC_APPID)
    {
       zgpDataIndParams->srcId |= (temp | *++indParams->msdu);
       zgpDataIndParams->srcId |= (temp | *++indParams->msdu) << 8;
       zgpDataIndParams->srcId |= (temp | *++indParams->msdu) << 16;
       zgpDataIndParams->srcId |= (temp | *++indParams->msdu) << 24; 
       if(zgpDataIndParams->srcId != zgpGetDeviceParams()->srcID)
       {
         return ZGP_MAC_INVALID_PARAMETER_STATUS;  
       }
       zgpDataIndParams->zgpAsduLen -= ZGP_SRC_ID_LENGTH;
    }
    if(zgpDataIndParams->appId == ZGP_IEEE_ADDR_APPID)
    {
      zgpDataIndParams->endPoint = *++indParams->msdu;
      if(zgpDataIndParams->endPoint != zgpGetDeviceParams()->endPoint &&
         zgpDataIndParams->endPoint != 0xFF && zgpDataIndParams->endPoint != 0x00)
      {
        return ZGP_MAC_INVALID_PARAMETER_STATUS;   
      }
      zgpDataIndParams->zgpAsduLen -= ZGP_ENDPOINT_LENGTH;
    }
#ifdef ZGP_SECURITY_ENABLE
  if(zgpDataIndParams->gpdfSecLevel == ZGP_SECURITY_LEVEL_2 || 
    zgpDataIndParams->gpdfSecLevel == ZGP_SECURITY_LEVEL_3)
  {
    zgpDataIndParams->zgpdSecFrameCounter = 0;
    zgpDataIndParams->zgpdSecFrameCounter |= (temp | *++indParams->msdu);
    zgpDataIndParams->zgpdSecFrameCounter |= (temp | *++indParams->msdu) << 8;
    zgpDataIndParams->zgpdSecFrameCounter |= (temp | *++indParams->msdu) << 16;
    zgpDataIndParams->zgpdSecFrameCounter |= (temp | *++indParams->msdu) << 24;       
  }
#endif
   zgpReadDataAndFrameInfo(indParams,zgpDataIndParams);
   return ZGP_SUCCESS_STATUS;  
}
/******************************************************************************
  \brief To parse data unit and header,footer information
  \param   none
  \return  none.
******************************************************************************/
static void zgpReadDataAndFrameInfo(MAC_DataInd_t *indParams,ZGP_DataInd_t *zgpDataIndParams)
{
  zgpDataIndParams->zgpAsdu = ++indParams->msdu;
  zgpDataIndParams->LQI = indParams->linkQuality;
  zgpDataIndParams->seqNum = indParams->dsn;
  zgpDataIndParams->srcAddrMode = indParams->srcAddrMode;
  zgpDataIndParams->srcPANID = indParams->srcPANId;
}
/**************************************************************************//**
  \brief to reconstruct the full 4B frame counter 
  \param receivedMacDsn
  \return none.
******************************************************************************/ 
#ifdef ZGP_SECURITY_ENABLE
bool zgpFrameCounterRecovery(uint8_t receivedMacDsn, uint32_t *recoveredFrameCounter)
{
  uint32_t currentFrameCounter = zgpGetSecParams()->inFrmCntrSet[0].inFrmCntr;
  int8_t diff = 0;  
  uint8_t currFrameCounterLsb = currentFrameCounter & 0x000000FF;
  if(receivedMacDsn > currFrameCounterLsb)
  {
    currentFrameCounter = currentFrameCounter & 0xFFFFFF00;
    currentFrameCounter |= 0x000000FF & receivedMacDsn;
    *recoveredFrameCounter = currentFrameCounter;
    return true;
  }
  else 
  {
    /* LSB  rollover  and Freshness check - refer A.3.7.2.4 and  A.3.6.1.3.1*/ 
    diff = currFrameCounterLsb - receivedMacDsn;
    diff = 256 - diff;
    if(diff > 1)
    {
      currentFrameCounter = currentFrameCounter >> 8;
      currentFrameCounter++;
      currentFrameCounter = currentFrameCounter << 8 | (0x000000FF & receivedMacDsn);
      *recoveredFrameCounter = currentFrameCounter;
      return true;
    } 
    else
    {
      return false; 
    }
  }
}
#endif
/******************************************************************************
  \brief  Received data indication callback for ZGP frames.
  \param  confirm - confirm parameters of operation.
  \return none.
******************************************************************************/
void zgpRxIndication(MAC_DataInd_t *indParams)
{
   ZGP_DataInd_t *zgpDataIndParams = &zgpMem.zgpDataIndParams; 
   if(ZGP_SUCCESS_STATUS != zgpParseFrame(indParams, zgpDataIndParams))
   {
     return;
   }
   if((sCommDone != getCommissioningState()) && (ZGP_SECURITY_LEVEL_0 != zgpDataIndParams->gpdfSecLevel))
   {
     //Filter all encrypted frames before commissioning succeed
     return;
   }

#ifdef ZGP_SECURITY_ENABLE 
  if (ZGP_SECURITY_LEVEL_0 != zgpGetDeviceParams()->secLevel)
  {
    if (ZGP_SECURITY_LEVEL_0 == zgpDataIndParams->gpdfSecLevel)
    {
      if (ZGP_COMMISSIONING_REPLY_CMD_ID == zgpMem.zgpDataIndParams.zgpAsdu[0])
      {
        if (NULL != zgpCommissioningCallback)
        {
          zgpCommissioningCallback(&zgpMem.zgpDataIndParams);
          return;
        }
      }
      else if(ZGP_CHANNEL_CONFIG_CMD_ID == zgpMem.zgpDataIndParams.zgpAsdu[0])
      {
        zgpRedirectReceivedFrame(&zgpMem.zgpDataIndParams);
        return;
      }
    }
    // todo A.1.5.2.2
//  if(zgpDataIndParams->gpdfSecLevel == ZGP_SECURITY_LEVEL_1 ||
//     zgpDataIndParams->gpdfSecLevel == ZGP_SECURITY_LEVEL_2 )
//  {
//        
//  }
  // Frame counter recovery
    if(zgpDataIndParams->gpdfSecLevel == ZGP_SECURITY_LEVEL_1)
    {
      zgpMem.zgpDecryptReq.macHeader[0] = (uint8_t)indParams->dstPANId;
      zgpMem.zgpDecryptReq.macHeader[1] = (uint8_t)(indParams->dstPANId >> 8);
      //This will copy the 2 LSB, irrespective of address mode
      zgpMem.zgpDecryptReq.macHeader[2] = (uint8_t)indParams->dstAddr.sh;
      zgpMem.zgpDecryptReq.macHeader[3] = (uint8_t)(indParams->dstAddr.sh >> 8);
      if(!zgpFrameCounterRecovery(indParams->dsn,&zgpDataIndParams->zgpdSecFrameCounter))
        return;
    }  
    if(zgpDataIndParams->zgpdSecFrameCounter < zgpGetSecParams()->inFrmCntrSet[0].inFrmCntr)
    {
      // packet is replayed
      return;
    }
    // Inputs to ssp Encryption
    if(zgpGetSecParams()->secKey.keyIsSet)
    {
      zgpMem.zgpDecryptReq.key = zgpGetSecParams()->secKey.key;
    }
    else
    {
      return;
    }
    zgpMem.zgpDecryptReq.securityFrameCounter = zgpDataIndParams->zgpdSecFrameCounter;
    zgpMem.zgpDecryptReq.securityLevel = zgpDataIndParams->gpdfSecLevel;
    zgpMem.zgpDecryptReq.appId = zgpDataIndParams->appId;
    zgpMem.zgpDecryptReq.srcID = zgpDataIndParams->srcId;
    zgpMem.zgpDecryptReq.dir = ZGP_TX_TO_ZGPD;
    if(zgpDataIndParams->appId == ZGP_IEEE_ADDR_APPID)
    {
      zgpMem.zgpDecryptReq.extAddr = zgpGetDeviceParams()->ieeeAddr;
    }
    else
    {
      zgpMem.zgpDecryptReq.extAddr = 0;
    }

  // header length is calculated in prepareCommonFrame() function
    zgpMem.zgpDecryptReq.headerLength =  indParams->msduLength - zgpDataIndParams->zgpAsduLen - ZGP_CMD_ID_LENGTH;
    zgpMem.zgpDecryptReq.payloadLength = ZGP_CMD_ID_LENGTH + zgpDataIndParams->zgpAsduLen;
    zgpMem.zgpDecryptReq.pdu = zgpDataIndParams->zgpAsdu - zgpMem.zgpDecryptReq.headerLength;
    zgpMem.zgpDecryptReq.SSP_ZgpDecryptFrameConf = zgpSspDecryptconfirm;
    SSP_ZgpDecryptFrameReq(&zgpMem.zgpDecryptReq);
  }
  else if (ZGP_COMMISSIONING_REPLY_CMD_ID == zgpMem.zgpDataIndParams.zgpAsdu[0])
  {
    if (NULL != zgpCommissioningCallback)
    {
      zgpCommissioningCallback(&zgpMem.zgpDataIndParams);
    }
  }
  else
  {
    zgpRedirectReceivedFrame(&zgpMem.zgpDataIndParams); 
  }
#else
  if (ZGP_COMMISSIONING_REPLY_CMD_ID == zgpMem.zgpDataIndParams.zgpAsdu[0])
  {
    if (NULL != zgpCommissioningCallback)
    {
      zgpCommissioningCallback(&zgpMem.zgpDataIndParams);
    }
  }
  else
  {
    zgpRedirectReceivedFrame(&zgpMem.zgpDataIndParams);
  }
#endif // eof ZGP_SECURITY_ENABLE
}
/******************************************************************************
  \brief  callback from SSP component on completion of Decryption
  \param  confirm - confirm parameters of operation.
  \return none.
******************************************************************************/
#ifdef ZGP_SECURITY_ENABLE 
static void zgpSspDecryptconfirm(SSP_ZgpDecryptFrameConf_t *conf)
{
  if(conf->status == SSP_SUCCESS_STATUS)
  {
    zgpGetSecParams()->inFrmCntrSet[0].inFrmCntr = conf->securityFrameCounter;
    zgpRedirectReceivedFrame(&zgpMem.zgpDataIndParams);
  }
}
#endif // eof ZGP_SECURITY_ENABLE 
/******************************************************************************
  \brief   To parse the received write attribute 
  \param   zgpDataIndParams - Zgp data indication parameters
  \return  none.
******************************************************************************/
void zgpParseWriteAttributeCmd(ZGP_DataInd_t *zgpDataIndParams)
{
  zgpMem.zgpWriteAttributeInd.options = *(++zgpDataIndParams->zgpAsdu);
  zgpDataIndParams->zgpAsdu = zgpDataIndParams->zgpAsdu + 1;
  if(zgpMem.zgpWriteAttributeInd.options && MANUFACTURER_ID_PRESENCE_MASK)
  {
    memcpy(&zgpMem.zgpWriteAttributeInd.manufacturerId,zgpDataIndParams->zgpAsdu,sizeof(uint16_t));
    zgpDataIndParams->zgpAsdu = zgpDataIndParams->zgpAsdu + sizeof(uint16_t);
  }
  memcpy(&zgpMem.zgpWriteAttributeInd.clusterId,zgpDataIndParams->zgpAsdu,sizeof(uint16_t));
  zgpDataIndParams->zgpAsdu = zgpDataIndParams->zgpAsdu + sizeof(uint16_t);
  zgpMem.zgpWriteAttributeInd.lengthOfRecordList = *(zgpDataIndParams->zgpAsdu++);
  memcpy(&zgpMem.zgpWriteAttributeInd.zgpAttrField,zgpDataIndParams->zgpAsdu,sizeof(zgpAttrField_t));
}
/******************************************************************************
  \brief   To redirect the received frame to the respective module after parsing
  \param   zgpDataIndParams - Zgp data indication parameters
  \return  none.
******************************************************************************/
static void zgpRedirectReceivedFrame(ZGP_DataInd_t *zgpDataIndParams)
{ 
  switch(*(zgpDataIndParams->zgpAsdu))
  {
    case ZGP_CHANNEL_CONFIG_CMD_ID:
      zgpChannelConfigInd(zgpDataIndParams);
      break;
    case ZGP_COMMISSIONING_REPLY_CMD_ID: 
     
      break;
    case ZGP_WRITE_ATTRIBUTE_CMD_ID:
      {
          zgpParseWriteAttributeCmd(zgpDataIndParams);
          ZGP_WriteAttributeInd(&zgpMem.zgpWriteAttributeInd);
      }
        break;
      default:
        ZGP_DataInd(zgpDataIndParams);
        break;   
  }    
}
/**************************************************************************//**
  \brief to request zgp to do data transmission 
  \param zgp_datareq - pointer to ZGP_DataReq_t structure which has inputs for data req
  \return none.
******************************************************************************/ 
ZGP_Status_t ZGP_DataReq(ZGP_DataReq_t *zgpDataReq)
{
  zgpDataReq->service.requestId = ZGP_DATA_REQ_ID;
  zgpDataReq->service.presenceInQueue = zgpPutReqInQueue((void *)zgpDataReq);
  // if TX queue is full, call the confirmation with error status, post the corresponding task otherwise
  if(zgpDataReq->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_DATA_REQ_ID);
  }
  else
  {
    // pass the status
    return(ZGP_TX_QUEUE_FULL);
  }
  
  return(ZGP_SUCCESS_STATUS);
}
/**************************************************************************//**
  \brief Indication from MAC-layer about receiving a new frame.
  \param[in] macDataInd - MCPS-DATA indication primitive's parameters, see
      IEEE 802.15.4-2006, 7.1.1.3 MCPS-DATA.indication.
  \return None.
 ******************************************************************************/
void MAC_DataInd(MAC_DataInd_t *indParams)
{
  ZGP_NwkFrameControl_t nwkFcf;
  
  // copy nwk frame control field and check zgp protocol version
   *((uint8_t*)&(nwkFcf)) = *indParams->msdu;
  if(nwkFcf.zigbeeProtVersion != GREENPOWER_PROTOCOL_VERSION)
  {
    return;     
  } 
   
//   // return if the address mode is not matching
//   if ((MAC_NO_ADDR_MODE != indParams->srcAddrMode)
//      || (MAC_SHORT_ADDR_MODE != indParams->dstAddrMode))
//    return;
  zgpRxIndication(indParams);  
}

/******************************************************************************
  \brief   This subscription will be used to register a commissioning callback,
              which will be used in Bidirectional commissioning
  \param   commissioningCB - Zgp commissioning callback
  \return  none.
******************************************************************************/
ZGP_Status_t ZGP_SubscribeCommissioning(commissioningCallback_t zgpCommissioningCB)
{
  if (NULL == zgpCommissioningCB)
  {
    return(ZGP_INVALID_PARAMETER);
  }
  else
  {
    //Register the callback
    zgpCommissioningCallback = zgpCommissioningCB;
    return(ZGP_SUCCESS_STATUS);
  }
}

/******************************************************************************
  \brief   This unsubscribe a commissioning callback, which was subscribed already
  \param   none.
  \return  none.
******************************************************************************/
void ZGP_UnsubscribeCommissioning(void)
{
  zgpCommissioningCallback = NULL;
}
//eof zgpDataHandler.c
