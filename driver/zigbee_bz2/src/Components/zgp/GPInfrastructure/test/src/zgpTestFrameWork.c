/*******************************************************************************
  Green power cluster test framework Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpTestFrameWork.c

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

#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#ifdef ENABLE_ZGP_TEST_FRAMEWORK

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zclGreenPowerCluster.h>
#include <zgp/GPInfrastructure/highZgp/include/zgpClusterStructure.h>
#include <zgp/GPInfrastructure/highZgp/include/private/zgpClusterGeneric.h>
#include <zgp/GPInfrastructure/highZgp/include/private/zgpClusterClient.h>
#include <zgp/GPInfrastructure/highZgp/include/zgpCluster.h>
#include <zgp/GPInfrastructure/lowZgp/include/zgpLowNvmTable.h>
#include <zgp/GPInfrastructure/lowZgp/include/private/zgpNvmTable.h>
#include <zgp/include/GPinfrastructure/test/include/zgpTestFrameWork.h>
#include <app_zigbee/zigbee_console/console.h>
/******************************************************************************
                    Define section
******************************************************************************/

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum _ZgpTestFrameTableOperationType_t
{
  ZGP_FRAMEWORK_TABLE_READ = 0x1,
  ZGP_FRAMEWORK_TABLE_WRITE = 0x2,
  ZGP_FRAMEWORK_TABLE_DELETE = 0x3,
  ZGP_FRAMEWORK_FRAMECOUNTER_READ = 0x4,
  ZGP_FRAMEWORK_FRAMECOUNTER_WRITE = 0x5,
} zgpTestFrameTableOperationType_t;

typedef enum _ZgpTestFrameBankInfo_t
{
  ZGP_FRAMEWORK_BANK_CONFIG = 0x1,
  ZGP_FRAMEWORK_BANK_STATUS = 0x2,
} zgpTestFrameBankInfo_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/


/******************************************************************************
                    Internal variables
******************************************************************************/

/******************************************************************************
                    Global variables
******************************************************************************/

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Processes get request command

\param[in] args - array of command arguments
******************************************************************************/
void processGetRequestCmd(const ScanValue_t *args)
{
  switch (args[0].uint8)
  {
    case ZGP_FRAMEWORK_BANK_CONFIG:
    {
      appSnprintf("zgpBankConfig = %d %d %d\r\n", ZGP_MAPPING_TABLE_BANK_COUNT, ZGP_MAX_ENTRIES_PER_BANK, ZGP_TOTAL_TABLE_ENTRIES);
    }
    break;
    case ZGP_FRAMEWORK_BANK_STATUS:
    {
      zgpBankInfo_t *bankInfo;

      bankInfo = zgpTableGetBankInfo();
      appSnprintf("zgpBankInfo = %d %d %d %d %d %d\r\n", bankInfo->noOfProxyTableEntries, bankInfo->noOfLogicalSinkTableEntries, \
                  bankInfo->noOfPhysicalSinkTableEntries, bankInfo->bankStatus[0][0], bankInfo->bankStatus[1][0], bankInfo->bankStatus[2][0]);
    }
    break;
  }
}

/**************************************************************************//**
\brief Processes get request command

\param[in] args - array of command arguments
******************************************************************************/
void processTableOperationCmd(const ScanValue_t *args)
{
  ZGP_GpdId_t gpdId;
  uint8_t endPoint;
  uint32_t frameCounterToBeUpdated;
  ZGP_TableOperationField_t operationField = {.nonEmptyIndexForRead = args[5].uint8};

  gpdId.gpdIeeeAddr = args[3].uint32;
  operationField.appId = args[2].uint8;
  operationField.entryType = args[1].uint8;
  operationField.commMode = args[6].uint8;
  endPoint = args[4].uint8;
  frameCounterToBeUpdated = args[7].uint32;

  switch (args[0].uint8)
  {
    case ZGP_FRAMEWORK_TABLE_READ:
    {
      ZGP_ReadOperationStatus_t readStatus;
      ZGP_ProxyTableEntry_t tableEntry;

      readStatus = ZGPL_ReadTableEntryFromNvm((void *)&tableEntry, operationField,\
                                                       &gpdId, endPoint);
 
      if (ENTRY_NOT_AVAILABLE == readStatus)
      {
        appSnprintf("ZgpTable Read Failed\r\n");
      }
      else
      {
        uint32_t frameCounter;
#if APP_ZGP_DEVICE_TYPE == APP_ZGP_DEVICE_TYPE_COMBO_BASIC
        if (ZGP_SINK_ENTRY == operationField.entryType)
        {
          frameCounter = ((ZGP_SinkTableEntry_t *)&tableEntry)->tableGenericInfo.gpdSecurityFrameCounter;
        }
        else
#endif
        {
          frameCounter = ((ZGP_ProxyTableEntry_t *)&tableEntry)->tableGenericInfo.gpdSecurityFrameCounter;
        }
        appSnprintf("ZgpTable Read Success: %d %d\r\n", readStatus, frameCounter);
      }
    }
    break;
    case ZGP_FRAMEWORK_TABLE_WRITE:
    {
      ZGP_ProxyTableEntry_t tableEntry;
      ZGP_TableUpdateAction_t action = UPDATE_ENTRY;

      memset(&tableEntry, (gpdId.gpdIeeeAddr & 0xFF), sizeof(tableEntry));
#if APP_ZGP_DEVICE_TYPE == APP_ZGP_DEVICE_TYPE_COMBO_BASIC
      if (ZGP_SINK_ENTRY == operationField.entryType)
      {
        ((ZGP_SinkTableEntry_t *)&tableEntry)->options.appId = operationField.appId;
        ((ZGP_SinkTableEntry_t *)&tableEntry)->options.communicationMode = operationField.commMode;
        memcpy (&((ZGP_SinkTableEntry_t *)&tableEntry)->tableGenericInfo.gpdId, &gpdId, sizeof(ZGP_GpdId_t));
        ((ZGP_SinkTableEntry_t *)&tableEntry)->tableGenericInfo.gpdSecurityFrameCounter = frameCounterToBeUpdated;
      }
      else
#endif
      {
        ((ZGP_ProxyTableEntry_t *)&tableEntry)->options.appId = operationField.appId;
        memcpy (&((ZGP_ProxyTableEntry_t *)&tableEntry)->tableGenericInfo.gpdId, &gpdId, sizeof(ZGP_GpdId_t));
        ((ZGP_ProxyTableEntry_t *)&tableEntry)->tableGenericInfo.gpdSecurityFrameCounter = frameCounterToBeUpdated;
      }

      if (ZGPL_AddOrUpdateTableEntryOnNvm((void *)&tableEntry, action, operationField.entryType))
      {
        appSnprintf("ZgpTable Write Success\r\n");
      }
      else
      {
        appSnprintf("ZgpTable Write Failed\r\n");
      }
    }
    break;
    case ZGP_FRAMEWORK_TABLE_DELETE:
    {
      if (ZGPL_DeleteTableEntryFromNvm(operationField, &gpdId, endPoint))
      {
        appSnprintf("ZgpTable Delete Success\r\n");
      }
      else
      {
        appSnprintf("ZgpTable Delete Failed\r\n");
      }
    }
    break;
    case ZGP_FRAMEWORK_FRAMECOUNTER_READ:
    case ZGP_FRAMEWORK_FRAMECOUNTER_WRITE:
    {

      if (ZGP_FRAMEWORK_FRAMECOUNTER_READ == args[0].uint8)
      {
        if (ZGPL_FrameCounterReadorUpdateOnNvm(&frameCounterToBeUpdated, operationField,\
                                        &gpdId, endPoint, false))
        {
          appSnprintf("ZgpFc Read Success: %d\r\n", frameCounterToBeUpdated);
        }
        else
        {
          appSnprintf("ZgpFc Read Failed\r\n");
        }
      }
      else
      {
        if (ZGPL_FrameCounterReadorUpdateOnNvm(&frameCounterToBeUpdated, operationField,\
                                        &gpdId, endPoint, true))
        {
          appSnprintf("ZgpFc Update Success\r\n");
        }
        else
        {
          appSnprintf("ZgpFc Update Failed\r\n");
        }
      }
        
    }
    break;
  }
}

#endif // ENABLE_ZGP_TEST_FRAMEWORK
#endif // APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#endif // _GREENPOWER_SUPPORT_

// eof zgpTestFrameWork.c
