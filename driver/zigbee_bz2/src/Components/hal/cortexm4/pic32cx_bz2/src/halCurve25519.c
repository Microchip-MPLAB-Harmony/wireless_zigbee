/*******************************************************************************
  HAL Curve25519 Source File

  Company:
    Microchip Technology Inc.

  File Name:
    hal_curve25519.c

  Summary:
    This file contains the Implementation BitCloud HAL Curve25519 for pic32cx.

  Description:
    This file contains the Implementation BitCloud HAL Curve25519 for pic32cx.
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
#include <hal/cortexm4/pic32cx/include/halCurve25519.h>
#include <hal/cortexm4/pic32cx/include/halDbg.h>
#include <systemenvironment/include/sysQueue.h>
#include <hal/include/halTaskManager.h>
#include <systemenvironment/include/sysAssert.h>

#ifdef _ZIGBEE_REV_23_SUPPORT_
//Instance of Crypto
static CRYPT_CURVE25519_CTX curve25519Ctx;
static CRYPT_RNG_CTX rng;
static HAL_Curve25519_Req_t req;

static DECLARE_QUEUE(halCurve25519RequestQueue);

/**************************************************************************//**
\brief HAL Curve25519 Key Function Request

\param[out] None
\param[in] reqParams_s - request structure of Curve25519
\return None
******************************************************************************/
void HAL_CURVE25519_KeyReq(HAL_Curve25519_Req_t *reqParams_s)
{
  memcpy(&req,reqParams_s,sizeof(HAL_Curve25519_Req_t));
  halPostTask(HAL_CURVE25519_REQ);
}

/**************************************************************************//**
\brief HAL Curve25519 State Machine Reset

\param[out] None
\param[in] None
\return None
******************************************************************************/
void HAL_CURVE25519_SmReset(void)
{
  resetQueue(&halCurve25519RequestQueue);
  halClearTask(HAL_CURVE25519_REQ);
}

/**************************************************************************//**
\brief Curve25519 HAL Handling of request

\param[out] None
\param[in] None
\return None
******************************************************************************/
void halCurve25519SmRequestHandler(void)
{
  HAL_Curve25519_Req_t *reqParams = NULL;
  int error = 0;

  reqParams = &req;

  if (NULL != reqParams)
  {
    switch (reqParams->cmd)
    {
      case SM_INIT_COMMAND:
    
        error = CRYPT_Curve25519_Init(&curve25519Ctx, &rng);

        if (error == 0)
          error = CRYPT_CURVE25519_Make_Key(&curve25519Ctx, &rng, reqParams->privateKeySize);
        break;

      case SM_GENERATE_PUBLIC_KEY_COMMAND:
        error = CRYPT_CURVE25519_Generic(&curve25519Ctx, reqParams->publicKeySize, reqParams->publicKey, reqParams->basePointSize, reqParams->basePoint);
        break;

      case SM_FREE_KEY:
        CRYPT_CURVE25519_Free(&curve25519Ctx);
        break;

      default:
        SYS_E_ASSERT_FATAL(false, HAL_CURVE25519);
        break;
    }

    SYS_E_ASSERT_FATAL(reqParams->curve25519Conf, HAL_CURVE25519);
    SYS_E_ASSERT_ERROR(error != 0, HAL_CURVE25519);
    reqParams->curve25519Conf();
  }
}
#endif //_ZIGBEE_REV_23_SUPPORT_