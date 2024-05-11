/*******************************************************************************
  MAC HWD ZGP Common Header File

  Company:
    Microchip Technology Inc.

  File Name:
    macHwdZgpCommon.h

  Summary:
    This file provides a interface for the MAC functions required by GP Device.

  Description:
    This file contains the Implementation of mac level zgp functionalities.
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

#ifndef _MACHWDZGPCOMMON_H
#define _MACHWDZGPCOMMON_H

#ifdef _ZGPD_SPECIFIC_
/******************************************************************************
                    Includes section
******************************************************************************/
#include <RF231_RF212/PHY/include/phyCommon.h>
/******************************************************************************
                    Prototype section
******************************************************************************/
/******************************************************************************
  \brief    generates a random number and seeds the srand function
  \param    none.
  \return   none.
******************************************************************************/
void macHwdZgpRandomSeed(void);
/******************************************************************************
  \brief    switching to necessary state before transmission
  \param    none.
  \return   none.
******************************************************************************/
PHY_ReqStatus_t macHwdZgpPrepareTx(void);
/******************************************************************************
  \brief    tx frame handling once the transmission is complete
  \param    none.
  \return   none.
******************************************************************************/
void macHwdZgpFinishTxFrameHandling(void);
/******************************************************************************
  Identical frame delay timer handler
  Parameters: none.
  Returns: none.
******************************************************************************/
void macHwdZgpIdenticalFrameDelayHandler(void);
/******************************************************************************
  RTimer event handler.To switch from receive to trx off state if the the rx on 
  duration is over
  Parameters:
    none.
  Returns:
    none.
******************************************************************************/
void macHwdZgpRxAfterTxIntervalHandler(void);
/******************************************************************************
  RTimer event handler. To switch from trx off to rx state if the the rx offset
  duration is over
  Parameters:
    none.
  Returns:
    none.
******************************************************************************/
void macHwdZgpRxOffsetHandler(void);
/******************************************************************************
  switch to trx off state
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACHWDZGP_SetTrxOffState(void);
/******************************************************************************
  sets rx after tx parameter.
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACHWDZGP_SetRxAfterTx(void);
/******************************************************************************
  resets rx after tx parameter.
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACHWDZGP_ResetRxAfterTx(void);
/******************************************************************************
  gives rx after tx parameter.
  Parameters: none.
  Returns: rx after tx enabled or disabled.
******************************************************************************/
bool MACHWDZGP_GetRxAfterTx(void);
#endif /*_ZGPD_SPECIFIC_*/
#endif /* _MACHWDZGPCOMMON_H */
