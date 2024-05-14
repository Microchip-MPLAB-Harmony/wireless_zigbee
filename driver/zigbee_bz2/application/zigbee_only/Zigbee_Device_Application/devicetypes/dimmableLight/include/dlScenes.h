/*******************************************************************************
  Dimmable Light Scenes Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dlScenes.h

  Summary:
    This file contains the Dimmable Light Scenes interface.

  Description:
    This file contains the Dimmable Light Scenes interface.
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

#ifndef _DLSCENES_H
#define _DLSCENES_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

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

  // On/Off Cluster
  bool      onOff;
  // Level Control Cluster
  uint8_t   currentLevel;
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

/**************************************************************************//**
\brief Gets next scene by group id

\param[in] scene - the pointer to current scene or NULL to get the first busy scene
\param[in] group - group id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *getNextSceneByGroup(Scene_t *scene, uint16_t group);

#endif // _DLSCENES_H

// eof dlScenesCluster.h