/*******************************************************************************
  Zigbee green power device memory Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdMem.h

  Summary:
    This file contains the ZGP device memory types.

  Description:
    This file contains the ZGP device memory types.
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

#ifndef ZGPDMEM_H
#define ZGPDMEM_H
/******************************************************************************
                        Includes  section.
******************************************************************************/
#include <systemenvironment/include/sysQueue.h>
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdCommissioningHandler.h>
#include <hal/include/appTimer.h>
#include <zgp/GPDevice/include/zgpdIb.h>
#ifdef ZGP_SECURITY_ENABLE
#include <security/serviceprovider/include/sspSfp.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#endif
#ifdef _COMMISSIONING_
#include <pds/include/wlPdsMemIds.h>
#endif

/******************************************************************************
                                 Macros
******************************************************************************/
#ifdef _COMMISSIONING_
#ifdef ZGP_SECURITY_ENABLE
#define ZGP_INCOMINGFRAMECOUNTER_MEM_ID   APP_PARAM1_MEM_ID
#define ZGP_OUTGOINGFRAMECOUNTER_MEM_ID   APP_PARAM2_MEM_ID
#define ZGP_SECURITYKEYS_MEM_ID           APP_PARAM3_MEM_ID
#endif
#define ZGP_DEVICEPARAMS_MEM_ID           APP_PARAM4_MEM_ID
#define ZGP_STACKPARAMS_MEM_ID            APP_PARAM5_MEM_ID
#define ZGP_MACSEQNO_MEM_ID               APP_PARAM6_MEM_ID
#define ZGP_FACTORYNEW_MEM_ID             APP_PARAM7_MEM_ID

#define ZGP_ALL_MEM_ID                    APP_DIR1_MEM_ID
#define ZGP_COMMISSIONING_MEM_ID          APP_DIR2_MEM_ID
#define ZGP_SECURITY_COMMISSIONING_MEM_ID APP_DIR3_MEM_ID
#define ZGP_COUNTERS_ID                   APP_DIR4_MEM_ID
#endif

/******************************************************************************
                        Types section.
******************************************************************************/
typedef struct
{
  ZgpState_t                managerState; // For the manager needs.
  //zgpCommissionState_t      commissioningState;
	//zgpCommissioningEvents_t  commissioningEvent;
  QueueDescriptor_t         reqQueueDescr;
  void                      *zgpReq;
  ZGP_Packet_t              zgpPacket;
#ifdef ZGP_SECURITY_ENABLE
  SSP_ZgpEncryptFrameReq_t  zgpEncryptReq;
  SSP_ZgpDecryptFrameReq_t  zgpDecryptReq;
#endif
  ZGP_WriteAttributeInd_t zgpWriteAttributeInd;
  ZGP_ClusterRecord_t   zgpClusterRecord;
  union
  {
    MAC_SetReq_t          set;
    MAC_ResetReq_t        reset;
    MAC_DataReq_t         data;
    RF_RandomReq_t        rnd;
  } macReq;
  ZGP_DataInd_t zgpDataIndParams;
  HAL_AppTimer_t timerDescr;
} ZGP_Mem_t;
/******************************************************************************
                        Prototypes section.
******************************************************************************/

#endif //ZGPDMEM_H

// eof zgpdMem.h
