/**
 * \file
 *
 * \brief SAM AES
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */

#ifndef _HRI_AES_E54_H_INCLUDED_
#define _HRI_AES_E54_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sysTypes.h>
#if defined(__ICCARM__)
#include <pic32cx1012bz25048_fpga.h>
#elif defined (__GNUC__)
#include <xc.h>
#endif

#include <component/aes.h>

#if defined(ENABLE_AES_CRITICAL_SECTIONS)
#define AES_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define AES_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define AES_CRITICAL_SECTION_ENTER()
#define AES_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_aes_ciplen_reg_t;
typedef uint32_t hri_aes_ctrla_reg_t;
typedef uint32_t hri_aes_ghash_reg_t;
typedef uint32_t hri_aes_hashkey_reg_t;
typedef uint32_t hri_aes_indata_reg_t;
typedef uint32_t hri_aes_intvectv_reg_t;
typedef uint32_t hri_aes_keyword_reg_t;
typedef uint32_t hri_aes_randseed_reg_t;
typedef uint8_t  hri_aes_ctrlb_reg_t;
typedef uint8_t  hri_aes_databufptr_reg_t;
typedef uint8_t  hri_aes_dbgctrl_reg_t;
typedef uint8_t  hri_aes_intenset_reg_t;
typedef uint8_t  hri_aes_intflag_reg_t;

static inline void hri_aes_set_INTEN_ENCCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTENSET = AES_INTENSET_ENCCMP(1);
}

static inline bool hri_aes_get_INTEN_ENCCMP_bit(const void *const hw)
{
	return ((AES_REGS->AES_INTENSET & AES_INTENSET_ENCCMP(1)) >> AES_INTENSET_ENCCMP_Pos);
}

static inline void hri_aes_write_INTEN_ENCCMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		AES_REGS->AES_INTENCLR = AES_INTENSET_ENCCMP(1);
	} else {
		AES_REGS->AES_INTENSET = AES_INTENSET_ENCCMP(1);
	}
}

static inline void hri_aes_clear_INTEN_ENCCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTENCLR = AES_INTENSET_ENCCMP(1);
}

static inline void hri_aes_set_INTEN_GFMCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTENSET = AES_INTENSET_GFMCMP(1);
}

static inline bool hri_aes_get_INTEN_GFMCMP_bit(const void *const hw)
{
	return ((AES_REGS->AES_INTENSET & AES_INTENSET_GFMCMP(1)) >> AES_INTENSET_GFMCMP_Pos);
}

static inline void hri_aes_write_INTEN_GFMCMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		AES_REGS->AES_INTENCLR = AES_INTENSET_GFMCMP(1);
	} else {
		AES_REGS->AES_INTENSET = AES_INTENSET_GFMCMP(1);
	}
}

static inline void hri_aes_clear_INTEN_GFMCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTENCLR = AES_INTENSET_GFMCMP(1);
}

static inline void hri_aes_set_INTEN_reg(const void *const hw, hri_aes_intenset_reg_t mask)
{
	AES_REGS->AES_INTENSET = mask;
}

static inline hri_aes_intenset_reg_t hri_aes_get_INTEN_reg(const void *const hw, hri_aes_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_INTENSET;
	tmp &= mask;
	return tmp;
}

static inline hri_aes_intenset_reg_t hri_aes_read_INTEN_reg(const void *const hw)
{
	return AES_REGS->AES_INTENSET;
}

static inline void hri_aes_write_INTEN_reg(const void *const hw, hri_aes_intenset_reg_t data)
{
	AES_REGS->AES_INTENSET = data;
	AES_REGS->AES_INTENCLR = ~data;
}

static inline void hri_aes_clear_INTEN_reg(const void *const hw, hri_aes_intenset_reg_t mask)
{
	AES_REGS->AES_INTENCLR = mask;
}

static inline bool hri_aes_get_INTFLAG_ENCCMP_bit(const void *const hw)
{
	return (AES_REGS->AES_INTFLAG & AES_INTFLAG_ENCCMP(1)) >> AES_INTFLAG_ENCCMP_Pos;
}

static inline void hri_aes_clear_INTFLAG_ENCCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTFLAG = AES_INTFLAG_ENCCMP(1);
}

static inline bool hri_aes_get_INTFLAG_GFMCMP_bit(const void *const hw)
{
	return (AES_REGS->AES_INTFLAG & AES_INTFLAG_GFMCMP(1)) >> AES_INTFLAG_GFMCMP_Pos;
}

static inline void hri_aes_clear_INTFLAG_GFMCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTFLAG = AES_INTFLAG_GFMCMP(1);
}

static inline bool hri_aes_get_interrupt_ENCCMP_bit(const void *const hw)
{
	return (AES_REGS->AES_INTFLAG & AES_INTFLAG_ENCCMP(1)) >> AES_INTFLAG_ENCCMP_Pos;
}

static inline void hri_aes_clear_interrupt_ENCCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTFLAG = AES_INTFLAG_ENCCMP(1);
}

static inline bool hri_aes_get_interrupt_GFMCMP_bit(const void *const hw)
{
	return (AES_REGS->AES_INTFLAG & AES_INTFLAG_GFMCMP(1)) >> AES_INTFLAG_GFMCMP_Pos;
}

static inline void hri_aes_clear_interrupt_GFMCMP_bit(const void *const hw)
{
	AES_REGS->AES_INTFLAG = AES_INTFLAG_GFMCMP(1);
}

static inline hri_aes_intflag_reg_t hri_aes_get_INTFLAG_reg(const void *const hw, hri_aes_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_INTFLAG;
	tmp &= mask;
	return tmp;
}

static inline hri_aes_intflag_reg_t hri_aes_read_INTFLAG_reg(const void *const hw)
{
	return AES_REGS->AES_INTFLAG;
}

static inline void hri_aes_clear_INTFLAG_reg(const void *const hw, hri_aes_intflag_reg_t mask)
{
	AES_REGS->AES_INTFLAG = mask;
}

static inline void hri_aes_write_KEYWORD_reg(const void *const hw, uint8_t index, hri_aes_keyword_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_KEYWORD[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_write_INTVECTV_reg(const void *const hw, uint8_t index, hri_aes_intvectv_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_INTVECTV[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_SWRST_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_SWRST(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_SWRST(1)) >> AES_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_aes_set_CTRLA_ENABLE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_ENABLE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_ENABLE(1)) >> AES_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_ENABLE(1);
	tmp |= value << AES_CTRLA_ENABLE_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_ENABLE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_ENABLE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_CIPHER(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_CIPHER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_CIPHER(1)) >> AES_CTRLA_CIPHER_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_CIPHER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_CIPHER(1);
	tmp |= value << AES_CTRLA_CIPHER_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_CIPHER(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_CIPHER(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_STARTMODE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_STARTMODE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_STARTMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_STARTMODE(1)) >> AES_CTRLA_STARTMODE_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_STARTMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_STARTMODE(1);
	tmp |= value << AES_CTRLA_STARTMODE_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_STARTMODE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_STARTMODE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_STARTMODE_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_STARTMODE(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_LOD(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_LOD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_LOD(1)) >> AES_CTRLA_LOD_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_LOD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_LOD(1);
	tmp |= value << AES_CTRLA_LOD_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_LOD(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_LOD(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_KEYGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_KEYGEN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_KEYGEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_KEYGEN(1)) >> AES_CTRLA_KEYGEN_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_KEYGEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_KEYGEN(1);
	tmp |= value << AES_CTRLA_KEYGEN_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_KEYGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_KEYGEN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_KEYGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_KEYGEN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_XORKEY_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_XORKEY(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLA_XORKEY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_XORKEY(1)) >> AES_CTRLA_XORKEY_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLA_XORKEY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_XORKEY(1);
	tmp |= value << AES_CTRLA_XORKEY_Pos;
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_XORKEY_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_XORKEY(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_XORKEY_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_XORKEY(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLA_AESMODE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_AESMODE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_get_CTRLA_AESMODE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_AESMODE(mask)) >> AES_CTRLA_AESMODE_Pos;
	return tmp;
}

static inline void hri_aes_write_CTRLA_AESMODE_bf(const void *const hw, hri_aes_ctrla_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_AESMODE_Msk;
	tmp |= AES_CTRLA_AESMODE(data);
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_AESMODE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_AESMODE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_AESMODE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_AESMODE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_read_CTRLA_AESMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_AESMODE_Msk) >> AES_CTRLA_AESMODE_Pos;
	return tmp;
}

static inline void hri_aes_set_CTRLA_CFBS_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_get_CTRLA_CFBS_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_CFBS(mask)) >> AES_CTRLA_CFBS_Pos;
	return tmp;
}

static inline void hri_aes_write_CTRLA_CFBS_bf(const void *const hw, hri_aes_ctrla_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_CFBS_Msk;
	tmp |= AES_CTRLA_CFBS(data);
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_CFBS_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_CFBS_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_read_CTRLA_CFBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_CFBS_Msk) >> AES_CTRLA_CFBS_Pos;
	return tmp;
}

static inline void hri_aes_set_CTRLA_KEYSIZE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_get_CTRLA_KEYSIZE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_KEYSIZE(mask)) >> AES_CTRLA_KEYSIZE_Pos;
	return tmp;
}

static inline void hri_aes_write_CTRLA_KEYSIZE_bf(const void *const hw, hri_aes_ctrla_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_KEYSIZE_Msk;
	tmp |= AES_CTRLA_KEYSIZE(data);
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_KEYSIZE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_KEYSIZE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_read_CTRLA_KEYSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_KEYSIZE_Msk) >> AES_CTRLA_KEYSIZE_Pos;
	return tmp;
}

static inline void hri_aes_set_CTRLA_CTYPE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= AES_CTRLA_CTYPE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_get_CTRLA_CTYPE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_CTYPE(mask)) >> AES_CTRLA_CTYPE_Pos;
	return tmp;
}

static inline void hri_aes_write_CTRLA_CTYPE_bf(const void *const hw, hri_aes_ctrla_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLA;
	tmp &= ~AES_CTRLA_CTYPE_Msk;
	tmp |= AES_CTRLA_CTYPE(data);
	AES_REGS->AES_CTRLA = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_CTYPE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~AES_CTRLA_CTYPE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_CTYPE_bf(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= AES_CTRLA_CTYPE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_read_CTRLA_CTYPE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp = (tmp & AES_CTRLA_CTYPE_Msk) >> AES_CTRLA_CTYPE_Pos;
	return tmp;
}

static inline void hri_aes_set_CTRLA_reg(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_get_CTRLA_reg(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CTRLA;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_CTRLA_reg(const void *const hw, hri_aes_ctrla_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLA_reg(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLA_reg(const void *const hw, hri_aes_ctrla_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLA ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrla_reg_t hri_aes_read_CTRLA_reg(const void *const hw)
{
	return AES_REGS->AES_CTRLA;
}

static inline void hri_aes_set_CTRLB_START_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB |= AES_CTRLB_START(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLB_START_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_CTRLB;
	tmp = (tmp & AES_CTRLB_START(1)) >> AES_CTRLB_START_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLB_START_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLB;
	tmp &= ~AES_CTRLB_START(1);
	tmp |= value << AES_CTRLB_START_Pos;
	AES_REGS->AES_CTRLB = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLB_START_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB &= ~AES_CTRLB_START(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLB_START_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB ^= AES_CTRLB_START(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLB_NEWMSG_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB |= AES_CTRLB_NEWMSG(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLB_NEWMSG_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_CTRLB;
	tmp = (tmp & AES_CTRLB_NEWMSG(1)) >> AES_CTRLB_NEWMSG_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLB_NEWMSG_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLB;
	tmp &= ~AES_CTRLB_NEWMSG(1);
	tmp |= value << AES_CTRLB_NEWMSG_Pos;
	AES_REGS->AES_CTRLB = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLB_NEWMSG_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB &= ~AES_CTRLB_NEWMSG(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLB_NEWMSG_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB ^= AES_CTRLB_NEWMSG(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLB_EOM_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB |= AES_CTRLB_EOM(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLB_EOM_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_CTRLB;
	tmp = (tmp & AES_CTRLB_EOM(1)) >> AES_CTRLB_EOM_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLB_EOM_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLB;
	tmp &= ~AES_CTRLB_EOM(1);
	tmp |= value << AES_CTRLB_EOM_Pos;
	AES_REGS->AES_CTRLB = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLB_EOM_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB &= ~AES_CTRLB_EOM(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLB_EOM_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB ^= AES_CTRLB_EOM(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLB_GFMUL_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB |= AES_CTRLB_GFMUL(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_CTRLB_GFMUL_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_CTRLB;
	tmp = (tmp & AES_CTRLB_GFMUL(1)) >> AES_CTRLB_GFMUL_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_CTRLB_GFMUL_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_CTRLB;
	tmp &= ~AES_CTRLB_GFMUL(1);
	tmp |= value << AES_CTRLB_GFMUL_Pos;
	AES_REGS->AES_CTRLB = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLB_GFMUL_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB &= ~AES_CTRLB_GFMUL(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLB_GFMUL_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB ^= AES_CTRLB_GFMUL(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_CTRLB_reg(const void *const hw, hri_aes_ctrlb_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrlb_reg_t hri_aes_get_CTRLB_reg(const void *const hw, hri_aes_ctrlb_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_CTRLB;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_CTRLB_reg(const void *const hw, hri_aes_ctrlb_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CTRLB_reg(const void *const hw, hri_aes_ctrlb_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CTRLB_reg(const void *const hw, hri_aes_ctrlb_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CTRLB ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ctrlb_reg_t hri_aes_read_CTRLB_reg(const void *const hw)
{
	return AES_REGS->AES_CTRLB;
}

static inline void hri_aes_set_DATABUFPTR_INDATAPTR_bf(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR |= AES_DATABUFPTR_INDATAPTR(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_databufptr_reg_t hri_aes_get_DATABUFPTR_INDATAPTR_bf(const void *const        hw,
                                                                           hri_aes_databufptr_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_DATABUFPTR;
	tmp = (tmp & AES_DATABUFPTR_INDATAPTR(mask)) >> AES_DATABUFPTR_INDATAPTR_Pos;
	return tmp;
}

static inline void hri_aes_write_DATABUFPTR_INDATAPTR_bf(const void *const hw, hri_aes_databufptr_reg_t data)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_DATABUFPTR;
	tmp &= ~AES_DATABUFPTR_INDATAPTR_Msk;
	tmp |= AES_DATABUFPTR_INDATAPTR(data);
	AES_REGS->AES_DATABUFPTR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_DATABUFPTR_INDATAPTR_bf(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR &= ~AES_DATABUFPTR_INDATAPTR(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_DATABUFPTR_INDATAPTR_bf(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR ^= AES_DATABUFPTR_INDATAPTR(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_databufptr_reg_t hri_aes_read_DATABUFPTR_INDATAPTR_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_DATABUFPTR;
	tmp = (tmp & AES_DATABUFPTR_INDATAPTR_Msk) >> AES_DATABUFPTR_INDATAPTR_Pos;
	return tmp;
}

static inline void hri_aes_set_DATABUFPTR_reg(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_databufptr_reg_t hri_aes_get_DATABUFPTR_reg(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_DATABUFPTR;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_DATABUFPTR_reg(const void *const hw, hri_aes_databufptr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_DATABUFPTR_reg(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_DATABUFPTR_reg(const void *const hw, hri_aes_databufptr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DATABUFPTR ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_databufptr_reg_t hri_aes_read_DATABUFPTR_reg(const void *const hw)
{
	return AES_REGS->AES_DATABUFPTR;
}

static inline void hri_aes_set_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL |= AES_DBGCTRL_DBGRUN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_DBGCTRL;
	tmp = (tmp & AES_DBGCTRL_DBGRUN(1)) >> AES_DBGCTRL_DBGRUN_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_DBGCTRL_DBGRUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = AES_REGS->AES_DBGCTRL;
	tmp &= ~AES_DBGCTRL_DBGRUN(1);
	tmp |= value << AES_DBGCTRL_DBGRUN_Pos;
	AES_REGS->AES_DBGCTRL = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL &= ~AES_DBGCTRL_DBGRUN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL ^= AES_DBGCTRL_DBGRUN(1);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_DBGCTRL_reg(const void *const hw, hri_aes_dbgctrl_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_dbgctrl_reg_t hri_aes_get_DBGCTRL_reg(const void *const hw, hri_aes_dbgctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = AES_REGS->AES_DBGCTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_DBGCTRL_reg(const void *const hw, hri_aes_dbgctrl_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_DBGCTRL_reg(const void *const hw, hri_aes_dbgctrl_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_DBGCTRL_reg(const void *const hw, hri_aes_dbgctrl_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_DBGCTRL ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_dbgctrl_reg_t hri_aes_read_DBGCTRL_reg(const void *const hw)
{
	return AES_REGS->AES_DBGCTRL;
}

static inline void hri_aes_set_INDATA_reg(const void *const hw, hri_aes_indata_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_INDATA |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_indata_reg_t hri_aes_get_INDATA_reg(const void *const hw, hri_aes_indata_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_INDATA;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_INDATA_reg(const void *const hw, hri_aes_indata_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_INDATA = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_INDATA_reg(const void *const hw, hri_aes_indata_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_INDATA &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_INDATA_reg(const void *const hw, hri_aes_indata_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_INDATA ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_indata_reg_t hri_aes_read_INDATA_reg(const void *const hw)
{
	return AES_REGS->AES_INDATA;
}

static inline void hri_aes_set_HASHKEY_reg(const void *const hw, uint8_t index, hri_aes_hashkey_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_HASHKEY[index] |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_hashkey_reg_t hri_aes_get_HASHKEY_reg(const void *const hw, uint8_t index,
                                                            hri_aes_hashkey_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_HASHKEY[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_HASHKEY_reg(const void *const hw, uint8_t index, hri_aes_hashkey_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_HASHKEY[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_HASHKEY_reg(const void *const hw, uint8_t index, hri_aes_hashkey_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_HASHKEY[index] &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_HASHKEY_reg(const void *const hw, uint8_t index, hri_aes_hashkey_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_HASHKEY[index] ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_hashkey_reg_t hri_aes_read_HASHKEY_reg(const void *const hw, uint8_t index)
{
	return AES_REGS->AES_HASHKEY[index];
}

static inline void hri_aes_set_GHASH_reg(const void *const hw, uint8_t index, hri_aes_ghash_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_GHASH[index] |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghash_reg_t hri_aes_get_GHASH_reg(const void *const hw, uint8_t index, hri_aes_ghash_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_GHASH[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_GHASH_reg(const void *const hw, uint8_t index, hri_aes_ghash_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_GHASH[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_GHASH_reg(const void *const hw, uint8_t index, hri_aes_ghash_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_GHASH[index] &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_GHASH_reg(const void *const hw, uint8_t index, hri_aes_ghash_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_GHASH[index] ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghash_reg_t hri_aes_read_GHASH_reg(const void *const hw, uint8_t index)
{
	return AES_REGS->AES_GHASH[index];
}

static inline void hri_aes_set_CIPLEN_reg(const void *const hw, hri_aes_ciplen_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CIPLEN |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ciplen_reg_t hri_aes_get_CIPLEN_reg(const void *const hw, hri_aes_ciplen_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_CIPLEN;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_CIPLEN_reg(const void *const hw, hri_aes_ciplen_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CIPLEN = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CIPLEN_reg(const void *const hw, hri_aes_ciplen_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CIPLEN &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CIPLEN_reg(const void *const hw, hri_aes_ciplen_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_CIPLEN ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ciplen_reg_t hri_aes_read_CIPLEN_reg(const void *const hw)
{
	return AES_REGS->AES_CIPLEN;
}

static inline void hri_aes_set_RANDSEED_reg(const void *const hw, hri_aes_randseed_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_RANDSEED |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_randseed_reg_t hri_aes_get_RANDSEED_reg(const void *const hw, hri_aes_randseed_reg_t mask)
{
	uint32_t tmp;
	tmp = AES_REGS->AES_RANDSEED;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_RANDSEED_reg(const void *const hw, hri_aes_randseed_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_RANDSEED = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_RANDSEED_reg(const void *const hw, hri_aes_randseed_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_RANDSEED &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_RANDSEED_reg(const void *const hw, hri_aes_randseed_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	AES_REGS->AES_RANDSEED ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_randseed_reg_t hri_aes_read_RANDSEED_reg(const void *const hw)
{
	return AES_REGS->AES_RANDSEED;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_AES_E54_H_INCLUDED */
