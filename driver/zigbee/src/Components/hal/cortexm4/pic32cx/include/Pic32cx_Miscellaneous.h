/*******************************************************************************
  PIC32CX Miscellaneous Header File

  Company:
    Microchip Technology Inc.

  File Name:
    pic32cx_miscellaneous.h

  Summary:
    This file contains the box of pic32cx miscellaneous items for the project.

  Description:
    This file contains the box of pic32cx miscellaneous items for the project.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

//
// 2019.3.4 JY created this file for the basic sanity test of Pic32cx GPIO
//
#ifndef PIC32CX_MISCELLANEOUS_H_INCLUDED
#define PIC32CX_MISCELLANEOUS_H_INCLUDED 

//#include <compiler.h>

//2019.3.7 JY
//NOTE : 16-byte offset per each 32-bit register
#define PORTA_BASEADDR  0x44002200UL
    #define ANSELA       (PORTA_BASEADDR + 0x00)
    #define TRISA        (PORTA_BASEADDR + 0x10)   
    #define PORTA        (PORTA_BASEADDR + 0x20)   
    #define LATA         (PORTA_BASEADDR + 0x30)   
    #define CNPUA        (PORTA_BASEADDR + 0x50)  //pull up
    #define CNPDA        (PORTA_BASEADDR + 0x60)  //pull down

#define PORTB_BASEADDR  0x44002300UL                     
    #define ANSELB       (PORTB_BASEADDR + 0x00)
    #define TRISB        (PORTB_BASEADDR + 0x10)   
    #define PORTB        (PORTB_BASEADDR + 0x20)   
    #define LATB         (PORTB_BASEADDR + 0x30)    
    #define CNPUB        (PORTB_BASEADDR + 0x50)  //pull up
    #define CNPDB        (PORTB_BASEADDR + 0x60)  //pull down


//2019.4.19 JY; for Flash access test
#define SFR_NVMCON      (*((volatile unsigned int*) (0x44000600) )) 
#define SFR_NVMCON_CLR  (*((volatile unsigned int*) (0x44000604) ))
#define SFR_NVMCON_SET  (*((volatile unsigned int*) (0x44000608) ))
#define SFR_NVMKEY      (*((volatile unsigned int*) (0x44000620) )) 
#define SFR_NVMADDR     (*((volatile unsigned int*) (0x44000630) )) 
#define SFR_NVMDATA     (*((volatile unsigned int*) (0x44000640) )) 
#define SFR_NVMDATA1    (*((volatile unsigned int*) (0x44000650) )) 
#define SFR_NVMDATA2    (*((volatile unsigned int*) (0x44000660) )) 
#define SFR_NVMDATA3    (*((volatile unsigned int*) (0x44000670) )) 
#define SFR_NVMSRCADDR  (*((volatile unsigned int*) (0x440006c0) ))



void set_pin_as_output            (char * /*port type: "PA", "PB"*/, uint8_t /*pin number: 0~15*/);
void write_data_to_pin            (char * /*port type: "PA", "PB"*/, uint8_t /*pin number: 0~15*/, uint16_t /*set pin value: 0 or 1*/);
void single_pin_output_drive_test (char * /*port type: "PA", "PB"*/, uint8_t /*pin number: 0~15*/);
void delay();
void GPIO_output_data(uint16_t);
void GPIO_init();

//--------------------------------------------
//2019.4.29 JY
//Flash operation through Flash controller
//--------------------------------------------

// return 0 : erase successfully;     return 1 : erase fail
int Flash_sector_erase(uint8_t );

// return 0 : erase successfully;     return 1 : erase fail
int Flash_chip_erase();

// return 0: program success;         return 2: data program fail
int Flash_row_program(uint8_t , uint8_t , uint32_t );


void Flash_32bitDATA_program(uint32_t , uint32_t ); 

// return 0: program success;         return 2: data program fail
int Flash_Word_Program(uint32_t , uint32_t , uint32_t , uint32_t , uint32_t );

#endif 
