/*******************************************************************************
  TrustCentre Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tc.h

  Summary:
    Security Trust Centre main header file - includes all others TC public
    header files.

  Description:
    This file contains the inclusion of all other TC public header files.
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


#ifndef _TCH
#define _TCH

/******************************************************************************
                             Include section.
******************************************************************************/
#include <security/TrustCentre/include/tcAuthentic.h>
#include <security/TrustCentre/include/tcCommon.h>
#include <security/TrustCentre/include/tcDbg.h>
#include <security/TrustCentre/include/tcDeviceTableCtrl.h>
#include <security/TrustCentre/include/tcKeyUpdate.h>
#include <security/TrustCentre/include/tcRemove.h>
#include <security/TrustCentre/include/tcReset.h>
#ifdef _LINK_SECURITY_
  #include <security/TrustCentre/include/tcKeyEstablish.h>
#endif // _LINK_SECURITY_

#endif // _TCH

// eof tc.h
