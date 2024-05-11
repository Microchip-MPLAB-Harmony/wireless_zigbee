/*******************************************************************************
  Zigbee Cluster Library OTAU Manager Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zclOtauManager.c

  Summary:
    The file implements the common OTAU stuffs (task handler etc).

  Description:
    The file implements the common OTAU stuffs (task handler etc).
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

#if APP_USE_OTAU == 1 && defined(_ZCL_SUPPORT_) 

/******************************************************************************
                   Includes section
******************************************************************************/
#include <zclOtauManager.h>
#if APP_DEVICE_OTAU_LOGGING == 1
#include <console.h>
#endif
#include <sysAssert.h>
#include <sysIdleHandler.h>
/******************************************************************************
                   Static functions prototype section
******************************************************************************/
#ifndef ZAPPSI_HOST
static void isZclOtauBusyOrPollRequest(SYS_EventId_t eventId, SYS_EventData_t data);
#endif

/******************************************************************************
                   Global variables section
******************************************************************************/
ZclOtauMem_t zclOtauMem;
bool isOtauBusy = false;
bool genericTimerArmed = false;

#ifndef ZAPPSI_HOST
static SYS_EventReceiver_t zclOtauBusyPollCheck = { .func = isZclOtauBusyOrPollRequest};
#endif

/******************************************************************************
                   Implementation section
******************************************************************************/
/***************************************************************************//**
\brief Checks whether OTAU cluster is busy or not.

\return true - if OTAU cluster is busy, false - otherwise.
******************************************************************************/
bool zclIsOtauBusy(void)
{
  return isOtauBusy;
}
 
/***************************************************************************//**
\brief Checks whether ZCL OTAU is busy or not.

\return true - if ZCL OTAU is busy, false - otherwise.
******************************************************************************/
bool ZCL_IsOtauBusy(void)
{
#ifdef _SLEEP_WHEN_IDLE_
  if (SYS_IsSleepWhenIdleEnabled())
    return false;
  else
#endif
    return zclIsOtauBusy(); 
}

#ifndef ZAPPSI_HOST
/**************************************************************************//**
  \brief Processes BC_EVENT_BUSY_REQUEST request

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data
 ******************************************************************************/
static void isZclOtauBusyOrPollRequest(SYS_EventId_t eventId, SYS_EventData_t data)
{
  bool *check = (bool *)data;

  if (BC_EVENT_BUSY_REQUEST == eventId)
    *check &= !ZCL_IsOtauBusy();
#if defined _ENDDEVICE_ && defined _SLEEP_WHEN_IDLE_
  else if (BC_EVENT_POLL_REQUEST == eventId)
    *check |= zclIsOtauBusy();
#endif
}

#endif  /* ZAPPSI_HOST */

/***************************************************************************//**
\brief OTAU parametres initialization. Start server discovery procedure
 on client side or start server.

\param[in] pInitParam - pointer to init structure.
\param[in] ind        - indication for OTAU actions \n
("ind" can be NULL if indication is not required.)
******************************************************************************/
ZCL_Status_t ZCL_StartOtauService(ZCL_OtauInitParams_t *pInitParam, ZCL_OtauStatInd_t ind)
{

#ifndef ZAPPSI_HOST
  SYS_SubscribeToEvent(BC_EVENT_BUSY_REQUEST, &zclOtauBusyPollCheck);
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zclOtauBusyPollCheck);
#endif

  if (NULL == pInitParam)
  {
    SYS_E_ASSERT_WARN(false, ZCL_OTAU_NULL_POINTER_TO_INIT_STRUCTURE);
    return ZCL_INVALID_PARAMETER_STATUS;
  }

  zclOtauMem.initParam = *pInitParam;
  zclOtauMem.otauInd = ind;

  if (ZCL_CLIENT_CLUSTER_TYPE == pInitParam->clusterSide)
  {
#ifdef OTAU_CLIENT
    zclStartOtauClient();
#endif
  }
  else
  {
#ifdef OTAU_SERVER
    zclStartOtauServer();
#endif
  }
  return ZCL_SUCCESS_STATUS;
}

/***************************************************************************//**
\brief Stop OTAU service. If image uploading was in progress, than process is finished.

\param[in] pInitParam - pointer to init structure.

\return Service status
******************************************************************************/
ZCL_Status_t ZCL_StopOtauService(ZCL_OtauInitParams_t *pInitParam)
{
  if (NULL == pInitParam)
  {
    SYS_E_ASSERT_WARN(false, ZCL_OTAU_NULL_POINTER_TO_INIT_STRUCTURE);
    return (ZCL_INVALID_PARAMETER_STATUS);
  }

  if (ZCL_SERVER_CLUSTER_TYPE == pInitParam->clusterSide)
    zclStopOtauServer();
  else
    zclStopOtauClient();

  return ZCL_SUCCESS_STATUS;
}

/***************************************************************************//**
\brief Lift otau cluster for customer.

\param[in] action - the OTAU action for a customer.
******************************************************************************/
void zclRaiseCustomMessage(const ZCL_OtauAction_t action)
{
  SYS_E_ASSERT_FATAL((action < OTAU_MAX_MESSAGE_NUMBER), ZCL_UNKNOWN_CUSTOM_MESSAGE);

  if (zclOtauMem.otauInd)
    zclOtauMem.otauInd(action);
}

/***************************************************************************//**
\brief Clear otau client memory.
******************************************************************************/
#ifdef OTAU_CLIENT
void zclClearOtauClientMemory(void)
{
  ZCL_OtauClientMem_t *clientMem = zclGetOtauClientMem();

  CS_ReadParameter(CS_ZCL_OTAU_DISCOVERED_SERVER_AMOUNT_ID, &clientMem->discoveredServerAmount);
  CS_GetMemory(CS_ZCL_OTAU_DISCOVERED_SERVER_RESULT_ID, (void *)&clientMem->discoveredServerMem);
  memset(clientMem->discoveredServerMem, 0x00, sizeof(ZclOtauDiscoveryResult_t) * clientMem->discoveredServerAmount);

#if APP_SUPPORT_OTAU_PAGE_REQUEST == 1
#if OTAU_BITCLOUD_LEGACY_SUPPORT == 1

  CS_GetMemory(CS_ZCL_OTAU_MISSED_BYTES_MASK_ID, (void *)&clientMem->missedBytesMask);

  CS_GetMemory(CS_ZCL_OTAU_PAGE_REQUEST_PAGE_BUFFER_ID, (void *)&clientMem->otauParam.imagePageData);
#else // if OTAU_BITCLOUD_LEGACY_SUPPORT =0
  CS_GetMemory(CS_ZCL_OTAU_PAGE_REQUEST_PAGE_BUFFER_ID, (void *)&clientMem->otauParam.receivedBlockPayload);
#endif
#endif // APP_SUPPORT_OTAU_PAGE_REQUEST == 1
}
#endif
/***************************************************************************//**
\brief Restart poll timer

\param[in] period - timer fired time
\param[in] cb     - pointer to fired method
******************************************************************************/
void otauStartGenericTimer(uint32_t period, void (* cb)(void))
{
  ZclOtauMem_t *otauMem = zclGetOtauMem();
  HAL_AppTimer_t *tmpTimer = &otauMem->genericTimer;

  HAL_StopAppTimer(tmpTimer);
  tmpTimer->interval  = period;
  tmpTimer->mode      = TIMER_ONE_SHOT_MODE;
  tmpTimer->callback  = cb;

  HAL_StartAppTimer(tmpTimer);
}

/***************************************************************************//**
\brief Stop poll timer
******************************************************************************/
void otauStopGenericTimer(void)
{
  ZclOtauMem_t *otauMem = zclGetOtauMem();
  HAL_AppTimer_t *tmpTimer = &otauMem->genericTimer;

  HAL_StopAppTimer(tmpTimer);
}
#endif // (_ZCL_SUPPORT_ == 1) 

// eof zclOtauManager.c
