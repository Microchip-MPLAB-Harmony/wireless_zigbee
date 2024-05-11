/**************************************************************************//**
  \file  usartAdapter.c

  \brief Implement layer between HAL and Serial Manager. It is intended to
  define logic specific to uart interface. This file implement buffered io via
  uart.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

******************************************************************************/
#ifndef BOARD_PC


#if (APP_INTERFACE == APP_INTERFACE_USART) || (APP_INTERFACE == APP_INTERFACE_VCP) || (APP_INTERFACE == APP_INTERFACE_UART) || (APP_INTERFACE == APP_INTERFACE_USBFIFO)

/******************************************************************************
                  Includes section
******************************************************************************/
#ifdef _PIC32CX_
#include <zigbee/ZAppSi/z3commonfiles/include/console.h>
#else
#include <rs232Controller.h>
#endif
#include <systemenvironment/include/sysQueue.h>
#include <consts.h>
#include <bufferallocator.h>
#include <systemenvironment/include/dbg.h>
#include <hal/include/appTimer.h>
#include <systemenvironment/include/sysUtils.h>
#include <ZAppSiSerialManager.h>


/******************************************************************************
                   Defines section
******************************************************************************/
#if APP_INTERFACE == APP_INTERFACE_USART
#if defined(_PIC32CX_)
  #define CLOSE_USART(...) (void)0
  #define OPEN_USART(...)  (void)0
#else
  #define OPEN_USART           HAL_OpenUsart
  #define CLOSE_USART          HAL_CloseUsart
  #define WRITE_USART          HAL_WriteUsart
  #define READ_USART           HAL_ReadUsart
  #define USART_CHANNEL        APP_USART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 160
  #define R_USART_CHANNEL      APP_USART_CHANNEL
#endif 
#endif // APP_INTERFACE_USART

#if APP_INTERFACE == APP_INTERFACE_VCP
  #define OPEN_USART            VCP_OpenUsart
  #define CLOSE_USART           VCP_CloseUsart
  #define WRITE_USART           VCP_WriteUsart
  #define READ_USART            VCP_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_VCP
  #define USART_RX_BUFFER_LENGTH 64
  #define R_USART_CHANNEL       USART_CHANNEL_VCP
#endif // APP_INTERFACE_VCP

#if APP_INTERFACE == APP_INTERFACE_UART
  #define OPEN_USART           HAL_OpenUart
  #define CLOSE_USART          HAL_CloseUart
  #define WRITE_USART          HAL_WriteUart
  #define READ_USART           HAL_ReadUart
  #define USART_CHANNEL        APP_UART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 160
  #define R_USART_CHANNEL      APP_UART_CHANNEL
#endif

#if APP_INTERFACE == APP_INTERFACE_USBFIFO
  #define OPEN_USART            USBFIFO_OpenUsart
  #define CLOSE_USART           USBFIFO_CloseUsart
  #define WRITE_USART           USBFIFO_WriteUsart
  #define READ_USART            USBFIFO_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_USBFIFO
  #define USART_RX_BUFFER_LENGTH 160
  #define R_USART_CHANNEL       USART_CHANNEL_USBFIFO
#endif // APP_INTERFACE_USBFIFO

#ifndef OPEN_USART
  #error 'USART interface is not defined.'
#endif // OPEN_USART

//USART baudrate
#ifndef R_USART_BAUDRATE
  #define R_USART_BAUDRATE                    USART_BAUDRATE_38400
#endif

//USART stop bits amount
#ifndef R_USART_STOPBITS
  #define R_USART_STOPBITS                    USART_STOPBIT_1
#endif

//USART parity mode
#ifndef R_USART_PARITY_MODE
  #define R_USART_PARITY_MODE                 USART_PARITY_NONE
#endif

//USART flow control mode
#ifndef R_USART_FLOW_CONTROL
  #define R_USART_FLOW_CONTROL                (USART_FLOW_CONTROL_NONE)
#endif

// Size of length field in frame
#define LEN_SIZE (sizeof(((ZS_CommandFrame_t*)NULL)->length))
// Start of frame market
#define SOF 0x2A
// 500 ms interbyte timeout should be enough for everyone
#define INTERBYTE_TIMEOUT 500

/******************************************************************************
                   Types section
******************************************************************************/
// States of tx FSM
typedef enum _TxState_t
{
  TX_ERR_OR_OFF,
  TX_IDLE,
  TX_SENDING_SOF,
  TX_SENDING_DATA,
} TxState_t;

// States of rx FSM
typedef enum _RxState_t
{
  RX_ERR_OR_OFF,
  RX_WAITING_START,   // AKA IDLE
  RX_WAITING_MSB_LEN,
  RX_WAITING_LSB_LEN,
  RX_WAITING_DATA,
} RxState_t;

/******************************************************************************
                   Static Function Prototypes section
******************************************************************************/
static void rInitUsart(void);
static void rStopUsart(void);
static SerialStatus_t rSendCommandFrame(ZS_CommandBuffer_t *cmd);

#ifdef _USE_RTOS_
void APP_UartEvtRunnerWriteUpload(uint8_t* cmdBuf);
#endif
/******************************************************************************
                  Static variables section
******************************************************************************/

static RxState_t rxState = RX_ERR_OR_OFF;
static TxState_t txState = TX_ERR_OR_OFF;
static ZS_CommandBuffer_t *currRxBuf;
static ZS_CommandBuffer_t *currTxBuf;
#ifndef _PIC32CX_
static HAL_UsartDescriptor_t rUsartDescriptor;
static uint8_t rUsartDescriptorRxBuffer[USART_RX_BUFFER_LENGTH];
static HAL_AppTimer_t interbyteTimer;
#else
extern void APP_UartWriteBuffer(void* buffer, uint8_t length);
extern void APP_UartWriteBufferSend(void* buffer, uint8_t length);
#endif
static DECLARE_QUEUE(rUsartRxQueue);
static DECLARE_QUEUE(rUsartTxQueue);

/*****************************************************************************
                             Global variables section
******************************************************************************/
SerialManager_t serialManager;

/******************************************************************************
                  Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Init USART module
******************************************************************************/
static void rInitUsart(void)
{
#ifdef _PIC32CX_
  currRxBuf = NULL;
  currTxBuf = NULL;
  rxState = RX_WAITING_START;
  txState = TX_IDLE;
  resetQueue(&rUsartRxQueue);
  resetQueue(&rUsartTxQueue);
#else
#ifdef BSP_ENABLE_RS232_CONTROL
 BSP_EnableRs232();
#endif /* BSP_ENABLE_RS232_CONTROL */
  currRxBuf = NULL;
  currTxBuf = NULL;

  rUsartDescriptor.tty            = R_USART_CHANNEL;
  rUsartDescriptor.mode           = USART_MODE_ASYNC;
  rUsartDescriptor.flowControl    = R_USART_FLOW_CONTROL;
  rUsartDescriptor.baudrate       = R_USART_BAUDRATE;
  rUsartDescriptor.dataLength     = USART_DATA8;
  rUsartDescriptor.parity         = R_USART_PARITY_MODE;
  rUsartDescriptor.stopbits       = R_USART_STOPBITS;
  rUsartDescriptor.rxBuffer       = rUsartDescriptorRxBuffer;
  rUsartDescriptor.rxBufferLength  = USART_RX_BUFFER_LENGTH; //BULK_SIZE
  rUsartDescriptor.txBuffer       = NULL;
  rUsartDescriptor.txBufferLength = 0;
  rUsartDescriptor.rxCallback     = rUsartReceivedHandler;
  rUsartDescriptor.txCallback     = rUsartTransmittedHandler;

  if (-1 != OPEN_USART(&rUsartDescriptor))
  {
    rxState = RX_WAITING_START;
    txState = TX_IDLE;
  }
  else
  {
    rxState = RX_ERR_OR_OFF;
    txState = TX_ERR_OR_OFF;
  }

  resetQueue(&rUsartRxQueue);
  resetQueue(&rUsartTxQueue);
  interbyteTimer.callback = interbyteTimeoutExpired;
  interbyteTimer.interval = INTERBYTE_TIMEOUT;
  interbyteTimer.mode = TIMER_ONE_SHOT_MODE;
#endif
}

/**************************************************************************//**
\brief Terminate serial transfers
******************************************************************************/
static void rStopUsart(void)
{
#ifndef _PIC32CX_
   rxState = RX_ERR_OR_OFF;
   txState = TX_ERR_OR_OFF;
   CLOSE_USART(&rUsartDescriptor);
#endif
}



#ifdef _PIC32CX_
/**************************************************************************//**
\brief Callback on reception of serial byte(s)

\param[in] bytesAmount number of received bytes
******************************************************************************/
void consoleRx(uint8_t data)
{
   static uint16_t rxCnt = 0;
   static uint8_t offset = 0;


   switch (rxState)
   {
     case RX_WAITING_START:
       {
         if (SOF == data)
         {
           rxState = RX_WAITING_LSB_LEN;
           offset++;
         }
       }
       break;

     case RX_WAITING_LSB_LEN:
     case RX_WAITING_MSB_LEN:
       {
         // Allocate new data buffer if required
         if (!currRxBuf)
           currRxBuf = bufferAllocator.allocate();

         if (RX_WAITING_LSB_LEN == rxState)
         {
           currRxBuf->commandFrame.length = data;
           rxState = RX_WAITING_MSB_LEN;
         }
         else
         {
           currRxBuf->commandFrame.length |= (uint16_t)data << 8;
           // Limit length to avoid possible buffer overflow
           currRxBuf->commandFrame.length = MIN(currRxBuf->commandFrame.length,
             sizeof(ZS_CommandFrame_t) - LEN_SIZE);

           if (currRxBuf->commandFrame.length > 0)
             rxState = RX_WAITING_DATA;
           else
             rxState = RX_WAITING_START; // Do not allow zero len
         }
         rxCnt = 0;
       }
       break;

     case RX_WAITING_DATA:
       {
         uint8_t *readPtr = (uint8_t *)&currRxBuf->commandFrame;

         readPtr += offsetof(ZS_CommandFrame_t, commandId) + rxCnt;
         
         *readPtr = data;

         rxCnt++;
         if (rxCnt >= currRxBuf->commandFrame.length)
         {
           // Full packet is received
           rxState = RX_WAITING_START;
           serialManager.service.notify(currRxBuf);
           currRxBuf = NULL;
         }
       }
       break;

     case RX_ERR_OR_OFF:
     default:
       return;
   } 
}
#endif

static SerialStatus_t rSendCommandFrame(ZS_CommandBuffer_t *cmd)
{
 static uint8_t sof = SOF;
 if (!cmd)
   return SERIAL_FAILED;

 if (!currTxBuf && (TX_IDLE == txState))
 {
    uint8_t *writePtr = NULL;
    // Send right now
    currTxBuf = cmd;
    writePtr = (uint8_t *)&currTxBuf->commandFrame;
    //txState = TX_SENDING_SOF;
    writePtr += offsetof(ZS_CommandFrame_t, length);
    APP_UartWriteBuffer(&sof, 1);
    APP_UartWriteBufferSend(writePtr, currTxBuf->commandFrame.length + LEN_SIZE);
    txState = TX_IDLE;

    bufferAllocator.free(currTxBuf);
    currTxBuf->state = R_BUFFER_FREE_STATE;
    currTxBuf = NULL;
 }
 else
 {
   // Defer frame
   if(!putQueueElem(&rUsartTxQueue, cmd))
   {
     /* failed to queue */
   }
 }
//How should the rUsartQueue be handled?
 return SERIAL_SUCCESS;
}

/**************************************************************************//**
\brief Open serial interface

\param[in] interfaceID - ID of serial channel
\param[in] notify - callback on receive of new command frame
******************************************************************************/
void openSerialManager(uint8_t interfaceID, void (*notify) (ZS_CommandBuffer_t *frame))
{
  // Implementation depends on 'length' field in ZS_CommandFrame_t being one byte
  // In case of change, several modifications would be required
  assert_static(2 == LEN_SIZE);

  switch (interfaceID)
  {
    case INTERFACE_ID_USART0:
      rInitUsart();
      serialManager.write = rSendCommandFrame;
      serialManager.service.notify = notify;
      serialManager.close = rStopUsart;
      break;
    default:
      break;
  }
}

/**************************************************************************//**
\brief Subtask for "Data is ready", should be called from task handler also.
******************************************************************************/
void rDataSlaveInd(void)
{}

#endif // (APP_INTERFACE == APP_INTERFACE_USART) || (APP_INTERFACE == APP_INTERFACE_VCP)

#endif // BOARD_PC

// eof usartAdapter.c
