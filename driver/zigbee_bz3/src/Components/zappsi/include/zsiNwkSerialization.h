/*******************************************************************************
  ZAppSI NWK Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiNwkSerialization.h

  Summary:
    This file contains the ZAppSI NWK primitives serialization interface.

  Description:
    This file contains the ZAppSI NWK primitives serialization interface.
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


#ifndef ZSINWKSERIALIZATION_H
#define ZSINWKSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <nwk.h>
#include <zsiFrames.h>
#include <zsiDriver.h>

/******************************************************************************
                    Types section
******************************************************************************/
#ifdef _SECURITY_
typedef struct _ZsiSetKey_t
{
  uint8_t key[SECURITY_KEY_SIZE];
  NWK_KeySeqNum_t keySeqNum;
} ZsiSetKey_t;
#endif //SECURITY

typedef struct _ZsiGroup_t
{
  uint16_t addr;
  uint8_t data;
} ZsiGroup_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for NWK commands deserialization and processing.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiNwkFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST

/**************************************************************************//**
  \brief Nwk-Leave.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
******************************************************************************/
void zsiNWK_LeaveConfCallback(void *const req);
/**************************************************************************//**
  \brief NWK-GetNextHop request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetNextHopReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetNextHop confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetNextHopConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetNextHop request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetNextHop request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetNextHopReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* shortAddr */
}

/**************************************************************************//**
  \brief NWK-IsGroupMember.Request primitive serialization and processing
         routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_IsGroupMemberReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-IsGroupMember.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_IsGroupMemberConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK_GroupReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK_GroupReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GroupReqLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint16_t)  + /* addr */
                    sizeof(uint8_t); /* data */
  return length;
}

/**************************************************************************//**
  \brief NWK-AddGroup.Request primitive serialization and processing
         routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_AddGroupReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-AddGroup.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_AddGroupConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-RemoveGroup.Request primitive serialization and processing
         routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_RemoveGroupReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-RemoveGroup.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_RemoveGroupConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-RemoveAllGroups.Request primitive serialization and processing
         routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_RemoveAllGroupsReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-RemoveAllGroups.Confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_RemoveAllGroupsConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t
zsiNWK_RemoveAllGroupsReqLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint8_t); /* data */
  return length;
}

/**************************************************************************//**
  \brief NWK-GetUpdateId.Request primitive serialization and processing
         routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetUpdateIdReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetUpdateId confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetUpdateIdConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GetUpdateIdReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief NWK-NextGroup request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_NextGroupReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-NextGroup confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_NextGroupConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_NextGroupReqLength(const void *const req)
{
   uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint16_t)  + /* addr */
                    sizeof(uint8_t); /* data */
  return length;
}

/**************************************************************************//**
  \brief NWK-GroupCapacity request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GroupCapacityReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GroupCapacity confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GroupCapacityConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GroupCapacityReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

ZsiProcessingResult_t zsiSerializeNWK_LeaveReq(const void *const memory,
  ZsiCommandFrame_t *const cmdFrame);

ZsiProcessingResult_t zsiDeserializeNWK_LeaveConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t
zsiNWK_LeaveReqLength(const NWK_LeaveReq_t *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t) + /* shortAddress */
         sizeof(uint64_t) + /* deviceAddress */
         sizeof(uint8_t)  + /* leaveControl.cleanRouteTable */
         sizeof(uint8_t) + /*leaveControl.cleanNeighborTable */
         sizeof(uint8_t) + /*leaveControl.cleanAddresmap */
         sizeof(uint8_t) + /*leaveControl.cleanKeyPairSet */
         sizeof(uint8_t) + /*leaveControl.cleanBindingTable */
         sizeof(uint8_t) + /*leaveControl.cleanGroupTable */
         sizeof(uint8_t) + /*leaveControl.cleanNwkSecKeys */ 
         sizeof(uint8_t) + /*leaveControl.silent */   
         sizeof(uint8_t) + /* removeChildren */
         sizeof(uint8_t) + /* rejoin */
         sizeof(uint8_t);   /* noExtendedAddress */
}

/**************************************************************************//**
  \brief NWK-GetParentShortAddr request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetParentShortAddrReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetParentShortAddr confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetParentShortAddrConf(void *memory,
ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GetParentShortAddrReqLength(void)
{
   return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief NWK-GetExtByShortAddress request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetExtByShortAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetExtByShortAddress request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetExtByShortAddress request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetExtByShortAddressReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* shortAddr */
}

/**************************************************************************//**
  \brief NWK-GetExtByShortAddress confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetExtByShortAddressConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetShortByExtAddress request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

      \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetShortByExtAddressReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetShortByExtAddress request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetShortByExtAddress request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetShortByExtAddressReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t); /* extAddr */
}

/**************************************************************************//**
  \brief NWK-GetShortByExtAddress confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetShortByExtAddressConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetUnicastDeliveryTime primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetUnicastDeliveryTimeReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetUnicastDeliveryTime frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-GetUnicastDeliveryTime request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetUnicastDeliveryTimeReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief NWK-GetUnicastDeliveryTime confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetUnicastDeliveryTimeConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetShortAddr primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetShortAddrReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetShortAddr frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-GetShortAddr request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiSerializeNWK_GetShortAddrReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief NWK-GetShortAddr confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetShortAddrConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief NWK-GetShortAddr primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetLogicalChannelReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief NWK-GetLogical frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-GetLogical Channel request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiSerializeNWK_GetLogicalChannelReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief NWK-GetShortAddr confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetLogicalChannelConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#ifdef _SECURITY_
/**************************************************************************//**
  \brief NWK-SetKey frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-SetKey request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiSerializeNWK_SetKeyReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         SECURITY_KEY_SIZE +
         sizeof(uint8_t);   /* KeySeqNum*/
}
/**************************************************************************//**
  \brief NWK-GetActiveKey frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-GetActiveKey request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiSerializeNWK_GetActiveKeyReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief NWK-SetKey primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_SetKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-SetKey confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_SetKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-ActivateKey primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_ActivateKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-ActivateKey frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] ind - indication parameters.

  \return NWK-ActivateKey request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiSerializeNWK_ActivateKeyReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t);   /* KeySeqNum*/;
}
/**************************************************************************//**
  \brief NWK-ActivateKey confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_ActivateKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-GetActiveKey primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetActiveKeyReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-GetActiveKeyConf confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetActiveKeyConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif /* _SECURITY_ */
/**************************************************************************//**
  \brief NWK_GetPanId primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_GetPanIdReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK_GetPanId confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetPanIdConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief NWK_ForceChangeOwnAddr primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_ForceChangeOwnAddrReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief NWK_ForceChangeOwnAddr confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_ForceChangeOwnAddrConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#elif defined(ZAPPSI_NP)
/**************************************************************************//**
  \brief NWK-GetNextHop request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetNextHopReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetNextHop confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetNextHop confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetNextHopConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* shortAddr */
}

/**************************************************************************//**
  \brief NWK-GetExtByShortAddress request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetExtByShortAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetExtByShortAddress confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetExtByShortAddress confirm frame size.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetUpdateIdReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GetUpdateIdConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t);
}
/**************************************************************************//**
  \brief NWK-IsGroupMember.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_IsGroupMemberReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-AddGroup.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_AddGroupReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t
zsiNWK_GroupConfLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(bool); /* status */
  return length;
}

/**************************************************************************//**
  \brief NWK-RemoveGroup.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_RemoveGroupReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-RemoveAllGroups.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_RemoveAllGroupsReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t
zsiNWK_RemoveAllGroupsConfLength(void)
{
  uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint8_t); /* data */
  return length;
}

INLINE uint16_t
zsiNWK_GetExtByShortAddressConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint64_t); /* extAddr */
}

/**************************************************************************//**
  \brief NWK-NextGroup.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_NextGroupReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_NextGroupConfLength(void)
{
   uint16_t length = ZSI_COMMAND_FRAME_OVERHEAD +
                    sizeof(uint16_t)  + /* addr */
                    sizeof(uint8_t); /* data */
  return length;
}

/**************************************************************************//**
  \brief NWK-GroupCapacity.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GroupCapacityReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GroupCapacityConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t);
}

ZsiProcessingResult_t zsiDeserializeNWK_LeaveReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t
zsiNWK_LeaveConfLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t);   /* status */
}

/**************************************************************************//**
  \brief NWK-GetParentShortAddr.request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetParentShortAddrReq(void *memory,
ZsiCommandFrame_t *const cmdFrame);

INLINE uint16_t zsiNWK_GetParentShortAddrConfLength(void)
{
   return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint16_t) /* shortAddress */;
}
/**************************************************************************//**
  \brief NWK-GetShortByExtAddress request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetShortByExtAddressReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetShortByExtAddress confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetShortByExtAddress confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetShortByExtAddressConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* shortAddr */
}

/**************************************************************************//**
  \brief NWK-GetUnicastDeliveryTime request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetUnicastDeliveryTimeReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-GetUnicastDeliveryTime confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-GetUnicastDeliveryTime confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetUnicastDeliveryTimeConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint32_t); /* deliveryTime */
}

/**************************************************************************//**
  \brief NWK-NWK_GetShortAdd request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetShortAddReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief NWK-NWK_GetShortAdd confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-NWK_GetShortAdd confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetShortAddConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint16_t); /* shortAddress */
}
/**************************************************************************//**
  \brief NWK-NWK_GetShortAdd request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetLogicalChannelReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-NWK_GetLogicalChannel confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-NWK_GetLogicalChannel confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetLogicalChannelConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t); /* channel */
}
/**************************************************************************//**
\brief NWK-Leave.Confirm primitive wrapper routine.

\param[in] conf - confirm parameters.

\return None.
******************************************************************************/
void zsiNWK_LeaveConf(NWK_LeaveConf_t *conf);
#ifdef _SECURITY_
/**************************************************************************//**
  \brief NWK-SetKey request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_SetKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-SetKey confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-SetKey confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_SetKeyConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief NWK-SetKey request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_ActivateKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-ActivateKey confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-ActivateKey confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_ActivateKeyConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief NWK-GetActiveKey request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetActiveKeyReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief NWK-GetActiveKey confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return NWK-ActivateKey confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiNWK_GetActiveKeyConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + SECURITY_KEY_SIZE;
}
/**************************************************************************//**
  \brief NWK-leave.Confirm primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeNWK_LeaveConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
#endif /* _SECURITY_ */
/**************************************************************************//**
  \brief NWK_GetPanId request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_GetPanIdReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief NWK_ForceChangeOwnAddr request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeNWK_ForceChangeOwnAddrReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif /* ZAPPSI_NP */

#if defined(ZAPPSI_HOST)
#define zsiDeserializeNWK_GetShortByExtAddressReq   NULL
#define zsiDeserializeNWK_GetNextHopReq             NULL
#define zsiDeserializeNWK_GetUnicastDeliveryTimeReq NULL
#define zsiDeserializeNWK_GetExtByShortAddressReq   NULL
#define zsiDeserializeNWK_GetShortAddReq            NULL
#define zsiDeserializeNWK_GetLogicalChannelReq      NULL
#define zsiDeserializeNWK_SetKeyReq                 NULL
#define zsiDeserializeNWK_ActivateKeyReq            NULL
#define zsiDeserializeNWK_GetActiveKeyReq           NULL
#define zsiDeserializeNWK_GetPanIdReq               NULL
#define zsiDeserializeNWK_ForceChangeOwnAddrReq     NULL
#define zsiDeserializeNWK_IsGroupMemberReq          NULL
#define zsiDeserializeNWK_AddGroupReq               NULL
#define zsiDeserializeNWK_RemoveGroupReq            NULL
#define zsiDeserializeNWK_RemoveAllGroupsReq        NULL
#define zsiDeserializeNWK_GetUpdateIdReq            NULL
#define zsiDeserializeNWK_NextGroupReq              NULL
#define zsiDeserializeNWK_GroupCapacityReq          NULL
#define zsiDeserializeNWK_LeaveReq                  NULL
#define zsiDeserializeNWK_GetParentShortAddrReq     NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeNWK_GetShortByExtAddressConf   NULL
#define zsiDeserializeNWK_GetNextHopConf             NULL
#define zsiDeserializeNWK_GetUnicastDeliveryTimeConf NULL
#define zsiDeserializeNWK_GetExtByShortAddressConf   NULL
#define zsiDeserializeNWK_GetShortAddrConf           NULL
#define zsiDeserializeNWK_GetLogicalChannelConf      NULL
#define zsiDeserializeNWK_SetKeyConf                 NULL
#define zsiDeserializeNWK_ActivateKeyConf            NULL
#define zsiDeserializeNWK_GetActiveKeyConf           NULL
#define zsiDeserializeNWK_GetPanIdConf               NULL
#define zsiDeserializeNWK_ForceChangeOwnAddrConf     NULL
#define zsiDeserializeNWK_IsGroupMemberConf          NULL
#define zsiDeserializeNWK_AddGroupConf               NULL
#define zsiDeserializeNWK_RemoveGroupConf            NULL
#define zsiDeserializeNWK_RemoveAllGroupsConf        NULL
#define zsiDeserializeNWK_GetUpdateIdConf            NULL
#define zsiDeserializeNWK_NextGroupConf              NULL
#define zsiDeserializeNWK_GroupCapacityConf          NULL
#define zsiDeserializeNWK_LeaveConf                  NULL
#define zsiDeserializeNWK_GetParentShortAddrConf     NULL

#endif /* ZAPPSI_NP */

#endif /* ZSIAPSSERIALIZATION_H */
