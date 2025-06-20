/*******************************************************************************
  ZAppSi HAL Serialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiHalSerialization.h

  Summary:
    This file contains the ZAppSI HAL primitives serialization interface.

  Description:
    This file contains the ZAppSI HAL primitives serialization interface.
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


#ifndef ZSIHALSERIALIZATION_H
#define ZSIHALSERIALIZATION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zsiFrames.h>
#include <zsiDriver.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Finds routine for HAL commands deserialization and processing.

  \param[in] commandId - command identifier.

  \return Pointer to appropriate routine.
 ******************************************************************************/
ZsiProcessingRoutine_t zsiHalFindProcessingRoutine(uint8_t commandId);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief HAL Reset request primitive serialization routine.

  \param[in] req - request parameters.
  \param[out] cmdFrame - frame, which keeps serialized data.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiSerializeHAL_ResetReq(const void *const req,
  ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief HAL-Reset confirm primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

  \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeHAL_ResetConf(void *memory, ZsiCommandFrame_t *const cmdFrame);

/**************************************************************************//**
  \brief HAL-Reset request frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return HAL-Reset request frame size.
 ******************************************************************************/
INLINE uint16_t zsiHAL_ResetReqLength()
{
  return ZSI_COMMAND_FRAME_OVERHEAD ;
}

/**************************************************************************//**
  \brief ZSI_ResetNP handler to send the serialized HAL reset req command 
   to reset the NP in case of Host - ZAPPSINP

  \return None.
 ******************************************************************************/
void ZSI_ResetNP(void);

#elif defined(ZAPPSI_NP)
/**************************************************************************//**
  \brief HAL-Reset Confirm frame size calculation routine.
         SOF and LENGTH fields are dismissed.

  \param[in] req - request parameters.

  \return HAL-Reset Confirm frame size.
 ******************************************************************************/
INLINE uint16_t
zsiHAL_ResetConfLength(const void *const confirm)
{
  (void)confirm;
  return ZSI_COMMAND_FRAME_OVERHEAD +
         sizeof(uint8_t);  /* status */
}

/**************************************************************************//**
  \brief HAL-Reset request primitive deserialization and processing
         routine.

  \param[out] memory - memory allocated for command processing.
  \param[in] cmdFrame - frame which keeps serialized command.

    \return Processing result.
 ******************************************************************************/
ZsiProcessingResult_t zsiDeserializeHAL_ResetReq(void *memory, ZsiCommandFrame_t *const cmdFrame);

#endif // ZAPPSI_NP


#ifdef ZAPPSI_HOST
#define zsiDeserializeHAL_ResetReq     NULL
#elif defined(ZAPPSI_NP)
#define zsiDeserializeHAL_ResetConf    NULL
#endif


#endif  //ZSIHALSERIALIZATION_H
