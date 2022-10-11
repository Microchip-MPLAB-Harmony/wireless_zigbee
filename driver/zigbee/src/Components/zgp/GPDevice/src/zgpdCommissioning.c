/*******************************************************************************
  Zigbee green power device commissioning Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdCommissioning.c

  Summary:
    This file contains the zgp device commissioning implementation.

  Description:
    This file contains the zgp device commissioning implementation.
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
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdIb.h>
#include <zgp/include/zgpDbg.h>

/******************************************************************************
  \brief    This will initiate the commissioning request command
  \param    panIdReq - panId required
  \param    keyReq - key required/none
  \param    keyEnc - device has capability to encrypt/decrypt the key
  \param    ZGP_CommissionConf - commissioning confirmation callback
  \param    confirm - confirmation status
  \return   ZGP_Status_t.
******************************************************************************/
ZGP_Status_t ZGP_CommissionReq(ZGP_CommissioningReq_t *zgpCommissionReq)
{
  uint8_t commType = 0, secLevel = 0;
  bool rxAfterTx = false;
  
  if (NULL == zgpCommissionReq->ZGP_CommissionConf)
  {
    return(ZGP_INVALID_PARAMETER);
  }
  
  //RxAfterTx should be true, for Bidirectional commissioning
  CS_ReadParameter(CS_ZGP_COMMISSIONING_TYPE_ID, &commType);
  CS_ReadParameter(CS_ZGP_RX_AFTER_TX_ID, &rxAfterTx);
  CS_ReadParameter(CS_ZGP_SECURITY_LEVEL_ID, &secLevel);
  
  if ((ZGP_BIDIRECTIONAL_COMMISSIONING == commType) && 
      (false == rxAfterTx))
  {
    return(ZGP_COMMISSIONING_REQ_INVALID);
  }
  
  if ((ZGP_SECURITY_LEVEL_0 == secLevel) && (true == zgpCommissionReq->keyReq))
  {
    return(ZGP_COMMISSIONING_REQ_INVALID);
  }
  
  zgpCommissionReq->service.requestId = ZGP_COMMISSION_REQ_ID;
  zgpCommissionReq->service.presenceInQueue = zgpPutReqInQueue((void *)zgpCommissionReq);
  
  // if TX queue is full, call the confirmation with error status, post the corresponding task otherwise
  if(zgpCommissionReq->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_COMMISSIONING_ID);
  }
  else
  {
    return(ZGP_TX_QUEUE_FULL);
  }
  
  return(ZGP_SUCCESS_STATUS);
}

/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_SuccessGpdfConf - Success gpdf confirmation callback
  \param    confirm - confirmation status
  \return  ZGP_Status_t.
******************************************************************************/
ZGP_Status_t ZGP_SuccessGpdfReq(ZgpSuccessGpdfReq_t *zgpSuccessReq)
{
  if (NULL == zgpSuccessReq->ZGP_SuccessGpdfConf)
  {
    return(ZGP_INVALID_PARAMETER);
  }
  
  zgpSuccessReq->service.requestId = ZGP_SUCCESS_GPDF_REQ_ID;
  zgpSuccessReq->service.presenceInQueue = zgpPutReqInQueue((void *)zgpSuccessReq);
  
  // if TX queue is full, call the confirmation with error status, post the corresponding task otherwise
  if(zgpSuccessReq->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_COMMISSIONING_ID);
  }
  else
  {
    return(ZGP_TX_QUEUE_FULL);
  }
  
  return(ZGP_SUCCESS_STATUS);
}

/******************************************************************************
  \brief    This will initiate the success GPDF command
  \param    key - which will be used for Success gpdf encription
  \param    ZGP_SuccessGpdfConf - Success gpdf confirmation callback
  \param    confirm - confirmation status
  \return  ZGP_Status_t.
******************************************************************************/
ZGP_Status_t ZGP_DecommissioningReq(ZGP_DecommissioningReq_t *zgpDecommissioningReq)
{
  if (NULL == zgpDecommissioningReq->ZGP_DecommissioningConf)
  {
    return(ZGP_INVALID_PARAMETER);
  }
  
  zgpDecommissioningReq->service.requestId = ZGP_DECOMMISSIONING_REQ_ID;
  zgpDecommissioningReq->service.presenceInQueue = zgpPutReqInQueue((void *)zgpDecommissioningReq);
  
  // if TX queue is full, call the confirmation with error status, post the corresponding task otherwise
  if(zgpDecommissioningReq->service.presenceInQueue)
  {
    zgpPostTask(ZGP_TASK_COMMISSIONING_ID);
  }
  else
  {
    return(ZGP_TX_QUEUE_FULL);
  }
  
  return(ZGP_SUCCESS_STATUS);
}
//eof ZGP_Commissioning.c
