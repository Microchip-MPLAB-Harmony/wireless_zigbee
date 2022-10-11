/**************************************************************************//**
  \file  halFlash.c

  \brief Implementation of flash access hardware-dependent module.

  \author
      Microchip Corporation: http://ww.microchip.com \n
      Support email: support@microchip.com

    Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
    Licensed under Microchip's Limited License Agreement.

  \internal
  History:
    07/04/14 karthik.p_u - Created
  Last change:
    $Id: halFlash.c 25824 2013-12-10 08:44:12Z mahendran.p $
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#if defined(HAL_USE_FLASH_ACCESS)

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <halFlash.h>
#if defined(HAL_USE_EE_READY)
#if defined(HAL_USE_EEPROM_EMULATION)
#include <halEeprom.h>
#endif
#endif
#include <halDbg.h>

#include <Pic32cx_Miscellaneous.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define FLASH_READY() (NVMCTRL_INTFLAG & NVMCTRL_INTFLAG_READY)

/******************************************************************************
                   Local variables section
******************************************************************************/
static uint32_t pageBufferToFill[ROW_SIZE_IN_HALF_WORDS];

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Implementations section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes the flash.
  \param[in] None
******************************************************************************/
void halInitFlash(void)
{
  //: check if Flash init. value is all 1 ---
  //NOTE : do this verification one time only when FPGA power-up
//  for(uint32_t i=0;i<(256*4*64*4);i++)
//    if((*(uint32_t *)(0x01000000+i*4)) !=0xffffffff )
//	{
//     	  while(1) {}
//    }  

#if defined(HAL_USE_EE_READY)
#if defined(HAL_USE_EEPROM_EMULATION)
  halInitEepromEmulator();
#endif
#endif
}
/* this function is not required*/
/**************************************************************************//**
  \brief Writes data to the page buffer.
  \param[in] startOffset - start position for writing within the page
  \param[in] length - data to write length in bytes
  \param[in] data - pointer to data to write
******************************************************************************/
void halFillFlashPageBuffer(uint32_t startOffset, uint16_t length, uint8_t *data)
{
  // Page size is 64 Bytes so that Row size becomes 4*64 = 256 Bytes
  // max. value of length may be 256 Bytes
  uint32_t unalignedWord;
  uint32_t alignedWord;
  uint8_t wordPos;

  if (startOffset % ROW_SIZE + length > ROW_SIZE)
  {
    // leaking into next row & abort the file operation
    sysAssert(false, FLASH_PAGEFILLBUFFERINCORRECTOFFSET_0);
    return;
  }

  // Initialize the page buffer
  for (uint16_t index = 0; index < ROW_SIZE_IN_HALF_WORDS; index++)
    pageBufferToFill[index] = 0xFFFFFFFF;
  // Check, if first byte of current data is unaligned
  uint8_t noOfBytesTobeAliagned = startOffset % 4;
  if(noOfBytesTobeAliagned)
  {
    /* Fill it as a MSB of a word */
    unalignedWord = (0xFFFFFFFF >> noOfBytesTobeAliagned*8) | ((uint32_t)*data++ << ((startOffset % 4)*8));
    wordPos = (startOffset % ROW_SIZE - noOfBytesTobeAliagned) / 4;
    pageBufferToFill[wordPos] = unalignedWord;
    startOffset++;
    length--;
  }

  // Handle if the last byte is not aligned
  if (length % 4)
  {
    unalignedWord = (0xFFFFFFFF << noOfBytesTobeAliagned*8)| data[length - noOfBytesTobeAliagned];
    wordPos = (startOffset % ROW_SIZE + length - noOfBytesTobeAliagned) / 4 ;
    pageBufferToFill[wordPos] = unalignedWord;
    length--;
  }

  // Copy the remaining aligneed bytes to page buffer
  for (uint16_t index =0; index < length/4; index++)
  {
    wordPos = startOffset % ROW_SIZE / 4;
    alignedWord = *data++;
    alignedWord = alignedWord | (*data++ << 8);
    alignedWord = alignedWord | (*data++ << 16);
    alignedWord = alignedWord | (*data++ << 24);
    pageBufferToFill[wordPos] = alignedWord;
    startOffset += 4;
  }
}

/**************************************************************************//**
  \brief Erases specified flash page.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halEraseFlashPage(uint32_t pageStartAddress)
{
  unsigned int flash_address;
  unsigned int data_to_read;
  unsigned int EraCheCnt;
  unsigned int i;
   
  //------------------------------------
  //	 variable initialization
  //------------------------------------
  flash_address = ( (0x010<<20) | (pageStartAddress<<12) ) & 0xfffff000;
  EraCheCnt = 0;

  //------------------------------------
  //	 sector[page] erase
  //------------------------------------
  SFR_NVMADDR    = flash_address;   
  SFR_NVMCON	   = 0x00004004;//wren and set-up for page erase			   
  SFR_NVMKEY	   = 0x00000000;
  SFR_NVMKEY	   = 0xAA996655;//unlock key								   
  SFR_NVMKEY	   = 0x556699AA;//unlock key
  SFR_NVMCON_SET = 0x00008000;//start write							   

  //Waiting for flash page erase done
  do {
	for (i=0 ; i<=5; i++) asm("nop");
	   data_to_read = SFR_NVMCON;
  } while ((data_to_read & 0x00008000 )!=0x00000000);
  SFR_NVMCON_CLR = 0x00004000;																 

  data_to_read = SFR_NVMCON; 

  //------------------------------------
  //	sector[page] data check after erase   
  //------------------------------------
  //64-word x 140-bit/wrod --> 64 x (32-bit x 4 ) = 256 x 32-bit
  for( i = 0; i < 256; i++ )
  {
	if( (*((volatile unsigned int*) (flash_address+i*4) )) != 0xffffffff ) 
	EraCheCnt++;
  } 
  // Check successful write
  if( EraCheCnt != 0 ) 
  {
  	  while(1) {}
  }

}
/* This function is not required now */
/**************************************************************************//**
  \brief Writes flash page buffer without erasing.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halWriteFlashPage(uint32_t pageStartAddress)
{
  if (pageStartAddress % ROW_SIZE)
    pageStartAddress = pageStartAddress - (pageStartAddress % ROW_SIZE);

  uint32_t data_to_read;
  uint32_t i;

  for (uint8_t wordCnt = 0; wordCnt < ROW_SIZE/4; wordCnt++)
  {
    if ( pageBufferToFill[wordCnt]== 0xffffffff) //workaround
         continue;
	SFR_NVMDATA	 = pageBufferToFill[wordCnt];
	SFR_NVMADDR	 = (pageStartAddress & 0xfffffffc);  
	SFR_NVMCON	 = 0x00004001;			  
	SFR_NVMKEY	 = 0x00000000;
	SFR_NVMKEY	 = 0xAA996655;			  //unlock key
	SFR_NVMKEY	 = 0x556699AA;			  //unlock key
	SFR_NVMCON_SET = 0x00008000;			  //start write
		  
	//Waiting for flash program done
	do
	{
	   for (i=0 ; i<=5; i++) asm("nop");
		  data_to_read = SFR_NVMCON;
	} while ((data_to_read & 0x00008000 )!=0x00000000);	 
	SFR_NVMCON_CLR = 0x00004000;
		  
	do
	{
		for (i=0 ; i<=5; i++) asm("nop");
	  	  data_to_read = SFR_NVMCON;
	} while ((data_to_read & 0x00004000 )!=0x00000000);  
                  
    pageStartAddress += sizeof(pageBufferToFill[wordCnt]);
  }
}

/******************************************************************************
  \brief Writes the data 32 bit wise in the flash without erasing.
  \param[in] pageStflashAddress - address within the flash
  \length[in] length - legth of the data to be written
  \dtat[in]  - data to be written into the flash
******************************************************************************/
void halWriteFlash32BitData(uint32_t flashAddress, uint16_t length, uint8_t *data )
{
  uint32_t pageBuffer[256];
  uint8_t  noOfBytesTobeAliagned = (length % 4);

  uint16_t alignedLength = length;
  uint32_t data_to_read;
  
  if(noOfBytesTobeAliagned)
     alignedLength = length - noOfBytesTobeAliagned + 4;
  
  for (uint16_t index = 0; index < alignedLength/4; index++)
  {
    uint32_t alignedWord = 0xFFFFFFFF;
    alignedWord = *data++;
    alignedWord = alignedWord | (*data++ << 8);
    alignedWord = alignedWord | (*data++ << 16);
    alignedWord = alignedWord | (*data++ << 24);
    pageBuffer[index] = alignedWord;
  }
  
  //handle last byte 
//  if (noOfBytesTobeAliagned)
//  {
//    uint32_t unalignedWord = (0xFFFFFFFF << noOfBytesTobeAliagned*8)| data[length - noOfBytesTobeAliagned];
//    uint8_t wordPos = length/4;
//    pageBuffer[wordPos] = unalignedWord;
//  }
  
  for (uint16_t wordCnt = 0; wordCnt < alignedLength/4; wordCnt++)
  {
    SFR_NVMDATA	 = pageBuffer[wordCnt];
    SFR_NVMADDR	 = (flashAddress & 0xfffffffc);  
    SFR_NVMCON	 = 0x00004001;			  
    SFR_NVMKEY	 = 0x00000000;
    SFR_NVMKEY	 = 0xAA996655;			  //unlock key
    SFR_NVMKEY	 = 0x556699AA;			  //unlock key
    SFR_NVMCON_SET = 0x00008000;		  //start write
    
    //Waiting for flash program done
    do {
          for (uint8_t i=0 ; i<=5; i++) asm("nop");
          data_to_read = SFR_NVMCON;
    } while ((data_to_read & 0x00008000 )!=0x00000000);	 
    SFR_NVMCON_CLR = 0x00004000;
    
    do {
          for (uint8_t i=0 ; i<=5; i++) asm("nop");
          data_to_read = SFR_NVMCON;
    } while ((data_to_read & 0x00004000 )!=0x00000000);
    
    flashAddress += sizeof(uint32_t);
  } 
}


#endif  // defined(HAL_USE_FLASH_ACCESS)
