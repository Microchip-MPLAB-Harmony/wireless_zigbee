    if (xTaskCreate(zigbee_task, "ZGB", TASK_ZGB_STACK_SIZE, NULL, TASK_ZGB_PRIORITY, &zigbeeTaskHandle) != pdPASS)
        while (true);
