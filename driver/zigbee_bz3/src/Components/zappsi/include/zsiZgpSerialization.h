/*******************************************************************************
  ZAppSI ZGP Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiZgpSerialization.h

  Summary:
    This file contains the ZAppSI ZGP primitives serialization interface.

  Description:
    This file contains the ZAppSI ZGP primitives serialization interface.
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


#ifndef _ZSIZGPSERIALIZATION_H_
#define _ZSIZGPSERIALIZATION_H_

#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zsiFrames.h>
#include <zsiDriver.h>
#include <include/zgpCommon.h>
#include <zgpLowNvmTable.h>
#include <zgpLowGpdf.h>
#include <zdo.h>
/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct PACK
{
  ZGP_TableUpdateAction_t action;
  ZGP_EntryType_t tableType;
  void *entry;
}zsiZgplAddUpdateTableEntryParams_t;

typedef struct PACK
{
  ZGP_TableOperationField_t tableOperationField;
  ZGP_GpdId_t *gpdId;
  uint8_t endPoint;
  void *entry;
}zsiZgplReadTableEntryFromNvmParams_t;

typedef struct PACK
{
  ZGP_TableOperationField_t tableOperationField;
  ZGP_GpdId_t gpdId;
  uint8_t endPoint;
}zsiZgplDeleteTableEntryFromNvmParams_t;

typedef struct PACK
{
  uint32_t *frameCounter;
  ZGP_TableOperationField_t tableOperationField;
  ZGP_GpdId_t gpdId;
  uint8_t endPoint;
  bool isUpdateOperation;
}zsiZgplFrameCounterReadorUpdateOnNvmParams_t;

typedef struct PACK
{
  bool isProxy;
  ZGP_Mode_t mode;
}zsiZgplSetDevModeParams_t;

typedef struct _ZsiZgpZdpReq_t
{
  ZDO_ZdpReq_t zdpReq;
  bool busy;
} zsiZgpZdpReq_t;

typedef union
{
  zsiZgplReadTableEntryFromNvmParams_t zgplReadTableEntryFromNvmParams;
  zsiZgplDeleteTableEntryFromNvmParams_t zgplDeleteTableEntryFromNvmParams;
  zsiZgplFrameCounterReadorUpdateOnNvmParams_t zgplFrameCounterReadOrUpdateOnNvmParams;
}zsiZgpInputParams_t;
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for ZGP commands deserialization.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiZgpFindProcessingRoutine(uint8_t commandId);
#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief ZGPL-NvmTableInit request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_NvmTableInitReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_NvmTableInit confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_NvmTableInitConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableEntry request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_ResetTableEntryReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableEntry request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_ResetTableEntry request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_ResetTableEntryReqLength(ZGP_EntryType_t tableType)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t); /* tabletype*/
  if(ZGP_PROXY_ENTRY == tableType)
  {
    length += sizeof(ZGP_ProxyTableEntry_t);
  }
  else if(ZGP_SINK_ENTRY == tableType)
  {
    length += sizeof(ZGP_SinkTableEntry_t);
  }
  return length;
}
/**************************************************************************//**
  \brief ZGPL_ResetTableEntry confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ResetTableEntryConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_TotalNonEmptyEntries request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_TotalNonEmptyTableEntriesReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_TotalNonEmptyEntries confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_TotalNonEmptyTableEntriesConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_AddOrUpdateTableEntryOnNvm request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_AddOrUpdateTableEntryOnNvmReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_AddOrUpdateTableEntryOnNvm request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_AddOrUpdateTableEntryOnNvm request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_AddOrUpdateTableEntryOnNvmLength(ZGP_EntryType_t tableType)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t) + sizeof(uint8_t); // tableType, action
  if(ZGP_PROXY_ENTRY == tableType)
  {
    length += sizeof(ZGP_ProxyTableEntry_t);
  }
  else if(ZGP_SINK_ENTRY == tableType)
  {
    length += sizeof(ZGP_SinkTableEntry_t);
  }
  return length;
}
/**************************************************************************//**
  \brief ZGPL_AddOrUpdateTableEntryOnNvm confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_AddOrUpdateTableEntryOnNvmConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ReadTableEntryFromNvm request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_ReadTableEntryFromNvmReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ReadTableEntryFromNvm request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_ReadTableEntryFromNvm request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_ReadTableEntryFromNvmLength(ZGP_TableOperationField_t tableOperationField)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ZGP_TableOperationField_t);
  if(ZGP_SRC_APPID == tableOperationField.appId)
    length += sizeof(ZGP_SourceId_t);
  else if(ZGP_IEEE_ADDR_APPID == tableOperationField.appId)
    length += sizeof(ExtAddr_t) + sizeof(uint8_t); //endpoint
  if(ZGP_PROXY_ENTRY == tableOperationField.tableType)
  {
    length += sizeof(ZGP_ProxyTableEntry_t);
  }
  else if(ZGP_SINK_ENTRY == tableOperationField.tableType)
  {
    length += sizeof(ZGP_SinkTableEntry_t);
  }
  return length;
}
/**************************************************************************//**
  \brief ZGPL_ReadTableEntryFromNvm confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ReadTableEntryFromNvmConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_DeleteTableEntryFromNvm request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_DeleteTableEntryFromNvmReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_DeleteTableEntryFromNvm request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_DeleteTableEntryFromNvm request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_DeleteTableEntryFromNvmLength(ZGP_TableOperationField_t tableOperationField)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ZGP_TableOperationField_t) + sizeof(uint8_t); // endpoint
  if(ZGP_SRC_APPID == tableOperationField.appId)
    length += sizeof(ZGP_SourceId_t);
  else if(ZGP_IEEE_ADDR_APPID == tableOperationField.appId)
    length += sizeof(ExtAddr_t);
  return length;
}
/**************************************************************************//**
  \brief ZGPL_DeleteTableEntryFromNvm confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_DeleteTableEntryFromNvmConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FrameCounterReadorUpdateOnNvm request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_FrameCounterReadorUpdateOnNvmReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FrameCounterReadorUpdateOnNvm request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_FrameCounterReadorUpdateOnNvm request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_FrameCounterReadorUpdateOnNvmLength(ZGP_TableOperationField_t tableOperationField)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint32_t) +sizeof(ZGP_TableOperationField_t)
                   + sizeof(uint8_t) + sizeof(uint8_t); // endpoint + updateOperation
  if(ZGP_SRC_APPID == tableOperationField.appId)
    length += sizeof(ZGP_SourceId_t);
  else if(ZGP_IEEE_ADDR_APPID == tableOperationField.appId)
    length += sizeof(ExtAddr_t);
  return length;
}
/**************************************************************************//**
  \brief ZGPL_FrameCounterReadorUpdateOnNvm confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_FrameCounterReadorUpdateOnNvmConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableToFN request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_ResetTableToFNReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableToFN request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_ResetTableToFN request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_ResetTableToFNReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief ZGPL_ResetTableToFN confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ResetTableToFNConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_SetDeviceMode request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_SetDeviceModeReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_SetDeviceMode confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_SetDeviceModeConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GetDeviceMode request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_GetDeviceModeReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GetDeviceMode confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_GetDeviceModeConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_EnableDisableDirectMode request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_EnableDisableDirectModeReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_EnableDisableDirectMode confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_EnableDisableDirectModeConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_Init request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_InitReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_Init confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_InitConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FlushTxQueue request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_FlushTxQueueReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FlushTxQueue confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_FlushTxQueueConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_CheckForDuplicate request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_CheckForDuplicateReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_CheckForDuplicateReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_CheckForDuplicateReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_CheckForDuplicateReqLength(ZGP_LowDataInd_t *zgpLowDataInd)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t) +  /* security key */
         sizeof(uint8_t) +  /* addr mode */
         sizeof(uint64_t) + /* srcAddress */
         sizeof(uint8_t) + /* appId */
         sizeof(uint32_t) + /* source ID*/
         sizeof(uint8_t) + /* endpoint*/
         sizeof(uint32_t) + /* gpdSecurityFrameCounter */
         sizeof(uint32_t) + /* mic */
         sizeof(uint32_t) + /* pan id */
         sizeof(uint8_t) + /* status */
         sizeof(uint8_t) + /*frameType */
         sizeof(uint8_t) + /* lqi */
         sizeof(uint8_t) + /* rssi */
         sizeof(uint8_t) + /* seqNumber */
         sizeof(uint8_t) + /* securityLevel*/
         sizeof(uint8_t) + /* secKeyType */
         sizeof(uint8_t) + /* command id */
         sizeof(uint8_t) + /* autoCommissioning bit */
         sizeof(uint8_t) + /* rxAfterTx */
         sizeof(uint8_t) + /* gpdAsduLength */
         zgpLowDataInd->gpdAsduLength;
}
/**************************************************************************//**
  \brief ZGPL_CheckForDuplicate confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_CheckForDuplicateConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GpdfDataReq request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiSerializeZGPL_GpdfDataReqReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GpdfDataReq request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return ZGPL_GpdfDataReq request frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_GpdfDataReqReqLength(ZGP_GpdfDataReq_t* req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint32_t) + /* gpTxQueueEntryLifeTime */
         sizeof(ZGP_FrameDir_t) + /* frame dir*/
         sizeof(ZGP_GpdfTxOptions_t) + /* txOptions */
         sizeof(ZGP_ApplicationId_t) + /* appId */
         sizeof(ZGP_SourceId_t) + /* srcId */
         sizeof(ExtAddr_t) + /* ExtAddr */
         sizeof(uint8_t) + /* endpoint*/
         sizeof(ZGP_CommandId_t) + /* zgp command id */
         sizeof(uint8_t) + /* gpepHandle*/
         sizeof(uint8_t) + /* asdulength */
         req->gpdAsduLength + /* pdu */
         sizeof(bool); /* action */
}
/**************************************************************************//**
  \brief ZGPL_GpdfDataReq confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_GpdfDataReqConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#elif defined (ZAPPSI_NP)
/**************************************************************************//**
  \brief ZGPL_NvmTableInit Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_NvmTableInitReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableEntry Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ResetTableEntryReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ResetTableEntry primitive frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] confirm - confirm parameters.

  \return ZGPL_ResetTableEntry primitive frame size.
******************************************************************************/
INLINE uint16_t
zsiZGPL_ResetTableEntryConfLength(ZGP_EntryType_t tableType)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD; /* tabletype*/
  if(ZGP_PROXY_ENTRY == tableType)
  {
    length += sizeof(ZGP_ProxyTableEntry_t);
  }
  else if(ZGP_SINK_ENTRY == tableType)
  {
    length += sizeof(ZGP_SinkTableEntry_t);
  }
  return length;
}
/**************************************************************************//**
  \brief ZGPL_TotalNonEmptyEntries Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_TotalNonEmptyTableEntriesReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_AddOrUpdateTableEntryOnNvm Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_AddOrUpdateTableEntryOnNvmReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ReadTableEntryFromNvm Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ReadTableEntryFromNvmReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_ReadTableEntryFromNvm confirm primitive frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] confirm - confirm parameters.

  \return ZGPL_ReadTableEntryFromNvm Confirm primitive frame size.
 ******************************************************************************/
INLINE uint16_t
zsiZGPL_ReadTableEntryFromNvmConfLength(ZGP_EntryType_t tableType)
{
  uint8_t length = ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t); //status
  if(ZGP_PROXY_ENTRY == tableType)
  {
    length += sizeof(ZGP_ProxyTableEntry_t);
  }
  else if(ZGP_SINK_ENTRY == tableType)
  {
    length += sizeof(ZGP_SinkTableEntry_t);
  }
  return length;
}
/**************************************************************************//**
  \brief ZGPL_DeleteTableEntryFromNvm Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_DeleteTableEntryFromNvmReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FrameCounterReadorUpdateOnNvm Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_FrameCounterReadorUpdateOnNvmReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief ZGPL_ResetTableToFN Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_ResetTableToFNReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_SetDeviceMode Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_SetDeviceModeReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GetDeviceMode Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_GetDeviceModeReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_EnableDisableDirectMode Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_EnableDisableDirectModeReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_Init Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_InitReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_FlushTxQueue Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_FlushTxQueueReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_CheckForDuplicate Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_CheckForDuplicateReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief ZGPL_GpdfDataReq Request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeZGPL_GpdfDataReqReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
#endif /* ZAPPSI_HOST */

#ifdef ZAPPSI_HOST
#define zsiDeserializeZGPL_NvmTableInitReq                   NULL
#define zsiDeserializeZGPL_ResetTableEntryReq                NULL
#define zsiDeserializeZGPL_TotalNonEmptyTableEntriesReq      NULL
#define zsiDeserializeZGPL_AddOrUpdateTableEntryOnNvmReq     NULL
#define zsiDeserializeZGPL_ReadTableEntryFromNvmReq          NULL
#define zsiDeserializeZGPL_DeleteTableEntryFromNvmReq        NULL
#define zsiDeserializeZGPL_FrameCounterReadorUpdateOnNvmReq  NULL
#define zsiDeserializeZGPL_ResetTableToFNReq                 NULL
#define zsiDeserializeZGPL_SetDeviceModeReq                  NULL
#define zsiDeserializeZGPL_GetDeviceModeReq                  NULL
#define zsiDeserializeZGPL_EnableDisableDirectModeReq        NULL
#define zsiDeserializeZGPL_InitReq                           NULL
#define zsiDeserializeZGPL_FlushTxQueueReq                   NULL
#define zsiDeserializeZGPL_CheckForDuplicateReq              NULL
#define zsiDeserializeZGPL_GpdfDataReqReq                    NULL
#elif defined (ZAPPSI_NP)
#define zsiDeserializeZGPL_NvmTableInitConf                  NULL
#define zsiDeserializeZGPL_ResetTableEntryConf               NULL
#define zsiDeserializeZGPL_TotalNonEmptyTableEntriesConf     NULL
#define zsiDeserializeZGPL_AddOrUpdateTableEntryOnNvmConf    NULL
#define zsiDeserializeZGPL_TotalNonEmptyEntriesConf          NULL
#define zsiDeserializeZGPL_ReadTableEntryFromNvmConf         NULL
#define zsiDeserializeZGPL_DeleteTableEntryFromNvmConf       NULL
#define zsiDeserializeZGPL_FrameCounterReadorUpdateOnNvmConf NULL
#define zsiDeserializeZGPL_ResetTableToFNConf                NULL
#define zsiDeserializeZGPL_SetDeviceModeConf                 NULL
#define zsiDeserializeZGPL_GetDeviceModeConf                 NULL
#define zsiDeserializeZGPL_EnableDisableDirectModeConf       NULL
#define zsiDeserializeZGPL_InitConf                          NULL
#define zsiDeserializeZGPL_FlushTxQueueConf                  NULL
#define zsiDeserializeZGPL_CheckForDuplicateConf             NULL
#define zsiDeserializeZGPL_GpdfDataReqConf                   NULL
#endif

#endif // APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#endif /* _ZSIZGPSERIALIZATION_H_ */
