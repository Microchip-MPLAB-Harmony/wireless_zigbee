/*******************************************************************************
  HAL Advanced Encryption Standard Source File

  Company:
    Microchip Technology Inc.

  File Name:
    halAes.c

  Summary:
    This file contains the Implementation of BitCloud HAL AES.

  Description:
    This file contains the Implementation of BitCloud HAL AES.
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

#include <hal/cortexm4/pic32cx/include/halAes.h>
#include <hal/cortexm4/pic32cx/include/halDbg.h>
#include <hal/include/halTaskManager.h>

#include <sxsymcrypt/blkcipher_api.h>
#include <sxsymcrypt/keyref_api.h>
#include <sxsymcrypt/statuscodes.h>

#include <systemenvironment/include/sysQueue.h>
#include <systemenvironment/include/sysAssert.h>


#define DRIVER_VERSION 0x00000001u


#define ERR_NONE 0
#define ERR_INVALID_DATA -1
#define BLOCK_SIZE   (16)
#define KEY_SIZE     (16)

struct sxblkcipher blkciph;
struct sxkeyref keyref;
static uint8_t key[KEY_SIZE];
static DECLARE_QUEUE(halAesRequestQueue);

HAL_AES_EncryptReq_t req;

/**************************************************************************//**
\brief HAL AES Encrypt Function Request

\param[in] reqParams_s - request structure of AES
\return None
******************************************************************************/
void HAL_AES_EncryptReq(HAL_AES_EncryptReq_t *reqParams_s)
{
  memcpy(&req,reqParams_s , sizeof(HAL_AES_EncryptReq_t));

  halPostTask(HAL_SM_REQ);
}

/**************************************************************************//**
\brief Aes HAL Init

\param[out] None
\param[in] None
\return None
*****************************************************************************/
void halAesInit(void)
{
    *((volatile uint32_t*)(0x43000000)) = 0x00000001; //swrst  
    *((volatile uint32_t*)(0x43000000)) = 0x00000002; //enable
    //aes_sync_init(&CRYPTOGRAPHY_0, AES_REGS); // To be called in sys init
}

/**************************************************************************//**
\brief HAL SmReset

\param[out] None
\param[in] None
\return None
******************************************************************************/
void HAL_SmReset(void)
{
  resetQueue(&halAesRequestQueue);
  halClearTask(HAL_SM_REQ);
  halAesInit();
}

/**************************************************************************//**
\brief Aes HAL Handling of request

\param[out] None
\param[in] None
\return None
******************************************************************************/
void halSmRequestHandler (void)
{
 	switch (req.aesCmd)
	{
	  case SM_SET_KEY_COMMAND :
      {
        memcpy(key, req.text, KEY_SIZE);
        keyref = SX_KEYREF_LOAD_MATERIAL(KEY_SIZE, key);
      }
	  break;
	  case SM_ECB_ENCRYPT_COMMAND :
      {
        int8_t res = SX_BLKCIPHER_CREATE_AESECB_ENC(&blkciph, &keyref);
        
        if(SX_OK == res)          
          res = SX_BLKCIPHER_CRYPT(&blkciph, req.text, BLOCK_SIZE, req.text);//outdata
        if(SX_OK == res)          
          res = SX_BLKCIPHER_RUN(&blkciph);
        if(SX_OK == res)          
          res  = SX_BLKCIPHER_WAIT(&blkciph);

        if(SX_OK != res)
          SYS_E_ASSERT_FATAL(false, HAL_AES);
      }
      break;
	  case SM_ECB_DECRYPT_COMMAND :
      {
         /*Block cipher copy */
        SX_BLKCIPHER_CREATE_AESECB_DEC(&blkciph, &keyref);
           
        int8_t res = SX_BLKCIPHER_CRYPT(&blkciph, req.text, BLOCK_SIZE, req.text);
        if (SX_OK == res)          
          res = SX_BLKCIPHER_RUN(&blkciph);
        if (SX_OK == res)          
          res = SX_BLKCIPHER_WAIT(&blkciph); 
        if (SX_OK != res)		 
          SYS_E_ASSERT_FATAL(false, HAL_AES);
	  }
      break;
	 default:
	   SYS_E_ASSERT_FATAL(false, HAL_AES);
	   break;
	}
	
	SYS_E_ASSERT_FATAL(req.encryptConf, HAL_AES);
	req.encryptConf();
}

