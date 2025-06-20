/*******************************************************************************
  Trust Center Swapout Source File 

  Company:
    Microchip Technology Inc.

  File Name:
    app_tcSwapout.c

  Summary:
    This file contains the implementation of Tc Swapout functions.

  Description:
    This file contains the implementation of Tc Swapout functions.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _ZIGBEE_REV_23_SUPPORT_
/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <z3device/common/include/app_tcSwapout.h>
#include <FreeRTOSConfig.h>
#include <osal/osal_freertos.h>
#include <osal/osal_freertos_extend.h>
#include <aps/include/aps.h>
#include <app_zigbee/zigbee_console/console.h>
#include <configserver/include/configserver.h>
#include <nwk/include/nwk.h>

/*******************************************************************************
                             Definition(s) section
*******************************************************************************/
#define BACKUP_BUFFER_SIZE 59U  /* size of aps backup data + index position. */

#define TC_SOF                   0x24 //'$'

#define TC_CMD_BACKUP_REQ        0x0001 // command for sending backup request
#define TC_CMD_BACKUP_DATA       0x0002 // command for sending backup data
#define TC_CMD_BACKUP_ACK        0x0010 // command for sending backup ack

#define TC_CMD_RESTORE_REQ       0x0003 // command for sending restore request
#define TC_CMD_RESTORE_DATA      0x0004 // command for sending restore data
#define TC_CMD_RESTORE_ACK       0x0020 // command for sending restore ack

#define TC_BACKUP_FRAME_COMMAND_SIZE 2U
#define TC_BACKUP_FRAME_LENGTH_SIZE  2U

#define TC_BACKUP_MAX_PAYLOAD_SIZE 59U

OSAL_QUEUE_HANDLE_TYPE tcBackupQueue;

/******************************************************************************
                   Types section
******************************************************************************/

/**************************************************************************//**
\brief  Describes the structure of TC backup tunnel descriptor.
 *****************************************************************************/
typedef struct
{
  DRV_HANDLE              tcbTunnelHandle;
  DRV_USART_BUFFER_HANDLE tcbReadBufferHandle;
  DRV_USART_BUFFER_HANDLE tcbWriteBufferHandle;
  uint8_t *rxBuffer;
  uint16_t rxBufferLength;
  uint8_t *txBuffer;
  uint16_t txBufferLength;
  void (*rxCallback)(uint16_t);
  void (*txCallback)(void);
  void (*errCallback)(uint16_t);

} TCB_TunnelDescriptor_t;

/**************************************************************************//**
\brief  Describes the differnt states of Tx during swapout.
 *****************************************************************************/
typedef enum _TcTxState_t
{
  TX_ERR_OR_OFF,
  TX_IDLE,
  TX_SENDING_SOF,
  TX_SENDING_DATA,
} TcTxState_t;

/**************************************************************************//**
\brief  Describes the differnt states of RX during swapout.
 *****************************************************************************/
typedef enum _TcRxState_t
{
  RX_ERR_OR_OFF,
  RX_WAITING_START,
  RX_WAITING_LENGTH,
  RX_WAITING_CMD,
  RX_WAITING_PAYLOAD,
} TcRxState_t;

/**************************************************************************//**
\brief  Describes the different states of the swapout state machine.
 *****************************************************************************/
typedef enum _TcSwapComState_t
{
  COMM_IDLE,
  SEND_BACKUP_REQ,
  RECEIVE_BACKUP_REQ_ACK,
  SEND_BACKUP_DATA,
  RECEIVE_BACKUP_DATA_ACK,
  RECEIVE_RESTORE_REQ,
  SEND_RESTORE_REQ_ACK,
  RECEIVE_RESTORE_DATA,
  SEND_RESTORE_DATA_ACK,
}TcSwapComState_t;

/**************************************************************************//**
\brief  Describes the frame structure of backup and restore.
 *****************************************************************************/
BEGIN_PACK
typedef struct PACK _TcBackupFrame_t
{
  /* data */
  uint16_t payloadLength;
  uint16_t commandId;
  uint8_t payload[TC_BACKUP_MAX_PAYLOAD_SIZE];
} TcBackupFrame_t;
END_PACK

/*******************************************************************************
                             Prototypes section
*******************************************************************************/
static bool checkIfItemDuplicated(TC_BackupId_t* backupItemId);
static void backupEventHandler(SYS_EventId_t ev, SYS_EventData_t data);
static bool appIsTCBackupItemsPending(void);
static void startTcBackupUartClient(void);
static void backupUartRead(void *buffer, uint8_t length);
static void backupUartWrite(uint8_t *buffer, uint8_t length);
static void backupUartReceivedHandler(uint16_t bytesReceived);
static void backupUartTransmittedHandler(void);
static void backupUartErrHandler(uint16_t processedBytes);
static void sendBackupRequest(void);
static void sendBackupData(void);
static void backupUSARTBufferEventHandler ( DRV_USART_BUFFER_EVENT bufferEvent,
                                                DRV_USART_BUFFER_HANDLE bufferHandle,
                                                uintptr_t context );
void consoleRx(uint8_t data);
static void swapoutCommunicationStateMachine(void);
static void backupUartClear(void);
static void tcSwapIntermessageTimeoutExpired(void);

/******************************************************************************
                  Static variables section
******************************************************************************/
static TCB_TunnelDescriptor_t backupTunnelDescriptor;
static TcBackupFrame_t tcBackupFrame;

static uint8_t tcBuffer;

static uint8_t txSof = TC_SOF;
static volatile TcRxState_t receiverStatus = RX_ERR_OR_OFF;
static volatile TcTxState_t transmitterStatus = TX_ERR_OR_OFF;
static TcSwapComState_t tcComState = COMM_IDLE;

static bool transactionBusy = false;
static bool backupCycleInProgress = false;

static TC_BackupId_t itemFromBackupQueue;

static SYS_EventReceiver_t backupEventReceiver = { .func = backupEventHandler};

static HAL_AppTimer_t tcSwapIntermessageTimer =
{
  .interval = 5000U,
  .mode = TIMER_ONE_SHOT_MODE,
  .callback = tcSwapIntermessageTimeoutExpired,
};

/*******************************************************************************
                             Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Trust center backup initialization.

\param - None.

\return - None.
******************************************************************************/
void APP_InitTCBackup(void)
{
  OSAL_QUEUE_Create(&tcBackupQueue, 5U, sizeof(TC_BackupId_t));

  SYS_SubscribeToEvent(BC_EVENT_APS_TC_BACKUP, &backupEventReceiver);

  /* TODO: Commenting temporarily. Will be */
  startTcBackupUartClient();
}

/**************************************************************************//**
\brief Start the backup process. This should be called during idle task.

\param - None.

\return - None.
******************************************************************************/
void APP_CommenceTCBackup(void)
{
  if (ZB_IsIdle())
  {
    if((!backupCycleInProgress) && (appIsTCBackupItemsPending()))
    {
      if(OSAL_RESULT_TRUE == OSAL_QUEUE_Receive(&tcBackupQueue, &itemFromBackupQueue, 0))
      {
        backupCycleInProgress = true;
        tcComState = SEND_BACKUP_REQ;
      }
    }
    if((!transactionBusy))
    {
      swapoutCommunicationStateMachine();
    }
  }
}

/**************************************************************************//**
\brief Restore the backup data to the device. 

\param - None.

\return - None.
******************************************************************************/
void APP_CommenceTCRestore(void)
{
  if(tcBackupFrame.payload[0U] == 0U)
  {
    static uint64_t extPanId = 0ULL;
    memcpy(&extPanId, &tcBackupFrame.payload[1U], sizeof(uint64_t));
    if(NWK_NO_EXT_PANID != extPanId)
    {
      NWK_SetExtPanId(&extPanId);
      CS_WriteParameter(CS_EXT_PANID_ID, &extPanId);
      SYS_PostEvent(BC_EVENT_APS_TC_SWAP, 0);
    }
  }
  else
  {
    APS_RestoreBackup(tcBackupFrame.payload[0U], &tcBackupFrame.payload[1U]);
  }

  if(NWK_GetSwapoutStatus() == false)
  {
    NWK_SetSwapoutStatus(true);
  }
}

/**************************************************************************//**
\brief Adds new entry into the backup queue.

\param[in] backupId - Offset id of the backup record.

\return True - If the operation is successful.
        False - Otherwise.
******************************************************************************/
bool APP_AddTCBackupEntry(TC_BackupId_t backupId)
{
  TC_BackupId_t itemIdToBackup = backupId;

  if(itemIdToBackup == 0)
  {
    return false;
  }

  if(checkIfItemDuplicated(&itemIdToBackup))
  {
    return true;
  }
  else if (OSAL_RESULT_TRUE != OSAL_QUEUE_Send(&tcBackupQueue, &itemIdToBackup, 0))
  {
    configASSERT(false);
    return false;
  }
  return true;
}

/**************************************************************************//**
\brief This function will check for any pending items in the queue to be
       backed up.

\param - None.

\return True - If there are any items in the queue to be backed up.
        False - Otherwise.
******************************************************************************/
static bool appIsTCBackupItemsPending(void)
{
  return ((uint8_t)uxQueueMessagesWaiting(tcBackupQueue)) > 0U ? true : false;
}

/**************************************************************************//**
\brief This function will check if the given item is already queued for 
       backup.

\param[in] backupItemId - pointer to the backup id.

\return True - If the itemId is alread in backup queue.
        False - Otherwise.
******************************************************************************/
static bool checkIfItemDuplicated(TC_BackupId_t* backupItemId)
{
  TC_BackupId_t itemId;
  bool result = false;

  UBaseType_t queueCount = uxQueueMessagesWaiting(tcBackupQueue);

  for (uint8_t i = 0U; i < queueCount; i++)
  {
    if (OSAL_RESULT_TRUE == OSAL_QUEUE_Receive(&tcBackupQueue, &itemId, 0))
    {
      /*Compare ID and OFFSET*/
      if(itemId == *backupItemId)
      {
        result = true;
      }
      // Repost the item
      OSAL_QUEUE_Send(&tcBackupQueue, &itemId, 0);
    }
    else
      configASSERT(false);  
  }
  
  return result;
}

/**************************************************************************//**
\brief This function will enqueue the backup entry during every SYS_Event

\param[in] ev - Sys-eventId that flagged this event.
\param[in] data - Data that was posted during this sys event.

\return None
******************************************************************************/
static void backupEventHandler(SYS_EventId_t ev, SYS_EventData_t data)
{
  if((TC_BackupId_t)data == NWK_EXT_PAN_ID_BACKUP_INDEX)
  {
    (void)APP_AddTCBackupEntry(data);
  }
  else
  {
    APS_KeyHandle_t *handle = (APS_KeyHandle_t *)data;
    (void)APP_AddTCBackupEntry(handle->idx); 
  }
}

/**************************************************************************//**
\brief This function will read the specific length of data from the Uart

\param[out] buffer - pointer to the buffer to which the uart read data 
                     stored.
\param[in] length - Length of the data to be read from the uart.

\return None
******************************************************************************/
static void backupUartRead(void *buffer, uint8_t length)
{
  DRV_USART_ReadBufferAdd(backupTunnelDescriptor.tcbTunnelHandle, buffer, length,  &(backupTunnelDescriptor.tcbReadBufferHandle));
}

/**************************************************************************//**
\brief This function will write the specific length of data to the Uart

\param[in] buffer - pointer to the buffer from which the data are transfered
                    via uart
\param[in] length - Length of the data to be send via uart.

\return None
******************************************************************************/
static void backupUartWrite(uint8_t *buffer, uint8_t length)
{
  DRV_USART_WriteBufferAdd(backupTunnelDescriptor.tcbTunnelHandle, buffer, length,  &(backupTunnelDescriptor.tcbWriteBufferHandle));
}

/**************************************************************************//**
\brief Handler function for uart reception during backup and restore 
       mechanism.

\return None
******************************************************************************/
static void backupUartReceivedHandler(uint16_t bytesReceived)
{
  switch (receiverStatus)
  {
    case RX_WAITING_START:
      {
        if(((tcComState == RECEIVE_BACKUP_REQ_ACK) || (tcComState == RECEIVE_BACKUP_DATA_ACK)
            || (tcComState == RECEIVE_RESTORE_REQ) || (tcComState == RECEIVE_RESTORE_DATA)) 
            && (TC_SOF == tcBuffer))
        {
          receiverStatus = RX_WAITING_LENGTH;
          backupUartRead((void*)&(tcBackupFrame.payloadLength), TC_BACKUP_FRAME_LENGTH_SIZE);
        }
        else
        {
          consoleRx(tcBuffer);
          backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
        }
      }
      break;
    case RX_WAITING_LENGTH:
      {
        uint16_t lengthValue = tcBackupFrame.payloadLength;
        if(lengthValue >= TC_BACKUP_FRAME_COMMAND_SIZE)
        {
          receiverStatus = RX_WAITING_CMD;
          backupUartRead((void*)&(tcBackupFrame.commandId), lengthValue);
        }
        else
        {
          receiverStatus = RX_ERR_OR_OFF;
          backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
        }
      }
      break;
    case RX_WAITING_CMD:
      {
        receiverStatus = RX_ERR_OR_OFF;
        transactionBusy = false;
        backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
        HAL_StopAppTimer(&tcSwapIntermessageTimer);
      }
      break;
    default:
      {
        receiverStatus = RX_ERR_OR_OFF;
        consoleRx(tcBuffer);
        backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
      }
  }
}

/**************************************************************************//**
\brief Handler function for uart transmission during backup and restore 
       mechanism.

\return None
******************************************************************************/
static void backupUartTransmittedHandler(void)
{
  switch (transmitterStatus)
  {
    case TX_SENDING_SOF:
      {
        uint8_t *writeBuffer = (uint8_t *)&tcBackupFrame;
        backupUartWrite(writeBuffer, tcBackupFrame.payloadLength + TC_BACKUP_FRAME_LENGTH_SIZE);
        transmitterStatus = TX_SENDING_DATA;
      }
      break;
    case TX_SENDING_DATA:
      {
        transmitterStatus = TX_IDLE;
        backupUartClear();
        receiverStatus = RX_WAITING_START;
        backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
      }
      break;
  }
}

/**************************************************************************//**
\brief Handler function for uart error during backup and restore 
       mechanism.

\return None
******************************************************************************/
static void backupUartErrHandler(uint16_t processedBytes)
{
  //TOOD error handling
}

/**************************************************************************//**
\brief This handler function is called during every uart event.

\param[in] bufferEvent - uart event that called this handler function.
\param[in] bufferHandler - uart handle that corresponds to this event.
\param[in] context - additional data / function that need to processed.

\return None
******************************************************************************/
static void backupUSARTBufferEventHandler(
    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context
)
{
    switch(bufferEvent)
    {
        case DRV_USART_BUFFER_EVENT_COMPLETE:
            if (bufferHandle == backupTunnelDescriptor.tcbWriteBufferHandle)
            {
                backupTunnelDescriptor.txCallback();
            }
            else if (bufferHandle == backupTunnelDescriptor.tcbReadBufferHandle)
            {
                uint8_t length = DRV_USART_BufferCompletedBytesGet(bufferHandle);
                backupTunnelDescriptor.rxCallback(length);
            }
            
            break;

        case DRV_USART_BUFFER_EVENT_ERROR:
        default:
        {
            uint16_t processedBytes= DRV_USART_BufferCompletedBytesGet(bufferHandle);
            backupTunnelDescriptor.errCallback(processedBytes);
        }
            break;
    }
}

/**************************************************************************//**
\brief This function will start the uart client for backup and restore purpose.

\return None
******************************************************************************/
static void startTcBackupUartClient(void)
{
  backupTunnelDescriptor.rxCallback = &backupUartReceivedHandler;
  backupTunnelDescriptor.txCallback = &backupUartTransmittedHandler;
  backupTunnelDescriptor.errCallback = &backupUartErrHandler;

  backupTunnelDescriptor.tcbTunnelHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);

  if (backupTunnelDescriptor.tcbTunnelHandle != DRV_HANDLE_INVALID)
  {
    DRV_USART_BufferEventHandlerSet(backupTunnelDescriptor.tcbTunnelHandle, backupUSARTBufferEventHandler, 0);
  }
  //Uart read to start receiving the data that may corresponds to console.
  backupUartRead((void*)(&tcBuffer), sizeof(tcBuffer));
  
  receiverStatus = RX_WAITING_START;
  transmitterStatus = TX_IDLE;

  backupCycleInProgress = false;
}

/**************************************************************************//**
\brief This function will clear the backup frame for next transmission or
       reception.

\return None
******************************************************************************/
static void clearBackupFrame(void)
{
  memset(&tcBackupFrame, 0x0, sizeof(tcBackupFrame));
}

/**************************************************************************//**
\brief This function will send the backup init request.

\return None
******************************************************************************/
static void sendBackupRequest(void)
{
  clearBackupFrame();

  tcBackupFrame.payloadLength = TC_BACKUP_FRAME_COMMAND_SIZE;
  tcBackupFrame.commandId = TC_CMD_BACKUP_REQ;

  transmitterStatus = TX_SENDING_SOF;
  receiverStatus = RX_ERR_OR_OFF;

  HAL_StartAppTimer(&tcSwapIntermessageTimer);
  backupUartWrite(&txSof, sizeof(txSof));
}

/**************************************************************************//**
\brief This function will send the backup data.

\return None
******************************************************************************/
static void sendBackupData(void)
{
  uint16_t backupLength = 0U;
  clearBackupFrame();

  tcBackupFrame.commandId = TC_CMD_BACKUP_DATA;
  if(itemFromBackupQueue == NWK_EXT_PAN_ID_BACKUP_INDEX)
  {
    tcBackupFrame.payload[0U] = 0x00;
    uint64_t extPanId = NWK_GetExtPanId();
    memcpy(&(tcBackupFrame.payload[1U]), &extPanId, sizeof(extPanId));
    backupLength = sizeof(extPanId);
  }
  else
  {
    tcBackupFrame.payload[0U] = (uint8_t)(itemFromBackupQueue & 0x00FF);
    backupLength = APS_FillBackup(itemFromBackupQueue, &(tcBackupFrame.payload[1U]));
  }
  
  tcBackupFrame.payloadLength = TC_BACKUP_FRAME_COMMAND_SIZE + backupLength + 1U;

  transmitterStatus = TX_SENDING_SOF;
  receiverStatus = RX_ERR_OR_OFF;

  HAL_StartAppTimer(&tcSwapIntermessageTimer);
  backupUartWrite(&txSof, sizeof(txSof));
}

/**************************************************************************//**
\brief This function will send the ack for restore data.

\return None
******************************************************************************/
static void sendRestoreAck(void)
{
  clearBackupFrame();

  tcBackupFrame.payloadLength = TC_BACKUP_FRAME_COMMAND_SIZE;
  tcBackupFrame.commandId = TC_CMD_RESTORE_ACK;

  transmitterStatus = TX_SENDING_SOF;
  receiverStatus = RX_ERR_OR_OFF;

  HAL_StartAppTimer(&tcSwapIntermessageTimer);
  backupUartWrite(&txSof, sizeof(txSof));
}

/**************************************************************************//**
\brief State machine function for the swapout mechanism.

\return None
******************************************************************************/
static void swapoutCommunicationStateMachine(void)
{
  switch(tcComState)
  {
    case SEND_BACKUP_REQ:
      {
        transactionBusy = true;
        sendBackupRequest();
        tcComState = RECEIVE_BACKUP_REQ_ACK;
        break;
      }
    case RECEIVE_BACKUP_REQ_ACK:
      {
        if(receiverStatus == RX_ERR_OR_OFF)
        {
          if(tcBackupFrame.commandId == TC_CMD_BACKUP_ACK)
          {
            tcComState = SEND_BACKUP_DATA;
          }
          if(tcBackupFrame.commandId == TC_CMD_RESTORE_REQ)
          {
            tcComState = SEND_RESTORE_REQ_ACK;
          }
        }
      }
      break;
    case SEND_BACKUP_DATA:
      {
        transactionBusy = true;
        sendBackupData();
        tcComState = RECEIVE_BACKUP_DATA_ACK;
        break;
      }
    case RECEIVE_BACKUP_DATA_ACK:
      {
        if(receiverStatus == RX_ERR_OR_OFF)
        {
          if(tcBackupFrame.commandId == TC_CMD_BACKUP_ACK)
          {
            tcComState = COMM_IDLE;
            backupCycleInProgress = false;
          }
        }
      }
      break;
    case SEND_RESTORE_REQ_ACK:
      {
        transactionBusy = true;
        sendRestoreAck();
        tcComState = RECEIVE_RESTORE_DATA;
      }
      break;
    case RECEIVE_RESTORE_DATA:
      {
        if(receiverStatus == RX_ERR_OR_OFF)
        {
          if(tcBackupFrame.commandId == TC_CMD_RESTORE_DATA)
          {
            APP_CommenceTCRestore();
            tcComState = SEND_RESTORE_DATA_ACK;
          }
        }
      }
      break;
    case SEND_RESTORE_DATA_ACK:
      {
        transactionBusy = true;
        sendRestoreAck();
        tcComState = RECEIVE_RESTORE_DATA;
      }
      break;
  }
}

/**************************************************************************//**
\brief This function will clear the backup uart write and read queue.

\return None
******************************************************************************/
static void backupUartClear(void)
{
  DRV_USART_WriteQueuePurge(backupTunnelDescriptor.tcbTunnelHandle);
  DRV_USART_ReadQueuePurge(backupTunnelDescriptor.tcbTunnelHandle);
}

/**************************************************************************//**
\brief Intermediate communication timeout function for tc swap.

\return None
******************************************************************************/
static void tcSwapIntermessageTimeoutExpired(void)
{
  tcComState = SEND_BACKUP_REQ;
  backupUartClear();
  receiverStatus = RX_ERR_OR_OFF;
  transmitterStatus = TX_IDLE;
  transactionBusy = false;
}

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
