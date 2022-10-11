/**************************************************************************//**
  \file  spiAdapter.c

  \brief Implement layer between HAL and Serial Manager. It is intended to
  define logic specific to spi interface. This file implement buffered io via
  spi.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
     26.10.10 - A. Khromykh - Created
******************************************************************************/
#ifndef BOARD_PC

#if (APP_INTERFACE == APP_INTERFACE_SPI)

#if (APP_SPI_MASTER_MODE == 1) && (defined(AT91SAM7X256) || defined(ATXMEGA256A3))
  #define VALID_MASTER_SPI
#endif

#if (APP_SPI_MASTER_MODE == 0) && defined(ATMEGA128RFA1)
  #define VALID_SLAVE_SPI
#endif

#if !defined(VALID_MASTER_SPI) && !defined(VALID_SLAVE_SPI)
  #error 'SPI adapter is not supported for the platform.'
#endif

//#define __DBG_SPI_ADAPTER__
/*****************************************************************************
      sam7x(master) ---------- xmega256a3(master)  ----------  megaRf(slave)
MISO      PA24                        PD6                           PB3
MOSI      PA23                        PD5                           PB2
SCK       PA22                        PD7                           PB1
CS        PA21                        PD4                           PB0
IRQ       PA29                        PD0                           PE5
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <spi.h>
#include <sysQueue.h>
#include <consts.h>
#include <bufferallocator.h>
#include <dbg.h>
#include <appTimer.h>
#include <sysUtils.h>
#if defined(VALID_MASTER_SPI)
  #include <irq.h>
  #if defined(__DBG_SPI_ADAPTER__)
    #include <usart.h>
  #endif // defined(__DBG_SPI_ADAPTER__)
#endif // defined(VALID_MASTER_SPI)

/******************************************************************************
                   Defines section
******************************************************************************/
// Size of length field in frame
#define LEN_SIZE (sizeof(((ZS_CommandFrame_t*)NULL)->length))
// Start of the writing
#define START_WRITE_MARKER 0x2A
// Start of the reading
#define START_READ_MARKER  0x2B

#if defined(VALID_SLAVE_SPI)
  // 1000 ms interbyte timeout should be enough for everyone
  #define INTERBYTE_TIMEOUT 1000
#endif

#if defined(VALID_MASTER_SPI)
  // spi parametres
  #define APP_SPI_MASTER_CLOCK_RATE         1000000ul
  #define APP_DELAY_BETWEEN_CS_AND_CLOCK    0.000001
  #define APP_DELAY_BETWEEN_CONS_TRANSFER   0.00016
  #define APP_SOFT_USDELAY_BETWEEN_BYTES    200
  #if defined(AT91SAM7X256)
    #define SLAVE_IRQ    IRQ_0
  #elif defined(ATXMEGA256A3)
    #define SLAVE_IRQ    IRQ_D0
  #endif
#endif

#if defined(__DBG_SPI_ADAPTER__)
  #define DBG_USART_BUFFER                  100
  #if defined(VALID_SLAVE_SPI)
    #define USART_CHANNEL    USART_CHANNEL_1
  #endif
  #if defined(VALID_MASTER_SPI)
    #if defined(AT91SAM7X256)
      #define USART_CHANNEL  USART_CHANNEL_0
    #elif defined(ATXMEGA256A3)
      #define USART_CHANNEL  USART_CHANNEL_F0
    #endif
  #endif
#endif // defined(__DBG_SPI_ADAPTER__)

/******************************************************************************
                   Types section
******************************************************************************/
// States of the spi
typedef enum _SpiState_t
{
  SPI_ERR_OR_OFF,
#if defined(VALID_SLAVE_SPI)
  WAITING_MARKER,
#endif
#if defined(VALID_MASTER_SPI)
  SPI_IDLE,
  WAITING_TX_MARKER,
  WAITING_RX_MARKER,
#endif
  WAITING_RX_LEN_LSB,
  WAITING_RX_LEN_MSB,
  WAITING_RX_DATA,
  WAITING_TX_LEN,
  WAITING_TX_DATA
} SpiState_t;

#if defined(VALID_MASTER_SPI)
typedef enum _SpiSlaveDataState_t
{
  SLAVE_THERE_IS_DATA,
  SLAVE_DATA_IS_READY,
  SLAVE_DATA_IS_EMPTY
} SpiSlaveDataState_t;

typedef enum _SpiMasterTypeTransaction_t
{
  MASTER_READ_TRANSACTION,
  MASTER_WRITE_TRANSACTION,
  MASTER_LAST_BYTE
} SpiMasterTypeTransaction_t;
#endif // defined(VALID_MASTER_SPI)

/******************************************************************************
                   Static Function Prototypes section
******************************************************************************/
static void rInitSpi(void);
static void rStopSpi(void);
static SerialStatus_t rSendCommandFrame(ZS_CommandBuffer_t *cmd);
static void rSpiCheckTxQueue(void);

#if defined(VALID_SLAVE_SPI)
static void rSpiReceivedHandler(uint16_t bytesAmount);
static void interbyteTimeoutExpired(void);
HAL_ASSIGN_PIN(IRQ_MASTER_LINE, E, 5);
#endif // defined(VALID_SLAVE_SPI)

#if defined(VALID_MASTER_SPI)
static void rSpiReceivedHandler(void);
static void rSlaveSpiDataInd(void);
static void rMasterSpiDelayer(void);
void rDataSlaveInd(void);
void HAL_Delay(uint8_t us);
#if defined(AT91SAM7X256)
HAL_ASSIGN_PIN(MASTER_CS, A, AT91C_PIO_PA21);
HAL_ASSIGN_PIN(EXT_IRQ,  A, AT91C_PIO_PA29);
#elif defined(ATXMEGA256A3)
HAL_ASSIGN_PIN(MASTER_CS, D, 4);
HAL_ASSIGN_PIN(EXT_IRQ,  D, 0);
#endif
#endif // defined(VALID_MASTER_SPI)

#if defined(__DBG_SPI_ADAPTER__)
static void openDbgUsart(void);
static void sendDbgData(uint8_t *buffer, uint16_t length);
#endif // defined(__DBG_SPI_ADAPTER__)

/******************************************************************************
                   Static variables section
******************************************************************************/
static HAL_SpiDescriptor_t rSpiDescriptor;
static SpiState_t spiState = SPI_ERR_OR_OFF;
static ZS_CommandBuffer_t *currRxBuf;
static ZS_CommandBuffer_t *currTxBuf;
static DECLARE_QUEUE(rSpiRxQueue);
static DECLARE_QUEUE(rSpiTxQueue);

#if defined(VALID_SLAVE_SPI)
  static HAL_AppTimer_t interbyteTimer =
  {
    .interval = INTERBYTE_TIMEOUT,
    .mode = TIMER_ONE_SHOT_MODE,
    .callback = interbyteTimeoutExpired,
  };
  static uint8_t rxCnt = 0;
#endif

#if defined(VALID_MASTER_SPI)
  static volatile SpiSlaveDataState_t slaveIndReady = SLAVE_DATA_IS_EMPTY;
  static SpiMasterTypeTransaction_t transacType;
  static uint16_t dataLength;
  static uint8_t *dataPointer;
  static bool masterTransactionInProgress = false;
#if defined(AT91SAM7X256)
  static const HAL_IrqMode_t thereIsData = IRQ_LOW_LEVEL;
  static const HAL_IrqMode_t dataReady   = IRQ_RISING_EDGE;
#elif defined(ATXMEGA256A3)
  static const HAL_IrqMode_t thereIsData = {.pin0 = IRQ_LOW_LEVEL,
                                            .pin1 = IRQ_IS_NOT_CHANGED,
                                            .pin2 = IRQ_IS_NOT_CHANGED,
                                            .pin3 = IRQ_IS_NOT_CHANGED,
                                            .pin4 = IRQ_IS_NOT_CHANGED,
                                            .pin5 = IRQ_IS_NOT_CHANGED,
                                            .pin6 = IRQ_IS_NOT_CHANGED,
                                            .pin7 = IRQ_IS_NOT_CHANGED};
  static const HAL_IrqMode_t dataReady   = {.pin0 = IRQ_RISING_EDGE,
                                            .pin1 = IRQ_IS_NOT_CHANGED,
                                            .pin2 = IRQ_IS_NOT_CHANGED,
                                            .pin3 = IRQ_IS_NOT_CHANGED,
                                            .pin4 = IRQ_IS_NOT_CHANGED,
                                            .pin5 = IRQ_IS_NOT_CHANGED,
                                            .pin6 = IRQ_IS_NOT_CHANGED,
                                            .pin7 = IRQ_IS_NOT_CHANGED};
#endif
#endif

#if defined(__DBG_SPI_ADAPTER__)
  static HAL_UsartDescriptor_t dbgUasrtDescriptor;
  static uint8_t usartTxBuffer[DBG_USART_BUFFER];
#endif

/*****************************************************************************
                              Global variables section
******************************************************************************/
SerialManager_t serialManager;

/******************************************************************************
                   Implementations section
******************************************************************************/
/********************* common part (begin) ***********************************/
/**************************************************************************//**
\brief Terminate serial transfers
******************************************************************************/
static void rStopSpi(void)
{
  spiState = SPI_ERR_OR_OFF;
  HAL_CloseSpi(&rSpiDescriptor);
}

/**************************************************************************//**
\brief Check spi tx queue, if queue is not empty then transmit is initiated
******************************************************************************/
static void rSpiCheckTxQueue(void)
{
  ZS_CommandBuffer_t *nextBuf;

  nextBuf = getQueueElem(&rSpiTxQueue);

  if (nextBuf)
  {
    deleteHeadQueueElem(&rSpiTxQueue);
    // txState would be modified inside callee
    rSendCommandFrame(nextBuf);
  }
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
  // Also depends on 'length' field being first field of command frame
  assert_static(0 == offsetof(ZS_CommandFrame_t, length));

  switch (interfaceID)
  {
    case INTERFACE_ID_SPI:
      rInitSpi();
      serialManager.write = rSendCommandFrame;
      serialManager.service.notify = notify;
      serialManager.close = rStopSpi;
      break;
    default:
      break;
  }
}

#if defined(__DBG_SPI_ADAPTER__)
/******************************************************************************
 Open usart interface for debugee data
******************************************************************************/
static void openDbgUsart(void)
{
  dbgUasrtDescriptor.tty             = USART_CHANNEL;
  dbgUasrtDescriptor.mode            = USART_MODE_ASYNC;
  dbgUasrtDescriptor.flowControl     = USART_FLOW_CONTROL_NONE;
  dbgUasrtDescriptor.baudrate        = USART_BAUDRATE_38400;
  dbgUasrtDescriptor.dataLength      = USART_DATA8;
  dbgUasrtDescriptor.parity          = USART_PARITY_NONE;
  dbgUasrtDescriptor.stopbits        = USART_STOPBIT_1;
  dbgUasrtDescriptor.rxBuffer        = NULL;
  dbgUasrtDescriptor.rxBufferLength  = 0;
  dbgUasrtDescriptor.txBuffer        = usartTxBuffer;
  dbgUasrtDescriptor.txBufferLength  = DBG_USART_BUFFER;
  dbgUasrtDescriptor.rxCallback      = NULL;
  dbgUasrtDescriptor.txCallback      = NULL;

  HAL_OpenUsart(&dbgUasrtDescriptor);
}

/******************************************************************************
 Send debugee data to usart

 param
   buffer - pointer to data
   length - data length
******************************************************************************/
static void sendDbgData(uint8_t *buffer, uint16_t length)
{
  HAL_WriteUsart(&dbgUasrtDescriptor, buffer, length);
}
#endif // defined(__DBG_SPI_ADAPTER__)
/********************* common part (end) *************************************/

/********************* spi slave part (begin) ********************************/
#if defined(VALID_SLAVE_SPI)
/**************************************************************************//**
\brief Init SPI module
******************************************************************************/
static void rInitSpi(void)
{
  currRxBuf = NULL;
  currTxBuf = NULL;

  rSpiDescriptor.tty            = APP_SPI_CHANNEL;
  rSpiDescriptor.clockMode      = SPI_CLOCK_MODE2;
  rSpiDescriptor.dataOrder      = SPI_DATA_MSB_FIRST;
  rSpiDescriptor.slave_callback = rSpiReceivedHandler;

  if (-1 != HAL_OpenSpi(&rSpiDescriptor))
    spiState = WAITING_MARKER;
  else
  {
    spiState = SPI_ERR_OR_OFF;
    return;
  }

  // set up master irq line
  GPIO_IRQ_MASTER_LINE_set();
  GPIO_IRQ_MASTER_LINE_make_out();
  (void)GPIO_IRQ_MASTER_LINE_read;
  (void)GPIO_IRQ_MASTER_LINE_state;
  (void)GPIO_IRQ_MASTER_LINE_make_pullup;
  (void)GPIO_IRQ_MASTER_LINE_make_in;
  (void)GPIO_IRQ_MASTER_LINE_toggle;

  resetQueue(&rSpiRxQueue);
  resetQueue(&rSpiTxQueue);

#if defined(__DBG_SPI_ADAPTER__)
  openDbgUsart();
#endif // defined(__DBG_SPI_ADAPTER__)
}

/**************************************************************************//**
\brief Reset rx FSM on expiration of interbyte timeout
******************************************************************************/
static void interbyteTimeoutExpired(void)
{
  if (spiState != SPI_ERR_OR_OFF)
  {
    spiState = WAITING_MARKER;
    rxCnt = 0;
  }
}

/**************************************************************************//**
\brief Callback on reception of serial byte(s)

\param[in] bytesAmount number of received bytes
******************************************************************************/
static void rSpiReceivedHandler(uint16_t bytesAmount)
{
  uint8_t data;

  while (bytesAmount)
  {
    switch (spiState)
    {
      case WAITING_MARKER:
        {
          if (HAL_ReadSpi(&rSpiDescriptor, &data, sizeof(uint8_t)) <= 0)
          {
            spiState = SPI_ERR_OR_OFF;
            return;
          }

#if defined(__DBG_SPI_ADAPTER__)
          sendDbgData(&data, sizeof(uint8_t));
#endif // defined(__DBG_SPI_ADAPTER__)

          if (START_WRITE_MARKER == data)
          {
            spiState = WAITING_RX_LEN_LSB;
          } else if (START_READ_MARKER == data)
          {
            spiState = WAITING_TX_LEN;
            rSpiCheckTxQueue();
          }
        }
        bytesAmount--;
        break;

      case WAITING_RX_LEN_LSB:
      case WAITING_RX_LEN_MSB:
        {
          if (HAL_ReadSpi(&rSpiDescriptor, &data, sizeof(uint8_t)) <= 0)
          {
            spiState = SPI_ERR_OR_OFF;
            return;
          }

#if defined(__DBG_SPI_ADAPTER__)
          sendDbgData(&data, sizeof(uint8_t));
#endif // defined(__DBG_SPI_ADAPTER__)

          bytesAmount--;

          // Allocate new data buffer if required
          if (!currRxBuf)
            currRxBuf = bufferAllocator.allocate();

          if (WAITING_RX_LEN_LSB == spiState)
          {
            currRxBuf->commandFrame.length = data;
            spiState = WAITING_RX_LEN_MSB;
          }
          else
          {
            currRxBuf->commandFrame.length |= ((uint16_t)data << 8U);
            // Limit length to avoid possible buffer overflow
            currRxBuf->commandFrame.length = MIN(currRxBuf->commandFrame.length,
              sizeof(ZS_CommandFrame_t) - LEN_SIZE);

            // Do not allow zero len
            if (0 < currRxBuf->commandFrame.length)
              spiState = WAITING_RX_DATA;
            else
              spiState = WAITING_MARKER;
          }
        }
        break;

      case WAITING_RX_DATA:
        {
          int readCnt = HAL_ReadSpi(&rSpiDescriptor,
            (uint8_t*)&currRxBuf->commandFrame.commandId + rxCnt,
            MIN(bytesAmount, (uint16_t) (currRxBuf->commandFrame.length - rxCnt)));

          if (readCnt <= 0)
          {
            spiState = SPI_ERR_OR_OFF;
            return;
          }

#if defined(__DBG_SPI_ADAPTER__)
          sendDbgData((uint8_t*)&currRxBuf->commandFrame.commandId + rxCnt, MIN(bytesAmount, (uint16_t) (currRxBuf->commandFrame.length - rxCnt)));
#endif // defined(__DBG_SPI_ADAPTER__)

          bytesAmount -= readCnt;
          rxCnt += readCnt;
          if (rxCnt >= currRxBuf->commandFrame.length)
          {
            rxCnt = 0;
            spiState = WAITING_MARKER;
            rSpiCheckTxQueue();
            // Full packet is received
            serialManager.service.notify(currRxBuf);
            currRxBuf = NULL;
          }
        }
        break;

      case WAITING_TX_DATA:
        {
          uint32_t dummyBuf;
          int readCnt = HAL_ReadSpi(&rSpiDescriptor, (uint8_t *)&dummyBuf, MIN(bytesAmount, sizeof(dummyBuf)));

          if (readCnt <= 0)
          {
            spiState = SPI_ERR_OR_OFF;
            return;
          }

          bytesAmount -= readCnt;
          rxCnt += readCnt;
          if (rxCnt >= (currTxBuf->commandFrame.length + LEN_SIZE))
          {
            rxCnt = 0;
            // Full packet was transmitted
            bufferAllocator.free(currTxBuf);
            currTxBuf->state = R_BUFFER_FREE_STATE;
            currTxBuf = NULL;
            spiState = WAITING_MARKER;
            rSpiCheckTxQueue();
          }
        }
        break;

      case SPI_ERR_OR_OFF:
      default:
        return;
    }
  }

  HAL_StopAppTimer(&interbyteTimer);

  if (WAITING_RX_DATA == spiState || WAITING_TX_DATA == spiState ||
      WAITING_RX_LEN_LSB == spiState || WAITING_RX_LEN_MSB == spiState)
    HAL_StartAppTimer(&interbyteTimer);
}

/**************************************************************************//**
\brief Initiate sending new command frame

\param[in] cmd - command buffer with frame to be send

\return result code
******************************************************************************/
static SerialStatus_t rSendCommandFrame(ZS_CommandBuffer_t *cmd)
{
  if (!cmd)
    return SERIAL_FAILED;

  if (WAITING_TX_LEN == spiState)
  {
    // Send right now
    currTxBuf = cmd;
    if (HAL_WriteSpi(&rSpiDescriptor, (uint8_t*)&currTxBuf->commandFrame.length, currTxBuf->commandFrame.length + LEN_SIZE) < 0)
      spiState = SPI_ERR_OR_OFF;
    else
    {
      spiState = WAITING_TX_DATA;

#if defined(__DBG_SPI_ADAPTER__)
      sendDbgData((uint8_t*)&currTxBuf->commandFrame.length, currTxBuf->commandFrame.length + LEN_SIZE);
#endif // defined(__DBG_SPI_ADAPTER__)
    }

    GPIO_IRQ_MASTER_LINE_set();
    if (SPI_ERR_OR_OFF == spiState)
      return SERIAL_FAILED;
  }
  else
  {
    // Defer frame
    if(!putQueueElem(&rSpiTxQueue, cmd))
    {
      /* failed to queue */
    }
    GPIO_IRQ_MASTER_LINE_clr();
  }
  return SERIAL_SUCCESS;
}
#endif //VALID_SLAVE_SPI
/********************* spi slave part (end) **********************************/

/********************* spi master part (begin) *******************************/
#if defined(VALID_MASTER_SPI)
/**************************************************************************//**
\brief Init SPI module
******************************************************************************/
static void rInitSpi(void)
{
  currRxBuf = NULL;
  currTxBuf = NULL;

  rSpiDescriptor.tty            = APP_SPI_CHANNEL;
  rSpiDescriptor.clockMode      = SPI_CLOCK_MODE2;
#if defined(AT91SAM7X256)
  rSpiDescriptor.symbolSize     = SPI_8BITS_SYMBOL;
  rSpiDescriptor.pack_parameter = HAL_SPI_PACK_PARAMETER(APP_SPI_MASTER_CLOCK_RATE,  \
                                                         APP_DELAY_BETWEEN_CS_AND_CLOCK, \
                                                         APP_DELAY_BETWEEN_CONS_TRANSFER);
#elif defined(ATXMEGA256A3)
  rSpiDescriptor.dataOrder      = SPI_DATA_MSB_FIRST;
  rSpiDescriptor.baudRate       = SPI_CLOCK_RATE_1000;
#endif
  rSpiDescriptor.callback       = rMasterSpiDelayer;

  if (-1 != HAL_OpenSpi(&rSpiDescriptor))
    spiState = SPI_IDLE;
  else
  {
    spiState = SPI_ERR_OR_OFF;
    return;
  }

  // set up master irq line
  GPIO_MASTER_CS_set();
  GPIO_MASTER_CS_make_out();
  GPIO_EXT_IRQ_make_in();
  GPIO_EXT_IRQ_make_pullup();
  // eliminate warnings about unused functions
  (void)GPIO_MASTER_CS_read;
  (void)GPIO_MASTER_CS_state;
  (void)GPIO_MASTER_CS_make_pullup;
  (void)GPIO_MASTER_CS_make_in;
  (void)GPIO_MASTER_CS_toggle;
  (void)GPIO_EXT_IRQ_read;
  (void)GPIO_EXT_IRQ_state;
  (void)GPIO_EXT_IRQ_set;
  (void)GPIO_EXT_IRQ_clr;
  (void)GPIO_EXT_IRQ_make_out;
  (void)GPIO_EXT_IRQ_toggle;
#if defined(ATXMEGA256A3)
  (void)GPIO_MASTER_CS_make_pulldown;
  (void)GPIO_EXT_IRQ_make_pulldown;
#endif

  // enable spi slave interrupt
  if(0 != HAL_RegisterIrq(SLAVE_IRQ, thereIsData, rSlaveSpiDataInd))
  {
    /* registration failed */
  }
  HAL_EnableIrq(SLAVE_IRQ);

  resetQueue(&rSpiRxQueue);
  resetQueue(&rSpiTxQueue);

#if defined(__DBG_SPI_ADAPTER__)
  openDbgUsart();
#endif // defined(__DBG_SPI_ADAPTER__)
}

/**************************************************************************//**
\brief "Data is ready" from spi slave interrupt task handler
******************************************************************************/
static void rSlaveSpiDataInd(void)
{
  if (SLAVE_DATA_IS_EMPTY == slaveIndReady)
  {
    slaveIndReady = SLAVE_THERE_IS_DATA;
  } else if (SLAVE_THERE_IS_DATA == slaveIndReady)
  {
    slaveIndReady = SLAVE_DATA_IS_READY;
  }
  HAL_DisableIrq(SLAVE_IRQ);
  SYS_PostTask(APL_TASK_ID);
}

/**************************************************************************//**
\brief Callback on spi transaction complete
******************************************************************************/
static void rSpiReceivedHandler(void)
{
  switch (spiState)
  {
    case WAITING_RX_MARKER:
      /* START_READ_MARKER transmission completed. Check for interrupt from slave
         to continue. */
      masterTransactionInProgress = false;
      rDataSlaveInd();
      break;

    case WAITING_RX_LEN_LSB:
      if (!currRxBuf->commandFrame.length)
        spiState = SPI_IDLE;

      #if defined(__DBG_SPI_ADAPTER__)
        sendDbgData((uint8_t*)&currRxBuf->commandFrame, LEN_SIZE);
      #endif // defined(__DBG_SPI_ADAPTER__)

      transacType = MASTER_READ_TRANSACTION;
      dataPointer = (uint8_t*)&currRxBuf->commandFrame;
      // for ARM compatibility (analigned structure member)
      dataPointer += offsetof(ZS_CommandFrame_t, commandId);
      dataLength = currRxBuf->commandFrame.length;
      spiState = WAITING_RX_DATA;
      rMasterSpiDelayer();
      break;

    case WAITING_RX_DATA:
      GPIO_MASTER_CS_set();
      spiState = SPI_IDLE;

      #if defined(__DBG_SPI_ADAPTER__)
        sendDbgData((uint8_t*)&currRxBuf->commandFrame +
          offsetof(ZS_CommandFrame_t, commandId), currRxBuf->commandFrame.length);
      #endif // defined(__DBG_SPI_ADAPTER__)

      // Full packet is received
      serialManager.service.notify(currRxBuf);
      currRxBuf = NULL;
      masterTransactionInProgress = false;
      // check spi to use again
      rDataSlaveInd();
      break;

    case WAITING_TX_MARKER:
      transacType = MASTER_WRITE_TRANSACTION;
      dataPointer = (uint8_t *)&currTxBuf->commandFrame;
      dataLength = currTxBuf->commandFrame.length + LEN_SIZE;
      spiState = WAITING_TX_DATA;
      rMasterSpiDelayer();
      break;

    case WAITING_TX_DATA:
      GPIO_MASTER_CS_set();
      // Full packet was transmitted
      bufferAllocator.free(currTxBuf);
      currTxBuf->state = R_BUFFER_FREE_STATE;
      currTxBuf = NULL;
      spiState = SPI_IDLE;
      masterTransactionInProgress = false;
      // check spi to use again
      rDataSlaveInd();
      break;

    default:
      break;
  }
}

/**************************************************************************//**
\brief Initiate sending new command frame

\param[in] cmd - command buffer with frame to be send

\return result code
******************************************************************************/
static SerialStatus_t rSendCommandFrame(ZS_CommandBuffer_t *cmd)
{
  static uint8_t startMarker = START_WRITE_MARKER;

  if (!cmd)
    return SERIAL_FAILED;

  if (SPI_IDLE == spiState)
  {
    // Send right now
    currTxBuf = cmd;
    GPIO_MASTER_CS_clr();

    transacType = MASTER_WRITE_TRANSACTION;
    dataPointer = &startMarker;
    dataLength = sizeof(uint8_t);
    spiState = WAITING_TX_MARKER;
    rMasterSpiDelayer();

    if (SPI_ERR_OR_OFF == spiState)
      return SERIAL_FAILED;
  }
  else
  {
    // Defer frame
    if(!putQueueElem(&rSpiTxQueue, cmd))
    {
      /* failed to queue */
    }
  }
  return SERIAL_SUCCESS;
}

/**************************************************************************//**
\brief Subtask for "Data is ready", should be called from task handler also.
******************************************************************************/
void rDataSlaveInd(void)
{
  static uint8_t startMarker = START_READ_MARKER;

  /* Deffer task execution until master current transaction finished */
  if (masterTransactionInProgress)
    return;

  switch (slaveIndReady)
  {
    case SLAVE_THERE_IS_DATA:
      if (SPI_IDLE == spiState)
      {
        HAL_UnregisterIrq(SLAVE_IRQ);
        if (0 != HAL_RegisterIrq(SLAVE_IRQ, dataReady, rSlaveSpiDataInd))
        {
          /* registration failed */
        }

        HAL_EnableIrq(SLAVE_IRQ);

        GPIO_MASTER_CS_clr();
        transacType = MASTER_WRITE_TRANSACTION;
        dataPointer = &startMarker;
        dataLength = sizeof(uint8_t);
        spiState = WAITING_RX_MARKER;
        rMasterSpiDelayer();
      }
      break;

    case SLAVE_DATA_IS_READY:
      if (WAITING_RX_MARKER == spiState)
      {
        // Allocate new data buffer if required
        if (!currRxBuf)
          currRxBuf = bufferAllocator.allocate();

        transacType = MASTER_READ_TRANSACTION;
        dataPointer = (uint8_t*)&currRxBuf->commandFrame;
        dataLength = LEN_SIZE;
        spiState = WAITING_RX_LEN_LSB;
        rMasterSpiDelayer();

        if (SPI_ERR_OR_OFF != spiState)
        {
          slaveIndReady = SLAVE_DATA_IS_EMPTY;
          // enable irq from slave
          HAL_UnregisterIrq(SLAVE_IRQ);
          if (0 != HAL_RegisterIrq(SLAVE_IRQ, thereIsData, rSlaveSpiDataInd))
          {
            /* registration failed */
          }
          HAL_EnableIrq(SLAVE_IRQ);
        }
      }
      break;

    default:
      if (SPI_IDLE == spiState)
        rSpiCheckTxQueue();
      break;
    }
}

/**************************************************************************//**
\brief Add software delay between spi bytes.
******************************************************************************/
static void rMasterSpiDelayer(void)
{
  int transacState;

  switch (transacType)
  {
    case MASTER_READ_TRANSACTION:
      HAL_Delay(APP_SOFT_USDELAY_BETWEEN_BYTES);
      transacState = HAL_ReadSpi(&rSpiDescriptor, dataPointer++, sizeof(uint8_t));
      break;

    case MASTER_WRITE_TRANSACTION:
      HAL_Delay(APP_SOFT_USDELAY_BETWEEN_BYTES);

      #if defined(__DBG_SPI_ADAPTER__)
        sendDbgData(dataPointer, sizeof(uint8_t));
      #endif // defined(__DBG_SPI_ADAPTER__)

      transacState = HAL_WriteSpi(&rSpiDescriptor, dataPointer++, sizeof(uint8_t));
      break;

    case MASTER_LAST_BYTE:
      rSpiReceivedHandler();
      return;

    default:
      break;
  }

  if (transacState)
  {
    spiState = SPI_ERR_OR_OFF;
    return;
  }

  masterTransactionInProgress = true;

  if (!--dataLength)
    transacType = MASTER_LAST_BYTE;
}

#endif //VALID_MASTER_SPI
/********************* spi master part (end) *********************************/
#endif // (APP_INTERFACE == APP_INTERFACE_SPI)

#endif // BOARD_PC
/* eof spiAdapter.c */
