/*******************************************************************************
  Custom Time Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customTimeCluster.c

  Summary:
    This file contains Custom Time Cluster Implementation.

  Description:
    This file contains Custom Time Cluster Implementation.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/common/include/appConsts.h>
#include <z3device/custom/include/customTimeCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclAttributes.h>
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/app_zigbee_handler.h>

/******************************************************************************
                    Defines section
******************************************************************************/
<#if (TIME_CLUSTER_CS != "CLIENT")>
#define ONE_SEC_TIME                     1000L
#define UTCTIME_START_YEAR               2000L
#define NO_OF_SECONDS_PER_MIN            60L
#define NO_OF_SECONDS_PER_HOUR           3600L
#define NO_OF_SECONDS_PER_DAY            (NO_OF_SECONDS_PER_HOUR*24)
#define NO_OF_SECONDS_PER_YEAR           (NO_OF_SECONDS_PER_DAY*365)
#define NO_OF_SECONDS_PER_LEAP_YEAR      (NO_OF_SECONDS_PER_DAY*366)
#define NO_OF_LEAP_PER_HUNDRED_YRS       24L
// UTC + 5:30
#define TIME_ZONE_INDIA                  ((NO_OF_SECONDS_PER_HOUR*5) + (NO_OF_SECONDS_PER_MIN*30))
#define TIME_STATUS_ATTR_MASK            0x02
#define INIT_UTC_TIME                    { .date = 12,\
                                           .month = 12,\
                                           .year = 2012,\
                                           .hour = 00,\
                                           .minute = 00,\
                                           .seconds = 00\
                                         }
 </#if>
/******************************************************************************
                   Prototypes section
******************************************************************************/
<#if (TIME_CLUSTER_CS != "CLIENT")>
static void timeUpdateClockTime(void);
static bool timeIsLeapYear(uint16_t year);
uint32_t timeGetStandardTime(void);
void timeUpdateLocalTimeForDst(void);
static void timeClusterEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
static void customTimeAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
 </#if>
/******************************************************************************
                    Global variables
******************************************************************************/
<#if (TIME_CLUSTER_CS != "CLIENT")>
ZCL_TimeClusterServerAttributes_t customTimeClusterServerAttributes =
{
  ZCL_DEFINE_TIME_CLUSTER_SERVER_ATTRIBUTES()
};
</#if>
<#if (TIME_CLUSTER_CS != "SERVER")>
ZCL_TimeClusterClientAttributes_t customTimeClusterClientAttributes=
{
  ZCL_DEFINE_TIME_CLUSTER_CLIENT_ATTRIBUTES() 
};
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")>
static SYS_EventReceiver_t customTimeEventReceiver = {.func = timeClusterEventListener};
uint8_t dstUpdatedInLocalTime = 0;
/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t clockTimeTimer;
</#if>
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Time cluster
******************************************************************************/
void customTimeClusterInit(void)
{
<#if (TIME_CLUSTER_CS != "CLIENT")>
  dateTime_t dateTimeInit = INIT_UTC_TIME;
  
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TIME_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
</#if>
<#if (TIME_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *timeCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TIME_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_CLUSTERREVISION == true)>
  customTimeClusterServerAttributes.clusterVersion.value = TIME_CLUSTER_VERSION;
 </#if>
  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = customTimeAttrEventInd;
  }
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>
  customTimeClusterServerAttributes.time.value = CCPU_TO_LE16(timeCalculateUTCTime(&dateTimeInit));
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>
  customTimeClusterServerAttributes.timeStatus.value.master = TIME_SERVER_MASTER;
  customTimeClusterServerAttributes.timeStatus.value.masterZoneDst = TIME_SERVER_MASTER_ZONE_DST;
  customTimeClusterServerAttributes.timeStatus.value.synchronized = 0;
  customTimeClusterServerAttributes.timeStatus.value.superseding = 0;
  customTimeClusterServerAttributes.timeStatus.value.reserved = 0;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>
  // Since the master bit is set change the time attribute as READONLY.
  customTimeClusterServerAttributes.time.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true)>
  // Since the masterZoneDst bit is set change zone and Dst attributes as READONLY.
  customTimeClusterServerAttributes.timeZone.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSTART == true)>
  customTimeClusterServerAttributes.dstStart.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTEND == true)>
  customTimeClusterServerAttributes.dstEnd.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSHIFT == true)>
  customTimeClusterServerAttributes.dstShift.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true)>
  customTimeClusterServerAttributes.timeZone.value = CCPU_TO_LE16(TIME_ZONE_INDIA);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSTART == true)>
  customTimeClusterServerAttributes.dstStart.value = CCPU_TO_LE16(ZCL_TIME_CLUSTER_DEF_INVALID_VALUE);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTEND == true)>
  customTimeClusterServerAttributes.dstEnd.value = CCPU_TO_LE16(ZCL_TIME_CLUSTER_DEF_INVALID_VALUE);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSHIFT == true)>
  customTimeClusterServerAttributes.dstShift.value = CCPU_TO_LE16(ZCL_TIME_CLUSTER_DEF_ZERO_VALUE);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_STDTIME == true)>
  customTimeClusterServerAttributes.standardTime.value = CCPU_TO_LE16(timeGetStandardTime());
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
  // no day light saving hence local time is standard time
  customTimeClusterServerAttributes.localTime.value = CCPU_TO_LE16(timeGetStandardTime());
</#if>
  // no update required for local time
  dstUpdatedInLocalTime = true;
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LASTSETTIME == true)>
  customTimeClusterServerAttributes.lastSetTime.value = customTimeClusterServerAttributes.time.value;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_VALIDUNTILTIME == true)>
  customTimeClusterServerAttributes.validUntilTime.value = CCPU_TO_LE16(ZCL_TIME_CLUSTER_DEF_INVALID_VALUE);
</#if>
  //start a timer to update the time value
  // if a RTC is used, this shall be removed
  clockTimeTimer.interval = ONE_SEC_TIME;
  clockTimeTimer.mode = TIMER_REPEAT_MODE;
  clockTimeTimer.callback = timeUpdateClockTime;
  HAL_StartAppTimer(&clockTimeTimer);
<#if (TIME_CLUSTER_CS != "SERVER")  && (TCC_CLUSTERREVISION == true)>
  customTimeClusterClientAttributes.clusterVersion.value = TIME_CLUSTER_VERSION;
</#if>
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")>
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &customTimeEventReceiver);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")>
  if(cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
<#else>
  if(timeCluster)
    timeCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
</#if>
}

<#if (TIME_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Update time, standard and local time

\param NA
******************************************************************************/
static void timeUpdateClockTime(void)
{
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>
  customTimeClusterServerAttributes.time.value += 1;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_STDTIME == true)>
  customTimeClusterServerAttributes.standardTime.value += 1;
</#if>

  if(dstUpdatedInLocalTime)
  {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
    customTimeClusterServerAttributes.localTime.value += 1;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTEND == true)>
    if(customTimeClusterServerAttributes.time.value >= customTimeClusterServerAttributes.dstEnd.value)
    {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
      customTimeClusterServerAttributes.localTime.value = timeGetStandardTime();
</#if>
    }
</#if>
  }
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
  else
  {
    timeUpdateLocalTimeForDst();
  }
</#if>
}
/**************************************************************************//**
\brief find whether an year is leap year or not 

\param year
******************************************************************************/
static bool timeIsLeapYear(uint16_t year)
{
  if (year%400 == 0)
    return true;
  else if (year%100 == 0)
    return false;
  else if (year%4 == 0)
    return true;
  else
    return false;
}
/**************************************************************************//**
\brief Number of leap years from 2000 till given year

\param start year, end year
******************************************************************************/
static uint8_t timeCountNoOfLeapYears(uint16_t currYear)
{
  // UTCTIME_START_YEAR is a leap year
  uint16_t noOfLeapYears = 0x0001;
  uint16_t noOfYears;
  uint16_t temp;

  if(currYear < UTCTIME_START_YEAR)
    return 0;

  noOfYears = currYear - UTCTIME_START_YEAR;
  if(noOfYears >= 100)
  {
    temp = noOfYears/100;
    noOfLeapYears += temp * NO_OF_LEAP_PER_HUNDRED_YRS;
  }
  if(noOfYears >= 400)
  {
    temp = noOfYears/400;
    // Every 100th year is not leap year unless it is divided by 400
    // hence for every 400 years there are 3 years divisible by 100 but not leap years
    noOfLeapYears += temp;
  }
  temp = noOfYears%100;
  noOfLeapYears += temp/4;

  return noOfLeapYears;
}
/**************************************************************************//**
\brief find UTCTime - the no of seconds elapsed since  
                      0hrs 0mins 0secs of 1st January,2000
\param pointer to dateTime structure
******************************************************************************/
uint32_t timeCalculateUTCTime(dateTime_t* dateTime)
{
  uint16_t i = 0;
  uint32_t utcTime = 0;
  //UTCTime data type mentioned in cluster specification starts by 2000
  if(dateTime->year < UTCTIME_START_YEAR)
    return ZCL_TIME_CLUSTER_DEF_ZERO_VALUE;
   
  utcTime = (NO_OF_SECONDS_PER_YEAR * (dateTime->year - UTCTIME_START_YEAR));
  utcTime += NO_OF_SECONDS_PER_DAY * timeCountNoOfLeapYears(dateTime->year - 1);
  for(i = MONTH_JANUARY; i< dateTime->month; i++)
  {
    switch(i)
    {
      case MONTH_JANUARY:
      case MONTH_MARCH:
      case MONTH_MAY:
      case MONTH_JULY:
      case MONTH_AUGUST:
      case MONTH_OCTOBER:
      case MONTH_DECEMBER:
        utcTime += NO_OF_SECONDS_PER_DAY * 31;
        break;
      case MONTH_APRIL:
      case MONTH_JUNE:
      case MONTH_SEPTEMBER:
      case MONTH_NOVEMBER:
        utcTime += NO_OF_SECONDS_PER_DAY * 30;
        break;
      case MONTH_FEBRUARY:
        {
          if(timeIsLeapYear(dateTime->year))
            utcTime += NO_OF_SECONDS_PER_DAY * 29;
          else
            utcTime += NO_OF_SECONDS_PER_DAY * 28;
          break;
        }
      default:
        break;
     }
   }
  utcTime += ((dateTime->date - 1) * NO_OF_SECONDS_PER_DAY) + (dateTime->hour * NO_OF_SECONDS_PER_HOUR) +
             (dateTime->minute * NO_OF_SECONDS_PER_MIN) + dateTime->seconds;
  return utcTime;
}
/**************************************************************************//**
\brief to get the standard time considering time and timeZone
\param none
******************************************************************************/
inline uint32_t timeGetStandardTime(void)
{
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true)>
  return (customTimeClusterServerAttributes.time.value + customTimeClusterServerAttributes.timeZone.value);
<#else>
  return (customTimeClusterServerAttributes.time.value);
</#if>
}
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
/**************************************************************************//**
\brief to get the local time considering time, timeZone and DST
\param none
******************************************************************************/
void timeUpdateLocalTimeForDst(void)
{
  if(dstUpdatedInLocalTime)
    return;
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSTART == true) && (TC_DSTEND == true)>  
  if(customTimeClusterServerAttributes.time.value >= customTimeClusterServerAttributes.dstStart.value &&
       customTimeClusterServerAttributes.time.value <= customTimeClusterServerAttributes.dstEnd.value)
  {

     // time is in the day light saving period local time needs to be shifted
     customTimeClusterServerAttributes.localTime.value = customTimeClusterServerAttributes.dstShift.value +
                                                     timeGetStandardTime();
     dstUpdatedInLocalTime = true;
  }
  else
     customTimeClusterServerAttributes.localTime.value = timeGetStandardTime();
</#if>
}
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>
/**************************************************************************//**
\brief to read the UTCTime
\param none
******************************************************************************/
uint32_t timeReadTimeAttribute(void)
{
  return customTimeClusterServerAttributes.time.value;
}
</#if>
/**************************************************************************//**
\brief set the UTCTime
\param date and time
******************************************************************************/
void timeSetTimeAttribute(dateTime_t setDateTime)
{
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>
  customTimeClusterServerAttributes.time.value = timeCalculateUTCTime(&setDateTime);
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LASTSETTIME == true)>
  // store the current time in last set time
  customTimeClusterServerAttributes.lastSetTime.value = customTimeClusterServerAttributes.time.value;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_STDTIME == true)>
  customTimeClusterServerAttributes.standardTime.value = timeGetStandardTime();
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
  dstUpdatedInLocalTime = false;
  // local time
  timeUpdateLocalTimeForDst();
</#if>
}
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>
/**************************************************************************//**
\brief  set the time status attribute bits
\param master - true if the server is the master
       synchronized - true if the time is synchronized with the network
       masterZoneDST - true if the server is the master for timeZone and DST
       Superseding - true if the server shall be choosen as best among other servers
******************************************************************************/
void timeSetTimeStatus(bool master, bool synchronized, bool masterZoneDst, bool superseding)
{
  customTimeClusterServerAttributes.timeStatus.value.master = master;
  // Since the master bit is set change time attribute as READONLY.
  if(master == true)
  {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>    
    customTimeClusterServerAttributes.timeStatus.value.synchronized = false;
</#if><#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>    
    customTimeClusterServerAttributes.time.properties |= ZCL_READONLY_ATTRIBUTE;
</#if>    
  }
  else
  {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIME == true)>    
    customTimeClusterServerAttributes.time.properties &= ~ZCL_READONLY_ATTRIBUTE; 
</#if><#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>    
    customTimeClusterServerAttributes.timeStatus.value.synchronized = synchronized;
</#if>    
  }
  
  customTimeClusterServerAttributes.timeStatus.value.masterZoneDst = masterZoneDst;
  // Since the masterZoneDst bit is set change zone and Dst attributes as READONLY.
  if(masterZoneDst == true)
  {
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true)>    
    customTimeClusterServerAttributes.timeZone.properties |= ZCL_READONLY_ATTRIBUTE;
  </#if>
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSTART == true)>
    customTimeClusterServerAttributes.dstStart.properties |= ZCL_READONLY_ATTRIBUTE;
  </#if>
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTEND == true)>
    customTimeClusterServerAttributes.dstEnd.properties |= ZCL_READONLY_ATTRIBUTE;
  </#if>
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSHIFT == true)>
    customTimeClusterServerAttributes.dstShift.properties |= ZCL_READONLY_ATTRIBUTE;
  </#if> 
  }
  else
  {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true)>    
    customTimeClusterServerAttributes.timeZone.properties &= ~ ZCL_READONLY_ATTRIBUTE;
</#if>    
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSTART == true)>
    customTimeClusterServerAttributes.dstStart.properties &= ~ZCL_READONLY_ATTRIBUTE;
  </#if>
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTEND == true)>
    customTimeClusterServerAttributes.dstEnd.properties &= ~ZCL_READONLY_ATTRIBUTE;
  </#if>
  <#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_DSTSHIFT == true)>
    customTimeClusterServerAttributes.dstShift.properties &= ~ZCL_READONLY_ATTRIBUTE;
  </#if> 
  }
  customTimeClusterServerAttributes.timeStatus.value.superseding = superseding;  
}
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMEZONE == true) && (TC_DSTSTART == true) && (TC_DSTEND == true) && (TC_DSTSHIFT == true)>
/**************************************************************************//**
\brief set the time zone and DST attributes
\param timeZone, dstStart, dstEnd and dstShift in seconds
******************************************************************************/
void timeSetTimezoneAndDSTAttributes(int32_t timeZone, uint32_t dstStart, uint32_t dstEnd, int32_t dstShift)
{
  customTimeClusterServerAttributes.timeZone.value = timeZone;
  customTimeClusterServerAttributes.dstStart.value = dstStart;
  customTimeClusterServerAttributes.dstEnd.value   = dstEnd;
  customTimeClusterServerAttributes.dstShift.value = dstShift;

  if(customTimeClusterServerAttributes.dstStart.value == ZCL_TIME_CLUSTER_DEF_INVALID_VALUE ||
   customTimeClusterServerAttributes.dstEnd.value == ZCL_TIME_CLUSTER_DEF_INVALID_VALUE ||
   customTimeClusterServerAttributes.dstShift.value == ZCL_TIME_CLUSTER_DEF_ZERO_VALUE )
  {
    dstUpdatedInLocalTime = true;
  }
  else
  {
    dstUpdatedInLocalTime = false;
  }
}
</#if>
/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customTimeAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_TIME;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
 
  if(attributeId == ZCL_TIME_CLUSTER_SERVER_TIME_ATTRIBUTE_ID && event == ZCL_WRITE_ATTRIBUTE_EVENT)
  {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LASTSETTIME == true)>
    customTimeClusterServerAttributes.lastSetTime.value = customTimeClusterServerAttributes.time.value;
</#if>
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_STDTIME == true)>
    customTimeClusterServerAttributes.standardTime.value = timeGetStandardTime();
</#if>
    dstUpdatedInLocalTime = false;
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_LOCALTIME == true)>
    // local time
    timeUpdateLocalTimeForDst();
</#if>
  }
  APP_Zigbee_Handler(eventItem);
}
/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void timeClusterEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;
  int16_t requestedValue = 0;
  if (BC_ZCL_EVENT_ACTION_REQUEST == eventId && ZCL_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
  {
     ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
     if((TIME_CLUSTER_ID != zclWriteAttrReq->clusterId) || 
              (ZCL_CLUSTER_SIDE_SERVER != zclWriteAttrReq->clusterSide))
     {
       return;
     }
     actionReq->denied = 0U;
     switch(zclWriteAttrReq->attrId)
     {
       case ZCL_TIME_CLUSTER_SERVER_TIME_ATTRIBUTE_ID:
       {
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>
         if(customTimeClusterServerAttributes.timeStatus.value.master == true ||
            customTimeClusterServerAttributes.timeStatus.value.superseding == true)
           actionReq->denied = 1U;
</#if>
       }
         break;
       case ZCL_TIME_CLUSTER_SERVER_TIME_STATUS_ATTRIBUTE_ID:
       { 
<#if (TIME_CLUSTER_CS != "CLIENT")  && (TC_TIMESTATUS == true)>
         requestedValue = *((int8_t*)(zclWriteAttrReq->attrValue));
         //Allow to write only the synchronized bit if the master bit is 0
         if(!customTimeClusterServerAttributes.timeStatus.value.master && 
            (requestedValue == 0x00 || requestedValue == 0x02))
         {
           *((int8_t*)(zclWriteAttrReq->attrValue)) |= customTimeClusterServerAttributes.timeStatus.value.masterZoneDst |
                                                       customTimeClusterServerAttributes.timeStatus.value.superseding;
         }
         else
           actionReq->denied = 1U;
</#if>
       }
         break;
     default:
         break;
      }
    } 
}
</#if>
#endif // APP_DEVICE_TYPE_CUSTOM_DEVICE

// eof customTimeCluster.c
