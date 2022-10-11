/*******************************************************************************
  Zigbee device object configuration Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoConfig.h

  Summary:
    This file contains the ZDO Constant definition header file.

  Description:
    This file contains the ZDO Constant definition header file.
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

#if !defined _ZDO_CONFIG_H
#define _ZDO_CONFIG_H

/******************************************************************************
                             Definitions section
 ******************************************************************************/
#if defined _CERTIFICATION_
/* It should be 1U on certification. See log from Golden Units on 2.4GHz. */
#define ZDP_BIND_APS_ACK 1U
#else
/** The flag requires APS acks for ZDP Bind request and response.*/
#define ZDP_BIND_APS_ACK 0U
#endif

#endif /* _ZDO_CONFIG_H */
/** eof zdoConfig.h */
