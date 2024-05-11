/**************************************************************************//**
  \file  rMain.c

  \brief Main

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include  "app.h"
#include <rTypes.h>
#include <rParser.h>
#include <rMem.h>
#include <rEvents.h>
#include <rZcl.h>
#include <rSys.h>
//#include <leds.h>
#include <aps/include/aps.h>
#include <zigbee/ZAppSi/z3commonfiles/include/console.h>
#include <bufferallocator.h>
#include <ZAppSiSerialManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <rInterpan.h>
#include <systemenvironment/include/sysIdleHandler.h>
#include <hal/include/sleep.h>
#include <systemenvironment/include/sysAssert.h>
//#include "compiler.h"
#include <zigbee/z3device/common/include/system.h>
#ifdef _USE_RTOS_
#include <z3device/stack_Interface/zgb_api.h>
#if (BDB_SUPPORT == 1)
#include <z3device/stack_Interface/bdb/include/bdb_api.h>
#include <z3device/stack_Interface/zcl/include/zcl_api.h>
#endif
#include <z3device/stack_Interface/configServer/include/cs_api.h>
#include "osal/osal_freertos.h"
#endif
#include <pds/include/wlPdsMemIds.h>

#if (BDB_SUPPORT == 1)
#include <bdb/include/bdb.h>
#endif
/*****************************************************************************
                         Types section
******************************************************************************/
typedef void (*taskHandlers_t)(void);
/****************************************************************************
                         Static functions prototypes section
******************************************************************************/
static void rInit(void);
static void assertHandler(SYS_AssertParam_t *assertParam);
static void APP_EvtUpload(void);
#if (BDB_SUPPORT == 1)
static void bdbInitCompleted(void);
#endif
/******************************************************************************
                         Prototypes section
 ******************************************************************************/
void *rGetMem(void);

/******************************************************************************
                         Static variables section
 ******************************************************************************/
//static uint8_t taskPosted = 0; //Array of bits indicates which task processor requested

/*****************************************************************************
                         Global variables section
******************************************************************************/
RState_t rState = R_INIT_STATE;

extern OSAL_QUEUE_HANDLE_TYPE zigbeeRequestQueueHandle;
extern OSAL_QUEUE_HANDLE_TYPE g_appQueue;
/******************************************************************************
                         Implementations section
 ******************************************************************************/

/**************************************************************************//**
\brief Handler to notify assertion (from down layers)
\param[in] SYS_AssertParam_t * type, holding information about the assertion
******************************************************************************/
static void assertHandler(SYS_AssertParam_t *assertParam)
{
#if (APP_ENABLE_SYSASSERT == 1)
  ZS_CommandBuffer_t *commandBuffer = bufferAllocator.allocate();
  uint8_t *ptr;
  
  if (NULL != assertParam)
  {
    switch (assertParam->level)
    {
      case FATAL_LEVEL:
      {
        /* fatal is considered irrecoverable.
           go for reset, after backing up needed stuff */
        while (1)
        {
          (void)assertParam->dbgCode;
        }
      }
      break;

      /* Add code here to take appropriate action for a level */
      case ERROR_LEVEL:
      {
        /* add error handling */
      }
      break;

      case WARN_LEVEL:
      default:
      break;
    }
    commandBuffer->commandFrame.commandId = R_SYS_ASSERT_INDICATION;

    ptr = &commandBuffer->commandFrame.payload[0];

    SYS_BYTE_MEMCPY(ptr, &assertParam->level, sizeof (uint16_t));
    ptr += sizeof (uint16_t);  

    SYS_BYTE_MEMCPY(ptr, &assertParam->dbgCode, sizeof (uint16_t));
    ptr += sizeof (uint16_t);  
  
    commandBuffer->commandFrame.length = R_COMMAND_ID_SIZE + (2*sizeof(uint16_t));
    incomingFrameHandler(commandBuffer);
  }
#else
  (void)assertParam;
#endif
}

/*****************************************************************************
  Peforms APS sublayer processing
  Parameters: None
  Returns: None
 *****************************************************************************/
void APL_TaskHandler(void)
{
  if (R_INIT_STATE == rState)
  {
    rInit();
  }
  else
  {
    rParserTaskHandler();
  }
}

static void rInit(void)
{
  //BSP_OpenLeds();
//  BSP_OffLed(LED_RED);
//  BSP_OffLed(LED_YELLOW);
//  BSP_OnLed(LED_GREEN);
   bdbIB.bdbNodeIsOnANetwork = false;
#ifdef _ENABLE_PERSISTENT_SERVER_
  if (PDS_IsAbleToRestore(BDB_PARAM1_MEM_ID))
  {
      PDS_Restore(BDB_PARAM1_MEM_ID);
      bdbIB.bdbNodeIsOnANetwork = true;
  }
  if(PDS_IsAbleToRestore(BC_ALL_MEMORY_MEM_ID))
  {
      PDS_Restore(BC_ALL_MEMORY_MEM_ID);
  }
  else if (PDS_IsAbleToRestore(NWK_SECURITY_COUNTERS_ITEM_ID))
    PDS_Restore(NWK_SECURITY_COUNTERS_ITEM_ID);
#endif // _ENABLE_PERSISTENT_SERVER_
  /* Device is NFN - */
  if((bdbIB.bdbNodeIsOnANetwork) || PDS_IsAbleToRestore(BC_ALL_MEMORY_MEM_ID))
  {
      BDB_DeviceInit();
  }
  
  rState = R_IDLE_STATE;

  openBufferAllocator();

#if (APP_INTERFACE == APP_INTERFACE_USART) || (APP_INTERFACE == APP_INTERFACE_VCP) || (APP_INTERFACE == APP_INTERFACE_UART) || (APP_INTERFACE == APP_INTERFACE_USBFIFO)
  openSerialManager(INTERFACE_ID_USART0, incomingFrameHandler);
#elif (APP_INTERFACE == APP_INTERFACE_SPI)
  openSerialManager(INTERFACE_ID_SPI, incomingFrameHandler);
#else
  #error "Unknown serial interface"
#endif

  rInitEvents();
#ifdef _INTERPAN_
 rInitInterpan();
#endif

#ifdef _ZCL_SUPPORT_
  zclReset();
#endif /* ZCL_SUPPORT == 1 */
  SYS_AssertSubscribe(assertHandler);
}
#if (BDB_SUPPORT == 1)
/**************************************************************************
\brief Callback on BDB init completetion
***************************************************************************/
static void bdbInitCompleted(void)
{
  // nothing to do
}
#endif // BDB_SUPPORT

/***************************************************************************//**
\brief Static callback for adapter assert
\param condition[in] - condition for assert
\param code[in] - assert code
\return none
******************************************************************************/
void adapterAssert(bool condition, uint16_t code)
{
  (void)condition;
  (void)code;
  halAssert(condition, code);
}

/**************************************************************************
\brief Create Application queue for zigbee and usart events
***************************************************************************/
void create_app_queue(void)
{
#ifdef H3_INDEPENDENT 
  g_appQueue = xQueueCreate( 64, sizeof(APP_Msg_T) );
#endif
}

/**************************************************************************
\brief Post Zigbee API CALLs into queue
***************************************************************************/
static void APP_EvtUpload(void)
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
\brief Zigbee API CALL
***************************************************************************/
inline void ZIGBEE_API_CALL(Stack_API_Request_t *request)
{
  if ( OSAL_RESULT_TRUE != OSAL_QUEUE_Send(&zigbeeRequestQueueHandle, &request,10))
  {
    while(1);   // ERROR , Should not hang here, handle with assert
  }
}

/**************************************************************************//**
\brief ZDO_ResetNetwork Confirmation function

\param[out] conf - Confirmation structure with status
******************************************************************************/
void __attribute__((optimize(0))) ZDO_ResetNetworkConf_CB(ZDO_ResetNetworkConf_t *conf)
{
  sysAssert(ZDO_SUCCESS_STATUS == conf->status, ZDOINIT_ZDOINITRESETNETWORKCONF_0);
  APP_EvtUpload();
}

void process_ZB_evt(void)
{
  APL_TaskHandler();   
}

/* eof rMain.c */
