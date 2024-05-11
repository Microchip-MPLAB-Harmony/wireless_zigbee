#------------------------------------------------------------------------------- 
#  \file  Makefile
#
#  \brief Make file for BDB.
#
#  \author
#    Microchip Corporation: http://ww.microchip.com \n
#    Support email: support@microchip.com
#
#  Copyright (c) 2009, Microchip Corporation. All rights reserved.
#  Licensed under Microchip's Limited License Agreement.
#
#------------------------------------------------------------------------------- 

#***************************** Macro definitions *******************************
COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

#***************************** Compiler's flags ********************************

#***************************** Define's flags **********************************

lib_name = lib$(BDB_LIB).a

# To remove IAR compiler error: wrong if (..) processing.
ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_ARM)
  TMP_CFLAGS:=$(filter-out -O%,$(CFLAGS))
  CFLAGS = $(TMP_CFLAGS) -On
endif

#***************************** Include directories *****************************
ifeq ($(USE_KF_MAC), TRUE)
  CFLAGS += $(addprefix -I,$(KF_INCS))
endif
# DEFINES = \
    # -DBDB_NWKFORMATION_SUPPORT \
    # -DBDB_FINDINGANDBINDING_SUPPORT
		  
		  
CFLAGS +=                        \
  -I$(BASE_PATH)                \
  -I$(BSP_PATH)/include          \
  -I$(SE_PATH)/include           \
  -I$(CS_PATH)/include           \
  -I$(CS_PATH)/include/private   \
  -I$(CRYPTO_PATH)               \
  -I$(COMPONENTS_PATH)/PDS/include\
  -I$(PDS_PATH)/lib              \
  -I$(MAC_HWD_PATH)/             \
  -I$(MAC_HWD_PATH)/RF231_RF212/PHY/include  \
  -I$(MAC_HWD_PATH)/include      \
  -I$(NWK_PATH)/include          \
  -I$(NWK_PATH)/include/private  \
  -I$(APS_PATH)/include          \
  -I$(APS_PATH)/include/private  \
  -I$(TC_PATH)/include           \
  -I$(ZDO_PATH)/include          \
  -I$(ZDO_PATH)/include/private  \
  -I$(ZGP_PATH)/include          \
  -I$(BDB_PATH)/include          \
  -I$(ZCL_PATH)/include          \
  -I$(ZCL_PATH)/include          \
  -I$(ZCL_CLUSTER_PATH)/include  \
  -I$(ZLL_PLATFORM_PATH)         \
  -I$(ZLL_PATH)/N_AddressManager/include     \
  -I$(ZLL_PATH)/N_Beacon/include     \
  -I$(ZLL_PATH)/N_Binding/include     \
  -I$(ZLL_PATH)/N_Cmi/include     \
  -I$(ZLL_PATH)/N_Connection/include     \
  -I$(ZLL_PATH)/N_DeviceInfo/include     \
  -I$(ZLL_PATH)/N_EndDeviceRobustness/include     \
  -I$(ZLL_PATH)/N_InterPan/include     \
  -I$(ZLL_PATH)/N_LinkInitiator/include     \
  -I$(ZLL_PATH)/N_LinkTarget/include     \
  -I$(ZLL_PATH)/N_PacketDistributor/include     \
  -I$(ZLL_PATH)/N_Radio/include     \
  -I$(ZLL_PATH)/N_ReconnectHandler/include     \
  -I$(ZLL_PATH)/N_Security/include     \
  -I$(ZLL_PATH)/N_Zdp/include     \
  -I$(ZLL_PATH)/N_Zcl_Framework/include   \
  -I$(ZLL_INFRA_PATH)/N_Address/include     \
  -I$(ZLL_INFRA_PATH)/N_Beacon/include     \
  -I$(ZLL_INFRA_PATH)/N_ErrH/include     \
  -I$(ZLL_INFRA_PATH)/N_Fsm/include     \
  -I$(ZLL_INFRA_PATH)/N_Log/include     \
  -I$(ZLL_INFRA_PATH)/N_Memory/include     \
  -I$(ZLL_INFRA_PATH)/N_Task/include     \
  -I$(ZLL_INFRA_PATH)/N_Init/include     \
  -I$(ZLL_INFRA_PATH)/N_Timer/include     \
  -I$(ZLL_INFRA_PATH)/N_Types/include     \
  -I$(ZLL_INFRA_PATH)/N_Util/include     \
  -I$(HAL_PATH)/include          \
  -I$(HAL_HWD_COMMON_PATH)/include      \
  -I$(MAC_PHY_PATH)/include      \
  -I$(MAC_ENV_PATH)/include      \
  -I$(HAL_PATH)/../include       \
  -I$(SSP_PATH)/include/private  \
  -I$(SSP_PATH)/include          \
  -I$(SSP_PATH)/../SoftAes       \
  -I$(OSAL_PATH)                   \
  -I$(OSAL_PATH)/osal              \
  -I$(FREE_RTOS_PATH)/include      \
  -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  -I$(RTOS_CONFIG_PATH)            \
  -I$(PARTPACK_PATCH)/include      \
  -I$(PARTPACK_PATCH)/include/soc  \
  -I$(CMIS_PATH)                   \
  -I$(UTILS_PATH)                  \
  -I$(UTILS_PATH)/preprocessor

#***************************** Object files ************************************
objects_bdb =                              \
  $(BDB_PATH)/objs/bdb.o            \
  $(BDB_PATH)/objs/bdbBcEventsHandler.o                \
  $(BDB_PATH)/objs/bdbCommissioning.o         \
  $(BDB_PATH)/objs/bdbFindingAndBinding.o        \
  $(BDB_PATH)/objs/bdbIB.o         \
  $(BDB_PATH)/objs/bdbInstallCode.o         \
  $(BDB_PATH)/objs/bdbNwkFormation.o        \
  $(BDB_PATH)/objs/bdbNwkSteering.o   \
  $(BDB_PATH)/objs/bdbReset.o               \
  $(BDB_PATH)/objs/bdbSecurity.o            \
  $(BDB_PATH)/objs/bdbTouchlink.o           \
  $(BDB_PATH)/objs/N_AddressManager.o            \
  $(BDB_PATH)/objs/N_Binding.o                \
  $(BDB_PATH)/objs/N_Cmi.o         \
  $(BDB_PATH)/objs/N_Connection_ReconnectHandler.o        \
  $(BDB_PATH)/objs/N_ConnectionAssociation.o         \
  $(BDB_PATH)/objs/N_ConnectionCommon.o         \
  $(BDB_PATH)/objs/N_ConnectionEnddevice.o        \
  $(BDB_PATH)/objs/N_ConnectionRouter.o   \
  $(BDB_PATH)/objs/N_DeviceInfo.o          \
  $(BDB_PATH)/objs/N_EndDeviceRobustness.o               \
  $(BDB_PATH)/objs/N_InterPan.o                  \
  $(BDB_PATH)/objs/N_InterPanBuffers.o           \
  $(BDB_PATH)/objs/N_LinkInitiator.o           \
  $(BDB_PATH)/objs/N_LinkTarget.o           \
  $(BDB_PATH)/objs/N_PacketDistributor.o           \
  $(BDB_PATH)/objs/N_Radio.o           \
  $(BDB_PATH)/objs/N_ReconnectHandler.o           \
  $(BDB_PATH)/objs/N_Security.o           \
  $(BDB_PATH)/objs/N_Security_Calc.o           \
  $(BDB_PATH)/objs/N_Zdp.o           \
  $(BDB_PATH)/objs/N_Address.o\
  $(BDB_PATH)/objs/N_ErrH.o               \
  $(BDB_PATH)/objs/N_Fsm.o                  \
  $(BDB_PATH)/objs/N_Fsm-Logging.o           \
  $(BDB_PATH)/objs/N_Log.o           \
  $(BDB_PATH)/objs/N_Memory-Microchip.o           \
  $(BDB_PATH)/objs/N_Task.o           \
  $(BDB_PATH)/objs/N_Task-Internal-Microchip.o           \
  $(BDB_PATH)/objs/N_Timer.o           \
  $(BDB_PATH)/objs/N_Timer-Internal-Microchip.o           \
  #$(BDB_PATH)/objs/N_Util.o           \
  
  
#***************************** Libraries ***************************************
lib_bdb = $(BDB_PATH)/lib/$(lib_name)

#***************************** Targets *****************************************
all: component_label $(lib_ bdb) size_bdb
component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo Base device Behaviour library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BDB_PATH)/objs/
	$(Q)mkdir -p $(BDB_PATH)/lib/
$(objects_bdb): 
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $^ -o $@
$(BDB_PATH)/objs/bdb.o:                          $(BDB_PATH)/src/bdb.c
$(BDB_PATH)/objs/bdbBcEventsHandler.o:           $(BDB_PATH)/src/bdbBcEventsHandler.c
$(BDB_PATH)/objs/bdbCommissioning.o:             $(BDB_PATH)/src/bdbCommissioning.c
$(BDB_PATH)/objs/bdbFindingAndBinding.o:         $(BDB_PATH)/src/bdbFindingAndBinding.c
$(BDB_PATH)/objs/bdbIB.o:                        $(BDB_PATH)/src/bdbIB.c
$(BDB_PATH)/objs/bdbInstallCode.o:               $(BDB_PATH)/src/bdbInstallCode.c
$(BDB_PATH)/objs/bdbNwkFormation.o:              $(BDB_PATH)/src/bdbNwkFormation.c
$(BDB_PATH)/objs/bdbNwkSteering.o:               $(BDB_PATH)/src/bdbNwkSteering.c
$(BDB_PATH)/objs/bdbReset.o:                     $(BDB_PATH)/src/bdbReset.c
$(BDB_PATH)/objs/bdbSecurity.o:                  $(BDB_PATH)/src/bdbSecurity.c
$(BDB_PATH)/objs/bdbTouchlink.o:                 $(BDB_PATH)/src/bdbTouchlink.c
#zll
$(BDB_PATH)/objs/N_AddressManager.o:              $(ZLL_PATH)/N_AddressManager/src/N_AddressManager.c
$(BDB_PATH)/objs/N_Binding.o:                     $(ZLL_PATH)/N_Binding/src/N_Binding.c
$(BDB_PATH)/objs/N_Cmi.o:                         $(ZLL_PATH)/N_Cmi/src/N_Cmi.c
$(BDB_PATH)/objs/N_Connection_ReconnectHandler.o: $(ZLL_PATH)/N_Connection/src/N_Connection_ReconnectHandler.c
$(BDB_PATH)/objs/N_ConnectionAssociation.o:       $(ZLL_PATH)/N_Connection/src/N_ConnectionAssociation.c
$(BDB_PATH)/objs/N_ConnectionCommon.o:            $(ZLL_PATH)/N_Connection/src/N_ConnectionCommon.c
$(BDB_PATH)/objs/N_ConnectionEnddevice.o:         $(ZLL_PATH)/N_Connection/src/N_ConnectionEnddevice.c
$(BDB_PATH)/objs/N_ConnectionRouter.o:            $(ZLL_PATH)/N_Connection/src/N_ConnectionRouter.c
$(BDB_PATH)/objs/N_DeviceInfo.o:                  $(ZLL_PATH)/N_DeviceInfo/src/N_DeviceInfo.c
$(BDB_PATH)/objs/N_EndDeviceRobustness.o:         $(ZLL_PATH)/N_EndDeviceRobustness/src/N_EndDeviceRobustness.c
$(BDB_PATH)/objs/N_InterPan.o:                    $(ZLL_PATH)/N_InterPan/src/N_InterPan.c
$(BDB_PATH)/objs/N_InterPanBuffers.o:             $(ZLL_PATH)/N_InterPan/src/N_InterPanBuffers.c
$(BDB_PATH)/objs/N_LinkInitiator.o:               $(ZLL_PATH)/N_LinkInitiator/src/N_LinkInitiator.c
$(BDB_PATH)/objs/N_LinkTarget.o:                  $(ZLL_PATH)/N_LinkTarget/src/N_LinkTarget.c
$(BDB_PATH)/objs/N_PacketDistributor.o:           $(ZLL_PATH)/N_PacketDistributor/src/N_PacketDistributor.c
$(BDB_PATH)/objs/N_Radio.o:                       $(ZLL_PATH)/N_Radio/src/N_Radio.c
$(BDB_PATH)/objs/N_ReconnectHandler.o:            $(ZLL_PATH)/N_ReconnectHandler/src/N_ReconnectHandler.c
$(BDB_PATH)/objs/N_Security.o:                    $(ZLL_PATH)/N_Security/src/N_Security.c
$(BDB_PATH)/objs/N_Security_Calc.o:               $(ZLL_PATH)/N_Security/src/N_Security_Calc.c
$(BDB_PATH)/objs/N_Zdp.o:                         $(ZLL_PATH)/N_Zdp/src/N_Zdp.c
$(BDB_PATH)/objs/N_Address.o:                     $(ZLL_INFRA_PATH)/N_Address/src/N_Address.c
$(BDB_PATH)/objs/N_ErrH.o:                        $(ZLL_INFRA_PATH)/N_ErrH/src/N_ErrH.c
$(BDB_PATH)/objs/N_Fsm.o:                         $(ZLL_INFRA_PATH)/N_Fsm/src/N_Fsm.c
$(BDB_PATH)/objs/N_Fsm-Logging.o:                 $(ZLL_INFRA_PATH)/N_Fsm/src/N_Fsm-Logging.c
$(BDB_PATH)/objs/N_Log.o:                         $(ZLL_INFRA_PATH)/N_Log/src/N_Log.c
$(BDB_PATH)/objs/N_Memory-Microchip.o:                $(ZLL_INFRA_PATH)/N_Memory/src/N_Memory-Microchip.c
$(BDB_PATH)/objs/N_Task.o:                        $(ZLL_INFRA_PATH)/N_Task/src/N_Task.c
$(BDB_PATH)/objs/N_Task-Internal-Microchip.o:         $(ZLL_INFRA_PATH)/N_Task/src/N_Task-Internal-Microchip.c
$(BDB_PATH)/objs/N_Timer.o:                       $(ZLL_INFRA_PATH)/N_Timer/src/N_Timer.c
$(BDB_PATH)/objs/N_Timer-Internal-Microchip.o:        $(ZLL_INFRA_PATH)/N_Timer/src/N_Timer-Internal-Microchip.c
#$(BDB_PATH)/objs/N_Util.o:                       $(ZLL_INFRA_PATH)/N_Util/src/N_Util.c

$(lib_bdb): $(objects_bdb)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(lib_bdb) $(objects_bdb)

size_bdb: $(lib_bdb)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(lib_bdb)

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo Base Device behaviour component cleaning is started...
	$(Q)rm -f $(objects_bdb) $(lib_bdb) $(wildcard $(BDB_PATH)/list/*.*)
	@echo Base Device behaviour component cleaning is done!
	@echo ----------------------------------------------------
