/*******************************************************************************
  ZAppSI Initialization Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiInit.h

  Summary:
    This file contains the ZAppSI initialization module interface.

  Description:
    This file contains the ZAppSI initialization module interface.
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


#ifndef ZSIINIT_H
#define ZSIINIT_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  \brief ZAppSI initialization routine.
 ******************************************************************************/
void ZSI_Init(void);

/******************************************************************************
  \brief ZAppSI initialization handler
 ******************************************************************************/
void zsiInitTaskHandler(void);

#ifdef ZAPPSI_HOST
/**************************************************************************//**
  \brief Initial parameters synchronization between HOST and NP.

  \return None.
 ******************************************************************************/
void zsiSynchronizeStartupParameters(void);
#endif /* ZAPPSI_HOST */
/**************************************************************************//**
  \brief Resets all zsi related queues

  \return None.
 ******************************************************************************/
void zsiResetQueues(void);

#endif /* ZSIINIT_H */
