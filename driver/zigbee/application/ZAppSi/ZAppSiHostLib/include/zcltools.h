/***************************************************************************//**
 \file zcltools.h
 \brief The header file describes TBD.
 \author Atmel Corporation: http://www.atmel.com

 \nSupport email: avr@atmel.com Copyright (c) 2008 , Atmel Corporation.
 \nAll rights reserved. Licensed under Atmel's Limited License Agreement (BitCloudTM).

 \internal History: 30.09.2009 akostyukov - Created
******************************************************************************/
#ifndef ZSETOOLS_H_
#define ZSETOOLS_H_
/*****************************************************************************
 Includes section
******************************************************************************/
#include <zcl.h>
/*****************************************************************************
Prototypes section
******************************************************************************/
/*******************************************************************************
 \brief Function counts the size of ZCL types
 \param[in] typeId - type identificator.
 \return the size of type in bytes
 ******************************************************************************/
uint8_t zsSizeofAttributeType(uint8_t typeId);

#endif /* ZSETOOLS_H_ */
//eof zsetools.h
