/*******************************************************************************
  \file serialInterface.h

  \brief Serial Manager definition file. It is not intended for include to
  serialManager.c only.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*******************************************************************************/
#ifndef _ZAPPSISERIALMANAGER_H
#define _ZAPPSISERIALMANAGER_H
/*******************************************************************************
                   Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <hal/cortexm4/pic32cx/include/halAssert.h>
#include <hal/include/appTimer.h>

/*******************************************************************************
                   Defines section
 ******************************************************************************/
#ifndef APP_MAX_COMMAND_PAYLOAD_SIZE
  #define APP_MAX_COMMAND_PAYLOAD_SIZE 100
#endif

/*******************************************************************************
                   Types section
*******************************************************************************/
typedef enum
{
  R_USART_RX_BUFFER_TYPE_ID,
  R_USART_TX_BUFFER_TYPE_ID
} RUsartBufferTypeId_t;

//ZS_CommandBuffer_t state field values
typedef enum
{
  R_BUFFER_FREE_STATE,
  R_BUFFER_BUSY_STATE
} ZS_CommandBufferState_t;

BEGIN_PACK
typedef struct PACK _ZS_CommandFrame_t
{
  uint16_t length;
  uint16_t commandId;
  uint8_t payload[APP_MAX_COMMAND_PAYLOAD_SIZE];
} ZS_CommandFrame_t;

typedef struct PACK
{
  uint16_t length;
  uint16_t commandId;
  uint16_t assertCode;
} ZS_AssertCommandFrame_t;

typedef enum
{
  SERIAL_SUCCESS,
  SERIAL_FAILED
} SerialStatus_t;

END_PACK

typedef struct _ZS_CommandBuffer_t
{
  struct
  {
    void *next;
  } service;
  uint8_t state;
  ZS_CommandFrame_t commandFrame;
} ZS_CommandBuffer_t;


typedef struct _SerialManager_t
{
  /*
   * service struct is intended for internal use
   */
  struct
  {
    void (*notify) (ZS_CommandBuffer_t* buf);
  } service;
  /*
   * write function sends frame to serial interface
   * Parameters:
   *  frame - frame to be sent
   */
  SerialStatus_t (*write) (ZS_CommandBuffer_t* buf);
  /*
   * close serial manager
   * Parameters:
   *  none
   */
  void (*close) (void);
} SerialManager_t;


typedef struct
{
  struct
  {
    void *next;
  } service;
  uint8_t state;
  ZS_AssertCommandFrame_t commandFrame;
} ZS_AssertCommandBuffer_t;

typedef enum
{
  INTERFACE_ID_USART0,
  INTERFACE_ID_USART1,
  INTERFACE_ID_SPI
} InterfaceID_t;

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
extern SerialManager_t serialManager;

/*
 * openSerialManager - initialized serial manager.
 * Parameters:
 *   interfaceID - serial connection type identificator
 *   notify - handler for incoming frames
 *
 */
void openSerialManager(uint8_t interfaceID,
  void (*notify) (ZS_CommandBuffer_t *frame));

/**************************************************************************//**
\brief Sequences next demo command
******************************************************************************/
void advanceDemo(void);

#ifdef BOARD_PC
/**************************************************************************//**
\brief Start timer function on PC
******************************************************************************/
int HAL_StartAppTimer(HAL_AppTimer_t *appTimer);

/**************************************************************************//**
\brief Stop timer function on PC
******************************************************************************/
int HAL_StopAppTimer(HAL_AppTimer_t *appTimer);
#endif // BOARD_PC

#endif // _SERIALINTERFACE_H

// eof serialInterface.h
