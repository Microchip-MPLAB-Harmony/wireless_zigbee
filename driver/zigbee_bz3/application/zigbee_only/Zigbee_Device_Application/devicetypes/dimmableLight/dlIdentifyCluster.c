/*******************************************************************************
  Dimmable Light Identify cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlIdentifyCluster.c

  Summary:
    This file contains the Dimmable Light Identify cluster interface.

  Description:
    This file contains the Dimmable Light Identify cluster interface.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlIdentifyCluster.h>
#include <identifyCluster.h>
#include <haClusters.h>
#include <console.h>
#include <zclCommandManager.h>
#include <pdsDataServer.h>
#include <z3Device.h>
#include <ezModeManager.h>
#include <leds.h>
#include <dimmableLight.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define IDENTIFY_TIMER_PERIOD 1000u

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
/*
static ZCL_Status_t ezModeInvokeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EzModeInvoke_t *payload);
static ZCL_Status_t updateCommissioningStateInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_UpdateCommissioningState_t *payload);
*/
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
static ZCL_Status_t sendIdentifyQueryResponse(ZCL_Addressing_t *addressing);
static void dlFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time);
static void identifyTimerFired(void);
static void fillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static ZCL_Status_t triggerEffectCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterServerAttributes_t dlIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IdentifyClusterClientAttributes_t dlIdentifyClusterClientAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_CLIENT_ATTRIBUTES()
};

ZCL_IdentifyClusterCommands_t   dlIdentifyCommands =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, triggerEffectCommand, identifyQueryResponseInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t identifyTimer;
static DECLARE_QUEUE(subscribers);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void identifyClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_SRC_ENDPOINT_ID, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  
  HAL_StopAppTimer(&identifyTimer);

  dlIdentifyClusterServerAttributes.identifyTime.value = 0;
  dlIdentifyClusterServerAttributes.clusterVersion.value = 1u;
  dlIdentifyClusterClientAttributes.clusterVersion.value = 1u;

  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;

  identifyTimer.interval = IDENTIFY_TIMER_PERIOD;
  identifyTimer.mode     = TIMER_REPEAT_MODE;
  identifyTimer.callback = identifyTimerFired;
}

/**************************************************************************//**
\brief Sends Identify request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] time - identify time
******************************************************************************/
void identifySendIdentify(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  uint16_t time)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_ID, sizeof(ZCL_Identify_t));
  fillIdentifyPayload((ZCL_Identify_t *)req->requestPayload, time);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
}


/**************************************************************************//**
\brief Fills Identify command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void fillIdentifyPayload(ZCL_Identify_t *payload, uint16_t time)
{
  payload->identifyTime = time;
}

/**************************************************************************//**
\brief Stops Identify cluster
******************************************************************************/
void identifyClusterStop(void)
{
  HAL_StopAppTimer(&identifyTimer);
}

/**************************************************************************//**
\brief Adds record to a list of subscribers

\param[in] subscriber - pointer to subscriber;
******************************************************************************/
void identifySubscribe(IdentifySubscriber_t *subscriber)
{
  if (!isQueueElem(&subscribers, subscriber))
    if(!putQueueElem(&subscribers, subscriber))
    {
	  /* failed to queue */
    }
}

/**************************************************************************//**
\brief Sends Identify Query request

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint
******************************************************************************/
void identifySendIdentifyQuery(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_COMMAND_ID, 0);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, IDENTIFY_CLUSTER_ID);
  commandManagerSendCommand(req);
  (void)mode, (void)addr, (void)ep;
}

/**************************************************************************//**
\brief Callback on receiving Identify Query Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  appSnprintf("->Identify Query Response, addr = %d, timeout = 0x%04x\r\n", addressing->addr.shortAddress, payload->timeout);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identifyQueryResponse);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends Update Commissioning State command

\param[in] mode - address mode;
\param[in] addr   - short address of destination node;
\param[in] ep     - destination endpoint;
\param[in] action - action to be done upon reception;
\param[in] mask   - commissiong state mask
******************************************************************************/
/*
void identifySendUpdateCommissioningState(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep,
  ZCL_UpdateCommissioningStateAction_t action, uint8_t mask)
{
  (void)mode, (void)addr, (void)ep, (void)action, (void)mask;
}
*/
/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool identifyIsIdentifying(void)
{
  return dlIdentifyClusterServerAttributes.identifyTime.value > 0;
}

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void idetifyStartIdentifying(uint16_t time)
{
  dlIdentifyClusterServerAttributes.identifyTime.value = time;
  HAL_StopAppTimer(&identifyTimer);
  HAL_StartAppTimer(&identifyTimer);
}

static void (*identifycb)(void);
/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void idetifyStartIdentifyingCb(uint16_t time, void (*cb)(void))
{
  dlIdentifyClusterServerAttributes.identifyTime.value = time;
  identifycb = cb;
  HAL_StopAppTimer(&identifyTimer);
  HAL_StartAppTimer(&identifyTimer);
}

/**************************************************************************//**
\brief Send Identify Query command unicastly

\param[in] nwkState        - new netwrok state;
\param[in] operationalState - new operational state
******************************************************************************/
/*
void identifyUpdateCommissioningState(bool nwkState, bool operationalState)
{
  dlIdentifyClusterServerAttributes.commissioningState.value.networkState     = nwkState;
  dlIdentifyClusterServerAttributes.commissioningState.value.operationalState = operationalState;
}
*/
/**************************************************************************//**
\brief Callback on receiving Identify command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload)
{
  appSnprintf("->Identify\r\n");

  dlIdentifyClusterServerAttributes.identifyTime.value = payload->identifyTime;

  HAL_StopAppTimer(&identifyTimer);

  if (payload->identifyTime)
    HAL_StartAppTimer(&identifyTimer);
  
  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identify);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Identify Query command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  appSnprintf( "->Identify Query\r\n");
  
  if (dlIdentifyClusterServerAttributes.identifyTime.value)
    return sendIdentifyQueryResponse(addressing);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, identifyQuery);

  (void)payload, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving EZ-Mode invoke command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
/*
static ZCL_Status_t ezModeInvokeInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EzModeInvoke_t *payload)
{
  LOG_STRING(identifyStr, "->EZ-Mode Invoke\r\n");
  appSnprintf(identifyStr);

  if (payload->factoryFresh)
    PDS_DeleteAll(false);
  if (payload->networkSteering)
  {
    appRestart(payload->findingAndBinding);
    return ZCL_SUCCESS_STATUS;
  }
  if (payload->findingAndBinding)
    invokeEzMode(NULL);

//  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, ezModeInvoke);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
*/
/**************************************************************************//**
\brief Callback on receiving Upodate Commissioning State command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
/*
static ZCL_Status_t updateCommissioningStateInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_UpdateCommissioningState_t *payload)
{
  LOG_STRING(identifyStr, "->Update Commissining State\r\n");
  appSnprintf(identifyStr);

  if (ZCL_UPDATE_COMMISSIONING_STATE_ACTION_SET == payload->action)
  {
    dlIdentifyClusterServerAttributes.commissioningState.value.networkState     |= payload->commissioningStateMask.networkState;
    dlIdentifyClusterServerAttributes.commissioningState.value.operationalState |= payload->commissioningStateMask.operationalState;
  }
  if (ZCL_UPDATE_COMMISSIONING_STATE_ACTION_CLEAR == payload->action)
  {
    dlIdentifyClusterServerAttributes.commissioningState.value.networkState     &= ~payload->commissioningStateMask.networkState;
    dlIdentifyClusterServerAttributes.commissioningState.value.operationalState &= ~payload->commissioningStateMask.operationalState;
  }

//  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(subscribers, updateCommissioningState);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
*/
/**************************************************************************//**
\brief Sends Identidy Query Response command

\param[in] addressing - addressing information about sender device

\returns status of sending
******************************************************************************/
static ZCL_Status_t sendIdentifyQueryResponse(ZCL_Addressing_t *addressing)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return ZCL_INSUFFICIENT_SPACE_STATUS;

  fillCommandRequest(req, ZCL_IDENTIFY_CLUSTER_IDENTIFY_QUERY_RESPONSE_COMMAND_ID,
                       sizeof(ZCL_IdentifyQueryResponse_t));
  dlFillIdentifyQueryResponsePayload((ZCL_IdentifyQueryResponse_t *)req->requestPayload, dlIdentifyClusterServerAttributes.identifyTime.value);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fills Identify Query Response command structure

\param[out] payload - pointer to command structure;
\param[in]  time    - identify time
******************************************************************************/
static void dlFillIdentifyQueryResponsePayload(ZCL_IdentifyQueryResponse_t *payload, uint16_t time)
{
  payload->timeout = time;
}

/**************************************************************************//**
\brief Identify timer has fired
******************************************************************************/
static void identifyTimerFired(void)
{
  --dlIdentifyClusterServerAttributes.identifyTime.value;
  /* Temp- for certification purpose*/
  BSP_ToggleLed(LED_FIRST);
  // TO DO: toggle LED
  if (!dlIdentifyClusterServerAttributes.identifyTime.value)
  {
    HAL_StopAppTimer(&identifyTimer);
    if (identifycb)
    {
      identifycb();
    }
    // TO DO: turn LED off
    /* Temp- for certification purpose*/
    BSP_OffLed(LED_FIRST);
  }
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_WRITE_ATTRIBUTE_EVENT == event) &&
      (ZCL_IDENTIFY_CLUSTER_IDENTIFY_TIME_ATTRIBUTE_ID == attributeId))
  {
    HAL_StopAppTimer(&identifyTimer);
    if (dlIdentifyClusterServerAttributes.identifyTime.value)
      HAL_StartAppTimer(&identifyTimer);

    (void)addressing;
  }
}

/**************************************************************************//**
\brief Callback on receive of Trigger Effect command
******************************************************************************/
static ZCL_Status_t triggerEffectCommand(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload)
{
  appSnprintf("->TriggerEffect %d\r\n",  payload->effectIdentifier);
  
  (void)addressing;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlIdentifyCluster.c

