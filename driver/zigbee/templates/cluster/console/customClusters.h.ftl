#ifndef _CUSTOMCLUSTER_H
#define _CUSTOMCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
<#assign customClusterServerCount = 0>
<#assign customClusterClientCount = 0>

<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >

  <#if (DEVICE == "SERVER")  >
  <#assign customClusterServerCount = customClusterServerCount + 1> 

  <#elseif (DEVICE == "CLIENT") >
  <#assign customClusterClientCount = customClusterClientCount + 1>

  </#if>

</#list>

<#function customClusterCount DEVICE>
<#assign count = ("customCluster"+ DEVICE?capitalize +"Count")?eval>

<#if (count != 0) >
<#return "+ "+ count>

<#else>
<#return "">
</#if>

</#function>

#define CUSTOM_SERVER_CLUSTERS_COUNT     ${NUMBER_OF_SERVER_CLUSTERS_COUNT}+1 ${customClusterCount("SERVER")}
 
#define CUSTOM_CLIENT_CLUSTERS_COUNT   ${NUMBER_OF_CLIENT_CLUSTERS_COUNT}+1 ${customClusterCount("CLIENT")}

#define CUSTOM_SERVER_CLUSTER_INIT_COUNT    CUSTOM_SERVER_CLUSTERS_COUNT

#define CUSTOM_CLIENT_CLUSTER_INIT_COUNT    CUSTOM_CLIENT_CLUSTERS_COUNT

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t customServerClusters[CUSTOM_SERVER_CLUSTERS_COUNT];
extern ClusterId_t customServerClusterIds[CUSTOM_SERVER_CLUSTERS_COUNT];
extern void (*customServerClusterInitFunctions[CUSTOM_SERVER_CLUSTER_INIT_COUNT])();

extern ZCL_Cluster_t customClientClusters[CUSTOM_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t customClientClusterIds[CUSTOM_CLIENT_CLUSTERS_COUNT];
extern void (*customClientClusterInitFunctions[CUSTOM_CLIENT_CLUSTER_INIT_COUNT])();


#endif // _CUSTOMCLUSTER_H

// eof customClusters.h
