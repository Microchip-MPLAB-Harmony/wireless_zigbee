/*****************************************************************************
  \file composer.h

  \brief Composer API file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    24/12/09 A. Kostyukov - Created
*****************************************************************************/

#ifndef COMPOSER_H_
#define COMPOSER_H_
/***************************************************************************//**
\brief Forms and sends frame which not required additional actions for payload.

It is used to prevent code duplication.

\param[in] cmdId - command id
\param[in] buf - pointer to payload
\param[in] size - payload size
\param[in] confId - supposed confirmation identifier
\param[in] conf - pointer to confirmation handler

\return nothing
******************************************************************************/
void generateSimpleFrame(uint16_t cmdId, void* buf, uint8_t size,
                            uint8_t confId, void* conf);
#endif /* COMPOSER_H_ */
