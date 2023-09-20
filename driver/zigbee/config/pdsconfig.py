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

#####################################################################################################
#################               PDS CONFIGURATION                                   ###############
#####################################################################################################

    # PDS Enable Wear Levelling
global pdsConfigEnablePDS
pdsConfigEnablePDS = drvZigbeeComponent.createBooleanSymbol("PDS_ENABLE", PersistentDataConfigMenu)
pdsConfigEnablePDS.setLabel("PDS Enable")
pdsConfigEnablePDS.setDefaultValue(True)
pdsConfigEnablePDS.setDescription("Enable Persistent Data Storage - check the box to enable")


global pdsConfigEnableWearLevelling
pdsConfigEnableWearLevelling = drvZigbeeComponent.createBooleanSymbol("PDS_ENABLE_WEAR_LEVELING", PersistentDataConfigMenu)
pdsConfigEnableWearLevelling.setLabel("Enable Wear Levelling")
pdsConfigEnableWearLevelling.setDefaultValue(True)
pdsConfigEnableWearLevelling.setDescription("PDS_ENABLE_WEAR_LEVELING- check the box to enable")
pdsConfigEnableWearLevelling.setDependencies(PdsEnableCheck, ["PDS_ENABLE"])

    # Memory to Use
global pdsConfigMemInternalExternal
pdsConfigMemInternalExternal = drvZigbeeComponent.createComboSymbol("PDS_USEMEM_INTEXT",  PersistentDataConfigMenu, ["INTERNAL", "EXTERNAL"])
pdsConfigMemInternalExternal.setLabel("Memory to use")
pdsConfigMemInternalExternal.setDefaultValue("INTERNAL")
pdsConfigMemInternalExternal.setDescription("Internal memory or external memory for PDS - check the box to enable")
pdsConfigMemInternalExternal.setDependencies(PdsEnableCheck, ["PDS_ENABLE"])

