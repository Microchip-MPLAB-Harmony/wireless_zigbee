/*******************************************************************************
  Zigbee Library ${REL_VER} Release

  Company:
    Microchip Technology Inc.

  File Name:
    zigbee.c

  Summary:
    Zigbee Library 3.0

  Description:
    Provides Initialization, Processing and ISR handler of zigbee library,
    Simple API functions to get/set the key zigbee parameters from/to the
    zigbee library data structures
*******************************************************************************/

/*******************************************************************************
Copyright (c)  ${REL_YEAR} released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/
//#include "zigbee/zigbee.h"
#include "definitions.h" 

/*----------------------------------------------------------------------------
 *   prototypes
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *     Global Variables
 *----------------------------------------------------------------------------*/

/* Test Flag  */
volatile uint8_t test_done_zigbee = 0;

/*============================================================================
void zigbee_init(void)
------------------------------------------------------------------------------
Purpose: Initialization of zigbee library.
Input  : none
Output : none
Notes  :
============================================================================*/
/*void zigbee_init(void)
{

}*/
