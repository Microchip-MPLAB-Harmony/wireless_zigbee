/*******************************************************************************
  ZAppSI PDS Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiPdsSerialization.h

  Summary:
    This file contains the ZAppSI PDS primitives serialization interface.

  Description:
    This file contains the ZAppSI PDS primitives serialization interface.
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


#ifndef _ZSIPDSSERIALIZATION_H
#define _ZSIPDSSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <wlPdsTypes.h>
#include <zsiFrames.h>
#include <zsiDriver.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for MAC commands deserialization.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiPdsFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/******************************************************************************
\brief PDS item initialization routine
******************************************************************************/
void PDS_InitItems_Host(void);

/**************************************************************************//**
\brief Checks if the specified PDS file or directory can be restored
       from non-volatile memory

\ingroup pds

PDS files not included in the current build configuration will be ignored.

\param[in] memoryId - an identifier of PDS file or directory to be checked.

\return true, if the specified memory can be restored; false - otherwise.
******************************************************************************/
bool PDS_IsAbleToRestore_Host(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Restores data from non-volatile storage.

\ingroup pds

PDS files not included in the current build configuration will be ignored.
Restoring process will be performed only if all files, expected for actual
configuration, are presented in NV storage.

\param[in] memoryId - an identifier of PDS file or directory to be restored
                      from non-volatile memory.

\return true, if all expected files have been restored, false - otherwise.
******************************************************************************/
bool PDS_Restore_Host(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Stores data in non-volatile memory in background, not blocking other
       processes.

\ingroup pds

All PDS files which are absent in the current build configuration will be ignored.

\param[in] memoryId - an identifier of PDS file or directory to be stored
                      in non-volatile memory.

\return True, if storing process has begun, false - otherwise.
******************************************************************************/
bool PDS_Store_Host(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Deletes data from non-volatile storage

\param[in] memoryId - an identifier of PDS item or directory to be deleted
                      from non-volatile memory

\return PDS_DataServerState_t - status of PDS delete
******************************************************************************/
PDS_DataServerState_t PDS_Delete_Host(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Deletes data from non-volatile storage except the Persistant items
       depending on the parameter passed.

\param[in] includingPersistentItems - deletes persistant items if TRUE
                                      deletes all other items except persistant 
                                      items if FALSE

\return PDS_DataServerState_t - status of PDS DeleteAll
******************************************************************************/
PDS_DataServerState_t PDS_DeleteAll_Host(bool includingPersistentItems);

/**************************************************************************//**
\brief Provides PDS with information about memory that should be kept up-to-date
       in the non-volatile storage.

\ingroup pds

Data will be saved im non-volatile memory upon specific events.

\param[in] memoryId - an identifier of PDS file or directory to be stored
                      in non-volatile memory.
******************************************************************************/
void PDS_StoreByEvents_Host(PDS_MemId_t memoryId);

/**************************************************************************//**
  \brief PDS_StoreReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_StoreReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_StoreConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_RestoreReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_RestoreReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_RestoreConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_DeleteReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_DeleteReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_DeleteConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_DeleteConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief PDS_DeleteAllReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_DeleteAllReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_DeleteConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_DeleteAllConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

  /**************************************************************************//**
  \brief PDS_StoreByEvents primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_StoreByEventsReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

 /**************************************************************************//**
  \brief PDS_StoreByEvents confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_StoreByEventsConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_IsAbleToRestoreReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_IsAbleToRestoreReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_IsAbleToRestoreConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_IsAbleToRestoreConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_InitItemsReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_InitItemsReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_InitItemConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_InitItemsConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

  /**************************************************************************//**
  \brief PDS_SubscribeToStoreCompletionReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializePDS_SubscribeToStoreCompletionReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_SubscribeToStoreCompletionConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_SubscribeToStoreCompletionConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_IsOwnExtAddrReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiPDS_StoreReqLength(const void *const req)
{
  (void)req;
  return (ZSI_COMMAND_FRAME_OVERHEAD + sizeof(PDS_MemId_t));
}

/**************************************************************************//**
  \brief PDS_DeleteReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiPDS_DeleteReqLength(const void *const req)
{
  (void)req;
  return (ZSI_COMMAND_FRAME_OVERHEAD + sizeof(PDS_MemId_t));
}

/**************************************************************************//**
  \brief PDS_SubscribeToStoreCompletionReqLength frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return  PDS_SubscribeToStoreCompletionReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiPDS_SubscribeToStoreCompletionReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(SYS_EventId_t);
}

#elif defined(ZAPPSI_NP)
/**************************************************************************//**
  \brief PDS_StoreReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_StoreReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_RestoreReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_DeleteReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_DeleteReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_DeleteAllReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_DeleteAllReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreByEvents request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_StoreByEventsReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_IsAbleToRestoreReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_IsAbleToRestoreReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_InitItmes request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_InitItemsReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_SubscribeToStoreCompletion request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializePDS_SubscribeToStoreCompletionReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_StoreConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return PDS_StoreConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiPDS_StoreConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(bool);
}

/**************************************************************************//**
  \brief zsiPDS_DeleteConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return zsiPDS_DeleteConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiPDS_DeleteConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(PDS_DataServerState_t);
}

/**************************************************************************//**
  \brief zsiPDS_StoreByEventsConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return zsiPDS_StoreByEventsConf request frame size.
 ******************************************************************************/
 INLINE uint16_t zsiPDS_StoreByEventsConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

#endif /* ZAPPSI_NP */


#ifdef ZAPPSI_HOST
#define zsiDeserializePDS_StoreReq                        NULL
#define zsiDeserializePDS_RestoreReq                      NULL
#define zsiDeserializePDS_DeleteReq                       NULL
#define zsiDeserializePDS_DeleteAllReq                    NULL
#define zsiDeserializePDS_StoreByEventsReq                NULL
#define zsiDeserializePDS_IsAbleToRestoreReq              NULL
#define zsiDeserializePDS_InitItemsReq                    NULL
#define zsiDeserializePDS_SubscribeToStoreCompletionReq   NULL

#elif defined(ZAPPSI_NP)
#define zsiDeserializePDS_StoreConf                       NULL
#define zsiDeserializePDS_RestoreConf                     NULL
#define zsiDeserializePDS_DeleteConf                      NULL
#define zsiDeserializePDS_DeleteAllConf                   NULL
#define zsiDeserializePDS_StoreByEventsConf               NULL
#define zsiDeserializePDS_IsAbleToRestoreConf             NULL
#define zsiDeserializePDS_InitItemsConf                   NULL
#define zsiDeserializePDS_SubscribeToStoreCompletionConf  NULL

#endif /* ZAPPSI_NP */

#endif /* _ZSIPDSSERIALIZATION_H */
