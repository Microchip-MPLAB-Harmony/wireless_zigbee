/*******************************************************************************
  APS SKKEInitiator Header File

  Company
    Microchip Technology Inc.

  File Name
    apsSkkeInitiator.h

  Summary
    Private interface of APS SKKE Initiator.

  Description
    This header file defines the interface to the APS SKKE initiator functions.
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

#if !defined _APS_SKKE_INITIATOR_H
#define _APS_SKKE_INITIATOR_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>

#if defined _HIGH_SECURITY_
/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of SKKE initiator.
 ******************************************************************************/
APS_PRIVATE void apsSkkeInitiatorTaskHandler(void);

/**************************************************************************//**
  \brief Process SKKE-2 command frame from a responder.

  \param[in] ind - pointer to NWK parameters of received SKKE-2 frame.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsISkke2Ind(NWK_DataInd_t *ind);

/**************************************************************************//**
  \brief Process SKKE-4 command frame from a responder.

  \param[in] ind - pointer to NWK parameters of received SKKE-4 frame.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsISkke4Ind(NWK_DataInd_t *ind);

#else /* no _HIGH_SECURITY_ */


#define apsSkkeInitiatorTaskHandler NULL

#endif /* _HIGH_SECURITY_ */

#endif /* _APS_SKKE_INITIATOR_H */
/** eof apsSkkeInitiator.h */

