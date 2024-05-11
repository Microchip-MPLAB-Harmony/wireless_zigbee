/*******************************************************************************
  APS SKKEResponder Header File

  Company
    Microchip Technology Inc.

  File Name
    apsSkkeResponder.h

  Summary
    Private interface of APS SKKE Responder.

  Description
    This header file defines the interface to the APS SKKE responder functions.
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

#if !defined _APS_SKKE_RESPONDER_H
#define _APS_SKKE_RESPONDER_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>

#if defined _HIGH_SECURITY_
/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of SKKE responder.
 ******************************************************************************/
APS_PRIVATE void apsSkkeResponderTaskHandler(void);

/**************************************************************************//**
  \brief Process SKKE-1 command frame from a initiator.

  \param[in] ind - pointer to NWK parameters of received SKKE-1 frame.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsRSkke1Ind(NWK_DataInd_t *ind);

/**************************************************************************//**
  \brief Process SKKE-3 command frame from a initiator.

  \param[in] ind - pointer to NWK parameters of received SKKE-3 frame.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsRSkke3Ind(NWK_DataInd_t *ind);

#else  /* _HIGH_SECURITY_ */


#define apsSkkeResponderTaskHandler NULL

#endif /* _HIGH_SECURITY_ */

#endif /* _APS_SKKE_RESPONDER_H */
/** eof apsSkkeResponder.h */
