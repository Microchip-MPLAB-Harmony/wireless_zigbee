/*******************************************************************************
  Trust Center Swapout header file

  Company:
    Microchip Technology Inc.

  File Name:
    app_tcSwapout.h

  Summary:
    This file contains the Trust center swapout interface declaration.

  Description:
    This file contains the Trust center swapout interface declaration.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#ifndef APP_TC_SWAPOUT_H
#define APP_TC_SWAPOUT_H

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                           Includes section
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <definitions.h>

/******************************************************************************
                           Definitions section
******************************************************************************/
#ifdef SYS_BACKUP
#undef SYS_BACKUP
#define SYS_BACKUP APP_CommenceTCBackup()
#endif

/******************************************************************************
                           Types section
 ******************************************************************************/
typedef int16_t TC_BackupId_t;

/******************************************************************************
                           Functions prototypes section
 ******************************************************************************/
/**************************************************************************//**
\brief Trust center backup initialization.

\param - None.

\return - None.
******************************************************************************/
void APP_InitTCBackup(void);

/**************************************************************************//**
\brief Start the backup process. This should be called during idle task.

\param - None.

\return - None.
******************************************************************************/
void APP_CommenceTCBackup(void);

/**************************************************************************//**
\brief Restore the backup data to the device. 

\param - None.

\return - None.
******************************************************************************/
void APP_CommenceTCRestore(void);

/**************************************************************************//**
\brief Adds new entry into the backup queue.

\param[in] backupId - Offset id of the backup record.

\return True - If the operation is successful.
        False - Otherwise.
******************************************************************************/
bool APP_AddTCBackupEntry(TC_BackupId_t backupId);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif // APP_TC_SWAPOUT_H
// eof app_tcSwapout.h