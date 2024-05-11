	// Create ZIGBEE Stack Message QUEUE
    OSAL_QUEUE_Create(&zigbeeRequestQueueHandle, QUEUE_LENGTH_ZIGBEE, QUEUE_ITEM_SIZE_ZIGBEE);

    // Retrieve Zigbee's data from Information Base
    ZB_CS_SYS_IBData_t zgbIBdata = {0};

    zgbIBdata.validityCheck.extMacDevAddrValid = IB_GetMACAddr(&zgbIBdata.extMacDevAddr[0]);
<#if USE_CUSTOM_ANT_GAIN>
    zgbIBdata.validityCheck.antennaGainValid = true;
    zgbIBdata.antGain = CUSTOM_ANT_GAIN;
<#else>
    zgbIBdata.validityCheck.antennaGainValid = IB_GetAntennaGain((uint8_t *)&zgbIBdata.antGain); // should be changed to 8bit
</#if>

    // Initialize ZIGBEE Stack
    Zigbee_Init(&osalAPIList, &zigbeeRequestQueueHandle, NULL, &zgbIBdata);

<#if DEVICE_DEEP_SLEEP_ENABLED>
    // pass the above read wakep src for the stack to use
	CS_WriteParameter(CS_DEVICE_DEEP_SLEEP_WAKEUP_SRC_ID, &deepSleepWakeupSrc);
</#if>
    //uint8_t value = PMU_Set_Mode(PMU_MODE_BUCK_PWM); //Set PMU as PWM mode
    //PMU_Set_Mode(PMU_MODE_BUCK_PWM); //Set PMU as PWM mode // For Buck Mode : PMU_MODE_MLDO
