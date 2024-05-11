/*******************************************************************************
  ZAppSI System Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiSysSerialization.h

  Summary:
    This file contains the ZAppSI system configuration primitives serialization interface.

  Description:
    This file contains the ZAppSI system configuration primitives serialization interface.
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


#ifndef ZSISYSSERIALIZATION_H
#define ZSISYSSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <appFramework.h>
#include <configserver.h>
#include <zdo.h>
#include <sleep.h>
#include <zsiFrames.h>
#include <zsiDriver.h>
#include <sysEventsHandler.h>
#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#include <zgpLowGpdf.h>
#endif
#endif
/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  SYS_EVENT_DATA_TYPE_DATA,
  SYS_EVENT_DATA_TYPE_ADDRESS,
  SYS_EVENT_DATA_TYPE_ADDRESS_IN_ADDRESS
}zsiSysEventDataType_t;

typedef struct _ZsiCsParameter_t
{
  CS_MemoryItemId_t parameterId;
  uint16_t          size;
  uint8_t           payload[CS_MAX_PARAMETER_SIZE];
} ZsiCsParameter_t;

typedef union _ZsiEventData_
{
  uint16_t u16Data;
  uint8_t* uint8ptr;
}ZsiEventData_t ;

typedef struct _ZsiSysPostEvent_t_t
{
  SYS_EventId_t id;
  ZsiEventData_t data;
} ZsiSysPostEvent_t;

typedef struct _ZsiAPSFrameFilteringByProfileIdContext_t
{
  Endpoint_t   endpoint;
  ProfileId_t profileId;
} ZsiApsFrameFilteringByProfileIdContext_t;

/******************************************************************************
                    External variable  section
******************************************************************************/
#if defined(ZAPPSI_NP) || defined(ZAPPSI_HOST)
extern ZsiSysPostEvent_t postEventData;
#endif
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for SYS command deserialization.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiSysFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief CS_ReadParameter request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeCS_ReadParameterReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief CS_WriteParameter request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeCS_WriteParameterReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief CS_ReadParameter request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return CS_WriteParameter frame size.
 ******************************************************************************/
INLINE uint16_t
zsiCS_ReadParameterReqLength(const CS_MemoryItemId_t *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t);  /* parameterId */
}

/**************************************************************************//**
  \brief CS_WriteParameter request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return CS_WriteParameter frame size.
 ******************************************************************************/
INLINE uint16_t
zsiCS_WriteParameterReqLength(const ZsiCsParameter_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) + /* parameterId */
         sizeof(uint16_t) + /* size */
         req->size;         /* payload */
}

/**************************************************************************//**
  \brief CS_WriteParameter confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeCS_WriteParameterConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief CS_ReadParameter confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeCS_ReadParameterConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief SYS_PseudoPowerOff request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSYS_PseudoPowerOffReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief SYS_PseudoPowerOff confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSYS_PseudoPowerOffConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

#elif defined(ZAPPSI_NP)
;/**************************************************************************//**
  \brief CS_ReadParameter request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeCS_ReadParameterReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief CS_ReadParameter confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return CS_WriteParameter frame size.
 ******************************************************************************/
INLINE uint16_t
zsiCS_ReadParameterConfLength(const ZsiCsParameter_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +  /* parameterId */
         sizeof(uint16_t) +  /* size */
         req->size;          /* payload */
}

/**************************************************************************//**
  \brief CS_WriteParameter request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeCS_WriteParameterReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief CS_WriteParameter confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return CS_WriteParameter frame size.
 ******************************************************************************/
INLINE uint16_t
zsiCS_WriteParameterConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief SYS_PseudoPowerOff request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSYS_PseudoPowerOffReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

#endif /* ZAPPSI_NP */

/**************************************************************************//**
  \brief SYS_PostEvent request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeSYS_PostEventReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);


/**************************************************************************//**
  \brief SYS_PostEvent confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSYS_PostEventConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief SYS_PostEventReq primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeSYS_PostEventReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
/**************************************************************************//**
  \brief APS-RegisterEndpoint request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return APS-RegisterEndpoint request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGP_LowDataIndLength(const ZGP_LowDataInd_t *const ind)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
  sizeof(uint16_t)  + /* srcAddress.sh */
  sizeof(uint64_t) + /* srcAddress.ext */
  sizeof(uint32_t) + /* srcId */
  sizeof(uint32_t) + /* gpdSecurityFrameCounter */
  sizeof(uint32_t) +/* mic*/
  sizeof(uint16_t) + /* srcPanId */
  sizeof(uint8_t) + /*  ZGP_GpdfIndStatusCode_t enum status */
  sizeof(uint8_t) + /* ZGP_FrameType_t enum frameType */
  sizeof(uint8_t) + /* linkQuality */
  sizeof(int8_t) + /* rssi */
  sizeof(uint8_t) + /* seqNumber */
  sizeof(uint8_t) + /* MAC_AddrMode_t srcAddrMode */
  sizeof(uint8_t) + /* ZGP_ApplicationId_t applicationId */
  sizeof(uint8_t) + /* ZGP_SecLevel_t gpdfSecurityLevel */
  sizeof(uint8_t) + /* ZGP_SecKeyType_t gpdfKeyType */
  sizeof(uint8_t) + /* endPoint */
  sizeof(uint8_t) + /* gpdCommandId */
  sizeof(uint8_t) + /* gpdAsduLength */
  ind->gpdAsduLength + /* gpd asdu */
  sizeof(uint8_t) + /* autoCommissioning */
  sizeof(uint8_t) ; /* rxAfterTx */

}
#endif // APP_ZGP_DEVICE_TYPE
#endif // _GREENPOWER_SUPPORT_
INLINE uint8_t zsiGetBcEventAccessReqContextSize(SYS_EventId_t id, BcAction_t action)
{
  uint8_t size = 0;
  switch(id)
  {
    case BC_EVENT_ACCESS_REQUEST:
    {
      switch (action)
      {
        case BC_TRANSPORT_NWK_KEY_ACTION:    //APS_TransportKeyInd_t
          size = sizeof(APS_TransportKeyInd_t);
          break;
        case BC_VERIFY_KEY_REQ_ATTTEMPS_ACTION: //   APS_VerifyKeyStatus_t
          size = sizeof(APS_VerifyKeyStatus_t); //enum
          break;
        case BC_CHILD_NWK_ADDR_ALLOC_ACTION: // & ShortAddr_t
          size = sizeof(ShortAddr_t);
          break;
        case BC_UPDATE_DEVICE_REQ_ACTION: //APS_UpdateDeviceInfo_t
          size = sizeof(APS_UpdateDeviceInfo_t);
          break;
        case BC_BIND_REQ_ACTION:   //APS_DataInd_t speacail handling
        case BC_UNBIND_REQ_ACTION:
        case BC_MATCH_DESCR_REQ_ACTION:
          break;
        case BC_FRAME_FILTERING_BY_PROFILE_ID_ACTION: //APS_FrameFilteringByProfileIdContext_t
          size = sizeof(ZsiApsFrameFilteringByProfileIdContext_t);
          break;
//       case BC_BEACON_FILTERING_ACTION: //MAC_BeaconNotifyInd_t
//          size = sizeof(MAC_BeaconNotifyInd_t); //pointers inside special handling required
//          break;
      default:
          break;
      }
    }
    break;
    case BC_EVENT_TC_ACCESS_REQUEST:
    {
      switch(action)
      {
        case BC_UPDATE_DEVICE_IND_ACTION: //APS_UpdateDeviceInd_t
          size = sizeof(APS_UpdateDeviceInd_t);
          break;
        case BC_REQUEST_KEY_IND_ACTION:  //APS_RequestKeyInd_t
          size = sizeof(APS_RequestKeyInd_t);
          break;
        case BC_VERIFY_KEY_IND_ACTION:   //APS_VerifyKeyInd_t
          size = sizeof(APS_VerifyKeyInd_t);
          break;
        default:
           break;
      }
    }
    break;
    default:
      break;
  }
  return size ;
}


#ifdef ZAPPSI_HOST
#define zsiDeserializeCS_WriteParameterReq NULL
#define zsiDeserializeCS_ReadParameterReq  NULL
#define zsiDeserializeSYS_PostEventConf    NULL
#define zsiDeserializeSYS_PseudoPowerOffReq  NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeCS_WriteParameterConf NULL
#define zsiDeserializeCS_ReadParameterConf  NULL
#define zsiDeserializeSYS_PostEventReq      NULL
#define zsiDeserializeSYS_PseudoPowerOffConf NULL
#endif /* ZAPPSI_NP */

#endif /* ZSISYSSERIALIZATION_H */
