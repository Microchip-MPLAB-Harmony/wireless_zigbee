/*******************************************************************************
  ZAppSI Test Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiTest.h

  Summary:
    This file contains the Wrappers to internal functions.

  Description:
    This file contains the Wrappers to internal functions.
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


#ifdef ZSI_TEST
  #include <testCommon.h>

  #define STATE_LOGGING testZsiStateLogging
  #define COLLISION_STATUS_LOGGING testZsiCollisionStateLogging
  #define RECEIVE_FRAME_LOGGING testZsiReceiveFrameLogging
#else 
  #define STATE_LOGGING(state) {}
  #define COLLISION_STATUS_LOGGING(state) {}
  #define RECEIVE_FRAME_LOGGING(frame) {}
#endif

#ifdef ZSI_TEST
/******************************************************************************
  \brief Adds FCS in the end of the frame.

  \param[in] frame - frame, which keeps serialized data.

  \return None.
 ******************************************************************************/
void TEST_zsiAddFrameFcs(void *const frame);

/******************************************************************************
  \brief Prepare ACK frame.

  \param[in] status - reception status: ZSI_NO_ERROR_STATUS,
                      ZSI_INVALID_FCS_STATUS or ZSI_OVERFLOW_STATUS.
  \param[in] sequenceNumber - sequnece number associated with received frame.
  \param[out] ackFrame - pointer to memory to prepare.

  \return None.
 ******************************************************************************/
void TEST_zsiPrepareAck(uint8_t status, uint8_t sequenceNumber,
  ZsiAckFrame_t *const ackFrame);

/******************************************************************************
  \brief Wrapper to routine. Send ACK frame with particular sequence number and status. If previous
         transmission wasn't finished - action will be postponed.

  \param[in] status - reception status: ZSI_NO_ERROR_STATUS,
                      ZSI_INVALID_FCS_STATUS or ZSI_OVERFLOW_STATUS.
  \param[in] sequenceNumber - sequnece number associated with received frame.

  \return None.
 ******************************************************************************/
void TEST_zsiReplyWithAck(uint8_t status, uint8_t sequenceNumber);

#endif /* ZSI_TEST */