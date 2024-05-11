#define TASK_ZGB_STACK_SIZE (8 *1024 / sizeof(portSTACK_TYPE))
#define TASK_ZGB_PRIORITY (tskIDLE_PRIORITY + 2)

/* Handle for the zigbee_task. */
TaskHandle_t zigbeeTaskHandle;
