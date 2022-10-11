/*******************************************************************************
  OTAU Service Source File

  Company:
    Microchip Technology Inc.

  File Name:
    otauService.c

  Summary:
    This file contains the OTAU interface declaration.

  Description:
    This file contains the OTAU interface declaration.
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

/*******************************************************************************
                    Includes section
*******************************************************************************/
#include <otauService.h>
#include <zclOTAUCluster.h>
#include <resetReason.h>
#include <zclOtauManager.h>
#include <private/csSIB.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
#ifdef OTAU_CLIENT
static void otauClusterIndication(ZCL_OtauAction_t action);
#endif // OTAU_CLIENT

/*******************************************************************************
                    Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Starts Over-the-air update server service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauServer(void)
{
#ifdef OTAU_SERVER
  ZCL_OtauInitParams_t initParam;
  uint32_t fileVersion;
  CS_ReadParameter(CS_ZCL_OTAU_FILE_VERSION_ID, &fileVersion);
  initParam.clusterSide = ZCL_SERVER_CLUSTER_TYPE;
  initParam.firmwareVersion.versionId = fileVersion;
  initParam.otauEndpoint = APP_SRC_ENDPOINT_ID;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, NULL))
  {
    /* failed to start otau service. Check for param validity */
  }
#endif // OTAU_SERVER
}

#ifdef OTAU_CLIENT

/**************************************************************************//**
\brief Starts Over-the-air update client service.

\param[out] - pointer to otau cluster
******************************************************************************/
void startOtauClient(void)
{
  uint32_t fileVersion;
  ZCL_OtauInitParams_t initParam;
  CS_ReadParameter(CS_ZCL_OTAU_FILE_VERSION_ID, &fileVersion);
  initParam.clusterSide = ZCL_CLIENT_CLUSTER_TYPE;
  initParam.firmwareVersion.versionId = fileVersion;
  initParam.otauEndpoint = APP_SRC_ENDPOINT_ID;
  initParam.profileId = APP_PROFILE_ID;
  if (ZCL_SUCCESS_STATUS != ZCL_StartOtauService(&initParam, otauClusterIndication))
  {
    /* failed to start otau service. Check for param validity */
  }
}

/***************************************************************************//**
\brief Get indication about all otau cluster actions.

\param[in] action - current action
*******************************************************************************/
static void otauClusterIndication(ZCL_OtauAction_t action)
{
  if (OTAU_DEVICE_SHALL_CHANGE_IMAGE == action) // client is ready to change image
  {
    /*Context switch to 2 sec for any pending tasks( PDS updates )??*/
    otauStartGenericTimer(OTAU_CONTEXT_BREAK_QUICK_TIMEOUT * 100,HAL_WarmReset);
  }
}
#endif // OTAU_CLIENT

// eof otauService.c
