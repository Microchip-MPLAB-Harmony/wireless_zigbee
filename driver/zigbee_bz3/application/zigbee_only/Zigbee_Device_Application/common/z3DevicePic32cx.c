/*******************************************************************************
  Z3 Device Pic32cx Source File

  Company:
    Microchip Technology Inc.

  File Name:
    z3DevicePic32cx.c

  Summary:
    This file contains the Z3 Device Pic32cx Implementation.

  Description:
     This file contains the Z3 Device Pic32cx Implementation.
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

#include <z3device/stack_interface/zgb_api.h>
#include <z3device/stack_interface/bdb/include/bdb_api.h>
#include <z3device/stack_interface/zcl/include/zcl_api.h>
#include <z3device/stack_interface/configServer/include/cs_api.h>
#include <z3device/stack_interface/nwk/include/nwk_api.h>
#include <z3device/stack_interface/bdb/include/BDB_Unpack.h>
#include <configserver/include/configserver.h>
#include <aps/include/apsCommon.h>
#include <zcl/include/zclAttributes.h>
#include <z3device/common/include/z3Device.h>
#include <zcl/include/clusters.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/zgpAppInterface.h>
#ifdef ZAPPSI_HOST
#include <zsiNotify.h>
#endif
#if defined ZAPPSI_HOST
#include <zsiHalSerialization.h>
#endif
#include <app_zigbee/zigbee_console/console.h>
#include <common_files/include/errH.h>
#include "app_zigbee.h"
#include  "app.h"
#include <zdo/include/private/zdoDbg.h>
#include <bdb/include/bdbZllBindings.h>
#include "zllplatform/ZLL/N_Connection/include/N_Connection.h"
#include "zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo.h"
#include "zllplatform/ZLL/N_Connection/include/N_Connection_Internal.h"
#include "zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget.h"

#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#include <z3device/common/include/zgpAppInterface.h>
#endif // APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#endif // _GREENPOWER_SUPPORT_
#ifndef APP_COMMISSIONING_TOUCHLINK
  #define APP_COMMISSIONING_TOUCHLINK 0
#endif

#ifndef APP_COMMISSIONING_STEERING
  #define APP_COMMISSIONING_STEERING 0
#endif

#ifndef APP_COMMISSIONING_FORMING
  #define APP_COMMISSIONING_FORMING 0
#endif

#ifndef APP_COMMISSIONING_FINDING_AND_BINDING
  #define APP_COMMISSIONING_FINDING_AND_BINDING 0
#endif

//Table 4 – Bits of the bdbCommissioningMode attribute
//5.3.2 bdbCommissioningMode attribute
#define BDB_COMMISSIONING_TOUCHLINK       0 //(1)
#define BDB_COMMISSIONING_NWK_STEERING    1 // (2)
#define BDB_COMMISSIONING_NWK_FORMATION   2 // (4)
#define BDB_COMMISSIONING_FINDING_BINDING 3 // (8)

#define TOUCHLINKING_MASK     (1 << BDB_COMMISSIONING_TOUCHLINK)
#define NWK_STEERING_MASK     (1 << BDB_COMMISSIONING_NWK_STEERING)
#define NWK_FORMATION_MASK    (1 << BDB_COMMISSIONING_NWK_FORMATION)
#define FINDING_BINDING_MASK  (1 << BDB_COMMISSIONING_FINDING_BINDING)

#define STEERING_AND_FINDING_BINDING_MASK  (NWK_STEERING_MASK | FINDING_BINDING_MASK)
#define TOUCHLINK_STEERING_FORMING_MASK    (TOUCHLINKING_MASK | NWK_STEERING_MASK | NWK_FORMATION_MASK)

#define APP_MAX_FIND_AND_BIND_ATTEMPTS      (5)
#define VISUALIZATION_PERIOD                (100u)
#define DEFAULT_VISUALIZATION_PERIODS       (1000u / VISUALIZATION_PERIOD)
#define JOIN_NETWORK_VISUALIZATION_PERIODS  (2000u / VISUALIZATION_PERIOD)

#define INTERPAN_PERIOD                     (10000u)

#define IDENTIFY_NON_COLOR_EFFECT false

// the application task will block on this semaphore until we have new data to process

static AppState_t appState = APP_INITIAL_STATE;
AppDeviceState_t appDeviceState = DEVICE_INITIAL_STATE;

static uint8_t epIndex;
static uint16_t visualizationPeriodsCounter;

static void UpdateNetworkIndication(void);
static void QeryingCompleted(void);
static void IdentifyStartIndication(uint16_t timeoutInSec);
static void Connected(void);
static void Disconnected(void);
static void IdentifyStopIndication(void);
static void JoinNetworkIndication(uint16_t groupIdFirst, uint16_t groupIdLast);


/* BDB Event Handlers */
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void interPanModeTimerFired(void);
static void NetworkFormationCompleted(BDB_CommissioningStatus_t status);
static void NetworkSteeringCompleted(BDB_CommissioningStatus_t status);
static void TouchlinkCompleted(BDB_CommissioningStatus_t status);
static void FindingBindingCompleted(BDB_CommissioningStatus_t status);
static void ResetToFactoryDefaults(void);
static void Querying(void);
static void Scanning(void);
static void Identifying(void);
static void Joining(void);
static uint8_t currentCommissioning;
#if BDB_TOUCHLINK_SUPPORT == 1
static void setTargetTypeDone(N_LinkTarget_Status_t status);
#endif
#endif
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void FindingBindingInitiatorModeCompleted(void);
#endif

#if ZB_COMMISSIONING_ON_STARTUP == 1
static void FindingBindingInitiatorModeCompleted(void);
#endif
#ifdef ZAPPSI_HOST
static void resetTimerFired(void);
#endif // ZAPPSI_HOST

static bool commissioningInProgress = false;
#if defined(ZIGBEE_END_DEVICE)
static uint32_t sleepPeriodConfigured;
static bool parentLost = false;
#endif
 
static void visualizationTimerFired(void);

static void networkEventsHandler(SYS_EventId_t eventId, SYS_EventData_t data);

static SYS_EventReceiver_t networkEventsListener  = { .func = networkEventsHandler};

static HAL_AppTimer_t visualizationTimer =
{
  .mode     = TIMER_REPEAT_MODE,
  .interval = VISUALIZATION_PERIOD,
  .callback = visualizationTimerFired
};

#if ZB_COMMISSIONING_ON_STARTUP == 1
static HAL_AppTimer_t interPanModeTimer =
{
  .mode     = TIMER_ONE_SHOT_MODE,
  .interval = INTERPAN_PERIOD,
  .callback = interPanModeTimerFired
};
#endif

#ifdef ZAPPSI_HOST
static HAL_AppTimer_t resetTimer =
{
  .interval = 150,
  .mode     = TIMER_ONE_SHOT_MODE,
  .callback = resetTimerFired,
};
#endif

#ifdef ZAPPSI_HOST
static BdbEventSubscriber_t s_BDB_EventsCallback =
#else
BdbEventSubscriber_t s_BDB_EventsCallback =
#endif
{
  .connected = Connected,
  .disconnected = Disconnected,
  .identifyStartIndication = IdentifyStartIndication,
  .identifyStopIndication = IdentifyStopIndication,
  .updateNetworkIndication = UpdateNetworkIndication,
  .queryingCompleted = QeryingCompleted,
  .joinNetworkIndication = JoinNetworkIndication,
  .SteeringNetwork = NULL,
  .tclkProcedureOngoing = NULL,
  .tclkProcedureCompleted = NULL,
  .addingBindingLinks = NULL,
  .scanIndication = NULL,
#if ZB_COMMISSIONING_ON_STARTUP == 1
  .touchlinkCompleted = TouchlinkCompleted,
  .networkFormationCompleted = NetworkFormationCompleted,
  .SteeringCompleted = NetworkSteeringCompleted,
  .findingBindingCompleted = FindingBindingCompleted,
  .ResetToFactoryDefaults = ResetToFactoryDefaults,
  .querying = Querying,  
  .scanning = Scanning,
  .identifying = Identifying,
  .joining = Joining,
#if ZB_COMMISSIONING_ON_STARTUP == 1
  .findingBindingInitiatorModeCompleted = FindingBindingInitiatorModeCompleted,
#endif  /* ZB_COMMISSIONING_ON_STARTUP == 1 */
#else
  .querying = NULL,  
  .scanning = NULL,
  .identifying = NULL,
  .joining = NULL,
#endif  /* ZB_COMMISSIONING_ON_STARTUP == 1 */
};

static BDB_InvokeCommissioningReq_t commissioningReq;
static bool findAndBind = false;



#if ZB_COMMISSIONING_ON_STARTUP == 1
static uint8_t joinInterval = APP_JOIN_ATTEMPT_INTERVAL;
static uint8_t joinAttempts = APP_JOIN_ATTEMPTS_AMOUNT;
static void joinRetryTimerFired(void);
static void handleTouchlinkFailure(void);

static HAL_AppTimer_t joinRetryTimer =
{
  .interval = APP_JOIN_ATTEMPT_INTERVAL* 1000,
  .mode     = TIMER_ONE_SHOT_MODE,
  .callback = joinRetryTimerFired,
};

static BDB_InitiatorReq_t appInitiatorReq;
#endif

AppBindReq_t* deviceBindReqs[APP_ENDPOINTS_AMOUNT];
BDB_CommissioningMode_t autoCommissionsEnableMask = ((APP_COMMISSIONING_TOUCHLINK << 0) | (APP_COMMISSIONING_STEERING << 1) |
  (APP_COMMISSIONING_FORMING << 2 ) | (APP_COMMISSIONING_FINDING_AND_BINDING << 3));


extern OSAL_QUEUE_HANDLE_TYPE zigbeeRequestQueueHandle;

/**************************************************************************
\brief Create Application queue for zigbee and usart events
***************************************************************************/
void create_app_queue(void)
{
#ifdef H3_INDEPENDENT   
  g_appQueue = xQueueCreate( 64, sizeof(APP_Msg_T) );
 //   APP_Initialize();
#endif    
}

/**************************************************************************
\brief Zigbee API CALL
***************************************************************************/
inline void ZIGBEE_API_CALL(Stack_API_Request_t *request)
{
  if ( OSAL_RESULT_TRUE != OSAL_QUEUE_Send(&zigbeeRequestQueueHandle, &request,10))
  {
    while(1);   // ERROR , Should not hang here, handle with assert
  }
}

/**************************************************************************
\brief Post Zigbee API CALLs into queue
***************************************************************************/

void APP_EvtUpload(void)
{
    APP_Msg_T   appMsg;
    APP_Msg_T   *p_appMsg;

    appMsg.msgId=APP_MSG_ZB_STACK_EVT;

    p_appMsg = &appMsg;
#ifdef H3_INDEPENDENT
    OSAL_QUEUE_Send(&g_appQueue, p_appMsg, 0);
#else
    OSAL_QUEUE_Send(&appData.appQueue, p_appMsg, 0);
#endif

}
/**************************************************************************
\brief Join retry timer fired callback
***************************************************************************/
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void joinRetryTimerFired(void)
{
  commissioningReq.mode = BDB_COMMISSIONING_NWK_STEERING;
  appState = APP_START_NETWORK_STATE;
  //OSAL_SEM_Post(&SEM_ZB_APP_TASK);
  APP_EvtUpload();
}
#endif
/**************************************************************************//**
\brief Checks if initialization has been done
******************************************************************************/
static void visualizationTimerFired(void)
{
  if (visualizationPeriodsCounter)
  {
    visualizationPeriodsCounter--;
    LED_TOGGLE();
  }
  else
  {
    HAL_StopAppTimer(&visualizationTimer);
    LED_OFF();
  }
}

/**************************************************************************//**
\brief Register Endpoint

\returns true, if Register Endpoint is Successful, false otherwise
******************************************************************************/
bool APP_RegisterEndpoint(ZCL_DeviceEndpoint_t *endpoint, AppBindReq_t* bindReq)
{
  if (APP_ENDPOINTS_AMOUNT == epIndex)
    return false;

  ZCL_RegisterEndpoint(endpoint);
  deviceBindReqs[epIndex++] = bindReq;
  return true;
}

/*******************************************************************************
  Function:
    void bdbInitCompleted(void *p)

  Remarks:
   bdb Initialisationn complete

*/
void bdbInitCompleted(void)
{

}

/**************************************************************************//**
\brief Performs operations with network address which depends
  static or dinamyc on addressing type

\returns device type.
*******************************************************************************/
static DeviceType_t detectNwkAddrAndDevType(void)
{
  DeviceType_t deviceType;
#if (1 == CS_NWK_UNIQUE_ADDR)
  ShortAddr_t nwkAddr;

  // Read NWK address as dipswitch's state.
  nwkAddr = NWK_NODE_ADDRESS;
  if (0 == nwkAddr)
    deviceType = DEVICE_TYPE_COORDINATOR;
  else
    deviceType = DEVICE_TYPE_ROUTER;
  // Set parameter to config server
  CS_WriteParameter(CS_NWK_ADDR_ID, &nwkAddr);
#else // (1 != CS_NWK_UNIQUE_ADDR)
  deviceType = (DeviceType_t)APP_DEVICE_TYPE;
#endif // (1 == CS_NWK_UNIQUE_ADDR)
  return deviceType;
}

#if ZB_COMMISSIONING_ON_STARTUP == 1
/**************************************************************************//**
\brief Callback on completion FindingAndBinding as Initiator
******************************************************************************/
static void FindingBindingInitiatorModeCompleted(void)
{
  appSnprintf("CommissioningStatus = Finding and Binding Successful\r\n");
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Finding & Binding Successful");

  if (epIndex < APP_ENDPOINTS_AMOUNT)
    appIdentifyStop();
}
#endif /* #if ZB_COMMISSIONING_ON_STARTUP == 1 */

#if ZB_COMMISSIONING_ON_STARTUP == 1
/**************************************************************************//**
\brief Callback on Querying
******************************************************************************/
static void Querying(void)
{
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Querying in Progress");
}
/**************************************************************************//**
\brief Callback on Scanning in Progress
******************************************************************************/
static void Scanning(void)
{
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Scanning....");  
}
/**************************************************************************//**
\brief Callback on Identifying in Progress
******************************************************************************/
static void Identifying(void)
{
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Identifying....");  
}
/**************************************************************************//**
\brief Callback on Joining in Progress
******************************************************************************/
static void Joining(void)
{
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Joining....");  
}
#endif

/**************************************************************************//**
\brief Callback on completion of Nwk formation
\param status - Commissioning Status
******************************************************************************/
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void NetworkFormationCompleted(BDB_CommissioningStatus_t status)
{
  if (BDB_COMMISSIONING_SUCCESS == status)
  {
    LCD_PRINT(0, 2,"                      ");
    LCD_PRINT(0, 2,"Network Formed");
    currentCommissioning = NWK_FORMATION_MASK;
  }
}

/**************************************************************************//**
\brief Callback on completion of Finding and Binding as Target
\param status - Commissioning STatus
******************************************************************************/
static void FindingBindingCompleted(BDB_CommissioningStatus_t status)
{
  appSnprintf("Identifying is Completed\r\n");
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Identifying Completed");

  currentCommissioning = FINDING_BINDING_MASK;
}

/**************************************************************************//**
\brief Callback on completion of Nwk Steering
\param status - Commissioning Status
******************************************************************************/
static void NetworkSteeringCompleted(BDB_CommissioningStatus_t status)
{
  if (BDB_COMMISSIONING_SUCCESS == status)
  {
    LCD_PRINT(0, 2,"                        ");
    LCD_PRINT(0, 2,"Steering    Sucessful");
    currentCommissioning = NWK_STEERING_MASK;
  }
}

/**************************************************************************//**
\brief Callback on reception of ResetToFactoryBNew command
\param status - Commissioning STatus
******************************************************************************/
static void ResetToFactoryDefaults(void)
{
  LCD_PRINT(0, 2,"                      ");
  LCD_PRINT(0, 1,"Reset To FN");
}

/**************************************************************************//**
\brief Callback on completion of Touchlink commssioning
\param status - Commissioning STatus
******************************************************************************/
static void TouchlinkCompleted(BDB_CommissioningStatus_t status)
{
  if (BDB_COMMISSIONING_SUCCESS == status)
  {
    LCD_PRINT(0, 2,"                      ");
    LCD_PRINT(0, 2,"Touchlink Completed");
    currentCommissioning = TOUCHLINKING_MASK;
  }
}

/**************************************************************************//**
\brief Eanbles the touchlink target type, if touchlinking is supported on a router device
******************************************************************************/
static void setTouchlinkTargetType(void)
{
#if BDB_TOUCHLINK_SUPPORT == 1
  DeviceType_t deviceType;
  BDB_NodeCommissioningCapability_t commissioningCapability;
  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);
  commissioningCapability = BDB_GetCommissioningCapability();
  if ((DEVICE_TYPE_ROUTER == deviceType) && commissioningCapability.touchlinkComissioningSupported)
  {
    N_LinkTarget_SetTargetType(true, setTargetTypeDone); //this implemenetation will be changed
    LCD_PRINT(0, 2,"                      ");
    LCD_PRINT(0, 3,"                      ");
    LCD_PRINT(0, 2," Touchlink Target");
  }
#endif
}
/**************************************************************************//**
\brief InterPan mode timer fired
******************************************************************************/
static void interPanModeTimerFired(void)
{
  setTouchlinkTargetType();
}
#endif
/**************************************************************************
\brief Check the starting of a network is required or not on startup
***************************************************************************/
static bool startNetwork(BDB_CommissioningMode_t commMode)
{
  if ((NWK_FORMATION_MASK == (NWK_FORMATION_MASK & commMode)) || (NWK_STEERING_MASK == (NWK_STEERING_MASK & commMode)) || (TOUCHLINKING_MASK == (TOUCHLINKING_MASK & commMode)) )
    return true;

  return false;
}

/**************************************************************************//**
\brief Listen different events from network

\param[in] eventId - id of raised event;
\param[in] data    - event's data.
******************************************************************************/
static void networkEventsHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  static bool resetToFactoryNew = false;
  
  switch(eventId)
  {
    case BC_EVENT_LEAVE_COMMAND_RECEIVED:
    {
      resetToFactoryNew = true;
      SYS_SubscribeToEvent(BC_EVENT_NETWORK_LEFT, &networkEventsListener);
    }
    break;
    
    case BC_EVENT_NETWORK_LEFT:
    {
      SYS_UnsubscribeFromEvent(BC_EVENT_NETWORK_LEFT, &networkEventsListener);
      if (resetToFactoryNew)
      {
#ifdef _ENABLE_PERSISTENT_SERVER_
        PDS_DeleteAll(false);
#endif
        SystemReset();
      }
      else //need to be checked
      {
        if (startNetwork((APP_COMMISSIONING_TOUCHLINK << 0) | (APP_COMMISSIONING_STEERING << 1) | (APP_COMMISSIONING_FORMING << 2 )))
        {
          appState = APP_START_NETWORK_STATE;
          APP_EvtUpload();
        }
      }
    }
    break;

    case BC_EVENT_NETWORK_ENTERED:      /* The device is in the network */
    { /* To handle finding and binding only enabled case */
      if (APP_START_WAIT_STATE == appState)
      {
        if (findAndBind)
        {
          commissioningReq.mode = BDB_COMMISSIONING_FINDING_BINDING;
          appState = APP_FINDING_BINDING_STATE;
        }
        else
        {
          appState = APP_IN_NETWORK_IDLE_STATE;
        }
        APP_EvtUpload();
      }

    }
    break;
  }
  (void)eventId;
  (void)data;
}


/**************************************************************************
\brief To Handle steeringfailure from application
***************************************************************************/
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void handleSteeringFailure(void)
{
  if (commissioningReq.mode == BDB_COMMISSIONING_NWK_STEERING)
  {
    if (joinInterval && joinAttempts)
    {     
      HAL_StartAppTimer(&joinRetryTimer);
    }
    else if (!joinInterval && joinAttempts)
    {
      commissioningReq.mode = BDB_COMMISSIONING_NWK_STEERING;
      /* Try to rejoin joinAttempts time with no delay */
      appState = APP_START_NETWORK_STATE;
      APP_EvtUpload();
    }
    else
    {
      appSnprintf("CommissioningStatus = No Networks Found\r\n");
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "No Network Found");
      appState = APP_START_NETWORK_STATE;
      APP_EvtUpload();
      return;
    }

    if ( joinAttempts && (joinAttempts !=  0xff))
      joinAttempts--;
  }
}

/**************************************************************************
\brief To Handle touchlinkfailure from application
***************************************************************************/
static void handleTouchlinkFailure(void)
{
  /* Try to rejoin joinAttempts time with no delay */
  appState = APP_START_NETWORK_STATE;
  APP_EvtUpload();
}

/*************************************************************//**
\brief CallBack on finishing the SetTartgetType
*****************************************************************/
#if BDB_TOUCHLINK_SUPPORT == 1
static void setTargetTypeDone(N_LinkTarget_Status_t status)
{
  /* Do Nothing */
  (void)status;
}
#endif
#endif

/**************************************************************************
\brief determine enabled commissioning modes
***************************************************************************/
BDB_CommissioningMode_t determineCommissionMode(uint8_t commMode)
{
  BDB_CommissioningMode_t retMode = 0xff;;
  
  if (autoCommissionsEnableMask & TOUCHLINKING_MASK)
  {
    retMode = BDB_COMMISSIONING_TOUCHLINK;
    autoCommissionsEnableMask &= ~TOUCHLINKING_MASK;

  }
  else if (autoCommissionsEnableMask & NWK_STEERING_MASK)
  {
    retMode = BDB_COMMISSIONING_NWK_STEERING;
        autoCommissionsEnableMask &= ~NWK_STEERING_MASK;
  }
  else if (autoCommissionsEnableMask & NWK_FORMATION_MASK)
  {
    retMode = BDB_COMMISSIONING_NWK_FORMATION;
    autoCommissionsEnableMask &=  ~NWK_FORMATION_MASK;
  }
  else if (autoCommissionsEnableMask & FINDING_BINDING_MASK)
  {
    retMode = BDB_COMMISSIONING_FINDING_BINDING;
    autoCommissionsEnableMask &=  ~FINDING_BINDING_MASK;
  }
  else
  { //error
  }
    return retMode;
}

/**************************************************************************//**
\brief Performs join retries if the steering is nwk failed
*******************************************************************************/
#if ZB_COMMISSIONING_ON_STARTUP == 1
static void commissioningDone(BDB_InvokeCommissioningConf_t *conf)
{
  commissioningInProgress = false;
  switch (conf->status)
  {
    //!< commissioning sub procedure is successful
    case BDB_COMMISSIONING_SUCCESS:
    { 
      switch (currentCommissioning)
      {
        case TOUCHLINKING_MASK:
        {
          appSnprintf("CommissioningStatus = Touchlink successful\r\n");
          appState = APP_IN_NETWORK_STATE;
          LCD_PRINT(0, 2,"                            ");
          LCD_PRINT(0, 2, "Touchlink successful");
        }
        break;
        case NWK_STEERING_MASK:
        {
          appSnprintf("CommissioningStatus = Nwk Steering successful\r\n");
          LCD_PRINT(0, 2, "                          ");
          LCD_PRINT(0, 2, "Steering successful");
          appState = APP_IN_NETWORK_STATE;
        }
        break;
        case NWK_FORMATION_MASK:
        {
          appSnprintf("CommissioningStatus = Nwk Formation successful\r\n");
          LCD_PRINT(0, 2,"                            ");
          LCD_PRINT(0, 2, "Nwk Formation successful");
          appState = APP_IN_NETWORK_PERMITJOIN_STATE;
        }
        break;
        case FINDING_BINDING_MASK:
        {
          currentCommissioning = 0;
          if (epIndex < APP_ENDPOINTS_AMOUNT)
            appState = APP_FINDING_BINDING_STATE;
          else
            appState = APP_IN_NETWORK_IDLE_STATE;
        }
        break;
        default: // Shall not come here
          appState = APP_START_WAIT_STATE;
          appSnprintf("CommissioningStatus = In wait State\r\n");
        break;
      }
      currentCommissioning = 0;
      APP_EvtUpload();
    }
    break;
    //!< The initiator is not address assignment capable during touchlink
    case BDB_COMMISSIONING_NOT_AA_CAPABLE:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "Not Address Capable Device");
      appSnprintf("CommissioningStatus = Device is Not Address Capable\r\n");
      break;
    //!< A network has not been found during network steering or touchlink
    case BDB_COMMISSIONING_NO_NETWORK:
      handleSteeringFailure();
      break;
    //!< A network could not be formed during network formation
    case BDB_COMMISSIONING_FORMATION_FAILURE:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "Network Formation Failed");
      appSnprintf("CommissioningStatus = Network Formation Failed\r\n");
      break;
    //!< No response to an identify query command has been received during finding & binding
    case BDB_COMMISSIONING_NO_IDENTIFY_QUERY_RESPONSE:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "IdentifyQuery Not Received");
      appSnprintf("CommissioningStatus = No IdentifyQueryResponse Received\r\n");
      currentCommissioning = 0;
      if (epIndex < APP_ENDPOINTS_AMOUNT)
         appState = APP_FINDING_BINDING_STATE;
      else
         appState = APP_IN_NETWORK_IDLE_STATE;
      APP_EvtUpload();
      break;
    //!< A binding table entry could not be created due to insufficient space in 
    //the binding table during finding & binding.
    case BDB_COMMISSIONING_BINDING_TABLE_FULL:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "Binding Table Full");
      appSnprintf("CommissioningStatus = Binding Table Full\r\n");
      break;
    //!< No response to a scan request inter-PAN command has been received during touchlink
    case BDB_COMMISSIONING_NO_SCAN_RESPONSE:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "No Scan Response Received");
      appSnprintf("CommissioningStatus = No Scan Response Received\r\n");
      /* If the router device couldn't find any target during touchlinking, let it continue as Target */
      setTouchlinkTargetType();
      handleTouchlinkFailure();
      break;
    //!< The Trust Center link key exchange procedure has failed attempting to 
    //join a centralized security network
    case BDB_COMMISSIONING_TCLK_EX_FAILURE:
      LCD_PRINT(0, 2,"                            ");
      LCD_PRINT(0, 2, "TCLK Exchange Failed");
      appSnprintf("CommissioningStatus = TCLK Exchange Failed\r\n");
      break;
    //!< The given commissioning is not supported
    case BDB_COMMISSIONING_NOT_SUPPORTED:
      appSnprintf("CommissioningStatus = Unsupported Commissioining mode\r\n");
      break;

    default:
      break;
  }
}
#endif
/**************************************************************************//**
\brief Reset the report configuration of the device's reportable attributes

\param[in] none
******************************************************************************/
void resetReportConfig(void)
{
  APS_RegisterEndpointReq_t *endpointDescriptor = NULL;
  uint8_t clusterCount = 0;
  while (NULL != (endpointDescriptor = APS_NextEndpoint(endpointDescriptor)))
  {
    for(clusterCount = 0; clusterCount < endpointDescriptor->simpleDescriptor->AppInClustersCount; clusterCount++)
    {
      ZCL_Cluster_t *cluster = ZCL_GetCluster(endpointDescriptor->simpleDescriptor->endpoint,
                                              endpointDescriptor->simpleDescriptor->AppInClustersList[clusterCount],
                                              ZCL_CLUSTER_SIDE_SERVER);
      ZclAttribute_t *attr = NULL;

      if(!cluster)
        continue;

      attr = (ZclAttribute_t *)cluster->attributes;
      // For all the attributes
      for (uint8_t attrIndex = 0; attrIndex < cluster->attributesAmount; attrIndex++)
      {
        // check if the attribute is reportable and the 'reporting configured' is already set
        if ((attr->properties & ZCL_REPORTABLE_ATTRIBUTE) && (attr->properties & ZCL_REPORTING_CONFIGURED))
        {
          // Resetting the attribute's reporting configuration property
          attr->properties &= ~ZCL_REPORTING_CONFIGURED;
        }
        attr = jumpToNextAttribute(attr);
      }
    }
  }
}
/**************************************************************************//**
\brief Network update notification
\param notify - update notification parameters
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf_CB(ZDO_MgmtNwkUpdateNotf_t *notify)
{
#if ZB_COMMISSIONING_ON_STARTUP == 1
  appSnprintf("Network update status - 0x%02x\r\n", notify->status);
#endif /* #if ZB_COMMISSIONING_ON_STARTUP == 1 */
}

/*******************************************************************************
  Description: just a stub.

  Parameters: none.

  Returns: nothing.
*******************************************************************************/
void ZDO_WakeUpInd_CB(void)
{
}

/**************************************************************************//**
\brief ZDO Binding indication function

\param[out] bindInd - ZDO bind indication parameters structure pointer.
                      For details go to ZDO_BindInd_t declaration
******************************************************************************/
void ZDO_BindIndication_CB(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/**************************************************************************//**
\brief ZDO Unbinding indication function

\param[out] unbindInd - ZDO unbind indication parameters structure pointer.
                        For details go to ZDO_UnbindInd_t declaration
******************************************************************************/
void ZDO_UnbindIndication_CB(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}

/**************************************************************************//**
\brief ZDO_ResetNetwork Confirmation function

\param[out] conf - Confirmation structure with status
******************************************************************************/
void ZDO_ResetNetworkConf_CB(ZDO_ResetNetworkConf_t *status)
{
  sysAssert(ZDO_SUCCESS_STATUS == status, ZDOINIT_ZDOINITRESETNETWORKCONF_0);
  APP_EvtUpload();
}

/**************************************************************************//**
\brief Check the commssioning in progress status

\returns true, if commissioning is in progress, false otherwise
******************************************************************************/
bool isCommssioiningInProgress(void)
{
  return commissioningInProgress;
}

/**************************************************************************//**
\brief Application and stack parameters initialization
*****************************************************************************/
static void initApp(void)
{
  ExtAddr_t extAddr;
  DeviceType_t deviceType;
  //Reads the UID set in configuration.h
  CS_ReadParameter(CS_UID_ID,&extAddr);
  if (extAddr == 0 || extAddr > APS_MAX_UNICAST_EXT_ADDRESS)
  {
    //BSP_ReadUid(&extAddr); //Will read the UID from chip
    CS_WriteParameter(CS_UID_ID, &extAddr); //Writes the read UID to the ram
  }

  CS_WriteParameter(CS_PERMIT_DURATION_ID, &(uint8_t){0});

  deviceType = detectNwkAddrAndDevType();
  // Set parameters to config server
  CS_WriteParameter(CS_DEVICE_TYPE_ID, &deviceType);

  errHInit();
  /* BDB Advance features like parallel Finding & Binding are enabled which is non Compliance */
  /* Few additional prints are added for demopurpose */
#if ZB_COMMISSIONING_ON_STARTUP == 1
  BDB_EnableAutoCommissioning();
#endif
  BDB_EventsSubscribe(&s_BDB_EventsCallback);
  BDB_Init(bdbInitCompleted);
  //BSP_OpenLeds();
  appDeviceInit();

#ifdef _ZCL_REPORTING_SUPPORT_
  resetReportConfig();
  ZCL_StartReporting();
#endif

#ifdef _GREENPOWER_SUPPORT_
#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
  ZGP_AppInit();
#endif //#if APP_ZGP_DEVICE_TYPE >= APP_ZGP_DEVICE_TYPE_PROXY_BASIC
#endif //_GREENPOWER_SUPPORT_

  epIndex = 0;
 

#if ZB_COMMISSIONING_ON_STARTUP == 1
  SYS_SubscribeToEvent(BC_EVENT_LEAVE_COMMAND_RECEIVED, &networkEventsListener);
  SYS_SubscribeToEvent(BC_EVENT_NETWORK_ENTERED, &networkEventsListener);

  /* Check the NFN Status of the device */
  if (BDB_GetBdbNodeIsOnANetwork())
  {
#if defined(ZIGBEE_END_DEVICE)
  if (DEVICE_TYPE_END_DEVICE == deviceType)
  {
#if BDB_TOUCHLINK_SUPPORT == 1
    if (!N_DeviceInfo_IsFactoryNew() && !N_Connection_IsConnected())
#else
    if(!N_Connection_IsConnected())
#endif   //#if BDB_TOUCHLINK_SUPPORT == 1
    {
      N_Connection_ReconnectUrgent();
    }
  }

#endif   //#if defined(ZIGBEE_END_DEVICE)
    appState = APP_IN_NETWORK_IDLE_STATE;    
    APP_EvtUpload();
    LCD_PRINT(0, 1,"                            ");
    LCD_PRINT(0, 1, "NFN Node");
    return;
  }
  commissioningReq.BDB_InvokeCommissioningConf = commissioningDone;
  if ((autoCommissionsEnableMask & FINDING_BINDING_MASK) == FINDING_BINDING_MASK)
  {
    findAndBind = true;
  }
  else
    findAndBind = false;

  /* Next action taken based on commissoining mode selected */
  if (startNetwork(autoCommissionsEnableMask))
  {
    appState = APP_START_NETWORK_STATE;
  }
  else
#endif /* #if ZB_COMMISSIONING_ON_STARTUP == 1 */
    appState = APP_START_WAIT_STATE;

  APP_EvtUpload();
}

/************************BDB Evenet Handling ******************************/
/**************************************************************************//**
\brief Callback on succeessfully connected to a network

******************************************************************************/
static void Connected(void)
{
  ExtPanId_t       csExtPanId;
  ExtPanId_t       csNwkExtPanId;
#if (MICROCHIP_APPLICATION_SUPPORT == 1)
    CS_ReadParameter(CS_EXT_PANID_ID, &csExtPanId);
    // CS_EXT_PANID is 0 on default, after joining any network its ext panId shall be retained
    if (!csExtPanId)
    {
      CS_ReadParameter(CS_NWK_EXT_PANID_ID, &csNwkExtPanId);
      CS_WriteParameter(CS_EXT_PANID_ID, &csNwkExtPanId);
    }
#endif

#if defined(ZIGBEE_END_DEVICE)
  DeviceType_t deviceType;

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);

  if ((DEVICE_TYPE_END_DEVICE == deviceType ) && parentLost)
  {
    // On reconnection, end device will restore its sleep period value
    // because it was set to zero on previous disconnected event
    if (sleepPeriodConfigured)
    {
      CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriodConfigured);
      sleepPeriodConfigured = 0;
    }
    parentLost = false;
  }
#endif

#if ZB_COMMISSIONING_ON_STARTUP == 1
 /* Print is excluded for Coordinator */
#ifdef COMBINED_INTERFACE_ROUTER
  appSnprintf("Connected\r\n");
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2, "Connected");
#elif (APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_COMBINED_INTERFACE)
  appSnprintf("Connected\r\n");
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2, "Connected");
#endif
  /* Start OTAU functionalty */
  appDeviceTaskHandler();
#endif   /* #if ZB_COMMISSIONING_ON_STARTUP == 1 */
  LCD_PRINT(0, 2, "         ");
  LCD_PRINT(0, 2,"NFN");
}

/**************************************************************************//**
\brief Callback on disconnection from a network

******************************************************************************/
static void Disconnected(void)
{
#if defined(ZIGBEE_END_DEVICE)
  DeviceType_t deviceType;

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);

  if (DEVICE_TYPE_END_DEVICE == deviceType)
  {
    uint32_t sleepPeriod;
    parentLost = true;
    // When disconnected event happens, then device won't not in network.
    // so settting end device sleep time to zero so that it will not do 
    // slow polling i.e polling in sleep period interval and taking backup of 
    // sleep period value
    CS_ReadParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
    if (sleepPeriod)
    {
      sleepPeriodConfigured = sleepPeriod;
      sleepPeriod = 0;
      CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
    }
    N_Connection_Reconnect();
  }
#endif
  
#if ZB_COMMISSIONING_ON_STARTUP == 1
  appSnprintf("Disconnected\r\n");
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Disconnected");
#endif /* #if ZB_COMMISSIONING_ON_STARTUP == 1 */
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"FN");  
}

/**************************************************************************//**
\brief Callback on completion of Nwk Update
******************************************************************************/
static void UpdateNetworkIndication(void)
{

}

/**************************************************************************//**
\brief Callback on completion of Querying
******************************************************************************/
static void QeryingCompleted(void)
{
  LCD_PRINT(0, 2,"                            ");
  LCD_PRINT(0, 2,"Querying Completed");
}

/**************************************************************************//**
\brief Callback on Start of Identification as Target
\param timeoutInSec - identifying time secs
******************************************************************************/
static void IdentifyStartIndication(uint16_t timeoutInSec)
{
#if ZB_COMMISSIONING_ON_STARTUP == 1
  HAL_StopAppTimer(&interPanModeTimer);
  HAL_StartAppTimer(&interPanModeTimer);
  LCD_PRINT(0, 2,"                      ");
  LCD_PRINT(0, 2,"Indentify Started");
  
  if (!visualizationPeriodsCounter)
  {
    // Converting to ms
    visualizationPeriodsCounter = (timeoutInSec == 0xFFFF) ? DEFAULT_VISUALIZATION_PERIODS : ((timeoutInSec * 1000)/VISUALIZATION_PERIOD);
    HAL_StartAppTimer(&visualizationTimer);
    LED_ON();
    appIdentifyStart(visualizationPeriodsCounter, IDENTIFY_NON_COLOR_EFFECT, 0u);
  }
  else
  {
    // Converting to ms
    visualizationPeriodsCounter = MAX(visualizationPeriodsCounter, ((timeoutInSec * 1000)/VISUALIZATION_PERIOD));
  }
#else
  visualizationPeriodsCounter = (timeoutInSec == 0xFFFF) ? DEFAULT_VISUALIZATION_PERIODS : timeoutInSec;
  appIdentifyStart(visualizationPeriodsCounter, IDENTIFY_NON_COLOR_EFFECT, 0u);
  HAL_StartAppTimer(&visualizationTimer);
  LED_ON();
#endif
}

/**************************************************************************//**
\brief Stops identifying.
******************************************************************************/
static void IdentifyStopIndication(void)
{
  visualizationPeriodsCounter = 0;
  HAL_StopAppTimer(&visualizationTimer);
  appIdentifyStop();
  LED_OFF();
}
/**************************************************************************//**
\brief Indication that the device has been linked

\param[in] groupIdFirst - the first group identifier assigned to
  the device during linking; zero if no groups where assigned;
\param[in] groupIdLast  - the last group identifier assigned to
  the device during linking; zero if no groups where assigned
******************************************************************************/
static void JoinNetworkIndication(uint16_t groupIdFirst, uint16_t groupIdLast)
{
  if (!visualizationPeriodsCounter)
  {
    visualizationPeriodsCounter = JOIN_NETWORK_VISUALIZATION_PERIODS;
    HAL_StartAppTimer(&visualizationTimer);
    LED_ON();
  }
  else
  {
    visualizationPeriodsCounter = MAX(visualizationPeriodsCounter, JOIN_NETWORK_VISUALIZATION_PERIODS);
  }
  (void)groupIdFirst;
  (void)groupIdLast;
}

/**************************************************************************//**
\brief Application task handler
******************************************************************************/
void process_ZB_evt(void)
{

  switch (appState)
  {
      // node is in initial state
      case APP_INITIAL_STATE:                 // Initial (after RESET) state
        initApp();                            // Init application
        break;

      case APP_START_WAIT_STATE:              //do nothing wait for user input to start commissioning
        // appSnprintf("App in wait State\r\n");
        break;

#if ZB_COMMISSIONING_ON_STARTUP == 1
      case APP_START_NETWORK_STATE:
      {
        LCD_PRINT(0, 2,"                            ");
        LCD_PRINT(0, 2, "Started Commissioning");
        commissioningInProgress = true;
        commissioningReq.mode = determineCommissionMode();
        BDB_InvokeCommissioning(&commissioningReq);
      }
      break;

      case APP_IN_NETWORK_STATE:              // Normal operating
      {
        if (findAndBind)
        {         
         commissioningReq.mode = BDB_COMMISSIONING_FINDING_BINDING;
         appState = APP_FINDING_BINDING_STATE;
        }
        else
        {
          appState = APP_IN_NETWORK_IDLE_STATE;
        }
        APP_EvtUpload();
      }
      break;

      case APP_IN_NETWORK_PERMITJOIN_STATE:
      {
        commissioningReq.mode = BDB_COMMISSIONING_NWK_STEERING;   //To do PermitJoin
        commissioningInProgress = true;
        BDB_InvokeCommissioning(&commissioningReq);
      }
      break;

      case APP_FINDING_BINDING_STATE:
      {
        AppBindReq_t *currBindReq = deviceBindReqs[epIndex++];
        
        appInitiatorReq.initiatorEndpoint = currBindReq->srcEndpoint;
        appInitiatorReq.clientClustersCount = currBindReq->remoteServersCnt;
        appInitiatorReq.serverClustersCount = currBindReq->remoteClientsCnt;

        appInitiatorReq.clientClustersList = currBindReq->remoteServers;
        appInitiatorReq.serverClustersList = currBindReq->remoteClients;

        appInitiatorReq.callback = currBindReq->callback;
        appInitiatorReq.groupId = currBindReq->groupId;

        commissioningReq.initiatorReq = &appInitiatorReq;
        commissioningInProgress = true;
        BDB_InvokeCommissioning(&commissioningReq);
      }
      break;
      case APP_IN_NETWORK_IDLE_STATE:
        break;
#endif
      default:
        break;
  }
}


#if defined WIN
/**************************************************************************//**
\brief Indicates reset Application.

\param[out]
\return none
******************************************************************************/
void restartApp(void)
{
  appState = APP_INITIAL_STATE;
  appDeviceState = DEVICE_INITIAL_STATE;
  idenityResetSubscribers();
  HAL_ResetAllTimers();
  BDB_ResetFsm();
  SYS_EnableTask(APL_TASK_ID);
  SYS_EnableTask(ZLL_TASK_ID);
  SYS_EnableTask(ZCL_TASK_ID);
  SYS_SysInit();
}
#endif
