/*******************************************************************************
  TrustCentre Memory Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcMem.h

  Summary:
    This file contains the Security Trust Centre memory manager prototypes.

  Description:
    This file contains the Security Trust Centre memory manager prototypes.
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

#ifndef _TCMEM_H
#define _TCMEM_H

/******************************************************************************
                              Includes section.
******************************************************************************/
#include <sysQueue.h>
#include <private/tcTaskManager.h>
#include <private/tcAuthenticHandler.h>
#include <private/tcKeyUpdateHandler.h>
#include <private/tcKeyEstablishHandler.h>
#include <private/tcRemoveHandler.h>

/******************************************************************************
                        Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  TcAuthenticHandlerMem_t    authenticHandlerMem;
  TcKeyUpdateHandlerMem_t    keyUpdateHandlerMem;
#ifdef _LINK_SECURITY_
  TcKeyEstablishHandlerMem_t keyEstablishHandlerMem;
#endif // _LINK_SECURITY_
  TcRemoveHandlerMem_t       removeHandlerMem;
  TcTaskManagerMem_t         taskManagerMem;
} TcMem_t;

/******************************************************************************
                        External variables.
******************************************************************************/
extern TcMem_t tcMem;

/******************************************************************************
                        Inline functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
INLINE TcTaskManagerMem_t* tcGetTaskManagerMem(void)
{
  return &tcMem.taskManagerMem;
}

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
INLINE TcAuthenticHandlerMem_t* tcGetAuthenticHandlerMem(void)
{
  return &tcMem.authenticHandlerMem;
}

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
INLINE TcKeyUpdateHandlerMem_t* tcGetKeyUpdateHandlerMem(void)
{
  return &tcMem.keyUpdateHandlerMem;
}

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
#ifdef _LINK_SECURITY_
INLINE TcKeyEstablishHandlerMem_t* tcGetKeyEstablishHandlerMem(void)
{
  return &tcMem.keyEstablishHandlerMem;
}
#endif // _LINK_SECURITY_

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
INLINE TcRemoveHandlerMem_t* tcGetRemoveHandlerMem(void)
{
  return &tcMem.removeHandlerMem;
}

#endif //_TCMEM_H

// eof tcMem.h
