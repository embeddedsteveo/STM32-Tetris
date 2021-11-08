
/**
  ****************************************************************************
  * @file    stm_drivers.h
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Header file for struct and register definitions for STM32F103VE.
  ****************************************************************************** 
**/

#ifndef STM_DRIVERS_H
#define STM_DRIVERS_H

typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef struct{
	
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
	
}GPIO_generic;

typedef struct{
	
	uint32_t Address_Setup_T;
	uint32_t Address_Hold_T;
	uint32_t Data_Setup_T;
	uint32_t Bus_TurnA_T;
	uint32_t CLK_Div;
	uint32_t Data_Latency;
	uint32_t Access_Mode;
	
}FSMC_Timing_Init;

typedef struct{
	
	uint32_t Bank;
	uint32_t Data_Mux;
	uint32_t Mem_Type;
	uint32_t Med_Width;
	uint32_t Burst_Mode;
	uint32_t Async_Wait;
	uint32_t Wait_Sig_Pol;
	uint32_t Wrap;
	uint32_t Wait_Sig_Active;
	uint32_t Write_Op;
	uint32_t Wait_Sig;
	uint32_t Ext_Mode;
	uint32_t Write_Burst;	
	
	FSMC_Timing_Init * FSMC_Write_Timing;
} FSMC_Init;

typedef struct{
	
	volatile uint32_t BCTR[8];
	
} FSMC_BANK;

typedef struct{
	
	//Note Bank 1E is of length 7 not 8
	volatile uint32_t BWTR[7];

}FSMC_BANK_E;

typedef struct {
	
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB1RESETR;
	volatile uint32_t APB2RESETR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDR;
	volatile uint32_t CSR;
	volatile uint32_t AHBRESETR;
	volatile uint32_t CFGR2;
	
}RCC_Generic;

typedef struct {

  volatile uint16_t CR1;
  uint16_t  RES0;
  volatile uint16_t CR2;
  uint16_t  RES1;
  volatile uint16_t SMCR;
  uint16_t  RES2;
  volatile uint16_t DIER;
  uint16_t  RES3;
  volatile uint16_t SR;
  uint16_t  RES4;
  volatile uint16_t EGR;
  uint16_t  RES5;
  volatile uint16_t CCMR1;
  uint16_t  RES6;
  volatile uint16_t CCMR2;
  uint16_t  RES7;
  volatile uint16_t CCER;
  uint16_t  RES8;
  volatile uint16_t CNT;
  uint16_t  RES9;
  volatile uint16_t PSC;
  uint16_t  RES10;
  volatile uint16_t ARR;
  uint16_t  RES11;
  volatile uint16_t RCR;
  uint16_t  RES12;
  volatile uint16_t CCR1;
  uint16_t  RES13;
  volatile uint16_t CCR2;
  uint16_t  RES14;
  volatile uint16_t CCR3;
  uint16_t  RES015;
  volatile uint16_t CCR4;
  uint16_t  RES016;
  volatile uint16_t BDTR;
  uint16_t  RES017;
  volatile uint16_t DCR;
  uint16_t  RES018;
  volatile uint16_t DMAR;
  uint16_t  RES19;

}TIM_Generic;


#define ENABLE ((uint32_t)0x01)
#define DISABLE ((uint32_t)0x00)

#define PERIPHERAL_BASE ((uint32_t)0x40000000)

#define APB1_BASE PERIPHERAL_BASE
#define APB2_BASE (PERIPHERAL_BASE + 0x10000)
#define AHB_BASE (PERIPHERAL_BASE + 0x20000)

#define PORTA_BASE (APB2_BASE + 0x0800)
#define PORTB_BASE (APB2_BASE + 0x0C00)
#define PORTC_BASE (APB2_BASE + 0x1000)
#define PORTD_BASE (APB2_BASE + 0x1400)
#define PORTE_BASE (APB2_BASE + 0x1800)
#define PORTF_BASE (APB2_BASE + 0x1C00)
#define PORTG_BASE (APB2_BASE + 0x2000)

#define ADC1_BASE (APB2_BASE + 0x2400)
#define ADC2_BASE (APB2_BASE + 0x2800)

#define GPIOA ((GPIO_generic *) PORTA_BASE)
#define GPIOB ((GPIO_generic *) PORTB_BASE)
#define GPIOC ((GPIO_generic *) PORTC_BASE)
#define GPIOD ((GPIO_generic *) PORTD_BASE)
#define GPIOE ((GPIO_generic *) PORTE_BASE)
#define GPIOF ((GPIO_generic *) PORTF_BASE)
#define GPIOG ((GPIO_generic *) PORTG_BASE)

#define GPIO_P0_MASK ((uint32_t)0x0001)  
#define GPIO_P1_MASK ((uint32_t)0x0002)  
#define GPIO_P2_MASK ((uint32_t)0x0004) 
#define GPIO_P3_MASK ((uint32_t)0x0008)  
#define GPIO_P4_MASK ((uint32_t)0x0010)  
#define GPIO_P5_MASK ((uint32_t)0x0020)  
#define GPIO_P6_MASK ((uint32_t)0x0040)  
#define GPIO_P7_MASK ((uint32_t)0x0080)  
#define GPIO_P8_MASK ((uint32_t)0x0100) 
#define GPIO_P9_MASK ((uint32_t)0x0200) 
#define GPIO_P10_MASK ((uint32_t)0x0400)  
#define GPIO_P11_MASK ((uint32_t)0x0800) 
#define GPIO_P12_MASK ((uint32_t)0x1000)  
#define GPIO_P13_MASK ((uint32_t)0x2000) 
#define GPIO_P14_MASK ((uint32_t)0x4000)  
#define GPIO_P15_MASK ((uint32_t)0x8000)  
#define GPIO_P_All_MASK ((uint32_t)0xFFFF)  

#define GPIO_P0 ((uint32_t) 0x00)  
#define GPIO_P1 ((uint32_t) 0x01)  
#define GPIO_P2 ((uint32_t) 0x02) 
#define GPIO_P3 ((uint32_t) 0x03)  
#define GPIO_P4 ((uint32_t) 0x04)  
#define GPIO_P5 ((uint32_t) 0x05)  
#define GPIO_P6 ((uint32_t) 0x06)  
#define GPIO_P7 ((uint32_t) 0x07)  
#define GPIO_P8 ((uint32_t) 0x08) 
#define GPIO_P9 ((uint32_t) 0x09) 
#define GPIO_P10 ((uint32_t) 0x0A)  
#define GPIO_P11 ((uint32_t) 0x0B) 
#define GPIO_P12 ((uint32_t) 0x0C)  
#define GPIO_P13 ((uint32_t) 0x0D) 
#define GPIO_P14 ((uint32_t) 0x0E)  
#define GPIO_P15 ((uint32_t) 0x0F)  

#define GPIO_CR_INPUT_ANAL ((uint32_t)0x00)
#define GPIO_CR_INPUT_FLOAT ((uint32_t)0x01)
#define GPIO_CR_INPUT_PUPD ((uint32_t)0x02)
#define GPIO_CR_INPUT_PULLUP ((uint32_t)0x08)

#define GPIO_CR_OUTPUT_10M_PUSH_PULL ((uint32_t)0x04)
#define GPIO_CR_OUTPUT_10M_OPEN_DRAIN ((uint32_t)0x05)
#define GPIO_CR_OUTPUT_10M_ALT_PUSH_PULL ((uint32_t)0x06)
#define GPIO_CR_OUTPUT_10M_ALT_OPEN_DRAIN ((uint32_t)0x07)

#define GPIO_CR_OUTPUT_2M_PUSH_PULL ((uint32_t)0x08)
#define GPIO_CR_OUTPUT_2M_OPEN_DRAIN ((uint32_t)0x09)
#define GPIO_CR_OUTPUT_2M_ALT_PUSH_PULL ((uint32_t)0x0A)
#define GPIO_CR_OUTPUT_2M_ALT_OPEN_DRAIN ((uint32_t)0x0B)

#define GPIO_CR_OUTPUT_50M_PUSH_PULL ((uint32_t)0x03)
#define GPIO_CR_OUTPUT_50M_OPEN_DRAIN ((uint32_t)0x0D)
#define GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL ((uint32_t)0x0B)
#define GPIO_CR_OUTPUT_50M_ALT_OPEN_DRAIN ((uint32_t)0x0F)

#define FSMC_BASE ((uint32_t) 0xA0000000)
#define FSMC_BANK_1_BASE FSMC_BASE
#define FSMC_BANK_1 ((FSMC_BANK *) FSMC_BANK_1_BASE)


#define FSMC_Bank_1E_BASE (FSMC_BASE + 0x0104) 
#define FSMC_BANK_1E ((FSMC_BANK_E *) FSMC_Bank_1E_BASE)

#define RCC_BASE (AHB_BASE + 0x1000)
#define RCC ((RCC_Generic *) RCC_BASE)

#define TIM2_BASE APB1_BASE 
#define TIM2 ((TIM_Generic *) TIM2_BASE)

#define TIM3_BASE (APB1_BASE + 0x0400)
#define TIM3 ((TIM_Generic *) TIM3_BASE)

#define TIM4_BASE (APB1_BASE + 0x0800)
#define TIM4 ((TIM_Generic *) TIM4_BASE)

#define TIM5_BASE (APB1_BASE + 0x0C00)
#define TIM5 ((TIM_Generic *) TIM5_BASE)

#define TIM6_BASE (APB1_BASE + 0x1000)
#define TIM6 ((TIM_Generic *) TIM6_BASE)


#define RCC_APB_TIM2 ((uint32_t)0x01)
#define RCC_APB_TIM3 ((uint32_t)0x02)
#define RCC_APB_TIM4 ((uint32_t)0x04)
#define RCC_APB_TIM5 ((uint32_t)0x08)
#define RCC_APB_TIM6 ((uint32_t)0x10)

#define RCC_APB1_DAC ((uint32_t) 0x20000000)


void set_gpio_pin_mode(GPIO_generic * GPIO, uint32_t pin, uint32_t mode); 
void fsmc_init(FSMC_Init * init_struct);
void enable_disable_fsmc_bank(uint32_t bank, uint32_t state);
void enable_disable_fsmc_bank(uint32_t bank, uint32_t state);
void rcc_ahb_clock_control(uint32_t perhp_mask, uint32_t state);
void rcc_apb1_clock_control(uint32_t perhp_mask, uint32_t state);
void rcc_apb2_clock_control(uint32_t perhp_mask, uint32_t state);
uint16_t read_gpio_pin(GPIO_generic * GPIO, uint32_t pin_mask);
void init_timer(TIM_Generic * timer, uint16_t auto_reload, uint16_t prescaler, uint32_t interupt_enable);

#endif