/*******************************************************************************
  ZAppSI MAC Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiMacSerialization.h

  Summary:
    This file contains the ZAppSI Mac primitives serialization interface.

  Description:
    This file contains the ZAppSI Mac primitives serialization interface.
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


#ifndef ZSIMACSERIALIZATION_H
#define ZSIMACSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <rfRandom.h>
#include <macEnvironment.h>
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
ZsiProcessingRoutine_t zsiMacFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief MAC_IsOwnExtAddrReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_IsOwnExtAddrReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_IsOwnExtAddrReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}

/**************************************************************************//**
  \brief MAC_GetExtAddrReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_GetExtAddrReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief RF_RandomReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return RF_RandomReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiRF_RandomReq(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD;
}

/**************************************************************************//**
  \brief MAC_IsOwnExtAddrReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeMAC_IsOwnExtAddrReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief MAC_IsOwnExtAddrConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_IsOwnExtAddrConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief MAC_GetExtAddrReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeMAC_GetExtAddrReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief MAC_GetExtAddrConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_GetExtAddrConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief RF_RandomReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeRF_RandomReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief RF_RandomConf confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeRF_RandomConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief MAC_SetReq primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeMAC_SetReqReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief MAC_SetReq frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_SetReq request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_SetReqLength(void)
{
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(MACPHY_PibId_t) + /* MACPHY_PibId_t */
         sizeof(MACPHY_PibAttr_t); /* MACPHY_PibAttr_t */
}
/**************************************************************************//**
  \brief MAC_SetReq confirm primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_SetReqConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
  /**************************************************************************//**
  \brief MAC_SetReq.Confirm callback wrapper routine.

  \param[in] req - request parameters.

  \return None.
 ******************************************************************************/
void zsiMAC_SetReqConfCallback(void *const req);
#elif defined(ZAPPSI_NP)

/**************************************************************************//**
  \brief MAC_IsOwnExtAddrConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_IsOwnExtAddrConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_IsOwnExtAddrConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(bool);
}

/**************************************************************************//**
  \brief MAC_GetExtAddrConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_GetExtAddrConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}

/**************************************************************************//**
  \brief RF_RandomConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiRF_RandomConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint16_t);
}

/**************************************************************************//**
  \brief MAC_IsOwnExtAddrReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_IsOwnExtAddrReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief MAC_GetExtAddrReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_GetExtAddrReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief RF_RandomReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeRF_RandomReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief RF_RandomConf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeRF_RandomConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
\brief Confirm for RF_RandomReq.

\param conf - pointer to confirm with result.
******************************************************************************/
void zsiRfRandomConf(RF_RandomConf_t *conf);
/**************************************************************************//**
  \brief MAC_SetReq request primitive deserialization and
         processing routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
*******************************************************************************/
ZsiProcessingResult_t zsiDeserializeMAC_SetReqReq(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief MAC_SetReq conf primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeMAC_SetReqConf(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief MAC_SetReq Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return MAC_GetExtAddrConf request frame size.
 ******************************************************************************/
INLINE uint16_t zsiMAC_SetReqConfLength(const void *const req)
{
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(uint8_t) + sizeof(uint8_t); // attrId, status
}
#endif /* ZAPPSI_NP */


#ifdef ZAPPSI_HOST
#define zsiDeserializeMAC_IsOwnExtAddrReq            NULL
#define zsiDeserializeMAC_GetExtAddrReq              NULL
#define zsiDeserializeRF_RandomReq                   NULL
#define zsiDeserializeMAC_SetReqReq                  NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeMAC_IsOwnExtAddrConf           NULL
#define zsiDeserializeMAC_GetExtAddrConf             NULL
#define zsiDeserializeRF_RandomConf                  NULL
#define zsiDeserializeMAC_SetReqConf                 NULL
#endif /* ZAPPSI_NP */

#endif /* ZSIMACSERIALIZATION_H */
