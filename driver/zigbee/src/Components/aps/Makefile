###########################################################################//##
# \file  Makefile
#
# \brief Main makefile of APS-layer.
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
#   $Id: Makefile 29223 2015-12-23 16:04:11Z parthasarathy.gunase $
################################################################################

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

#ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_AVR)
#  TMP_CFLAGS:=$(patsubst -Ohz,,$(CFLAGS))
#  CFLAGS = $(TMP_CFLAGS) -On
#endif

# Build APS layer as whole file
APS_WHOLE_BUILD = 1

###### APS MODULES #########
modules =              \
  apsAuthenticate      \
  apsBinding           \
  apsBindingTable      \
  apsCommand           \
  apsDataManager       \
  apsEndpoint          \
  apsGroup             \
  apsGroupTable        \
  apsInterpan          \
  apsKeyPairSet        \
  apsMemoryManager     \
  apsRejectDuplicate   \
  apsRemoveDevice      \
  apsRequestKey        \
  apsSkke              \
  apsSkkeInitiator     \
  apsSkkeResponder     \
  apsSmSsp             \
  apsStateMachine      \
  apsSwitchKey         \
  apsTaskManager       \
  apsTransportAppKey   \
  apsTransportNwkKey   \
  apsTransportTrustKey \
  apsTransportKey      \
  apsUpdateDevice      \
  apsAIB               \
  apsVerifyKey         \
  apsConfirmKey

include_path =                        \
  $(BASE_PATH)                        \
  $(KF_INCS)                          \
  $(SSP_PATH)/include                 \
  $(SE_PATH)/include                  \
  $(TC_PATH)/include                  \
  $(MAC_PHY_PATH)/include             \
  $(MAC_HWI_PATH)/include             \
  $(MAC_HWD_PATH)/include             \
  $(MAC_ENV_PATH)/include             \
  $(MAC_PHY_PATH)/MAC_ENV/include     \
  $(MAC_PHY_PATH)/MAC_HWD_PHY/include \
  $(MAC_PHY_PATH)/MAC_HWI/include     \
  $(CS_PATH)/include                  \
  $(CS_PATH)/include/private          \
  $(NWK_PATH)/include                 \
  $(ZDO_PATH)/include                 \
  $(ZDO_PATH)/include/private         \
  $(ZCL_PATH)/include                 \
  $(ZCL_PATH)/include/private         \
  $(HAL_HWD_COMMON_PATH)/include      \
  $(HAL_HWI_PATH)/include             \
  $(HAL_PATH)/include                 \
  $(APS_PATH)/include                 \
  $(APS_PATH)/include/private         \
  $(OSAL_PATH)                        \
  $(OSAL_PATH)/osal                   \
  $(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  $(FREE_RTOS_PATH)/include           \
  $(RTOS_CONFIG_PATH)                 \
  $(PARTPACK_PATCH)/include           \
  $(PARTPACK_PATCH)/include/soc       \
  $(CMIS_PATH)

ifeq ($(COMPILER_TYPE), GCC) # GCC flags -------------------------------
  #CFLAGS += -pedantic -Wextra -Wfatal-errors -Werror
  CFLAGS += -Wstrict-overflow -Wstrict-overflow=5 -Wmissing-noreturn
  #CFLAGS += -Wpointer-arith -Wswitch-default  -Wredundant-decls
  CFLAGS += -Wuninitialized -Winit-self -Wdeclaration-after-statement
  CFLAGS += -Wundef -Wshadow -Wunsafe-loop-optimizations
  CFLAGS += -Wdisabled-optimization -Wstrict-prototypes
  #CFLAGS += -Wmissing-prototypes -Wmissing-declarations
  #CFLAGS += -Wbad-function-cast -Wcast-qual -Wnested-externs
  CFLAGS += -Winline -Wno-multichar
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
CFLAGS += $(addprefix -I,$(include_path))

CFLAGS += --misrac2004=4,~4.1,5,~5.1,~5.3,~5.4,6,~6.3,~6.4,8,~8.1,~8.5,~8.11,9,~9.2,~9.3,10,~10.1,~10.3,~10.5,~10.6
CFLAGS += --misrac2004=11.1,~11.3,13,~13.5,15,~15.2,~15.4,16,~16.3,~16.5,17,~17.4,18.1,20,~20.1,~20.2,~20.6
CFLAGS += --misrac_verbose

endif

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIBNAME=lib$(APS_LIB).a
LIB = $(LIBDIR)/$(LIBNAME)

cmodules = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

ifeq ($(APS_WHOLE_BUILD), 1)
  CFLAGS +=-DAPS_PRIVATE=static
  sources = $(BUILDDIR)/src/aps.c
  objects = $(BUILDDIR)/objs/aps.o
else
  CFLAGS +=-DAPS_PRIVATE=   
  sources = $(cmodules)
  objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))
endif

###### TARGETS ################
all: component_label $(LIB)
component_label:
	@echo
	@echo ----------------------------------------------------
	@echo APS library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BUILDDIR)/objs/
	$(Q)mkdir -p $(BUILDDIR)/lib/
################
$(BUILDDIR)/src/aps.c: $(cmodules)
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
	@echo APS component cleaning is started...
	$(Q)rm -f $(objects) $(LIB) $(wildcard $(APS_PATH)/list/*.*)
	$(Q)rm -f $(BUILDDIR)/src/aps.c
	@echo APS component cleaning is done!
	@echo ----------------------------------------------------

