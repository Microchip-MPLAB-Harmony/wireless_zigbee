/*******************************************************************************
  HAL Sha256 Source File

  Company:
    Microchip Technology Inc.

  File Name:
    halSha256.c

  Summary:
    This file contains the Implementation BitCloud HAL Sha256 for pic32cx.

  Description:
    This file contains the Implementation BitCloud HAL Sha256 for pic32cx.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#if defined(__ICCARM__)
#include <pic32cx1012bz25048.h>
#elif defined (__GNUC__)
#include <xc.h>
#endif

#include "configuration.h"
#include <hal/cortexm4/pic32cx/include/halSha256.h>
#include <hal/cortexm4/pic32cx/include/halDbg.h>
#include <systemenvironment/include/sysQueue.h>
#include <hal/include/halTaskManager.h>
#include <systemenvironment/include/sysAssert.h>

#ifdef _ZIGBEE_REV_23_SUPPORT_
//Instance of Crypto
static CRYPT_SHA256_CTX sha256Ctx;
static HAL_SHA256_Req_t req;
static DECLARE_QUEUE(halSha256RequestQueue);

/**************************************************************************//**
\brief HAL Sha256 Generation Request

\param[in] reqParams_s - request structure of Sha256
\return none
******************************************************************************/
void HAL_SHA256_Req(HAL_SHA256_Req_t *reqParams_s)
{
  memcpy(&req, reqParams_s, sizeof(HAL_SHA256_Req_t));
  halPostTask(HAL_SHA256_REQ);
}

/**************************************************************************//**
\brief HAL Sha256 State Machine Reset

\param[in] none
\return none
******************************************************************************/
void HAL_SHA256_SmReset(void)
{
  resetQueue(&halSha256RequestQueue);
  halClearTask(HAL_SHA256_REQ);
}

/**************************************************************************//**
\brief HAL Sha256 request handler

\param[in] none
\return none
******************************************************************************/
void halSha256SmRequestHandler(void)
{
  HAL_SHA256_Req_t *reqParams = NULL;
  int error = 0;

  reqParams = &req;

  if (NULL != reqParams)
  {
    switch (reqParams->cmd)
    {
      case SM_SHA256_INIT_COMMAND:
        error = CRYPT_SHA256_Initialize(&sha256Ctx);
        break;

      case SM_SHA256_DATA_ADD_COMMAND:
        error = CRYPT_SHA256_DataAdd(&sha256Ctx, reqParams->message, reqParams->messageSize);
        break;

      case SM_SHA256_FINALIZE_COMMAND:
        CRYPT_SHA256_Finalize(&sha256Ctx, reqParams->hash);
        break;

      default:
        SYS_E_ASSERT_FATAL(false, HAL_SHA256);
        break;
    }

    SYS_E_ASSERT_FATAL(reqParams->sha256Conf, HAL_SHA256);
    SYS_E_ASSERT_ERROR(error != 0, HAL_SHA256);
    reqParams->sha256Conf();
  }
}
#endif //_ZIGBEE_REV_23_SUPPORT_