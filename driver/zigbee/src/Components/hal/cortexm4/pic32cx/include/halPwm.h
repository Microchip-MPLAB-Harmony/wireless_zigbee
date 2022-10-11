/**************************************************************************//**
  \file  halPwm.h

  \brief Declaration of hardware depended PWM interface.

  \author
      Microchip Corporation: http://ww.microchip.com \n
      Support email: support@microchip.com

    Copyright (c) 2008-2012, Microchip Corporation. All rights reserved.
    Licensed under Microchip's Limited License Agreement.

  \internal
    History:
     27/01/14 Agasthian S - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALPWM_H
#define _HALPWM_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <gpio.h>
#include <pwm.h>
#include <halDiagnostic.h>

/******************************************************************************
                   Definitions section
******************************************************************************/
/* PWN unit base channel pins position. PWM module dependent. */
#define PWM_UNIT_1_BASE_CHANNEL_PIN PORTA_OUT_P18
#define PWM_UNIT_3_BASE_CHANNEL_PIN PORTA_OUT_P16

/* Compare Output Mode base bit number. PWM module independent. */
#define POLARITY_BASE_BIT TCC_WAVE_POL0
/* Compare Output Mode bitfield size. PWM module and channel independent. */
#define POLARITY_BITFIELD_POS TCC_WAVE_POL0_Pos

#define CAPTEN_BITPOS            TCC_CTRLA_CPTEN0_Pos

#define RESOULTION_BITPOS        TCC_CTRLA_RESOLUTION_Pos


#define SYNBUSY_CHANNEL_BITPOS   TCC_SYNCBUSY_CC0_Pos

/* Compare Output Mode low bit number. PWM module independent. */
#define PolarityPosition(descriptor) ((descriptor)->service.COMnx0)
/* Output Compare Register. PWM module and channel dependent. */
#define OCRnx(descriptor) (*((descriptor)->service.OCRnx))
/* Data Direction Rregister. PWM module dependent. */
#define DDRn(descriptor) (*((descriptor)->service.DDRn))

#define CCx_COUNT_SIZE 4U

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes the PWM.

\param [in] pwmUnit - PWM unit number.
                      Equal to ID of Timer/Counter witch serves PWM module.
******************************************************************************/
void halOpenPwm(HAL_PwmUnit_t pwmUnit);

/**************************************************************************//**
\brief Starts PWM on specified channel.

\param [in] descriptor - PWM channel descriptor.
******************************************************************************/
void halStartPwm(HAL_PwmDescriptor_t *descriptor);

/**************************************************************************//**
\brief Stops PWM on specified channel.

\param [in] descriptor - PWM channel descriptor.
******************************************************************************/
void halStopPwm(HAL_PwmDescriptor_t *descriptor);

/**************************************************************************//**
\brief Sets base frequency of module. Common for all module channels.

\param [in] descriptor - PWM channel descriptor.
\param [in] top - value for the TOP register.
\param [in] prescaler - clock prescaler.
******************************************************************************/
void halSetPwmFrequency(HAL_PwmDescriptor_t *descriptor, uint16_t top, HAL_PwmPrescaler_t prescaler);

/**************************************************************************//**
\brief Sets compare value for the PWM channel.

\param [in] descriptor - PWM channel descriptor.
******************************************************************************/
void halSetPwmCompareValue(HAL_PwmDescriptor_t *descriptor, uint16_t cmpValue);

/**************************************************************************//**
\brief Closes the PWM.

\param [in] pwmUnit - PWM unit number.
                      Equal to ID of Timer/Counter witch serves PWM module.
******************************************************************************/
void halClosePwm(HAL_PwmUnit_t pwmUnit);

#endif /* _HALPWM_H */

// eof halPwm.h
