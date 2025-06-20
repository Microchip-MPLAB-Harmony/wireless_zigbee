/*******************************************************************************
  ZAppSI Debug Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiDbg.h

  Summary:
    This file contains the ZAppSI debug information.

  Description:
    This file contains the ZAppSI debug information.
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


#ifndef ZSIDBG_H
#define ZSIDBG_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dbg.h>

/******************************************************************************
                    Defines section
******************************************************************************/

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum _ZSI_DbgCodeId_t
{
  ZSIDRIVER_ZSIKEEPBEARINGENTITY0                  = 0xA000,
  ZSIDRIVER_ZSIPROCESSCOMMAND0                     = 0xA001,
  ZSIDRIVER_ZSICOMMANDRECEIVED0                    = 0xA002,
  ZSIDRIVER_ZSIDRIVERTASKHANDLER0                  = 0xA003,
  ZSIDRIVER_ZSIDRIVERTASKHANDLER1                  = 0xA004,
  ZSIDRIVER_ZSIDRIVERTASKHANDLER2                  = 0xA005,
  ZSIDRIVER_ZSISRSP_OUTSIDE_BLOCKING               = 0xA006,

  ZSISERIALCONTROLLER_ZSISERIALSEND0               = 0xA010,
  ZSISERIALCONTROLLER_ZSISERIALACKTIMERFIRED0      = 0xA011,
  ZSISERIALCONTROLLER_ZSISERIALACKTIMERFIRED1      = 0xA012,
  ZSISERIALCONTROLLER_ZSISERIALSRSPTIMERFIRED0     = 0xA013,
  ZSISERIALCONTROLLER_ZSISERIALSRSPTIMERFIRED1     = 0xA014,
  ZSISERIALCONTROLLER_ZSISERIALOVERFLOWTIMERFIRED0 = 0xA015,
  ZSISERIALCONTROLLER_ZSIMEDIUMRECEIVE0            = 0xA016,
  ZSISERIALCONTROLLER_ZSISERIALACKRECEIVED0        = 0xA017,
  ZSISERIALCONTROLLER_ZSISERIALACKRECEIVED1        = 0xA018,
  ZSISERIALCONTROLLER_ZSISERIALACKRECEIVED2        = 0xA019,
  ZSISERIALCONTROLLER_ZSISERIALCOMMANDRECEIVED0    = 0xA01A,
  ZSISERIALCONTROLLER_ZSISERIALCOMMANDRECEIVED1    = 0xA01B,
  ZSISERIALCONTROLLER_ZSISERIALCOMMANDRECEIVED2    = 0xA01C,
  ZSISERIALCONTROLLER_ZSISERIALRECEIVE0            = 0xA01D,

  ZSIMEMORYMANAGER_MEMORYCORRUPTION0               = 0xA020,
  ZSIMEMORYMANAGER_MEMORYCORRUPTION1               = 0xA021,
  ZSIMEMORYMANAGER_MEMORYCORRUPTION2               = 0xA022,
  ZSIMEMORYMANAGER_MEMORYCORRUPTION3               = 0xA023,
  ZSIMEMORYMANAGER_MEMORYCORRUPTION4               = 0xA024,
  ZSIMEMORYMANAGER_ZSIFREEMEMORY0                  = 0xA025,
  ZSIMEMORYMANAGER_ZSIALLOCATEMORY0                = 0xA026,
  ZSIMEMORYMANAGER_ZSIALLOCATEMORY1                = 0xA027,

  ZSISERIALIZER_ZSISERIALIZEUINT80                 = 0xA030,
  ZSISERIALIZER_ZSISERIALIZEUINT160                = 0xA031,
  ZSISERIALIZER_ZSISERIALIZEUINT320                = 0xA032,
  ZSISERIALIZER_ZSISERIALIZEUINT640                = 0xA033,
  ZSISERIALIZER_ZSISERIALIZEDATA0                  = 0xA034,
  ZSISERIALIZER_ZSIDESERIALIZEUINT80               = 0xA035,
  ZSISERIALIZER_ZSIDESERIALIZEUINT160              = 0xA036,
  ZSISERIALIZER_ZSIDESERIALIZEUINT320              = 0xA037,
  ZSISERIALIZER_ZSIDESERIALIZEUINT640              = 0xA038,
  ZSISERIALIZER_ZSIDESERIALIZEDATA0                = 0xA039,

  ZSIMEDIUM_ZSIMEDIUMLINKSAFETYTIMERFIRED0         = 0xA040,
  ZSIMEDIUM_ZSIMEDIUMRXCALLBACK0                   = 0xA041,

  ZSIAPSSERIALIZATION_ZSIDESERIALIZEAPSDATAREQ0    = 0xA050,
  ZSIKESERIALIZATION_ZSEECCGENERATEKEY             = 0xA051,
  ZSIKESERIALIZATION_ZSEECCKEYBITGENERATE          = 0xA052,
  ZSIKESERIALIZATION_SSPBCBHASH                    = 0xA053,

  ZSIINIT_ZSIINITRESETNETWORKCONF0                 = 0xA060
} ZSI_DbgCodeId_t;

#endif /* ZSIDBG_H */
