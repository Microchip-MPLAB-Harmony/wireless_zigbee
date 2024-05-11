/*******************************************************************************
  Security Service Provider Challenge Generator Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sspChallengeGenHandler.h

  Summary:
    This file contains the SSP Challenge generator handler declaration.

  Description:
    This file contains the SSP Challenge generator handler declaration.
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


#ifndef _SSPCHALLENGEGENHANDLER_H
#define _SSPCHALLENGEGENHANDLER_H

/******************************************************************************
                        Includes section.
******************************************************************************/

/******************************************************************************
                        Definition section.
******************************************************************************/

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Resets Security Service Provider entity.
  Parameters:
    challenge - pointer to the memory for saving generated challenge.
  Return:
    none.
********************************************************************************/
void sspGenerateChallengeHandler(uint8_t challenge[/*CHALLENGE_SEQUENCE_SIZE*/]);
#endif //_SSPCHALLENGEGENHANDLER_H

// eof sspChallengeGenHandler.h

