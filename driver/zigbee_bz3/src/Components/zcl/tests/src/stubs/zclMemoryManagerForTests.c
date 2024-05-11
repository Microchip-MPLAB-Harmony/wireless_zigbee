/*******************************************************************************
  ZCL MemoryManager test file

  Company:
    Microchip Technology Inc.

  File Name:
    zclMamoryManagerForTests.c

  Summary:
    File zclMemoryManager with tests extensions.

  Description:
    File zclMemoryManager with tests extensions.
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


/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclUnitTesting.h>
#include <zclMemoryManager.c>
#include <sysAssert.h>

/******************************************************************************
                    Implementation section
******************************************************************************/
/*************************************************************************//**
\brief Releases all memory buffers. Only for testing purposes.
*****************************************************************************/
void ZCL_ReleaseAllMemBuffers(void)
{
  uint8_t bufferAmount;
  ZclMmBufferDescriptor_t *descriptor, *iter;

  CS_ReadParameter(CS_ZCL_MEMORY_BUFFERS_AMOUNT_ID, (void *)&bufferAmount);
  CS_GetMemory(CS_ZCL_BUFFER_DESCRIPTORS_ID, (void *)&descriptor);
  iter = descriptor;

  while (iter < (descriptor + bufferAmount))
  {
    iter->type = ZCL_UNKNOWN_BUFFER;
    iter->link = NULL;
    iter->timeout = 0;
    iter++;
  }
}

/*************************************************************************//**
\brief Gets next mem descr. Only for testing purposes.
*****************************************************************************/
ZclMmBufferDescriptor_t* ZCL_GetNextBufferDescriptor(ZclMmBufferDescriptor_t *descr)
{
  uint8_t bufferAmount;
  bool bool_exp;
  ZclMmBufferDescriptor_t *descriptor, *iter;

  CS_ReadParameter(CS_ZCL_MEMORY_BUFFERS_AMOUNT_ID, (void *)&bufferAmount);
  CS_GetMemory(CS_ZCL_BUFFER_DESCRIPTORS_ID, (void *)&descriptor);
  bool_exp = (((descr >= descriptor) && (descr < descriptor + bufferAmount)) || (NULL == descr));

  if (false == bool_exp)
  {
    SYS_E_ASSERT_ERROR(false, ZCLMEMORYMANAGER_ZCLMMGETNEXTBUSYDESCRIPTOR_0);
    return NULL;
  }      
  if ((descr < descriptor) && (descr >= descriptor + bufferAmount))
    return NULL;

  if (descr)
    iter = descr + 1;
  else
    iter = descriptor;

  if  (iter < (descriptor + bufferAmount))
    return iter;

  return NULL;
}

// eof zclMamoryManagerForTests.c
