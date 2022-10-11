/*******************************************************************************
  Security Service Provider Debug Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspDbg.h

  Summary:
    This file contains the Debug Information for SSP layer.

  Description:
    This file provides the Debug Information for SSP layer routines.
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


#ifndef _SSPDBGH
#define _SSPDBGH

#include <dbg.h>

typedef enum
{
  SSPSFPHANDLERC_SSPENCRYPTFRAMEREQHANDLER_00 = 0x7800,
  SSPMANAGER_TASKHANDLER_00                   = 0x7801,
  SSPMANAGER_TASKHANDLER_01                   = 0x7802,
  SSPCCM_SSPAESCONF_00                        = 0x7803,
  SSPSFPHANDLERC_CCMCONFIRM_00                = 0x7804,
  SSPHASHHANDLERC_BCBHASHCONF_00              = 0x7805,
  SSPSFPHANDLERC_SSPKEYEDHASHMACCONFIRM_00    = 0x7806,
  SSPSKKEHANDLERC_HASHCONFIRM_00              = 0x7807,
  SSPMANAGER_SENDREQTOHANDLER_00              = 0x7808,
  SSPHASHHANDLERC_SSPBCBHASH_0                = 0x7809,
  SSPCCM_SSPAESCONFWHILEMICCHECK_00           = 0x780a,
  SSPCCM_SSPAESCONFWHILEMICCHECK_01           = 0x780b,
  SSPCCM_SSPAESCONFWHILEMICCHECK_02           = 0x780c,
  SSPCCMHANDLER_DETECTNEXTSTATE_0             = 0x780d,
  SSPCCMHANDLER_SSPAESCONF_00                 = 0x780e,
  SPP_CCM_NULLCALLBACK0                       = 0x780F,
  SPP_CCM_NULLCALLBACK1                       = 0x7810,
  SSP_CALCULATEAUTHENTIC_NULLCALLBACK0        = 0x781A,
  SSP_KEYEDHASHMAC_NULLCALLBACK0              = 0x781B,
  SSP_AESENCRYPT_NULLCALLBACK0                = 0x781C,
  SSPMANAGER_MUTEXLOCKCONF_00                 = 0x781E,
  SSPMANAGER_SSPCCMREQHANDLER_00              = 0x781F
} SspDbgCodeId_t;
#endif // _SSPDBGH
