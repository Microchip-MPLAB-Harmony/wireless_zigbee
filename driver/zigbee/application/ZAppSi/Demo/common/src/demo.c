/*****************************************************************************
  \file demo.c

  \brief Demo application file contains application entry point.
  APL_TaskHandler

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/09/09 D. Kasyanov - Created
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
                             Types section
******************************************************************************/

/*****************************************************************************
                      Prototypes section
******************************************************************************/
static void setConf(const ZS_SysSetConf_t *conf);
void rDataSlaveInd(void);

/*****************************************************************************
                     Global variables section
******************************************************************************/
ZS_ZclStartRequest_t startReq;
#if CERTICOM_SUPPORT == 1
ZCL_LinkKeyDesc_t *linkKeyDescr = 0;
#endif /* CERTICOM_SUPPORT == 1 */


/*******************************************************************************
                      Implementation section
*******************************************************************************/
/*******************************************************************************
\brief ZCL get status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void zclGetConf(ZS_ZclGetConfirm_t* conf)
{
  halAssert(ZCL_SUCCESS_STATUS == conf->status, APP_ZCL_GET_FAILED);

  BSP_ToggleLed(LED_SECOND);

  if (ZCL_LINK_KEY_DESC_ID == conf->id)
  {
#if CERTICOM_SUPPORT == 1
    linkKeyDescr = (ZCL_LinkKeyDesc_t*)conf->value;
    (void)linkKeyDescr;
#endif // CERTICOM_SUPPORT == 1
  }
  matchBindClusters(&startReq, bindingConf);
}

/*******************************************************************************
\brief ZCL start status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void zclStartConf(RZclStartConfirm_t* conf)
{
  halAssert(ZCL_SECURITY_STATUS_SUCCESS == conf->status, APP_ZCL_START_FAILED);
  //as meter has no corresponding logic so no additional actions required

  BSP_ToggleLed(LED_SECOND);

  // we need the request to get link key.
  ZS_ZclGetRequest_t zclGetRequest;
  zclGetRequest.addr = APP_COORD_EXTENDED_ADDR;
  zclGetRequest.id = ZCL_LINK_KEY_DESC_ID;

  ZS_ZclGetReq(&zclGetRequest, zclGetConf);
}

/*******************************************************************************
\brief ZDO start status handler
\param[in] status - command status
\return nothing
*******************************************************************************/
static void zdoStartConf(ZDO_Status_t* status)
{
  if (ZDO_SUCCESS_STATUS != *status)
  {
    ZS_ZdoStartReq(zdoStartConf);
    return;
  }

  BSP_ToggleLed(LED_SECOND);

  startReq.appDeviceId = APP_DEVICE_DEVICE_ID;
  startReq.endpoint = APP_ENDPOINT;
  startReq.inClustersCount = inClusterCount;
  startReq.inClustersList = inClusterList;
  startReq.appProfileId = APP_PROFILE_ID;
  startReq.outClustersCount = outClusterCount;
  startReq.outClustersList = outClusterList;

  ZS_ZclStartReq(&startReq, zclStartConf);
}

/*******************************************************************************
\brief ZCL set status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void zclSetConf(RZclSetConfirm_t* conf)
{
#if CERTICOM_SUPPORT == 1
  ZS_ZclSetRequest_t zclSetRequest;
#endif // CERTICOM_SUPPORT == 1

  halAssert(ZCL_SUCCESS_STATUS == conf->status, APP_ZCL_SET_FAILED);

  BSP_ToggleLed(LED_SECOND);

  switch (conf->id)
  {
    case ZCL_LINK_KEY_DESC_ID:
#if CERTICOM_SUPPORT == 1
      {
        ZCL_CertificateDesc_t certificateDesc = {APP_ICERT_PUBLIC_KEY,
                                             APP_ICERT_PRIVATE_KEY,
                                             APP_ICERT_CERTIFICATE};
        zclSetRequest.id = ZCL_CERTIFICATE_DESC_ID;
        zclSetRequest.length = sizeof(certificateDesc);
        zclSetRequest.value = (uint8_t*)&certificateDesc;

        ZS_ZclSetReq(&zclSetRequest, zclSetConf);
        break;
      }
    case ZCL_CERTIFICATE_DESC_ID:
      {
        uint8_t endpoint = APP_KE_CLUSTER_ENDPOINT;

        zclSetRequest.id = ZCL_KE_ACTIVE_ENDPOINT_ID;
        zclSetRequest.length = sizeof(endpoint);
        zclSetRequest.value = &endpoint;

        ZS_ZclSetReq(&zclSetRequest, zclSetConf);
        break;
      }
    case ZCL_KE_ACTIVE_ENDPOINT_ID:
#endif // CERTICOM_SUPPORT == 1
      ZS_ZdoStartReq(zdoStartConf);
      break;
    default:
      break;
  }
}

/*******************************************************************************
\brief Device type set status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void setDeviceTypeConf(const ZS_SysSetDeviceTypeConf_t *conf)
{
  ZCL_LinkKeyDesc_t linkKeyDesc = {APP_COORD_EXTENDED_ADDR, APP_LINK_KEY};
  ZS_ZclSetRequest_t zclSetRequest;

  halAssert(ZS_SUCCESS_STATUS == conf->status, APP_DEV_TYPE_SET_FAILED);

  BSP_ToggleLed(LED_SECOND);

  zclSetRequest.id = ZCL_LINK_KEY_DESC_ID;
  zclSetRequest.length = sizeof(linkKeyDesc);
  zclSetRequest.value = (uint8_t*)&linkKeyDesc;

  ZS_ZclSetReq(&zclSetRequest, zclSetConf);
}

/*******************************************************************************
\brief Set status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void setConf(const ZS_SysSetConf_t *conf)
{
  ZS_SysSetReq_t sysSetReq;

  halAssert(ZS_SUCCESS_STATUS == conf->status, APP_SYS_SET_FAILED);

  BSP_ToggleLed(LED_SECOND);

  if (ZS_CHANNEL_MASK_ATTR_ID == conf->attributeId)
  {
    sysSetReq.attributeId = ZS_EXTENDED_PANID_ATTR_ID;
    sysSetReq.attributeLength = sizeof(uint64_t);
    sysSetReq.attributeValue.uint64 = APP_EXT_PANID;
  }
  else if (ZS_EXTENDED_PANID_ATTR_ID == conf->attributeId)
  {
    sysSetReq.attributeId = ZS_NWK_EXTENDED_PANID_ATTR_ID;
    sysSetReq.attributeLength = sizeof(uint64_t);
    sysSetReq.attributeValue.uint64 = APP_EXT_PANID;
  }
  else if (ZS_NWK_EXTENDED_PANID_ATTR_ID == conf->attributeId)
  {
    sysSetReq.attributeId = ZS_PERMIT_DURATION_ATTR_ID;
    sysSetReq.attributeLength = sizeof(uint8_t);
    sysSetReq.attributeValue.uint8 = APP_PERMIT_DURATION;
  }
  else if (ZS_PERMIT_DURATION_ATTR_ID == conf->attributeId)
  {
    sysSetReq.attributeId = ZS_EXTENDED_ADDRESS_ATTR_ID;
    sysSetReq.attributeLength = sizeof(uint64_t);
    sysSetReq.attributeValue.uint64 = APP_EXTENDED_ADDR;
  }
  else if (ZS_EXTENDED_ADDRESS_ATTR_ID == conf->attributeId)
  {
    sysSetReq.attributeId = ZS_TRUST_CENTER_ADDRESS_ATTR_ID;
    sysSetReq.attributeLength = sizeof(uint64_t);
    sysSetReq.attributeValue.uint64 = APP_TRUST_CENTER_ADDRESS;
  }
  else if (ZS_TRUST_CENTER_ADDRESS_ATTR_ID == conf->attributeId)
  {
    ZS_SysSetDeviceTypeReq_t sysSetDeviceType;
    sysSetDeviceType.deviceType = APP_DEV_TYPE;
    ZS_SysSetDeviceTypeReq(&sysSetDeviceType, setDeviceTypeConf);
    return;
  }
  ZS_SysSetReq(&sysSetReq, setConf);
}

/*******************************************************************************
\brief Reset status handler
\param[in] conf - command status
\return nothing
*******************************************************************************/
static void resetConf(const ZS_SysResetConf_t *conf)
{
  BSP_OpenLeds();
  BSP_OnLed(LED_FIRST);
  BSP_OnLed(LED_SECOND);
  ZS_SysSetReq_t req;

  halAssert(ZS_SUCCESS_STATUS == conf->status,APP_RESET_FAILED);

  req.attributeId = ZS_CHANNEL_MASK_ATTR_ID;
  req.attributeLength = sizeof(uint32_t);
  req.attributeValue.uint32 = APP_CHANNEL_MASK;

  ZS_SysSetReq(&req, setConf);
}

/*******************************************************************************
\brief Application entry point
\param none
\return nothing
*******************************************************************************/
void APL_TaskHandler(void)
{
  static bool started = false;

  if (!started)
  {
#if (APP_INTERFACE == APP_INTERFACE_SPI)
    ZS_Open(INTERFACE_ID_SPI);
#else
    ZS_Open(INTERFACE_ID_USART0);
#endif

    ZS_SysResetReq_t req;
    req.resetType = 0x01;
    ZS_SysResetReq(&req, resetConf);
    started = true;
  }
#ifndef BOARD_PC
  else
  {
    rDataSlaveInd();
  }
#endif //#ifndef BOARD_PC
}

#ifndef BOARD_PC
/**********************************************************************//**
  \brief Main - C program main start function

  \param none
  \return none
**************************************************************************/
int main(void)
{
  SYS_SysInit();

  for(;;)
  {
    SYS_RunTask();
  }
}
#endif //#ifndef BOARD_PC
//eof demo.c

