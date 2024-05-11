/*******************************************************************************
  Security Service Provider SKKE Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspSkkeHandler.h

  Summary:
    This file contains the SKKE routine declaration.

  Description:
    This file contains the SSP SKKE routine declaration.
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


#ifndef _SSPSKKEHANDLER_H
#define _SSPSKKEHANDLER_H

#ifdef _LINK_SECURITY_

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <sysTypes.h>
#include <sspManager.h>
#include <sspAesHandler.h>

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum
{
  SKKE_STATE_IDLE,
  SKKE_STATE_CALCULATE_MACTAG1,
  SKKE_STATE_CALCULATE_MACTAG2,
  SKKE_STATE_CALCULATE_FINAL_MACTAG1,
  SKKE_STATE_CALCULATE_HASH1,
  SKKE_STATE_CALCULATE_HASH2,
} SspSkkeState_t;
/******************************************************************************
  TBD
******************************************************************************/
typedef struct
{
  SspSkkeState_t skkeState;
  uint8_t        macKey[SECURITY_KEY_SIZE];
  BEGIN_PACK
  struct PACK
  {
    volatile uint8_t keyExpander[SECURITY_KEY_SIZE];
    uint8_t macData[MAX_HASH_TEXT_SIZE];
    volatile uint8_t bitsExpander[16];
  };
  END_PACK
  union
  {
    SspKeyedHashMacReq_t keyedHashMacParam;
    SspBcbHashReq_t      bcbHashReqParam;
  };
} SspSkkeHandlerMem_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Calculates parameters of Security-Key Key Esteblishment procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateSkkeParamsReqHandler(void);

/***************************************************************************\\**
  \brief Copies with mirroring "length" bytes from "src" to "dst".

  \param
    dst - destination memory.
    src - source memory.
    length - number of bytes to copy.
  \return
    none.
********************************************************************************/
INLINE void mirrorMemcpy(uint8_t *dst, uint8_t *src, uint8_t length)
{
  while(length)
    *(dst++) = *(src + --length);
}

/**************************************************************************//**
  \brief Resets Skke handler
 ******************************************************************************/
void sspResetSkke(void);

#endif // _LINK_SECURITY_

#endif //_SSPSKKEHANDLER_H

// eof sspSkkeHandler.h

