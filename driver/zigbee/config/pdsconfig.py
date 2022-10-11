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

