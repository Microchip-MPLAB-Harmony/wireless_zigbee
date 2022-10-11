/**
 * \brief Component description for FC
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
#ifndef _BZ25_FC_COMPONENT_H_
#define _BZ25_FC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR FC                                           */
/* ************************************************************************** */

/* -------- FC_NVMCON : (FC Offset: 0x00) (R/W 32)  -------- */
#define FC_NVMCON_RESETVALUE                  _U_(0x00)                                            /**<  (FC_NVMCON)   Reset Value */

#define FC_NVMCON_NVMOP_Pos                   _U_(0)                                               /**< (FC_NVMCON)  Position */
#define FC_NVMCON_NVMOP_Msk                   (_U_(0xF) << FC_NVMCON_NVMOP_Pos)                    /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_NVMOP(value)                (FC_NVMCON_NVMOP_Msk & ((value) << FC_NVMCON_NVMOP_Pos))
#define FC_NVMCON_BFSWAP_Pos                  _U_(6)                                               /**< (FC_NVMCON)  Position */
#define FC_NVMCON_BFSWAP_Msk                  (_U_(0x1) << FC_NVMCON_BFSWAP_Pos)                   /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_BFSWAP(value)               (FC_NVMCON_BFSWAP_Msk & ((value) << FC_NVMCON_BFSWAP_Pos))
#define FC_NVMCON_PFSWAP_Pos                  _U_(7)                                               /**< (FC_NVMCON)  Position */
#define FC_NVMCON_PFSWAP_Msk                  (_U_(0x1) << FC_NVMCON_PFSWAP_Pos)                   /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_PFSWAP(value)               (FC_NVMCON_PFSWAP_Msk & ((value) << FC_NVMCON_PFSWAP_Pos))
#define FC_NVMCON_HTDPGM_Pos                  _U_(8)                                               /**< (FC_NVMCON)  Position */
#define FC_NVMCON_HTDPGM_Msk                  (_U_(0x1) << FC_NVMCON_HTDPGM_Pos)                   /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_HTDPGM(value)               (FC_NVMCON_HTDPGM_Msk & ((value) << FC_NVMCON_HTDPGM_Pos))
#define FC_NVMCON_LVDERR_Pos                  _U_(12)                                              /**< (FC_NVMCON)  Position */
#define FC_NVMCON_LVDERR_Msk                  (_U_(0x1) << FC_NVMCON_LVDERR_Pos)                   /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_LVDERR(value)               (FC_NVMCON_LVDERR_Msk & ((value) << FC_NVMCON_LVDERR_Pos))
#define FC_NVMCON_WRERR_Pos                   _U_(13)                                              /**< (FC_NVMCON)  Position */
#define FC_NVMCON_WRERR_Msk                   (_U_(0x1) << FC_NVMCON_WRERR_Pos)                    /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_WRERR(value)                (FC_NVMCON_WRERR_Msk & ((value) << FC_NVMCON_WRERR_Pos))
#define FC_NVMCON_WREN_Pos                    _U_(14)                                              /**< (FC_NVMCON)  Position */
#define FC_NVMCON_WREN_Msk                    (_U_(0x1) << FC_NVMCON_WREN_Pos)                     /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_WREN(value)                 (FC_NVMCON_WREN_Msk & ((value) << FC_NVMCON_WREN_Pos))
#define FC_NVMCON_WR_Pos                      _U_(15)                                              /**< (FC_NVMCON)  Position */
#define FC_NVMCON_WR_Msk                      (_U_(0x1) << FC_NVMCON_WR_Pos)                       /**< (FC_NVMCON)  Mask */
#define FC_NVMCON_WR(value)                   (FC_NVMCON_WR_Msk & ((value) << FC_NVMCON_WR_Pos))  
#define FC_NVMCON_Msk                         _U_(0x0000F1CF)                                      /**< (FC_NVMCON) Register Mask  */


/* -------- FC_NVMCONCLR : (FC Offset: 0x04) (R/W 32)  -------- */
#define FC_NVMCONCLR_RESETVALUE               _U_(0x00)                                            /**<  (FC_NVMCONCLR)   Reset Value */

#define FC_NVMCONCLR_Msk                      _U_(0x00000000)                                      /**< (FC_NVMCONCLR) Register Mask  */


/* -------- FC_NVMCONSET : (FC Offset: 0x08) (R/W 32)  -------- */
#define FC_NVMCONSET_RESETVALUE               _U_(0x00)                                            /**<  (FC_NVMCONSET)   Reset Value */

#define FC_NVMCONSET_Msk                      _U_(0x00000000)                                      /**< (FC_NVMCONSET) Register Mask  */


/* -------- FC_NVMCONINV : (FC Offset: 0x0C) (R/W 32)  -------- */
#define FC_NVMCONINV_RESETVALUE               _U_(0x00)                                            /**<  (FC_NVMCONINV)   Reset Value */

#define FC_NVMCONINV_Msk                      _U_(0x00000000)                                      /**< (FC_NVMCONINV) Register Mask  */


/* -------- FC_NVMCON2 : (FC Offset: 0x10) (R/W 32)  -------- */
#define FC_NVMCON2_RESETVALUE                 _U_(0x00)                                            /**<  (FC_NVMCON2)   Reset Value */

#define FC_NVMCON2_PREPG_Pos                  _U_(0)                                               /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_PREPG_Msk                  (_U_(0x1) << FC_NVMCON2_PREPG_Pos)                   /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_PREPG(value)               (FC_NVMCON2_PREPG_Msk & ((value) << FC_NVMCON2_PREPG_Pos))
#define FC_NVMCON2_SWAPLK_Pos                 _U_(6)                                               /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_SWAPLK_Msk                 (_U_(0x3) << FC_NVMCON2_SWAPLK_Pos)                  /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_SWAPLK(value)              (FC_NVMCON2_SWAPLK_Msk & ((value) << FC_NVMCON2_SWAPLK_Pos))
#define FC_NVMCON2_RETRY_Pos                  _U_(8)                                               /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_RETRY_Msk                  (_U_(0x3) << FC_NVMCON2_RETRY_Pos)                   /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_RETRY(value)               (FC_NVMCON2_RETRY_Msk & ((value) << FC_NVMCON2_RETRY_Pos))
#define FC_NVMCON2_VREAD1_Pos                 _U_(12)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_VREAD1_Msk                 (_U_(0x1) << FC_NVMCON2_VREAD1_Pos)                  /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_VREAD1(value)              (FC_NVMCON2_VREAD1_Msk & ((value) << FC_NVMCON2_VREAD1_Pos))
#define FC_NVMCON2_CREAD1_Pos                 _U_(13)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_CREAD1_Msk                 (_U_(0x1) << FC_NVMCON2_CREAD1_Pos)                  /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_CREAD1(value)              (FC_NVMCON2_CREAD1_Msk & ((value) << FC_NVMCON2_CREAD1_Pos))
#define FC_NVMCON2_TEMP_Pos                   _U_(14)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_TEMP_Msk                   (_U_(0x1) << FC_NVMCON2_TEMP_Pos)                    /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_TEMP(value)                (FC_NVMCON2_TEMP_Msk & ((value) << FC_NVMCON2_TEMP_Pos))
#define FC_NVMCON2_WS_Pos                     _U_(16)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_WS_Msk                     (_U_(0x1F) << FC_NVMCON2_WS_Pos)                     /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_WS(value)                  (FC_NVMCON2_WS_Msk & ((value) << FC_NVMCON2_WS_Pos))
#define FC_NVMCON2_SLEEP_Pos                  _U_(24)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_SLEEP_Msk                  (_U_(0x1) << FC_NVMCON2_SLEEP_Pos)                   /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_SLEEP(value)               (FC_NVMCON2_SLEEP_Msk & ((value) << FC_NVMCON2_SLEEP_Pos))
#define FC_NVMCON2_ERS_Pos                    _U_(28)                                              /**< (FC_NVMCON2)  Position */
#define FC_NVMCON2_ERS_Msk                    (_U_(0xF) << FC_NVMCON2_ERS_Pos)                     /**< (FC_NVMCON2)  Mask */
#define FC_NVMCON2_ERS(value)                 (FC_NVMCON2_ERS_Msk & ((value) << FC_NVMCON2_ERS_Pos))
#define FC_NVMCON2_Msk                        _U_(0xF11F73C1)                                      /**< (FC_NVMCON2) Register Mask  */

#define FC_NVMCON2_VREAD_Pos                  _U_(12)                                              /**< (FC_NVMCON2 Position)  */
#define FC_NVMCON2_VREAD_Msk                  (_U_(0x1) << FC_NVMCON2_VREAD_Pos)                   /**< (FC_NVMCON2 Mask) VREAD */
#define FC_NVMCON2_VREAD(value)               (FC_NVMCON2_VREAD_Msk & ((value) << FC_NVMCON2_VREAD_Pos)) 
#define FC_NVMCON2_CREAD_Pos                  _U_(13)                                              /**< (FC_NVMCON2 Position)  */
#define FC_NVMCON2_CREAD_Msk                  (_U_(0x1) << FC_NVMCON2_CREAD_Pos)                   /**< (FC_NVMCON2 Mask) CREAD */
#define FC_NVMCON2_CREAD(value)               (FC_NVMCON2_CREAD_Msk & ((value) << FC_NVMCON2_CREAD_Pos)) 

/* -------- FC_NVMCON2CLR : (FC Offset: 0x14) (R/W 32)  -------- */
#define FC_NVMCON2CLR_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMCON2CLR)   Reset Value */

#define FC_NVMCON2CLR_Msk                     _U_(0x00000000)                                      /**< (FC_NVMCON2CLR) Register Mask  */


/* -------- FC_NVMCON2SET : (FC Offset: 0x18) (R/W 32)  -------- */
#define FC_NVMCON2SET_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMCON2SET)   Reset Value */

#define FC_NVMCON2SET_Msk                     _U_(0x00000000)                                      /**< (FC_NVMCON2SET) Register Mask  */


/* -------- FC_NVMCON2INV : (FC Offset: 0x1C) (R/W 32)  -------- */
#define FC_NVMCON2INV_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMCON2INV)   Reset Value */

#define FC_NVMCON2INV_Msk                     _U_(0x00000000)                                      /**< (FC_NVMCON2INV) Register Mask  */


/* -------- FC_NVMKEY : (FC Offset: 0x20) (R/W 32)  -------- */
#define FC_NVMKEY_RESETVALUE                  _U_(0x00)                                            /**<  (FC_NVMKEY)   Reset Value */

#define FC_NVMKEY_NVMKEY_Pos                  _U_(0)                                               /**< (FC_NVMKEY)  Position */
#define FC_NVMKEY_NVMKEY_Msk                  (_U_(0xFFFFFFFF) << FC_NVMKEY_NVMKEY_Pos)            /**< (FC_NVMKEY)  Mask */
#define FC_NVMKEY_NVMKEY(value)               (FC_NVMKEY_NVMKEY_Msk & ((value) << FC_NVMKEY_NVMKEY_Pos))
#define FC_NVMKEY_Msk                         _U_(0xFFFFFFFF)                                      /**< (FC_NVMKEY) Register Mask  */


/* -------- FC_NVMADDR : (FC Offset: 0x30) (R/W 32)  -------- */
#define FC_NVMADDR_RESETVALUE                 _U_(0x00)                                            /**<  (FC_NVMADDR)   Reset Value */

#define FC_NVMADDR_NVMADDR_Pos                _U_(0)                                               /**< (FC_NVMADDR)  Position */
#define FC_NVMADDR_NVMADDR_Msk                (_U_(0xFFFFFFFF) << FC_NVMADDR_NVMADDR_Pos)          /**< (FC_NVMADDR)  Mask */
#define FC_NVMADDR_NVMADDR(value)             (FC_NVMADDR_NVMADDR_Msk & ((value) << FC_NVMADDR_NVMADDR_Pos))
#define FC_NVMADDR_Msk                        _U_(0xFFFFFFFF)                                      /**< (FC_NVMADDR) Register Mask  */


/* -------- FC_NVMDATA0 : (FC Offset: 0x40) (R/W 32)  -------- */
#define FC_NVMDATA0_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA0)   Reset Value */

#define FC_NVMDATA0_NVMDATA0_Pos              _U_(0)                                               /**< (FC_NVMDATA0)  Position */
#define FC_NVMDATA0_NVMDATA0_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA0_NVMDATA0_Pos)        /**< (FC_NVMDATA0)  Mask */
#define FC_NVMDATA0_NVMDATA0(value)           (FC_NVMDATA0_NVMDATA0_Msk & ((value) << FC_NVMDATA0_NVMDATA0_Pos))
#define FC_NVMDATA0_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA0) Register Mask  */


/* -------- FC_NVMDATA1 : (FC Offset: 0x50) (R/W 32)  -------- */
#define FC_NVMDATA1_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA1)   Reset Value */

#define FC_NVMDATA1_NVMDATA1_Pos              _U_(0)                                               /**< (FC_NVMDATA1)  Position */
#define FC_NVMDATA1_NVMDATA1_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA1_NVMDATA1_Pos)        /**< (FC_NVMDATA1)  Mask */
#define FC_NVMDATA1_NVMDATA1(value)           (FC_NVMDATA1_NVMDATA1_Msk & ((value) << FC_NVMDATA1_NVMDATA1_Pos))
#define FC_NVMDATA1_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA1) Register Mask  */


/* -------- FC_NVMDATA2 : (FC Offset: 0x60) (R/W 32)  -------- */
#define FC_NVMDATA2_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA2)   Reset Value */

#define FC_NVMDATA2_NVMDATA2_Pos              _U_(0)                                               /**< (FC_NVMDATA2)  Position */
#define FC_NVMDATA2_NVMDATA2_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA2_NVMDATA2_Pos)        /**< (FC_NVMDATA2)  Mask */
#define FC_NVMDATA2_NVMDATA2(value)           (FC_NVMDATA2_NVMDATA2_Msk & ((value) << FC_NVMDATA2_NVMDATA2_Pos))
#define FC_NVMDATA2_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA2) Register Mask  */


/* -------- FC_NVMDATA3 : (FC Offset: 0x70) (R/W 32)  -------- */
#define FC_NVMDATA3_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA3)   Reset Value */

#define FC_NVMDATA3_NVMDATA3_Pos              _U_(0)                                               /**< (FC_NVMDATA3)  Position */
#define FC_NVMDATA3_NVMDATA3_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA3_NVMDATA3_Pos)        /**< (FC_NVMDATA3)  Mask */
#define FC_NVMDATA3_NVMDATA3(value)           (FC_NVMDATA3_NVMDATA3_Msk & ((value) << FC_NVMDATA3_NVMDATA3_Pos))
#define FC_NVMDATA3_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA3) Register Mask  */


/* -------- FC_NVMDATA4 : (FC Offset: 0x80) (R/W 32)  -------- */
#define FC_NVMDATA4_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA4)   Reset Value */

#define FC_NVMDATA4_NVMDATA4_Pos              _U_(0)                                               /**< (FC_NVMDATA4)  Position */
#define FC_NVMDATA4_NVMDATA4_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA4_NVMDATA4_Pos)        /**< (FC_NVMDATA4)  Mask */
#define FC_NVMDATA4_NVMDATA4(value)           (FC_NVMDATA4_NVMDATA4_Msk & ((value) << FC_NVMDATA4_NVMDATA4_Pos))
#define FC_NVMDATA4_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA4) Register Mask  */


/* -------- FC_NVMDATA5 : (FC Offset: 0x90) (R/W 32)  -------- */
#define FC_NVMDATA5_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA5)   Reset Value */

#define FC_NVMDATA5_NVMDATA5_Pos              _U_(0)                                               /**< (FC_NVMDATA5)  Position */
#define FC_NVMDATA5_NVMDATA5_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA5_NVMDATA5_Pos)        /**< (FC_NVMDATA5)  Mask */
#define FC_NVMDATA5_NVMDATA5(value)           (FC_NVMDATA5_NVMDATA5_Msk & ((value) << FC_NVMDATA5_NVMDATA5_Pos))
#define FC_NVMDATA5_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA5) Register Mask  */


/* -------- FC_NVMDATA6 : (FC Offset: 0xA0) (R/W 32)  -------- */
#define FC_NVMDATA6_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA6)   Reset Value */

#define FC_NVMDATA6_NVMDATA6_Pos              _U_(0)                                               /**< (FC_NVMDATA6)  Position */
#define FC_NVMDATA6_NVMDATA6_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA6_NVMDATA6_Pos)        /**< (FC_NVMDATA6)  Mask */
#define FC_NVMDATA6_NVMDATA6(value)           (FC_NVMDATA6_NVMDATA6_Msk & ((value) << FC_NVMDATA6_NVMDATA6_Pos))
#define FC_NVMDATA6_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA6) Register Mask  */


/* -------- FC_NVMDATA7 : (FC Offset: 0xB0) (R/W 32)  -------- */
#define FC_NVMDATA7_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMDATA7)   Reset Value */

#define FC_NVMDATA7_NVMDATA7_Pos              _U_(0)                                               /**< (FC_NVMDATA7)  Position */
#define FC_NVMDATA7_NVMDATA7_Msk              (_U_(0xFFFFFFFF) << FC_NVMDATA7_NVMDATA7_Pos)        /**< (FC_NVMDATA7)  Mask */
#define FC_NVMDATA7_NVMDATA7(value)           (FC_NVMDATA7_NVMDATA7_Msk & ((value) << FC_NVMDATA7_NVMDATA7_Pos))
#define FC_NVMDATA7_Msk                       _U_(0xFFFFFFFF)                                      /**< (FC_NVMDATA7) Register Mask  */


/* -------- FC_NVMSRCADDR : (FC Offset: 0xC0) (R/W 32)  -------- */
#define FC_NVMSRCADDR_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMSRCADDR)   Reset Value */

#define FC_NVMSRCADDR_NVMSRCADDR_Pos          _U_(0)                                               /**< (FC_NVMSRCADDR)  Position */
#define FC_NVMSRCADDR_NVMSRCADDR_Msk          (_U_(0xFFFFFFFF) << FC_NVMSRCADDR_NVMSRCADDR_Pos)    /**< (FC_NVMSRCADDR)  Mask */
#define FC_NVMSRCADDR_NVMSRCADDR(value)       (FC_NVMSRCADDR_NVMSRCADDR_Msk & ((value) << FC_NVMSRCADDR_NVMSRCADDR_Pos))
#define FC_NVMSRCADDR_Msk                     _U_(0xFFFFFFFF)                                      /**< (FC_NVMSRCADDR) Register Mask  */


/* -------- FC_NVMPWPLT : (FC Offset: 0xD0) (R/W 32)  -------- */
#define FC_NVMPWPLT_RESETVALUE                _U_(0x00)                                            /**<  (FC_NVMPWPLT)   Reset Value */

#define FC_NVMPWPLT_PWPLT_Pos                 _U_(0)                                               /**< (FC_NVMPWPLT)  Position */
#define FC_NVMPWPLT_PWPLT_Msk                 (_U_(0xFFFFFF) << FC_NVMPWPLT_PWPLT_Pos)             /**< (FC_NVMPWPLT)  Mask */
#define FC_NVMPWPLT_PWPLT(value)              (FC_NVMPWPLT_PWPLT_Msk & ((value) << FC_NVMPWPLT_PWPLT_Pos))
#define FC_NVMPWPLT_ULOCK_Pos                 _U_(31)                                              /**< (FC_NVMPWPLT)  Position */
#define FC_NVMPWPLT_ULOCK_Msk                 (_U_(0x1) << FC_NVMPWPLT_ULOCK_Pos)                  /**< (FC_NVMPWPLT)  Mask */
#define FC_NVMPWPLT_ULOCK(value)              (FC_NVMPWPLT_ULOCK_Msk & ((value) << FC_NVMPWPLT_ULOCK_Pos))
#define FC_NVMPWPLT_Msk                       _U_(0x80FFFFFF)                                      /**< (FC_NVMPWPLT) Register Mask  */


/* -------- FC_NVMPWPLTCLR : (FC Offset: 0xD4) (R/W 32)  -------- */
#define FC_NVMPWPLTCLR_RESETVALUE             _U_(0x00)                                            /**<  (FC_NVMPWPLTCLR)   Reset Value */

#define FC_NVMPWPLTCLR_Msk                    _U_(0x00000000)                                      /**< (FC_NVMPWPLTCLR) Register Mask  */


/* -------- FC_NVMPWPLTSET : (FC Offset: 0xD8) (R/W 32)  -------- */
#define FC_NVMPWPLTSET_RESETVALUE             _U_(0x00)                                            /**<  (FC_NVMPWPLTSET)   Reset Value */

#define FC_NVMPWPLTSET_Msk                    _U_(0x00000000)                                      /**< (FC_NVMPWPLTSET) Register Mask  */


/* -------- FC_NVMPWPLTINV : (FC Offset: 0xDC) (R/W 32)  -------- */
#define FC_NVMPWPLTINV_RESETVALUE             _U_(0x00)                                            /**<  (FC_NVMPWPLTINV)   Reset Value */

#define FC_NVMPWPLTINV_Msk                    _U_(0x00000000)                                      /**< (FC_NVMPWPLTINV) Register Mask  */


/* -------- FC_NVMPWPGTE : (FC Offset: 0xE0) (R/W 32)  -------- */
#define FC_NVMPWPGTE_RESETVALUE               _U_(0x00)                                            /**<  (FC_NVMPWPGTE)   Reset Value */

#define FC_NVMPWPGTE_PWPGTE_Pos               _U_(0)                                               /**< (FC_NVMPWPGTE)  Position */
#define FC_NVMPWPGTE_PWPGTE_Msk               (_U_(0xFFFFFF) << FC_NVMPWPGTE_PWPGTE_Pos)           /**< (FC_NVMPWPGTE)  Mask */
#define FC_NVMPWPGTE_PWPGTE(value)            (FC_NVMPWPGTE_PWPGTE_Msk & ((value) << FC_NVMPWPGTE_PWPGTE_Pos))
#define FC_NVMPWPGTE_ULOCK_Pos                _U_(31)                                              /**< (FC_NVMPWPGTE)  Position */
#define FC_NVMPWPGTE_ULOCK_Msk                (_U_(0x1) << FC_NVMPWPGTE_ULOCK_Pos)                 /**< (FC_NVMPWPGTE)  Mask */
#define FC_NVMPWPGTE_ULOCK(value)             (FC_NVMPWPGTE_ULOCK_Msk & ((value) << FC_NVMPWPGTE_ULOCK_Pos))
#define FC_NVMPWPGTE_Msk                      _U_(0x80FFFFFF)                                      /**< (FC_NVMPWPGTE) Register Mask  */


/* -------- FC_NVMPWPGTECLR : (FC Offset: 0xE4) (R/W 32)  -------- */
#define FC_NVMPWPGTECLR_RESETVALUE            _U_(0x00)                                            /**<  (FC_NVMPWPGTECLR)   Reset Value */

#define FC_NVMPWPGTECLR_Msk                   _U_(0x00000000)                                      /**< (FC_NVMPWPGTECLR) Register Mask  */


/* -------- FC_NVMPWPGTESET : (FC Offset: 0xE8) (R/W 32)  -------- */
#define FC_NVMPWPGTESET_RESETVALUE            _U_(0x00)                                            /**<  (FC_NVMPWPGTESET)   Reset Value */

#define FC_NVMPWPGTESET_Msk                   _U_(0x00000000)                                      /**< (FC_NVMPWPGTESET) Register Mask  */


/* -------- FC_NVMPWPGTEINV : (FC Offset: 0xEC) (R/W 32)  -------- */
#define FC_NVMPWPGTEINV_RESETVALUE            _U_(0x00)                                            /**<  (FC_NVMPWPGTEINV)   Reset Value */

#define FC_NVMPWPGTEINV_Msk                   _U_(0x00000000)                                      /**< (FC_NVMPWPGTEINV) Register Mask  */


/* -------- FC_NVMLBWP : (FC Offset: 0xF0) (R/W 32)  -------- */
#define FC_NVMLBWP_RESETVALUE                 _U_(0x00)                                            /**<  (FC_NVMLBWP)   Reset Value */

#define FC_NVMLBWP_LBWP0_Pos                  _U_(0)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP0_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP0_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP0(value)               (FC_NVMLBWP_LBWP0_Msk & ((value) << FC_NVMLBWP_LBWP0_Pos))
#define FC_NVMLBWP_LBWP1_Pos                  _U_(1)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP1_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP1_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP1(value)               (FC_NVMLBWP_LBWP1_Msk & ((value) << FC_NVMLBWP_LBWP1_Pos))
#define FC_NVMLBWP_LBWP2_Pos                  _U_(2)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP2_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP2_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP2(value)               (FC_NVMLBWP_LBWP2_Msk & ((value) << FC_NVMLBWP_LBWP2_Pos))
#define FC_NVMLBWP_LBWP3_Pos                  _U_(3)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP3_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP3_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP3(value)               (FC_NVMLBWP_LBWP3_Msk & ((value) << FC_NVMLBWP_LBWP3_Pos))
#define FC_NVMLBWP_LBWP4_Pos                  _U_(4)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP4_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP4_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP4(value)               (FC_NVMLBWP_LBWP4_Msk & ((value) << FC_NVMLBWP_LBWP4_Pos))
#define FC_NVMLBWP_LBWP5_Pos                  _U_(5)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP5_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP5_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP5(value)               (FC_NVMLBWP_LBWP5_Msk & ((value) << FC_NVMLBWP_LBWP5_Pos))
#define FC_NVMLBWP_LBWP6_Pos                  _U_(6)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP6_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP6_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP6(value)               (FC_NVMLBWP_LBWP6_Msk & ((value) << FC_NVMLBWP_LBWP6_Pos))
#define FC_NVMLBWP_LBWP7_Pos                  _U_(7)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP7_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP7_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP7(value)               (FC_NVMLBWP_LBWP7_Msk & ((value) << FC_NVMLBWP_LBWP7_Pos))
#define FC_NVMLBWP_LBWP8_Pos                  _U_(8)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP8_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP8_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP8(value)               (FC_NVMLBWP_LBWP8_Msk & ((value) << FC_NVMLBWP_LBWP8_Pos))
#define FC_NVMLBWP_LBWP9_Pos                  _U_(9)                                               /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP9_Msk                  (_U_(0x1) << FC_NVMLBWP_LBWP9_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP9(value)               (FC_NVMLBWP_LBWP9_Msk & ((value) << FC_NVMLBWP_LBWP9_Pos))
#define FC_NVMLBWP_LBWP10_Pos                 _U_(10)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP10_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP10_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP10(value)              (FC_NVMLBWP_LBWP10_Msk & ((value) << FC_NVMLBWP_LBWP10_Pos))
#define FC_NVMLBWP_LBWP11_Pos                 _U_(11)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP11_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP11_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP11(value)              (FC_NVMLBWP_LBWP11_Msk & ((value) << FC_NVMLBWP_LBWP11_Pos))
#define FC_NVMLBWP_LBWP12_Pos                 _U_(12)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP12_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP12_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP12(value)              (FC_NVMLBWP_LBWP12_Msk & ((value) << FC_NVMLBWP_LBWP12_Pos))
#define FC_NVMLBWP_LBWP13_Pos                 _U_(13)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP13_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP13_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP13(value)              (FC_NVMLBWP_LBWP13_Msk & ((value) << FC_NVMLBWP_LBWP13_Pos))
#define FC_NVMLBWP_LBWP14_Pos                 _U_(14)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP14_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP14_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP14(value)              (FC_NVMLBWP_LBWP14_Msk & ((value) << FC_NVMLBWP_LBWP14_Pos))
#define FC_NVMLBWP_LBWP15_Pos                 _U_(15)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP15_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP15_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP15(value)              (FC_NVMLBWP_LBWP15_Msk & ((value) << FC_NVMLBWP_LBWP15_Pos))
#define FC_NVMLBWP_LBWP16_Pos                 _U_(16)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP16_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP16_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP16(value)              (FC_NVMLBWP_LBWP16_Msk & ((value) << FC_NVMLBWP_LBWP16_Pos))
#define FC_NVMLBWP_LBWP17_Pos                 _U_(17)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP17_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP17_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP17(value)              (FC_NVMLBWP_LBWP17_Msk & ((value) << FC_NVMLBWP_LBWP17_Pos))
#define FC_NVMLBWP_LBWP18_Pos                 _U_(18)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP18_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP18_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP18(value)              (FC_NVMLBWP_LBWP18_Msk & ((value) << FC_NVMLBWP_LBWP18_Pos))
#define FC_NVMLBWP_LBWP19_Pos                 _U_(19)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP19_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP19_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP19(value)              (FC_NVMLBWP_LBWP19_Msk & ((value) << FC_NVMLBWP_LBWP19_Pos))
#define FC_NVMLBWP_LBWP20_Pos                 _U_(20)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP20_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP20_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP20(value)              (FC_NVMLBWP_LBWP20_Msk & ((value) << FC_NVMLBWP_LBWP20_Pos))
#define FC_NVMLBWP_LBWP21_Pos                 _U_(21)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP21_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP21_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP21(value)              (FC_NVMLBWP_LBWP21_Msk & ((value) << FC_NVMLBWP_LBWP21_Pos))
#define FC_NVMLBWP_LBWP22_Pos                 _U_(22)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP22_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP22_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP22(value)              (FC_NVMLBWP_LBWP22_Msk & ((value) << FC_NVMLBWP_LBWP22_Pos))
#define FC_NVMLBWP_LBWP23_Pos                 _U_(23)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_LBWP23_Msk                 (_U_(0x1) << FC_NVMLBWP_LBWP23_Pos)                  /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_LBWP23(value)              (FC_NVMLBWP_LBWP23_Msk & ((value) << FC_NVMLBWP_LBWP23_Pos))
#define FC_NVMLBWP_ULOCK_Pos                  _U_(31)                                              /**< (FC_NVMLBWP)  Position */
#define FC_NVMLBWP_ULOCK_Msk                  (_U_(0x1) << FC_NVMLBWP_ULOCK_Pos)                   /**< (FC_NVMLBWP)  Mask */
#define FC_NVMLBWP_ULOCK(value)               (FC_NVMLBWP_ULOCK_Msk & ((value) << FC_NVMLBWP_ULOCK_Pos))
#define FC_NVMLBWP_Msk                        _U_(0x80FFFFFF)                                      /**< (FC_NVMLBWP) Register Mask  */

#define FC_NVMLBWP_LBWP_Pos                   _U_(0)                                               /**< (FC_NVMLBWP Position)  */
#define FC_NVMLBWP_LBWP_Msk                   (_U_(0xFFFFFF) << FC_NVMLBWP_LBWP_Pos)               /**< (FC_NVMLBWP Mask) LBWP */
#define FC_NVMLBWP_LBWP(value)                (FC_NVMLBWP_LBWP_Msk & ((value) << FC_NVMLBWP_LBWP_Pos)) 

/* -------- FC_NVMLBWPCLR : (FC Offset: 0xF4) (R/W 32)  -------- */
#define FC_NVMLBWPCLR_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMLBWPCLR)   Reset Value */

#define FC_NVMLBWPCLR_Msk                     _U_(0x00000000)                                      /**< (FC_NVMLBWPCLR) Register Mask  */


/* -------- FC_NVMLBWPSET : (FC Offset: 0xF8) (R/W 32)  -------- */
#define FC_NVMLBWPSET_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMLBWPSET)   Reset Value */

#define FC_NVMLBWPSET_Msk                     _U_(0x00000000)                                      /**< (FC_NVMLBWPSET) Register Mask  */


/* -------- FC_NVMLBWPINV : (FC Offset: 0xFC) (R/W 32)  -------- */
#define FC_NVMLBWPINV_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMLBWPINV)   Reset Value */

#define FC_NVMLBWPINV_Msk                     _U_(0x00000000)                                      /**< (FC_NVMLBWPINV) Register Mask  */


/* -------- FC_NVMUBWP : (FC Offset: 0x100) (R/W 32)  -------- */
#define FC_NVMUBWP_RESETVALUE                 _U_(0x00)                                            /**<  (FC_NVMUBWP)   Reset Value */

#define FC_NVMUBWP_UBWP0_Pos                  _U_(0)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP0_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP0_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP0(value)               (FC_NVMUBWP_UBWP0_Msk & ((value) << FC_NVMUBWP_UBWP0_Pos))
#define FC_NVMUBWP_UBWP1_Pos                  _U_(1)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP1_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP1_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP1(value)               (FC_NVMUBWP_UBWP1_Msk & ((value) << FC_NVMUBWP_UBWP1_Pos))
#define FC_NVMUBWP_UBWP2_Pos                  _U_(2)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP2_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP2_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP2(value)               (FC_NVMUBWP_UBWP2_Msk & ((value) << FC_NVMUBWP_UBWP2_Pos))
#define FC_NVMUBWP_UBWP3_Pos                  _U_(3)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP3_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP3_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP3(value)               (FC_NVMUBWP_UBWP3_Msk & ((value) << FC_NVMUBWP_UBWP3_Pos))
#define FC_NVMUBWP_UBWP4_Pos                  _U_(4)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP4_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP4_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP4(value)               (FC_NVMUBWP_UBWP4_Msk & ((value) << FC_NVMUBWP_UBWP4_Pos))
#define FC_NVMUBWP_UBWP5_Pos                  _U_(5)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP5_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP5_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP5(value)               (FC_NVMUBWP_UBWP5_Msk & ((value) << FC_NVMUBWP_UBWP5_Pos))
#define FC_NVMUBWP_UBWP6_Pos                  _U_(6)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP6_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP6_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP6(value)               (FC_NVMUBWP_UBWP6_Msk & ((value) << FC_NVMUBWP_UBWP6_Pos))
#define FC_NVMUBWP_UBWP7_Pos                  _U_(7)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP7_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP7_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP7(value)               (FC_NVMUBWP_UBWP7_Msk & ((value) << FC_NVMUBWP_UBWP7_Pos))
#define FC_NVMUBWP_UBWP8_Pos                  _U_(8)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP8_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP8_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP8(value)               (FC_NVMUBWP_UBWP8_Msk & ((value) << FC_NVMUBWP_UBWP8_Pos))
#define FC_NVMUBWP_UBWP9_Pos                  _U_(9)                                               /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP9_Msk                  (_U_(0x1) << FC_NVMUBWP_UBWP9_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP9(value)               (FC_NVMUBWP_UBWP9_Msk & ((value) << FC_NVMUBWP_UBWP9_Pos))
#define FC_NVMUBWP_UBWP10_Pos                 _U_(10)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP10_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP10_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP10(value)              (FC_NVMUBWP_UBWP10_Msk & ((value) << FC_NVMUBWP_UBWP10_Pos))
#define FC_NVMUBWP_UBWP11_Pos                 _U_(11)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP11_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP11_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP11(value)              (FC_NVMUBWP_UBWP11_Msk & ((value) << FC_NVMUBWP_UBWP11_Pos))
#define FC_NVMUBWP_UBWP12_Pos                 _U_(12)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP12_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP12_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP12(value)              (FC_NVMUBWP_UBWP12_Msk & ((value) << FC_NVMUBWP_UBWP12_Pos))
#define FC_NVMUBWP_UBWP13_Pos                 _U_(13)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP13_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP13_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP13(value)              (FC_NVMUBWP_UBWP13_Msk & ((value) << FC_NVMUBWP_UBWP13_Pos))
#define FC_NVMUBWP_UBWP14_Pos                 _U_(14)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP14_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP14_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP14(value)              (FC_NVMUBWP_UBWP14_Msk & ((value) << FC_NVMUBWP_UBWP14_Pos))
#define FC_NVMUBWP_UBWP15_Pos                 _U_(15)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP15_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP15_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP15(value)              (FC_NVMUBWP_UBWP15_Msk & ((value) << FC_NVMUBWP_UBWP15_Pos))
#define FC_NVMUBWP_UBWP16_Pos                 _U_(16)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP16_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP16_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP16(value)              (FC_NVMUBWP_UBWP16_Msk & ((value) << FC_NVMUBWP_UBWP16_Pos))
#define FC_NVMUBWP_UBWP17_Pos                 _U_(17)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP17_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP17_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP17(value)              (FC_NVMUBWP_UBWP17_Msk & ((value) << FC_NVMUBWP_UBWP17_Pos))
#define FC_NVMUBWP_UBWP18_Pos                 _U_(18)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP18_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP18_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP18(value)              (FC_NVMUBWP_UBWP18_Msk & ((value) << FC_NVMUBWP_UBWP18_Pos))
#define FC_NVMUBWP_UBWP19_Pos                 _U_(19)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP19_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP19_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP19(value)              (FC_NVMUBWP_UBWP19_Msk & ((value) << FC_NVMUBWP_UBWP19_Pos))
#define FC_NVMUBWP_UBWP20_Pos                 _U_(20)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP20_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP20_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP20(value)              (FC_NVMUBWP_UBWP20_Msk & ((value) << FC_NVMUBWP_UBWP20_Pos))
#define FC_NVMUBWP_UBWP21_Pos                 _U_(21)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP21_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP21_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP21(value)              (FC_NVMUBWP_UBWP21_Msk & ((value) << FC_NVMUBWP_UBWP21_Pos))
#define FC_NVMUBWP_UBWP22_Pos                 _U_(22)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP22_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP22_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP22(value)              (FC_NVMUBWP_UBWP22_Msk & ((value) << FC_NVMUBWP_UBWP22_Pos))
#define FC_NVMUBWP_UBWP23_Pos                 _U_(23)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_UBWP23_Msk                 (_U_(0x1) << FC_NVMUBWP_UBWP23_Pos)                  /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_UBWP23(value)              (FC_NVMUBWP_UBWP23_Msk & ((value) << FC_NVMUBWP_UBWP23_Pos))
#define FC_NVMUBWP_ULOCK_Pos                  _U_(31)                                              /**< (FC_NVMUBWP)  Position */
#define FC_NVMUBWP_ULOCK_Msk                  (_U_(0x1) << FC_NVMUBWP_ULOCK_Pos)                   /**< (FC_NVMUBWP)  Mask */
#define FC_NVMUBWP_ULOCK(value)               (FC_NVMUBWP_ULOCK_Msk & ((value) << FC_NVMUBWP_ULOCK_Pos))
#define FC_NVMUBWP_Msk                        _U_(0x80FFFFFF)                                      /**< (FC_NVMUBWP) Register Mask  */

#define FC_NVMUBWP_UBWP_Pos                   _U_(0)                                               /**< (FC_NVMUBWP Position)  */
#define FC_NVMUBWP_UBWP_Msk                   (_U_(0xFFFFFF) << FC_NVMUBWP_UBWP_Pos)               /**< (FC_NVMUBWP Mask) UBWP */
#define FC_NVMUBWP_UBWP(value)                (FC_NVMUBWP_UBWP_Msk & ((value) << FC_NVMUBWP_UBWP_Pos)) 

/* -------- FC_NVMUBWPCLR : (FC Offset: 0x104) (R/W 32)  -------- */
#define FC_NVMUBWPCLR_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMUBWPCLR)   Reset Value */

#define FC_NVMUBWPCLR_Msk                     _U_(0x00000000)                                      /**< (FC_NVMUBWPCLR) Register Mask  */


/* -------- FC_NVMUBWPSET : (FC Offset: 0x108) (R/W 32)  -------- */
#define FC_NVMUBWPSET_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMUBWPSET)   Reset Value */

#define FC_NVMUBWPSET_Msk                     _U_(0x00000000)                                      /**< (FC_NVMUBWPSET) Register Mask  */


/* -------- FC_NVMUBWPINV : (FC Offset: 0x10C) (R/W 32)  -------- */
#define FC_NVMUBWPINV_RESETVALUE              _U_(0x00)                                            /**<  (FC_NVMUBWPINV)   Reset Value */

#define FC_NVMUBWPINV_Msk                     _U_(0x00000000)                                      /**< (FC_NVMUBWPINV) Register Mask  */


/** \brief FC register offsets definitions */
#define FC_NVMCON_REG_OFST             (0x00)              /**< (FC_NVMCON)  Offset */
#define FC_NVMCONCLR_REG_OFST          (0x04)              /**< (FC_NVMCONCLR)  Offset */
#define FC_NVMCONSET_REG_OFST          (0x08)              /**< (FC_NVMCONSET)  Offset */
#define FC_NVMCONINV_REG_OFST          (0x0C)              /**< (FC_NVMCONINV)  Offset */
#define FC_NVMCON2_REG_OFST            (0x10)              /**< (FC_NVMCON2)  Offset */
#define FC_NVMCON2CLR_REG_OFST         (0x14)              /**< (FC_NVMCON2CLR)  Offset */
#define FC_NVMCON2SET_REG_OFST         (0x18)              /**< (FC_NVMCON2SET)  Offset */
#define FC_NVMCON2INV_REG_OFST         (0x1C)              /**< (FC_NVMCON2INV)  Offset */
#define FC_NVMKEY_REG_OFST             (0x20)              /**< (FC_NVMKEY)  Offset */
#define FC_NVMADDR_REG_OFST            (0x30)              /**< (FC_NVMADDR)  Offset */
#define FC_NVMDATA0_REG_OFST           (0x40)              /**< (FC_NVMDATA0)  Offset */
#define FC_NVMDATA1_REG_OFST           (0x50)              /**< (FC_NVMDATA1)  Offset */
#define FC_NVMDATA2_REG_OFST           (0x60)              /**< (FC_NVMDATA2)  Offset */
#define FC_NVMDATA3_REG_OFST           (0x70)              /**< (FC_NVMDATA3)  Offset */
#define FC_NVMDATA4_REG_OFST           (0x80)              /**< (FC_NVMDATA4)  Offset */
#define FC_NVMDATA5_REG_OFST           (0x90)              /**< (FC_NVMDATA5)  Offset */
#define FC_NVMDATA6_REG_OFST           (0xA0)              /**< (FC_NVMDATA6)  Offset */
#define FC_NVMDATA7_REG_OFST           (0xB0)              /**< (FC_NVMDATA7)  Offset */
#define FC_NVMSRCADDR_REG_OFST         (0xC0)              /**< (FC_NVMSRCADDR)  Offset */
#define FC_NVMPWPLT_REG_OFST           (0xD0)              /**< (FC_NVMPWPLT)  Offset */
#define FC_NVMPWPLTCLR_REG_OFST        (0xD4)              /**< (FC_NVMPWPLTCLR)  Offset */
#define FC_NVMPWPLTSET_REG_OFST        (0xD8)              /**< (FC_NVMPWPLTSET)  Offset */
#define FC_NVMPWPLTINV_REG_OFST        (0xDC)              /**< (FC_NVMPWPLTINV)  Offset */
#define FC_NVMPWPGTE_REG_OFST          (0xE0)              /**< (FC_NVMPWPGTE)  Offset */
#define FC_NVMPWPGTECLR_REG_OFST       (0xE4)              /**< (FC_NVMPWPGTECLR)  Offset */
#define FC_NVMPWPGTESET_REG_OFST       (0xE8)              /**< (FC_NVMPWPGTESET)  Offset */
#define FC_NVMPWPGTEINV_REG_OFST       (0xEC)              /**< (FC_NVMPWPGTEINV)  Offset */
#define FC_NVMLBWP_REG_OFST            (0xF0)              /**< (FC_NVMLBWP)  Offset */
#define FC_NVMLBWPCLR_REG_OFST         (0xF4)              /**< (FC_NVMLBWPCLR)  Offset */
#define FC_NVMLBWPSET_REG_OFST         (0xF8)              /**< (FC_NVMLBWPSET)  Offset */
#define FC_NVMLBWPINV_REG_OFST         (0xFC)              /**< (FC_NVMLBWPINV)  Offset */
#define FC_NVMUBWP_REG_OFST            (0x100)             /**< (FC_NVMUBWP)  Offset */
#define FC_NVMUBWPCLR_REG_OFST         (0x104)             /**< (FC_NVMUBWPCLR)  Offset */
#define FC_NVMUBWPSET_REG_OFST         (0x108)             /**< (FC_NVMUBWPSET)  Offset */
#define FC_NVMUBWPINV_REG_OFST         (0x10C)             /**< (FC_NVMUBWPINV)  Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief FC register API structure */
typedef struct
{  /* flash controller */
  __IO  uint32_t                       FC_NVMCON;          /**< Offset: 0x00 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCONCLR;       /**< Offset: 0x04 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCONSET;       /**< Offset: 0x08 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCONINV;       /**< Offset: 0x0C (R/W  32)  */
  __IO  uint32_t                       FC_NVMCON2;         /**< Offset: 0x10 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCON2CLR;      /**< Offset: 0x14 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCON2SET;      /**< Offset: 0x18 (R/W  32)  */
  __IO  uint32_t                       FC_NVMCON2INV;      /**< Offset: 0x1C (R/W  32)  */
  __IO  uint32_t                       FC_NVMKEY;          /**< Offset: 0x20 (R/W  32)  */
  __I   uint8_t                        Reserved1[0x0C];
  __IO  uint32_t                       FC_NVMADDR;         /**< Offset: 0x30 (R/W  32)  */
  __I   uint8_t                        Reserved2[0x0C];
  __IO  uint32_t                       FC_NVMDATA0;        /**< Offset: 0x40 (R/W  32)  */
  __I   uint8_t                        Reserved3[0x0C];
  __IO  uint32_t                       FC_NVMDATA1;        /**< Offset: 0x50 (R/W  32)  */
  __I   uint8_t                        Reserved4[0x0C];
  __IO  uint32_t                       FC_NVMDATA2;        /**< Offset: 0x60 (R/W  32)  */
  __I   uint8_t                        Reserved5[0x0C];
  __IO  uint32_t                       FC_NVMDATA3;        /**< Offset: 0x70 (R/W  32)  */
  __I   uint8_t                        Reserved6[0x0C];
  __IO  uint32_t                       FC_NVMDATA4;        /**< Offset: 0x80 (R/W  32)  */
  __I   uint8_t                        Reserved7[0x0C];
  __IO  uint32_t                       FC_NVMDATA5;        /**< Offset: 0x90 (R/W  32)  */
  __I   uint8_t                        Reserved8[0x0C];
  __IO  uint32_t                       FC_NVMDATA6;        /**< Offset: 0xA0 (R/W  32)  */
  __I   uint8_t                        Reserved9[0x0C];
  __IO  uint32_t                       FC_NVMDATA7;        /**< Offset: 0xB0 (R/W  32)  */
  __I   uint8_t                        Reserved10[0x0C];
  __IO  uint32_t                       FC_NVMSRCADDR;      /**< Offset: 0xC0 (R/W  32)  */
  __I   uint8_t                        Reserved11[0x0C];
  __IO  uint32_t                       FC_NVMPWPLT;        /**< Offset: 0xD0 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPLTCLR;     /**< Offset: 0xD4 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPLTSET;     /**< Offset: 0xD8 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPLTINV;     /**< Offset: 0xDC (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPGTE;       /**< Offset: 0xE0 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPGTECLR;    /**< Offset: 0xE4 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPGTESET;    /**< Offset: 0xE8 (R/W  32)  */
  __IO  uint32_t                       FC_NVMPWPGTEINV;    /**< Offset: 0xEC (R/W  32)  */
  __IO  uint32_t                       FC_NVMLBWP;         /**< Offset: 0xF0 (R/W  32)  */
  __IO  uint32_t                       FC_NVMLBWPCLR;      /**< Offset: 0xF4 (R/W  32)  */
  __IO  uint32_t                       FC_NVMLBWPSET;      /**< Offset: 0xF8 (R/W  32)  */
  __IO  uint32_t                       FC_NVMLBWPINV;      /**< Offset: 0xFC (R/W  32)  */
  __IO  uint32_t                       FC_NVMUBWP;         /**< Offset: 0x100 (R/W  32)  */
  __IO  uint32_t                       FC_NVMUBWPCLR;      /**< Offset: 0x104 (R/W  32)  */
  __IO  uint32_t                       FC_NVMUBWPSET;      /**< Offset: 0x108 (R/W  32)  */
  __IO  uint32_t                       FC_NVMUBWPINV;      /**< Offset: 0x10C (R/W  32)  */
} fc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _BZ25_FC_COMPONENT_H_ */
