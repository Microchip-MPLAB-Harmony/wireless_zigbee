/***************************************************************************//**
 \file zcltools.c
 \brief The header file describes TBD.
 \author Atmel Corporation: http://www.atmel.com

 \nSupport email: avr@atmel.com Copyright (c) 2008 , Atmel Corporation.
 \nAll rights reserved. Licensed under Atmel's Limited License Agreement (BitCloudTM).

 \internal History: 30.09.2009 akostyukov - Created
******************************************************************************/

/*****************************************************************************
 Includes section
******************************************************************************/
#include <zcltools.h>

/******************************************************************************
Implementations section
******************************************************************************/
/*******************************************************************************
 \brief Function counts the size of ZCL types
 \param[in] typeId - type identificator.
 \return the size of type in bytes
 ******************************************************************************/
uint8_t zsSizeofAttributeType(uint8_t typeId)
{
  uint8_t length = 0;

  switch (typeId)
  {
      //General data
    case ZCL_S8BIT_DATA_TYPE_ID:
    case ZCL_U8BIT_DATA_TYPE_ID:
    case ZCL_8BIT_DATA_TYPE_ID:
    case ZCL_BOOLEAN_DATA_TYPE_ID:
    case ZCL_8BIT_BITMAP_DATA_TYPE_ID:
    case ZCL_8BIT_ENUM_DATA_TYPE_ID:
      length = 1;
      break;

    case ZCL_U16BIT_DATA_TYPE_ID:
    case ZCL_S16BIT_DATA_TYPE_ID:
    case ZCL_16BIT_DATA_TYPE_ID:
    case ZCL_16BIT_BITMAP_DATA_TYPE_ID:
    case ZCL_16BIT_ENUM_DATA_TYPE_ID:
    case ZCL_CLUSTER_ID_DATA_TYPE_ID:
    case ZCL_ATTRIBUTE_ID_DATA_TYPE_ID:
      length = 2;
      break;

    case ZCL_U24BIT_DATA_TYPE_ID:
    case ZCL_S24BIT_DATA_TYPE_ID:
    case ZCL_24BIT_DATA_TYPE_ID:
    case ZCL_24BIT_BITMAP_DATA_TYPE_ID:
      length = 3;
      break;

    case ZCL_U32BIT_DATA_TYPE_ID:
    case ZCL_S32BIT_DATA_TYPE_ID:
    case ZCL_UTC_TIME_DATA_TYPE_ID:
    case ZCL_32BIT_DATA_TYPE_ID:
    case ZCL_32BIT_BITMAP_DATA_TYPE_ID:
      length = 4;
      break;

    case ZCL_U40BIT_DATA_TYPE_ID:
    case ZCL_S40BIT_DATA_TYPE_ID:
    case ZCL_40BIT_DATA_TYPE_ID:
    case ZCL_40BIT_BITMAP_DATA_TYPE_ID:
      length = 5;
      break;

    case ZCL_U48BIT_DATA_TYPE_ID:
    case ZCL_S48BIT_DATA_TYPE_ID:
    case ZCL_48BIT_DATA_TYPE_ID:
    case ZCL_48BIT_BITMAP_DATA_TYPE_ID:
      length = 6;
      break;

    case ZCL_U56BIT_DATA_TYPE_ID:
    case ZCL_S56BIT_DATA_TYPE_ID:
    case ZCL_56BIT_DATA_TYPE_ID:
    case ZCL_56BIT_BITMAP_DATA_TYPE_ID:
      length = 7;
      break;

    case ZCL_U64BIT_DATA_TYPE_ID:
    case ZCL_S64BIT_DATA_TYPE_ID:
    case ZCL_64BIT_DATA_TYPE_ID:
    case ZCL_64BIT_BITMAP_DATA_TYPE_ID:
    case ZCL_IEEE_ADDRESS_DATA_TYPE_ID:
      length = 8;
      break;

    case ZCL_128BIT_SECURITY_KEY_DATA_TYPE_ID:
      length = 16;
      break;

    default:
      break;
  }

  return length;
}
//eof zcltools.c


