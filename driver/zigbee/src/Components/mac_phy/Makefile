#-------------------------------------------------------------------------------
#  \file Makefile
#
#  \brief Make file for MAC sublayer part.
#
#  \author
#    Microchip Corporation: http://ww.microchip.com \n
#    Support email: support@microchip.com
#
#  Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
#  Licensed under Microchip's Limited License Agreement.
#
#-------------------------------------------------------------------------------

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules
#***************************** Macro definitions *******************************

#***************************** Define's flags **********************************
## If this falg is enabled, frame will be sent by writing TX_START SPI command,
## otherwise by setting SLP_TR pin.
#CFLAGS += -D_SENT_BY_SPI_CMD_

## If this falg is enabled, standard supports frames of IEEE 802.15.4-2003
## otherwise frames of IEEE 802.15.4-2006.
CFLAGS += -D_MAC_IEEE_STD_2003_

## If this flag is enbaled, frames with different frame version will be discarted.
#CFLAGS_HWD += -DCHECK_FRAME_VERSION

## If this flag is enabled, the library will try to check pending data
## and control Frame Pending Bit of ACK for Data Request.
## This feature should be used with _PENDING_EMPTY_DATA_FRAME_ together.
#CFLAGS += -D_CONTROL_FRAME_PENDING_BIT_

## If this flag is enabled, the library will ignore Frame Pending Bit of ACK from
## Data Request.
CFLAGS += -D_IGNORE_FRAME_PENDING_BIT_

## If this flag is enabled, Poll Confirm will be called before Data Indication
## like in standard.
#CFLAGS += -D_POLL_CONF_BEFORE_DATA_IND

## If this flag is enabled, Battery Monitor functions will be added to the library.
#CFLAGS += -D_RF_BAT_MON_

## If this flag is enabled, Random generation function will be added to the library.
CFLAGS += -D_RF_RND_

## If this flag is enabled, frames will be retransmitted by software
## otherwise by hardware. It's available only for AT86RF230.
CFLAGS_HWD += -D_SW_FRAME_RETRANSMISSION_

## If this flag is enabled, there will be a reply empty data frame in the air after
## data request acknowledged by ack with frame pending bit set to one.
## In compliance with IEEE2006 (7.5.6.3 Extracting pending data from a coordinator).
#CFLAGS += -D_PENDING_EMPTY_DATA_FRAME_

#Detecting a pan id conflict on MAC layer.
#CFLAGS += -D_MAC_DETECT_PANID_CONFLICT

## If this flag is enabled - MAC accepts ZigBee standart corrections related to IEEE.
#CFLAGS += -D_IEEE_ZIGBEE_COMPLIANCE_

## This flag specifies that the pending address list will be included in a frame or not.
#CFLAGS += -D_MAC_BEACON_PENDING_ADDR_LIST_

## Enable FTN and PLL calibration of RF chip. See the RF_CalibrationReq request.
CFLAGS += -D_RF_CALIBRATION_

## Enable register accessing of RF chip. See the RF_RegAccessReq request.
#CFLAGS += -D_RF_REG_ACCESS_

#*******************************************************************************

ifneq (, $(findstring -D_MAC_HW_AES_, $(CFLAGS)))
  ifeq (, $(findstring $(RFCHIP), AT86RF231 AT86RF233 AT86RF212))
    $(error ERROR: $(RFCHIP) doesn't support security)
  endif
  CFLAGS += -D_RF_AES_
  RF_AES = 1
endif

ifneq (, $(findstring -D_RF_BAT_MON_, $(CFLAGS)))
RF_BAT_MON = 1
endif

ifneq (, $(findstring -D_RF_RND_, $(CFLAGS)))
RF_RND = 1
endif

ifneq (, $(findstring -D_RF_TX_RX_INDICATOR_, $(CFLAGS)))
RF_TX_RX_INDICATOR = 1
endif

ifneq (, $(findstring -D_RF_CALIBRATION_, $(CFLAGS)))
RF_CALIBRATION = 1
endif

ifneq (, $(findstring -D_RF_REG_ACCESS_, $(CFLAGS)))
RF_REG_ACCESS = 1
endif

ifeq ($(MAC_CONTROL_FRAME_PENDING_BIT), TRUE)
 CFLAGS += -D_PENDING_EMPTY_DATA_FRAME_
 CFLAGS += -D_CONTROL_FRAME_PENDING_BIT_
 CFLAGS := $(filter-out -D_IGNORE_FRAME_PENDING_BIT_,$(CFLAGS))
endif

CFLAGS_HWD += -D$(RFCHIP)

#***************************** Paths *******************************************

MACHWI_PATH             = $(MAC_PHY_PATH)/MAC_HWI
MACHWDPHY_PATH          = $(MAC_PHY_PATH)/MAC_HWD_PHY
## AT86RF230 paths
ifeq ($(RFCHIP), AT86RF230)
MACHWD_PATH             = $(MACHWDPHY_PATH)/RF230/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/RF230/PHY
endif
## AT86RF230B paths
ifeq ($(RFCHIP), AT86RF230B)
MACHWD_PATH             = $(MACHWDPHY_PATH)/RF230/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/RF230/PHY
endif
## AT86RF231 paths
ifeq ($(RFCHIP), AT86RF231)
MACHWD_PATH             = $(MACHWDPHY_PATH)/RF231_RF212/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/RF231_RF212/PHY
endif
## AT86RF233 paths
ifeq ($(RFCHIP), AT86RF233)
MACHWD_PATH             = $(MACHWDPHY_PATH)/RF231_RF212/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/RF231_RF212/PHY
  ifeq ($(STACK_TYPE), ZGPDEVICE)
  MACHWDZGP_PATH        = $(MACHWDPHY_PATH)/RF231_RF212/MACHWD_ZGP
  endif
  ifeq ($(STACK_TYPE), COMMON_MAC_DEVICE)
  MACHWDZGP_PATH        = $(MACHWDPHY_PATH)/RF231_RF212/MACHWD_ZGP
  endif
endif
## AT86RF212 paths
ifeq ($(RFCHIP), AT86RF212)
MACHWD_PATH             = $(MACHWDPHY_PATH)/RF231_RF212/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/RF231_RF212/PHY
endif
## ATMEGA128RFA1 paths
ifeq ($(RFCHIP), ATMEGA128RFA1)
MACHWD_PATH             = $(MACHWDPHY_PATH)/ATMEGA128RFA1/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/ATMEGA128RFA1/PHY
endif
## ATMEGA256RFR2 paths
ifeq ($(RFCHIP), ATMEGA256RFR2)
MACHWD_PATH             = $(MACHWDPHY_PATH)/ATMEGA128RFA1/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/ATMEGA128RFA1/PHY
  ifeq ($(STACK_TYPE), ZGPDEVICE)
  MACHWDZGP_PATH        = $(MACHWDPHY_PATH)/ATMEGA128RFA1/MACHWD_ZGP
  endif
endif
## ATMEGA256RFR2 paths
ifeq ($(RFCHIP), ATMEGA2564RFR2)
MACHWD_PATH             = $(MACHWDPHY_PATH)/ATMEGA128RFA1/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/ATMEGA128RFA1/PHY
endif
# CUSTOMRF3 paths
ifeq ($(RFCHIP), CUSTOMRF3)
MACHWD_PATH             = $(MACHWDPHY_PATH)/CUSTOMRF3/MAC_HWD
PHY_PATH                = $(MACHWDPHY_PATH)/CUSTOMRF3/PHY
endif

#***************************** Include directories *****************************
CFLAGS +=                        \
-I$(BASE_PATH)     \
-I$(SE_PATH)/include             \
-I$(CS_PATH)/include             \
-I$(CS_PATH)/include/private     \
-I$(HAL_PATH)/include            \
-I$(HAL_HWD_COMMON_PATH)/include \
-I$(HAL_MAC_API_PATH)/include    \
-I$(OSAL_PATH)       \
-I$(OSAL_PATH)/osal       \
-I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
-I$(FREE_RTOS_PATH)/include  \
-I$(RTOS_CONFIG_PATH)        \
-I$(PARTPACK_PATCH)/include \
-I$(PARTPACK_PATCH)/include/soc \
-I$(CMIS_PATH) \

ifeq ($(RF_AES), 1)
CFLAGS +=             \
-I$(SSP_PATH)/include
endif

CFLAGS_HWI +=               \
-I$(BASE_PATH)      \
-I$(MAC_PHY_PATH)/include   \
-I$(MACHWI_PATH)/include    \
-I$(MAC_ENV_PATH)/include   \
-I$(MACHWDPHY_PATH)/        \
-I$(MACHWDPHY_PATH)/include  \
-I$(NWK_PATH)/include       \
-I$(ZDO_PATH)/include       \
-I$(APS_PATH)/include       \
-I$(ZCL_PATH)/include       \
-I$(TC_PATH)/include        \
-I$(SSP_PATH)/include       \
-I$(ZGP_PATH)/include       \
-I$(ZGP_PATH)/GPDevice/include  \
-I$(MACHWDZGP_PATH)/include    \
-I$(PHY_PATH)/include        \
-I$(MACHWD_PATH)/include    \
-I$(OSAL_PATH)/osal        \
-I$(FREE_RTOS_PATH)/include  \
-I$(RTOS_CONFIG_PATH) 

CFLAGS_HWD +=               \
-I$(BASE_PATH)     \
-I$(MAC_PHY_PATH)/include   \
-I$(MACHWI_PATH)/include    \
-I$(MAC_ENV_PATH)/include   \
-I$(MACHWDPHY_PATH)/        \
-I$(MACHWD_PATH)/include    \
-I$(PHY_PATH)/include       \
-I$(NWK_PATH)/include       \
-I$(ZDO_PATH)/include       \
-I$(APS_PATH)/include       \
-I$(ZGP_PATH)/include       \
-I$(ZGP_PATH)/GPDevice/include  \
-I$(MACHWDZGP_PATH)/include  \
-I$(TC_PATH)/include        \
-I$(SSP_PATH)/include       \
# -I$($(OSAL_PATH)/osal
#-I$(FREE_RTOS_PATH)/include \
#-I$(RTOS_CONFIG_PATH)

#***************************** Object files ************************************
# CUSTOMRF3 uses a different files layout
ifneq ($(RFCHIP), CUSTOMRF3)
  objects_machwd =                           \
  $(MACHWD_PATH)/objs/machwdManager.o        \
  $(MACHWD_PATH)/objs/machwdHandlerCtrl.o    \
  $(MACHWD_PATH)/objs/machwdFrameRoutine.o   \
  $(MACHWD_PATH)/objs/machwdTrxCtrl.o        \
  $(MACHWD_PATH)/objs/machwdTrxHandler.o     \
  $(MACHWD_PATH)/objs/machwdTxFrameHandler.o \
  $(MACHWD_PATH)/objs/machwdEdHandler.o      \
  $(MACHWD_PATH)/objs/machwdRxBuffer.o       \
  $(MACHWD_PATH)/objs/machwdRxFrameHandler.o \
  $(MACHWD_PATH)/objs/machwdSetHandler.o     \
  $(MACHWD_PATH)/objs/machwdResetHandler.o
  ifeq ($(RF_AES), 1)
  objects_machwd += \
  $(MACHWD_PATH)/objs/machwdEncryptHandler.o
  endif
  ifeq ($(RF_BAT_MON), 1)
  objects_machwd += \
  $(MACHWD_PATH)/objs/machwdBatMonHandler.o
  endif
  ifeq ($(RF_RND), 1)
  objects_machwd += \
  $(MACHWD_PATH)/objs/machwdRndHandler.o
  endif
  ifeq ($(RF_CALIBRATION), 1)
  objects_machwd += \
  $(MACHWD_PATH)/objs/machwdCalibHandler.o
  endif

  ifeq ($(RF_REG_ACCESS), 1)
  objects_machwd += \
  $(MACHWD_PATH)/objs/machwdRegAccessHandler.o
  endif

  objects_phy =                              \
  $(PHY_PATH)/objs/phyInit.o                 \
  $(PHY_PATH)/objs/phyEd.o                   \
  $(PHY_PATH)/objs/phyStateMachine.o         \
  $(PHY_PATH)/objs/phyRxFrame.o              \
  $(PHY_PATH)/objs/phySetTrxState.o          \
  $(PHY_PATH)/objs/phyTxFrame.o              \
  $(PHY_PATH)/objs/phySet.o                  \
  $(PHY_PATH)/objs/phyReset.o                \
  $(PHY_PATH)/objs/phyRxTxIndicator.o        \
  $(PHY_PATH)/objs/phyAntDiversity.o         \
  $(PHY_PATH)/objs/phyTxPowerConverter.o

  ifneq ($(RFCHIP), ATMEGA128RFA1)
  ifneq ($(RFCHIP), ATMEGA256RFR2)
  ifneq ($(RFCHIP), ATMEGA2564RFR2)
  ifneq ($(HAL), _PIC32CX_)
  objects_phy +=                             \
    $(PHY_PATH)/objs/phyRfSpiProto.o
  endif
  endif
  endif
  endif

  ifeq ($(RF_AES), 1)
  objects_phy += \
    $(PHY_PATH)/objs/phyEncrypt.o
  endif

  ifeq ($(RF_BAT_MON), 1)
  objects_phy += \
    $(PHY_PATH)/objs/phyBatMon.o
  endif

  ifeq ($(RF_RND), 1)
  ifneq ($(RFCHIP), AT86RF230)
  ifneq ($(RFCHIP), AT86RF230B)
  objects_phy += \
  $(PHY_PATH)/objs/phyRnd.o
  endif
  endif
  endif

  ifeq ($(RF_CALIBRATION), 1)
  ifneq ($(RFCHIP), AT86RF230)
  ifneq ($(RFCHIP), AT86RF230B)
  objects_phy += \
  $(PHY_PATH)/objs/phyCalib.o
  endif
  endif
  endif

  ifeq ($(RF_REG_ACCESS), 1)
  objects_phy += \
  $(PHY_PATH)/objs/phyRegAccess.o
  endif

  ifeq ($(RFCHIP), AT86RF233)
  objects_phy += \
  $(PHY_PATH)/objs/phyDeepSleep.o
  endif

  objects_phy_irq =                          \
  $(PHY_PATH)/objs/phyRfIrqDispatcher.o      \
  $(PHY_PATH)/objs/phyRtimerIrqDispatcher.o
  ifeq ($(COMPILER_TYPE), IAR)
    $(PHY_PATH)/objs/phyRfIrqDispatcher.o:  CFLAGS  := $(filter-out -O%,$(CFLAGS)) -Oh
    $(PHY_PATH)/objs/phyRtimerIrqDispatcher.o:  CFLAGS  := $(filter-out -O%,$(CFLAGS)) -Oh
  else ifeq ($(COMPILER_TYPE), GCC)
    $(PHY_PATH)/objs/phyRfIrqDispatcher.o:  CFLAGS  := $(filter-out -O%,$(CFLAGS)) -O3
    $(PHY_PATH)/objs/phyRtimerIrqDispatcher.o:  CFLAGS  := $(filter-out -O%,$(CFLAGS)) -O3
  endif
else # !CUSTOMRF3
  objects_machwd =                           	\
  $(MACHWD_PATH)/objs/machwdDispatcher.o        \
  $(MACHWD_PATH)/objs/machwdFrameProcessor.o    \
  $(MACHWD_PATH)/objs/machwdFrameRoutine.o   	\
  $(MACHWD_PATH)/objs/machwdRxBuffer.o       	\
  $(MACHWD_PATH)/objs/machwdManager.o

  objects_phy =                              	\
  $(PHY_PATH)/objs/phyFrame.o                	\
  $(PHY_PATH)/objs/phyFsm.o                  	\
  $(PHY_PATH)/objs/phyRfSpi.o                	\
  $(PHY_PATH)/objs/phyCustomRf3.o
endif #CUSTOMRF3

objects_macenv =                \
$(MAC_ENV_PATH)/objs/macenvPib.o \
$(MAC_ENV_PATH)/objs/macMem.o

objects_machwi =                                \
$(MACHWI_PATH)/objs/machwiTransactionQueue.o    \
$(MACHWI_PATH)/objs/machwiSwitchRxCtrl.o        \
$(MACHWI_PATH)/objs/machwiTransactionHandler.o  \
$(MACHWI_PATH)/objs/machwiDataHandler.o         \
$(MACHWI_PATH)/objs/machwiDisassociateHandler.o \
$(MACHWI_PATH)/objs/machwiPollHandler.o         \
$(MACHWI_PATH)/objs/machwiPurgeHandler.o        \
$(MACHWI_PATH)/objs/machwiAssociateHandler.o    \
$(MACHWI_PATH)/objs/machwiStartHandler.o        \
$(MACHWI_PATH)/objs/machwiRxEnableHandler.o     \
$(MACHWI_PATH)/objs/machwiOrphanHandler.o       \
$(MACHWI_PATH)/objs/machwiBeaconHandler.o       \
$(MACHWI_PATH)/objs/machwiPanServer.o           \
$(MACHWI_PATH)/objs/machwiSetGetHandler.o       \
$(MACHWI_PATH)/objs/machwiScanHandler.o         \
$(MACHWI_PATH)/objs/machwiManager.o             \
$(MACHWI_PATH)/objs/machwiResetHandler.o        \
$(MACHWI_PATH)/objs/machwiPanIdConflictHandler.o\
$(MACHWI_PATH)/objs/machwiBanNode.o		\
$(MACHWI_PATH)/objs/machwiTransactionHash.o

ifeq ($(STACK_TYPE), ZGPDEVICE)
objects_maczgp =                                \
$(MACHWDZGP_PATH)/objs/macHwdZgpCommon.o
endif

ifeq ($(STACK_TYPE), COMMON_MAC_DEVICE)
objects_maczgp +=                               \
$(MACHWDZGP_PATH)/objs/macHwdZgpCommon.o        
endif

#***************************** Libraries ***************************************
lib_mac = $(MAC_PHY_PATH)/lib/lib$(MAC_PHY_LIB).a

#***************************** Targets *****************************************
vpath %.c $(PHY_PATH)/src/
vpath %.c $(MACHWD_PATH)/src/
ifeq ($(STACK_TYPE), COMMON_MAC_DEVICE)
vpath %.c $(MACHWDZGP_PATH)/src/
endif
vpath %.c $(MAC_ENV_PATH)/src/
vpath %.c $(MACHWI_PATH)/src/
ifeq ($(STACK_TYPE), ZGPDEVICE)
vpath %.c $(MACHWDZGP_PATH)/src/
endif
all: component_label $(lib_mac) size_mac

component_label:
	@echo
	@echo ----------------------------------------------------
	@echo MAC and PHY library creation.
	@echo ----------------------------------------------------

	$(Q)mkdir -p $(MAC_ENV_PATH)/objs/
	$(Q)mkdir -p $(PHY_PATH)/objs/
	$(Q)mkdir -p $(MACHWD_PATH)/objs/
	$(Q)mkdir -p $(MACHWI_PATH)/objs/
	$(Q)mkdir -p $(MACHWDZGP_PATH)/objs/
	$(Q)mkdir -p $(MAC_PHY_PATH)/lib/

$(PHY_PATH)/objs/%.o: %.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $< -o $@

$(MACHWD_PATH)/objs/%.o: %.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $< -o $@

$(MAC_ENV_PATH)/objs/%.o: %.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWI) $(CFLAGS_HWD) $< -o $@

$(MACHWI_PATH)/objs/%.o: %.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWI) $^ -o $@

$(MACHWDZGP_PATH)/objs/%.o: %.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWI) $^ -o $@

$(lib_mac): $(objects_phy) $(objects_phy_irq) $(objects_machwd) $(objects_macenv) $(objects_machwi) $(objects_maczgp)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $@ $^

size_mac: $(lib_mac)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(lib_mac)

clean:
	@echo
	@echo ----------------------------------------------------
	@echo 'MAC & PHY common component cleaning is started...'
	$(Q)rm -f $(objects_machwd) $(objects_phy) $(objects_phy_irq) $(objects_macenv) $(objects_machwi) $(objects_maczgp) $(lib_mac) $(wildcard $(MAC_PHY_PATH)/list/*.*)
	@echo 'MAC & PHY common component cleaning is done!'
	@echo ----------------------------------------------------

# eof Makefile
