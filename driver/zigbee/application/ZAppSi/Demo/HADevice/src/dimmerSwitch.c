/*****************************************************************************
  \file dimmerSwitch.c

  \brief This file contains specific functions that demonstrate dimmerSwitch' behavior


  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    16/12/10 A. Egorov - Created
*******************************************************************************/
/******************************************************************************
                      Includes section
******************************************************************************/
#include <ZAppSiSerialManager.h>
#include <ZAppSiCommands.h>
#include <ZAppSiHost.h>
#include <stdio.h>
#include <demo.h>
#include <halAssert.h>
#include <bindManager.h>

/******************************************************************************
                        Defines section
******************************************************************************/
// Constants for demo commands
#define GROUP_ID  LE16_TO_CPU(0x1222)
#define SCENE0_ID 0x12
#define SCENE1_ID 0x15
#define LEVEL0    0x23
#define LEVEL1    0xAA
#define STEP0     0x10
#define STEP1     0x7F
#define TRANSITION_TIME 0
// Speed of demonstration
#define DEMO_STEP_DELAY 5000
#define APP_ENDPOINT_DIMMABLE_LIGHT 0x11

/******************************************************************************
                             Types section
******************************************************************************/
// Sequence of commands to be demonstrated
typedef enum
{
  SEND_ADD_GROUP, // This command should be first
  SEND_ADD_SCENE0,
  SEND_ADD_SCENE1,
  SEND_VIEW_GROUP,
  SEND_VIEW_SCENE0,
  SEND_VIEW_SCENE1,
  SEND_GET_GROUP_MEMBERSHIP,
  SEND_GET_SCENE_MEMBERSHIP,
  SEND_ON,
  SEND_OFF,
  SEND_TOGGLE,
  SEND_STORE_SCENE,
  SEND_MOVE_TO_LEVEL,
  SEND_MOVE,
  SEND_STEP,
  SEND_STOP,
  SEND_MOVE_TO_LEVEL_W_ONOFF,
  SEND_MOVE_W_ONOFF,
  SEND_STEP_W_ONOFF,
  SEND_STOP_W_ONOFF,
  SEND_RECALL_SCENE,
  SEND_REMOVE_ALL_SCENES,
  SEND_REMOVE_ALL_GROUPS,
  RESTART_DEMO,
  STOP_DEMO,              // Place STOP_DEMO before RESTART_DEMO to terminate demonstration
} DemoSequence_t;

typedef enum
{
  OFF_VALUE = 0,
  ON_VALUE = 1,
} OnOffValues_t;

typedef enum
{
  MOVE_MODE_UP = 0,
  MOVE_MODE_DOWN = 1,
} MoveModeValues_t;

typedef enum
{
  STEP_MODE_UP = 0,
  STEP_MODE_DOWN = 1,
} StepModeValues_t;

/*****************************************************************************
                      Prototypes section
******************************************************************************/
void rDataSlaveInd(void);
static void sendAddGroup(uint16_t groupId, char *name);
static void sendAddScene(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, char *name, const extFields_t *ext);
static void sendViewGroup(uint16_t groupId);
static void sendViewScene(uint16_t groupId, uint8_t sceneId);
static void sendGetGroupMembership(void);
static void sendGetSceneMembership(uint16_t groupId);
static void sendOn(void);
static void sendOff(void);
static void sendToggle(void);
static void sendStoreScene(uint16_t groupId, uint8_t sceneId);
static void sendMove(uint8_t moveMode, uint8_t rate, uint8_t affectOnOff);
static void sendMoveToLevel(uint8_t level, uint16_t transitionTime, uint8_t affectOnOff);
static void sendStep(uint8_t stepMode, uint8_t stepSize, uint16_t transitionTime, uint8_t affectOnOff);
static void sendStop(uint8_t affectOnOff);
static void sendRemoveAllScenes(uint16_t groupId);
static void sendRemoveAllGroups(void);
static void sendRecallScene(uint16_t groupId, uint8_t sceneId);
/*****************************************************************************
                     Global variables section
******************************************************************************/
ClusterId_t inClusterList[] = { ONOFF_SWITCH_CONFIGURATION_CLUSTER_ID };

ClusterId_t outClusterList[] = {
#if CERTICOM_SUPPORT == 1
  ZCL_KEY_ESTABLISHMENT_CLUSTER_ID,
#endif /* CERTICOM_SUPPORT == 1 */

  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID
};



int inClusterCount = sizeof(inClusterList)/sizeof(ClusterId_t);
int outClusterCount = sizeof(outClusterList)/sizeof(ClusterId_t);

static HAL_AppTimer_t demoStepTimer =
{
  .interval = DEMO_STEP_DELAY,
  .mode = TIMER_REPEAT_MODE,
  .callback = advanceDemo,
};

// Bitmap to control commands' responses
static struct
{
  bool confirmResponse : 1;
  bool responsedSuccessfully : 1;
  bool needNextSeqNum : 1;
} responseMap =
{
  .confirmResponse = false,
  .responsedSuccessfully = false,
  .needNextSeqNum = true
};

static char *groupName = "Room";
static char *scene0Name = "Morning";
static char *scene1Name = "Evening";
static DemoSequence_t demoCommand;

// Const extension fields for Add Scene command
static const extFields_t morningOnOffClusterExtFieldSet =
{
  .onOff = {DEFINE_ONOFF_CLUSTER_EXTENSION_FIELD_SET(false)},
  .levelControl = {DEFINE_LEVEL_CONTROL_CLUSTER_EXTENSION_FIELD_SET(12)},
};

// Const extension fields for Add Scene command
static const extFields_t eveningOnOffClusterExtFieldSet =
{
  .onOff = {DEFINE_ONOFF_CLUSTER_EXTENSION_FIELD_SET(true)},
  .levelControl = {DEFINE_LEVEL_CONTROL_CLUSTER_EXTENSION_FIELD_SET(15)},
};

static uint8_t actualZclSequenceNumber;

/*******************************************************************************
                      Implementation section
*******************************************************************************/
/**************************************************************************//**
\brief Confirm message.

\param  conf - confirm information
******************************************************************************/
void commonCommandConf(RZclCommandConfirm_t *conf)
{
  responseMap.confirmResponse = false;
  responseMap.needNextSeqNum = true;
  (void)conf;
}

/***************************************************************************//**
\brief Default Response indication handler. Actual for commands without special
       defined response.

\param[in] ind - indication parameters
*******************************************************************************/
void ZS_ZclDefaultResponseInd(const RZclDefaultResponseInd_t *ind)
{
  switch (demoCommand)
  {
    case SEND_ON:
    case SEND_OFF:
    case SEND_TOGGLE:
    case SEND_MOVE_TO_LEVEL:
    case SEND_MOVE:
    case SEND_STEP:
    case SEND_STOP:
    case SEND_MOVE_TO_LEVEL_W_ONOFF:
    case SEND_MOVE_W_ONOFF:
    case SEND_STEP_W_ONOFF:
    case SEND_STOP_W_ONOFF:
    case SEND_RECALL_SCENE:
    case SEND_REMOVE_ALL_GROUPS:
      if (ZCL_SUCCESS_STATUS == ind->status)
        responseMap.responsedSuccessfully = true;
      break;

    default:
      break;
  }
}

/**************************************************************************//**
\brief Next zcl sequence number response handler

\param[in] ind - indication parameters
******************************************************************************/
void ZS_ZclNextSeqNumberRespInd(const RZclNextSequenceNumberResp_t *ind)
{
  actualZclSequenceNumber = ind->sequenceNumber;
}

/**************************************************************************//**
\brief Sends Add Group command

\param[in] groupId - group id
\param[in] name - group name
******************************************************************************/
static void sendAddGroup(uint16_t groupId, char *name)
{
  ZS_ZclAddGroupReq_t req;
  int len;

  req.addGroup.groupId = groupId;
  len = strlen(name);
  req.addGroup.groupNameLen = len;
  req.addGroup.name = groupName;
  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclAddGroupReq(&req, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Add Scene command

\param[in] groupId - group id
\param[in] sceneId - scene id
\param[in] transitionTime - transition to scene time
\param[in] name - scene name
\param[in] ext - extension fields
******************************************************************************/
static void sendAddScene(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, char *name, const extFields_t *ext)
{
  ZS_ZclAddSceneReq_t addSceneReq;
  int len;

  addSceneReq.addScene.groupId = groupId;
  addSceneReq.addScene.sceneId = sceneId;
  addSceneReq.addScene.transitionTime = transitionTime;
  len = strlen(name);
  addSceneReq.addScene.sceneNameLen = len;
  addSceneReq.addScene.name = name;
  addSceneReq.command.defaultResponse = 0;
  addSceneReq.command.sequenceNumber = actualZclSequenceNumber;
  addSceneReq.command.srcEndpoint = APP_ENDPOINT;
  addSceneReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;
  memcpy(&addSceneReq.addScene.extField, ext, sizeof(extFields_t));

  ZS_ZclAddSceneReq(&addSceneReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends View Group command

\param[in] groupId - group id
******************************************************************************/
static void sendViewGroup(uint16_t groupId)
{
  ZS_ZclViewGroupReq_t viewGroupReq;

  viewGroupReq.viewGroup.groupId = groupId;
  viewGroupReq.command.defaultResponse = 0;
  viewGroupReq.command.sequenceNumber = actualZclSequenceNumber;
  viewGroupReq.command.srcEndpoint = APP_ENDPOINT;
  viewGroupReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclViewGroupReq(&viewGroupReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends View Scene command

\param[in] groupId - group id
\param[in] sceneId - scene id
******************************************************************************/
static void sendViewScene(uint16_t groupId, uint8_t sceneId)
{
  ZS_ZclViewSceneReq_t viewSceneReq;

  viewSceneReq.viewScene.groupId = groupId;
  viewSceneReq.viewScene.sceneId = sceneId;
  viewSceneReq.command.defaultResponse = 0;
  viewSceneReq.command.sequenceNumber = actualZclSequenceNumber;
  viewSceneReq.command.srcEndpoint = APP_ENDPOINT;
  viewSceneReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclViewSceneReq(&viewSceneReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Get Group Membership Command
******************************************************************************/
static void sendGetGroupMembership(void)
{
  ZS_ZclGetGroupMembershipReq_t getGroupMembershipReq;

  getGroupMembershipReq.groupMembership.groupCount = 0;
  getGroupMembershipReq.command.defaultResponse = 0;
  getGroupMembershipReq.command.sequenceNumber = actualZclSequenceNumber;
  getGroupMembershipReq.command.srcEndpoint = APP_ENDPOINT;
  getGroupMembershipReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclGetGroupMembershipReq(&getGroupMembershipReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Get Scene Membership command

\param[in] groupId - groupId
******************************************************************************/
static void sendGetSceneMembership(uint16_t groupId)
{
  ZS_ZclGetSceneMembershipReq_t getSceneMembershipReq;

  getSceneMembershipReq.sceneMembership.groupId = groupId;
  getSceneMembershipReq.command.defaultResponse = 0;
  getSceneMembershipReq.command.sequenceNumber = actualZclSequenceNumber;
  getSceneMembershipReq.command.srcEndpoint = APP_ENDPOINT;
  getSceneMembershipReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclGetSceneMembershipReq(&getSceneMembershipReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends On command
******************************************************************************/
static void sendOn(void)
{
  ZS_ZclEmptyPayloadReq_t  req;

  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclOnReq(&req, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Off command
******************************************************************************/
static void sendOff(void)
{
  ZS_ZclEmptyPayloadReq_t  req;

  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclOffReq(&req, commonCommandConf);
}

/**************************************************************************//**
\brief Sends toggle command
******************************************************************************/
static void sendToggle(void)
{
  ZS_ZclEmptyPayloadReq_t  req;

  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclToggleReq(&req, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Store Scene commands

\param[in] groupId - group id
\param[in] sceneId - group id
******************************************************************************/
static void sendStoreScene(uint16_t groupId, uint8_t sceneId)
{
  ZS_ZclStoreSceneReq_t storeSceneReq;

  storeSceneReq.storeScene.groupId = groupId;
  storeSceneReq.storeScene.sceneId = sceneId;
  storeSceneReq.command.defaultResponse = 0;
  storeSceneReq.command.sequenceNumber = actualZclSequenceNumber;
  storeSceneReq.command.srcEndpoint = APP_ENDPOINT;
  storeSceneReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclStoreSceneReq(&storeSceneReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Move To Level command

\param[in] level - level to be moved to
\param[in] transitionTime - time of movement
\param[in] affectOnOff - should On/Off Cluster be affected
******************************************************************************/
static void sendMoveToLevel(uint8_t level, uint16_t transitionTime, uint8_t affectOnOff)
{
  ZS_ZclMoveToLevelReq_t moveToLevelReq;

  moveToLevelReq.moveToLevel.level = level;
  moveToLevelReq.moveToLevel.transitionTime = transitionTime;
  moveToLevelReq.affectOnOff = affectOnOff;
  moveToLevelReq.command.defaultResponse = 0;
  moveToLevelReq.command.sequenceNumber = actualZclSequenceNumber;
  moveToLevelReq.command.srcEndpoint = APP_ENDPOINT;
  moveToLevelReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclMoveToLevelReq(&moveToLevelReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Move command

\param[in] moveMode - mode of move
\param[in] rate - rate of move
\param[in] affectOnOff - should On/Off Cluster be affected
******************************************************************************/
static void sendMove(uint8_t moveMode, uint8_t rate, uint8_t affectOnOff)
{
  ZS_ZclMoveReq_t moveReq;

  moveReq.move.moveMode = moveMode;
  moveReq.move.rate = rate;
  moveReq.affectOnOff = affectOnOff;
  moveReq.command.defaultResponse = 0;
  moveReq.command.sequenceNumber = actualZclSequenceNumber;
  moveReq.command.srcEndpoint = APP_ENDPOINT;
  moveReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclMoveReq(&moveReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Step Command

\param[in] stepMode - mode of step
\param[in] stepSize - size of step
\param[in] transitionTime - time of step
\param[in] affectOnOff - should On/Off Cluster be affected
******************************************************************************/
static void sendStep(uint8_t stepMode, uint8_t stepSize, uint16_t transitionTime, uint8_t affectOnOff)
{
  ZS_ZclStepReq_t stepReq;

  stepReq.step.stepMode = stepMode;
  stepReq.step.stepSize = stepSize;
  stepReq.step.transitionTime = transitionTime;
  stepReq.affectOnOff = affectOnOff;
  stepReq.command.defaultResponse = 0;
  stepReq.command.sequenceNumber = actualZclSequenceNumber;
  stepReq.command.srcEndpoint = APP_ENDPOINT;
  stepReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclStepReq(&stepReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Stop command

\param[in] affectOnOff - should On/Off Cluster be affected
******************************************************************************/
static void sendStop(uint8_t affectOnOff)
{
  ZS_ZclEmptyPayloadReq_t req;

  req.affectOnOff = affectOnOff;
  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclStopReq(&req, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Recall Scene command

\param[in] groupId - group id
\param[in] sceneId - scene id
******************************************************************************/
static void sendRecallScene(uint16_t groupId, uint8_t sceneId)
{
  ZS_ZclRecallSceneReq_t recallSceneReq;

  recallSceneReq.recallScene.groupId = groupId;
  recallSceneReq.recallScene.sceneId = sceneId;
  recallSceneReq.command.defaultResponse = 0;
  recallSceneReq.command.sequenceNumber = actualZclSequenceNumber;
  recallSceneReq.command.srcEndpoint = APP_ENDPOINT;
  recallSceneReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclRecallSceneReq(&recallSceneReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Remove All Scenes command

\param[in] groupId - group id
******************************************************************************/
static void sendRemoveAllScenes(uint16_t groupId)
{
  ZS_ZclRemoveAllScenesReq_t removeAllScenesReq;

  removeAllScenesReq.removeScenes.groupId = groupId;
  removeAllScenesReq.command.defaultResponse = 0;
  removeAllScenesReq.command.sequenceNumber = actualZclSequenceNumber;
  removeAllScenesReq.command.srcEndpoint = APP_ENDPOINT;
  removeAllScenesReq.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclRemoveAllScenesReq(&removeAllScenesReq, commonCommandConf);
}

/**************************************************************************//**
\brief Sends Remove All Groups command
******************************************************************************/
static void sendRemoveAllGroups(void)
{
  ZS_ZclEmptyPayloadReq_t req;

  req.command.defaultResponse = 0;
  req.command.sequenceNumber = actualZclSequenceNumber;
  req.command.srcEndpoint = APP_ENDPOINT;
  req.command.dstEndpoint = APP_ENDPOINT_DIMMABLE_LIGHT;

  ZS_ZclRemoveAllGroupsReq(&req, commonCommandConf);
}

/***************************************************************************//**
\brief The function is invoked when a Add Group Response command is received.

\param[in] ind - Indication details. See ZS_ZclAddGroupResponseInd_t for details.
*******************************************************************************/
void ZS_ZclAddGroupResponseInd(ZS_ZclAddGroupResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->addGroupResponse.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a Add Scene Response command is received.

\param[in] ind - Indication details. See ZS_ZclAddSceneResponseInd_t for details.
*******************************************************************************/
void ZS_ZclAddSceneResponseInd(ZS_ZclAddSceneResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->addScene.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a View Group Response command is received.

\param[in] ind - Indication details. See ZS_ZclViewGroupResponseInd_t for details.
*******************************************************************************/
void ZS_ZclViewGroupResponseInd(ZS_ZclViewGroupResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->viewGroup.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a View Scene Response command is received.

\param[in] ind - Indication details. See ZS_ZclViewSceneResponseInd_t for details.
*******************************************************************************/
void ZS_ZclViewSceneResponseInd(ZS_ZclViewSceneResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->viewScene.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a Get Group Membership Response command is received.

\param[in] ind - Indication details. See ZS_ZclGetGroupMembershipResponseInd_t for details.
*******************************************************************************/
void ZS_ZclGetGroupMembershipResponseInd(ZS_ZclGetGroupMembershipResponseInd_t *ind)
{
  /* Status field is omitted. Checkings here depends on particular scenario */
  if (1 == ind->groupMembership.groupCount)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a Get Scene Membership Response command is received.

\param[in] ind - Indication details. See ZS_ZclGetSceneMembershipResponseInd_t for details.
*******************************************************************************/
void ZS_ZclGetSceneMembershipResponseInd(ZS_ZclGetSceneMembershipResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->sceneMembership.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a Store Scene Response command is received.

\param[in] ind - Indication details. See ZS_ZclStoreSceneResponseInd_t for details.
*******************************************************************************/
void ZS_ZclStoreSceneResponseInd(ZS_ZclStoreSceneResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->storeScene.status)
    responseMap.responsedSuccessfully = true;
}

/***************************************************************************//**
\brief The function is invoked when a Remove All Scenes Response command is received.

\param[in] ind - Indication details. See ZS_ZclRemoveAllScenesResponseInd_t for details.
*******************************************************************************/
void ZS_ZclRemoveAllScenesResponseInd(ZS_ZclRemoveAllScenesResponseInd_t *ind)
{
  if (ZCL_SUCCESS_STATUS == ind->removeScenes.status)
    responseMap.responsedSuccessfully = true;
}

/**************************************************************************//**
  \brief Confirmation of performed binding procedure.

  \param[in] status - status of performed binding procedure.
  \return None.
 ******************************************************************************/
void bindingConf(bool status)
{
  halAssert(status, APP_BINDING_FAILED);
  demoCommand = SEND_ADD_GROUP;
  HAL_StartAppTimer(&demoStepTimer);  // Start demo
  //do further actions
}

/**************************************************************************//**
\brief Sequences next demo command
******************************************************************************/
void advanceDemo(void)
{
  if (responseMap.needNextSeqNum)
  {
    responseMap.needNextSeqNum = false;
    ZS_ZclNextSeqNumberReq();
    return;
  }

  if (responseMap.confirmResponse)
    return;

  if (responseMap.responsedSuccessfully)
    demoCommand++;

  switch (demoCommand)
  {
    case SEND_ADD_GROUP:
      sendAddGroup(GROUP_ID, groupName);
      break;

    case SEND_ADD_SCENE0:
      sendAddScene(GROUP_ID, SCENE0_ID, TRANSITION_TIME, scene0Name, &morningOnOffClusterExtFieldSet);
      break;

    case SEND_ADD_SCENE1:
      sendAddScene(GROUP_ID, SCENE1_ID, TRANSITION_TIME, scene1Name, &eveningOnOffClusterExtFieldSet);
      break;

    case SEND_VIEW_GROUP:
      sendViewGroup(GROUP_ID);
      break;

    case SEND_VIEW_SCENE0:
      sendViewScene(GROUP_ID, SCENE0_ID);
      break;

    case SEND_VIEW_SCENE1:
      sendViewScene(GROUP_ID, SCENE1_ID);
      break;

    case SEND_GET_GROUP_MEMBERSHIP:
      sendGetGroupMembership();
      break;

    case SEND_GET_SCENE_MEMBERSHIP:
      sendGetSceneMembership(GROUP_ID);
      break;

    case SEND_ON:
      sendOn();
      break;

    case SEND_OFF:
      sendOff();
      break;

    case SEND_TOGGLE:
      sendToggle();
      break;

    case SEND_STORE_SCENE:
      sendStoreScene(GROUP_ID, SCENE0_ID);
      break;

    case SEND_MOVE_TO_LEVEL:
      sendMoveToLevel(LEVEL0, TRANSITION_TIME, 0);
      break;

    case SEND_MOVE:
      sendMove(MOVE_MODE_UP, 0, 0);
      break;

    case SEND_STEP:
      sendStep(STEP_MODE_DOWN, STEP0, TRANSITION_TIME, 0);
      break;

    case SEND_STOP:
      sendStop(0);
      break;

    case SEND_MOVE_TO_LEVEL_W_ONOFF:
      sendMoveToLevel(LEVEL1, TRANSITION_TIME, 1);
      break;

    case SEND_MOVE_W_ONOFF:
      sendMove(MOVE_MODE_DOWN, 0, 1);
      break;

    case SEND_STEP_W_ONOFF:
      sendStep(STEP_MODE_UP, STEP1, TRANSITION_TIME, 1);
      break;

    case SEND_STOP_W_ONOFF:
      sendStop(1);
      break;

    case SEND_RECALL_SCENE:
      sendRecallScene(GROUP_ID, SCENE0_ID);
      break;

    case SEND_REMOVE_ALL_SCENES:
      sendRemoveAllScenes(GROUP_ID);
      break;

    case SEND_REMOVE_ALL_GROUPS:
      sendRemoveAllGroups();
      break;

    case RESTART_DEMO:
      demoCommand = SEND_ADD_GROUP;
      responseMap.confirmResponse = false;
      responseMap.responsedSuccessfully = false;
      return;             // return here is for a reason

    case STOP_DEMO:
      HAL_StopAppTimer(&demoStepTimer);
      return;  // return here is for a reason

    default:
      break;
  }
  responseMap.confirmResponse = true;
  responseMap.responsedSuccessfully = false;
}
// eof dimmerSwitch.c
