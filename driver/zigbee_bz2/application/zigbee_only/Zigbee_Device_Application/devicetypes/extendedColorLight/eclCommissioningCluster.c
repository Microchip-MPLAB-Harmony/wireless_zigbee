/*******************************************************************************
  Light device Commissioning cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclCommissioningCluster.c

  Summary:
    This file contains the Light device Commissioning cluster interface.

  Description:
    This file contains the Light device Commissioning cluster interface.
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

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3Device.h>
#include <commandManager.h>
#include <sysUtils.h>
#include <uartManager.h>
#include <haClusters.h>

#include <eclCommissioningCluster.h>

#include <extendedColorLight.h>
/******************************************************************************
                    Prototypes
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload);
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload);
//static ZCL_Status_t endpointInformationResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EndpointInformation_t *payload);
//static ZCL_Status_t getGroupIdentifiersResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiersResponse_t *payload);
//static ZCL_Status_t getEndpointListResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointListResponse_t *payload);

// payload fillers
static uint8_t eclFillGetGroupIdentifiersResponsePayload(ZCL_GetGroupIdentifiersResponse_t *payload, uint8_t startIndex);
static uint8_t eclFillGetEndpointListResponsePayload(ZCL_GetEndpointListResponse_t *payload, uint8_t startIndex);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_CommissioningClusterServerAttributes_t eclCommissioningClusterServerAttributes =
{
  ZCL_DEFINE_COMMISSIONING_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_CommissioningClusterCommands_t eclCommissioningClusterCommands =
{
  ZCL_DEFINE_COMMISSIONING_CLUSTER_COMMANDS(getGroupIdentifiersInd,
                                            getEndpointListInd,
                                            NULL,
                                            NULL,
                                            NULL)
};

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Commissioning cluster.
******************************************************************************/
void commissioningClusterInit(void)
{
  ZCL_Cluster_t *commissioningCluster = ZCL_GetCluster(APP_ENDPOINT_EXTENDED_COLOR_LIGHT,
                                                       ZLL_COMMISSIONING_CLUSTER_ID,
                                                       ZCL_CLUSTER_SIDE_SERVER);

  eclCommissioningClusterServerAttributes.clusterVersion.value = 1;
  
  //commissioningCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Fill endpoint information command payload
******************************************************************************/
static void eclFillEndpointInformationPayload(ZCL_EndpointInformation_t *payload)
{
  ExtAddr_t ieeeAddr;
 
  memcpy(&ieeeAddr, MAC_GetExtAddr(), sizeof(ExtAddr_t));
  
  payload->ieeeAddress    = ieeeAddr;
  payload->networkAddress = NWK_GetShortAddr();
  payload->endpointId     = APP_ENDPOINT_EXTENDED_COLOR_LIGHT;
  payload->profileId      = APP_PROFILE_ID;
  payload->deviceId       = APP_DEVICE_ID;
  payload->version        = APP_VERSION;
}

/**************************************************************************//**
\brief Send Endpoint Information command to target device.

\param[in] mode - addressing mode
\param[in] addr - dst address
\param[in] ep   - dst endpoint
******************************************************************************/
void commissioningSendEndpointInformation(ShortAddr_t addr, Endpoint_t ep)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
  {
    return;
  }
  
  // fill command request
  fillCommandRequest(req, ZCL_COMMISSIONING_CLUSTER_ENDPOINT_INFORMATION_COMMAND_ID,
                     sizeof(ZCL_EndpointInformation_t));
  // Enable default response for this command
  req->defaultResponse = ZCL_FRAME_CONTROL_ENABLE_DEFAULT_RESPONSE;
  
  // fill command payload
  eclFillEndpointInformationPayload((ZCL_EndpointInformation_t *)req->requestPayload);
  
  // fill destination addressing
  fillDstAddressingServer(&req->dstAddressing, APS_SHORT_ADDRESS, addr, ep, ZLL_COMMISSIONING_CLUSTER_ID);
  
  commandManagerSendCommand(req);
}

/**************************************************************************//**
\brief Fill the get group identifiers response command payload

\param[in] payload - pointer to response payload
\param[in] startIndex - start index

\return Size of the command payload
******************************************************************************/
static uint8_t eclFillGetGroupIdentifiersResponsePayload(ZCL_GetGroupIdentifiersResponse_t *payload, uint8_t startIndex)
{
  uint8_t size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;
  uint8_t index = 0, n = 0;
  
  NWK_GroupTableEntry_t *group = NWK_NextGroup(NULL); // returns the first group entry
 
  while (NULL != group)
  {
    if (index >= startIndex && (n < ARRAY_SIZE(payload->recordList)))
    {
      payload->recordList[n].groupId = group->addr;
      payload->recordList[n].groupType = 0;
      n++;
      
      size += sizeof(ZCL_GroupInformationRecord_t);
    }
    
    group = NWK_NextGroup(group);
    index++;
  }

  payload->total = index;
  payload->startIndex = startIndex;
  payload->count = n;

  return size;
}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers command
******************************************************************************/
static ZCL_Status_t getGroupIdentifiersInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiers_t *payload)
{
  ZCL_Request_t *req;
  uint8_t size;

  appSnprintf("getGroupIdentifiersInd(), startIndex=%02d\r\n", payload->startIndex);
  
  if (!(req = getFreeCommand()))
  {
   return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  
  size = eclFillGetGroupIdentifiersResponsePayload((ZCL_GetGroupIdentifiersResponse_t *)req->requestPayload,  payload->startIndex);
  fillCommandRequest(req, ZCL_COMMISSIONING_CLUSTER_GET_GROUP_IDENTIFIERS_RESPONSE_COMMAND_ID, size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void) payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Fill the get endpoint list response command payload

\param[in] payload - pointer to response payload
\param[in] startIndex - start index

\return Size of the command payload
******************************************************************************/
static uint8_t eclFillGetEndpointListResponsePayload(ZCL_GetEndpointListResponse_t *payload, uint8_t startIndex)
{
  uint8_t size = sizeof(uint8_t) /*total*/ + sizeof(uint8_t) /*startIndex*/ + sizeof(uint8_t) /*count*/;

  if (0 == startIndex)
  {
    payload->recordList[0].networkAddress = NWK_GetShortAddr();
    payload->recordList[0].endpointId = APP_ENDPOINT_EXTENDED_COLOR_LIGHT;
    payload->recordList[0].profileId = APP_PROFILE_ID;
    payload->recordList[0].deviceId = APP_DEVICE_ID;
    payload->recordList[0].version = APP_VERSION;

    size += sizeof(ZCL_EndpointInformationRecord_t);
    payload->count = 1;
  }
  else
  {
    payload->count = 0;
  }
  payload->total = 1;
  payload->startIndex = startIndex;

  return size;
}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List command
******************************************************************************/
static ZCL_Status_t getEndpointListInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointList_t *payload)
{
  ZCL_Request_t *req;
  uint8_t size;

  appSnprintf("getEndpointListInd(), startIndex=%02d\r\n", payload->startIndex);
  
  if (!(req = getFreeCommand()))
  {
   return ZCL_INSUFFICIENT_SPACE_STATUS;
  }
  
  size = eclFillGetEndpointListResponsePayload((ZCL_GetEndpointListResponse_t *)req->requestPayload,  payload->startIndex);
  fillCommandRequest(req, ZCL_COMMISSIONING_CLUSTER_GET_ENDPOINT_LIST_RESPONSE_COMMAND_ID, size);
  fillDstAddressingViaSourceAddressing(&req->dstAddressing, addressing, ZCL_CLUSTER_SIDE_CLIENT);
  commandManagerSendCommand(req);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Endpoint Information command
******************************************************************************/
//static ZCL_Status_t endpointInformationResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_EndpointInformation_t *payload)
//{
//  (void)addressing;
//  (void)payloadLength;
//  (void)payload;
//  return ZCL_SUCCESS_STATUS;
//}

/**************************************************************************//**
\brief Callback on receive of Get Group Identifiers Response command
******************************************************************************/
//static ZCL_Status_t getGroupIdentifiersResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetGroupIdentifiersResponse_t *payload)
//{
//  (void)addressing;
//  (void)payloadLength;
//  (void)payload;
//  return ZCL_SUCCESS_STATUS;
//}

/**************************************************************************//**
\brief Callback on receive of Get Endpoint List Response command
******************************************************************************/
//static ZCL_Status_t getEndpointListResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetEndpointListResponse_t *payload)
//{
//  (void)addressing;
//  (void)payloadLength;
//  (void)payload;
//  return ZCL_SUCCESS_STATUS;
//}

#endif //def APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof lightCommissioningCluster.c
