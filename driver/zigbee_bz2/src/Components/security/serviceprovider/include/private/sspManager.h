/*******************************************************************************
  Security Service Provider Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspManager.h

  Summary:
    This file contains the Security Service Provider management routines.

  Description:
    This file contains the Security Service Provider management routines.
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


#ifndef _SSPMANAGER_H
#define _SSPMANAGER_H

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <sysQueue.h>

/******************************************************************************
                             Definition section.
******************************************************************************/
#ifdef _SSP_USE_FLASH_FOR_CONST_DATA
  #include <sysTypes.h>
  #define HANDLERS_MEM  FLASH_VAR
  #define HANDLERS_GET(A, I) memcpy_P(A, &sspHandlers[I], sizeof(SspTask_t))
#else // _SSP_USE_FLASH_FOR_CONST_DATA
  #define HANDLERS_MEM
  #define HANDLERS_GET(A, I) (((A)->task) = sspHandlers[I].task)
#endif // _SSP_USE_FLASH_FOR_CONST_DATA

#if defined(_MAC_HW_AES_) || defined(_HAL_HW_AES_)
  #ifdef _LINK_SECURITY_
    #ifdef _R20_LEGACY_
    #define SSP_TASKS_LIST                      \
      {sspCalculateAuthenticMacTag1ReqHandler}, \
      {sspCalculateAuthenticMacTag2ReqHandler}, \
      {sspCalculateSkkeParamsReqHandler},       \
      {sspKeyedHashReqHandler},                 \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler}
    #else
    #define SSP_TASKS_LIST                      \
      {sspKeyedHashReqHandler},                 \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler}
    #endif
  #else // _LINK_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler}
  #endif // _LINK_SECURITY_

#elif defined(_SSP_SW_AES_)
  #ifdef _LINK_SECURITY_
    #ifdef _R20_LEGACY_
    #define SSP_TASKS_LIST                      \
      {sspCalculateAuthenticMacTag1ReqHandler}, \
      {sspCalculateAuthenticMacTag2ReqHandler}, \
      {sspCalculateSkkeParamsReqHandler},       \
      {sspKeyedHashReqHandler},                 \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler},                       \
      {sspAesReqHandler}
    #else // _R20_LEGACY_
    #define SSP_TASKS_LIST                      \
      {sspKeyedHashReqHandler},                 \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler},                       \
      {sspAesReqHandler}
    #endif //    _R20_LEGACY_
  #else // _LINK_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspCcmReqHandler},                       \
      {sspAesReqHandler}
  #endif // _LINK_SECURITY_
#else
  #error Unknown AES routine provider
#endif

#ifdef ZGP_SECURITY_ENABLE
  #define ZGP_SSP_TASKS_LIST                  \
	{sspZgpEncryptFrameReqHandler}, 		  \
	{sspZgpDecryptFrameReqHandler}
#endif

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  void (*task)(void);
} SspTask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum
{
#ifdef _LINK_SECURITY_
  #ifdef _R20_LEGACY_
    SSP_TASK_AUTHENTIC_MAC_TAG1,
    SSP_TASK_AUTHENTIC_MAC_TAG2,
    SSP_TASK_SKKE,
  #endif
  SSP_TASK_KEYED_HASH,
#endif // _LINK_SECURITY_
  SSP_TASK_ENCRYPT_FRAME,
  SSP_TASK_DECRYPT_FRAME,
  SSP_TASK_CCM_REQ,
#ifdef _SSP_SW_AES_
  SSP_TASK_AES,
#endif // _SSP_SW_AES_
#ifdef ZGP_SECURITY_ENABLE
  SSP_TASK_ZGP_ENCRYPT_FRAME,
  SSP_TASK_ZGP_DECRYPT_FRAME,
#endif /* ZGP_SECURITY_ENABLE */
  SSP_TASKS_SIZE,
} SspTaskId_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum  // ssp possible requests' types.
{
#ifdef _LINK_SECURITY_
  #ifdef _R20_LEGACY_
    SSP_REQ_ID_AUTHENTIC_MAC_TAG1 = SSP_TASK_AUTHENTIC_MAC_TAG1,
    SSP_REQ_ID_AUTHENTIC_MAC_TAG2 = SSP_TASK_AUTHENTIC_MAC_TAG2,
    SSP_REQ_ID_SKKE               = SSP_TASK_SKKE,
  #endif
  SSP_REQ_ID_KEYED_HASH         = SSP_TASK_KEYED_HASH,
#endif // _LINK_SECURITY_
  SSP_REQ_ID_SFP_ENCRYPT_FRAME  = SSP_TASK_ENCRYPT_FRAME,
  SSP_REQ_ID_SFP_DECRYPT_FRAME  = SSP_TASK_DECRYPT_FRAME,
  SSP_REQ_ID_CCM_REQ            = SSP_TASK_CCM_REQ,
#ifdef ZGP_SECURITY_ENABLE
  SSP_REQ_ID_SFP_ZGP_ENCRYPT_FRAME = SSP_TASK_ZGP_ENCRYPT_FRAME,
  SSP_REQ_ID_SFP_ZGP_DECRYPT_FRAME = SSP_TASK_ZGP_DECRYPT_FRAME
#endif /* ZGP_SECURITY_ENABLE */
} SspRequestId_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef uint16_t SspTaskBitMask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  SspTaskBitMask_t  taskBitMask;
  QueueDescriptor_t reqQueueDescr;
} SspManagerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void sspPostTask(SspTaskId_t taskID);

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void sspResetTaskManager(void);

/******************************************************************************
 Sends confirmation to the SSP user.
 Parameters:
   request - parameters of the request to be confirmed.
 Returns:
   none.
******************************************************************************/
void sspSendConfToUpperLayer(void *request);

/**************************************************************************//**
  \brief Resets SSP manager.
 ******************************************************************************/
void sspResetManager(void);

#endif // _SSPMANAGER_H

// eof sspManager.h
