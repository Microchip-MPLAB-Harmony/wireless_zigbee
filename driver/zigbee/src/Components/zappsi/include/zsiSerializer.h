/*******************************************************************************
  ZAppSI Serializer Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiSerializer.h

  Summary:
    This file contains the ZAppSI serializer module interface.

  Description:
    This file contains the ZAppSI serializer module interface.
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


#ifndef _ZSISERIALIZER_H_
#define _ZSISERIALIZER_H_

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct _ZsiSerializer_t
{
  uint8_t *pow;
  const uint8_t *por;
} ZsiSerializer_t;

/******************************************************************************
                    Defines section
******************************************************************************/
#define zsiSerializeBitfield zsiSerializeUint8
#define zsiDeserializeBitfield zsiDeserializeUint8

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  \brief uint8 value serialization routine.

  \param[in] serializer - serializer context.
  \param[in] value - value to serialize.

  \return None.
 ******************************************************************************/
void zsiSerializeUint8(ZsiSerializer_t *const serializer, uint8_t value);

/******************************************************************************
  \brief uint16 value serialization routine.

  \param[in] serializer - serializer context.
  \param[in] value - value to serialize.

  \return None.
 ******************************************************************************/
void zsiSerializeUint16(ZsiSerializer_t *const serializer, uint16_t value);

/******************************************************************************
  \brief uint32 value serialization routine.

  \param[in] serializer - serializer context.
  \param[in] value - value to serialize.

  \return None.
 ******************************************************************************/
void zsiSerializeUint32(ZsiSerializer_t *const serializer,
  const uint32_t *const value);

/******************************************************************************
  \brief uint64 value serialization routine.

  \param[in] serializer - serializer context.
  \param[in] value - value to serialize.

  \return None.
 ******************************************************************************/
void zsiSerializeUint64(ZsiSerializer_t *const serializer,
  const uint64_t *const value);

/******************************************************************************
  \brief Data block serialization routine.

  \param[in] serializer - serializer context.
  \param[in] data - pointer to data block.
  \param[out] size - data block size.

  \return None.
 ******************************************************************************/
void zsiSerializeData(ZsiSerializer_t *const serializer, const void *const data,
  uint16_t size);

/******************************************************************************
  \brief uint8 value deserialization routine.

  \param[in] serializer - serializer context.
  \param[out] pow - pointer to region were deserialized data should be stored.

  \return None.
 ******************************************************************************/
void zsiDeserializeUint8(ZsiSerializer_t *const serializer, uint8_t *const pow);

/******************************************************************************
  \brief uint16 value deserialization routine.

  \param[in] serializer - serializer context.
  \param[out] pow - pointer to region were deserialized data should be stored.

  \return None.
 ******************************************************************************/
void zsiDeserializeUint16(ZsiSerializer_t *const serializer, uint16_t *const pow);

/******************************************************************************
  \brief uint32 value deserialization routine.

  \param[in] serializer - serializer context.
  \param[out] pow - pointer to region were deserialized data should be stored.

  \return None.
 ******************************************************************************/
void zsiDeserializeUint32(ZsiSerializer_t *const serializer, uint32_t *const pow);

/******************************************************************************
  \brief uint64 value deserialization routine.

  \param[in] serializer - serializer context.
  \param[out] pow - pointer to region were deserialized data should be stored.

  \return None.
 ******************************************************************************/
void zsiDeserializeUint64(ZsiSerializer_t *const serializer, uint64_t *const pow);

/******************************************************************************
  \brief Data block deserialization routine.

  \param[in] serializer - serializer context.
  \param[out] pow - pointer to region were deserialized data should be stored.
  \param[out] size - data block size.

  \return None.
 ******************************************************************************/
void zsiDeserializeData(ZsiSerializer_t *const serializer, void *const pow,
  uint16_t size);

/******************************************************************************
  \brief Returns a pointer to data block in serialized payload.

  \param[in] serializer - serializer context.
  \param[out] pow - region were pointer should be stored.
  \param[out] size - data block size.

  \return None.
 ******************************************************************************/
void zsiDeserializeToPointer(ZsiSerializer_t *const serializer, uint8_t **const pow,
  uint16_t size);

#endif /* _ZSISERIALIZER_H_ */
