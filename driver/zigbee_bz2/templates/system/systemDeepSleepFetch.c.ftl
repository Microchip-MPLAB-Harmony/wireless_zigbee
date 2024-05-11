<#if DEVICE_DEEP_SLEEP_ENABLED && (!APP_ENABLE_CONSOLE)>
	uint8_t deepSleepWakeupSrc;
	
	DEVICE_DeepSleepWakeSrc_T wakeSrc;
	DEVICE_GetDeepSleepWakeUpSrc(&wakeSrc);

	deepSleepWakeupSrc = (uint8_t) wakeSrc;
	if ((wakeSrc == DEVICE_DEEP_SLEEP_WAKE_NONE) || (wakeSrc == DEVICE_DEEP_SLEEP_WAKE_MCLR))  
	{
		deepSleepWakeupSrc = (uint8_t) DEVICE_DEEP_SLEEP_WAKE_NONE;
		RTC_Initialize();
	}
</#if>