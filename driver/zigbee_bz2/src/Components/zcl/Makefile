###########################################################################//##
# \file  Makefile
# \brief Main makefile of ZCL-layer.
#
# \author
#   Microchip Corporation: http://ww.microchip.com \n
#   Support email: support@microchip.com
#
# Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
# Licensed under Microchip's Limited License Agreement.
#
# \internal
#  History:
#   2010-10-15 Max Gekk - Created.
#  Last change:
#   $Id: Makefile 28547 2015-09-10 13:10:16Z mukesh.basrani $
################################################################################

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

# Build ZCL layer as separate files
ZCL_WHOLE_BUILD = 0

#ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_AVR)
#  TMP_CFLAGS:=$(patsubst -Ohz,,$(CFLAGS))
#  CFLAGS = $(TMP_CFLAGS) -Om
#endif

###### ZCL MODULES #########
modules =                      \
  zcl                          \
  zclParser                    \
  zclAttributes                \
  zclMemoryManager             \
  zclTaskManager               \
  zclDummyEcc                  \
  zclKeyEstablishmentCluster   \
  zclSecurityManager           \
  zclApsInterface              \
  zclCommandAnalyzer
 
include_path =                   \
  $(KF_INCS)                     \
  $(COMPONENTS_PATH)             \
  $(SSP_PATH)/include            \
  $(SE_PATH)/include             \
  $(TC_PATH)/include             \
  $(MAC_PHY_PATH)/include        \
  $(MAC_HWI_PATH)/include        \
  $(MAC_HWD_PATH)/include        \
  $(MAC_ENV_PATH)/include        \
  $(CS_PATH)/include             \
  $(CS_PATH)/include/private     \
  $(PDS_PATH)/include            \
  $(PDS_PATH)/wl/include         \
  $(APS_PATH)/include            \
  $(NWK_PATH)/include            \
  $(ZCL_PATH)/clusters/include   \
  $(ZCL_PATH)/include            \
  $(ZCL_PATH)/include/private    \
  $(ZDO_PATH)/include            \
  $(ZDO_PATH)/include/private    \
  $(BDB_PATH)/include            \
  $(ZLL_PLATFORM_PATH)           \
  $(ZLL_PATH)/S_Nv/include     \
  $(ZLL_PATH)/D_Nv/include     \
  $(ZLL_PATH)/N_AddressManager/include     \
  $(ZLL_PATH)/N_Beacon/include     \
  $(ZLL_PATH)/N_Binding/include     \
  $(ZLL_PATH)/N_Cmi/include     \
  $(ZLL_PATH)/N_Connection/include     \
  $(ZLL_PATH)/N_DeviceInfo/include     \
  $(ZLL_PATH)/N_EndDeviceRobustness/include     \
  $(ZLL_PATH)/N_InterPan/include     \
  $(ZLL_PATH)/N_LinkInitiator/include     \
  $(ZLL_PATH)/N_LinkTarget/include     \
  $(ZLL_PATH)/N_PacketDistributor/include     \
  $(ZLL_PATH)/N_Radio/include     \
  $(ZLL_PATH)/N_ReconnectHandler/include     \
  $(ZLL_PATH)/N_Security/include     \
  $(ZLL_PATH)/N_Zdp/include     \
  $(ZLL_PATH)/N_Zcl_Framework/include   \
  $(ZLL_INFRA_PATH)/N_Address/include     \
  $(ZLL_INFRA_PATH)/N_Beacon/include     \
  $(ZLL_INFRA_PATH)/N_ErrH/include     \
  $(ZLL_INFRA_PATH)/N_Fsm/include     \
  $(ZLL_INFRA_PATH)/N_Log/include     \
  $(ZLL_INFRA_PATH)/N_Memory/include     \
  $(ZLL_INFRA_PATH)/N_Task/include     \
  $(ZLL_INFRA_PATH)/N_Init/include     \
  $(ZLL_INFRA_PATH)/N_Timer/include     \
  $(ZLL_INFRA_PATH)/N_Types/include     \
  $(ZLL_INFRA_PATH)/N_Util/include     \
  $(DRIVERS_PATH)/include        \
  $(HAL_HWD_COMMON_PATH)/include \
  $(HAL_HWI_PATH)/include        \
  $(HAL_PATH)/include            \
  $(OSAL_PATH)                   \
  $(OSAL_PATH)/osal              \
  $(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  $(FREE_RTOS_PATH)/include      \
  $(RTOS_CONFIG_PATH)            \
  $(PARTPACK_PATCH)/include      \
  $(PARTPACK_PATCH)/include/soc  \
  $(CMIS_PATH)

ifeq ($(COMPILER_TYPE), GCC) # GCC flags -------------------------------
  #CFLAGS += -pedantic -Wextra -Wfatal-errors -Werror
  CFLAGS += -Wstrict-overflow -Wstrict-overflow=5 -Wmissing-noreturn
  #CFLAGS += -Wpointer-arith -Wswitch-default  -Wredundant-decls
  #CFLAGS += -Wuninitialized -Winit-self -Wdeclaration-after-statement
  #CFLAGS += -Wundef -Wshadow -Wunsafe-loop-optimizations
  CFLAGS += -Wdisabled-optimization -Wstrict-prototypes
  #CFLAGS += -Wmissing-prototypes -Wmissing-declarations
  #CFLAGS += -Wbad-function-cast -Wcast-qual -Wnested-externs
  CFLAGS += -Winline -Wno-multichar -Wno-unused-function
#  CFLAGS += -Wsign-conversion
ifeq ($(CROSS_COMPILER), avr-)
  CFLAGS += -Wpadded
  CFLAGS += -Wlogical-op  -Wcast-align -Wpacked
##### OPTIMIZATION OPTIONS #####
  CFLAGS += -fsee
endif
ifeq ($(CROSS_COMPILER), arm-none-eabi-)
  CFLAGS += -Wjump-misses-init
endif
##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -isystem ,$(include_path))
else

#TMP_CFLAGS:=$(patsubst -e,,$(CFLAGS))
#CFLAGS = $(TMP_CFLAGS) --strict_ansi

#CFLAGS += --misrac2004=4,5,~5.1,~5.3,~5.4,6,~6.3,~6.4,8,~8.1,~8.5,~8.11,9,~9.2,~9.3,10,~10.1,~10.3,~10.5,~10.6
#CFLAGS += --misrac2004=11.1,~11.3,13,~13.5,15,~15.2,~15.4,16,~16.3,~16.5,17,~17.4,18.1,20,~20.1,~20.2,~20.6
CFLAGS += --misrac_verbose

##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -I,$(include_path))
endif

##### PATHS FLAGS OF ZCL INCLUDES #########
CFLAGS += -I$(ZCL_PATH)/include
CFLAGS += -I$(ZCL_PATH)/include/private

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIBNAME=lib$(ZCL_LIB).a
LIB = $(LIBDIR)/$(LIBNAME)

cmodules = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

ifeq ($(ZCL_WHOLE_BUILD), 1)
CFLAGS +=-DZCL_PRIVATE=static
sources = $(BUILDDIR)/src/zclComplete.c
objects = $(BUILDDIR)/objs/zclComplete.o
else
CFLAGS +=-DZCL_PRIVATE=   
sources = $(cmodules)
objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))
endif

###### TARGETS ################
all: component_label $(LIB)
component_label:
	@echo
	@echo ----------------------------------------------------
	@echo ZCL library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BUILDDIR)/objs/
	$(Q)mkdir -p $(BUILDDIR)/lib/
################
$(BUILDDIR)/src/zclComplete.c: $(cmodules)
	$(Q)cat $^ > $@

################
$(BUILDDIR)/objs/%.o: $(BUILDDIR)/src/%.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $^ -o $@

################
$(LIB): $(objects)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(LIB) $(objects)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(LIB)

################
clean:
	@echo
	@echo ----------------------------------------------------
	@echo ZCL component cleaning is started...
	$(Q)rm -f $(objects) $(LIB) $(wildcard $(ZCL_PATH)/list/*.*)
	$(Q)rm -f $(BUILDDIR)/src/zclComplete.c
	@echo ZCL component cleaning is done!
	@echo ----------------------------------------------------
