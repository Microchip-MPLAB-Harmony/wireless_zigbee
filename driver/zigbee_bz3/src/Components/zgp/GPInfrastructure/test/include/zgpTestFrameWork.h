/*******************************************************************************
  Green power cluster test framework Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpTestFrameWork.h

  Summary:
    This file contains green power cluster test framework interface.

  Description:
    This file contains green power cluster test framework interface..
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

#ifndef ZGPTESTFRAMEWORK_H
#define ZGPTESTFRAMEWORK_H

#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#ifdef ENABLE_ZGP_TEST_FRAMEWORK
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zclGreenPowerCluster.h>
#include <zgp/GPInfrastructure/lowZgp/include/zgpLowNvmTable.h>
#include <zgp/GPInfrastructure/lowZgp/include/private/zgpDstub.h>
#include <app_zigbee/zigbee_console/console.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define ZGP_TEST_FRAMEWORK_COMMANDS \
  {"getReq", "d", processGetRequestCmd, "-> reading parameters <id>\r\n"},\
  {"tableOperation", "dddddddd", processTableOperationCmd, "<operaType> <tableType> <appId> <gpdId> <ep> <index> <commMode> <frameCounter>\r\n"},\

/******************************************************************************
                    Type section
******************************************************************************/

/******************************************************************************
                    Externals
******************************************************************************/

/******************************************************************************
                    Prototypes
******************************************************************************/
/**************************************************************************//**
\brief Processes get request command

\param[in] args - array of command arguments
******************************************************************************/
void processGetRequestCmd(const ScanValue_t *args);

/**************************************************************************//**
\brief Processes get request command

\param[in] args - array of command arguments
******************************************************************************/
void processTableOperationCmd(const ScanValue_t *args);

#endif // ENABLE_ZGP_TEST_FRAMEWORK
#endif // APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#endif // _GREENPOWER_SUPPORT_
#endif // ZGPTESTFRAMEWORK_H

// eof zgpTestFrameWork.h
