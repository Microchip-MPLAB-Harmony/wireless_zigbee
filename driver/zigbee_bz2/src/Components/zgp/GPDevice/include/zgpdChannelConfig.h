/*******************************************************************************
  Zigbee green power channel config Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdChannelConfig.h

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

#ifndef ZGPDCHANNELCONFIG_H
#define ZGPDCHANNELCONFIG_H
/******************************************************************************
                        Includes section.
******************************************************************************/
#include <zgp/GPDevice/include/zgpdDataHandler.h>
/******************************************************************************
                        Defines section.
******************************************************************************/
#define ZGP_CHANNELREQ_CMD_PAYLOAD_START     1
#define ZGP_CHANNELREQ_PAYLOAD_LEN           1

#define ZGP_CHANNEL_CONFIG_OPERCH_MASK       0x0F
#define ZGP_CHANNEL_CONFIG_UNIDIR_MASK       0x10
#define ZGP_CHREQ_NXT_CHANNEL_DELAY          2000
#define ZGP_CHANNEL_CONFIG_WAIT_DELAY        50

#define setChannelConfigState(state)         \
    zgpGetStackParams()->channelConfigState = state;

#define getChannelConfigState(state)         \
    zgpGetStackParams()->channelConfigState
/******************************************************************************
                        Types section.
******************************************************************************/
/* Channel Req confirmation */
BEGIN_PACK
typedef struct _ZGP_ChannelReqConf_t
{
  ZGP_Status_t status;
}ZGP_ChannelReqConf_t;
END_PACK

/* channel Request parameters */
BEGIN_PACK
typedef struct _ZGP_ChannelReq_t
{
  ZGP_Service_t service;
  uint8_t firstRxChannel;
  uint8_t secondRxChannel;
  void (*ZGP_ChannelReqConf)(ZGP_ChannelReqConf_t *conf);
  ZGP_ChannelReqConf_t confirm;
}ZGP_ChannelReq_t;
END_PACK
typedef enum _zgpChannelConfigState_t
{
  sChannelConfigIdle = 0,
  sChannelReqTx,
  sChannelReqTxDone,
  sChannelConfigWaiting,
  sChannelConfigDone
}zgpChannelConfigState_t;
/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  \brief    Handles the channel request and config procedure. Two Channel requests
            are sent in each channel, device opens rxWindow in every second request 
            and waits for channel config. Once the operating channel is fixed, 
            commissioning shall happen.
  \param    none.
  \return   none.
******************************************************************************/
void zgpChannelReqHandler(void);
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
ZGP_Status_t ZGP_ChannelReq(ZGP_ChannelReq_t *zgpChannelReq);
/******************************************************************************
  \brief    handles received channel config command
  \param    none.
  \return   none.
******************************************************************************/
void zgpChannelConfigInd(ZGP_DataInd_t *zgpChannelConfigInd);
#endif // ZGPDCHANNELCONFIG_H
//eof zgpdChannelConfig.h
