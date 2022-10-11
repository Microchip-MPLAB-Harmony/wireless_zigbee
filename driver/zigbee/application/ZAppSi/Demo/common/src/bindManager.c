/************************************************************************//**
  \file bindmanager.c

  \brief
    ZclDevice: Bind manager implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    11.01.09 A. Taradov - Created.
******************************************************************************/

/***********************************************************************************
                          Includes section
***********************************************************************************/
#include <bindManager.h>
#include <halAssert.h>
#include <demo.h>
#include <ZAppSiHost.h>
/***********************************************************************************
                          Defines section
***********************************************************************************/
#define MAX_BIND_ATTEMPT 5
/***********************************************************************************
                          Global variables section
***********************************************************************************/

/***********************************************************************************
                          Local variables section
***********************************************************************************/
static ExtAddr_t extAddrToBindWith;
static MatchBindRequest_t matchBindReq;
static ZS_ZclStartRequest_t* config = NULL;
static void (*matchBindClustersConf)(bool);
static uint8_t bindAttempts = 0;
static uint8_t clusterIndex = 0;
static bool isKeyGotten = false;

/***********************************************************************************
                          Global functions section
***********************************************************************************/
void matchBindDevices(void);
/***********************************************************************************
                          Static functions section
***********************************************************************************/
static void doApsBinding(ExtAddr_t *remoteDevExtAddr);
static void doIeeeAddrReq(void);
static void zdpBindResp(ZS_ZdpBindConf_t *resp);
static void zdpIeeeAddrResp(ZS_ZdoIeeeAddrConf_t* resp);
static void zdpMatchDescResp(ZS_ZdpMatchDescConf_t* resp);
static void apsRequestKeyConf(ZS_ApsRequestKeyConf_t *conf);

/***********************************************************************************
                          Implementation section
***********************************************************************************/
void apsBindConf(const ZS_ApsBindConf_t* conf)
{
  ZS_ZdpBindReq_t zdoBindReq;
  if (APS_SUCCESS_STATUS != conf->status)
  {
    matchBindReq.callback(false);
  }
  zdoBindReq.targetAddrMode = EXT_ADDR_MODE;
  COPY_EXT_ADDR(zdoBindReq.targetExtAddr, conf->dstExtAddr);
  zdoBindReq.reqCluster = BIND_CLID;
  zdoBindReq.targetNwkAddr = NWK_NO_SHORT_ADDR;

  COPY_EXT_ADDR(zdoBindReq.payload.srcAddr, conf->dstExtAddr);
  zdoBindReq.payload.srcEndpoint = conf->dstEndpoint;
  zdoBindReq.payload.clusterId = matchBindReq.cluster;
  zdoBindReq.payload.dstAddrMode = APS_EXT_ADDRESS;
  zdoBindReq.payload.dstExtAddr = APP_EXTENDED_ADDR;
  zdoBindReq.payload.dstEndpoint = matchBindReq.srcEndpoint;
  ZS_ZdpBindReq(&zdoBindReq, zdpBindResp);
}

/********************************************************************
  Description: Initiates APS and ZDO binding.
  Parameters:  ieeeAddr - address to bind.
  Returns:     none
********************************************************************/
static void doApsBinding(ExtAddr_t *remoteDevExtAddr)
{
  ZS_ApsBindReq_t apsBindReq;
  ExtAddr_t ownExtAddr;
  uint8_t i;

  halAssert(matchBindReq.matchesReceived, APP_BINDMANAGER_0);
  matchBindReq.matchesReceived--;
  if (matchBindReq.matchDescResp[matchBindReq.matchesReceived].matchLength)
  {
    i = --matchBindReq.matchDescResp[matchBindReq.matchesReceived].matchLength;
    // APS binding an ZDO binding.
    ownExtAddr = APP_EXTENDED_ADDR;
    apsBindReq.srcAddr = ownExtAddr;
    apsBindReq.srcEndpoint = matchBindReq.srcEndpoint;
    apsBindReq.clusterId = matchBindReq.cluster;
    apsBindReq.dstAddrMode = APS_EXT_ADDRESS;
    apsBindReq.dstExtAddr = *remoteDevExtAddr;
    apsBindReq.dstEndpoint = matchBindReq.matchDescResp[matchBindReq.matchesReceived].matchList[i];
    ZS_ApsBindReq(&apsBindReq, apsBindConf);
  }
  else
  {
    matchBindReq.callback(false);
  }
}

/********************************************************************
  Description: Response to IEEE address request
  Parameters:  resp - response parameters
  Returns:     none
********************************************************************/
static void zdpIeeeAddrResp(ZS_ZdoIeeeAddrConf_t* resp)
{
  if (ZDO_SUCCESS_STATUS == resp->status)
  {
    extAddrToBindWith = resp->resp.ieeeAddrRemote;
    doApsBinding(&extAddrToBindWith);
  }
  else
    matchBindReq.callback(false);
}

/****************************************************************//**
  \brief Confiramtion for key request.
  \param conf[in] confirmaiton status
  \return none
********************************************************************/
static void apsRequestKeyConf(ZS_ApsRequestKeyConf_t *conf)
{
  if (APS_RKR_SUCCESS_STATUS == conf->status)
  {
    matchBindReq.callback(true);
  }
  else
  {
    matchBindReq.callback(false);
  }
}

/****************************************************************//**
  \brief Checks whether Link key for the remote device presents or not.
  \param none
  \return true if Link Key has been already set, false otherwise.
********************************************************************/
static bool checkLinkKey(void)
{
  if (APP_TRUST_CENTER_ADDRESS != extAddrToBindWith && !isKeyGotten)
  {
    ZS_ApsRequestKeyReq_t apsKeyReq;

    isKeyGotten = true;
    apsKeyReq.destAddress = APP_TRUST_CENTER_ADDRESS;
    apsKeyReq.keyType = APS_APP_KEY_TYPE;
    apsKeyReq.partnerAddress = extAddrToBindWith;

    ZS_ApsRequestKeyReq(&apsKeyReq, apsRequestKeyConf);

    return false;
  }
  return true;
}

/********************************************************************
  Description: Response to ZDP Bind request
  Parameters:  resp - zdp response parameters
               (go to ZDO_ZdpResp_t declaration for details)
  Returns:     none
********************************************************************/
static void zdpBindResp(ZS_ZdpBindConf_t* resp)
{
  if (ZDO_SUCCESS_STATUS == resp->status)
  {
    if (matchBindReq.matchDescResp[matchBindReq.matchesReceived].matchLength)
    {
      doApsBinding(&extAddrToBindWith);
    }
    else
    {
      if (matchBindReq.matchesReceived)
        doIeeeAddrReq();
      else
        if (checkLinkKey())
          matchBindReq.callback(true);
    }
  }
  else
  {
    matchBindReq.callback(false);
  }
}

/********************************************************************
  Description: Perform IEEE adddress request
  Parameters:  none
  Returns:     none
********************************************************************/
static void doIeeeAddrReq(void)
{
  ZDO_IeeeAddrReq_t ieeeAddrReq;

  ieeeAddrReq.nwkAddrOfInterest = matchBindReq.matchDescResp[matchBindReq.matchesReceived-1].nwkAddrOfInterest;
  ieeeAddrReq.reqType = 0;
  ieeeAddrReq.startIndex = 0;
  ZS_ZdoIeeeAddrReq(&ieeeAddrReq, zdpIeeeAddrResp);
}

/********************************************************************
  Description: Response to match descriptor request
  Parameters:  resp - response parameters
  Returns:     none
********************************************************************/
static void zdpMatchDescResp(ZS_ZdpMatchDescConf_t* resp)
{
  ZDO_MatchDescResp_t *matchResp = &resp->resp;
  ZDO_Status_t status = resp->status;

  if (ZDO_CMD_COMPLETED_STATUS == status)
  {
    if (matchBindReq.matchesReceived)
      doIeeeAddrReq();
    else
      matchBindReq.callback(false);
  }
  else if (ZDO_SUCCESS_STATUS != status)
  {
    matchBindReq.callback(false);
  }
  else if (MAX_MATCH_DESC_RESP_AMOUNT > matchBindReq.matchesReceived)
  {
    memcpy(&matchBindReq.matchDescResp[matchBindReq.matchesReceived], matchResp, sizeof(ZDO_MatchDescResp_t));
    matchBindReq.matchesReceived++;
  }
}

/********************************************************************
  Description: Perform match descriptor request, IEEE address request
               and binding
  Parameters:  none
  Returns:     none
********************************************************************/
void matchBindDevices(void)
{
  ZS_ZdpMatchDescReq_t matchDescReq;
  halAssert(NULL != matchBindReq.callback, APP_BINDMANAGER_1);
  matchBindReq.matchesReceived = 0;

  matchDescReq.nwkAddrOfInterest = RX_ON_WHEN_IDLE_ADDR;
  matchDescReq.profileId = APP_PROFILE_ID;

  if (BIND_DIRECTION_IN == matchBindReq.direction)
  {
    matchDescReq.numInClusters = 1;
    matchDescReq.numOutClusters = 0;
    matchDescReq.inClusterList = &matchBindReq.cluster;
  }
  else
  {
    matchDescReq.numInClusters = 0;
    matchDescReq.numOutClusters = 1;
    matchDescReq.outClusterList = &matchBindReq.cluster;
  }

  ZS_ZdpMatchDescReq(&matchDescReq, zdpMatchDescResp);
}


/*******************************************************************************
\brief Bind individual cluster with choosen directions
\param nothing
\return nothing
*******************************************************************************/
void matchBindCb(bool status)
{
  if (false == status)
  {
    if (MAX_BIND_ATTEMPT == bindAttempts)
    {
      matchBindClustersConf(false);
    }
    else
    {
      bindAttempts++;
      matchBindDevices();
    }
  }
  if (BIND_DIRECTION_OUT == matchBindReq.direction)
  {
    if (clusterIndex == config->inClustersCount - 1)
    {
      matchBindReq.direction = BIND_DIRECTION_IN;
      if (config->outClustersCount > 0)
      {
        matchBindReq.cluster = config->outClustersList[clusterIndex = 0];
      }
      else
      {
        matchBindClustersConf(true);
        return;
      }
    }
    else
      matchBindReq.cluster = config->inClustersList[++clusterIndex];
  }
  else
  {
    if (clusterIndex == config->outClustersCount - 1)
    {
      matchBindClustersConf(true);
      return;
    }
    else
      matchBindReq.cluster = config->outClustersList[++clusterIndex];
  }
  if (ZCL_KEY_ESTABLISHMENT_CLUSTER_ID == matchBindReq.cluster)
    matchBindReq.callback(true); //it supposed that KE cluster is bound by default
  else
    matchBindDevices();
}

void matchBindClusters(ZS_ZclStartRequest_t* cfg, void (*conf)(bool status))
{
  //store req params
  config = cfg;
  matchBindClustersConf = conf;
  matchBindReq.srcEndpoint = config->endpoint;
  if (config->inClustersCount != 0)
  {
    matchBindReq.direction = BIND_DIRECTION_OUT;
  }
  else if (config->outClustersCount != 0)
  {
    matchBindReq.direction = BIND_DIRECTION_IN;
  }
  else
  {
    //no clusters required
    matchBindClustersConf(true);
    return;
  }
  matchBindReq.callback = matchBindCb;
  //reverse cluster
  matchBindReq.cluster = (BIND_DIRECTION_OUT == matchBindReq.direction) ?
                    config->inClustersList[clusterIndex]:
		    config->outClustersList[clusterIndex];
  bindAttempts = 0;
  matchBindDevices();
}


// eof bindManager.c
