/*******************************************************************************
  Applicaiton callback for Zigbee File

  Company:
    Microchip Technology Inc.

  File Name:
    zgb_app_callback.c

  Summary:
    This file contains source code of application callback used by the Zigbee task
    to send responses to the application.

  Description:
    It implements the "APP_ZB_StackCallBack" function that used by the BLE task to
    send responses to the application.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <framework_defs.h>
#include <z3device/stack_interface/zgb_api.h>
#include <z3device/stack_interface/bdb/include/bdb_api.h>
#include <z3device/api/include/zdo_api.h>
#include <z3device/common/include/z3Device.h>
#include <app_zigbee/zigbee_console/console.h>

/******************************************************************************
                    External variables
******************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
#ifdef H3_INDEPENDENT
void ZDO_ResetNetworkConf_Callback (void *resp);
void ZDO_MgmtNwkUpdateNotf_CallBack(void *resp);
void ZDO_WakeUpInd_CallBack(void *resp);
void ZDO_BindIndication_CallBack(void *resp);
void ZDO_UnbindIndication_CallBack(void *resp);

ZDO_CALLBACK_ptr ZB_ZDO_CallBack[ZDO_APP_CALLBACK_MAX] =
{
  ZDO_ResetNetworkConf_Callback,
  ZDO_MgmtNwkUpdateNotf_CallBack,
  ZDO_WakeUpInd_CallBack,
  ZDO_BindIndication_CallBack,
  ZDO_UnbindIndication_CallBack,
};
#endif
/**************************************************************************//**
\brief Network update notification
\param notify - update notification parameters
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf_CallBack(void *resp)
{
  ZDO_MgmtNwkUpdateNotf_t *notify = resp;
  ZDO_MgmtNwkUpdateNotf(notify);
}

void ZDO_ResetNetworkConf_Callback (void *resp)
{
  ZDO_ResetNetworkConf_t *conf = (ZDO_ResetNetworkConf_t *)resp;
  ZDO_ResetNetworkConf(conf);
}
/*******************************************************************************
  Description: just a stub.

  Parameters: none.

  Returns: nothing.
*******************************************************************************/
void ZDO_WakeUpInd_CallBack(void *resp)
{
  ZDO_WakeUpInd();
  (void)resp;
}

/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer.
                      For details go to ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication_CallBack(void *resp)
{
  ZDO_BindInd_t *bindInd = (ZDO_BindInd_t *)resp;
  ZDO_BindIndication(bindInd);

  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer.
                        For details go to ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication_CallBack( void *resp)
{
  ZDO_UnbindInd_t *unbindInd = (ZDO_UnbindInd_t *)resp;
  ZDO_UnbindIndication(unbindInd);

  (void)unbindInd;
}
#ifdef H3_INDEPENDENT
/*******************************************************************************
  Function:
    void APP_ZB_StackCallBack(ZB_AppGenericCallbackParam_t *response)

  Remarks:
    See prototype in application.h.
******************************************************************************/

void APP_ZB_StackCallBack(ZB_AppGenericCallbackParam_t *cb)
{
    switch (cb->eModuleID)
    {
      case ZIGBEE_BDB:
        ZB_BDB_CallBack(cb);
      break;

      case ZIGBEE_ZDO:
        ZB_ZDO_CallBack[cb->uCallBackID]((void *)cb->parameters);
      break;

      case ZIGBEE_ZCL:
      break;
      
      default:
        appSnprintf("[APP CB]  Default case\r\n");
      break;
    }
}
#endif