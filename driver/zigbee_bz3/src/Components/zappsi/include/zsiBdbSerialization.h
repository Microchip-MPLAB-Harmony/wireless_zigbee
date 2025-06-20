/*******************************************************************************
  ZAppSI BDB Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiBdbSerialization.h

  Summary:
    This file contains the ZAppSI Bdb primitives serialization interface.

  Description:
    This file contains the ZAppSI Bdb primitives serialization interface.
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

#ifndef ZSIBDBSERIALIZATION_H
#define ZSIBDBSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
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
ZsiProcessingRoutine_t zsiBdbFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST

/**************************************************************************//**
  \brief zsiSerializeBDB_GetBdbNodeIsOnANetworkReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeBDB_GetBdbNodeIsOnANetworkReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief PDS_IsAbleToRestoreConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBDB_GetBdbNodeIsOnANetworkConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief BDB_SetBdbNodeIsOnANetworkReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeBDB_SetBdbNodeIsOnANetworkReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief BDB_SetBdbNodeIsOnANetwork confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBDB_SetBdbNodeIsOnANetworkConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief BDB_GetBdbNodeIsOnANetwork Req frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return BDB_GetBdbNodeIsOnANetwork request frame size.
 ******************************************************************************/
INLINE uint16_t zsiBDB_GetBdbNodeIsOnANetworkReqLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}
/**************************************************************************//**
  \brief BDB_GetBdbNodeIsOnANetworkReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_IsOwnExtAddrReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiBDB_SetBdbNodeIsOnANetworkReqLength(const void *const req)
{
  (void)req;
  return (ZSI_COMMAND_FRAME_OVERHEAD + sizeof(bool));
}

#elif defined(ZAPPSI_NP)

/**************************************************************************//**
  \brief BDB_GetBdbNodeIsOnANetworkReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBDB_GetBdbNodeIsOnANetworkReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief BDB_SetBdbNodeIsOnANetworkReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBDB_SetBdbNodeIsOnANetworkReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief BDB_GetBdbNodeIsOnANetwork frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return BDB_GetBdbNodeIsOnANetwork request frame size.
 ******************************************************************************/
INLINE uint16_t zsiBDB_GetBdbNodeIsOnANetworkLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(bool);
}

/**************************************************************************//**
  \brief zsiPDS_DeleteConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiBDB_SetBdbNodeIsOnANetworkConfLength(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

#endif /* ZAPPSI_NP */


#ifdef ZAPPSI_HOST
#define zsiDeserializeBDB_GetBdbNodeIsOnANetworkReq NULL
#define zsiDeserializeBDB_SetBdbNodeIsOnANetworkReq NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeBDB_GetBdbNodeIsOnANetworkConf NULL
#define zsiDeserializeBDB_SetBdbNodeIsOnANetworkConf NULL
#endif /* ZAPPSI_NP */

#endif /* ZSIPDSSERIALIZATION_H */
