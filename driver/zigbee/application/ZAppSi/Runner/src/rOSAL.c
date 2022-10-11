#include <z3device/stack_Interface/zgb_api.h>
#include <stack_Interface/configServer/include/cs_api.h>
#include <z3device/api/include/nwk_api.h>
#include <configserver/include/configserver.h>
#include <aps/include/apsCommon.h>
#include <zcl/include/zclAttributes.h>
#include <zcl/include/clusters.h>
#include <pds/include/wlPdsMemIds.h>
#include <zigbee/ZAppSi/z3commonfiles/include/console.h>
#include <zigbee/ZAppSi/z3commonfiles/include/errH.h>
#include <rTypes.h>
#include <rParser.h>
//#include "app_task.h"
#include "app.h"

#include <bdb/include/bdbZllBindings.h>

extern OSAL_QUEUE_HANDLE_TYPE zigbeeRequestQueueHandle;
extern OSAL_QUEUE_HANDLE_TYPE g_appQueue;
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
\brief Zigbee API CALL
***************************************************************************/
inline void ZIGBEE_API_CALL(Stack_API_Request_t *request)
{
  if ( OSAL_RESULT_TRUE != OSAL_QUEUE_Send(&zigbeeRequestQueueHandle, &request,10))
  {
    while(1);   // ERROR , Should not hang here, handle with assert
  }
}
