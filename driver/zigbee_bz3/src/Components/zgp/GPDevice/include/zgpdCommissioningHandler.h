/*******************************************************************************
  Zigbee green power commissioning handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdCommissioningHandler.h

  Summary:
    This file contains the zgpd commissioning core functionalities.

  Description:
    This file contains the zgpd commissioning core functionalities.
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

#ifndef ZGPDCOMMISSIONINGHANDLER_H
#define ZGPDCOMMISSIONINGHANDLER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#include <zgp/include/zgpDbg.h>


/******************************************************************************
                        Defines  section.
******************************************************************************/
#define ZGP_CHANNEL_START       11
#define ZGP_CHANNEL_END         26

#define ZGP_COMM_CMD_PAYLOAD_START           0
#define ZGP_COMM_PAYLOAD_CMD_ID_START        0
#define ZGP_COMM_PAYLOAD_CMD_ID_LEN          1
#define ZGP_COMM_PAYLOAD_DEVICE_ID_STRAT     (ZGP_COMM_PAYLOAD_CMD_ID_START + ZGP_COMM_PAYLOAD_CMD_ID_LEN)
#define ZGP_COMM_PAYLOAD_DEVICE_ID_LEN       1
#define ZGP_COMM_PAYLOAD_OPTIONS_STRAT       (ZGP_COMM_PAYLOAD_DEVICE_ID_STRAT + ZGP_COMM_PAYLOAD_DEVICE_ID_LEN)
#define ZGP_COMM_PAYLOAD_OPTIONS_LEN         1
#define ZGP_COMM_PAYLOAD_EXT_OPTIONS_STRAT   (ZGP_COMM_PAYLOAD_OPTIONS_STRAT + ZGP_COMM_PAYLOAD_OPTIONS_LEN)
#define ZGP_COMM_PAYLOAD_EXT_OPTIONS_LEN     1
#define ZGP_COMM_PAYLOAD_SEC_KEY_STRAT       (ZGP_COMM_PAYLOAD_EXT_OPTIONS_STRAT + ZGP_COMM_PAYLOAD_EXT_OPTIONS_LEN)
#define ZGP_COMM_PAYLOAD_SEC_KEY_LEN         16
#define ZGP_COMM_PAYLOAD_KEY_MIC_STRAT       (ZGP_COMM_PAYLOAD_SEC_KEY_STRAT + ZGP_COMM_PAYLOAD_SEC_KEY_LEN)
#define ZGP_COMM_PAYLOAD_KEY_MIC_LEN         4
#define ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_STRAT  (ZGP_COMM_PAYLOAD_KEY_MIC_STRAT + ZGP_COMM_PAYLOAD_KEY_MIC_LEN)
#define ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN    4
#define ZGP_COMM_PAYLOAD_APP_INFO_START      (ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_STRAT + ZGP_COMM_PAYLOAD_OUT_FRM_CNTR_LEN)

#define ZGP_COMM_KEY_HEADER_LEN              4
#define ZGP_COMM_PAYLOAD_KEY_OFFSET          ZGP_COMM_KEY_HEADER_LEN


#define ZGP_COMM_REPLY_PAYLOAD_START          0
#define ZGP_COMM_REPLY_CMD_ID_START           0
#define ZGP_COMM_REPLY_CMD_ID_LEN             1
#define ZGP_COMM_REPLY_OPTIONS_START          (ZGP_COMM_REPLY_CMD_ID_START + ZGP_COMM_REPLY_CMD_ID_LEN)
#define ZGP_COMM_REPLY_OPTIONS_LEN            1
#define ZGP_COMM_REPLY_PANID_START            (ZGP_COMM_REPLY_OPTIONS_START + ZGP_COMM_REPLY_OPTIONS_LEN)
#define ZGP_COMM_REPLY_PANID_LEN              2
#define ZGP_COMM_REPLY_SEC_KEY_START          (ZGP_COMM_REPLY_PANID_START + ZGP_COMM_REPLY_PANID_LEN)
#define ZGP_COMM_REPLY_SEC_KEY_LEN            16
#define ZGP_COMM_REPLY_KEY_MIC_START          (ZGP_COMM_REPLY_SEC_KEY_START + ZGP_COMM_REPLY_SEC_KEY_LEN)
#define ZGP_COMM_REPLY_KEY_MIC_LEN            4

#define ZGP_COMM_REPLY_KEY_TYPE_MASK          0xE0
#define ZGP_COMM_REPLY_KEY_TYPE_SHIFT         5

#define setOneShotTimer(ref, cb, time) \
    ref.mode = TIMER_ONE_SHOT_MODE;         \
    ref.callback = cb;                \
    ref.interval = time;

    
#define setCommissioningState(state)         \
    zgpGetStackParams()->commissioningState = state;

#define setCommissioningEvent(event)         \
    zgpGetStackParams()->commissioningEvent = event;

#define getCommissioningState(state)         \
    zgpGetStackParams()->commissioningState

#define getCommissioningEvent()         \
    zgpGetStackParams()->commissioningEvent
    

/******************************************************************************
                        Types section.
******************************************************************************/
typedef void (*commissioningCmdConfCallback)(MAC_DataConf_t *confirm);

typedef enum _zgpCommissioningEvents_t // events
{
  eCommIdle,
  eCommReq,
  eCommCommandTx,
  eTimer,
  eCommSuccess,
  eCommFailure,
  eCommReplyRcvd,
  eCommReplyOk,
  eCommReplyFail,
  eCommSuccessTx
}zgpCommissioningEvents_t;

typedef enum _zgpCommissionState_t
{
  sCommIdle,
  sCommCommandTx,
  sReplyWaiting,
  sCommReplyRx,
  sCommReplyOk,
  sCommSuccessTx,
  sCommDone
}zgpCommissionState_t;

BEGIN_PACK
typedef struct _ZgpCommissionCmdExtOptions_t
{
  uint8_t securityLevel        : 2;
  uint8_t securityKeyType      : 3;
  uint8_t GPDKeyPresent        : 1;
  uint8_t GPDKeyEncryption     : 1;
  uint8_t GPDOutgoingFrmCntr   : 1;
}ZgpCommissionCmdExtOptions_t;
END_PACK

BEGIN_PACK
typedef struct _ZgpCommissionCmdOptions_t
{
  uint8_t macSeqNumCapability  : 1;
  uint8_t rxOnCapability       : 1;
  uint8_t appInfo              : 1;
  uint8_t reserved             : 1;
  uint8_t panIdRequest         : 1;
  uint8_t securityKeyRequest   : 1;
  uint8_t fixedLocation        : 1;
  uint8_t extendedOptions      : 1;
}ZgpCommissionCmdOptions_t;
END_PACK

BEGIN_PACK
typedef struct _ZgpCommissionReplyOptions_t
{
  uint8_t panIdPresent         : 1;
  uint8_t GPDKeyPresent        : 1;
  uint8_t GPDKeyEncryption     : 1;
  uint8_t securityLevel        : 2;
  uint8_t securityKeyType      : 3;
}ZgpCommissionReplyOptions_t;
END_PACK

/* Commissioning command confirmation */
BEGIN_PACK
typedef struct _zgpCommissionConf_t
{
  ZGP_Status_t status;
}zgpCommissionConf_t;
END_PACK

/* Commissioning command confirmation */
BEGIN_PACK
typedef struct _zgpCommAppInfo_t
{
  uint8_t manufacturerIdPresent: 1;
  uint8_t modelIdPresent: 1;
  uint8_t gpdCommandsPresent: 1;
  uint8_t clusterListPresent: 1;
  uint8_t reserved: 4;
}zgpCommAppInfo_t;
END_PACK

/* Commissioning command confirmation callback */
typedef void (*zgpCommissioningCmdConf)(zgpCommissionConf_t *conf);

/******************************************************************************
                            Globals
******************************************************************************/


/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  \brief    handle all commissioning request
  \param    none.
  \return   none.
******************************************************************************/
void zgpCommissioningHandler(void);


/******************************************************************************
  \brief   This subscription will be used to register a commissioning callback,
              which will be used in Bidirectional commissioning
  \param   commissioningCB - Zgp commissioning callback
  \return  none.
******************************************************************************/
//void ZGP_SubscribeCommissioning(commissioningCallback_t commissioningCB);


/******************************************************************************
  \brief    This will initiate the commissioning request command
  \param    callback - commissioning confirmation callback
  \return  none.
******************************************************************************/
void zgpSendCommissioningReq(commissioningCmdConfCallback conf);


/******************************************************************************
  \brief    Set MAC Data Request parameters
  \param    macDataReq - MAC Data Req
  \param    handle - Mac Data Request handle
  \return  none.
******************************************************************************/
void zgpSetMacDataReqParams(MAC_DataReq_t *macDataReq, uint8_t cmdID);


/******************************************************************************
  \brief    This will fill the NWK Frame Control field and Extended NWK Frame 
              Control field
  \param    nwkFcf - NWK frame control fields. This parameter needs to be rest 
              before call this API
  \param    extNwkFcf - Extended NWK Frame Control fields. . This parameter 
              needs to be rest before call this API
  \param    cmd - command ID
  \return  none.
******************************************************************************/
void zgpFCFConstruct(ZGP_NwkFrameControl_t *nwkFcf, ZGP_ExtNwkFrameControl_t *extNwkFcf, uint8_t cmd);


/******************************************************************************
  \brief    This will fill the command header
  \param    cmd - command ID
  \return  none.
******************************************************************************/
void zgpBuildCommCommandHeader(uint8_t cmd);


/******************************************************************************
  \brief    This will fill the command payload
  \param    msduLength - pointer to command payload length
  \param    msduLength - pointer to command payload
  \return  none.
******************************************************************************/
void zgpBuildCommCommandPayload(uint8_t *msduLength, uint8_t *payload);


/******************************************************************************
  \brief    send commissioning command confirmation to application
  \param    confirm - confirmation status from MAC
  \return  none.
******************************************************************************/
void zgpCommTransmitConfirm(MAC_DataConf_t *confirm);


/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_SuccessGpdfConf - Success gpdf confirmation callback
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
void zgpSendSuccessGpdf(commissioningCmdConfCallback conf);


/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_DecommissioningConf - Decommissioning confirmation callback
  \param    confirm - confirmation status
  \return  none.
******************************************************************************/
void zgpSendDecommissioning(commissioningCmdConfCallback conf);


/******************************************************************************
  \brief    sends the commissioning payload less commands
  \param    cmd - command that needs to be sent
  \param    conf - confirmation callback for MAC data request
  \return  none.
******************************************************************************/
void zgpSendPayloadlessCommissioningCmd(uint8_t cmd, commissioningCmdConfCallback conf);


/******************************************************************************
  \brief    automated bidirectional commissioning handler
  \param    none.
  \return   none.
******************************************************************************/
void zgpBiCommissioningHandler(void);


/******************************************************************************
  \brief    automated decommissioning handler
  \param    none.
  \return   none.
******************************************************************************/
void zgpDecommissioningHandler(void);


/******************************************************************************
  \brief   creates IEEE address based on two SrcIds
  \param   none.
  \return  none.
******************************************************************************/
void zgpMakeIEEEAddrFromSrcAddr(ExtAddr_t *ieeeAddr, uint32_t *srcIDMsb, uint32_t *srcIDLsb);

#ifdef ZGP_SECURITY_ENABLE
/******************************************************************************
  \brief    fill necessary info for encryption
  \param    pdu - data to be encrypted
  \param    headerLen - length of header
  \param    payloadLen - length of payload
  \return   none.
******************************************************************************/
void zgpFillEncryptReq(uint8_t *pdu, uint8_t headerLen, uint8_t payloadLen);
#endif //ZGP_SECURITY_ENABLE

#endif //ZGPDCOMMISSIONINGHANDLER_H

//eof zgpdCommissioninghandler.h
