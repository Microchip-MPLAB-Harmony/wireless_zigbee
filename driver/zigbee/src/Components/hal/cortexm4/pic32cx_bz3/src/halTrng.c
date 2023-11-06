/*******************************************************************************
  HAL True Random Number Generator Source File

  Company:
    Microchip Technology Inc.

  File Name:
    halTrng.c

  Summary:
    This file provides the interface to true random number generator functions.

  Description:
    This file provides the interface to true random number generator functions.
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



#if defined(__ICCARM__)
#include <pic32cx1012bz25048_fpga.h>
#elif defined (__GNUC__)
#include <xc.h>
#endif


#include <sxsymcrypt/trng_api.h>
#include <sxsymcrypt/statuscodes.h>

#include <hal/include/halTaskManager.h>
#include <systemenvironment/include/sysAssert.h>



struct sx_trng ctx;
/**************************************************************************//**
\brief HAL AES Encrypt Function Request

\param[in] reqParams_s - request structure of AES
\return None
******************************************************************************/
uint16_t TRNG_ReadData(void)
{
	char randBytes[2] = {0};
	uint8_t randSize = 2;
	bool readSuccess = false;

    if(SX_OK == SX_TRNG_INIT(&ctx, NULL))
    {
	  while(!readSuccess)
	  {			
	    int result = SX_TRNG_GET(&ctx, randBytes, randSize);
	    if (result == SX_OK)
		  readSuccess = true;
	  }
    }
    return (*(uint16_t*)(&randBytes[0]));
}


