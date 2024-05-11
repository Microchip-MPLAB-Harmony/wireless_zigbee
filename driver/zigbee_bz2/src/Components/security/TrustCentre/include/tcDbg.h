/*******************************************************************************
  TrustCentre Debug Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcDbg.h

  Summary:
    This file contains the Security Trust Centre debug Information.

  Description:
    This file contains the Security Trust Centre debug Information.
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


#ifndef _TCDBGH
#define _TCDBGH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <systemenvironment/include/dbg.h>

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Trust Centre debug codes declaration.

   These codes are used for debuging.
******************************************************************************/
typedef enum
{
  TCAUTHENTICHANDLERC_APSUPDATEDEVICEINDICATION_01    = 0x7000,
  TCAUTHENTICHANDLERC_APSUPDATEDEVICEINDICATION_02    = 0x7001,
  TCAUTHENTICHANDLERC_TCAUTHENTICTASKHANDLER_01       = 0x7002,
  TCKEYUPDATEHANDLER_TCKEYUPDATETASKHANDLER_00        = 0x7003,
  TCAUTHENTICHANDLERC_APSREMOVEDEVICECONF_00          = 0x7004,
  TCKEYUPDATEHANDLERC_ENDUPDATENETWORKKEYOPERATION_00 = 0x7005,
  TCDEVICETABLECTRLHANDLER_TCSETDEVICEKEY_00          = 0x7006,
  TCAUTHENTICHANDLERC_APSESTABLISHKEYCONF_00          = 0x7007,
  TCTASKMANAGER_00                                    = 0x7008,
  TCAUTHENTICHANDLERC_APSUPDATEDEVICEINDICATION_03    = 0x7009,
  TCAUTHENTICHANDLERC_APSTRANSPORTKEYCONF_00          = 0x700A,
  TC_KEYUPDATE_NULLCALLBACK0                          = 0x700B,
  TC_REMOVEDEVICE_NULLCALLBACK0                       = 0x700C,
  TC_KEYESTABLISHMEM_NO_MEMORY0                       = 0x700D,
  TC_KEYESTABLISH_APSTRANSPORTKEYCONF_00              = 0x700E,
} TcDbgCodeId_t;
#endif // _TCDBGH

// eof tcDbg.h
