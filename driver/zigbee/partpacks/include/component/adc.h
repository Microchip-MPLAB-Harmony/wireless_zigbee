/**
 * \brief Component description for ADC
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
#ifndef _BZ25_ADC_COMPONENT_H_
#define _BZ25_ADC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR ADC                                          */
/* ************************************************************************** */

/* -------- ADC_ADCCON1 : (ADC Offset: 0x00) (R/W 32)  -------- */
#define ADC_ADCCON1_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCCON1)   Reset Value */

#define ADC_ADCCON1_DMABL_Pos                 _U_(0)                                               /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_DMABL_Msk                 (_U_(0x7) << ADC_ADCCON1_DMABL_Pos)                  /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_DMABL(value)              (ADC_ADCCON1_DMABL_Msk & ((value) << ADC_ADCCON1_DMABL_Pos))
#define ADC_ADCCON1_STRGLVL_Pos               _U_(3)                                               /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_STRGLVL_Msk               (_U_(0x1) << ADC_ADCCON1_STRGLVL_Pos)                /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_STRGLVL(value)            (ADC_ADCCON1_STRGLVL_Msk & ((value) << ADC_ADCCON1_STRGLVL_Pos))
#define ADC_ADCCON1_IRQVS_Pos                 _U_(4)                                               /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_IRQVS_Msk                 (_U_(0x7) << ADC_ADCCON1_IRQVS_Pos)                  /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_IRQVS(value)              (ADC_ADCCON1_IRQVS_Msk & ((value) << ADC_ADCCON1_IRQVS_Pos))
#define ADC_ADCCON1_SCANEN_Pos                _U_(8)                                               /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_SCANEN_Msk                (_U_(0x1) << ADC_ADCCON1_SCANEN_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_SCANEN(value)             (ADC_ADCCON1_SCANEN_Msk & ((value) << ADC_ADCCON1_SCANEN_Pos))
#define ADC_ADCCON1_FSYUPB_Pos                _U_(9)                                               /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_FSYUPB_Msk                (_U_(0x1) << ADC_ADCCON1_FSYUPB_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_FSYUPB(value)             (ADC_ADCCON1_FSYUPB_Msk & ((value) << ADC_ADCCON1_FSYUPB_Pos))
#define ADC_ADCCON1_FSYDMA_Pos                _U_(10)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_FSYDMA_Msk                (_U_(0x1) << ADC_ADCCON1_FSYDMA_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_FSYDMA(value)             (ADC_ADCCON1_FSYDMA_Msk & ((value) << ADC_ADCCON1_FSYDMA_Pos))
#define ADC_ADCCON1_SIDL_Pos                  _U_(13)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_SIDL_Msk                  (_U_(0x1) << ADC_ADCCON1_SIDL_Pos)                   /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_SIDL(value)               (ADC_ADCCON1_SIDL_Msk & ((value) << ADC_ADCCON1_SIDL_Pos))
#define ADC_ADCCON1_FRZ_Pos                   _U_(14)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_FRZ_Msk                   (_U_(0x1) << ADC_ADCCON1_FRZ_Pos)                    /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_FRZ(value)                (ADC_ADCCON1_FRZ_Msk & ((value) << ADC_ADCCON1_FRZ_Pos))
#define ADC_ADCCON1_ON_Pos                    _U_(15)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_ON_Msk                    (_U_(0x1) << ADC_ADCCON1_ON_Pos)                     /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_ON(value)                 (ADC_ADCCON1_ON_Msk & ((value) << ADC_ADCCON1_ON_Pos))
#define ADC_ADCCON1_STRGSRC_Pos               _U_(16)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_STRGSRC_Msk               (_U_(0x1F) << ADC_ADCCON1_STRGSRC_Pos)               /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_STRGSRC(value)            (ADC_ADCCON1_STRGSRC_Msk & ((value) << ADC_ADCCON1_STRGSRC_Pos))
#define ADC_ADCCON1_SELRES_Pos                _U_(21)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_SELRES_Msk                (_U_(0x3) << ADC_ADCCON1_SELRES_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_SELRES(value)             (ADC_ADCCON1_SELRES_Msk & ((value) << ADC_ADCCON1_SELRES_Pos))
#define ADC_ADCCON1_FRACT_Pos                 _U_(23)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_FRACT_Msk                 (_U_(0x1) << ADC_ADCCON1_FRACT_Pos)                  /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_FRACT(value)              (ADC_ADCCON1_FRACT_Msk & ((value) << ADC_ADCCON1_FRACT_Pos))
#define ADC_ADCCON1_TRBSLV_Pos                _U_(24)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_TRBSLV_Msk                (_U_(0x7) << ADC_ADCCON1_TRBSLV_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_TRBSLV(value)             (ADC_ADCCON1_TRBSLV_Msk & ((value) << ADC_ADCCON1_TRBSLV_Pos))
#define ADC_ADCCON1_TRBMST_Pos                _U_(27)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_TRBMST_Msk                (_U_(0x7) << ADC_ADCCON1_TRBMST_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_TRBMST(value)             (ADC_ADCCON1_TRBMST_Msk & ((value) << ADC_ADCCON1_TRBMST_Pos))
#define ADC_ADCCON1_TRBERR_Pos                _U_(30)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_TRBERR_Msk                (_U_(0x1) << ADC_ADCCON1_TRBERR_Pos)                 /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_TRBERR(value)             (ADC_ADCCON1_TRBERR_Msk & ((value) << ADC_ADCCON1_TRBERR_Pos))
#define ADC_ADCCON1_TRBEN_Pos                 _U_(31)                                              /**< (ADC_ADCCON1)  Position */
#define ADC_ADCCON1_TRBEN_Msk                 (_U_(0x1) << ADC_ADCCON1_TRBEN_Pos)                  /**< (ADC_ADCCON1)  Mask */
#define ADC_ADCCON1_TRBEN(value)              (ADC_ADCCON1_TRBEN_Msk & ((value) << ADC_ADCCON1_TRBEN_Pos))
#define ADC_ADCCON1_Msk                       _U_(0xFFFFE77F)                                      /**< (ADC_ADCCON1) Register Mask  */


/* -------- ADC_ADCCON2 : (ADC Offset: 0x10) (R/W 32)  -------- */
#define ADC_ADCCON2_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCCON2)   Reset Value */

#define ADC_ADCCON2_ADCDIV_Pos                _U_(0)                                               /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_ADCDIV_Msk                (_U_(0x7F) << ADC_ADCCON2_ADCDIV_Pos)                /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_ADCDIV(value)             (ADC_ADCCON2_ADCDIV_Msk & ((value) << ADC_ADCCON2_ADCDIV_Pos))
#define ADC_ADCCON2_ADCEIS_Pos                _U_(8)                                               /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_ADCEIS_Msk                (_U_(0x7) << ADC_ADCCON2_ADCEIS_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_ADCEIS(value)             (ADC_ADCCON2_ADCEIS_Msk & ((value) << ADC_ADCCON2_ADCEIS_Pos))
#define ADC_ADCCON2_ENXCNVRT_Pos              _U_(11)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_ENXCNVRT_Msk              (_U_(0x1) << ADC_ADCCON2_ENXCNVRT_Pos)               /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_ENXCNVRT(value)           (ADC_ADCCON2_ENXCNVRT_Msk & ((value) << ADC_ADCCON2_ENXCNVRT_Pos))
#define ADC_ADCCON2_ADCEIOVR_Pos              _U_(12)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_ADCEIOVR_Msk              (_U_(0x1) << ADC_ADCCON2_ADCEIOVR_Pos)               /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_ADCEIOVR(value)           (ADC_ADCCON2_ADCEIOVR_Msk & ((value) << ADC_ADCCON2_ADCEIOVR_Pos))
#define ADC_ADCCON2_EOSIEN_Pos                _U_(13)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_EOSIEN_Msk                (_U_(0x1) << ADC_ADCCON2_EOSIEN_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_EOSIEN(value)             (ADC_ADCCON2_EOSIEN_Msk & ((value) << ADC_ADCCON2_EOSIEN_Pos))
#define ADC_ADCCON2_REFFLTIEN_Pos             _U_(14)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_REFFLTIEN_Msk             (_U_(0x1) << ADC_ADCCON2_REFFLTIEN_Pos)              /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_REFFLTIEN(value)          (ADC_ADCCON2_REFFLTIEN_Msk & ((value) << ADC_ADCCON2_REFFLTIEN_Pos))
#define ADC_ADCCON2_BGVRIEN_Pos               _U_(15)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_BGVRIEN_Msk               (_U_(0x1) << ADC_ADCCON2_BGVRIEN_Pos)                /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_BGVRIEN(value)            (ADC_ADCCON2_BGVRIEN_Msk & ((value) << ADC_ADCCON2_BGVRIEN_Pos))
#define ADC_ADCCON2_SAMC_Pos                  _U_(16)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_SAMC_Msk                  (_U_(0x3FF) << ADC_ADCCON2_SAMC_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_SAMC(value)               (ADC_ADCCON2_SAMC_Msk & ((value) << ADC_ADCCON2_SAMC_Pos))
#define ADC_ADCCON2_CVDCPL_Pos                _U_(26)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_CVDCPL_Msk                (_U_(0x7) << ADC_ADCCON2_CVDCPL_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_CVDCPL(value)             (ADC_ADCCON2_CVDCPL_Msk & ((value) << ADC_ADCCON2_CVDCPL_Pos))
#define ADC_ADCCON2_EOSRDY_Pos                _U_(29)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_EOSRDY_Msk                (_U_(0x1) << ADC_ADCCON2_EOSRDY_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_EOSRDY(value)             (ADC_ADCCON2_EOSRDY_Msk & ((value) << ADC_ADCCON2_EOSRDY_Pos))
#define ADC_ADCCON2_REFFLT_Pos                _U_(30)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_REFFLT_Msk                (_U_(0x1) << ADC_ADCCON2_REFFLT_Pos)                 /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_REFFLT(value)             (ADC_ADCCON2_REFFLT_Msk & ((value) << ADC_ADCCON2_REFFLT_Pos))
#define ADC_ADCCON2_BGVRRDY_Pos               _U_(31)                                              /**< (ADC_ADCCON2)  Position */
#define ADC_ADCCON2_BGVRRDY_Msk               (_U_(0x1) << ADC_ADCCON2_BGVRRDY_Pos)                /**< (ADC_ADCCON2)  Mask */
#define ADC_ADCCON2_BGVRRDY(value)            (ADC_ADCCON2_BGVRRDY_Msk & ((value) << ADC_ADCCON2_BGVRRDY_Pos))
#define ADC_ADCCON2_Msk                       _U_(0xFFFFFF7F)                                      /**< (ADC_ADCCON2) Register Mask  */


/* -------- ADC_ADCCON3 : (ADC Offset: 0x20) (R/W 32)  -------- */
#define ADC_ADCCON3_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCCON3)   Reset Value */

#define ADC_ADCCON3_ADINSEL_Pos               _U_(0)                                               /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_ADINSEL_Msk               (_U_(0x3F) << ADC_ADCCON3_ADINSEL_Pos)               /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_ADINSEL(value)            (ADC_ADCCON3_ADINSEL_Msk & ((value) << ADC_ADCCON3_ADINSEL_Pos))
#define ADC_ADCCON3_GSWTRG_Pos                _U_(6)                                               /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_GSWTRG_Msk                (_U_(0x1) << ADC_ADCCON3_GSWTRG_Pos)                 /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_GSWTRG(value)             (ADC_ADCCON3_GSWTRG_Msk & ((value) << ADC_ADCCON3_GSWTRG_Pos))
#define ADC_ADCCON3_GLSWTRG_Pos               _U_(7)                                               /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_GLSWTRG_Msk               (_U_(0x1) << ADC_ADCCON3_GLSWTRG_Pos)                /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_GLSWTRG(value)            (ADC_ADCCON3_GLSWTRG_Msk & ((value) << ADC_ADCCON3_GLSWTRG_Pos))
#define ADC_ADCCON3_RQCNVRT_Pos               _U_(8)                                               /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_RQCNVRT_Msk               (_U_(0x1) << ADC_ADCCON3_RQCNVRT_Pos)                /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_RQCNVRT(value)            (ADC_ADCCON3_RQCNVRT_Msk & ((value) << ADC_ADCCON3_RQCNVRT_Pos))
#define ADC_ADCCON3_SAMP_Pos                  _U_(9)                                               /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_SAMP_Msk                  (_U_(0x1) << ADC_ADCCON3_SAMP_Pos)                   /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_SAMP(value)               (ADC_ADCCON3_SAMP_Msk & ((value) << ADC_ADCCON3_SAMP_Pos))
#define ADC_ADCCON3_UPDRDY_Pos                _U_(10)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_UPDRDY_Msk                (_U_(0x1) << ADC_ADCCON3_UPDRDY_Pos)                 /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_UPDRDY(value)             (ADC_ADCCON3_UPDRDY_Msk & ((value) << ADC_ADCCON3_UPDRDY_Pos))
#define ADC_ADCCON3_UPDIEN_Pos                _U_(11)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_UPDIEN_Msk                (_U_(0x1) << ADC_ADCCON3_UPDIEN_Pos)                 /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_UPDIEN(value)             (ADC_ADCCON3_UPDIEN_Msk & ((value) << ADC_ADCCON3_UPDIEN_Pos))
#define ADC_ADCCON3_TRGSUSP_Pos               _U_(12)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_TRGSUSP_Msk               (_U_(0x1) << ADC_ADCCON3_TRGSUSP_Pos)                /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_TRGSUSP(value)            (ADC_ADCCON3_TRGSUSP_Msk & ((value) << ADC_ADCCON3_TRGSUSP_Pos))
#define ADC_ADCCON3_VREFSEL_Pos               _U_(13)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_VREFSEL_Msk               (_U_(0x7) << ADC_ADCCON3_VREFSEL_Pos)                /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_VREFSEL(value)            (ADC_ADCCON3_VREFSEL_Msk & ((value) << ADC_ADCCON3_VREFSEL_Pos))
#define ADC_ADCCON3_CHN_EN_SHR_Pos            _U_(23)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_CHN_EN_SHR_Msk            (_U_(0x1) << ADC_ADCCON3_CHN_EN_SHR_Pos)             /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_CHN_EN_SHR(value)         (ADC_ADCCON3_CHN_EN_SHR_Msk & ((value) << ADC_ADCCON3_CHN_EN_SHR_Pos))
#define ADC_ADCCON3_CONCLKDIV_Pos             _U_(24)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_CONCLKDIV_Msk             (_U_(0x3F) << ADC_ADCCON3_CONCLKDIV_Pos)             /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_CONCLKDIV(value)          (ADC_ADCCON3_CONCLKDIV_Msk & ((value) << ADC_ADCCON3_CONCLKDIV_Pos))
#define ADC_ADCCON3_ADCSEL_Pos                _U_(30)                                              /**< (ADC_ADCCON3)  Position */
#define ADC_ADCCON3_ADCSEL_Msk                (_U_(0x3) << ADC_ADCCON3_ADCSEL_Pos)                 /**< (ADC_ADCCON3)  Mask */
#define ADC_ADCCON3_ADCSEL(value)             (ADC_ADCCON3_ADCSEL_Msk & ((value) << ADC_ADCCON3_ADCSEL_Pos))
#define ADC_ADCCON3_Msk                       _U_(0xFF80FFFF)                                      /**< (ADC_ADCCON3) Register Mask  */


/* -------- ADC_ADTFCC : (ADC Offset: 0x30) (R/W 32)  -------- */
#define ADC_ADTFCC_RESETVALUE                 _U_(0x00)                                            /**<  (ADC_ADTFCC)   Reset Value */

#define ADC_ADTFCC_SSAMPEN0_Pos               _U_(0)                                               /**< (ADC_ADTFCC)  Position */
#define ADC_ADTFCC_SSAMPEN0_Msk               (_U_(0x1) << ADC_ADTFCC_SSAMPEN0_Pos)                /**< (ADC_ADTFCC)  Mask */
#define ADC_ADTFCC_SSAMPEN0(value)            (ADC_ADTFCC_SSAMPEN0_Msk & ((value) << ADC_ADTFCC_SSAMPEN0_Pos))
#define ADC_ADTFCC_STRGEN0_Pos                _U_(8)                                               /**< (ADC_ADTFCC)  Position */
#define ADC_ADTFCC_STRGEN0_Msk                (_U_(0x1) << ADC_ADTFCC_STRGEN0_Pos)                 /**< (ADC_ADTFCC)  Mask */
#define ADC_ADTFCC_STRGEN0(value)             (ADC_ADTFCC_STRGEN0_Msk & ((value) << ADC_ADTFCC_STRGEN0_Pos))
#define ADC_ADTFCC_SH0ALT_Pos                 _U_(16)                                              /**< (ADC_ADTFCC)  Position */
#define ADC_ADTFCC_SH0ALT_Msk                 (_U_(0x3) << ADC_ADTFCC_SH0ALT_Pos)                  /**< (ADC_ADTFCC)  Mask */
#define ADC_ADTFCC_SH0ALT(value)              (ADC_ADTFCC_SH0ALT_Msk & ((value) << ADC_ADTFCC_SH0ALT_Pos))
#define ADC_ADTFCC_Msk                        _U_(0x00030101)                                      /**< (ADC_ADTFCC) Register Mask  */

#define ADC_ADTFCC_SSAMPEN_Pos                _U_(0)                                               /**< (ADC_ADTFCC Position)  */
#define ADC_ADTFCC_SSAMPEN_Msk                (_U_(0x1) << ADC_ADTFCC_SSAMPEN_Pos)                 /**< (ADC_ADTFCC Mask) SSAMPEN */
#define ADC_ADTFCC_SSAMPEN(value)             (ADC_ADTFCC_SSAMPEN_Msk & ((value) << ADC_ADTFCC_SSAMPEN_Pos)) 
#define ADC_ADTFCC_STRGEN_Pos                 _U_(8)                                               /**< (ADC_ADTFCC Position)  */
#define ADC_ADTFCC_STRGEN_Msk                 (_U_(0x1) << ADC_ADTFCC_STRGEN_Pos)                  /**< (ADC_ADTFCC Mask) STRGEN */
#define ADC_ADTFCC_STRGEN(value)              (ADC_ADTFCC_STRGEN_Msk & ((value) << ADC_ADTFCC_STRGEN_Pos)) 

/* -------- ADC_ADIMOD1 : (ADC Offset: 0x40) (R/W 32)  -------- */
#define ADC_ADIMOD1_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADIMOD1)   Reset Value */

#define ADC_ADIMOD1_SIGN0_Pos                 _U_(0)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN0_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN0_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN0(value)              (ADC_ADIMOD1_SIGN0_Msk & ((value) << ADC_ADIMOD1_SIGN0_Pos))
#define ADC_ADIMOD1_DIFF0_Pos                 _U_(1)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF0_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF0_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF0(value)              (ADC_ADIMOD1_DIFF0_Msk & ((value) << ADC_ADIMOD1_DIFF0_Pos))
#define ADC_ADIMOD1_SIGN1_Pos                 _U_(2)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN1_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN1_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN1(value)              (ADC_ADIMOD1_SIGN1_Msk & ((value) << ADC_ADIMOD1_SIGN1_Pos))
#define ADC_ADIMOD1_DIFF1_Pos                 _U_(3)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF1_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF1_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF1(value)              (ADC_ADIMOD1_DIFF1_Msk & ((value) << ADC_ADIMOD1_DIFF1_Pos))
#define ADC_ADIMOD1_SIGN2_Pos                 _U_(4)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN2_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN2_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN2(value)              (ADC_ADIMOD1_SIGN2_Msk & ((value) << ADC_ADIMOD1_SIGN2_Pos))
#define ADC_ADIMOD1_DIFF2_Pos                 _U_(5)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF2_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF2_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF2(value)              (ADC_ADIMOD1_DIFF2_Msk & ((value) << ADC_ADIMOD1_DIFF2_Pos))
#define ADC_ADIMOD1_SIGN3_Pos                 _U_(6)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN3_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN3_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN3(value)              (ADC_ADIMOD1_SIGN3_Msk & ((value) << ADC_ADIMOD1_SIGN3_Pos))
#define ADC_ADIMOD1_DIFF3_Pos                 _U_(7)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF3_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF3_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF3(value)              (ADC_ADIMOD1_DIFF3_Msk & ((value) << ADC_ADIMOD1_DIFF3_Pos))
#define ADC_ADIMOD1_SIGN4_Pos                 _U_(8)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN4_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN4_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN4(value)              (ADC_ADIMOD1_SIGN4_Msk & ((value) << ADC_ADIMOD1_SIGN4_Pos))
#define ADC_ADIMOD1_DIFF4_Pos                 _U_(9)                                               /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF4_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF4_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF4(value)              (ADC_ADIMOD1_DIFF4_Msk & ((value) << ADC_ADIMOD1_DIFF4_Pos))
#define ADC_ADIMOD1_SIGN5_Pos                 _U_(10)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN5_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN5_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN5(value)              (ADC_ADIMOD1_SIGN5_Msk & ((value) << ADC_ADIMOD1_SIGN5_Pos))
#define ADC_ADIMOD1_DIFF5_Pos                 _U_(11)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF5_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF5_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF5(value)              (ADC_ADIMOD1_DIFF5_Msk & ((value) << ADC_ADIMOD1_DIFF5_Pos))
#define ADC_ADIMOD1_SIGN6_Pos                 _U_(12)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN6_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN6_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN6(value)              (ADC_ADIMOD1_SIGN6_Msk & ((value) << ADC_ADIMOD1_SIGN6_Pos))
#define ADC_ADIMOD1_DIFF6_Pos                 _U_(13)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF6_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF6_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF6(value)              (ADC_ADIMOD1_DIFF6_Msk & ((value) << ADC_ADIMOD1_DIFF6_Pos))
#define ADC_ADIMOD1_SIGN7_Pos                 _U_(14)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN7_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN7_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN7(value)              (ADC_ADIMOD1_SIGN7_Msk & ((value) << ADC_ADIMOD1_SIGN7_Pos))
#define ADC_ADIMOD1_DIFF7_Pos                 _U_(15)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF7_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF7_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF7(value)              (ADC_ADIMOD1_DIFF7_Msk & ((value) << ADC_ADIMOD1_DIFF7_Pos))
#define ADC_ADIMOD1_SIGN8_Pos                 _U_(16)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_SIGN8_Msk                 (_U_(0x1) << ADC_ADIMOD1_SIGN8_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_SIGN8(value)              (ADC_ADIMOD1_SIGN8_Msk & ((value) << ADC_ADIMOD1_SIGN8_Pos))
#define ADC_ADIMOD1_DIFF8_Pos                 _U_(17)                                              /**< (ADC_ADIMOD1)  Position */
#define ADC_ADIMOD1_DIFF8_Msk                 (_U_(0x1) << ADC_ADIMOD1_DIFF8_Pos)                  /**< (ADC_ADIMOD1)  Mask */
#define ADC_ADIMOD1_DIFF8(value)              (ADC_ADIMOD1_DIFF8_Msk & ((value) << ADC_ADIMOD1_DIFF8_Pos))
#define ADC_ADIMOD1_Msk                       _U_(0x0003FFFF)                                      /**< (ADC_ADIMOD1) Register Mask  */


/* -------- ADC_ADIRQEN1 : (ADC Offset: 0x80) (R/W 32)  -------- */
#define ADC_ADIRQEN1_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADIRQEN1)   Reset Value */

#define ADC_ADIRQEN1_AGIEN1_Pos               _U_(1)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN1_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN1_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN1(value)            (ADC_ADIRQEN1_AGIEN1_Msk & ((value) << ADC_ADIRQEN1_AGIEN1_Pos))
#define ADC_ADIRQEN1_AGIEN2_Pos               _U_(2)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN2_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN2_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN2(value)            (ADC_ADIRQEN1_AGIEN2_Msk & ((value) << ADC_ADIRQEN1_AGIEN2_Pos))
#define ADC_ADIRQEN1_AGIEN3_Pos               _U_(3)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN3_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN3_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN3(value)            (ADC_ADIRQEN1_AGIEN3_Msk & ((value) << ADC_ADIRQEN1_AGIEN3_Pos))
#define ADC_ADIRQEN1_AGIEN4_Pos               _U_(4)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN4_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN4_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN4(value)            (ADC_ADIRQEN1_AGIEN4_Msk & ((value) << ADC_ADIRQEN1_AGIEN4_Pos))
#define ADC_ADIRQEN1_AGIEN5_Pos               _U_(5)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN5_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN5_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN5(value)            (ADC_ADIRQEN1_AGIEN5_Msk & ((value) << ADC_ADIRQEN1_AGIEN5_Pos))
#define ADC_ADIRQEN1_AGIEN6_Pos               _U_(6)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN6_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN6_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN6(value)            (ADC_ADIRQEN1_AGIEN6_Msk & ((value) << ADC_ADIRQEN1_AGIEN6_Pos))
#define ADC_ADIRQEN1_AGIEN7_Pos               _U_(7)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN7_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN7_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN7(value)            (ADC_ADIRQEN1_AGIEN7_Msk & ((value) << ADC_ADIRQEN1_AGIEN7_Pos))
#define ADC_ADIRQEN1_AGIEN8_Pos               _U_(8)                                               /**< (ADC_ADIRQEN1)  Position */
#define ADC_ADIRQEN1_AGIEN8_Msk               (_U_(0x1) << ADC_ADIRQEN1_AGIEN8_Pos)                /**< (ADC_ADIRQEN1)  Mask */
#define ADC_ADIRQEN1_AGIEN8(value)            (ADC_ADIRQEN1_AGIEN8_Msk & ((value) << ADC_ADIRQEN1_AGIEN8_Pos))
#define ADC_ADIRQEN1_Msk                      _U_(0x000001FE)                                      /**< (ADC_ADIRQEN1) Register Mask  */

#define ADC_ADIRQEN1_AGIEN_Pos                _U_(1)                                               /**< (ADC_ADIRQEN1 Position)  */
#define ADC_ADIRQEN1_AGIEN_Msk                (_U_(0xFF) << ADC_ADIRQEN1_AGIEN_Pos)                /**< (ADC_ADIRQEN1 Mask) AGIEN */
#define ADC_ADIRQEN1_AGIEN(value)             (ADC_ADIRQEN1_AGIEN_Msk & ((value) << ADC_ADIRQEN1_AGIEN_Pos)) 

/* -------- ADC_ADCCSS1 : (ADC Offset: 0xA0) (R/W 32)  -------- */
#define ADC_ADCCSS1_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCCSS1)   Reset Value */

#define ADC_ADCCSS1_CSS1_Pos                  _U_(1)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS1_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS1_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS1(value)               (ADC_ADCCSS1_CSS1_Msk & ((value) << ADC_ADCCSS1_CSS1_Pos))
#define ADC_ADCCSS1_CSS2_Pos                  _U_(2)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS2_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS2_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS2(value)               (ADC_ADCCSS1_CSS2_Msk & ((value) << ADC_ADCCSS1_CSS2_Pos))
#define ADC_ADCCSS1_CSS3_Pos                  _U_(3)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS3_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS3_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS3(value)               (ADC_ADCCSS1_CSS3_Msk & ((value) << ADC_ADCCSS1_CSS3_Pos))
#define ADC_ADCCSS1_CSS4_Pos                  _U_(4)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS4_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS4_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS4(value)               (ADC_ADCCSS1_CSS4_Msk & ((value) << ADC_ADCCSS1_CSS4_Pos))
#define ADC_ADCCSS1_CSS5_Pos                  _U_(5)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS5_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS5_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS5(value)               (ADC_ADCCSS1_CSS5_Msk & ((value) << ADC_ADCCSS1_CSS5_Pos))
#define ADC_ADCCSS1_CSS6_Pos                  _U_(6)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS6_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS6_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS6(value)               (ADC_ADCCSS1_CSS6_Msk & ((value) << ADC_ADCCSS1_CSS6_Pos))
#define ADC_ADCCSS1_CSS7_Pos                  _U_(7)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS7_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS7_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS7(value)               (ADC_ADCCSS1_CSS7_Msk & ((value) << ADC_ADCCSS1_CSS7_Pos))
#define ADC_ADCCSS1_CSS8_Pos                  _U_(8)                                               /**< (ADC_ADCCSS1)  Position */
#define ADC_ADCCSS1_CSS8_Msk                  (_U_(0x1) << ADC_ADCCSS1_CSS8_Pos)                   /**< (ADC_ADCCSS1)  Mask */
#define ADC_ADCCSS1_CSS8(value)               (ADC_ADCCSS1_CSS8_Msk & ((value) << ADC_ADCCSS1_CSS8_Pos))
#define ADC_ADCCSS1_Msk                       _U_(0x000001FE)                                      /**< (ADC_ADCCSS1) Register Mask  */

#define ADC_ADCCSS1_CSS_Pos                   _U_(1)                                               /**< (ADC_ADCCSS1 Position)  */
#define ADC_ADCCSS1_CSS_Msk                   (_U_(0xFF) << ADC_ADCCSS1_CSS_Pos)                   /**< (ADC_ADCCSS1 Mask) CSS */
#define ADC_ADCCSS1_CSS(value)                (ADC_ADCCSS1_CSS_Msk & ((value) << ADC_ADCCSS1_CSS_Pos)) 

/* -------- ADC_ADISTAT1 : (ADC Offset: 0xC0) (R/W 32)  -------- */
#define ADC_ADISTAT1_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADISTAT1)   Reset Value */

#define ADC_ADISTAT1_ARDY1_Pos                _U_(1)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY1_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY1_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY1(value)             (ADC_ADISTAT1_ARDY1_Msk & ((value) << ADC_ADISTAT1_ARDY1_Pos))
#define ADC_ADISTAT1_ARDY2_Pos                _U_(2)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY2_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY2_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY2(value)             (ADC_ADISTAT1_ARDY2_Msk & ((value) << ADC_ADISTAT1_ARDY2_Pos))
#define ADC_ADISTAT1_ARDY3_Pos                _U_(3)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY3_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY3_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY3(value)             (ADC_ADISTAT1_ARDY3_Msk & ((value) << ADC_ADISTAT1_ARDY3_Pos))
#define ADC_ADISTAT1_ARDY4_Pos                _U_(4)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY4_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY4_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY4(value)             (ADC_ADISTAT1_ARDY4_Msk & ((value) << ADC_ADISTAT1_ARDY4_Pos))
#define ADC_ADISTAT1_ARDY5_Pos                _U_(5)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY5_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY5_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY5(value)             (ADC_ADISTAT1_ARDY5_Msk & ((value) << ADC_ADISTAT1_ARDY5_Pos))
#define ADC_ADISTAT1_ARDY6_Pos                _U_(6)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY6_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY6_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY6(value)             (ADC_ADISTAT1_ARDY6_Msk & ((value) << ADC_ADISTAT1_ARDY6_Pos))
#define ADC_ADISTAT1_ARDY7_Pos                _U_(7)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY7_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY7_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY7(value)             (ADC_ADISTAT1_ARDY7_Msk & ((value) << ADC_ADISTAT1_ARDY7_Pos))
#define ADC_ADISTAT1_ARDY8_Pos                _U_(8)                                               /**< (ADC_ADISTAT1)  Position */
#define ADC_ADISTAT1_ARDY8_Msk                (_U_(0x1) << ADC_ADISTAT1_ARDY8_Pos)                 /**< (ADC_ADISTAT1)  Mask */
#define ADC_ADISTAT1_ARDY8(value)             (ADC_ADISTAT1_ARDY8_Msk & ((value) << ADC_ADISTAT1_ARDY8_Pos))
#define ADC_ADISTAT1_Msk                      _U_(0x000001FE)                                      /**< (ADC_ADISTAT1) Register Mask  */

#define ADC_ADISTAT1_ARDY_Pos                 _U_(1)                                               /**< (ADC_ADISTAT1 Position)  */
#define ADC_ADISTAT1_ARDY_Msk                 (_U_(0xFF) << ADC_ADISTAT1_ARDY_Pos)                 /**< (ADC_ADISTAT1 Mask) ARDY */
#define ADC_ADISTAT1_ARDY(value)              (ADC_ADISTAT1_ARDY_Msk & ((value) << ADC_ADISTAT1_ARDY_Pos)) 

/* -------- ADC_ADCMPEN0 : (ADC Offset: 0xE0) (R/W 32)  -------- */
#define ADC_ADCMPEN0_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCMPEN0)   Reset Value */

#define ADC_ADCMPEN0_CMPE1_Pos                _U_(1)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE1_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE1_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE1(value)             (ADC_ADCMPEN0_CMPE1_Msk & ((value) << ADC_ADCMPEN0_CMPE1_Pos))
#define ADC_ADCMPEN0_CMPE2_Pos                _U_(2)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE2_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE2_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE2(value)             (ADC_ADCMPEN0_CMPE2_Msk & ((value) << ADC_ADCMPEN0_CMPE2_Pos))
#define ADC_ADCMPEN0_CMPE3_Pos                _U_(3)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE3_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE3_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE3(value)             (ADC_ADCMPEN0_CMPE3_Msk & ((value) << ADC_ADCMPEN0_CMPE3_Pos))
#define ADC_ADCMPEN0_CMPE4_Pos                _U_(4)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE4_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE4_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE4(value)             (ADC_ADCMPEN0_CMPE4_Msk & ((value) << ADC_ADCMPEN0_CMPE4_Pos))
#define ADC_ADCMPEN0_CMPE5_Pos                _U_(5)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE5_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE5_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE5(value)             (ADC_ADCMPEN0_CMPE5_Msk & ((value) << ADC_ADCMPEN0_CMPE5_Pos))
#define ADC_ADCMPEN0_CMPE6_Pos                _U_(6)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE6_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE6_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE6(value)             (ADC_ADCMPEN0_CMPE6_Msk & ((value) << ADC_ADCMPEN0_CMPE6_Pos))
#define ADC_ADCMPEN0_CMPE7_Pos                _U_(7)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE7_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE7_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE7(value)             (ADC_ADCMPEN0_CMPE7_Msk & ((value) << ADC_ADCMPEN0_CMPE7_Pos))
#define ADC_ADCMPEN0_CMPE8_Pos                _U_(8)                                               /**< (ADC_ADCMPEN0)  Position */
#define ADC_ADCMPEN0_CMPE8_Msk                (_U_(0x1) << ADC_ADCMPEN0_CMPE8_Pos)                 /**< (ADC_ADCMPEN0)  Mask */
#define ADC_ADCMPEN0_CMPE8(value)             (ADC_ADCMPEN0_CMPE8_Msk & ((value) << ADC_ADCMPEN0_CMPE8_Pos))
#define ADC_ADCMPEN0_Msk                      _U_(0x000001FE)                                      /**< (ADC_ADCMPEN0) Register Mask  */

#define ADC_ADCMPEN0_CMPE_Pos                 _U_(1)                                               /**< (ADC_ADCMPEN0 Position)  */
#define ADC_ADCMPEN0_CMPE_Msk                 (_U_(0xFF) << ADC_ADCMPEN0_CMPE_Pos)                 /**< (ADC_ADCMPEN0 Mask) CMPE */
#define ADC_ADCMPEN0_CMPE(value)              (ADC_ADCMPEN0_CMPE_Msk & ((value) << ADC_ADCMPEN0_CMPE_Pos)) 

/* -------- ADC_ADCMP0 : (ADC Offset: 0xF0) (R/W 32)  -------- */
#define ADC_ADCMP0_RESETVALUE                 _U_(0x00)                                            /**<  (ADC_ADCMP0)   Reset Value */

#define ADC_ADCMP0_ADCMPLO_Pos                _U_(0)                                               /**< (ADC_ADCMP0)  Position */
#define ADC_ADCMP0_ADCMPLO_Msk                (_U_(0xFFFF) << ADC_ADCMP0_ADCMPLO_Pos)              /**< (ADC_ADCMP0)  Mask */
#define ADC_ADCMP0_ADCMPLO(value)             (ADC_ADCMP0_ADCMPLO_Msk & ((value) << ADC_ADCMP0_ADCMPLO_Pos))
#define ADC_ADCMP0_ADCMPHI_Pos                _U_(16)                                              /**< (ADC_ADCMP0)  Position */
#define ADC_ADCMP0_ADCMPHI_Msk                (_U_(0xFFFF) << ADC_ADCMP0_ADCMPHI_Pos)              /**< (ADC_ADCMP0)  Mask */
#define ADC_ADCMP0_ADCMPHI(value)             (ADC_ADCMP0_ADCMPHI_Msk & ((value) << ADC_ADCMP0_ADCMPHI_Pos))
#define ADC_ADCMP0_Msk                        _U_(0xFFFFFFFF)                                      /**< (ADC_ADCMP0) Register Mask  */


/* -------- ADC_ADCMPEN1 : (ADC Offset: 0x100) (R/W 32)  -------- */
#define ADC_ADCMPEN1_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCMPEN1)   Reset Value */

#define ADC_ADCMPEN1_CMPE1_Pos                _U_(1)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE1_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE1_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE1(value)             (ADC_ADCMPEN1_CMPE1_Msk & ((value) << ADC_ADCMPEN1_CMPE1_Pos))
#define ADC_ADCMPEN1_CMPE2_Pos                _U_(2)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE2_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE2_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE2(value)             (ADC_ADCMPEN1_CMPE2_Msk & ((value) << ADC_ADCMPEN1_CMPE2_Pos))
#define ADC_ADCMPEN1_CMPE3_Pos                _U_(3)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE3_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE3_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE3(value)             (ADC_ADCMPEN1_CMPE3_Msk & ((value) << ADC_ADCMPEN1_CMPE3_Pos))
#define ADC_ADCMPEN1_CMPE4_Pos                _U_(4)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE4_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE4_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE4(value)             (ADC_ADCMPEN1_CMPE4_Msk & ((value) << ADC_ADCMPEN1_CMPE4_Pos))
#define ADC_ADCMPEN1_CMPE5_Pos                _U_(5)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE5_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE5_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE5(value)             (ADC_ADCMPEN1_CMPE5_Msk & ((value) << ADC_ADCMPEN1_CMPE5_Pos))
#define ADC_ADCMPEN1_CMPE6_Pos                _U_(6)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE6_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE6_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE6(value)             (ADC_ADCMPEN1_CMPE6_Msk & ((value) << ADC_ADCMPEN1_CMPE6_Pos))
#define ADC_ADCMPEN1_CMPE7_Pos                _U_(7)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE7_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE7_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE7(value)             (ADC_ADCMPEN1_CMPE7_Msk & ((value) << ADC_ADCMPEN1_CMPE7_Pos))
#define ADC_ADCMPEN1_CMPE8_Pos                _U_(8)                                               /**< (ADC_ADCMPEN1)  Position */
#define ADC_ADCMPEN1_CMPE8_Msk                (_U_(0x1) << ADC_ADCMPEN1_CMPE8_Pos)                 /**< (ADC_ADCMPEN1)  Mask */
#define ADC_ADCMPEN1_CMPE8(value)             (ADC_ADCMPEN1_CMPE8_Msk & ((value) << ADC_ADCMPEN1_CMPE8_Pos))
#define ADC_ADCMPEN1_Msk                      _U_(0x000001FE)                                      /**< (ADC_ADCMPEN1) Register Mask  */

#define ADC_ADCMPEN1_CMPE_Pos                 _U_(1)                                               /**< (ADC_ADCMPEN1 Position)  */
#define ADC_ADCMPEN1_CMPE_Msk                 (_U_(0xFF) << ADC_ADCMPEN1_CMPE_Pos)                 /**< (ADC_ADCMPEN1 Mask) CMPE */
#define ADC_ADCMPEN1_CMPE(value)              (ADC_ADCMPEN1_CMPE_Msk & ((value) << ADC_ADCMPEN1_CMPE_Pos)) 

/* -------- ADC_ADCMP1 : (ADC Offset: 0x110) (R/W 32)  -------- */
#define ADC_ADCMP1_RESETVALUE                 _U_(0x00)                                            /**<  (ADC_ADCMP1)   Reset Value */

#define ADC_ADCMP1_ADCMPLO_Pos                _U_(0)                                               /**< (ADC_ADCMP1)  Position */
#define ADC_ADCMP1_ADCMPLO_Msk                (_U_(0xFFFF) << ADC_ADCMP1_ADCMPLO_Pos)              /**< (ADC_ADCMP1)  Mask */
#define ADC_ADCMP1_ADCMPLO(value)             (ADC_ADCMP1_ADCMPLO_Msk & ((value) << ADC_ADCMP1_ADCMPLO_Pos))
#define ADC_ADCMP1_ADCMPHI_Pos                _U_(16)                                              /**< (ADC_ADCMP1)  Position */
#define ADC_ADCMP1_ADCMPHI_Msk                (_U_(0xFFFF) << ADC_ADCMP1_ADCMPHI_Pos)              /**< (ADC_ADCMP1)  Mask */
#define ADC_ADCMP1_ADCMPHI(value)             (ADC_ADCMP1_ADCMPHI_Msk & ((value) << ADC_ADCMP1_ADCMPHI_Pos))
#define ADC_ADCMP1_Msk                        _U_(0xFFFFFFFF)                                      /**< (ADC_ADCMP1) Register Mask  */


/* -------- ADC_ADFLTR0 : (ADC Offset: 0x1A0) (R/W 32)  -------- */
#define ADC_ADFLTR0_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADFLTR0)   Reset Value */

#define ADC_ADFLTR0_FLTRDATA_Pos              _U_(0)                                               /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_FLTRDATA_Msk              (_U_(0xFFFF) << ADC_ADFLTR0_FLTRDATA_Pos)            /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_FLTRDATA(value)           (ADC_ADFLTR0_FLTRDATA_Msk & ((value) << ADC_ADFLTR0_FLTRDATA_Pos))
#define ADC_ADFLTR0_CHNLID_Pos                _U_(16)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_CHNLID_Msk                (_U_(0x1F) << ADC_ADFLTR0_CHNLID_Pos)                /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_CHNLID(value)             (ADC_ADFLTR0_CHNLID_Msk & ((value) << ADC_ADFLTR0_CHNLID_Pos))
#define ADC_ADFLTR0_AFRDY_Pos                 _U_(24)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_AFRDY_Msk                 (_U_(0x1) << ADC_ADFLTR0_AFRDY_Pos)                  /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_AFRDY(value)              (ADC_ADFLTR0_AFRDY_Msk & ((value) << ADC_ADFLTR0_AFRDY_Pos))
#define ADC_ADFLTR0_AFGIEN_Pos                _U_(25)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_AFGIEN_Msk                (_U_(0x1) << ADC_ADFLTR0_AFGIEN_Pos)                 /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_AFGIEN(value)             (ADC_ADFLTR0_AFGIEN_Msk & ((value) << ADC_ADFLTR0_AFGIEN_Pos))
#define ADC_ADFLTR0_OVRSAM_Pos                _U_(26)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_OVRSAM_Msk                (_U_(0x7) << ADC_ADFLTR0_OVRSAM_Pos)                 /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_OVRSAM(value)             (ADC_ADFLTR0_OVRSAM_Msk & ((value) << ADC_ADFLTR0_OVRSAM_Pos))
#define ADC_ADFLTR0_DFMODE_Pos                _U_(29)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_DFMODE_Msk                (_U_(0x1) << ADC_ADFLTR0_DFMODE_Pos)                 /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_DFMODE(value)             (ADC_ADFLTR0_DFMODE_Msk & ((value) << ADC_ADFLTR0_DFMODE_Pos))
#define ADC_ADFLTR0_DATA16EN_Pos              _U_(30)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_DATA16EN_Msk              (_U_(0x1) << ADC_ADFLTR0_DATA16EN_Pos)               /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_DATA16EN(value)           (ADC_ADFLTR0_DATA16EN_Msk & ((value) << ADC_ADFLTR0_DATA16EN_Pos))
#define ADC_ADFLTR0_AFEN_Pos                  _U_(31)                                              /**< (ADC_ADFLTR0)  Position */
#define ADC_ADFLTR0_AFEN_Msk                  (_U_(0x1) << ADC_ADFLTR0_AFEN_Pos)                   /**< (ADC_ADFLTR0)  Mask */
#define ADC_ADFLTR0_AFEN(value)               (ADC_ADFLTR0_AFEN_Msk & ((value) << ADC_ADFLTR0_AFEN_Pos))
#define ADC_ADFLTR0_Msk                       _U_(0xFF1FFFFF)                                      /**< (ADC_ADFLTR0) Register Mask  */


/* -------- ADC_ADFLTR1 : (ADC Offset: 0x1B0) (R/W 32)  -------- */
#define ADC_ADFLTR1_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADFLTR1)   Reset Value */

#define ADC_ADFLTR1_FLTRDATA_Pos              _U_(0)                                               /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_FLTRDATA_Msk              (_U_(0xFFFF) << ADC_ADFLTR1_FLTRDATA_Pos)            /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_FLTRDATA(value)           (ADC_ADFLTR1_FLTRDATA_Msk & ((value) << ADC_ADFLTR1_FLTRDATA_Pos))
#define ADC_ADFLTR1_CHNLID_Pos                _U_(16)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_CHNLID_Msk                (_U_(0x1F) << ADC_ADFLTR1_CHNLID_Pos)                /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_CHNLID(value)             (ADC_ADFLTR1_CHNLID_Msk & ((value) << ADC_ADFLTR1_CHNLID_Pos))
#define ADC_ADFLTR1_AFRDY_Pos                 _U_(24)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_AFRDY_Msk                 (_U_(0x1) << ADC_ADFLTR1_AFRDY_Pos)                  /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_AFRDY(value)              (ADC_ADFLTR1_AFRDY_Msk & ((value) << ADC_ADFLTR1_AFRDY_Pos))
#define ADC_ADFLTR1_AFGIEN_Pos                _U_(25)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_AFGIEN_Msk                (_U_(0x1) << ADC_ADFLTR1_AFGIEN_Pos)                 /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_AFGIEN(value)             (ADC_ADFLTR1_AFGIEN_Msk & ((value) << ADC_ADFLTR1_AFGIEN_Pos))
#define ADC_ADFLTR1_OVRSAM_Pos                _U_(26)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_OVRSAM_Msk                (_U_(0x7) << ADC_ADFLTR1_OVRSAM_Pos)                 /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_OVRSAM(value)             (ADC_ADFLTR1_OVRSAM_Msk & ((value) << ADC_ADFLTR1_OVRSAM_Pos))
#define ADC_ADFLTR1_DFMODE_Pos                _U_(29)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_DFMODE_Msk                (_U_(0x1) << ADC_ADFLTR1_DFMODE_Pos)                 /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_DFMODE(value)             (ADC_ADFLTR1_DFMODE_Msk & ((value) << ADC_ADFLTR1_DFMODE_Pos))
#define ADC_ADFLTR1_DATA16EN_Pos              _U_(30)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_DATA16EN_Msk              (_U_(0x1) << ADC_ADFLTR1_DATA16EN_Pos)               /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_DATA16EN(value)           (ADC_ADFLTR1_DATA16EN_Msk & ((value) << ADC_ADFLTR1_DATA16EN_Pos))
#define ADC_ADFLTR1_AFEN_Pos                  _U_(31)                                              /**< (ADC_ADFLTR1)  Position */
#define ADC_ADFLTR1_AFEN_Msk                  (_U_(0x1) << ADC_ADFLTR1_AFEN_Pos)                   /**< (ADC_ADFLTR1)  Mask */
#define ADC_ADFLTR1_AFEN(value)               (ADC_ADFLTR1_AFEN_Msk & ((value) << ADC_ADFLTR1_AFEN_Pos))
#define ADC_ADFLTR1_Msk                       _U_(0xFF1FFFFF)                                      /**< (ADC_ADFLTR1) Register Mask  */


/* -------- ADC_ADCTRG0 : (ADC Offset: 0x200) (R/W 32)  -------- */
#define ADC_ADCTRG0_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCTRG0)   Reset Value */

#define ADC_ADCTRG0_TRGSRC0_Pos               _U_(0)                                               /**< (ADC_ADCTRG0)  Position */
#define ADC_ADCTRG0_TRGSRC0_Msk               (_U_(0x1F) << ADC_ADCTRG0_TRGSRC0_Pos)               /**< (ADC_ADCTRG0)  Mask */
#define ADC_ADCTRG0_TRGSRC0(value)            (ADC_ADCTRG0_TRGSRC0_Msk & ((value) << ADC_ADCTRG0_TRGSRC0_Pos))
#define ADC_ADCTRG0_TRGSRC1_Pos               _U_(8)                                               /**< (ADC_ADCTRG0)  Position */
#define ADC_ADCTRG0_TRGSRC1_Msk               (_U_(0x1F) << ADC_ADCTRG0_TRGSRC1_Pos)               /**< (ADC_ADCTRG0)  Mask */
#define ADC_ADCTRG0_TRGSRC1(value)            (ADC_ADCTRG0_TRGSRC1_Msk & ((value) << ADC_ADCTRG0_TRGSRC1_Pos))
#define ADC_ADCTRG0_TRGSRC2_Pos               _U_(16)                                              /**< (ADC_ADCTRG0)  Position */
#define ADC_ADCTRG0_TRGSRC2_Msk               (_U_(0x1F) << ADC_ADCTRG0_TRGSRC2_Pos)               /**< (ADC_ADCTRG0)  Mask */
#define ADC_ADCTRG0_TRGSRC2(value)            (ADC_ADCTRG0_TRGSRC2_Msk & ((value) << ADC_ADCTRG0_TRGSRC2_Pos))
#define ADC_ADCTRG0_TRGSRC3_Pos               _U_(24)                                              /**< (ADC_ADCTRG0)  Position */
#define ADC_ADCTRG0_TRGSRC3_Msk               (_U_(0x1F) << ADC_ADCTRG0_TRGSRC3_Pos)               /**< (ADC_ADCTRG0)  Mask */
#define ADC_ADCTRG0_TRGSRC3(value)            (ADC_ADCTRG0_TRGSRC3_Msk & ((value) << ADC_ADCTRG0_TRGSRC3_Pos))
#define ADC_ADCTRG0_Msk                       _U_(0x1F1F1F1F)                                      /**< (ADC_ADCTRG0) Register Mask  */


/* -------- ADC_ADCTRG1 : (ADC Offset: 0x210) (R/W 32)  -------- */
#define ADC_ADCTRG1_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCTRG1)   Reset Value */

#define ADC_ADCTRG1_TRGSRC4_Pos               _U_(0)                                               /**< (ADC_ADCTRG1)  Position */
#define ADC_ADCTRG1_TRGSRC4_Msk               (_U_(0x1F) << ADC_ADCTRG1_TRGSRC4_Pos)               /**< (ADC_ADCTRG1)  Mask */
#define ADC_ADCTRG1_TRGSRC4(value)            (ADC_ADCTRG1_TRGSRC4_Msk & ((value) << ADC_ADCTRG1_TRGSRC4_Pos))
#define ADC_ADCTRG1_TRGSRC5_Pos               _U_(8)                                               /**< (ADC_ADCTRG1)  Position */
#define ADC_ADCTRG1_TRGSRC5_Msk               (_U_(0x1F) << ADC_ADCTRG1_TRGSRC5_Pos)               /**< (ADC_ADCTRG1)  Mask */
#define ADC_ADCTRG1_TRGSRC5(value)            (ADC_ADCTRG1_TRGSRC5_Msk & ((value) << ADC_ADCTRG1_TRGSRC5_Pos))
#define ADC_ADCTRG1_TRGSRC6_Pos               _U_(16)                                              /**< (ADC_ADCTRG1)  Position */
#define ADC_ADCTRG1_TRGSRC6_Msk               (_U_(0x1F) << ADC_ADCTRG1_TRGSRC6_Pos)               /**< (ADC_ADCTRG1)  Mask */
#define ADC_ADCTRG1_TRGSRC6(value)            (ADC_ADCTRG1_TRGSRC6_Msk & ((value) << ADC_ADCTRG1_TRGSRC6_Pos))
#define ADC_ADCTRG1_TRGSRC7_Pos               _U_(24)                                              /**< (ADC_ADCTRG1)  Position */
#define ADC_ADCTRG1_TRGSRC7_Msk               (_U_(0x1F) << ADC_ADCTRG1_TRGSRC7_Pos)               /**< (ADC_ADCTRG1)  Mask */
#define ADC_ADCTRG1_TRGSRC7(value)            (ADC_ADCTRG1_TRGSRC7_Msk & ((value) << ADC_ADCTRG1_TRGSRC7_Pos))
#define ADC_ADCTRG1_Msk                       _U_(0x1F1F1F1F)                                      /**< (ADC_ADCTRG1) Register Mask  */


/* -------- ADC_ADCTRG2 : (ADC Offset: 0x220) (R/W 32)  -------- */
#define ADC_ADCTRG2_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCTRG2)   Reset Value */

#define ADC_ADCTRG2_TRGSRC8_Pos               _U_(0)                                               /**< (ADC_ADCTRG2)  Position */
#define ADC_ADCTRG2_TRGSRC8_Msk               (_U_(0x1F) << ADC_ADCTRG2_TRGSRC8_Pos)               /**< (ADC_ADCTRG2)  Mask */
#define ADC_ADCTRG2_TRGSRC8(value)            (ADC_ADCTRG2_TRGSRC8_Msk & ((value) << ADC_ADCTRG2_TRGSRC8_Pos))
#define ADC_ADCTRG2_Msk                       _U_(0x0000001F)                                      /**< (ADC_ADCTRG2) Register Mask  */


/* -------- ADC_ADCCMPCON0 : (ADC Offset: 0x280) (R/W 32)  -------- */
#define ADC_ADCCMPCON0_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCMPCON0)   Reset Value */

#define ADC_ADCCMPCON0_IELOLO_Pos             _U_(0)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_IELOLO_Msk             (_U_(0x1) << ADC_ADCCMPCON0_IELOLO_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_IELOLO(value)          (ADC_ADCCMPCON0_IELOLO_Msk & ((value) << ADC_ADCCMPCON0_IELOLO_Pos))
#define ADC_ADCCMPCON0_IELOHI_Pos             _U_(1)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_IELOHI_Msk             (_U_(0x1) << ADC_ADCCMPCON0_IELOHI_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_IELOHI(value)          (ADC_ADCCMPCON0_IELOHI_Msk & ((value) << ADC_ADCCMPCON0_IELOHI_Pos))
#define ADC_ADCCMPCON0_IEHILO_Pos             _U_(2)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_IEHILO_Msk             (_U_(0x1) << ADC_ADCCMPCON0_IEHILO_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_IEHILO(value)          (ADC_ADCCMPCON0_IEHILO_Msk & ((value) << ADC_ADCCMPCON0_IEHILO_Pos))
#define ADC_ADCCMPCON0_IEHIHI_Pos             _U_(3)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_IEHIHI_Msk             (_U_(0x1) << ADC_ADCCMPCON0_IEHIHI_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_IEHIHI(value)          (ADC_ADCCMPCON0_IEHIHI_Msk & ((value) << ADC_ADCCMPCON0_IEHIHI_Pos))
#define ADC_ADCCMPCON0_IEBTWN_Pos             _U_(4)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_IEBTWN_Msk             (_U_(0x1) << ADC_ADCCMPCON0_IEBTWN_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_IEBTWN(value)          (ADC_ADCCMPCON0_IEBTWN_Msk & ((value) << ADC_ADCCMPCON0_IEBTWN_Pos))
#define ADC_ADCCMPCON0_DCMPED_Pos             _U_(5)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_DCMPED_Msk             (_U_(0x1) << ADC_ADCCMPCON0_DCMPED_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_DCMPED(value)          (ADC_ADCCMPCON0_DCMPED_Msk & ((value) << ADC_ADCCMPCON0_DCMPED_Pos))
#define ADC_ADCCMPCON0_DCMPGIEN_Pos           _U_(6)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_DCMPGIEN_Msk           (_U_(0x1) << ADC_ADCCMPCON0_DCMPGIEN_Pos)            /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_DCMPGIEN(value)        (ADC_ADCCMPCON0_DCMPGIEN_Msk & ((value) << ADC_ADCCMPCON0_DCMPGIEN_Pos))
#define ADC_ADCCMPCON0_ENDCMP_Pos             _U_(7)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_ENDCMP_Msk             (_U_(0x1) << ADC_ADCCMPCON0_ENDCMP_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_ENDCMP(value)          (ADC_ADCCMPCON0_ENDCMP_Msk & ((value) << ADC_ADCCMPCON0_ENDCMP_Pos))
#define ADC_ADCCMPCON0_AINID_Pos              _U_(8)                                               /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_AINID_Msk              (_U_(0x3F) << ADC_ADCCMPCON0_AINID_Pos)              /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_AINID(value)           (ADC_ADCCMPCON0_AINID_Msk & ((value) << ADC_ADCCMPCON0_AINID_Pos))
#define ADC_ADCCMPCON0_CVDDATA_Pos            _U_(16)                                              /**< (ADC_ADCCMPCON0)  Position */
#define ADC_ADCCMPCON0_CVDDATA_Msk            (_U_(0xFFFF) << ADC_ADCCMPCON0_CVDDATA_Pos)          /**< (ADC_ADCCMPCON0)  Mask */
#define ADC_ADCCMPCON0_CVDDATA(value)         (ADC_ADCCMPCON0_CVDDATA_Msk & ((value) << ADC_ADCCMPCON0_CVDDATA_Pos))
#define ADC_ADCCMPCON0_Msk                    _U_(0xFFFF3FFF)                                      /**< (ADC_ADCCMPCON0) Register Mask  */


/* -------- ADC_ADCCMPCON1 : (ADC Offset: 0x290) (R/W 32)  -------- */
#define ADC_ADCCMPCON1_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCMPCON1)   Reset Value */

#define ADC_ADCCMPCON1_IELOLO_Pos             _U_(0)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_IELOLO_Msk             (_U_(0x1) << ADC_ADCCMPCON1_IELOLO_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_IELOLO(value)          (ADC_ADCCMPCON1_IELOLO_Msk & ((value) << ADC_ADCCMPCON1_IELOLO_Pos))
#define ADC_ADCCMPCON1_IELOHI_Pos             _U_(1)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_IELOHI_Msk             (_U_(0x1) << ADC_ADCCMPCON1_IELOHI_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_IELOHI(value)          (ADC_ADCCMPCON1_IELOHI_Msk & ((value) << ADC_ADCCMPCON1_IELOHI_Pos))
#define ADC_ADCCMPCON1_IEHILO_Pos             _U_(2)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_IEHILO_Msk             (_U_(0x1) << ADC_ADCCMPCON1_IEHILO_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_IEHILO(value)          (ADC_ADCCMPCON1_IEHILO_Msk & ((value) << ADC_ADCCMPCON1_IEHILO_Pos))
#define ADC_ADCCMPCON1_IEHIHI_Pos             _U_(3)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_IEHIHI_Msk             (_U_(0x1) << ADC_ADCCMPCON1_IEHIHI_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_IEHIHI(value)          (ADC_ADCCMPCON1_IEHIHI_Msk & ((value) << ADC_ADCCMPCON1_IEHIHI_Pos))
#define ADC_ADCCMPCON1_IEBTWN_Pos             _U_(4)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_IEBTWN_Msk             (_U_(0x1) << ADC_ADCCMPCON1_IEBTWN_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_IEBTWN(value)          (ADC_ADCCMPCON1_IEBTWN_Msk & ((value) << ADC_ADCCMPCON1_IEBTWN_Pos))
#define ADC_ADCCMPCON1_DCMPED_Pos             _U_(5)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_DCMPED_Msk             (_U_(0x1) << ADC_ADCCMPCON1_DCMPED_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_DCMPED(value)          (ADC_ADCCMPCON1_DCMPED_Msk & ((value) << ADC_ADCCMPCON1_DCMPED_Pos))
#define ADC_ADCCMPCON1_DCMPGIEN_Pos           _U_(6)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_DCMPGIEN_Msk           (_U_(0x1) << ADC_ADCCMPCON1_DCMPGIEN_Pos)            /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_DCMPGIEN(value)        (ADC_ADCCMPCON1_DCMPGIEN_Msk & ((value) << ADC_ADCCMPCON1_DCMPGIEN_Pos))
#define ADC_ADCCMPCON1_ENDCMP_Pos             _U_(7)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_ENDCMP_Msk             (_U_(0x1) << ADC_ADCCMPCON1_ENDCMP_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_ENDCMP(value)          (ADC_ADCCMPCON1_ENDCMP_Msk & ((value) << ADC_ADCCMPCON1_ENDCMP_Pos))
#define ADC_ADCCMPCON1_AINID_Pos              _U_(8)                                               /**< (ADC_ADCCMPCON1)  Position */
#define ADC_ADCCMPCON1_AINID_Msk              (_U_(0x1F) << ADC_ADCCMPCON1_AINID_Pos)              /**< (ADC_ADCCMPCON1)  Mask */
#define ADC_ADCCMPCON1_AINID(value)           (ADC_ADCCMPCON1_AINID_Msk & ((value) << ADC_ADCCMPCON1_AINID_Pos))
#define ADC_ADCCMPCON1_Msk                    _U_(0x00001FFF)                                      /**< (ADC_ADCCMPCON1) Register Mask  */


/* -------- ADC_ADCFSTAT : (ADC Offset: 0x2E0) (R/W 32)  -------- */
#define ADC_ADCFSTAT_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCFSTAT)   Reset Value */

#define ADC_ADCFSTAT_ADCID_Pos                _U_(0)                                               /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_ADCID_Msk                (_U_(0x7) << ADC_ADCFSTAT_ADCID_Pos)                 /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_ADCID(value)             (ADC_ADCFSTAT_ADCID_Msk & ((value) << ADC_ADCFSTAT_ADCID_Pos))
#define ADC_ADCFSTAT_FSIGN_Pos                _U_(7)                                               /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FSIGN_Msk                (_U_(0x1) << ADC_ADCFSTAT_FSIGN_Pos)                 /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FSIGN(value)             (ADC_ADCFSTAT_FSIGN_Msk & ((value) << ADC_ADCFSTAT_FSIGN_Pos))
#define ADC_ADCFSTAT_FCNT_Pos                 _U_(8)                                               /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FCNT_Msk                 (_U_(0xFF) << ADC_ADCFSTAT_FCNT_Pos)                 /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FCNT(value)              (ADC_ADCFSTAT_FCNT_Msk & ((value) << ADC_ADCFSTAT_FCNT_Pos))
#define ADC_ADCFSTAT_FWROVERR_Pos             _U_(21)                                              /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FWROVERR_Msk             (_U_(0x1) << ADC_ADCFSTAT_FWROVERR_Pos)              /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FWROVERR(value)          (ADC_ADCFSTAT_FWROVERR_Msk & ((value) << ADC_ADCFSTAT_FWROVERR_Pos))
#define ADC_ADCFSTAT_FRDY_Pos                 _U_(22)                                              /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FRDY_Msk                 (_U_(0x1) << ADC_ADCFSTAT_FRDY_Pos)                  /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FRDY(value)              (ADC_ADCFSTAT_FRDY_Msk & ((value) << ADC_ADCFSTAT_FRDY_Pos))
#define ADC_ADCFSTAT_FIEN_Pos                 _U_(23)                                              /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FIEN_Msk                 (_U_(0x1) << ADC_ADCFSTAT_FIEN_Pos)                  /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FIEN(value)              (ADC_ADCFSTAT_FIEN_Msk & ((value) << ADC_ADCFSTAT_FIEN_Pos))
#define ADC_ADCFSTAT_ADC0EN_Pos               _U_(24)                                              /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_ADC0EN_Msk               (_U_(0x1) << ADC_ADCFSTAT_ADC0EN_Pos)                /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_ADC0EN(value)            (ADC_ADCFSTAT_ADC0EN_Msk & ((value) << ADC_ADCFSTAT_ADC0EN_Pos))
#define ADC_ADCFSTAT_FEN_Pos                  _U_(31)                                              /**< (ADC_ADCFSTAT)  Position */
#define ADC_ADCFSTAT_FEN_Msk                  (_U_(0x1) << ADC_ADCFSTAT_FEN_Pos)                   /**< (ADC_ADCFSTAT)  Mask */
#define ADC_ADCFSTAT_FEN(value)               (ADC_ADCFSTAT_FEN_Msk & ((value) << ADC_ADCFSTAT_FEN_Pos))
#define ADC_ADCFSTAT_Msk                      _U_(0x81E0FF87)                                      /**< (ADC_ADCFSTAT) Register Mask  */


/* -------- ADC_ADCFIFO : (ADC Offset: 0x2F0) (R/W 32)  -------- */
#define ADC_ADCFIFO_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCFIFO)   Reset Value */

#define ADC_ADCFIFO_DATA_Pos                  _U_(0)                                               /**< (ADC_ADCFIFO)  Position */
#define ADC_ADCFIFO_DATA_Msk                  (_U_(0xFFFFFFFF) << ADC_ADCFIFO_DATA_Pos)            /**< (ADC_ADCFIFO)  Mask */
#define ADC_ADCFIFO_DATA(value)               (ADC_ADCFIFO_DATA_Msk & ((value) << ADC_ADCFIFO_DATA_Pos))
#define ADC_ADCFIFO_Msk                       _U_(0xFFFFFFFF)                                      /**< (ADC_ADCFIFO) Register Mask  */


/* -------- ADC_ADCBASE : (ADC Offset: 0x300) (R/W 32)  -------- */
#define ADC_ADCBASE_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCBASE)   Reset Value */

#define ADC_ADCBASE_ADCBASE_Pos               _U_(0)                                               /**< (ADC_ADCBASE)  Position */
#define ADC_ADCBASE_ADCBASE_Msk               (_U_(0xFFFF) << ADC_ADCBASE_ADCBASE_Pos)             /**< (ADC_ADCBASE)  Mask */
#define ADC_ADCBASE_ADCBASE(value)            (ADC_ADCBASE_ADCBASE_Msk & ((value) << ADC_ADCBASE_ADCBASE_Pos))
#define ADC_ADCBASE_Msk                       _U_(0x0000FFFF)                                      /**< (ADC_ADCBASE) Register Mask  */


/* -------- ADC_ADCDMAST : (ADC Offset: 0x310) (R/W 32)  -------- */
#define ADC_ADCDMAST_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDMAST)   Reset Value */

#define ADC_ADCDMAST_RAF0_Pos                 _U_(0)                                               /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_RAF0_Msk                 (_U_(0x1) << ADC_ADCDMAST_RAF0_Pos)                  /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_RAF0(value)              (ADC_ADCDMAST_RAF0_Msk & ((value) << ADC_ADCDMAST_RAF0_Pos))
#define ADC_ADCDMAST_RAF0IEN_Pos              _U_(8)                                               /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_RAF0IEN_Msk              (_U_(0x1) << ADC_ADCDMAST_RAF0IEN_Pos)               /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_RAF0IEN(value)           (ADC_ADCDMAST_RAF0IEN_Msk & ((value) << ADC_ADCDMAST_RAF0IEN_Pos))
#define ADC_ADCDMAST_DMACNTEN_Pos             _U_(15)                                              /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_DMACNTEN_Msk             (_U_(0x1) << ADC_ADCDMAST_DMACNTEN_Pos)              /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_DMACNTEN(value)          (ADC_ADCDMAST_DMACNTEN_Msk & ((value) << ADC_ADCDMAST_DMACNTEN_Pos))
#define ADC_ADCDMAST_RBF0_Pos                 _U_(16)                                              /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_RBF0_Msk                 (_U_(0x1) << ADC_ADCDMAST_RBF0_Pos)                  /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_RBF0(value)              (ADC_ADCDMAST_RBF0_Msk & ((value) << ADC_ADCDMAST_RBF0_Pos))
#define ADC_ADCDMAST_WROVRERR_Pos             _U_(23)                                              /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_WROVRERR_Msk             (_U_(0x1) << ADC_ADCDMAST_WROVRERR_Pos)              /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_WROVRERR(value)          (ADC_ADCDMAST_WROVRERR_Msk & ((value) << ADC_ADCDMAST_WROVRERR_Pos))
#define ADC_ADCDMAST_RBF0IEN_Pos              _U_(24)                                              /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_RBF0IEN_Msk              (_U_(0x1) << ADC_ADCDMAST_RBF0IEN_Pos)               /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_RBF0IEN(value)           (ADC_ADCDMAST_RBF0IEN_Msk & ((value) << ADC_ADCDMAST_RBF0IEN_Pos))
#define ADC_ADCDMAST_DMAEN_Pos                _U_(31)                                              /**< (ADC_ADCDMAST)  Position */
#define ADC_ADCDMAST_DMAEN_Msk                (_U_(0x1) << ADC_ADCDMAST_DMAEN_Pos)                 /**< (ADC_ADCDMAST)  Mask */
#define ADC_ADCDMAST_DMAEN(value)             (ADC_ADCDMAST_DMAEN_Msk & ((value) << ADC_ADCDMAST_DMAEN_Pos))
#define ADC_ADCDMAST_Msk                      _U_(0x81818101)                                      /**< (ADC_ADCDMAST) Register Mask  */

#define ADC_ADCDMAST_RAF_Pos                  _U_(0)                                               /**< (ADC_ADCDMAST Position)  */
#define ADC_ADCDMAST_RAF_Msk                  (_U_(0x1) << ADC_ADCDMAST_RAF_Pos)                   /**< (ADC_ADCDMAST Mask) RAF */
#define ADC_ADCDMAST_RAF(value)               (ADC_ADCDMAST_RAF_Msk & ((value) << ADC_ADCDMAST_RAF_Pos)) 
#define ADC_ADCDMAST_RBF_Pos                  _U_(16)                                              /**< (ADC_ADCDMAST Position)  */
#define ADC_ADCDMAST_RBF_Msk                  (_U_(0x1) << ADC_ADCDMAST_RBF_Pos)                   /**< (ADC_ADCDMAST Mask) RBF */
#define ADC_ADCDMAST_RBF(value)               (ADC_ADCDMAST_RBF_Msk & ((value) << ADC_ADCDMAST_RBF_Pos)) 

/* -------- ADC_ADCCNTB : (ADC Offset: 0x320) (R/W 32)  -------- */
#define ADC_ADCCNTB_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCCNTB)   Reset Value */

#define ADC_ADCCNTB_ADCCNTB_Pos               _U_(0)                                               /**< (ADC_ADCCNTB)  Position */
#define ADC_ADCCNTB_ADCCNTB_Msk               (_U_(0xFFFFFFFF) << ADC_ADCCNTB_ADCCNTB_Pos)         /**< (ADC_ADCCNTB)  Mask */
#define ADC_ADCCNTB_ADCCNTB(value)            (ADC_ADCCNTB_ADCCNTB_Msk & ((value) << ADC_ADCCNTB_ADCCNTB_Pos))
#define ADC_ADCCNTB_Msk                       _U_(0xFFFFFFFF)                                      /**< (ADC_ADCCNTB) Register Mask  */


/* -------- ADC_ADCDMAB : (ADC Offset: 0x330) (R/W 32)  -------- */
#define ADC_ADCDMAB_RESETVALUE                _U_(0x00)                                            /**<  (ADC_ADCDMAB)   Reset Value */

#define ADC_ADCDMAB_ADDMAB_Pos                _U_(0)                                               /**< (ADC_ADCDMAB)  Position */
#define ADC_ADCDMAB_ADDMAB_Msk                (_U_(0xFFFFFFFF) << ADC_ADCDMAB_ADDMAB_Pos)          /**< (ADC_ADCDMAB)  Mask */
#define ADC_ADCDMAB_ADDMAB(value)             (ADC_ADCDMAB_ADDMAB_Msk & ((value) << ADC_ADCDMAB_ADDMAB_Pos))
#define ADC_ADCDMAB_Msk                       _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDMAB) Register Mask  */


/* -------- ADC_ADCTRGSNS : (ADC Offset: 0x340) (R/W 32)  -------- */
#define ADC_ADCTRGSNS_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCTRGSNS)   Reset Value */

#define ADC_ADCTRGSNS_LVL0_Pos                _U_(0)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL0_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL0_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL0(value)             (ADC_ADCTRGSNS_LVL0_Msk & ((value) << ADC_ADCTRGSNS_LVL0_Pos))
#define ADC_ADCTRGSNS_LVL1_Pos                _U_(1)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL1_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL1_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL1(value)             (ADC_ADCTRGSNS_LVL1_Msk & ((value) << ADC_ADCTRGSNS_LVL1_Pos))
#define ADC_ADCTRGSNS_LVL2_Pos                _U_(2)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL2_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL2_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL2(value)             (ADC_ADCTRGSNS_LVL2_Msk & ((value) << ADC_ADCTRGSNS_LVL2_Pos))
#define ADC_ADCTRGSNS_LVL3_Pos                _U_(3)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL3_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL3_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL3(value)             (ADC_ADCTRGSNS_LVL3_Msk & ((value) << ADC_ADCTRGSNS_LVL3_Pos))
#define ADC_ADCTRGSNS_LVL4_Pos                _U_(4)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL4_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL4_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL4(value)             (ADC_ADCTRGSNS_LVL4_Msk & ((value) << ADC_ADCTRGSNS_LVL4_Pos))
#define ADC_ADCTRGSNS_LVL5_Pos                _U_(5)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL5_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL5_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL5(value)             (ADC_ADCTRGSNS_LVL5_Msk & ((value) << ADC_ADCTRGSNS_LVL5_Pos))
#define ADC_ADCTRGSNS_LVL6_Pos                _U_(6)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL6_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL6_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL6(value)             (ADC_ADCTRGSNS_LVL6_Msk & ((value) << ADC_ADCTRGSNS_LVL6_Pos))
#define ADC_ADCTRGSNS_LVL7_Pos                _U_(7)                                               /**< (ADC_ADCTRGSNS)  Position */
#define ADC_ADCTRGSNS_LVL7_Msk                (_U_(0x1) << ADC_ADCTRGSNS_LVL7_Pos)                 /**< (ADC_ADCTRGSNS)  Mask */
#define ADC_ADCTRGSNS_LVL7(value)             (ADC_ADCTRGSNS_LVL7_Msk & ((value) << ADC_ADCTRGSNS_LVL7_Pos))
#define ADC_ADCTRGSNS_Msk                     _U_(0x000000FF)                                      /**< (ADC_ADCTRGSNS) Register Mask  */

#define ADC_ADCTRGSNS_LVL_Pos                 _U_(0)                                               /**< (ADC_ADCTRGSNS Position)  */
#define ADC_ADCTRGSNS_LVL_Msk                 (_U_(0xFF) << ADC_ADCTRGSNS_LVL_Pos)                 /**< (ADC_ADCTRGSNS Mask) LVL */
#define ADC_ADCTRGSNS_LVL(value)              (ADC_ADCTRGSNS_LVL_Msk & ((value) << ADC_ADCTRGSNS_LVL_Pos)) 

/* -------- ADC_ADTIM0 : (ADC Offset: 0x350) (R/W 32)  -------- */
#define ADC_ADTIM0_RESETVALUE                 _U_(0x00)                                            /**<  (ADC_ADTIM0)   Reset Value */

#define ADC_ADTIM0_SAMC_Pos                   _U_(0)                                               /**< (ADC_ADTIM0)  Position */
#define ADC_ADTIM0_SAMC_Msk                   (_U_(0x3FF) << ADC_ADTIM0_SAMC_Pos)                  /**< (ADC_ADTIM0)  Mask */
#define ADC_ADTIM0_SAMC(value)                (ADC_ADTIM0_SAMC_Msk & ((value) << ADC_ADTIM0_SAMC_Pos))
#define ADC_ADTIM0_ADCDIV_Pos                 _U_(16)                                              /**< (ADC_ADTIM0)  Position */
#define ADC_ADTIM0_ADCDIV_Msk                 (_U_(0x7F) << ADC_ADTIM0_ADCDIV_Pos)                 /**< (ADC_ADTIM0)  Mask */
#define ADC_ADTIM0_ADCDIV(value)              (ADC_ADTIM0_ADCDIV_Msk & ((value) << ADC_ADTIM0_ADCDIV_Pos))
#define ADC_ADTIM0_BCHEN0_Pos                 _U_(23)                                              /**< (ADC_ADTIM0)  Position */
#define ADC_ADTIM0_BCHEN0_Msk                 (_U_(0x1) << ADC_ADTIM0_BCHEN0_Pos)                  /**< (ADC_ADTIM0)  Mask */
#define ADC_ADTIM0_BCHEN0(value)              (ADC_ADTIM0_BCHEN0_Msk & ((value) << ADC_ADTIM0_BCHEN0_Pos))
#define ADC_ADTIM0_SELRES_Pos                 _U_(24)                                              /**< (ADC_ADTIM0)  Position */
#define ADC_ADTIM0_SELRES_Msk                 (_U_(0x3) << ADC_ADTIM0_SELRES_Pos)                  /**< (ADC_ADTIM0)  Mask */
#define ADC_ADTIM0_SELRES(value)              (ADC_ADTIM0_SELRES_Msk & ((value) << ADC_ADTIM0_SELRES_Pos))
#define ADC_ADTIM0_ADCEIS_Pos                 _U_(26)                                              /**< (ADC_ADTIM0)  Position */
#define ADC_ADTIM0_ADCEIS_Msk                 (_U_(0x7) << ADC_ADTIM0_ADCEIS_Pos)                  /**< (ADC_ADTIM0)  Mask */
#define ADC_ADTIM0_ADCEIS(value)              (ADC_ADTIM0_ADCEIS_Msk & ((value) << ADC_ADTIM0_ADCEIS_Pos))
#define ADC_ADTIM0_Msk                        _U_(0x1FFF03FF)                                      /**< (ADC_ADTIM0) Register Mask  */

#define ADC_ADTIM0_BCHEN_Pos                  _U_(23)                                              /**< (ADC_ADTIM0 Position)  */
#define ADC_ADTIM0_BCHEN_Msk                  (_U_(0x1) << ADC_ADTIM0_BCHEN_Pos)                   /**< (ADC_ADTIM0 Mask) BCHEN */
#define ADC_ADTIM0_BCHEN(value)               (ADC_ADTIM0_BCHEN_Msk & ((value) << ADC_ADTIM0_BCHEN_Pos)) 

/* -------- ADC_ADCEISTAT1 : (ADC Offset: 0x3E0) (R/W 32)  -------- */
#define ADC_ADCEISTAT1_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCEISTAT1)   Reset Value */

#define ADC_ADCEISTAT1_EIRDY0_Pos             _U_(0)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY0_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY0_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY0(value)          (ADC_ADCEISTAT1_EIRDY0_Msk & ((value) << ADC_ADCEISTAT1_EIRDY0_Pos))
#define ADC_ADCEISTAT1_EIRDY1_Pos             _U_(1)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY1_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY1_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY1(value)          (ADC_ADCEISTAT1_EIRDY1_Msk & ((value) << ADC_ADCEISTAT1_EIRDY1_Pos))
#define ADC_ADCEISTAT1_EIRDY2_Pos             _U_(2)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY2_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY2_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY2(value)          (ADC_ADCEISTAT1_EIRDY2_Msk & ((value) << ADC_ADCEISTAT1_EIRDY2_Pos))
#define ADC_ADCEISTAT1_EIRDY3_Pos             _U_(3)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY3_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY3_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY3(value)          (ADC_ADCEISTAT1_EIRDY3_Msk & ((value) << ADC_ADCEISTAT1_EIRDY3_Pos))
#define ADC_ADCEISTAT1_EIRDY4_Pos             _U_(4)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY4_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY4_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY4(value)          (ADC_ADCEISTAT1_EIRDY4_Msk & ((value) << ADC_ADCEISTAT1_EIRDY4_Pos))
#define ADC_ADCEISTAT1_EIRDY5_Pos             _U_(5)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY5_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY5_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY5(value)          (ADC_ADCEISTAT1_EIRDY5_Msk & ((value) << ADC_ADCEISTAT1_EIRDY5_Pos))
#define ADC_ADCEISTAT1_EIRDY6_Pos             _U_(6)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY6_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY6_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY6(value)          (ADC_ADCEISTAT1_EIRDY6_Msk & ((value) << ADC_ADCEISTAT1_EIRDY6_Pos))
#define ADC_ADCEISTAT1_EIRDY7_Pos             _U_(7)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY7_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY7_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY7(value)          (ADC_ADCEISTAT1_EIRDY7_Msk & ((value) << ADC_ADCEISTAT1_EIRDY7_Pos))
#define ADC_ADCEISTAT1_EIRDY8_Pos             _U_(8)                                               /**< (ADC_ADCEISTAT1)  Position */
#define ADC_ADCEISTAT1_EIRDY8_Msk             (_U_(0x1) << ADC_ADCEISTAT1_EIRDY8_Pos)              /**< (ADC_ADCEISTAT1)  Mask */
#define ADC_ADCEISTAT1_EIRDY8(value)          (ADC_ADCEISTAT1_EIRDY8_Msk & ((value) << ADC_ADCEISTAT1_EIRDY8_Pos))
#define ADC_ADCEISTAT1_Msk                    _U_(0x000001FF)                                      /**< (ADC_ADCEISTAT1) Register Mask  */

#define ADC_ADCEISTAT1_EIRDY_Pos              _U_(0)                                               /**< (ADC_ADCEISTAT1 Position)  */
#define ADC_ADCEISTAT1_EIRDY_Msk              (_U_(0x1FF) << ADC_ADCEISTAT1_EIRDY_Pos)             /**< (ADC_ADCEISTAT1 Mask) EIRDY */
#define ADC_ADCEISTAT1_EIRDY(value)           (ADC_ADCEISTAT1_EIRDY_Msk & ((value) << ADC_ADCEISTAT1_EIRDY_Pos)) 

/* -------- ADC_ADCANCON : (ADC Offset: 0x400) (R/W 32)  -------- */
#define ADC_ADCANCON_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCANCON)   Reset Value */

#define ADC_ADCANCON_ANEN0_Pos                _U_(0)                                               /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_ANEN0_Msk                (_U_(0x1) << ADC_ADCANCON_ANEN0_Pos)                 /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_ANEN0(value)             (ADC_ADCANCON_ANEN0_Msk & ((value) << ADC_ADCANCON_ANEN0_Pos))
#define ADC_ADCANCON_ANEN7_Pos                _U_(7)                                               /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_ANEN7_Msk                (_U_(0x1) << ADC_ADCANCON_ANEN7_Pos)                 /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_ANEN7(value)             (ADC_ADCANCON_ANEN7_Msk & ((value) << ADC_ADCANCON_ANEN7_Pos))
#define ADC_ADCANCON_WKRDY0_Pos               _U_(8)                                               /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_WKRDY0_Msk               (_U_(0x1) << ADC_ADCANCON_WKRDY0_Pos)                /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_WKRDY0(value)            (ADC_ADCANCON_WKRDY0_Msk & ((value) << ADC_ADCANCON_WKRDY0_Pos))
#define ADC_ADCANCON_WKRDY7_Pos               _U_(15)                                              /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_WKRDY7_Msk               (_U_(0x1) << ADC_ADCANCON_WKRDY7_Pos)                /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_WKRDY7(value)            (ADC_ADCANCON_WKRDY7_Msk & ((value) << ADC_ADCANCON_WKRDY7_Pos))
#define ADC_ADCANCON_WKIEN0_Pos               _U_(16)                                              /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_WKIEN0_Msk               (_U_(0x1) << ADC_ADCANCON_WKIEN0_Pos)                /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_WKIEN0(value)            (ADC_ADCANCON_WKIEN0_Msk & ((value) << ADC_ADCANCON_WKIEN0_Pos))
#define ADC_ADCANCON_WKIEN7_Pos               _U_(23)                                              /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_WKIEN7_Msk               (_U_(0x1) << ADC_ADCANCON_WKIEN7_Pos)                /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_WKIEN7(value)            (ADC_ADCANCON_WKIEN7_Msk & ((value) << ADC_ADCANCON_WKIEN7_Pos))
#define ADC_ADCANCON_WKUPCLKCNT_Pos           _U_(24)                                              /**< (ADC_ADCANCON)  Position */
#define ADC_ADCANCON_WKUPCLKCNT_Msk           (_U_(0xF) << ADC_ADCANCON_WKUPCLKCNT_Pos)            /**< (ADC_ADCANCON)  Mask */
#define ADC_ADCANCON_WKUPCLKCNT(value)        (ADC_ADCANCON_WKUPCLKCNT_Msk & ((value) << ADC_ADCANCON_WKUPCLKCNT_Pos))
#define ADC_ADCANCON_Msk                      _U_(0x0F818181)                                      /**< (ADC_ADCANCON) Register Mask  */

#define ADC_ADCANCON_ANEN_Pos                 _U_(0)                                               /**< (ADC_ADCANCON Position)  */
#define ADC_ADCANCON_ANEN_Msk                 (_U_(0x3) << ADC_ADCANCON_ANEN_Pos)                  /**< (ADC_ADCANCON Mask) ANEN */
#define ADC_ADCANCON_ANEN(value)              (ADC_ADCANCON_ANEN_Msk & ((value) << ADC_ADCANCON_ANEN_Pos)) 
#define ADC_ADCANCON_WKRDY_Pos                _U_(8)                                               /**< (ADC_ADCANCON Position)  */
#define ADC_ADCANCON_WKRDY_Msk                (_U_(0x3) << ADC_ADCANCON_WKRDY_Pos)                 /**< (ADC_ADCANCON Mask) WKRDY */
#define ADC_ADCANCON_WKRDY(value)             (ADC_ADCANCON_WKRDY_Msk & ((value) << ADC_ADCANCON_WKRDY_Pos)) 
#define ADC_ADCANCON_WKIEN_Pos                _U_(16)                                              /**< (ADC_ADCANCON Position)  */
#define ADC_ADCANCON_WKIEN_Msk                (_U_(0x3) << ADC_ADCANCON_WKIEN_Pos)                 /**< (ADC_ADCANCON Mask) WKIEN */
#define ADC_ADCANCON_WKIEN(value)             (ADC_ADCANCON_WKIEN_Msk & ((value) << ADC_ADCANCON_WKIEN_Pos)) 

/* -------- ADC_ADCFGSHR : (ADC Offset: 0x670) (R/W 32)  -------- */
#define ADC_ADCFGSHR_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCFGSHR)   Reset Value */

#define ADC_ADCFGSHR_ADCFGSHR_Pos             _U_(0)                                               /**< (ADC_ADCFGSHR)  Position */
#define ADC_ADCFGSHR_ADCFGSHR_Msk             (_U_(0xFFFFFFFF) << ADC_ADCFGSHR_ADCFGSHR_Pos)       /**< (ADC_ADCFGSHR)  Mask */
#define ADC_ADCFGSHR_ADCFGSHR(value)          (ADC_ADCFGSHR_ADCFGSHR_Msk & ((value) << ADC_ADCFGSHR_ADCFGSHR_Pos))
#define ADC_ADCFGSHR_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCFGSHR) Register Mask  */


/* -------- ADC_ADCSVCON : (ADC Offset: 0x680) (R/W 32)  -------- */
#define ADC_ADCSVCON_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCSVCON)   Reset Value */

#define ADC_ADCSVCON_SVSEL_Pos                _U_(0)                                               /**< (ADC_ADCSVCON)  Position */
#define ADC_ADCSVCON_SVSEL_Msk                (_U_(0x3F) << ADC_ADCSVCON_SVSEL_Pos)                /**< (ADC_ADCSVCON)  Mask */
#define ADC_ADCSVCON_SVSEL(value)             (ADC_ADCSVCON_SVSEL_Msk & ((value) << ADC_ADCSVCON_SVSEL_Pos))
#define ADC_ADCSVCON_SVCLKEN_Pos              _U_(6)                                               /**< (ADC_ADCSVCON)  Position */
#define ADC_ADCSVCON_SVCLKEN_Msk              (_U_(0x1) << ADC_ADCSVCON_SVCLKEN_Pos)               /**< (ADC_ADCSVCON)  Mask */
#define ADC_ADCSVCON_SVCLKEN(value)           (ADC_ADCSVCON_SVCLKEN_Msk & ((value) << ADC_ADCSVCON_SVCLKEN_Pos))
#define ADC_ADCSVCON_ADSVEN_Pos               _U_(7)                                               /**< (ADC_ADCSVCON)  Position */
#define ADC_ADCSVCON_ADSVEN_Msk               (_U_(0x1) << ADC_ADCSVCON_ADSVEN_Pos)                /**< (ADC_ADCSVCON)  Mask */
#define ADC_ADCSVCON_ADSVEN(value)            (ADC_ADCSVCON_ADSVEN_Msk & ((value) << ADC_ADCSVCON_ADSVEN_Pos))
#define ADC_ADCSVCON_Msk                      _U_(0x000000FF)                                      /**< (ADC_ADCSVCON) Register Mask  */


/* -------- ADC_ADCSYSCFG0 : (ADC Offset: 0x700) (R/W 32)  -------- */
#define ADC_ADCSYSCFG0_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCSYSCFG0)   Reset Value */

#define ADC_ADCSYSCFG0_ADSYSCFG0_Pos          _U_(0)                                               /**< (ADC_ADCSYSCFG0)  Position */
#define ADC_ADCSYSCFG0_ADSYSCFG0_Msk          (_U_(0xFFFFF) << ADC_ADCSYSCFG0_ADSYSCFG0_Pos)       /**< (ADC_ADCSYSCFG0)  Mask */
#define ADC_ADCSYSCFG0_ADSYSCFG0(value)       (ADC_ADCSYSCFG0_ADSYSCFG0_Msk & ((value) << ADC_ADCSYSCFG0_ADSYSCFG0_Pos))
#define ADC_ADCSYSCFG0_Msk                    _U_(0x000FFFFF)                                      /**< (ADC_ADCSYSCFG0) Register Mask  */


/* -------- ADC_ADCDATA1 : (ADC Offset: 0xA10) (R/W 32)  -------- */
#define ADC_ADCDATA1_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA1)   Reset Value */

#define ADC_ADCDATA1_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA1)  Position */
#define ADC_ADCDATA1_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA1_DATA_Pos)           /**< (ADC_ADCDATA1)  Mask */
#define ADC_ADCDATA1_DATA(value)              (ADC_ADCDATA1_DATA_Msk & ((value) << ADC_ADCDATA1_DATA_Pos))
#define ADC_ADCDATA1_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA1) Register Mask  */


/* -------- ADC_ADCDATA2 : (ADC Offset: 0xA20) (R/W 32)  -------- */
#define ADC_ADCDATA2_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA2)   Reset Value */

#define ADC_ADCDATA2_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA2)  Position */
#define ADC_ADCDATA2_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA2_DATA_Pos)           /**< (ADC_ADCDATA2)  Mask */
#define ADC_ADCDATA2_DATA(value)              (ADC_ADCDATA2_DATA_Msk & ((value) << ADC_ADCDATA2_DATA_Pos))
#define ADC_ADCDATA2_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA2) Register Mask  */


/* -------- ADC_ADCDATA3 : (ADC Offset: 0xA30) (R/W 32)  -------- */
#define ADC_ADCDATA3_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA3)   Reset Value */

#define ADC_ADCDATA3_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA3)  Position */
#define ADC_ADCDATA3_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA3_DATA_Pos)           /**< (ADC_ADCDATA3)  Mask */
#define ADC_ADCDATA3_DATA(value)              (ADC_ADCDATA3_DATA_Msk & ((value) << ADC_ADCDATA3_DATA_Pos))
#define ADC_ADCDATA3_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA3) Register Mask  */


/* -------- ADC_ADCDATA4 : (ADC Offset: 0xA40) (R/W 32)  -------- */
#define ADC_ADCDATA4_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA4)   Reset Value */

#define ADC_ADCDATA4_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA4)  Position */
#define ADC_ADCDATA4_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA4_DATA_Pos)           /**< (ADC_ADCDATA4)  Mask */
#define ADC_ADCDATA4_DATA(value)              (ADC_ADCDATA4_DATA_Msk & ((value) << ADC_ADCDATA4_DATA_Pos))
#define ADC_ADCDATA4_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA4) Register Mask  */


/* -------- ADC_ADCDATA5 : (ADC Offset: 0xA50) (R/W 32)  -------- */
#define ADC_ADCDATA5_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA5)   Reset Value */

#define ADC_ADCDATA5_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA5)  Position */
#define ADC_ADCDATA5_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA5_DATA_Pos)           /**< (ADC_ADCDATA5)  Mask */
#define ADC_ADCDATA5_DATA(value)              (ADC_ADCDATA5_DATA_Msk & ((value) << ADC_ADCDATA5_DATA_Pos))
#define ADC_ADCDATA5_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA5) Register Mask  */


/* -------- ADC_ADCDATA6 : (ADC Offset: 0xA60) (R/W 32)  -------- */
#define ADC_ADCDATA6_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA6)   Reset Value */

#define ADC_ADCDATA6_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA6)  Position */
#define ADC_ADCDATA6_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA6_DATA_Pos)           /**< (ADC_ADCDATA6)  Mask */
#define ADC_ADCDATA6_DATA(value)              (ADC_ADCDATA6_DATA_Msk & ((value) << ADC_ADCDATA6_DATA_Pos))
#define ADC_ADCDATA6_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA6) Register Mask  */


/* -------- ADC_ADCDATA7 : (ADC Offset: 0xA70) (R/W 32)  -------- */
#define ADC_ADCDATA7_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA7)   Reset Value */

#define ADC_ADCDATA7_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA7)  Position */
#define ADC_ADCDATA7_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA7_DATA_Pos)           /**< (ADC_ADCDATA7)  Mask */
#define ADC_ADCDATA7_DATA(value)              (ADC_ADCDATA7_DATA_Msk & ((value) << ADC_ADCDATA7_DATA_Pos))
#define ADC_ADCDATA7_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA7) Register Mask  */


/* -------- ADC_ADCDATA8 : (ADC Offset: 0xA80) (R/W 32)  -------- */
#define ADC_ADCDATA8_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA8)   Reset Value */

#define ADC_ADCDATA8_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA8)  Position */
#define ADC_ADCDATA8_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA8_DATA_Pos)           /**< (ADC_ADCDATA8)  Mask */
#define ADC_ADCDATA8_DATA(value)              (ADC_ADCDATA8_DATA_Msk & ((value) << ADC_ADCDATA8_DATA_Pos))
#define ADC_ADCDATA8_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA8) Register Mask  */


/* -------- ADC_ADCDATA9 : (ADC Offset: 0xA90) (R/W 32)  -------- */
#define ADC_ADCDATA9_RESETVALUE               _U_(0x00)                                            /**<  (ADC_ADCDATA9)   Reset Value */

#define ADC_ADCDATA9_DATA_Pos                 _U_(0)                                               /**< (ADC_ADCDATA9)  Position */
#define ADC_ADCDATA9_DATA_Msk                 (_U_(0xFFFFFFFF) << ADC_ADCDATA9_DATA_Pos)           /**< (ADC_ADCDATA9)  Mask */
#define ADC_ADCDATA9_DATA(value)              (ADC_ADCDATA9_DATA_Msk & ((value) << ADC_ADCDATA9_DATA_Pos))
#define ADC_ADCDATA9_Msk                      _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA9) Register Mask  */


/* -------- ADC_ADCDATA10 : (ADC Offset: 0xAA0) (R/W 32)  -------- */
#define ADC_ADCDATA10_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCDATA10)   Reset Value */

#define ADC_ADCDATA10_DATA_Pos                _U_(0)                                               /**< (ADC_ADCDATA10)  Position */
#define ADC_ADCDATA10_DATA_Msk                (_U_(0xFFFFFFFF) << ADC_ADCDATA10_DATA_Pos)          /**< (ADC_ADCDATA10)  Mask */
#define ADC_ADCDATA10_DATA(value)             (ADC_ADCDATA10_DATA_Msk & ((value) << ADC_ADCDATA10_DATA_Pos))
#define ADC_ADCDATA10_Msk                     _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA10) Register Mask  */


/* -------- ADC_ADCDATA11 : (ADC Offset: 0xAB0) (R/W 32)  -------- */
#define ADC_ADCDATA11_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCDATA11)   Reset Value */

#define ADC_ADCDATA11_DATA_Pos                _U_(0)                                               /**< (ADC_ADCDATA11)  Position */
#define ADC_ADCDATA11_DATA_Msk                (_U_(0xFFFFFFFF) << ADC_ADCDATA11_DATA_Pos)          /**< (ADC_ADCDATA11)  Mask */
#define ADC_ADCDATA11_DATA(value)             (ADC_ADCDATA11_DATA_Msk & ((value) << ADC_ADCDATA11_DATA_Pos))
#define ADC_ADCDATA11_Msk                     _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA11) Register Mask  */


/* -------- ADC_ADCDATA12 : (ADC Offset: 0xAC0) (R/W 32)  -------- */
#define ADC_ADCDATA12_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCDATA12)   Reset Value */

#define ADC_ADCDATA12_DATA_Pos                _U_(0)                                               /**< (ADC_ADCDATA12)  Position */
#define ADC_ADCDATA12_DATA_Msk                (_U_(0xFFFFFFFF) << ADC_ADCDATA12_DATA_Pos)          /**< (ADC_ADCDATA12)  Mask */
#define ADC_ADCDATA12_DATA(value)             (ADC_ADCDATA12_DATA_Msk & ((value) << ADC_ADCDATA12_DATA_Pos))
#define ADC_ADCDATA12_Msk                     _U_(0xFFFFFFFF)                                      /**< (ADC_ADCDATA12) Register Mask  */


/* -------- ADC_ADCCON1CLR : (ADC Offset: 0x04) (R/W 32) Bit clear register -------- */
#define ADC_ADCCON1CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON1CLR) Bit clear register  Reset Value */

#define ADC_ADCCON1CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON1CLR) Register Mask  */


/* -------- ADC_ADCCON1SET : (ADC Offset: 0x08) (R/W 32) Bit set register -------- */
#define ADC_ADCCON1SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON1SET) Bit set register  Reset Value */

#define ADC_ADCCON1SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON1SET) Register Mask  */


/* -------- ADC_ADCCON1INV : (ADC Offset: 0x0C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCON1INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON1INV) Bit invert register  Reset Value */

#define ADC_ADCCON1INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON1INV) Register Mask  */


/* -------- ADC_ADCCON2CLR : (ADC Offset: 0x14) (R/W 32) Bit clear register -------- */
#define ADC_ADCCON2CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON2CLR) Bit clear register  Reset Value */

#define ADC_ADCCON2CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON2CLR) Register Mask  */


/* -------- ADC_ADCCON2SET : (ADC Offset: 0x18) (R/W 32) Bit set register -------- */
#define ADC_ADCCON2SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON2SET) Bit set register  Reset Value */

#define ADC_ADCCON2SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON2SET) Register Mask  */


/* -------- ADC_ADCCON2INV : (ADC Offset: 0x1C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCON2INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON2INV) Bit invert register  Reset Value */

#define ADC_ADCCON2INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON2INV) Register Mask  */


/* -------- ADC_ADCCON3CLR : (ADC Offset: 0x24) (R/W 32) Bit clear register -------- */
#define ADC_ADCCON3CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON3CLR) Bit clear register  Reset Value */

#define ADC_ADCCON3CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON3CLR) Register Mask  */


/* -------- ADC_ADCCON3SET : (ADC Offset: 0x28) (R/W 32) Bit set register -------- */
#define ADC_ADCCON3SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON3SET) Bit set register  Reset Value */

#define ADC_ADCCON3SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON3SET) Register Mask  */


/* -------- ADC_ADCCON3INV : (ADC Offset: 0x2C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCON3INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCON3INV) Bit invert register  Reset Value */

#define ADC_ADCCON3INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCON3INV) Register Mask  */


/* -------- ADC_ADTFCCCLR : (ADC Offset: 0x34) (R/W 32) Bit clear register -------- */
#define ADC_ADTFCCCLR_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTFCCCLR) Bit clear register  Reset Value */

#define ADC_ADTFCCCLR_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTFCCCLR) Register Mask  */


/* -------- ADC_ADTFCCSET : (ADC Offset: 0x38) (R/W 32) Bit set register -------- */
#define ADC_ADTFCCSET_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTFCCSET) Bit set register  Reset Value */

#define ADC_ADTFCCSET_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTFCCSET) Register Mask  */


/* -------- ADC_ADTFCCINV : (ADC Offset: 0x3C) (R/W 32) Bit invert register -------- */
#define ADC_ADTFCCINV_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTFCCINV) Bit invert register  Reset Value */

#define ADC_ADTFCCINV_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTFCCINV) Register Mask  */


/* -------- ADC_ADIMOD1CLR : (ADC Offset: 0x44) (R/W 32) Bit clear register -------- */
#define ADC_ADIMOD1CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADIMOD1CLR) Bit clear register  Reset Value */

#define ADC_ADIMOD1CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADIMOD1CLR) Register Mask  */


/* -------- ADC_ADIMOD1SET : (ADC Offset: 0x48) (R/W 32) Bit set register -------- */
#define ADC_ADIMOD1SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADIMOD1SET) Bit set register  Reset Value */

#define ADC_ADIMOD1SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADIMOD1SET) Register Mask  */


/* -------- ADC_ADIMOD1INV : (ADC Offset: 0x4C) (R/W 32) Bit invert register -------- */
#define ADC_ADIMOD1INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADIMOD1INV) Bit invert register  Reset Value */

#define ADC_ADIMOD1INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADIMOD1INV) Register Mask  */


/* -------- ADC_ADIRQEN1CLR : (ADC Offset: 0x84) (R/W 32) Bit clear register -------- */
#define ADC_ADIRQEN1CLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADIRQEN1CLR) Bit clear register  Reset Value */

#define ADC_ADIRQEN1CLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADIRQEN1CLR) Register Mask  */


/* -------- ADC_ADIRQEN1SET : (ADC Offset: 0x88) (R/W 32) Bit set register -------- */
#define ADC_ADIRQEN1SET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADIRQEN1SET) Bit set register  Reset Value */

#define ADC_ADIRQEN1SET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADIRQEN1SET) Register Mask  */


/* -------- ADC_ADIRQEN1INV : (ADC Offset: 0x8C) (R/W 32) Bit invert register -------- */
#define ADC_ADIRQEN1INV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADIRQEN1INV) Bit invert register  Reset Value */

#define ADC_ADIRQEN1INV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADIRQEN1INV) Register Mask  */


/* -------- ADC_ADCCSS1CLR : (ADC Offset: 0xA4) (R/W 32) Bit clear register -------- */
#define ADC_ADCCSS1CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCSS1CLR) Bit clear register  Reset Value */

#define ADC_ADCCSS1CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCSS1CLR) Register Mask  */


/* -------- ADC_ADCCSS1SET : (ADC Offset: 0xA8) (R/W 32) Bit set register -------- */
#define ADC_ADCCSS1SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCSS1SET) Bit set register  Reset Value */

#define ADC_ADCCSS1SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCSS1SET) Register Mask  */


/* -------- ADC_ADCCSS1INV : (ADC Offset: 0xAC) (R/W 32) Bit invert register -------- */
#define ADC_ADCCSS1INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCSS1INV) Bit invert register  Reset Value */

#define ADC_ADCCSS1INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCSS1INV) Register Mask  */


/* -------- ADC_ADISTAT1CLR : (ADC Offset: 0xC4) (R/W 32) Bit clear register -------- */
#define ADC_ADISTAT1CLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADISTAT1CLR) Bit clear register  Reset Value */

#define ADC_ADISTAT1CLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADISTAT1CLR) Register Mask  */


/* -------- ADC_ADISTAT1SET : (ADC Offset: 0xC8) (R/W 32) Bit set register -------- */
#define ADC_ADISTAT1SET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADISTAT1SET) Bit set register  Reset Value */

#define ADC_ADISTAT1SET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADISTAT1SET) Register Mask  */


/* -------- ADC_ADISTAT1INV : (ADC Offset: 0xCC) (R/W 32) Bit invert register -------- */
#define ADC_ADISTAT1INV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADISTAT1INV) Bit invert register  Reset Value */

#define ADC_ADISTAT1INV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADISTAT1INV) Register Mask  */


/* -------- ADC_ADCMPEN0CLR : (ADC Offset: 0xE4) (R/W 32) Bit clear register -------- */
#define ADC_ADCMPEN0CLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN0CLR) Bit clear register  Reset Value */

#define ADC_ADCMPEN0CLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN0CLR) Register Mask  */


/* -------- ADC_ADCMPEN0SET : (ADC Offset: 0xE8) (R/W 32) Bit set register -------- */
#define ADC_ADCMPEN0SET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN0SET) Bit set register  Reset Value */

#define ADC_ADCMPEN0SET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN0SET) Register Mask  */


/* -------- ADC_ADCMPEN0INV : (ADC Offset: 0xEC) (R/W 32) Bit invert register -------- */
#define ADC_ADCMPEN0INV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN0INV) Bit invert register  Reset Value */

#define ADC_ADCMPEN0INV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN0INV) Register Mask  */


/* -------- ADC_ADCMP0CLR : (ADC Offset: 0xF4) (R/W 32) Bit clear register -------- */
#define ADC_ADCMP0CLR_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP0CLR) Bit clear register  Reset Value */

#define ADC_ADCMP0CLR_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP0CLR) Register Mask  */


/* -------- ADC_ADCMP0SET : (ADC Offset: 0xF8) (R/W 32) Bit set register -------- */
#define ADC_ADCMP0SET_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP0SET) Bit set register  Reset Value */

#define ADC_ADCMP0SET_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP0SET) Register Mask  */


/* -------- ADC_ADCMP0INV : (ADC Offset: 0xFC) (R/W 32) Bit invert register -------- */
#define ADC_ADCMP0INV_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP0INV) Bit invert register  Reset Value */

#define ADC_ADCMP0INV_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP0INV) Register Mask  */


/* -------- ADC_ADCMPEN1CLR : (ADC Offset: 0x104) (R/W 32) Bit clear register -------- */
#define ADC_ADCMPEN1CLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN1CLR) Bit clear register  Reset Value */

#define ADC_ADCMPEN1CLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN1CLR) Register Mask  */


/* -------- ADC_ADCMPEN1SET : (ADC Offset: 0x108) (R/W 32) Bit set register -------- */
#define ADC_ADCMPEN1SET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN1SET) Bit set register  Reset Value */

#define ADC_ADCMPEN1SET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN1SET) Register Mask  */


/* -------- ADC_ADCMPEN1INV : (ADC Offset: 0x10C) (R/W 32) Bit invert register -------- */
#define ADC_ADCMPEN1INV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCMPEN1INV) Bit invert register  Reset Value */

#define ADC_ADCMPEN1INV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCMPEN1INV) Register Mask  */


/* -------- ADC_ADCMP1CLR : (ADC Offset: 0x114) (R/W 32) Bit clear register -------- */
#define ADC_ADCMP1CLR_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP1CLR) Bit clear register  Reset Value */

#define ADC_ADCMP1CLR_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP1CLR) Register Mask  */


/* -------- ADC_ADCMP1SET : (ADC Offset: 0x118) (R/W 32) Bit set register -------- */
#define ADC_ADCMP1SET_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP1SET) Bit set register  Reset Value */

#define ADC_ADCMP1SET_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP1SET) Register Mask  */


/* -------- ADC_ADCMP1INV : (ADC Offset: 0x11C) (R/W 32) Bit invert register -------- */
#define ADC_ADCMP1INV_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADCMP1INV) Bit invert register  Reset Value */

#define ADC_ADCMP1INV_Msk                     _U_(0x00000000)                                      /**< (ADC_ADCMP1INV) Register Mask  */


/* -------- ADC_ADFLTR0CLR : (ADC Offset: 0x1A4) (R/W 32) Bit clear register -------- */
#define ADC_ADFLTR0CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR0CLR) Bit clear register  Reset Value */

#define ADC_ADFLTR0CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR0CLR) Register Mask  */


/* -------- ADC_ADFLTR0SET : (ADC Offset: 0x1A8) (R/W 32) Bit set register -------- */
#define ADC_ADFLTR0SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR0SET) Bit set register  Reset Value */

#define ADC_ADFLTR0SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR0SET) Register Mask  */


/* -------- ADC_ADFLTR0INV : (ADC Offset: 0x1AC) (R/W 32) Bit invert register -------- */
#define ADC_ADFLTR0INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR0INV) Bit invert register  Reset Value */

#define ADC_ADFLTR0INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR0INV) Register Mask  */


/* -------- ADC_ADFLTR1CLR : (ADC Offset: 0x1B4) (R/W 32) Bit clear register -------- */
#define ADC_ADFLTR1CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR1CLR) Bit clear register  Reset Value */

#define ADC_ADFLTR1CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR1CLR) Register Mask  */


/* -------- ADC_ADFLTR1SET : (ADC Offset: 0x1B8) (R/W 32) Bit set register -------- */
#define ADC_ADFLTR1SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR1SET) Bit set register  Reset Value */

#define ADC_ADFLTR1SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR1SET) Register Mask  */


/* -------- ADC_ADFLTR1INV : (ADC Offset: 0x1BC) (R/W 32) Bit invert register -------- */
#define ADC_ADFLTR1INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADFLTR1INV) Bit invert register  Reset Value */

#define ADC_ADFLTR1INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADFLTR1INV) Register Mask  */


/* -------- ADC_ADCTRG0CLR : (ADC Offset: 0x204) (R/W 32) Bit clear register -------- */
#define ADC_ADCTRG0CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG0CLR) Bit clear register  Reset Value */

#define ADC_ADCTRG0CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG0CLR) Register Mask  */


/* -------- ADC_ADCTRG0SET : (ADC Offset: 0x208) (R/W 32) Bit set register -------- */
#define ADC_ADCTRG0SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG0SET) Bit set register  Reset Value */

#define ADC_ADCTRG0SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG0SET) Register Mask  */


/* -------- ADC_ADCTRG0INV : (ADC Offset: 0x20C) (R/W 32) Bit invert register -------- */
#define ADC_ADCTRG0INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG0INV) Bit invert register  Reset Value */

#define ADC_ADCTRG0INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG0INV) Register Mask  */


/* -------- ADC_ADCTRG1CLR : (ADC Offset: 0x214) (R/W 32) Bit clear register -------- */
#define ADC_ADCTRG1CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG1CLR) Bit clear register  Reset Value */

#define ADC_ADCTRG1CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG1CLR) Register Mask  */


/* -------- ADC_ADCTRG1SET : (ADC Offset: 0x218) (R/W 32) Bit set register -------- */
#define ADC_ADCTRG1SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG1SET) Bit set register  Reset Value */

#define ADC_ADCTRG1SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG1SET) Register Mask  */


/* -------- ADC_ADCTRG1INV : (ADC Offset: 0x21C) (R/W 32) Bit invert register -------- */
#define ADC_ADCTRG1INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG1INV) Bit invert register  Reset Value */

#define ADC_ADCTRG1INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG1INV) Register Mask  */


/* -------- ADC_ADCTRG2CLR : (ADC Offset: 0x224) (R/W 32) Bit clear register -------- */
#define ADC_ADCTRG2CLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG2CLR) Bit clear register  Reset Value */

#define ADC_ADCTRG2CLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG2CLR) Register Mask  */


/* -------- ADC_ADCTRG2SET : (ADC Offset: 0x228) (R/W 32) Bit set register -------- */
#define ADC_ADCTRG2SET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG2SET) Bit set register  Reset Value */

#define ADC_ADCTRG2SET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG2SET) Register Mask  */


/* -------- ADC_ADCTRG2INV : (ADC Offset: 0x22C) (R/W 32) Bit invert register -------- */
#define ADC_ADCTRG2INV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCTRG2INV) Bit invert register  Reset Value */

#define ADC_ADCTRG2INV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCTRG2INV) Register Mask  */


/* -------- ADC_ADCCMPCON0CLR : (ADC Offset: 0x284) (R/W 32) Bit clear register -------- */
#define ADC_ADCCMPCON0CLR_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON0CLR) Bit clear register  Reset Value */

#define ADC_ADCCMPCON0CLR_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON0CLR) Register Mask  */


/* -------- ADC_ADCCMPCON0SET : (ADC Offset: 0x288) (R/W 32) Bit set register -------- */
#define ADC_ADCCMPCON0SET_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON0SET) Bit set register  Reset Value */

#define ADC_ADCCMPCON0SET_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON0SET) Register Mask  */


/* -------- ADC_ADCCMPCON0INV : (ADC Offset: 0x28C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCMPCON0INV_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON0INV) Bit invert register  Reset Value */

#define ADC_ADCCMPCON0INV_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON0INV) Register Mask  */


/* -------- ADC_ADCCMPCON1CLR : (ADC Offset: 0x294) (R/W 32) Bit clear register -------- */
#define ADC_ADCCMPCON1CLR_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON1CLR) Bit clear register  Reset Value */

#define ADC_ADCCMPCON1CLR_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON1CLR) Register Mask  */


/* -------- ADC_ADCCMPCON1SET : (ADC Offset: 0x298) (R/W 32) Bit set register -------- */
#define ADC_ADCCMPCON1SET_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON1SET) Bit set register  Reset Value */

#define ADC_ADCCMPCON1SET_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON1SET) Register Mask  */


/* -------- ADC_ADCCMPCON1INV : (ADC Offset: 0x29C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCMPCON1INV_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCCMPCON1INV) Bit invert register  Reset Value */

#define ADC_ADCCMPCON1INV_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCCMPCON1INV) Register Mask  */


/* -------- ADC_ADCFSTATCLR : (ADC Offset: 0x2E4) (R/W 32) Bit clear register -------- */
#define ADC_ADCFSTATCLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFSTATCLR) Bit clear register  Reset Value */

#define ADC_ADCFSTATCLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFSTATCLR) Register Mask  */


/* -------- ADC_ADCFSTATSET : (ADC Offset: 0x2E8) (R/W 32) Bit set register -------- */
#define ADC_ADCFSTATSET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFSTATSET) Bit set register  Reset Value */

#define ADC_ADCFSTATSET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFSTATSET) Register Mask  */


/* -------- ADC_ADCFSTATINV : (ADC Offset: 0x2EC) (R/W 32) Bit invert register -------- */
#define ADC_ADCFSTATINV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFSTATINV) Bit invert register  Reset Value */

#define ADC_ADCFSTATINV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFSTATINV) Register Mask  */


/* -------- ADC_ADCFIFOCLR : (ADC Offset: 0x2F4) (R/W 32) Bit clear register -------- */
#define ADC_ADCFIFOCLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCFIFOCLR) Bit clear register  Reset Value */

#define ADC_ADCFIFOCLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCFIFOCLR) Register Mask  */


/* -------- ADC_ADCFIFOSET : (ADC Offset: 0x2F8) (R/W 32) Bit set register -------- */
#define ADC_ADCFIFOSET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCFIFOSET) Bit set register  Reset Value */

#define ADC_ADCFIFOSET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCFIFOSET) Register Mask  */


/* -------- ADC_ADCFIFOINV : (ADC Offset: 0x2FC) (R/W 32) Bit invert register -------- */
#define ADC_ADCFIFOINV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCFIFOINV) Bit invert register  Reset Value */

#define ADC_ADCFIFOINV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCFIFOINV) Register Mask  */


/* -------- ADC_ADCBASECLR : (ADC Offset: 0x304) (R/W 32) Bit clear register -------- */
#define ADC_ADCBASECLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCBASECLR) Bit clear register  Reset Value */

#define ADC_ADCBASECLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCBASECLR) Register Mask  */


/* -------- ADC_ADCBASESET : (ADC Offset: 0x308) (R/W 32) Bit set register -------- */
#define ADC_ADCBASESET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCBASESET) Bit set register  Reset Value */

#define ADC_ADCBASESET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCBASESET) Register Mask  */


/* -------- ADC_ADCBASEINV : (ADC Offset: 0x30C) (R/W 32) Bit invert register -------- */
#define ADC_ADCBASEINV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCBASEINV) Bit invert register  Reset Value */

#define ADC_ADCBASEINV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCBASEINV) Register Mask  */


/* -------- ADC_ADCDMASTCLR : (ADC Offset: 0x314) (R/W 32) Bit clear register -------- */
#define ADC_ADCDMASTCLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCDMASTCLR) Bit clear register  Reset Value */

#define ADC_ADCDMASTCLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCDMASTCLR) Register Mask  */


/* -------- ADC_ADCDMASTSET : (ADC Offset: 0x318) (R/W 32) Bit set register -------- */
#define ADC_ADCDMASTSET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCDMASTSET) Bit set register  Reset Value */

#define ADC_ADCDMASTSET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCDMASTSET) Register Mask  */


/* -------- ADC_ADCDMASTINV : (ADC Offset: 0x31C) (R/W 32) Bit invert register -------- */
#define ADC_ADCDMASTINV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCDMASTINV) Bit invert register  Reset Value */

#define ADC_ADCDMASTINV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCDMASTINV) Register Mask  */


/* -------- ADC_ADCCNTBCLR : (ADC Offset: 0x324) (R/W 32) Bit clear register -------- */
#define ADC_ADCCNTBCLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCNTBCLR) Bit clear register  Reset Value */

#define ADC_ADCCNTBCLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCNTBCLR) Register Mask  */


/* -------- ADC_ADCCNTBSET : (ADC Offset: 0x328) (R/W 32) Bit set register -------- */
#define ADC_ADCCNTBSET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCNTBSET) Bit set register  Reset Value */

#define ADC_ADCCNTBSET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCNTBSET) Register Mask  */


/* -------- ADC_ADCCNTBINV : (ADC Offset: 0x32C) (R/W 32) Bit invert register -------- */
#define ADC_ADCCNTBINV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCCNTBINV) Bit invert register  Reset Value */

#define ADC_ADCCNTBINV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCCNTBINV) Register Mask  */


/* -------- ADC_ADCDMABCLR : (ADC Offset: 0x334) (R/W 32) Bit clear register -------- */
#define ADC_ADCDMABCLR_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCDMABCLR) Bit clear register  Reset Value */

#define ADC_ADCDMABCLR_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCDMABCLR) Register Mask  */


/* -------- ADC_ADCDMABSET : (ADC Offset: 0x338) (R/W 32) Bit set register -------- */
#define ADC_ADCDMABSET_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCDMABSET) Bit set register  Reset Value */

#define ADC_ADCDMABSET_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCDMABSET) Register Mask  */


/* -------- ADC_ADCDMABINV : (ADC Offset: 0x33C) (R/W 32) Bit invert register -------- */
#define ADC_ADCDMABINV_RESETVALUE             _U_(0x00)                                            /**<  (ADC_ADCDMABINV) Bit invert register  Reset Value */

#define ADC_ADCDMABINV_Msk                    _U_(0x00000000)                                      /**< (ADC_ADCDMABINV) Register Mask  */


/* -------- ADC_ADCTRGSNSCLR : (ADC Offset: 0x344) (R/W 32) Bit clear register -------- */
#define ADC_ADCTRGSNSCLR_RESETVALUE           _U_(0x00)                                            /**<  (ADC_ADCTRGSNSCLR) Bit clear register  Reset Value */

#define ADC_ADCTRGSNSCLR_Msk                  _U_(0x00000000)                                      /**< (ADC_ADCTRGSNSCLR) Register Mask  */


/* -------- ADC_ADCTRGSNSSET : (ADC Offset: 0x348) (R/W 32) Bit set register -------- */
#define ADC_ADCTRGSNSSET_RESETVALUE           _U_(0x00)                                            /**<  (ADC_ADCTRGSNSSET) Bit set register  Reset Value */

#define ADC_ADCTRGSNSSET_Msk                  _U_(0x00000000)                                      /**< (ADC_ADCTRGSNSSET) Register Mask  */


/* -------- ADC_ADCTRGSNSINV : (ADC Offset: 0x34C) (R/W 32) Bit invert register -------- */
#define ADC_ADCTRGSNSINV_RESETVALUE           _U_(0x00)                                            /**<  (ADC_ADCTRGSNSINV) Bit invert register  Reset Value */

#define ADC_ADCTRGSNSINV_Msk                  _U_(0x00000000)                                      /**< (ADC_ADCTRGSNSINV) Register Mask  */


/* -------- ADC_ADTIM0CLR : (ADC Offset: 0x354) (R/W 32) Bit clear register -------- */
#define ADC_ADTIM0CLR_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTIM0CLR) Bit clear register  Reset Value */

#define ADC_ADTIM0CLR_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTIM0CLR) Register Mask  */


/* -------- ADC_ADTIM0SET : (ADC Offset: 0x358) (R/W 32) Bit set register -------- */
#define ADC_ADTIM0SET_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTIM0SET) Bit set register  Reset Value */

#define ADC_ADTIM0SET_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTIM0SET) Register Mask  */


/* -------- ADC_ADTIM0INV : (ADC Offset: 0x35C) (R/W 32) Bit invert register -------- */
#define ADC_ADTIM0INV_RESETVALUE              _U_(0x00)                                            /**<  (ADC_ADTIM0INV) Bit invert register  Reset Value */

#define ADC_ADTIM0INV_Msk                     _U_(0x00000000)                                      /**< (ADC_ADTIM0INV) Register Mask  */


/* -------- ADC_ADCEISTAT1CLR : (ADC Offset: 0x3E4) (R/W 32) Bit clear register -------- */
#define ADC_ADCEISTAT1CLR_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCEISTAT1CLR) Bit clear register  Reset Value */

#define ADC_ADCEISTAT1CLR_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCEISTAT1CLR) Register Mask  */


/* -------- ADC_ADCEISTAT1SET : (ADC Offset: 0x3E8) (R/W 32) Bit set register -------- */
#define ADC_ADCEISTAT1SET_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCEISTAT1SET) Bit set register  Reset Value */

#define ADC_ADCEISTAT1SET_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCEISTAT1SET) Register Mask  */


/* -------- ADC_ADCEISTAT1INV : (ADC Offset: 0x3EC) (R/W 32) Bit invert register -------- */
#define ADC_ADCEISTAT1INV_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCEISTAT1INV) Bit invert register  Reset Value */

#define ADC_ADCEISTAT1INV_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCEISTAT1INV) Register Mask  */


/* -------- ADC_ADCANCONCLR : (ADC Offset: 0x404) (R/W 32) Bit clear register -------- */
#define ADC_ADCANCONCLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCANCONCLR) Bit clear register  Reset Value */

#define ADC_ADCANCONCLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCANCONCLR) Register Mask  */


/* -------- ADC_ADCANCONSET : (ADC Offset: 0x408) (R/W 32) Bit set register -------- */
#define ADC_ADCANCONSET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCANCONSET) Bit set register  Reset Value */

#define ADC_ADCANCONSET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCANCONSET) Register Mask  */


/* -------- ADC_ADCANCONINV : (ADC Offset: 0x40C) (R/W 32) Bit invert register -------- */
#define ADC_ADCANCONINV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCANCONINV) Bit invert register  Reset Value */

#define ADC_ADCANCONINV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCANCONINV) Register Mask  */


/* -------- ADC_ADCFGSHRCLR : (ADC Offset: 0x674) (R/W 32) Bit clear register -------- */
#define ADC_ADCFGSHRCLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFGSHRCLR) Bit clear register  Reset Value */

#define ADC_ADCFGSHRCLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFGSHRCLR) Register Mask  */


/* -------- ADC_ADCFGSHRSET : (ADC Offset: 0x678) (R/W 32) Bit set register -------- */
#define ADC_ADCFGSHRSET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFGSHRSET) Bit set register  Reset Value */

#define ADC_ADCFGSHRSET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFGSHRSET) Register Mask  */


/* -------- ADC_ADCFGSHRINV : (ADC Offset: 0x67C) (R/W 32) Bit invert register -------- */
#define ADC_ADCFGSHRINV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCFGSHRINV) Bit invert register  Reset Value */

#define ADC_ADCFGSHRINV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCFGSHRINV) Register Mask  */


/* -------- ADC_ADCSVCONCLR : (ADC Offset: 0x684) (R/W 32) Bit clear register -------- */
#define ADC_ADCSVCONCLR_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCSVCONCLR) Bit clear register  Reset Value */

#define ADC_ADCSVCONCLR_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCSVCONCLR) Register Mask  */


/* -------- ADC_ADCSVCONSET : (ADC Offset: 0x688) (R/W 32) Bit set register -------- */
#define ADC_ADCSVCONSET_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCSVCONSET) Bit set register  Reset Value */

#define ADC_ADCSVCONSET_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCSVCONSET) Register Mask  */


/* -------- ADC_ADCSVCONINV : (ADC Offset: 0x68C) (R/W 32) Bit invert register -------- */
#define ADC_ADCSVCONINV_RESETVALUE            _U_(0x00)                                            /**<  (ADC_ADCSVCONINV) Bit invert register  Reset Value */

#define ADC_ADCSVCONINV_Msk                   _U_(0x00000000)                                      /**< (ADC_ADCSVCONINV) Register Mask  */


/* -------- ADC_ADCSYSCFG0CLR : (ADC Offset: 0x704) (R/W 32) Bit clear register -------- */
#define ADC_ADCSYSCFG0CLR_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCSYSCFG0CLR) Bit clear register  Reset Value */

#define ADC_ADCSYSCFG0CLR_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCSYSCFG0CLR) Register Mask  */


/* -------- ADC_ADCSYSCFG0SET : (ADC Offset: 0x708) (R/W 32) Bit set register -------- */
#define ADC_ADCSYSCFG0SET_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCSYSCFG0SET) Bit set register  Reset Value */

#define ADC_ADCSYSCFG0SET_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCSYSCFG0SET) Register Mask  */


/* -------- ADC_ADCSYSCFG0INV : (ADC Offset: 0x70C) (R/W 32) Bit invert register -------- */
#define ADC_ADCSYSCFG0INV_RESETVALUE          _U_(0x00)                                            /**<  (ADC_ADCSYSCFG0INV) Bit invert register  Reset Value */

#define ADC_ADCSYSCFG0INV_Msk                 _U_(0x00000000)                                      /**< (ADC_ADCSYSCFG0INV) Register Mask  */


/** \brief ADC register offsets definitions */
#define ADC_ADCCON1_REG_OFST           (0x00)              /**< (ADC_ADCCON1)  Offset */
#define ADC_ADCCON2_REG_OFST           (0x10)              /**< (ADC_ADCCON2)  Offset */
#define ADC_ADCCON3_REG_OFST           (0x20)              /**< (ADC_ADCCON3)  Offset */
#define ADC_ADTFCC_REG_OFST            (0x30)              /**< (ADC_ADTFCC)  Offset */
#define ADC_ADIMOD1_REG_OFST           (0x40)              /**< (ADC_ADIMOD1)  Offset */
#define ADC_ADIRQEN1_REG_OFST          (0x80)              /**< (ADC_ADIRQEN1)  Offset */
#define ADC_ADCCSS1_REG_OFST           (0xA0)              /**< (ADC_ADCCSS1)  Offset */
#define ADC_ADISTAT1_REG_OFST          (0xC0)              /**< (ADC_ADISTAT1)  Offset */
#define ADC_ADCMPEN0_REG_OFST          (0xE0)              /**< (ADC_ADCMPEN0)  Offset */
#define ADC_ADCMP0_REG_OFST            (0xF0)              /**< (ADC_ADCMP0)  Offset */
#define ADC_ADCMPEN1_REG_OFST          (0x100)             /**< (ADC_ADCMPEN1)  Offset */
#define ADC_ADCMP1_REG_OFST            (0x110)             /**< (ADC_ADCMP1)  Offset */
#define ADC_ADFLTR0_REG_OFST           (0x1A0)             /**< (ADC_ADFLTR0)  Offset */
#define ADC_ADFLTR1_REG_OFST           (0x1B0)             /**< (ADC_ADFLTR1)  Offset */
#define ADC_ADCTRG0_REG_OFST           (0x200)             /**< (ADC_ADCTRG0)  Offset */
#define ADC_ADCTRG1_REG_OFST           (0x210)             /**< (ADC_ADCTRG1)  Offset */
#define ADC_ADCTRG2_REG_OFST           (0x220)             /**< (ADC_ADCTRG2)  Offset */
#define ADC_ADCCMPCON0_REG_OFST        (0x280)             /**< (ADC_ADCCMPCON0)  Offset */
#define ADC_ADCCMPCON1_REG_OFST        (0x290)             /**< (ADC_ADCCMPCON1)  Offset */
#define ADC_ADCFSTAT_REG_OFST          (0x2E0)             /**< (ADC_ADCFSTAT)  Offset */
#define ADC_ADCFIFO_REG_OFST           (0x2F0)             /**< (ADC_ADCFIFO)  Offset */
#define ADC_ADCBASE_REG_OFST           (0x300)             /**< (ADC_ADCBASE)  Offset */
#define ADC_ADCDMAST_REG_OFST          (0x310)             /**< (ADC_ADCDMAST)  Offset */
#define ADC_ADCCNTB_REG_OFST           (0x320)             /**< (ADC_ADCCNTB)  Offset */
#define ADC_ADCDMAB_REG_OFST           (0x330)             /**< (ADC_ADCDMAB)  Offset */
#define ADC_ADCTRGSNS_REG_OFST         (0x340)             /**< (ADC_ADCTRGSNS)  Offset */
#define ADC_ADTIM0_REG_OFST            (0x350)             /**< (ADC_ADTIM0)  Offset */
#define ADC_ADCEISTAT1_REG_OFST        (0x3E0)             /**< (ADC_ADCEISTAT1)  Offset */
#define ADC_ADCANCON_REG_OFST          (0x400)             /**< (ADC_ADCANCON)  Offset */
#define ADC_ADCFGSHR_REG_OFST          (0x670)             /**< (ADC_ADCFGSHR)  Offset */
#define ADC_ADCSVCON_REG_OFST          (0x680)             /**< (ADC_ADCSVCON)  Offset */
#define ADC_ADCSYSCFG0_REG_OFST        (0x700)             /**< (ADC_ADCSYSCFG0)  Offset */
#define ADC_ADCDATA1_REG_OFST          (0xA10)             /**< (ADC_ADCDATA1)  Offset */
#define ADC_ADCDATA2_REG_OFST          (0xA20)             /**< (ADC_ADCDATA2)  Offset */
#define ADC_ADCDATA3_REG_OFST          (0xA30)             /**< (ADC_ADCDATA3)  Offset */
#define ADC_ADCDATA4_REG_OFST          (0xA40)             /**< (ADC_ADCDATA4)  Offset */
#define ADC_ADCDATA5_REG_OFST          (0xA50)             /**< (ADC_ADCDATA5)  Offset */
#define ADC_ADCDATA6_REG_OFST          (0xA60)             /**< (ADC_ADCDATA6)  Offset */
#define ADC_ADCDATA7_REG_OFST          (0xA70)             /**< (ADC_ADCDATA7)  Offset */
#define ADC_ADCDATA8_REG_OFST          (0xA80)             /**< (ADC_ADCDATA8)  Offset */
#define ADC_ADCDATA9_REG_OFST          (0xA90)             /**< (ADC_ADCDATA9)  Offset */
#define ADC_ADCDATA10_REG_OFST         (0xAA0)             /**< (ADC_ADCDATA10)  Offset */
#define ADC_ADCDATA11_REG_OFST         (0xAB0)             /**< (ADC_ADCDATA11)  Offset */
#define ADC_ADCDATA12_REG_OFST         (0xAC0)             /**< (ADC_ADCDATA12)  Offset */
#define ADC_ADCCON1CLR_REG_OFST        (0x04)              /**< (ADC_ADCCON1CLR) Bit clear register Offset */
#define ADC_ADCCON1SET_REG_OFST        (0x08)              /**< (ADC_ADCCON1SET) Bit set register Offset */
#define ADC_ADCCON1INV_REG_OFST        (0x0C)              /**< (ADC_ADCCON1INV) Bit invert register Offset */
#define ADC_ADCCON2CLR_REG_OFST        (0x14)              /**< (ADC_ADCCON2CLR) Bit clear register Offset */
#define ADC_ADCCON2SET_REG_OFST        (0x18)              /**< (ADC_ADCCON2SET) Bit set register Offset */
#define ADC_ADCCON2INV_REG_OFST        (0x1C)              /**< (ADC_ADCCON2INV) Bit invert register Offset */
#define ADC_ADCCON3CLR_REG_OFST        (0x24)              /**< (ADC_ADCCON3CLR) Bit clear register Offset */
#define ADC_ADCCON3SET_REG_OFST        (0x28)              /**< (ADC_ADCCON3SET) Bit set register Offset */
#define ADC_ADCCON3INV_REG_OFST        (0x2C)              /**< (ADC_ADCCON3INV) Bit invert register Offset */
#define ADC_ADTFCCCLR_REG_OFST         (0x34)              /**< (ADC_ADTFCCCLR) Bit clear register Offset */
#define ADC_ADTFCCSET_REG_OFST         (0x38)              /**< (ADC_ADTFCCSET) Bit set register Offset */
#define ADC_ADTFCCINV_REG_OFST         (0x3C)              /**< (ADC_ADTFCCINV) Bit invert register Offset */
#define ADC_ADIMOD1CLR_REG_OFST        (0x44)              /**< (ADC_ADIMOD1CLR) Bit clear register Offset */
#define ADC_ADIMOD1SET_REG_OFST        (0x48)              /**< (ADC_ADIMOD1SET) Bit set register Offset */
#define ADC_ADIMOD1INV_REG_OFST        (0x4C)              /**< (ADC_ADIMOD1INV) Bit invert register Offset */
#define ADC_ADIRQEN1CLR_REG_OFST       (0x84)              /**< (ADC_ADIRQEN1CLR) Bit clear register Offset */
#define ADC_ADIRQEN1SET_REG_OFST       (0x88)              /**< (ADC_ADIRQEN1SET) Bit set register Offset */
#define ADC_ADIRQEN1INV_REG_OFST       (0x8C)              /**< (ADC_ADIRQEN1INV) Bit invert register Offset */
#define ADC_ADCCSS1CLR_REG_OFST        (0xA4)              /**< (ADC_ADCCSS1CLR) Bit clear register Offset */
#define ADC_ADCCSS1SET_REG_OFST        (0xA8)              /**< (ADC_ADCCSS1SET) Bit set register Offset */
#define ADC_ADCCSS1INV_REG_OFST        (0xAC)              /**< (ADC_ADCCSS1INV) Bit invert register Offset */
#define ADC_ADISTAT1CLR_REG_OFST       (0xC4)              /**< (ADC_ADISTAT1CLR) Bit clear register Offset */
#define ADC_ADISTAT1SET_REG_OFST       (0xC8)              /**< (ADC_ADISTAT1SET) Bit set register Offset */
#define ADC_ADISTAT1INV_REG_OFST       (0xCC)              /**< (ADC_ADISTAT1INV) Bit invert register Offset */
#define ADC_ADCMPEN0CLR_REG_OFST       (0xE4)              /**< (ADC_ADCMPEN0CLR) Bit clear register Offset */
#define ADC_ADCMPEN0SET_REG_OFST       (0xE8)              /**< (ADC_ADCMPEN0SET) Bit set register Offset */
#define ADC_ADCMPEN0INV_REG_OFST       (0xEC)              /**< (ADC_ADCMPEN0INV) Bit invert register Offset */
#define ADC_ADCMP0CLR_REG_OFST         (0xF4)              /**< (ADC_ADCMP0CLR) Bit clear register Offset */
#define ADC_ADCMP0SET_REG_OFST         (0xF8)              /**< (ADC_ADCMP0SET) Bit set register Offset */
#define ADC_ADCMP0INV_REG_OFST         (0xFC)              /**< (ADC_ADCMP0INV) Bit invert register Offset */
#define ADC_ADCMPEN1CLR_REG_OFST       (0x104)             /**< (ADC_ADCMPEN1CLR) Bit clear register Offset */
#define ADC_ADCMPEN1SET_REG_OFST       (0x108)             /**< (ADC_ADCMPEN1SET) Bit set register Offset */
#define ADC_ADCMPEN1INV_REG_OFST       (0x10C)             /**< (ADC_ADCMPEN1INV) Bit invert register Offset */
#define ADC_ADCMP1CLR_REG_OFST         (0x114)             /**< (ADC_ADCMP1CLR) Bit clear register Offset */
#define ADC_ADCMP1SET_REG_OFST         (0x118)             /**< (ADC_ADCMP1SET) Bit set register Offset */
#define ADC_ADCMP1INV_REG_OFST         (0x11C)             /**< (ADC_ADCMP1INV) Bit invert register Offset */
#define ADC_ADFLTR0CLR_REG_OFST        (0x1A4)             /**< (ADC_ADFLTR0CLR) Bit clear register Offset */
#define ADC_ADFLTR0SET_REG_OFST        (0x1A8)             /**< (ADC_ADFLTR0SET) Bit set register Offset */
#define ADC_ADFLTR0INV_REG_OFST        (0x1AC)             /**< (ADC_ADFLTR0INV) Bit invert register Offset */
#define ADC_ADFLTR1CLR_REG_OFST        (0x1B4)             /**< (ADC_ADFLTR1CLR) Bit clear register Offset */
#define ADC_ADFLTR1SET_REG_OFST        (0x1B8)             /**< (ADC_ADFLTR1SET) Bit set register Offset */
#define ADC_ADFLTR1INV_REG_OFST        (0x1BC)             /**< (ADC_ADFLTR1INV) Bit invert register Offset */
#define ADC_ADCTRG0CLR_REG_OFST        (0x204)             /**< (ADC_ADCTRG0CLR) Bit clear register Offset */
#define ADC_ADCTRG0SET_REG_OFST        (0x208)             /**< (ADC_ADCTRG0SET) Bit set register Offset */
#define ADC_ADCTRG0INV_REG_OFST        (0x20C)             /**< (ADC_ADCTRG0INV) Bit invert register Offset */
#define ADC_ADCTRG1CLR_REG_OFST        (0x214)             /**< (ADC_ADCTRG1CLR) Bit clear register Offset */
#define ADC_ADCTRG1SET_REG_OFST        (0x218)             /**< (ADC_ADCTRG1SET) Bit set register Offset */
#define ADC_ADCTRG1INV_REG_OFST        (0x21C)             /**< (ADC_ADCTRG1INV) Bit invert register Offset */
#define ADC_ADCTRG2CLR_REG_OFST        (0x224)             /**< (ADC_ADCTRG2CLR) Bit clear register Offset */
#define ADC_ADCTRG2SET_REG_OFST        (0x228)             /**< (ADC_ADCTRG2SET) Bit set register Offset */
#define ADC_ADCTRG2INV_REG_OFST        (0x22C)             /**< (ADC_ADCTRG2INV) Bit invert register Offset */
#define ADC_ADCCMPCON0CLR_REG_OFST     (0x284)             /**< (ADC_ADCCMPCON0CLR) Bit clear register Offset */
#define ADC_ADCCMPCON0SET_REG_OFST     (0x288)             /**< (ADC_ADCCMPCON0SET) Bit set register Offset */
#define ADC_ADCCMPCON0INV_REG_OFST     (0x28C)             /**< (ADC_ADCCMPCON0INV) Bit invert register Offset */
#define ADC_ADCCMPCON1CLR_REG_OFST     (0x294)             /**< (ADC_ADCCMPCON1CLR) Bit clear register Offset */
#define ADC_ADCCMPCON1SET_REG_OFST     (0x298)             /**< (ADC_ADCCMPCON1SET) Bit set register Offset */
#define ADC_ADCCMPCON1INV_REG_OFST     (0x29C)             /**< (ADC_ADCCMPCON1INV) Bit invert register Offset */
#define ADC_ADCFSTATCLR_REG_OFST       (0x2E4)             /**< (ADC_ADCFSTATCLR) Bit clear register Offset */
#define ADC_ADCFSTATSET_REG_OFST       (0x2E8)             /**< (ADC_ADCFSTATSET) Bit set register Offset */
#define ADC_ADCFSTATINV_REG_OFST       (0x2EC)             /**< (ADC_ADCFSTATINV) Bit invert register Offset */
#define ADC_ADCFIFOCLR_REG_OFST        (0x2F4)             /**< (ADC_ADCFIFOCLR) Bit clear register Offset */
#define ADC_ADCFIFOSET_REG_OFST        (0x2F8)             /**< (ADC_ADCFIFOSET) Bit set register Offset */
#define ADC_ADCFIFOINV_REG_OFST        (0x2FC)             /**< (ADC_ADCFIFOINV) Bit invert register Offset */
#define ADC_ADCBASECLR_REG_OFST        (0x304)             /**< (ADC_ADCBASECLR) Bit clear register Offset */
#define ADC_ADCBASESET_REG_OFST        (0x308)             /**< (ADC_ADCBASESET) Bit set register Offset */
#define ADC_ADCBASEINV_REG_OFST        (0x30C)             /**< (ADC_ADCBASEINV) Bit invert register Offset */
#define ADC_ADCDMASTCLR_REG_OFST       (0x314)             /**< (ADC_ADCDMASTCLR) Bit clear register Offset */
#define ADC_ADCDMASTSET_REG_OFST       (0x318)             /**< (ADC_ADCDMASTSET) Bit set register Offset */
#define ADC_ADCDMASTINV_REG_OFST       (0x31C)             /**< (ADC_ADCDMASTINV) Bit invert register Offset */
#define ADC_ADCCNTBCLR_REG_OFST        (0x324)             /**< (ADC_ADCCNTBCLR) Bit clear register Offset */
#define ADC_ADCCNTBSET_REG_OFST        (0x328)             /**< (ADC_ADCCNTBSET) Bit set register Offset */
#define ADC_ADCCNTBINV_REG_OFST        (0x32C)             /**< (ADC_ADCCNTBINV) Bit invert register Offset */
#define ADC_ADCDMABCLR_REG_OFST        (0x334)             /**< (ADC_ADCDMABCLR) Bit clear register Offset */
#define ADC_ADCDMABSET_REG_OFST        (0x338)             /**< (ADC_ADCDMABSET) Bit set register Offset */
#define ADC_ADCDMABINV_REG_OFST        (0x33C)             /**< (ADC_ADCDMABINV) Bit invert register Offset */
#define ADC_ADCTRGSNSCLR_REG_OFST      (0x344)             /**< (ADC_ADCTRGSNSCLR) Bit clear register Offset */
#define ADC_ADCTRGSNSSET_REG_OFST      (0x348)             /**< (ADC_ADCTRGSNSSET) Bit set register Offset */
#define ADC_ADCTRGSNSINV_REG_OFST      (0x34C)             /**< (ADC_ADCTRGSNSINV) Bit invert register Offset */
#define ADC_ADTIM0CLR_REG_OFST         (0x354)             /**< (ADC_ADTIM0CLR) Bit clear register Offset */
#define ADC_ADTIM0SET_REG_OFST         (0x358)             /**< (ADC_ADTIM0SET) Bit set register Offset */
#define ADC_ADTIM0INV_REG_OFST         (0x35C)             /**< (ADC_ADTIM0INV) Bit invert register Offset */
#define ADC_ADCEISTAT1CLR_REG_OFST     (0x3E4)             /**< (ADC_ADCEISTAT1CLR) Bit clear register Offset */
#define ADC_ADCEISTAT1SET_REG_OFST     (0x3E8)             /**< (ADC_ADCEISTAT1SET) Bit set register Offset */
#define ADC_ADCEISTAT1INV_REG_OFST     (0x3EC)             /**< (ADC_ADCEISTAT1INV) Bit invert register Offset */
#define ADC_ADCANCONCLR_REG_OFST       (0x404)             /**< (ADC_ADCANCONCLR) Bit clear register Offset */
#define ADC_ADCANCONSET_REG_OFST       (0x408)             /**< (ADC_ADCANCONSET) Bit set register Offset */
#define ADC_ADCANCONINV_REG_OFST       (0x40C)             /**< (ADC_ADCANCONINV) Bit invert register Offset */
#define ADC_ADCFGSHRCLR_REG_OFST       (0x674)             /**< (ADC_ADCFGSHRCLR) Bit clear register Offset */
#define ADC_ADCFGSHRSET_REG_OFST       (0x678)             /**< (ADC_ADCFGSHRSET) Bit set register Offset */
#define ADC_ADCFGSHRINV_REG_OFST       (0x67C)             /**< (ADC_ADCFGSHRINV) Bit invert register Offset */
#define ADC_ADCSVCONCLR_REG_OFST       (0x684)             /**< (ADC_ADCSVCONCLR) Bit clear register Offset */
#define ADC_ADCSVCONSET_REG_OFST       (0x688)             /**< (ADC_ADCSVCONSET) Bit set register Offset */
#define ADC_ADCSVCONINV_REG_OFST       (0x68C)             /**< (ADC_ADCSVCONINV) Bit invert register Offset */
#define ADC_ADCSYSCFG0CLR_REG_OFST     (0x704)             /**< (ADC_ADCSYSCFG0CLR) Bit clear register Offset */
#define ADC_ADCSYSCFG0SET_REG_OFST     (0x708)             /**< (ADC_ADCSYSCFG0SET) Bit set register Offset */
#define ADC_ADCSYSCFG0INV_REG_OFST     (0x70C)             /**< (ADC_ADCSYSCFG0INV) Bit invert register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief ADC register API structure */
typedef struct
{  /*  */
  __IO  uint32_t                       ADC_ADCCON1;        /**< Offset: 0x00 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCON1CLR;     /**< Offset: 0x04 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCON1SET;     /**< Offset: 0x08 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCON1INV;     /**< Offset: 0x0C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCCON2;        /**< Offset: 0x10 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCON2CLR;     /**< Offset: 0x14 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCON2SET;     /**< Offset: 0x18 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCON2INV;     /**< Offset: 0x1C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCCON3;        /**< Offset: 0x20 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCON3CLR;     /**< Offset: 0x24 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCON3SET;     /**< Offset: 0x28 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCON3INV;     /**< Offset: 0x2C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADTFCC;         /**< Offset: 0x30 (R/W  32)  */
  __IO  uint32_t                       ADC_ADTFCCCLR;      /**< Offset: 0x34 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADTFCCSET;      /**< Offset: 0x38 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADTFCCINV;      /**< Offset: 0x3C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADIMOD1;        /**< Offset: 0x40 (R/W  32)  */
  __IO  uint32_t                       ADC_ADIMOD1CLR;     /**< Offset: 0x44 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADIMOD1SET;     /**< Offset: 0x48 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADIMOD1INV;     /**< Offset: 0x4C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved1[0x30];
  __IO  uint32_t                       ADC_ADIRQEN1;       /**< Offset: 0x80 (R/W  32)  */
  __IO  uint32_t                       ADC_ADIRQEN1CLR;    /**< Offset: 0x84 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADIRQEN1SET;    /**< Offset: 0x88 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADIRQEN1INV;    /**< Offset: 0x8C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved2[0x10];
  __IO  uint32_t                       ADC_ADCCSS1;        /**< Offset: 0xA0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCSS1CLR;     /**< Offset: 0xA4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCSS1SET;     /**< Offset: 0xA8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCSS1INV;     /**< Offset: 0xAC (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved3[0x10];
  __IO  uint32_t                       ADC_ADISTAT1;       /**< Offset: 0xC0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADISTAT1CLR;    /**< Offset: 0xC4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADISTAT1SET;    /**< Offset: 0xC8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADISTAT1INV;    /**< Offset: 0xCC (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved4[0x10];
  __IO  uint32_t                       ADC_ADCMPEN0;       /**< Offset: 0xE0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCMPEN0CLR;    /**< Offset: 0xE4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCMPEN0SET;    /**< Offset: 0xE8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCMPEN0INV;    /**< Offset: 0xEC (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCMP0;         /**< Offset: 0xF0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCMP0CLR;      /**< Offset: 0xF4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCMP0SET;      /**< Offset: 0xF8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCMP0INV;      /**< Offset: 0xFC (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCMPEN1;       /**< Offset: 0x100 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCMPEN1CLR;    /**< Offset: 0x104 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCMPEN1SET;    /**< Offset: 0x108 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCMPEN1INV;    /**< Offset: 0x10C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCMP1;         /**< Offset: 0x110 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCMP1CLR;      /**< Offset: 0x114 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCMP1SET;      /**< Offset: 0x118 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCMP1INV;      /**< Offset: 0x11C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved5[0x80];
  __IO  uint32_t                       ADC_ADFLTR0;        /**< Offset: 0x1A0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADFLTR0CLR;     /**< Offset: 0x1A4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADFLTR0SET;     /**< Offset: 0x1A8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADFLTR0INV;     /**< Offset: 0x1AC (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADFLTR1;        /**< Offset: 0x1B0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADFLTR1CLR;     /**< Offset: 0x1B4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADFLTR1SET;     /**< Offset: 0x1B8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADFLTR1INV;     /**< Offset: 0x1BC (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved6[0x40];
  __IO  uint32_t                       ADC_ADCTRG0;        /**< Offset: 0x200 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCTRG0CLR;     /**< Offset: 0x204 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCTRG0SET;     /**< Offset: 0x208 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCTRG0INV;     /**< Offset: 0x20C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCTRG1;        /**< Offset: 0x210 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCTRG1CLR;     /**< Offset: 0x214 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCTRG1SET;     /**< Offset: 0x218 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCTRG1INV;     /**< Offset: 0x21C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCTRG2;        /**< Offset: 0x220 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCTRG2CLR;     /**< Offset: 0x224 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCTRG2SET;     /**< Offset: 0x228 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCTRG2INV;     /**< Offset: 0x22C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved7[0x50];
  __IO  uint32_t                       ADC_ADCCMPCON0;     /**< Offset: 0x280 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCMPCON0CLR;  /**< Offset: 0x284 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCMPCON0SET;  /**< Offset: 0x288 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCMPCON0INV;  /**< Offset: 0x28C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCCMPCON1;     /**< Offset: 0x290 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCMPCON1CLR;  /**< Offset: 0x294 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCMPCON1SET;  /**< Offset: 0x298 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCMPCON1INV;  /**< Offset: 0x29C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved8[0x40];
  __IO  uint32_t                       ADC_ADCFSTAT;       /**< Offset: 0x2E0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCFSTATCLR;    /**< Offset: 0x2E4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCFSTATSET;    /**< Offset: 0x2E8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCFSTATINV;    /**< Offset: 0x2EC (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCFIFO;        /**< Offset: 0x2F0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCFIFOCLR;     /**< Offset: 0x2F4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCFIFOSET;     /**< Offset: 0x2F8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCFIFOINV;     /**< Offset: 0x2FC (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCBASE;        /**< Offset: 0x300 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCBASECLR;     /**< Offset: 0x304 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCBASESET;     /**< Offset: 0x308 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCBASEINV;     /**< Offset: 0x30C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCDMAST;       /**< Offset: 0x310 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCDMASTCLR;    /**< Offset: 0x314 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCDMASTSET;    /**< Offset: 0x318 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCDMASTINV;    /**< Offset: 0x31C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCCNTB;        /**< Offset: 0x320 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCCNTBCLR;     /**< Offset: 0x324 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCCNTBSET;     /**< Offset: 0x328 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCCNTBINV;     /**< Offset: 0x32C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCDMAB;        /**< Offset: 0x330 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCDMABCLR;     /**< Offset: 0x334 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCDMABSET;     /**< Offset: 0x338 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCDMABINV;     /**< Offset: 0x33C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCTRGSNS;      /**< Offset: 0x340 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCTRGSNSCLR;   /**< Offset: 0x344 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCTRGSNSSET;   /**< Offset: 0x348 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCTRGSNSINV;   /**< Offset: 0x34C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADTIM0;         /**< Offset: 0x350 (R/W  32)  */
  __IO  uint32_t                       ADC_ADTIM0CLR;      /**< Offset: 0x354 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADTIM0SET;      /**< Offset: 0x358 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADTIM0INV;      /**< Offset: 0x35C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved9[0x80];
  __IO  uint32_t                       ADC_ADCEISTAT1;     /**< Offset: 0x3E0 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCEISTAT1CLR;  /**< Offset: 0x3E4 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCEISTAT1SET;  /**< Offset: 0x3E8 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCEISTAT1INV;  /**< Offset: 0x3EC (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved10[0x10];
  __IO  uint32_t                       ADC_ADCANCON;       /**< Offset: 0x400 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCANCONCLR;    /**< Offset: 0x404 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCANCONSET;    /**< Offset: 0x408 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCANCONINV;    /**< Offset: 0x40C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved11[0x260];
  __IO  uint32_t                       ADC_ADCFGSHR;       /**< Offset: 0x670 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCFGSHRCLR;    /**< Offset: 0x674 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCFGSHRSET;    /**< Offset: 0x678 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCFGSHRINV;    /**< Offset: 0x67C (R/W  32) Bit invert register */
  __IO  uint32_t                       ADC_ADCSVCON;       /**< Offset: 0x680 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCSVCONCLR;    /**< Offset: 0x684 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCSVCONSET;    /**< Offset: 0x688 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCSVCONINV;    /**< Offset: 0x68C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved12[0x70];
  __IO  uint32_t                       ADC_ADCSYSCFG0;     /**< Offset: 0x700 (R/W  32)  */
  __IO  uint32_t                       ADC_ADCSYSCFG0CLR;  /**< Offset: 0x704 (R/W  32) Bit clear register */
  __IO  uint32_t                       ADC_ADCSYSCFG0SET;  /**< Offset: 0x708 (R/W  32) Bit set register */
  __IO  uint32_t                       ADC_ADCSYSCFG0INV;  /**< Offset: 0x70C (R/W  32) Bit invert register */
  __I   uint8_t                        Reserved13[0x300];
  __IO  uint32_t                       ADC_ADCDATA1;       /**< Offset: 0xA10 (R/W  32)  */
  __I   uint8_t                        Reserved14[0x0C];
  __IO  uint32_t                       ADC_ADCDATA2;       /**< Offset: 0xA20 (R/W  32)  */
  __I   uint8_t                        Reserved15[0x0C];
  __IO  uint32_t                       ADC_ADCDATA3;       /**< Offset: 0xA30 (R/W  32)  */
  __I   uint8_t                        Reserved16[0x0C];
  __IO  uint32_t                       ADC_ADCDATA4;       /**< Offset: 0xA40 (R/W  32)  */
  __I   uint8_t                        Reserved17[0x0C];
  __IO  uint32_t                       ADC_ADCDATA5;       /**< Offset: 0xA50 (R/W  32)  */
  __I   uint8_t                        Reserved18[0x0C];
  __IO  uint32_t                       ADC_ADCDATA6;       /**< Offset: 0xA60 (R/W  32)  */
  __I   uint8_t                        Reserved19[0x0C];
  __IO  uint32_t                       ADC_ADCDATA7;       /**< Offset: 0xA70 (R/W  32)  */
  __I   uint8_t                        Reserved20[0x0C];
  __IO  uint32_t                       ADC_ADCDATA8;       /**< Offset: 0xA80 (R/W  32)  */
  __I   uint8_t                        Reserved21[0x0C];
  __IO  uint32_t                       ADC_ADCDATA9;       /**< Offset: 0xA90 (R/W  32)  */
  __I   uint8_t                        Reserved22[0x0C];
  __IO  uint32_t                       ADC_ADCDATA10;      /**< Offset: 0xAA0 (R/W  32)  */
  __I   uint8_t                        Reserved23[0x0C];
  __IO  uint32_t                       ADC_ADCDATA11;      /**< Offset: 0xAB0 (R/W  32)  */
  __I   uint8_t                        Reserved24[0x0C];
  __IO  uint32_t                       ADC_ADCDATA12;      /**< Offset: 0xAC0 (R/W  32)  */
} adc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _BZ25_ADC_COMPONENT_H_ */
