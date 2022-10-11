/*******************************************************************************
  TrustCentre Promiscuous Mode Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcPromiscuousMode.h

  Summary:
    This file contains the TC Promiscuous mode module interface.

  Description:
    This file contains the TC Promiscuous mode module interface.
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


#ifndef _TCPROMISCUOUSMODE_H_
#define _TCPROMISCUOUSMODE_H_

#ifdef _LINK_SECURITY_ 
#ifdef _TC_PROMISCUOUS_MODE_

/******************************************************************************
                              Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                              Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Forces TC to enter the Promiscuous mode

  \return None.
******************************************************************************/
void TC_EnterPromiscuousMode(void);

/**************************************************************************//**
  \brief Forces TC to leave the Promiscuous mode

  \return None.
******************************************************************************/
void TC_LeavePromiscuousMode(void);

/**************************************************************************//**
  \brief Checks, if TC is in the Promiscuous mode

  \return True, if TC is in the Promiscuous mode, False - otherwise
******************************************************************************/
bool TC_IsPromiscuousMode(void);

#endif /* _TC_PROMISCUOUS_MODE_ */
#endif /* _LINK_SECURITY_ */

#endif /* _TCPROMISCUOUSMODE_H_ */
