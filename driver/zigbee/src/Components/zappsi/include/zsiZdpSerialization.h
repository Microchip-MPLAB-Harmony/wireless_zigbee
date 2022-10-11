/*******************************************************************************
  ZAppSI ZDP Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiZdpSerialization.h

  Summary:
    This file contains the ZAppSI ZDP primitives serialization interface.

  Description:
    This file contains the ZAppSI ZDP primitives serialization interface.
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


#ifndef _ZSIZDPSERIALIZATION_H_
#define _ZSIZDPSERIALIZATION_H_

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zdo.h>
#include <zsiFrames.h>
#include <zsiDriver.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for ZDP commands serialization.

  \param[in] clusterId - ZDP cluster identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiSerializeRoutine_t zsiZdpFindSerializationRoutine(uint16_t clusterId);

/**************************************************************************//**
  \brief Finds routine for ZDP commands deserialization and processing.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiZdpFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief ZDP-IeeeAddress.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpIeeeAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-IeeeAddress.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-IeeeAddressReq frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpIeeeAddressReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +            /* nwkAddrOfInterest */
         sizeof(uint8_t)  +            /* reqType */
         sizeof(uint8_t);              /* startIndex */
}

/**************************************************************************//**
  \brief ZDP-IeeeAddress.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpIeeeAddressResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-PermitJoining.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpPermitJoiningReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-PermitJoining.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-PermitJoiningReq frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpPermitJoiningReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +             /* permitDuration */
         sizeof(uint8_t);              /* tcSignificance */
}

/**************************************************************************//**
  \brief ZDP-PermitJoining.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpPermitJoiningResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

  /**************************************************************************//**
  \brief ZDP-DeviceAnnounce.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpDeviceAnnceReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief ZDP-DeviceAnnce.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-DeviceAnnce frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpDeviceAnnceReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(ShortAddr_t) +             /* NwkAddOfLocalDevice */
         sizeof(ExtAddr_t) ;               /* IeeeAddrOfLocalDevice */
}
/**************************************************************************//**
  \brief ZDP-DeviceAnnce.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-DeviceAnnce frame size.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeDeviceAnnceZgpResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpSimpleDescriptorReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-SimpleDescriptorReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpSimpleDescriptorReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                       /* nwkAddrOfInterest */
         sizeof(uint8_t);                        /* endpoint */
}

/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpSimpleDescriptorResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-ActiveEndpoints.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpActiveEndpointpReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

  /**************************************************************************//**
  \brief ZDP-ActiveEndpointsResp primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpActiveEndpointsResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-ActiveEp.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-SimpleDescriptorReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpActiveEPReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) ;                      /* nwkAddrOfInterest */

}

/**************************************************************************//**
  \brief ZDP-NwkAddress.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpNwkAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

  /**************************************************************************//**
  \brief ZDP-NwkAddressResp primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpNwkAddressResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NwkAddress.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-SimpleDescriptorReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpNwkAddressReqLength(const void *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(ExtAddr_t) +                      /* ieeeAddrOfInterest */
         sizeof(uint8_t) +                        /* reqType */
         sizeof(uint8_t);                       /* startIndex */
}

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpNodeDescriptorReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-NodeDescriptor request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpNodeDescriptorReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                       /* nwkAddrOfInterest */
         sizeof(uint16_t);                        /* destAddr */
}

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpNodeDescriptorResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLqi.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtLqiReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLqi.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtLqiResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLeave.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtLeaveiReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLeave.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtLeaveResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-NodeDescriptor request frame size.
******************************************************************************/
INLINE uint16_t
zsiZdpMgmtLeaveReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t) +                       /* deviceAddr */
         sizeof(uint8_t)+                        /* removeChildren */
         sizeof(uint8_t);                        /* rejoin */
}  

/**************************************************************************//**
  \brief ZDP-MgmtNwkUpdate.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtUpdateReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtNwkUpdate.Notify primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtUpdateNotify(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtNwkUpdate.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-NodeDescriptor request frame size.
******************************************************************************/
INLINE uint16_t
zsiZdpMgmtUpdateReqLength(ZDO_MgmtNwkUpdateReq_t *mgmtUpdateRequest)
{
  uint16_t addressLength = (mgmtUpdateRequest->scanDuration == ZDO_MGMT_NWK_PARAMS_CHANGE)? sizeof(uint16_t):0;
  uint16_t scanCountOrUpdateIdLen = ((ZDO_MGMT_ED_SCAN_DUR_5 >= mgmtUpdateRequest->scanDuration) ||
                                  (ZDO_MGMT_CHANNEL_CHANGE == mgmtUpdateRequest->scanDuration) || 
                                  (ZDO_MGMT_NWK_PARAMS_CHANGE == mgmtUpdateRequest->scanDuration))? sizeof(uint8_t):0;


  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint32_t) +                      /* scanChannels */
         sizeof(uint8_t)+                        /* scanDuration */
         scanCountOrUpdateIdLen +                /* scanCount or nwkUpdateId*/ 
         addressLength;                          /* nwkManagerAddr */
}

#ifdef _BINDING_
/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMatchDescriptorReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-MatchDescriptorReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpMatchDescriptorReqLength(const ZDO_MatchDescReq_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                       /* nwkAddrOfInterest */
         sizeof(uint16_t) +                       /* profileId */
         sizeof(uint8_t)  +                       /* numInClusters */
         req->numInClusters * sizeof(uint16_t)  + /* inClusterList */
         sizeof(uint8_t)  +                       /* numOutClusters */
         req->numOutClusters * sizeof(uint16_t);  /* inClusterList */
}

/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMatchDescriptorResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Bind.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpBindReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Bind.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-Bind.Request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpBindReqLength(const ZDO_BindReq_t *const req)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint64_t) + /* srcAddr */
                    sizeof(uint8_t) +  /* srcEndpoint */
                    sizeof(uint16_t) + /* clusterId */
                    sizeof(uint8_t);   /* dstAddrMode */

  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    length += sizeof(uint64_t) + /* dstExtAddr */
              sizeof(uint8_t);   /* dstEndpoint */
  }
  else
    length += sizeof(uint16_t);  /* dstGroupAddr */

  return length;
}

/**************************************************************************//**
  \brief ZDP-Bind.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpBindResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Unbind.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpUnbindReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Unbind.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZDP-Unbind.Request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpUnbindReqLength(const ZDO_UnbindReq_t *const req)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint64_t) + /* srcAddr */
                    sizeof(uint8_t) +  /* srcEndpoint */
                    sizeof(uint16_t) + /* clusterId */
                    sizeof(uint8_t);   /* dstAddrMode */

  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    length += sizeof(uint64_t) + /* dstExtAddr */
              sizeof(uint8_t);   /* dstEndpoint */
  }
  else
    length += sizeof(uint16_t);  /* dstGroupAddr */

  return length;
}
/**************************************************************************//**
  \brief ZDP-Unbind.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpUnbindResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtBind.Reqest primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtBindReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);


/**************************************************************************//**
  \brief ZDP-MgmtBind.Response primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtBindResp(void *memory,
  ZsiCommandFrame_t *const cmdFrame);


#endif /* _BINDING_ */

#elif defined(ZAPPSI_NP)
/**************************************************************************//**
  \brief ZDP-IeeeAddress.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpIeeeAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-IeeeAddress.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpIeeeAddressResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-IeeeAddress.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-IeeeAddress.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpIeeeAddressRespLength(const ZDO_IeeeAddrResp_t *const resp)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t) +                    /* ieeeAddrRemote */
         sizeof(uint16_t)  +                   /* nwkAddrRemote */
         sizeof(uint8_t)  +                    /* numAssocDev */
         sizeof(uint8_t)  +                    /* startIndex */
         resp->numAssocDev * sizeof(uint16_t); /* nwkAddrAssocDevList */
}

/**************************************************************************//**
  \brief ZDP-PermitJoining.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpPermitJoiningReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-PermitJoining.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpDeviceAnnceReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZDP-PermitJoining.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpPermitJoiningResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-PermitJoining.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-PermitJoining.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpPermitJoiningRespLength(const void *const resp)
{
  (void)resp;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief ZDP-DeviceAnnceRaspframe size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-DeviceAnnce.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpDeviceAnnceRespLength(const void *const resp)
{
  (void)resp;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief ZDP-DeviceAnnceZgp.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeDeviceAnnceZgpResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpSimpleDescriptorReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpSimpleDescriptorResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-SimpleDescriptor.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-SimpleDescriptor.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpSimpleDescriptorRespLength(const ZDO_SimpleDescResp_t *const resp)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                   /* nwkAddrOfInterest */
         sizeof(uint8_t)  +                   /* simpleDescLength */
         resp->length * sizeof(uint8_t);      /* simple desc response payload */
}

/**************************************************************************//**
  \brief ZDP-ActiveEPReq primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpActiveEndpointsReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-ActiveEndpoints.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpActiveEndPointsResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-MatchDescriptor.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpActiveEndpointsRespLength(const ZDO_ActiveEPResp_t *const resp)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                   /* nwkAddrOfInterest */
         sizeof(uint8_t)  +                   /* activeEPCount */
         resp->activeEPCount * sizeof(uint8_t); /* activeEPList */
}

/**************************************************************************//**
  \brief ZDP-NwkAddress.Req primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpNwkAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NwkAddress.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpNwkAddressResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NwkAddress.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-MatchDescriptor.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpNwkAddressRespLength(const  ZDO_NwkAddrResp_t *const resp)
{

  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(ExtAddr_t) +     /* ieeeAddrRemote */
         sizeof(ShortAddr_t)+    /* nwkAddrRemote */
         sizeof(uint8_t)  +       /* numAssocDev */
         ((resp->numAssocDev)?sizeof(uint8_t):0) +  /* startIndex */
         sizeof(ShortAddr_t) * resp->numAssocDev; /* associated device list */
}

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpNodeDescriptorReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpNodeDescriptorResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-NodeDescriptor.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-NodeDescriptor.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpNodeDescriptorRespLength(const ZDO_NodeDescResp_t *const resp)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                   /* nwkAddrOfInterest */
         sizeof(NodeDescriptor_t);          /* NodeDescriptor_t */
}

/**************************************************************************//**
  \brief ZDP-MgmtLqi.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtLqiReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLqi.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtLqiResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtLqi.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-Bind.Response request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZdpMgmtLqiRespLength(const ZDO_MgmtLqiResp_t *const resp)
{
  uint8_t neigbTableLength = 0;
  for (uint8_t i = 0; i < resp->neighborTableListCount; i++)
  {
    neigbTableLength +=  sizeof(uint64_t) + /* extPandId */
                         sizeof(uint64_t) + /* extAddr */
                         sizeof(uint16_t) + /* networkAddr */
                         sizeof(uint8_t) +  /* deviceType */
                         sizeof(uint8_t) +  /* rxOnWhenIdle */
                         sizeof(uint8_t) +  /* relationship */
                         sizeof(uint8_t) +  /* permitJoining */
                         sizeof(uint8_t) +  /* depth */
                         sizeof(uint8_t);   /* lqi */
  }

  return ZSI_COMMAND_FRAME_OVERHEAD + 
         sizeof(uint8_t)   +   /* neighborTableEntries */
         sizeof(uint8_t)   +   /* startIndex */
         sizeof(uint8_t)   +   /* neighborTableListCount */
         neigbTableLength;        /* neighbor table */
}

/**************************************************************************//**
  \brief ZDP-MgmtLeave.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtLeaveReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  
/**************************************************************************//**
  \brief ZDP-MgmtLeave.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtLeaveResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtNwkUpdate.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtUpdateReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  
/**************************************************************************//**
  \brief ZDP-MgmtNwkUpdate.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtUpdateNotify(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtUpdateNotf.Resp frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-MgmtUpdate.Notify request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZdpMgmtUpdateNotfLength(const ZDO_MgmtNwkUpdateNotf_t *mgmtUpdateNotify)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + 
         //sizeof(uint16_t)   +  /* conflictAddress */
         sizeof(uint32_t)   +   /* scanResult.scannedChannels */
         sizeof(uint16_t)   +   /* scanResult.totalTransmissions */
         sizeof(uint16_t)   +   /* scanResult.transmissionsFailures */
         sizeof(uint8_t)    +   /* scanResult.scannedChannelsListCount); */
         (sizeof(uint8_t) * mgmtUpdateNotify->scanResult.scannedChannelsListCount); 
                                /*energyValues */

}

#ifdef _BINDING_
/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMatchDescriptorReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMatchDescriptorResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MatchDescriptor.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-MatchDescriptor.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpMatchDescriptorRespLength(const ZDO_MatchDescResp_t *const resp)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +                   /* nwkAddrOfInterest */
         sizeof(uint8_t)  +                   /* matchLength */
         (resp->matchLength * sizeof(uint8_t)); /* matchList */
}

/**************************************************************************//**
  \brief ZDP-Bind.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpBindReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Bind.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpBindResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Bind.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-Bind.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpBindRespLength(const void *const resp)
{
  (void)resp;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */

}

/**************************************************************************//**
  \brief ZDP-Unbind.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpUnbindReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Unbind.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpUnbindResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-Unbind.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-Unbind.Response request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZdpUnbindRespLength(const void *const resp)
{
  (void)resp;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */

}

/**************************************************************************//**
  \brief ZDP-MgmtBind.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZdpMgmtBindReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtBind.Response primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZdpMgmtBindResp(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief ZDP-MgmtBind.Response frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] resp - response parameters.

  \return ZDP-Bind.Response request frame size.
 ******************************************************************************/
INLINE uint16_t zsiZdpMgmtBindRespLength(const ZDO_MgmtBindResp_t *const resp)
{
  uint8_t bindReqLength = 0;
  for (uint8_t i = 0;i < resp->bindingTableListCount; i++)
  {
    bindReqLength +=  sizeof(uint64_t) + /* srcAddr */
                              sizeof(uint8_t) +  /* srcEndpoint */
                              sizeof(uint16_t) + /* clusterId */
                              sizeof(uint8_t);   /* dstAddrMode */

    if (APS_EXT_ADDRESS == resp->bindingTableList[i].dstAddrMode)
    {
      bindReqLength += sizeof(uint64_t) + /* dstExtAddr */
                       sizeof(uint8_t);   /* dstEndpoint */
    }
    else
      bindReqLength += sizeof(uint16_t);  /* dstGroupAddr */
  }
  return ZSI_COMMAND_FRAME_OVERHEAD + 
         sizeof(uint8_t)   +   /* bindingTableEntries */
         sizeof(uint8_t)   +   /* startIndex */
         sizeof(uint8_t)   +   /* bindingTableListCount */
         bindReqLength;        /* Bind Reqs */
}

#endif /* _BINDING_ */

#endif /* ZAPPSI_NP */

#ifdef ZAPPSI_HOST
#define zsiDeserializeZdpMatchDescriptorReq  NULL
#define zsiDeserializeZdpSimpleDescriptorReq NULL
#define zsiDeserializeZdpIeeeAddressReq      NULL
#define zsiDeserializeZdpPermitJoiningReq    NULL
#define zsiDeserializeZdpDeviceAnnceReq      NULL
#define zsiDeserializeZdpBindReq             NULL
#define zsiDeserializeZdpUnbindReq           NULL
#define zsiDeserializeZdpActiveEndpointsReq  NULL
#define zsiDeserializeZdpNwkAddressReq       NULL
#define zsiDeserializeZdpNodeDescriptorReq   NULL
#define zsiDeserializeZdpMgmtBindReq         NULL
#define zsiDeserializeZdpMgmtLqiReq          NULL
#define zsiDeserializeZdpMgmtLeaveReq        NULL
#define zsiDeserializeZdpMgmtUpdateReq       NULL 
#ifndef _BINDING_
#define zsiSerializeZdpMatchDescriptorReq    NULL
#define zsiSerializeZdpBindReq               NULL
#define zsiSerializeZdpUnbindReq             NULL
#define zsiDeserializeZdpMatchDescriptorResp NULL
#define zsiDeserializeZdpBindResp            NULL
#define zsiSerializeZdpMgmtBindReq           NULL
#define zsiDeserializeZdpmgmtBindResp        NULL
#endif /* _BINDING_ */

#elif defined(ZAPPSI_NP)
#define zsiDeserializeZdpMatchDescriptorResp NULL
#define zsiDeserializeZdpSimpleDescriptorResp NULL
#define zsiDeserializeZdpIeeeAddressResp     NULL
#define zsiDeserializeZdpPermitJoiningResp   NULL
#define zsiDeserializeDeviceAnnceZgpResp     NULL
#define zsiDeserializeZdpBindResp            NULL
#define zsiDeserializeZdpUnbindResp          NULL
#define zsiDeserializeZdpActiveEndpointsResp NULL
#define zsiDeserializeZdpNwkAddressResp      NULL
#define zsiDeserializeZdpNodeDescriptorResp  NULL
#define zsiDeserializeZdpMgmtBindResp        NULL
#define zsiDeserializeZdpMgmtLqiResp         NULL
#define zsiDeserializeZdpMgmtLeaveResp       NULL
#define zsiDeserializeZdpMgmtUpdateNotify    NULL
#ifndef _BINDING_
#define zsiDeserializeZdpMatchDescriptorReq  NULL
#define zsiDeserializeZdpBindReq             NULL
#define zsiSerializeZdpMatchDescriptorResp   NULL
#define zsiSerializeZdpBindResp              NULL
#define zsiSerializeZdpUnbindResp            NULL
#define zsiDeserializeZdpMgmtBindReq         NULL
#define zsiSerializeZdpMgmtBindResp          NULL
#endif /* _BINDING_ */

#endif /* ZAPPSI_NP */

#endif /* _ZSIZDPSERIALIZATION_H_ */
