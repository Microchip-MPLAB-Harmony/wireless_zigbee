/*******************************************************************************
  ZAppSI Serial Controller Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiSerialController.h

  Summary:
    This file contains the ZAppSI serial controller interface.

  Description:
    This file contains the ZAppSI serial controller interface.
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


#ifndef ZSISERIALCONTROLLER_H
#define ZSISERIALCONTROLLER_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <zsiFrames.h>
#include <appTimer.h>
#include <sysQueue.h>

/******************************************************************************
                              Defines section
******************************************************************************/
#define ZSI_MEDIUM_RX_BUFFER_LENGTH sizeof(ZsiCommandFrame_t)
                              
/* Collision types to be resolved. */
#define ZSI_NO_COLLISIONS 0U
/* Collision occures, when new command received from medium, while current
   transmission (AREQ, SREQ, SRSP) still inprogress. So we can't reply with
   ACK imidiately. Note, that ACK transmission fact will not affect current
   transmission state. */
#define ZSI_SERIAL_IMMIDIATE_ACK_REQUIRED      (1U << 0U)
/* Collision occures, when AREQ, SREQ, SRSP transmission state changes
   (e.g. ackTimer fired), but raised with ZSI_SERIAL_IMMIDIATE_ACK_REQUIRED
   collision ACK transmission is still inprogress. So we can't resend (e.g.)
   imidiately. Note, that ACK transmission fact will not affect current
   transmission state, so it changes anyway.*/
#define ZSI_SERIAL_IMMIDIATE_CMD_SEND_REQUIRED (1U << 1U)
/*  Collision occures, when ACK with success status received during ACK
    transmission, so we can't finish current transaction because of changed
    context. */
#define ZSI_SERIAL_CMD_TRANSMISSION_FINISHED   (1U << 3U)

/* Macros to drive transmitting transaction with ack waiting */
#define ZSI_ACK_TX_IN_PROGRESS(ackTxState)     (ackTxState |= 0x80)
#define ZSI_ACK_TX_COMPLETE(ackTxState)        (ackTxState &= ~0x80)
#define ZSI_ACK_TX_IS_IN_PROGRESS(ackTxState)  (ackTxState & 0x80)
#define ZSI_ACK_TX_COUNT_UP(ackTxState)        (ackTxState++)
#define ZSI_ACK_TX_COUNT_DOWN(ackTxState)      (ackTxState--)
#define ZSI_ACK_TX_QUANTITY(ackTxState)        (ackTxState & 0x7F)

/******************************************************************************
                              Types section
******************************************************************************/
typedef enum _ZsiSerialState_t
{
  ZSI_SERIAL_STATE_INIT               = 0x00,
  ZSI_SERIAL_STATE_IDLE               = 0x01,
  ZSI_SERIAL_STATE_SENDING            = 0x02,
  ZSI_SERIAL_STATE_WAITING_ACK        = 0x03,
  ZSI_SERIAL_STATE_WAITING_SRSP       = 0x04,
  ZSI_SERIAL_STATE_OVERFLOW_RESOLVING = 0x05
} ZsiSerialState_t;

typedef struct _ZsiSerialSynchroModeTimer_t
{
  BcTime_t expirationTime;
  bool     started;
} ZsiSerialSynchroModeTimer_t;

typedef struct _ZsiSerialController_t
{
  ZsiSerialState_t            state;
  uint8_t                     collisionStatus;
  uint8_t                     ackRetries;
  void                        *currentTransmission;
  HAL_AppTimer_t              ackWaitTimer;
  HAL_AppTimer_t              overflowTimer;
  ZsiSerialSynchroModeTimer_t synchroModeTimer;
  QueueDescriptor_t           txQueue;
} ZsiSerialController_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief ZAppSI serial controller reset routine.

  \return None.
 ******************************************************************************/
void zsiResetSerial(void);

/******************************************************************************
  \brief Transaction has been finished. Clear pointer and memory.
*******************************************************************************/
void zsiSerialClearCurTransac(void);

/******************************************************************************
  \brief ZAppSI serial controller task handler.

  \return None.
 ******************************************************************************/
void zsiSerialTaskHandler(void);

/******************************************************************************
  \brief Returns serial controller status.

  \return True, if serial controller is busy, otherwise - false.
 ******************************************************************************/
bool zsiSerialIsBusy(void);

/******************************************************************************
  \brief Send frame to ZAppSI serial controller for further transmisson.

  \param[in] cmdFrame - frame, which keeps serialized data.

  \return None.
 ******************************************************************************/
void zsiSerialSend(ZsiCommandFrame_t *const cmdFrame);

/******************************************************************************
  \brief Pass data for transmission through medium.

  \param[in] frame - frame, which keeps serialized data.
  \param[in] size - actual frame size.

  \return None.
 ******************************************************************************/
int zsiMediumSend(void *frame, uint16_t size);

/******************************************************************************
  \brief Serial medium initialization routine.
         Should be implemented in particular medium adapter.

  \return Transmission status.
 ******************************************************************************/
int zsiMediumInit(void);

/******************************************************************************
  \brief Indication of new frame received from remote device.

  \param[in] status - reception status:
                      ZSI_NO_ERROR_STATUS or ZSI_OVERFLOW_STATUS.
  \param[in] sequenceNumber - sequnece number associated with frame.
  \param[in] frame - pointer to received frame.

  \return None.
 ******************************************************************************/
void zsiMediumReceive(uint8_t status, uint8_t sequenceNumber, void *const frame);

/******************************************************************************
  \brief Callback for medium transmission finished.

  \return None.
 ******************************************************************************/
void zsiMediumSendingDone(void);

/******************************************************************************
  \brief Store new command for further transmission.

  \param[in] cmdFrame - frame, which keeps serialized data.

  \return None.
 ******************************************************************************/
void zsiSerialStoreTxCmd(const ZsiCommandFrame_t *const cmdFrame);

#endif /* ZSISERIALCONTROLLER_H */
/* eof zsiSerialController.h */
