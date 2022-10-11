/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef __APP_TASK_H__
#define __APP_TASK_H__

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
    
  
extern OSAL_QUEUE_HANDLE_TYPE g_appQueue;
extern void ZDO_ResetNetworkConf_Callback (void *resp);
extern void ZDO_MgmtNwkUpdateNotf_CallBack(void *resp);
extern void ZDO_WakeUpInd_CallBack(void *resp);
extern void ZDO_BindIndication_CallBack(void *resp);
extern void ZDO_UnbindIndication_CallBack(void *resp);
extern void APP_ZigbeeStackInit();

#endif /* _APP_BLE_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
