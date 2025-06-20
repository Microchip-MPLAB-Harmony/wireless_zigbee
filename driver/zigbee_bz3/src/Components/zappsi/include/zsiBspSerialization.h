/*******************************************************************************
  ZAppSI BSP Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiBspSerialization.h

  Summary:
    This file contains the ZAppSI BSP APIs serialization interface.

  Description:
    This file contains the ZAppSI BSP APIs serialization interface.
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

#ifndef ZSIBSPSERIALIZATION_H
#define ZSIBSPSERIALIZATION_H
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zsiFrames.h>
#include <zsiDriver.h>
#include <macAddr.h>

/**************************************************************************//**
  \brief Finds routine for BSP commands deserialization.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiBspFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief BSP read UID frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return BSP-ReadUID frame size.
 ******************************************************************************/
INLINE uint16_t zsiBSP_ReadUidReqLength()
{
  return ZSI_COMMAND_FRAME_OVERHEAD ;
}

/**************************************************************************//**
  \brief BSP_ReadUid confirm deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBSP_ReadUidConf(void *memory,
  ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief BSP read uid request serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeBSP_ReadUidReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);
#elif defined(ZAPPSI_NP)
/**************************************************************************//**
  \brief BSP_ReadUid Request deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeBSP_ReadUidReq(void *memory, ZsiCommandFrame_t *const cmdFrame);
/**************************************************************************//**
  \brief BSP_ReadUidConf frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return BSP_ReadUidConf confirm frame size.
 ******************************************************************************/
INLINE uint16_t zsiBSP_ReadUidConf(const void *const req)
{
  (void)req;
  return ZSI_COMMAND_FRAME_OVERHEAD + sizeof(ExtAddr_t);
}
#endif //ZAPPSI_HOST

#ifdef ZAPPSI_HOST
#define zsiDeserializeBSP_ReadUidReq                  NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeBSP_ReadUidConf                 NULL
#endif /*ZAPPSI_HOST*/

#endif//ZSIBSPSERIALIZATION_H