###########################################################################//##
# \file  Makefile
#
# \brief Main makefile of NWK-layer.
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
#   $Id: Makefile 30955 2016-08-25 11:09:52Z agasthian.s $
################################################################################

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

# Build NWK layer as whole file
NWK_WHOLE_BUILD = 1

#ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_AVR)
#  TMP_CFLAGS:=$(patsubst -Ohz,,$(CFLAGS))
#  CFLAGS = $(TMP_CFLAGS) -Om
#endif

###### NWK MODULES #########
modules =                \
  nwkAddress             \
  nwkAddressConflict     \
  nwkAddressMap          \
  nwkAddressResolv       \
  nwkBTT                 \
  nwkCommands            \
  nwkConcentrator        \
  nwkDataReq             \
  nwkDirectJoin          \
  nwkDiscovery           \
  nwkEDScan              \
  nwkFormation           \
  nwkFrame               \
  nwkGroup               \
  nwkIB                  \
  nwkInCounterSet        \
  nwkJoinInd             \
  nwkJoinReq             \
  nwkLeaveInd            \
  nwkLeaveReq            \
  nwkLinkStatus          \
  nwkLoopback            \
  nwkManager             \
  nwkManyToOne           \
  nwkNeighborTable       \
  nwkMem                 \
  nwkOrphan              \
  nwkSilentJoin          \
  nwkPacket              \
  nwkPassiveAck          \
  nwkPermitJoining       \
  nwkProfiler            \
  nwkReportCommand       \
  nwkReset               \
  nwkRouteCache          \
  nwkRouteDiscovery      \
  nwkRouteDiscoveryTable \
  nwkRouteRecord         \
  nwkRouteReply          \
  nwkRouteRequest        \
  nwkRouting             \
  nwkRoutingTable        \
  nwkRx                  \
  nwkSecurity            \
  nwkSourceRouting       \
  nwkStartRouter         \
  nwkStateMachine        \
  nwkStatusInd           \
  nwkStatusReq           \
  nwkSync                \
  nwkSyncLoss            \
  nwkTaskManager         \
  nwkTx                  \
  nwkTxDelay             \
  nwkTxSecurity          \
  nwkUpdateCommand       \
  nwkEndDeviceTimeoutReq \
  nwkEndDeviceTimeoutInd

include_path =                     \
  $(BASE_PATH)                     \
  $(KF_INCS)                       \
  $(SSP_PATH)/include              \
  $(SE_PATH)/include               \
  $(MAC_PHY_PATH)/include          \
  $(MAC_HWI_PATH)/include          \
  $(MAC_HWD_PATH)/include          \
  $(MAC_ENV_PATH)/include          \
  $(CS_PATH)/include               \
  $(CS_PATH)/include/private       \
  $(ZLL_PLATFORM_PATH)             \
  $(ZLL_PATH)                      \
  $(PDS_PATH)/lib/include          \
  $(COMPONENTS_PATH)/PDS/include   \
  $(ZLL_INFRA_PATH)/N_Types/include\
  $(APS_PATH)/include              \
  $(ZCL_PATH)/include              \
  $(APS_PATH)/include/private    \
  $(ZDO_PATH)/include            \
  $(ZDO_PATH)/include/private    \
  $(HAL_HWD_COMMON_PATH)/include   \
  $(HAL_HWI_PATH)/include          \
  $(HAL_PATH)/include              \
  $(OSAL_PATH)       \
  $(OSAL_PATH)/osal       \
  $(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  $(FREE_RTOS_PATH)/include  \
  $(RTOS_CONFIG_PATH)        \
  $(PARTPACK_PATCH)/include \
  $(PARTPACK_PATCH)/include/soc \
  $(CMIS_PATH)

ifeq ($(COMPILER_TYPE), GCC) # GCC flags -------------------------------
  #CFLAGS += -pedantic -Wextra -Wfatal-errors -Werror
  CFLAGS += -Wstrict-overflow -Wstrict-overflow=5 -Wmissing-noreturn
  CFLAGS += -Wpointer-arith -Wswitch-default  
  CFLAGS += -Wuninitialized -Winit-self -Wdeclaration-after-statement
  CFLAGS += -Wundef -Wshadow 
  CFLAGS += -Wdisabled-optimization -Wstrict-prototypes
  #CFLAGS += -Wmissing-prototypes -Wmissing-declarations
  CFLAGS += -Wbad-function-cast -Wcast-qual -Wnested-externs
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

CFLAGS += --misrac2004=4,5,~5.1,~5.3,~5.4,6,~6.3,~6.4,8,~8.1,~8.5,~8.11,9,~9.3,10,~10.1,~10.3,~10.5
CFLAGS += --misrac2004=11.1,~11.3,13,~13.5,15,~15.2,~15.4,16,~16.3,~16.5,17,~17.4,18.1,20,~20.1,~20.2,~20.6
CFLAGS += --misrac_verbose

##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -I,$(include_path))
endif

##### PATHS FLAGS OF NWK INCLUDES #########
CFLAGS += -I$(NWK_PATH)/include
CFLAGS += -I$(NWK_PATH)/include/private

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIBNAME=lib$(NWK_LIB).a
LIB = $(LIBDIR)/$(LIBNAME)

cmodules = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

ifeq ($(NWK_WHOLE_BUILD), 1)
CFLAGS +=-DNWK_PRIVATE=static
sources = $(BUILDDIR)/src/nwk.c
objects = $(BUILDDIR)/objs/nwk.o
else
CFLAGS +=-DNWK_PRIVATE=   
sources = $(cmodules)
objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))
endif

###### TARGETS ################
all: component_label $(LIB)
component_label:
	@echo
	@echo ----------------------------------------------------
	@echo NWK library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BUILDDIR)/objs/
	$(Q)mkdir -p $(BUILDDIR)/lib/
################
$(BUILDDIR)/src/nwk.c: $(cmodules)
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
	@echo NWK component cleaning is started...
	$(Q)rm -f $(objects) $(LIB) $(wildcard $(NWK_PATH)/list/*.*)
	$(Q)rm -f $(BUILDDIR)/src/nwk.c
	@echo NWK component cleaning is done!
	@echo ----------------------------------------------------

