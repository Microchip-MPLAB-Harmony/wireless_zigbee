/*******************************************************************************
  Control Bridge device Color Control cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cbColorControlCluster.c

  Summary:
    This file contains Control Bridge device Color Control cluster interface.

  Description:
    This file contains Control Bridge device Color Control cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CONTROL_BRIDGE)

/******************************************************************************
                    Includes
******************************************************************************/
#include <zcl.h>
#include <clusters.h>
#include <haClusters.h>
#include <zclCommandManager.h>
#include <zclZllColorControlCluster.h>
#include <cbColorControlCluster.h>
#include <cbClusters.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ColorControlClusterClientAttributes_t cbColorControlClusterClientAttributes =
{
  ZCL_DEFINE_COLOR_CONTROL_CLIENT_CLUSTER_ATTRIBUTES()
};

PROGMEM_DECLARE(ZCL_ColorControlClusterCommands_t cbColorControlCommands) =
{
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_COLOR_SCENE_CONTROLLER()
};

/******************************************************************************
                    Local variables
******************************************************************************/

/******************************************************************************
                    Prototypes
******************************************************************************/
static void cbColorControlReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);

/******************************************************************************
                    Implementations
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void cbColorControlClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CONTROL_BRIDGE, COLOR_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_ReportInd = cbColorControlReportInd;
  
  cbColorControlClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void cbColorControlReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  uint8_t *report = reportPayload;
  ZCL_Report_t *attrReport;
  ZCL_DataTypeDescriptor_t descr;
  uint16_t value;

  while (report /* current report */ < (reportPayload + reportLength) /* end */)
  {
    attrReport = (ZCL_Report_t *) report;
    ZCL_GetDataTypeDescriptor(attrReport->type, NULL, &descr);
    value = 0u;
    memcpy(&value, attrReport->value, descr.length);
    appSnprintf("<-Color Control Attr (0x%x) Report: t = %d\r\n", (unsigned)attrReport->id, value);
    report += (sizeof(ZCL_AttributeId_t) /* id */
               + sizeof(uint8_t) /* type */
               + descr.length /* size */);
  }

  (void)addressing, (void)reportLength;
}

#endif // APP_DEVICE_TYPE_CONTROL_BRIDGE

// eof cbColorControlCluster.c
