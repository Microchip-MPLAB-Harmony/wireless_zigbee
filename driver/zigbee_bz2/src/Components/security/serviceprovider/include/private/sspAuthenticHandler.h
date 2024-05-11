/*******************************************************************************
  Security Service Provider Authentic Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspAuthenticHandler.h

  Summary:
    This file contains the Mutual Symmetric-Key Entity Authentication routine handler's.

  Description:
    This file contains the Mutual Symmetric-Key Entity Authentication routine handler's.
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


#ifndef _SSPAUTHENTICHANDLER_H
#define _SSPAUTHENTICHANDLER_H

#ifdef _LINK_SECURITY_
/******************************************************************************
                        Includes section.
******************************************************************************/
#include <sysTypes.h>
#include <sspManager.h>
#include <sspHashHandler.h>
#include <sspAesHandler.h>

/******************************************************************************
                        Types section.
******************************************************************************/
/******************************************************************************
  TBD
******************************************************************************/
typedef struct
{
  SspKeyedHashMacReq_t keyedHashMacParams;
  BEGIN_PACK
  struct PACK
  {
    volatile uint8_t keyExpander[SECURITY_KEY_SIZE];
    uint8_t macData[MAX_HASH_TEXT_SIZE];
    volatile uint8_t bitsExpander[16];
  };
  END_PACK
} SspAuthenticHandlerMem_t;
/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Calculates parameters (MacTag1) for Mutual Symmetric-Key Entity Authentication
  procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateAuthenticMacTag1ReqHandler(void);

/*******************************************************************************
  Calculates parameters (MacTag2) for Mutual Symmetric-Key Entity Authentication
  procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateAuthenticMacTag2ReqHandler(void);

#endif // _LINK_SECURITY_

#endif //_SSPAUTHENTICHANDLER_H

// eof sspAuthenticHandler.h

