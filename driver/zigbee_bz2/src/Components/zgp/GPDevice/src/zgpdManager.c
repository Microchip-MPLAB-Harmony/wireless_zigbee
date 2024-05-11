/*******************************************************************************
  Zigbee green power manager Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdManager.c

  Summary:
    This file contains the ZGP layer request manager.

  Description:
    This file contains the ZGP layer request manager.
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
#include <systemenvironment/include/sysQueue.h>
#include <systemenvironment/include/sysTaskManager.h>
#include <zgp/GPDevice/include/zgpdMemAccess.h>
#include <zgp/GPDevice/include/zgpdManager.h>
#include <zgp/GPDevice/include/zgpdResetHandler.h>
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdCommissioning.h>
#include <zgp/GPDevice/include/zgpdCommissioningHandler.h>
#include <zgp/GPDevice/include/zgpdChannelConfig.h>
#include <zgp/GPDevice/include/zgpdCommon.h>
/******************************************************************************
                    Define(s) section
******************************************************************************/
#define HANDLERS_GET(A, I) memcpy_P(A, &zgpHandlers[I], sizeof(ZgpTask_t))
/******************************************************************************
                    Types section
******************************************************************************/
/** Pointer to a ZGP task handler. */
typedef void (* ZgpTask_t)(void);
/** Type of task in progmem. */
typedef PROGMEM_DECLARE(ZgpTask_t) ZgpProgmemTask_t;

/******************************************************************************
                    Constants section
******************************************************************************/
/** Array of ZGP task handlers. */
static const ZgpProgmemTask_t zgpHandlers[ZGP_TASKS_SIZE] =
{
  [ZGP_TASK_INIT_ID]      = zgpInitHandler,
  [ZGP_TASK_RESET_REQ_ID] = zgpResetReqHandler,
  [ZGP_TASK_DATA_REQ_ID] = zgpDataReqHandler,
#ifdef _COMMISSIONING_
  [ZGP_TASK_CHANNEL_REQ_ID] = zgpChannelReqHandler,
  [ZGP_TASK_COMMISSIONING_ID] = zgpCommissioningHandler
#endif
};
/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
                    Static functions prototypes section
******************************************************************************/
/******************************************************************************
                    Global variables section
******************************************************************************/
static ZgpTaskBitMask_t zgpTaskBitMap = (1U << ZGP_TASK_INIT_ID);
static ZgpTaskIdIter_t zgpCurrentTask = 0U;
/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
 \brief Changes current managerState.
 \param state - state to be set.
 \return none.
******************************************************************************/
static inline void setState(ZgpState_t state)
{
  zgpGetMem()->managerState = state;
}

/******************************************************************************
 \brief Gets current managerState.
 \param none.
 \return current managerState.
******************************************************************************/
static inline ZgpState_t getState(void)
{
  return zgpGetMem()->managerState;
}
/******************************************************************************
 \brief  Stores regquest to ZGP queue.
 \param  request - request to be store.
 \return none.
******************************************************************************/
bool zgpPutReqInQueue(void *request)
{    
    if (ZGP_IDLE_STATE == getState())
    {
      putQueueElem(&zgpGetMem()->reqQueueDescr, request);
      return true;
    }
    return false;
}
/**************************************************************************//**
  \brief Prepare to run same ZGP task handler.

  \param[in] taskId - identifier of ZGP task.
  \returns None.
 ******************************************************************************/
void zgpPostTask(const ZgpTaskID_t taskID)
{
  zgpTaskBitMap |= (1UL << taskID);
  SYS_PostTask(ZGP_TASK_ID);
}

/******************************************************************************
  \brief Cancel ZGP task.

  \param[in] mask - bit mask of NWK task dentifier.
  \return None.
 ******************************************************************************/
void zgpClearTaskBit(const ZgpTaskBitMask_t mask)
{
  zgpTaskBitMap &= ~mask;
}
/******************************************************************************
  \brief  Main system entry point.
  \param  none.
  \return none.
******************************************************************************/
void ZGP_TaskHandler(void)
{
  void *zgpRequest = getQueueElem(&zgpGetMem()->reqQueueDescr);
  const ZgpTaskIdIter_t last = zgpCurrentTask;
  do
  {
    if (ZGP_TASKS_SIZE <= ++zgpCurrentTask)
      zgpCurrentTask = 0U;

    if (zgpTaskBitMap & (1UL << zgpCurrentTask))
    {
      ZgpTask_t handler;
      
      zgpTaskBitMap ^= 1UL << zgpCurrentTask; /* &=~ */
      HANDLERS_GET(&handler, zgpCurrentTask);
      //sysAssert(handler, NWKTASKMANAGER_NWKTASKHANDLER0);
      if(zgpRequest != NULL)
      {
        zgpStoreReqParams(zgpRequest);
        setState((ZgpState_t)((ZGP_Service_t *)zgpRequest)->requestId);
      }
      handler();
      break;
    }
  } while (last != zgpCurrentTask);

  if (zgpTaskBitMap)
    SYS_PostTask(ZGP_TASK_ID);
}
/******************************************************************************
 \brief  Sends confirmation to the upper layer.
 \param  request - parameters of the request to be confirmed.
 \return none.
******************************************************************************/
void zgpSendConfToUpperLayer(void *request)
{
  switch((ZgpRequestId_t)((ZGP_Service_t *)request)->requestId)
  {
    case ZGP_RESET_REQ_ID:
      sysAssert((NULL != ((ZGP_ResetReq_t *)request)->ZGP_ResetConf), ZGPD_INVALIDCALLBACK);
      ((ZGP_ResetReq_t *)request)->ZGP_ResetConf(&((ZGP_ResetReq_t *)request)->confirm);
      break;

    case ZGP_DATA_REQ_ID:
      sysAssert((NULL != ((ZGP_DataReq_t *)request)->ZGP_DataConf), ZGPD_INVALIDCALLBACK);
      ((ZGP_DataReq_t *)request)->ZGP_DataConf(&((ZGP_DataReq_t *)request)->confirm);
      break;
    
    case ZGP_CHANNEL_REQ_ID:
      sysAssert((NULL != ((ZGP_ChannelReq_t *)request)->ZGP_ChannelReqConf), ZGPD_INVALIDCALLBACK);
      ((ZGP_ChannelReq_t *)request)->ZGP_ChannelReqConf(&((ZGP_ChannelReq_t *)request)->confirm);
      break;
     
    case ZGP_COMMISSION_REQ_ID:
      sysAssert((NULL != ((ZGP_CommissioningReq_t *)request)->ZGP_CommissionConf), ZGPD_INVALIDCALLBACK);
      ((ZGP_CommissioningReq_t *)request)->ZGP_CommissionConf(&((ZGP_CommissioningReq_t *)request)->confirm);
      break;
        
    case ZGP_DECOMMISSIONING_REQ_ID:
      sysAssert((NULL != ((ZGP_DecommissioningReq_t *)request)->ZGP_DecommissioningConf), ZGPD_INVALIDCALLBACK);
      ((ZGP_DecommissioningReq_t *)request)->ZGP_DecommissioningConf(&((ZGP_DecommissioningReq_t *)request)->confirm);
      break;
      
    case ZGP_SUCCESS_GPDF_REQ_ID:
      sysAssert((NULL != ((ZgpSuccessGpdfReq_t *)request)->ZGP_SuccessGpdfConf), ZGPD_INVALIDCALLBACK);
      ((ZgpSuccessGpdfReq_t *)request)->ZGP_SuccessGpdfConf(&((ZgpSuccessGpdfReq_t *)request)->confirm);
      break;
    default:
      sysAssert(0, ZGPD_INVALIDREQUESTID);
      return;    
  }
  
  // delete the queue element only if something was queued
  if((ZgpRequestId_t)((ZGP_Service_t *)request)->presenceInQueue)
  {
    setState(ZGP_IDLE_STATE);
    deleteHeadQueueElem(&zgpGetMem()->reqQueueDescr);
  }
}


//eof zgpManager.c
