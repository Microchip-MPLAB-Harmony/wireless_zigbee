##################################################################################################
######################### ZigbeeDriver Configurations ############################################
##################################################################################################


################################################################################
################################# Component ####################################
################################################################################

def instantiateComponent(drvZigbeeComponent):
    print('ZIGBEE Driver Component')
    configName = Variables.get("__CONFIGURATION_NAME")
    print configName

    # Interface Information
    execfile(Module.getPath() +"/driver/zigbee/config/interface.py")

    ############################################################################
    ### Activate dependent components
    ############################################################################
    res = Database.activateComponents(["tcc2"])

    # Device Type Selection Menu
    global zigbeeDeviceType
    zigbeeDeviceType = drvZigbeeComponent.createComboSymbol("ZB_DEVICE_TYPE", None, 
       ["",
        "COLOR_SCENE_CONTROLLER",
        "MULTI_SENSOR",
        "COMBINED_INTERFACE",
        # "CONTROL_BRIDGE",
        "THERMOSTAT",
        "IAS_ACE",
        "ON_OFF_LIGHT",
        "DIMMABLE_LIGHT", 
        "COLOR_LIGHT",
        "EXTENDED_COLOR_LIGHT", 
        "TEMPERATURE_COLOR_LIGHT",
        "CUSTOM"
       ])
    zigbeeDeviceType.setDefaultValue("")
    zigbeeDeviceType.setLabel("Select Device Type")
    zigbeeDeviceType.setVisible(False)
    zigbeeDeviceType.setValue(drvZigbeeComponent.getID())
    zigbeeDeviceType.setDefaultValue(drvZigbeeComponent.getID()) 

    # Auto Configuration Option
    global zigbeeDevsym_autoConfig
    zigbeeDevsym_autoConfig = drvZigbeeComponent.createBooleanSymbol("AUTOMATIC_CONFIGURATION", None)
    zigbeeDevsym_autoConfig.setLabel("Automatic(Default) Configuration")
    zigbeeDevsym_autoConfig.setVisible((drvZigbeeComponent.getID() != "CUSTOM"))
    zigbeeDevsym_autoConfig.setDefaultValue(True)
    zigbeeDevsym_autoConfig.setDescription("Automatic Configuration which provides the default recommended configuration")
    zigbeeDevsym_autoConfig.setDependencies(zigbeeDevTypeEventAutoConfigCheck, ["MANUAL_CONFIGURATION"])

    # Manual Configuration option
    global zigbeeDevsym_manulConfig
    zigbeeDevsym_manulConfig = drvZigbeeComponent.createBooleanSymbol("MANUAL_CONFIGURATION", None)
    zigbeeDevsym_manulConfig.setLabel("Manual Configuration")
    zigbeeDevsym_manulConfig.setVisible(True)
    zigbeeDevsym_manulConfig.setDefaultValue(False)
    zigbeeDevsym_manulConfig.setDescription("Manual Configuration which provides the options for customization")
    zigbeeDevsym_manulConfig.setDependencies(zigbeeDevTypeEventManualConfigCheck, ["AUTOMATIC_CONFIGURATION"])


    # Stack Configuration Menu
    stackConfigMenu = drvZigbeeComponent.createMenuSymbol("STACKCONFIG_MENU", zigbeeDevsym_manulConfig)
    stackConfigMenu.setLabel("Stack Configuration")
    stackConfigMenu.setVisible(False)
    stackConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Commissioning Configuration Menu
    commissioningConfigMenu = drvZigbeeComponent.createMenuSymbol("COMMCONFIG_MENU", zigbeeDevsym_manulConfig)
    commissioningConfigMenu.setLabel("Commissioning Configuration")
    commissioningConfigMenu.setVisible(False)
    commissioningConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Application Configuration Menu
    applicationConfigMenu = drvZigbeeComponent.createMenuSymbol("APPCONFIG_MENU", zigbeeDevsym_manulConfig)
    applicationConfigMenu.setLabel("Application Configuration")
    applicationConfigMenu.setVisible(False)
    applicationConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Persistent Data Configuration Menu
    PersistentDataConfigMenu = drvZigbeeComponent.createMenuSymbol("PERSISCONFIG_MENU", zigbeeDevsym_manulConfig)
    PersistentDataConfigMenu.setLabel("Persistent Data Configuration")
    PersistentDataConfigMenu.setVisible(False)
    PersistentDataConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # OTAU Configuration Menu
    OtauConfigMenu = drvZigbeeComponent.createMenuSymbol("OTAUCONFIG_MENU", zigbeeDevsym_manulConfig)
    OtauConfigMenu.setLabel("Over the Air Upgrade Configuration")
    OtauConfigMenu.setVisible(False)
    OtauConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Green Power Configuration Menu
    GreenPowerConfigMenu = drvZigbeeComponent.createMenuSymbol("GREENPOWERCONFIG_MENU", zigbeeDevsym_manulConfig)
    GreenPowerConfigMenu.setLabel("Green Power Configuration")
    GreenPowerConfigMenu.setVisible(False)
    GreenPowerConfigMenu.setDependencies(manualConfigVisibility, ["AUTOMATIC_CONFIGURATION", "MANUAL_CONFIGURATION"])

    # Cluster Configuration Menu
    clusterConfigMenu = drvZigbeeComponent.createMenuSymbol("CLUSTERCONFIG_MENU", zigbeeDevsym_manulConfig)
    clusterConfigMenu.setLabel("Cluster Configuration")
    clusterConfigMenu.setVisible(False)
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
    execfile(Module.getPath() +"/driver/zigbee/config/pdsconfig.py")

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
    # Application Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/appconfig.py")

#####################################################################################################
#################               Commissioning CONFIGURATION                           ###############
#####################################################################################################
    # Application Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/commissionconfig.py")


    checkDevTypeLight              =  (zigbeeDeviceType.getValue() == 'COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'ON_OFF_LIGHT') or (zigbeeDeviceType.getValue() == 'TEMPERATURE_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'EXTENDED_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'DIMMABLE_LIGHT')
    checkDevTypeRemote             =  (zigbeeDeviceType.getValue() == 'COLOR_SCENE_CONTROLLER')
    checkDevTypeDimSwitch          =  (zigbeeDeviceType.getValue() == 'DIMMER_SWITCH')
    checkDevTypeCombInterface      =  (zigbeeDeviceType.getValue() == 'COMBINED_INTERFACE')
    checkDevTypeControlBridge      =  (zigbeeDeviceType.getValue() == 'CONTROL_BRIDGE')
    checkDevTypeIasAce             =  (zigbeeDeviceType.getValue() == 'IAS_ACE')
    checkDevTypeMultiSensor        =  (zigbeeDeviceType.getValue() == 'MULTI_SENSOR')
    checkDevTypeThermostat         =  (zigbeeDeviceType.getValue() == 'THERMOSTAT')
    checkCommTypeNetworkFormation  =  (commnConfigNWKFormation.getValue()       == True)
    checkCommTypeNetworkSteering   =  (commnConfigNWKSteering.getValue()        == True)
    checkCommTypeTouchlink         =  (commnConfigTouchlink.getValue()          == True)
    checkCommTypeFindingBinding    =  (commnConfigFindingAndbinding.getValue() == True)
    checkPDSEnableWearLevelling    =  ((pdsConfigEnablePDS.getValue() == True) and (pdsConfigEnableWearLevelling.getValue() == True))
    checkPDSEnableStandard         =  ((pdsConfigEnablePDS.getValue() == True) and (pdsConfigEnableWearLevelling.getValue() == False))
    checkPDSUseExternalMem         =  (pdsConfigMemInternalExternal.getValue() == 'EXTERNAL')
    checkPDSUseInternalMem         =  (pdsConfigMemInternalExternal.getValue() == 'INTERNAL')

    condAlways                          = [True,                          None,                                        []]

    condDevLight                        = [checkDevTypeLight,             setEnableLightDevice,                        ['ZB_DEVICE_TYPE']]
    condDevColorSceneController         = [checkDevTypeRemote,            setEnableColorSceneController,               ['ZB_DEVICE_TYPE']]
    condDevDimmerSwitch                 = [checkDevTypeDimSwitch,         setEnableDimSwitch,                          ['ZB_DEVICE_TYPE']]
    condDevCombInterface                = [checkDevTypeCombInterface,     setEnableCombInterface,                      ['ZB_DEVICE_TYPE']]
    condDevControlBridge                = [checkDevTypeControlBridge,     setEnableControlBridge,                      ['ZB_DEVICE_TYPE']]
    condDevIasAce                       = [checkDevTypeIasAce,            setEnableIasAce,                             ['ZB_DEVICE_TYPE']]
    condDevMultiSensor                  = [checkDevTypeMultiSensor,       setEnableMultiSensor,                        ['ZB_DEVICE_TYPE']]
    condDevThermostat                   = [checkDevTypeThermostat ,       setEnableThermostat ,                        ['ZB_DEVICE_TYPE']]

    condCommnNetworkFormation           = [checkCommTypeNetworkFormation ,  setEnableCommnNetworkFormation ,          ['NETWORK_FORMATION']]
    condCommnNetworkSteering            = [checkCommTypeNetworkSteering ,   setEnableCommnNetworkSteering ,           ['NETWORK_STEERING']]
    condCommnTouchlink                  = [checkCommTypeTouchlink ,         setEnableCommnTouchlink ,                 ['TOUCHLINK']]
    condCommnFindingBinding             = [checkCommTypeFindingBinding ,    setEnableCommnFindingBinding ,            ['FINDING_AND_BINDING']]

    condPDSStandard                     = [checkPDSEnableStandard ,         setEnablePDSStandard ,                    ['PDS_ENABLE_WEAR_LEVELING']]
    condPDSWearLevelling                = [checkPDSEnableWearLevelling ,    setEnablePDSWearLevelling  ,              ['PDS_ENABLE_WEAR_LEVELING']]
    condPDSUseInternalMem               = [checkPDSUseInternalMem ,         setEnablePDSUseInternalMem ,              ['PDS_USEMEM_INTEXT']]
    condPDSUseExternalMem               = [checkPDSUseExternalMem ,         setEnablePDSUseExternalMem ,              ['PDS_USEMEM_INTEXT']]

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
    zigbeeDevSelectConf.setDestPath("/application/configs")
    zigbeeDevSelectConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeDevSelectConf.setType("HEADER")
    zigbeeDevSelectConf.setOverwrite(True)
    zigbeeDevSelectConf.setMarkup(True)

    # Makerule
    zigbeeDevSelectConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_MAKERULE_HEADER", None)
    zigbeeDevSelectConf.setSourcePath("/driver/zigbee/templates/Zigbee_AllDevice_Makerules.h.ftl")
    zigbeeDevSelectConf.setOutputName("Zigbee_AllDevice_Makerules.h")
    zigbeeDevSelectConf.setDestPath("/application/configs")
    zigbeeDevSelectConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeDevSelectConf.setType("HEADER")
    zigbeeDevSelectConf.setOverwrite(True)
    zigbeeDevSelectConf.setMarkup(True)

    zigbeeAppConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_APPCONF_HEADER", None)
    zigbeeAppConf.setSourcePath("/driver/zigbee/templates/zigbeeAppConfig.h.ftl")
    zigbeeAppConf.setOutputName("zigbeeAppConfig.h")
    zigbeeAppConf.setDestPath("/application/configs")
    zigbeeAppConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeAppConf.setType("HEADER")
    zigbeeAppConf.setOverwrite(True)
    zigbeeAppConf.setMarkup(True)

    zigbeeBitCloudPreConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_BITPRE_HEADER", None)
    zigbeeBitCloudPreConf.setSourcePath("/driver/zigbee/templates/bitcloudPreInclude.h.ftl")
    zigbeeBitCloudPreConf.setOutputName("bitcloudPreInclude.h")
    zigbeeBitCloudPreConf.setDestPath("/application/configs")
    zigbeeBitCloudPreConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeBitCloudPreConf.setType("HEADER")
    zigbeeBitCloudPreConf.setOverwrite(True)
    zigbeeBitCloudPreConf.setMarkup(True)

    zigbeeStackConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__STACKCONF_HEADER", None)
    zigbeeStackConf.setSourcePath("/driver/zigbee/templates/stackConfig.h.ftl")
    zigbeeStackConf.setOutputName("stackConfig.h")
    zigbeeStackConf.setDestPath("/application/configs")
    zigbeeStackConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeStackConf.setType("HEADER")
    zigbeeStackConf.setOverwrite(True)
    zigbeeStackConf.setMarkup(True)

    zigbeeOtauConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__OTAUCONF_HEADER", None)
    zigbeeOtauConf.setSourcePath("/driver/zigbee/templates/otauConfig.h.ftl")
    zigbeeOtauConf.setOutputName("otauConfig.h")
    zigbeeOtauConf.setDestPath("/application/configs")
    zigbeeOtauConf.setProjectPath("config/" + configName + "/application/configs")
    zigbeeOtauConf.setType("HEADER")
    zigbeeOtauConf.setOverwrite(True)
    zigbeeOtauConf.setMarkup(True)

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
    app_zgbSourceFile.setDestPath('../../')
    app_zgbSourceFile.setProjectPath('')
    app_zgbSourceFile.setType('SOURCE')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    # Add app_zigbee.h - static file
    app_zgbHeaderFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbHeaderFile.setSourcePath('driver/zigbee/templates/zigbee_app_header.h.ftl')
    app_zgbHeaderFile.setOutputName('app_zigbee.h')
    app_zgbHeaderFile.setOverwrite(True)
    app_zgbHeaderFile.setDestPath('../../')
    app_zgbHeaderFile.setProjectPath('')
    app_zgbHeaderFile.setType('HEADER')
    app_zgbHeaderFile.setEnabled(True)

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
        ['aps/include/private/apsAuthenticate.h',    condAlways],
        ['aps/include/private/apsBinding.h',         condAlways],
        ['aps/include/private/apsCommand.h',         condAlways],
        ['aps/include/private/apsConfig.h',          condAlways],
        ['aps/include/private/apsConfirmKey.h',      condAlways],
        ['aps/include/private/apsDataManager.h',     condAlways],
        ['aps/include/private/apsDbg.h',             condAlways],
        ['aps/include/private/apsEndpoint.h',        condAlways],
        ['aps/include/private/apsFrames.h',          condAlways],
        ['aps/include/private/apsGroup.h',           condAlways],
        ['aps/include/private/apsKeyPairSet.h',      condAlways],
        ['aps/include/private/apsMemoryManager.h',   condAlways],
        ['aps/include/private/apsRejectDuplicate.h', condAlways],
        ['aps/include/private/apsRemoveDevice.h',    condAlways],
        ['aps/include/private/apsRequestKey.h',      condAlways],
        ['aps/include/private/apsSkke.h',            condAlways],
        ['aps/include/private/apsSkkeInitiator.h',   condAlways],
        ['aps/include/private/apsSkkeResponder.h',   condAlways],
        ['aps/include/private/apsSmSsp.h',           condAlways],
        ['aps/include/private/apsState.h',           condAlways],
        ['aps/include/private/apsSwitchKey.h',       condAlways],
        ['aps/include/private/apsTaskManager.h',     condAlways],
        ['aps/include/private/apsTransportAppKey.h', condAlways],
        ['aps/include/private/apsTransportKey.h',    condAlways],
        ['aps/include/private/apsTransportNwkKey.h',    condAlways],
        ['aps/include/private/apsTransportTrustKey.h',  condAlways],
        ['aps/include/private/apsUpdateDevice.h',       condAlways],
        ['aps/include/private/apsVerifyKey.h',          condAlways],
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
        ['nwk/include/private/nwkAddress.h',                  condAlways],
        ['nwk/include/private/nwkAddressConflict.h',          condAlways],
        ['nwk/include/private/nwkAddressMap.h',               condAlways],
        ['nwk/include/private/nwkBTT.h',                      condAlways],
        ['nwk/include/private/nwkCommands.h',                 condAlways],
        ['nwk/include/private/nwkConcentrator.h',             condAlways],
        ['nwk/include/private/nwkConfig.h',                   condAlways],
        ['nwk/include/private/nwkDataReq.h',                  condAlways],
        ['nwk/include/private/nwkDbg.h',                      condAlways],
        ['nwk/include/private/nwkDirectJoin.h',               condAlways],
        ['nwk/include/private/nwkDiscovery.h',                condAlways],
        ['nwk/include/private/nwkEDScan.h',                   condAlways],
        ['nwk/include/private/nwkEndDeviceTimeoutInd.h',      condAlways],
        ['nwk/include/private/nwkEndDeviceTimeoutReq.h',      condAlways],
        ['nwk/include/private/nwkFormation.h',                condAlways],
        ['nwk/include/private/nwkFrame.h',                    condAlways],
        ['nwk/include/private/nwkIB.h',                       condAlways],
        ['nwk/include/private/nwkInCounterSet.h',             condAlways],
        ['nwk/include/private/nwkJoinInd.h',                  condAlways],
        ['nwk/include/private/nwkJoinReq.h',                  condAlways],
        ['nwk/include/private/nwkKeys.h',                     condAlways],
        ['nwk/include/private/nwkLeave.h',                    condAlways],
        ['nwk/include/private/nwkLinkStatus.h',               condAlways],
        ['nwk/include/private/nwkLoopback.h',                 condAlways],
        ['nwk/include/private/nwkManager.h',                  condAlways],
        ['nwk/include/private/nwkManyToOne.h',                condAlways],
        ['nwk/include/private/nwkMem.h',                      condAlways],
        ['nwk/include/private/nwkNeighborTable.h',            condAlways],
        ['nwk/include/private/nwkOrphan.h',                   condAlways],
        ['nwk/include/private/nwkPacket.h',                   condAlways],
        ['nwk/include/private/nwkPassiveAck.h',               condAlways],
        ['nwk/include/private/nwkPermitJoining.h',            condAlways],
        ['nwk/include/private/nwkReportCommand.h',            condAlways],
        ['nwk/include/private/nwkReset.h',                    condAlways],
        ['nwk/include/private/nwkRouteCache.h',               condAlways],
        ['nwk/include/private/nwkRouteDiscovery.h',           condAlways],
        ['nwk/include/private/nwkRouteDiscoveryTable.h',      condAlways],
        ['nwk/include/private/nwkRouteRecord.h',              condAlways],
        ['nwk/include/private/nwkRouteReply.h',               condAlways],
        ['nwk/include/private/nwkRouteRequest.h',             condAlways],
        ['nwk/include/private/nwkRouting.h',                  condAlways],
        ['nwk/include/private/nwkRoutingTable.h',             condAlways],
        ['nwk/include/private/nwkRx.h',                       condAlways],
        ['nwk/include/private/nwkRxSecurity.h',               condAlways],
        ['nwk/include/private/nwkSilentJoin.h',               condAlways],
        ['nwk/include/private/nwkSourceRouting.h',            condAlways],
        ['nwk/include/private/nwkStartRouter.h',              condAlways],
        ['nwk/include/private/nwkStateMachine.h',             condAlways],
        ['nwk/include/private/nwkStatusInd.h',                condAlways],
        ['nwk/include/private/nwkStatusReq.h',                condAlways],
        ['nwk/include/private/nwkSync.h',                     condAlways],
        ['nwk/include/private/nwkSyncLoss.h',                 condAlways],
        ['nwk/include/private/nwkSystem.h',                   condAlways],
        ['nwk/include/private/nwkTaskManager.h',              condAlways],
        ['nwk/include/private/nwkTx.h',                       condAlways],
        ['nwk/include/private/nwkTxDelay.h',                  condAlways],
        ['nwk/include/private/nwkTxSecurity.h',               condAlways],
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
        ['mac_phy/include/macDbg.h',               condAlways],
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
        ['mac_phy/include/rfInit.h',               condAlways],
        ['mac_phy/include/rfRandom.h',             condAlways],
        ['mac_phy/include/rfRegAccess.h',          condAlways],
        ['mac_phy/mac_env/include/macenvMem.h',    condAlways],
        ['mac_phy/mac_env/include/macenvPib.h',    condAlways],
        ['mac_phy/mac_hwd_phy/include/machwd.h',   condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdBatMon.h',                             condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdCalibration.h',                        condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdData.h',                               condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdEd.h',                                 condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdEncrypt.h',                            condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdRegAccess.h',                          condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdReset.h',                              condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdRnd.h',                                condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdService.h',                            condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdSet.h',                                condAlways],
        ['mac_phy/mac_hwd_phy/include/machwdSetTrx.h',                             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdBatMonHandler.h',  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdCalibHandler.h',   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdEdHandler.h',      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdEncryptHandler.h', condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdFrameRoutine.h',   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdHandlerCtrl.h',    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdManager.h',        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdMem.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdMemAccess.h',      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRegAccessHandler.h', condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdResetHandler.h',     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRndHandler.h',       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRxBuffer.h',         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRxFrameHandler.h',   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdSetHandler.h',       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTrxCtrl.h',          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTrxHandler.h',       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTxFrameHandler.h',   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/at86rf233.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyAntDiversity.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyBatMon.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyCalib.h',                   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyPic32cx.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyCommon.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDataStatus.h',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDeepSleep.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyEd.h',                      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyEncrypt.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyInit.h',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMem.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMemAccess.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRegAccess.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyReset.h',                   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRnd.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRtimerIrqDispatcher.h',     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRxFrame.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRxTxIndicator.h',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySet.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyStateMachine.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyTxFrame.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyTxPowerConverter.h',        condAlways],
        ['mac_phy/mac_hwi/include/machwiAssociateHandler.h',                         condAlways],
        ['mac_phy/mac_hwi/include/machwiBeaconHandler.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiDataHandler.h',                              condAlways],
        ['mac_phy/mac_hwi/include/machwiDisassociateHandler.h',                      condAlways],
        ['mac_phy/mac_hwi/include/machwiHwdReqMemPool.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiManager.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiMem.h',                                      condAlways],
        ['mac_phy/mac_hwi/include/machwiMemAccess.h',                                condAlways],
        ['mac_phy/mac_hwi/include/machwiOrphanHandler.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiPanIdConflictHandler.h',                     condAlways],
        ['mac_phy/mac_hwi/include/machwiPanServer.h',                                condAlways],
        ['mac_phy/mac_hwi/include/machwiPollHandler.h',                              condAlways],
        ['mac_phy/mac_hwi/include/machwiPurgeHandler.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiResetHandler.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiRxEnableHandler.h',                          condAlways],
        ['mac_phy/mac_hwi/include/machwiScanHandler.h',                              condAlways],
        ['mac_phy/mac_hwi/include/machwiSetGetHandler.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiStartHandler.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiSwitchRxCtrl.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionHandler.h',                       condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionHash.h',                          condAlways],
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
        ['security/serviceprovider/include/sspDbg.h',                       condAlways],
        ['security/serviceprovider/include/sspHash.h',                      condAlways],
        ['security/serviceprovider/include/sspReset.h',                     condAlways],
        ['security/serviceprovider/include/sspSfp.h',                       condAlways],
        ['security/serviceprovider/include/sspSkke.h',                      condAlways],
        ['security/TrustCentre/include/tc.h',                               condAlways],
        ['security/TrustCentre/include/tcAuthentic.h',                      condAlways],
        ['security/TrustCentre/include/tcCommon.h',                         condAlways],
        ['security/TrustCentre/include/tcDbg.h',                            condAlways],
        ['security/TrustCentre/include/tcDeviceTableCtrl.h',                condAlways],
        ['security/TrustCentre/include/tcKeyEstablish.h',                   condAlways],
        ['security/TrustCentre/include/tcKeyUpdate.h',                      condAlways],
        ['security/TrustCentre/include/tcPermissions.h',                    condAlways],
        ['security/TrustCentre/include/tcPromiscuousMode.h',                condAlways],
        ['security/TrustCentre/include/tcRemove.h',                         condAlways],
        ['security/TrustCentre/include/tcReset.h',                          condAlways],
        ['security/serviceprovider/include/private/sspAuthenticHandler.h',      condAlways],
        ['security/serviceprovider/include/private/sspCcmHandler.h',            condAlways],
        ['security/serviceprovider/include/private/sspChallengeGenHandler.h',   condAlways],
        ['security/serviceprovider/include/private/sspHashHandler.h',           condAlways],
        ['security/serviceprovider/include/private/sspManager.h',               condAlways],
        ['security/serviceprovider/include/private/sspMem.h',                   condAlways],
        ['security/serviceprovider/include/private/sspSfpHandler.h',            condAlways],
        ['security/serviceprovider/include/private/sspSkkeHandler.h',           condAlways],
        ['security/TrustCentre/include/private/tcAuthenticHandler.h',           condAlways],
        ['security/TrustCentre/include/private/tcDeviceTableCtrlHandler.h',     condAlways],
        ['security/TrustCentre/include/private/tcKeyEstablishHandler.h',        condAlways],
        ['security/TrustCentre/include/private/tcKeyUpdateHandler.h',           condAlways],
        ['security/TrustCentre/include/private/tcMem.h',                        condAlways],
        ['security/TrustCentre/include/private/tcRemoveHandler.h',              condAlways],
        ['security/TrustCentre/include/private/tcTaskManager.h',                condAlways],
        ['security/SoftAes/sspAesHandler.h',                                    condAlways],
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
        ['zdo/include/private/zdoBinding.h',           condAlways],
        ['zdo/include/private/zdoCommands.h',          condAlways],
        ['zdo/include/private/zdoConfig.h',            condAlways],
        ['zdo/include/private/zdoDbg.h',               condAlways],
        ['zdo/include/private/zdoEndDeviceBinding.h',  condAlways],
        ['zdo/include/private/zdoInit.h',              condAlways],
        ['zdo/include/private/zdoLeaveNetwork.h',      condAlways],
        ['zdo/include/private/zdoMem.h',               condAlways],
        ['zdo/include/private/zdoMgmtNwkUpdate.h',     condAlways],
        ['zdo/include/private/zdoNodeManager.h',       condAlways],
        ['zdo/include/private/zdoNwkManager.h',        condAlways],
        ['zdo/include/private/zdoParentAnnounce.h',    condAlways],
        ['zdo/include/private/zdoPermissionsTable.h',  condAlways],
        ['zdo/include/private/zdoPowerManager.h',      condAlways],
        ['zdo/include/private/zdoServiceDiscovery.h',  condAlways],
        ['zdo/include/private/zdoStartNetwork.h',      condAlways],
        ['zdo/include/private/zdoStateMachine.h',      condAlways],
        ['zdo/include/private/zdoTaskManager.h',       condAlways],
        ['zdo/include/private/zdoZdpReq.h',            condAlways],
        ['zdo/include/private/zdoZib.h',               condAlways],
    ]

    zdrvStackHALIncFiles = [
        ['hal/include/atomic.h',                                 condAlways],
        ['hal/include/bcTimer.h',                                condAlways],
        ['hal/include/appTimer.h',                               condAlways],
        ['hal/include/eeprom.h',                                 condAlways],
        ['hal/include/flash.h',                                  condAlways],
        ['hal/include/halTaskManager.h',                         condAlways],
        ['hal/include/sleep.h',                                  condAlways],
        ['hal/include/sleepTimer.h',                             condAlways],
        ['hal/include/statStack.h',                              condAlways],
        #['hal/cortexm4/pic32cx/include/hal_aes_sync.h',          condAlways],
        ['hal/cortexm4/pic32cx/include/halAppClock.h',           condAlways],
        ['hal/cortexm4/pic32cx/include/halAssert.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halDbg.h',                condAlways],
        ['hal/cortexm4/pic32cx/include/halDiagnostic.h',         condAlways],
        ['hal/cortexm4/pic32cx/include/halFlash.h',              condAlways],
        ['hal/cortexm4/pic32cx/include/halMacIsr.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halRfCtrl.h',             condAlways],
        ['hal/cortexm4/pic32cx/include/halSleep.h',              condAlways],
        ['hal/cortexm4/pic32cx/include/halSleepTimerClock.h',    condAlways],
        #['hal/cortexm4/pic32cx/include/hpl_aes.h',               condAlways],
        #['hal/cortexm4/pic32cx/include/hpl_aes_sync.h',          condAlways],
        #['hal/cortexm4/pic32cx/include/hri_aes_e54.h',           condAlways],
        ['hal/cortexm4/pic32cx/include/halAes.h',                condAlways],
        ['hal/cortexm4/pic32cx/include/Pic32cx_Miscellaneous.h', condAlways],
    ]

    zdrvStackZCLIncFiles = [
        ['zcl/clusters/include/groupsCluster.h',         condAlways],
        ['zcl/clusters/include/identifyCluster.h',       condAlways],
        ['zcl/clusters/include/scenes.h',                condAlways],
        ['zcl/include/zcl.h',                            condAlways],
        ['zcl/include/clusters.h',                       condAlways],
        ['zcl/include/eccAux.h',                         condAlways],
        ['zcl/include/genericEcc.h',                     condAlways],
        ['zcl/include/zclAlarmsCluster.h',               condAlways],
        ['zcl/include/zclAttributes.h',                  condAlways],
        ['zcl/include/zclBACnetProtocolTunnelCluster.h', condAlways],
        ['zcl/include/zclBasicCluster.h',                condAlways],
        ['zcl/include/zclCommandManager.h',              condAlways],
        ['zcl/include/zclCommandAnalyzer.h',             condAlways],
        ['zcl/include/zclDemandResponseCluster.h',       condAlways],
        ['zcl/include/zclDiagnosticsCluster.h',          condAlways],
        ['zcl/include/zclFanControlCluster.h',           condAlways],
        ['zcl/include/zclGenericTunnelCluster.h',        condAlways],
        ['zcl/include/zclGreenPowerCluster.h',           condAlways],
        ['zcl/include/zclGroupsCluster.h',               condAlways],
        ['zcl/include/zclHumidityMeasurementCluster.h',  condAlways],
        ['zcl/include/zclIasACECluster.h',               condAlways],
        ['zcl/include/zclIasZoneCluster.h',              condAlways],
        ['zcl/include/zclIdentifyCluster.h',             condAlways],
        ['zcl/include/zclIlluminanceMeasurementCluster.h',  condAlways],
        ['zcl/include/zclInt.h',                            condAlways],
        ['zcl/include/zclKeyEstablishmentCluster.h',        condAlways],
        ['zcl/include/zclLevelControlCluster.h',            condAlways],
        ['zcl/include/zclLinkInfoCluster.h',                condAlways],
        ['zcl/include/zclMem.h',                            condAlways],
        ['zcl/include/zclMemoryManager.h',                  condAlways],
        ['zcl/include/zclMessagingCluster.h',               condAlways],
        ['zcl/include/zcloccupancysensingcluster.h',        condAlways],
        ['zcl/include/zclOnOffCluster.h',                   condAlways],
        ['zcl/include/zclOnOffSwitchConfigurationCluster.h',   condAlways],
        ['zcl/include/zclOtauClient.h',                        condAlways],
        ['zcl/include/zclOTAUCluster.h',                       condAlways],
        ['zcl/include/zclOtauManager.h',                       condAlways],
        ['zcl/include/zclParser.h',                            condAlways],
        ['zcl/include/zclPowerConfigurationCluster.h',         condAlways],
        ['zcl/include/zclPriceCluster.h',                      condAlways],
        ['zcl/include/zclScenesCluster.h',                     condAlways],
        ['zcl/include/zclSecurityManager.h',                   condAlways],
        ['zcl/include/zclSimpleMeteringCluster.h',             condAlways],
        ['zcl/include/zclSimpleMeteringClusterMacroSet.h',     condAlways],
        ['zcl/include/zclSmartEnergyTunnelCluster.h',          condAlways],
        ['zcl/include/zclTaskManager.h',                       condAlways],
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
        ['zcl/include/private/zclDbg.h',                       condAlways],
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
        ['zllplatform/ZLL/N_SourceRouting/include/N_SourceRouting.h',                      condAlways],
        ['zllplatform/ZLL/N_SourceRouting/include/N_SourceRouting_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_TrustCenter/include/N_TrustCenter.h',                          condAlways],
        ['zllplatform/ZLL/N_TrustCenter/include/N_TrustCenter_Bindings.h',                 condAlways],
        ['zllplatform/ZLL/N_TrustCenter/include/N_TrustCenter_Init.h',                     condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_Framework.h',                      condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_DataRequest.h',                    condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_DataInd.h',                        condAlways],
        ['zllplatform/ZLL/N_Zcl_Framework/include/N_Zcl_Framework_Bindings.h',             condAlways],
        ['zllplatform/ZLL/N_Zdp/include/N_Zdp.h',                                          condAlways],
        ['zllplatform/ZLL/N_Zdp/include/N_Zdp_Bindings.h',                                 condAlways],
        ['zllplatform/ZLL/N_Zdp/include/N_Zdp_Init.h',                                     condAlways],
        ['zllplatform/ZLL/S_Nv/include/S_Nv.h',                                            condAlways],
        ['zllplatform/ZLL/S_Nv/include/S_Nv_Bindings.h',                                   condAlways],
        ['zllplatform/ZLL/S_Nv/include/S_Nv_Init.h',                                       condAlways],
        ['zllplatform/ZLL/S_Nv/include/S_Nv_Stack_Ids.h',                                  condAlways],
        ['zllplatform/ZLL/S_Nv/include/S_NvInternal.h',                                    condAlways],
        ['zllplatform/ZLL/D_Nv/include/D_Nv.h',                                            condAlways],
        ['zllplatform/ZLL/D_Nv/include/D_Nv_Bindings.h',                                   condAlways],
        ['zllplatform/ZLL/D_Nv/include/D_Nv_Init.h',                                       condAlways],
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
        ['PersistDataServer/include/pdsDataServer.h',                       condAlways],
        ['PersistDataServer/include/pdsMemIds.h',                           condAlways],
        ['PersistDataServer/wl/include/wlPdsBindings.h',                    condAlways],
        ['PersistDataServer/wl/include/wlPdsMemIds.h',                      condAlways],
        ['PersistDataServer/wl/include/wlPdsSecurity.h',                    condAlways],
        ['PersistDataServer/wl/include/wlPdsTaskManager.h',                 condAlways],
        ['PersistDataServer/wl/include/wlPdsTypes.h',                       condAlways],
        ['PersistDataServer/wl/include/wlPdsTypesConverter.h',              condAlways],
        ['PersistDataServer/std/include/stdPdsCrcService.h',                condAlways],
        ['PersistDataServer/std/include/stdPdsDbg.h',                       condAlways],
        ['PersistDataServer/std/include/stdPdsFiles.h',                     condAlways],
        ['PersistDataServer/std/include/stdPdsMem.h',                       condAlways],
        ['PersistDataServer/std/include/stdPdsMemAbstract.h',               condAlways],
        ['PersistDataServer/std/include/stdPdsMemAccess.h',                 condAlways],
        ['PersistDataServer/std/include/stdPdsMemIds.h',                    condAlways],
        ['PersistDataServer/std/include/stdPdsTimer.h',                     condAlways],
        ['PersistDataServer/std/include/stdPdsWriteData.h',                 condAlways],
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

    #freeRTOSIncFiles = [
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/deprecated_definitions.h',              condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/FreeRTOS.h',                            condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/list.h',                                condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/mpu_wrappers.h',                        condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/portable.h',                            condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/projdefs.h',                            condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/queue.h',                               condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/semphr.h',                              condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/stack_macros.h',                        condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/task.h',                                condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/timers.h',                              condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/GCC/ARM_CM4F/portmacro.h',             condAlways],
    #]

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
        ['application/zigbee_only/Zigbee_Device_Application/api/include/bdb_api.h',                     condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/include/cs_api.h',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/include/nwk_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/include/zcl_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/include/zdo_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/include/zgb_api.h',                             condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/appConsts.h',                       condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/colorSceneRemoteBindings.h',        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/commandManager.h',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/include/consoleCmds.h',                     condAlways],
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
        ['drivers/sercom/usart/drv_usart.h',          condAlways],
        # ['drivers/sercom/usart/usart.h',              condAlways],
        #['drivers/calibration/calibration.h',         condAlways],
        #['drivers/calibration/info_block.h',          condAlways],
        #['drivers/clock/clock.h',                     condAlways],
        #['drivers/rf/rf.h',                           condAlways],
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
        ['application/zigbee_only/common_files/include/printLcd.h',                                            condAlways],
        ['application/zigbee_only/common_files/include/errH.h',                                                condAlways],
        ['application/zigbee_only/common_files/include/console.h',                                             condAlways],
    ]

    zgbWrappersIncFiles = [
        ['src/zgb_wrappers/bdb/BDB_Unpack.h',                      condAlways],
        ['src/zgb_wrappers/configserver/CS_Unpack.h',              condAlways],
        ['src/zgb_wrappers/nwk/NWK_Unpack.h',                      condAlways],
        ['src/zgb_wrappers/zcl/ZCL_Unpack.h',                      condAlways],
        ['src/zgb_wrappers/zdo/ZDO_Unpack.h',                      condAlways],
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

    for incFileEntry in utilsIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in driversIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)

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
        ['aps/src/apsAIB.c',                  condAlways],
        ['aps/src/apsAuthenticate.c',         condAlways],
        ['aps/src/apsCommand.c',              condAlways],
        ['aps/src/apsBinding.c',              condAlways],
        ['aps/src/apsBindingTable.c',         condAlways],
        ['aps/src/apsConfirmKey.c',           condAlways],
        ['aps/src/apsDataManager.c',          condAlways],
        ['aps/src/apsEndpoint.c',             condAlways],
        ['aps/src/apsGroup.c',                condAlways],
        ['aps/src/apsGroupTable.c',           condAlways],
        ['aps/src/apsInterpan.c',             condAlways],
        ['aps/src/apsKeyPairSet.c',           condAlways],
        ['aps/src/apsMemoryManager.c',        condAlways],
        ['aps/src/apsRejectDuplicate.c',      condAlways],
        ['aps/src/apsRemoveDevice.c',         condAlways],
        ['aps/src/apsRequestKey.c',           condAlways],
        ['aps/src/apsSkke.c',                 condAlways],
        ['aps/src/apsSkkeInitiator.c',        condAlways],
        ['aps/src/apsSkkeResponder.c',        condAlways],
        ['aps/src/apsSmSsp.c',                condAlways],
        ['aps/src/apsStateMachine.c',         condAlways],
        ['aps/src/apsSwitchKey.c',            condAlways],
        ['aps/src/apsTaskManager.c',          condAlways],
        ['aps/src/apsTransportAppKey.c',      condAlways],
        ['aps/src/apsTransportKey.c',         condAlways],
        ['aps/src/apsTransportNwkKey.c',      condAlways],
        ['aps/src/apsTransportTrustKey.c',    condAlways],
        ['aps/src/apsUpdateDevice.c',         condAlways],
        ['aps/src/apsVerifyKey.c',            condAlways],
    ]

    zdrvStackBDBSrcFiles = [
        ['bdb/src/bdb.c',                        condAlways],
        ['bdb/src/bdbBcEventsHandler.c',         condAlways],
        ['bdb/src/bdbFindingAndBinding.c',       condCommnFindingBinding],
        ['bdb/src/bdbInstallCode.c',             condAlways],
        ['bdb/src/bdbCommissioning.c',           condAlways],
        ['bdb/src/bdbNwkFormation.c',            condCommnNetworkFormation],
        ['bdb/src/bdbNwkSteering.c',             condCommnNetworkSteering],
        ['bdb/src/bdbSecurity.c',                condAlways],
        ['bdb/src/bdbTouchlink.c',               condCommnTouchlink],
        ['bdb/src/bdbPdt.c',                     condAlways],
        ['bdb/src/bdbReset.c',                   condAlways],
        ['bdb/src/bdbIB.c',                      condAlways],
    ]

    zdrvStackConfigServerSrcFiles = [
        ['configserver/src/configserver.c',      condAlways],
        ['configserver/src/csMem.c',             condAlways],
        ['configserver/src/csPersistentMem.c',   condAlways],
    ]

    zdrvStackNWKSrcFiles = [
        ['nwk/src/nwkAddress.c',                 condAlways],
        ['nwk/src/nwkAddressConflict.c',         condAlways],
        ['nwk/src/nwkAddressMap.c',              condAlways],
        ['nwk/src/nwkAddressResolv.c',           condAlways],
        ['nwk/src/nwkBTT.c',                     condAlways],
        ['nwk/src/nwkCommands.c',                condAlways],
        ['nwk/src/nwkConcentrator.c',            condAlways],
        ['nwk/src/nwkDataReq.c',                 condAlways],
        ['nwk/src/nwkDirectJoin.c',              condAlways],
        ['nwk/src/nwkDiscovery.c',               condAlways],
        ['nwk/src/nwkEDScan.c',                  condAlways],
        ['nwk/src/nwkEndDeviceTimeoutInd.c',     condAlways],
        ['nwk/src/nwkEndDeviceTimeoutReq.c',     condAlways],
        ['nwk/src/nwkFormation.c',               condAlways],
        ['nwk/src/nwkFrame.c',                   condAlways],
        ['nwk/src/nwkGroup.c',                   condAlways],
        ['nwk/src/nwkIB.c',                      condAlways],
        ['nwk/src/nwkInCounterSet.c',            condAlways],
        ['nwk/src/nwkJoinInd.c',                 condAlways],
        ['nwk/src/nwkJoinReq.c',                 condAlways],
        ['nwk/src/nwkLeaveInd.c',                condAlways],
        ['nwk/src/nwkLeaveReq.c',                condAlways],
        ['nwk/src/nwkLinkStatus.c',              condAlways],
        ['nwk/src/nwkLoopback.c',                condAlways],
        ['nwk/src/nwkManager.c',                 condAlways],
        ['nwk/src/nwkManyToOne.c',               condAlways],
        ['nwk/src/nwkMem.c',                     condAlways],
        ['nwk/src/nwkNeighborTable.c',           condAlways],
        ['nwk/src/nwkOrphan.c',                  condAlways],
        ['nwk/src/nwkPacket.c',                  condAlways],
        ['nwk/src/nwkPassiveAck.c',              condAlways],
        ['nwk/src/nwkPermitJoining.c',           condAlways],
        ['nwk/src/nwkProfiler.c',                condAlways],
        ['nwk/src/nwkReportCommand.c',           condAlways],
        ['nwk/src/nwkReset.c',                   condAlways],
        ['nwk/src/nwkRouteCache.c',              condAlways],
        ['nwk/src/nwkRouteDiscovery.c',          condAlways],
        ['nwk/src/nwkRouteDiscoveryTable.c',     condAlways],
        ['nwk/src/nwkRouteRecord.c',             condAlways],
        ['nwk/src/nwkRouteReply.c',              condAlways],
        ['nwk/src/nwkRouteRequest.c',            condAlways],
        ['nwk/src/nwkRouting.c',                 condAlways],
        ['nwk/src/nwkRoutingTable.c',            condAlways],
        ['nwk/src/nwkRx.c',                      condAlways],
        ['nwk/src/nwkSecurity.c',                condAlways],
        ['nwk/src/nwkSilentJoin.c',              condAlways],
        ['nwk/src/nwkSourceRouting.c',           condAlways],
        ['nwk/src/nwkStartRouter.c',             condAlways],
        ['nwk/src/nwkStateMachine.c',            condAlways],
        ['nwk/src/nwkStatusInd.c',               condAlways],
        ['nwk/src/nwkStatusReq.c',               condAlways],
        ['nwk/src/nwkSync.c',                    condAlways],
        ['nwk/src/nwkSyncLoss.c',                condAlways],
        ['nwk/src/nwkTaskManager.c',             condAlways],
        ['nwk/src/nwkTx.c',                      condAlways],
        ['nwk/src/nwkTxDelay.c',                 condAlways],
        ['nwk/src/nwkTxSecurity.c',              condAlways],
        ['nwk/src/nwkUpdateCommand.c',           condAlways],
    ]

    zdrvStackMACSrcFiles = [
        # MAC Environment
        ['mac_phy/mac_env/src/macenvPib.c',                                         condAlways],
        ['mac_phy/mac_env/src/macMem.c',                                            condAlways],

        # MAC HWD
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdBatMonHandler.c',       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdCalibHandler.c',        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdEdHandler.c',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdEncryptHandler.c',      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdFrameRoutine.c',        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdHandlerCtrl.c',         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdManager.c',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRegAccessHandler.c',    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdResetHandler.c',        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRndHandler.c',          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRxBuffer.c',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRxFrameHandler.c',      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdSetHandler.c',          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTrxCtrl.c',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTrxHandler.c',          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTxFrameHandler.c',      condAlways],

        # PHY
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyAntDiversity.c',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyBatMon.c',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyCalib.c',                      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyDeepSleep.c',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyEd.c',                         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyEncrypt.c',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyInit.c',                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRegAccess.c',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyReset.c',                      condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRfIrqDispatcher.c',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRnd.c',                        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRtimerIrqDispatcher.c',        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRxFrame.c',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRxTxIndicator.c',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phySet.c',                        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phySetTrxState.c',                condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyStateMachine.c',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyTxFrame.c',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyTxPowerConverter.c',           condAlways],

        # MAC HWI
        ['mac_phy/mac_hwi/src/machwiAssociateHandler.c',                            condAlways],
        ['mac_phy/mac_hwi/src/machwiBanNode.c',                                     condAlways],
        ['mac_phy/mac_hwi/src/machwiBeaconHandler.c',                               condAlways],
        ['mac_phy/mac_hwi/src/machwiDataHandler.c',                                 condAlways],
        ['mac_phy/mac_hwi/src/machwiDisassociateHandler.c',                         condAlways],
        ['mac_phy/mac_hwi/src/machwiManager.c',                                     condAlways],
        ['mac_phy/mac_hwi/src/machwiOrphanHandler.c',                               condAlways],
        ['mac_phy/mac_hwi/src/machwiPanIdConflictHandler.c',                        condAlways],
        ['mac_phy/mac_hwi/src/machwiPanServer.c',                                   condAlways],
        ['mac_phy/mac_hwi/src/machwiPollHandler.c',                                 condAlways],
        ['mac_phy/mac_hwi/src/machwiPurgeHandler.c',                                condAlways],
        ['mac_phy/mac_hwi/src/machwiResetHandler.c',                                condAlways],
        ['mac_phy/mac_hwi/src/machwiRxEnableHandler.c',                             condAlways],
        ['mac_phy/mac_hwi/src/machwiScanHandler.c',                                 condAlways],
        ['mac_phy/mac_hwi/src/machwiSetGetHandler.c',                               condAlways],
        ['mac_phy/mac_hwi/src/machwiStartHandler.c',                                condAlways],
        ['mac_phy/mac_hwi/src/machwiSwitchRxCtrl.c',                                condAlways],
        ['mac_phy/mac_hwi/src/machwiTransactionHandler.c',                          condAlways],
        ['mac_phy/mac_hwi/src/machwiTransactionHash.c',                             condAlways],
        ['mac_phy/mac_hwi/src/machwiTransactionQueue.c',                            condAlways],
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
        ['security/serviceprovider/src/sspAuthenticHandler.c',                 condAlways],
        ['security/serviceprovider/src/sspCcmHandler.c',                       condAlways],
        ['security/serviceprovider/src/sspChallengeGenHandler.c',              condAlways],
        ['security/serviceprovider/src/sspHash.c',                             condAlways],
        ['security/serviceprovider/src/sspHashHandler.c',                      condAlways],
        ['security/serviceprovider/src/sspManager.c',                          condAlways],
        ['security/serviceprovider/src/sspMem.c',                              condAlways],
        ['security/serviceprovider/src/sspReset.c',                            condAlways],
        ['security/serviceprovider/src/sspSfpHandler.c',                       condAlways],
        ['security/serviceprovider/src/sspSkkeHandler.c',                      condAlways],
        ['security/TrustCentre/src/tcAuthenticHandler.c',                      condAlways],
        ['security/TrustCentre/src/tcDeviceTableCtrlHandler.c',                condAlways],
        ['security/TrustCentre/src/tcIndInput.c',                              condAlways],
        ['security/TrustCentre/src/tcKeyEstablishHandler.c',                   condAlways],
        ['security/TrustCentre/src/tcKeyUpdateHandler.c',                      condAlways],
        ['security/TrustCentre/src/tcMem.c',                                   condAlways],
        ['security/TrustCentre/src/tcPermissions.c',                           condAlways],
        ['security/TrustCentre/src/tcPromiscuousMode.c',                       condAlways],
        ['security/TrustCentre/src/tcRemoveHandler.c',                         condAlways],
        ['security/TrustCentre/src/tcResetHandler.c',                          condAlways],
        ['security/TrustCentre/src/tcTaskManager.c',                           condAlways],
        ['security/SoftAes/sspAesHandler.c',                                   condAlways],
    ]

    zdrvStackZDOSrcFiles = [
        ['zdo/src/zdoAddrResolving.c',                    condAlways],
        ['zdo/src/zdoBinding.c',                          condAlways],
        ['zdo/src/zdoCommands.c',                         condAlways],
        ['zdo/src/zdoEndDeviceBinding.c',                 condAlways],
        ['zdo/src/zdoInit.c',                             condAlways],
        ['zdo/src/zdoIntraPanPortability.c',              condAlways],
        ['zdo/src/zdoLeaveNetwork.c',                     condAlways],
        ['zdo/src/zdoMem.c',                              condAlways],
        ['zdo/src/zdoMgmtNwkUpdate.c',                    condAlways],
        ['zdo/src/zdoNodeManager.c',                      condAlways],
        ['zdo/src/zdoNotify.c',                           condAlways],
        ['zdo/src/zdoNwkManager.c',                       condAlways],
        ['zdo/src/zdoParentAnnounce.c',                   condAlways],
        ['zdo/src/zdoPermissionsTable.c',                 condAlways],
        ['zdo/src/zdoPowerManager.c',                     condAlways],
        ['zdo/src/zdoReset.c',                            condAlways],
        ['zdo/src/zdoSecurityManager.c',                  condAlways],
        ['zdo/src/zdoServiceDiscovery.c',                 condAlways],
        ['zdo/src/zdoStartNetwork.c',                     condAlways],
        ['zdo/src/zdoStateMachine.c',                     condAlways],
        ['zdo/src/zdoTaskManager.c',                      condAlways],
        ['zdo/src/zdoZdpReq.c',                           condAlways],
        ['zdo/src/zdoZib.c',                              condAlways],
    ]

    zdrvStackZCLSrcFiles = [
        ['zcl/src/zcl.c',                       condAlways],
        ['zcl/src/zclApsInterface.c',           condAlways],
        ['zcl/src/zclAttributes.c',             condAlways],
        ['zcl/src/zclCommandAnalyzer.c',        condAlways],
        ['zcl/src/zclCommandManager.c',         condAlways],
        ['zcl/src/zclDummyEcc.c',               condAlways],
        ['zcl/src/zclKeyEstablishmentCluster.c',condAlways],
        ['zcl/src/zclMemoryManager.c',          condAlways],
        ['zcl/src/zclOtauClient.c',             condAlways],
        ['zcl/src/zclOtauClientDiscovery.c',    condAlways],
        ['zcl/src/zclOtauClientDownload.c',     condAlways],
        ['zcl/src/zclOtauClientPdt.c',          condAlways],
        ['zcl/src/zclOtauClientQuery.c',        condAlways],
        ['zcl/src/zclOtauClientUpgrade.c',      condAlways],
        ['zcl/src/zclOtauManager.c',            condAlways],
        ['zcl/src/zclOtauServer.c',             condAlways],
        ['zcl/src/zclParser.c',                 condAlways],
        ['zcl/src/zclSecurityManager.c',        condAlways],
        ['zcl/src/zclTaskManager.c',            condAlways],
		['zcl/clusters/src/scenes.c',           condAlways],
    ]

    zdrvStackHALSrcFiles = [
        ['hal/cortexm4/pic32cx/src/atomic.c',                 condAlways],
        #['hal/cortexm4/pic32cx/src/hal_aes_sync.c',           condAlways],
        ['hal/cortexm4/pic32cx/src/halAppClock.c',            condAlways],
        ['hal/cortexm4/pic32cx/src/halFlash.c',               condAlways],
        ['hal/cortexm4/pic32cx/src/halMacIsr.c',              condAlways],
        ['hal/cortexm4/pic32cx/src/halRfCtrl.c',              condAlways],
        ['hal/cortexm4/pic32cx/src/halSleep.c',               condAlways],
        ['hal/cortexm4/pic32cx/src/halSleepTimerClock.c',     condAlways],
        #['hal/cortexm4/pic32cx/src/hpl_aes.c',                condAlways],
        ['hal/cortexm4/pic32cx/src/halAes.c',                 condAlways],
        ['hal/cortexm4/common/src/appTimer.c',                condAlways],
        ['hal/cortexm4/common/src/flash.c',                   condAlways],
        ['hal/cortexm4/common/src/halTaskManager.c',          condAlways],
        ['hal/cortexm4/common/src/sleep.c',                   condAlways],
        ['hal/cortexm4/common/src/sleepTimer.c',              condAlways],
        ['hal/cortexm4/common/src/statStack.c',               condAlways],
        ['hal/cortexm4/common/src/timer.c',                   condAlways],
    ]

    zdrvStackZLLSrcFiles = [
        ['zllplatform/ZLL/N_AddressManager/src/N_AddressManager.c',                 condAlways],
        ['zllplatform/ZLL/N_AddressMap/src/N_AddressMap.c',                         condAlways],
        ['zllplatform/ZLL/N_Binding/src/N_Binding.c',                               condAlways],
        ['zllplatform/ZLL/N_Cmi/src/N_Cmi.c',                                       condAlways],
        ['zllplatform/ZLL/N_Connection/src/N_Connection_ReconnectHandler.c',        condAlways],
        ['zllplatform/ZLL/N_Connection/src/N_ConnectionAssociation.c',              condAlways],
        ['zllplatform/ZLL/N_Connection/src/N_ConnectionCommon.c',                   condAlways],
        ['zllplatform/ZLL/N_Connection/src/N_ConnectionEnddevice.c',                condAlways],
        ['zllplatform/ZLL/N_Connection/src/N_ConnectionRouter.c',                   condAlways],
        ['zllplatform/ZLL/N_DeviceInfo/src/N_DeviceInfo.c',                         condAlways],
        ['zllplatform/ZLL/N_EndDeviceRobustness/src/N_EndDeviceRobustness.c',       condAlways],
        ['zllplatform/ZLL/N_Groups/src/N_Groups.c',                                 condAlways],
        ['zllplatform/ZLL/N_InterPan/src/N_InterPan.c',                             condAlways],
        ['zllplatform/ZLL/N_InterPan/src/N_InterPanBuffers.c',                      condAlways],
        ['zllplatform/ZLL/N_LinkInitiator/src/N_LinkInitiator.c',                   condCommnTouchlink],
        ['zllplatform/ZLL/N_LinkTarget/src/N_LinkTarget.c',                         condAlways],
        ['zllplatform/ZLL/N_PacketDistributor/src/N_PacketDistributor.c',           condAlways],
        ['zllplatform/ZLL/N_Radio/src/N_Radio.c',                                   condAlways],
        ['zllplatform/ZLL/N_ReconnectHandler/src/N_ReconnectHandler.c',             condAlways],
        ['zllplatform/ZLL/N_Security/src/N_Security.c',                             condAlways],
        ['zllplatform/ZLL/N_Security/src/N_Security_Calc.c',                        condAlways],
        ['zllplatform/ZLL/N_SourceRouting/src/N_SourceRouting.c',                   condAlways],
        ['zllplatform/ZLL/N_TrustCenter/src/N_TrustCenter.c',                       condAlways],
        ['zllplatform/ZLL/N_Zdp/src/N_Zdp.c',                                       condAlways],
        ['zllplatform/infrastructure/N_Address/src/N_Address.c',                    condAlways],
        ['zllplatform/infrastructure/N_ErrH/src/N_ErrH.c',                          condAlways],
        ['zllplatform/infrastructure/N_Fsm/src/N_Fsm.c',                            condAlways],
        ['zllplatform/infrastructure/N_Log/src/N_Log.c',                            condAlways],
        ['zllplatform/infrastructure/N_Memory/src/N_Memory-Atmel.c',                condAlways],
        ['zllplatform/infrastructure/N_Task/src/N_Task-Internal-Atmel.c',           condAlways],
        ['zllplatform/infrastructure/N_Task/src/N_Task.c',                          condAlways],
        ['zllplatform/infrastructure/N_Timer/src/N_Timer.c',                        condAlways],
        ['zllplatform/infrastructure/N_Timer/src/N_Timer-Internal-Atmel.c',         condAlways],
        ['zllplatform/infrastructure/N_Util/src/N_Util.c',                          condAlways],
    ]

    zdrvStackPDSSrcFiles = [
        ['PersistDataServer/src/fakePds.c',                       condAlways],
        ['PersistDataServer/std/src/stdPdsCrcService.c',          condPDSStandard],
        ['PersistDataServer/std/src/stdPdsDataServer.c',          condPDSStandard],
        ['PersistDataServer/std/src/stdPdsEvents.c',              condPDSStandard],
        ['PersistDataServer/std/src/stdPdsInit.c',                condPDSStandard],
        ['PersistDataServer/std/src/stdPdsMem.c',                 condPDSStandard],
        ['PersistDataServer/std/src/stdPdsMemAccess.c',           condPDSStandard],
        ['PersistDataServer/std/src/stdPdsTimer.c',               condPDSStandard],
        ['PersistDataServer/std/src/stdPdsWriteData.c',           condPDSStandard],
        ['PersistDataServer/wl/src/wlPdsDataServer.c',            condPDSWearLevelling],
        ['PersistDataServer/wl/src/wlPdsInit.c',                  condPDSWearLevelling],
        ['PersistDataServer/wl/src/wlPdsSecurity.c',              condPDSWearLevelling],
        ['PersistDataServer/wl/src/wlPdsTaskManager.c',           condPDSWearLevelling],
        ['PersistDataServer/wl/src/wlPdsTypesConverter.c',        condPDSWearLevelling],
        ['zllplatform/ZLL/S_Nv/src/S_Nv-Pic32cx.c',               condPDSUseInternalMem],
        ['zllplatform/ZLL/S_Nv/src/S_Nv-External.c',              condPDSUseExternalMem],
        ['zllplatform/ZLL/S_Nv/src/S_Nv_Stub.c',                  condAlways],
        ['zllplatform/ZLL/D_Nv/src/D_Nv.c',                       condPDSUseInternalMem],
        ['zllplatform/ZLL/S_XNv/src/S_XNv.c',                     condPDSUseExternalMem],
#       ['zllplatform/ZLL/D_XNv/src/D_XNv.c',                     condPDSUseExternalMem],
    ]
    
    zdrvBSPSrcFiles = [
        ['bsp/PIC32CX/src/fakeBSP.c',                                     condAlways],
    ]

    zdrvGreenPowerSrcFiles = [
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterClient.c',          condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterGeneric.c',         condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpClusterServer.c',          condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpHighGeneric.c',            condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpHighMem.c',                condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpMiddleProxy.c',            condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyBasic.c',             condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyPdt.c',               condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpProxyTable.c',             condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkBasic.c',              condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkPdt.c',                condAlways],
        ['ZGP/GPInfrastructure/highZgp/src/zgpSinkTable.c',              condAlways],
        
        ['ZGP/GPInfrastructure/lowZgp/src/zgpCstub.c',                   condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpDstub.c',                   condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowGeneric.c',              condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowMem.c',                  condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowProxy.c',                condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpLowSink.c',                 condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpNvmTable.c',                condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpPacket.c',                  condAlways],
        ['ZGP/GPInfrastructure/lowZgp/src/zgpTaskManager.c',             condAlways],
        
        ['ZGP/GPInfrastructure/src/zgpGeneric.c',                        condAlways],
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

    #freeRTOSSrcFiles = [
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/list.c',                      condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/queue.c',                     condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/tasks.c',                     condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/timers.c',                    condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/GCC/ARM_CM4F/port.c',condAlways],
        #['thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang/heap_2.c',   condAlways],
    #]

    utilsSrcFiles = [
        ['utils/interrupt/interrupt_sam_nvic.c',                      condAlways],
    ]

    #frameworkSrcFiles = [
        #['framework/osal/src/osal_freertos.c',                        condAlways],
        #['framework/osal/src/osal_freertos_extend.c',               condAlways],
    #]

    driversSrcFiles = [
        ['drivers/sercom/usart/drv_usart.c',                  condAlways],
        ['drivers/sercom/usart/write.c',                      condAlways],
    ]

    zgbWrappersSrcFiles = [
        ['src/zgb_wrappers/bdb/BDB_Unpack.c',                      condAlways],
        ['src/zgb_wrappers/configserver/CS_Unpack.c',              condAlways],
        ['src/zgb_wrappers/nwk/NWK_Unpack.c',                      condAlways],
        ['src/zgb_wrappers/zcl/ZCL_Unpack.c',                      condAlways],
        ['src/zgb_wrappers/zdo/ZDO_Unpack.c',                      condAlways],
    ]

    applicationCommonSrcFiles = [
        ['application/zigbee_only/common_files/src/initialization.c',                                    condAlways],
        ##['application/zigbee_only/Zigbee_Device_Application/common/src/app_zigbee.c',                    condAlways],
        ##['application/zigbee_only/Zigbee_Device_Application/common/src/main.c',                          condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/zgb_init.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/zgb_task.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/src/system_tasks.c',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/zgb_app_callback.c',              condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/z3DevicePic32cx.c',               condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/src/z3Device.c',                     condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/common/src/otauService.c',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/zgpTranslationTable.c',           condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/zgpAppInterface.c',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/hs2xy.c',                         condAlways],
        ['application/zigbee_only/common_files/src/errH.c',                                              condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/identifyCluster.c',             condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/scenes.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/groupsCluster.c',               condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/haClusters.c',                  condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/levelControlCluster.c',         condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/colorControlCluster.c',         condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/onOffCluster.c',                condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/commissioningCluster.c',        condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/alarmCluster.c',                condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/scenesCluster.c',                condAlways],

        # Console Files
        ['application/zigbee_only/Zigbee_Device_Application/common/src/console.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/consoleCmds.c',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/common/src/commandManager.c',               condAlways],
        ['application/zigbee_only/common_files/src/uartManager.c',                                      condAlways],

        # API Wrapper Files
        ['application/zigbee_only/Zigbee_Device_Application/api/src/BDB_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/src/CS_API.c',                       condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/src/NWK_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/src/ZCL_API.c',                      condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/api/src/ZDO_API.c',                      condAlways],
    ]

    applicationClustersSrcFiles = [
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/identifyCluster.c',             condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/scenes.c',                      condAlways],
        #['application/zigbee_only/Zigbee_Device_Application/clusters/src/groupsCluster.c',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/haClusters.c',                  condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/levelControlCluster.c',         condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/colorControlCluster.c',         condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/onOffCluster.c',                condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/commissioningCluster.c',        condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/alarmCluster.c',                condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/src/scenesCluster.c',                condAlways],
        #['src/Components/zcl/clusters/src/groupsCluster.c',                                              condAlways],
        #['src/Components/zcl/clusters/src/identifyCluster.c',                                            condAlways],
        #['src/Components/zcl/clusters/src/scenes.c',                                                     condAlways],
    ]

    deviceTypesSrcFiles = [
         # Light Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/light.c',                                     condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightClusters.c',                             condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightBasicCluster.c',                         condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightIdentifyCluster.c',                      condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightGroupsCluster.c',                        condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightScenesCluster.c',                        condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightOnOffCluster.c',                         condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightLevelControlCluster.c',                  condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightColorControlCluster.c',                  condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightColorSchemesConversion.c',               condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightCommissioningCluster.c',                 condDevLight],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/lightConsole.c',                              condDevLight],

        # Color Scene Controller Device Type
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/colorSceneController.c',       condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscBasicCluster.c',            condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscClusters.c',                condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscColorControlCluster.c',     condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscCommissioningCluster.c',    condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscConsole.c',                 condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscGroupsCluster.c',           condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscIdentifyCluster.c',         condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscLevelControlCluster.c',     condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscOnOffCluster.c',            condDevColorSceneController],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/src/cscScenesCluster.c',           condDevColorSceneController],

        # Combined Interface Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciAlarmsCluster.c',               condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciBasicCluster.c',                condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciClusters.c',                    condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciColorControlCluster.c',         condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciCommissioningCluster.c',        condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciConsole.c',                     condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciFanControlCluster.c',           condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciGroupsCluster.c',               condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciHumidityMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciIasACECluster.c',               condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciIasZoneCluster.c',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciIdentifyCluster.c',                condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciIlluminanceMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciLevelControlCluster.c',            condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciOccupancySensingCluster.c',        condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciOnOffCluster.c',                   condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciScenesCluster.c',                  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciTemperatureMeasurementCluster.c',  condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciThermostatCluster.c',              condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciThermostatUiConfCluster.c',        condDevCombInterface],    
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/ciTimeCluster.c',                    condDevCombInterface],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/src/combinedInterface.c',                condDevCombInterface],

          # Control Bridge Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbBasicCluster.c',                  condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbClusters.c',                      condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbColorControlCluster.c',           condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbCommissioningCluster.c',          condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbConsole.c',                       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbGroupsCluster.c',                 condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbIdentifyCluster.c',               condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbIlluminanceMeasurementCluster.c', condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbLevelControlCluster.c',           condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbOccupancySensingCluster.c',       condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbOnOffCluster.c',                  condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/cbScenesCluster.c',                 condDevControlBridge],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/src/controlBridge.c',                   condDevControlBridge],

          # Dimmer Switch Device Type Files 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dimmerSwitch.c',                     condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsBasicCluster.c',                   condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsClusters.c',                       condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsConsole.c',                        condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsGroupsCluster.c',                  condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsIdentifyCluster.c',                condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsLevelControlCluster.c',            condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsOnOffCluster.c',                   condDevDimmerSwitch],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/src/dsScenesCluster.c',                  condDevDimmerSwitch],

         # IAS ACE
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACE.c',                                condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEAceCluster.c',                      condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEBasicCluster.c',                    condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACECluster.c',                         condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEConsole.c',                         condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEGroupsCluster.c',                   condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEIdentifyCluster.c',                 condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEPdt.c',                             condDevIasAce],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/src/iasACEZoneCluster.c',                     condDevIasAce],

         # Multi Sensor
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/hsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/hsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/hsHumidityMeasurementCluster.c',      condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/hsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/lsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/lsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/lsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/lsIlluminanceMeasurementCluster.c',   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/msClusters.c',                        condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/msConsole.c',                         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/msPdt.c',                             condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/multiSensor.c',                       condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/osBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/osGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/osIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/osOccupancySensingCluster.c',         condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/tsBasicCluster.c',                    condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/tsGroupsCluster.c',                   condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/tsIdentifyCluster.c',                 condDevMultiSensor],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/src/tsTemperatureMeasurementCluster.c',   condDevMultiSensor],

         # Thermostat
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thAlarmsCluster.c',                     condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thBasicCluster.c',                      condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thClusters.c',                          condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thConsole.c',                           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thermostat.c',                          condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thFanControlCluster.c',                 condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thGroupsCluster.c',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thHumidityMeasurementCluster.c',        condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thIdentifyCluster.c',                   condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thOccupancySensingCluster.c',           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thPdt.c',                               condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thScenesCluster.c',                     condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thTemperatureMeasurementCluster.c',     condDevThermostat], 
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thThermostatCluster.c',                 condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thThermostatUiConfCluster.c',           condDevThermostat],
        ['application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/src/thTimeCluster.c',                       condDevThermostat],
    ]

    zigbeeLightSrc = drvZigbeeComponent.createFileSymbol("ZIGBEELIGHT_SRC", None)
    zigbeeLightSrc.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_Device_Application/devicetypes/light/src/light.c")
    zigbeeLightSrc.setOutputName("light.c")
    zigbeeLightSrc.setDestPath("/application/devicetypes/light/src")
    zigbeeLightSrc.setProjectPath("config/" + configName + "/application/devicetypes/light/src")
    zigbeeLightSrc.setType("SOURCE")
    zigbeeLightSrc.setEnabled(False)
    zigbeeLightSrc.setDependencies(setEnableLightDevice, ["ZB_DEVICE_TYPE"])

    #for srcFileEntry in freeRTOSSrcFiles:
        #importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in utilsSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    #for srcFileEntry in frameworkSrcFiles:
        #importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in driversSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zgbWrappersSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationCommonSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationClustersSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in deviceTypesSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)


    zigbeeStackdrvIncPaths = [
        ['/',                                                                  condAlways],
        ['/src/Components',                                                    condAlways],
        ['/src/Components/aps/include',                                        condAlways],
        ['/src/Components/aps/include/private',                                condAlways],
        ['/src/Components/bdb/include',                                        condAlways],
        ['/src/Components/bsp/include',                                        condAlways],
        ['/src/Components/bsp/PIC32CX/include',                                condAlways],
        ['/src/Components/configserver/include',                               condAlways],
        ['/src/Components/configserver/include/private',                       condAlways],
        ['/src/Components/hal/include',                                        condAlways],
        ['/src/Components/hal/cortexm4/pic32cx/include',                       condAlways],
        ['/src/Components/mac_phy/include',                                    condAlways],
        ['/src/Components/mac_phy/mac_env/include',                            condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/include',                        condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy',                                condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD',            condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include',    condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/PHY',                condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/PHY/include',        condAlways],
        ['/src/Components/mac_phy/mac_hwi/include',                            condAlways],
        ['/src/Components/nwk/include',                                        condAlways],
        ['/src/Components/nwk/include/private',                                condAlways],
        ['/src/Components/PersistDataServer/include',                          condAlways],
        ['/src/Components/PersistDataServer/std/include',                      condAlways],
        ['/src/Components/PersistDataServer/wl/include',                       condAlways],
        ['/src/Components/security/serviceprovider/include',                   condAlways],
        ['/src/Components/security/serviceprovider/include/private',           condAlways],
        ['/src/Components/security/SoftAes',                                   condAlways],
        ['/src/Components/security/TrustCentre/include',                       condAlways],
        ['/src/Components/security/TrustCentre/include/private',               condAlways],
        ['/src/Components/systemenvironment/include',                          condAlways],
        ['/src/Components/systemenvironment/include/private',                  condAlways],
        ['/src/Components/zcl/include/private',                                condAlways],
        ['/src/Components/zdo/include/private',                                condAlways],
        ['/src/Components/zcl/include',                                        condAlways],
        ['/src/Components/zcl/clusters/include',                               condAlways],
        ['/src/Components/zdo/include',                                        condAlways],
        ['/src/Components/ZLLPlatform',                                        condAlways],
        ['/src/Components/zllplatform/include',                                condAlways],
        ['/src/Components/zllplatform/infrastructure',                         condAlways],
        ['/src/Components/zllplatform/ZLL',                                    condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Address/include',       condAlways],
        ['/src/Components/zllplatform/infrastructure/N_ErrH/include',          condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Beacon/include',        condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Fsm/include',           condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Init/include',          condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Log/include',           condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Memory/include',        condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Task/include',          condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Timer/include',         condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Types/include',         condAlways],
        ['/src/Components/zllplatform/infrastructure/N_Util/include',          condAlways],
        ['/src/Components/zllplatform/ZLL/N_AddressManager/include',           condAlways],
        ['/src/Components/zllplatform/ZLL/N_AddressMap/include',               condAlways],
        ['/src/Components/zllplatform/ZLL/N_Beacon/include',                   condAlways],
        ['/src/Components/zllplatform/ZLL/N_Binding/include',                  condAlways],
        ['/src/Components/zllplatform/ZLL/N_Cmi/include',                      condAlways],
        ['/src/Components/zllplatform/ZLL/N_Connection/include',               condAlways],
        ['/src/Components/zllplatform/ZLL/N_DeviceInfo/include',               condAlways],
        ['/src/Components/zllplatform/ZLL/N_Diagnostics/include',              condAlways],
        ['/src/Components/zllplatform/ZLL/N_EndDeviceRobustness/include',      condAlways],
        ['/src/Components/zllplatform/ZLL/N_Groups/include',                   condAlways],
        ['/src/Components/zllplatform/ZLL/N_Hac/include',                      condAlways],
        ['/src/Components/zllplatform/ZLL/N_InterPan/include',                 condAlways],
        ['/src/Components/zllplatform/ZLL/N_LinkInitiator/include',            condAlways],
        ['/src/Components/zllplatform/ZLL/N_LinkTarget/include',               condAlways],
        ['/src/Components/zllplatform/ZLL/N_LowPower/include',                 condAlways],
        ['/src/Components/zllplatform/ZLL/N_PacketDistributor/include',        condAlways],
        ['/src/Components/zllplatform/ZLL/N_Radio/include',                    condAlways],
        ['/src/Components/zllplatform/ZLL/N_ReconnectHandler/include',         condAlways],
        ['/src/Components/zllplatform/ZLL/N_Security/include',                 condAlways],
        ['/src/Components/zllplatform/ZLL/N_SourceRouting/include',            condAlways],
        ['/src/Components/zllplatform/ZLL/N_TrustCenter/include',              condAlways],
        ['/src/Components/zllplatform/ZLL/N_Watchdog/include',                 condAlways],
        ['/src/Components/zllplatform/ZLL/N_Zcl_Framework/include',            condAlways],
        ['/src/Components/zllplatform/ZLL/N_Zdp/include',                      condAlways],
        ['/src/Components/zllplatform/ZLL/S_Nv/include',                       condAlways],
        ['/src/Components/zllplatform/ZLL/S_XNv/include',                      condAlways],
        ['/src/Components/zllplatform/ZLL/D_Nv/include',                         condAlways],
        # ['/src/Components/zllplatform/ZLL/D_XNv/include',                      condAlways],
        ['/src/zgb_wrappers/bdb',                                                condAlways],
        ['/src/zgb_wrappers/configserver',                                       condAlways],
        ['/src/zgb_wrappers/nwk',                                                condAlways],
        ['/src/zgb_wrappers/zcl',                                                condAlways],
        ['/src/zgb_wrappers/zdo',                                                condAlways],
        ['/utils',                                                               condAlways],
        # ['/cmsis',                                                               condAlways],
        ['/drivers/sercom/usart',                                                condAlways],
        ['/utils/interrupt',                                                     condAlways],
        ['/utils/preprocessor',                                                  condAlways],
        # ['/framework',                                                           condAlways],
        # ['/framework/osal',                                                      condAlways],
        ['/application/zigbee_only/common_files/include',                        condAlways], 
        ['/application/zigbee_only/Zigbee_Device_Application',                   condAlways], 
        #['/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include',             condAlways],
        #['/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/GCC/ARM_CM4F',                        condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/common/include',                              condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/api/include',                                 condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/clusters/include',                            condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/configs',                                     condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes',                                 condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/colorSceneController/include',    condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include',       condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/controlBridge/include',           condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmableLight/include',           condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/dimmerSwitch/include',            condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/extendedColorLight/include',      condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/ias_ace/include',                 condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/light/include',                   condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/multiSensor/include',             condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/devicetypes/thermostat/include',              condAlways],
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
    zigbeeLinkerFile = drvZigbeeComponent.createFileSymbol("ZB_LINKER_FILE", None)
    zigbeeLinkerFile.setSourcePath("/driver/zigbee/templates/zb_PIC32CX1012BZ25048.ld")
    zigbeeLinkerFile.setOutputName("zb_PIC32CX1012BZ25048.ld")
    zigbeeLinkerFile.setMarkup(True)
    zigbeeLinkerFile.setOverwrite(True)
    zigbeeLinkerFile.setType("LINKER")

    preprocessorLD = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD1', None)
    preprocessorLD.setValue('false')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('no-device-startup-code')
    preprocessorLD.setEnabled(True)

    preprocessorLD = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD2', None)
    preprocessorLD.setValue('4096')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('heap-size')
    preprocessorLD.setEnabled(True)

    preprocessorLD = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD3', None)
    preprocessorLD.setValue('1024')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('stack-size')
    preprocessorLD.setEnabled(True)

    preprocessorAS = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_AS', None)
    preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;HAL_USE_FLASH_ACCESS;Z3DEVICE_APP')
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
    optlevel.setValue('-Os')
    optlevel.setCategory('C32')
    optlevel.setKey('optimization-level')

    setAdditionaloptionXC32GCC = drvZigbeeComponent.createSettingSymbol('SET_XC32_GCC_ADD_INC', None)
    setAdditionaloptionXC32GCC.setValue('-include"zigbeeAppConfig.h"')
    setAdditionaloptionXC32GCC.setCategory('C32')
    setAdditionaloptionXC32GCC.setKey('appendMe')

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
    incFileSym.setDestPath('/stack/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/stack/'+ secDName + '')
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
    secTname = secDName.replace('Zigbee_Device_Application','application')
    secDName = secTname


    incFileSym.setDestPath('/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

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
    secTname = secDName.replace('Zigbee_Device_Application','application')
    secDName = secTname

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/' + secDName+ '/src/')
    srcFileSym.setProjectPath('config/' + configName + '/' + secDName + '/src/')
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
    srcFileSym.setDestPath('/stack/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/stack/' + secDName)
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
    incPath = incPath.replace('Zigbee_Device_Application','application')
    incPath = incPath.replace('/Components','/stack')
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

def PdsEnableCheck(symbol, event):
    if (pdsConfigEnablePDS.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def OtauEnableCheck(symbol, event):
    if (otauConfigEnable.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def stackDeviceTypeSetCheck():
    if ((zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")):
        return(1) #Coordinator
    elif ((zigbeeDeviceType.getValue() == "THERMOSTAT") or (zigbeeDeviceType.getValue() == "ON_OFF_LIGHT")
          or (zigbeeDeviceType.getValue() == "DIMMABLE_LIGHT") or (zigbeeDeviceType.getValue() == "COLOR_LIGHT")
          or (zigbeeDeviceType.getValue() == "EXTENDED_COLOR_LIGHT") or (zigbeeDeviceType.getValue() == "TEMPERATURE_COLOR_LIGHT")
          ):
        return(2)#Router
    elif ((zigbeeDeviceType.getValue() == "CUSTOM")):
        return(0)#SelectOption
    else:
        return(3)#Enddevice

def NetworkFormationCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "IAS_ACE")
             ):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")
              or (zigbeeDeviceType.getValue() == "THERMOSTAT")
              or (zigbeeDeviceType.getValue() == "ON_OFF_LIGHT")
              or (zigbeeDeviceType.getValue() == "DIMMABLE_LIGHT")
              or (zigbeeDeviceType.getValue() == "COLOR_LIGHT")
              or (zigbeeDeviceType.getValue() == "EXTENDED_COLOR_LIGHT")
              or (zigbeeDeviceType.getValue() == "TEMPERATURE_COLOR_LIGHT")        
             ):
            return(1)
        elif (zigbeeDeviceType.getValue() == "CUSTOM"):
            return(1)
        else:
            return(0)

def NetworkSteeringCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "TEMPERATURE_COLOR_LIGHT")
             ):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "CUSTOM")):
            return(1)
        else:
            return(0)

def TouchlinkCommnSetCheck():
        if (zigbeeDeviceType.getValue() == "COLOR_SCENE_CONTROLLER"):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")
             or (zigbeeDeviceType.getValue() == "CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "TEMPERATURE_COLOR_LIGHT")
             ):
            return(0)
        elif ((zigbeeDeviceType.getValue() == "CUSTOM")):
            return(1)
        else:
            return(0)

def FindingBindingCommnSetCheck():
        if ((zigbeeDeviceType.getValue() == "COLOR_SCENE_CONTROLLER")
             or (zigbeeDeviceType.getValue() == "MULTI_SENSOR")
             or (zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")
             or (zigbeeDeviceType.getValue() == "CONTROL_BRIDGE")
             or (zigbeeDeviceType.getValue() == "THERMOSTAT")
             or (zigbeeDeviceType.getValue() == "IAS_ACE")
             or (zigbeeDeviceType.getValue() == "ON_OFF_LIGHT")
             or (zigbeeDeviceType.getValue() == "DIMMABLE_LIGHT")
             or (zigbeeDeviceType.getValue() == "COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "EXTENDED_COLOR_LIGHT")
             or (zigbeeDeviceType.getValue() == "TEMPERATURE_COLOR_LIGHT")             
             ):
            return(1)
        elif ((zigbeeDeviceType.getValue() == "CUSTOM")):
            return(1)
        else:
            return(0)

def OTAURoleCheck():
    if ((zigbeeDeviceType.getValue() == "COMBINED_INTERFACE")):
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

def setEnableLightDevice(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if (setDevice == "COLOR_LIGHT") or (setDevice == "TEMPERATURE_COLOR_LIGHT") or (setDevice == "ON_OFF_LIGHT") or (zigbeeDeviceType.getValue() == 'EXTENDED_COLOR_LIGHT') or (zigbeeDeviceType.getValue() == 'DIMMABLE_LIGHT'):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableColorSceneController(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "COLOR_SCENE_CONTROLLER")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableCombInterface(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "COMBINED_INTERFACE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableControlBridge(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "CONTROL_BRIDGE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableDimLight(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "DIMMABLE_LIGHT")):
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

    if ((setDevice == "EXTENDED_COLOR_LIGHT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableIasAce(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "IAS_ACE")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableMultiSensor(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "MULTI_SENSOR")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableTempColorLight(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "TEMPERATURE_COLOR_LIGHT")):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableThermostat(symbol, event):
    component = symbol.getComponent()

    setDevice  =  component.getSymbolValue('ZB_DEVICE_TYPE')

    if ((setDevice == "THERMOSTAT")):
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


def onAttachmentConnected(source, target):

    localComponent = source["component"]
    remoteComponent = target["component"]
    remoteID = remoteComponent.getID()
    connectID = source["id"]
    targetID = target["id"]

    print(localComponent.getID())
    print(connectID)
    print(remoteComponent.getID())
    print(remoteID)

    if connectID == "StackLib_SuperSet":
        if (( localComponent.getID() == "COLOR_SCENE_CONTROLLER" ) or ( localComponent.getID() == "MULTI_SENSOR" ) or ( localComponent.getID() == "IAS_ACE" )):
            localComponent.setDependencyEnabled("StackLib_EndDevice", False)
        elif (( localComponent.getID() == "THERMOSTAT" ) or ( localComponent.getID() == "ON_OFF_LIGHT" ) or ( localComponent.getID() == "DIMMABLE_LIGHT" ) or ( localComponent.getID() == "COLOR_LIGHT" ) or ( localComponent.getID() == "EXTENDED_COLOR_LIGHT" ) or ( localComponent.getID() == "TEMPERATURE_COLOR_LIGHT" )):
            localComponent.setDependencyEnabled("StackLib_Router", False)
        elif ( localComponent.getID() == "COMBINED_INTERFACE" ):
            localComponent.setDependencyEnabled("StackLib_Coordinator", False)
        else:
            print ("Custom Device")
    else:
        localComponent.setDependencyEnabled("StackLib_SuperSet", False)



def onAttachmentDisconnected(source, target):

    localComponent = source["component"]
    remoteComponent = target["component"]
    remoteID = remoteComponent.getID()
    connectID = source["id"]
    targetID = target["id"]

    if connectID == "StackLib_SuperSet":
        if (( localComponent.getID() == "COLOR_SCENE_CONTROLLER" ) or ( localComponent.getID() == "MULTI_SENSOR" ) or ( localComponent.getID() == "IAS_ACE" )):
            localComponent.setDependencyEnabled("StackLib_EndDevice", True)
        elif (( localComponent.getID() == "THERMOSTAT" ) or ( localComponent.getID() == "ON_OFF_LIGHT" ) or ( localComponent.getID() == "DIMMABLE_LIGHT" ) or ( localComponent.getID() == "COLOR_LIGHT" ) or ( localComponent.getID() == "EXTENDED_COLOR_LIGHT" ) or ( localComponent.getID() == "TEMPERATURE_COLOR_LIGHT" )):
            localComponent.setDependencyEnabled("StackLib_Router", True)
        elif ( localComponent.getID() == "COMBINED_INTERFACE" ):
            localComponent.setDependencyEnabled("StackLib_Coordinator", True)
        else:
            print ("Custom Device")
    else:
        localComponent.setDependencyEnabled("StackLib_SuperSet", True)


