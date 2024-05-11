/** \file

$Id: N_TrustCenter_Init.h 9279 2014-02-11 13:27:30Z gertjan.maas@philips.com $

Copyright (c) 2011 Koninklijke Philips N.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Koninklijke Philips N.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Koninklijke Philips N.V.
*/

#ifndef N_TRUSTCENTER_INIT_H
#define N_TRUSTCENTER_INIT_H

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

/** Initializes the component.
*/
void N_TrustCenter_Init(void);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_TRUSTCENTER_INIT_H
