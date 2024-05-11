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

############################################################################################################
###########################################  COLORCONTROL CLUSTER CONFIGURATION  ###########################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def ColorControlClusterCsCheck(symbol, event):
    if (ColorControlCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def ColorControlClusterEnableCheck(symbol, event):
    if (ColorControlCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customColorControlClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (ColorControlCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def ColorControlClusterClientCheck(symbol, event):
    if ((ColorControlCluster.getValue() == False) or ColorControlClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def ColorControlClusterServerCheck(symbol, event):
    if ((ColorControlCluster.getValue() == False) or ColorControlClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def colorControlClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        ):
        ColorControlCluster.setVisible(True)
        ColorControlCluster.setValue(True)
        ColorControlCluster.setReadOnly(True)
        ColorControlClusterCS.setValue("CLIENT")
        ColorControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")
         or (getDevice == "ZIGBEE_THERMOSTAT")
         or (getDevice == "ZIGBEE_IAS_ACE")
         or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
         or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
         ):
        ColorControlCluster.setVisible(False)
        ColorControlCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COLOR_LIGHT")
          or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
          or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
          ):
        ColorControlCluster.setVisible(True)
        ColorControlCluster.setValue(True)
        ColorControlCluster.setReadOnly(True)
        ColorControlClusterCS.setValue("SERVER")
        ColorControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        ColorControlCluster.setVisible(True)
        ColorControlCluster.setValue(True)
        ColorControlClusterCS.setValue("BOTH")
    else:
        ColorControlCluster.setVisible(False)

def ColorControlClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (ColorCtrlClusterServerAttributeCurrentHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeCurrentSaturation.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeRemainingTime.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeCurrentX.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeCurrentY.getValue()):
            count += 1
    # if (ColorCtrlClusterServerAttributeDriftCompensation.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeCompensationText.getValue()):
            # count += 1
    if (ColorCtrlClusterServerAttributeColorTemperatureMireds.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorMode.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeOptions.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeNumberOfPrimaries.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary1X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary1Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary1Intensity.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary2X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary2Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary2Intensity.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary3X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary3Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary3Intensity.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary4X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary4Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary4Intensity.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary5X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary5Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary5Intensity.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary6X.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary6Y.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributePrimary6Intensity.getValue()):
            count += 1
    # if (ColorCtrlClusterServerAttributeWhitePointX.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeWhitePointY.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointRX.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointRY.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointRIntensity.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointGX.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointGY.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointGIntensity.getValue()):
            # count += 1
    # if (ColorCtrlClusterServerAttributeColorPointBX.getValue()):
            # count += 1            
    # if (ColorCtrlClusterServerAttributeColorPointBY.getValue()):
            # count += 1
    # # if (ColorCtrlClusterServerAttributeColorPointBIntensity.getValue()):
            # count += 1
    if (ColorCtrlClusterServerAttributeEnhancedCurrentHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeEnhancedColorMode.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorLoopActive.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorLoopDirection.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorLoopTime.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorLoopStartEnhancedHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorLoopStoredEnhancedHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorCapabilities.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorTempPhysicalMinMireds.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeColorTempPhysicalMaxMireds.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeCoupleColorTempToLevelMinMireds.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeStartUpColorTemperatureMireds.getValue()):
            count += 1
    if (ColorCtrlClusterServerAttributeClusterRevision.getValue()):
            count += 1
    ColorControlClusterServerAttributeCount.setValue(count) 
    return count

def ColorControlClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (ColorCtrlClusterServerCmdMoveToHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdStepHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMovetoSat.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveSat.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdStepSat.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMovetoHueSat.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveToColor.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveColor.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdStepColor.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveToColorTemp.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdEnhancedMoveToHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdEnhancedMoveHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdEnhancedStepHue.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdEnhancedMovetoHueSat.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdColorloopset.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdStopMoveStep.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdMoveTocolortemp.getValue()):
            count += 1            
    if (ColorCtrlClusterServerCmdMovecolortemp.getValue()):
            count += 1
    if (ColorCtrlClusterServerCmdStepcolortemp.getValue()):
            count += 1
    ColorCtrlClusterServerCommandCount.setValue(count)
    return count

def ColorControlClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (ColorCtrlClusterClientAttributeClusterRevision.getValue()):
        count += 1
    ColorCtrlClusterClientAttributeCount.setValue(count)
    return count

def ColorControlClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (ColorCtrlClusterClientCmdMoveToHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMoveHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdStepHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMovetoSat.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMoveSat.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdStepSat.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMovetoHueSat.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMoveToColor.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMoveColor.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdStepColor.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdMoveToColorTemp.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdEnhancedMoveToHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdEnhancedMoveHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdEnhancedStepHue.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdEnhancedMovetoHueSat.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdColorloopset.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdStopMoveStep.getValue()):
            count += 1     
    if (ColorCtrlClusterClientCmdMovecolortemp.getValue()):
            count += 1
    if (ColorCtrlClusterClientCmdStepcolortemp.getValue()):
            count += 1
    ColorCtrlClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global ColorControlCluster
ColorControlCluster = drvZigbeeComponent.createBooleanSymbol("COLORCONTROL_CLUSTER_ENABLE", clusterConfigMenu)
ColorControlCluster.setLabel("0x0300 Color Control Cluster")
ColorControlCluster.setDefaultValue(False)
ColorControlCluster.setVisible(False)
ColorControlCluster.setDescription("COLORCONTROL CLUSTER- check the box to enable")

global ColorControlClusterCS
ColorControlClusterCS = drvZigbeeComponent.createComboSymbol("COLORCONTROL_CLUSTER_CS",  ColorControlCluster, ["CLIENT","SERVER", "BOTH"])
ColorControlClusterCS.setLabel("Supported Implementation")
ColorControlClusterCS.setDefaultValue("")
ColorControlClusterCS.setVisible(False)
ColorControlClusterCS.setDescription("COLORCONTROL CLUSTER Supported Implementation- check the box to enable")
ColorControlClusterCS.setDependencies(ColorControlClusterCsCheck,["COLORCONTROL_CLUSTER_ENABLE"])

ColorControlClusterClientMenu = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_CLIENT_MENU", ColorControlCluster)
ColorControlClusterClientMenu.setLabel("Client")
ColorControlClusterClientMenu.setVisible(False)
ColorControlClusterClientMenu.setDescription("COLORCONTROL CLUSTER CLIENT")
ColorControlClusterClientMenu.setDependencies(ColorControlClusterClientCheck,["COLORCONTROL_CLUSTER_CS","COLORCONTROL_CLUSTER_ENABLE"])

ColorControlClusterServerMenu = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_SERVER_MENU", ColorControlCluster)
ColorControlClusterServerMenu.setLabel("Server")
ColorControlClusterServerMenu.setVisible(False)
ColorControlClusterServerMenu.setDescription("COLORCONTROL CLUSTER SERVER")
ColorControlClusterServerMenu.setDependencies(ColorControlClusterServerCheck,["COLORCONTROL_CLUSTER_CS","COLORCONTROL_CLUSTER_ENABLE"])

ColorControlClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_CLIENT__ATTRIBUTES_MENU", ColorControlClusterClientMenu)
ColorControlClusterClientAttributes.setLabel("Attributes")
#ColorControlClusterClientAttributes.setVisible(False)
ColorControlClusterClientAttributes.setDescription("COLORCONTROL CLUSTER CLIENT ATTRIBUTES")
ColorControlClusterClientAttributes.setDependencies(ColorControlClusterClientCheck,["COLORCONTROL_CLUSTER_CS"])

ColorControlClusterClientCommands = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_CLIENT__COMMANDS_MENU", ColorControlClusterClientMenu)
ColorControlClusterClientCommands.setLabel("Commands")
#ColorControlClusterClientCommands.setVisible(False)
ColorControlClusterClientCommands.setDescription("COLORCONTROL CLUSTER CLIENT COMMANDS")
ColorControlClusterClientCommands.setDependencies(ColorControlClusterClientCheck,["COLORCONTROL_CLUSTER_CS"])

ColorControlClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_SERVER__ATTRIBUTES_MENU", ColorControlClusterServerMenu)
ColorControlClusterServerAttributes.setLabel("Attributes")
#ColorControlClusterServerAttributes.setVisible(False)
ColorControlClusterServerAttributes.setDescription("COLORCONTROL CLUSTER SERVER ATTRIBUTES")
ColorControlClusterServerAttributes.setDependencies(ColorControlClusterServerCheck,["COLORCONTROL_CLUSTER_CS"])

ColorControlClusterServerCommands = drvZigbeeComponent.createMenuSymbol("COLORCONTROL_CLUSTER_SERVER__COMMANDS_MENU", ColorControlClusterServerMenu)
ColorControlClusterServerCommands.setLabel("Commands")
#ColorControlClusterServerCommands.setVisible(False)
ColorControlClusterServerCommands.setDescription("COLORCONTROL CLUSTER SERVER COMMANDS")
ColorControlClusterServerCommands.setDependencies(ColorControlClusterServerCheck,["COLORCONTROL_CLUSTER_CS"])

#################               Server Attributes                                 ###############
global ColorCtrlClusterServerAttributeCurrentHue
ColorCtrlClusterServerAttributeCurrentHue = drvZigbeeComponent.createBooleanSymbol("CC_CURRENTHUE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeCurrentHue.setLabel("0x0000 CurrentHue")
ColorCtrlClusterServerAttributeCurrentHue.setDefaultValue(True)

global ColorCtrlClusterServerAttributeCurrentSaturation
ColorCtrlClusterServerAttributeCurrentSaturation = drvZigbeeComponent.createBooleanSymbol("CC_CURRENTSATURATION", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeCurrentSaturation.setLabel("0x0001 CurrentSaturation")
ColorCtrlClusterServerAttributeCurrentSaturation.setDefaultValue(True)

global ColorCtrlClusterServerAttributeRemainingTime
ColorCtrlClusterServerAttributeRemainingTime = drvZigbeeComponent.createBooleanSymbol("CC_REMAININGTIME", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeRemainingTime.setLabel("0x0002 RemainingTime")
ColorCtrlClusterServerAttributeRemainingTime.setDefaultValue(True)

global ColorCtrlClusterServerAttributeCurrentX
ColorCtrlClusterServerAttributeCurrentX = drvZigbeeComponent.createBooleanSymbol("CC_CURRENTX", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeCurrentX.setLabel("0x0003 CurrentX")
ColorCtrlClusterServerAttributeCurrentX.setDefaultValue(True)
ColorCtrlClusterServerAttributeCurrentX.setReadOnly(True)

global ColorCtrlClusterServerAttributeCurrentY
ColorCtrlClusterServerAttributeCurrentY = drvZigbeeComponent.createBooleanSymbol("CC_CURRENTY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeCurrentY.setLabel("0x0004 CurrentY")
ColorCtrlClusterServerAttributeCurrentY.setDefaultValue(True)
ColorCtrlClusterServerAttributeCurrentY.setReadOnly(True)

# global ColorCtrlClusterServerAttributeDriftCompensation
# ColorCtrlClusterServerAttributeDriftCompensation = drvZigbeeComponent.createBooleanSymbol("CC_DRIFTCOMPENSATION", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeDriftCompensation.setLabel("0x0005 DriftCompensation")
# ColorCtrlClusterServerAttributeDriftCompensation.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeCompensationText
# ColorCtrlClusterServerAttributeCompensationText = drvZigbeeComponent.createBooleanSymbol("CC_COMPENSATIONTEXT", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeCompensationText.setLabel("0x0006 CompensationText")
# ColorCtrlClusterServerAttributeCompensationText.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorTemperatureMireds
ColorCtrlClusterServerAttributeColorTemperatureMireds = drvZigbeeComponent.createBooleanSymbol("CC_COLORTEMPMIREDS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorTemperatureMireds.setLabel("0x0007 ColorTemperatureMireds")
ColorCtrlClusterServerAttributeColorTemperatureMireds.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorMode
ColorCtrlClusterServerAttributeColorMode = drvZigbeeComponent.createBooleanSymbol("CC_COLORMODE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorMode.setLabel("0x0008 ColorMode")
ColorCtrlClusterServerAttributeColorMode.setDefaultValue(True)
ColorCtrlClusterServerAttributeColorMode.setReadOnly(True)

global ColorCtrlClusterServerAttributeOptions
ColorCtrlClusterServerAttributeOptions = drvZigbeeComponent.createBooleanSymbol("CC_OPTIONS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeOptions.setLabel("0x000F Options")
ColorCtrlClusterServerAttributeOptions.setDefaultValue(True)
ColorCtrlClusterServerAttributeOptions.setReadOnly(True)

global ColorCtrlClusterServerAttributeNumberOfPrimaries
ColorCtrlClusterServerAttributeNumberOfPrimaries = drvZigbeeComponent.createBooleanSymbol("CC_NUMBEROFPRIMARIES", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeNumberOfPrimaries.setLabel("0x0010 NumberOfPrimaries")
ColorCtrlClusterServerAttributeNumberOfPrimaries.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary1X
ColorCtrlClusterServerAttributePrimary1X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY1X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary1X.setLabel("0x0011 Primary1X")
ColorCtrlClusterServerAttributePrimary1X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary1Y
ColorCtrlClusterServerAttributePrimary1Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY1Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary1Y.setLabel("0x0012 Primary1Y")
ColorCtrlClusterServerAttributePrimary1Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary1Intensity
ColorCtrlClusterServerAttributePrimary1Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY1INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary1Intensity.setLabel("0x0013 Primary1Intensity")
ColorCtrlClusterServerAttributePrimary1Intensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary2X
ColorCtrlClusterServerAttributePrimary2X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY2X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary2X.setLabel("0x0015 Primary2X")
ColorCtrlClusterServerAttributePrimary2X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary2Y
ColorCtrlClusterServerAttributePrimary2Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY2Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary2Y.setLabel("0x0016 Primary2Y")
ColorCtrlClusterServerAttributePrimary2Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary2Intensity
ColorCtrlClusterServerAttributePrimary2Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY2INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary2Intensity.setLabel("0x0017 Primary2Intensity")
ColorCtrlClusterServerAttributePrimary2Intensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary3X
ColorCtrlClusterServerAttributePrimary3X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY3X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary3X.setLabel("0x0019 Primary3X")
ColorCtrlClusterServerAttributePrimary3X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary3Y
ColorCtrlClusterServerAttributePrimary3Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY3Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary3Y.setLabel("0x001A Primary3Y")
ColorCtrlClusterServerAttributePrimary3Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary3Intensity
ColorCtrlClusterServerAttributePrimary3Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY3INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary3Intensity.setLabel("0x001B Primary3Intensity")
ColorCtrlClusterServerAttributePrimary3Intensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary4X
ColorCtrlClusterServerAttributePrimary4X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY4X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary4X.setLabel("0x0020 Primary4X")
ColorCtrlClusterServerAttributePrimary4X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary4Y
ColorCtrlClusterServerAttributePrimary4Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY4Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary4Y.setLabel("0x0021 Primary4Y")
ColorCtrlClusterServerAttributePrimary4Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary4Intensity
ColorCtrlClusterServerAttributePrimary4Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY4INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary4Intensity.setLabel("0x0022 Primary4Intensity")
ColorCtrlClusterServerAttributePrimary4Intensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary5X
ColorCtrlClusterServerAttributePrimary5X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY5X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary5X.setLabel("0x0024 Primary5X")
ColorCtrlClusterServerAttributePrimary5X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary5Y
ColorCtrlClusterServerAttributePrimary5Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY5Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary5Y.setLabel("0x0025 Primary5Y")
ColorCtrlClusterServerAttributePrimary5Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary5Intensity
ColorCtrlClusterServerAttributePrimary5Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY5INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary5Intensity.setLabel("0x0026 Primary5Intensity")
ColorCtrlClusterServerAttributePrimary5Intensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary6X
ColorCtrlClusterServerAttributePrimary6X = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY6X", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary6X.setLabel("0x0028 Primary6X")
ColorCtrlClusterServerAttributePrimary6X.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary6Y
ColorCtrlClusterServerAttributePrimary6Y = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY6Y", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary6Y.setLabel("0x0029 Primary6Y")
ColorCtrlClusterServerAttributePrimary6Y.setDefaultValue(True)

global ColorCtrlClusterServerAttributePrimary6Intensity
ColorCtrlClusterServerAttributePrimary6Intensity = drvZigbeeComponent.createBooleanSymbol("CC_PRIMARY6INTENSITY", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributePrimary6Intensity.setLabel("0x002A Primary6Intensity")
ColorCtrlClusterServerAttributePrimary6Intensity.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeWhitePointX
# ColorCtrlClusterServerAttributeWhitePointX = drvZigbeeComponent.createBooleanSymbol("CC_WHITEPOINTX", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeWhitePointX.setLabel("0x0030 WhitePointX")
# ColorCtrlClusterServerAttributeWhitePointX.setDefaultValue(True)
# ColorCtrlClusterServerAttributeWhitePointX.setReadOnly(True)

# global ColorCtrlClusterServerAttributeWhitePointY
# ColorCtrlClusterServerAttributeWhitePointY = drvZigbeeComponent.createBooleanSymbol("CC_WHITEPOINTY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeWhitePointY.setLabel("0x0031 WhitePointY")
# ColorCtrlClusterServerAttributeWhitePointY.setDefaultValue(True)
# ColorCtrlClusterServerAttributeWhitePointY.setReadOnly(True)

# global ColorCtrlClusterServerAttributeColorPointRX
# ColorCtrlClusterServerAttributeColorPointRX = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTRX", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointRX.setLabel("0x0032 ColorPointRX")
# ColorCtrlClusterServerAttributeColorPointRX.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointRY
# ColorCtrlClusterServerAttributeColorPointRY = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTRY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointRY.setLabel("0x0033 ColorPointRY")
# ColorCtrlClusterServerAttributeColorPointRY.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointRIntensity
# ColorCtrlClusterServerAttributeColorPointRIntensity = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTRINTENSITY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointRIntensity.setLabel("0x0034 ColorPointRIntensity")
# ColorCtrlClusterServerAttributeColorPointRIntensity.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointGX
# ColorCtrlClusterServerAttributeColorPointGX = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTGX", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointGX.setLabel("0x0035 ColorPointGX")
# ColorCtrlClusterServerAttributeColorPointGX.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointGY
# ColorCtrlClusterServerAttributeColorPointGY = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTGY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointGY.setLabel("0x0037 ColorPointGY")
# ColorCtrlClusterServerAttributeColorPointGY.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointGIntensity
# ColorCtrlClusterServerAttributeColorPointGIntensity = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTGINTENSITY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointGIntensity.setLabel("0x0038 ColorPointGIntensity")
# ColorCtrlClusterServerAttributeColorPointGIntensity.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointBX
# ColorCtrlClusterServerAttributeColorPointBX = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTBX", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointBX.setLabel("0x003A ColorPointBX")
# ColorCtrlClusterServerAttributeColorPointBX.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointBY
# ColorCtrlClusterServerAttributeColorPointBY = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTBY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointBY.setLabel("0x003B ColorPointBY")
# ColorCtrlClusterServerAttributeColorPointBY.setDefaultValue(True)

# global ColorCtrlClusterServerAttributeColorPointBIntensity
# ColorCtrlClusterServerAttributeColorPointBIntensity = drvZigbeeComponent.createBooleanSymbol("CC_COLORPOINTBINTENSITY", ColorControlClusterServerAttributes)
# ColorCtrlClusterServerAttributeColorPointBIntensity.setLabel("0x003C ColorPointBIntensity")
# ColorCtrlClusterServerAttributeColorPointBIntensity.setDefaultValue(True)

global ColorCtrlClusterServerAttributeEnhancedCurrentHue
ColorCtrlClusterServerAttributeEnhancedCurrentHue = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDCURRENTHUE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeEnhancedCurrentHue.setLabel("0x4000 EnhancedCurrentHue")
ColorCtrlClusterServerAttributeEnhancedCurrentHue.setDefaultValue(True)

global ColorCtrlClusterServerAttributeEnhancedColorMode
ColorCtrlClusterServerAttributeEnhancedColorMode = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDCOLORMODE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeEnhancedColorMode.setLabel("0x4001 EnhancedColorMode")
ColorCtrlClusterServerAttributeEnhancedColorMode.setDefaultValue(True)
ColorCtrlClusterServerAttributeEnhancedColorMode.setReadOnly(True)

global ColorCtrlClusterServerAttributeColorLoopActive
ColorCtrlClusterServerAttributeColorLoopActive = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPACTIVE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorLoopActive.setLabel("0x4002 ColorLoopActive")
ColorCtrlClusterServerAttributeColorLoopActive.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorLoopDirection
ColorCtrlClusterServerAttributeColorLoopDirection = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPDIRECTION", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorLoopDirection.setLabel("0x4003 ColorLoopDirection")
ColorCtrlClusterServerAttributeColorLoopDirection.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorLoopTime
ColorCtrlClusterServerAttributeColorLoopTime = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPTIME", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorLoopTime.setLabel("0x4004 ColorLoopTime")
ColorCtrlClusterServerAttributeColorLoopTime.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorLoopStartEnhancedHue
ColorCtrlClusterServerAttributeColorLoopStartEnhancedHue = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPSTARTENHANCEDHUE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorLoopStartEnhancedHue.setLabel("0x4005 ColorLoopStartEnhancedHue")
ColorCtrlClusterServerAttributeColorLoopStartEnhancedHue.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorLoopStoredEnhancedHue
ColorCtrlClusterServerAttributeColorLoopStoredEnhancedHue = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPSTOREDENHANCEDHUE", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorLoopStoredEnhancedHue.setLabel("0x4006 ColorLoopStoredEnhancedHue")
ColorCtrlClusterServerAttributeColorLoopStoredEnhancedHue.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorCapabilities
ColorCtrlClusterServerAttributeColorCapabilities = drvZigbeeComponent.createBooleanSymbol("CC_COLORCAPABILITIES", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorCapabilities.setLabel("0x400A ColorCapabilities")
ColorCtrlClusterServerAttributeColorCapabilities.setDefaultValue(True)
ColorCtrlClusterServerAttributeColorCapabilities.setReadOnly(True)

global ColorCtrlClusterServerAttributeColorTempPhysicalMinMireds
ColorCtrlClusterServerAttributeColorTempPhysicalMinMireds = drvZigbeeComponent.createBooleanSymbol("CC_COLORTEMPPHYMINMIREDS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorTempPhysicalMinMireds.setLabel("0x400B ColorTempPhysicalMinMireds")
ColorCtrlClusterServerAttributeColorTempPhysicalMinMireds.setDefaultValue(True)

global ColorCtrlClusterServerAttributeColorTempPhysicalMaxMireds
ColorCtrlClusterServerAttributeColorTempPhysicalMaxMireds = drvZigbeeComponent.createBooleanSymbol("CC_COLORTEMPPHYMAXMIREDS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeColorTempPhysicalMaxMireds.setLabel("0x400C ColorTempPhysicalMaxMireds")
ColorCtrlClusterServerAttributeColorTempPhysicalMaxMireds.setDefaultValue(True)

global ColorCtrlClusterServerAttributeCoupleColorTempToLevelMinMireds
ColorCtrlClusterServerAttributeCoupleColorTempToLevelMinMireds = drvZigbeeComponent.createBooleanSymbol("CC_COUPLECOLORTEMPTOLEVELMINMIREDS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeCoupleColorTempToLevelMinMireds.setLabel("0x400D CoupleColorTempToLevelMinMireds")
ColorCtrlClusterServerAttributeCoupleColorTempToLevelMinMireds.setDefaultValue(True)

global ColorCtrlClusterServerAttributeStartUpColorTemperatureMireds
ColorCtrlClusterServerAttributeStartUpColorTemperatureMireds = drvZigbeeComponent.createBooleanSymbol("CC_STARTUPCOLORTEMPMIREDS", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeStartUpColorTemperatureMireds.setLabel("0x4010 StartUpColorTemperatureMireds")
ColorCtrlClusterServerAttributeStartUpColorTemperatureMireds.setDefaultValue(True)

global ColorCtrlClusterServerAttributeClusterRevision
ColorCtrlClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("CC_CLUSTERREVISION", ColorControlClusterServerAttributes)
ColorCtrlClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
ColorCtrlClusterServerAttributeClusterRevision.setDefaultValue(True)
ColorCtrlClusterServerAttributeClusterRevision.setReadOnly(True)

global ColorControlClusterServerAttributeCount
ColorControlClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("CC_SERVERATTRIBUTECOUNT", ColorControlClusterServerAttributes)
ColorControlClusterServerAttributeCount.setLabel("Attributes Count")
ColorControlClusterServerAttributeCount.setDefaultValue(ColorControlClusterServerAttributeCountUpdate(0,0))
ColorControlClusterServerAttributeCount.setVisible(True)
ColorControlClusterServerAttributeCount.setDescription("Attributes Count")
ColorControlClusterServerAttributeCount.setReadOnly(True)
ColorControlClusterServerAttributeCount.setDependencies(ColorControlClusterServerAttributeCountUpdate,["CC_CURRENTHUE","CC_CURRENTSATURATION","CC_REMAININGTIME","CC_CURRENTX","CC_CURRENTY","CC_DRIFTCOMPENSATION","CC_COMPENSATIONTEXT","CC_COLORTEMPMIREDS","CC_COLORMODE","CC_OPTIONS","CC_NUMBEROFPRIMARIES","CC_PRIMARY1X","CC_PRIMARY1Y","CC_PRIMARY1INTENSITY","CC_PRIMARY2X",                                                                                         "CC_PRIMARY2Y","CC_PRIMARY2INTENSITY","CC_PRIMARY3X","CC_PRIMARY3Y","CC_PRIMARY3INTENSITY","CC_PRIMARY4X","CC_PRIMARY4Y",                                                                                         "CC_PRIMARY4INTENSITY","CC_PRIMARY5X","CC_PRIMARY5Y","CC_PRIMARY5INTENSITY","CC_PRIMARY6X","CC_PRIMARY6Y","CC_PRIMARY6INTENSITY",                                                                                        "CC_WHITEPOINTX","CC_WHITEPOINTY","CC_COLORPOINTRX","CC_COLORPOINTRY","CC_COLORPOINTRINTENSITY","CC_COLORPOINTGX","CC_COLORPOINTGY",                                                                                        "CC_COLORPOINTGINTENSITY","CC_COLORPOINTBX","CC_COLORPOINTBY","CC_COLORPOINTBINTENSITY","CC_ENHANCEDCURRENTHUE","CC_ENHANCEDCOLORMODE","CC_COLORLOOPACTIVE",	
                                                                                                        "CC_COLORLOOPDIRECTION","CC_COLORLOOPTIME","CC_COLORLOOPSTARTENHANCEDHUE","CC_COLORLOOPSTOREDENHANCEDHUE","CC_COLORCAPABILITIES","CC_COLORTEMPPHYMINMIREDS","CC_COLORTEMPPHYMAXMIREDS","CC_COUPLECOLORTEMPTOLEVELMINMIREDS","CC_STARTUPCOLORTEMPMIREDS","CC_CLUSTERREVISION"])

#################               Server Commands                                 ###############

# Commands received
global ColorCtrlClusterServerCmdMoveToHue
ColorCtrlClusterServerCmdMoveToHue = drvZigbeeComponent.createBooleanSymbol("CC_MOVETOHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveToHue.setLabel("0x00.Rx Move to hue")
ColorCtrlClusterServerCmdMoveToHue.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveToHue.setDescription("Receive Move to hue command - check the box to enable")

global ColorCtrlClusterServerCmdMoveHue
ColorCtrlClusterServerCmdMoveHue = drvZigbeeComponent.createBooleanSymbol("CC_MOVEHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveHue.setLabel("0x01.Rx Move hue")
ColorCtrlClusterServerCmdMoveHue.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveHue.setDescription("Receive Move hue command - check the box to enable")

global ColorCtrlClusterServerCmdStepHue
ColorCtrlClusterServerCmdStepHue = drvZigbeeComponent.createBooleanSymbol("CC_STEPHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdStepHue.setLabel("0x02.Rx Step hue")
ColorCtrlClusterServerCmdStepHue.setDefaultValue(True)
ColorCtrlClusterServerCmdStepHue.setDescription("Receive Step hue command - check the box to enable")

global ColorCtrlClusterServerCmdMovetoSat
ColorCtrlClusterServerCmdMovetoSat = drvZigbeeComponent.createBooleanSymbol("CC_MOVETOSATURATION", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMovetoSat.setLabel("0x03.Rx Move to saturation")
ColorCtrlClusterServerCmdMovetoSat.setDefaultValue(True)
ColorCtrlClusterServerCmdMovetoSat.setDescription("Receive Move to saturation command - check the box to enable")

global ColorCtrlClusterServerCmdMoveSat
ColorCtrlClusterServerCmdMoveSat = drvZigbeeComponent.createBooleanSymbol("CC_MOVESATURATION", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveSat.setLabel("0x04.Rx Move saturation")
ColorCtrlClusterServerCmdMoveSat.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveSat.setDescription("Receive Move saturation command - check the box to enable")

global ColorCtrlClusterServerCmdStepSat
ColorCtrlClusterServerCmdStepSat = drvZigbeeComponent.createBooleanSymbol("CC_STEPSATURATION", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdStepSat.setLabel("0x05.Rx Step saturation")
ColorCtrlClusterServerCmdStepSat.setDefaultValue(True)
ColorCtrlClusterServerCmdStepSat.setDescription("Receive Step saturation command - check the box to enable")

global ColorCtrlClusterServerCmdMovetoHueSat
ColorCtrlClusterServerCmdMovetoHueSat = drvZigbeeComponent.createBooleanSymbol("CC_MOVETOHUESATURATION", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMovetoHueSat.setLabel("0x06.Rx Move to hue and saturation")
ColorCtrlClusterServerCmdMovetoHueSat.setDefaultValue(True)
ColorCtrlClusterServerCmdMovetoHueSat.setDescription("Receive Move to hue and saturation command - check the box to enable")

global ColorCtrlClusterServerCmdMoveToColor
ColorCtrlClusterServerCmdMoveToColor = drvZigbeeComponent.createBooleanSymbol("CC_MOVETOCOLOR", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveToColor.setLabel("0x07.Rx Move to color")
ColorCtrlClusterServerCmdMoveToColor.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveToColor.setDescription("Receive Move to color command - check the box to enable")
ColorCtrlClusterServerCmdMoveToColor.setReadOnly(True)

global ColorCtrlClusterServerCmdMoveColor
ColorCtrlClusterServerCmdMoveColor = drvZigbeeComponent.createBooleanSymbol("CC_MOVECOLOR", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveColor.setLabel("0x08.Rx Move color")
ColorCtrlClusterServerCmdMoveColor.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveColor.setDescription("Receive Move color command - check the box to enable")
ColorCtrlClusterServerCmdMoveColor.setReadOnly(True)

global ColorCtrlClusterServerCmdStepColor
ColorCtrlClusterServerCmdStepColor = drvZigbeeComponent.createBooleanSymbol("CC_STEPCOLOR", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdStepColor.setLabel("0x09.Rx Step color")
ColorCtrlClusterServerCmdStepColor.setDefaultValue(True)
ColorCtrlClusterServerCmdStepColor.setDescription("Receive Step color command - check the box to enable")
ColorCtrlClusterServerCmdStepColor.setReadOnly(True)

global ColorCtrlClusterServerCmdMoveToColorTemp
ColorCtrlClusterServerCmdMoveToColorTemp = drvZigbeeComponent.createBooleanSymbol("CC_MOVETOCOLORTEMP", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveToColorTemp.setLabel("0x0A.Rx Move to color temperature")
ColorCtrlClusterServerCmdMoveToColorTemp.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveToColorTemp.setDescription("Receive Move to color temperature command - check the box to enable")

global ColorCtrlClusterServerCmdEnhancedMoveToHue
ColorCtrlClusterServerCmdEnhancedMoveToHue = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDMOVETOHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdEnhancedMoveToHue.setLabel("0x40.Rx Enhanced move to hue")
ColorCtrlClusterServerCmdEnhancedMoveToHue.setDefaultValue(True)
ColorCtrlClusterServerCmdEnhancedMoveToHue.setDescription("Receive Enhanced move to hue command - check the box to enable")
ColorCtrlClusterServerCmdEnhancedMoveToHue.setReadOnly(True)

global ColorCtrlClusterServerCmdEnhancedMoveHue
ColorCtrlClusterServerCmdEnhancedMoveHue = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDMOVEHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdEnhancedMoveHue.setLabel("0x41.Rx Enhanced move hue")
ColorCtrlClusterServerCmdEnhancedMoveHue.setDefaultValue(True)
ColorCtrlClusterServerCmdEnhancedMoveHue.setDescription("Receive Enhanced move hue command - check the box to enable")
ColorCtrlClusterServerCmdEnhancedMoveHue.setReadOnly(True)

global ColorCtrlClusterServerCmdEnhancedStepHue
ColorCtrlClusterServerCmdEnhancedStepHue = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDSTEPHUE", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdEnhancedStepHue.setLabel("0x42.Rx Enhanced step hue")
ColorCtrlClusterServerCmdEnhancedStepHue.setDefaultValue(True)
ColorCtrlClusterServerCmdEnhancedStepHue.setDescription("Receive Enhanced step hue command - check the box to enable")
ColorCtrlClusterServerCmdEnhancedStepHue.setReadOnly(True)

global ColorCtrlClusterServerCmdEnhancedMovetoHueSat
ColorCtrlClusterServerCmdEnhancedMovetoHueSat = drvZigbeeComponent.createBooleanSymbol("CC_ENHANCEDMOVETOHUESATURATION", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdEnhancedMovetoHueSat.setLabel("0x43.Rx Enhanced move to hue and saturation")
ColorCtrlClusterServerCmdEnhancedMovetoHueSat.setDefaultValue(True)
ColorCtrlClusterServerCmdEnhancedMovetoHueSat.setDescription("Receive Enhanced move to hue and saturation command - check the box to enable")
ColorCtrlClusterServerCmdEnhancedMovetoHueSat.setReadOnly(True)

global ColorCtrlClusterServerCmdColorloopset
ColorCtrlClusterServerCmdColorloopset = drvZigbeeComponent.createBooleanSymbol("CC_COLORLOOPSET", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdColorloopset.setLabel("0x44.Rx Color loop set")
ColorCtrlClusterServerCmdColorloopset.setDefaultValue(True)
ColorCtrlClusterServerCmdColorloopset.setDescription("Receive Color loop set command - check the box to enable")
ColorCtrlClusterServerCmdColorloopset.setReadOnly(True)

global ColorCtrlClusterServerCmdStopMoveStep
ColorCtrlClusterServerCmdStopMoveStep = drvZigbeeComponent.createBooleanSymbol("CC_STOPMOVESTEP", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdStopMoveStep.setLabel("0x47.Rx Stop move step")
ColorCtrlClusterServerCmdStopMoveStep.setDefaultValue(True)
ColorCtrlClusterServerCmdStopMoveStep.setDescription("Receive Stop move step command - check the box to enable")
ColorCtrlClusterServerCmdStopMoveStep.setReadOnly(True)

global ColorCtrlClusterServerCmdMoveTocolortemp
ColorCtrlClusterServerCmdMoveTocolortemp = drvZigbeeComponent.createBooleanSymbol("CC_MOVTOECOLORTEMP", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMoveTocolortemp.setLabel("0x4A.Rx Move To color temperature")
ColorCtrlClusterServerCmdMoveTocolortemp.setDefaultValue(True)
ColorCtrlClusterServerCmdMoveTocolortemp.setDescription("Receive Move color temperature command - check the box to enable")
ColorCtrlClusterServerCmdMoveTocolortemp.setReadOnly(True)

global ColorCtrlClusterServerCmdMovecolortemp
ColorCtrlClusterServerCmdMovecolortemp = drvZigbeeComponent.createBooleanSymbol("CC_MOVECOLORTEMP", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdMovecolortemp.setLabel("0x4B.Rx Move color temperature")
ColorCtrlClusterServerCmdMovecolortemp.setDefaultValue(True)
ColorCtrlClusterServerCmdMovecolortemp.setDescription("Receive Move color temperature command - check the box to enable")
ColorCtrlClusterServerCmdMovecolortemp.setReadOnly(True)

global ColorCtrlClusterServerCmdStepcolortemp
ColorCtrlClusterServerCmdStepcolortemp = drvZigbeeComponent.createBooleanSymbol("CC_STEPCOLORTEMP", ColorControlClusterServerCommands)
ColorCtrlClusterServerCmdStepcolortemp.setLabel("0x4C.Rx Step color temperature")
ColorCtrlClusterServerCmdStepcolortemp.setDefaultValue(True)
ColorCtrlClusterServerCmdStepcolortemp.setDescription("Receive Step color temperature command - check the box to enable")
ColorCtrlClusterServerCmdStepcolortemp.setReadOnly(True)

global ColorCtrlClusterServerCommandCount
ColorCtrlClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("CCC_SERVERCOMMANDCOUNT", ColorControlClusterServerCommands)
ColorCtrlClusterServerCommandCount.setLabel("Commands Count")
ColorCtrlClusterServerCommandCount.setDefaultValue(ColorControlClusterServerCommandCountUpdate(0,0))
ColorCtrlClusterServerCommandCount.setVisible(True)
ColorCtrlClusterServerCommandCount.setDescription("Commands Count")
ColorCtrlClusterServerCommandCount.setReadOnly(True)
ColorCtrlClusterServerCommandCount.setDependencies(ColorControlClusterServerCommandCountUpdate,["CC_MOVETOHUE","CC_MOVEHUE","CC_STEPHUE","CC_MOVETOSATURATION","CC_MOVESATURATION","CC_STEPSATURATION","CC_MOVETOHUESATURATION","CC_MOVETOCOLOR","CC_MOVECOLOR","CC_STEPCOLOR","CC_MOVETOCOLORTEMP","CC_ENHANCEDMOVETOHUE","CC_ENHANCEDMOVEHUE","CC_ENHANCEDSTEPHUE","CC_ENHANCEDMOVETOHUESATURATION","CC_COLORLOOPSET","CC_STOPMOVESTEP","CC_MOVTOECOLORTEMP","CC_MOVECOLORTEMP","CC_STEPCOLORTEMP"])

#################               Client Attributes                               ###############

global ColorCtrlClusterClientAttributeClusterRevision
ColorCtrlClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("CCC_CLUSTERREVISION", ColorControlClusterClientAttributes)
ColorCtrlClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
ColorCtrlClusterClientAttributeClusterRevision.setDefaultValue(True)
ColorCtrlClusterClientAttributeClusterRevision.setReadOnly(True)

global ColorCtrlClusterClientAttributeCount
ColorCtrlClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("CCC_CLIENTATTRIBUTECOUNT", ColorControlClusterClientAttributes)
ColorCtrlClusterClientAttributeCount.setLabel("Attributes Count")
ColorCtrlClusterClientAttributeCount.setDefaultValue(ColorControlClusterClientAttributeCountUpdate(0,0))
ColorCtrlClusterClientAttributeCount.setVisible(True)
ColorCtrlClusterClientAttributeCount.setDescription("Attributes Count")
ColorCtrlClusterClientAttributeCount.setReadOnly(True)
ColorCtrlClusterClientAttributeCount.setDependencies(ColorControlClusterClientAttributeCountUpdate,["CCC_CLUSTERREVISION"])


#################               Client Commands                                 ###############

# Commands generated
global ColorCtrlClusterClientCmdMoveToHue
ColorCtrlClusterClientCmdMoveToHue = drvZigbeeComponent.createBooleanSymbol("CCC_MOVETOHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveToHue.setLabel("0x00.Tx Move to hue")
ColorCtrlClusterClientCmdMoveToHue.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveToHue.setDescription("Send Move to hue command - check the box to enable")

global ColorCtrlClusterClientCmdMoveHue
ColorCtrlClusterClientCmdMoveHue = drvZigbeeComponent.createBooleanSymbol("CCC_MOVEHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveHue.setLabel("0x01.Tx Move hue")
ColorCtrlClusterClientCmdMoveHue.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveHue.setDescription("Send Move hue command - check the box to enable")

global ColorCtrlClusterClientCmdStepHue
ColorCtrlClusterClientCmdStepHue = drvZigbeeComponent.createBooleanSymbol("CCC_STEPHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdStepHue.setLabel("0x02.Tx Step hue")
ColorCtrlClusterClientCmdStepHue.setDefaultValue(True)
ColorCtrlClusterClientCmdStepHue.setDescription("Send Step hue command - check the box to enable")

global ColorCtrlClusterClientCmdMovetoSat
ColorCtrlClusterClientCmdMovetoSat = drvZigbeeComponent.createBooleanSymbol("CCC_MOVETOSATURATION", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMovetoSat.setLabel("0x03.Tx Move to saturation")
ColorCtrlClusterClientCmdMovetoSat.setDefaultValue(True)
ColorCtrlClusterClientCmdMovetoSat.setDescription("Send Move to saturation command - check the box to enable")

global ColorCtrlClusterClientCmdMoveSat
ColorCtrlClusterClientCmdMoveSat = drvZigbeeComponent.createBooleanSymbol("CCC_MOVESATURATION", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveSat.setLabel("0x04.Tx Move saturation")
ColorCtrlClusterClientCmdMoveSat.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveSat.setDescription("Send Move saturation command - check the box to enable")

global ColorCtrlClusterClientCmdStepSat
ColorCtrlClusterClientCmdStepSat = drvZigbeeComponent.createBooleanSymbol("CCC_STEPSATURATION", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdStepSat.setLabel("0x05.Tx Step saturation")
ColorCtrlClusterClientCmdStepSat.setDefaultValue(True)
ColorCtrlClusterClientCmdStepSat.setDescription("Send Step saturation command - check the box to enable")

global ColorCtrlClusterClientCmdMovetoHueSat
ColorCtrlClusterClientCmdMovetoHueSat = drvZigbeeComponent.createBooleanSymbol("CCC_MOVETOHUESATURATION", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMovetoHueSat.setLabel("0x06.Tx Move to hue and saturation")
ColorCtrlClusterClientCmdMovetoHueSat.setDefaultValue(True)
ColorCtrlClusterClientCmdMovetoHueSat.setDescription("Send Move to hue and saturation command - check the box to enable")

global ColorCtrlClusterClientCmdMoveToColor
ColorCtrlClusterClientCmdMoveToColor = drvZigbeeComponent.createBooleanSymbol("CCC_MOVETOCOLOR", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveToColor.setLabel("0x07.Tx Move to color")
ColorCtrlClusterClientCmdMoveToColor.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveToColor.setDescription("Send Move to color command - check the box to enable")

global ColorCtrlClusterClientCmdMoveColor
ColorCtrlClusterClientCmdMoveColor = drvZigbeeComponent.createBooleanSymbol("CCC_MOVECOLOR", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveColor.setLabel("0x08.Tx Move color")
ColorCtrlClusterClientCmdMoveColor.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveColor.setDescription("Send Move color command - check the box to enable")

global ColorCtrlClusterClientCmdStepColor
ColorCtrlClusterClientCmdStepColor = drvZigbeeComponent.createBooleanSymbol("CCC_STEPCOLOR", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdStepColor.setLabel("0x09.Tx Step color")
ColorCtrlClusterClientCmdStepColor.setDefaultValue(True)
ColorCtrlClusterClientCmdStepColor.setDescription("Send Step color command - check the box to enable")

global ColorCtrlClusterClientCmdMoveToColorTemp
ColorCtrlClusterClientCmdMoveToColorTemp = drvZigbeeComponent.createBooleanSymbol("CCC_MOVETOCOLORTEMP", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMoveToColorTemp.setLabel("0x0A.Tx Move to color temperature")
ColorCtrlClusterClientCmdMoveToColorTemp.setDefaultValue(True)
ColorCtrlClusterClientCmdMoveToColorTemp.setDescription("Send Move to color temperature command - check the box to enable")

global ColorCtrlClusterClientCmdEnhancedMoveToHue
ColorCtrlClusterClientCmdEnhancedMoveToHue = drvZigbeeComponent.createBooleanSymbol("CCC_ENHANCEDMOVETOHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdEnhancedMoveToHue.setLabel("0x40.Tx Enhanced move to hue")
ColorCtrlClusterClientCmdEnhancedMoveToHue.setDefaultValue(True)
ColorCtrlClusterClientCmdEnhancedMoveToHue.setDescription("Send Enhanced move to hue command - check the box to enable")

global ColorCtrlClusterClientCmdEnhancedMoveHue
ColorCtrlClusterClientCmdEnhancedMoveHue = drvZigbeeComponent.createBooleanSymbol("CCC_ENHANCEDMOVEHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdEnhancedMoveHue.setLabel("0x41.Tx Enhanced move hue")
ColorCtrlClusterClientCmdEnhancedMoveHue.setDefaultValue(True)
ColorCtrlClusterClientCmdEnhancedMoveHue.setDescription("Send Enhanced move hue command - check the box to enable")

global ColorCtrlClusterClientCmdEnhancedStepHue
ColorCtrlClusterClientCmdEnhancedStepHue = drvZigbeeComponent.createBooleanSymbol("CCC_ENHANCEDSTEPHUE", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdEnhancedStepHue.setLabel("0x42.Tx Enhanced step hue")
ColorCtrlClusterClientCmdEnhancedStepHue.setDefaultValue(True)
ColorCtrlClusterClientCmdEnhancedStepHue.setDescription("Send Enhanced step hue command - check the box to enable")

global ColorCtrlClusterClientCmdEnhancedMovetoHueSat
ColorCtrlClusterClientCmdEnhancedMovetoHueSat = drvZigbeeComponent.createBooleanSymbol("CCC_ENHANCEDMOVETOHUESATURATION", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdEnhancedMovetoHueSat.setLabel("0x43.Tx Enhanced move to hue and saturation")
ColorCtrlClusterClientCmdEnhancedMovetoHueSat.setDefaultValue(True)
ColorCtrlClusterClientCmdEnhancedMovetoHueSat.setDescription("Send Enhanced move to hue and saturation command - check the box to enable")

global ColorCtrlClusterClientCmdColorloopset
ColorCtrlClusterClientCmdColorloopset = drvZigbeeComponent.createBooleanSymbol("CCC_COLORLOOPSET", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdColorloopset.setLabel("0x44.Tx Color loop set")
ColorCtrlClusterClientCmdColorloopset.setDefaultValue(True)
ColorCtrlClusterClientCmdColorloopset.setDescription("Send Color loop set command - check the box to enable")

global ColorCtrlClusterClientCmdStopMoveStep
ColorCtrlClusterClientCmdStopMoveStep = drvZigbeeComponent.createBooleanSymbol("CCC_STOPMOVESTEP", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdStopMoveStep.setLabel("0x47.Tx Stop move step")
ColorCtrlClusterClientCmdStopMoveStep.setDefaultValue(True)
ColorCtrlClusterClientCmdStopMoveStep.setDescription("Send Stop move step command - check the box to enable")

global ColorCtrlClusterClientCmdMovecolortemp
ColorCtrlClusterClientCmdMovecolortemp = drvZigbeeComponent.createBooleanSymbol("CCC_MOVECOLORTEMP", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdMovecolortemp.setLabel("0x4B.Tx Move color temperature")
ColorCtrlClusterClientCmdMovecolortemp.setDefaultValue(True)
ColorCtrlClusterClientCmdMovecolortemp.setDescription("Send Move color temperature command - check the box to enable")

global ColorCtrlClusterClientCmdStepcolortemp
ColorCtrlClusterClientCmdStepcolortemp = drvZigbeeComponent.createBooleanSymbol("CCC_STEPCOLORTEMP", ColorControlClusterClientCommands)
ColorCtrlClusterClientCmdStepcolortemp.setLabel("0x4C.Tx Step color temperature")
ColorCtrlClusterClientCmdStepcolortemp.setDefaultValue(True)
ColorCtrlClusterClientCmdStepcolortemp.setDescription("Send Step color temperature command - check the box to enable")

global ColorCtrlClusterClientCommandCount
ColorCtrlClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("CCC_CLIENTCOMMANDCOUNT", ColorControlClusterClientCommands)
ColorCtrlClusterClientCommandCount.setLabel("Commands Count")
ColorCtrlClusterClientCommandCount.setDefaultValue(ColorControlClusterClientCommandCountUpdate(0,0))
ColorCtrlClusterClientCommandCount.setVisible(True)
ColorCtrlClusterClientCommandCount.setDescription("Commands Count")
ColorCtrlClusterClientCommandCount.setReadOnly(True)
ColorCtrlClusterClientCommandCount.setDependencies(ColorControlClusterClientCommandCountUpdate, ["CCC_MOVETOHUE","CCC_MOVEHUE","CCC_STEPHUE","CCC_MOVETOSATURATION","CCC_MOVESATURATION","CCC_STEPSATURATION","CCC_MOVETOHUESATURATION","CCC_MOVETOCOLOR","CCC_MOVECOLOR","CCC_STEPCOLOR","CCC_MOVETOCOLORTEMP","CCC_ENHANCEDMOVETOHUE","CCC_ENHANCEDMOVEHUE","CCC_ENHANCEDSTEPHUE","CCC_ENHANCEDMOVETOHUESATURATION","CCC_COLORLOOPSET","CCC_STOPMOVESTEP","CCC_MOVTOECOLORTEMP","CCC_MOVECOLORTEMP","CCC_STEPCOLORTEMP"])
############################################################################################################
# Default Values Settings based on device type
colorControlClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# COLORControl CLUSTER Common header
colorControlClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCONTROL_CLUSTER_CONF2", None)
colorControlClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/zclZllColorControlCluster.h.ftl")
colorControlClusterConf.setOutputName("zclZllColorControlCluster.h")
colorControlClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
colorControlClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
colorControlClusterConf.setType("HEADER")
colorControlClusterConf.setOverwrite(True)
colorControlClusterConf.setMarkup(True)

colorControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCLUSTER_CONF_SRC1", None)
colorControlClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/colorControlCluster.c.ftl")
colorControlClusterConfSrc.setOutputName("colorControlCluster.c")
colorControlClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
colorControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
colorControlClusterConfSrc.setType("SOURCE")
colorControlClusterConfSrc.setOverwrite(True)
colorControlClusterConfSrc.setMarkup(True)
colorControlClusterConfSrc.setEnabled(ColorControlCluster.getValue())
colorControlClusterConfSrc.setDependencies(ColorControlClusterEnableCheck,["COLORCONTROL_CLUSTER_ENABLE"])

# COLORCONTROL CLUSTER - Light
colorControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCONTROL_CLUSTER_CONF_SRC_LIGHT", None)
colorControlClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/lightColorControlCluster.c.ftl")
colorControlClusterConfSrc.setOutputName("lightColorControlCluster.c")
colorControlClusterConfSrc.setDestPath("/zigbee/z3device/light")
colorControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
colorControlClusterConfSrc.setType("SOURCE")
colorControlClusterConfSrc.setOverwrite(True)
colorControlClusterConfSrc.setMarkup(True)
colorControlClusterConfSrc.setEnabled(checkDevTypeLight)

# COLORCONTROL CLUSTER - Custom
colorControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCONTROL_CLUSTER_CONF_SRC_CUSTOM", None)
colorControlClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/customColorControlCluster.c.ftl")
colorControlClusterConfSrc.setOutputName("customColorControlCluster.c")
colorControlClusterConfSrc.setDestPath("/zigbee/z3device/custom")
colorControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
colorControlClusterConfSrc.setType("SOURCE")
colorControlClusterConfSrc.setOverwrite(True)
colorControlClusterConfSrc.setMarkup(True)
colorControlClusterConfSrc.setEnabled(checkDevTypeCustom and ColorControlCluster.getValue())
colorControlClusterConfSrc.setDependencies(customColorControlClusterEnableCheck,["COLORCONTROL_CLUSTER_ENABLE"])

# COLORCONTROL CLUSTER - Color Scene Controller
colorControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCONTROL_CLUSTER_CONF_SRC_CSC", None)
colorControlClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/cscColorControlCluster.c.ftl")
colorControlClusterConfSrc.setOutputName("cscColorControlCluster.c")
colorControlClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
colorControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
colorControlClusterConfSrc.setType("SOURCE")
colorControlClusterConfSrc.setOverwrite(True)
colorControlClusterConfSrc.setMarkup(True)
colorControlClusterConfSrc.setEnabled(checkDevTypeRemote)

# COLORCONTROL CLUSTER - Combined Interface
colorControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_COLORCONTROL_CLUSTER_CONF_SRC_CI", None)
colorControlClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/colorControl/ciColorControlCluster.c.ftl")
colorControlClusterConfSrc.setOutputName("ciColorControlCluster.c")
colorControlClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
colorControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
colorControlClusterConfSrc.setType("SOURCE")
colorControlClusterConfSrc.setOverwrite(True)
colorControlClusterConfSrc.setMarkup(True)
colorControlClusterConfSrc.setEnabled(checkDevTypeCombInterface)
############################################################################################################
