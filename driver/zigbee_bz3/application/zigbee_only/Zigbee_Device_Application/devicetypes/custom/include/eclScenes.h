/**************************************************************************//**
  \file dlScenes.h

  \brief
    Extended Color Light Scenes interface.

  \author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

  \internal
    History:
    11.12.12 N. Fomin - Created.
    24.09.15 Karthik.P_u - Copied, Modified.
******************************************************************************/
#ifndef ECLSCENES_H
#define ECLSCENES_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>
#include <zclZllColorControlCluster.h>
/******************************************************************************
                    Definition(s) section
******************************************************************************/

#ifndef MAX_SCENES_AMOUNT
#define MAX_SCENES_AMOUNT 16u
#endif

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  bool      busy;
  uint8_t   sceneId;
  uint16_t  groupId;
  uint16_t  transitionTime;
  uint8_t   transitionTime100ms;

  // On/Off Cluster
  bool      onOff;

  // Level Control Cluster
  uint8_t   currentLevel;

  // Color Control Cluster
  ZCL_ZllEnhancedColorMode_t colorMode;
  uint16_t  currentX;
  uint16_t  currentY;
  uint16_t  enhancedCurrentHue;
  uint8_t   currentSaturation;
  uint8_t   colorLoopActive;
  uint8_t   colorLoopDirection;
  uint16_t  colorLoopTime;
} Scene_t;

/******************************************************************************
                    External variables section
******************************************************************************/
extern Scene_t scenePool[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes scene
******************************************************************************/
void initScenes(void);

/**************************************************************************//**
\brief Allocates scene

\returns the pointer to allocated scene if allocation is successful,
  NULL otherwise
******************************************************************************/
Scene_t *allocateScene(void);

/**************************************************************************//**
\brief Frees scene

\param[in] scene - the pointer to the scene to be freed
******************************************************************************/
void freeScene(Scene_t *scene);

/**************************************************************************//**
\brief Gets appropriate scene by group id and scene id

\param[in] group - group id
\param[in] scene - scene id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *findSceneBySceneAndGroup(uint16_t group, uint8_t scene);

/**************************************************************************//**
\brief Removes all scenes associated with the given group

\param[in] group - group id

\return amount of removed groups
******************************************************************************/
uint8_t removeScenesByGroup(uint16_t group);

#endif // ECLSCENES_H

// eof dlScenesCluster.h
