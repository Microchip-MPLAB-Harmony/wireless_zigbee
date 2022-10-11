#####################################################################################################
#################               OTAU CONFIGURATION                                   ###############
#####################################################################################################

# OTAU Enable
global otauConfigEnable
otauConfigEnable = drvZigbeeComponent.createBooleanSymbol("OTAU_ENABLE", OtauConfigMenu)
otauConfigEnable.setLabel("OTAU Enable")
otauConfigEnable.setDefaultValue(False)
otauConfigEnable.setDescription("OTAU Enable - check the box to enable")

# OTAU Role
global otauConfigRole
otauConfigRole = drvZigbeeComponent.createComboSymbol("OTAU_ROLE",  OtauConfigMenu, ["CLIENT", "SERVER"])
otauConfigRole.setLabel("OTAU Role")
otauConfigRole.setDefaultValue(OTAURoleCheck())
otauConfigRole.setVisible(False)
otauConfigRole.setDescription("OTAU Role - check the box to enable")
otauConfigRole.setDependencies(OtauEnableCheck, ["OTAU_ENABLE"])

global otauDiscoveredServerAmount
otauDiscoveredServerAmount = drvZigbeeComponent.createIntegerSymbol("OTAU_SERVER_AMOUNT", OtauConfigMenu)
otauDiscoveredServerAmount.setLabel("Max Discovered Server Amount")
otauDiscoveredServerAmount.setDefaultValue(1)
otauDiscoveredServerAmount.setVisible(False)
otauDiscoveredServerAmount.setMin(1)
otauDiscoveredServerAmount.setMax(5)
otauDiscoveredServerAmount.setDescription("Max Discovered Server Amount")
otauDiscoveredServerAmount.setDependencies(OtauClientEnableCheck, ["OTAU_ROLE","OTAU_ENABLE"])

global otauServerDiscoveryPeriod
otauServerDiscoveryPeriod = drvZigbeeComponent.createIntegerSymbol("OTAU_DISCOVERY_PERIOD", OtauConfigMenu)
otauServerDiscoveryPeriod.setLabel("Min Discovery Period (ms)")
otauServerDiscoveryPeriod.setDefaultValue(60000)
otauServerDiscoveryPeriod.setVisible(False)
otauServerDiscoveryPeriod.setMin(1000)
otauServerDiscoveryPeriod.setDescription("Min Discovery Period (ms)")
otauServerDiscoveryPeriod.setDependencies(OtauClientEnableCheck, ["OTAU_ROLE","OTAU_ENABLE"])

global otauQueryInterval
otauQueryInterval = drvZigbeeComponent.createIntegerSymbol("OTAU_QUERY_INTERVAL", OtauConfigMenu)
otauQueryInterval.setLabel("Image Request Query Interval(ms)")
otauQueryInterval.setDefaultValue(10000)
otauQueryInterval.setVisible(False)
otauQueryInterval.setMin(1000)
otauQueryInterval.setDescription("Image Request Query Interval(ms)")
otauQueryInterval.setDependencies(OtauClientEnableCheck, ["OTAU_ROLE","OTAU_ENABLE"])

global otauMinBlockPeriod
otauMinBlockPeriod = drvZigbeeComponent.createIntegerSymbol("OTAU_MIN_BLOCK_PERIOD", OtauConfigMenu)
otauMinBlockPeriod.setLabel("Minimum block period (ms)")
otauMinBlockPeriod.setDefaultValue(1000)
otauMinBlockPeriod.setVisible(False)
otauMinBlockPeriod.setMin(10)
otauMinBlockPeriod.setMax(65534)
otauMinBlockPeriod.setDescription("Minimum block period")
otauMinBlockPeriod.setDependencies(OtauClientEnableCheck, ["OTAU_ROLE","OTAU_ENABLE"])

global otauConfigPageMode
otauConfigPageMode = drvZigbeeComponent.createBooleanSymbol("Page_mode", OtauConfigMenu)
otauConfigPageMode.setLabel("Page mode")
otauConfigPageMode.setDefaultValue(False)
otauConfigPageMode.setVisible(False)
otauConfigPageMode.setDescription("Enable for Page mode image transfer")
otauConfigPageMode.setDependencies(OtauClientEnableCheck, ["OTAU_ROLE","OTAU_ENABLE"])