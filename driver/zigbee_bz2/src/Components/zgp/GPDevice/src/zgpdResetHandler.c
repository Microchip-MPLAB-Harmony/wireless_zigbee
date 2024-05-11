/*******************************************************************************
  Zigbee green power reset handler Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdResetHandler.c

  Summary:
    This file contains the zgpd reset primitives implementation.

  Description:
    This file contains the zgpd reset primitives implementation.
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
#include <systemenvironment/include/sysTaskManager.h>
#include <zgp/GPDevice/include/zgpdResetHandler.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <zgp/GPDevice/include/zgpdMemAccess.h>
#include <configserver/include/configserver.h>
/******************************************************************************
                    Define(s) section
******************************************************************************/

/******************************************************************************
                    Types section
******************************************************************************/

/******************************************************************************
                    Constants section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/
extern void APP_EvtUpload(void);
/******************************************************************************
                    Static functions prototypes section
******************************************************************************/
static void zgpInitMacConfirm(MAC_ResetConf_t *conf);
static void zgpResetMacConfirm(MAC_ResetConf_t *conf);
static void zgpChannelMacSetConfirm(MAC_SetConf_t *conf);
static void zgpMacSetConfirm(MAC_SetConf_t *conf);
/******************************************************************************
                    Global variables section
******************************************************************************/
extern ZGP_Mem_t zgpMem;
/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
  \brief To raise ZGP reset Req
  \param reqParams - reset request parameters structure.
  \return none.
******************************************************************************/
void ZGP_ResetReq(ZGP_ResetReq_t *reqParams)
{
  reqParams->service.requestId = ZGP_RESET_REQ_ID;
  reqParams->service.presenceInQueue =  zgpPutReqInQueue((void *)reqParams);
  // if TX queue is full, call the confirmation with error status, post the corresponding task otherwise
  if(reqParams->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_RESET_REQ_ID);
  }
  else
  {
     // pass the status
    reqParams->confirm.status = ZGP_TX_QUEUE_FULL;
    zgpSendConfToUpperLayer((void *)reqParams);   
  }
}
/******************************************************************************
  \brief Initialize congifuration parameters in config server 
  and raise MAC reset request
  \param  none
  \return none.
******************************************************************************/
void zgpInitHandler(void)
{
  ZB_CS_SYS_IBData_t zgbIBdata = {0};
  CS_Init(&zgbIBdata);
  zgpResetZgib();
#ifdef _COMMISSIONING_      
  // Check for factoryNew status & restore the ZGP parameters
  PDS_Restore(ZGP_FACTORYNEW_MEM_ID);
  if (!isFactoryNew)
  {
    restoreAllParamsFromNvm();
  }
#endif
  zgpMem.macReq.reset.setDefaultPib = true;
  zgpMem.macReq.reset.MAC_ResetConf = zgpInitMacConfirm; 
  MAC_ResetReq(&zgpMem.macReq.reset); 
}
/******************************************************************************
  \brief Confirm of reset request.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
static void zgpInitMacConfirm(MAC_ResetConf_t *conf)
{
  zgpMem.macReq.set.attrId.phyPibId = PHY_PIB_CURRENT_CHANNEL_ID;
  zgpMem.macReq.set.attrValue.phyPibAttr.channel = zgpGetStackParams()->Channel;
  zgpMem.macReq.set.MAC_SetConf = zgpChannelMacSetConfirm;
  MAC_SetReq(&zgpMem.macReq.set);
  
  //To make Compiler happy
  conf = conf; 
}
/**************************************************************************//**
  \brief Confirm form MAC for channel set request.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
static void zgpChannelMacSetConfirm(MAC_SetConf_t *conf)
{
  APP_EvtUpload();
  //To make Compiler happy
  conf = conf;
}
/******************************************************************************
  \brief Initialize congifuration parameters in config server 
  and raise MAC reset request
  \param    none.
  \return   none.
******************************************************************************/
void zgpResetReqHandler(void)
{
  ZB_CS_SYS_IBData_t zgbIBdata = {0};
  CS_Init(&zgbIBdata);  
  zgpMem.macReq.reset.setDefaultPib = true;
  zgpMem.macReq.reset.MAC_ResetConf = zgpResetMacConfirm; 
  MAC_ResetReq(&zgpMem.macReq.reset);  
}

/******************************************************************************
  \brief Confirm of reset request.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
static void zgpResetMacConfirm(MAC_ResetConf_t *conf)
{
  ZGP_ResetReq_t  *resetReq = (ZGP_ResetReq_t *)zgpGetReqParams();
  zgpSendConfToUpperLayer((void *)resetReq);

  //To make Compiler happy
  conf = conf;
}
/******************************************************************************
  \brief set zgp channel.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
void ZGP_SetChannel(uint8_t channel)
{
  zgpGetStackParams()->Channel = channel;
  zgpMem.macReq.set.attrId.phyPibId = PHY_PIB_CURRENT_CHANNEL_ID;
  zgpMem.macReq.set.attrValue.phyPibAttr.channel = channel;
  zgpMem.macReq.set.MAC_SetConf = zgpMacSetConfirm;
  MAC_SetReq(&zgpMem.macReq.set); 
}
/**************************************************************************//**
  \brief Confirm form MAC for channel set request.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
static void zgpMacSetConfirm(MAC_SetConf_t *conf)
{
  //To make Compiler happy
  conf = conf;   
}
/******************************************************************************
  \brief get zgp channel.
  \param conf - confirm structure.
  \return none.
******************************************************************************/
void ZGP_GetChannel(uint8_t *channel)
{
  *channel = zgpGetStackParams()->Channel;
}
// eof rzgpResetHandler.c
