/*********************************************************************************************/
/**
\file  

\brief D_XNv Initialization Interface

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2018, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal

$Id: D_XNv_Init.h 24615 2013-02-27 05:14:24Z mahendranp $

***************************************************************************************************/

#ifndef D_XNV_INIT_H
#define D_XNV_INIT_H

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


/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************//**************************************************************************/
/**
  \brief Initializes the component.

  \return None
 *****************************************************************************
*/

void D_XNv_Init(void);

/**************************************************************************/
/**
  \brief D_Xnv Integrity check function.

  \return None
 *****************************************************************************
*/
void D_XNv_SetSystemIntegrityCheckFunction(void (*pf)(void));

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // D_XNV_INIT_H
