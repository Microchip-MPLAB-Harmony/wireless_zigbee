/** \file

$Id: N_GreenPower_Core_Init.h 7927 2013-07-24 09:24:54Z gertjan.maas@philips.com $

Copyright (c) 2011 Koninklijke Philips N.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Koninklijke Philips N.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Koninklijke Philips N.V.
*/

#ifndef N_GREENPOWER_CORE_INIT_H
#define N_GREENPOWER_CORE_INIT_H

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
***************************************************************************************************//**************************************************************************//**
  \brief Initializes the component.

  \return None
 ******************************************************************************/

void N_GreenPower_Core_Init(void);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_GREENPOWER_CORE_INIT_H
