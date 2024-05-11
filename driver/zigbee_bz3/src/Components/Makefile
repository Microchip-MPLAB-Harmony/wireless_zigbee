#-------------------------------------------------------------------------------------
# Some global vars
COMPONENTS_PATH = .
MAKEFLAGS += --no-print-directory

#-------------------------------------------------------------------------------------
# Includes.
include $(COMPONENTS_PATH)/Makerules
#-------------------------------------------------------------------------------------
# List of libraries which are included into the general library.
# If a user wants to change BSP or HAL, BSP or HAL should be excluded from list

ifneq ($(BUILD_TARGET), TARGET_HAL_SE)
  LIBS_TO_INCLUDE = $(MAC_PHY_PATH)/lib/lib$(MAC_PHY_LIB).a
  ifneq ($(BUILD_TARGET), TARGET_MAC)
    LIBS_TO_INCLUDE += $(NWK_PATH)/lib/lib$(NWK_LIB).a
    ifneq ($(BUILD_TARGET), TARGET_NWK)
      LIBS_TO_INCLUDE += $(APS_PATH)/lib/lib$(APS_LIB).a
      LIBS_TO_INCLUDE += $(ZCL_PATH)/lib/lib$(ZCL_LIB).a
      LIBS_TO_INCLUDE += $(ZDO_PATH)/lib/lib$(ZDO_LIB).a
      ifeq ($(BUILD_TARGET), TARGET_ZIGBEE_BDB_STACK)
        LIBS_TO_INCLUDE += $(BDB_PATH)/lib/lib$(BDB_LIB).a
      endif 
      ifneq ($(SECURITY_MODE), NO_SECURITY_MODE)
        ifdef TRUST_CENTRE
          LIBS_TO_INCLUDE += $(TC_PATH)/lib/lib$(TC_LIB).a
        endif
        LIBS_TO_INCLUDE += $(SSP_PATH)/lib/lib$(SSP_LIB).a
      endif
    endif
  endif
endif

ifeq (, $(findstring $(BUILD_TARGET), TARGET_ZIGBEE_STACK TARGET_ZIGBEE_BDB_STACK))
  LIBS_TO_INCLUDE += $(SE_PATH)/lib/lib$(SE_LIB).a
endif

LIBS_TO_INCLUDE_NO_PATH =$(notdir $(LIBS_TO_INCLUDE))

EXTRACT_OBJECTS_COMMAND_TMP = $(addprefix && $(AR) $(AR_EXTRACT_KEYS) , $(LIBS_TO_INCLUDE_NO_PATH))
EXTRACT_OBJECTS_COMMAND = $(wordlist 2,$(words $(EXTRACT_OBJECTS_COMMAND_TMP)),$(EXTRACT_OBJECTS_COMMAND_TMP))

#-------------------------------------------------------------------------------------
# generated makerules library definition
MAKERULES_HAL = Makerules$(LIB_NAME_MICRO)$(LIB_NAME_COMPILER)
MAKERULES = $(STACK_LIB)_Makerules

ifndef STACK_LIB
  $(error ERROR: Build target is not defined)
endif

ifeq ($(COMPILER_TYPE), IAR)
  TMP_CFLAGS := $(patsubst -c,,$(CFLAGS_NO_PATHS))
  APP_CFLAGS := $(value HAL_CFLAGS_PATH) $(patsubst --debug,,$(TMP_CFLAGS))
else
  APP_CFLAGS := $(value HAL_CFLAGS_PATH) $(CFLAGS_NO_PATHS)
endif

ifeq ($(COMPILER_TYPE), GCC)
  	COMPILER_VERSION := $(strip $(shell $(CC) -v 2>&1 | grep 'gcc version'))
endif
ifeq ($(COMPILER_TYPE), IAR)
  	COMPILER_VERSION := $(strip $(shell $(CC) | grep 'C/C++ Compiler V'))
endif
ifneq ($(EXP_VERSION), $(COMPILER_VERSION))
  $(error ERROR in file Makerules: You are using incorrect version of compiler: \
    installed $(COMPILER_VERSION), expected $(EXP_VERSION))
endif

# Targets.
all: | prepare_lib gen_hal_makerules gen_app_makerules gen_iar_header

ifeq ($(BUILD_TARGET), TARGET_HAL_SE)
layers: se_make
endif

ifeq ($(BUILD_TARGET), TARGET_MAC)
layers: mac_phy_make se_make
endif

ifeq ($(BUILD_TARGET), TARGET_NWK)
layers: mac_phy_make se_make nwk_make ssp_make tc_make
endif

ifneq (, $(findstring $(BUILD_TARGET), TARGET_ZIGBEE_STACK))
layers: mac_phy_make nwk_make aps_make zcl_make zdo_make ssp_make tc_make 
endif

ifneq (, $(findstring $(BUILD_TARGET), TARGET_ZIGBEE_BDB_STACK))
layers: mac_phy_make nwk_make aps_make zcl_make zdo_make bdb_make ssp_make tc_make 
endif

ifeq ($(MAKERULES_ONLY), FALSE)
prepare_lib: | gen_lib_creation gen_lib_size clean_lib_dir
else
prepare_lib:
endif

se_make:
	$(Q)$(MAKE) -j1 all -C $(SE_PATH)

mac_phy_make:
	$(Q)$(MAKE) -j1 all -C $(MAC_PHY_PATH)

nwk_make:
	$(Q)$(MAKE) -j1 all -C $(NWK_PATH)

aps_make:
	$(Q)$(MAKE) -j1 all -C $(APS_PATH)

zcl_make:
	$(Q)$(MAKE) -j1 all -C $(ZCL_PATH)

zdo_make:
	$(Q)$(MAKE) -j1 all -C $(ZDO_PATH)

bdb_make:
	$(Q)$(MAKE) -j1 all -C $(BDB_PATH)

ssp_make:
ifneq ($(SECURITY_MODE), NO_SECURITY_MODE)
	$(Q)$(MAKE) -j1 all -C $(SSP_PATH)
endif

tc_make:
ifneq ($(SECURITY_MODE), NO_SECURITY_MODE)
	$(Q)$(MAKE) -j1 all -C $(TC_PATH)
endif

ifeq ($(USE_KF_MAC), TRUE)
se_make:mac_phy_make
nwk_make:mac_phy_make
aps_make:mac_phy_make
zcl_make:mac_phy_make
zdo_make:mac_phy_make
ssp_make:mac_phy_make
tc_make:mac_phy_make

endif

zappsi_make:
	$(Q)$(MAKE) all -C $(ZAPPSI_PATH)

copy_libs: layers
	@echo
	@echo ----------------------------------------------------
	@echo Libraries local copies creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(STACK_LIB_PATH)/tmp
	$(Q)cp $(LIBS_TO_INCLUDE) $(STACK_LIB_PATH)/tmp

extract_objs: copy_libs
ifneq ($(COMPILER_AND_MICRO_TYPE), IAR_AVR)
	@echo
	@echo ----------------------------------------------------
	@echo Objects extracting from the libraries.
	@echo ----------------------------------------------------
	$(Q)cd $(STACK_LIB_PATH)/tmp && $(EXTRACT_OBJECTS_COMMAND)
endif # IAR_AVR

gen_lib_creation: extract_objs
	@echo
	@echo ----------------------------------------------------
	@echo General library creation.
	@echo ----------------------------------------------------
ifneq ( , $(findstring $(COMPILER_AND_MICRO_TYPE), IAR_AVR IAR_AVR32))
	$(Q)cd $(STACK_LIB_PATH)/tmp && $(AR) $(LIBS_TO_INCLUDE_NO_PATH) -o ../lib$(STACK_LIB).a
else
	$(Q)$(AR) $(AR_KEYS) $(STACK_LIB_PATH)/$(STACK_LIB)_Lib.a $(STACK_LIB_PATH)/tmp/*.o
endif

gen_lib_size: gen_lib_creation
ifeq ( , $(findstring $(COMPILER_AND_MICRO_TYPE), IAR_AVR IAR_AVR32 IAR_ARM))
	@echo
	@echo ----------------------------------------------------
	@echo Total general library size.
	@echo ----------------------------------------------------
	$(Q)$(SIZE) -t $(STACK_LIB_PATH)/$(STACK_LIB)_Lib.a | grep [Tt][Oe][Tx][At]
endif

clean_lib_dir: gen_lib_size
	@echo
	@echo ----------------------------------------------------
	@echo Remove temporary files from stack lib directory.
	@echo ----------------------------------------------------
	$(Q)rm -r $(STACK_LIB_PATH)/tmp

print_gen_lib_info:
	@echo
	@echo ----------------------------------------------------
	@echo General libary info.
	@echo ----------------------------------------------------
	@echo 'BUILD_TARGET            = '$(BUILD_TARGET)
	@echo 'HAL                     = '$(HAL)
	@echo 'CPU                     = '$(CPU)
	@echo 'RFCHIP                  = '$(RFCHIP)
	@echo 'STACK_TYPE             = '$(STACK_TYPE)
	@echo 'SECURITY_MODE           = '$(SECURITY_MODE)
ifneq ($(SECURITY_MODE), NO_SECURITY_MODE)
	@echo 'TRUST_CENTRE            = '$(TRUST_CENTRE)
	@echo 'PERMISSIONS             = '$(PERMISSIONS)
	@echo 'AES_TYPE                = '$(AES_TYPE)
endif # !NO_SECURITY_MODE

	@echo 'NWK_MANY_TO_ONE_ROUTING = '$(NWK_MANY_TO_ONE_ROUTING)
	@echo 'APS_FRAGMENTATION       = '$(APS_FRAGMENTATION)
	@echo 'ZCL_SUPPORT		       = '$(ZCL_SUPPORT)
	@echo 'NWK_GROUP               = '$(NWK_GROUP)
	@echo 'APS_MULTICAST           = '$(APS_MULTICAST)
	@echo 'COMMISSIONING           = '$(COMMISSIONING)
ifneq (, $(findstring $(BUILD_TARGET), TARGET_ZIGBEE_STACK TARGET_ZIGBEE_BDB_STACK))
	@echo 'BINDING                 = '$(BINDING)
	@echo 'RESOLVE_PANID_CONFLICT  = '$(RESOLVE_PANID_CONFLICT)
	@echo 'NETWORK_MANAGER         = '$(NETWORK_MANAGER)
	@echo 'INTERPAN                = '$(INTERPAN)
endif
	@echo 'FREQUENCY_AGILITY       = '$(FREQUENCY_AGILITY)

#auxilary variable for gen_iar_header target
CREATE_PARAMETERS = $(foreach flag, $(filter -D%, $(STACK_CFLAGS) $(HAL_CFLAGS)), \
	$(shell echo $(wordlist 1, 2, $(subst =, , $(subst -D, '\#ifndef ', $(flag)))) >> $(MAKERULES).h ) \
	$(shell echo $(subst -D, '\#define ', $(subst =, , $(flag))) >> $(MAKERULES).h )  \
	$(shell echo '\#endif' >> $(MAKERULES).h ))

gen_iar_header: prepare_lib
	$(CREATE_PARAMETERS)
	$(shell echo '#if defined (Z3DEVICE_APP) || defined (ZGPSENSOR_APP) || defined (ZGPSWITCH_APP)' >> $(MAKERULES).h)
	$(shell echo '#include <zigbeeAppConfig.h>' >> $(MAKERULES).h)
	$(shell echo '#endif' >> $(MAKERULES).h)
	$(Q)mv $(MAKERULES).h $(STACK_LIB_PATH)

gen_hal_makerules: prepare_lib
	@echo '#'---------------------------------------------- >> $(MAKERULES_HAL)
	@echo '#'HAL makerules - should be included into components Makerules >> $(MAKERULES_HAL)
	@echo '#'---------------------------------------------- >> $(MAKERULES_HAL)
	@echo >> $(MAKERULES_HAL)
	@echo '#'-Compiler type definition--------------------- >> $(MAKERULES_HAL)
ifeq ($(COMPILER_TYPE), IAR)
	@echo IAR_PATH = '$(value IAR_PATH)' >> $(MAKERULES_HAL)
endif
	@echo 'COMPILER_TYPE =' $(COMPILER_TYPE) >> $(MAKERULES_HAL)
	@echo 'COMPILER_AND_MICRO_TYPE =' $(COMPILER_AND_MICRO_TYPE) >> $(MAKERULES_HAL)
	@echo '#'-Tools definitions---------------------------- >> $(MAKERULES_HAL)

ifeq ($(COMPILER_TYPE), IAR)
	@echo 'AS       =' '$(value AS)' >> $(MAKERULES_HAL)
	@echo 'LD       =' '$(value LD)' >> $(MAKERULES_HAL)
	@echo 'CC       =' '$(value CC)' >> $(MAKERULES_HAL)
	@echo 'CPP      =' '$(value CPP)' >> $(MAKERULES_HAL)
	@echo 'AR       =' '$(value AR)' >> $(MAKERULES_HAL)
	@echo 'IELFTOOL =' '$(value IELFTOOL)' >> $(MAKERULES_HAL)
else
	@echo 'AS       =' $(AS) >> $(MAKERULES_HAL)
	@echo 'LD       =' $(LD) >> $(MAKERULES_HAL)
	@echo 'CC       =' $(CC) >> $(MAKERULES_HAL)
	@echo 'CPP      =' $(CPP) >> $(MAKERULES_HAL)
	@echo 'AR       =' $(AR) >> $(MAKERULES_HAL)
endif
	@echo 'NM       =' $(NM) >> $(MAKERULES_HAL)
	@echo 'STRIP    =' $(STRIP) >> $(MAKERULES_HAL)
	@echo 'OBJCOPY  =' $(OBJCOPY) >> $(MAKERULES_HAL)
	@echo 'OBJDUMP  =' $(OBJDUMP) >> $(MAKERULES_HAL)
	@echo 'SIZE     =' $(SIZE) >> $(MAKERULES_HAL)
	@echo >> $(MAKERULES_HAL)
	@echo '#'-Compiler flags------------------------------- >> $(MAKERULES_HAL)
	@echo CFLAGS = '$(value HAL_CFLAGS_PATH)' $(HAL_CFLAGS) >> $(MAKERULES_HAL)
	@echo AR_KEYS = $(AR_KEYS) >> $(MAKERULES_HAL)
	@echo >> $(MAKERULES_HAL)
ifeq ($(HAL), AT91SAM7X256)
	@echo '#'-Thumb mode flags----------------------------- >> $(MAKERULES_HAL)
	@echo 'ARM_MODE_THUMBS_CFLAGS =' $(ARM_MODE_THUMBS_CFLAGS) >> $(MAKERULES_HAL)
	@echo 'ARM_MODE_ARM_CFLAGS    =' $(ARM_MODE_ARM_CFLAGS) >> $(MAKERULES_HAL)
endif
	@echo >> $(MAKERULES_HAL)
	@echo '#'-Objects to be linked with app---------------- >> $(MAKERULES_HAL)
	@echo 'PLATFORM_SPECIFIC_OBJECTS  = '$(WDT_INIT_OBJ) $(BOOT_OBJ) >> $(MAKERULES_HAL)
	@echo >> $(MAKERULES_HAL)
	@echo 'SE_PATH      = $$''(COMPONENTS_PATH)/'$(SE_PATH)  >> $(MAKERULES_HAL)
	@echo 'CS_PATH      = $$''(COMPONENTS_PATH)/'$(CS_PATH)  >> $(MAKERULES_HAL)
	$(Q)mv $(MAKERULES_HAL) $(STACK_LIB_PATH)

gen_app_makerules: prepare_lib
	@echo
	@echo ----------------------------------------------------
	@echo Generate app makerules
	@echo ----------------------------------------------------
	@echo '#'---------------------------------------------- >> $(MAKERULES)
	@echo '#'User application makerules - should be included into user application Makefile >> $(MAKERULES)
	@echo '#'---------------------------------------------- >> $(MAKERULES)
	@echo >> $(MAKERULES)
	@echo 'include $$''(COMPONENTS_PATH)/../lib/'$(MAKERULES_HAL)  >> $(MAKERULES)
	@echo >> $(MAKERULES)
ifeq ($(COMPILER_TYPE), IAR)
	@echo IAR_PATH = '$(value IAR_PATH)' >> $(MAKERULES)
endif
	@echo >> $(MAKERULES)
	@echo '#'-Compiler flags------------------------------- >> $(MAKERULES)
	@echo  CFLAGS = '$(value APP_CFLAGS)' >> $(MAKERULES)
	@echo 'CFLAGS += $$(BOARDCFLAGS)' >> $(MAKERULES)
	@echo '#'-Libraries names------------------------------ >> $(MAKERULES)
	@echo 'CS_LIB    =' $(CS_LIB) >> $(MAKERULES)
	@echo 'PDS_LIB   =' $(PDS_LIB) >> $(MAKERULES)
ifeq ($(HAL), AT91SAM7X256)
	@echo 'VCP_LIB   =' $(VCP_LIB) >> $(MAKERULES)
endif
ifeq ($(HAL), AT90USB1287)
	@echo 'VCP_LIB   =' $(VCP_LIB) >> $(MAKERULES)
endif
ifeq ($(OTAU), TRUE)
	@echo 'OFD_LIB   =' $(OFD_LIB) >> $(MAKERULES)
endif
ifeq ($(OS), FREE_RTOS)
	@echo 'FREE_RTOS_LIB   =' $(FREE_RTOS_LIB) >> $(MAKERULES)
endif
	@echo >> $(MAKERULES)
	@echo '#'-Stack components paths----------------------- >> $(MAKERULES)
	@echo 'HAL_HWD_COMMON_PATH = $$''(COMPONENTS_PATH)/'$(HAL_HWD_COMMON_PATH) >> $(MAKERULES)
	@echo 'HAL_MAC_API_PATH = $$''(COMPONENTS_PATH)/'$(HAL_MAC_API_PATH) >> $(MAKERULES)
	@echo 'HAL_PATH     = $$''(COMPONENTS_PATH)/'$(HAL_PATH) >> $(MAKERULES)
ifneq ($(BUILD_TARGET), TARGET_HAL_SE)
	@echo 'MAC_PHY_PATH = $$''(COMPONENTS_PATH)/'$(MAC_PHY_PATH) >> $(MAKERULES)
	@echo 'MAC_ENV_PATH = $$''(COMPONENTS_PATH)/'$(MAC_ENV_PATH) >> $(MAKERULES)
	@echo 'MAC_HWD_PATH = $$''(COMPONENTS_PATH)/'$(MAC_HWD_PATH) >> $(MAKERULES)
	@echo 'MAC_HWI_PATH = $$''(COMPONENTS_PATH)/'$(MAC_HWI_PATH) >> $(MAKERULES)
  ifneq ($(BUILD_TARGET), TARGET_MAC)
		@echo 'NWK_PATH     = $$''(COMPONENTS_PATH)/'$(NWK_PATH) >> $(MAKERULES)
		@echo 'APS_PATH     = $$''(COMPONENTS_PATH)/'$(APS_PATH) >> $(MAKERULES)
		@echo 'ZCL_PATH     = $$''(COMPONENTS_PATH)/'$(ZCL_PATH) >> $(MAKERULES)
		@echo 'ZDO_PATH     = $$''(COMPONENTS_PATH)/'$(ZDO_PATH) >> $(MAKERULES)
		@echo 'SSP_PATH     = $$''(COMPONENTS_PATH)/'$(SSP_PATH) >> $(MAKERULES)
		@echo 'TC_PATH      = $$''(COMPONENTS_PATH)/'$(TC_PATH)  >> $(MAKERULES)
		@echo 'PDS_PATH     = $$''(COMPONENTS_PATH)/'$(PDS_PATH) >> $(MAKERULES)
  endif
endif
	@echo 'CS_PATH      = $$''(COMPONENTS_PATH)/'$(CS_PATH)  >> $(MAKERULES)
	@echo 'PDS_PATH     = $$''(COMPONENTS_PATH)/'$(PDS_PATH) >> $(MAKERULES)
	@echo 'BSP_PATH     = $$''(COMPONENTS_PATH)/'$(BSP_PATH) >> $(MAKERULES)
	@echo 'DRIVERS_PATH = $$''(COMPONENTS_PATH)/'$(DRIVERS_PATH) >> $(MAKERULES)
	@echo >> $(MAKERULES)
ifeq ($(OS), FREE_RTOS)
	@echo 'FREE_RTOS_PATH = $$''(COMPONENTS_PATH)/'$(FREE_RTOS_PATH) >> $(MAKERULES)
endif
	$(Q)mv $(MAKERULES) $(STACK_LIB_PATH)

ifeq ($(MAKERULES_ONLY), FALSE)
clean_stack:
	@echo
	@echo ----------------------------------------------------
	@echo All components libraries cleaning is started...
	$(Q)$(MAKE) clean -C $(SE_PATH)
ifneq ($(BUILD_TARGET), TARGET_HAL_SE)
	$(Q)$(MAKE) -j1 clean -C $(MAC_PHY_PATH)
  ifneq ($(BUILD_TARGET), TARGET_MAC)
		$(Q)$(MAKE) -j1 clean -C $(NWK_PATH)
		$(Q)$(MAKE) -j1 clean -C $(APS_PATH)
		$(Q)$(MAKE) -j1 clean -C $(ZCL_PATH)
		$(Q)$(MAKE) -j1 clean -C $(ZDO_PATH)
		$(Q)$(MAKE) -j1 clean -C $(SSP_PATH)
		$(Q)$(MAKE) -j1 clean -C $(TC_PATH)
		$(Q)$(MAKE) -j1 clean -C $(BDB_PATH)
  endif
endif
	@echo All components libraries cleaning is done!
	@echo ----------------------------------------------------
else
clean_stack:
endif

clean: clean_stack
	@echo
	@echo ----------------------------------------------------
	@echo General stack library cleaning is started...
	$(Q)rm -f $(wildcard $(STACK_LIB_PATH)/*$(STACK_LIB)*)
	$(Q)rm -f $(STACK_LIB_PATH)/$(MAKERULES_HAL)
	$(Q)rm -rf $(STACK_LIB_PATH)/tmp
	@echo General stack library cleaning is done!
	@echo ----------------------------------------------------

test:
	jython ../Test/Feature/scripts/auxScripts/BuildStack.py

allTypes:
	jython ../Test/Feature/scripts/auxScripts/BuildStackAllLibTypes.py

mac2:
	jython ../Test/Feature/scripts/auxScripts/mac2.py

mrproper:
	@cd ../Services/build && python mrproper.py

ifeq ($(MAKECMDGOALS), fresh)
fresh:
	$(Q)$(MAKE) clean
	$(Q)$(MAKE) -j5 all
endif
