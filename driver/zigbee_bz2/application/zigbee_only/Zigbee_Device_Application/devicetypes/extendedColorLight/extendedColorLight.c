/*******************************************************************************
  Extended Color Light Source File

  Company:
    Microchip Technology Inc.

  File Name:
   extendedColorLight.c

  Summary:
    This file contains the Extended Color Light interface.

  Description:
    This file contains the Extended Color Light interface.
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
* BEEN ADVISED OextendedColorLight.hF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                             Includes section
******************************************************************************/
#include <eclClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <eclIdentifyCluster.h>
#include <eclOnOffCluster.h>
#include <eclLevelControlCluster.h>
#include <eclColorControlCluster.h>
#include <eclGroupsCluster.h>
#include <eclScenesCluster.h>
#include <eclCommissioningCluster.h>
#include <z3Device.h>
#include <zclSecurityManager.h>
#include <uartManager.h>
#include <console.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>
#include <haClusters.h>
#include <otauService.h>
#include <commandManager.h>

/******************************************************************************
                   type(s) section
******************************************************************************/
typedef enum _thBoundClustersInEzMode_t
{
  ON_OFF_CLUSTER_BOUND = 1,
  LEVEL_CONTROL_CLUSTER_BOUND = (1 << 1)
}thBoundClustersInEzMode_t;

typedef enum _ReportingState_t
{
  CONFIG_REPORT_INIT_STATE = 0,
  ON_OFF_REPORTING_CONFIGURED,
  CONFIGURE_REPORTING_COMPLETED
}ReportingState_t;

/*******************************************************************************
                    Static functions section
*******************************************************************************/
//static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload);

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void eclConfigureReportingResp(ZCL_Notify_t *ntfy);
//static void handleDlConfigReporting(void);
static void eclFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId);

/******************************************************************************
                    Local variables section
******************************************************************************/

static AppEpFindingAnbdBindingRole_t eclEpFindingBindingRoleOrder[3] = {FINDING_BINDING_TARGET, FINDING_BINDING_INITIATOR, FINDING_BINDING_NONE};

static ZCL_DeviceEndpoint_t eclEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_EXTENDED_COLOR_LIGHT,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_DIMMABLE_LIGHT_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(eclServerClusterIds),
    .AppInClustersList   = eclServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(eclClientClusterIds),
    .AppOutClustersList  = eclClientClusterIds,
  },
  .serverCluster = eclServerClusters,
  .clientCluster = eclClientClusters,
};

static ClusterId_t eclClientClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
};

static ClusterId_t eclServerClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID  
};

static AppBindReq_t eclBindReq =
{
  .srcEndpoint       = APP_ENDPOINT_EXTENDED_COLOR_LIGHT,
  .remoteServersCnt  = ARRAY_SIZE(eclClientClusterToBindIds),
  .remoteClientsCnt  = ARRAY_SIZE(eclServerClusterToBindIds),
  .groupId           = 0xffff, 
  .remoteServers     = eclClientClusterToBindIds,
  .remoteClients     = eclServerClusterToBindIds,
  .callback          = eclFindingBindingFinishedForACluster,
  .fbRoleOrder       = eclEpFindingBindingRoleOrder
};

static IdentifySubscriber_t subcriber = NULL;


/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void eclDeviceInit(void)
{
  APP_RegisterEndpoint(&eclEndpoint, &eclBindReq);

  /* Subscribe the Commissioning update command for Target devices */
  identifySubscribe(&subcriber);
  
  commandManagerInit();

  basicClusterInit();
  identifyClusterInit();
  onOffClusterInit();
  levelControlClusterInit();
  groupsClusterInit();
  scenesClusterInit();
  commissioningClusterInit();

  if (PDS_IsAbleToRestore(APP_LIGHT_DATA_MEM_ID))
    PDS_Restore(APP_LIGHT_DATA_MEM_ID);
  
  if (PDS_IsAbleToRestore(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID))
    PDS_Restore(APP_LIGHT_SCENE_CLUSTER_SERVER_ATTR_MEM_ID);
  
  if (PDS_IsAbleToRestore(APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID))
    PDS_Restore(APP_LIGHT_ONOFF_CLUSTER_SERVER_ATTR_MEM_ID);
  
  if (PDS_IsAbleToRestore(APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID))
    PDS_Restore(APP_LIGHT_LEVEL_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID);
  
  if (PDS_IsAbleToRestore(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID))
    PDS_Restore(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID);
}

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void eclDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
      }
#ifdef OTAU_CLIENT
      startOtauClient(&eclClientClusters[ECL_CLIENT_CLUSTERS_COUNT - 1]);
#endif
      break;
    case DEVICE_ACTIVE_IDLE_STATE:
    default:
      break;
  }
}
/*******************************************************************************
\brief callback called on the finishing of binding of one cluster
********************************************************************************/            
static void eclFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId)
{
  ZCL_Cluster_t *serverCluster;
  switch(clusterId)
  {
    case ONOFF_CLUSTER_ID:
      serverCluster = ZCL_GetCluster(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
      if (serverCluster)
        sendConfigureReportingToNotify(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, APP_ENDPOINT_DIMMABLE_LIGHT, ONOFF_CLUSTER_ID,
                                     ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, ONOFF_VAL_MAX_REPORT_PERIOD, 
                                     eclConfigureReportingResp);
      break;
    case LEVEL_CONTROL_CLUSTER_ID:
       serverCluster = ZCL_GetCluster(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, LEVEL_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
       if (serverCluster)
         sendConfigureReportingToNotify(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, APP_ENDPOINT_COMBINED_INTERFACE, 
                                      LEVEL_CONTROL_CLUSTER_ID,ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, 
                                      LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD, eclConfigureReportingResp);
       break;
       
    case COLOR_CONTROL_CLUSTER_ID:
      break;
       
  }
   
}

/**************************************************************************//**
\brief EZ-Mode done callback

\returns function which is called by EZ-Mode manager when it is done
******************************************************************************/
void appEzModeDone(void)
{}

/**************************************************************************//**
\brief Update Commissioning State received callback

\param[in] addressing - pointer to addressing information;
\param[in] payload - data pointer
******************************************************************************/
/*
static void updateCommissioningStateCb(ZCL_Addressing_t *addressing, ZCL_UpdateCommissioningState_t *payload)
{
  handleDlConfigReporting();
  ZCL_StartReporting();
  (void)addressing, (void)payload;
}
*/

/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void eclConfigureReportingResp(ZCL_Notify_t *ntfy)
{
  ZCL_StartReporting();
  (void)ntfy;
}

/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer. For details go to
            ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer. For details go to
            ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
// eof dimmableLight.c