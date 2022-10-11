/*******************************************************************************
  Zigbee green power device commissioning handler Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdCommissioningHandler.c

  Summary:
    This file contains the implementation of zgpd commissioning handler procedure.

  Description:
    This file contains the implementation of zgpd commissioning handler procedure.
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
#include <mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h>
#include <mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include/macHwdZgpCommon.h>
/******************************************************************************
                    Defines section
******************************************************************************/
//#define ZGP_APP_INFO_ENABLE

#ifdef ZGP_APP_INFO_ENABLE
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 1)
// Application information for MSP GPD
#define MANUFACTURER_ID             0x1014
#define MODEL_ID                    0x0001
//#define NO_OF_CMDS                  2
//#define COMMAND_LIST                0x20,0x21
#define NO_OF_CMDS                  1
#define COMMAND_LIST                0xB1
#define NO_OF_SERVER_CLUSTERS       2
#define NO_OF_CLIENT_CLUSTERS       2
#define NO_OF_CLUSTERS              (NO_OF_SERVER_CLUSTERS + NO_OF_CLIENT_CLUSTERS)
#define CLUSTER_LIST                0xFC01, 0xFC02, 0xFC03, 0xFC04
//#define NO_OF_SERVER_CLUSTERS       0
//#define NO_OF_CLIENT_CLUSTERS       0
//#define NO_OF_CLUSTERS              (NO_OF_SERVER_CLUSTERS + NO_OF_CLIENT_CLUSTERS)
//#define CLUSTER_LIST                NULL
uint8_t zgpCommandList[] = {COMMAND_LIST};
uint16_t zgpClusterList[] = {CLUSTER_LIST};
#else
// Application information for MSP GPD
#define MANUFACTURER_ID             0xFFFF
#define MODEL_ID                    0xFFFF
//#define NO_OF_CMDS                  2
//#define COMMAND_LIST                0x20,0x21
#define NO_OF_CMDS                  0
#define COMMAND_LIST                NULL
#define NO_OF_SERVER_CLUSTERS       2
#define NO_OF_CLIENT_CLUSTERS       0
#define NO_OF_CLUSTERS              (NO_OF_SERVER_CLUSTERS + NO_OF_CLIENT_CLUSTERS)
#define CLUSTER_LIST                0x0000,0x0402
//#define NO_OF_SERVER_CLUSTERS       0
//#define NO_OF_CLIENT_CLUSTERS       0
//#define NO_OF_CLUSTERS              (NO_OF_SERVER_CLUSTERS + NO_OF_CLIENT_CLUSTERS)
//#define CLUSTER_LIST                NULL
uint8_t zgpCommandList[] = {COMMAND_LIST};
uint16_t zgpClusterList[] = {CLUSTER_LIST};
#endif

#define APP_INFO_LEN           1
#define MANUFACTURER_ID_LEN    2
#define MODEL_ID_LEN           2
#endif
/******************************************************************************
                    Prototypes
******************************************************************************/
#ifdef ZGP_SECURITY_ENABLE
/******************************************************************************
  \brief    key encrytion confirmation
  \param    conf - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpSspEncryptKeyconfirm(SSP_ZgpEncryptFrameConf_t *conf);

/******************************************************************************
  \brief    encrypt commissioning payload less commands (Success GPDF/Decommissioning)
  \param    zgp_Mem - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpEncryptPayloadlessCmd(ZGP_Mem_t* zgp_Mem);


/******************************************************************************
  \brief    confirmation callback for payload less command encryption (Success GPDF/Decommissioning)
  \param    zgp_Mem - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpSuccessCmdEncryptconfirm(SSP_ZgpEncryptFrameConf_t *conf);
#endif //ZGP_SECURITY_ENABLE

/******************************************************************************
  \brief    send Decommissioning confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpDecommissioningConfirm(MAC_DataConf_t *confirm);

/******************************************************************************
  \brief    send Success GPDF confirmation to application
  \param    confirm - confirmation status
  \return   none.
******************************************************************************/
static void zgpSuccessGpdfConfirm(MAC_DataConf_t *confirm);
#ifdef ZGP_APP_INFO_ENABLE
static void zgpBuildAndAppendAppInfo(uint8_t *payload, uint8_t* length);
#endif
/******************************************************************************
  \brief    This will initiate the commissioning request command
  \param    panIdReq - panId required
  \param    keyReq - key required/none
  \param    keyEnc - device has capability to encrypt/decrypt the key
  \param    key - which will be shared with sink
  \param    ZGP_CommissionConf - commissioning confirmation callback
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
void zgpSendCommissioningReq(commissioningCmdConfCallback conf)
{
  
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  
  // fill the command field.
  zgp_Mem->zgpPacket.payload[0] = ZGP_COMMISSIONING_CMD_ID;
  // Commissioning request confirmation callback
  zgp_Mem->macReq.data.MAC_DataConf = conf;
  // fill parameters of Mac data request 
  zgpSetMacDataReqParams(&zgp_Mem->macReq.data, ZGP_COMMISSIONING_CMD_ID);
  //Fill the commissioning request header
  zgpBuildCommCommandHeader(ZGP_COMMISSIONING_CMD_ID);
  // build payload for commissioning command
  zgpBuildCommCommandPayload(&zgp_Mem->macReq.data.msduLength, &zgp_Mem->zgpPacket.payload[0]);
}

/******************************************************************************
  \brief    Set MAC Data Request parameters
  \param    macDataReq - MAC Data Request
  \param    handle - Mac Data Request handle
  \return  none.
******************************************************************************/
void zgpSetMacDataReqParams(MAC_DataReq_t *macDataReq, uint8_t cmdID)
{
  macDataReq->txOptions = MAC_NO_TXOPTION;
  macDataReq->dstAddrMode = MAC_SHORT_ADDR_MODE;

  if (ZGP_COMMISSIONING_CMD_ID == cmdID || ZGP_CHANNEL_REQUEST_CMD_ID == cmdID)
  {
    zgpGetStackParams()->panId = ZGP_BROADCAST_PANID;
    macDataReq->dstPanId = zgpGetStackParams()->panId;
  }
  else
  {
    macDataReq->dstPanId = zgpGetStackParams()->panId;
  }

  macDataReq->dstAddr.sh = ZGP_BROADCAST_ADDR;
  macDataReq->performCsma = zgpGetDeviceParams()->useCsmaCA;
  macDataReq->msduHandle = cmdID;
  macDataReq->msduLength = ZGP_CMD_ID_LENGTH;
  if(csZGIB.deviceParams.appId == 0x00)
      macDataReq->srcAddrMode = MAC_NO_ADDR_MODE;
   else if(csZGIB.deviceParams.appId == 0x02)
      macDataReq->srcAddrMode = MAC_EXT_ADDR_MODE;
}

/******************************************************************************
  \brief    This will fill the NWK Frame Control field and Extended NWK Frame 
              Control field
  \param    nwkFcf - NWK frame control fields. This parameter needs to be rest 
              before call this API
  \param    extNwkFcf - Extended NWK Frame Control fields. This parameter 
              needs to be rest before call this API
  \param    cmd - command ID
  \return  none.
******************************************************************************/
void zgpFCFConstruct(ZGP_NwkFrameControl_t *nwkFcf, ZGP_ExtNwkFrameControl_t *extNwkFcf, uint8_t cmd)
{
#ifdef ZGP_SECURITY_ENABLE
  zgpdSecMaterialSet_t *zgpSecMaterial = zgpGetSecParams();
#endif
  
  // Filling nwk frame control fields
  nwkFcf->frametype = ZGP_FRAME_DATA;
  nwkFcf->zigbeeProtVersion = GREENPOWER_PROTOCOL_VERSION;
  if(csZGIB.deviceParams.commissioningType == ZGP_AUTO_COMMISSIONING)
    nwkFcf->autoCommissioning = true;
  else
    nwkFcf->autoCommissioning = false;

  // Filling extended nwk frame control fields
  extNwkFcf->appId = zgpGetDeviceParams()->appId;
  extNwkFcf->rxAfterTx = zgpGetDeviceParams()->rxAfterTx;
#ifdef _ZGPD_SPECIFIC_
  extNwkFcf->direction = ZGP_TX_BY_ZGPD;
#else
  extNwkFcf->direction = ZGP_TX_BY_ZGPP;
#endif //_ZGPD_SPECIFIC_

#ifdef ZGP_SECURITY_ENABLE
  if (zgpGetDeviceParams()->secLevel && zgpSecMaterial->secKey.keyIsSet)
  {
    ZGP_SecKeyType_t keyType = ZGP_KEY_TYPE_NO_KEY;
    
    //Include the security level for necessary commands
    switch(cmd)
    {
    case ZGP_COMMISSIONING_CMD_ID:
      break;
    case ZGP_DECOMMISSIONING_CMD_ID:
    case ZGP_COMMISSIONING_SUCCESS_CMD_ID:
    { 
       if ((zgpGetDeviceParams()->secLevel != ZGP_SECURITY_LEVEL_0) && 
               (zgpGetSecParams()->secKey.keyIsSet))
        {
          extNwkFcf->secLevel = zgpGetDeviceParams()->secLevel;
        }
      /* Extract a security key type from Zgp IB and based on the key type set the
      Security key sub field.
      IF the key type is ZGP_KEY_TYPE_OOB_ZGPD_KEY or ZGP_KEY_TYPE_DERIVED_INDIVIDUAL_ZGPD_KEY,
      set the Security Key field as 1 (Individual key). Otherwise reset the
      security field as 0 (Shared key) */
      CS_ReadParameter(CS_ZGP_SECURITY_KEY_TYPE_ID,&keyType);
      
      if ((keyType == ZGP_KEY_TYPE_OOB_ZGPD_KEY) || (keyType == ZGP_KEY_TYPE_DERIVED_INDIVIDUAL_ZGPD_KEY))
      {
        /* Set Security key sub-field */
        extNwkFcf->secKey = ZGP_SECURITY_KEY_INDIVIDUAL;
      }
      else
      {
        extNwkFcf->secKey = ZGP_SECURITY_KEY_SHARED;
      }
    }
    break;
    default:
      return;
    }
  }
#else
  //SecLevel and SecKey parameters are zero
  extNwkFcf->secLevel = 0x00;
  extNwkFcf->secKey = 0x00;
#endif //#ifdef ZGP_SECURITY_ENABLE
  
  //If Extended NWK FCF has any non-zero value then, it will be included
  if (*(uint8_t*)extNwkFcf)
  {
    nwkFcf->isExtNwkFcf = true;
  }
}

/******************************************************************************
  \brief    This will fill the command header
  \param    cmd - command ID
  \return  none.
******************************************************************************/
void zgpBuildCommCommandHeader(uint8_t cmd)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  uint8_t *currFieldPtr = zgp_Mem->zgpPacket.payload;
  ZGP_NwkFrameControl_t nwkFcf = {0};
  ZGP_ExtNwkFrameControl_t extNwkFcf = {0};  
    
  // Construct the nwk fcf and ext nwk fcf
  zgpFCFConstruct(&nwkFcf, &extNwkFcf, cmd);
  
  //Include the outgoing frame counter for necessary frames
  switch(cmd)
  {
    case ZGP_COMMISSIONING_CMD_ID:
      break;
    case ZGP_DECOMMISSIONING_CMD_ID:
    case ZGP_COMMISSIONING_SUCCESS_CMD_ID:
  #ifdef ZGP_SECURITY_ENABLE
      if ((zgpGetDeviceParams()->secLevel > ZGP_SECURITY_LEVEL_1) && 
             (zgpGetSecParams()->secKey.keyIsSet))
      {
        incAndStoreOutgngFrameCntr();
        zgp_Mem->macReq.data.msduLength += ZGP_SEC_FRAME_CTR_LENGTH;
        currFieldPtr -= ZGP_SEC_FRAME_CTR_LENGTH;
        memcpy(currFieldPtr, (uint8_t*)(&zgpGetSecParams()->outFrmCntr), ZGP_SEC_FRAME_CTR_LENGTH);
      }
      else if ((ZGP_SECURITY_LEVEL_1 == zgpGetDeviceParams()->secLevel) && 
             (zgpGetSecParams()->secKey.keyIsSet))
      {
        incAndStoreOutgngFrameCntr();
      }
  #endif
      break;
    default:
      return;
  }
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
    zgp_Mem->macReq.data.msduLength += ZGP_SRC_ID_LENGTH;
    currFieldPtr -= ZGP_SRC_ID_LENGTH;
    memcpy(currFieldPtr, (uint8_t*)&(zgpGetDeviceParams()->srcID), ZGP_SRC_ID_LENGTH);
  }
  
  // fill extended nwk frame control field if present
  if(nwkFcf.isExtNwkFcf)
  {
    currFieldPtr -= ZGP_EXT_NWK_FCF_LENGTH;
    memcpy(currFieldPtr, (uint8_t*)&(extNwkFcf), ZGP_EXT_NWK_FCF_LENGTH);
    zgp_Mem->macReq.data.msduLength += ZGP_EXT_NWK_FCF_LENGTH;        
  }
  // fill nwk frame control field
  currFieldPtr -= ZGP_NWK_FCF_LENGTH;
  *currFieldPtr = *((uint8_t*)&(nwkFcf));
  zgp_Mem->macReq.data.msduLength += ZGP_NWK_FCF_LENGTH;
      
  zgp_Mem->macReq.data.msdu = currFieldPtr;
}

/******************************************************************************
  \brief    This will fill the commissioning command payload
  \param    msduLength - length of command payload
  \param    payload - pointer to command payload
  \return  none.
******************************************************************************/
void zgpBuildCommCommandPayload(uint8_t *msduLength, uint8_t *payload)
{
#ifdef ZGP_SECURITY_ENABLE
  zgpdSecMaterialSet_t *zgpSecMaterial = zgpGetSecParams();
#endif
  ZGP_CommissioningReq_t *commissionReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
  bool sendFrame = true;
  
  ZgpCommissionCmdOptions_t *commCmdOptions = (ZgpCommissionCmdOptions_t *)(payload + ZGP_COMM_PAYLOAD_OPTIONS_STRAT);
  *(payload + ZGP_COMM_PAYLOAD_OPTIONS_STRAT) = 0;
  
  //Command Options
  *(payload + ZGP_COMM_PAYLOAD_DEVICE_ID_STRAT) = commissionReq->deviceId;
  *msduLength += ZGP_COMM_PAYLOAD_DEVICE_ID_LEN + ZGP_COMM_PAYLOAD_OPTIONS_LEN;
  commCmdOptions->macSeqNumCapability = zgpGetDeviceParams()->useIncSeqNum;
  commCmdOptions->rxOnCapability = zgpGetDeviceParams()->rxAfterTx;
  //commCmdOptions->Reserved = 0;
  commCmdOptions->panIdRequest = commissionReq->panIdReq;
  commCmdOptions->fixedLocation = commissionReq->fixedLocation;
  commCmdOptions->extendedOptions = false;
  commCmdOptions->securityKeyRequest = false;
#ifdef ZGP_APP_INFO_ENABLE
  commCmdOptions->appInfo = true;
#endif
  
#ifdef ZGP_SECURITY_ENABLE
  //Extended options will be enabled, if security level is not zero
  if (zgpGetDeviceParams()->secLevel)
  {
    ZgpCommissionCmdExtOptions_t *CommExtCmdOptions = (ZgpCommissionCmdExtOptions_t *)(payload + ZGP_COMM_PAYLOAD_EXT_OPTIONS_STRAT);
    *(payload + ZGP_COMM_PAYLOAD_EXT_OPTIONS_STRAT) = 0;
    
    //Enable the extended option, if device is either request key or send the key
    commCmdOptions->extendedOptions = true;
    *msduLength += ZGP_COMM_PAYLOAD_EXT_OPTIONS_LEN;
    CommExtCmdOptions->securityLevel = zgpGetDeviceParams()->secLevel;
    
    commCmdOptions->securityKeyRequest = commissionReq->keyReq;
    CommExtCmdOptions->GPDKeyPresent = (zgpSecMaterial->secKey.keyIsSet && 
                                        zgpIsValidKey(zgpSecMaterial->secKey.key) && 
                                          zgpSecMaterial->secKey.keyType);
    
    if (commCmdOptions->securityKeyRequest || CommExtCmdOptions->GPDKeyPresent)
    {      
      CommExtCmdOptions->GPDKeyEncryption = (zgpSecMaterial->secKey.gpLinkKeyIsSet && 
                                             zgpIsValidKey(zgpSecMaterial->secKey.gpLinkKey));
      CommExtCmdOptions->GPDOutgoingFrmCntr = true;
      incAndStoreOutgngFrameCntr();
      if (CommExtCmdOptions->GPDKeyPresent && CommExtCmdOptions->GPDKeyEncryption)
      {
        uint8_t mic[4] = {0, 0, 0, 0};
        
        CommExtCmdOptions->securityKeyType = zgpGetSecParams()->secKey.keyType;
        /*Header info. This will not transmit over-the-air.
        Refer ZGP spec: 095499r24 Section A.1.5.3.3.3 */
        if (ZGP_SRC_APPID == zgpGetDeviceParams()->appId)
        {
          memcpy((payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT), &zgpGetDeviceParams()->srcID, ZGP_COMM_KEY_HEADER_LEN);
        }
        else if (ZGP_IEEE_ADDR_APPID == zgpGetDeviceParams()->appId)
        {
          memcpy((payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT), &zgpGetDeviceParams()->ieeeAddr, ZGP_COMM_KEY_HEADER_LEN);
        }
        
        memcpy((payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT + ZGP_COMM_PAYLOAD_KEY_OFFSET), zgpGetSecParams()->secKey.key, ZGP_COMM_PAYLOAD_SEC_KEY_LEN);
        memcpy((payload + ZGP_COMM_PAYLOAD_KEY_MIC_STRAT + ZGP_COMM_PAYLOAD_KEY_OFFSET), mic, ZGP_COMM_PAYLOAD_KEY_MIC_LEN);
        memcpy((payload + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_STRAT + ZGP_COMM_PAYLOAD_KEY_OFFSET), &zgpGetSecParams()->outFrmCntr, ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN);
        *msduLength += ZGP_COMM_KEY_HEADER_LEN + ZGP_COMM_PAYLOAD_SEC_KEY_LEN + ZGP_COMM_PAYLOAD_KEY_MIC_LEN + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN;
        
        sendFrame = false;
        zgpFillEncryptReq((payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT), ZGP_COMM_KEY_HEADER_LEN, ZGP_COMM_PAYLOAD_SEC_KEY_LEN);
      }
      else if (CommExtCmdOptions->GPDKeyPresent)
      {
        CommExtCmdOptions->securityKeyType = zgpGetSecParams()->secKey.keyType;
        memcpy((payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT), zgpGetSecParams()->secKey.key, ZGP_COMM_PAYLOAD_SEC_KEY_LEN);
        memcpy((payload + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_STRAT - ZGP_COMM_PAYLOAD_KEY_MIC_LEN), 
               &zgpGetSecParams()->outFrmCntr, ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN);
        *msduLength += ZGP_COMM_PAYLOAD_SEC_KEY_LEN + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN;
      }
      else
      {
        CommExtCmdOptions->securityKeyType = ZGP_KEY_TYPE_NO_KEY;
        memcpy((payload + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_STRAT - (ZGP_COMM_PAYLOAD_SEC_KEY_LEN + ZGP_COMM_PAYLOAD_KEY_MIC_LEN)), 
               &zgpGetSecParams()->outFrmCntr, ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN);
        *msduLength += ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN;
      }
    }
  }
  else
#endif //#ifdef ZGP_SECURITY_ENABLE
  {
    if (commissionReq->keyReq)
    {
      //Send error confirmation
      commissionReq->confirm.status = ZGP_COMMISSIONING_REQ_INVALID;
      zgpSendConfToUpperLayer((void *)commissionReq);
    }
#ifdef ZGP_APP_INFO_ENABLE
    if(commCmdOptions->appInfo)
    {
      // App info will be added after options field in case of no security
      zgpBuildAndAppendAppInfo(payload + ZGP_COMM_PAYLOAD_EXT_OPTIONS_STRAT, msduLength);
    }
#endif
  }
  if (sendFrame)
  {
    zgpTxReq(&zgpGetMem()->macReq.data);
  }
}

/******************************************************************************
  \brief    send commissioning command confirmation to application
  \param    confirm - confirmation status from MAC
  \return  none.
******************************************************************************/
void zgpCommTransmitConfirm(MAC_DataConf_t *confirm)
{
  ZGP_CommissioningReq_t *commissioningReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
  
  //Update the commissioning request
  sysAssert((NULL != commissioningReq->ZGP_CommissionConf), ZGPDCOMMISSIONING_CALLBACKMISSING0);
  commissioningReq->confirm.status = confirm->status;
  // for unidirectional commissioning, if the packet is sent out properly then
  // commissioning is success
  if(confirm->status == MAC_SUCCESS_STATUS && 
     ZGP_UNIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
  {
    setCommissioningState(sCommDone);  
  }
  zgpSendConfToUpperLayer((void *)commissioningReq);
}

/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_SuccessGpdfConf - Success gpdf confirmation callback
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
void zgpSendSuccessGpdf(commissioningCmdConfCallback conf)
{
  // rx after tx is disabled temprarily for Success GPDF
  MACHWDZGP_ResetRxAfterTx();
  zgpSendPayloadlessCommissioningCmd(ZGP_COMMISSIONING_SUCCESS_CMD_ID, conf);
}

/******************************************************************************
  \brief    send Success GPDF confirmation to application
  \param    confirm - confirmation status
  \return   none.
******************************************************************************/
static void zgpSuccessGpdfConfirm(MAC_DataConf_t *confirm)
{
  ZgpSuccessGpdfReq_t *successReq = (ZgpSuccessGpdfReq_t *)zgpGetReqParams();

  successReq->confirm.status = confirm->status;
  zgpSendConfToUpperLayer(successReq);
}

/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_DecommissioningConf - Decommissioning confirmation callback
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
void zgpSendDecommissioning(commissioningCmdConfCallback conf)
{
  // rx after tx is disabled temprarily for Decommissioning GPDF
  MACHWDZGP_ResetRxAfterTx();
  zgpSendPayloadlessCommissioningCmd(ZGP_DECOMMISSIONING_CMD_ID, conf);
}


/******************************************************************************
  \brief    send Decommissioning confirmation to application
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
static void zgpDecommissioningConfirm(MAC_DataConf_t *confirm)
{
  ZGP_DecommissioningReq_t *decommissioningReq = (ZGP_DecommissioningReq_t *)zgpGetReqParams();

  decommissioningReq->confirm.status = confirm->status;
  zgpSendConfToUpperLayer(decommissioningReq);
}


/******************************************************************************
  \brief    sends the commissioning payload less commands
  \param    cmd - command that needs to be sent
  \param    conf - confirmation callback for MAC data request
  \return  none.
******************************************************************************/
void zgpSendPayloadlessCommissioningCmd(uint8_t cmd, commissioningCmdConfCallback conf)
{
  uint8_t *macData;
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  
  // fill the command field.
  zgp_Mem->zgpPacket.payload[ZGP_COMM_PAYLOAD_CMD_ID_START] = cmd;
  // payload less command confirmation callback
  zgp_Mem->macReq.data.MAC_DataConf = conf;
  // fill parameters of Mac data request  
  zgpSetMacDataReqParams(&zgp_Mem->macReq.data, cmd);
  // fill the commissioning request header
  zgpBuildCommCommandHeader(cmd);
  // clear the rx_after_tx field 
  macData = zgp_Mem->macReq.data.msdu + ZGP_NWK_FCF_LENGTH;
  *macData &= ~(1 << ZGP_FCF_RXAFTX_POS);
   if(csZGIB.deviceParams.appId == 0x00)
        zgp_Mem->macReq.data.srcAddrMode = MAC_NO_ADDR_MODE;
   else if(csZGIB.deviceParams.appId == 0x02)
        zgp_Mem->macReq.data.srcAddrMode = MAC_EXT_ADDR_MODE;
#ifdef ZGP_SECURITY_ENABLE
  if ((zgpGetDeviceParams()->secLevel != ZGP_SECURITY_LEVEL_0) && (zgpGetSecParams()->secKey.keyIsSet))
  {
    zgpEncryptPayloadlessCmd(zgp_Mem);
  }
  else
#endif
  zgpTxReq(&zgp_Mem->macReq.data);
}

/******************************************************************************
  \brief    handle all commissioning request
  \param    none.
  \return   none.
******************************************************************************/
void zgpCommissioningHandler(void)
{
  ZGP_Service_t *service = (ZGP_Service_t *)zgpGetReqParams();
  
  //ZGP Commissioning
  if (ZGP_COMMISSION_REQ_ID == service->requestId)
  {
#if (CS_ZGP_COMMISSIONING_AUTOMATION != true)
    MACHWDZGP_SetRxAfterTx();
    if (ZGP_UNIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
    {
      // rx after tx is disabled for Unidirectional commissioning command
      MACHWDZGP_ResetRxAfterTx();
    }
    zgpSendCommissioningReq(zgpCommTransmitConfirm);
#else
    if (ZGP_UNIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
    {
      // rx after tx is disabled for Unidirectional commissioning command
      MACHWDZGP_ResetRxAfterTx();
      zgpSendCommissioningReq(zgpCommTransmitConfirm);
    }
    else if (ZGP_BIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
    {
      zgpBiCommissioningHandler();
    }
#endif
  }
  //ZGP Success GPDF
  else if (ZGP_SUCCESS_GPDF_REQ_ID == service->requestId)
  {
    zgpSendSuccessGpdf(zgpSuccessGpdfConfirm);
  }
  //ZGP Decommissioning
  else if (ZGP_DECOMMISSIONING_REQ_ID == service->requestId)
  {
#if (CS_ZGP_COMMISSIONING_AUTOMATION != true)
    zgpSendDecommissioning(zgpDecommissioningConfirm);
#else
    if (ZGP_UNIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
    {
      zgpSendDecommissioning(zgpDecommissioningConfirm);
    }
    else if (ZGP_BIDIRECTIONAL_COMMISSIONING == zgpGetDeviceParams()->commissioningType)
    {
      zgpDecommissioningHandler();
    }
#endif
  }
}

/******************************************************************************
  \brief    make an IEEE arrress based on SrcIDs
  \param    ieeeAddr - pointer to an IEEE address
  \param    srcIDMsb - SrcID, which needs to be placed in MSB of IEEE address
  \param    srcIDLsb - SrcID, which needs to be placed in LSB of IEEE address
  \return   none.
******************************************************************************/
void zgpMakeIEEEAddrFromSrcAddr(ExtAddr_t *ieeeAddr, uint32_t *srcIDMsb, uint32_t *srcIDLsb)
{
  *ieeeAddr = (ExtAddr_t)*srcIDMsb;
  *ieeeAddr = *ieeeAddr << 32;
  *ieeeAddr |= (ExtAddr_t)*srcIDLsb;
}

#ifdef ZGP_SECURITY_ENABLE
/******************************************************************************
  \brief    fill necessary info for encryption
  \param    pdu - data to be encrypted
  \param    headerLen - length of header
  \param    payloadLen - length of payload
  \return   none.
******************************************************************************/
void zgpFillEncryptReq(uint8_t *pdu, uint8_t headerLen, uint8_t payloadLen)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  
  zgp_Mem->zgpEncryptReq.key = zgpGetSecParams()->secKey.gpLinkKey;
  zgp_Mem->zgpEncryptReq.securityLevel = zgpGetDeviceParams()->secLevel;
  zgp_Mem->zgpEncryptReq.appId = zgpGetDeviceParams()->appId;
  zgp_Mem->zgpEncryptReq.srcID = zgpGetDeviceParams()->srcID;
  zgp_Mem->zgpEncryptReq.dir = ZGP_TX_BY_ZGPD;

  if (ZGP_SRC_APPID == zgp_Mem->zgpEncryptReq.appId)
  {
    zgpMakeIEEEAddrFromSrcAddr(&zgp_Mem->zgpEncryptReq.extAddr, &zgp_Mem->zgpEncryptReq.srcID, &zgp_Mem->zgpEncryptReq.srcID);
    zgp_Mem->zgpEncryptReq.securityFrameCounter = zgp_Mem->zgpEncryptReq.srcID;
  }
  else if (ZGP_IEEE_ADDR_APPID == zgp_Mem->zgpEncryptReq.appId)
  {
    zgp_Mem->zgpEncryptReq.extAddr = zgpGetDeviceParams()->ieeeAddr;
    zgp_Mem->zgpEncryptReq.securityFrameCounter = (uint32_t)zgpGetDeviceParams()->ieeeAddr;
  }
  
  zgp_Mem->zgpEncryptReq.pdu = pdu;
  zgp_Mem->zgpEncryptReq.headerLength = headerLen;
  zgp_Mem->zgpEncryptReq.payloadLength = payloadLen;
  zgp_Mem->zgpEncryptReq.SSP_ZgpEncryptFrameConf = zgpSspEncryptKeyconfirm;
  zgp_Mem->zgpEncryptReq.securityLevel = 3;
  SSP_ZgpEncryptFrameReq(&zgp_Mem->zgpEncryptReq);
}

/******************************************************************************
  \brief    key encrytion confirmation
  \param    conf - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpSspEncryptKeyconfirm(SSP_ZgpEncryptFrameConf_t *conf)
{
  ZGP_Mem_t* zgp_Mem = zgpGetMem();
  zgp_Mem->zgpEncryptReq.securityLevel = 0;
  if (SSP_SUCCESS_STATUS == conf->status)
  {
    ZGP_Mem_t* zgp_Mem = zgpGetMem();
    
    zgp_Mem->macReq.data.msduLength -= ZGP_SEC_FOURBYTE_MIC;
    //Append the MIC
    memcpy((zgp_Mem->zgpPacket.payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT), 
           (zgp_Mem->zgpPacket.payload + ZGP_COMM_PAYLOAD_SEC_KEY_STRAT + ZGP_COMM_PAYLOAD_KEY_OFFSET), 
           (ZGP_COMM_PAYLOAD_SEC_KEY_LEN + ZGP_COMM_PAYLOAD_KEY_MIC_LEN + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN));
#ifdef ZGP_APP_INFO_ENABLE
    zgpBuildAndAppendAppInfo(zgp_Mem->zgpPacket.payload + ZGP_COMM_PAYLOAD_APP_INFO_START, &zgp_Mem->macReq.data.msduLength);
#endif
    zgpTxReq(&zgpGetMem()->macReq.data);
  }
  else
  {
    ZGP_CommissioningReq_t *commissionReq = (ZGP_CommissioningReq_t *)zgpGetReqParams();
    
    commissionReq->confirm.status = conf->status;
    setCommissioningEvent(eCommFailure);
  }
}

/******************************************************************************
  \brief    encrypt commissioning payload less commands (Success GPDF/Decommissioning)
  \param    zgp_Mem - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpEncryptPayloadlessCmd(ZGP_Mem_t* zgp_Mem)
{
  // Inputs to ssp Encryption
  zgp_Mem->zgpEncryptReq.key = (uint8_t const *)&zgpGetSecParams()->secKey.key;
  zgp_Mem->zgpEncryptReq.securityFrameCounter = zgpGetSecParams()->outFrmCntr;
  zgp_Mem->zgpEncryptReq.securityLevel = zgpGetDeviceParams()->secLevel;
  zgp_Mem->zgpEncryptReq.appId = zgpGetDeviceParams()->appId;
  zgp_Mem->zgpEncryptReq.srcID = zgpGetDeviceParams()->srcID;
  zgp_Mem->zgpEncryptReq.dir = ZGP_TX_BY_ZGPD;

  if(zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_1)
  {
    zgp_Mem->zgpEncryptReq.macHeader[0] = (uint8_t)zgpGetStackParams()->panId;  
    zgp_Mem->zgpEncryptReq.macHeader[1] = (uint8_t)(zgpGetStackParams()->panId >> 8);
    zgp_Mem->zgpEncryptReq.macHeader[2] = (uint8_t)zgp_Mem->macReq.data.dstAddr.sh;
    zgp_Mem->zgpEncryptReq.macHeader[3] = (uint8_t)(zgp_Mem->macReq.data.dstAddr.sh >> 8);
  }
  if(zgpGetDeviceParams()->appId == ZGP_IEEE_ADDR_APPID)
  {  
    CS_ReadParameter(CS_UID_ID, &zgp_Mem->zgpEncryptReq.extAddr); 
  }
  zgp_Mem->zgpEncryptReq.pdu = zgp_Mem->macReq.data.msdu;
  // header length is calculated in prepareCommonFrame() function
  zgp_Mem->zgpEncryptReq.headerLength =  zgp_Mem->macReq.data.msduLength - ZGP_CMD_ID_LENGTH;
  zgp_Mem->zgpEncryptReq.payloadLength = ZGP_CMD_ID_LENGTH;
  zgp_Mem->zgpEncryptReq.SSP_ZgpEncryptFrameConf = zgpSuccessCmdEncryptconfirm;
  SSP_ZgpEncryptFrameReq(&zgp_Mem->zgpEncryptReq);
}

/******************************************************************************
  \brief    confirmation callback for payload less command encryption (Success GPDF/Decommissioning)
  \param    zgp_Mem - key encryption confirmation status
  \return   none.
******************************************************************************/
static void zgpSuccessCmdEncryptconfirm(SSP_ZgpEncryptFrameConf_t *conf)
{
  // msdulength is incremented to accomodate MIC 
  if(zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_2 || zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_3)
  {
    zgpMem.macReq.data.msduLength += ZGP_SEC_FOURBYTE_MIC;
  }  
  else if(zgpGetDeviceParams()->secLevel == ZGP_SECURITY_LEVEL_1)
  {
    zgpMem.macReq.data.msduLength += ZGP_SEC_TWOBYTE_MIC;
  }
  zgpTxReq(&zgpMem.macReq.data);
  
  //To make Compiler happy
  conf = conf;    
}
/******************************************************************************
  \brief    to build and append the application information fields in commissioning payload
  \param    pointer to payload
  \return   none.
******************************************************************************/
#ifdef ZGP_APP_INFO_ENABLE
static void zgpBuildAndAppendAppInfo(uint8_t *payload, uint8_t* length)
{
  zgpCommAppInfo_t appInfo;
  uint16_t manufacturerId = MANUFACTURER_ID;
  uint16_t modelId = MODEL_ID;
  if(MANUFACTURER_ID != 0xFFFF)
    appInfo.manufacturerIdPresent = true;
  else
    appInfo.manufacturerIdPresent = false;
  
  if(MODEL_ID != 0xFFFF)
    appInfo.modelIdPresent = true;
  else
    appInfo.modelIdPresent = false;
  
  if(NO_OF_CLUSTERS != 0)
    appInfo.clusterListPresent = true;
  else
    appInfo.clusterListPresent = false;

  if(NO_OF_CMDS != 0)
    appInfo.gpdCommandsPresent = true;
  else
    appInfo.gpdCommandsPresent = false;
  appInfo.reserved = 0;
  // app info
  //appInfo = 0x08;
  memcpy(payload,&appInfo,1);
  *length += 1;
  payload++;

  if(appInfo.manufacturerIdPresent == true)
  {
    memcpy(payload, &manufacturerId, MANUFACTURER_ID_LEN);
    *length += MANUFACTURER_ID_LEN;
    payload += MANUFACTURER_ID_LEN;
  }

  if(appInfo.modelIdPresent == true)
  {
    memcpy(payload, &modelId, MODEL_ID_LEN);
    *length += MODEL_ID_LEN;
    payload += MODEL_ID_LEN;
  }
  
  if(appInfo.gpdCommandsPresent == true)
  {
    // commands
    uint8_t noOfCommands = NO_OF_CMDS;
    memcpy(payload,&noOfCommands,1);  
    *length += 1;
    payload++;
    // command list
    memcpy(payload, zgpCommandList, NO_OF_CMDS);
    *length += NO_OF_CMDS;
    payload += NO_OF_CMDS;
  }

  if(appInfo.clusterListPresent == true)
  {
       // length of cluster list
  uint8_t noOfClusters = NO_OF_SERVER_CLUSTERS + (NO_OF_CLIENT_CLUSTERS << 4);
  memcpy(payload,&noOfClusters,1);
  *length += 1;
  payload += 1;
  memcpy(payload,zgpClusterList,NO_OF_CLUSTERS *2);
  *length += NO_OF_CLUSTERS * 2;
  }
}
#endif
#endif //#ifdef ZGP_SECURITY_ENABLE
//eof  zgpCommissioninghandler.c
