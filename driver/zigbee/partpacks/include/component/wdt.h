/**
 * \brief Component description for WDT
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

/* file generated from device description version 2019-09-25T17:04:07Z */
#ifndef _BZ25_WDT_COMPONENT_H_
#define _BZ25_WDT_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR WDT                                          */
/* ************************************************************************** */

/* -------- WDT_WDTCON : (WDT Offset: 0x00) (R/W 32)  -------- */
#define WDT_WDTCON_RESETVALUE                 _U_(0x00)                                            /**<  (WDT_WDTCON)   Reset Value */

#define WDT_WDTCON_WDTWINEN_Pos               _U_(0)                                               /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_WDTWINEN_Msk               (_U_(0x1) << WDT_WDTCON_WDTWINEN_Pos)                /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_WDTWINEN(value)            (WDT_WDTCON_WDTWINEN_Msk & ((value) << WDT_WDTCON_WDTWINEN_Pos))
#define WDT_WDTCON_SLPDIV_Pos                 _U_(1)                                               /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_SLPDIV_Msk                 (_U_(0x1F) << WDT_WDTCON_SLPDIV_Pos)                 /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_SLPDIV(value)              (WDT_WDTCON_SLPDIV_Msk & ((value) << WDT_WDTCON_SLPDIV_Pos))
#define WDT_WDTCON_CLKSEL_Pos                 _U_(6)                                               /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_CLKSEL_Msk                 (_U_(0x3) << WDT_WDTCON_CLKSEL_Pos)                  /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_CLKSEL(value)              (WDT_WDTCON_CLKSEL_Msk & ((value) << WDT_WDTCON_CLKSEL_Pos))
#define WDT_WDTCON_RUNDIV_Pos                 _U_(8)                                               /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_RUNDIV_Msk                 (_U_(0x1F) << WDT_WDTCON_RUNDIV_Pos)                 /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_RUNDIV(value)              (WDT_WDTCON_RUNDIV_Msk & ((value) << WDT_WDTCON_RUNDIV_Pos))
#define WDT_WDTCON_ON_Pos                     _U_(15)                                              /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_ON_Msk                     (_U_(0x1) << WDT_WDTCON_ON_Pos)                      /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_ON(value)                  (WDT_WDTCON_ON_Msk & ((value) << WDT_WDTCON_ON_Pos))
#define WDT_WDTCON_WDTCLRKEY_Pos              _U_(16)                                              /**< (WDT_WDTCON)  Position */
#define WDT_WDTCON_WDTCLRKEY_Msk              (_U_(0xFFFF) << WDT_WDTCON_WDTCLRKEY_Pos)            /**< (WDT_WDTCON)  Mask */
#define WDT_WDTCON_WDTCLRKEY(value)           (WDT_WDTCON_WDTCLRKEY_Msk & ((value) << WDT_WDTCON_WDTCLRKEY_Pos))
#define WDT_WDTCON_Msk                        _U_(0xFFFF9FFF)                                      /**< (WDT_WDTCON) Register Mask  */


/* -------- WDT_WDTCLR : (WDT Offset: 0x04) (R/W 32)  -------- */
#define WDT_WDTCLR_RESETVALUE                 _U_(0x00)                                            /**<  (WDT_WDTCLR)   Reset Value */

#define WDT_WDTCLR_Msk                        _U_(0x00000000)                                      /**< (WDT_WDTCLR) Register Mask  */


/* -------- WDT_WDTSET : (WDT Offset: 0x08) (R/W 32)  -------- */
#define WDT_WDTSET_RESETVALUE                 _U_(0x00)                                            /**<  (WDT_WDTSET)   Reset Value */

#define WDT_WDTSET_Msk                        _U_(0x00000000)                                      /**< (WDT_WDTSET) Register Mask  */


/* -------- WDT_WDTINV : (WDT Offset: 0x0C) (R/W 32)  -------- */
#define WDT_WDTINV_RESETVALUE                 _U_(0x00)                                            /**<  (WDT_WDTINV)   Reset Value */

#define WDT_WDTINV_Msk                        _U_(0x00000000)                                      /**< (WDT_WDTINV) Register Mask  */


/** \brief WDT register offsets definitions */
#define WDT_WDTCON_REG_OFST            (0x00)              /**< (WDT_WDTCON)  Offset */
#define WDT_WDTCLR_REG_OFST            (0x04)              /**< (WDT_WDTCLR)  Offset */
#define WDT_WDTSET_REG_OFST            (0x08)              /**< (WDT_WDTSET)  Offset */
#define WDT_WDTINV_REG_OFST            (0x0C)              /**< (WDT_WDTINV)  Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief WDT register API structure */
typedef struct
{  /* Watch Dog Timer */
  __IO  uint32_t                       WDT_WDTCON;         /**< Offset: 0x00 (R/W  32)  */
  __IO  uint32_t                       WDT_WDTCLR;         /**< Offset: 0x04 (R/W  32)  */
  __IO  uint32_t                       WDT_WDTSET;         /**< Offset: 0x08 (R/W  32)  */
  __IO  uint32_t                       WDT_WDTINV;         /**< Offset: 0x0C (R/W  32)  */
} wdt_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _BZ25_WDT_COMPONENT_H_ */
