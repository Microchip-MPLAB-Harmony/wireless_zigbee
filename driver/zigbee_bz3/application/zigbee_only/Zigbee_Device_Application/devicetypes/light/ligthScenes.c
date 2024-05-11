/*******************************************************************************
  Light Scenes Source File

  Company:
    Microchip Technology Inc.

  File Name:
    lightScenes.c

  Summary:
    This file contains the Light Scenes implementation.

  Description:
    This file contains the Light Scenes implementation.
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
//#include <lightScenes.h>
/******************************************************************************
                    Global variables section
******************************************************************************/
Scene_t scenePool[MAX_SCENES_AMOUNT];

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes scene
******************************************************************************/
void initScenes(void)
{
  memset(scenePool, 0, sizeof(Scene_t) * MAX_SCENES_AMOUNT);
}

/**************************************************************************//**
\brief Allocates scene

\returns the pointer to allocated scene if allocation is successful,
  NULL otherwise
******************************************************************************/
Scene_t *allocateScene(void)
{
  uint8_t i = 0;

  for (i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if (!scenePool[i].busy)
    {
      scenePool[i].busy = true;
      return &scenePool[i];
    }
  }

  return NULL;
}

/**************************************************************************//**
\brief Frees scene

\param[in] scene - the pointer to the scene to be freed
******************************************************************************/
void freeScene(Scene_t *scene)
{
  memset(scene, 0, sizeof(Scene_t));
}

/**************************************************************************//**
\brief Gets appropriate scene by group id and scene id

\param[in] group - group id
\param[in] scene - scene id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *findSceneBySceneAndGroup(uint16_t group, uint8_t scene)
{
  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((scenePool[i].groupId == group) && (scenePool[i].sceneId == scene))
      return &scenePool[i];
  }

  return NULL;
}

/**************************************************************************//**
\brief Removes all scenes associated with the given group

\param[in] group - group id

\return amount of removed scenes
******************************************************************************/
uint8_t removeScenesByGroup(uint16_t group)
{
  uint8_t amount = 0;

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if (scenePool[i].groupId == group)
    {
      freeScene(&scenePool[i]);
      amount++;
    }
  }

  return amount;
}

/**************************************************************************//**
\brief Gets next scene by group id

\param[in] scene - the pointer to current scene or NULL to get the first busy scene
\param[in] group - group id

\returns the pointer to scene if it is found, NULL otherwise
******************************************************************************/
Scene_t *getNextSceneByGroup(Scene_t *scene, uint16_t group)
{
  if (!scene)
  {
    for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
    {
      if (scenePool[i].busy && (scenePool[i].groupId == group))
        return &scenePool[i];
    }
    return NULL;
  }

  if ((scene < scenePool) || (scene > &scenePool[MAX_SCENES_AMOUNT - 1]))
    return NULL;

  for (uint8_t i = 0; i < MAX_SCENES_AMOUNT; i++)
  {
    if ((scene < &scenePool[i]) && (scenePool[i].busy) && (scenePool[i].groupId == group))
      return &scenePool[i];
  }

  return NULL;
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT
// eof lightScenes.c

