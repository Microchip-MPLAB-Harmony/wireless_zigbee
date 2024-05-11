/*******************************************************************************
 System Initialization File

  Company:
    Microchip Technology Inc.

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains implementation of "SYS_Initialize" function requiered for
    MPLAB Harmony system initialization to initialize all system components.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#ifdef __XC32__
#include <xc.h>
#endif
#include "compiler.h"

#ifdef _USE_RTOS_
#include "osal_freertos_extend.h"
#include "framework_defs.h"
#include <zgb_task.h>
#endif

#include <RF231_RF212/PHY/include/phyPic32cx.h>
#include "calibration.h"

#ifdef _ENABLE_PERSISTENT_SERVER_
#include <wlPdsMemIDs.h>
#include <nvm/plib_nvm.h>
#endif

#ifdef TRNG_MODULE_ENABLED
#include <trng/plib_trng.h>
#endif

#define VECTOR_TABLE_SIZE (128)
#define QUEUE_LENGTH (8)
#define QUEUE_ITEM_SIZE (sizeof(void *))

#ifdef __XC32__
uint32_t sram_vector_table[VECTOR_TABLE_SIZE] __attribute__((aligned(VECTOR_TABLE_SIZE * 4)));
#else
//__no_init uint32_t sram_vector_table[VECTOR_TABLE_SIZE] @ 0x20000000;
#pragma data_alignment = VECTOR_TABLE_SIZE * 4
uint32_t sram_vector_table[VECTOR_TABLE_SIZE];
#endif

#ifdef _USE_RTOS_
OSAL_API_LIST_TYPE     osalAPIList;
OSAL_QUEUE_HANDLE_TYPE zigbeeRequestQueueHandle;

extern void APP_ZB_StackCallBack(void *response);
extern void create_app_queue(void);
#else
extern void zigbee_init(uint32_t *sram_vector_table);
#endif

#ifdef __XC32__
void system_pll_clock_init(void);

static void PLL_Configure(void);

/******************************************************************************
                    Implementations section
******************************************************************************/

void CMCC_Init_icdis_dcdis(uint8_t icdis, uint8_t dcdis)
{
    // Disable CMCC first
    CMCC_REGS->CMCC_CTRL = CMCC_CTRL_CEN(0);
    //cc->CMCC_CTRL = CMCC_CTRL_CEN(0);
  
    // Cache Controller Software Reset and wait the reset done (check status bit)
    CMCC_REGS->CMCC_MCTRL = CMCC_MCTRL_SWRST(1);
    while((CMCC_REGS->CMCC_SR & CMCC_SR_CSTS_Msk) == 1);

    // Enable I & D cache, set cache size to 4KB
    CMCC_REGS->CMCC_CFG = (CMCC_CFG_ICDIS(icdis)  
                    |CMCC_CFG_DCDIS(dcdis)
                    |CMCC_CFG_CSIZESW(CMCC_CFG_CSIZESW_CONF_CSIZE_4KB_Val ));

    // Enable CMCC again
    CMCC_REGS->CMCC_CTRL = CMCC_CTRL_CEN(1);
}
#endif
/*******************************************************************************
  Function:
    void SYS_Initialize(void *p)

  Remarks:
    See prototype in initialization.h.
*/
void SYS_Initialize(void *p)
{
#ifdef __XC32__
    CMCC_Init_icdis_dcdis(0, 1);
#endif

    system_pll_clock_init();

    uint32_t *flash_vector_table     = (uint32_t *)0x00000000;

#ifdef _USE_RTOS_
    osalAPIList.OSAL_CRIT_Enter      = OSAL_CRIT_Enter;
    osalAPIList.OSAL_CRIT_Leave      = OSAL_CRIT_Leave;

    osalAPIList.OSAL_SEM_Create      = OSAL_SEM_Create;
    osalAPIList.OSAL_SEM_Pend        = OSAL_SEM_Pend;
    osalAPIList.OSAL_SEM_Post        = OSAL_SEM_Post;
    osalAPIList.OSAL_SEM_PostISR     = OSAL_SEM_PostISR;
    osalAPIList.OSAL_SEM_GetCount    = OSAL_SEM_GetCount;

    osalAPIList.OSAL_QUEUE_Create    = OSAL_QUEUE_Create;
    osalAPIList.OSAL_QUEUE_Send      = OSAL_QUEUE_Send;
    osalAPIList.OSAL_QUEUE_SendISR   = OSAL_QUEUE_SendISR;
    osalAPIList.OSAL_QUEUE_Receive   = OSAL_QUEUE_Receive;
    osalAPIList.OSAL_QUEUE_IsFullISR = OSAL_QUEUE_IsFullISR;

    osalAPIList.OSAL_QUEUE_CreateSet = OSAL_QUEUE_CreateSet;
    osalAPIList.OSAL_QUEUE_AddToSet  = OSAL_QUEUE_AddToSet;
    osalAPIList.OSAL_QUEUE_SelectFromSet = OSAL_QUEUE_SelectFromSet;

    OSAL_QUEUE_Create(&zigbeeRequestQueueHandle, QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    create_app_queue();
#endif

    // initialize the vector table in SRAM from the vector table in flash
    for (uint32_t i = 0; i < VECTOR_TABLE_SIZE; i++)
    {
        sram_vector_table[i] = flash_vector_table[i];
    }
    
    // TODO: initialize arbiter - arbiter common initialization
    ARB_REGS->ARB_EVENT_CTRL = 0x471;
    ARB_REGS->ARB_INT_MASK = 0x7F;      //0x80 //0x3F // Mask Arbiter IDLE Mask
    ARB_REGS->ARB_ZB_CTRL = 0x13;       // Maximum Time from abort_bt assertion to task_complete_bt assertion = 19 uSec
    ARB_REGS->ARB_CORE_CTRL = 0x40;     // Release Arbiter Core State Machine from Reset

    // set the ARM core Vector Table Offset Register value to the sram vector table
    // from now on the ARM core will use the new vecrtor table to handle the exceptions.
    SCB->VTOR = (uint32_t)&sram_vector_table;
#ifdef _ENABLE_PERSISTENT_SERVER_
  NVM_Initialize();
  PDS_Init(PDS_ZB_MAX_ITEMS_AMOUNT, PDS_ZB_MAX_DIR_MEM_ID_AMOUNT);
#endif

#ifdef _USE_RTOS_
    // initialize zigbee stack
    zigbee_init(sram_vector_table, &osalAPIList, &zigbeeRequestQueueHandle, (ZB_AppGenericCallBack)&APP_ZB_StackCallBack);
 #else
    zigbee_init(sram_vector_table);
#endif
#ifdef TRNG_MODULE_ENABLED
    // initialize true random number generator
    TRNG_Initialize();
    NVIC_DisableIRQ((IRQn_Type)TRNG_IRQn);
    NVIC_SetPriority((IRQn_Type)TRNG_IRQn, 6);
    NVIC_ClearPendingIRQ((IRQn_Type)TRNG_IRQn);
    NVIC_EnableIRQ((IRQn_Type)TRNG_IRQn);
#endif
}


/***************************************************************************//**
\brief System PLL Initialization
*******************************************************************************/
void Clock_System()
{
   volatile uint32_t reg_32;
   
   //Clock Enable 
    CRU_REGS->CRU_REFO1CON = 0x9907;    // Maping Sys clock onto REFO1
    //PPS_REGS->PPS_RPB12G1R = 0x13;      // Map REFO1 to RPB12
    
    CRU_REGS->CRU_REFO2CON = 0x9905;    // Maping SPLL1 clock onto REFO2
    //PPS_REGS->PPS_RPB13G2R = 0x13;      // Map REFO2 to RPB13
    
    CFG_REGS->CFG_SYSKEY = 0x00000000; // Write junk to lock it if it is already unlocked
    CFG_REGS->CFG_SYSKEY = 0xAA996655;
    CFG_REGS->CFG_SYSKEY = 0x556699AA;

#if (CPU_CLK_HZ == 48000000 )    
    // Set SPLL1DIV=2 to generate 48MHz clock from 96MHz PLL Clock
    CRU_REGS->CRU_SPLLCONSET = 0x00000200;    // 48 MHz
#elif (CPU_CLK_HZ ==64000000 )    
    // Set SPLL1DIV=1.5 to generate 64MHz clock from 96MHz PLL Clock
    CRU_REGS->CRU_SPLLCONSET = 0x00000100;      // 64 MHz
#endif    
    // Power up the PLL. SPLLPWDN=0
    CRU_REGS->CRU_SPLLCONCLR = 0x00000008;

    // Configure OSCCON to Switch to SPLL_CLK1
    CRU_REGS->CRU_OSCCONSET = 0x00000101;

    do {
        reg_32 = CRU_REGS->CRU_OSCCON;
    } while ((reg_32 & 0x00000001) != 0x00000000);

    CFG_REGS->CFG_SYSKEY = 0x00000000; // Write junk to lock it if it is already unlocked

    CFG_REGS->CFG_CFGPCLKGEN1 = 0x00909000; // Provide GCLK to SERCOM + TCC2
    CFG_REGS->CFG_CFGPCLKGEN3 = 0x09000000; // Provide GCLK to TC0
   
    // Change src_clk source to PLL CLK
    reg_32 = z_readReg32(SUBSYS_CNTRL_REG1_ADDR);
    reg_32 |= 0x00000010;
    z_reg_write32(SUBSYS_CNTRL_REG1_ADDR,reg_32);
    
    // set bt_en_main_clk[20], bt_pdc_ov[16], zb_en_main_clk[4]
    reg_32 = 0x01100010;
    z_reg_write32(SUBSYS_CNTRL_REG0_ADDR,reg_32);
}

/***************************************************************************//**
\brief System PLL Initialization
*******************************************************************************/
void system_pll_clock_init(void) 
{
    volatile uint32_t reg_32;

    // wait for xtal_ready      
    do {
        reg_32 = readl(SUBSYS_STATUS_REG1);
    } while ((reg_32 & 0x01) != 0x1);
    
    // set PLL_en
    z_do_bitwr8(BT_ana_ip_ctrl_reg2_hl_addr, 0x02, 0x00);
    do {
        reg_32 = z_do_bitrd32(SUBSYS_STATS_REG1_ADDR, 0x03);
    } while ((reg_32 & 0x03) != 0x03);   
    
    //Enable Clock
    Clock_System();
    
    //RF PLL Frequency set to 96 MHZ
    PLL_Configure();
    
    //RF_Cal_Init();
    //RF_Calibration(); // New RF Set - Todo
}


/***************************************************************************//**
\brief PLL Configuration Values for the Board
*******************************************************************************/
static void FPGA_Board_Calib_Values(void)
{
  // My Board 26 Calibration Values- Yog , Change this value set based on the FPGA number.
 spi_write(0x08,0xE35A);
 spi_write(0x62,0x36FF);
 spi_write(0x0A,0xE35A);
 spi_write(0x63,0x36E0);
 spi_write(0x81,0xE35A);
 spi_write(0x80,0x37FF);
 spi_write(0x83,0xE35A);
 spi_write(0x82,0x37FA);
 spi_write(0x85,0xE35A);
 spi_write(0x84,0x37F5);
 spi_write(0x87,0xE35A);
 spi_write(0x86,0x37F2);
 spi_write(0x89,0xE35A);
 spi_write(0x88,0x37EA);
 spi_write(0x8B,0xE35A);
 spi_write(0x8A,0x37E0);
 spi_write(0x8D,0xE35A);
 spi_write(0x8C,0x37D6);
 spi_write(0x7D,0x2125);
 spi_write(0x75,0x2125);
 spi_write(0x3D,0xE356);
 spi_write(0x64,0x2CFF);
 spi_write(0x3F,0xE356);
 spi_write(0x65,0x2CBC);
 spi_write(0x45,0xE356);
 spi_write(0x66,0x2CA5);
 spi_write(0x4D,0xE356);
 spi_write(0x67,0x2C98);
 spi_write(0x36,0xE356);
 spi_write(0x37,0x2C8D);
 spi_write(0x38,0xE356);
 spi_write(0x39,0x2C87);
 spi_write(0x8F,0xE356);
 spi_write(0x8E,0x2DFB);
 spi_write(0x91,0xE356);
 spi_write(0x90,0x2DED);
 spi_write(0x93,0xE356);
 spi_write(0x92,0x2DE0);
 spi_write(0x95,0xE356);
 spi_write(0x94,0x2DD6);
 spi_write(0x97,0xE356);
 spi_write(0x96,0x2DCA);
 spi_write(0x99,0xE356);
 spi_write(0x98,0x2DC0);
 spi_write(0x9B,0xE356);
 spi_write(0x9A,0x2D96);
 spi_write(0x9D,0xE356);
 spi_write(0x9C,0x2D90);
 spi_write(0x9F,0xE356);
 spi_write(0x9E,0x2D8A);
 spi_write(0x6A,0x2124);
 spi_write(0x49,0x2124);
 spi_write(0x14,0x02BE);
 spi_write(0x17,0x40E0);
 spi_write(0x18,0x44A0);
 spi_write(0x19,0xCAA6);
 spi_write(0x44,0xCA26);
 spi_write(0x48,0xCA07);
}

/***************************************************************************//**
\brief PLL Configuration Values for the RF and Board
*******************************************************************************/
static void PLL_Configure(void)
{
  spi_write(0x00, 0x0053);
  spi_write(0x01, 0x165A);
  spi_write(0x02, 0x4800);
  spi_write(0x03, 0x0A3C);
  spi_write(0x04, 0x0A30);
  spi_write(0x05, 0x32A5);
  spi_write(0x06, 0x0300);
  spi_write(0x07, 0x1006);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x08, 0xE358);
  spi_write(0x09, 0x0001);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x0A, 0x3F0F);
  spi_write(0x0B, 0x007F);
  
  //CCA Mode 1 Fix - > 0xD32F  to 032F
  spi_write(0x0C, 0x032F);
  
  spi_write(0x0D, 0x7704);
  spi_write(0x0E, 0x7704);
  spi_write(0x0F, 0x0144);
  spi_write(0x10, 0x0124);
  spi_write(0x11, 0x5218);
  spi_write(0x12, 0x0000);
  spi_write(0x13, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x14, 0x02B0);
  spi_write(0x15, 0x3E80);
  spi_write(0x16, 0xFFF9);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x17, 0x41A0);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x18, 0x8524);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x19, 0xCA86);
  spi_write(0x1A, 0x001C);
  spi_write(0x1B, 0x003E);
  spi_write(0x1C, 0x0020);
  spi_write(0x1D, 0xB820);
  spi_write(0x1E, 0xDE21);
  spi_write(0x1F, 0x02F8);
  spi_write(0x20, 0x0024);
  spi_write(0x21, 0x8100);
  spi_write(0x22, 0x0000);
  spi_write(0x23, 0x0000);
  spi_write(0x24, 0xD849);
  spi_write(0x25, 0xDF28);
  spi_write(0x26, 0xFFF3);
  spi_write(0x27, 0xFFB0);
  spi_write(0x28, 0x38D0);
  spi_write(0x29, 0x0189);
  spi_write(0x2A, 0x4B22);
  spi_write(0x2B, 0x0D37);
  spi_write(0x2C, 0x0C00);
  spi_write(0x2D, 0x0000);
  spi_write(0x2E, 0x7504);
  spi_write(0x2F, 0x3404);
  spi_write(0x30, 0x0104);
  spi_write(0x31, 0xF05F);
  spi_write(0x32, 0x6000);
  spi_write(0x33, 0x0E80);
  spi_write(0x34, 0x0404);
  spi_write(0x35, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x36, 0x3F0F);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x37, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x38, 0x3F0F);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x39, 0x0000);
  spi_write(0x3A, 0x727A);
  spi_write(0x3B, 0x0100);
  spi_write(0x3C, 0xF800);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x3D, 0x3F0F);
  spi_write(0x3E, 0x1004);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x3F, 0x3F0F);
  spi_write(0x40, 0x52EE);
  spi_write(0x41, 0xFFFF);
  spi_write(0x42, 0x9FAF);
  spi_write(0x43, 0xFFA0);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x44, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x45, 0x3F0F);
  spi_write(0x46, 0x489B);
  spi_write(0x47, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x48, 0x0000);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x49, 0x0000);
  spi_write(0x4A, 0x9913);
  spi_write(0x4B, 0xC438);
  spi_write(0x4C, 0x00C5);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x4D, 0x3F0F);
  spi_write(0x4E, 0x8F80);
  spi_write(0x4F, 0x00FF);
  spi_write(0x50, 0x8A44);
  spi_write(0x51, 0xAA2C);
  spi_write(0x52, 0x071F);
  spi_write(0x53, 0x4280);
  spi_write(0x54, 0x39B0);
  spi_write(0x55, 0xE002);
  spi_write(0x56, 0x2060);
  spi_write(0x57, 0x0000);
  spi_write(0x58, 0x8122);
  spi_write(0x59, 0x001A);
  spi_write(0x5A, 0x11A0);
  spi_write(0x5B, 0x20F8);
  spi_write(0x5C, 0x0098);
  spi_write(0x5D, 0x1F80);
  spi_write(0x5E, 0x65E4); // bit[15] = 0 => 96M PLL clock, bit[15] = 1 => 64M PLL clock
  spi_write(0x5F, 0x4000);
  spi_write(0x60, 0x0000);
  spi_write(0x61, 0xF09C);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x62, 0x3BFF);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x63, 0x9D88);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x64, 0x9D68);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x65, 0x9D48);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x66, 0x9D28);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x67, 0x9D08);
  spi_write(0x68, 0x0987);
  spi_write(0x69, 0x140B);
  // replaced with FS corner calib value in below section as given by junie spi_write(0x6A, 0x0000);
  spi_write(0x6B, 0xDA62);
  spi_write(0x6C, 0x717A);
  spi_write(0x6D, 0xEB58);
  spi_write(0x6E, 0x0F0F);
  spi_write(0x6F, 0x0100);
  spi_write(0x70, 0x0122);
  spi_write(0x71, 0xC1E1);
  spi_write(0x72, 0xFF49);
  spi_write(0x73, 0x0222);
  spi_write(0x74, 0x0000);
  spi_write(0x75, 0x0000);
  spi_write(0x76, 0x0222);
  spi_write(0x77, 0x0222);
  spi_write(0x78, 0x0222);
  spi_write(0x79, 0x0223);
  spi_write(0x7A, 0x0223);
  spi_write(0x7B, 0x0223);
  spi_write(0x7C, 0x0A0A);
  spi_write(0x7D, 0x0000);
  spi_write(0x7E, 0x8956);
  spi_write(0x7F, 0xF000);
  
  FPGA_Board_Calib_Values();
  
  //synz cal
  spi_write(0x60, 0x0008);
  spi_write(0x60, 0x0000);

  // clkgen_rstn pulse
  z_do_bitwr8(BT_ana_ip_ctrl_reg2_hl_addr, 0x02, 0x02); // PLL-dis
  z_do_bitwr8(BT_ana_ip_ctrl_reg2_hl_addr, 0x02, 0x00); // PLL-en
}

/***************************************************************************//**
\brief System PLL Initialization
*******************************************************************************/
void system_xtal_pll_init(void)
{
  uint32_t reg;
  uint16_t reg16;
    
 //1. Xtal Ready
   
  reg = readl(SUBSYS_STATUS_REG1);
  while((reg & BIT0) != 0x1)
  {
      reg = readl(SUBSYS_STATUS_REG1);
  }
    
 //2. Pll Initialisation   
 // Dummy SPI access to make sure SPI accesses work when PLL is off.
  reg16 = spi_read(0x0e); //store the value to restore later
  spi_write(0x0e, 0xbaab);
  reg = spi_read(0x0e);
  //do 
    {
      reg = spi_read(0x0e);
    };//while((reg & 0xffff) != 0xbaab);

  spi_write(0x0e, reg16); //revert back to original value
  z_reg_write8(BT_RF_Control_Register_RF_CTRL_ll_addr, 0x00);     // restoring default values
  z_reg_write8(BT_rf_control_register_rf_ctrl_2_hl_addr, 0x00);    // restoring default values
  z_reg_write8(BT_rf_programming_register_rfprog_hl_addr, 0x00);    // restoring default values

  // PLL Defaults and Board Calibration Values

  PLL_Configure();

   //3. PLL Lock
  //log_message (SIMCTRL_LOG_INFO, "Wait for PLL Lock");
  reg = z_do_bitrd32(SUBSYS_STATS_REG1_ADDR, 0x03);
  while (reg != 0x03)
  {
      reg = z_do_bitrd32(SUBSYS_STATS_REG1_ADDR, 0x03);
  }  
}

