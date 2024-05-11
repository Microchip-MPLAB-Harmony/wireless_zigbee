/*******************************************************************************
  Zigbee green power device memory Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdMem.c

  Summary:
    This file contains the ZGP variable's memory.

  Description:
    This file contains the ZGP variable's memory.
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

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zgp/GPDevice/include/zgpdMem.h>
#include <systemenvironment/include/sysUtils.h>
/******************************************************************************
                    Global variables section
******************************************************************************/
ZGP_Mem_t zgpMem;
#ifdef _ENABLE_PERSISTENT_SERVER_
#ifdef _COMMISSIONING_
#ifdef ZGP_SECURITY_ENABLE
PDS_DECLARE_FILE(ZGP_INCOMINGFRAMECOUNTER_MEM_ID,     
        (ZGP_SEC_INFRM_CNTR_SIZE*(sizeof(zgpInFrmCounter_t))),  
        &csZGIB.secParams.inFrmCntrSet[0], 
        FILE_INTEGRITY_CONTROL_MARK);
PDS_DECLARE_FILE(ZGP_OUTGOINGFRAMECOUNTER_MEM_ID,     (sizeof(zgpGetSecParams()->outFrmCntr)),              &csZGIB.secParams.outFrmCntr,      NO_ITEM_FLAGS);
PDS_DECLARE_FILE(ZGP_SECURITYKEYS_MEM_ID,             sizeof(zgpSecurityKeys_t),                          &csZGIB.secParams.secKey,          NO_ITEM_FLAGS);
#endif
PDS_DECLARE_FILE(ZGP_DEVICEPARAMS_MEM_ID,             sizeof(zgpDeviceParams_t),                          &csZGIB.deviceParams,              NO_ITEM_FLAGS);
PDS_DECLARE_FILE(ZGP_STACKPARAMS_MEM_ID,              sizeof(zgpStackParams_t),                           &csZGIB.stackparams,               NO_ITEM_FLAGS);
PDS_DECLARE_FILE(ZGP_MACSEQNO_MEM_ID,                 sizeof(csPIB.macAttr.dsn),                          &csPIB.macAttr.dsn,                NO_ITEM_FLAGS);
PDS_DECLARE_FILE(ZGP_FACTORYNEW_MEM_ID,               sizeof(isFactoryNew),                               &isFactoryNew,                     NO_ITEM_FLAGS);

PROGMEM_DECLARE(PDS_MemId_t csZgpMemoryIdsTable[]) =
{
#ifdef ZGP_SECURITY_ENABLE
  ZGP_INCOMINGFRAMECOUNTER_MEM_ID,
  ZGP_OUTGOINGFRAMECOUNTER_MEM_ID,
  ZGP_SECURITYKEYS_MEM_ID,
#endif
  ZGP_DEVICEPARAMS_MEM_ID,
  ZGP_STACKPARAMS_MEM_ID,
  ZGP_MACSEQNO_MEM_ID,
  ZGP_FACTORYNEW_MEM_ID
};

/* ZGP  parameters directory descriptor.
   Shall be placed in the PDS_FD code segment. */
PDS_DECLARE_DIR(PDS_DirDescr_t csZgpGeneralParamsDirDescr) =
{
  .list       = csZgpMemoryIdsTable,
  .filesCount = ARRAY_SIZE(csZgpMemoryIdsTable),
  .memoryId   = ZGP_ALL_MEM_ID
};

PROGMEM_DECLARE(PDS_MemId_t csZgpCommissioningIdsTable[]) =
{
#ifdef ZGP_SECURITY_ENABLE
  ZGP_OUTGOINGFRAMECOUNTER_MEM_ID,
#endif
  ZGP_MACSEQNO_MEM_ID,
  ZGP_STACKPARAMS_MEM_ID,
  ZGP_DEVICEPARAMS_MEM_ID,
  ZGP_FACTORYNEW_MEM_ID
};

PDS_DECLARE_DIR(PDS_DirDescr_t csZgpCommissioningDirDescr) =
{
  .list       = csZgpCommissioningIdsTable,
  .filesCount = ARRAY_SIZE(csZgpCommissioningIdsTable),
  .memoryId   = ZGP_COMMISSIONING_MEM_ID
};

PROGMEM_DECLARE(PDS_MemId_t csZgpSecurityCommissioningIdsTable[]) =
{
#ifdef ZGP_SECURITY_ENABLE
  ZGP_SECURITYKEYS_MEM_ID,
  ZGP_OUTGOINGFRAMECOUNTER_MEM_ID,
#endif
  ZGP_MACSEQNO_MEM_ID,
  ZGP_STACKPARAMS_MEM_ID,
  ZGP_FACTORYNEW_MEM_ID
};

PDS_DECLARE_DIR(PDS_DirDescr_t csZgpSecurityCommissioningDirDescr) =
{
  .list       = csZgpSecurityCommissioningIdsTable,
  .filesCount = ARRAY_SIZE(csZgpSecurityCommissioningIdsTable),
  .memoryId   = ZGP_SECURITY_COMMISSIONING_MEM_ID
};

PROGMEM_DECLARE(PDS_MemId_t csZgpCountersIdsTable[]) =
{
#ifdef ZGP_SECURITY_ENABLE
  ZGP_OUTGOINGFRAMECOUNTER_MEM_ID,
#endif
  ZGP_MACSEQNO_MEM_ID
};

PDS_DECLARE_DIR(PDS_DirDescr_t csZgpCountersDirDescr) =
{
  .list       = csZgpCountersIdsTable,
  .filesCount = ARRAY_SIZE(csZgpCountersIdsTable),
  .memoryId   = ZGP_COUNTERS_ID
};
#endif
#endif
// eof zgpMem.c


