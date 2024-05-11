/*****************************************************************************
  \file pccomAdapter.c

  \brief  Serial port manager for various connection type.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).


  History:
******************************************************************************/

#ifdef BOARD_PC
/******************************************************************************
                   Includes section
******************************************************************************/
#include <ZAppSiSerialManager.h>
#include <parser.h>
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <bufferAllocator.h>
#include <time.h>
#include <appTimer.h>
#include <sysUtils.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// Reserve space for 4 packets
#define MAX_PACKET_SIZE (sizeof(ZS_CommandFrame_t) + sizeof(uint8_t))
#define MAX_RX_BUF_SIZE (MAX_PACKET_SIZE * 4)

// Start of frame marker
#define SOF 0x2A

/******************************************************************************
                   Prototype(s) section
******************************************************************************/
void APL_TaskHandler(void);
/******************************************************************************
                   Global(s) section
******************************************************************************/
SerialManager_t serialManager;

/***********************************************************************************
                          Local variables section
***********************************************************************************/
static HANDLE hSerial;
static char comName[sizeof("\\\\.\\COM255")];
static ZS_CommandBuffer_t inBuffer;
static ZS_CommandFrame_t *inFrame = &inBuffer.commandFrame;

static clock_t startClock;
static bool timerHasStarted;
static HAL_AppTimer_t gAppTimer;
/*******************************************************************************
                      Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Write packet to COM port

\param[in] buffer - buffer with frame to be send
\return success status
******************************************************************************/
SerialStatus_t write(ZS_CommandBuffer_t* buffer)
{
  DWORD dwBytesWritten = 0;
  ZS_CommandFrame_t* frame = &buffer->commandFrame;
  int txLen = frame->length + sizeof(frame->length);
  uint8_t txBuf[MAX_PACKET_SIZE];

  txBuf[0] = SOF;
  memcpy(&txBuf[1], frame, txLen);

  if (!WriteFile(hSerial, txBuf, txLen + 1, &dwBytesWritten, NULL))
  {
    fprintf(stderr,"Serial port writing error");
    exit(1);
  }
  bufferAllocator.free(buffer);
  return SERIAL_SUCCESS;
}

/**************************************************************************//**
\brief Open COM cort

\param[in] interfaceID - port ID
\param[in] notify - callback on frame receive
******************************************************************************/
void openSerialManager(uint8_t interfaceID, void (*notify) (ZS_CommandBuffer_t *frame))
{
  sysAssert(INTERFACE_ID_USART0 == interfaceID);
  hSerial = CreateFile(comName,
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);
  if (INVALID_HANDLE_VALUE == hSerial)
  {
    fprintf(stderr, "Failed to open serial port %s. Error %ld", comName, GetLastError());
    exit(1);
    }
  {
    DCB dcbSerialParams;
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
      fprintf(stderr, "Error getting port parameters");
      exit(1);
    }
    dcbSerialParams.BaudRate=CBR_38400;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
      fprintf(stderr, "Error setting port parameters");
      exit(1);
    }
  }
  {
    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = 200;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier = 50;
    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier = 50;
    if (!SetCommTimeouts(hSerial, &timeouts))
    {
      fprintf(stderr, "Error setting port timeouts");
      exit(1);
    }
  }
  serialManager.write = write;
  serialManager.service.notify = notify;
}

/**************************************************************************//**
\brief Main loop
******************************************************************************/
void waitForInputFrames()
{
  static int animState = 0;
  DWORD dwBytesRead = 0;
  int rxCnt;
  uint8_t rxBuf[MAX_RX_BUF_SIZE];
  uint8_t *framePos = rxBuf;

  if (!ReadFile(hSerial, rxBuf, MAX_RX_BUF_SIZE, &dwBytesRead, NULL))
    {
      fprintf(stderr,"Serial port reading error");
    exit(1);
    }

  rxCnt = dwBytesRead;

  // Parse buffer
  while (rxCnt > 0)
  {
    int len;
    // Seek for the start of frame (excluding last byte, there shouldn't be SOF)
    uint8_t *sofPos = memchr(framePos, SOF, rxCnt - 1);
    // No frame found
    if (!sofPos)
      return;
    // Rewind to the length field
    sofPos++;
    rxCnt -= sofPos - framePos;
    framePos = sofPos;
    // Safe-limit packet length to avoid overflow
    len = *framePos = MIN(*framePos, sizeof(ZS_CommandFrame_t) - sizeof(inFrame->length));
    // Let the len include size of 'length' field
    len += sizeof(inFrame->length);
    // Drop incomplete packets (with expired interbyte timeout)
    if (len > rxCnt)
      return;

    // Visualize reception
    printf("\r%c", "_\\|/-\\|/"[++animState & 0x07]);

    memcpy(inFrame, framePos, len);
    serialManager.service.notify(&inBuffer);

    rxCnt -= len;
    framePos += len;
  }
}

int HAL_StartAppTimer(HAL_AppTimer_t *appTimer)
{
  startClock = clock();
  gAppTimer.interval = appTimer->interval;
  timerHasStarted = 1;

  return 0;
}

int HAL_StopAppTimer(HAL_AppTimer_t *appTimer)
{
  (void)appTimer;
  timerHasStarted = 0;

  return 0;
}

void simulateTimer(void)
{
  if (!timerHasStarted)
    return;

  if ((unsigned)(clock() - startClock) > gAppTimer.interval)
  {
    startClock = clock();
    advanceDemo();
  }
}

/**************************************************************************//**
\brief Application entry point

\param[in] argc - arguments count
\param[in] argv - vector of arguments
\return 0
******************************************************************************/
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid command line parameters.\n "
            "Usage: demo.exe COM10\n");
    exit(1);
  }

  snprintf(comName, sizeof(comName), "\\\\.\\%s", argv[1]);

    while(1)
    {
      APL_TaskHandler();
      waitForInputFrames();
      simulateTimer();
    }
  }

#endif // BOARD_PC
//eof pccomAdapter.c
