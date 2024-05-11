/**************************************************************************//**
  \file  rMessageCluster.c

  \brief Message Cluster Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#if defined(_ZCL_SUPPORT_) && (APP_REDUCED_OTAU_SERVER == 0)
/*******************************************************************************
                             Includes section
 ******************************************************************************/
#include <stdbool.h>
#include <zcl/include/zcl.h>
#include <zcl/include/zclMessagingCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
#include <systemenvironment/include/sysUtils.h>
#include <rTimeCluster.h>
#include <rZcl.h>
/*******************************************************************************
                   Prototypes section
 ******************************************************************************/
static ZCL_Status_t displayMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength, DisplayMessage_t *message);
static ZCL_Status_t cancelMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength, CancelMessage_t *message);
static ZCL_Status_t getLastMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength, void *message);
static ZCL_Status_t messageConfirmationInd(ZCL_Addressing_t *addr, uint8_t payloadLength, MessageConfirmation_t *message);
/*******************************************************************************
                   Global Variables section
 ******************************************************************************/
static struct
{
  uint8_t requestLength;
  uint8_t requestBuf[ZCL_REQUEST_BUF_SIZE];
  ZCL_UTCTime_t sentTime; // the time message being sent
} lastMessage = {.requestLength = 0, .sentTime = 0};

static MessagingClusterCommands_t messagingCommands =
{
  DEFINE_MESSAGING_CLUSTER_COMMANDS(displayMessageInd, cancelMessageInd, getLastMessageInd, messageConfirmationInd)
};
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/*******************************************************************************
Display Message command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t displayMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength, DisplayMessage_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}
/*******************************************************************************
Cancel Message command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t cancelMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength, CancelMessage_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}
/*******************************************************************************
Get Last Message command handler. Creates and sends Display Message if one exists
and isn't expired.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t getLastMessageInd(ZCL_Addressing_t *addr, uint8_t payloadLength,  void *message)
{
#ifdef ZSE_ESP_CLUSTERS_LOGIC
  if (lastMessage.requestLength != 0)
  {
    DisplayMessage_t *displayMessage = (DisplayMessage_t*)lastMessage.requestBuf;

    // if duration is set
    if (displayMessage->duration != DISPLAY_MESSAGE_DURATION_UNTIL_CHANGED)
    {

      if (displayMessage->startTime <= timeClusterGetCurrentUtcTime())
      {
          // 1. Test Spec variant
          // when start time remains constant but duration is changed.
          uint16_t minutesPassed = (timeClusterGetCurrentUtcTime() - lastMessage.sentTime) / 60;

          // decrease duration if minitues are passed
          if (minutesPassed >= 1)
          {
            // save the the time the message being sent
            lastMessage.sentTime = timeClusterGetCurrentUtcTime();

            if (displayMessage->duration < minutesPassed)
              displayMessage->duration = 0;
            else
              displayMessage->duration -= minutesPassed;
          }
      }

      // Message expired
      if (displayMessage->duration == 0)
      {
        lastMessage.requestLength = 0;
        return ZCL_NOT_FOUND_STATUS;
      }

/*
      // 2. Logical variant
      // when duration remains constant and start time remains constant.

      ZCL_UTCTime_t expTime = lastMessage.sentTime + (displayMessage->duration * 60);

      // Message expired.
      if (expTime >= timeClusterGetCurrentUtcTime())
      {
        lastMessage.requestLength = 0;
        return ZCL_NOT_FOUND_STATUS;
      }

      // overides start time in a case if start time is 'now'.
      displayMessage->startTime = lastMessage.sentTime;
*/
    }

    ZCL_Request_t *request = getZclRequest();

    request->id = DISPLAY_MESSAGE_COMMAND_ID;
    request->defaultResponse = ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE;
    request->requestLength = lastMessage.requestLength;
    request->requestPayload = lastMessage.requestBuf;
    request->dstAddressing = *addr;
    request->dstAddressing.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
    request->ZCL_Notify = NULL;

    ZCL_CommandReq(request);

    return ZCL_SUCCESS_STATUS;
  }

  return ZCL_NOT_FOUND_STATUS;

#else
  commandInd(addr, payloadLength, (uint8_t *)message);
  return (ZCL_Status_t)rGetLastMessageReturnValue();
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
}
/*******************************************************************************
Display Message Confirmation command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t messageConfirmationInd(ZCL_Addressing_t *addr, uint8_t payloadLength,  MessageConfirmation_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}
/***************************************************************************//**
\brief Saves Display Message. The saved message returns in response to Get Last
Message Command.

\param[in] request - that contains message's payload.

\return
******************************************************************************/
void saveMessageCommand(ZCL_Request_t *request)
{
  lastMessage.requestLength = request->requestLength;
  lastMessage.sentTime = timeClusterGetCurrentUtcTime();
  SYS_BYTE_MEMCPY(lastMessage.requestBuf, request->requestPayload, request->requestLength);
}
/***************************************************************************//**
\brief Gets Messaging Cluster Commands.

\param

\return Message Cluster Commands.
******************************************************************************/
MessagingClusterCommands_t *getMessagingCommands(void)
{
  return &messagingCommands;
}
/***************************************************************************//**
\brief Cancels Message.

\param[in] request - that contains message's payload.

\return
******************************************************************************/
void cancelMessageCommand(ZCL_Request_t *request)
{
  (void)request;
  lastMessage.requestLength = 0;
}

#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rMessageCluster.c */
