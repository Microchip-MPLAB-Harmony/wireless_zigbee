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

#####################################################################################################################
########################               APPLICATION CONFIGURATION                             ########################
#####################################################################################################################
global devicename
devicename = Variables.get("__PROCESSOR")

def appChannelTypeCheckChannel(symbol, event):
    if (appConfigUseChannel.getValue() == "YES"):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def appChannelTypeCheckMask(symbol, event):
    if (appConfigUseChannel.getValue() == "NO"):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)



def zigbeeDevResetToFN(symbol, event):
    if( deviceName in pic32cx_bz2_family):
        wbzSymbols = Database.getComponentByID('pic32cx_bz2_devsupport')
    else:
        wbzSymbols = Database.getComponentByID('pic32cx_bz3_devsupport')
        
    resetToFNSymbol = wbzSymbols.getSymbolByID('ENABLE_RESET_TO_FN')
    if((event["value"] == True)):
        symbol.setValue(True)
        resetToFNSymbol.setValue(True)
        eicActiavtionResult = Database.activateComponents(["eic"])
        if(eicActiavtionResult):
            eicDeepSleepConfig()
        else:
            print("EIC activation failed")
        
    elif((event["value"] == False)):
        symbol.setValue(False)
        resetToFNSymbol.setValue(False)
        eicActiavtionResult = Database.deactivateComponents(["eic"])


# Configuration selection to use channel or channel mask
global appConfigUseChannel
appConfigUseChannel = drvZigbeeComponent.createComboSymbol("APP_USE_CHANNEL", applicationConfigMenu,  ["YES", "NO"])
appConfigUseChannel.setDefaultValue("NO")
appConfigUseChannel.setLabel("Use Channel instead of Mask")

# Primary Channel 
appConfigPrimaryChannel = drvZigbeeComponent.createIntegerSymbol("APP_PRIMARY_CHANNEL", applicationConfigMenu)
appConfigPrimaryChannel.setLabel("Primary Channel")
appConfigPrimaryChannel.setDefaultValue(20)
appConfigPrimaryChannel.setMin(11)
appConfigPrimaryChannel.setMax(26)
appConfigPrimaryChannel.setVisible(appConfigUseChannel.getValue() == "YES")
appConfigPrimaryChannel.setDependencies(appChannelTypeCheckChannel, ["APP_USE_CHANNEL"])

# Secondary Channel 
appConfigSecondaryChannel = drvZigbeeComponent.createIntegerSymbol("APP_SECONDARY_CHANNEL", applicationConfigMenu)
appConfigSecondaryChannel.setLabel("Secondary Channel")
appConfigSecondaryChannel.setDefaultValue(20)
appConfigSecondaryChannel.setMin(11)
appConfigSecondaryChannel.setMax(26)
appConfigSecondaryChannel.setVisible(appConfigUseChannel.getValue() == "YES")
appConfigSecondaryChannel.setDependencies(appChannelTypeCheckChannel, ["APP_USE_CHANNEL"])

# Primary Channel Mask
appConfigPrimaryChannelMask = drvZigbeeComponent.createHexSymbol("APP_PRIMARY_CHANNELS_MASK", applicationConfigMenu)
appConfigPrimaryChannelMask.setLabel("Primary Channel Mask")
appConfigPrimaryChannelMask.setDefaultValue(0x2108800)
appConfigPrimaryChannelMask.setMin(0)
appConfigPrimaryChannelMask.setMax(0xFFFFFFFF)
appConfigPrimaryChannelMask.setVisible(appConfigUseChannel.getValue() == "NO")
appConfigPrimaryChannelMask.setDependencies(appChannelTypeCheckMask, ["APP_USE_CHANNEL"])

# Secondary Channel Mask
appConfigSecondaryChannelMask = drvZigbeeComponent.createHexSymbol("APP_SECONDARY_CHANNELS_MASK", applicationConfigMenu)
appConfigSecondaryChannelMask.setLabel("Secondary Channel Mask")
appConfigSecondaryChannelMask.setDefaultValue(0x5EF7000)
appConfigSecondaryChannelMask.setMin(0)
appConfigSecondaryChannelMask.setMax(0xFFFFFFFF)
appConfigSecondaryChannelMask.setVisible(appConfigUseChannel.getValue() == "NO")
appConfigSecondaryChannelMask.setDependencies(appChannelTypeCheckMask, ["APP_USE_CHANNEL"])


global ResetTOFnEnabling
ResetTOFnEnabling = drvZigbeeComponent.createBooleanSymbol("RESET_TO_FN_ENABLE", applicationConfigMenu)
ResetTOFnEnabling.setLabel("Reset To FN on button press")
ResetTOFnEnabling.setVisible((drvZigbeeComponent.getID() in deviceDeepSleepEnabledList))
ResetTOFnEnabling.setDefaultValue(False)
ResetTOFnEnabling.setDependencies(zigbeeDevResetToFN, ["RESET_TO_FN_ENABLE"]) 
# Console
global appConfigEnableConsole
appConfigEnableConsole = drvZigbeeComponent.createBooleanSymbol("APP_ENABLE_CONSOLE", applicationConfigMenu)
appConfigEnableConsole.setLabel("Enable Zigbee Console Commands")
appConfigEnableConsole.setDefaultValue(False)
appConfigEnableConsole.setDescription("APP_ENABLE_CONSOLE- check the box to enable")

global bdbconsolecommandEnable
bdbconsolecommandEnable = drvZigbeeComponent.createBooleanSymbol("BDB_COMMANDS_IN_CONSOLE", appConfigEnableConsole)
bdbconsolecommandEnable.setLabel("Enable BDB Console Commands")
bdbconsolecommandEnable.setDefaultValue(False)
bdbconsolecommandEnable.setDescription("BDB_COMMANDS_IN_CONSOLE- check the box to enable")

global zclconsolecommandEnable
zclconsolecommandEnable = drvZigbeeComponent.createBooleanSymbol("ZCL_COMMANDS_IN_CONSOLE", appConfigEnableConsole)
zclconsolecommandEnable.setLabel("Enable ZCL Console Commands")
zclconsolecommandEnable.setDefaultValue(False)
zclconsolecommandEnable.setDescription("ZCL_COMMANDS_IN_CONSOLE- check the box to enable")

global zdoconsolecommandEnable
zdoconsolecommandEnable = drvZigbeeComponent.createBooleanSymbol("ZDO_COMMANDS_IN_CONSOLE", appConfigEnableConsole)
zdoconsolecommandEnable.setLabel("Enable ZDO Console Commands")
zdoconsolecommandEnable.setDefaultValue(False)
zdoconsolecommandEnable.setDescription("ZDO_COMMANDS_IN_CONSOLE- check the box to enable")

global commsnzdoconsolecommandEnable
commsnzdoconsolecommandEnable = drvZigbeeComponent.createBooleanSymbol("COMMISSIONING_COMMANDS_IN_CONSOLE", appConfigEnableConsole)
commsnzdoconsolecommandEnable.setLabel("Enable Commissioining Console Commands")
commsnzdoconsolecommandEnable.setDefaultValue(False)
commsnzdoconsolecommandEnable.setDescription("COMMISSIONING_COMMANDS_IN_CONSOLE- check the box to enable")

global appConfigZloExtraClusters
appConfigZloExtraClusters = drvZigbeeComponent.createBooleanSymbol("ZLO_EXTRA_CLUSTERS_SUPPORT", appConfigEnableConsole)
appConfigZloExtraClusters.setLabel("Enable ZLO Extra Clusters Support")
appConfigZloExtraClusters.setDefaultValue(False)
appConfigZloExtraClusters.setDescription("ZLO_EXTRA_CLUSTERS_SUPPORT- check the box to enable")

global appConfigZloClustersEnhancements
appConfigZloClustersEnhancements = drvZigbeeComponent.createBooleanSymbol("ZLO_CLUSTER_ENHANCEMENTS", appConfigEnableConsole)
appConfigZloClustersEnhancements.setLabel("Enable ZLO Clusters Enhancements")
appConfigZloClustersEnhancements.setDefaultValue(False)
appConfigZloClustersEnhancements.setDescription("ZLO_CLUSTER_ENHANCEMENTS- check the box to enable")

# Certification Extension
global appConfigCertificationExtension
appConfigCertificationExtension = drvZigbeeComponent.createBooleanSymbol("APP_ENABLE_CERTIFICATION_EXTENSION", appConfigEnableConsole)
appConfigCertificationExtension.setLabel("Certification Extension")
appConfigCertificationExtension.setDefaultValue(False)
appConfigCertificationExtension.setDescription("APP_ENABLE_CERTIFICATION_EXTENSION- check the box to enable")
