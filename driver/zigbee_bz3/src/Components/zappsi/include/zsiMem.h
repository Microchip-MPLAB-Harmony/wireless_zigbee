/*******************************************************************************
  ZAppSI Memory Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiMem.h

  Summary:
    This file contains the ZAppSI memory interface.

  Description:
    This file contains the ZAppSI memory interface.
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


#ifndef _ZSIMEM_H_
#define _ZSIMEM_H_

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>
#include <zsiTaskManager.h>
#include <zsiMemoryManager.h>
#include <zsiSerialController.h>
#include <zsiDriver.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct _ZsiMem_t
{
  ZsiTaskManager_t      taskManager;
  ZsiMemoryManager_t    memoryManager;
  ZsiSerialController_t serialController;
  ZsiDriver_t           driver;
} ZsiMem_t;

/*****************************************************************************
                    External variables section
******************************************************************************/
extern ZsiMem_t zsiMem;

/******************************************************************************
                    Global functions section
******************************************************************************/
/******************************************************************************
  \brief ZAppSI task manager component getter routine.

  \return Pointer to ZAppSI task manager component.
 ******************************************************************************/
INLINE ZsiTaskManager_t *zsiTaskManager(void)
{
  return &zsiMem.taskManager;
}

/******************************************************************************
  \brief ZAppSI memory manager component getter routine.

  \return Pointer to ZAppSI memory manager component.
 ******************************************************************************/
INLINE ZsiMemoryManager_t *zsiMemoryManager(void)
{
  return &zsiMem.memoryManager;
}

/******************************************************************************
  \brief ZAppSI serial controller component getter routine.

  \return Pointer to ZAppSI serial controller component.
 ******************************************************************************/
INLINE ZsiSerialController_t *zsiSerial(void)
{
  return &zsiMem.serialController;
}

/******************************************************************************
  \brief ZAppSI driver component getter routine.

  \return Pointer to ZAppSI driver component.
 ******************************************************************************/
INLINE ZsiDriver_t *zsiDriver(void)
{
  return &zsiMem.driver;
}

#endif /* _ZSIMEM_H_ */
