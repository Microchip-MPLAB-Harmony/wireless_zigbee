/*********************************************************************************************/
/**
\file  

\brief 

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2013-2014, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal


$Id: S_Nv_Stack_Ids.h 24615 2013-02-27 05:14:24Z arazinkov $

***************************************************************************************************/

#ifndef S_NV_STACK_IDS_H
#define S_NV_STACK_IDS_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "S_Nv.h"

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/

/**
    This file defines the flash storage ids used by the ZLLPlatform.
    NOTE: Future additions to the ZLLPlatform should use IDs from the range
    S_NV_STACK_RANGE_MIN..S_NV_STACK_RANGE_MAX, defined in \ref wlPdsMemIds.h.
    The two items defined here are legacy and should not be changed.
*/
#define FREE_RANGES_STORAGE_ID                      (S_NV_PLATFORM_RANGE1_MIN + 1u) // addressManager
#define FACTORY_NEW_STORAGE_ID                      (S_NV_PLATFORM_RANGE1_MIN + 2u) // device info
#define TC_MODE_STORAGE_ID                          (S_NV_PLATFORM_RANGE1_MIN + 3u) // device info

#endif //S_NV_STACK_IDS_H
