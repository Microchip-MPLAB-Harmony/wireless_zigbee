/*******************************************************************************
  Fpga RF Source File

  Company:
    Microchip Technology Inc.

  File Name:
    fpgaRFTest.c

  Summary:
    This file contains the Fpga RF Test implementation.

  Description:
    This file contains the Fpga RF Test implementation.
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

#include <RF231_RF212/PHY/include/At86rf233.h>
//#include <pic32cx.h>
#include <string.h>
//#include <liberty.h>
#include <core_cm4.h>
#define REG_READ_RETRY_COUNT 50

#define bool    _Bool
#define true    1
#define false   0

uint8_t regValue = 0;
uint8_t retry = 0;
bool testResult[20];

uint8_t Rf_ReadReg (uint8_t regOffset)
{
  return  (uint8_t) *((volatile uint8_t *) (ZB_BASEADDR + regOffset));  
}

void Rf_WriteReg (uint8_t regOffset, uint8_t value)
{
  *((volatile uint8_t *) (ZB_BASEADDR + regOffset)) = value;
}

bool RF_InitTest_PartNum (void)
{
  regValue = Rf_ReadReg(PART_NUM_OFFSET);
  if (0x0B == regValue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_InitTest_VerNum (void)
{
  regValue = Rf_ReadReg(VERSION_NUM_OFFSET);
  if (regValue == 0xc0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_InitTest_PanID (void)
{
  uint16_t panId = 0;
  
  Rf_WriteReg(PAN_ID_0_OFFSET,0xA5);
  Rf_WriteReg(PAN_ID_1_OFFSET,0x5A);
  
  panId = Rf_ReadReg(PAN_ID_0_OFFSET);
  panId |= Rf_ReadReg(PAN_ID_1_OFFSET) << 8;
  
  if (0x5AA5 == panId)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_InitTest_IEEE_Address (void)
{
  uint32_t ieeeAddress_lsb = 0;
  uint32_t ieeeAddress_msb = 0;

  Rf_WriteReg(IEEE_ADDR_0_OFFSET,0xA5);
  Rf_WriteReg(IEEE_ADDR_1_OFFSET,0x5A);
  Rf_WriteReg(IEEE_ADDR_2_OFFSET,0xA5);
  Rf_WriteReg(IEEE_ADDR_3_OFFSET,0x5A);
  Rf_WriteReg(IEEE_ADDR_4_OFFSET,0xA5);
  Rf_WriteReg(IEEE_ADDR_5_OFFSET,0x5A);
  Rf_WriteReg(IEEE_ADDR_6_OFFSET,0xA5);
  Rf_WriteReg(IEEE_ADDR_7_OFFSET,0x5A);
  
  ieeeAddress_lsb = Rf_ReadReg(IEEE_ADDR_0_OFFSET)  << (8 * 0);
  ieeeAddress_lsb |= Rf_ReadReg(IEEE_ADDR_1_OFFSET) << (8 * 1);
  ieeeAddress_lsb |= Rf_ReadReg(IEEE_ADDR_2_OFFSET) << (8 * 2);
  ieeeAddress_lsb |= Rf_ReadReg(IEEE_ADDR_3_OFFSET) << (8 * 3);

  ieeeAddress_msb = Rf_ReadReg(IEEE_ADDR_4_OFFSET)  << (8 * 0);
  ieeeAddress_msb |= Rf_ReadReg(IEEE_ADDR_5_OFFSET) << (8 * 1);
  ieeeAddress_msb |= Rf_ReadReg(IEEE_ADDR_6_OFFSET) << (8 * 2);
  ieeeAddress_msb |= Rf_ReadReg(IEEE_ADDR_7_OFFSET) << (8 * 3);
  
  if ((0x5AA55AA5 == ieeeAddress_lsb) && 
       (0x5AA55AA5 == ieeeAddress_msb))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_InitTest_ShortAddr (void)
{
  uint16_t shortAddr = 0;

  Rf_WriteReg(SHORT_ADDR_0_OFFSET,0xA5);
  Rf_WriteReg(SHORT_ADDR_1_OFFSET,0x5A);
  
  shortAddr = Rf_ReadReg(SHORT_ADDR_0_OFFSET);
  shortAddr |= Rf_ReadReg(SHORT_ADDR_1_OFFSET) << 8;
  
  if (0x5AA5 == shortAddr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_InitTest_CCA (void)
{
  
  Rf_WriteReg(PHY_CC_CCA_OFFSET,0x15);
  
  regValue = Rf_ReadReg(PHY_CC_CCA_OFFSET);
   
  if ((regValue == 0x15))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool RF_ModeTest_TRX_OFF (void)
{
  //Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TRX_OFF);
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_FORCE_TRX_OFF);
  retry = REG_READ_RETRY_COUNT;
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && ((regValue & TRX_STATUS_TRX_OFF) != TRX_STATUS_TRX_OFF));
  
  if (retry)
    return true;
  return false;
}



bool setPLL_ON (void)
{
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_PLL_ON);
  retry = REG_READ_RETRY_COUNT;
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && ((TRX_STATUS_PLL_ON & regValue) != TRX_STATUS_PLL_ON ));

  if (retry)
    return true;
  return false;
}

void EIC_0_Handler (void)
{
  while(1);
}

void EIC_1_Handler               ( void )
{
  while(1);
}
void EIC_2_Handler               ( void )
{
  while(1);
}
void EIC_3_Handler               ( void )
{
  while(1);
}
void EIC_4_Handler               ( void )
{
  while(1);
}
void EIC_5_Handler               ( void )
{
  while(1);
}
void EIC_6_Handler               ( void )
{
  while(1);
}
void EIC_7_Handler               ( void )
{
  while(1);
}
void EIC_8_Handler               ( void )
{
  while(1);
}
void EIC_9_Handler               ( void )
{
  while(1);
}
void EIC_10_Handler              ( void )
{
  while(1);
}
void EIC_11_Handler              ( void )
{
  while(1);
}
void EIC_12_Handler              ( void )
{
  while(1);
}
void EIC_13_Handler              ( void )
{
  while(1);
}
void EIC_14_Handler              ( void )
{
  while(1);
}
void EIC_15_Handler              ( void )
{
  while(1);
}

void BT_ZB_SUBSYS_IRQ_0(void)
{
   regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);
   while(1);
}

void BT_ZB_SUBSYS_IRQ_1 (void)
{
  regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);  
  while(1);
  
}
void BT_ZB_SUBSYS_IRQ_2 (void)
{
  regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);  
    while(1);
}
    
void BT_ZB_SUBSYS_IRQ_3(void)
{
  regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);  
    while(1);
}

bool RF_ModeTest_ISR (void)
{

  *(volatile uint32_t *)DIRECT_RFIELD_MASK0 = (1U << IRQ_LE_PL_RCV_OK | 1U << IRQ_PCSG_TRIGGER | 1U << IRQ_LE_PL_RCV_ERR);
  *(volatile uint32_t *)DIRECT_RFIELD_MASK1 = (1U << IRQ_USER_ERROR);
  *(volatile uint32_t *)DIRECT_RFIELD_MASK2 = (1U << IRQ_SCH_PAR_IDLE | 1U << IRQ_SCAN_PRO_DONE | 1U << IRQ_SCAN_ERROR | 1U << IRQ_SCAN_ADV_EVENT_DETECTED);
  //enable auto-clear function of int0_masked_interrupt_vector_register_set_0
  *(volatile uint32_t *)DIRECT_RFIELD_FCLR0 = 0xFFFF;
  //enable auto-clear function of int0_masked_interrupt_vector_register_set_1
  *(volatile uint32_t *)DIRECT_RFIELD_FCLR1 = 0xFFFF;
  //enable auto-clear function of int0_masked_interrupt_vector_register_set_2
  *(volatile uint32_t *)DIRECT_RFIELD_FCLR2 = 0xFFFF;
  //enable all user error interrupts
  *(volatile uint32_t *)DIRECT_RFIELD_USER_ERROR_INT_MASK = 0xFFFF;

//  for (uint8_t irqn = 0;irqn <= PERIPH_COUNT_IRQn; irqn++)
//  {
//    NVIC_DisableIRQ((IRQn_Type)irqn);
//    NVIC_SetPriority((IRQn_Type)irqn,  1);
//    NVIC_ClearPendingIRQ((IRQn_Type)irqn);
//    NVIC_EnableIRQ((IRQn_Type)irqn);
//  }
 
    //enable BT_ZB_SUBSYS_IRQ_1
  NVIC_DisableIRQ((IRQn_Type)1);
  NVIC_SetPriority((IRQn_Type)1,  1);
  NVIC_ClearPendingIRQ((IRQn_Type)1);
  NVIC_EnableIRQ((IRQn_Type)1);

  //enable BT_ZB_SUBSYS_IRQ_2
  
//  NVIC_DisableIRQ((IRQn_Type)2);
//  NVIC_SetPriority((IRQn_Type)2,  1);
//  NVIC_ClearPendingIRQ((IRQn_Type)2);
//  NVIC_EnableIRQ((IRQn_Type)2);
  
//  NVIC_DisableIRQ((IRQn_Type)3);
//  NVIC_SetPriority((IRQn_Type)3,  1);
//  NVIC_ClearPendingIRQ((IRQn_Type)3);
//  NVIC_EnableIRQ((IRQn_Type)3);
//  
//  NVIC_DisableIRQ((IRQn_Type)4);
//  NVIC_SetPriority((IRQn_Type)4,  1);
//  NVIC_ClearPendingIRQ((IRQn_Type)4);
//  NVIC_EnableIRQ((IRQn_Type)4);
//  
  regValue = Rf_ReadReg(TRX_CTRL_1_OFFSET);
  regValue |= 2;                // Enable Interrupt
  Rf_WriteReg(TRX_CTRL_1_OFFSET,regValue);
  Rf_WriteReg(IRQ_MASK_OFFSET,0xff);
  
  // PLL ON
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_PLL_ON);
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while ((TRX_STATUS_PLL_ON & regValue) != TRX_STATUS_PLL_ON );
  
   
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TX_START);

  while(1);
}

void ZB_Write_RF_Reg(uint8_t addr,uint16_t value);
uint8_t rxBuffer[128];
uint8_t txBuffer[128];

void RF_ZB_ContinousModeTest (void)
{

  Rf_WriteReg(IRQ_MASK_OFFSET,0xff);
  Rf_WriteReg(RAD_CTRL_IRQ_MASK,0xff);
 
  regValue = Rf_ReadReg(0x04); // TRX_CTRL_1_OFFSET Disable AUTO CRC mode
  regValue &=~ (1 << 5);
  Rf_WriteReg(0x04,0); // TRX_CTRL_1_OFFSET Disable AUTO CRC mode

  Rf_WriteReg(0x42,0x01); // ZB_RADIO_CTRL Disable radio controller (May also require setting radio arbiter in static ZB mode)
  
 // Set State = TRX_OFF
  while (!RF_ModeTest_TRX_OFF());
 
  
  Rf_WriteReg(0x3,0x05); //16MHz
  Rf_WriteReg(ZB_MAC_TX_MODEM_2, 0x10); //ADC Format = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_0, 0x80); //DAC Format = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_2, 0x08); //TX_MOD_FLIP = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_5, 0x1C); //RX IF freq = 28

 Rf_WriteReg(ZB_MAC_TX_MODEM_4, 0x20); //RX IQ SWAP= 1
 
  
 // Poll for IRQ AWAKE
 do
  regValue = Rf_ReadReg(0xf);
 while(regValue & (1 << 4) != (1 << 4));
 
 ZB_Write_RF_Reg(0x0f,0x150); // Ch 14 // Set ZB Channel Number
 
 Rf_WriteReg(0x05,0x00); // Set TX output power, for example to PTX_MAX
 
 do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (((regValue & TRX_STATUS_TRX_OFF) != TRX_STATUS_TRX_OFF));
 
 Rf_WriteReg(0x11,0x0B); // Set cont_tx_mode = 1
 
 Rf_WriteReg(0x0c,0x03);
 Rf_WriteReg(0x0A,0x37);
 
  uint32_t *txAddress = (uint32_t *)ZB_TX_FRAME_BUFFER_ADDR;
  for (uint32_t index =0; index <128/4; index ++) 
  {
    *(volatile uint32_t *) txAddress++ = (uint32_t)0xffffffff;
  }
 
 Rf_WriteReg(0x1c,0x54);
   for(uint8_t j=0; j<14; j++)
  {
      _nop_;
  }
 Rf_WriteReg(0x1c,0x46);
 

  while(!setPLL_ON());
  
 Rf_WriteReg(0x02,0x02);
 regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);
 
 while(1)
 {
    // memset(txAddress,0x9,128);
   txAddress = (uint32_t *)ZB_TX_FRAME_BUFFER_ADDR;
  for (uint32_t index =0; index <128/4; index ++) 
  {
    *(volatile uint32_t *) txAddress++ = (uint32_t)0xffffffff;
  }
 }
 
#if 0
 Rf_WriteReg(TRX_CTRL_0_OFFSET,0x05);
 
 Rf_WriteReg(ZB_MAC_TX_MODEM_2, 0x10); //ADC Format = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_0, 0x80); //DAC Format = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_2, 0x08); //TX_MOD_FLIP = 1

 Rf_WriteReg(ZB_MAC_TX_MODEM_5, 0x1C); //RX IF freq = 28

 Rf_WriteReg(ZB_MAC_TX_MODEM_4, 0x20); //RX IQ SWAP= 1
 
 ZB_Write_RF_Reg(0x0F, 0x0150);
 
 regValue = Rf_ReadReg(IRQ_STATUS_OFFSET);
  
  
  {
      for (uint32_t index =0; index <128/4; index ++) 
      {
        *(volatile uint32_t *) txAddress++ = (uint32_t)0xa5a5a5a5;
      }
      setPLL_ON();
       Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TX_START);
  }
#endif
}

bool RF_ModeTest_PLL_ON (void)
{
  if(setPLL_ON())
    return (RF_ModeTest_TRX_OFF());
  return false;
}

bool RF_ModeTest_RX_ON (void)
{
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_RX_ON);
  retry = REG_READ_RETRY_COUNT;
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && (TRX_STATUS_RX_ON != regValue));
  
  if (retry)
    return (RF_ModeTest_TRX_OFF());
  return false;
}

bool RF_ModeTest_PrepDeepSleep (void)
{
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_PREP_DEEP_SLEEP);
   retry = REG_READ_RETRY_COUNT;
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && (TRX_STATUS_PREP_DEEP_SLEEP != regValue));
  
  return (RF_ModeTest_TRX_OFF());
}

bool RF_ModeTest_ForceTRXoff (void)
{
  setPLL_ON();
  
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_FORCE_TRX_OFF);

  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);  
  while (TRX_STATUS_TRX_OFF != regValue);
  return true;
}

bool RF_ModeTest_ForcePLL_ON (void)
{
  RF_ModeTest_TRX_OFF();
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_FORCE_PLL_ON);
  retry = REG_READ_RETRY_COUNT;
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);  
  while (--retry && (TRX_STATUS_PLL_ON != regValue));
  
  if (retry)
    return (RF_ModeTest_TRX_OFF());
  return false;
  
}

bool RF_ExtModeTest_TX_ARET_ON (void)
{
  // Pre-condition
  setPLL_ON();
  // Test
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TX_ARET_ON);
  retry = REG_READ_RETRY_COUNT;
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && (TRX_STATUS_TX_ARET_ON != regValue));

  if (retry)
    return (setPLL_ON());
  else
    return false;
  
}

bool RF_ExtModeTest_RX_AACK_ON (void)
{
  // Pre-condition
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_RX_ON);
  // Test
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_RX_AACK_ON);
  retry = REG_READ_RETRY_COUNT;
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && (TRX_STATUS_RX_AACK_ON != regValue));
  
  if (retry)
  {
    Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_RX_ON);
    do
      regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
    while (TRX_STATUS_RX_ON != regValue);
    return true;
  }
  return false;
}

bool RF_ExtModeTest_BUSY_TX_ARET (void)
{
  uint8_t trxState = 0;
  
  // Pre-condition
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TX_ARET_ON);
  
  Rf_WriteReg(XAH_CTRL_0_OFFSET,0x56);
  Rf_WriteReg(CSMA_SEED_0_OFFSET,0xA5);
  Rf_WriteReg(CSMA_SEED_1_OFFSET,0x5A);
  Rf_WriteReg(CSMA_BE_OFFSET,0x53);
  
  // Test
  retry = REG_READ_RETRY_COUNT;
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (--retry && (TRX_STATUS_TX_ARET_ON != regValue));
  
  if (!retry)
  {
    return false;
  }
  regValue = Rf_ReadReg(XAH_CTRL_0_OFFSET);
  if ((0x56 != regValue))
  {
    return false;
  }
  regValue = Rf_ReadReg(CSMA_SEED_0_OFFSET);
  if ((0xA5 != regValue))
  {
    return false;
  }
  regValue = Rf_ReadReg(CSMA_SEED_1_OFFSET);
  if ((0x5A != regValue))
  {
    return false;
  }
  regValue = Rf_ReadReg(CSMA_BE_OFFSET);
  if ((0x53 != regValue))
  {
    return false;
  }
  /* 
  TODO : Initiate IEEE Packet
  */
  
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_TX_START);
  setPLL_ON();
  do
  {
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
    trxState = Rf_ReadReg(TRX_STATE_OFFSET) >> 5 ;
  }
  while ((TRAC_STATUS_SUCCESS != trxState) || (TRX_STATUS_PLL_ON != regValue));
  
  /*Note: Also Verify the tx complete interrupt*/
  
  /*
    Introduce Noise / busy in the channel configured for test
  */
  /*
    • Channel is monitored for noise / busy
    • Expected to see ARET_FRAME_RETRIES to be L times due to the busy channel
    • Expected to see ARET_CSMA_RETRIES to be M times due to the busy channel
    • Expected to see MAX_FRAME_RETRIES to be N times due to the busy channel
    • Expected to see MAX_CSMA_RETRIES to be O times due to the busy channel
  */
  do
    trxState = Rf_ReadReg(TRX_STATE_OFFSET) >> 5;
  while (TRAC_STATUS_CHANNEL_ACCESS_FAILURE != trxState);
  
  return true;

}

bool RF_ExtModeTest_RX_ACCK_ON (void)
{
  setPLL_ON();
  
  Rf_WriteReg(TRX_STATE_OFFSET,TRX_CMD_RX_AACK_ON);
  
  do
    regValue = Rf_ReadReg(TRX_STATUS_OFFSET);
  while (regValue & (TRX_STATUS_RX_AACK_ON != TRX_STATUS_RX_AACK_ON));
  
  /*
    After Tester initiates the transmission with ACK bit enabled, 
    DUT will send an Acknowledgement packet back to the Tester
  */
  return true;  
}


void FPGA_performRFTest (void)
{
  //(*(volatile uint32_t *) (SUBSYS_BASEADDR)) = SUBSYS_ZB_EN_MAIN_CLK_16MHZ;
  (*(volatile uint32_t *) (WIRELESS_ZBT_BASEADDR+0x4000) ) = ((*(volatile uint32_t *) (WIRELESS_ZBT_BASEADDR+0x4000) ) | 0x00000010);
  
  testResult[0] = RF_InitTest_PartNum();
  testResult[1] = RF_InitTest_VerNum();
  testResult[2] = RF_InitTest_PanID();
  testResult[3] = RF_InitTest_IEEE_Address();
  testResult[4] = RF_InitTest_ShortAddr();
  testResult[5] = RF_InitTest_CCA();

  testResult[6] = RF_ModeTest_TRX_OFF();
  
  RF_ModeTest_ISR();
//  RF_ZB_ContinousModeTest();
  testResult[7] = RF_ModeTest_PLL_ON();
    
  testResult[8] = RF_ModeTest_RX_ON();
  testResult[9] = RF_ModeTest_PrepDeepSleep();
  testResult[10] = RF_ModeTest_ForceTRXoff();
  testResult[11] = RF_ModeTest_ForcePLL_ON();

  testResult[12] = RF_ExtModeTest_TX_ARET_ON();
  testResult[13] = RF_ExtModeTest_RX_AACK_ON();
  testResult[14] = RF_ExtModeTest_BUSY_TX_ARET();
  testResult[15] = RF_ExtModeTest_RX_ACCK_ON();
  while(1);
}