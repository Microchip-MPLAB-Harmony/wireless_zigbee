/*********************************************************************************************/
/**
\file  

\brief External Nv Initialization Interface

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2018, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal

$Id: S_XNv_Init.h 24615 2013-02-27 05:14:24Z mahendranp $

***************************************************************************************************/

#ifndef S_XNV_INIT_H
#define S_XNV_INIT_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Task/include/N_Task.h"
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


/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/
/**************************************************************************//**
  \brief Initializes the external flash service for early access.
         Note: It is not required to call this function if the application does not require early access
         to external Nv. Note that the S_XNv component is fully functional after calling S_XNv_EarlyInit(),
         but until S_XNv_Init() is called, chances are much higher that the component blocks when a sector
         becomes full. Only after S_XNv_Init() is called, compacting the sector is decoupled as much as
         possible.

  \return None.
 *****************************************************************************/
void S_XNv_EarlyInit(void);

/**************************************************************************//**
  \brief Initializes the rest of the component (timers and task). Note that N_Task and N_Timer must be
        initialised first.

  \return None.
 *****************************************************************************/
void S_XNv_Init(void);

/**************************************************************************//**
  \brief The event handler for the component's task.

  \return handler status.
 *****************************************************************************/
bool S_XNv_EventHandler(N_Task_Event_t evt);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // S_XNV_INIT_H
