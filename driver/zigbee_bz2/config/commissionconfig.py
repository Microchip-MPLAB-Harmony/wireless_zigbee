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

###################################################################################################################
###############################               COMMISSIONING CONFIGURATION                           ###############
###################################################################################################################
######################################## Function definitions #####################################################
def JoinViaInstallCodeCheck(symbol, event):
    if (commnConfigInstallCodeJoin.getValue() == False):
        symbol.setVisible(False)
        symbol.setEnabled(False)
    else:
        symbol.setVisible(True)
        symbol.setEnabled(True)
        if ((commnConfigNWKFormation.getValue() == True) and (zigbeeDeviceType.getValue() != "ZIGBEE_COMBINED_INTERFACE")):
            Log.writeErrorMessage("Note: Network Formation Commissioning is disabled since install code based joining is enabled")
            commnConfigNWKFormation.setValue(False)

def JoinViaInstallCodeDevAddr(symbol, event):
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_COMBINED_INTERFACE") or ((stackConfigDeviceType.getValue() == 0) and (zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM"))):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

######################################## Configuration definitions #####################################################

# Auto Commissioning
global commnConfigAutoCommissioning
commnConfigAutoCommissioning = drvZigbeeComponent.createBooleanSymbol("AUTOMATIC_COMMISSIONING_ON_STARTUP", commissioningConfigMenu)
commnConfigAutoCommissioning.setLabel("AUTOMATIC COMMISSIONING ON STARTUP")
commnConfigAutoCommissioning.setDefaultValue(True)
commnConfigAutoCommissioning.setDescription("AUTOMATIC_COMMISSIONING_ON_STARTUP- check the box to enable")

# Network Formation Commissioning
global commnConfigNWKFormation
commnConfigNWKFormation = drvZigbeeComponent.createBooleanSymbol("NETWORK_FORMATION", commissioningConfigMenu)
commnConfigNWKFormation.setLabel("Network Formation Commissioning Enable")
commnConfigNWKFormation.setDefaultValue(NetworkFormationCommnSetCheck())
commnConfigNWKFormation.setDescription("Network Formation- check the box to enable")
commnConfigNWKFormation.setDependencies(stackDevTypeForcommnConfigNwkFormationEvent, ["STACK_DEVICE_TYPE"])

# Network Steering Commissioning
global commnConfigNWKSteering
commnConfigNWKSteering = drvZigbeeComponent.createBooleanSymbol("NETWORK_STEERING", commissioningConfigMenu)
commnConfigNWKSteering.setLabel("Network Steering Commissioning Enable")
commnConfigNWKSteering.setDefaultValue(NetworkSteeringCommnSetCheck())
commnConfigNWKSteering.setDescription("Network Steering- check the box to enable")
commnConfigNWKSteering.setDependencies(stackDevTypeForcommnConfigNwkSteeringEvent, ["STACK_DEVICE_TYPE"])

# Touchlink Commissioning
global commnConfigTouchlink
commnConfigTouchlink = drvZigbeeComponent.createBooleanSymbol("TOUCHLINK", commissioningConfigMenu)
commnConfigTouchlink.setLabel("Touchlink Commissioning Enable")
commnConfigTouchlink.setDefaultValue(TouchlinkCommnSetCheck())
commnConfigTouchlink.setDescription("Touchlink Initiator- check the box to enable")
commnConfigTouchlink.setDependencies(ciAsBridgeForcommnConfigTouchlinkEvent, ["CI_AS_BRIDGE"])
commnConfigTouchlink.setDependencies(stackDevTypeForcommnConfigNwkTouchlinkEvent, ["STACK_DEVICE_TYPE"])

# commnConfigTouchlinkTarType = drvZigbeeComponent.createComboSymbol("TLTARGETTYPE",  commissioningConfigMenu, ["BOTH","INITIATOR", "TARGET"])
# commnConfigTouchlinkTarType.setLabel("Touchlink Target Type")
# commnConfigTouchlinkTarType.setDefaultValue("TARGET")
# commnConfigTouchlinkTarType.setDescription("Touchlink Target type- check the box to enable)

# Finding and binding Commissioning
global commnConfigFindingAndbinding
commnConfigFindingAndbinding = drvZigbeeComponent.createBooleanSymbol("FINDING_AND_BINDING", commissioningConfigMenu)
commnConfigFindingAndbinding.setLabel("Finding and binding Commissioning Enable")
commnConfigFindingAndbinding.setDefaultValue(FindingBindingCommnSetCheck())
commnConfigFindingAndbinding.setDescription("Finding and binding - check the box to enable")

# commnConfigFindingAndbindingTarType = drvZigbeeComponent.createComboSymbol("FBTARGETTYPE",  commissioningConfigMenu, ["BOTH","INITIATOR", "TARGET"])
# commnConfigFindingAndbindingTarType.setLabel("Finding and binding Target Type")
# commnConfigFindingAndbindingTarType.setDefaultValue("BOTH")
# commnConfigFindingAndbindingTarType.setDescription("Finding and binding Target type- check the box to enable")

# Install Code based Joining
global commnConfigInstallCodeJoin
commnConfigInstallCodeJoin = drvZigbeeComponent.createBooleanSymbol("JOIN_ONLY_INSTALL_CODE", commissioningConfigMenu)
commnConfigInstallCodeJoin.setLabel("INSTALL CODE ONLY JOINING")
commnConfigInstallCodeJoin.setDefaultValue(False)
commnConfigInstallCodeJoin.setDescription("Joining only thro install code - check the box to enable")

commnConfigInstallCode = drvZigbeeComponent.createStringSymbol("INSTALL_CODE", commnConfigInstallCodeJoin)
commnConfigInstallCode.setLabel("Install Code")
commnConfigInstallCode.setVisible(False)
commnConfigInstallCode.setDefaultValue('0x83,0xFE,0xD3,0x40,0x7A,0x93,0x97,0x23,0xA5,0xC6,0x39,0xB2,0x69,0x16,0xD5,0x05,0xC3,0xB5')
commnConfigInstallCode.setDescription("Install code")
commnConfigInstallCode.setDependencies(JoinViaInstallCodeCheck, ["JOIN_ONLY_INSTALL_CODE"])

commnConfigICDevAddr = drvZigbeeComponent.createStringSymbol("IC_DEVICE_ADDRESS", commnConfigInstallCodeJoin)
commnConfigICDevAddr.setLabel("Device Address")
commnConfigICDevAddr.setVisible(False)
commnConfigICDevAddr.setDefaultValue('0x0000000000000BEF')
commnConfigICDevAddr.setDescription("Device Address corresponding to Install code")
commnConfigICDevAddr.setDependencies(JoinViaInstallCodeDevAddr, ["JOIN_ONLY_INSTALL_CODE"])

######################################## FTL definitions #####################################################

installCodeSrc = drvZigbeeComponent.createFileSymbol("INIT_FILE", None)
installCodeSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/z3DevicePic32cx.c.ftl")
installCodeSrc.setOutputName("z3DevicePic32cx.c")
installCodeSrc.setDestPath("/zigbee/z3device/common")
installCodeSrc.setProjectPath("config/" + configName + "/zigbee/z3device/common/")
installCodeSrc.setType("SOURCE")
installCodeSrc.setOverwrite(True)
installCodeSrc.setMarkup(True)
installCodeSrc.setEnabled(True)
#installCodeSrc.setDependencies(JoinViaInstallCodeCheck, ["JOIN_ONLY_INSTALL_CODE"])

