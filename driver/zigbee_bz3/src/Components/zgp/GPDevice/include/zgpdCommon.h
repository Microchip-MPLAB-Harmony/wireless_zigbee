/*******************************************************************************
  Zigbee green power device common Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdCommon.h

  Summary:
    This file contains the ZGP device common definitions.

  Description:
    This file contains the ZGP device common definitions.
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

#ifndef _ZGPD_COMMON_H_
#define _ZGPD_COMMON_H_
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zgp/include/zgpCommon.h>

/******************************************************************************
//                               ZGP Data Structures
******************************************************************************/
#define NO_OF_ATTRIBUTE_REPORT_FIELD      1
#define NO_OF_ATTR_RECORDS                1

/******************************************************************************
                               ZGP Prototypes
******************************************************************************/
typedef enum _ZgpState_t// zgpManager possible states.
{
     ZGP_IDLE_STATE = 0x00,
     ZGP_RESET_REQ_STATE,
     ZGP_DATA_REQ_STATE,
     ZGP_CHANNEL_REQ_STATE,
     ZGP_COMMISSION_REQ_STATE,
     ZGP_DECOMMISSIONING_REQ_STATE,
     ZGP_SUCCESS_GPDF_REQ_STATE
}ZgpState_t;

typedef enum  
{
    ZGP_RESET_REQ_ID      = ZGP_RESET_REQ_STATE,
    ZGP_DATA_REQ_ID       = ZGP_DATA_REQ_STATE,
    ZGP_CHANNEL_REQ_ID    = ZGP_CHANNEL_REQ_STATE,
    ZGP_COMMISSION_REQ_ID = ZGP_COMMISSION_REQ_STATE,
    ZGP_DECOMMISSIONING_REQ_ID = ZGP_DECOMMISSIONING_REQ_STATE,
    ZGP_SUCCESS_GPDF_REQ_ID = ZGP_SUCCESS_GPDF_REQ_STATE
} ZgpRequestId_t;

//! Internal service fields which give us opportunity to compose requests' queue.
typedef struct
{
  void    *next;
  uint8_t requestId;
  bool presenceInQueue;
} ZGP_Service_t;

/******************************************************************************
  Finds next channel to scan from mask channels.
  Parameters:
    startChannel - pointer to the start channel for search.
    mask - mask of channels to scan.
  Returns:
    false - if channel was not found, true otherwise.
******************************************************************************/
INLINE bool findNextSupportedChannel(uint8_t *startChannel, uint32_t mask)
{
  uint8_t i = *startChannel;
  bool result = false;
  i++;
  for (; i < sizeof(mask)*NO_OF_BITS_IN_BYTE; i++)
  {
    if ((1ul << i) & mask)
    {
      *startChannel = i;
      result = true;
      break;
    }
  }
  return result;
}

#endif /*_ZGPD_COMMON_H_*/

//eof zgpdCommon.h
