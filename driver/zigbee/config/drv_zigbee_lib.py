##################################################################################################
######################### ZigbeeDriver Configurations ############################################
##################################################################################################


################################################################################
################################# Component ####################################
################################################################################
global deviceName
deviceName = Variables.get("__PROCESSOR")

def powerRegionCheckFCC(symbol, event):
    if (customAntennaRegion.getValue() == "FCC"):
        symbol.setVisible(True)
    elif (customAntennaRegion.getValue() == "ETSI_FCC"):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def powerRegionCheck(symbol, event):
    if (customAntennaRegion.getValue() == "ETSI"):
        symbol.setVisible(True)
        appPowerRegion.setMin(-14)
        appPowerRegion.setMax(8)
    elif (customAntennaRegion.getValue() == "FCC"):
        symbol.setVisible(True)
        appPowerRegion.setMin(-14)
        appPowerRegion.setMax(12)
    elif (customAntennaRegion.getValue() == "ETSI_FCC"):
        symbol.setVisible(True)
        appPowerRegion.setMin(-14)
        appPowerRegion.setMax(8)
    else:
        symbol.setVisible(False)

def finalizeComponent(zigbeeComponent):
    print(zigbeeDeviceType.getValue())
    result = Database.connectDependencies([[zigbeeDeviceType.getValue(), 'TCC2_PWM_Zigbee', 'tcc2', 'TCC2_PWM']])
    result = Database.connectDependencies([[zigbeeDeviceType.getValue(), 'Zigbee_WolfCrypt_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])
    result = Database.connectDependencies([['lib_crypto', 'LIB_CRYPTO_WOLFCRYPT_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])

def handleMessage(messageID, args):
    # Log.writeInfoMessage('drv_zigbee_lib:handleMessage ID={} argLen={}'.format(messageID, len(args)))
    ''' This message handler is designed to process messages
        sent from the driver/pic32cx-bz/config/device_support.py
        script.
    '''
    if(messageID == 'ANTENNA_GAIN_CHANGE'):
        component = Database.getComponentByID(args['target'])
        if (component):
            customGainEnabled = component.getSymbolByID('USE_CUSTOM_ANT_GAIN')
            customGainValue = component.getSymbolByID('CUSTOM_ANT_GAIN')
            customRegion = component.getSymbolByID('CUSTOM_ANT_REGION')
            Log.writeInfoMessage('{:<17}: Handling - target={}'.format('drv_zigbee_lib.py', args['target']))
            for arg in args:
                Log.writeInfoMessage('{:<17}: {}: {}'.format('', arg, args[arg]))
                if('CUSTOM_ANT_ENABLE' == arg):
                    customGainEnabled.setValue(args[arg])
                if('CUSTOM_ANT_GAIN' == arg):
                    customGainValue.setValue(args[arg])
                if('CUSTOM_ANT_REGION' == arg):
                    customRegion.setValue(args[arg])

def instantiateComponent(drvZigbeeComponent):
    print('ZIGBEE Driver Component')
    configName = Variables.get("__CONFIGURATION_NAME")
    print configName

    # Interface Information
    execfile(Module.getPath() +"/driver/zigbee/config/interface.py")

    ############################################################################
    ### Auto Activate and Dependent components
    ############################################################################
    #res = Database.activateComponents(["tcc2", "rfSystem", "pdsSystem", "lib_crypto", "lib_wolfcrypt","sys_time", "rtc", "uart", "stdio", "sercom0","SERCOM0_UART"])
    #res = Database.activateComponents(["sys_time", "rtc", "uart", "stdio", "sercom0","SERCOM0_UART"])

    # res = Database.activateComponents(["trng"])
    activeComponents = Database.getActiveComponentIDs()
    requiredComponents = ['trng', 'lib_wolfcrypt',"tcc2","pic32cx_bz2_devsupport", "lib_crypto"]
    for r in requiredComponents:
        if r not in activeComponents:
            print("require component '{}' - activating it".format(r))
            res = Database.activateComponents([r])

    #result = Database.connectDependencies([['stdio', 'UART', 'sercom0', 'SERCOM0_UART']])
    #result = Database.connectDependencies([['stdio', 'UART', 'sercom0', 'SERCOM0_UART']])
    #result3 = Database.connectDependencies([['sys_time', 'sys_time_TMR_dependency', 'rtc', 'RTC_TMR']])
    #result2 = Database.connectDependencies([['lib_crypto', 'LIB_CRYPTO_WOLFCRYPT_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])

    remoteComponent = Database.getComponentByID("trng")
    if (remoteComponent):
        print('Printing TRNG remoteComponent Value')    
        print(remoteComponent)
        symbol = remoteComponent.getSymbolByID("trngEnableInterrupt")
        symbol1 = remoteComponent.getSymbolByID("trngEnableEvent")
        symbol2 = remoteComponent.getSymbolByID("TRNG_STANDBY")
        print('Printing TRNG Symbol Value')
        print(symbol)
        symbol.setReadOnly(True)
        symbol1.setReadOnly(True)
        symbol2.setReadOnly(True)
    #Database.setSymbolValue("trng", "trngEnableInterrupt", True)
    #Database.setSymbolValue("trng", "trngEnableEvent", True)
    #Database.setSymbolValue("trng", "TRNG_STANDBY", True)
    Database.setSymbolValue("core", "AES_CLOCK_ENABLE", True)
    Database.setSymbolValue("core", "ZIGBEE_CLOCK_ENABLE", True)
    Database.setSymbolValue("core", "CONFIG_SCOM0_HSEN", "DIRECT")

    # Device Type Selection Menu
    global zigbeeDeviceType
    zigbeeDeviceType = drvZigbeeComponent.createComboSymbol("ZB_DEVICE_TYPE", None, 
       ["",
        "ZIGBEE_COLOR_SCENE_CONTROLLER",
        "ZIGBEE_MULTI_SENSOR",
        "ZIGBEE_COMBINED_INTERFACE",
        #"ZIGBEE_CONTROL_BRIDGE",
        "ZIGBEE_THERMOSTAT",
        "ZIGBEE_IAS_ACE",
        "ZIGBEE_ON_OFF_LIGHT",
        "ZIGBEE_DIMMABLE_LIGHT", 
        "ZIGBEE_COLOR_LIGHT",
        "ZIGBEE_EXTENDED_COLOR_LIGHT", 
        "ZIGBEE_TEMPERATURE_COLOR_LIGHT",
        "ZIGBEE_CUSTOM"
       ])
    zigbeeDeviceType.setDefaultValue("")
    zigbeeDeviceType.setLabel("Select Device Type")
    zigbeeDeviceType.setVisible(False)
    zigbeeDeviceType.setValue(drvZigbeeComponent.getID())
    zigbeeDeviceType.setDefaultValue(drvZigbeeComponent.getID())

    global deviceID
    deviceID = drvZigbeeComponent.createStringSymbol("APP_DEVICE_ID", None)
    deviceID.setLabel("Zigbee Device ID")
    deviceID.setDescription("Zigbee Device ID")
    if (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER"):
        deviceID.setDefaultValue("0x0810")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR"):
        deviceID.setDefaultValue("0x0106")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE"):
        deviceID.setDefaultValue("0x0007")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE"):
        deviceID.setDefaultValue("0x0840")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT"):
        deviceID.setDefaultValue("0x0301")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE"):
        deviceID.setDefaultValue("0x0401")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT"):
        deviceID.setDefaultValue("0x0100")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT"):
        deviceID.setDefaultValue("0x0101")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT"):
        deviceID.setDefaultValue("0x0102")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT"):
        deviceID.setDefaultValue("0x010D")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT"):
        deviceID.setDefaultValue("0x010C")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM"):
        deviceID.setDefaultValue("0x0F00")
    deviceID.setVisible(True)
    deviceID.setReadOnly(True)

    global endPoint
    endPoint = drvZigbeeComponent.createStringSymbol("APP_ENDPOINT", None)
    endPoint.setLabel("Zigbee Application Endpoint")
    endPoint.setDescription("Zigbee Application Endpoint")
    if (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER"):
        endPoint.setDefaultValue("0x26")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR"):
        endPoint.setDefaultValue("0x15")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE"):
        endPoint.setDefaultValue("0x14")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE"):
        endPoint.setDefaultValue("0x0840")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT"):
        endPoint.setDefaultValue("0x19")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE"):
        endPoint.setDefaultValue("0x1A")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT"):
        endPoint.setDefaultValue("0x20")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT"):
        endPoint.setDefaultValue("0x21")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT"):
        endPoint.setDefaultValue("0x22")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT"):
        endPoint.setDefaultValue("0x23")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT"):
        endPoint.setDefaultValue("0x24")
    elif (zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM"):
        endPoint.setDefaultValue("0x30")
    endPoint.setVisible(True)
    endPoint.setReadOnly(True)

    global bridgeSelectionSym
    bridgeSelectionSym = drvZigbeeComponent.createBooleanSymbol("CI_AS_BRIDGE", None)
    bridgeSelectionSym.setLabel("Act as Bridge")
    bridgeSelectionSym.setVisible((zigbeeDeviceType.getValue() == 'ZIGBEE_COMBINED_INTERFACE'))
    bridgeSelectionSym.setDefaultValue(False)
    bridgeSelectionSym.setDescription("Act like Bridge or not")

    # Auto Configuration Option
    global zigbeeDevsym_autoConfig
    zigbeeDevsym_autoConfig = drvZigbeeComponent.createBooleanSymbol("AUTOMATIC_CONFIGURATION", None)
    zigbeeDevsym_autoConfig.setLabel("Automatic(Default) Configuration")
    zigbeeDevsym_autoConfig.setVisible((drvZigbeeComponent.getID() != "ZIGBEE_CUSTOM"))
    zigbeeDevsym_autoConfig.setDefaultValue((drvZigbeeComponent.getID() != "ZIGBEE_CUSTOM"))
    zigbeeDevsym_autoConfig.setDescription("Automatic Configuration which provides the default recommended configuration")
    zigbeeDevsym_autoConfig.setDependencies(zigbeeDevTypeEventAutoConfigCheck, ["MANUAL_CONFIGURATION"])

    # Manual Configuration option
    global zigbeeDevsym_manulConfig
    zigbeeDevsym_manulConfig = drvZigbeeComponent.createBooleanSymbol("MANUAL_CONFIGURATION", None)
    zigbeeDevsym_manulConfig.setLabel("Manual Configuration")
    zigbeeDevsym_manulConfig.setVisible(True)
    zigbeeDevsym_manulConfig.setDefaultValue((drvZigbeeComponent.getID() == "ZIGBEE_CUSTOM"))
    zigbeeDevsym_manulConfig.setReadOnly((drvZigbeeComponent.getID() == "ZIGBEE_CUSTOM"))
    zigbeeDevsym_manulConfig.setDescription("Manual Configuration which provides the options for customization")
    zigbeeDevsym_manulConfig.setDependencies(zigbeeDevTypeEventManualConfigCheck, ["AUTOMATIC_CONFIGURATION"])


    # Stack Configuration Menu
    stackConfigMenu = drvZigbeeComponent.createMenuSymbol("STACKCONFIG_MENU", zigbeeDevsym_manulConfig)
    stackConfigMenu.setLabel("Stack Configuration")
    stackConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    stackConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Commissioning Configuration Menu
    commissioningConfigMenu = drvZigbeeComponent.createMenuSymbol("COMMCONFIG_MENU", zigbeeDevsym_manulConfig)
    commissioningConfigMenu.setLabel("Commissioning Configuration")
    commissioningConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    commissioningConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Application Configuration Menu
    applicationConfigMenu = drvZigbeeComponent.createMenuSymbol("APPCONFIG_MENU", zigbeeDevsym_manulConfig)
    applicationConfigMenu.setLabel("Application Configuration")
    applicationConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    applicationConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

#    # Persistent Data Configuration Menu
#    PersistentDataConfigMenu = drvZigbeeComponent.createMenuSymbol("PERSISCONFIG_MENU", zigbeeDevsym_manulConfig)
#    PersistentDataConfigMenu.setLabel("Persistent Data Configuration")
#    PersistentDataConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
#    PersistentDataConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # OTAU Configuration Menu
    OtauConfigMenu = drvZigbeeComponent.createMenuSymbol("OTAUCONFIG_MENU", zigbeeDevsym_manulConfig)
    OtauConfigMenu.setLabel("OTAU - Over the Air Upgrade Configuration")
    OtauConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    OtauConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Green Power Configuration Menu
    GreenPowerConfigMenu = drvZigbeeComponent.createMenuSymbol("GREENPOWERCONFIG_MENU", zigbeeDevsym_manulConfig)
    GreenPowerConfigMenu.setLabel("Green Power Configuration")
    GreenPowerConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    GreenPowerConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])
    GreenPowerConfigMenu.setDependencies(stackDevTypeForGreenPowerMenuEvent, ["STACK_DEVICE_TYPE"])

    # Cluster Configuration Menu
    clusterConfigMenu = drvZigbeeComponent.createMenuSymbol("CLUSTERCONFIG_MENU", zigbeeDevsym_manulConfig)
    clusterConfigMenu.setLabel("Cluster Configuration")
    clusterConfigMenu.setVisible(zigbeeDevsym_manulConfig.getValue() == True)
    clusterConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

#####################################################################################################
#################               GREEN POWER CONFIGURATION                             ###############
#####################################################################################################
    # Green Power Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/greenpowerconfig.py")

#####################################################################################################
#################               PERSISTENCE DATA CONFIGURATION                             ##########
#####################################################################################################
    # Persistent Data Configuration
    #execfile(Module.getPath() +"/driver/zigbee/config/pdsconfig.py")

#####################################################################################################
#################               OTAU CONFIGURATION                                   ################
#####################################################################################################
    # OTAU Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/otauconfig.py")

#####################################################################################################
#################               STACK CONFIGURATION                                   ###############
#####################################################################################################
    # Stack Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/stackconfig.py")

#####################################################################################################
#################               Application CONFIGURATION                             ###############
#####################################################################################################
    ################################### Custom Antenna Gain Support #####################################

    # Custom Antenna Gain Enabled
    customAntennaSpecified = drvZigbeeComponent.createBooleanSymbol('USE_CUSTOM_ANT_GAIN', None)
    customAntennaSpecified.setVisible(False)
    customAntennaSpecified.setReadOnly(True)
    customAntennaSpecified.setValue(False)

    # Custom Antenna Gain
    global customAntennaGain
    customAntennaGain = drvZigbeeComponent.createIntegerSymbol('CUSTOM_ANT_GAIN', None)
    customAntennaGain.setVisible(False)
    customAntennaGain.setReadOnly(True)
    customAntennaGain.setValue(3)

    # Custom Antenna Gain Region
    global  customAntennaRegion
    customAntennaRegion = drvZigbeeComponent.createStringSymbol('CUSTOM_ANT_REGION', None)
    customAntennaRegion.setVisible(False)
    customAntennaRegion.setReadOnly(True)
    customAntennaRegion.setValue('ETSI')

    
    # Power Channel 
    global  appPowerRegion
    appPowerRegion = drvZigbeeComponent.createIntegerSymbol("APP_TX_POWER", applicationConfigMenu)
    appPowerRegion.setLabel("Tx Power Set")
    if (deviceName == "PIC32CX1012BZ25048") or (deviceName == "PIC32CX1012BZ25032"):
        appPowerRegion.setDefaultValue(7)
    elif (deviceName == "PIC32CX1012BZ21032"):
        appPowerRegion.setDefaultValue(5)
        appPowerRegion.setMin(-16)
        appPowerRegion.setMax(6) 
    appPowerRegion.setDependencies(powerRegionCheck, ["CUSTOM_ANT_REGION"])

    global appConfigChannel26power
    appConfigChannel26power = drvZigbeeComponent.createIntegerSymbol("APP_CHANNEL_26_POWER", applicationConfigMenu)
    appConfigChannel26power.setLabel("Channel-26 Power Set")
    appConfigChannel26power.setDefaultValue(0)
    appConfigChannel26power.setMin(-8)
    appConfigChannel26power.setMax(8)
    appConfigChannel26power.setDescription("Antenna Gain Set")
    appConfigChannel26power.setDependencies(powerRegionCheckFCC, ["CUSTOM_ANT_REGION"])

    # Application Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/appconfig.py")

#####################################################################################################
#################               Commissioning CONFIGURATION                           ###############
#####################################################################################################
    # Application Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/commissionconfig.py")


    checkDevTypeLight              =  (zigbeeDeviceType.getValue() == 'ZIGBEE_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'ZIGBEE_ON_OFF_LIGHT') or (zigbeeDeviceType.getValue() == 'ZIGBEE_TEMPERATURE_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'ZIGBEE_EXTENDED_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'ZIGBEE_DIMMABLE_LIGHT')
    checkDevTypeRemote             =  (zigbeeDeviceType.getValue() == 'ZIGBEE_COLOR_SCENE_CONTROLLER')
    checkDevTypeDimSwitch          =  (zigbeeDeviceType.getValue() == 'DIMMER_SWITCH')
    checkDevTypeCombInterface      =  (zigbeeDeviceType.getValue() == 'ZIGBEE_COMBINED_INTERFACE')
    checkDevTypeControlBridge      =  (zigbeeDeviceType.getValue() == 'ZIGBEE_CONTROL_BRIDGE')
    checkDevTypeIasAce             =  (zigbeeDeviceType.getValue() == 'ZIGBEE_IAS_ACE')
    checkDevTypeMultiSensor        =  (zigbeeDeviceType.getValue() == 'ZIGBEE_MULTI_SENSOR')
    checkDevTypeThermostat         =  (zigbeeDeviceType.getValue() == 'ZIGBEE_THERMOSTAT')
    checkDevTypeCustom             =  (zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM')
    checkCommTypeNetworkFormation  =  (commnConfigNWKFormation.getValue()       == True)
    checkCommTypeNetworkSteering   =  (commnConfigNWKSteering.getValue()        == True)
    checkCommTypeTouchlink         =  (commnConfigTouchlink.getValue()          == True)
    checkCommTypeFindingBinding    =  (commnConfigFindingAndbinding.getValue() == True)
    checkGPDevTypeNotNone          =  (greenPowerConfigZGPDeviceType.getValue() != 0)
    checkOtauEnable                =  (otauConfigEnable.getValue() == True)
    checkOtauPageMode              =  (otauConfigPageMode.getValue() == True)
    checkOtauServer                =  (otauConfigRole.getValue() == 'SERVER')
    checkOtauClient                =  (otauConfigRole.getValue() == 'CLIENT')
    #checkPDSEnableWearLevelling    =  ((pdsConfigEnablePDS.getValue() == True) and (pdsConfigEnableWearLevelling.getValue() == True))
    #checkPDSEnableStandard         =  ((pdsConfigEnablePDS.getValue() == True) and (pdsConfigEnableWearLevelling.getValue() == False))
    #checkPDSUseExternalMem         =  (pdsConfigMemInternalExternal.getValue() == 'EXTERNAL')
    #checkPDSUseInternalMem         =  (pdsConfigMemInternalExternal.getValue() == 'INTERNAL')

    condAlways                          = [True,                          None,                                        []]

    condDevLight                        = [checkDevTypeLight,             setEnableLightDevice,                        ['ZB_DEVICE_TYPE']]
    condDevColorSceneController         = [checkDevTypeRemote,            setEnableColorSceneController,               ['ZB_DEVICE_TYPE']]
    condDevDimmerSwitch                 = [checkDevTypeDimSwitch,         setEnableDimSwitch,                          ['ZB_DEVICE_TYPE']]
    condDevCombInterface                = [checkDevTypeCombInterface,     setEnableCombInterface,                      ['ZB_DEVICE_TYPE']]
    condDevControlBridge                = [checkDevTypeControlBridge,     setEnableControlBridge,                      ['ZB_DEVICE_TYPE']]
    condDevIasAce                       = [checkDevTypeIasAce,            setEnableIasAce,                             ['ZB_DEVICE_TYPE']]
    condDevMultiSensor                  = [checkDevTypeMultiSensor,       setEnableMultiSensor,                        ['ZB_DEVICE_TYPE']]
    condDevThermostat                   = [checkDevTypeThermostat ,       setEnableThermostat ,                        ['ZB_DEVICE_TYPE']]
    condDevCustom                       = [checkDevTypeCustom,            setEnableCustomDevice,                       ['ZB_DEVICE_TYPE']]

    condDevGPNotNone                    = [checkGPDevTypeNotNone,         setEnableGPDevice,                           ['GP_DEVICE_TYPE']]

    condCommnNetworkFormation           = [checkCommTypeNetworkFormation ,  setEnableCommnNetworkFormation ,          ['NETWORK_FORMATION']]
    condCommnNetworkSteering            = [checkCommTypeNetworkSteering ,   setEnableCommnNetworkSteering ,           ['NETWORK_STEERING']]
    condCommnTouchlink                  = [checkCommTypeTouchlink ,         setEnableCommnTouchlink ,                 ['TOUCHLINK']]
    condCommnFindingBinding             = [checkCommTypeFindingBinding ,    setEnableCommnFindingBinding ,            ['FINDING_AND_BINDING']]

    condOtauEnable                      = [checkOtauEnable,             setEnableOtau,                              ['OTAU_ENABLE']]
    condOtauPageMode                    = [checkOtauPageMode,           setEnablePageMode,                          ['OTAU_ENABLE']]
    condOtauServer                      = [checkOtauServer,             setEnableOtauServer,                        ['OTAU_ENABLE']]
    condOtauClient                      = [checkOtauClient,             setEnableOtauClient,                        ['OTAU_ENABLE']]

    #condPDSStandard                     = [checkPDSEnableStandard ,         setEnablePDSStandard ,                    ['PDS_ENABLE_WEAR_LEVELING']]
    #condPDSWearLevelling                = [checkPDSEnableWearLevelling ,    setEnablePDSWearLevelling  ,              ['PDS_ENABLE_WEAR_LEVELING']]
    #condPDSUseInternalMem               = [checkPDSUseInternalMem ,         setEnablePDSUseInternalMem ,              ['PDS_USEMEM_INTEXT']]
    #condPDSUseExternalMem               = [checkPDSUseExternalMem ,         setEnablePDSUseExternalMem ,              ['PDS_USEMEM_INTEXT']]

#####################################################################################################
#################               Cluster CONFIGURATION                                 ###############
#####################################################################################################
    # Cluster Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/clusterconfig.py")

#####################################################################################################
#####################################################################################################
#####################################################################################################
#####################################################################################################


#####################################################################################################
####################################### Code Generation #############################################
#####################################################################################################
#####################################################################################################
##############################  IMPORT INC AND SRC DEFINITIONS ######################################
#####################################################################################################

    # # Instance FTL files
    zigbeeDevSelectConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_DEVSEL_HEADER", None)
    zigbeeDevSelectConf.setSourcePath("/driver/zigbee/templates/zigbeeAppDeviceSelect.h.ftl")
    zigbeeDevSelectConf.setOutputName("zigbeeAppDeviceSelect.h")
    zigbeeDevSelectConf.setDestPath("/zigbee/z3device_configs")
    zigbeeDevSelectConf.setProjectPath("config/" + configName + "/zigbee/z3device_configs")
    zigbeeDevSelectConf.setType("HEADER")
    zigbeeDevSelectConf.setOverwrite(True)
    zigbeeDevSelectConf.setMarkup(True)

    zigbeeAppConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_APPCONF_HEADER", None)
    zigbeeAppConf.setSourcePath("/driver/zigbee/templates/zigbeeAppConfig.h.ftl")
    zigbeeAppConf.setOutputName("zigbeeAppConfig.h")
    zigbeeAppConf.setDestPath("/zigbee/z3device_configs")
    zigbeeAppConf.setProjectPath("config/" + configName + "/zigbee/z3device_configs")
    zigbeeAppConf.setType("HEADER")
    zigbeeAppConf.setOverwrite(True)
    zigbeeAppConf.setMarkup(True)

    zigbeeStackConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__STACKCONF_HEADER", None)
    zigbeeStackConf.setSourcePath("/driver/zigbee/templates/stackConfig.h.ftl")
    zigbeeStackConf.setOutputName("stackConfig.h")
    zigbeeStackConf.setDestPath("/zigbee/z3device_configs")
    zigbeeStackConf.setProjectPath("config/" + configName + "/zigbee/z3device_configs")
    zigbeeStackConf.setType("HEADER")
    zigbeeStackConf.setOverwrite(True)
    zigbeeStackConf.setMarkup(True)

    zigbeeAppConst = drvZigbeeComponent.createFileSymbol("ZIGBEE_APPCONST_HEADER", None)
    zigbeeAppConst.setSourcePath("/driver/zigbee/templates/appConsts.h.ftl")
    zigbeeAppConst.setOutputName("appConsts.h")
    zigbeeAppConst.setDestPath("/zigbee/z3device/common/include")
    zigbeeAppConst.setProjectPath("config/" + configName + "/zigbee/z3device/common/include")
    zigbeeAppConst.setType("HEADER")
    zigbeeAppConst.setOverwrite(True)
    zigbeeAppConst.setMarkup(True)
    #zigbeeAppConst.setEnabled(checkDevTypeCustom)

    zigbeeOtauConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__OTAUCONF_HEADER", None)
    zigbeeOtauConf.setSourcePath("/driver/zigbee/templates/otauConfig.h.ftl")
    zigbeeOtauConf.setOutputName("otauConfig.h")
    zigbeeOtauConf.setDestPath("/zigbee/z3device_configs")
    zigbeeOtauConf.setProjectPath("config/" + configName + "/zigbee/z3device_configs")
    zigbeeOtauConf.setType("HEADER")
    zigbeeOtauConf.setOverwrite(True)
    zigbeeOtauConf.setMarkup(True)
    zigbeeOtauConf.setEnabled(False)
    zigbeeOtauConf.setDependencies(setEnableOtau, ["OTAU_ENABLE"])

    #System Initialization
    #ptcSystemInitFile = drvZigbeeComponent.createFileSymbol("ZIGBEE_SYS_INIT", None)
    #ptcSystemInitFile.setType("STRING")
    #ptcSystemInitFile.setOutputName("core.LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE")
    #ptcSystemInitFile.setSourcePath("driver/zigbee/templates/system/initialization.c.ftl")
    #ptcSystemInitFile.setMarkup(True)

    # System Definition
    ptcSystemDefFile = drvZigbeeComponent.createFileSymbol("ZIGBEE_SYS_DEF", None)
    ptcSystemDefFile.setType("STRING")
    ptcSystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    ptcSystemDefFile.setSourcePath("driver/zigbee/templates/system/definitions.h.ftl")
    ptcSystemDefFile.setMarkup(True)

    # Configuration what OSAL Creates - Temporary - Need to find in the Systems
    #sys_configHeaderFile = drvZigbeeComponent.createFileSymbol(None, None)
    #sys_configHeaderFile.setSourcePath('driver/zigbee/templates/system/configuration.h.ftl')
    #sys_configHeaderFile.setOutputName('configuration.h')
    #sys_configHeaderFile.setOverwrite(True)
    #sys_configHeaderFile.setDestPath('../../')
    #sys_configHeaderFile.setProjectPath('')
    #sys_configHeaderFile.setType('HEADER')
    #sys_configHeaderFile.setEnabled(True)

    #################################################################
    ###############  System Initialization Settings   ###############
    #################################################################
    zigbeeInitTemplates = [('sysInitData', 'system_initialize_data.c.ftl', 'core.LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA'),
        ('sysInitMiddleware', 'system_initialize_middleware.c.ftl', 'core.LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE'),
        ('sysTaskMiddlewareDef', 'system_tasks_def.c.ftl', 'core.LIST_SYSTEM_RTOS_TASKS_C_DEFINITIONS'),
        ('sysTaskMiddleware', 'system_tasks.c.ftl', 'core.LIST_SYSTEM_TASKS_C_CALL_LIB_TASKS'),
        ('sysDefZB', 'system_definitions.h.ftl', 'core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES'),
        ]

    n = 0
    zigbeeInit = []
    for i, f, p in zigbeeInitTemplates:
        zigbeeInit.append( drvZigbeeComponent.createFileSymbol(i, None))
        zigbeeInit[n].setType('STRING')
        zigbeeInit[n].setOutputName(p)
        zigbeeInit[n].setSourcePath('driver/zigbee/templates/system/' + f)
        zigbeeInit[n].setMarkup(True)
        print('{} file: {} pos: {}'.format(n, f, p))
        n = n + 1

    ###############  app_zigbee.c app_zigbee.h files ######################
    # Add app_zigbee.c - generated file
    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee/templates/zigbee_app_source.c.ftl')
    app_zgbSourceFile.setOutputName('app_zigbee.c')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('../../app_zigbee/')
    app_zgbSourceFile.setProjectPath('app_zigbee')
    app_zgbSourceFile.setType('SOURCE')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee/templates/app_zigbee_handler.c.ftl')
    app_zgbSourceFile.setOutputName('app_zigbee_handler.c')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('../../app_zigbee/')
    app_zgbSourceFile.setProjectPath('app_zigbee')
    app_zgbSourceFile.setType('SOURCE')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee/templates/app_zigbee_handler.h.ftl')
    app_zgbSourceFile.setOutputName('app_zigbee_handler.h')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('../../app_zigbee/')
    app_zgbSourceFile.setProjectPath('app_zigbee')
    app_zgbSourceFile.setType('HEADER')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee/templates/pic32cxBSP.c.ftl')
    app_zgbSourceFile.setOutputName('pic32cxBSP.c')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('/zigbee/z3device/common')
    app_zgbSourceFile.setProjectPath('config/' + configName + '/zigbee/z3device/common/')
    app_zgbSourceFile.setType('SOURCE')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee/templates/pic32cxBSP.h.ftl')
    app_zgbSourceFile.setOutputName('pic32cxBSP.h')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('/zigbee/z3device/common/include/')
    app_zgbSourceFile.setProjectPath('config/' + configName + '/zigbee/z3device/common/include/')
    app_zgbSourceFile.setType('HEADER')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    # Add app_uart.c - generated file
    app_uartSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_uartSourceFile.setSourcePath('driver/zigbee/templates/app_uart.c.ftl')
    app_uartSourceFile.setOutputName('app_uart.c')
    app_uartSourceFile.setOverwrite(True)
    app_uartSourceFile.setDestPath('../../app_zigbee/')
    app_uartSourceFile.setProjectPath('app_zigbee/zigbee_console/')
    app_uartSourceFile.setType('SOURCE')
    app_uartSourceFile.setEnabled(False)
    app_uartSourceFile.setMarkup(True)
    app_uartSourceFile.setDependencies(isConsoleEnabled, ["APP_ENABLE_CONSOLE"])

    # Add app_zigbee.h - static file
    app_zgbHeaderFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbHeaderFile.setSourcePath('driver/zigbee/templates/zigbee_app_header.h.ftl')
    app_zgbHeaderFile.setOutputName('app_zigbee.h')
    app_zgbHeaderFile.setOverwrite(True)
    app_zgbHeaderFile.setDestPath('../../app_zigbee/')
    app_zgbHeaderFile.setProjectPath('app_zigbee')
    app_zgbHeaderFile.setType('HEADER')
    app_zgbHeaderFile.setEnabled(True)

    app_consolecommonSrcFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_consolecommonSrcFile.setSourcePath('driver/zigbee/templates/cluster/console/console.c.ftl')
    app_consolecommonSrcFile.setOutputName('console.c')
    app_consolecommonSrcFile.setOverwrite(True)
    app_consolecommonSrcFile.setDestPath('../../app_zigbee/zigbee_console/')
    app_consolecommonSrcFile.setProjectPath('app_zigbee/zigbee_console/')
    app_consolecommonSrcFile.setType('SOURCE')
    app_consolecommonSrcFile.setEnabled(True)

    #app_consolecommonSrcFile1 = drvZigbeeComponent.createFileSymbol(None, None)
    #app_consolecommonSrcFile1.setSourcePath('driver/zigbee/templates/cluster/console/commandManager.c.ftl')
    #app_consolecommonSrcFile1.setOutputName('commandManager.c')
    #app_consolecommonSrcFile1.setOverwrite(True)
    #app_consolecommonSrcFile1.setDestPath('../../app_zigbee/zigbee_console/')
    #app_consolecommonSrcFile1.setProjectPath('')
    #app_consolecommonSrcFile1.setType('SOURCE')
    #app_consolecommonSrcFile1.setEnabled(True)

    app_consolecommonSrcFile2 = drvZigbeeComponent.createFileSymbol(None, None)
    app_consolecommonSrcFile2.setSourcePath('driver/zigbee/templates/cluster/console/consoleCmds.c.ftl')
    app_consolecommonSrcFile2.setOutputName('consoleCmds.c')
    app_consolecommonSrcFile2.setOverwrite(True)
    app_consolecommonSrcFile2.setDestPath('../../app_zigbee/zigbee_console/')
    app_consolecommonSrcFile2.setProjectPath('app_zigbee/zigbee_console/')
    app_consolecommonSrcFile2.setType('SOURCE')
    app_consolecommonSrcFile2.setEnabled(True)

    #app_consolecommonHFile = drvZigbeeComponent.createFileSymbol(None, None)
    #app_consolecommonHFile.setSourcePath('driver/zigbee/templates/cluster/console/commandManager.h.ftl')
    #app_consolecommonHFile.setOutputName('commandManager.h')
    #app_consolecommonHFile.setOverwrite(True)
    #app_consolecommonHFile.setDestPath('../../app_zigbee/zigbee_console/')
    #app_consolecommonHFile.setProjectPath('')
    #app_consolecommonHFile.setType('HEADER')
    #app_consolecommonHFile.setEnabled(True)

    app_consolecommonHFile1 = drvZigbeeComponent.createFileSymbol(None, None)
    app_consolecommonHFile1.setSourcePath('driver/zigbee/templates/cluster/console/consoleCmds.h.ftl')
    app_consolecommonHFile1.setOutputName('consoleCmds.h')
    app_consolecommonHFile1.setOverwrite(True)
    app_consolecommonHFile1.setDestPath('../../app_zigbee/zigbee_console/')
    app_consolecommonHFile1.setProjectPath('app_zigbee/zigbee_console/')
    app_consolecommonHFile1.setType('HEADER')
    app_consolecommonHFile1.setEnabled(True)

    app_consolecommonHFile2 = drvZigbeeComponent.createFileSymbol(None, None)
    app_consolecommonHFile2.setSourcePath('driver/zigbee/templates/cluster/console/console.h.ftl')
    app_consolecommonHFile2.setOutputName('console.h')
    app_consolecommonHFile2.setOverwrite(True)
    app_consolecommonHFile2.setDestPath('../../app_zigbee/zigbee_console/')
    app_consolecommonHFile2.setProjectPath('app_zigbee/zigbee_console/')
    app_consolecommonHFile2.setType('HEADER')
    app_consolecommonHFile2.setEnabled(True)

#####################################################################################################
################################### ZIGBEE STACK FILES ##############################################
#####################################################################################################

################################### HEADER FILES ####################################################

    zdrvStackAPSIncFiles = [
        ['aps/include/aps.h',                        condAlways],
        ['aps/include/apsAIB.h',                     condAlways],
        ['aps/include/apsCommandReq.h',              condAlways],
        ['aps/include/apsCommon.h',                  condAlways],
        ['aps/include/apsConfigServer.h',            condAlways],
        ['aps/include/apsCryptoKeys.h',              condAlways],
        ['aps/include/apsdeData.h',                  condAlways],
        ['aps/include/apsdeEndpoint.h',              condAlways],
        ['aps/include/apsmeAuthenticate.h',          condAlways],
        ['aps/include/apsmeBind.h',                  condAlways],
        ['aps/include/apsmeConfirmKey.h',            condAlways],
        ['aps/include/apsmeEstablishKey.h',          condAlways],
        ['aps/include/apsmeGroup.h',                 condAlways],
        ['aps/include/apsmeRemoveDevice.h',          condAlways],
        ['aps/include/apsmeRequestKey.h',            condAlways],
        ['aps/include/apsmeSwitchKey.h',             condAlways],
        ['aps/include/apsmeTransportKey.h',          condAlways],
        ['aps/include/apsmeUpdateDevice.h',          condAlways],
        ['aps/include/apsmeVerifyKey.h',             condAlways],
        ['aps/include/intrpData.h',                  condAlways],
        ['aps/include/private/apsFrames.h',          condAlways],
        ['aps/include/private/apsKeyPairSet.h',      condAlways],
        ['aps/include/private/apsMemoryManager.h',   condAlways],
    ]

    zdrvStackBDBIncFiles = [
        ['bdb/include/bdb.h',                        condAlways],
        ['bdb/include/bdbDbg.h',                     condAlways],
        ['bdb/include/bdbFindingAndBinding.h',       condAlways],
        ['bdb/include/bdbInstallCode.h',             condAlways],
        ['bdb/include/bdbInternal.h',                condAlways],
        ['bdb/include/bdbNwkFormation.h',            condAlways],
        ['bdb/include/bdbNwkSteering.h',             condAlways],
        ['bdb/include/bdbSecurity.h',                condAlways],
        ['bdb/include/bdbTouchlink.h',               condAlways],
        ['bdb/include/bdbZllBindings.h',             condAlways],
    ]

    zdrvStackConfigServerIncFiles = [
        ['configserver/include/configserver.h',                   condAlways],
        ['configserver/include/csDefaults.h',                     condAlways],
        ['configserver/include/stackVersion.h',                   condAlways],
        ['configserver/include/private/csBuffers.h',              condAlways],
        ['configserver/include/private/csConstTable.h',           condAlways],
        ['configserver/include/private/csDbg.h',                  condAlways],
        ['configserver/include/private/csMemTable.h',             condAlways],
        ['configserver/include/private/csSIB.h',                  condAlways],
        ['configserver/include/private/csVarTable.h',             condAlways],
    ]

    zdrvStackNWKIncFiles = [
        ['nwk/include/nldeData.h',                     condAlways],
        ['nwk/include/nlmeNetworkFormation.h',         condAlways],
        ['nwk/include/nlmeStartRouter.h',              condAlways],
        ['nwk/include/nwkCommon.h',                    condAlways],
        ['nwk/include/nwkRouteInfo.h',                 condAlways],
        ['nwk/include/nlmeDirectJoin.h',               condAlways],
        ['nwk/include/nlmeNwkStatus.h',                condAlways],
        ['nwk/include/nlmeSync.h',                     condAlways],
        ['nwk/include/nwkConfigServer.h',              condAlways],
        ['nwk/include/nwkRouteTable.h',                condAlways],
        ['nwk/include/nlmeEdScan.h',                   condAlways],
        ['nwk/include/nlmePermitJoining.h',            condAlways],
        ['nwk/include/nlmeSyncLoss.h',                 condAlways],
        ['nwk/include/nwkEndDeviceTimeout.h',          condAlways],
        ['nwk/include/nwkSecurity.h',                  condAlways],
        ['nwk/include/nlmeJoin.h',                     condAlways],
        ['nwk/include/nlmeReset.h',                    condAlways],
        ['nwk/include/nwk.h',                          condAlways],
        ['nwk/include/nwkGroup.h',                     condAlways],
        ['nwk/include/nlmeLeave.h',                    condAlways],
        ['nwk/include/nlmeRouteDiscovery.h',           condAlways],
        ['nwk/include/nwkAddressResolv.h',             condAlways],
        ['nwk/include/nwkNeighbor.h',                  condAlways],
        ['nwk/include/nlmeNetworkDiscovery.h',         condAlways],
        ['nwk/include/nlmeSetGet.h',                   condAlways],
        ['nwk/include/nwkAttributes.h',                condAlways],
        ['nwk/include/nwkProfiler.h',                  condAlways],
        ['nwk/include/private/nwkAddressMap.h',               condAlways],
        ['nwk/include/private/nwkBTT.h',                      condAlways],
        ['nwk/include/private/nwkConfig.h',                   condAlways],
        ['nwk/include/private/nwkDbg.h',                      condAlways],
        ['nwk/include/private/nwkEndDeviceTimeoutInd.h',      condAlways],
        ['nwk/include/private/nwkFrame.h',                    condAlways],
        ['nwk/include/private/nwkIB.h',                       condAlways],
        ['nwk/include/private/nwkJoinInd.h',                  condAlways],
        ['nwk/include/private/nwkPacket.h',                   condAlways],
        ['nwk/include/private/nwkPassiveAck.h',               condAlways],
        ['nwk/include/private/nwkRouteCache.h',               condAlways],
        ['nwk/include/private/nwkRouteDiscovery.h',           condAlways],
        ['nwk/include/private/nwkRouteDiscoveryTable.h',      condAlways],
        ['nwk/include/private/nwkRouteRecord.h',              condAlways],
        ['nwk/include/private/nwkRoutingTable.h',             condAlways],
        ['nwk/include/private/nwkRx.h',                       condAlways],
        ['nwk/include/private/nwkSystem.h',                   condAlways],
        ['nwk/include/private/nwkTx.h',                       condAlways],
        ['nwk/include/private/nwkTxDelay.h',                  condAlways],
        ['nwk/include/private/nwkUpdateCommand.h',            condAlways],
    ]

    zdrvStackMACIncFiles = [
        ['mac_phy/include/mac.h',                  condAlways],
        ['mac_phy/include/macAddr.h',              condAlways],
        ['mac_phy/include/macAffix.h',             condAlways],
        ['mac_phy/include/macAssociate.h',         condAlways],
        ['mac_phy/include/macBanNode.h',           condAlways],
        ['mac_phy/include/macBeacon.h',            condAlways],
        ['mac_phy/include/macBuffers.h',           condAlways],
        ['mac_phy/include/macCommon.h',            condAlways],
        ['mac_phy/include/macCommStatus.h',        condAlways],
        ['mac_phy/include/macData.h',              condAlways],
        # ['mac_phy/include/macDbg.h',               condAlways],
        ['mac_phy/include/macDisassociate.h',      condAlways],
        ['mac_phy/include/macEnvironment.h',       condAlways],
        ['mac_phy/include/macFrame.h',             condAlways],
        ['mac_phy/include/macMem.h',               condAlways],
        ['mac_phy/include/macOrphan.h',            condAlways],
        ['mac_phy/include/macphyPib.h',            condAlways],
        ['mac_phy/include/macPoll.h',              condAlways],
        ['mac_phy/include/macPurge.h',             condAlways],
        ['mac_phy/include/macReset.h',             condAlways],
        ['mac_phy/include/macRxEnable.h',          condAlways],
        ['mac_phy/include/macScan.h',              condAlways],
        ['mac_phy/include/macSetGet.h',            condAlways],
        ['mac_phy/include/macStart.h',             condAlways],
        ['mac_phy/include/macSuperframe.h',        condAlways],
        ['mac_phy/include/macSync.h',              condAlways],
        ['mac_phy/include/phy.h',                  condAlways],
        ['mac_phy/include/rfBattery.h',            condAlways],
        ['mac_phy/include/rfCalibration.h',        condAlways],
        ['mac_phy/include/rfEncrypt.h',            condAlways],
        # ['mac_phy/include/rfInit.h',               condAlways],
        ['mac_phy/include/rfRandom.h',             condAlways],
        ['mac_phy/include/rfRegAccess.h',          condAlways],
        ['mac_phy/mac_env/include/macenvMem.h',    condAlways],
        ['mac_phy/mac_env/include/macenvPib.h',    condAlways],
        ['mac_phy/mac_hwd_phy/include/machwd.h',   condAlways],
        # ['mac_phy/mac_hwd_phy/include/machwdBatMon.h',                             condAlways],
        # ['mac_phy/mac_hwd_phy/include/machwdCalibration.h',                        condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdData.h',                               condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdEd.h',                                 condAlways],
        # ['mac_phy/mac_hwd_phy/include/machwdEncrypt.h',                            condAlways],
        # ['mac_phy/mac_hwd_phy/include/machwdRegAccess.h',                          condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdReset.h',                              condAlways],
        # ['mac_phy/mac_hwd_phy/include/machwdRnd.h',                                condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdService.h',                            condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdSet.h',                                condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdSetTrx.h',                             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdMem.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/at86rf233.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyPic32cx.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyCommon.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDataStatus.h',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyInit.h',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMem.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMemAccess.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRtimerIrqDispatcher.h',     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDeepSleep.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySet.h',                     condAlways],        
        ['mac_phy/mac_hwi/include/machwiAssociateHandler.h',                         condAlways],
        ['mac_phy/mac_hwi/include/machwiDisassociateHandler.h',                      condAlways],
        ['mac_phy/mac_hwi/include/machwiHwdReqMemPool.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiManager.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiMem.h',                                      condAlways],
        ['mac_phy/mac_hwi/include/machwiPollHandler.h',                              condAlways],
        ['mac_phy/mac_hwi/include/machwiScanHandler.h',                              condAlways],
        ['mac_phy/mac_hwi/include/machwiStartHandler.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionHandler.h',                       condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionQueue.h',                         condAlways],
    ]

    zdrvStackSYSENVIncFiles = [
        ['systemenvironment/include/dbg.h',                 condAlways],
        ['systemenvironment/include/sysAssert.h',           condAlways],
        ['systemenvironment/include/sysDbg.h',              condAlways],
        ['systemenvironment/include/sysDuplicateTable.h',   condAlways],
        ['systemenvironment/include/sysEndian.h',           condAlways],
        ['systemenvironment/include/sysEvents.h',           condAlways],
        ['systemenvironment/include/sysEventsHandler.h',    condAlways],
        ['systemenvironment/include/sysIdleHandler.h',      condAlways],
        ['systemenvironment/include/sysIncrementMacro.h',   condAlways],
        ['systemenvironment/include/sysInit.h',             condAlways],
        ['systemenvironment/include/sysMutex.h',            condAlways],
        ['systemenvironment/include/sysQueue.h',            condAlways],
        ['systemenvironment/include/sysRepeatMacro.h',      condAlways],
        ['systemenvironment/include/sysSleep.h',            condAlways],
        ['systemenvironment/include/sysStat.h',             condAlways],
        ['systemenvironment/include/sysTaskManager.h',      condAlways],
        ['systemenvironment/include/sysTimer.h',            condAlways],
        ['systemenvironment/include/sysTypes.h',            condAlways],
        ['systemenvironment/include/sysUtils.h',            condAlways],
    ]

    zdrvStackSECIncFiles = [
        ['security/serviceprovider/include/sspAuthentic.h',                 condAlways],
        ['security/serviceprovider/include/sspChallengeGen.h',              condAlways],
        ['security/serviceprovider/include/sspCommon.h',                    condAlways],
        # ['security/serviceprovider/include/sspDbg.h',                       condAlways],
        ['security/serviceprovider/include/sspHash.h',                      condAlways],
        # ['security/serviceprovider/include/sspReset.h',                     condAlways],
        ['security/serviceprovider/include/sspSfp.h',                       condAlways],
        ['security/serviceprovider/include/sspSkke.h',                      condAlways],
        # ['security/TrustCentre/include/tc.h',                               condAlways],
        ['security/TrustCentre/include/tcAuthentic.h',                      condAlways],
        ['security/TrustCentre/include/tcKeyEstablish.h',                   condAlways],
        ['security/TrustCentre/include/tcPermissions.h',                    condAlways],
        ['security/serviceprovider/include/private/sspHashHandler.h',           condAlways],
    ]

    zdrvStackZDOIncFiles = [
        ['zdo/include/appFramework.h',                 condAlways],
        ['zdo/include/zdo.h',                          condAlways],
        ['zdo/include/zdoAddrResolving.h',             condAlways],
        ['zdo/include/zdoCommon.h',                    condAlways],
        ['zdo/include/zdoConfigServer.h',              condAlways],
        ['zdo/include/zdoNotify.h',                    condAlways],
        ['zdo/include/zdoPermissions.h',               condAlways],
        ['zdo/include/zdoSecurityManager.h',           condAlways],
        ['zdo/include/private/zdoAddrResolvingInt.h',  condAlways],
        # ['zdo/include/private/zdoBinding.h',           condAlways],
        ['zdo/include/private/zdoCommands.h',          condAlways],
        # ['zdo/include/private/zdoConfig.h',            condAlways],
        ['zdo/include/private/zdoDbg.h',               condAlways],
        ['zdo/include/private/zdoEndDeviceBinding.h',  condAlways],
        # ['zdo/include/private/zdoInit.h',              condAlways],
        ['zdo/include/private/zdoLeaveNetwork.h',      condAlways],
        ['zdo/include/private/zdoMem.h',               condAlways],
        ['zdo/include/private/zdoMgmtNwkUpdate.h',     condAlways],
        # ['zdo/include/private/zdoNodeManager.h',       condAlways],
        ['zdo/include/private/zdoNwkManager.h',        condAlways],
        # ['zdo/include/private/zdoParentAnnounce.h',    condAlways],
        ['zdo/include/private/zdoPermissionsTable.h',  condAlways],
        ['zdo/include/private/zdoPowerManager.h',      condAlways],
        # ['zdo/include/private/zdoServiceDiscovery.h',  condAlways],
        ['zdo/include/private/zdoStartNetwork.h',      condAlways],
        # ['zdo/include/private/zdoStateMachine.h',      condAlways],
        ['zdo/include/private/zdoTaskManager.h',       condAlways],
        ['zdo/include/private/zdoZdpReq.h',            condAlways],
        ['zdo/include/private/zdoZib.h',               condAlways],
    ]

    zdrvStackHALIncFiles = [
        ['hal/include/atomic.h',                                 condAlways],
        ['hal/include/bcTimer.h',                                condAlways],
        ['hal/include/appTimer.h',                               condAlways],
        ['hal/include/halTaskManager.h',                         condAlways],
        ['hal/include/sleep.h',                                  condAlways],
        ['hal/include/sleepTimer.h',                             condAlways],
        ['hal/include/statStack.h',                              condAlways],
        #['hal/cortexm4/pic32cx/include/hal_aes_sync.h',          condAlways],
        ['hal/cortexm4/pic32cx/include/halAppClock.h',           condAlways],
        ['hal/cortexm4/pic32cx/include/halAssert.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halDbg.h',                condAlways],
        ['hal/cortexm4/pic32cx/include/halDiagnostic.h',         condAlways],
        #['hal/cortexm4/pic32cx/include/halFlash.h',              condAlways],
        ['hal/cortexm4/pic32cx/include/halMacIsr.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halRfCtrl.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halSleep.h',              condAlways],
        ['hal/cortexm4/pic32cx/include/halSleepTimerClock.h',    condAlways],
        #['hal/cortexm4/pic32cx/include/hpl_aes.h',               condAlways],
        #['hal/cortexm4/pic32cx/include/hpl_aes_sync.h',          condAlways],
        #['hal/cortexm4/pic32cx/include/hri_aes_e54.h',           condAlways],
        ['hal/cortexm4/pic32cx/include/halAes.h',                condAlways],
        # ['hal/cortexm4/pic32cx/include/Pic32cx_Miscellaneous.h', condAlways],
    ]

    zdrvStackZCLIncFiles = [
        ['zcl/clusters/include/groupsCluster.h',         condAlways],
        ['zcl/clusters/include/identifyCluster.h',       condAlways],
        ['zcl/clusters/include/scenes.h',                condAlways],
        ['zcl/include/zcl.h',                            condAlways],
        ['zcl/include/clusters.h',                       condAlways],
        # ['zcl/include/eccAux.h',                         condAlways],
        ['zcl/include/genericEcc.h',                     condAlways],
        ['zcl/include/zclAlarmsCluster.h',               condAlways],
        ['zcl/include/zclAttributes.h',                  condAlways],
        # ['zcl/include/zclBACnetProtocolTunnelCluster.h', condAlways],
        ['zcl/include/zclBasicCluster.h',                condAlways],
        ['zcl/include/zclCommandManager.h',              condAlways],
        # ['zcl/include/zclCommandAnalyzer.h',             condAlways],
        # ['zcl/include/zclDemandResponseCluster.h',       condAlways],
        ['zcl/include/zclDiagnosticsCluster.h',          condAlways],
        ['zcl/include/zclFanControlCluster.h',           condAlways],
        # ['zcl/include/zclGenericTunnelCluster.h',        condAlways],
        ['zcl/include/zclGreenPowerCluster.h',           condAlways],
        ['zcl/include/zclGroupsCluster.h',               condAlways],
        ['zcl/include/zclHumidityMeasurementCluster.h',  condAlways],
        ['zcl/include/zclIasACECluster.h',               condAlways],
        ['zcl/include/zclIasZoneCluster.h',              condAlways],
        ['zcl/include/zclIdentifyCluster.h',             condAlways],
        ['zcl/include/zclIlluminanceMeasurementCluster.h',  condAlways],
        ['zcl/include/zclInt.h',                            condAlways],
        # ['zcl/include/zclKeyEstablishmentCluster.h',        condAlways],
        ['zcl/include/zclLevelControlCluster.h',            condAlways],
        # ['zcl/include/zclLinkInfoCluster.h',                condAlways],
        ['zcl/include/zclMem.h',                            condAlways],
        ['zcl/include/zclMemoryManager.h',                  condAlways],
        # ['zcl/include/zclMessagingCluster.h',               condAlways],
        ['zcl/include/zcloccupancysensingcluster.h',        condAlways],
        ['zcl/include/zclOnOffCluster.h',                   condAlways],
        ['zcl/include/zclOnOffSwitchConfigurationCluster.h',   condAlways],
        ['zcl/include/zclParser.h',                            condAlways],
        # ['zcl/include/zclPowerConfigurationCluster.h',         condAlways],
        # ['zcl/include/zclPriceCluster.h',                      condAlways],
        ['zcl/include/zclScenesCluster.h',                     condAlways],
        ['zcl/include/zclSecurityManager.h',                   condAlways],
        # ['zcl/include/zclSimpleMeteringCluster.h',             condAlways],
        # ['zcl/include/zclSimpleMeteringClusterMacroSet.h',     condAlways],
        # ['zcl/include/zclSmartEnergyTunnelCluster.h',          condAlways],
        # ['zcl/include/zclTaskManager.h',                       condAlways],
        ['zcl/include/zclTemperatureMeasurementCluster.h',     condAlways],
        ['zcl/include/zclThermostatCluster.h',                 condAlways],
        ['zcl/include/zclThermostatUiConfCluster.h',           condAlways],
        ['zcl/include/zclTimeCluster.h',                       condAlways],
        ['zcl/include/zclZllBasicCluster.h',                   condAlways],
        ['zcl/include/zclZllColorControlCluster.h',            condAlways],
        ['zcl/include/zclZllCommissioningCluster.h',           condAlways],
        ['zcl/include/zclZllGroupsCluster.h',                  condAlways],
        ['zcl/include/zclZllIdentifyCluster.h',                condAlways],
        ['zcl/include/zclZllLevelControlCluster.h',            condAlways],
        ['zcl/include/zclZllOnOffCluster.h',                   condAlways],
        ['zcl/include/zclZllScenesCluster.h',                  condAlways],
        ['zcl/include/zclDbg.h',                                condOtauEnable],
        ['zcl/include/zclOtauManager.h',                        condOtauEnable],
        ['zcl/include/zclOTAUCluster.h',                        condOtauEnable],
        ['zcl/include/zclOtauClient.h',                         condOtauClient],
    ]

    zdrvStackZLLIncFiles = [
        ['zllplatform/devconfig.h',                                                  condAlways],
        ['zllplatform/ZLL/N_AddressManager/include/N_AddressManager.h',              condAlways],
        ['zllplatform/ZLL/N_AddressManager/include/N_AddressManager_Bindings.h',     condAlways],
        ['zllplatform/ZLL/N_AddressManager/include/N_AddressManager_Init.h',         condAlways],
        ['zllplatform/ZLL/N_AddressMap/include/N_AddressMap.h',                      condAlways],
        ['zllplatform/ZLL/N_AddressMap/include/N_AddressMap_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_Binding/include/N_Binding.h',                            condAlways],
        ['zllplatform/ZLL/N_Binding/include/N_Binding_Bindings.h',                   condAlways],
        ['zllplatform/ZLL/N_Binding/include/N_Binding_Init.h',                       condAlways],
        ['zllplatform/ZLL/N_Cmi/include/N_Cmi.h',                                    condAlways],
        ['zllplatform/ZLL/N_Cmi/include/N_Cmi_Bindings.h',                           condAlways],
        ['zllplatform/ZLL/N_Cmi/include/N_Cmi_Init.h',                               condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_Connection_ReconnectHandler.h',     condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_Connection.h',                      condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_Connection_Private.h',              condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_Connection_Internal.h',             condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_ConnectionEnddevice_Init.h',        condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_ConnectionRouter_Init.h',           condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_ConnectionEnddevice_Bindings.h',    condAlways],
        ['zllplatform/ZLL/N_Connection/include/N_ConnectionRouter_Bindings.h',       condAlways],
        ['zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo.h',                      condAlways],
        ['zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo_Init.h',                 condAlways],
        ['zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo_Version.h',              condAlways],
        ['zllplatform/ZLL/N_EndDeviceRobustness/include/N_EndDeviceRobustness.h',    condAlways],
        ['zllplatform/ZLL/N_EndDeviceRobustness/include/N_EndDeviceRobustness_Bindings.h', condAlways],
        ['zllplatform/ZLL/N_EndDeviceRobustness/include/N_EndDeviceRobustness_Init.h',     condAlways],
        ['zllplatform/ZLL/N_Groups/include/N_Groups.h',                                    condAlways],
        ['zllplatform/ZLL/N_Groups/include/N_Groups_Bindings.h',                           condAlways],
        ['zllplatform/ZLL/N_InterPan/include/N_InterPan.h',                                condAlways],
        ['zllplatform/ZLL/N_InterPan/include/N_InterPan_Bindings.h',                       condAlways],
        ['zllplatform/ZLL/N_InterPan/include/N_InterPan_Init.h',                           condAlways],
        ['zllplatform/ZLL/N_InterPan/include/N_InterPanBuffers.h',                         condAlways],
        ['zllplatform/ZLL/N_LinkInitiator/include/N_LinkInitiator.h',                      condAlways],
        ['zllplatform/ZLL/N_LinkInitiator/include/N_LinkInitiator_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_LinkInitiator/include/N_LinkInitiator_Init.h',                 condAlways],
        ['zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget.h',                            condAlways],
        ['zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget_Bindings.h',                   condAlways],
        ['zllplatform/ZLL/N_LinkTarget/include/N_LinkTarget_Init.h',                       condAlways],
        ['zllplatform/ZLL/N_PacketDistributor/include/N_PacketDistributor.h',              condAlways],
        ['zllplatform/ZLL/N_PacketDistributor/include/N_ZllEndpoint.h',                    condAlways],
        ['zllplatform/ZLL/N_Radio/include/N_Radio.h',                                      condAlways],
        ['zllplatform/ZLL/N_Radio/include/N_Radio_Bindings.h',                             condAlways],
        ['zllplatform/ZLL/N_Radio/include/N_Radio_Init.h',                                 condAlways],
        ['zllplatform/ZLL/N_Radio/include/N_Radio_Internal.h',                             condAlways],
        ['zllplatform/ZLL/N_ReconnectHandler/include/N_ReconnectHandler.h',                condAlways],
        ['zllplatform/ZLL/N_ReconnectHandler/include/N_ReconnectHandler_Bindings.h',       condAlways],
        ['zllplatform/ZLL/N_ReconnectHandler/include/N_ReconnectHandler_Init.h',           condAlways],
        ['zllplatform/ZLL/N_Security/include/N_Security.h',                                condAlways],
        ['zllplatform/ZLL/N_Security/include/N_Security_Bindings.h',                       condAlways],
        ['zllplatform/ZLL/N_Security/include/N_Security_Init.h',                           condAlways],
        ['zllplatform/ZLL/N_Security/include/N_Security_Calc.h',                           condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_Framework.h',                      condAlways],
        ['zllplatform/ZLL/N_Zdp/include/N_Zdp.h',                                          condAlways],
        ['zllplatform/ZLL/N_Zdp/include/N_Zdp_Bindings.h',                                 condAlways],
        # ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_DataRequest.h',                    condAlways],
        # ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_DataInd.h',                        condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_Framework_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_Beacon/include/N_Beacon.h',                                    condAlways],
        #['zllplatform/infrastructure/N_Beacon/include/N_Beacon.h',                         condAlways],
        ['zllplatform/infrastructure/N_Address/include/N_Address.h',                       condAlways],
        ['zllplatform/infrastructure/N_ErrH/include/N_ErrH.h',                             condAlways],
        ['zllplatform/infrastructure/N_Types/include/N_Types.h',                           condAlways],
        ['zllplatform/infrastructure/N_Fsm/include/N_Fsm.h',                               condAlways],
        ['zllplatform/infrastructure/N_Log/include/N_Log.h',                               condAlways],
        ['zllplatform/infrastructure/N_Init/include/N_Init.h',                             condAlways],
        ['zllplatform/infrastructure/N_Init/include/N_Init-Atmel_Bindings.h',              condAlways],
        ['zllplatform/infrastructure/N_Memory/include/N_Memory.h',                         condAlways],
        ['zllplatform/infrastructure/N_Task/include/N_Task.h',                             condAlways],
        ['zllplatform/infrastructure/N_Task/include/N_Task_Bindings.h',                    condAlways],
        ['zllplatform/infrastructure/N_Task/include/N_Task_Init.h',                        condAlways],
        ['zllplatform/infrastructure/N_Task/include/N_Task-Internal.h',                    condAlways],
        ['zllplatform/infrastructure/N_Timer/include/N_Timer.h',                           condAlways],
        ['zllplatform/infrastructure/N_Timer/include/N_Timer_Bindings.h',                  condAlways],
        ['zllplatform/infrastructure/N_Timer/include/N_Timer_Init.h',                      condAlways],
        ['zllplatform/infrastructure/N_Timer/include/N_Timer-Internal.h',                  condAlways],
        ['zllplatform/infrastructure/N_Util/include/N_Util.h',                             condAlways],
        ['zllplatform/infrastructure/N_Util/include/N_Util_Bindings.h',                    condAlways],
    ]

    zdrvStackPdsServerIncFiles = [
        ['pds/include/wlPdsMemIds.h',                                        condAlways],
        ['pds/include/wlPdsTypesConverter.h',                                condAlways],
        ['pds/include/bcPDS.h',                                              condAlways],
    ]

    zdrvGreenPowerIncFiles = [
        ['ZGP/GPInfrastructure/highZgp/include/zgpCluster.h',                    condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/zgpClusterStructure.h',           condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/zgpClusterZclInterface.h',        condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/zgpInfraDevice.h',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/zgpMiddleProxy.h',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterClient.h',      condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterGeneric.h',     condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterServer.h',      condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpHighGeneric.h',        condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpHighMem.h',            condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpProxyBasic.h',         condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpProxyTable.h',         condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpSinkBasic.h',          condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpSinkTable.h',          condDevGPNotNone],
        
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLow.h',                         condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowGpdf.h',                     condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowNvmTable.h',                 condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowMiddleProxy.h',              condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpCstub.h',               condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpDstub.h',               condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowGeneric.h',          condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowMem.h',              condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowProxy.h',            condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowSink.h',             condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpNvmTable.h',            condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpNvmTableBindings.h',    condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpPacket.h',              condDevGPNotNone], 
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpTaskManager.h',         condDevGPNotNone],

        ['ZGP/include/zgpCommon.h',                                              condDevGPNotNone],
        ['ZGP/include/zgpDbg.h',                                                 condDevGPNotNone],
    ]

    for incFileEntry in zdrvStackPdsServerIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackAPSIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackBDBIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackConfigServerIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackNWKIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackMACIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackHALIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackSYSENVIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackSECIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackZDOIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackZCLIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvStackZLLIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zdrvGreenPowerIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)

    utilsIncFiles = [
        ['utils/compiler.h',                       condAlways],
        ['utils/interrupt.h',                      condAlways],
        ['utils/status_codes.h',                   condAlways],
        ['utils/interrupt/interrupt_sam_nvic.h',   condAlways],
        ['utils/preprocessor/mrecursion.h',        condAlways],
        ['utils/preprocessor/mrepeat.h',           condAlways],
        ['utils/preprocessor/preprocessor.h',      condAlways],
        ['utils/preprocessor/stringz.h',           condAlways],
        ['utils/preprocessor/tpaste.h',            condAlways],
    ]

    clusterCommonIncFiles = [
        #['application/zigbee_only/Zigbee_Device_Application/common/include/app_zigbee.h',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/basicCluster.h',           condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/colorControlCluster.h',    condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/commissioningCluster.h',   condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/include/groupsCluster.h',          condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/haClusters.h',             condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/include/identifyCluster.h',        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/levelControlCluster.h',    condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/onOffCluster.h',           condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/include/scenes.h',                 condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/scenesCluster.h',          condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/bdb/include/bdb_api.h',                     condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/configServer/include/cs_api.h',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/nwk/include/nwk_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zcl/include/zcl_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zdo/include/zdo_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zgb_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/appConsts.h',                       condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/colorSceneRemoteBindings.h',        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/commandManager.h',                  condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/include/consoleCmds.h',                     condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/ezModeManager.h',                   condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/hs2xy.h',                           condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/keyboardPoll.h',                    condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/otauService.h',                     condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/include/S_SerialComm.h',                    condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/system.h',                          condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/z3Device.h',                        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/zgb_task.h',                        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/zgpAppConfig.h',                    condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/zgpAppInterface.h',                 condAlways],
    ]

    # cmsisIncFiles = [
        # ['cmsis/core_cm4.h',                         condAlways],
        # ['cmsis/core_cmFunc.h',                      condAlways],
        # ['cmsis/core_cmInstr.h',                     condAlways],
        # ['cmsis/core_cmSimd.h',                      condAlways],
    # ]

    driversIncFiles = [
        #['drivers/sercom/usart/usart.h',              condAlways],
        ['drivers/PersistDataServer/wl/include/wlPdsBindings.h',        condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv.h',               condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Bindings.h',      condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Init.h',          condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Stack_Ids.h',     condAlways],
    ]

    devicesIncFiles = [
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/light.h',                                        condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightBasicCluster.h',                            condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightClusters.h',                                condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightColorControlCluster.h',                     condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightColorSchemesConversion.h',                  condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightCommissioningCluster.h',                    condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightGroupsCluster.h',                           condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightIdentifyCluster.h',                         condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightLevelControlCluster.h',                     condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightOnOffCluster.h',                            condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include/lightScenesCluster.h',                           condDevLight],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/buttonHandlers.h',                condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscBasicCluster.h',               condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscClusters.h',                   condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscColorControlCluster.h',        condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscCommissioningCluster.h',       condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscGroupsCluster.h',              condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscIdentifyCluster.h',            condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscLevelControlCluster.h',        condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscOnOffCluster.h',               condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include/cscScenesCluster.h',              condDevColorSceneController],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciAlarmsCluster.h',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciBasicCluster.h',                   condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciClusters.h',                       condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciColorControlCluster.h',            condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciCommissioningCluster.h',           condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciFanControlCluster.h',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciGroupsCluster.h',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciHumidityMeasurementCluster.h',     condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciIasACECluster.h',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciIasZoneCluster.h',                 condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciIdentifyCluster.h',                condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciIlluminanceMeasurementCluster.h',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciLevelControlCluster.h',            condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciOccupancySensingCluster.h',        condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciOnOffCluster.h',                   condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciScenesCluster.h',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciTemperatureMeasurementCluster.h',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciThermostatCluster.h',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciThermostatUiConfCluster.h',        condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciTimeCluster.h',                    condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/combinedInterface.h',                condDevCombInterface],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbBasicCluster.h',                       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbClusters.h',                           condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbColorControlCluster.h',                condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbCommissioningCluster.h',               condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbGroupsCluster.h',                      condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbIdentifyCluster.h',                    condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbIlluminanceMeasurementCluster.h',      condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbLevelControlCluster.h',                condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbOccupancySensingCluster.h',            condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbOnOffCluster.h',                       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include/cbScenesCluster.h',                      condDevControlBridge],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasACEAceCluster.h',                           condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasacebasiccluster.h',                         condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasACECluster.h',                              condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasACEGroupsCluster.h',                        condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasaceidentifycluster.h',                      condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include/iasACEZoneCluster.h',                          condDevIasAce],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/hsBasicCluster.h',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/hsGroupsCluster.h',                        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/hsHumidityMeasurementCluster.h',           condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/hsIdentifyCluster.h',                      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/lsBasicCluster.h',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/lsGroupsCluster.h',                        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/lsIdentifyCluster.h',                      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/lsIlluminanceMeasurementCluster.h',        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/msClusters.h',                             condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/multiSensor.h',                            condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/osBasicCluster.h',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/osGroupsCluster.h',                        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/osIdentifyCluster.h',                      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/osOccupancySensingCluster.h',              condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/tsBasicCluster.h',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/tsGroupsCluster.h',                        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/tsIdentifyCluster.h',                      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include/tsTemperatureMeasurementCluster.h',        condDevMultiSensor],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thAlarmsCluster.h',                         condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thBasicCluster.h',                          condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thClusters.h',                              condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thFanControlCluster.h',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thGroupsCluster.h',                         condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thHumidityMeasurementCluster.h',            condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thIdentifyCluster.h',                       condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thOccupancySensingCluster.h',               condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thScenesCluster.h',                         condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thTemperatureMeasurementCluster.h',         condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thThermostatCluster.h',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thThermostatUiConfCluster.h',               condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include/thTimeCluster.h',                           condDevThermostat],

        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/custom.h',                                        condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customAlarmsCluster.h',                           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customBasicCluster.h',                            condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customClusters.h',                                condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customDiagnosticsCluster.h',                     condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customColorControlCluster.h',                     condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customColorSchemesConversion.h',                  condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customCommissioningCluster.h',                    condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customGroupsCluster.h',                           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customIdentifyCluster.h',                         condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customLevelControlCluster.h',                     condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customOnOffCluster.h',                            condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customScenesCluster.h',                           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customHumidityMeasurementCluster.h',              condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customIlluminanceMeasurementCluster.h',           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customOccupancySensingCluster.h',                 condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customTemperatureMeasurementCluster.h',           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customFanControlCluster.h',                       condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customIasACECluster.h',                           condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customIasZoneCluster.h',                          condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customThermostatCluster.h',                       condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customThermostatUiConfCluster.h',                 condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/include/customTimeCluster.h',                             condDevCustom],
    ]

    #applicationConfigIncFiles = [
        #['application/zigbee_only/Zigbee_Device_Application/configs/bitcloudPreInclude.h',              condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/configs/stackConfig.h',                     condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/configs/otauConfig.h',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/configs/zigbeeAppConfig.h',                 condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/configs/zigbeeAppDeviceSelect.h',           condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/configs/FreeRTOSConfig.h',                  condAlways],
    #]

    applicationCommonIncFiles = [
        ['application/zigbee_only/Zigbee_Device_Application/common/include/printLcd.h',                                            condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/errH.h',                                                condAlways],
        #['application/zigbee_only/common_files/include/console.h',                                             condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/otau/isd/include/isdFakeDriver.h',      condOtauServer],
        ['application/zigbee_only/Zigbee_Device_Application/otau/isd/include/isdImageStorage.h',      condOtauServer],
        ['application/zigbee_only/Zigbee_Device_Application/otau/isd/include/isdConsoleTunneling.h',      condOtauServer],
        ['application/zigbee_only/Zigbee_Device_Application/otau/ofd/include/ofdMemoryDriver.h',    condOtauClient],
    ]

    zgbWrappersIncFiles = [
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/bdb/include/BDB_Unpack.h',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/configServer/include/CS_Unpack.h',              condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/nwk/include/NWK_Unpack.h',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zcl/include/ZCL_Unpack.h',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zdo/include/ZDO_Unpack.h',                      condAlways],
    ]

    # frameworkIncFiles = [
        # ['framework/framework_defs.h',                      condAlways],
        # ['framework/osal/osal_freertos.h',                  condAlways],
        # ['framework/osal/osal_freertos_extend.h',           condAlways],
    # ]

    for incFileEntry in devicesIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    # for incFileEntry in cmsisIncFiles:
        # importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in clusterCommonIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    #for incFileEntry in freeRTOSIncFiles:
        #importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    #for incFileEntry in utilsIncFiles:
        #importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    #for incFileEntry in driversIncFiles:
        #importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    #for incFileEntry in driversPDSIncFiles:
     #   importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zgbWrappersIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    # for incFileEntry in frameworkIncFiles:
        # importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    #for incFileEntry in applicationConfigIncFiles:
        #importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in applicationCommonIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)
################################### APS FILES #######################################################

################################### SOURCE FILES ####################################################
################################### APS FILES #######################################################
    zdrvStackAPSSrcFiles = [
    ]

    zdrvStackBDBSrcFiles = [
    ]

    zdrvStackConfigServerSrcFiles = [
        ['configserver/src/configserver.c',      condAlways],
        ['configserver/src/csMem.c',             condAlways],
        ['configserver/src/csPersistentMem.c',   condAlways],
    ]

    zdrvStackNWKSrcFiles = [
    ]

    zdrvStackMACSrcFiles = [
    ]

    zdrvStackSYSENVSrcFiles = [
        ['systemenvironment/src/dbg.c',                 condAlways],
        ['systemenvironment/src/sysAssert.c',           condAlways],
        ['systemenvironment/src/sysDuplicateTable.c',   condAlways],
        ['systemenvironment/src/sysEventsHandler.c',    condAlways],
        ['systemenvironment/src/sysIdleHandler.c',      condAlways],
        ['systemenvironment/src/sysInit.c',             condAlways],
        ['systemenvironment/src/sysMutex.c',            condAlways],
        ['systemenvironment/src/sysQueue.c',            condAlways],
        ['systemenvironment/src/sysSleep.c',            condAlways],
        ['systemenvironment/src/sysStat.c',             condAlways],
        ['systemenvironment/src/sysTaskManager.c',      condAlways],
        ['systemenvironment/src/sysTimer.c',            condAlways],
        ['systemenvironment/src/sysUtils.c',            condAlways],
    ]

    zdrvStackSECSrcFiles = [
    ]

    zdrvStackZDOSrcFiles = [
    ]

    zdrvStackZCLSrcFiles = [
        ['zcl/src/zclCommandManager.c',                  condAlways],
        #['zcl/clusters/src/groupsCluster.c',             condAlways],
        #['zcl/clusters/src/identifyCluster.c',           condAlways],
        ['zcl/clusters/src/scenes.c',                    condAlways],
        ['zcl/src/zclOtauServer.c',                      condOtauServer],
        ['zcl/src/zclOtauClient.c',                      condOtauClient],
        ['zcl/src/zclOtauClientDiscovery.c',             condOtauClient],
        ['zcl/src/zclOtauClientDownload.c',              condOtauClient],
        ['zcl/src/zclOtauClientPdt.c',                   condOtauClient],
        ['zcl/src/zclOtauClientQuery.c',                 condOtauClient],
        ['zcl/src/zclOtauClientUpgrade.c',               condOtauClient],
    ]

    zdrvStackHALSrcFiles = [
        ['hal/cortexm4/pic32cx/src/atomic.c',                 condAlways],
        #['hal/cortexm4/pic32cx/src/hal_aes_sync.c',           condAlways],
        ['hal/cortexm4/pic32cx/src/halAppClock.c',            condAlways],
        #['hal/cortexm4/pic32cx/src/halFlash.c',               condAlways],
        ['hal/cortexm4/pic32cx/src/halMacIsr.c',              condAlways],
        ['hal/cortexm4/pic32cx/src/halRfCtrl.c',              condAlways],
        ['hal/cortexm4/pic32cx/src/halSleep.c',               condAlways],
        ['hal/cortexm4/pic32cx/src/halSleepTimerClock.c',     condAlways],
        #['hal/cortexm4/pic32cx/src/hpl_aes.c',                condAlways],
        ['hal/cortexm4/pic32cx/src/halAes.c',                 condAlways],
        ['hal/cortexm4/common/src/appTimer.c',                condAlways],
        ##['hal/cortexm4/common/src/flash.c',                   condAlways],
        ['hal/cortexm4/common/src/halTaskManager.c',          condAlways],
        ['hal/cortexm4/common/src/sleep.c',                   condAlways],
        ['hal/cortexm4/common/src/sleepTimer.c',              condAlways],
        ['hal/cortexm4/common/src/statStack.c',               condAlways],
        ['hal/cortexm4/common/src/timer.c',                   condAlways],
    ]

    zdrvStackZLLSrcFiles = [
       ['zllplatform/infrastructure/N_Util/src/N_Util.c',          condAlways],
    ]

    zdrvStackPDSSrcFiles = [
        ['pds/src/bcPDS.c',                                     condAlways],
        ['pds/src/wlPdsTypesConverter.c',                       condAlways],

    ]
    
    zdrvBSPSrcFiles = [
        ['bsp/PIC32CX/src/fakeBSP.c',                                     condAlways],
    ]

    zdrvGreenPowerSrcFiles = [
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterClient.c',          condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterGeneric.c',         condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterServer.c',          condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpHighGeneric.c',            condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpHighMem.c',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpMiddleProxy.c',            condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyBasic.c',             condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyPdt.c',               condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyTable.c',             condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkBasic.c',              condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkPdt.c',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkTable.c',              condDevGPNotNone],
        
        ['ZGP/GPInfrastructure/lowZgp/src/zgpCstub.c',                   condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpDstub.c',                   condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowGeneric.c',              condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowMem.c',                  condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowProxy.c',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowSink.c',                 condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpNvmTable.c',                condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpPacket.c',                  condDevGPNotNone],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpTaskManager.c',             condDevGPNotNone],
        
        ['ZGP/GPInfrastructure/src/zgpGeneric.c',                        condDevGPNotNone],
    ]
    
    for srcFileEntry in zdrvStackAPSSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackBDBSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackConfigServerSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackNWKSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackMACSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackSYSENVSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackSECSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackZDOSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackZCLSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackHALSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackZLLSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackPDSSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvBSPSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvGreenPowerSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    #freeRTOSSrcFiles = [
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/list.c',                      condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/queue.c',                     condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/tasks.c',                     condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/timers.c',                    condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/GCC/ARM_CM4F/port.c',condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang/heap_2.c',   condAlways],
    #]

    utilsSrcFiles = [
       # ['utils/interrupt/interrupt_sam_nvic.c',                      condAlways],
    ]

    #frameworkSrcFiles = [
        #['framework/osal/src/osal_freertos.c',                        condAlways],
        #['framework/osal/src/osal_freertos_extend.c',               condAlways],
    #]

    driversSrcFiles = [
        # ['drivers/sercom/usart/drv_usart.c',                  condAlways],
        # ['drivers/sercom/usart/write.c',                      condAlways],
      ##  ['drivers/PersistDataServer/src/fakePds.c',                       condAlways],
      ##  ['drivers/PersistDataServer/wl/src/wlPdsDataServer.c',            condAlways],
      ##  ['drivers/PersistDataServer/wl/src/wlPdsInit.c',                  condAlways],
      ##  ['drivers/PersistDataServer/wl/src/wlPdsSecurity.c',              condAlways],
      ##  ['drivers/PersistDataServer/S_Nv/src/S_Nv-Pic32cx.c',               condAlways],
        #['drivers/PersistDataServer/S_Nv/src/S_Nv-External.c',              condAlways],
        #['drivers/PersistDataServer/S_Nv/src/S_Nv_Stub.c',                  condAlways],
      ##  ['drivers/PersistDataServer/D_Nv/src/D_Nv.c',                       condAlways],
        #['drivers/PersistDataServer/S_XNv/src/S_XNv.c',                     condAlways],
     ##   ['drivers/PersistDataServer/flash/flash.c',                     condAlways],
      ##  ['drivers/PersistDataServer/flash/halFlash.c',                     condAlways],
#       ['zllplatform/ZLL/D_XNv/src/D_XNv.c',                     condPDSUseExternalMem],
    ]

    zgbWrappersSrcFiles = [
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/bdb/BDB_Unpack.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/configServer/CS_Unpack.c',              condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/nwk/NWK_Unpack.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zcl/ZCL_Unpack.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zdo/ZDO_Unpack.c',                      condAlways],
    ]
    
    otauServerSrcFiles = [
        ['src/Components/zcl/src/zclOtauServer.c',                      condOtauServer],
    ]

    applicationCommonSrcFiles = [
        #['application/zigbee_only/common_files/src/initialization.c',                                    condAlways],
         ['application/zigbee_only/Zigbee_Device_Application/common/zigbee_init.c',                                    condAlways],    
        ##['application/zigbee_only/Zigbee_Device_Application/common/app_zigbee.c',                    condAlways],
        ##['application/zigbee_only/Zigbee_Device_Application/common/main.c',                          condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/zgb_init.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/zgb_task.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/system_tasks.c',                  condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/common/zgb_app_callback.c',              condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/z3DevicePic32cx.c',               condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/z3Device.c',                     condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/otauService.c',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/zgpTranslationTable.c',           condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/zgpAppInterface.c',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/hs2xy.c',                         condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/errH.c',                                              condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/identifyCluster.c',             condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/scenes.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/groupsCluster.c',               condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/haClusters.c',                  condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/levelControlCluster.c',         condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/colorControlCluster.c',         condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/onOffCluster.c',                condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/commissioningCluster.c',        condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/alarmCluster.c',                condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/scenesCluster.c',                condAlways],

        # Console Files
        #['application/zigbee_only/Zigbee_Device_Application/common/console.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/consoleCmds.c',                  condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/commandManager.c',               condAlways],
        # ['application/zigbee_only/common_files/uartManager.c',                                      condAlways],

        # API Wrapper Files
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/bdb/BDB_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/configServer/CS_API.c',                       condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/nwk/NWK_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zcl/ZCL_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/stack_interface/zdo/ZDO_API.c',                      condAlways],
        # OTAU dependent files
        ['application/zigbee_only/Zigbee_Device_Application/otau/common/appOtauManager.c',         condOtauEnable],
        ['application/zigbee_only/Zigbee_Device_Application/otau/isd/isdConsoleTunneling.c',      condOtauServer],
        ['application/zigbee_only/Zigbee_Device_Application/otau/isd/isdImageStorage.c',      condOtauServer],
        # ['application/zigbee_only/Zigbee_Device_Application/otau/ofd/ofdFakeDriver.c',      condOtauClient],
    ]

    #consoleCommonSrcFiles = [
    #    ['application/zigbee_only/Zigbee_Device_Application/common/console.c',                      condAlways],
    #    ['application/zigbee_only/Zigbee_Device_Application/common/consoleCmds.c',                  condAlways],
    #    ['application/zigbee_only/Zigbee_Device_Application/common/commandManager.c',               condAlways],
    #]

    applicationClustersSrcFiles = [
        #['application/zigbee_only/Zigbee_Device_Application/clusters/identifyCluster.c',             condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/scenes.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/groupsCluster.c',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/haClusters.c',                  condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/clusters/levelControlCluster.c',         condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/clusters/colorControlCluster.c',         condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/clusters/onOffCluster.c',                condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/commissioningCluster.c',        condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/clusters/alarmCluster.c',                condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/clusters/scenesCluster.c',                condAlways],
        #['src/Components/zcl/clusters/groupsCluster.c',                                              condAlways],
        #['src/Components/zcl/clusters/identifyCluster.c',                                            condAlways],
        #['src/Components/zcl/clusters/scenes.c',                                                     condAlways],
    ]

    deviceTypesSrcFiles = [
         # Light Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/light.c',                                     condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightClusters.c',                             condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightBasicCluster.c',                         condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightIdentifyCluster.c',                      condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightGroupsCluster.c',                        condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightScenesCluster.c',                        condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightOnOffCluster.c',                         condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightLevelControlCluster.c',                  condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightColorControlCluster.c',                  condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightColorSchemesConversion.c',               condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightCommissioningCluster.c',                 condDevLight],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightConsole.c',                              condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/lightPdt.c',                                  condDevLight],

        # Color Scene Controller Device Type
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/colorSceneController.c',       condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscBasicCluster.c',            condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscClusters.c',                condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscColorControlCluster.c',     condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscCommissioningCluster.c',    condDevColorSceneController],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscConsole.c',                 condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscGroupsCluster.c',           condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscIdentifyCluster.c',         condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscLevelControlCluster.c',     condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscOnOffCluster.c',            condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/cscScenesCluster.c',           condDevColorSceneController],

        # Combined Interface Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciAlarmsCluster.c',               condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciBasicCluster.c',                condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciClusters.c',                    condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciColorControlCluster.c',         condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciCommissioningCluster.c',        condDevCombInterface],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciConsole.c',                     condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciFanControlCluster.c',           condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciGroupsCluster.c',               condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciHumidityMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciIasACECluster.c',               condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciIasZoneCluster.c',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciIdentifyCluster.c',                condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciIlluminanceMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciLevelControlCluster.c',            condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciOccupancySensingCluster.c',        condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciOnOffCluster.c',                   condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciScenesCluster.c',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciTemperatureMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciThermostatCluster.c',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciThermostatUiConfCluster.c',        condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/ciTimeCluster.c',                    condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/combinedInterface.c',                condDevCombInterface],

          # Control Bridge Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbBasicCluster.c',                  condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbClusters.c',                      condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbColorControlCluster.c',           condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbCommissioningCluster.c',          condDevControlBridge],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbConsole.c',                       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbGroupsCluster.c',                 condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbIdentifyCluster.c',               condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbIlluminanceMeasurementCluster.c', condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbLevelControlCluster.c',           condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbOccupancySensingCluster.c',       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbOnOffCluster.c',                  condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/cbScenesCluster.c',                 condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/controlBridge.c',                   condDevControlBridge],

          # Dimmer Switch Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dimmerSwitch.c',                     condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsBasicCluster.c',                   condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsClusters.c',                       condDevDimmerSwitch],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsConsole.c',                        condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsGroupsCluster.c',                  condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsIdentifyCluster.c',                condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsLevelControlCluster.c',            condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsOnOffCluster.c',                   condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/dsScenesCluster.c',                  condDevDimmerSwitch],

         # IAS ACE
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACE.c',                                condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEAceCluster.c',                      condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEBasicCluster.c',                    condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACECluster.c',                         condDevIasAce],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEConsole.c',                         condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEGroupsCluster.c',                   condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEIdentifyCluster.c',                 condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEPdt.c',                             condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/iasACEZoneCluster.c',                     condDevIasAce],

         # Multi Sensor
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/hsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/hsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/hsHumidityMeasurementCluster.c',      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/hsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/lsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/lsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/lsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/lsIlluminanceMeasurementCluster.c',   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/msClusters.c',                        condDevMultiSensor],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/msConsole.c',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/msPdt.c',                             condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/multiSensor.c',                       condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/osBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/osGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/osIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/osOccupancySensingCluster.c',         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/tsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/tsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/tsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/tsTemperatureMeasurementCluster.c',   condDevMultiSensor],

         # Thermostat
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thAlarmsCluster.c',                     condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thBasicCluster.c',                      condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thClusters.c',                          condDevThermostat],
        #['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thConsole.c',                           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thermostat.c',                          condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thFanControlCluster.c',                 condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thGroupsCluster.c',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thHumidityMeasurementCluster.c',        condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thIdentifyCluster.c',                   condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thOccupancySensingCluster.c',           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thPdt.c',                               condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thScenesCluster.c',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thTemperatureMeasurementCluster.c',     condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thThermostatCluster.c',                 condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thThermostatUiConfCluster.c',           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/thTimeCluster.c',                       condDevThermostat],

        # custom Device Type Files 
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/custom.c',                                     condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customClusters.c',                             condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customBasicCluster.c',                         condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customIdentifyCluster.c',                      condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customGroupsCluster.c',                        condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customScenesCluster.c',                        condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customOnOffCluster.c',                         condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customLevelControlCluster.c',                  condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customColorControlCluster.c',                  condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customColorSchemesConversion.c',               condDevCustom],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customCommissioningCluster.c',                 condDevCustom],
        # ['application/zigbee_only/Zigbee_Device_Application/devicetypes/custom/customConsole.c',                              condDevCustom],
    ]

    zigbeeLightSrc = drvZigbeeComponent.createFileSymbol("ZIGBEELIGHT_SRC", None)
    zigbeeLightSrc.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_Device_Application/devicetypes/light/light.c")
    zigbeeLightSrc.setOutputName("light.c")
    zigbeeLightSrc.setDestPath("/zigbee/z3device/light")
    zigbeeLightSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light")
    zigbeeLightSrc.setType("SOURCE")
    zigbeeLightSrc.setEnabled(False)
    zigbeeLightSrc.setDependencies(setEnableLightDevice, ["ZB_DEVICE_TYPE"])

    #for srcFileEntry in freeRTOSSrcFiles:
        #importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    #for srcFileEntry in utilsSrcFiles:
        #importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    #for srcFileEntry in frameworkSrcFiles:
        #importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in driversSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    #for srcFileEntry in driversPDSSrcFiles:
     #   importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zgbWrappersSrcFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationCommonSrcFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)

#    for srcFileEntry in consoleCommonSrcFiles:
#        importConsoleSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationClustersSrcFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in deviceTypesSrcFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)


    zigbeeStackdrvIncPaths = [
        ['/src/Components',                                                    condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application',                   condAlways], 
        ['/application/zigbee_only/Zigbee_Device_Application/configs',                                     condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes',                                 condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include',    condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include',       condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include',           condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmableLight/include',           condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/include',            condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/extendedColorLight/include',      condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include',                 condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include',                   condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include',             condAlways],
        #['/application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include',              condAlways],
        ['/peripheral',                                                                                    condAlways],
        ['/driver/pds/include',                                                                            condAlways],
        #['/peripheral/trng',                                                                               condAlways],
        ['/crypto',                                                                                        condAlways],
    ]

    for incPathEntry in zigbeeStackdrvIncPaths:
        setIncPath(drvZigbeeComponent, configName, incPathEntry)

    preprocessormac = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR', None) 
    preprocessormac.setValue('_PIC32CX_;PIC32CX_CHIP_SOC')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('preprocessor-macros')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    preprocessormac = drvZigbeeComponent.createSettingSymbol('ZIGBEE_ISOLATEFUNCTION', None) 
    preprocessormac.setValue('false')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('isolate-each-function')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    preprocessormac = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PLACEDATASECTION', None) 
    preprocessormac.setValue('false')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('place-data-into-section')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    # Disable Default linker script
    Database.setSymbolValue("core", "ADD_LINKER_FILE", False)

    # Use Custom linker script
    #zigbeeLinkerFile = drvZigbeeComponent.createFileSymbol("ZB_LINKER_FILE", None)
    #zigbeeLinkerFile.setSourcePath("/driver/zigbee/templates/zb_PIC32CX1012BZ25048.ld")
    #zigbeeLinkerFile.setOutputName("zb_PIC32CX1012BZ25048.ld")
    #zigbeeLinkerFile.setMarkup(True)
    #zigbeeLinkerFile.setOverwrite(True)
    #zigbeeLinkerFile.setType("LINKER")

    # Setting the required heap size for the application
    Database.sendMessage("core", "HEAP_SIZE", {"heap_size":4096})

    preprocessorLD = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD3', None)
    preprocessorLD.setValue('1024')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('stack-size')
    preprocessorLD.setEnabled(True)

    preprocessorAS = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_AS', None)
    preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;_USE_LIB_;_SUPER_SET_LIB_;HAL_USE_FLASH_ACCESS;Z3DEVICE_APP')
    preprocessorAS.setCategory('C32')
    preprocessorAS.setKey('preprocessor-macros')
    preprocessorAS.setAppend(True, ';')
    preprocessorAS.setEnabled(True)

    warningerr = drvZigbeeComponent.createSettingSymbol('WARNINGG_ERR', None)
    warningerr.setValue('false')
    warningerr.setCategory('C32')
    warningerr.setKey('make-warnings-into-errors')

    warningadd = drvZigbeeComponent.createSettingSymbol('WARNINGG_ADD', None)
    warningadd.setValue('false')
    warningadd.setCategory('C32')
    warningadd.setKey('additional-warnings')

    optlevel = drvZigbeeComponent.createSettingSymbol('PET_LEVEL', None)
    optlevel.setValue('-O2')
    optlevel.setCategory('C32')
    optlevel.setKey('optimization-level')

    #setAdditionaloptionXC32GCC = drvZigbeeComponent.createSettingSymbol('SET_XC32_GCC_ADD_INC', None)
    #setAdditionaloptionXC32GCC.setValue('-include"zigbeeAppConfig.h"')
    #setAdditionaloptionXC32GCC.setCategory('C32')
    #setAdditionaloptionXC32GCC.setKey('appendMe')

################################### Library File ####################################################
    # Makerule
    zigbeeMakeRulesFile = drvZigbeeComponent.createFileSymbol("ZIGBEE_MAKERULE_HEADER", None)
    zigbeeMakeRulesFile.setSourcePath("/driver/zigbee/templates/Zigbee_AllDevice_Makerules.h.ftl")
    zigbeeMakeRulesFile.setOutputName("Zigbee_AllDevice_Makerules.h")
    zigbeeMakeRulesFile.setDestPath("/zigbee/lib/")
    zigbeeMakeRulesFile.setProjectPath("config/" + configName + "/zigbee/lib/")
    zigbeeMakeRulesFile.setType("HEADER")
    zigbeeMakeRulesFile.setOverwrite(True)
    zigbeeMakeRulesFile.setMarkup(True)

    setAdditionaloptionXC32GCC = drvZigbeeComponent.createSettingSymbol('SET_XC32_GCC_ADD_INC', None)
    setAdditionaloptionXC32GCC.setValue('-include"lib/Zigbee_AllDevice_Makerules.h"')
    setAdditionaloptionXC32GCC.setCategory('C32')
    setAdditionaloptionXC32GCC.setKey('appendMe')

    zigbeeLibFile = drvZigbeeComponent.createLibrarySymbol("ZB_LIB_FILE", None)
    zigbeeLibFile.setDestPath('/zigbee/lib/')
    zigbeeLibFile.setSourcePath("/driver/zigbee/src/lib/Zigbee_AllDevice_Lib.a")
    zigbeeLibFile.setOutputName("zigbee_alldevice_lib.a")
################################### SOURCE FILES ####################################################

def importIncFile(component, configName, incFileEntry, firmwarePath = None):
    incFilePath  = incFileEntry[0]
    isEnabled    = incFileEntry[1][0]
    callback     = incFileEntry[1][1]
    dependencies = incFileEntry[1][2]

    incFilePathTup = incFilePath.rsplit('/', 1)

    if len(incFilePathTup) == 1:
        secName = ''
        incFile = incFilePathTup[0]
    else :
        secName = incFilePathTup[0]
        incFile = incFilePathTup[1]

    symName = incFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath('driver/zigbee/src/Components/' + secSName + '/' + incFile)
    incFileSym.setOutputName(incFile)
    incFileSym.setDestPath('/zigbee/lib/inc/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/zigbee/lib/inc/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importIncFileNonStack(component, configName, incFileEntry, firmwarePath = None):
    incFilePath  = incFileEntry[0]
    isEnabled    = incFileEntry[1][0]
    callback     = incFileEntry[1][1]
    dependencies = incFileEntry[1][2]

    incFilePathTup = incFilePath.rsplit('/', 1)

    if len(incFilePathTup) == 1:
        secName = ''
        incFile = incFilePathTup[0]
    else :
        secName = incFilePathTup[0]
        incFile = incFilePathTup[1]

    symName = incFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath('driver/zigbee/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_Device_Application','z3device')
    secDName = secTname.replace('stack_Interface','stack_Interface')
    secDName = secDName.replace('devicetypes','')
    #secDName = secTName


    incFileSym.setDestPath('/zigbee/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/zigbee/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importIncFileNonStackdriver(component, configName, incFileEntry, firmwarePath = None):
    incFilePath  = incFileEntry[0]
    isEnabled    = incFileEntry[1][0]
    callback     = incFileEntry[1][1]
    dependencies = incFileEntry[1][2]

    incFilePathTup = incFilePath.rsplit('/', 1)

    if len(incFilePathTup) == 1:
        secName = ''
        incFile = incFilePathTup[0]
    else :
        secName = incFilePathTup[0]
        incFile = incFilePathTup[1]

    symName = incFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath('driver/zigbee/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/common_files','zgp_common_files')

    incFileSym.setDestPath('/driver/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/driver/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importSrcFileNonStackdriver(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/common_files','zgp_common_files')

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/' + secDName+ '/src/')
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/' + secDName + '/src/')
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)


def importConsoleSrcFileNonStack(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_Device_Application','app_zigbee')
    secDName = secTname.replace('common/src','zigbee_console')

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('../../app_zigbee/' + secDName+ '/src/')
    srcFileSym.setProjectPath('' + secDName + '/src/')
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def importSrcFileNonStack(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_Device_Application','z3device')
    secDName = secTname.replace('stack_Interface','stack_Interface')
    secDName = secDName.replace('devicetypes','')
    #secDName = secTName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/' + secDName+ '/src/')
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/' + secDName + '/src/')
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)
        
def importSrcFileNonStackNew(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_Device_Application','z3device')
    secDName = secTname.replace('stack_Interface','stack_Interface')
    secDName = secDName.replace('devicetypes','')
    #secDName = secTName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/' + secDName + '/')
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def importSrcFile(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/src/Components/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/systemresource/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/systemresource/' + secDName)
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def setIncPath(component, configName, incPathEntry):
    incPath      = incPathEntry[0]
    isEnabled    = incPathEntry[1][0]
    callback     = incPathEntry[1][1]
    dependencies = incPathEntry[1][2]

    incPath = incPath.replace('/src','')
    incPath = incPath.replace('/application/zigbee_only','')
    incPath = incPath.replace('Zigbee_Device_Application','zigbee')
    incPath = incPath.replace('/Components','/zigbee/lib/inc')
    incPath = incPath.replace('drivers','driver')
    #incPath = incPath.replace('zigbeeutils','zigbeeutils')
    #incPath = incPath.replace('zgb_wrappers','zigbee/af_interface')
    #incPath = incPath.replace('common_files','zigbee')
    incPathSym = component.createSettingSymbol('ZIGBEE_INC_PATH' + incPath.replace('.', '_').replace('/', '_').upper(), None)
    incPathSym.setValue('../src/config/' + configName + incPath + ';')
    incPathSym.setCategory('C32')
    incPathSym.setKey('extra-include-directories')
    incPathSym.setAppend(True, ';')
    incPathSym.setEnabled(isEnabled)
    incPathSym.setDependencies(callback, dependencies)
#####################################################################################################
#####################################################################################################

#####################################################################################################
################################### ZIGBEE APP FILES ################################################
#####################################################################################################


#####################################################################################################
#####################################################################################################

def zigbeeDevTypeEventAutoConfigCheck(symbol, event):
    symbol.setValue((event["value"] == False))

def zigbeeDevTypeEventManualConfigCheck(symbol, event):
    if ((event["value"] == True)):
        symbol.setValue(False)
        symbol.setVisible(False)
        zigbeeDevsym_autoConfig.setValue(True)
    else:
        symbol.setValue(True)
        symbol.setVisible(True)
        zigbeeDevsym_autoConfig.setValue(False)

def manualConfigVisibility(symbol, event):
    if ((event["value"] == True)):
        symbol.setVisible(True)
    else:
        symbol.setVisible(True)

def commnConfigVisibility(symbol, event):
    if (commissioningConfigMenu.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def gpMenuCheck():
    if (greenPowerConfigZGPDeviceType.getValue() == "NONE"):
        return(False)
    else:
        return(True)

#def PdsEnableCheck(symbol, event):
#    if (pdsConfigEnablePDS.getValue() == False):
#        symbol.setVisible(False)
#    else:
#        symbol.setVisible(True)

def OtauEnableCheck(symbol, event):
    if (otauConfigEnable.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)


def OtauClientEnableCheck(symbol, event):
    if ((otauConfigEnable.getValue() == True) and (otauConfigRole.getValue() == "CLIENT")):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)
        
def stackDeviceTypeSetCheck():
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")):
        return(0) #Coordinator
    elif ((zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT") or (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT")
          or (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT") or (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT")
          or (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT") or (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
          or (zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
        return(1)#Router
    #elif ((zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
    #    return(0)#SelectOption
    else:
        return(2)#Enddevice

def NetworkFormationCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE")
             ):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT")
              or (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")        
             ):
            return(1)
        elif (zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM"):
            return(1)
        else:
            return(0)

def NetworkSteeringCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
             ):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
            return(1)
        else:
            return(0)

def TouchlinkCommnSetCheck():
        if (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER"):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
             ):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
            return(0)
        else:
            return(0)

def FindingBindingCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")             
             ):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
            return(1)
        else:
            return(0)

def OTAURoleCheck():
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE")):
        return('SERVER')
    else:
        return('CLIENT')

def OTAUExtMemCheck(symbol, event):
        if ((zigbeeDevsym_OTAU_MemInternalExternal.getValue() == "EXTERNAL")):
            symbol.setVisible(True)
            symbol.setLabel("***  WARNING!!! There is no external memory defined for this device ***")
        else:
            symbol.setVisible(False)

def stackMenuCheck():
    if (stackConfigDeviceType.getValue() == ""):
        return(False)
    else:
        return(True)

def zigbeeDevType2EventInputVisibility(symbol, event):
    if (zigbeeDeviceType.getValue() != "Combined Interface"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def pageReqenaCheck(symbol, event):
    if (zigbeeDevsym_IMAGE_PAGE_REQUEST_ENABLE.getValue() == "False"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def ciAsBridgeForstackDevTypeEvent(symbol, event):
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE") and event["value"] == True):
        symbol.setValue(1)#ROUTER
    else:
        symbol.setValue(0)#COORDINATOR

def ciAsBridgeForcommnConfigTouchlinkEvent(symbol, event):
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE") and event["value"] == True):
        symbol.setValue(True)
    else:
        symbol.setValue(False)

def stackDevTypeForcommnConfigNwkSteeringEvent(symbol, event):
    if (event["value"] == 0):#COORDINATOR
        symbol.setValue(False)
        symbol.setReadOnly(True)
    else:
        symbol.setValue(True)
        symbol.setReadOnly(False)

def stackDevTypeForcommnConfigNwkFormationEvent(symbol, event):
    if (event["value"] == 2):#ENDDEVICE
        symbol.setValue(False)
        symbol.setReadOnly(True)
    else:
        symbol.setValue(True)
        symbol.setReadOnly(False)

def stackDevTypeForcommnConfigNwkTouchlinkEvent(symbol, event):
    if (event["value"] == 0):#COORDINATOR
        symbol.setValue(False)
        symbol.setReadOnly(True)
    elif (event["value"] == 1):#ROUTER
        symbol.setValue(False)
    else:
        symbol.setValue(True)
        symbol.setReadOnly(False)

def stackDevTypeForGreenPowerMenuEvent(symbol, event):
    if (event["value"] == 2 or (zigbeeDevsym_manulConfig.getValue() == False)):#ENDDEVICE
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def setEnableLightDevice(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if (setDevice == "ZIGBEE_COLOR_LIGHT") or (setDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT") or (setDevice == "ZIGBEE_ON_OFF_LIGHT") or (zigbeeDeviceType.getValue() == 'ZIGBEE_EXTENDED_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'ZIGBEE_DIMMABLE_LIGHT'):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableColorSceneController(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableOtau(symbol, event):
    component = symbol.getComponent()

    otauEnable  =  component.getSymbolValue('OTAU_ENABLE')

    if ((otauEnable == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnablePageMode(symbol, event):
    component = symbol.getComponent()

    pageMode  =  component.getSymbolValue('Page_mode')

    if ((pageMode == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableOtauServer(symbol, event):
    component = symbol.getComponent()

    otauServerRole  =  component.getSymbolValue('OTAU_ROLE')

    if ((otauServerRole == "SERVER")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableOtauClient(symbol, event):
    component = symbol.getComponent()

    otauClientRole  =  component.getSymbolValue('OTAU_ROLE')

    if ((otauClientRole == "CLIENT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCombInterface(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_COMBINED_INTERFACE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableControlBridge(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_CONTROL_BRIDGE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableDimLight(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_DIMMABLE_LIGHT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableDimSwitch(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "DIMMER_SWITCH")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableExtColorLight(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableIasAce(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_IAS_ACE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableMultiSensor(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_MULTI_SENSOR")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCustomDevice(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if (setDevice == "ZIGBEE_CUSTOM"):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableGPDevice(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('GP_DEVICE_TYPE')

    if (setDevice != "NONE"):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableTempColorLight(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableThermostat(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "ZIGBEE_THERMOSTAT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCommnNetworkFormation(symbol, event):
    component = symbol.getComponent()

    CommnEnabled  =  component.getSymbolValue('NETWORK_FORMATION')

    if ((CommnEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCommnNetworkSteering(symbol, event):
    component = symbol.getComponent()

    CommnEnabled  =  component.getSymbolValue('NETWORK_STEERING')

    if ((CommnEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCommnTouchlink(symbol, event):
    component = symbol.getComponent()

    CommnEnabled  =  component.getSymbolValue('TOUCHLINK')

    if ((CommnEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCommnFindingBinding(symbol, event):
    component = symbol.getComponent()

    CommnEnabled  =  component.getSymbolValue('FINDING_AND_BINDING')

    if ((CommnEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnablePDSWearLevelling(symbol, event):
    component = symbol.getComponent()

    pdsWearLevllingEnabled  =  component.getSymbolValue('PDS_ENABLE_WEAR_LEVELING')

    if ((pdsWearLevllingEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnablePDSStandard(symbol, event):
    component = symbol.getComponent()

    pdsWearLevllingEnabled  =  component.getSymbolValue('PDS_ENABLE_WEAR_LEVELING')

    if ((pdsWearLevllingEnabled == False)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnablePDSUseInternalMem(symbol, event):
    component = symbol.getComponent()

    pdsWearLevllingEnabled  =  component.getSymbolValue('PDS_USEMEM_INTEXT')

    if ((pdsWearLevllingEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnablePDSUseExternalMem(symbol, event):
    component = symbol.getComponent()

    pdsWearLevllingEnabled  =  component.getSymbolValue('PDS_USEMEM_INTEXT')

    if ((pdsWearLevllingEnabled == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def isConsoleEnabled(symbol, event):
    component = symbol.getComponent()

    enableConsole  =  component.getSymbolValue('APP_ENABLE_CONSOLE')

    if ((enableConsole == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)


def onAttachmentConnected(source, target):

    localComponent = source["component"]
    remoteComponent = target["component"]
    remoteID = remoteComponent.getID()
    connectID = source["id"]
    print("drv_zigbee_lib:onAttachmentConnected ConnectID '{}'".format(connectID))
    targetID = target["id"]
    Log.writeInfoMessage('drv_zigbee_lib:onAttachmentConnected: source = {} remote = {}'.
            format(localComponent.getID(), targetID))

    if (connectID == "Zigbee_USART"):
        appConfigEnableConsole.setValue(True)
        bdbconsolecommandEnable.setValue(True)
        zclconsolecommandEnable.setValue(True)
        zdoconsolecommandEnable.setValue(True)
        commsnzdoconsolecommandEnable.setValue(True)
        appConfigZloExtraClusters.setValue(True)
        appConfigZloClustersEnhancements.setValue(True)
        appConfigCertificationExtension.setValue(True)
        Database.setSymbolValue("drv_usart", "DRV_USART_COMMON_MODE", "Asynchronous")
        Database.sendMessage("pic32cx_bz2_devsupport", "CONSOLE_ENABLE", {"isEnabled":True})
        print("setting ENABLE CONSOLE in application Configuration as True Since DRV_USART is connected")
    elif (connectID == "Zigbee_WolfCrypt_Dependency"):
        print("drv_zigbee_lib:onAttachmentConnected configuring lib_wolfcrypt")
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_hw", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_md5", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_sha1", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_sha256", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_hmac", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_tdes", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_hw", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_128", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_192", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_256", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_ecb", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_ecb_hw", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_cbc", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_cbc_hw", True)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_ctr", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_gcm", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_aes_ccm", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_ecc", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_rsa", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_oaep", False)
        Database.setSymbolValue("lib_wolfcrypt", "wolfcrypt_asn1", False)
    elif (connectID == "PIC32CX_BZ2_DevSupport_Dependency"):
        # if Zigbee device requires RTC for sleep, send message to Device_Support
        requiresRTCSupport = [
                "ZIGBEE_COLOR_SCENE_CONTROLLER",
                "ZIGBEE_IAS_ACE",
                "ZIGBEE_MULTI_SENSOR",
                ]
        zigbeeDeviceType = localComponent.getID()
        # Log.writeInfoMessage("drv_zigbee_lib:onAttachmentConnected:PIC32CX_BZ2_DevSupport: zigbeeDeviceType = {}".
        #         format(zigbeeDeviceType))
        if zigbeeDeviceType in requiresRTCSupport:
            Database.sendMessage(remoteID, "RTC_SUPPORT", {"target":remoteID,
                                                        "source": localComponent.getID(),
                                                        "rtcRequired": True})


def onAttachmentDisconnected(source, target):

    localComponent = source["component"]
    remoteComponent = target["component"]
    remoteID = remoteComponent.getID()
    connectID = source["id"]
    targetID = target["id"]

    if (connectID == "Zigbee_USART"):
        appConfigEnableConsole.setValue(False)
        bdbconsolecommandEnable.setValue(False)
        zclconsolecommandEnable.setValue(False)
        zdoconsolecommandEnable.setValue(False)
        commsnzdoconsolecommandEnable.setValue(False)
        appConfigZloExtraClusters.setValue(False)
        appConfigZloClustersEnhancements.setValue(False)
        appConfigCertificationExtension.setValue(False)
        Database.sendMessage("pic32cx_bz2_devsupport", "CONSOLE_ENABLE", {"isEnabled":False})
        print("setting ENABLE CONSOLE in application Configuration as False Since DRV_USART is disconnected")

# def onAttachmentConnected(source, target):

    # localComponent = source["component"]
    # remoteComponent = target["component"]
    # remoteID = remoteComponent.getID()
    # connectID = source["id"]
    # targetID = target["id"]

    # print(localComponent.getID())
    # print(connectID)
    # print(remoteComponent.getID())
    # print(remoteID)

    # if connectID == "StackLib_SuperSet":
        # if (( localComponent.getID() == "ZIGBEE_COLOR_SCENE_CONTROLLER" ) or ( localComponent.getID() == "ZIGBEE_MULTI_SENSOR" ) or ( localComponent.getID() == "ZIGBEE_IAS_ACE" )):
            # localComponent.setDependencyEnabled("StackLib_EndDevice", False)
        # elif (( localComponent.getID() == "ZIGBEE_THERMOSTAT" ) or ( localComponent.getID() == "ZIGBEE_ON_OFF_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_DIMMABLE_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_COLOR_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_EXTENDED_COLOR_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT" )):
            # localComponent.setDependencyEnabled("StackLib_Router", False)
        # elif ( localComponent.getID() == "ZIGBEE_COMBINED_INTERFACE" ):
            # localComponent.setDependencyEnabled("StackLib_Coordinator", False)
        # else:
            # print ("Custom Device")
    # else:
        # localComponent.setDependencyEnabled("StackLib_SuperSet", False)

# def onAttachmentDisconnected(source, target):

    # localComponent = source["component"]
    # remoteComponent = target["component"]
    # remoteID = remoteComponent.getID()
    # connectID = source["id"]
    # targetID = target["id"]

    # if connectID == "StackLib_SuperSet":
        # if (( localComponent.getID() == "ZIGBEE_COLOR_SCENE_CONTROLLER" ) or ( localComponent.getID() == "ZIGBEE_MULTI_SENSOR" ) or ( localComponent.getID() == "ZIGBEE_IAS_ACE" )):
            # localComponent.setDependencyEnabled("StackLib_EndDevice", True)
        # elif (( localComponent.getID() == "ZIGBEE_THERMOSTAT" ) or ( localComponent.getID() == "ZIGBEE_ON_OFF_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_DIMMABLE_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_COLOR_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_EXTENDED_COLOR_LIGHT" ) or ( localComponent.getID() == "ZIGBEE_TEMPERATURE_COLOR_LIGHT" )):
            # localComponent.setDependencyEnabled("StackLib_Router", True)
        # elif ( localComponent.getID() == "ZIGBEE_COMBINED_INTERFACE" ):
            # localComponent.setDependencyEnabled("StackLib_Coordinator", True)
        # else:
            # print ("Custom Device")
    # else:
        # localComponent.setDependencyEnabled("StackLib_SuperSet", True)


