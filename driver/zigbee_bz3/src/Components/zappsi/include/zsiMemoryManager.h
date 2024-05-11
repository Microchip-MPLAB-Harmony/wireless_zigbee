/*******************************************************************************
  ZAppSI Memory Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiMemoryManager.h

  Summary:
    This file contains the ZAppSI memory manager interface.

  Description:
    This file contains the ZAppSI memory manager interface.
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


#ifndef _ZSIMEMORYMANAGER_H
#define _ZSIMEMORYMANAGER_H

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <zsiFrames.h>
#include <zsiDbg.h>
#include <sysQueue.h>
#include <zdo.h>
#include <zsiSysSerialization.h>
#include <zsiKeSerialization.h>

/******************************************************************************
                              Defines section
******************************************************************************/
#ifndef BOARD_PC

#define ZSI_MEMORY_BUFFERS_AMOUNT 18U
#if ZSI_MEMORY_BUFFERS_AMOUNT < 18U
#error "Not enough ZAppSI memory buffers: 18 or more required! "
#endif

#else

#define ZSI_MEMORY_BUFFERS_AMOUNT 128U
#if ZSI_MEMORY_BUFFERS_AMOUNT < 128U //6U
#error "Not enough ZAppSI memory buffers: 128 or more required! "
#endif

#endif


/* Indexes of memory buffers reserved for SREQ/SRSP processing */
#define ZSI_SYNC0_RESERVED_MEMORY_BUFFER 0U
#define ZSI_SYNC1_RESERVED_MEMORY_BUFFER 1U

#define ZSI_SYNC2_RESERVED_MEMORY_BUFFER 2U
#define ZSI_SYNC3_RESERVED_MEMORY_BUFFER 3U
#define ZSI_SYNC4_RESERVED_MEMORY_BUFFER 4U
#define ZSI_SYNC5_RESERVED_MEMORY_BUFFER 5U

#ifndef BOARD_PC
/* Mutual memory buffers start index */
#define ZSI_MUTUAL_MEMORY_BUFFERS_START  8U
#else
/* Mutual memory buffers start index */
#define ZSI_MUTUAL_MEMORY_BUFFERS_START  16U
#endif

/* Mutual memory marker */
#define ZSI_MUTUAL_MEMORY 0x2AU
#define ZSI_RX_ACK_MEMORY 0x2BU
#define ZSI_TX_ACK_MEMORY 0x2CU

/******************************************************************************
                              Types section
******************************************************************************/
typedef struct _ZsiMemoryBuffer_t
{
  QueueElement_t next;
  bool busy;
  TOP_GUARD
  union
  {
    uint8_t                         memory;
    ZsiCommandFrame_t               commandFrame;
    ZDO_StartNetworkReq_t           zdoStartNetworkReq;
    ZsiCsParameter_t                csParameter;
    ZDO_MgmtNwkUpdateNotf_t         zdoNwkUpdateNtfy;
    APS_DataInd_t                   apsDataInd;
    APS_DataReq_t                   apsDataReq;
    ZDO_ZdpReq_t                    zdpReq;
    MAC_SetReq_t                    macSetReq;
#if CERTICOM_SUPPORT == 1
    ZsiEccKeyBitGenerate_t          zsiEccKeyBitGenerate;
    ZsiEccGenerateKey_t             zsiEccGenerateKey;
#endif
    SSP_ZgpEncryptFrameReq_t zgpEncryptFrameReq;
    SSP_ZgpDecryptFrameReq_t zgpDecryptFrameReq;
  };
  BOTTOM_GUARD
} ZsiMemoryBuffer_t;

typedef struct _ZsiMemoryPool_t
{
  TOP_GUARD
  ZsiAckFrame_t     ackTxFrame;
  ZsiAckFrame_t     ackRxFrame;
  BOTTOM_GUARD
  ZsiMemoryBuffer_t buffers[ZSI_MEMORY_BUFFERS_AMOUNT];
} ZsiMemoryPool_t;

typedef struct _ZsiMemoryManager_t
{
  ZsiMemoryPool_t memoryPool;
} ZsiMemoryManager_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief ZAppSI memory manager reset routine.
 ******************************************************************************/
void zsiResetMemoryManager(void);

/******************************************************************************
  \brief Allocates memory for ZAppSI frames and BitCloud primitives.

  \return Pointer to memory.
 ******************************************************************************/
void *zsiAllocateMemory(uint8_t memoryType);

/******************************************************************************
  \brief Free memory allocated for ZAppSI command frames and BitCloud
         primitives.

  \param[in] memory - allocated memory to free.

  \return None.
 ******************************************************************************/
void zsiFreeMemory(const void *const memory);

/******************************************************************************
  \brief Checks if free memory buffer is available.

  \return True, if free memory buffer is available, false - otherwise.
 ******************************************************************************/
bool zsiIsMemoryAvailable(void);

#endif /* _ZSIMEMORYMANAGER_H */
/* eof zsiMemoryManager.h */
