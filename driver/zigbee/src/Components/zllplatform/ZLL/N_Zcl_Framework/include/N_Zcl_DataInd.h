/*******************************************************************************
  ZLL ZCL Data Indication Header File

  Company:
    Microchip Technology Inc.

  File Name:
    N_Zcl_DataInd.h

  Summary:
    This file contains the ZLL ZCL Data Indication functions.

  Description:
    ZCL data indication header file to register/subscribe for callback 
    and the associated structure.
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


#ifndef N_ZCLDATAIND_H
#define N_ZCLDATAIND_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Types/include/N_Types.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/
typedef struct N_Zcl_DataInd_Callback_t
{
  /** Pass the incoming data
  *   \param dataInd The incoming data structure
  */
  void (*DataInd)(APS_DataInd_t* dataInd);

  /** Guard to ensure the initializer contains all functions. Must be -1.
  */
  int8_t endOfList;
} N_Zcl_DataInd_Callback_t;

/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/
/**************************************************************************//**
  \brief Subscribe to this component's callbacks.
	
  \param endpoint ZigBee end-point to subscribe to.
  \param pCallback Pointer to a callback structure filled with functions to be called,
                     use NULL for callbacks not of interrest.

  \return None
 *****************************************************************************/
void N_Zcl_DataInd_Subscribe(uint8_t endpoint, const N_Zcl_DataInd_Callback_t* pCallback);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_ZCLDATAIND_H
