/*******************************************************************************
  ZappSi APS Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiApsSerialization.h

  Summary:
    This file contains the ZAppSI APS primitives serialization interface.

  Description:
    This file contains the ZAppSI APS primitives serialization interface.
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


#ifndef _ZSIAPSSERIALIZATION_H_
#define _ZSIAPSSERIALIZATION_H_

/******************************************************************************
                    Includes section
******************************************************************************/
#include <aps.h>
#include <zsiFrames.h>
#include <zsiDriver.h>
#include <sspCommon.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define ZSI_MAX_ENDPOINTS_AMOUNT 3U
#define ZSI_MAX_OUT_CLUSTERS_PER_ENDPOINT 18U
#define ZSI_MAX_IN_CLUSTERS_PER_ENDPOINT   8U

#define ISBOUNDTOANYGROUP_PARAMS_SIZE   3
#define UPDATESECURITYPOLICY_PARAMS_SIZE 2

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct _ZsiEndpointDescriptor_t
{
  bool                      busy;
  APS_RegisterEndpointReq_t registerEndpointReq;
  SimpleDescriptor_t        simpleDescriptor;
  ClusterId_t               inClusterList[ZSI_MAX_IN_CLUSTERS_PER_ENDPOINT];
  ClusterId_t               outClusterList[ZSI_MAX_OUT_CLUSTERS_PER_ENDPOINT];
} ZsiEndpointDescriptor_t;

typedef struct _ZsiKeyDescriptor_t
{
  uint8_t         keyFond;
  const ExtAddr_t *extAddress;
  uint8_t         *key;
} ZsiKeyDescriptor_t;

typedef struct _ZsiSetAuthorizedStatus_t
{
  const ExtAddr_t *extAddress;
  bool status;
} ZsiSetAuthorizedStatus_t;

#ifdef _BINDING_
typedef struct _ZsiIsBoundParams_t
{
  uint16_t clusterId;
  uint8_t endpoint;
}ZsiIsBoundParams_t;
#endif // _BINDING_

#ifdef _LINK_SECURITY_
typedef struct _ZsiUpdateSecurityPolicy_t
{
  uint8_t spid;
  uint8_t policy;
}ZsiUpdateSecurityPolicy_t;
#endif
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for APS commands deserialization and processing.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiApsFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief Finds APS endpoint descriptor whithin endpoints queue.

  \param[in] endpoint - endpoint identifier.

  \return Pointer to appropriate endpoint descriptor, or NULL if wasn't found.
 ******************************************************************************/
APS_RegisterEndpointReq_t* zsiApsFindEndpoint(Endpoint_t endpoint);

/**************************************************************************//**
  \brief APS-RegisterEndpoint request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_RegisterEndpointReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-RegisterEndpoint request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-RegisterEndpoint request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_RegisterEndpointReqLength(const APS_RegisterEndpointReq_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +  /* endpoint */
         sizeof(uint16_t) + /* AppProfileId */
         sizeof(uint16_t) + /* AppDeviceId */
         sizeof(uint8_t) + /* AppDeviceVersion */
         sizeof(uint8_t) + /* AppInClustersCount */
                           /* AppInClustersList */
         req->simpleDescriptor->AppInClustersCount * sizeof(uint16_t) +
         sizeof(uint8_t) + /* AppOutClustersCount */
                           /* AppOutClustersList */
         req->simpleDescriptor->AppOutClustersCount * sizeof(uint16_t);
}

/**************************************************************************//**
  \brief APS-RegisterEndpoint confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_RegisterEndpointConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextBindingEntry request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_NextBindingEntryReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextBindingEntryReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-RegisterEndpoint request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_NextBindingEntryReqLength(const ApsBindingEntry_t *const req)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint64_t) + /* srcAddr */
                    sizeof(uint8_t)  + /* srcEndpoint */
                    sizeof(uint16_t) + /* clusterId */
                    sizeof(uint8_t);   /* dstAddrMode */

  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    length += sizeof(uint64_t) + /* extAddr */
              sizeof(uint8_t);   /* endpoint */
  }
  else
    length += sizeof(uint16_t); /* group */

  return length;
}
/**************************************************************************//**
  \brief APS-NextBindingEntry confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_NextBindingEntryConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Indication primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_DataInd(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_DataReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-Data.Request request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_DataReqLength(const APS_DataReq_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t)  + /* dstAddrMode */
         sizeof(uint16_t) + /* dstAddress.shortAddress */
         sizeof(uint64_t) + /* dstAddress.extAddress */
         sizeof(uint8_t)  + /* dstEndpoint */
         sizeof(uint16_t) + /* profileId */
         sizeof(uint16_t) + /* clusterId */
         sizeof(uint8_t)  + /* srcEndpoint */
         sizeof(uint16_t) + /* asduLength */
         req->asduLength  + /* asdu */
         sizeof(uint8_t)  + /* txOptions.securityEnabledTransmission */
         sizeof(uint8_t)  + /* txOptions.useNwkKey */
         sizeof(uint8_t)  + /* txOptions.acknowledgedTransmission */
         sizeof(uint8_t)  + /* txOptions.fragmentationPermitted */
         sizeof(uint8_t)  + /* txOptions.includeExtendedNonce */
         sizeof(uint8_t)  + /* txOptions.doNotDecrypt */
         sizeof(uint8_t)  + /* txOptions.indicateBroadcasts */
#if defined _GREENPOWER_SUPPORT_
         sizeof(uint8_t)     + /*useAlias*/
         sizeof(uint16_t) + /*aliasSrcAddr*/
         sizeof(uint8_t)  + /*aliasSeqNumber*/
#endif
         sizeof(uint8_t);   /* radius */
}

/**************************************************************************//**
  \brief APS-Data.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_DataConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
 ******************************************************************************/
void zsiAPS_DataConfCallback(void *const req);

#ifdef _BINDING_
/**************************************************************************//**
  \brief APS-Bind.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_BindReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Bind.Request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-Bind.Request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_BindReqLength(const APS_BindReq_t *const req)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint64_t) + /* srcAddr */
                    sizeof(uint8_t)  + /* srcEndpoint */
                    sizeof(uint16_t) + /* clusterId */
                    sizeof(uint8_t);   /* dstAddrMode */

  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    length += sizeof(uint64_t) + /* extAddr */
              sizeof(uint8_t);   /* endpoint */
  }
  else
    length += sizeof(uint16_t); /* group */

  return length;
}

/**************************************************************************//**
  \brief APS-Bind.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_BindConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-Unbind.Request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_UnBindReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-Unbind.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_UnBindConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_FreeBindingEntryReq request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_FreeBindingEntryReq(const void *const memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-FreeBindingEntry.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_FreeBindingEntryConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-IsBoundToAnyGroup.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_IsBoundToAnyGroupReq(const void *const memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-IsBoundToAnyGroup frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_IsBoundToAnyGroup frame size.
******************************************************************************/
INLINE uint16_t
zsiAPS_IsBoundToAnyGroupReqLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint8_t)  + /* srcEndpoint */
                    sizeof(uint16_t); /* clusterId */
  return length;
}
/**************************************************************************//**
  \brief APS-IsBoundToAnyGroup.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_IsBoundToAnyGroupConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif /* _BINDING_ */
#if defined _SECURITY_
/**************************************************************************//**
  \brief APS-GetOwnTcMode request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_GetOwnTcModeReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_GetOwnTcModeReqLength request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_GetOwnTcMode request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_GetOwnTcModeReqLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD;
  return length;
}
/**************************************************************************//**
  \brief APS-GetOwnTcMode confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetOwnTcModeConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_SetTrustCenterAddressReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_SetTrustCenterAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief zsiAPS_SetTrustCenterAddressReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_SetTrustCenterAddressReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_SetTrustCenterAddressReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}
/**************************************************************************//**
  \brief APS_SetTrustCenterAddressConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetTrustCenterAddressConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-InitKeyPairSetReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_InitKeyPairSetReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_InitKeyPairSet request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_InitKeyPairSet request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_InitKeyPairSetReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief InitKeyPairSetReq confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_InitKeyPairSetConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif // _SECURITY_
#ifdef _LINK_SECURITY_
/**************************************************************************//**
  \brief APS-UpdateSecurityPolicy request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_UpdateSecurityPolicyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_UpdateSecurityPolicyLength request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_UpdateSecurityPolicy request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_UpdateSecurityPolicyReqLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t) +sizeof(uint8_t);
  return length;
}
/**************************************************************************//**
  \brief APS-UpdateSecurityPolicy confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_UpdateSecurityPolicyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-SetLinkKey request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_SetLinkKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-SetLinkKey request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-SetLinkKey request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_SetLinkKeyReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t) + /* extAddress */
         SECURITY_KEY_SIZE; /* key */
}

/**************************************************************************//**
  \brief APS-SetLinkKey confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetLinkKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetLinkKey request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_GetLinkKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetLinkKey request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-GetLinkKey request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_GetLinkKeyReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* handle */
}

/**************************************************************************//**
  \brief APS-GetLinkKey confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetLinkKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-FindKeys request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_FindKeysReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-FindKeys request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-FindKeys request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_FindKeysReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t); /* extAddress */
}

/**************************************************************************//**
  \brief APS-FindKeys confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_FindKeysConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetKeyPairDeviceAddress request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_GetKeyPairDeviceAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetKeyPairDeviceAddress request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-GetKeyPairDeviceAddress request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_GetKeyPairDeviceAddressReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +
         sizeof(uint16_t);
}

/**************************************************************************//**
  \brief APS-GetKeyPairDeviceAddress confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetKeyPairDeviceAddressConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextKeys request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_NextKeysReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextKeys request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-NextKeys request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_NextKeysReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +
         sizeof(uint16_t);
}

/**************************************************************************//**
  \brief APS_SetAuthorizedStatus request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-NextKeys request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_SetAuthorizedStatusReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(ExtAddr_t) +
         sizeof(bool);
}

/**************************************************************************//**
  \brief APS_SetDefaultKeyPairStatusReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-NextKeys request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_SetDefaultKeyPairStatusReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(APS_KeyPairFlags_t);
}

/**************************************************************************//**
  \brief APS_AreKeysAuthorizedReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-NextKeys request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_AreKeysAuthorizedReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}

/**************************************************************************//**
  \brief APS_GetTrustCenterAddressReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_GetTrustCenterAddressReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_GetTrustCenterAddressReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief APS-NextKeys confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_NextKeysConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_SetAuthorizedStatusReq request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_SetAuthorizedStatusReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_SetAuthorizedStatus confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetAuthorizedStatusConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-AreKeysAuthorizedReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_AreKeysAuthorizedReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_SetDefaultKeyPairStatusReq request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_SetDefaultKeyPairStatusReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-SetDefaultKeyPairStatus.confirm deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetDefaultKeyPairStatusConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_AreKeysAuthorized.confirm deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_AreKeysAuthorizedConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-MarkGlobalKeyAsTCKey.request serialization and
         processing routine.

  \param[in] handle - valid key handle.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_MarkGlobalKeyAsTCKeyReq(const void *const hndl,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-MarkGlobalKeyAsTCKey confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_MarkGlobalKeyAsTCkeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_GetTrustCenterAddressReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_GetTrustCenterAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_GetTrustCenterAddressConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetTrustCenterAddressConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief Request to mark specified global key as 'TC key', size calculation routine.

  \param[in] handle - pointer to valid key handle.

  \return Processing result.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_MarkGlobalKeyAsTCKeyReqLength(const APS_KeyHandle_t *const handle)
{
  (void)handle;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) + /* idx */
         sizeof(uint8_t);   /* flags */
}
#if defined (_TRUST_CENTRE_)
/**************************************************************************//**
  \brief TC_SetAllowInstallCodes primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeTC_SetAllowInstallCodesReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief TC_SetAllowInstallCodes confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeTC_SetAllowInstallCodesConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief zsiTC_SetAllowInstallCodesReqLength

  \param[in] handle - pointer to valid key handle.

  \return size of the PzsiTC_SetAllowInstallCodesReq.
 ******************************************************************************/
INLINE uint16_t
zsiTC_SetAllowInstallCodesReqLength(const APS_KeyHandle_t *const handle)
{
  (void)handle;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t);
}
#endif /* #if defined (_TRUST_CENTRE_)*/
#endif /* _LINK_SECURITY_ */
/**************************************************************************//**
  \brief To reset the apsEndpoint Queue

 ******************************************************************************/
void zsiApsclearEndPointQueue(void);

#elif defined(ZAPPSI_NP)
/********************************************************************
\brief Application endpoint indication handler wrapper

\param[in] ind - APS Data Indication primitive pointer

\return None.
********************************************************************/
void APS_DataInd(APS_DataInd_t *ind);

/**************************************************************************//**
\brief APS-Data.Confirm primitive wrapper routine.

\param[in] conf - confirm parameters.

\return None.
******************************************************************************/
void zsiAPS_DataConf(APS_DataConf_t *conf);

/**************************************************************************//**
  \brief APS-Data.Indication primitive serialization routine.

  \param[in] ind - indication parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_DataInd(const void *const ind,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_DataReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Confirm primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeAPS_DataConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Data.Confirm primitive frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] confirm - confirm parameters.

  \return APS-Data.Confirm primitive frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_DataConfLength(const void *const confirm)
{
  (void)confirm;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +   /* status */
         sizeof(uint32_t);   /* txTime */
}

/**************************************************************************//**
  \brief APS-RegisterEndpoint request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_RegisterEndpointReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextBindingEntry request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_NextBindingEntryReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-RegisterEndpoint request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-RegisterEndpoint request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_RegisterEndpointConfLength(const void *const confirm)
{
  (void)confirm;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t);  /* status */
}

/**************************************************************************//**
  \brief APS-Bind.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-Bind.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_NextBindingEntryConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */
}
#if defined _SECURITY_
/**************************************************************************//**
  \brief APS-GetOwnTcMode request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetOwnTcModeReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_GetOwnTcMode.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS_GetOwnTcMode.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_GetOwnTcModeConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* Mode */
}
/**************************************************************************//**
  \brief APS_SetTrustCenterAddressReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetTrustCenterAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_SetTrustCenterAddress.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS_SetTrustCenterAddress.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_SetTrustCenterAddressConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
#endif // _SECURITY_
#ifdef _LINK_SECURITY_
/**************************************************************************//**
  \brief APS_UpdateSecurityPolicy request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_UpdateSecurityPolicyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \briefAPS_UpdateSecurityPolicyLength frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS_UpdateSecurityPolicy frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_UpdateSecurityPolicyConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief APS_InitKeyPairSet request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_InitKeyPairSetReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \briefAPS_InitKeyPairSet frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS_InitKeyPairSet frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_InitKeyPairSetConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
#endif //_LINK_SECURITY_
#if defined _BINDING_
/**************************************************************************//**
  \brief APS_UnBindReq request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_UnBindReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-UnBind.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-Unbind.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_UnBindConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */
}
/**************************************************************************//**
  \brief APS-FreeBindingEntry.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_FreeBindingEntryReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS_IsBoundToAnyGroup request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_IsBoundToAnyGroupReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief APS-IsBoundToAnyGroupConfLength.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-IsBoundToAnyGroup.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_IsBoundToAnyGroupConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */
}
#endif //_BINDING_


#ifdef _BINDING_
/**************************************************************************//**
  \brief APS-Bind.Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_BindReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-Bind.Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-Bind.Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_BindConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* status */
}

#endif /* _BINDING_ */

#ifdef _LINK_SECURITY_
/**************************************************************************//**
  \brief APS-SetLinkKey request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetLinkKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-SetLinkKey confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-SetLinkKey confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_SetLinkKeyConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* handle */
}

/**************************************************************************//**
  \brief APS-GetLinkKey request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetLinkKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetLinkKey confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-GetLinkKey confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_GetLinkKeyConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +  /* keyFond */
         SECURITY_KEY_SIZE; /* key */
}

/**************************************************************************//**
  \brief APS-FindKeys request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_FindKeysReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-FindKeys confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-FindKeys confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_FindKeysConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* handle */
}

/**************************************************************************//**
  \brief APS-GetKeyPairDeviceAddress request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetKeyPairDeviceAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-GetKeyPairDeviceAddress confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-GetKeyPairDeviceAddress confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_GetKeyPairDeviceAddressConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t); /* deviceAddress */
}

/**************************************************************************//**
  \brief APS-NextKeys request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_NextKeysReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-NextKeys confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-NextKeys confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_NextKeysConfLength(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) +
         sizeof(uint8_t);
}
/**************************************************************************//**
  \brief APS_SetAuthorizedStatus confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] conf - confirm parameters.

  \return APS-NextKeys confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_SetAuthorizedStatusConf(const void *const conf)
{
  (void)conf;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief APS_SetAuthorizedStatus request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetAuthorizedStatusReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS-MarkGlobalKeyAsTCKey.request deserialization and
         processing routine.

  \param[in] handle - valid key handle.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_MarkGlobalKeyAsTCKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief size calculation routine.

  \return Processing result.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_MarkGlobalKeyAsTCKeyConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief size of APS_SetDefaultKeyPairStatusConf calculation routine.

  \return Processing result.
 ******************************************************************************/
INLINE uint16_t zsiAPS_SetDefaultKeyPairStatusConf(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief APS_AreKeysAuthorizedConf request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS-NextKeys request frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_AreKeysAuthorizedConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(bool);
}

/**************************************************************************//**
  \brief APS_GetTrustCenterAddressConf request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return APS_GetTrustCenterAddressConf confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiAPS_GetTrustCenterAddressConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}

/**************************************************************************//**
  \brief APS-SetDefaultKeyPairStatus.request deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_SetDefaultKeyPairStatusReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_AreKeysAuthorized.request deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_AreKeysAuthorizedReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief APS_GetTrustCenterAddressReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeAPS_GetTrustCenterAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#if defined (_TRUST_CENTRE_)
/**************************************************************************//**
  \brief TC_SetAllowInstallCodes request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeTC_SetAllowInstallCodesReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief zsiTC_SetAllowInstallCodesConfLengthConf request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return zsiTC_SetAllowInstallCodes Confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiTC_SetAllowInstallCodesConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
#endif /* #if defined (_TRUST_CENTRE_)*/
#endif /* _LINK_SECURITY_ */

#endif /* ZAPPSI_NP */

/**************************************************************************//**
  \brief Allocate memory for new endpoint.

  \return Pointer to memory if allocated.
 ******************************************************************************/
ZsiEndpointDescriptor_t *zsiApsAllocateEndpointMemory(void);
/**************************************************************************//**
  \brief Free memory for new endpoint.

  \param[in] Pointer to memory to be freed allocated.
 ******************************************************************************/
void zsiFreeEndpointMemory(ZsiEndpointDescriptor_t * memory);

/**************************************************************************//**
  \brief APS-RegisterEndpoint request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return APS-RegisterEndpoint request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiAPS_DataIndLength(const APS_DataInd_t *const ind)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t)  + /* dstAddrMode */
         sizeof(uint16_t) + /* dstAddress.shortAddress */
         sizeof(uint64_t) + /* dstAddress.extAddress */
         sizeof(uint8_t)  + /* dstEndpoint */
         sizeof(uint8_t)  + /* srcAddrMode */
         sizeof(uint16_t) + /* srcAddress.shortAddress */
         sizeof(uint64_t) + /* srcAddress.extAddress */
         sizeof(uint16_t) + /* prevHopAddr */
         sizeof(uint8_t)  + /* srcEndpoint */
         sizeof(uint16_t) + /* profileId */
         sizeof(uint16_t) + /* clusterId */
         sizeof(uint16_t) + /* asduLength */
         ind->asduLength  + /* asdu */
         sizeof(uint8_t)  + /* status */
         sizeof(uint8_t)  + /* securityStatus */
         sizeof(uint8_t)  + /* nwkSecurityStatus */
         sizeof(uint8_t)  + /* linkQuality */
         sizeof(uint32_t) + /* rxTime */
         sizeof(int8_t);    /* rssi */
}


#ifdef ZAPPSI_HOST

#define zsiDeserializeAPS_RegisterEndpointReq         NULL
#define zsiDeserializeAPS_NextBindingEntryReq         NULL
#define zsiDeserializeAPS_DataReq                     NULL
#define zsiDeserializeAPS_SetLinkKeyReq               NULL
#define zsiDeserializeAPS_FindKeysReq                 NULL
#define zsiDeserializeAPS_GetLinkKeyReq               NULL
#define zsiDeserializeAPS_GetKeyPairDeviceAddressReq  NULL
#define zsiDeserializeAPS_NextKeysReq                 NULL
#define zsiDeserializeAPS_MarkGlobalKeyAsTCKeyReq     NULL
#define zsiDeserializeAPS_BindReq                     NULL
#define zsiDeserializeAPS_SetAuthorizedStatusReq      NULL
#define zsiDeserializeAPS_SetDefaultKeyPairStatusReq  NULL
#define zsiDeserializeAPS_AreKeysAuthorizedReq        NULL
#define zsiDeserializeAPS_GetTrustCenterAddressReq    NULL
#define zsiDeserializeTC_SetAllowInstallCodesReq      NULL
#define zsiDeserializeAPS_SetTrustCenterAddressReq    NULL
#define zsiDeserializeAPS_GetOwnTcModeReq             NULL
#define zsiDeserializeAPS_UpdateSecurityPolicyReq     NULL
#define zsiDeserializeAPS_InitKeyPairSetReq           NULL
#define zsiDeserializeAPS_UnBindReq                   NULL
#define zsiDeserializeAPS_FreeBindingEntryReq         NULL
#define zsiDeserializeAPS_IsBoundToAnyGroupReq        NULL
#ifndef _BINDING_
#define zsiDeserializeAPS_BindConf                    NULL
#endif /* _BINDING_ */

#ifndef _LINK_SECURITY_
#define zsiDeserializeAPS_SetLinkKeyConf              NULL
#define zsiDeserializeAPS_GetLinkKeyConf              NULL
#define zsiDeserializeAPS_FindKeysConf                NULL
#define zsiDeserializeAPS_GetKeyPairDeviceAddressConf NULL
#define zsiDeserializeAPS_NextKeysConf                NULL
#define zsiDeserializeAPS_SetAuthorizedStatusConf     NULL
#define zsiDeserializeAPS_SetAuthorizedStatusConf     NULL
#define zsiDeserializeAPS_AreKeysAuthorizedConf       NULL
#define zsiDeserializeAPS_GetTrustCenterAddressConf   NULL
#define zsiDeserializeTC_SetAllowInstallCodesConf     NULL
#define zsiDeserializeAPS_GetOwnTcModeConf            NULL
#define zsiDeserializeAPS_SetTrustCenterAddressConf   NULL
#define zsiDeserializeAPS_UpdateSecurityPolicyConf    NULL
#define zsiDeserializeAPS_InitKeyPairSetConf          NULL
#define zsiDeserializeAPS_UnBindConf                  NULL
#define zsiDeserializeAPS_FreeBindingEntryConf        NULL
#define zsiDeserializeAPS_IsBoundToAnyGroupConf       NULL
#endif /* _LINK_SECURITY_ */

#elif defined(ZAPPSI_NP)

#define zsiDeserializeAPS_RegisterEndpointConf        NULL
#define zsiDeserializeAPS_NextBindingEntryConf        NULL
#define zsiDeserializeAPS_DataInd                     NULL
#define zsiDeserializeAPS_DataConf                    NULL
#define zsiDeserializeAPS_SetLinkKeyConf              NULL
#define zsiDeserializeAPS_GetLinkKeyConf              NULL
#define zsiDeserializeAPS_FindKeysConf                NULL
#define zsiDeserializeAPS_GetKeyPairDeviceAddressConf NULL
#define zsiDeserializeAPS_NextKeysConf                NULL
#define zsiDeserializeAPS_MarkGlobalKeyAsTCkeyConf    NULL
#define zsiDeserializeAPS_BindConf                    NULL
#define zsiDeserializeAPS_SetAuthorizedStatusConf     NULL
#define zsiDeserializeAPS_SetDefaultKeyPairStatusConf NULL
#define zsiDeserializeAPS_AreKeysAuthorizedConf       NULL
#define zsiDeserializeAPS_GetTrustCenterAddressConf   NULL
#define zsiDeserializeTC_SetAllowInstallCodesConf     NULL
#define zsiDeserializeAPS_GetOwnTcModeConf            NULL
#define zsiDeserializeAPS_SetTrustCenterAddressConf   NULL
#define zsiDeserializeAPS_UpdateSecurityPolicyConf    NULL
#define zsiDeserializeAPS_InitKeyPairSetConf          NULL
#define zsiDeserializeAPS_UnBindConf                  NULL
#define zsiDeserializeAPS_FreeBindingEntryConf        NULL
#define zsiDeserializeAPS_IsBoundToAnyGroupConf       NULL
#ifndef _BINDING_
#define zsiDeserializeAPS_BindReq                     NULL
#endif /* _BINDING_ */

#ifndef _LINK_SECURITY_
#define zsiDeserializeAPS_SetLinkKeyReq               NULL
#define zsiDeserializeAPS_FindKeysReq                 NULL
#define zsiDeserializeAPS_GetLinkKeyReq               NULL
#define zsiDeserializeAPS_GetKeyPairDeviceAddressReq  NULL
#define zsiDeserializeAPS_NextKeysReq                 NULL
#define zsiDeserializeAPS_SetAuthorizedStatusReq      NULL
#define zsiDeserializeAPS_SetDefaultKeyPairStatusReq  NULL
#define zsiDeserializeAPS_AreKeysAuthorizedReq        NULL
#define zsiDeserializeAPS_MarkGlobalKeyAsTCKeyReq     NULL
#define zsiDeserializeAPS_GetTrustCenterAddressReq    NULL
#define zsiDeserializeTC_SetAllowInstallCodesReq      NULL
#define zsiDeserializeAPS_SetTrustCenterAddressReq    NULL
#define zsiDeserializeAPS_UpdateSecurityPolicyReq     NULL
#define zsiDeserializeAPS_InitKeyPairSetReq           NULL
#define zsiDeserializeAPS_UnBindReq                   NULL
#define zsiDeserializeAPS_FreeBindingEntryReq         NULL
#define zsiDeserializeAPS_IsBoundToAnyGroupReq        NULL
#endif /* _LINK_SECURITY_ */

#endif /* ZAPPSI_NP */

#endif /* _ZSIAPSSERIALIZATION_H_ */
