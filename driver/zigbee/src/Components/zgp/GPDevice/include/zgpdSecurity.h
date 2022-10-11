/*******************************************************************************
  Zigbee green power device security Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdSecurity.h

  Summary:
    This file contains the ZGP security definitions.

  Description:
    This file contains the ZGP security definitions.
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

#ifndef _ZGPD_SEC_H_
#define _ZGPD_SEC_H_

/******************************************************************************
                          Header files
******************************************************************************/
#include <zgp/GPDevice/include/zgpdCommon.h>

/******************************************************************************
                              Defines
******************************************************************************/
#define ZGP_SEC_KEY_SIZE                      16u
#define ZGP_SEC_INFRM_CNTR_SIZE               1u

/******************************************************************************
                              Typedefs
******************************************************************************/
BEGIN_PACK
typedef struct _ZgpInFrmCounter_t
{
  uint32_t inFrmCntr;
  ExtAddr_t senderAddress;
}zgpInFrmCounter_t;
END_PACK

BEGIN_PACK
typedef struct _ZgpSecurityKeys_t_
{
  uint8_t gpLinkKey[ZGP_SEC_KEY_SIZE];  //Link key
  uint8_t key[ZGP_SEC_KEY_SIZE];        //KEY
  ZGP_SecKeyType_t keyType;              //Type of KEY
  bool gpLinkKeyIsSet;                  //Will be set if Link key is available
  bool keyIsSet;                        //Will be set if KEY is available
}zgpSecurityKeys_t;
END_PACK

typedef struct _zgpdSecMaterialSet_t
{
  uint32_t outFrmCntr;                  //Outgoing frame counter
  zgpSecurityKeys_t secKey;
  zgpInFrmCounter_t inFrmCntrSet[ZGP_SEC_INFRM_CNTR_SIZE];
}zgpdSecMaterialSet_t;

/******************************************************************************
                              Externs
******************************************************************************/


/******************************************************************************
                              Prototypes
******************************************************************************/
bool zgpIsValidKey(uint8_t *key);
bool zgpSetLinkKey(uint8_t *key);
bool zgpSetSecurityKey(uint8_t *key);

#endif //_ZGPD_SEC_H_

//eof zgpdSecurity.h
