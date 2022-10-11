/**
 * \brief Header file for PIC32CX1012BZ25048_FPGA
 *
 * Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2019-10-24T22:02:23Z */
#ifndef _PIC32CX1012BZ25048_FPGA_H_
#define _PIC32CX1012BZ25048_FPGA_H_

// Header version uses Semantic Versioning 2.0.0 (https://semver.org/)
#define HEADER_FORMAT_VERSION "2.0.0"

#define HEADER_FORMAT_VERSION_MAJOR (2)
#define HEADER_FORMAT_VERSION_MINOR (0)

/** \addtogroup PIC32CX1012BZ25048_FPGA_definitions PIC32CX1012BZ25048_FPGA definitions
  This file defines all structures and symbols for PIC32CX1012BZ25048_FPGA:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
 *  @{
 */

#ifdef __cplusplus
 extern "C" {
#endif

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  include <stdint.h>
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !defined(SKIP_INTEGER_LITERALS)
#  if defined(_U_) || defined(_L_) || defined(_UL_)
#    error "Integer Literals macros already defined elsewhere"
#  endif

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/* Macros that deal with adding suffixes to integer literal constants for C/C++ */
#  define _U_(x) (x ## U)    /**< C code: Unsigned integer literal constant value */
#  define _L_(x) (x ## L)    /**< C code: Long integer literal constant value */
#  define _UL_(x) (x ## UL)  /**< C code: Unsigned Long integer literal constant value */

#else /* Assembler */

#  define _U_(x) x    /**< Assembler: Unsigned integer literal constant value */
#  define _L_(x) x    /**< Assembler: Long integer literal constant value */
#  define _UL_(x) x   /**< Assembler: Unsigned Long integer literal constant value */
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* SKIP_INTEGER_LITERALS */
/** @}  end of Atmel Global Defines */

/* ************************************************************************** */
/*   CMSIS DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                            */
/* ************************************************************************** */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** Interrupt Number Definition */
typedef enum IRQn
{
/******  CORTEX-M4 Processor Exceptions Numbers ******************************/
  Reset_IRQn                = -15, /**< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn       = -14, /**< -14 Non Maskable Interrupt              */
  HardFault_IRQn            = -13, /**< -13 Cortex-M4 Hard Fault Interrupt      */
  MemoryManagement_IRQn     = -12, /**< -12 Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn             = -11, /**< -11 Cortex-M4 Bus Fault Interrupt       */
  UsageFault_IRQn           = -10, /**< -10 Cortex-M4 Usage Fault Interrupt     */
  SVCall_IRQn               =  -5, /**< -5  Cortex-M4 SV Call Interrupt         */
  DebugMonitor_IRQn         =  -4, /**< -4  Cortex-M4 Debug Monitor Interrupt   */
  PendSV_IRQn               =  -2, /**< -2  Cortex-M4 Pend SV Interrupt         */
  SysTick_IRQn              =  -1, /**< -1  Cortex-M4 System Tick Interrupt     */
/******  PIC32CX1012BZ25048_FPGA specific Interrupt Numbers ***********************************/
  RTC_IRQn                  =   0, /**< 0   Real-Time Counter (RTC)             */
  EIC_IRQn                  =   1, /**< 1   External Interrupt Controller (EIC) */
  FREQM_IRQn                =   2, /**< 2   Frequency Meter (FREQM)             */
  FSIB_0_IRQn               =   3, /**< 3   flash controller (FC)               */
  PORT_A_IRQn               =   4, /**< 4   GPIO (GPIOA)                        */
  PORT_B_IRQn               =   5, /**< 5   GPIO (GPIOB)                        */
  DMAC_0_3_IRQn             =   6, /**< 6   Direct Memory Access Controller (DMAC) */
  DMAC_4_15_IRQn            =   7, /**< 7   Direct Memory Access Controller (DMAC) */
  EVSYS_0_3_IRQn            =   8, /**< 8   Event System Interface (EVSYS)      */
  EVSYS_11_4_IRQn           =   9, /**< 9   Event System Interface (EVSYS)      */
  PAC_IRQn                  =  10, /**< 10  Peripheral Access Controller (PAC)  */
  RAMECC_IRQn               =  11, /**< 11  RAM ECC (RAMECC)                    */
  SERCOM0_0_IRQn            =  12, /**< 12  Serial Communication Interface (SERCOM0) */
  SERCOM1_0_IRQn            =  13, /**< 13  Serial Communication Interface (SERCOM1) */
  SERCOM2_0_IRQn            =  14, /**< 14  Serial Communication Interface (SERCOM2) */
  SERCOM3_0_IRQn            =  15, /**< 15  Serial Communication Interface (SERCOM3) */
  TCC0_0_IRQn               =  16, /**< 16  Timer Counter Control (TCC0)        */
  TCC1_0_IRQn               =  17, /**< 17  Timer Counter Control (TCC1)        */
  TCC2_0_IRQn               =  18, /**< 18  Timer Counter Control (TCC2)        */
  TC0_IRQn                  =  19, /**< 19  Basic Timer Counter (TC0)           */
  TC1_IRQn                  =  20, /**< 20  Basic Timer Counter (TC1)           */
  TC2_IRQn                  =  21, /**< 21  Basic Timer Counter (TC2)           */
  TC3_IRQn                  =  22, /**< 22  Basic Timer Counter (TC3)           */
  ADCTRL_IRQn               =  23, /**< 23  12-bit Analog to Digital Converter (ADC) */
  AC_IRQn                   =  24, /**< 24  Analog Comparators (AC)             */
  AES_IRQn                  =  25, /**< 25  Advanced Encryption Standard (AES)  */
  TRNG_IRQn                 =  26, /**< 26  True Random Generator (TRNG)        */
  ICM_IRQn                  =  27, /**< 27  Integrity Check Monitor (ICM)       */
  PUKCC_IRQn                =  28, /**< 28  PUblic-Key Cryptography Controller (PUKCC) */
  QSPI_IRQn                 =  29, /**< 29  Quad SPI interface (QSPI)           */
  ZB_INT0_IRQn              =  30, /**< 30  ZIGBEE Radio Registers (ZIGBEE)     */
  BT_INT0_IRQn              =  31, /**< 31  BLE Radio Registers (BLE)           */
  BT_INT1_IRQn              =  32, /**< 32  BLE Radio Registers (BLE)           */
  ARBITER_IRQn              =  33, /**< 33  Radio Arbiter (ARB)                 */
  ADC_FLT_IRQn              =  34, /**< 34  12-bit Analog to Digital Converter (ADC) */
  ADC_FCC_IRQn              =  35, /**< 35  12-bit Analog to Digital Converter (ADC) */
  ADC_BGVR_RDY_IRQn         =  36, /**< 36  12-bit Analog to Digital Converter (ADC) */
  CLKI_WAKEUP_NMI_IRQn      =  37, /**< 37  BLE Radio Registers (BLE)           */
  BT_LC_IRQn                =  38, /**< 38  BLE Radio Registers (BLE)           */
  BT_RC_IRQn                =  39, /**< 39  BLE Radio Registers (BLE)           */

  PERIPH_MAX_IRQn           =  39  /**< Max peripheral ID */
} IRQn_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;
  /* Cortex-M handlers */
  void* pfnReset_Handler;                        /* -15 Reset Vector, invoked on Power up and warm reset */
  void* pfnNonMaskableInt_Handler;               /* -14 Non Maskable Interrupt */
  void* pfnHardFault_Handler;                    /* -13 Cortex-M4 Hard Fault Interrupt */
  void* pfnMemoryManagement_Handler;             /* -12 Cortex-M4 Memory Management Interrupt */
  void* pfnBusFault_Handler;                     /* -11 Cortex-M4 Bus Fault Interrupt */
  void* pfnUsageFault_Handler;                   /* -10 Cortex-M4 Usage Fault Interrupt */
  void* pvReservedC9;
  void* pvReservedC8;
  void* pvReservedC7;
  void* pvReservedC6;
  void* pfnSVCall_Handler;                       /*  -5 Cortex-M4 SV Call Interrupt */
  void* pfnDebugMonitor_Handler;                 /*  -4 Cortex-M4 Debug Monitor Interrupt */
  void* pvReservedC3;
  void* pfnPendSV_Handler;                       /*  -2 Cortex-M4 Pend SV Interrupt */
  void* pfnSysTick_Handler;                      /*  -1 Cortex-M4 System Tick Interrupt */

  /* Peripheral handlers */
  void* pfnRTC_Handler;                          /*   0 Real-Time Counter (RTC) */
  void* pfnEIC_Handler;                          /*   1 External Interrupt Controller (EIC) */
  void* pfnFREQM_Handler;                        /*   2 Frequency Meter (FREQM) */
  void* pfnFSIB_0_Handler;                       /*   3 flash controller (FC) */
  void* pfnPORT_A_Handler;                       /*   4 GPIO (GPIOA) */
  void* pfnPORT_B_Handler;                       /*   5 GPIO (GPIOB) */
  void* pfnDMAC_0_3_Handler;                     /*   6 Direct Memory Access Controller (DMAC) */
  void* pfnDMAC_4_15_Handler;                    /*   7 Direct Memory Access Controller (DMAC) */
  void* pfnEVSYS_0_3_Handler;                    /*   8 Event System Interface (EVSYS) */
  void* pfnEVSYS_11_4_Handler;                   /*   9 Event System Interface (EVSYS) */
  void* pfnPAC_Handler;                          /*  10 Peripheral Access Controller (PAC) */
  void* pfnRAMECC_Handler;                       /*  11 RAM ECC (RAMECC) */
  void* pfnSERCOM0_0_Handler;                    /*  12 Serial Communication Interface (SERCOM0) */
  void* pfnSERCOM1_0_Handler;                    /*  13 Serial Communication Interface (SERCOM1) */
  void* pfnSERCOM2_0_Handler;                    /*  14 Serial Communication Interface (SERCOM2) */
  void* pfnSERCOM3_0_Handler;                    /*  15 Serial Communication Interface (SERCOM3) */
  void* pfnTCC0_0_Handler;                       /*  16 Timer Counter Control (TCC0) */
  void* pfnTCC1_0_Handler;                       /*  17 Timer Counter Control (TCC1) */
  void* pfnTCC2_0_Handler;                       /*  18 Timer Counter Control (TCC2) */
  void* pfnTC0_Handler;                          /*  19 Basic Timer Counter (TC0) */
  void* pfnTC1_Handler;                          /*  20 Basic Timer Counter (TC1) */
  void* pfnTC2_Handler;                          /*  21 Basic Timer Counter (TC2) */
  void* pfnTC3_Handler;                          /*  22 Basic Timer Counter (TC3) */
  void* pfnADCTRL_Handler;                       /*  23 12-bit Analog to Digital Converter (ADC) */
  void* pfnAC_Handler;                           /*  24 Analog Comparators (AC) */
  void* pfnAES_Handler;                          /*  25 Advanced Encryption Standard (AES) */
  void* pfnTRNG_Handler;                         /*  26 True Random Generator (TRNG) */
  void* pfnICM_Handler;                          /*  27 Integrity Check Monitor (ICM) */
  void* pfnPUKCC_Handler;                        /*  28 PUblic-Key Cryptography Controller (PUKCC) */
  void* pfnQSPI_Handler;                         /*  29 Quad SPI interface (QSPI) */
  void* pfnZB_INT0_Handler;                      /*  30 ZIGBEE Radio Registers (ZIGBEE) */
  void* pfnBT_INT0_Handler;                      /*  31 BLE Radio Registers (BLE) */
  void* pfnBT_INT1_Handler;                      /*  32 BLE Radio Registers (BLE) */
  void* pfnARBITER_Handler;                      /*  33 Radio Arbiter (ARB) */
  void* pfnADC_FLT_Handler;                      /*  34 12-bit Analog to Digital Converter (ADC) */
  void* pfnADC_FCC_Handler;                      /*  35 12-bit Analog to Digital Converter (ADC) */
  void* pfnADC_BGVR_RDY_Handler;                 /*  36 12-bit Analog to Digital Converter (ADC) */
  void* pfnCLKI_WAKEUP_NMI_Handler;              /*  37 BLE Radio Registers (BLE) */
  void* pfnBT_LC_Handler;                        /*  38 BLE Radio Registers (BLE) */
  void* pfnBT_RC_Handler;                        /*  39 BLE Radio Registers (BLE) */
} DeviceVectors;

/* Defines for Deprecated Interrupt and Exceptions handler names */
#define pfnMemManage_Handler      pfnMemoryManagement_Handler     /**< \deprecated  Backward compatibility for ASF*/
#define pfnDebugMon_Handler       pfnDebugMonitor_Handler         /**< \deprecated  Backward compatibility for ASF*/
#define pfnNMI_Handler            pfnNonMaskableInt_Handler       /**< \deprecated  Backward compatibility for ASF*/
#define pfnSVC_Handler            pfnSVCall_Handler               /**< \deprecated  Backward compatibility for ASF*/

#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#if !defined DONT_USE_PREDEFINED_CORE_HANDLERS
/* CORTEX-M4 exception handlers */
void Reset_Handler                 ( void );
void NonMaskableInt_Handler        ( void );
void HardFault_Handler             ( void );
void MemoryManagement_Handler      ( void );
void BusFault_Handler              ( void );
void UsageFault_Handler            ( void );
void SVCall_Handler                ( void );
void DebugMonitor_Handler          ( void );
void PendSV_Handler                ( void );
void SysTick_Handler               ( void );
#endif /* DONT_USE_PREDEFINED_CORE_HANDLERS */

#if !defined DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS
/* Peripherals interrupt handlers */
void RTC_Handler                   ( void );
void EIC_Handler                   ( void );
void FREQM_Handler                 ( void );
void FSIB_0_Handler                ( void );
void PORT_A_Handler                ( void );
void PORT_B_Handler                ( void );
void DMAC_0_3_Handler              ( void );
void DMAC_4_15_Handler             ( void );
void EVSYS_0_3_Handler             ( void );
void EVSYS_11_4_Handler            ( void );
void PAC_Handler                   ( void );
void RAMECC_Handler                ( void );
void SERCOM0_0_Handler             ( void );
void SERCOM1_0_Handler             ( void );
void SERCOM2_0_Handler             ( void );
void SERCOM3_0_Handler             ( void );
void TCC0_0_Handler                ( void );
void TCC1_0_Handler                ( void );
void TCC2_0_Handler                ( void );
void TC0_Handler                   ( void );
void TC1_Handler                   ( void );
void TC2_Handler                   ( void );
void TC3_Handler                   ( void );
void ADCTRL_Handler                ( void );
void AC_Handler                    ( void );
void AES_Handler                   ( void );
void TRNG_Handler                  ( void );
void ICM_Handler                   ( void );
void PUKCC_Handler                 ( void );
void QSPI_Handler                  ( void );
void ZB_INT0_Handler               ( void );
void BT_INT0_Handler               ( void );
void BT_INT1_Handler               ( void );
void ARBITER_Handler               ( void );
void ADC_FLT_Handler               ( void );
void ADC_FCC_Handler               ( void );
void ADC_BGVR_RDY_Handler          ( void );
void CLKI_WAKEUP_NMI_Handler       ( void );
void BT_LC_Handler                 ( void );
void BT_RC_Handler                 ( void );
#endif /* DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS */
/* Defines for Deprecated Interrupt and Exceptions handler names */
#define MemManage_Handler         MemoryManagement_Handler        /**< \deprecated  Backward compatibility*/
#define DebugMon_Handler          DebugMonitor_Handler            /**< \deprecated  Backward compatibility*/
#define NMI_Handler               NonMaskableInt_Handler          /**< \deprecated  Backward compatibility*/
#define SVC_Handler               SVCall_Handler                  /**< \deprecated  Backward compatibility*/

#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/*
 * \brief Configuration of the CORTEX-M4 Processor and Core Peripherals
 */
#define __CM4_REV                 0x0001
#define __DEBUG_LVL                    3
#define __FPU_PRESENT                  1
#define __MPU_PRESENT                  1
#define __NVIC_PRIO_BITS               3
#define __TRACE_LVL                    2
#define __VTOR_PRESENT                 1
#define __Vendor_SysTickConfig         0

/*
 * \brief CMSIS includes
 */
#include "core_cm4.h"
#if defined USE_CMSIS_INIT
#include "system_bz25.h"
#endif /* USE_CMSIS_INIT */

/** \defgroup PIC32CX1012BZ25048_FPGA_api Peripheral Software API
 *  @{
 */

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR PIC32CX1012BZ25048_FPGA           */
/* ************************************************************************** */
#include "component/ac.h"
#include "component/adc.h"
#include "component/aes.h"
#include "component/ccl.h"
#include "component/cfg.h"
#include "component/cmcc.h"
#include "component/cru.h"
#include "component/dmac.h"
#include "component/dmt.h"
#include "component/dscon.h"
#include "component/dsu.h"
#include "component/eic.h"
#include "component/evsys.h"
#include "component/fc.h"
#include "component/freqm.h"
#include "component/gpio.h"
#include "component/hmatrixb.h"
#include "component/icm.h"
#include "component/pac.h"
#include "component/pche.h"
#include "component/pfw.h"
#include "component/pmu.h"
#include "component/pps.h"
#include "component/pukcc.h"
#include "component/qspi.h"
#include "component/ramecc.h"
#include "component/rtc.h"
#include "component/sercom.h"
#include "component/tc.h"
#include "component/tcc.h"
#include "component/trng.h"
#include "component/wdt.h"
#include "component/arb.h"
#include "component/ble.h"
#include "component/zigbee.h"
/** @}  end of Peripheral Software API */

/** \addtogroup PIC32CX1012BZ25048_FPGA_id Peripheral Ids Definitions
 *  @{
 */

/* ************************************************************************** */
/*  PERIPHERAL ID DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                     */
/* ************************************************************************** */
#define ID_PAC           (  0) /**< \brief Peripheral Access Controller (PAC) */
#define ID_RTC           (  9) /**< \brief Real-Time Counter (RTC) */
#define ID_EIC           ( 10) /**< \brief External Interrupt Controller (EIC) */
#define ID_FREQM         ( 11) /**< \brief Frequency Meter (FREQM) */
#define ID_SERCOM0       ( 12) /**< \brief Serial Communication Interface (SERCOM0) */
#define ID_SERCOM1       ( 13) /**< \brief Serial Communication Interface (SERCOM1) */
#define ID_TC0           ( 14) /**< \brief Basic Timer Counter (TC0) */
#define ID_TC1           ( 15) /**< \brief Basic Timer Counter (TC1) */
#define ID_DSU           ( 33) /**< \brief Device Service Unit (DSU) */
#define ID_CMCC          ( 35) /**< \brief Cortex M Cache Controller (CMCC) */
#define ID_DMAC          ( 37) /**< \brief Direct Memory Access Controller (DMAC) */
#define ID_HMATRIX       ( 38) /**< \brief HSB Matrix (HMATRIX) */
#define ID_EVSYS         ( 39) /**< \brief Event System Interface (EVSYS) */
#define ID_SERCOM2       ( 41) /**< \brief Serial Communication Interface (SERCOM2) */
#define ID_SERCOM3       ( 42) /**< \brief Serial Communication Interface (SERCOM3) */
#define ID_TCC0          ( 43) /**< \brief Timer Counter Control (TCC0) */
#define ID_TCC1          ( 44) /**< \brief Timer Counter Control (TCC1) */
#define ID_TC2           ( 45) /**< \brief Basic Timer Counter (TC2) */
#define ID_TC3           ( 46) /**< \brief Basic Timer Counter (TC3) */
#define ID_RAMECC        ( 48) /**< \brief RAM ECC (RAMECC) */
#define ID_TCC2          ( 67) /**< \brief Timer Counter Control (TCC2) */
#define ID_AC            ( 72) /**< \brief Analog Comparators (AC) */
#define ID_AES           ( 73) /**< \brief Advanced Encryption Standard (AES) */
#define ID_TRNG          ( 74) /**< \brief True Random Generator (TRNG) */
#define ID_ICM           ( 75) /**< \brief Integrity Check Monitor (ICM) */
#define ID_PUKCC         ( 76) /**< \brief PUblic-Key Cryptography Controller (PUKCC) */
#define ID_QSPI          ( 77) /**< \brief Quad SPI interface (QSPI) */
#define ID_CCL           ( 78) /**< \brief Configurable Custom Logic (CCL) */

#define ID_PERIPH_MAX    ( 78) /**< \brief Number of peripheral IDs */
/** @}  end of Peripheral Ids Definitions */

/** \addtogroup PIC32CX1012BZ25048_FPGA_base Peripheral Base Address Definitions
 *  @{
 */

/* ************************************************************************** */
/*   REGISTER STRUCTURE ADDRESS DEFINITIONS FOR PIC32CX1012BZ25048_FPGA       */
/* ************************************************************************** */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#define AC_REGS                          ((ac_registers_t*)0x42001c00)                 /**< \brief AC Registers Address         */
#define ADC_REGS                         ((adc_registers_t*)0x44001400)                /**< \brief ADC Registers Address        */
#define AES_REGS                         ((aes_registers_t*)0x42000400)                /**< \brief AES Registers Address        */
#define CCL_REGS                         ((ccl_registers_t*)0x42001800)                /**< \brief CCL Registers Address        */
#define CFG_REGS                         ((cfg_registers_t*)0x44000000)                /**< \brief CFG Registers Address        */
#define CMCC_REGS                        ((cmcc_registers_t*)0x41002000)               /**< \brief CMCC Registers Address       */
#define CRU_REGS                         ((cru_registers_t*)0x44000a00)                /**< \brief CRU Registers Address        */
#define DMAC_REGS                        ((dmac_registers_t*)0x41004000)               /**< \brief DMAC Registers Address       */
#define DMT_REGS                         ((dmt_registers_t*)0x44000e00)                /**< \brief DMT Registers Address        */
#define DSCON_REGS                       ((dscon_registers_t*)0x42011000)              /**< \brief DSCON Registers Address      */
#define DSU_REGS                         ((dsu_registers_t*)0x41000000)                /**< \brief DSU Registers Address        */
#define EIC_REGS                         ((eic_registers_t*)0x40000800)                /**< \brief EIC Registers Address        */
#define EVSYS_REGS                       ((evsys_registers_t*)0x41006000)              /**< \brief EVSYS Registers Address      */
#define FC_REGS                          ((fc_registers_t*)0x44000600)                 /**< \brief FC Registers Address         */
#define FREQM_REGS                       ((freqm_registers_t*)0x40000400)              /**< \brief FREQM Registers Address      */
#define GPIOA_REGS                       ((gpio_registers_t*)0x44002200)               /**< \brief GPIOA Registers Address      */
#define GPIOB_REGS                       ((gpio_registers_t*)0x44002300)               /**< \brief GPIOB Registers Address      */
#define HMATRIX_REGS                     ((hmatrixb_registers_t*)0x42002400)           /**< \brief HMATRIX Registers Address    */
#define ICM_REGS                         ((icm_registers_t*)0x42002c00)                /**< \brief ICM Registers Address        */
#define PAC_REGS                         ((pac_registers_t*)0x40000000)                /**< \brief PAC Registers Address        */
#define PCHE_REGS                        ((pche_registers_t*)0x44012400)               /**< \brief PCHE Registers Address       */
#define PFW_REGS                         ((pfw_registers_t*)0x44000800)                /**< \brief PFW Registers Address        */
#define PMU_REGS                         ((pmu_registers_t*)0x44002e00)                /**< \brief PMU Registers Address        */
#define PPS_REGS                         ((pps_registers_t*)0x44001000)                /**< \brief PPS Registers Address        */
#define QSPI_REGS                        ((qspi_registers_t*)0x42000000)               /**< \brief QSPI Registers Address       */
#define RAMECC_REGS                      ((ramecc_registers_t*)0x41008000)             /**< \brief RAMECC Registers Address     */
#define RTC_REGS                         ((rtc_registers_t*)0x42010000)                /**< \brief RTC Registers Address        */
#define SERCOM0_REGS                     ((sercom_registers_t*)0x40000c00)             /**< \brief SERCOM0 Registers Address    */
#define SERCOM1_REGS                     ((sercom_registers_t*)0x40001000)             /**< \brief SERCOM1 Registers Address    */
#define SERCOM2_REGS                     ((sercom_registers_t*)0x42000c00)             /**< \brief SERCOM2 Registers Address    */
#define SERCOM3_REGS                     ((sercom_registers_t*)0x42001000)             /**< \brief SERCOM3 Registers Address    */
#define TC0_REGS                         ((tc_registers_t*)0x40001400)                 /**< \brief TC0 Registers Address        */
#define TC1_REGS                         ((tc_registers_t*)0x40001800)                 /**< \brief TC1 Registers Address        */
#define TC2_REGS                         ((tc_registers_t*)0x40001c00)                 /**< \brief TC2 Registers Address        */
#define TC3_REGS                         ((tc_registers_t*)0x40002000)                 /**< \brief TC3 Registers Address        */
#define TCC0_REGS                        ((tcc_registers_t*)0x40002400)                /**< \brief TCC0 Registers Address       */
#define TCC1_REGS                        ((tcc_registers_t*)0x40002800)                /**< \brief TCC1 Registers Address       */
#define TCC2_REGS                        ((tcc_registers_t*)0x40002c00)                /**< \brief TCC2 Registers Address       */
#define TRNG_REGS                        ((trng_registers_t*)0x42002800)               /**< \brief TRNG Registers Address       */
#define WDT_REGS                         ((wdt_registers_t*)0x44000500)                /**< \brief WDT Registers Address        */
#define BLE_REGS                         ((ble_registers_t*)0x41012000)                /**< \brief BLE Registers Address        */
#define ZIGBEE_REGS                      ((zigbee_registers_t*)0x41010000)             /**< \brief ZIGBEE Registers Address     */
#define ARB_REGS                         ((arb_registers_t*)0x41011000)                /**< \brief ARB Registers Address        */
#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Peripheral Base Address Definitions */

/** \addtogroup PIC32CX1012BZ25048_FPGA_base Peripheral Base Address Definitions
 *  @{
 */

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                     */
/* ************************************************************************** */
#define AC_BASE_ADDRESS                  _UL_(0x42001c00)                              /**< \brief AC Base Address */
#define ADC_BASE_ADDRESS                 _UL_(0x44001400)                              /**< \brief ADC Base Address */
#define AES_BASE_ADDRESS                 _UL_(0x42000400)                              /**< \brief AES Base Address */
#define CCL_BASE_ADDRESS                 _UL_(0x42001800)                              /**< \brief CCL Base Address */
#define CFG_BASE_ADDRESS                 _UL_(0x44000000)                              /**< \brief CFG Base Address */
#define CMCC_BASE_ADDRESS                _UL_(0x41002000)                              /**< \brief CMCC Base Address */
#define CRU_BASE_ADDRESS                 _UL_(0x44000a00)                              /**< \brief CRU Base Address */
#define DMAC_BASE_ADDRESS                _UL_(0x41004000)                              /**< \brief DMAC Base Address */
#define DMT_BASE_ADDRESS                 _UL_(0x44000e00)                              /**< \brief DMT Base Address */
#define DSCON_BASE_ADDRESS               _UL_(0x42011000)                              /**< \brief DSCON Base Address */
#define DSU_BASE_ADDRESS                 _UL_(0x41000000)                              /**< \brief DSU Base Address */
#define EIC_BASE_ADDRESS                 _UL_(0x40000800)                              /**< \brief EIC Base Address */
#define EVSYS_BASE_ADDRESS               _UL_(0x41006000)                              /**< \brief EVSYS Base Address */
#define FC_BASE_ADDRESS                  _UL_(0x44000600)                              /**< \brief FC Base Address */
#define FREQM_BASE_ADDRESS               _UL_(0x40000400)                              /**< \brief FREQM Base Address */
#define GPIOA_BASE_ADDRESS               _UL_(0x44002200)                              /**< \brief GPIOA Base Address */
#define GPIOB_BASE_ADDRESS               _UL_(0x44002300)                              /**< \brief GPIOB Base Address */
#define HMATRIX_BASE_ADDRESS             _UL_(0x42002400)                              /**< \brief HMATRIX Base Address */
#define ICM_BASE_ADDRESS                 _UL_(0x42002c00)                              /**< \brief ICM Base Address */
#define PAC_BASE_ADDRESS                 _UL_(0x40000000)                              /**< \brief PAC Base Address */
#define PCHE_BASE_ADDRESS                _UL_(0x44012400)                              /**< \brief PCHE Base Address */
#define PFW_BASE_ADDRESS                 _UL_(0x44000800)                              /**< \brief PFW Base Address */
#define PMU_BASE_ADDRESS                 _UL_(0x44002e00)                              /**< \brief PMU Base Address */
#define PPS_BASE_ADDRESS                 _UL_(0x44001000)                              /**< \brief PPS Base Address */
#define QSPI_BASE_ADDRESS                _UL_(0x42000000)                              /**< \brief QSPI Base Address */
#define RAMECC_BASE_ADDRESS              _UL_(0x41008000)                              /**< \brief RAMECC Base Address */
#define RTC_BASE_ADDRESS                 _UL_(0x42010000)                              /**< \brief RTC Base Address */
#define SERCOM0_BASE_ADDRESS             _UL_(0x40000c00)                              /**< \brief SERCOM0 Base Address */
#define SERCOM1_BASE_ADDRESS             _UL_(0x40001000)                              /**< \brief SERCOM1 Base Address */
#define SERCOM2_BASE_ADDRESS             _UL_(0x42000c00)                              /**< \brief SERCOM2 Base Address */
#define SERCOM3_BASE_ADDRESS             _UL_(0x42001000)                              /**< \brief SERCOM3 Base Address */
#define TC0_BASE_ADDRESS                 _UL_(0x40001400)                              /**< \brief TC0 Base Address */
#define TC1_BASE_ADDRESS                 _UL_(0x40001800)                              /**< \brief TC1 Base Address */
#define TC2_BASE_ADDRESS                 _UL_(0x40001c00)                              /**< \brief TC2 Base Address */
#define TC3_BASE_ADDRESS                 _UL_(0x40002000)                              /**< \brief TC3 Base Address */
#define TCC0_BASE_ADDRESS                _UL_(0x40002400)                              /**< \brief TCC0 Base Address */
#define TCC1_BASE_ADDRESS                _UL_(0x40002800)                              /**< \brief TCC1 Base Address */
#define TCC2_BASE_ADDRESS                _UL_(0x40002c00)                              /**< \brief TCC2 Base Address */
#define TRNG_BASE_ADDRESS                _UL_(0x42002800)                              /**< \brief TRNG Base Address */
#define WDT_BASE_ADDRESS                 _UL_(0x44000500)                              /**< \brief WDT Base Address */
#define BLE_BASE_ADDRESS                 _UL_(0x41012000)                              /**< \brief BLE Base Address */
#define ZIGBEE_BASE_ADDRESS              _UL_(0x41010000)                              /**< \brief ZIGBEE Base Address */
#define ARB_BASE_ADDRESS                 _UL_(0x41011000)                              /**< \brief ARB Base Address */
/** @}  end of Peripheral Base Address Definitions */

/** \addtogroup PIC32CX1012BZ25048_FPGA_pio Peripheral Pio Definitions
 *  @{
 */

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                              */
/* ************************************************************************** */
#include "pio/pic32cx1012bz25048_fpga.h"
/** @}  end of Peripheral Pio Definitions */

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                   */
/* ************************************************************************** */

#define CMCC_SIZE                      _UL_(0x01000000)    /* 16384kB Memory segment type: io */
#define CMCC_DATARAM_SIZE              _UL_(0x00001000)    /*    4kB Memory segment type: io */
#define CMCC_TAGRAM_SIZE               _UL_(0x00000400)    /*    1kB Memory segment type: io */
#define CMCC_VALIDRAM_SIZE             _UL_(0x00000040)    /*    0kB Memory segment type: io */
#define HSRAM_SIZE                     _UL_(0x00020000)    /*  128kB Memory segment type: ram */
#define HSRAM_ETB_SIZE                 _UL_(0x00008000)    /*   32kB Memory segment type: ram */
#define HSRAM_RET1_SIZE                _UL_(0x00008000)    /*   32kB Memory segment type: ram */
#define HPB0_SIZE                      _UL_(0x00003000)    /*   12kB Memory segment type: io */
#define HPB1_SIZE                      _UL_(0x00015000)    /*   84kB Memory segment type: io */
#define HPB2_SIZE                      _UL_(0x00002400)    /*    9kB Memory segment type: io */
#define HPB3_SIZE                      _UL_(0x00003000)    /*   12kB Memory segment type: io */
#define BKUPRAM_SIZE                   _UL_(0x00002000)    /*    8kB Memory segment type: ram */
#define FLASH_SIZE                     _UL_(0x00100000)    /* 1024kB Memory segment type: flash */
#define FLASH_PAGE_SIZE                _UL_(      4096)
#define FLASH_NB_OF_PAGES              _UL_(       256)

#define PPB_SIZE                       _UL_(0x00100000)    /* 1024kB Memory segment type: io */
#define QSPI_SIZE                      _UL_(0x01000000)    /* 16384kB Memory segment type: other */
#define SCS_SIZE                       _UL_(0x00001000)    /*    4kB Memory segment type: io */
#define BOOT_FLASH_SIZE                _UL_(0x00005000)    /*   20kB Memory segment type: flash */
#define BOOT_FLASH_PAGE_SIZE           _UL_(      4096)
#define BOOT_FLASH_NB_OF_PAGES         _UL_(         5)

#define CFG_FLASH_SIZE                 _UL_(0x00001000)    /*    4kB Memory segment type: flash */
#define CFG_FLASH_PAGE_SIZE            _UL_(      4096)
#define CFG_FLASH_NB_OF_PAGES          _UL_(         1)

#define OTP_FLASH_SIZE                 _UL_(0x00001000)    /*    4kB Memory segment type: flash */
#define OTP_FLASH_PAGE_SIZE            _UL_(      4096)
#define OTP_FLASH_NB_OF_PAGES          _UL_(         1)


#define CMCC_ADDR                      _UL_(0x03000000)    /**< CMCC base address (type: io)*/
#define CMCC_DATARAM_ADDR              _UL_(0x03000000)    /**< CMCC_DATARAM base address (type: io)*/
#define CMCC_TAGRAM_ADDR               _UL_(0x03001000)    /**< CMCC_TAGRAM base address (type: io)*/
#define CMCC_VALIDRAM_ADDR             _UL_(0x03002000)    /**< CMCC_VALIDRAM base address (type: io)*/
#define HSRAM_ADDR                     _UL_(0x20000000)    /**< HSRAM base address (type: ram)*/
#define HSRAM_ETB_ADDR                 _UL_(0x20000000)    /**< HSRAM_ETB base address (type: ram)*/
#define HSRAM_RET1_ADDR                _UL_(0x20000000)    /**< HSRAM_RET1 base address (type: ram)*/
#define HPB0_ADDR                      _UL_(0x40000000)    /**< HPB0 base address (type: io)*/
#define HPB1_ADDR                      _UL_(0x41000000)    /**< HPB1 base address (type: io)*/
#define HPB2_ADDR                      _UL_(0x42000000)    /**< HPB2 base address (type: io)*/
#define HPB3_ADDR                      _UL_(0x44000000)    /**< HPB3 base address (type: io)*/
#define BKUPRAM_ADDR                   _UL_(0x44014000)    /**< BKUPRAM base address (type: ram)*/
#define FLASH_ADDR                     _UL_(0x01000000)    /**< FLASH base address (type: flash)*/
#define PPB_ADDR                       _UL_(0xe0000000)    /**< PPB base address (type: io)*/
#define QSPI_ADDR                      _UL_(0x04000000)    /**< QSPI base address (type: other)*/
#define SCS_ADDR                       _UL_(0xe000e000)    /**< SCS base address (type: io)*/
#define BOOT_FLASH_ADDR                _UL_(0x00000000)    /**< BOOT_FLASH base address (type: flash)*/
#define CFG_FLASH_ADDR                 _UL_(0x00005000)    /**< CFG_FLASH base address (type: flash)*/
#define OTP_FLASH_ADDR                 _UL_(0x00006000)    /**< OTP_FLASH base address (type: flash)*/

/* ************************************************************************** */
/**  DEVICE SIGNATURES FOR PIC32CX1012BZ25048_FPGA                            */
/* ************************************************************************** */
#define CHIP_JTAGID                    _UL_(0X09B8F053)
#define DSU_DID                        _UL_(0X00009B8F)

/* ************************************************************************** */
/**  ELECTRICAL DEFINITIONS FOR PIC32CX1012BZ25048_FPGA                       */
/* ************************************************************************** */

/* ************************************************************************** */
/** Event Generator IDs for C32CX1012BZ25048_FPGA */
/* ************************************************************************** */
#define EVENT_ID_GEN_RTC_PER_0                            0 /**< ID for RTC event generator PER_0 */
#define EVENT_ID_GEN_RTC_PER_1                            1 /**< ID for RTC event generator PER_1 */
#define EVENT_ID_GEN_RTC_PER_2                            2 /**< ID for RTC event generator PER_2 */
#define EVENT_ID_GEN_RTC_PER_3                            3 /**< ID for RTC event generator PER_3 */
#define EVENT_ID_GEN_RTC_PER_4                            4 /**< ID for RTC event generator PER_4 */
#define EVENT_ID_GEN_RTC_PER_5                            5 /**< ID for RTC event generator PER_5 */
#define EVENT_ID_GEN_RTC_PER_6                            6 /**< ID for RTC event generator PER_6 */
#define EVENT_ID_GEN_RTC_PER_7                            7 /**< ID for RTC event generator PER_7 */
#define EVENT_ID_GEN_RTC_CMP_0                            8 /**< ID for RTC event generator CMP_0 */
#define EVENT_ID_GEN_RTC_CMP_1                            9 /**< ID for RTC event generator CMP_1 */
#define EVENT_ID_GEN_RTC_CMP_2                           10 /**< ID for RTC event generator CMP_2 */
#define EVENT_ID_GEN_RTC_CMP_3                           11 /**< ID for RTC event generator CMP_3 */
#define EVENT_ID_GEN_RTC_TAMPER                          12 /**< ID for RTC event generator TAMPER */
#define EVENT_ID_GEN_RTC_OVF                             13 /**< ID for RTC event generator OVF */
#define EVENT_ID_GEN_EIC_EXTINT_0                        14 /**< ID for EIC event generator EXTINT_0 */
#define EVENT_ID_GEN_EIC_EXTINT_1                        15 /**< ID for EIC event generator EXTINT_1 */
#define EVENT_ID_GEN_EIC_EXTINT_2                        16 /**< ID for EIC event generator EXTINT_2 */
#define EVENT_ID_GEN_EIC_EXTINT_3                        17 /**< ID for EIC event generator EXTINT_3 */
#define EVENT_ID_GEN_DMAC_CH_0                           18 /**< ID for DMAC event generator CH_0 */
#define EVENT_ID_GEN_DMAC_CH_1                           19 /**< ID for DMAC event generator CH_1 */
#define EVENT_ID_GEN_DMAC_CH_2                           20 /**< ID for DMAC event generator CH_2 */
#define EVENT_ID_GEN_DMAC_CH_3                           21 /**< ID for DMAC event generator CH_3 */
#define EVENT_ID_GEN_PAC_ACCERR                          22 /**< ID for PAC event generator ACCERR */
#define EVENT_ID_GEN_TCC0_OVF                            23 /**< ID for TCC0 event generator OVF */
#define EVENT_ID_GEN_TCC0_TRG                            24 /**< ID for TCC0 event generator TRG */
#define EVENT_ID_GEN_TCC0_CNT                            25 /**< ID for TCC0 event generator CNT */
#define EVENT_ID_GEN_TCC0_MC_0                           26 /**< ID for TCC0 event generator MC_0 */
#define EVENT_ID_GEN_TCC0_MC_1                           27 /**< ID for TCC0 event generator MC_1 */
#define EVENT_ID_GEN_TCC0_MC_2                           28 /**< ID for TCC0 event generator MC_2 */
#define EVENT_ID_GEN_TCC0_MC_3                           29 /**< ID for TCC0 event generator MC_3 */
#define EVENT_ID_GEN_TCC0_MC_4                           30 /**< ID for TCC0 event generator MC_4 */
#define EVENT_ID_GEN_TCC0_MC_5                           31 /**< ID for TCC0 event generator MC_5 */
#define EVENT_ID_GEN_TCC1_OVF                            32 /**< ID for TCC1 event generator OVF */
#define EVENT_ID_GEN_TCC1_TRG                            33 /**< ID for TCC1 event generator TRG */
#define EVENT_ID_GEN_TCC1_CNT                            34 /**< ID for TCC1 event generator CNT */
#define EVENT_ID_GEN_TCC1_MC_0                           35 /**< ID for TCC1 event generator MC_0 */
#define EVENT_ID_GEN_TCC1_MC_1                           36 /**< ID for TCC1 event generator MC_1 */
#define EVENT_ID_GEN_TCC1_MC_2                           37 /**< ID for TCC1 event generator MC_2 */
#define EVENT_ID_GEN_TCC1_MC_3                           38 /**< ID for TCC1 event generator MC_3 */
#define EVENT_ID_GEN_TCC2_MC_4                           39 /**< ID for TCC2 event generator MC_4 */
#define EVENT_ID_GEN_TCC2_MC_5                           40 /**< ID for TCC2 event generator MC_5 */
#define EVENT_ID_GEN_TCC2_OVF                            41 /**< ID for TCC2 event generator OVF */
#define EVENT_ID_GEN_TCC2_TRG                            42 /**< ID for TCC2 event generator TRG */
#define EVENT_ID_GEN_TCC2_CNT                            43 /**< ID for TCC2 event generator CNT */
#define EVENT_ID_GEN_TCC2_MC_0                           44 /**< ID for TCC2 event generator MC_0 */
#define EVENT_ID_GEN_TCC2_MC_1                           45 /**< ID for TCC2 event generator MC_1 */
#define EVENT_ID_GEN_TC0_OVF                             46 /**< ID for TC0 event generator OVF */
#define EVENT_ID_GEN_TC0_MC_0                            47 /**< ID for TC0 event generator MC_0 */
#define EVENT_ID_GEN_TC0_MC_1                            48 /**< ID for TC0 event generator MC_1 */
#define EVENT_ID_GEN_TC1_OVF                             49 /**< ID for TC1 event generator OVF */
#define EVENT_ID_GEN_TC1_MC_0                            50 /**< ID for TC1 event generator MC_0 */
#define EVENT_ID_GEN_TC1_MC_1                            51 /**< ID for TC1 event generator MC_1 */
#define EVENT_ID_GEN_TC2_OVF                             52 /**< ID for TC2 event generator OVF */
#define EVENT_ID_GEN_TC2_MC_0                            53 /**< ID for TC2 event generator MC_0 */
#define EVENT_ID_GEN_TC2_MC_1                            54 /**< ID for TC2 event generator MC_1 */
#define EVENT_ID_GEN_TC3_OVF                             55 /**< ID for TC3 event generator OVF */
#define EVENT_ID_GEN_TC3_MC_0                            56 /**< ID for TC3 event generator MC_0 */
#define EVENT_ID_GEN_TC3_MC_1                            57 /**< ID for TC3 event generator MC_1 */
#define EVENT_ID_GEN_ADC_RESRDY                          58 /**< ID for ADC event generator RESRDY */
#define EVENT_ID_GEN_AC_COMP_0                           61 /**< ID for AC event generator COMP_0 */
#define EVENT_ID_GEN_AC_COMP_1                           62 /**< ID for AC event generator COMP_1 */
#define EVENT_ID_GEN_AC_WIN_0                            63 /**< ID for AC event generator WIN_0 */
#define EVENT_ID_GEN_TRNG_READY                          64 /**< ID for TRNG event generator READY */
#define EVENT_ID_GEN_CCL_LUTOUT_0                        65 /**< ID for CCL event generator LUTOUT_0 */
#define EVENT_ID_GEN_CCL_LUTOUT_1                        66 /**< ID for CCL event generator LUTOUT_1 */
#define EVENT_ID_GEN_ZB_TX_TS_ACT                        67 /**< ID for ZBT event generator ZB_TX_TS_ACT */
#define EVENT_ID_GEN_ZB_RX_TS_ACT                        68 /**< ID for ZBT event generator ZB_RX_TS_ACT */

/* ************************************************************************** */
/** Event User IDs for C32CX1012BZ25048_FPGA */
/* ************************************************************************** */
#define EVENT_ID_USER_RTC_TAMPER                          0 /**< ID for RTC event user TAMPER */
#define EVENT_ID_USER_DMAC_CH_0                           1 /**< ID for DMAC event user CH_0 */
#define EVENT_ID_USER_DMAC_CH_1                           2 /**< ID for DMAC event user CH_1 */
#define EVENT_ID_USER_DMAC_CH_2                           3 /**< ID for DMAC event user CH_2 */
#define EVENT_ID_USER_DMAC_CH_3                           4 /**< ID for DMAC event user CH_3 */
#define EVENT_ID_USER_DMAC_CH_4                           5 /**< ID for DMAC event user CH_4 */
#define EVENT_ID_USER_DMAC_CH_5                           6 /**< ID for DMAC event user CH_5 */
#define EVENT_ID_USER_DMAC_CH_6                           7 /**< ID for DMAC event user CH_6 */
#define EVENT_ID_USER_DMAC_CH_7                           8 /**< ID for DMAC event user CH_7 */
#define EVENT_ID_USER_CM4_TRACE_START                     9 /**< ID for CM4 event user TRACE_START */
#define EVENT_ID_USER_CM4_TRACE_STOP                     10 /**< ID for CM4 event user TRACE_STOP */
#define EVENT_ID_USER_CM4_TRACE_TRIG                     11 /**< ID for CM4 event user TRACE_TRIG */
#define EVENT_ID_USER_TCC0_EV_0                          12 /**< ID for TCC0 event user EV_0 */
#define EVENT_ID_USER_TCC0_EV_1                          13 /**< ID for TCC0 event user EV_1 */
#define EVENT_ID_USER_TCC0_MC_0                          14 /**< ID for TCC0 event user MC_0 */
#define EVENT_ID_USER_TCC0_MC_1                          15 /**< ID for TCC0 event user MC_1 */
#define EVENT_ID_USER_TCC0_MC_2                          16 /**< ID for TCC0 event user MC_2 */
#define EVENT_ID_USER_TCC0_MC_3                          17 /**< ID for TCC0 event user MC_3 */
#define EVENT_ID_USER_TCC0_MC_4                          18 /**< ID for TCC0 event user MC_4 */
#define EVENT_ID_USER_TCC0_MC_5                          19 /**< ID for TCC0 event user MC_5 */
#define EVENT_ID_USER_TCC1_EV_0                          20 /**< ID for TCC1 event user EV_0 */
#define EVENT_ID_USER_TCC1_EV_1                          21 /**< ID for TCC1 event user EV_1 */
#define EVENT_ID_USER_TCC1_MC_0                          22 /**< ID for TCC1 event user MC_0 */
#define EVENT_ID_USER_TCC1_MC_1                          23 /**< ID for TCC1 event user MC_1 */
#define EVENT_ID_USER_TCC1_MC_2                          24 /**< ID for TCC1 event user MC_2 */
#define EVENT_ID_USER_TCC1_MC_3                          25 /**< ID for TCC1 event user MC_3 */
#define EVENT_ID_USER_TCC1_MC_4                          26 /**< ID for TCC1 event user MC_4 */
#define EVENT_ID_USER_TCC1_MC_5                          27 /**< ID for TCC1 event user MC_5 */
#define EVENT_ID_USER_TCC2_EV_0                          28 /**< ID for TCC2 event user EV_0 */
#define EVENT_ID_USER_TCC2_EV_1                          29 /**< ID for TCC2 event user EV_1 */
#define EVENT_ID_USER_TCC2_MC_0                          30 /**< ID for TCC2 event user MC_0 */
#define EVENT_ID_USER_TCC2_MC_1                          31 /**< ID for TCC2 event user MC_1 */
#define EVENT_ID_USER_TC0_EVU                            32 /**< ID for TC0 event user EVU */
#define EVENT_ID_USER_TC1_EVU                            33 /**< ID for TC1 event user EVU */
#define EVENT_ID_USER_TC2_EVU                            34 /**< ID for TC2 event user EVU */
#define EVENT_ID_USER_TC3_EVU                            35 /**< ID for TC3 event user EVU */
#define EVENT_ID_USER_ADC_TRIG_5                         36 /**< ID for ADC event user TRIG_5 */
#define EVENT_ID_USER_ADC_TRIG_6                         37 /**< ID for ADC event user TRIG_6 */
#define EVENT_ID_USER_ADC_TRIG_7                         38 /**< ID for ADC event user TRIG_7 */
#define EVENT_ID_USER_ADC_TRIG_8                         39 /**< ID for ADC event user TRIG_8 */
#define EVENT_ID_USER_ADC_TRIG_9                         40 /**< ID for ADC event user TRIG_9 */
#define EVENT_ID_USER_ADC_TRIG_10                        41 /**< ID for ADC event user TRIG_10 */
#define EVENT_ID_USER_ADC_TRIG_11                        42 /**< ID for ADC event user TRIG_11 */
#define EVENT_ID_USER_ADC_TRIG_12                        43 /**< ID for ADC event user TRIG_12 */
#define EVENT_ID_USER_ADC_TRIG_13                        44 /**< ID for ADC event user TRIG_13 */
#define EVENT_ID_USER_ADC_TRIG_14                        45 /**< ID for ADC event user TRIG_14 */
#define EVENT_ID_USER_ADC_TRIG_15                        46 /**< ID for ADC event user TRIG_15 */
#define EVENT_ID_USER_ADC_TRIG_16                        47 /**< ID for ADC event user TRIG_16 */
#define EVENT_ID_USER_AC_SOC_0                           48 /**< ID for AC event user SOC_0 */
#define EVENT_ID_USER_AC_SOC_1                           49 /**< ID for AC event user SOC_1 */
#define EVENT_ID_USER_CCL_LUTIN_0                        50 /**< ID for CCL event user LUTIN_0 */
#define EVENT_ID_USER_CCL_LUTIN_1                        51 /**< ID for CCL event user LUTIN_1 */

#ifdef __cplusplus
}
#endif

/** @}  end of PIC32CX1012BZ25048_FPGA definitions */


#endif /* _PIC32CX1012BZ25048_FPGA_H_ */

