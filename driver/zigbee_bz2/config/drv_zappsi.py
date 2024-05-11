"""*****************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""

##################################################################################################
######################### ZigbeeDriver Configurations ############################################
##################################################################################################


################################################################################
################################# Component ####################################
################################################################################
pic32cx_bz2_family = {'PIC32CX1012BZ25048',
                      'PIC32CX1012BZ25032',
                      'PIC32CX1012BZ24032',
                      'WBZ451',
                      'WBZ450',
                      'WBZ451H',
                      }

pic32cx_bz2_hpa_family = {
                      'WBZ451H',
                      }

pic32cx_bz3_family = {'PIC32CX5109BZ31048',
                      'PIC32CX5109BZ31032',
                      'WBZ351',
                      'WBZ350',
                      }

global deviceName
deviceName = Variables.get("__PROCESSOR")

#We get variable suffix from this file
execfile(Module.getPath() + "/config/getDeviceSuffix.py")

def finalizeComponent(zigbeeComponent):
    if (deviceName in pic32cx_bz2_family):
        res = Database.activateComponents(["tc0","pic32cx_bz2_devsupport", "lib_crypto"])
        result = Database.connectDependencies([['ZIGBEE_ZAPPSI', 'Zigbee_WolfCrypt_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])
        result = Database.connectDependencies([['lib_crypto', 'LIB_CRYPTO_WOLFCRYPT_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])
        result = Database.connectDependencies([['ZIGBEE_ZAPPSI', 'TC0_TMR_Zigbee', 'tc0', 'TC0_TMR']])

    elif (deviceName in pic32cx_bz3_family):
        #res = Database.activateComponents(["tcc2","pic32cx_bz3_devsupport"])
        #result = Database.connectDependencies([['ZIGBEE_ZAPPSI', 'TCC2_PWM_Zigbee', 'tcc2', 'TCC2_PWM']])
        res = Database.activateComponents(["tc0","pic32cx_bz3_devsupport"])
        result = Database.connectDependencies([['ZIGBEE_ZAPPSI', 'TC0_TMR_Zigbee', 'tc0', 'TC0_TMR']])

def handleMessage(messageID, args):
    # Log.writeInfoMessage('drv_zigbee_lib:handleMessage ID={} argLen={}'.format(messageID, len(args)))
    ''' This message handler is designed to process messages
        sent from the driver/pic32cx-bz/config/device_support.py
        script.
    '''
    if(messageID == 'ANTENNA_GAIN_CHANGE'):
        component = Database.getComponentByID(args['target'])
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
    print('ZIGBEE ZAppSi Component')
    configName = Variables.get("__CONFIGURATION_NAME")
    print configName

    ############################################################################
    ### Auto Activate and Dependent components
    ############################################################################
    if (deviceName in pic32cx_bz2_family):
      activeComponents = Database.getActiveComponentIDs()
      requiredComponents = ['trng', 'lib_wolfcrypt']
      for r in requiredComponents:
        if r not in activeComponents:
            print("require component '{}' - activating it".format(r))
            res = Database.activateComponents([r])

      remoteComponent = Database.getComponentByID("trng")
      if(remoteComponent):
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
      Database.setSymbolValue("core", "AES_CLOCK_ENABLE", True)
    Database.setSymbolValue("core", "ZIGBEE_CLOCK_ENABLE", True)
    Database.setSymbolValue("core", "CONFIG_SCOM0_HSEN", "DIRECT")

    # Timer Configuration Menu
    if(deviceName in pic32cx_bz2_family):
        timerConfigMenu = drvZigbeeComponent.createMenuSymbol("TIMERCONFIG_MENU", None)
        timerConfigMenu.setLabel("Timer Configuration")
        timerConfigMenu.setVisible(True)


    if( deviceName in pic32cx_bz2_family):
        drvZigbeeComponent.setDependencyEnabled('TCC2_PWM_Zigbee', False) #If bz2, disable TCC2 by default
    elif( deviceName in pic32cx_bz3_family):
        #drvZigbeeComponent.setDependencyEnabled('TC0_TMR_Zigbee', False)
        drvZigbeeComponent.setDependencyEnabled('TCC2_PWM_Zigbee', False)

    global drvComponent # used to pass component to timerconfig.py
    drvComponent = drvZigbeeComponent
#####################################################################################################
#################               TIMER CONFIGURATION                                   ###############
#####################################################################################################
    # Timer Configuration
    execfile(Module.getPath() +"/driver/zigbee" + suffix + "/config/timerconfig.py")

#################################################################
    condAlways                          = [True,                          None,                                        []]
#####################################################################################################
#####################################################################################################

#####################################################################################################
####################################### Code Generation #############################################
#####################################################################################################
#####################################################################################################
##############################  IMPORT INC AND SRC DEFINITIONS ######################################
#####################################################################################################

    zigbeeAppConst = drvZigbeeComponent.createFileSymbol("ZIGBEE_APPCONST_HEADER", None)
    zigbeeAppConst.setSourcePath("/driver/zigbee" + suffix + "/application/ZAppSi/templates/appConsts.h.ftl")
    zigbeeAppConst.setOutputName("appConsts.h")
    zigbeeAppConst.setDestPath("/zigbee/z3device/common/include")
    zigbeeAppConst.setProjectPath("config/" + configName + "/zigbee/z3device/common/include")
    zigbeeAppConst.setType("HEADER")
    zigbeeAppConst.setOverwrite(True)

    # System Definition
    ptcSystemDefFile = drvZigbeeComponent.createFileSymbol("ZIGBEE_SYS_DEF", None)
    ptcSystemDefFile.setType("STRING")
    ptcSystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    ptcSystemDefFile.setSourcePath("driver/zigbee" + suffix + "/application/ZAppSi/templates/system/definitions.h.ftl")
    ptcSystemDefFile.setMarkup(True)

    # FreeRtos Config - Time bring Until Sleep is complete.
    zigbeeFreeRTOSConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_RTOS_HEADER", None)
    zigbeeFreeRTOSConf.setSourcePath("/driver/zigbee" + suffix + "/application/zigbee_only/Zigbee_ZgpSensor_Application/configs/FreeRTOSConfig.h.ftl")
    zigbeeFreeRTOSConf.setOutputName("FreeRTOSConfig.h")
    zigbeeFreeRTOSConf.setDestPath("")
    zigbeeFreeRTOSConf.setProjectPath("config/" + configName)
    zigbeeFreeRTOSConf.setType("HEADER")
    zigbeeFreeRTOSConf.setOverwrite(True)
    zigbeeFreeRTOSConf.setMarkup(True)

    ZAppSiRunnerStackConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__STACKCONF_HEADER", None)
    ZAppSiRunnerStackConf.setSourcePath("/driver/zigbee" + suffix + "/application/ZAppSi/Runner/configs/stackConfig.h")
    ZAppSiRunnerStackConf.setOutputName("stackConfig.h")
    ZAppSiRunnerStackConf.setDestPath("/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerStackConf.setProjectPath("config/" + configName + "/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerStackConf.setType("HEADER")
    ZAppSiRunnerStackConf.setOverwrite(True)
    ZAppSiRunnerStackConf.setMarkup(True)
    
    ZAppSiRunnerAppConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_APPCONF_HEADER", None)
    ZAppSiRunnerAppConf.setSourcePath("/driver/zigbee" + suffix + "/application/ZAppSi/Runner/configs/ZigbeeAppConfig.h")
    ZAppSiRunnerAppConf.setOutputName("ZigbeeAppConfig.h")
    ZAppSiRunnerAppConf.setDestPath("/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerAppConf.setProjectPath("config/" + configName + "/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerAppConf.setType("HEADER")
    ZAppSiRunnerAppConf.setOverwrite(True)
    ZAppSiRunnerAppConf.setMarkup(True)
    
    ZAppSiRunnerPreIncludeConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__PREINCLUDECONF_HEADER", None)
    ZAppSiRunnerPreIncludeConf.setSourcePath("/driver/zigbee" + suffix + "/application/ZAppSi/Runner/configs/bitcloudPreInclude.h")
    ZAppSiRunnerPreIncludeConf.setOutputName("bitcloudPreInclude.h")
    ZAppSiRunnerPreIncludeConf.setDestPath("/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerPreIncludeConf.setProjectPath("config/" + configName + "/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerPreIncludeConf.setType("HEADER")
    ZAppSiRunnerPreIncludeConf.setOverwrite(True)
    ZAppSiRunnerPreIncludeConf.setMarkup(True)
    
    ZAppSiRunnerAppDeviceSelectConf = drvZigbeeComponent.createFileSymbol("ZIGBEE__APPDEVICESELECTCONF_HEADER", None)
    ZAppSiRunnerAppDeviceSelectConf.setSourcePath("/driver/zigbee" + suffix + "/application/ZAppSi/Runner/configs/zigbeeAppDeviceSelect.h")
    ZAppSiRunnerAppDeviceSelectConf.setOutputName("zigbeeAppDeviceSelect.h")
    ZAppSiRunnerAppDeviceSelectConf.setDestPath("/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerAppDeviceSelectConf.setProjectPath("config/" + configName + "/zigbee/ZAppSiRunner_configs")
    ZAppSiRunnerAppDeviceSelectConf.setType("HEADER")
    ZAppSiRunnerAppDeviceSelectConf.setOverwrite(True)
    ZAppSiRunnerAppDeviceSelectConf.setMarkup(True)
 
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
    customAntennaRegion.setValue('none')

    #global zappsiSleepSupportedDevice
    zappsiSleepSupportedDevice = drvZigbeeComponent.createBooleanSymbol("SLEEP_SUPPORTED_DEVICE", None)
    zappsiSleepSupportedDevice.setVisible(False)
    zappsiSleepSupportedDevice.setDefaultValue(False)

    #global deviceDeepSleepenabled1
    deviceDeepSleepenabled1 = drvZigbeeComponent.createBooleanSymbol('DEVICE_DEEP_SLEEP_ENABLED', None)
    deviceDeepSleepenabled1.setVisible(False)
    deviceDeepSleepenabled1.setDefaultValue(False)
    
    global BZ2HPASymbol
    BZ2HPASymbol = drvZigbeeComponent.createBooleanSymbol("PIC32CXBZ2_HPA", None)
    BZ2HPASymbol.setDefaultValue(False)
    BZ2HPASymbol.setVisible(False)
    
    if (deviceName in pic32cx_bz2_hpa_family):
      BZ2HPASymbol.setDefaultValue(True)

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
        zigbeeInit[n].setSourcePath('driver/zigbee' + suffix + '/templates/system/' + f)
        zigbeeInit[n].setMarkup(True)
        print('{} file: {} pos: {}'.format(n, f, p))
        n = n + 1

    ######################    hal appTimer.c file    ######################
    
    # Add appTimer.c - generated file
    appTimerSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    appTimerSourceFile.setSourcePath('driver/zigbee' + suffix + '/templates/appTimer.c.ftl')
    appTimerSourceFile.setOutputName('appTimer.c')
    appTimerSourceFile.setOverwrite(True)
    appTimerSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/common/src/')
    appTimerSourceFile.setProjectPath('/config/default/zigbee/systemresource/hal/cortexm4/common/src/')
    appTimerSourceFile.setType('SOURCE')
    appTimerSourceFile.setEnabled(True)
    appTimerSourceFile.setMarkup(True)
    
    ###############  app_zigbee.c app_zigbee.h files ######################
    # Add app_zigbee.c - generated file
    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee' + suffix + '/templates/zigbee_app_source.c.ftl')
    app_zgbSourceFile.setOutputName('app_zigbee.c')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('../../app_zigbee/')
    app_zgbSourceFile.setProjectPath('app_zigbee')
    app_zgbSourceFile.setType('SOURCE')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    app_zgbSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbSourceFile.setSourcePath('driver/zigbee' + suffix + '/application/ZAppSi/templates/pic32cxBSP.h.ftl')
    app_zgbSourceFile.setOutputName('pic32cxBSP.h')
    app_zgbSourceFile.setOverwrite(True)
    app_zgbSourceFile.setDestPath('/zigbee/z3device/common/include/')
    app_zgbSourceFile.setProjectPath('config/' + configName + '/zigbee/z3device/common/include/')
    app_zgbSourceFile.setType('HEADER')
    app_zgbSourceFile.setEnabled(True)
    app_zgbSourceFile.setMarkup(True)

    # Add app_uart.c - generated file
    app_uartSourceFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_uartSourceFile.setSourcePath('driver/zigbee' + suffix + '/templates/app_uart.c.ftl')
    app_uartSourceFile.setOutputName('app_uart.c')
    app_uartSourceFile.setOverwrite(True)
    app_uartSourceFile.setDestPath('../../app_zigbee/')
    app_uartSourceFile.setProjectPath('app_zigbee/zigbee_console/')
    app_uartSourceFile.setType('SOURCE')
    app_uartSourceFile.setEnabled(True)
    app_uartSourceFile.setMarkup(True)
    #app_uartSourceFile.setDependencies(isConsoleEnabled, ["APP_ENABLE_CONSOLE"])

    # Add app_zigbee.h - static file
    app_zgbHeaderFile = drvZigbeeComponent.createFileSymbol(None, None)
    app_zgbHeaderFile.setSourcePath('driver/zigbee' + suffix + '/templates/zigbee_app_header.h.ftl')
    app_zgbHeaderFile.setOutputName('app_zigbee.h')
    app_zgbHeaderFile.setOverwrite(True)
    app_zgbHeaderFile.setDestPath('../../app_zigbee/')
    app_zgbHeaderFile.setProjectPath('app_zigbee')
    app_zgbHeaderFile.setType('HEADER')
    app_zgbHeaderFile.setEnabled(True)

    app_consolecommonHFile2 = drvZigbeeComponent.createFileSymbol(None, None)
    app_consolecommonHFile2.setSourcePath('driver/zigbee' + suffix + '/templates/cluster/console/console.h.ftl')
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
        # ['mac_phy/include/rfInit.h',               condAlways],
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
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdMem.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdBatMonHandler.h',          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdCalibHandler.h',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdEdHandler.h',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdEncryptHandler.h',         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdFrameRoutine.h',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdHandlerCtrl.h',            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdManager.h',                condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdMemAccess.h',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRegAccessHandler.h',       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdResetHandler.h',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRndHandler.h',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRxBuffer.h',               condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdRxFrameHandler.h',         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdSetHandler.h',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTrxCtrl.h',                condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTrxHandler.h',             condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include/machwdTxFrameHandler.h',         condAlways],

        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyBatMon.h',                        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyCalib.h',                         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyAntDiversity.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDeepSleep.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyEd.h',                            condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyEncrypt.h',                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRxFrame.h',                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRxTxIndicator.h',                 condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySetTrxState.h',                   condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyStateMachine.h',                  condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/at86rf233.h',                        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyPic32cx.h',                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyCommon.h',                        condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyDataStatus.h',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyInit.h',                          condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMem.h',                           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyMemAccess.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRtimerIrqDispatcher.h',           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyTxFrame.h',                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyTxPowerConverter.h',              condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRegAccess.h',                     condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyReset.h',                         condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRfSpiProto.h',                    condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyRnd.h',                           condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phySet.h',                           condAlways],


        ['mac_phy/mac_hwi/include/machwiAssociateHandler.h',                               condAlways],
        ['mac_phy/mac_hwi/include/machwiDisassociateHandler.h',                            condAlways],
        ['mac_phy/mac_hwi/include/machwiHwdReqMemPool.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiManager.h',                                        condAlways],
        ['mac_phy/mac_hwi/include/machwiMem.h',                                            condAlways],
        ['mac_phy/mac_hwi/include/machwiPollHandler.h',                                    condAlways],
        ['mac_phy/mac_hwi/include/machwiScanHandler.h',                                    condAlways],
        ['mac_phy/mac_hwi/include/machwiStartHandler.h',                                   condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionHandler.h',                             condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionQueue.h',                               condAlways],
        ['mac_phy/mac_hwi/include/machwiBeaconHandler.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiDataHandler.h',                                    condAlways],
        ['mac_phy/mac_hwi/include/machwiOrphanHandler.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiPanIdConflictHandler.h',                           condAlways],
        ['mac_phy/mac_hwi/include/machwiPanServer.h',                                      condAlways],
        ['mac_phy/mac_hwi/include/machwiPurgeHandler.h',                                   condAlways],
        ['mac_phy/mac_hwi/include/machwiResetHandler.h',                                   condAlways],
        ['mac_phy/mac_hwi/include/machwiRxEnableHandler.h',                                condAlways],
        ['mac_phy/mac_hwi/include/machwiSetGetHandler.h',                                  condAlways],
        ['mac_phy/mac_hwi/include/machwiSwitchRxCtrl.h',                                   condAlways],
        ['mac_phy/mac_hwi/include/machwiTransactionHash.h',                                condAlways],
        ['mac_phy/mac_hwi/include/machwiMemAccess.h',                                      condAlways],
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
        ['security/TrustCentre/include/tcKeyUpdate.h',                      condAlways],
        ['security/TrustCentre/include/tcRemove.h',                         condAlways],
        ['security/TrustCentre/include/tcReset.h',                          condAlways],
        ['security/TrustCentre/include/tcKeyEstablish.h',                   condAlways],
        ['security/TrustCentre/include/tcDeviceTableCtrl.h',                condAlways],
        ['security/TrustCentre/include/tcPermissions.h',                    condAlways],
        ['security/serviceprovider/include/private/sspHashHandler.h',       condAlways],
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
        #['hal/cortexm4/pic32cx_bz2/include/hal_aes_sync.h',          condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/halAppClock.h',           condAlways],
		['hal/cortexm4/pic32cx_bz2/include/halAppClock.h',           condAlways],
        ['hal/cortexm4/pic32cx_bz2/include/halAssert.h',             condAlways],
        ['hal/cortexm4/pic32cx_bz2/include/halDbg.h',                condAlways],
        ['hal/cortexm4/pic32cx_bz2/include/halDiagnostic.h',         condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/halFlash.h',              condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/halMacIsr.h',             condAlways],
		['hal/cortexm4/pic32cx_bz2/include/halMacIsr.h',             condAlways],
        ['hal/cortexm4/pic32cx_bz2/include/halRfCtrl.h',             condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/halSleep.h',              condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/halSleepTimerClock.h',    condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/hpl_aes.h',               condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/hpl_aes_sync.h',          condAlways],
        #['hal/cortexm4/pic32cx_bz2/include/hri_aes_e54.h',           condAlways],
        ['hal/cortexm4/pic32cx_bz2/include/halAes.h',                condAlways],
        # ['hal/cortexm4/pic32cx_bz2/include/Pic32cx_Miscellaneous.h', condAlways],
    ]
    
    zdrvStackHALCommonIncFiles = [
        ['hal/include/atomic.h',                                 condAlways],
        ['hal/include/bcTimer.h',                                condAlways],
        ['hal/include/appTimer.h',                               condAlways],
        # ['hal/include/eeprom.h',                                 condAlways],
        #['hal/include/flash.h',                                  condAlways],
        ['hal/include/halTaskManager.h',                         condAlways],
        ['hal/include/sleep.h',                                  condAlways],
        #['hal/include/sleepTimer.h',                             condAlways],
        ['hal/include/statStack.h',                              condAlways],
    ]

    zdrvStackBZ3HALIncFiles = [
        #['hal/cortexm4/pic32cx_bz3/include/hal_aes_sync.h',          condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halAppClock.h',           condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halAssert.h',             condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halDbg.h',                condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halDiagnostic.h',         condAlways],
        #['hal/cortexm4/pic32cx_bz3/include/halFlash.h',              condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halMacIsr.h',             condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halRfCtrl.h',             condAlways],
        #['hal/cortexm4/pic32cx_bz3/include/halSleep.h',              condAlways],
        #['hal/cortexm4/pic32cx_bz3/include/halSleepTimerClock.h',    condAlways],
        #['hal/cortexm4/pic32cx_bz3/include/hpl_aes.h',               condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halTrng.h',               condAlways],
        #['hal/cortexm4/pic32cx_bz3/include/hri_aes_e54.h',           condAlways],
        ['hal/cortexm4/pic32cx_bz3/include/halAes.h',                condAlways],
        # ['hal/cortexm4/pic32cx_bz3/include/Pic32cx_Miscellaneous.h', condAlways],
    ]

    zdrvStackBZ3HALCommonIncFiles = [
        ['hal/include/atomic.h',                                 condAlways],
        ['hal/include/bcTimer.h',                                condAlways],
        ['hal/include/appTimer.h',                               condAlways],
        # ['hal/include/eeprom.h',                                 condAlways],
        #['hal/include/flash.h',                                  condAlways],
        ['hal/include/halTaskManager.h',                         condAlways],
        ['hal/include/sleep.h',                                  condAlways],
        #['hal/include/sleepTimer.h',                             condAlways],
        ['hal/include/statStack.h',                              condAlways],
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
        # ['zcl/include/private/zclDbg.h',                       condAlways],
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
        ['ZGP/GPInfrastructure/highZgp/include/zgpCluster.h',                    condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/zgpClusterStructure.h',           condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/zgpClusterZclInterface.h',        condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/zgpInfraDevice.h',                condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/zgpMiddleProxy.h',                condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterClient.h',      condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterGeneric.h',     condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpClusterServer.h',      condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpHighGeneric.h',        condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpHighMem.h',            condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpProxyBasic.h',         condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpProxyTable.h',         condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpSinkBasic.h',          condAlways],
        ['ZGP/GPInfrastructure/highZgp/include/private/zgpSinkTable.h',          condAlways],
        
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLow.h',                         condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowGpdf.h',                     condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowNvmTable.h',                 condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/zgpLowMiddleProxy.h',              condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpCstub.h',               condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpDstub.h',               condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowGeneric.h',          condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowMem.h',              condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowProxy.h',            condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpLowSink.h',             condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpNvmTable.h',            condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpNvmTableBindings.h',    condAlways],
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpPacket.h',              condAlways], 
        ['ZGP/GPInfrastructure/lowZgp/include/private/zgpTaskManager.h',         condAlways],

        ['ZGP/include/zgpCommon.h',                                              condAlways],
        ['ZGP/include/zgpDbg.h',                                                 condAlways],
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

    if (deviceName in pic32cx_bz3_family):
      for incFileEntry in zdrvStackBZ3HALCommonIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)
        
      incPathSym = drvZigbeeComponent.createSettingSymbol('SILEX_PATH_INCLUDE_PATH', None)
      incPathSym.setValue('../src/config/default/driver/security' + ';')
      incPathSym.setCategory('C32')
      incPathSym.setKey('extra-include-directories')
      incPathSym.setAppend(True, ';')
      incPathSym.setEnabled(True)
    else:
      for incFileEntry in zdrvStackHALCommonIncFiles:
        importIncFile(drvZigbeeComponent, configName, incFileEntry)
        
    if (deviceName in pic32cx_bz3_family):
      for incFileEntry in zdrvStackBZ3HALIncFiles:
        importHalIncFile(drvZigbeeComponent, configName, incFileEntry)
    else:
      for incFileEntry in zdrvStackHALIncFiles:
        importHalIncFile(drvZigbeeComponent, configName, incFileEntry)

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
        ['application/zigbee_only/Zigbee_Device_Application/common/include/app_zigbee.h',               condAlways],
        ['application/zigbee_only/Zigbee_Device_Application/clusters/include/haClusters.h',             condAlways],
        # ['application/zigbee_only/Zigbee_Device_Application/common/include/appConsts.h',                       condAlways],
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

    driversIncFiles = [
        ['drivers/PersistDataServer/wl/include/wlPdsBindings.h',                    condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Bindings.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Init.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Stack_Ids.h',              condAlways],
    ]

    applicationCommonIncFiles = [
         ['application/ZAppSi/common/include/bufferallocator.h',                                           condAlways],
         ['application/ZAppSi/common/include/ZAppSiCommands.h',                                            condAlways],
         ['application/ZAppSi/common/include/ZAppSiHost.h',                                                condAlways],
         ['application/ZAppSi/common/include/ZAppSiSerialManager.h',                                       condAlways],
         ['application/ZAppSi/common/include/private/consts.h',                                            condAlways],
         ['application/ZAppSi/common/include/private/serialManagerPC.h',                                   condAlways],
         ['application/ZAppSi/common/include/private/ZAppSiDataTemplates.h',                               condAlways],
         ['application/ZAppSi/common/include/private/ZAppSiIdentifiers.h',                               condAlways],

         ['application/ZAppSi/Runner/clusters/include/basicCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/clusters/include/colorControlCluster.h',                        condAlways],
         ['application/ZAppSi/Runner/clusters/include/commissioningCluster.h',                       condAlways],
         # ['application/ZAppSi/Runner/clusters/include/haClusters.h',                                 condAlways],
         ['application/ZAppSi/Runner/clusters/include/levelControlCluster.h',                        condAlways],
         ['application/ZAppSi/Runner/clusters/include/onOffCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/clusters/include/scenesCluster.h',                              condAlways],

         ['application/ZAppSi/Runner/include/rZdo.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rZcl.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rTypes.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rTimer.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rTimeCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rTc.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rSys.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rScenesCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rPriceCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rParser.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rOtauCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rNwk.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rMessageCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rMem.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rMac.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rInterpan.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rIdentifyCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rHal.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rGroupsCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rGenericTunnelCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rExtensions.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rEvents.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rDebug.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rBdb.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rBACnetProtocolTunnelCluster.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rAux.h',                               condAlways],
         ['application/ZAppSi/Runner/include/rAps.h',                               condAlways],



         # ['application/ZAppSi/Runner/configs/zigbeeAppConfig.h',                                     condAlways],
         # ['application/ZAppSi/Runner/configs/zigbeeAppDeviceSelect.h',                               condAlways],
         # ['application/ZAppSi/Runner/configs/stackConfig.h',                                         condAlways],
         # ['application/ZAppSi/Runner/configs/bitcloudPreInclude.h',                                  condAlways],
         # ['application/ZAppSi/Runner/configs/Zigbee_AllDevice_Makerules.h',                          condAlways],
    ]

    commonFiles = [
        ['application/ZAppSi/z3commonfiles/include/printLcd.h',                                            condAlways],
        ['application/ZAppSi/z3commonfiles/include/errH.h',                                                condAlways],
        ['application/ZAppSi/z3commonfiles/include/console.h',                                             condAlways],
    ]
    zgbWrappersIncFiles = [
        ['application/ZAppSi/stack_Interface/bdb/include/BDB_Unpack.h',                      condAlways],
        ['application/ZAppSi/stack_Interface/configserver/include/CS_Unpack.h',              condAlways],
        ['application/ZAppSi/stack_Interface/nwk/include/NWK_Unpack.h',                      condAlways],
        ['application/ZAppSi/stack_Interface/zcl/include/ZCL_Unpack.h',                      condAlways],
        ['application/ZAppSi/stack_Interface/zdo/include/ZDO_Unpack.h',                      condAlways],
        ['application/ZAppSi/stack_Interface/zgb_api.h',                             condAlways],
        ['application/ZAppSi/stack_Interface/bdb/include/bdb_api.h',                     condAlways],
        ['application/ZAppSi/stack_Interface/configServer/include/cs_api.h',                      condAlways],
        ['application/ZAppSi/stack_Interface/nwk/include/nwk_api.h',                             condAlways],
        ['application/ZAppSi/stack_Interface/zcl/include/zcl_api.h',                             condAlways],
        ['application/ZAppSi/stack_Interface/zdo/include/zdo_api.h',                             condAlways],
    ]

    for incFileEntry in clusterCommonIncFiles:
        importIncFileNonStackNew(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in zgbWrappersIncFiles:
        importIncFileNonStackWrapper(drvZigbeeComponent, configName, incFileEntry)

    for incFileEntry in applicationCommonIncFiles:
        importIncFileNonStack(drvZigbeeComponent, configName, incFileEntry)
        
    for incFileEntry in commonFiles:
        importIncFileNonStackNew(drvZigbeeComponent, configName, incFileEntry)   
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
        ['zcl/clusters/src/scenes.c',                    condAlways],
    ]

    zdrvStackHALSrcFiles = [
        ['hal/cortexm4/pic32cx_bz2/src/atomic.c',                 condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halAppClock.c',            condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halMacIsr.c',              condAlways],
        ['hal/cortexm4/pic32cx_bz2/src/halRfCtrl.c',              condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halSleep.c',               condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halSleepTimerClock.c',     condAlways],
        ['hal/cortexm4/pic32cx_bz2/src/halAes.c',                 condAlways],
    ]

    zdrvStackHALCommonSrcFiles = [
        #['hal/cortexm4/common/src/appTimer.c',                condAlways],
        ['hal/cortexm4/common/src/halTaskManager.c',          condAlways],
        #['hal/cortexm4/common/src/sleep.c',                   condAlways],
        #['hal/cortexm4/common/src/sleepTimer.c',              condAlways],
        ['hal/cortexm4/common/src/statStack.c',               condAlways],
        ['hal/cortexm4/common/src/timer.c',                   condAlways],
     ]
     
    zdrvStackBZ3HALSrcFiles = [
        ['hal/cortexm4/pic32cx_bz3/src/atomic.c',                 condAlways],
        #['hal/cortexm4/pic32cx_bz3/src/hal_aes_sync.c',           condAlways],
        ['hal/cortexm4/pic32cx_bz3/src/halAppClock.c',            condAlways],
        #['hal/cortexm4/pic32cx_bz3/src/halFlash.c',               condAlways],
        ['hal/cortexm4/pic32cx_bz3/src/halMacIsr.c',              condAlways],
        ['hal/cortexm4/pic32cx_bz3/src/halRfCtrl.c',              condAlways],
        #['hal/cortexm4/pic32cx_bz3/src/halSleep.c',               condAlways],
        #['hal/cortexm4/pic32cx_bz3/src/halSleepTimerClock.c',     condAlways],
        ['hal/cortexm4/pic32cx_bz3/src/halTrng.c',                condAlways],
        ['hal/cortexm4/pic32cx_bz3/src/halAes.c',                 condAlways],
    ]
    
    zdrvStackBZ3HALCommonSrcFiles = [
        #['hal/cortexm4/common/src/appTimer.c',                condAlways],
        ##['hal/cortexm4/common/src/flash.c',                   condAlways],
        ['hal/cortexm4/common/src/halTaskManager.c',          condAlways],
        #['hal/cortexm4/common/src/sleep.c',                   condAlways],
        #['hal/cortexm4/common/src/sleepTimer.c',              condAlways],
        ['hal/cortexm4/common/src/statStack.c',               condAlways],
        ['hal/cortexm4/common/src/timer.c',                   condAlways],
    ]

    zdrvStackZLLSrcFiles = [
       ['zllplatform/infrastructure/N_Util/src/N_Util.c',          condAlways],
    ]

    zdrvStackPDSSrcFiles = [
        ['pds/src/bcPDS.c',                       condAlways],
        ['pds/src/wlPdsTypesConverter.c',                       condAlways],

    ]
    
    zdrvBSPSrcFiles = [
        ['bsp/PIC32CX/src/fakeBSP.c',                                     condAlways],
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

    if (deviceName in pic32cx_bz3_family):
      for srcFileEntry in zdrvStackBZ3HALSrcFiles:
        importSrcHalFile(drvZigbeeComponent, configName, srcFileEntry)
    else:
      for srcFileEntry in zdrvStackHALSrcFiles:
        importSrcHalFile(drvZigbeeComponent, configName, srcFileEntry)
        
    if (deviceName in pic32cx_bz3_family):
      for srcFileEntry in zdrvStackBZ3HALCommonSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)
    else:
      for srcFileEntry in zdrvStackHALCommonSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)    

    for srcFileEntry in zdrvStackZLLSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvStackPDSSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zdrvBSPSrcFiles:
        importSrcFile(drvZigbeeComponent, configName, srcFileEntry)


    utilsSrcFiles = [
    ]

    driversSrcFiles = [
    ]

    zgbWrappersSrcFiles = [
        ['application/ZAppSi/stack_Interface/bdb/BDB_Unpack.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/configserver/CS_Unpack.c',              condAlways],
        ['application/ZAppSi/stack_Interface/nwk/NWK_Unpack.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/zcl/ZCL_Unpack.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/zdo/ZDO_Unpack.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/bdb/BDB_API.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/configServer/CS_API.c',                       condAlways],
        ['application/ZAppSi/stack_Interface/nwk/NWK_API.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/zcl/ZCL_API.c',                      condAlways],
        ['application/ZAppSi/stack_Interface/zdo/ZDO_API.c',                      condAlways],
    ]

    applicationCommonFiles = [
         ['application/ZAppSi/z3commonfiles/src/zigbee_init.c',                                    condAlways],
    ]
    applicationCommonSrcFiles = [

         ['application/ZAppSi/common/src/bufferallocator.c',                                           condAlways],
         ['application/ZAppSi/common/src/pccomAdapter.c',                                              condAlways],    
         ['application/ZAppSi/common/src/usartAdapter.c',                                              condAlways],
         #['application/ZAppSi/common/src/spiAdapter.c',                                                condAlways],

         ['application/ZAppSi/Runner/src/eccAux.c',                                              condAlways],
         ['application/ZAppSi/Runner/src/rAps.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rAux.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rBdb.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rDebug.c',                                              condAlways],
         ['application/ZAppSi/Runner/src/rEvents.c',                                             condAlways],
         ['application/ZAppSi/Runner/src/rExtensions.c',                                         condAlways],
         ['application/ZAppSi/Runner/src/rGroupsCluster.c',                                      condAlways],
         ['application/ZAppSi/Runner/src/rHal.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rIdentifyCluster.c',                                    condAlways],
         ['application/ZAppSi/Runner/src/rInterpan.c',                                           condAlways],
         ['application/ZAppSi/Runner/src/rMac.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rMain.c',                                               condAlways],
         ['application/ZAppSi/Runner/src/rMem.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rMessageCluster.c',                                     condAlways],
         ['application/ZAppSi/Runner/src/rNwk.c',                                                condAlways],
         # ['application/ZAppSi/Runner/src/rOSAL.c',                                               condAlways],
         ['application/ZAppSi/Runner/src/rParser.c',                                             condAlways],
         ['application/ZAppSi/Runner/src/rPriceCluster.c',                                       condAlways],
         ['application/ZAppSi/Runner/src/rScenesCluster.c',                                      condAlways],
         ['application/ZAppSi/Runner/src/rSys.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rTc.c',                                                 condAlways],
         ['application/ZAppSi/Runner/src/rTimeCluster.c',                                        condAlways],
         ['application/ZAppSi/Runner/src/rTimer.c',                                              condAlways],
         ['application/ZAppSi/Runner/src/rZcl.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rZdo.c',                                                condAlways],
         ['application/ZAppSi/Runner/src/rGenericTunnelCluster.c',                               condAlways],
         ['application/ZAppSi/Runner/src/rOtauCluster.c',                                        condAlways],
         ['application/ZAppSi/Runner/src/rBACnetProtocolTunnelCluster.c',                        condAlways],

         ['application/ZAppSi/Runner/clusters/src/groupsClusterfake.c',                          condAlways],
         # ['application/ZAppSi/Runner/clusters/src/haClusters.c',                                 condAlways],
         ['application/ZAppSi/Runner/clusters/src/identifyClusterfake.c',                        condAlways],
         ['application/ZAppSi/Runner/common/src/zgb_task.c',                                     condAlways],
         ['application/ZAppSi/Runner/common/src/console.c',                                      condAlways],
         ['application/ZAppSi/Runner/common/src/zgb_app_callback.c',                             condAlways],


    ]

    for srcFileEntry in driversSrcFiles:
        importSrcFileNonStack(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in zgbWrappersSrcFiles:
        importSrcFileNonStackWrapper(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationCommonSrcFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)

    for srcFileEntry in applicationCommonFiles:
        importSrcFileNonStackNew(drvZigbeeComponent, configName, srcFileEntry)
  
    zigbeeStackdrvIncPaths = [
        ['/src/Components',                                                    condAlways],
        ['/src/Components/hal',                                                    condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application',                   condAlways], 
        ['/zigbee/application/ZAppSi/Runner/include',                   condAlways], 
        ['/zigbee/application/ZAppSi/Runner/clusters/include',                   condAlways], 
        ['/zigbee/application/ZAppSi/Runner/common/include',                   condAlways], 
        ['/zigbee/application/ZAppSi/common/include',                   condAlways],
        ['/zigbee/application/ZAppSi/common/include/private',                   condAlways],
        ['/application/zigbee_only/Zigbee_Device_Application/configs',                                     condAlways],
        ['/zigbee/ZAppSi/z3commonfiles/include',                                     condAlways],
        ['/zigbee/ZAppSi/Runner/include',                                     condAlways],
        ['/zigbee/ZAppSi/Runner/include/private',                                     condAlways],
        ['/zigbee/ZAppSi/common/include/private',                                     condAlways],
        ['/zigbee/ZAppSi/common/include',                                     condAlways],
        ['/zigbee/ZAppSi',                                     condAlways],
        ['/zigbee',                                     condAlways],
        ['/peripheral',                                                                                    condAlways],
        ['/driver/pds/include',                                                                            condAlways],
        ['/zigbee/drivers/sercom/usart',                                          condAlways],
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

    # Setting the required heap size for the application
    Database.sendMessage("core", "HEAP_SIZE", {"heap_size":4096})

    preprocessorLD = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD3', None)
    preprocessorLD.setValue('1024')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('stack-size')
    preprocessorLD.setEnabled(True)

    preprocessorAS = drvZigbeeComponent.createSettingSymbol('ZIGBEE_PREPRECESSOR_AS', None)
    if (deviceName in pic32cx_bz2_family):
        preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;_USE_LIB_;_SUPER_SET_LIB_;HAL_USE_FLASH_ACCESS;ZIGBEE_ZAPPSI;_RUNNER_OSAL_')
    elif (deviceName in pic32cx_bz3_family):
        preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;_USE_LIB_;_SUPER_SET_LIB_;HAL_USE_FLASH_ACCESS;ZIGBEE_ZAPPSI;_RUNNER_OSAL_;PLATFORM_PIC32CXBZ3')
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


################################### Library File ####################################################
    ZAppSiRunnerMakeRulesFile = drvZigbeeComponent.createFileSymbol("ZIGBEE_MAKERULE_HEADER", None)
    if (deviceName in pic32cx_bz2_family):
      ZAppSiRunnerMakeRulesFile.setSourcePath("/driver/zigbee" + suffix + "/templates/Zigbee_AllDevice_Makerules.h.ftl")
    elif (deviceName in pic32cx_bz3_family):
      ZAppSiRunnerMakeRulesFile.setSourcePath("/driver/zigbee" + suffix + "/templates/Zigbee_AllDevice_Makerules_Bz3.h.ftl")
    ZAppSiRunnerMakeRulesFile.setOutputName("Zigbee_AllDevice_Makerules.h")
    ZAppSiRunnerMakeRulesFile.setDestPath('/zigbee/lib/')
    ZAppSiRunnerMakeRulesFile.setProjectPath("config/" + configName + "/zigbee/lib/")
    ZAppSiRunnerMakeRulesFile.setType("HEADER")
    ZAppSiRunnerMakeRulesFile.setOverwrite(True)
    ZAppSiRunnerMakeRulesFile.setMarkup(True)
    
    setAdditionaloptionXC32GCC = drvZigbeeComponent.createSettingSymbol('SET_XC32_GCC_ADD_INC_LIB', None)
    setAdditionaloptionXC32GCC.setValue('-include"lib/Zigbee_AllDevice_Makerules.h"')
    setAdditionaloptionXC32GCC.setCategory('C32')
    setAdditionaloptionXC32GCC.setKey('appendMe')
    setAdditionaloptionXC32GCC.setEnabled(True)

    zigbeeLibFile = drvZigbeeComponent.createLibrarySymbol("ZB_LIB_FILE", None)
    zigbeeLibFile.setDestPath('/zigbee/lib/')
    if (deviceName in pic32cx_bz2_family):
      zigbeeLibFile.setSourcePath("/driver/zigbee" + suffix + "/src/lib/Zigbee_AllDevice_Bz2_Lib.a")
    elif (deviceName in pic32cx_bz3_family):
      zigbeeLibFile.setSourcePath("/driver/zigbee" + suffix + "/src/lib/Zigbee_AllDevice_Bz3_Lib.a")
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
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/src/Components/' + secSName + '/' + incFile)
    incFileSym.setOutputName(incFile)
    incFileSym.setDestPath('/zigbee/lib/inc/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/zigbee/lib/inc/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importHalIncFile(component, configName, incFileEntry, firmwarePath = None):
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
    setDestPath = '/zigbee/lib/inc/' + secDName
    setNewDestPathL = setDestPath.rsplit('/',3)[0]
    setNewDestPathRSplit = setDestPath.rsplit('/',2)
    setNewDestPathREnd = setNewDestPathRSplit[1]
    setNewDestPathR = setNewDestPathREnd.rsplit('/', 1)[-1]

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/src/Components/' + secSName + '/' + incFile)
    incFileSym.setOutputName(incFile)
    incFileSym.setDestPath(setNewDestPathL + '/pic32cx/' + setNewDestPathR + '/')
    incFileSym.setProjectPath('config/' + configName + setNewDestPathL + '/pic32cx/' + setNewDestPathR + '/')
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
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_Device_Application','z3device')
    secSname = secDName.replace('application/ZAppSi', 'ZAppSi')
    secDName = secTname.replace('common_files','common_files')
    secDName = secSname.replace('stack_Interface','stack_Interface')
    #secDName = secTName


    incFileSym.setDestPath('/zigbee/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/zigbee/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)
        
def importIncFileNonStackNew(component, configName, incFileEntry, firmwarePath = None):
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
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/Zigbee_Device_Application','z3device')
    secSname = secDName.replace('application/ZAppSi', 'ZAppSi')
    secDName = secSname.replace('z3commonfiles', 'z3commonfiles')
    secDName = secSname.replace('stack_Interface','stack_Interface')
    #secDName = secTName


    incFileSym.setDestPath('/zigbee/' + secDName + '')
    incFileSym.setProjectPath('config/' + configName + '/zigbee/'+ secDName + '')
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importIncFileNonStackWrapper(component, configName, incFileEntry, firmwarePath = None):
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
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/Zigbee_Device_Application','z3device')
    secSname = secDName.replace('application/ZAppSi', 'z3device')
    secDName = secSname.replace('stack_Interface','stack_Interface')
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
    incFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + incFile)
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
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + srcFile)
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
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + srcFile)
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
    secTname = secDName.replace('application','z3device')
    secTname = secDName.replace('Zigbee_Device_Application','z3device')
    secDName = secTname.replace('common_files','common_files')
    secDName = secSName.replace('stack_Interface','stack_Interface')
    #secDName = secTName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + srcFile)
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
    secDName = secTname.replace('application/zigbee_only/Zigbee_Device_Application','z3device')
    secSname = secDName.replace('application/ZAppSi', 'ZAppSi')
    secDName = secSname.replace('z3commonfiles', 'z3commonfiles')
    secDName = secSname.replace('stack_Interface','stack_Interface')
    #secDName = secTName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/' + secDName+  '/')
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def importSrcFileNonStackWrapper(component, configName, srcFileEntry, firmwarePath = None):
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
    secDName = secTname.replace('application/zigbee_only/Zigbee_Device_Application','z3device')
    secSname = secDName.replace('application/ZAppSi', 'z3device')
    secDName = secSname.replace('stack_Interface','stack_Interface')
    #secDName = secTName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/' + secDName+  '/')
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
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/src/Components/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('/zigbee/systemresource/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/zigbee/systemresource/' + secDName)
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def importSrcHalFile(component, configName, srcFileEntry, firmwarePath = None):
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
    setDestPath = '/zigbee/systemresource/' + secDName
    setNewDestPathL = setDestPath.rsplit('/',3)[0]
    setNewDestPathRSplit = setDestPath.rsplit('/',2)
    setNewDestPathREnd = setNewDestPathRSplit[1]
    setNewDestPathR = setNewDestPathREnd.rsplit('/', 1)[-1]

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/zigbee' + suffix + '/src/Components/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath(setNewDestPathL + '/pic32cx/' + setNewDestPathR + '/')
    srcFileSym.setProjectPath('config/' + configName + setNewDestPathL + '/pic32cx/' + setNewDestPathR + '/')
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
    # incPath = incPath.replace('application','zigbee')
    incPath = incPath.replace('Zigbee_Device_Application','z3device')
    incPath = incPath.replace('/Components/hal','/zigbee/lib/inc/hal/cortexm4/pic32cx/include')
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

    if (connectID == "Zigbee_USART"):
        # appConfigEnableConsole.setValue(True)
        Database.setSymbolValue("drv_usart", "DRV_USART_COMMON_MODE", "Asynchronous")
        if (deviceName in pic32cx_bz2_family):
          Database.sendMessage("pic32cx_bz2_devsupport", "CONSOLE_ENABLE", {"isEnabled":True})
        elif (deviceName in pic32cx_bz3_family):
          Database.sendMessage("pic32cx_bz3_devsupport", "CONSOLE_ENABLE", {"isEnabled":True})
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

def onAttachmentDisconnected(source, target):

    localComponent = source["component"]
    remoteComponent = target["component"]
    remoteID = remoteComponent.getID()
    connectID = source["id"]
    targetID = target["id"]

    if (connectID == "Zigbee_USART"):
        # appConfigEnableConsole.setValue(False)
        if (deviceName in pic32cx_bz2_family):
          Database.sendMessage("pic32cx_bz2_devsupport", "CONSOLE_ENABLE", {"isEnabled":False})
        elif (deviceName in pic32cx_bz3_family):
          Database.sendMessage("pic32cx_bz3_devsupport", "CONSOLE_ENABLE", {"isEnabled":False})
        print("setting ENABLE CONSOLE in application Configuration as False Since DRV_USART is disconnected")
