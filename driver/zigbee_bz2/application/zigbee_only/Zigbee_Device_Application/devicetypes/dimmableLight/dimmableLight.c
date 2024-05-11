/*******************************************************************************
  Dimmable Light Source File

  Company:
    Microchip Technology Inc.

  File Name:
   dimmableLight.c

  Summary:
    This file contains the Dimmable Light interface.

  Description:
    This file contains the Dimmable Light interface.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                             Includes section
******************************************************************************/
#include <dlClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <dlIdentifyCluster.h>
#include <dlOnOffCluster.h>
#include <dlLevelControlCluster.h>
#include <dlGroupsCluster.h>
#include <dlScenesCluster.h>
#include <z3Device.h>
#include <zclSecurityManager.h>
#include <console.h>
#include <pdsDataServer.h>
#include <ezModeManager.h>
#include <haClusters.h>
#include <otauService.h>
#include <zclCommandManager.h>
#include <dimmableLight.h>


/******************************************************************************
                   type(s) section
******************************************************************************/

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void dlFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t id);

/******************************************************************************
                    Local variables section
******************************************************************************/
static AppEpFindingAnbdBindingRole_t dlEpFindingBindingRoleOrder[3] = {FINDING_BINDING_TARGET, FINDING_BINDING_INITIATOR, FINDING_BINDING_NONE};

static ZCL_DeviceEndpoint_t dlEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_DIMMABLE_LIGHT,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = HA_DIMMABLE_LIGHT_DEVICE_ID,
    .AppDeviceVersion    = 0x1,    
    .AppInClustersCount  = ARRAY_SIZE(dlServerClusterIds),
    .AppInClustersList   = dlServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(dlClientClusterIds),
    .AppOutClustersList  = dlClientClusterIds,
  },
  .serverCluster = dlServerClusters,
  .clientCluster = dlClientClusters,
};

static ClusterId_t dlClientClusterToBindIds[] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
};

static ClusterId_t dlServerClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
};

static AppBindReq_t dlBindReq =
{
  .srcEndpoint       = APP_ENDPOINT_DIMMABLE_LIGHT,
  .remoteServersCnt  = ARRAY_SIZE(dlClientClusterToBindIds),
  .remoteClientsCnt  = ARRAY_SIZE(dlServerClusterToBindIds),
  .groupId           = 0xffff, 
  .remoteServers     = dlClientClusterToBindIds,
  .remoteClients     = dlServerClusterToBindIds,
  .callback          = dlFindingBindingFinishedForACluster,
  .fbRoleOrder       = dlEpFindingBindingRoleOrder
};

static IdentifySubscriber_t subcriber = NULL;


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void dlConfigureReportingResp(ZCL_Notify_t *ntfy);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void dlDeviceInit(void)
{
  if (!APP_RegisterEndpoint(&dlEndpoint, &dlBindReq))
    return;

  /* Subscribe the Commissioning update command for Target devices */
  identifySubscribe(&subcriber);

  basicClusterInit();
  identifyClusterInit();
  onOffClusterInit();
  levelControlClusterInit();
  groupsClusterInit();
  scenesClusterInit();
  commandManagerInit();

  if (PDS_IsAbleToRestore(APP_DL_SCENES_MEM_ID))
    PDS_Restore(APP_DL_SCENES_MEM_ID);
  if (PDS_IsAbleToRestore(APP_DL_ONOFF_MEM_ID))
    PDS_Restore(APP_DL_ONOFF_MEM_ID);
  if (PDS_IsAbleToRestore(APP_DL_LEVEL_CONTROL_MEM_ID))
    PDS_Restore(APP_DL_LEVEL_CONTROL_MEM_ID);

}

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void dlDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
      }
#ifdef OTAU_CLIENT
      startOtauClient(&dlClientClusters[DL_CLIENT_CLUSTERS_COUNT - 1]);
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
static void dlFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId)
{
  ZCL_Cluster_t *serverCluster;
  switch(clusterId)
  {
    case ONOFF_CLUSTER_ID:
      serverCluster = ZCL_GetCluster(APP_ENDPOINT_DIMMABLE_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
      if (serverCluster)
        sendConfigureReportingToNotify(APP_ENDPOINT_DIMMABLE_LIGHT, 0, ONOFF_CLUSTER_ID,
                                     ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, ONOFF_VAL_MAX_REPORT_PERIOD, 
                                     dlConfigureReportingResp);
      break;

    case LEVEL_CONTROL_CLUSTER_ID:
       serverCluster = ZCL_GetCluster(APP_ENDPOINT_DIMMABLE_LIGHT, LEVEL_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
       if (serverCluster)
         sendConfigureReportingToNotify(APP_ENDPOINT_DIMMABLE_LIGHT, 0, 
                                      LEVEL_CONTROL_CLUSTER_ID,ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, 
                                      LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD, dlConfigureReportingResp);
      break;
  }

}

/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void dlConfigureReportingResp(ZCL_Notify_t *ntfy)
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

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT
// eof dimmableLight.c