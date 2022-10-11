/*******************************************************************************
  MAC HWD ZGP Common Header File

  Company:
    Microchip Technology Inc.

  File Name:
    macZgpCommon.h

  Summary:
    This file provides a interface for the MAC functions required by GP Device.

  Description:
    This file provides a interface for the MAC functions required by GP Device.
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

#ifndef _MACZGPCOMMON_H
#define _MACZGPCOMMON_H

#ifdef _ZGPD_SPECIFIC_
/******************************************************************************
                    Includes section
******************************************************************************/
/******************************************************************************
                    Prototype section
******************************************************************************/
/******************************************************************************
  \brief    generates a random number and seeds the srand function
  \param    none.
  \return   none.
******************************************************************************/
void macZgpRandomSeed(void);
/******************************************************************************
  \brief    enable/disable csma based on the input
  \param    none.
  \return   none.
******************************************************************************/
void macZgpSetCsma(bool csma);
/******************************************************************************
  \brief    switching to necessary state before transmission
  \param    none.
  \return   none.
******************************************************************************/
PHY_ReqStatus_t macZgpPrepareTx(void);
/******************************************************************************
  \brief    tx frame handling once the transmission is complete
  \param    none.
  \return   none.
******************************************************************************/
void macZgpFinishTxFrameHandling(void);
/******************************************************************************
  gives enable transceiver
  Parameters: none.
  Returns: rx after tx enabled or disabled.
******************************************************************************/
inline void macZgpEnableTransceiver(void)
{
  PRR1 &= ~(1 << PRTRX24);
}
/******************************************************************************
  Identical frame delay timer handler
  Parameters: none.
  Returns: none.
******************************************************************************/
void macZgpIdenticalFrameDelayHandler(void);
/******************************************************************************
  RTimer event handler.To switch from receive to trx off state if the the rx on 
  duration is over
  Parameters:
    none.
  Returns:
    none.
******************************************************************************/
void macZgpRxAfterTxIntervalHandler(void);
/******************************************************************************
  RTimer event handler. To switch from trx off to rx state if the the rx offset
  duration is over
  Parameters:
    none.
  Returns:
    none.
******************************************************************************/
void macZgpRxOffsetHandler(void);
/******************************************************************************
  switch to trx off state
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACZGP_SetTrxOffState(void);
/******************************************************************************
  sets rx after tx parameter.
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACZGP_SetRxAfterTx(void);
/******************************************************************************
  resets rx after tx parameter.
  Parameters: none.
  Returns: none.
******************************************************************************/
void MACZGP_ResetRxAfterTx(void);
/******************************************************************************
  gives rx after tx parameter.
  Parameters: none.
  Returns: rx after tx enabled or disabled.
******************************************************************************/
bool MACZGP_GetRxAfterTx(void);
#endif /*_ZGPD_SPECIFIC_*/
#endif /* _MACZGPCOMMON_H */
