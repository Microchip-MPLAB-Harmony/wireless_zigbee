/**
 * \brief Component description for CRU
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
#ifndef _BZ25_CRU_COMPONENT_H_
#define _BZ25_CRU_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR CRU                                          */
/* ************************************************************************** */

/* -------- CRU_OSCCON : (CRU Offset: 0x00) (R/W 32)  -------- */
#define CRU_OSCCON_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_OSCCON)   Reset Value */

#define CRU_OSCCON_OSWEN_Pos                  _U_(0)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_OSWEN_Msk                  (_U_(0x1) << CRU_OSCCON_OSWEN_Pos)                   /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_OSWEN(value)               (CRU_OSCCON_OSWEN_Msk & ((value) << CRU_OSCCON_OSWEN_Pos))
#define CRU_OSCCON_SOSCEN_Pos                 _U_(1)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_SOSCEN_Msk                 (_U_(0x1) << CRU_OSCCON_SOSCEN_Pos)                  /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_SOSCEN(value)              (CRU_OSCCON_SOSCEN_Msk & ((value) << CRU_OSCCON_SOSCEN_Pos))
#define CRU_OSCCON_UFRCEN_Pos                 _U_(2)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_UFRCEN_Msk                 (_U_(0x1) << CRU_OSCCON_UFRCEN_Pos)                  /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_UFRCEN(value)              (CRU_OSCCON_UFRCEN_Msk & ((value) << CRU_OSCCON_UFRCEN_Pos))
#define CRU_OSCCON_CF_Pos                     _U_(3)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_CF_Msk                     (_U_(0x1) << CRU_OSCCON_CF_Pos)                      /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_CF(value)                  (CRU_OSCCON_CF_Msk & ((value) << CRU_OSCCON_CF_Pos))
#define CRU_OSCCON_SLPEN_Pos                  _U_(4)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_SLPEN_Msk                  (_U_(0x1) << CRU_OSCCON_SLPEN_Pos)                   /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_SLPEN(value)               (CRU_OSCCON_SLPEN_Msk & ((value) << CRU_OSCCON_SLPEN_Pos))
#define CRU_OSCCON_CLKLOCK_Pos                _U_(7)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_CLKLOCK_Msk                (_U_(0x1) << CRU_OSCCON_CLKLOCK_Pos)                 /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_CLKLOCK(value)             (CRU_OSCCON_CLKLOCK_Msk & ((value) << CRU_OSCCON_CLKLOCK_Pos))
#define CRU_OSCCON_NOSC_Pos                   _U_(8)                                               /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_NOSC_Msk                   (_U_(0xF) << CRU_OSCCON_NOSC_Pos)                    /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_NOSC(value)                (CRU_OSCCON_NOSC_Msk & ((value) << CRU_OSCCON_NOSC_Pos))
#define CRU_OSCCON_COSC_Pos                   _U_(12)                                              /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_COSC_Msk                   (_U_(0xF) << CRU_OSCCON_COSC_Pos)                    /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_COSC(value)                (CRU_OSCCON_COSC_Msk & ((value) << CRU_OSCCON_COSC_Pos))
#define CRU_OSCCON_WAKE2SPD_Pos               _U_(21)                                              /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_WAKE2SPD_Msk               (_U_(0x1) << CRU_OSCCON_WAKE2SPD_Pos)                /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_WAKE2SPD(value)            (CRU_OSCCON_WAKE2SPD_Msk & ((value) << CRU_OSCCON_WAKE2SPD_Pos))
#define CRU_OSCCON_DRMEN_Pos                  _U_(23)                                              /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_DRMEN_Msk                  (_U_(0x1) << CRU_OSCCON_DRMEN_Pos)                   /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_DRMEN(value)               (CRU_OSCCON_DRMEN_Msk & ((value) << CRU_OSCCON_DRMEN_Pos))
#define CRU_OSCCON_FRCDIV_Pos                 _U_(24)                                              /**< (CRU_OSCCON)  Position */
#define CRU_OSCCON_FRCDIV_Msk                 (_U_(0x7) << CRU_OSCCON_FRCDIV_Pos)                  /**< (CRU_OSCCON)  Mask */
#define CRU_OSCCON_FRCDIV(value)              (CRU_OSCCON_FRCDIV_Msk & ((value) << CRU_OSCCON_FRCDIV_Pos))
#define CRU_OSCCON_Msk                        _U_(0x07A0FF9F)                                      /**< (CRU_OSCCON) Register Mask  */


/* -------- CRU_OSCCONCLR : (CRU Offset: 0x04) (R/W 32)  -------- */
#define CRU_OSCCONCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCCONCLR)   Reset Value */

#define CRU_OSCCONCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCCONCLR) Register Mask  */


/* -------- CRU_OSCCONSET : (CRU Offset: 0x08) (R/W 32)  -------- */
#define CRU_OSCCONSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCCONSET)   Reset Value */

#define CRU_OSCCONSET_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCCONSET) Register Mask  */


/* -------- CRU_OSCCONINV : (CRU Offset: 0x0C) (R/W 32)  -------- */
#define CRU_OSCCONINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCCONINV)   Reset Value */

#define CRU_OSCCONINV_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCCONINV) Register Mask  */


/* -------- CRU_OSCTRM : (CRU Offset: 0x10) (R/W 32)  -------- */
#define CRU_OSCTRM_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_OSCTRM)   Reset Value */

#define CRU_OSCTRM_TUN_Pos                    _U_(0)                                               /**< (CRU_OSCTRM)  Position */
#define CRU_OSCTRM_TUN_Msk                    (_U_(0x3F) << CRU_OSCTRM_TUN_Pos)                    /**< (CRU_OSCTRM)  Mask */
#define CRU_OSCTRM_TUN(value)                 (CRU_OSCTRM_TUN_Msk & ((value) << CRU_OSCTRM_TUN_Pos))
#define CRU_OSCTRM_Msk                        _U_(0x0000003F)                                      /**< (CRU_OSCTRM) Register Mask  */


/* -------- CRU_OSCTRMCLR : (CRU Offset: 0x14) (R/W 32)  -------- */
#define CRU_OSCTRMCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCTRMCLR)   Reset Value */

#define CRU_OSCTRMCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCTRMCLR) Register Mask  */


/* -------- CRU_OSCTRMSET : (CRU Offset: 0x18) (R/W 32)  -------- */
#define CRU_OSCTRMSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCTRMSET)   Reset Value */

#define CRU_OSCTRMSET_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCTRMSET) Register Mask  */


/* -------- CRU_OSCTRMINV : (CRU Offset: 0x1C) (R/W 32)  -------- */
#define CRU_OSCTRMINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCTRMINV)   Reset Value */

#define CRU_OSCTRMINV_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCTRMINV) Register Mask  */


/* -------- CRU_SPLLCON : (CRU Offset: 0x20) (R/W 32)  -------- */
#define CRU_SPLLCON_RESETVALUE                _U_(0x00)                                            /**<  (CRU_SPLLCON)   Reset Value */

#define CRU_SPLLCON_SPLLPWDN_Pos              _U_(3)                                               /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLLPWDN_Msk              (_U_(0x1) << CRU_SPLLCON_SPLLPWDN_Pos)               /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLLPWDN(value)           (CRU_SPLLCON_SPLLPWDN_Msk & ((value) << CRU_SPLLCON_SPLLPWDN_Pos))
#define CRU_SPLLCON_SPLLFLOCK_Pos             _U_(4)                                               /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLLFLOCK_Msk             (_U_(0x1) << CRU_SPLLCON_SPLLFLOCK_Pos)              /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLLFLOCK(value)          (CRU_SPLLCON_SPLLFLOCK_Msk & ((value) << CRU_SPLLCON_SPLLFLOCK_Pos))
#define CRU_SPLLCON_SPLLRST_Pos               _U_(5)                                               /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLLRST_Msk               (_U_(0x1) << CRU_SPLLCON_SPLLRST_Pos)                /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLLRST(value)            (CRU_SPLLCON_SPLLRST_Msk & ((value) << CRU_SPLLCON_SPLLRST_Pos))
#define CRU_SPLLCON_SPLL1POSTDIV_Pos          _U_(8)                                               /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLL1POSTDIV_Msk          (_U_(0xFF) << CRU_SPLLCON_SPLL1POSTDIV_Pos)          /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLL1POSTDIV(value)       (CRU_SPLLCON_SPLL1POSTDIV_Msk & ((value) << CRU_SPLLCON_SPLL1POSTDIV_Pos))
#define CRU_SPLLCON_SPLL2POSTDIV2_Pos         _U_(16)                                              /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLL2POSTDIV2_Msk         (_U_(0xF) << CRU_SPLLCON_SPLL2POSTDIV2_Pos)          /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLL2POSTDIV2(value)      (CRU_SPLLCON_SPLL2POSTDIV2_Msk & ((value) << CRU_SPLLCON_SPLL2POSTDIV2_Pos))
#define CRU_SPLLCON_SPLL_BYP_Pos              _U_(30)                                              /**< (CRU_SPLLCON)  Position */
#define CRU_SPLLCON_SPLL_BYP_Msk              (_U_(0x3) << CRU_SPLLCON_SPLL_BYP_Pos)               /**< (CRU_SPLLCON)  Mask */
#define CRU_SPLLCON_SPLL_BYP(value)           (CRU_SPLLCON_SPLL_BYP_Msk & ((value) << CRU_SPLLCON_SPLL_BYP_Pos))
#define CRU_SPLLCON_Msk                       _U_(0xC00FFF38)                                      /**< (CRU_SPLLCON) Register Mask  */


/* -------- CRU_SPLLCONCLR : (CRU Offset: 0x24) (R/W 32)  -------- */
#define CRU_SPLLCONCLR_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SPLLCONCLR)   Reset Value */

#define CRU_SPLLCONCLR_Msk                    _U_(0x00000000)                                      /**< (CRU_SPLLCONCLR) Register Mask  */


/* -------- CRU_SPLLCONSET : (CRU Offset: 0x28) (R/W 32)  -------- */
#define CRU_SPLLCONSET_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SPLLCONSET)   Reset Value */

#define CRU_SPLLCONSET_Msk                    _U_(0x00000000)                                      /**< (CRU_SPLLCONSET) Register Mask  */


/* -------- CRU_SPLLCONINV : (CRU Offset: 0x2C) (R/W 32)  -------- */
#define CRU_SPLLCONINV_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SPLLCONINV)   Reset Value */

#define CRU_SPLLCONINV_Msk                    _U_(0x00000000)                                      /**< (CRU_SPLLCONINV) Register Mask  */


/* -------- CRU_RCON : (CRU Offset: 0x30) (R/W 32)  -------- */
#define CRU_RCON_RESETVALUE                   _U_(0x00)                                            /**<  (CRU_RCON)   Reset Value */

#define CRU_RCON_POR_Pos                      _U_(0)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_POR_Msk                      (_U_(0x1) << CRU_RCON_POR_Pos)                       /**< (CRU_RCON)  Mask */
#define CRU_RCON_POR(value)                   (CRU_RCON_POR_Msk & ((value) << CRU_RCON_POR_Pos))  
#define CRU_RCON_BOR_Pos                      _U_(1)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_BOR_Msk                      (_U_(0x1) << CRU_RCON_BOR_Pos)                       /**< (CRU_RCON)  Mask */
#define CRU_RCON_BOR(value)                   (CRU_RCON_BOR_Msk & ((value) << CRU_RCON_BOR_Pos))  
#define CRU_RCON_IDLE_Pos                     _U_(2)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_IDLE_Msk                     (_U_(0x1) << CRU_RCON_IDLE_Pos)                      /**< (CRU_RCON)  Mask */
#define CRU_RCON_IDLE(value)                  (CRU_RCON_IDLE_Msk & ((value) << CRU_RCON_IDLE_Pos))
#define CRU_RCON_SLEEP_Pos                    _U_(3)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_SLEEP_Msk                    (_U_(0x1) << CRU_RCON_SLEEP_Pos)                     /**< (CRU_RCON)  Mask */
#define CRU_RCON_SLEEP(value)                 (CRU_RCON_SLEEP_Msk & ((value) << CRU_RCON_SLEEP_Pos))
#define CRU_RCON_WDTO_Pos                     _U_(4)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_WDTO_Msk                     (_U_(0x1) << CRU_RCON_WDTO_Pos)                      /**< (CRU_RCON)  Mask */
#define CRU_RCON_WDTO(value)                  (CRU_RCON_WDTO_Msk & ((value) << CRU_RCON_WDTO_Pos))
#define CRU_RCON_DMTO_Pos                     _U_(5)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_DMTO_Msk                     (_U_(0x1) << CRU_RCON_DMTO_Pos)                      /**< (CRU_RCON)  Mask */
#define CRU_RCON_DMTO(value)                  (CRU_RCON_DMTO_Msk & ((value) << CRU_RCON_DMTO_Pos))
#define CRU_RCON_SWR_Pos                      _U_(6)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_SWR_Msk                      (_U_(0x1) << CRU_RCON_SWR_Pos)                       /**< (CRU_RCON)  Mask */
#define CRU_RCON_SWR(value)                   (CRU_RCON_SWR_Msk & ((value) << CRU_RCON_SWR_Pos))  
#define CRU_RCON_EXTR_Pos                     _U_(7)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_EXTR_Msk                     (_U_(0x1) << CRU_RCON_EXTR_Pos)                      /**< (CRU_RCON)  Mask */
#define CRU_RCON_EXTR(value)                  (CRU_RCON_EXTR_Msk & ((value) << CRU_RCON_EXTR_Pos))
#define CRU_RCON_CMR_Pos                      _U_(9)                                               /**< (CRU_RCON)  Position */
#define CRU_RCON_CMR_Msk                      (_U_(0x1) << CRU_RCON_CMR_Pos)                       /**< (CRU_RCON)  Mask */
#define CRU_RCON_CMR(value)                   (CRU_RCON_CMR_Msk & ((value) << CRU_RCON_CMR_Pos))  
#define CRU_RCON_DPSLP_Pos                    _U_(10)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_DPSLP_Msk                    (_U_(0x1) << CRU_RCON_DPSLP_Pos)                     /**< (CRU_RCON)  Mask */
#define CRU_RCON_DPSLP(value)                 (CRU_RCON_DPSLP_Msk & ((value) << CRU_RCON_DPSLP_Pos))
#define CRU_RCON_NVMOEL_Pos                   _U_(24)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_NVMOEL_Msk                   (_U_(0x1) << CRU_RCON_NVMOEL_Pos)                    /**< (CRU_RCON)  Mask */
#define CRU_RCON_NVMOEL(value)                (CRU_RCON_NVMOEL_Msk & ((value) << CRU_RCON_NVMOEL_Pos))
#define CRU_RCON_NVMLTA_Pos                   _U_(25)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_NVMLTA_Msk                   (_U_(0x1) << CRU_RCON_NVMLTA_Pos)                    /**< (CRU_RCON)  Mask */
#define CRU_RCON_NVMLTA(value)                (CRU_RCON_NVMLTA_Msk & ((value) << CRU_RCON_NVMLTA_Pos))
#define CRU_RCON_BCFGFAIL_Pos                 _U_(26)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_BCFGFAIL_Msk                 (_U_(0x1) << CRU_RCON_BCFGFAIL_Pos)                  /**< (CRU_RCON)  Mask */
#define CRU_RCON_BCFGFAIL(value)              (CRU_RCON_BCFGFAIL_Msk & ((value) << CRU_RCON_BCFGFAIL_Pos))
#define CRU_RCON_BCFGERR_Pos                  _U_(27)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_BCFGERR_Msk                  (_U_(0x1) << CRU_RCON_BCFGERR_Pos)                   /**< (CRU_RCON)  Mask */
#define CRU_RCON_BCFGERR(value)               (CRU_RCON_BCFGERR_Msk & ((value) << CRU_RCON_BCFGERR_Pos))
#define CRU_RCON_PORCORE_Pos                  _U_(30)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_PORCORE_Msk                  (_U_(0x1) << CRU_RCON_PORCORE_Pos)                   /**< (CRU_RCON)  Mask */
#define CRU_RCON_PORCORE(value)               (CRU_RCON_PORCORE_Msk & ((value) << CRU_RCON_PORCORE_Pos))
#define CRU_RCON_PORIO_Pos                    _U_(31)                                              /**< (CRU_RCON)  Position */
#define CRU_RCON_PORIO_Msk                    (_U_(0x1) << CRU_RCON_PORIO_Pos)                     /**< (CRU_RCON)  Mask */
#define CRU_RCON_PORIO(value)                 (CRU_RCON_PORIO_Msk & ((value) << CRU_RCON_PORIO_Pos))
#define CRU_RCON_Msk                          _U_(0xCF0006FF)                                      /**< (CRU_RCON) Register Mask  */


/* -------- CRU_RCONCLR : (CRU Offset: 0x34) (R/W 32)  -------- */
#define CRU_RCONCLR_RESETVALUE                _U_(0x00)                                            /**<  (CRU_RCONCLR)   Reset Value */

#define CRU_RCONCLR_Msk                       _U_(0x00000000)                                      /**< (CRU_RCONCLR) Register Mask  */


/* -------- CRU_RCONSET : (CRU Offset: 0x38) (R/W 32)  -------- */
#define CRU_RCONSET_RESETVALUE                _U_(0x00)                                            /**<  (CRU_RCONSET)   Reset Value */

#define CRU_RCONSET_Msk                       _U_(0x00000000)                                      /**< (CRU_RCONSET) Register Mask  */


/* -------- CRU_RCONINV : (CRU Offset: 0x3C) (R/W 32)  -------- */
#define CRU_RCONINV_RESETVALUE                _U_(0x00)                                            /**<  (CRU_RCONINV)   Reset Value */

#define CRU_RCONINV_Msk                       _U_(0x00000000)                                      /**< (CRU_RCONINV) Register Mask  */


/* -------- CRU_RSWRST : (CRU Offset: 0x40) (R/W 32)  -------- */
#define CRU_RSWRST_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_RSWRST)   Reset Value */

#define CRU_RSWRST_SWRST_Pos                  _U_(0)                                               /**< (CRU_RSWRST)  Position */
#define CRU_RSWRST_SWRST_Msk                  (_U_(0x1) << CRU_RSWRST_SWRST_Pos)                   /**< (CRU_RSWRST)  Mask */
#define CRU_RSWRST_SWRST(value)               (CRU_RSWRST_SWRST_Msk & ((value) << CRU_RSWRST_SWRST_Pos))
#define CRU_RSWRST_Msk                        _U_(0x00000001)                                      /**< (CRU_RSWRST) Register Mask  */


/* -------- CRU_RSWRSTCLR : (CRU Offset: 0x44) (R/W 32)  -------- */
#define CRU_RSWRSTCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_RSWRSTCLR)   Reset Value */

#define CRU_RSWRSTCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_RSWRSTCLR) Register Mask  */


/* -------- CRU_RSWRSTSET : (CRU Offset: 0x48) (R/W 32)  -------- */
#define CRU_RSWRSTSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_RSWRSTSET)   Reset Value */

#define CRU_RSWRSTSET_Msk                     _U_(0x00000000)                                      /**< (CRU_RSWRSTSET) Register Mask  */


/* -------- CRU_RSWRSTINV : (CRU Offset: 0x4C) (R/W 32)  -------- */
#define CRU_RSWRSTINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_RSWRSTINV)   Reset Value */

#define CRU_RSWRSTINV_Msk                     _U_(0x00000000)                                      /**< (CRU_RSWRSTINV) Register Mask  */


/* -------- CRU_RNMICON : (CRU Offset: 0x50) (R/W 32)  -------- */
#define CRU_RNMICON_RESETVALUE                _U_(0x00)                                            /**<  (CRU_RNMICON)   Reset Value */

#define CRU_RNMICON_NMICNT_Pos                _U_(0)                                               /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_NMICNT_Msk                (_U_(0xFFFF) << CRU_RNMICON_NMICNT_Pos)              /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_NMICNT(value)             (CRU_RNMICON_NMICNT_Msk & ((value) << CRU_RNMICON_NMICNT_Pos))
#define CRU_RNMICON_WDTS_Pos                  _U_(16)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_WDTS_Msk                  (_U_(0x1) << CRU_RNMICON_WDTS_Pos)                   /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_WDTS(value)               (CRU_RNMICON_WDTS_Msk & ((value) << CRU_RNMICON_WDTS_Pos))
#define CRU_RNMICON_CF_Pos                    _U_(17)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_CF_Msk                    (_U_(0x1) << CRU_RNMICON_CF_Pos)                     /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_CF(value)                 (CRU_RNMICON_CF_Msk & ((value) << CRU_RNMICON_CF_Pos))
#define CRU_RNMICON_PLVD_Pos                  _U_(18)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_PLVD_Msk                  (_U_(0x1) << CRU_RNMICON_PLVD_Pos)                   /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_PLVD(value)               (CRU_RNMICON_PLVD_Msk & ((value) << CRU_RNMICON_PLVD_Pos))
#define CRU_RNMICON_EXT_Pos                   _U_(19)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_EXT_Msk                   (_U_(0x1) << CRU_RNMICON_EXT_Pos)                    /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_EXT(value)                (CRU_RNMICON_EXT_Msk & ((value) << CRU_RNMICON_EXT_Pos))
#define CRU_RNMICON_SWNMI_Pos                 _U_(23)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_SWNMI_Msk                 (_U_(0x1) << CRU_RNMICON_SWNMI_Pos)                  /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_SWNMI(value)              (CRU_RNMICON_SWNMI_Msk & ((value) << CRU_RNMICON_SWNMI_Pos))
#define CRU_RNMICON_WDTR_Pos                  _U_(24)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_WDTR_Msk                  (_U_(0x1) << CRU_RNMICON_WDTR_Pos)                   /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_WDTR(value)               (CRU_RNMICON_WDTR_Msk & ((value) << CRU_RNMICON_WDTR_Pos))
#define CRU_RNMICON_DMTO_Pos                  _U_(25)                                              /**< (CRU_RNMICON)  Position */
#define CRU_RNMICON_DMTO_Msk                  (_U_(0x1) << CRU_RNMICON_DMTO_Pos)                   /**< (CRU_RNMICON)  Mask */
#define CRU_RNMICON_DMTO(value)               (CRU_RNMICON_DMTO_Msk & ((value) << CRU_RNMICON_DMTO_Pos))
#define CRU_RNMICON_Msk                       _U_(0x038FFFFF)                                      /**< (CRU_RNMICON) Register Mask  */


/* -------- CRU_RNMICONCLR : (CRU Offset: 0x54) (R/W 32)  -------- */
#define CRU_RNMICONCLR_RESETVALUE             _U_(0x00)                                            /**<  (CRU_RNMICONCLR)   Reset Value */

#define CRU_RNMICONCLR_Msk                    _U_(0x00000000)                                      /**< (CRU_RNMICONCLR) Register Mask  */


/* -------- CRU_RNMICONSET : (CRU Offset: 0x58) (R/W 32)  -------- */
#define CRU_RNMICONSET_RESETVALUE             _U_(0x00)                                            /**<  (CRU_RNMICONSET)   Reset Value */

#define CRU_RNMICONSET_Msk                    _U_(0x00000000)                                      /**< (CRU_RNMICONSET) Register Mask  */


/* -------- CRU_RNMICONINV : (CRU Offset: 0x5C) (R/W 32)  -------- */
#define CRU_RNMICONINV_RESETVALUE             _U_(0x00)                                            /**<  (CRU_RNMICONINV)   Reset Value */

#define CRU_RNMICONINV_Msk                    _U_(0x00000000)                                      /**< (CRU_RNMICONINV) Register Mask  */


/* -------- CRU_PWRCON : (CRU Offset: 0x60) (R/W 32)  -------- */
#define CRU_PWRCON_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_PWRCON)   Reset Value */

#define CRU_PWRCON_Msk                        _U_(0x00000000)                                      /**< (CRU_PWRCON) Register Mask  */


/* -------- CRU_REFO1CON : (CRU Offset: 0x70) (R/W 32)  -------- */
#define CRU_REFO1CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO1CON)   Reset Value */

#define CRU_REFO1CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO1CON_ROSEL_Pos)                 /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_ROSEL(value)             (CRU_REFO1CON_ROSEL_Msk & ((value) << CRU_REFO1CON_ROSEL_Pos))
#define CRU_REFO1CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO1CON_ACTIVE_Pos)                /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_ACTIVE(value)            (CRU_REFO1CON_ACTIVE_Msk & ((value) << CRU_REFO1CON_ACTIVE_Pos))
#define CRU_REFO1CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO1CON_DIVSWEN_Pos)               /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_DIVSWEN(value)           (CRU_REFO1CON_DIVSWEN_Msk & ((value) << CRU_REFO1CON_DIVSWEN_Pos))
#define CRU_REFO1CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO1CON_RSLP_Pos)                  /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_RSLP(value)              (CRU_REFO1CON_RSLP_Msk & ((value) << CRU_REFO1CON_RSLP_Pos))
#define CRU_REFO1CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_OE_Msk                   (_U_(0x1) << CRU_REFO1CON_OE_Pos)                    /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_OE(value)                (CRU_REFO1CON_OE_Msk & ((value) << CRU_REFO1CON_OE_Pos))
#define CRU_REFO1CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO1CON_SIDL_Pos)                  /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_SIDL(value)              (CRU_REFO1CON_SIDL_Msk & ((value) << CRU_REFO1CON_SIDL_Pos))
#define CRU_REFO1CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO1CON_FRZ_Pos)                   /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_FRZ(value)               (CRU_REFO1CON_FRZ_Msk & ((value) << CRU_REFO1CON_FRZ_Pos))
#define CRU_REFO1CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_ON_Msk                   (_U_(0x1) << CRU_REFO1CON_ON_Pos)                    /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_ON(value)                (CRU_REFO1CON_ON_Msk & ((value) << CRU_REFO1CON_ON_Pos))
#define CRU_REFO1CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO1CON)  Position */
#define CRU_REFO1CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO1CON_RODIV_Pos)              /**< (CRU_REFO1CON)  Mask */
#define CRU_REFO1CON_RODIV(value)             (CRU_REFO1CON_RODIV_Msk & ((value) << CRU_REFO1CON_RODIV_Pos))
#define CRU_REFO1CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO1CON) Register Mask  */


/* -------- CRU_REFO1CONCLR : (CRU Offset: 0x74) (R/W 32)  -------- */
#define CRU_REFO1CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO1CONCLR)   Reset Value */

#define CRU_REFO1CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO1CONCLR) Register Mask  */


/* -------- CRU_REFO1CONSET : (CRU Offset: 0x78) (R/W 32)  -------- */
#define CRU_REFO1CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO1CONSET)   Reset Value */

#define CRU_REFO1CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO1CONSET) Register Mask  */


/* -------- CRU_REFO1CONINV : (CRU Offset: 0x7C) (R/W 32)  -------- */
#define CRU_REFO1CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO1CONINV)   Reset Value */

#define CRU_REFO1CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO1CONINV) Register Mask  */


/* -------- CRU_REFO1TRIM : (CRU Offset: 0x80) (R/W 32)  -------- */
#define CRU_REFO1TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO1TRIM)   Reset Value */

#define CRU_REFO1TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO1TRIM)  Position */
#define CRU_REFO1TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO1TRIM_ROTRIM_Pos)             /**< (CRU_REFO1TRIM)  Mask */
#define CRU_REFO1TRIM_ROTRIM(value)           (CRU_REFO1TRIM_ROTRIM_Msk & ((value) << CRU_REFO1TRIM_ROTRIM_Pos))
#define CRU_REFO1TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO1TRIM) Register Mask  */


/* -------- CRU_REFO1TRIMCLR : (CRU Offset: 0x84) (R/W 32)  -------- */
#define CRU_REFO1TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO1TRIMCLR)   Reset Value */

#define CRU_REFO1TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO1TRIMCLR) Register Mask  */


/* -------- CRU_REFO1TRIMSET : (CRU Offset: 0x88) (R/W 32)  -------- */
#define CRU_REFO1TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO1TRIMSET)   Reset Value */

#define CRU_REFO1TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO1TRIMSET) Register Mask  */


/* -------- CRU_REFO1TRIMINV : (CRU Offset: 0x8C) (R/W 32)  -------- */
#define CRU_REFO1TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO1TRIMINV)   Reset Value */

#define CRU_REFO1TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO1TRIMINV) Register Mask  */


/* -------- CRU_REFO2CON : (CRU Offset: 0x90) (R/W 32)  -------- */
#define CRU_REFO2CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO2CON)   Reset Value */

#define CRU_REFO2CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO2CON_ROSEL_Pos)                 /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_ROSEL(value)             (CRU_REFO2CON_ROSEL_Msk & ((value) << CRU_REFO2CON_ROSEL_Pos))
#define CRU_REFO2CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO2CON_ACTIVE_Pos)                /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_ACTIVE(value)            (CRU_REFO2CON_ACTIVE_Msk & ((value) << CRU_REFO2CON_ACTIVE_Pos))
#define CRU_REFO2CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO2CON_DIVSWEN_Pos)               /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_DIVSWEN(value)           (CRU_REFO2CON_DIVSWEN_Msk & ((value) << CRU_REFO2CON_DIVSWEN_Pos))
#define CRU_REFO2CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO2CON_RSLP_Pos)                  /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_RSLP(value)              (CRU_REFO2CON_RSLP_Msk & ((value) << CRU_REFO2CON_RSLP_Pos))
#define CRU_REFO2CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_OE_Msk                   (_U_(0x1) << CRU_REFO2CON_OE_Pos)                    /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_OE(value)                (CRU_REFO2CON_OE_Msk & ((value) << CRU_REFO2CON_OE_Pos))
#define CRU_REFO2CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO2CON_SIDL_Pos)                  /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_SIDL(value)              (CRU_REFO2CON_SIDL_Msk & ((value) << CRU_REFO2CON_SIDL_Pos))
#define CRU_REFO2CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO2CON_FRZ_Pos)                   /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_FRZ(value)               (CRU_REFO2CON_FRZ_Msk & ((value) << CRU_REFO2CON_FRZ_Pos))
#define CRU_REFO2CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_ON_Msk                   (_U_(0x1) << CRU_REFO2CON_ON_Pos)                    /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_ON(value)                (CRU_REFO2CON_ON_Msk & ((value) << CRU_REFO2CON_ON_Pos))
#define CRU_REFO2CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO2CON)  Position */
#define CRU_REFO2CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO2CON_RODIV_Pos)              /**< (CRU_REFO2CON)  Mask */
#define CRU_REFO2CON_RODIV(value)             (CRU_REFO2CON_RODIV_Msk & ((value) << CRU_REFO2CON_RODIV_Pos))
#define CRU_REFO2CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO2CON) Register Mask  */


/* -------- CRU_REFO2CONCLR : (CRU Offset: 0x94) (R/W 32)  -------- */
#define CRU_REFO2CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO2CONCLR)   Reset Value */

#define CRU_REFO2CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO2CONCLR) Register Mask  */


/* -------- CRU_REFO2CONSET : (CRU Offset: 0x98) (R/W 32)  -------- */
#define CRU_REFO2CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO2CONSET)   Reset Value */

#define CRU_REFO2CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO2CONSET) Register Mask  */


/* -------- CRU_REFO2CONINV : (CRU Offset: 0x9C) (R/W 32)  -------- */
#define CRU_REFO2CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO2CONINV)   Reset Value */

#define CRU_REFO2CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO2CONINV) Register Mask  */


/* -------- CRU_REFO2TRIM : (CRU Offset: 0xA0) (R/W 32)  -------- */
#define CRU_REFO2TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO2TRIM)   Reset Value */

#define CRU_REFO2TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO2TRIM)  Position */
#define CRU_REFO2TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO2TRIM_ROTRIM_Pos)             /**< (CRU_REFO2TRIM)  Mask */
#define CRU_REFO2TRIM_ROTRIM(value)           (CRU_REFO2TRIM_ROTRIM_Msk & ((value) << CRU_REFO2TRIM_ROTRIM_Pos))
#define CRU_REFO2TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO2TRIM) Register Mask  */


/* -------- CRU_REFO2TRIMCLR : (CRU Offset: 0xA4) (R/W 32)  -------- */
#define CRU_REFO2TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO2TRIMCLR)   Reset Value */

#define CRU_REFO2TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO2TRIMCLR) Register Mask  */


/* -------- CRU_REFO2TRIMSET : (CRU Offset: 0xA8) (R/W 32)  -------- */
#define CRU_REFO2TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO2TRIMSET)   Reset Value */

#define CRU_REFO2TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO2TRIMSET) Register Mask  */


/* -------- CRU_REFO2TRIMINV : (CRU Offset: 0xAC) (R/W 32)  -------- */
#define CRU_REFO2TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO2TRIMINV)   Reset Value */

#define CRU_REFO2TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO2TRIMINV) Register Mask  */


/* -------- CRU_REFO3CON : (CRU Offset: 0xB0) (R/W 32)  -------- */
#define CRU_REFO3CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO3CON)   Reset Value */

#define CRU_REFO3CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO3CON_ROSEL_Pos)                 /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_ROSEL(value)             (CRU_REFO3CON_ROSEL_Msk & ((value) << CRU_REFO3CON_ROSEL_Pos))
#define CRU_REFO3CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO3CON_ACTIVE_Pos)                /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_ACTIVE(value)            (CRU_REFO3CON_ACTIVE_Msk & ((value) << CRU_REFO3CON_ACTIVE_Pos))
#define CRU_REFO3CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO3CON_DIVSWEN_Pos)               /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_DIVSWEN(value)           (CRU_REFO3CON_DIVSWEN_Msk & ((value) << CRU_REFO3CON_DIVSWEN_Pos))
#define CRU_REFO3CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO3CON_RSLP_Pos)                  /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_RSLP(value)              (CRU_REFO3CON_RSLP_Msk & ((value) << CRU_REFO3CON_RSLP_Pos))
#define CRU_REFO3CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_OE_Msk                   (_U_(0x1) << CRU_REFO3CON_OE_Pos)                    /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_OE(value)                (CRU_REFO3CON_OE_Msk & ((value) << CRU_REFO3CON_OE_Pos))
#define CRU_REFO3CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO3CON_SIDL_Pos)                  /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_SIDL(value)              (CRU_REFO3CON_SIDL_Msk & ((value) << CRU_REFO3CON_SIDL_Pos))
#define CRU_REFO3CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO3CON_FRZ_Pos)                   /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_FRZ(value)               (CRU_REFO3CON_FRZ_Msk & ((value) << CRU_REFO3CON_FRZ_Pos))
#define CRU_REFO3CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_ON_Msk                   (_U_(0x1) << CRU_REFO3CON_ON_Pos)                    /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_ON(value)                (CRU_REFO3CON_ON_Msk & ((value) << CRU_REFO3CON_ON_Pos))
#define CRU_REFO3CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO3CON)  Position */
#define CRU_REFO3CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO3CON_RODIV_Pos)              /**< (CRU_REFO3CON)  Mask */
#define CRU_REFO3CON_RODIV(value)             (CRU_REFO3CON_RODIV_Msk & ((value) << CRU_REFO3CON_RODIV_Pos))
#define CRU_REFO3CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO3CON) Register Mask  */


/* -------- CRU_REFO3CONCLR : (CRU Offset: 0xB4) (R/W 32)  -------- */
#define CRU_REFO3CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO3CONCLR)   Reset Value */

#define CRU_REFO3CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO3CONCLR) Register Mask  */


/* -------- CRU_REFO3CONSET : (CRU Offset: 0xB8) (R/W 32)  -------- */
#define CRU_REFO3CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO3CONSET)   Reset Value */

#define CRU_REFO3CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO3CONSET) Register Mask  */


/* -------- CRU_REFO3CONINV : (CRU Offset: 0xBC) (R/W 32)  -------- */
#define CRU_REFO3CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO3CONINV)   Reset Value */

#define CRU_REFO3CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO3CONINV) Register Mask  */


/* -------- CRU_REFO3TRIM : (CRU Offset: 0xC0) (R/W 32)  -------- */
#define CRU_REFO3TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO3TRIM)   Reset Value */

#define CRU_REFO3TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO3TRIM)  Position */
#define CRU_REFO3TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO3TRIM_ROTRIM_Pos)             /**< (CRU_REFO3TRIM)  Mask */
#define CRU_REFO3TRIM_ROTRIM(value)           (CRU_REFO3TRIM_ROTRIM_Msk & ((value) << CRU_REFO3TRIM_ROTRIM_Pos))
#define CRU_REFO3TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO3TRIM) Register Mask  */


/* -------- CRU_REFO3TRIMCLR : (CRU Offset: 0xC4) (R/W 32)  -------- */
#define CRU_REFO3TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO3TRIMCLR)   Reset Value */

#define CRU_REFO3TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO3TRIMCLR) Register Mask  */


/* -------- CRU_REFO3TRIMSET : (CRU Offset: 0xC8) (R/W 32)  -------- */
#define CRU_REFO3TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO3TRIMSET)   Reset Value */

#define CRU_REFO3TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO3TRIMSET) Register Mask  */


/* -------- CRU_REFO3TRIMINV : (CRU Offset: 0xCC) (R/W 32)  -------- */
#define CRU_REFO3TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO3TRIMINV)   Reset Value */

#define CRU_REFO3TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO3TRIMINV) Register Mask  */


/* -------- CRU_REFO4CON : (CRU Offset: 0xD0) (R/W 32)  -------- */
#define CRU_REFO4CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO4CON)   Reset Value */

#define CRU_REFO4CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO4CON_ROSEL_Pos)                 /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_ROSEL(value)             (CRU_REFO4CON_ROSEL_Msk & ((value) << CRU_REFO4CON_ROSEL_Pos))
#define CRU_REFO4CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO4CON_ACTIVE_Pos)                /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_ACTIVE(value)            (CRU_REFO4CON_ACTIVE_Msk & ((value) << CRU_REFO4CON_ACTIVE_Pos))
#define CRU_REFO4CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO4CON_DIVSWEN_Pos)               /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_DIVSWEN(value)           (CRU_REFO4CON_DIVSWEN_Msk & ((value) << CRU_REFO4CON_DIVSWEN_Pos))
#define CRU_REFO4CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO4CON_RSLP_Pos)                  /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_RSLP(value)              (CRU_REFO4CON_RSLP_Msk & ((value) << CRU_REFO4CON_RSLP_Pos))
#define CRU_REFO4CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_OE_Msk                   (_U_(0x1) << CRU_REFO4CON_OE_Pos)                    /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_OE(value)                (CRU_REFO4CON_OE_Msk & ((value) << CRU_REFO4CON_OE_Pos))
#define CRU_REFO4CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO4CON_SIDL_Pos)                  /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_SIDL(value)              (CRU_REFO4CON_SIDL_Msk & ((value) << CRU_REFO4CON_SIDL_Pos))
#define CRU_REFO4CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO4CON_FRZ_Pos)                   /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_FRZ(value)               (CRU_REFO4CON_FRZ_Msk & ((value) << CRU_REFO4CON_FRZ_Pos))
#define CRU_REFO4CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_ON_Msk                   (_U_(0x1) << CRU_REFO4CON_ON_Pos)                    /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_ON(value)                (CRU_REFO4CON_ON_Msk & ((value) << CRU_REFO4CON_ON_Pos))
#define CRU_REFO4CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO4CON)  Position */
#define CRU_REFO4CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO4CON_RODIV_Pos)              /**< (CRU_REFO4CON)  Mask */
#define CRU_REFO4CON_RODIV(value)             (CRU_REFO4CON_RODIV_Msk & ((value) << CRU_REFO4CON_RODIV_Pos))
#define CRU_REFO4CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO4CON) Register Mask  */


/* -------- CRU_REFO4CONCLR : (CRU Offset: 0xD4) (R/W 32)  -------- */
#define CRU_REFO4CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO4CONCLR)   Reset Value */

#define CRU_REFO4CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO4CONCLR) Register Mask  */


/* -------- CRU_REFO4CONSET : (CRU Offset: 0xD8) (R/W 32)  -------- */
#define CRU_REFO4CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO4CONSET)   Reset Value */

#define CRU_REFO4CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO4CONSET) Register Mask  */


/* -------- CRU_REFO4CONINV : (CRU Offset: 0xDC) (R/W 32)  -------- */
#define CRU_REFO4CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO4CONINV)   Reset Value */

#define CRU_REFO4CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO4CONINV) Register Mask  */


/* -------- CRU_REFO4TRIM : (CRU Offset: 0xE0) (R/W 32)  -------- */
#define CRU_REFO4TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO4TRIM)   Reset Value */

#define CRU_REFO4TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO4TRIM)  Position */
#define CRU_REFO4TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO4TRIM_ROTRIM_Pos)             /**< (CRU_REFO4TRIM)  Mask */
#define CRU_REFO4TRIM_ROTRIM(value)           (CRU_REFO4TRIM_ROTRIM_Msk & ((value) << CRU_REFO4TRIM_ROTRIM_Pos))
#define CRU_REFO4TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO4TRIM) Register Mask  */


/* -------- CRU_REFO4TRIMCLR : (CRU Offset: 0xE4) (R/W 32)  -------- */
#define CRU_REFO4TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO4TRIMCLR)   Reset Value */

#define CRU_REFO4TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO4TRIMCLR) Register Mask  */


/* -------- CRU_REFO4TRIMSET : (CRU Offset: 0xE8) (R/W 32)  -------- */
#define CRU_REFO4TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO4TRIMSET)   Reset Value */

#define CRU_REFO4TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO4TRIMSET) Register Mask  */


/* -------- CRU_REFO4TRIMINV : (CRU Offset: 0xEC) (R/W 32)  -------- */
#define CRU_REFO4TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO4TRIMINV)   Reset Value */

#define CRU_REFO4TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO4TRIMINV) Register Mask  */


/* -------- CRU_REFO5CON : (CRU Offset: 0xF0) (R/W 32)  -------- */
#define CRU_REFO5CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO5CON)   Reset Value */

#define CRU_REFO5CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO5CON_ROSEL_Pos)                 /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_ROSEL(value)             (CRU_REFO5CON_ROSEL_Msk & ((value) << CRU_REFO5CON_ROSEL_Pos))
#define CRU_REFO5CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO5CON_ACTIVE_Pos)                /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_ACTIVE(value)            (CRU_REFO5CON_ACTIVE_Msk & ((value) << CRU_REFO5CON_ACTIVE_Pos))
#define CRU_REFO5CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO5CON_DIVSWEN_Pos)               /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_DIVSWEN(value)           (CRU_REFO5CON_DIVSWEN_Msk & ((value) << CRU_REFO5CON_DIVSWEN_Pos))
#define CRU_REFO5CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO5CON_RSLP_Pos)                  /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_RSLP(value)              (CRU_REFO5CON_RSLP_Msk & ((value) << CRU_REFO5CON_RSLP_Pos))
#define CRU_REFO5CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_OE_Msk                   (_U_(0x1) << CRU_REFO5CON_OE_Pos)                    /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_OE(value)                (CRU_REFO5CON_OE_Msk & ((value) << CRU_REFO5CON_OE_Pos))
#define CRU_REFO5CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO5CON_SIDL_Pos)                  /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_SIDL(value)              (CRU_REFO5CON_SIDL_Msk & ((value) << CRU_REFO5CON_SIDL_Pos))
#define CRU_REFO5CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO5CON_FRZ_Pos)                   /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_FRZ(value)               (CRU_REFO5CON_FRZ_Msk & ((value) << CRU_REFO5CON_FRZ_Pos))
#define CRU_REFO5CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_ON_Msk                   (_U_(0x1) << CRU_REFO5CON_ON_Pos)                    /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_ON(value)                (CRU_REFO5CON_ON_Msk & ((value) << CRU_REFO5CON_ON_Pos))
#define CRU_REFO5CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO5CON)  Position */
#define CRU_REFO5CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO5CON_RODIV_Pos)              /**< (CRU_REFO5CON)  Mask */
#define CRU_REFO5CON_RODIV(value)             (CRU_REFO5CON_RODIV_Msk & ((value) << CRU_REFO5CON_RODIV_Pos))
#define CRU_REFO5CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO5CON) Register Mask  */


/* -------- CRU_REFO5CONCLR : (CRU Offset: 0xF4) (R/W 32)  -------- */
#define CRU_REFO5CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO5CONCLR)   Reset Value */

#define CRU_REFO5CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO5CONCLR) Register Mask  */


/* -------- CRU_REFO5CONSET : (CRU Offset: 0xF8) (R/W 32)  -------- */
#define CRU_REFO5CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO5CONSET)   Reset Value */

#define CRU_REFO5CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO5CONSET) Register Mask  */


/* -------- CRU_REFO5CONINV : (CRU Offset: 0xFC) (R/W 32)  -------- */
#define CRU_REFO5CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO5CONINV)   Reset Value */

#define CRU_REFO5CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO5CONINV) Register Mask  */


/* -------- CRU_REFO5TRIM : (CRU Offset: 0x100) (R/W 32)  -------- */
#define CRU_REFO5TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO5TRIM)   Reset Value */

#define CRU_REFO5TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO5TRIM)  Position */
#define CRU_REFO5TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO5TRIM_ROTRIM_Pos)             /**< (CRU_REFO5TRIM)  Mask */
#define CRU_REFO5TRIM_ROTRIM(value)           (CRU_REFO5TRIM_ROTRIM_Msk & ((value) << CRU_REFO5TRIM_ROTRIM_Pos))
#define CRU_REFO5TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO5TRIM) Register Mask  */


/* -------- CRU_REFO5TRIMCLR : (CRU Offset: 0x104) (R/W 32)  -------- */
#define CRU_REFO5TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO5TRIMCLR)   Reset Value */

#define CRU_REFO5TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO5TRIMCLR) Register Mask  */


/* -------- CRU_REFO5TRIMSET : (CRU Offset: 0x108) (R/W 32)  -------- */
#define CRU_REFO5TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO5TRIMSET)   Reset Value */

#define CRU_REFO5TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO5TRIMSET) Register Mask  */


/* -------- CRU_REFO5TRIMINV : (CRU Offset: 0x10C) (R/W 32)  -------- */
#define CRU_REFO5TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO5TRIMINV)   Reset Value */

#define CRU_REFO5TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO5TRIMINV) Register Mask  */


/* -------- CRU_REFO6CON : (CRU Offset: 0x110) (R/W 32)  -------- */
#define CRU_REFO6CON_RESETVALUE               _U_(0x00)                                            /**<  (CRU_REFO6CON)   Reset Value */

#define CRU_REFO6CON_ROSEL_Pos                _U_(0)                                               /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_ROSEL_Msk                (_U_(0xF) << CRU_REFO6CON_ROSEL_Pos)                 /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_ROSEL(value)             (CRU_REFO6CON_ROSEL_Msk & ((value) << CRU_REFO6CON_ROSEL_Pos))
#define CRU_REFO6CON_ACTIVE_Pos               _U_(8)                                               /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_ACTIVE_Msk               (_U_(0x1) << CRU_REFO6CON_ACTIVE_Pos)                /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_ACTIVE(value)            (CRU_REFO6CON_ACTIVE_Msk & ((value) << CRU_REFO6CON_ACTIVE_Pos))
#define CRU_REFO6CON_DIVSWEN_Pos              _U_(9)                                               /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_DIVSWEN_Msk              (_U_(0x1) << CRU_REFO6CON_DIVSWEN_Pos)               /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_DIVSWEN(value)           (CRU_REFO6CON_DIVSWEN_Msk & ((value) << CRU_REFO6CON_DIVSWEN_Pos))
#define CRU_REFO6CON_RSLP_Pos                 _U_(11)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_RSLP_Msk                 (_U_(0x1) << CRU_REFO6CON_RSLP_Pos)                  /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_RSLP(value)              (CRU_REFO6CON_RSLP_Msk & ((value) << CRU_REFO6CON_RSLP_Pos))
#define CRU_REFO6CON_OE_Pos                   _U_(12)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_OE_Msk                   (_U_(0x1) << CRU_REFO6CON_OE_Pos)                    /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_OE(value)                (CRU_REFO6CON_OE_Msk & ((value) << CRU_REFO6CON_OE_Pos))
#define CRU_REFO6CON_SIDL_Pos                 _U_(13)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_SIDL_Msk                 (_U_(0x1) << CRU_REFO6CON_SIDL_Pos)                  /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_SIDL(value)              (CRU_REFO6CON_SIDL_Msk & ((value) << CRU_REFO6CON_SIDL_Pos))
#define CRU_REFO6CON_FRZ_Pos                  _U_(14)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_FRZ_Msk                  (_U_(0x1) << CRU_REFO6CON_FRZ_Pos)                   /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_FRZ(value)               (CRU_REFO6CON_FRZ_Msk & ((value) << CRU_REFO6CON_FRZ_Pos))
#define CRU_REFO6CON_ON_Pos                   _U_(15)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_ON_Msk                   (_U_(0x1) << CRU_REFO6CON_ON_Pos)                    /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_ON(value)                (CRU_REFO6CON_ON_Msk & ((value) << CRU_REFO6CON_ON_Pos))
#define CRU_REFO6CON_RODIV_Pos                _U_(16)                                              /**< (CRU_REFO6CON)  Position */
#define CRU_REFO6CON_RODIV_Msk                (_U_(0x7FFF) << CRU_REFO6CON_RODIV_Pos)              /**< (CRU_REFO6CON)  Mask */
#define CRU_REFO6CON_RODIV(value)             (CRU_REFO6CON_RODIV_Msk & ((value) << CRU_REFO6CON_RODIV_Pos))
#define CRU_REFO6CON_Msk                      _U_(0x7FFFFB0F)                                      /**< (CRU_REFO6CON) Register Mask  */


/* -------- CRU_REFO6CONCLR : (CRU Offset: 0x114) (R/W 32)  -------- */
#define CRU_REFO6CONCLR_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO6CONCLR)   Reset Value */

#define CRU_REFO6CONCLR_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO6CONCLR) Register Mask  */


/* -------- CRU_REFO6CONSET : (CRU Offset: 0x118) (R/W 32)  -------- */
#define CRU_REFO6CONSET_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO6CONSET)   Reset Value */

#define CRU_REFO6CONSET_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO6CONSET) Register Mask  */


/* -------- CRU_REFO6CONINV : (CRU Offset: 0x11C) (R/W 32)  -------- */
#define CRU_REFO6CONINV_RESETVALUE            _U_(0x00)                                            /**<  (CRU_REFO6CONINV)   Reset Value */

#define CRU_REFO6CONINV_Msk                   _U_(0x00000000)                                      /**< (CRU_REFO6CONINV) Register Mask  */


/* -------- CRU_REFO6TRIM : (CRU Offset: 0x120) (R/W 32)  -------- */
#define CRU_REFO6TRIM_RESETVALUE              _U_(0x00)                                            /**<  (CRU_REFO6TRIM)   Reset Value */

#define CRU_REFO6TRIM_ROTRIM_Pos              _U_(23)                                              /**< (CRU_REFO6TRIM)  Position */
#define CRU_REFO6TRIM_ROTRIM_Msk              (_U_(0x1FF) << CRU_REFO6TRIM_ROTRIM_Pos)             /**< (CRU_REFO6TRIM)  Mask */
#define CRU_REFO6TRIM_ROTRIM(value)           (CRU_REFO6TRIM_ROTRIM_Msk & ((value) << CRU_REFO6TRIM_ROTRIM_Pos))
#define CRU_REFO6TRIM_Msk                     _U_(0xFF800000)                                      /**< (CRU_REFO6TRIM) Register Mask  */


/* -------- CRU_REFO6TRIMCLR : (CRU Offset: 0x124) (R/W 32)  -------- */
#define CRU_REFO6TRIMCLR_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO6TRIMCLR)   Reset Value */

#define CRU_REFO6TRIMCLR_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO6TRIMCLR) Register Mask  */


/* -------- CRU_REFO6TRIMSET : (CRU Offset: 0x128) (R/W 32)  -------- */
#define CRU_REFO6TRIMSET_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO6TRIMSET)   Reset Value */

#define CRU_REFO6TRIMSET_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO6TRIMSET) Register Mask  */


/* -------- CRU_REFO6TRIMINV : (CRU Offset: 0x12C) (R/W 32)  -------- */
#define CRU_REFO6TRIMINV_RESETVALUE           _U_(0x00)                                            /**<  (CRU_REFO6TRIMINV)   Reset Value */

#define CRU_REFO6TRIMINV_Msk                  _U_(0x00000000)                                      /**< (CRU_REFO6TRIMINV) Register Mask  */


/* -------- CRU_PB1DIV : (CRU Offset: 0x130) (R/W 32)  -------- */
#define CRU_PB1DIV_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_PB1DIV)   Reset Value */

#define CRU_PB1DIV_PBDIV_Pos                  _U_(0)                                               /**< (CRU_PB1DIV)  Position */
#define CRU_PB1DIV_PBDIV_Msk                  (_U_(0x7F) << CRU_PB1DIV_PBDIV_Pos)                  /**< (CRU_PB1DIV)  Mask */
#define CRU_PB1DIV_PBDIV(value)               (CRU_PB1DIV_PBDIV_Msk & ((value) << CRU_PB1DIV_PBDIV_Pos))
#define CRU_PB1DIV_PBDIVRDY_Pos               _U_(11)                                              /**< (CRU_PB1DIV)  Position */
#define CRU_PB1DIV_PBDIVRDY_Msk               (_U_(0x1) << CRU_PB1DIV_PBDIVRDY_Pos)                /**< (CRU_PB1DIV)  Mask */
#define CRU_PB1DIV_PBDIVRDY(value)            (CRU_PB1DIV_PBDIVRDY_Msk & ((value) << CRU_PB1DIV_PBDIVRDY_Pos))
#define CRU_PB1DIV_ON_Pos                     _U_(15)                                              /**< (CRU_PB1DIV)  Position */
#define CRU_PB1DIV_ON_Msk                     (_U_(0x1) << CRU_PB1DIV_ON_Pos)                      /**< (CRU_PB1DIV)  Mask */
#define CRU_PB1DIV_ON(value)                  (CRU_PB1DIV_ON_Msk & ((value) << CRU_PB1DIV_ON_Pos))
#define CRU_PB1DIV_Msk                        _U_(0x0000887F)                                      /**< (CRU_PB1DIV) Register Mask  */


/* -------- CRU_PB1DIVCLR : (CRU Offset: 0x134) (R/W 32)  -------- */
#define CRU_PB1DIVCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB1DIVCLR)   Reset Value */

#define CRU_PB1DIVCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_PB1DIVCLR) Register Mask  */


/* -------- CRU_PB1DIVSET : (CRU Offset: 0x138) (R/W 32)  -------- */
#define CRU_PB1DIVSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB1DIVSET)   Reset Value */

#define CRU_PB1DIVSET_Msk                     _U_(0x00000000)                                      /**< (CRU_PB1DIVSET) Register Mask  */


/* -------- CRU_PB1DIVINV : (CRU Offset: 0x13C) (R/W 32)  -------- */
#define CRU_PB1DIVINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB1DIVINV)   Reset Value */

#define CRU_PB1DIVINV_Msk                     _U_(0x00000000)                                      /**< (CRU_PB1DIVINV) Register Mask  */


/* -------- CRU_PB2DIV : (CRU Offset: 0x140) (R/W 32)  -------- */
#define CRU_PB2DIV_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_PB2DIV)   Reset Value */

#define CRU_PB2DIV_PBDIV_Pos                  _U_(0)                                               /**< (CRU_PB2DIV)  Position */
#define CRU_PB2DIV_PBDIV_Msk                  (_U_(0x7F) << CRU_PB2DIV_PBDIV_Pos)                  /**< (CRU_PB2DIV)  Mask */
#define CRU_PB2DIV_PBDIV(value)               (CRU_PB2DIV_PBDIV_Msk & ((value) << CRU_PB2DIV_PBDIV_Pos))
#define CRU_PB2DIV_PBDIVRDY_Pos               _U_(11)                                              /**< (CRU_PB2DIV)  Position */
#define CRU_PB2DIV_PBDIVRDY_Msk               (_U_(0x1) << CRU_PB2DIV_PBDIVRDY_Pos)                /**< (CRU_PB2DIV)  Mask */
#define CRU_PB2DIV_PBDIVRDY(value)            (CRU_PB2DIV_PBDIVRDY_Msk & ((value) << CRU_PB2DIV_PBDIVRDY_Pos))
#define CRU_PB2DIV_ON_Pos                     _U_(15)                                              /**< (CRU_PB2DIV)  Position */
#define CRU_PB2DIV_ON_Msk                     (_U_(0x1) << CRU_PB2DIV_ON_Pos)                      /**< (CRU_PB2DIV)  Mask */
#define CRU_PB2DIV_ON(value)                  (CRU_PB2DIV_ON_Msk & ((value) << CRU_PB2DIV_ON_Pos))
#define CRU_PB2DIV_Msk                        _U_(0x0000887F)                                      /**< (CRU_PB2DIV) Register Mask  */


/* -------- CRU_PB2DIVCLR : (CRU Offset: 0x144) (R/W 32)  -------- */
#define CRU_PB2DIVCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB2DIVCLR)   Reset Value */

#define CRU_PB2DIVCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_PB2DIVCLR) Register Mask  */


/* -------- CRU_PB2DIVSET : (CRU Offset: 0x148) (R/W 32)  -------- */
#define CRU_PB2DIVSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB2DIVSET)   Reset Value */

#define CRU_PB2DIVSET_Msk                     _U_(0x00000000)                                      /**< (CRU_PB2DIVSET) Register Mask  */


/* -------- CRU_PB2DIVINV : (CRU Offset: 0x14C) (R/W 32)  -------- */
#define CRU_PB2DIVINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB2DIVINV)   Reset Value */

#define CRU_PB2DIVINV_Msk                     _U_(0x00000000)                                      /**< (CRU_PB2DIVINV) Register Mask  */


/* -------- CRU_PB3DIV : (CRU Offset: 0x150) (R/W 32)  -------- */
#define CRU_PB3DIV_RESETVALUE                 _U_(0x00)                                            /**<  (CRU_PB3DIV)   Reset Value */

#define CRU_PB3DIV_PBDIV_Pos                  _U_(0)                                               /**< (CRU_PB3DIV)  Position */
#define CRU_PB3DIV_PBDIV_Msk                  (_U_(0x7F) << CRU_PB3DIV_PBDIV_Pos)                  /**< (CRU_PB3DIV)  Mask */
#define CRU_PB3DIV_PBDIV(value)               (CRU_PB3DIV_PBDIV_Msk & ((value) << CRU_PB3DIV_PBDIV_Pos))
#define CRU_PB3DIV_PBDIVRDY_Pos               _U_(11)                                              /**< (CRU_PB3DIV)  Position */
#define CRU_PB3DIV_PBDIVRDY_Msk               (_U_(0x1) << CRU_PB3DIV_PBDIVRDY_Pos)                /**< (CRU_PB3DIV)  Mask */
#define CRU_PB3DIV_PBDIVRDY(value)            (CRU_PB3DIV_PBDIVRDY_Msk & ((value) << CRU_PB3DIV_PBDIVRDY_Pos))
#define CRU_PB3DIV_ON_Pos                     _U_(15)                                              /**< (CRU_PB3DIV)  Position */
#define CRU_PB3DIV_ON_Msk                     (_U_(0x1) << CRU_PB3DIV_ON_Pos)                      /**< (CRU_PB3DIV)  Mask */
#define CRU_PB3DIV_ON(value)                  (CRU_PB3DIV_ON_Msk & ((value) << CRU_PB3DIV_ON_Pos))
#define CRU_PB3DIV_Msk                        _U_(0x0000887F)                                      /**< (CRU_PB3DIV) Register Mask  */


/* -------- CRU_PB3DIVCLR : (CRU Offset: 0x154) (R/W 32)  -------- */
#define CRU_PB3DIVCLR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB3DIVCLR)   Reset Value */

#define CRU_PB3DIVCLR_Msk                     _U_(0x00000000)                                      /**< (CRU_PB3DIVCLR) Register Mask  */


/* -------- CRU_PB3DIVSET : (CRU Offset: 0x158) (R/W 32)  -------- */
#define CRU_PB3DIVSET_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB3DIVSET)   Reset Value */

#define CRU_PB3DIVSET_Msk                     _U_(0x00000000)                                      /**< (CRU_PB3DIVSET) Register Mask  */


/* -------- CRU_PB3DIVINV : (CRU Offset: 0x15C) (R/W 32)  -------- */
#define CRU_PB3DIVINV_RESETVALUE              _U_(0x00)                                            /**<  (CRU_PB3DIVINV)   Reset Value */

#define CRU_PB3DIVINV_Msk                     _U_(0x00000000)                                      /**< (CRU_PB3DIVINV) Register Mask  */


/* -------- CRU_SLEWCON : (CRU Offset: 0x160) (R/W 32)  -------- */
#define CRU_SLEWCON_RESETVALUE                _U_(0x00)                                            /**<  (CRU_SLEWCON)   Reset Value */

#define CRU_SLEWCON_BUSY_Pos                  _U_(0)                                               /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_BUSY_Msk                  (_U_(0x1) << CRU_SLEWCON_BUSY_Pos)                   /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_BUSY(value)               (CRU_SLEWCON_BUSY_Msk & ((value) << CRU_SLEWCON_BUSY_Pos))
#define CRU_SLEWCON_DNEN_Pos                  _U_(1)                                               /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_DNEN_Msk                  (_U_(0x1) << CRU_SLEWCON_DNEN_Pos)                   /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_DNEN(value)               (CRU_SLEWCON_DNEN_Msk & ((value) << CRU_SLEWCON_DNEN_Pos))
#define CRU_SLEWCON_UPEN_Pos                  _U_(2)                                               /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_UPEN_Msk                  (_U_(0x1) << CRU_SLEWCON_UPEN_Pos)                   /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_UPEN(value)               (CRU_SLEWCON_UPEN_Msk & ((value) << CRU_SLEWCON_UPEN_Pos))
#define CRU_SLEWCON_SLWDIV_Pos                _U_(8)                                               /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_SLWDIV_Msk                (_U_(0x7) << CRU_SLEWCON_SLWDIV_Pos)                 /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_SLWDIV(value)             (CRU_SLEWCON_SLWDIV_Msk & ((value) << CRU_SLEWCON_SLWDIV_Pos))
#define CRU_SLEWCON_SYSDIV_Pos                _U_(16)                                              /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_SYSDIV_Msk                (_U_(0xF) << CRU_SLEWCON_SYSDIV_Pos)                 /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_SYSDIV(value)             (CRU_SLEWCON_SYSDIV_Msk & ((value) << CRU_SLEWCON_SYSDIV_Pos))
#define CRU_SLEWCON_SLWDELAY_Pos              _U_(24)                                              /**< (CRU_SLEWCON)  Position */
#define CRU_SLEWCON_SLWDELAY_Msk              (_U_(0xF) << CRU_SLEWCON_SLWDELAY_Pos)               /**< (CRU_SLEWCON)  Mask */
#define CRU_SLEWCON_SLWDELAY(value)           (CRU_SLEWCON_SLWDELAY_Msk & ((value) << CRU_SLEWCON_SLWDELAY_Pos))
#define CRU_SLEWCON_Msk                       _U_(0x0F0F0707)                                      /**< (CRU_SLEWCON) Register Mask  */


/* -------- CRU_SLEWCONCLR : (CRU Offset: 0x164) (R/W 32)  -------- */
#define CRU_SLEWCONCLR_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SLEWCONCLR)   Reset Value */

#define CRU_SLEWCONCLR_Msk                    _U_(0x00000000)                                      /**< (CRU_SLEWCONCLR) Register Mask  */


/* -------- CRU_SLEWCONSET : (CRU Offset: 0x168) (R/W 32)  -------- */
#define CRU_SLEWCONSET_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SLEWCONSET)   Reset Value */

#define CRU_SLEWCONSET_Msk                    _U_(0x00000000)                                      /**< (CRU_SLEWCONSET) Register Mask  */


/* -------- CRU_SLEWCONINV : (CRU Offset: 0x16C) (R/W 32)  -------- */
#define CRU_SLEWCONINV_RESETVALUE             _U_(0x00)                                            /**<  (CRU_SLEWCONINV)   Reset Value */

#define CRU_SLEWCONINV_Msk                    _U_(0x00000000)                                      /**< (CRU_SLEWCONINV) Register Mask  */


/* -------- CRU_CLKSTAT : (CRU Offset: 0x170) (R/W 32)  -------- */
#define CRU_CLKSTAT_RESETVALUE                _U_(0x00)                                            /**<  (CRU_CLKSTAT)   Reset Value */

#define CRU_CLKSTAT_FRCRDY_Pos                _U_(0)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_FRCRDY_Msk                (_U_(0x1) << CRU_CLKSTAT_FRCRDY_Pos)                 /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_FRCRDY(value)             (CRU_CLKSTAT_FRCRDY_Msk & ((value) << CRU_CLKSTAT_FRCRDY_Pos))
#define CRU_CLKSTAT_SPLL1RDY_Pos              _U_(1)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_SPLL1RDY_Msk              (_U_(0x1) << CRU_CLKSTAT_SPLL1RDY_Pos)               /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_SPLL1RDY(value)           (CRU_CLKSTAT_SPLL1RDY_Msk & ((value) << CRU_CLKSTAT_SPLL1RDY_Pos))
#define CRU_CLKSTAT_POSCRDY_Pos               _U_(2)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_POSCRDY_Msk               (_U_(0x1) << CRU_CLKSTAT_POSCRDY_Pos)                /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_POSCRDY(value)            (CRU_CLKSTAT_POSCRDY_Msk & ((value) << CRU_CLKSTAT_POSCRDY_Pos))
#define CRU_CLKSTAT_SOSCRDY_Pos               _U_(3)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_SOSCRDY_Msk               (_U_(0x1) << CRU_CLKSTAT_SOSCRDY_Pos)                /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_SOSCRDY(value)            (CRU_CLKSTAT_SOSCRDY_Msk & ((value) << CRU_CLKSTAT_SOSCRDY_Pos))
#define CRU_CLKSTAT_LPRCRDY_Pos               _U_(4)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_LPRCRDY_Msk               (_U_(0x1) << CRU_CLKSTAT_LPRCRDY_Pos)                /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_LPRCRDY(value)            (CRU_CLKSTAT_LPRCRDY_Msk & ((value) << CRU_CLKSTAT_LPRCRDY_Pos))
#define CRU_CLKSTAT_SPLL3RDY_Pos              _U_(6)                                               /**< (CRU_CLKSTAT)  Position */
#define CRU_CLKSTAT_SPLL3RDY_Msk              (_U_(0x1) << CRU_CLKSTAT_SPLL3RDY_Pos)               /**< (CRU_CLKSTAT)  Mask */
#define CRU_CLKSTAT_SPLL3RDY(value)           (CRU_CLKSTAT_SPLL3RDY_Msk & ((value) << CRU_CLKSTAT_SPLL3RDY_Pos))
#define CRU_CLKSTAT_Msk                       _U_(0x0000005F)                                      /**< (CRU_CLKSTAT) Register Mask  */


/* -------- CRU_OSCCONBAR : (CRU Offset: 0x180) (R/W 32)  -------- */
#define CRU_OSCCONBAR_RESETVALUE              _U_(0x00)                                            /**<  (CRU_OSCCONBAR)   Reset Value */

#define CRU_OSCCONBAR_Msk                     _U_(0x00000000)                                      /**< (CRU_OSCCONBAR) Register Mask  */


/* -------- CRU_CLKDIAG : (CRU Offset: 0x190) (R/W 32)  -------- */
#define CRU_CLKDIAG_RESETVALUE                _U_(0x00)                                            /**<  (CRU_CLKDIAG)   Reset Value */

#define CRU_CLKDIAG_POSC_STOP_Pos             _U_(0)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_POSC_STOP_Msk             (_U_(0x1) << CRU_CLKDIAG_POSC_STOP_Pos)              /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_POSC_STOP(value)          (CRU_CLKDIAG_POSC_STOP_Msk & ((value) << CRU_CLKDIAG_POSC_STOP_Pos))
#define CRU_CLKDIAG_SOSC_STOP_Pos             _U_(1)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_SOSC_STOP_Msk             (_U_(0x1) << CRU_CLKDIAG_SOSC_STOP_Pos)              /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_SOSC_STOP(value)          (CRU_CLKDIAG_SOSC_STOP_Msk & ((value) << CRU_CLKDIAG_SOSC_STOP_Pos))
#define CRU_CLKDIAG_FRC_STOP_Pos              _U_(2)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_FRC_STOP_Msk              (_U_(0x1) << CRU_CLKDIAG_FRC_STOP_Pos)               /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_FRC_STOP(value)           (CRU_CLKDIAG_FRC_STOP_Msk & ((value) << CRU_CLKDIAG_FRC_STOP_Pos))
#define CRU_CLKDIAG_LPRC_STOP_Pos             _U_(3)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_LPRC_STOP_Msk             (_U_(0x1) << CRU_CLKDIAG_LPRC_STOP_Pos)              /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_LPRC_STOP(value)          (CRU_CLKDIAG_LPRC_STOP_Msk & ((value) << CRU_CLKDIAG_LPRC_STOP_Pos))
#define CRU_CLKDIAG_SPLL1_STOP_Pos            _U_(4)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_SPLL1_STOP_Msk            (_U_(0x1) << CRU_CLKDIAG_SPLL1_STOP_Pos)             /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_SPLL1_STOP(value)         (CRU_CLKDIAG_SPLL1_STOP_Msk & ((value) << CRU_CLKDIAG_SPLL1_STOP_Pos))
#define CRU_CLKDIAG_SPLL2_STOP_Pos            _U_(5)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_SPLL2_STOP_Msk            (_U_(0x1) << CRU_CLKDIAG_SPLL2_STOP_Pos)             /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_SPLL2_STOP(value)         (CRU_CLKDIAG_SPLL2_STOP_Msk & ((value) << CRU_CLKDIAG_SPLL2_STOP_Pos))
#define CRU_CLKDIAG_SPLL3_STOP_Pos            _U_(6)                                               /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_SPLL3_STOP_Msk            (_U_(0x1) << CRU_CLKDIAG_SPLL3_STOP_Pos)             /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_SPLL3_STOP(value)         (CRU_CLKDIAG_SPLL3_STOP_Msk & ((value) << CRU_CLKDIAG_SPLL3_STOP_Pos))
#define CRU_CLKDIAG_NMICTR_Pos                _U_(16)                                              /**< (CRU_CLKDIAG)  Position */
#define CRU_CLKDIAG_NMICTR_Msk                (_U_(0xFFFF) << CRU_CLKDIAG_NMICTR_Pos)              /**< (CRU_CLKDIAG)  Mask */
#define CRU_CLKDIAG_NMICTR(value)             (CRU_CLKDIAG_NMICTR_Msk & ((value) << CRU_CLKDIAG_NMICTR_Pos))
#define CRU_CLKDIAG_Msk                       _U_(0xFFFF007F)                                      /**< (CRU_CLKDIAG) Register Mask  */


/* -------- CRU_CLKDIAGCLR : (CRU Offset: 0x194) (R/W 32)  -------- */
#define CRU_CLKDIAGCLR_RESETVALUE             _U_(0x00)                                            /**<  (CRU_CLKDIAGCLR)   Reset Value */

#define CRU_CLKDIAGCLR_Msk                    _U_(0x00000000)                                      /**< (CRU_CLKDIAGCLR) Register Mask  */


/* -------- CRU_CLKDIAGSET : (CRU Offset: 0x198) (R/W 32)  -------- */
#define CRU_CLKDIAGSET_RESETVALUE             _U_(0x00)                                            /**<  (CRU_CLKDIAGSET)   Reset Value */

#define CRU_CLKDIAGSET_Msk                    _U_(0x00000000)                                      /**< (CRU_CLKDIAGSET) Register Mask  */


/* -------- CRU_CLKDIAGINV : (CRU Offset: 0x19C) (R/W 32)  -------- */
#define CRU_CLKDIAGINV_RESETVALUE             _U_(0x00)                                            /**<  (CRU_CLKDIAGINV)   Reset Value */

#define CRU_CLKDIAGINV_Msk                    _U_(0x00000000)                                      /**< (CRU_CLKDIAGINV) Register Mask  */


/** \brief CRU register offsets definitions */
#define CRU_OSCCON_REG_OFST            (0x00)              /**< (CRU_OSCCON)  Offset */
#define CRU_OSCCONCLR_REG_OFST         (0x04)              /**< (CRU_OSCCONCLR)  Offset */
#define CRU_OSCCONSET_REG_OFST         (0x08)              /**< (CRU_OSCCONSET)  Offset */
#define CRU_OSCCONINV_REG_OFST         (0x0C)              /**< (CRU_OSCCONINV)  Offset */
#define CRU_OSCTRM_REG_OFST            (0x10)              /**< (CRU_OSCTRM)  Offset */
#define CRU_OSCTRMCLR_REG_OFST         (0x14)              /**< (CRU_OSCTRMCLR)  Offset */
#define CRU_OSCTRMSET_REG_OFST         (0x18)              /**< (CRU_OSCTRMSET)  Offset */
#define CRU_OSCTRMINV_REG_OFST         (0x1C)              /**< (CRU_OSCTRMINV)  Offset */
#define CRU_SPLLCON_REG_OFST           (0x20)              /**< (CRU_SPLLCON)  Offset */
#define CRU_SPLLCONCLR_REG_OFST        (0x24)              /**< (CRU_SPLLCONCLR)  Offset */
#define CRU_SPLLCONSET_REG_OFST        (0x28)              /**< (CRU_SPLLCONSET)  Offset */
#define CRU_SPLLCONINV_REG_OFST        (0x2C)              /**< (CRU_SPLLCONINV)  Offset */
#define CRU_RCON_REG_OFST              (0x30)              /**< (CRU_RCON)  Offset */
#define CRU_RCONCLR_REG_OFST           (0x34)              /**< (CRU_RCONCLR)  Offset */
#define CRU_RCONSET_REG_OFST           (0x38)              /**< (CRU_RCONSET)  Offset */
#define CRU_RCONINV_REG_OFST           (0x3C)              /**< (CRU_RCONINV)  Offset */
#define CRU_RSWRST_REG_OFST            (0x40)              /**< (CRU_RSWRST)  Offset */
#define CRU_RSWRSTCLR_REG_OFST         (0x44)              /**< (CRU_RSWRSTCLR)  Offset */
#define CRU_RSWRSTSET_REG_OFST         (0x48)              /**< (CRU_RSWRSTSET)  Offset */
#define CRU_RSWRSTINV_REG_OFST         (0x4C)              /**< (CRU_RSWRSTINV)  Offset */
#define CRU_RNMICON_REG_OFST           (0x50)              /**< (CRU_RNMICON)  Offset */
#define CRU_RNMICONCLR_REG_OFST        (0x54)              /**< (CRU_RNMICONCLR)  Offset */
#define CRU_RNMICONSET_REG_OFST        (0x58)              /**< (CRU_RNMICONSET)  Offset */
#define CRU_RNMICONINV_REG_OFST        (0x5C)              /**< (CRU_RNMICONINV)  Offset */
#define CRU_PWRCON_REG_OFST            (0x60)              /**< (CRU_PWRCON)  Offset */
#define CRU_REFO1CON_REG_OFST          (0x70)              /**< (CRU_REFO1CON)  Offset */
#define CRU_REFO1CONCLR_REG_OFST       (0x74)              /**< (CRU_REFO1CONCLR)  Offset */
#define CRU_REFO1CONSET_REG_OFST       (0x78)              /**< (CRU_REFO1CONSET)  Offset */
#define CRU_REFO1CONINV_REG_OFST       (0x7C)              /**< (CRU_REFO1CONINV)  Offset */
#define CRU_REFO1TRIM_REG_OFST         (0x80)              /**< (CRU_REFO1TRIM)  Offset */
#define CRU_REFO1TRIMCLR_REG_OFST      (0x84)              /**< (CRU_REFO1TRIMCLR)  Offset */
#define CRU_REFO1TRIMSET_REG_OFST      (0x88)              /**< (CRU_REFO1TRIMSET)  Offset */
#define CRU_REFO1TRIMINV_REG_OFST      (0x8C)              /**< (CRU_REFO1TRIMINV)  Offset */
#define CRU_REFO2CON_REG_OFST          (0x90)              /**< (CRU_REFO2CON)  Offset */
#define CRU_REFO2CONCLR_REG_OFST       (0x94)              /**< (CRU_REFO2CONCLR)  Offset */
#define CRU_REFO2CONSET_REG_OFST       (0x98)              /**< (CRU_REFO2CONSET)  Offset */
#define CRU_REFO2CONINV_REG_OFST       (0x9C)              /**< (CRU_REFO2CONINV)  Offset */
#define CRU_REFO2TRIM_REG_OFST         (0xA0)              /**< (CRU_REFO2TRIM)  Offset */
#define CRU_REFO2TRIMCLR_REG_OFST      (0xA4)              /**< (CRU_REFO2TRIMCLR)  Offset */
#define CRU_REFO2TRIMSET_REG_OFST      (0xA8)              /**< (CRU_REFO2TRIMSET)  Offset */
#define CRU_REFO2TRIMINV_REG_OFST      (0xAC)              /**< (CRU_REFO2TRIMINV)  Offset */
#define CRU_REFO3CON_REG_OFST          (0xB0)              /**< (CRU_REFO3CON)  Offset */
#define CRU_REFO3CONCLR_REG_OFST       (0xB4)              /**< (CRU_REFO3CONCLR)  Offset */
#define CRU_REFO3CONSET_REG_OFST       (0xB8)              /**< (CRU_REFO3CONSET)  Offset */
#define CRU_REFO3CONINV_REG_OFST       (0xBC)              /**< (CRU_REFO3CONINV)  Offset */
#define CRU_REFO3TRIM_REG_OFST         (0xC0)              /**< (CRU_REFO3TRIM)  Offset */
#define CRU_REFO3TRIMCLR_REG_OFST      (0xC4)              /**< (CRU_REFO3TRIMCLR)  Offset */
#define CRU_REFO3TRIMSET_REG_OFST      (0xC8)              /**< (CRU_REFO3TRIMSET)  Offset */
#define CRU_REFO3TRIMINV_REG_OFST      (0xCC)              /**< (CRU_REFO3TRIMINV)  Offset */
#define CRU_REFO4CON_REG_OFST          (0xD0)              /**< (CRU_REFO4CON)  Offset */
#define CRU_REFO4CONCLR_REG_OFST       (0xD4)              /**< (CRU_REFO4CONCLR)  Offset */
#define CRU_REFO4CONSET_REG_OFST       (0xD8)              /**< (CRU_REFO4CONSET)  Offset */
#define CRU_REFO4CONINV_REG_OFST       (0xDC)              /**< (CRU_REFO4CONINV)  Offset */
#define CRU_REFO4TRIM_REG_OFST         (0xE0)              /**< (CRU_REFO4TRIM)  Offset */
#define CRU_REFO4TRIMCLR_REG_OFST      (0xE4)              /**< (CRU_REFO4TRIMCLR)  Offset */
#define CRU_REFO4TRIMSET_REG_OFST      (0xE8)              /**< (CRU_REFO4TRIMSET)  Offset */
#define CRU_REFO4TRIMINV_REG_OFST      (0xEC)              /**< (CRU_REFO4TRIMINV)  Offset */
#define CRU_REFO5CON_REG_OFST          (0xF0)              /**< (CRU_REFO5CON)  Offset */
#define CRU_REFO5CONCLR_REG_OFST       (0xF4)              /**< (CRU_REFO5CONCLR)  Offset */
#define CRU_REFO5CONSET_REG_OFST       (0xF8)              /**< (CRU_REFO5CONSET)  Offset */
#define CRU_REFO5CONINV_REG_OFST       (0xFC)              /**< (CRU_REFO5CONINV)  Offset */
#define CRU_REFO5TRIM_REG_OFST         (0x100)             /**< (CRU_REFO5TRIM)  Offset */
#define CRU_REFO5TRIMCLR_REG_OFST      (0x104)             /**< (CRU_REFO5TRIMCLR)  Offset */
#define CRU_REFO5TRIMSET_REG_OFST      (0x108)             /**< (CRU_REFO5TRIMSET)  Offset */
#define CRU_REFO5TRIMINV_REG_OFST      (0x10C)             /**< (CRU_REFO5TRIMINV)  Offset */
#define CRU_REFO6CON_REG_OFST          (0x110)             /**< (CRU_REFO6CON)  Offset */
#define CRU_REFO6CONCLR_REG_OFST       (0x114)             /**< (CRU_REFO6CONCLR)  Offset */
#define CRU_REFO6CONSET_REG_OFST       (0x118)             /**< (CRU_REFO6CONSET)  Offset */
#define CRU_REFO6CONINV_REG_OFST       (0x11C)             /**< (CRU_REFO6CONINV)  Offset */
#define CRU_REFO6TRIM_REG_OFST         (0x120)             /**< (CRU_REFO6TRIM)  Offset */
#define CRU_REFO6TRIMCLR_REG_OFST      (0x124)             /**< (CRU_REFO6TRIMCLR)  Offset */
#define CRU_REFO6TRIMSET_REG_OFST      (0x128)             /**< (CRU_REFO6TRIMSET)  Offset */
#define CRU_REFO6TRIMINV_REG_OFST      (0x12C)             /**< (CRU_REFO6TRIMINV)  Offset */
#define CRU_PB1DIV_REG_OFST            (0x130)             /**< (CRU_PB1DIV)  Offset */
#define CRU_PB1DIVCLR_REG_OFST         (0x134)             /**< (CRU_PB1DIVCLR)  Offset */
#define CRU_PB1DIVSET_REG_OFST         (0x138)             /**< (CRU_PB1DIVSET)  Offset */
#define CRU_PB1DIVINV_REG_OFST         (0x13C)             /**< (CRU_PB1DIVINV)  Offset */
#define CRU_PB2DIV_REG_OFST            (0x140)             /**< (CRU_PB2DIV)  Offset */
#define CRU_PB2DIVCLR_REG_OFST         (0x144)             /**< (CRU_PB2DIVCLR)  Offset */
#define CRU_PB2DIVSET_REG_OFST         (0x148)             /**< (CRU_PB2DIVSET)  Offset */
#define CRU_PB2DIVINV_REG_OFST         (0x14C)             /**< (CRU_PB2DIVINV)  Offset */
#define CRU_PB3DIV_REG_OFST            (0x150)             /**< (CRU_PB3DIV)  Offset */
#define CRU_PB3DIVCLR_REG_OFST         (0x154)             /**< (CRU_PB3DIVCLR)  Offset */
#define CRU_PB3DIVSET_REG_OFST         (0x158)             /**< (CRU_PB3DIVSET)  Offset */
#define CRU_PB3DIVINV_REG_OFST         (0x15C)             /**< (CRU_PB3DIVINV)  Offset */
#define CRU_SLEWCON_REG_OFST           (0x160)             /**< (CRU_SLEWCON)  Offset */
#define CRU_SLEWCONCLR_REG_OFST        (0x164)             /**< (CRU_SLEWCONCLR)  Offset */
#define CRU_SLEWCONSET_REG_OFST        (0x168)             /**< (CRU_SLEWCONSET)  Offset */
#define CRU_SLEWCONINV_REG_OFST        (0x16C)             /**< (CRU_SLEWCONINV)  Offset */
#define CRU_CLKSTAT_REG_OFST           (0x170)             /**< (CRU_CLKSTAT)  Offset */
#define CRU_OSCCONBAR_REG_OFST         (0x180)             /**< (CRU_OSCCONBAR)  Offset */
#define CRU_CLKDIAG_REG_OFST           (0x190)             /**< (CRU_CLKDIAG)  Offset */
#define CRU_CLKDIAGCLR_REG_OFST        (0x194)             /**< (CRU_CLKDIAGCLR)  Offset */
#define CRU_CLKDIAGSET_REG_OFST        (0x198)             /**< (CRU_CLKDIAGSET)  Offset */
#define CRU_CLKDIAGINV_REG_OFST        (0x19C)             /**< (CRU_CLKDIAGINV)  Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief CRU register API structure */
typedef struct
{  /*  */
  __IO  uint32_t                       CRU_OSCCON;         /**< Offset: 0x00 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCCONCLR;      /**< Offset: 0x04 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCCONSET;      /**< Offset: 0x08 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCCONINV;      /**< Offset: 0x0C (R/W  32)  */
  __IO  uint32_t                       CRU_OSCTRM;         /**< Offset: 0x10 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCTRMCLR;      /**< Offset: 0x14 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCTRMSET;      /**< Offset: 0x18 (R/W  32)  */
  __IO  uint32_t                       CRU_OSCTRMINV;      /**< Offset: 0x1C (R/W  32)  */
  __IO  uint32_t                       CRU_SPLLCON;        /**< Offset: 0x20 (R/W  32)  */
  __IO  uint32_t                       CRU_SPLLCONCLR;     /**< Offset: 0x24 (R/W  32)  */
  __IO  uint32_t                       CRU_SPLLCONSET;     /**< Offset: 0x28 (R/W  32)  */
  __IO  uint32_t                       CRU_SPLLCONINV;     /**< Offset: 0x2C (R/W  32)  */
  __IO  uint32_t                       CRU_RCON;           /**< Offset: 0x30 (R/W  32)  */
  __IO  uint32_t                       CRU_RCONCLR;        /**< Offset: 0x34 (R/W  32)  */
  __IO  uint32_t                       CRU_RCONSET;        /**< Offset: 0x38 (R/W  32)  */
  __IO  uint32_t                       CRU_RCONINV;        /**< Offset: 0x3C (R/W  32)  */
  __IO  uint32_t                       CRU_RSWRST;         /**< Offset: 0x40 (R/W  32)  */
  __IO  uint32_t                       CRU_RSWRSTCLR;      /**< Offset: 0x44 (R/W  32)  */
  __IO  uint32_t                       CRU_RSWRSTSET;      /**< Offset: 0x48 (R/W  32)  */
  __IO  uint32_t                       CRU_RSWRSTINV;      /**< Offset: 0x4C (R/W  32)  */
  __IO  uint32_t                       CRU_RNMICON;        /**< Offset: 0x50 (R/W  32)  */
  __IO  uint32_t                       CRU_RNMICONCLR;     /**< Offset: 0x54 (R/W  32)  */
  __IO  uint32_t                       CRU_RNMICONSET;     /**< Offset: 0x58 (R/W  32)  */
  __IO  uint32_t                       CRU_RNMICONINV;     /**< Offset: 0x5C (R/W  32)  */
  __IO  uint32_t                       CRU_PWRCON;         /**< Offset: 0x60 (R/W  32)  */
  __I   uint8_t                        Reserved1[0x0C];
  __IO  uint32_t                       CRU_REFO1CON;       /**< Offset: 0x70 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1CONCLR;    /**< Offset: 0x74 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1CONSET;    /**< Offset: 0x78 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1CONINV;    /**< Offset: 0x7C (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1TRIM;      /**< Offset: 0x80 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1TRIMCLR;   /**< Offset: 0x84 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1TRIMSET;   /**< Offset: 0x88 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO1TRIMINV;   /**< Offset: 0x8C (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2CON;       /**< Offset: 0x90 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2CONCLR;    /**< Offset: 0x94 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2CONSET;    /**< Offset: 0x98 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2CONINV;    /**< Offset: 0x9C (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2TRIM;      /**< Offset: 0xA0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2TRIMCLR;   /**< Offset: 0xA4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2TRIMSET;   /**< Offset: 0xA8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO2TRIMINV;   /**< Offset: 0xAC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3CON;       /**< Offset: 0xB0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3CONCLR;    /**< Offset: 0xB4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3CONSET;    /**< Offset: 0xB8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3CONINV;    /**< Offset: 0xBC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3TRIM;      /**< Offset: 0xC0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3TRIMCLR;   /**< Offset: 0xC4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3TRIMSET;   /**< Offset: 0xC8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO3TRIMINV;   /**< Offset: 0xCC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4CON;       /**< Offset: 0xD0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4CONCLR;    /**< Offset: 0xD4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4CONSET;    /**< Offset: 0xD8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4CONINV;    /**< Offset: 0xDC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4TRIM;      /**< Offset: 0xE0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4TRIMCLR;   /**< Offset: 0xE4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4TRIMSET;   /**< Offset: 0xE8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO4TRIMINV;   /**< Offset: 0xEC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5CON;       /**< Offset: 0xF0 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5CONCLR;    /**< Offset: 0xF4 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5CONSET;    /**< Offset: 0xF8 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5CONINV;    /**< Offset: 0xFC (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5TRIM;      /**< Offset: 0x100 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5TRIMCLR;   /**< Offset: 0x104 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5TRIMSET;   /**< Offset: 0x108 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO5TRIMINV;   /**< Offset: 0x10C (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6CON;       /**< Offset: 0x110 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6CONCLR;    /**< Offset: 0x114 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6CONSET;    /**< Offset: 0x118 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6CONINV;    /**< Offset: 0x11C (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6TRIM;      /**< Offset: 0x120 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6TRIMCLR;   /**< Offset: 0x124 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6TRIMSET;   /**< Offset: 0x128 (R/W  32)  */
  __IO  uint32_t                       CRU_REFO6TRIMINV;   /**< Offset: 0x12C (R/W  32)  */
  __IO  uint32_t                       CRU_PB1DIV;         /**< Offset: 0x130 (R/W  32)  */
  __IO  uint32_t                       CRU_PB1DIVCLR;      /**< Offset: 0x134 (R/W  32)  */
  __IO  uint32_t                       CRU_PB1DIVSET;      /**< Offset: 0x138 (R/W  32)  */
  __IO  uint32_t                       CRU_PB1DIVINV;      /**< Offset: 0x13C (R/W  32)  */
  __IO  uint32_t                       CRU_PB2DIV;         /**< Offset: 0x140 (R/W  32)  */
  __IO  uint32_t                       CRU_PB2DIVCLR;      /**< Offset: 0x144 (R/W  32)  */
  __IO  uint32_t                       CRU_PB2DIVSET;      /**< Offset: 0x148 (R/W  32)  */
  __IO  uint32_t                       CRU_PB2DIVINV;      /**< Offset: 0x14C (R/W  32)  */
  __IO  uint32_t                       CRU_PB3DIV;         /**< Offset: 0x150 (R/W  32)  */
  __IO  uint32_t                       CRU_PB3DIVCLR;      /**< Offset: 0x154 (R/W  32)  */
  __IO  uint32_t                       CRU_PB3DIVSET;      /**< Offset: 0x158 (R/W  32)  */
  __IO  uint32_t                       CRU_PB3DIVINV;      /**< Offset: 0x15C (R/W  32)  */
  __IO  uint32_t                       CRU_SLEWCON;        /**< Offset: 0x160 (R/W  32)  */
  __IO  uint32_t                       CRU_SLEWCONCLR;     /**< Offset: 0x164 (R/W  32)  */
  __IO  uint32_t                       CRU_SLEWCONSET;     /**< Offset: 0x168 (R/W  32)  */
  __IO  uint32_t                       CRU_SLEWCONINV;     /**< Offset: 0x16C (R/W  32)  */
  __IO  uint32_t                       CRU_CLKSTAT;        /**< Offset: 0x170 (R/W  32)  */
  __I   uint8_t                        Reserved2[0x0C];
  __IO  uint32_t                       CRU_OSCCONBAR;      /**< Offset: 0x180 (R/W  32)  */
  __I   uint8_t                        Reserved3[0x0C];
  __IO  uint32_t                       CRU_CLKDIAG;        /**< Offset: 0x190 (R/W  32)  */
  __IO  uint32_t                       CRU_CLKDIAGCLR;     /**< Offset: 0x194 (R/W  32)  */
  __IO  uint32_t                       CRU_CLKDIAGSET;     /**< Offset: 0x198 (R/W  32)  */
  __IO  uint32_t                       CRU_CLKDIAGINV;     /**< Offset: 0x19C (R/W  32)  */
} cru_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _BZ25_CRU_COMPONENT_H_ */
