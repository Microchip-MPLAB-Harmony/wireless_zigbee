/**************************************************************************//**
  \file rPriceCluster.c

  \brief Runner Price Cluster implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009 Andrey Kostyukov  - Created.
 ******************************************************************************/
#if defined(_ZCL_SUPPORT_) && (APP_REDUCED_OTAU_SERVER == 0)
/******************************************************************************
                        Includes section.
 ******************************************************************************/
#include <stdbool.h>
#include <systemenvironment/include/sysUtils.h>
#include <zcl/include/zcl.h>
#include <zcl/include/zclTimeCluster.h>
#include <rPriceCluster.h>
#include <rZcl.h>
#include <rTimeCluster.h>
/*****************************************************************************
                               Definitions section
******************************************************************************/
#define MOVE_TEMPLATE(orig, off_in_bytes) (orig = (void*)(((uint8_t*)(orig)) + (off_in_bytes)))
/******************************************************************************
                        Static Functions Prototypes section.
 ******************************************************************************/
static ZCL_Status_t getCurrentPriceInd(ZCL_Addressing_t *addr, uint8_t payloadLength,
                                ZCL_GetCurrentPrice_t *message);
static ZCL_Status_t publishPriceInd(ZCL_Addressing_t *addr, uint8_t payloadLength,
                             ZCL_PublishPrice_t *message);
#ifdef ZSE_ESP_CLUSTERS_LOGIC
static ZCL_Status_t makePriceResponse(ZCL_Addressing_t *addr, uint8_t payloadLength,
                       ZCL_GetCurrentPrice_t *message);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
/******************************************************************************
                       Static Variables section.
 ******************************************************************************/
static ZCL_PriceClusterCommands_t priceCommands =
  { PRICE_CLUSTER_COMMANDS(getCurrentPriceInd, publishPriceInd, NULL, NULL) };

#ifdef ZSE_ESP_CLUSTERS_LOGIC
#define RATE_LABEL "BASE"
static ZCL_PublishPrice_t autoResponse =
{
  .providerId = 0x01,
  .rateLabelLength = sizeof(RATE_LABEL) - 1,
  // string length without termination zero
  .rateLabel = RATE_LABEL,
  .issuerEventId = 0x01,
  .unitOfMeasure = 0x00,
  .currency = 840,
  .priceTrailDigitPriceTier.priceTrailDigit = 0x0,
  .priceTrailDigitPriceTier.priceTier = 0x1,
  .numberOfPriceTiersRegisterTier.numberOfPriceTiers = 0x0,
  .numberOfPriceTiersRegisterTier.registerTier = 0x4,
  .startTime = PUBLISH_PRICE_START_TIME_NOW,
  .durationInMinutes = PUBLISH_PRICE_DURATION_UNTIL_CHANGED,
  .price = 0x12,
  .priceRatio = PUBLISH_PRICE_PRICE_RATIO_IS_NOT_USED,
  .generationPrice = PUBLISH_PRICE_GENERATION_PRICE_IS_NOT_USED,
  .generationPriceRatio = PUBLISH_PRICE_GENERATION_PRICE_RATIO_IS_NOT_USED,
  .numberOfBlockThresholds = PUBLISH_NUMBER_OF_BLOCK_THRESHOLDS_IS_NOT_USED,
  .priceControl = PUBLISH_PRICE_CONTROL_IS_NOT_USED,
  .standingCharge = PUBLISH_STANDING_CHARGE_IS_NOT_USED,
}; // ZigBee-095310r23ZB Payload Format
static uint8_t autoResponseLength = sizeof(ZCL_PublishPrice_t);
#ifdef TIME_LIMITED_PRICE
static ZCL_UTCTime_t autoResponseSetupTime = 0;
static ZCL_UTCTime_t autoResponseExpirationTime = 0xFFFFFFFF; //until changed
#endif /* TIME_LIMITED_PRICE */
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
/******************************************************************************
                        Implementation section.
 ******************************************************************************/
/**//**
 * \brief Function gives access to Price cluster commands descriptor.

This function is used to get access to Price cluster commands descriptor when
ZCL starts.
This function is not intended for use in other cases.

\param none
\return pointer to command descriptor
 */
ZCL_PriceClusterCommands_t* getPriceCommands(void)
{
  return &priceCommands;
}
/**//**
 * \brief Publish Price command handler.

This function is used to handle Publish Price command from remote device.
This function is callback and not intended for direct call.
ZIGBEE SMART ENERGY PROFILE SPECIFICATION, r15, D.4.2.4.1 Publish Price Command

\param addr[in] - information about source of commands
\param payloadLength[in] - length of command payload
\param message[in] - pointer to command payload

\return status of handling
 */
static ZCL_Status_t publishPriceInd(ZCL_Addressing_t *addr, uint8_t payloadLength,
                             ZCL_PublishPrice_t *message)
{
  return commandInd(addr, payloadLength, (uint8_t *)message);
}
/**//**
 * \brief Get Current Price command handler.

This function is used to handle Get Current Price command from remote device.
This function is callback and not intended for direct call.
ZIGBEE SMART ENERGY PROFILE SPECIFICATION, r15,
D.4.2.3.1 Get Current Price Command

\param addr[in] - information about source of commands
\param payloadLength[in] - length of command payload
\param message[in] - pointer to command payload

\return status of handling
 */
static ZCL_Status_t getCurrentPriceInd(ZCL_Addressing_t *addr, uint8_t payloadLength,
                                ZCL_GetCurrentPrice_t *message)
{
#ifdef ZSE_ESP_CLUSTERS_LOGIC
  return makePriceResponse(addr,payloadLength,message);
#else
  return commandInd(addr, payloadLength, (uint8_t *)message);
#endif /* ZSE_ESP_CLUSTERS_LOGIC */
}
/**//**
 * \brief Activity immitation function.

This function is used certification purposes to fullfill test case.
AMI_Test_Specification r17,
12.5 SE Network GetCurrentPrice and PublishPrice Response

\param addr[in] - information about source of commands
\param payloadLength[in] - length of command payload
\param message[in] - pointer to command payload

\return none
 */

#ifdef ZSE_ESP_CLUSTERS_LOGIC
static ZCL_Status_t makePriceResponse(ZCL_Addressing_t *addr, uint8_t payloadLength,
                       ZCL_GetCurrentPrice_t *message)
{
  ZCL_UTCTime_t time = timeClusterGetCurrentUtcTime();
  ZCL_Request_t* zclRequest = getZclRequest();
  ZCL_PublishPrice_t* cmd = (ZCL_PublishPrice_t*)(zclRequest->requestPayload);
  ZCL_Status_t status = ZCL_SUCCESS_STATUS;

  //if autoresponse variable field is not compressed
  if ((autoResponseLength == sizeof(ZCL_PublishPrice_t))
      && (RATE_LABEL_MAX_LEN != cmd->rateLabelLength))
  {
    autoResponseLength -= RATE_LABEL_MAX_LEN - autoResponse.rateLabelLength;
    //memmove
    SYS_BYTE_MEMCPY(&autoResponse.rateLabel[autoResponse.rateLabelLength],
           &autoResponse.issuerEventId,
           sizeof(ZCL_PublishPrice_t)
           - FIELD_OFFSET(ZCL_PublishPrice_t,issuerEventId));

  }

#ifdef TIME_LIMITED_PRICE
  //check if price is expired
  if (time > autoResponseExpirationTime)
    status = ZCL_NOT_FOUND_STATUS;
#endif /* TIME_LIMITED_PRICE */

  //if autoresponse was correctly set up
  if ((0 != autoResponseLength) && (ZCL_SUCCESS_STATUS == status))
  {
    zclRequest->id                      = PUBLISH_PRICE_COMMAND_ID;
    zclRequest->defaultResponse            = ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE;
    zclRequest->dstAddressing.addrMode  = APS_NO_ADDRESS;
    zclRequest->dstAddressing.clusterId = addr->clusterId;
    zclRequest->dstAddressing.endpointId = addr->endpointId;
    zclRequest->dstAddressing.profileId = PROFILE_ID_SMART_ENERGY;
    zclRequest->dstAddressing.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
    //filled at endpoint registration//zclRequest.endpointId              = endpoint;

    memcpy(cmd, &autoResponse, autoResponseLength);
    zclRequest->requestLength = autoResponseLength;
    MOVE_TEMPLATE(cmd, autoResponseLength - sizeof(ZCL_PublishPrice_t));
    cmd->currentTime = time;
    ZCL_CommandReq(zclRequest);
  }
  return status;
}

/**//**
 * \brief Set autorespone payload from given command frame.

This function is called on capturing configuration command frame.
Input frame is checked if it is publish price commands is in payload. If
publish price has come then set auto response payload to input payload.

\param frame[in] - input command frame
\return none
 */
void setPriceAutoResponse(ZS_CommandFrame_t* frame)
{
  RZclCommandRequest_t* cmd = (RZclCommandRequest_t*)frame->payload;

  if ((PRICE_CLUSTER_ID == cmd->clusterId) &&
      (PUBLISH_PRICE_COMMAND_ID == cmd->commandId) &&
      (ZCL_DIRECTION_FROM_SERVER == cmd->commandOptions.direction))
  {
    ZCL_PublishPrice_t* pAutoResponse = &autoResponse;

    autoResponseLength = frame->length - sizeof(frame->commandId)
                       - FIELD_OFFSET(RZclCommandRequest_t, request);
    autoResponseSetupTime = timeClusterGetCurrentUtcTime();
    SYS_BYTE_MEMCPY(&autoResponse, cmd->request,
                    autoResponseLength);
#ifdef TIME_LIMITED_PRICE
    //evalute expiration time
    MOVE_TEMPLATE(pAutoResponse, autoResponseLength - sizeof(ZCL_PublishPrice_t));
    if (PUBLISH_PRICE_START_TIME_NOW == pAutoResponse->startTime)
      pAutoResponse->startTime = autoResponseSetupTime;

    if (PUBLISH_PRICE_DURATION_UNTIL_CHANGED == pAutoResponse->durationInMinutes)
    {
      autoResponseExpirationTime = 0xffffffff; //until changed
    }
    else
    {
      autoResponseExpirationTime = (pAutoResponse->durationInMinutes * 60) + pAutoResponse->startTime;
    }
#endif /* TIME_LIMITED_PRICE */
  }
}

#endif /* ZSE_ESP_CLUSTERS_LOGIC */
#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rPriceCluster.c */
