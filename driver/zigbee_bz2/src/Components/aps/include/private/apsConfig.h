/*******************************************************************************
  APS Config Header File

  Company
    Microchip Technology Inc.

  File Name
    apsConfig.h

  Summary
    Configuration constants and definitions of APS layer.

  Description
    This header file defines the configuration constants and definitions of APS layer.
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

#if !defined _APS_CONFIG_H
#define _APS_CONFIG_H

/******************************************************************************
                             Definitions section
 ******************************************************************************/
/* Rejection table timeouts counted in 500ms intervals.
 * So we can use narrow data types. */
#define APS_DUPLICATE_REJECTION_INTERVAL 512U

#ifdef _APS_FRAGMENTATION_
  #if defined _CERTIFICATION_
    #define APS_INTERFRAME_DELAY (10*HAL_APPTIMERINTERVAL)
  #else
    #define APS_INTERFRAME_DELAY (HAL_APPTIMERINTERVAL)
  #endif
#endif

/* Random delay for retransmission to decrease amount of collisions */
#define RETRANSMISSION_RANDOM_DELAY_RANGE 0x1ff

#define RETRANSMISSION_DELAY_WITH_NO_PHY_ACK 1000U

#endif /* _APS_CONFIG_H */
/** eof apsConfig.h */

