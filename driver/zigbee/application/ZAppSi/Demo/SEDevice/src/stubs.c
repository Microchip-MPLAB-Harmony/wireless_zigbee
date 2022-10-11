/*******************************************************************************
  \file stubs.c

  \brief stubs file contains function the user free to redefine.
 This file should be linked to user's application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*******************************************************************************/
/***************************************************************************//**
Include section
*******************************************************************************/
#include <ZAppSiHost.h>
#include <demo.h>
/******************************************************************************
Implementations section
******************************************************************************/
/***************************************************************************//**
\brief Wakeup indication

\param

\return
*******************************************************************************/
void ZS_ZdoWakeupInd()
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked when data is received.
Implemented by user.

\param[in] ind - Holds received data.
See ZS_ApsDataInd_t for details.

\return
*******************************************************************************/
void ZS_ApsDataInd(const ZS_ApsDataInd_t *ind)
{
  // Insert your code here
  (void)ind;
}

/***************************************************************************//**
*******************************************************************************/
void zdoTcSwapOutConfirm(uint8_t *status)
{
  if (ZCL_SUCCESS_STATUS != *status)
  {
     ZS_ZdoSwapOutReq(zdoTcSwapOutConfirm);
  }
}
/***************************************************************************//**
\brief Callback for notification about network changes.

The local device is notified of the local channel conditions at the transmitting
device, or of its attempt to update network configuration parameters.
ZigBee Specification r17, 2.4.4.3.9 Mgmt_NWK_Update_notify

\param[in] notf - Response status.
See description of ZS_MgmtNwkUpdateNotf_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtNwkUpdateNotify(ZS_MgmtNwkUpdateNotf_t* notf)
{
 if (ZDO_TC_NOT_AVAILABLE_STATUS == notf->status)
  {
    ZS_ZdoSwapOutReq(zdoTcSwapOutConfirm);
  }
}
/***************************************************************************//**
\brief The Function is invoked when an Identify command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyInd(const ZS_ZclIdentifyInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The Function is invoked when an Identify Query command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyQueryInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryInd(const ZS_ZclIdentifyQueryInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The Function is invoked when an Identify Query Response command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyQueryResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryResponseInd(const ZS_ZclIdentifyQueryResponseInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoked when Get Current Price command is received.
Implemented by user.

\param[in]
See ZS_ZclGetCurrentPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetCurrentPriceInd(const ZS_ZclGetCurrentPriceInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoked when a Publish Price command is received.
Implemented by user.

\param[in]
See ZS_ZclPublishPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZclPublishPriceInd(const ZS_ZclPublishPriceInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoke when a Report Event Status command is received.
Implemented by user.

\param[in]
See ZS_ZclReportEventStatusInd_t for details.

\return
*******************************************************************************/
void ZS_ZclReportEventStatusInd(const ZS_ZclReportEventStatusInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoked when a Get Scheduled Events command is received.
Implemented by user.

\param[in]
See ZS_ZclGetScheduledEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetScheduledEventsInd(const ZS_ZclGetScheduledEventsInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoked when a Load Control Event command is received.
Implemented by user.

\param[in]
See ZS_ZclLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclLoadControlEventInd(const ZS_ZclLoadControlEventInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoke when a Cancel Load Control Event command is received.
Implemented by user.

\param[in]
See ZS_ZclCancelLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelLoadControlEventInd(const ZS_ZclCancelLoadControlEventInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Function is invoked when a Cancel All Load Control Events command is
received.
Implemented by user.

\param[in]
See ZS_ZclCancelAllLoadControlEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelAllLoadControlEventsInd(const ZS_ZclCancelAllLoadControlEventsInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Get Last Message command is received.
Implemented by user.

\param[in]
See ZS_ZclGetLastMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetLastMessageInd(const ZS_ZclGetLastMessageInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Message Confirmation command is received.
Implemented by user.

\param[in]
See ZS_ZclMessageConfirmationInd_t for details.

\return
*******************************************************************************/
void ZS_ZclMessageConfirmationInd(const ZS_ZclMessageConfirmationInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is inoked when a Display Message command is received.
Implemented by user.

\param[in]
See ZS_ZclDisplayMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclDisplayMessageInd(const ZS_ZclDisplayMessageInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Cancel Message command is received.
Implemented by user.

\param[in]
See ZS_ZclCancelMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelMessageInd(const ZS_ZclCancelMessageInd_t *ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Attribute reporting indication.

Notify of the latest values of one or more
of the attributes of another device.

ZigBee_Cluster_Library_Specification 075123r02ZB, 2.4.11.1 Report Attributes Command Frame Format

\param[in] ind - Indication details.
See description of ZS_ZclReportInd_t for details.

\return
*******************************************************************************/
void ZS_ZclReportInd(ZS_ZclReportInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief Attribute event indication.

Notifes about the actions take place on cluster's attribute.

\param[in] ind - Indication details.
See sescription of ZS_ZclAttributeEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAttributeEventInd(ZS_ZclAttributeEventInd_t* ind)
{
  if (ZCL_READ_ATTRIBUTE_EVENT == ind->event)
  {
    BSP_ToggleLed(LED_THIRD);
  }
  else if (ZCL_WRITE_ATTRIBUTE_EVENT == ind->event)
  {
    BSP_ToggleLed(LED_FOURTH);
  }
}
/***************************************************************************//**
\brief The function is invoked when a Add Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclAddGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAddGroupResponseInd(ZS_ZclAddGroupResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a View Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclViewGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclViewGroupResponseInd(ZS_ZclViewGroupResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Get Group Membership Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclGetGroupMembershipResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetGroupMembershipResponseInd(ZS_ZclGetGroupMembershipResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Remove Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclRemoveGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclRemoveGroupResponseInd(ZS_ZclRemoveGroupResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Add Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclAddSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAddSceneResponseInd(ZS_ZclAddSceneResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a View Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclViewSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclViewSceneResponseInd(ZS_ZclViewSceneResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Remove All Scenes Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclRemoveAllScenesResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclRemoveAllScenesResponseInd(ZS_ZclRemoveAllScenesResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Store Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclStoreSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclStoreSceneResponseInd(ZS_ZclStoreSceneResponseInd_t* ind)
{
  // Insert your code here
  (void)ind;
}
/***************************************************************************//**
\brief The function is invoked when a Get Scene Membership Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclGetSceneMembershipResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetSceneMembershipResponseInd(ZS_ZclGetSceneMembershipResponseInd_t *ind)
{
  // Insert your code here
  (void)ind;
}

/***************************************************************************//**
\brief Default Response indication handler. Actual for commands without special
       defined response.

\param[in] ind - indication parameters
*******************************************************************************/
void ZS_ZclDefaultResponseInd(const RZclDefaultResponseInd_t *ind)
{
  // Insert your code here
  (void)ind;
}

/**************************************************************************//**
\brief Next zcl sequence number response handler

\param[in] ind - indication parameters
******************************************************************************/
void ZS_ZclNextSeqNumberRespInd(const RZclNextSequenceNumberResp_t *ind)
{
  // Insert your code here
  (void)ind;
}
//eof stubs.c
