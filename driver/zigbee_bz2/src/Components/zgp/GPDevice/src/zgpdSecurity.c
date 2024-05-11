/*******************************************************************************
  Zigbee green power device security Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdSecurity.c

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

#ifdef ZGP_SECURITY_ENABLE
#include <zgp/GPDevice/include/zgpdIb.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
/******************************************************************************
                                Globals
******************************************************************************/

/******************************************************************************
  \brief    Check the key is valid, return true if it is valid and false otherwise.
  \param    key - that needs to be validated.
  \return   bool.
******************************************************************************/
bool zgpIsValidKey(uint8_t *key)
{
  uint8_t index;
  
  for (index = 0; index < ZGP_SEC_KEY_SIZE; index++)
  {
    if(key[index])
    {
      return(true);
    }
  }
  
  return(false);
}

/******************************************************************************
  \brief    Set the GPLinkKey
  \param    key - that needs to be validated.
  \return   bool - true success, false otherwise.
******************************************************************************/
bool zgpSetLinkKey(uint8_t *key)
{
  if (NULL == key)
  {
    return(false);
  }
  
  memcpy(zgpGetSecParams()->secKey.gpLinkKey, key, ZGP_SEC_KEY_SIZE);
  
  return(true);
}

/******************************************************************************
  \brief    Set security key
  \param    key - that needs to be validated.
  \return   bool - true success, false otherwise.
******************************************************************************/
bool zgpSetSecurityKey(uint8_t *key)
{
  if (NULL == key)
  {
    return(false);
  }
  
  memcpy(zgpGetSecParams()->secKey.key, key, ZGP_SEC_KEY_SIZE);
  
  return(true);
}

#endif //ZGP_SECURITY_ENABLE

//eof zgpSecurity.c
