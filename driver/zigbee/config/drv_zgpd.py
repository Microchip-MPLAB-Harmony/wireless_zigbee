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
######################### MacTester Configurations ############################################
##################################################################################################


################################################################################
################################# Component ####################################
################################################################################
pic32cx_bz2_family = {'PIC32CX1012BZ25048',
                      'PIC32CX1012BZ25032',
                      'PIC32CX1012BZ24032',
                      'WBZ451',
                      'WBZ450',
                      }

pic32cx_bz3_family = {'PIC32CX5109BZ31048',
                      'PIC32CX5109BZ31032',
                      'WBZ351',
                      'WBZ350',
                      }

global deviceName
deviceName = Variables.get("__PROCESSOR")

def finalizeComponent(drvzgpdevice):
    if (deviceName in pic32cx_bz2_family):
        res = Database.activateComponents(["tc0","pic32cx_bz2_devsupport", "lib_crypto"])
        #res = Database.activateComponents(["tc0","pic32cx_bz2_devsupport"])
        result = Database.connectDependencies([[drvzgpdevice.getID(), 'Zigbee_WolfCrypt_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])
        result = Database.connectDependencies([['lib_crypto', 'LIB_CRYPTO_WOLFCRYPT_Dependency', 'lib_wolfcrypt', 'lib_wolfcrypt']])
        result = Database.connectDependencies([[drvzgpdevice.getID(), 'TC0_TMR_Zigbee', 'tc0', 'TC0_TMR']])

    elif (deviceName in pic32cx_bz3_family):
        #res = Database.activateComponents(["tcc2","pic32cx_bz3_devsupport"])
        #result = Database.connectDependencies([[drvzgpdevice.getID(), 'TCC2_PWM_Zigbee', 'tcc2', 'TCC2_PWM']])
        res = Database.activateComponents(["tc0","pic32cx_bz3_devsupport"])
        result = Database.connectDependencies([[drvzgpdevice.getID(), 'TC0_TMR_Zigbee', 'tc0', 'TC0_TMR']])

    #responsible for adding custom app.c to project path instead of the app.c from device support
    try:
        if( deviceName in pic32cx_bz2_family):
            disableDeviceApp = Database.getComponentByID("pic32cx_bz2_devsupport")
            devicecAppFile = disableDeviceApp.getSymbolByID("DEVICE_APP_C")
            devicecAppFile.setEnabled(False)
            print("DISABLED APP FILE GENERATION FROM DEVICE SUPPORT")
        elif( deviceName in pic32cx_bz3_family):
            disableDeviceApp = Database.getComponentByID("pic32cx_bz3_devsupport")
            devicecAppFile = disableDeviceApp.getSymbolByID("DEVICE_APP_C")
            devicecAppFile.setEnabled(False)
            print("DISABLED APP FILE GENERATION FROM DEVICE SUPPORT")
        
    except Exception as e:
        print("EXCEPTION AT DRV_MAC_TESTER.py Custom App generation at finalizeComponent(), Exception: " ,e)
    
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

def instantiateComponent(drvzgpdevice):
    print('Zigbee Green Power Device')
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

    #rtc = Database.activateComponents(["rtc"])    
    #Database.setSymbolValue("rtc", "RTC_MODE0_INTENSET_CMP0_ENABLE", True)

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
      Database.setSymbolValue("core", "AES_CLOCK_ENABLE", True)

    Database.setSymbolValue("core", "ZIGBEE_CLOCK_ENABLE", True)
    Database.setSymbolValue("core", "CONFIG_SCOM0_HSEN", "DIRECT")
    if (deviceName in pic32cx_bz3_family):
          activeComponents = Database.getActiveComponentIDs()
          #requiredComponents = ["tcc2","pic32cx_bz3_devsupport"]
          requiredComponents = ["tc0","pic32cx_bz3_devsupport"]
          for r in requiredComponents:
              if r not in activeComponents:
                  print("require component '{}' - activating it".format(r))
                  res = Database.activateComponents([r])

    global MacAsSource
    MacAsSource = drvzgpdevice.createBooleanSymbol("MAC_AS_SOURCE", None)
    MacAsSource.setLabel("Use Source Files")
    MacAsSource.setVisible(False)
    MacAsSource.setDefaultValue(False)
    MacAsSource.setDescription("Use MAC,PHY,SysEnvironment Sources files")

    global UseRTOS
    UseRTOS = drvzgpdevice.createBooleanSymbol("USE_FREERTOS", None)
    UseRTOS.setLabel("Use RTOS")
    UseRTOS.setVisible(False)
    UseRTOS.setDefaultValue(True)
    UseRTOS.setDescription("Use FreeRTOS")

#####################################################################################################
    checkMacAsSource             =  (MacAsSource.getValue() == True)
    checkMacAsLib                =  (MacAsSource.getValue() == False)
    checkUseFreeRTOS             =  (UseRTOS.getValue() == True)
    checkWithoutRTOS             =  (UseRTOS.getValue() == False)

    condAlways                          = [True,                          None,                                        []]
    condMacSource                       = [checkMacAsSource,              setEnableMACSource,                          ['MAC_AS_SOURCE']]
    condMacLib                          = [checkMacAsLib,                 setEnableMACLib,                             ['MAC_AS_SOURCE']]
    condFreeRTOS                        = [checkUseFreeRTOS,              setEnableRTOS,                               ['USE_FREERTOS']]
    condNoRTOS                          = [checkWithoutRTOS,              setEnableWithoutRTOS,                        ['USE_FREERTOS']]
#####################################################################################################
#####################################################################################################


    # Timer Configuration Menu
    if(deviceName in pic32cx_bz2_family):
        timerConfigMenu = drvzgpdevice.createMenuSymbol("TIMERCONFIG_MENU", None)
        timerConfigMenu.setLabel("Timer Configuration")
        timerConfigMenu.setVisible(True)


    if( deviceName in pic32cx_bz2_family):
        drvzgpdevice.setDependencyEnabled('TCC2_PWM_Zigbee', False) #If bz2, disable TCC2 by default
    elif( deviceName in pic32cx_bz3_family):
        #drvzgpdevice.setDependencyEnabled('TC0_TMR_Zigbee', False)
        drvzgpdevice.setDependencyEnabled('TCC2_PWM_Zigbee', False)

    global drvComponent # used to pass component to timerconfig.py
    drvComponent = drvzgpdevice
#####################################################################################################
#################               TIMER CONFIGURATION                                   ###############
#####################################################################################################
    # Timer Configuration
    execfile(Module.getPath() +"/driver/zigbee/config/timerconfig.py")




#####################################################################################################
####################################### Code Generation #############################################
#####################################################################################################
#####################################################################################################
##############################  IMPORT INC AND SRC DEFINITIONS ######################################
#####################################################################################################
    # # Instance FTL files
    zigbeeAppConf = drvzgpdevice.createFileSymbol("ZIGBEE_APPCONF_HEADER", None)
    zigbeeAppConf.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/configs/zigbeeAppConfig.h.ftl")
    zigbeeAppConf.setOutputName("zigbeeAppConfig.h")
    zigbeeAppConf.setDestPath("/zigbee/zgpdevice_configs")
    zigbeeAppConf.setProjectPath("config/" + configName + "/zigbee/zgpdevice_configs")
    zigbeeAppConf.setType("HEADER")
    zigbeeAppConf.setOverwrite(True)
    zigbeeAppConf.setMarkup(True)

    zigbeeBitCloudPreConf = drvzgpdevice.createFileSymbol("ZIGBEE_BITPRE_HEADER", None)
    zigbeeBitCloudPreConf.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/configs/bitcloudPreInclude.h.ftl")
    zigbeeBitCloudPreConf.setOutputName("bitcloudPreInclude.h")
    zigbeeBitCloudPreConf.setDestPath("/zigbee/zgpdevice_configs")
    zigbeeBitCloudPreConf.setProjectPath("config/" + configName + "/zigbee/zgpdevice_configs")
    zigbeeBitCloudPreConf.setType("HEADER")
    zigbeeBitCloudPreConf.setOverwrite(True)
    zigbeeBitCloudPreConf.setMarkup(True)

    zigbeeStackConf = drvzgpdevice.createFileSymbol("ZIGBEE__STACKCONF_HEADER", None)
    zigbeeStackConf.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/configs/stackConfig.h.ftl")
    zigbeeStackConf.setOutputName("stackConfig.h")
    zigbeeStackConf.setDestPath("/zigbee/zgpdevice_configs")
    zigbeeStackConf.setProjectPath("config/" + configName + "/zigbee/zgpdevice_configs")
    zigbeeStackConf.setType("HEADER")
    zigbeeStackConf.setOverwrite(True)
    zigbeeStackConf.setMarkup(True)
    # System Definition
    ptcSystemDefFile = drvzgpdevice.createFileSymbol("ZIGBEE_SYS_DEF", None)
    ptcSystemDefFile.setType("STRING")
    ptcSystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    ptcSystemDefFile.setSourcePath("driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/templates/system/definitions.h.ftl")
    ptcSystemDefFile.setMarkup(True)

    # FreeRtos Config - Time bring Until Sleep is complete.
    zigbeeFreeRTOSConf = drvzgpdevice.createFileSymbol("ZIGBEE_RTOS_HEADER", None)
    zigbeeFreeRTOSConf.setSourcePath("/driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/configs/FreeRTOSConfig.h.ftl")
    zigbeeFreeRTOSConf.setOutputName("FreeRTOSConfig.h")
    zigbeeFreeRTOSConf.setDestPath("")
    zigbeeFreeRTOSConf.setProjectPath("config/" + configName)
    zigbeeFreeRTOSConf.setType("HEADER")
    zigbeeFreeRTOSConf.setOverwrite(True)
    zigbeeFreeRTOSConf.setMarkup(True)

    # Custom Antenna Gain Enabled
    customAntennaSpecified = drvzgpdevice.createBooleanSymbol('USE_CUSTOM_ANT_GAIN', None)
    customAntennaSpecified.setVisible(False)
    customAntennaSpecified.setReadOnly(True)
    customAntennaSpecified.setValue(False)

    # Custom Antenna Gain
    global customAntennaGain
    customAntennaGain = drvzgpdevice.createIntegerSymbol('CUSTOM_ANT_GAIN', None)
    customAntennaGain.setVisible(False)
    customAntennaGain.setReadOnly(True)
    customAntennaGain.setValue(3)

    # Custom Antenna Gain Region
    global  customAntennaRegion
    customAntennaRegion = drvzgpdevice.createStringSymbol('CUSTOM_ANT_REGION', None)
    customAntennaRegion.setVisible(False)
    customAntennaRegion.setReadOnly(True)
    customAntennaRegion.setValue('none')
    
    #global zgpdSleepSupportedDevice
    zgpdSleepSupportedDevice = drvzgpdevice.createBooleanSymbol("SLEEP_SUPPORTED_DEVICE", None)
    zgpdSleepSupportedDevice.setVisible(False)
    zgpdSleepSupportedDevice.setDefaultValue(False)

    #global deviceDeepSleepenabled1
    deviceDeepSleepenabled1 = drvzgpdevice.createBooleanSymbol('DEVICE_DEEP_SLEEP_ENABLED', None)
    deviceDeepSleepenabled1.setVisible(False)
    deviceDeepSleepenabled1.setDefaultValue(False)
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
        zigbeeInit.append( drvzgpdevice.createFileSymbol(i, None))
        zigbeeInit[n].setType('STRING')
        zigbeeInit[n].setOutputName(p)
        zigbeeInit[n].setSourcePath('driver/zigbee/templates/system/' + f)
        zigbeeInit[n].setMarkup(True)
        print('{} file: {} pos: {}'.format(n, f, p))
        n = n + 1


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

        ['mac_phy/MAC_ZGP/include/macZgpCommon.h',                                       condAlways],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include/macHwdZgpCommon.h',         condAlways],
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
        # ['security/TrustCentre/include/tc.h',                               condAlways],
        ['security/TrustCentre/include/tcAuthentic.h',                      condAlways],
        ['security/TrustCentre/include/tcKeyEstablish.h',                   condAlways],
        ['security/TrustCentre/include/tcPermissions.h',                    condAlways],
        ['security/serviceprovider/include/private/sspHashHandler.h',           condAlways],
        ['security/serviceprovider/include/private/sspMem.h',                   condAlways],
        ['security/serviceprovider/include/private/sspAuthenticHandler.h',      condAlways],
        ['security/serviceprovider/include/private/sspCcmHandler.h',            condAlways],
        ['security/serviceprovider/include/private/sspChallengeGenHandler.h',   condAlways],
        ['security/serviceprovider/include/private/sspManager.h',               condAlways],
        ['security/serviceprovider/include/private/sspSfpHandler.h',            condAlways],
        ['security/serviceprovider/include/private/sspSkkeHandler.h',           condAlways],
		['security/SoftAes/sspAesHandler.h',                                    condAlways],
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
    
    zdrvStackPdsServerIncFiles = [
        ['pds/include/wlPdsMemIds.h',                                        condAlways],
        ['pds/include/wlPdsTypesConverter.h',                                condAlways],
        ['pds/include/bcPDS.h',                                              condAlways],
    ]

    zdrvGreenPowerIncFiles = [
        ['zgp/GPDevice/include/zgpd.h',                              condAlways],
        ['zgp/GPDevice/include/zgpdChannelConfig.h',                 condAlways],
        ['zgp/GPDevice/include/zgpdCommissioning.h',                 condAlways],
        ['zgp/GPDevice/include/zgpdCommissioningHandler.h',          condAlways],
        ['zgp/GPDevice/include/zgpdCommon.h',                        condAlways],
        ['zgp/GPDevice/include/zgpdDataHandler.h',                   condAlways],
        ['zgp/GPDevice/include/zgpdIb.h',                            condAlways],
        ['zgp/GPDevice/include/zgpdManager.h',                       condAlways],
        ['zgp/GPDevice/include/zgpdMem.h',                           condAlways],
        ['zgp/GPDevice/include/zgpdMemAccess.h',                     condAlways],
        ['zgp/GPDevice/include/zgpdResetHandler.h',                  condAlways],
        ['zgp/GPDevice/include/zgpdSecurity.h',                      condAlways],

        ['zgp/include/zgpCommon.h',                                  condAlways],
        ['zgp/include/zgpDbg.h',                                     condAlways],
    ]
    for incFileEntry in zdrvStackPdsServerIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackAPSIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackNWKIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackConfigServerIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackMACIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    if (deviceName in pic32cx_bz3_family):
      for incFileEntry in zdrvStackBZ3HALCommonIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)
        
      incPathSym = drvzgpdevice.createSettingSymbol('SILEX_PATH_INCLUDE_PATH', None)
      incPathSym.setValue('../src/config/default/driver/security' + ';')
      incPathSym.setCategory('C32')
      incPathSym.setKey('extra-include-directories')
      incPathSym.setAppend(True, ';')
      incPathSym.setEnabled(True)
    else:
      for incFileEntry in zdrvStackHALCommonIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    if (deviceName in pic32cx_bz3_family):
      for incFileEntry in zdrvStackBZ3HALIncFiles:
        importHalIncFile(drvzgpdevice, configName, incFileEntry)
    else:
      for incFileEntry in zdrvStackHALIncFiles:
        importHalIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackSYSENVIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackSECIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvStackZDOIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zdrvGreenPowerIncFiles:
        importIncFile(drvzgpdevice, configName, incFileEntry)

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

    zgpAppIncFiles = [
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/app_task.h',          condAlways],
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/console.h',           condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/macInds.h',           condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/system.h',            condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/zgb_task.h',          condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/zgpSensor.h',         condAlways],

        ['application/zigbee_only/Zigbee_ZgpSensor_Application/stack_interface/configServer/include/cs_api.h',         condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/stack_interface/zgb_api.h',         condAlways],

       #['application/zigbee_only/Zigbee_ZgpSensor_Application/configs/Mac2_CommonMac_StdzgpSec_Pic32cx_Rf233_Gcc_Makerules.h',      condAlways],
    ]


    driversIncFiles = [
        #['drivers/sercom/usart/usart.h',              condAlways],
        ['drivers/PersistDataServer/wl/include/wlPdsBindings.h',                    condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Bindings.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Init.h',              condAlways],
        ['drivers/PersistDataServer/S_Nv/include/S_Nv_Stack_Ids.h',              condAlways],
    ]


    applicationCommonIncFiles = [
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/printLcd.h',                                            condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/errH.h',                                                condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/include/console.h',                                             condAlways],
    ]

    zgbWrappersIncFiles = [
        #['src/zgb_wrappers/bdb/BDB_Unpack.h',                      condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/stack_interface/configServer/include/CS_Unpack.h',              condAlways],
        #['src/zgb_wrappers/nwk/NWK_Unpack.h',                      condAlways],
        #['src/zgb_wrappers/zcl/ZCL_Unpack.h',                      condAlways],
        #['src/zgb_wrappers/zdo/ZDO_Unpack.h',                      condAlways],
    ]

    for incFileEntry in zgpAppIncFiles:
        importIncFileNonStack(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in zgbWrappersIncFiles:
        importIncFileNonStack(drvzgpdevice, configName, incFileEntry)

    for incFileEntry in applicationCommonIncFiles:
        importIncFileNonStack(drvzgpdevice, configName, incFileEntry)

    # for incFileEntry in utilsIncFiles:
        # importIncFileNonStack(drvzgpdevice, configName, incFileEntry)
################################### APS FILES #######################################################

################################### SOURCE FILES ####################################################
################################### APS FILES #######################################################
    zdrvStackConfigServerSrcFiles = [
        ['configserver/src/configserver.c',      condAlways],
        ['configserver/src/csMem.c',             condAlways],
        # ['configserver/src/csPersistentMem.c',   condAlways],
    ]

    zdrvStackMACSrcFiles = [
        # MAC Environment
        ['mac_phy/mac_env/src/macenvPib.c',                                         condMacSource],
        ['mac_phy/mac_env/src/macMem.c',                                            condMacSource],

        # MAC HWD
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdBatMonHandler.c',       condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdCalibHandler.c',        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdEdHandler.c',           condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdEncryptHandler.c',      condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdFrameRoutine.c',        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdHandlerCtrl.c',         condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdManager.c',             condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRegAccessHandler.c',    condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdResetHandler.c',        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRndHandler.c',          condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRxBuffer.c',            condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdRxFrameHandler.c',      condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdSetHandler.c',          condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTrxCtrl.c',             condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTrxHandler.c',          condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/src/machwdTxFrameHandler.c',      condMacSource],

        # PHY
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyAntDiversity.c',               condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyBatMon.c',                     condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyCalib.c',                      condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyDeepSleep.c',                  condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyEd.c',                         condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyEncrypt.c',                    condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyInit.c',                       condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRegAccess.c',                  condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyReset.c',                      condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRfIrqDispatcher.c',            condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRnd.c',                        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRtimerIrqDispatcher.c',        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRxFrame.c',                    condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyRxTxIndicator.c',              condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phySet.c',                        condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phySetTrxState.c',                condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyStateMachine.c',               condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyTxFrame.c',                    condMacSource],
        ['mac_phy/mac_hwd_phy/RF231_RF212/PHY/src/phyTxPowerConverter.c',           condMacSource],

        # MAC HWI
        ['mac_phy/mac_hwi/src/machwiAssociateHandler.c',                            condMacSource],
        ['mac_phy/mac_hwi/src/machwiBanNode.c',                                     condMacSource],
        ['mac_phy/mac_hwi/src/machwiBeaconHandler.c',                               condMacSource],
        ['mac_phy/mac_hwi/src/machwiDataHandler.c',                                 condMacSource],
        ['mac_phy/mac_hwi/src/machwiDisassociateHandler.c',                         condMacSource],
        ['mac_phy/mac_hwi/src/machwiManager.c',                                     condMacSource],
        ['mac_phy/mac_hwi/src/machwiOrphanHandler.c',                               condMacSource],
        ['mac_phy/mac_hwi/src/machwiPanIdConflictHandler.c',                        condMacSource],
        ['mac_phy/mac_hwi/src/machwiPanServer.c',                                   condMacSource],
        ['mac_phy/mac_hwi/src/machwiPollHandler.c',                                 condMacSource],
        ['mac_phy/mac_hwi/src/machwiPurgeHandler.c',                                condMacSource],
        ['mac_phy/mac_hwi/src/machwiResetHandler.c',                                condMacSource],
        ['mac_phy/mac_hwi/src/machwiRxEnableHandler.c',                             condMacSource],
        ['mac_phy/mac_hwi/src/machwiScanHandler.c',                                 condMacSource],
        ['mac_phy/mac_hwi/src/machwiSetGetHandler.c',                               condMacSource],
        ['mac_phy/mac_hwi/src/machwiStartHandler.c',                                condMacSource],
        ['mac_phy/mac_hwi/src/machwiSwitchRxCtrl.c',                                condMacSource],
        ['mac_phy/mac_hwi/src/machwiTransactionHandler.c',                          condMacSource],
        ['mac_phy/mac_hwi/src/machwiTransactionHash.c',                             condMacSource],
        ['mac_phy/mac_hwi/src/machwiTransactionQueue.c',                            condMacSource],
        # ['mac_phy/MAC_ZGP/src/macZgpCommon.c',                                      condAlways],

        ['mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/src/macHwdZgpCommon.c',        condMacSource],
    ]

    zdrvStackSYSENVSrcFiles = [
        ['systemenvironment/src/dbg.c',                 condMacSource],#condMacSource
        ['systemenvironment/src/sysAssert.c',           condMacSource],
        ['systemenvironment/src/sysDuplicateTable.c',   condMacSource],
        ['systemenvironment/src/sysEventsHandler.c',    condMacSource],
        ['systemenvironment/src/sysIdleHandler.c',      condAlways],#condAlways
        ['systemenvironment/src/sysInit.c',             condMacSource],
        ['systemenvironment/src/sysMutex.c',            condMacSource],
        ['systemenvironment/src/sysQueue.c',            condMacSource],
        ['systemenvironment/src/sysSleep.c',            condMacSource],
        ['systemenvironment/src/sysStat.c',             condMacSource],
        ['systemenvironment/src/sysTaskManager.c',      condAlways],#condAlways
        ['systemenvironment/src/sysTimer.c',            condMacSource],
        ['systemenvironment/src/sysUtils.c',            condMacSource],
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
        # ['security/TrustCentre/src/tcAuthenticHandler.c',                      condAlways],
        # ['security/TrustCentre/src/tcDeviceTableCtrlHandler.c',                condAlways],
        # ['security/TrustCentre/src/tcIndInput.c',                              condAlways],
        # ['security/TrustCentre/src/tcKeyEstablishHandler.c',                   condAlways],
        # ['security/TrustCentre/src/tcKeyUpdateHandler.c',                      condAlways],
        # ['security/TrustCentre/src/tcMem.c',                                   condAlways],
        # ['security/TrustCentre/src/tcPermissions.c',                           condAlways],
        # ['security/TrustCentre/src/tcPromiscuousMode.c',                       condAlways],
        # ['security/TrustCentre/src/tcRemoveHandler.c',                         condAlways],
        # ['security/TrustCentre/src/tcResetHandler.c',                          condAlways],
        # ['security/TrustCentre/src/tcTaskManager.c',                           condAlways],
        # ['security/SoftAes/sspAesHandler.c',                                   condAlways],
    ]


    zdrvStackHALSrcFiles = [
        ['hal/cortexm4/pic32cx_bz2/src/atomic.c',                 condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/hal_aes_sync.c',           condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halAppClock.c',            condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halFlash.c',               condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halMacIsr.c',              condAlways],
        ['hal/cortexm4/pic32cx_bz2/src/halRfCtrl.c',              condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halSleep.c',               condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/halSleepTimerClock.c',     condAlways],
        #['hal/cortexm4/pic32cx_bz2/src/hpl_aes.c',                condAlways],
        ['hal/cortexm4/pic32cx_bz2/src/halAes.c',                 condAlways],
    ]
    
    zdrvStackHALCommonSrcFiles = [
        #['hal/cortexm4/common/src/appTimer.c',                condAlways],
        ##['hal/cortexm4/common/src/flash.c',                   condAlways],
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
    zdrvGreenPowerSrcFiles = [
        ['zgp/GPDevice/src/zgpdBidirectionalCommissioning.c',          condAlways],
        ['zgp/GPDevice/src/zgpdChannelConfig.c',                       condAlways],
        ['zgp/GPDevice/src/zgpdCommissioning.c',                       condAlways],
        ['zgp/GPDevice/src/zgpdCommissioningHandler.c',                condAlways],
        ['zgp/GPDevice/src/zgpdDataHandler.c',                         condAlways],
        ['zgp/GPDevice/src/zgpdIb.c',                                  condAlways],
        ['zgp/GPDevice/src/zgpdManager.c',                             condAlways],
        ['zgp/GPDevice/src/zgpdMem.c',                                 condAlways],
        ['zgp/GPDevice/src/zgpdResetHandler.c',                        condAlways],
        ['zgp/GPDevice/src/zgpdSecurity.c',                            condAlways],
    ]
    

    for srcFileEntry in zdrvStackConfigServerSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in zdrvStackMACSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in zdrvStackSYSENVSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in zdrvStackSECSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    if (deviceName in pic32cx_bz3_family):
      for srcFileEntry in zdrvStackBZ3HALSrcFiles:
        importSrcHalFile(drvzgpdevice, configName, srcFileEntry)
    else:
      for srcFileEntry in zdrvStackHALSrcFiles:
        importSrcHalFile(drvzgpdevice, configName, srcFileEntry)

    if (deviceName in pic32cx_bz3_family):
      for srcFileEntry in zdrvStackBZ3HALCommonSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)
    else:
      for srcFileEntry in zdrvStackHALCommonSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in zdrvBSPSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in zdrvGreenPowerSrcFiles:
        importSrcFile(drvzgpdevice, configName, srcFileEntry)
    zgbWrappersSrcFiles = [
        # ['src/zgb_wrappers/bdb/BDB_Unpack.c',                      condAlways],
         ['application/zigbee_only/Zigbee_ZgpSensor_Application/stack_interface/configServer/CS_Unpack.c',              condAlways],
        # ['src/zgb_wrappers/nwk/NWK_Unpack.c',                      condAlways],
        # ['src/zgb_wrappers/zcl/ZCL_Unpack.c',                      condAlways],
        # ['src/zgb_wrappers/zdo/ZDO_Unpack.c',                      condAlways],
    ]

    applicationCommonSrcFiles = [
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/zigbee_init.c',              condAlways],
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/zgb_init.c',               condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/zgb_task.c',               condAlways],
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/app_task.c',               condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/console.c',                condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/macInds.c',                condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/sensorConsole.c',          condAlways],
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/system_tasks.c',           condAlways],
        ['application/zigbee_only/Zigbee_ZgpSensor_Application/common/src/ZgpSensor.c',              condAlways],

        # API Wrapper Files
        # ['application/zigbee_only/Zigbee_ZgpSensor_Application/api/src/CS_API.c',                       condAlways],
    ]

    for srcFileEntry in zgbWrappersSrcFiles:
        importSrcFileNonStack(drvzgpdevice, configName, srcFileEntry)

    for srcFileEntry in applicationCommonSrcFiles:
        importSrcFileNonStack(drvzgpdevice, configName, srcFileEntry)

    zigbeeStackdrvIncPaths = [
        ['/src/Components',                                                    condAlways],
        ['/src/Components/configserver/include',                               condAlways],
        ['/src/Components/configserver/include/private',                       condAlways],
        ['/src/Components/hal/include',                                        condAlways],
        ['/src/Components/hal/cortexm4/pic32cx/include',                       condAlways],
        ['/src/Components/mac_phy/include',                                    condAlways],
        ['/src/Components/mac_phy/MAC_ZGP/include',                            condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/MACHWD_ZGP/include', condAlways],
        ['/src/Components/mac_phy/mac_env/include',                            condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/include',                        condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy',                                condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/',                                condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD',            condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/MAC_HWD/include',    condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/PHY',                condAlways],
        ['/src/Components/mac_phy/mac_hwd_phy/RF231_RF212/PHY/include',        condAlways],
        ['/src/Components/mac_phy/mac_hwi/include',                            condAlways],
        ['/src/Components/nwk/include',                                        condAlways],
        ['/src/Components/zgp',                                                condAlways],
        ['/src/Components/zgp/include',                                        condAlways],
        ['/src/Components/zgp/GPDevice/include',                               condAlways],
        ['/src/Components/nwk/include/private',                                condAlways],
        ['/src/Components/systemenvironment/include',                          condAlways],
        ['/src/Components/systemenvironment/include/private',                  condAlways],
        ['/zigbee',                                                         condAlways],
        ['/zigbee/utils',                                                         condAlways],
        ['/zigbee/drivers/sercom/usart',                                          condAlways],
        ['/zigbee/drivers/calibration',                                           condAlways],
        ['/zigbee/drivers/rf',                                                    condAlways],
        ['/zigbee/utils/interrupt',                                                     condAlways],
        ['/zigbee/utils/preprocessor',                                                  condAlways],
        ['/application/zigbee_only/Zigbee_ZgpSensor_Application',                   condAlways], 
		['/application/zigbee_only/Zigbee_ZgpSensor_Application/common/include',                   condAlways], 
		['/application/zigbee_only/Zigbee_ZgpSensor_Application/api/include',                   condAlways],
        ['/zigbee/Zigbee_ZgpSensor_Application',                                     condAlways],
        ['/zigbee/Zigbee_ZgpSensor_Application/common/include',                                     condAlways],
        ['/zigbee/Zigbee_ZgpSensor_Application/api/include',                                     condAlways],
		['/zigbee/common_files/include',                                     condAlways],
		['/src/Components/security/serviceprovider/include',                   condAlways],
        ['/src/Components/security/serviceprovider/include/private',           condAlways],
        ['/src/Components/security/SoftAes',                                   condAlways],
        ['/peripheral',                                                                                    condAlways],
        ['/driver/pds/include',                                                                            condAlways],
        ['/crypto',                                                                                        condAlways],
        ['/osal',                                                                                        condAlways],
    ]

    for incPathEntry in zigbeeStackdrvIncPaths:
        setIncPath(drvzgpdevice, configName, incPathEntry)

    # Add appTimer.c - generated file
    appTimerSourceFile = drvzgpdevice.createFileSymbol(None, None)
    appTimerSourceFile.setSourcePath('driver/zigbee/templates/appTimer.c.ftl')
    appTimerSourceFile.setOutputName('appTimer.c')
    appTimerSourceFile.setOverwrite(True)
    appTimerSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/common/src/')
    appTimerSourceFile.setProjectPath('/config/default/zigbee/systemresource/hal/cortexm4/common/src/')
    appTimerSourceFile.setType('SOURCE')
    appTimerSourceFile.setEnabled(True)
    appTimerSourceFile.setMarkup(True)
    
    # Add app_uart.c - generated file
    app_uartSourceFile = drvzgpdevice.createFileSymbol(None, None)
    app_uartSourceFile.setSourcePath('driver/zigbee/templates/app_uart.c.ftl')
    app_uartSourceFile.setOutputName('app_uart.c')
    app_uartSourceFile.setOverwrite(True)
    app_uartSourceFile.setDestPath('../../app_zigbee/')
    app_uartSourceFile.setProjectPath('app_zigbee/zigbee_console/')
    app_uartSourceFile.setType('SOURCE')
    app_uartSourceFile.setEnabled(True)
    app_uartSourceFile.setMarkup(True)

    # Add app_zigbee.h - static file
    app_zgbHeaderFile = drvzgpdevice.createFileSymbol(None, None)
    app_zgbHeaderFile.setSourcePath('driver/zigbee/templates/zigbee_app_header.h.ftl')
    app_zgbHeaderFile.setOutputName('app_zigbee.h')
    app_zgbHeaderFile.setOverwrite(True)
    app_zgbHeaderFile.setDestPath('../../app_zigbee/')
    app_zgbHeaderFile.setProjectPath('app_zigbee')
    app_zgbHeaderFile.setType('HEADER')
    app_zgbHeaderFile.setEnabled(True)

    app_SourceFile = drvzgpdevice.createFileSymbol(None, None)
    app_SourceFile.setSourcePath('driver/zigbee/application/zigbee_only/Zigbee_ZgpSensor_Application/templates/app.c')
    app_SourceFile.setOutputName('app.c')
    app_SourceFile.setOverwrite(True)
    app_SourceFile.setDestPath('../../')
    app_SourceFile.setProjectPath('')
    app_SourceFile.setType('SOURCE')
    app_SourceFile.setEnabled(True)
    app_SourceFile.setMarkup(True)

    preprocessormac = drvzgpdevice.createSettingSymbol('ZIGBEE_PREPRECESSOR', None) 
    preprocessormac.setValue('_PIC32CX_;PIC32CX_CHIP_SOC;ZGPSENSOR_APP')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('preprocessor-macros')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    preprocessormac = drvzgpdevice.createSettingSymbol('ZIGBEE_ISOLATEFUNCTION', None) 
    preprocessormac.setValue('false')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('isolate-each-function')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    preprocessormac = drvzgpdevice.createSettingSymbol('ZIGBEE_PLACEDATASECTION', None) 
    preprocessormac.setValue('false')
    preprocessormac.setCategory('C32')
    preprocessormac.setKey('place-data-into-section')
    preprocessormac.setAppend(True, ';')
    preprocessormac.setEnabled(True)

    # Disable Default linker script
    Database.setSymbolValue("core", "ADD_LINKER_FILE", False)

    # Setting the required heap size for the application
    Database.sendMessage("core", "HEAP_SIZE", {"heap_size":4096})
    Database.sendMessage("pic32cx_bz2_devsupport", "CONSOLE_ENABLE", {"isEnabled":True})
    Database.setSymbolValue("drv_usart", "DRV_USART_COMMON_MODE", "Asynchronous")

    preprocessorLD = drvzgpdevice.createSettingSymbol('ZIGBEE_PREPRECESSOR_LD3', None)
    preprocessorLD.setValue('1024')
    preprocessorLD.setCategory('C32-LD')
    preprocessorLD.setKey('stack-size')
    preprocessorLD.setEnabled(True)

    preprocessorAS = drvzgpdevice.createSettingSymbol('ZIGBEE_PREPRECESSOR_AS', None)
    if (deviceName in pic32cx_bz2_family):
        preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;HAL_USE_FLASH_ACCESS;_MAC2_')
    elif (deviceName in pic32cx_bz3_family):
        preprocessorAS.setValue('PIC32CX_CHIP_SOC;_PIC32CX_;HAL_USE_FLASH_ACCESS;_MAC2_;PLATFORM_PIC32CXBZ3')
    preprocessorAS.setCategory('C32')
    preprocessorAS.setKey('preprocessor-macros')
    preprocessorAS.setAppend(True, ';')
    preprocessorAS.setEnabled(True)

    warningerr = drvzgpdevice.createSettingSymbol('WARNINGG_ERR', None)
    warningerr.setValue('false')
    warningerr.setCategory('C32')
    warningerr.setKey('make-warnings-into-errors')

    warningadd = drvzgpdevice.createSettingSymbol('WARNINGG_ADD', None)
    warningadd.setValue('false')
    warningadd.setCategory('C32')
    warningadd.setKey('additional-warnings')

    optlevel = drvzgpdevice.createSettingSymbol('PET_LEVEL', None)
    optlevel.setValue('-O2')
    optlevel.setCategory('C32')
    optlevel.setKey('optimization-level')

################################### Library File ####################################################
    setAdditionaloptionXC32GCC = drvzgpdevice.createSettingSymbol('SET_XC32_GCC_ADD_INC', None)
    setAdditionaloptionXC32GCC.setValue('-include"zigbee/zgpdevice_configs/zigbeeAppConfig.h"')
    setAdditionaloptionXC32GCC.setCategory('C32')
    setAdditionaloptionXC32GCC.setKey('appendMe')
    setAdditionaloptionXC32GCC.setEnabled(checkMacAsSource)
    setAdditionaloptionXC32GCC.setDependencies(setEnableMACSource, ["MAC_AS_SOURCE"])

    zgpdMakeRulesFile = drvzgpdevice.createFileSymbol("ZIGBEE_MAKERULE_HEADER", None)
    if (deviceName in pic32cx_bz2_family):   
      zgpdMakeRulesFile.setSourcePath("/driver/zigbee/application//zigbee_only/Zigbee_ZgpSensor_Application/configs/Mac_Common_StdzgpSec_bz2_Makerules.h")
      zgpdMakeRulesFile.setOutputName("Mac_Common_StdzgpSec_bz2_Makerules.h")
    elif (deviceName in pic32cx_bz3_family):
      zgpdMakeRulesFile.setSourcePath("/driver/zigbee/application//zigbee_only/Zigbee_ZgpSensor_Application/configs/Mac_Common_StdzgpSec_bz3_Makerules.h")
      zgpdMakeRulesFile.setOutputName("Mac_Common_StdzgpSec_bz3_Makerules.h")
    zgpdMakeRulesFile.setDestPath("/zigbee/lib/")
    #zgpdMakeRulesFile.setProjectPath("config/" + configName + "/zigbee/lib/")
    zgpdMakeRulesFile.setType("HEADER")
    zgpdMakeRulesFile.setOverwrite(True)
    zgpdMakeRulesFile.setMarkup(True)
    
    setAdditionaloptionXC32GCC1 = drvzgpdevice.createSettingSymbol('SET_XC32_GCC_ADD_INC_LIB', None)
    if (deviceName in pic32cx_bz2_family):
      setAdditionaloptionXC32GCC1.setValue('-include"lib/Mac_Common_StdzgpSec_bz2_Makerules.h"')
    elif (deviceName in pic32cx_bz3_family):
      setAdditionaloptionXC32GCC1.setValue('-include"lib/Mac_Common_StdzgpSec_bz3_Makerules.h"')
    setAdditionaloptionXC32GCC1.setCategory('C32')
    setAdditionaloptionXC32GCC1.setKey('appendMe')
    setAdditionaloptionXC32GCC1.setEnabled(checkMacAsLib)
    setAdditionaloptionXC32GCC1.setDependencies(setEnableMACLib, ["MAC_AS_SOURCE"])

    MacLibFile = drvzgpdevice.createLibrarySymbol("ZBMAC_LIB_FILE", None)
    MacLibFile.setDestPath('/zigbee/lib/')
    if (deviceName in pic32cx_bz2_family):
      MacLibFile.setSourcePath("/driver/zigbee/src/lib/Mac_Common_StdzgpSec_bz2_Lib.a")
      MacLibFile.setOutputName("Mac_Common_StdzgpSec_bz2_Lib.a")
    elif (deviceName in pic32cx_bz3_family):
      MacLibFile.setSourcePath("/driver/zigbee/src/lib/Mac_Common_StdzgpSec_bz3_Lib.a")
      MacLibFile.setOutputName("Mac_Common_StdzgpSec_bz3_Lib.a")
    MacLibFile.setEnabled(checkMacAsLib)
    MacLibFile.setDependencies(setEnableMACLib, ["MAC_AS_SOURCE"])
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
    incFileSym.setSourcePath('driver/zigbee/src/Components/' + secSName + '/' + incFile)
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
    incFileSym.setSourcePath('driver/zigbee/' + secSName + incFile)
    incFileSym.setOutputName(incFile)


    secTname = secDName.replace('src/','')
    secDName = secTname.replace('application/zigbee_only/','')
    secTname = secDName.replace('Zigbee_ZgpSensor_Application','zgpdevice')
    secDName = secTname.replace('stack_interface','stack_interface')

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
    secTname = secDName.replace('Zigbee_ZgpSensor_Application','zgpdevice')
    secDName = secTname.replace('stack_interface','stack_interface')

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
    srcFileSym.setSourcePath('driver/zigbee/src/Components/' + secSName + srcFile)
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
    incPath = incPath.replace('Zigbee_ZgpSensor_Application','zgpdevice')
    incPath = incPath.replace('/Components','/zigbee/lib/inc')
    incPath = incPath.replace('drivers','driver')
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

#####################################################################################################
#####################################################################################################

def setEnableMACSource(symbol, event):
    component = symbol.getComponent()
    MacAsSourceCheck  =  component.getSymbolValue('MAC_AS_SOURCE')
    print(MacAsSourceCheck)
    if (MacAsSourceCheck == True):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableMACLib(symbol, event):
    component = symbol.getComponent()
    MacAsSourceCheck  =  component.getSymbolValue('MAC_AS_SOURCE')
    print(MacAsSourceCheck)
    if (MacAsSourceCheck == False):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableRTOS(symbol, event):
    if (event["value"] == True):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def setEnableWithoutRTOS(symbol, event):
    if (event["value"] == False):
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
