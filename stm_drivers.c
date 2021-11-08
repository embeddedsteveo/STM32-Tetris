
/**
  ******************************************************************************
  * @file    lcd.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Generic HAL function implementations.
  ****************************************************************************** 
**/
#include "stm_drivers.h"

/**
  ******************************************************************************
  * @function fsmc_init
  * @desc Inits the FSMC registers based on the given FSMC init struct
  * @output None.
  ****************************************************************************** 
**/

void fsmc_init(FSMC_Init * init_struct)
{
		FSMC_BANK_1->BCTR[init_struct->Bank] = (uint32_t) (init_struct->Async_Wait |
		init_struct->Burst_Mode |
		init_struct->Data_Mux |
		init_struct->Ext_Mode |
		init_struct->Med_Width |
		init_struct->Mem_Type |
		init_struct->Wait_Sig |
		init_struct->Wait_Sig_Active |
		init_struct->Wait_Sig_Pol |
		init_struct->Wrap |
		init_struct->Write_Burst |
		init_struct->Write_Op);
	
		FSMC_BANK_1->BCTR[init_struct->Bank + 1] = (uint32_t) (init_struct->FSMC_Write_Timing->Address_Setup_T |
		init_struct->FSMC_Write_Timing->Address_Hold_T << 4 |
		init_struct->FSMC_Write_Timing->Data_Setup_T << 8 |
	  init_struct->FSMC_Write_Timing->Bus_TurnA_T << 16 |
		init_struct->FSMC_Write_Timing->CLK_Div << 20 |
		init_struct->FSMC_Write_Timing->Data_Latency << 24 |
		init_struct->FSMC_Write_Timing->Access_Mode << 28);
	
		//Only working in extended mode disabled
		FSMC_BANK_1E->BWTR[init_struct->Bank] = 0x0FFFFFFF;
	
}


/**
  ******************************************************************************
  * @function enable_disable_fsmc_bank
  * @desc Enables or disbles a FSMC Bank based on state (ENABLE,DISABLE)
  * @output None.
  ****************************************************************************** 
**/

void enable_disable_fsmc_bank(uint32_t bank, uint32_t state)
{
	if (state == DISABLE)
	{
		FSMC_BANK_1->BCTR[bank] &= ((uint32_t)0x000FFFFE);	

	}else
	{
		FSMC_BANK_1->BCTR[bank] |= ((uint32_t)0x00000001);
	}

}
/**
  ******************************************************************************
  * @function rcc_ahb_clock_control
  * @desc Enables or disbles a RCC->AHP clock based on state (ENABLE,DISABLE)
  * @output None.
  ****************************************************************************** 
**/
void rcc_ahb_clock_control(uint32_t perhp_mask, uint32_t state)
{
	if (state == DISABLE)
	{
		RCC->AHBENR &= ~perhp_mask;	

	}else
	{
		RCC->AHBENR |= perhp_mask;	
	}

}
/**
  ******************************************************************************
  * @function rcc_ahb_clock_control
  * @desc Enables or disbles a RCC->APB1 clock based on state (ENABLE,DISABLE)
  * @output None.
  ****************************************************************************** 
**/
void rcc_apb1_clock_control(uint32_t perhp_mask, uint32_t state)
{
	if (state == DISABLE)
	{
		RCC->APB1ENR &= ~perhp_mask;	

	}else
	{
		RCC->APB1ENR |= perhp_mask;	
	}

}
/**
  ******************************************************************************
  * @function rcc_ahb_clock_control
  * @desc Enables or disbles a RCC->APB2 clock based on state (ENABLE,DISABLE)
  * @output None.
  ****************************************************************************** 
**/
void rcc_apb2_clock_control(uint32_t perhp_mask, uint32_t state)
{
	//uint32_t temp = RCC->APB2ENR
	//RCC->APB2ENR = (state)?(temp | perhp_mask):(temp & ~perhp_mask);
	
	if (state == DISABLE)
	{
		RCC->APB2ENR &= ~perhp_mask;	

	}else
	{
		RCC->APB2ENR |= perhp_mask;	
	}

}

/**
  ******************************************************************************
  * @function set_gpio_pin_mode
  * @desc Sets the GPIO operation mode for a given pin on a given port
  * @output None.
  ****************************************************************************** 
**/
void set_gpio_pin_mode(GPIO_generic * GPIO, uint32_t pin, uint32_t mode)
{
	uint32_t offset;
	offset = (pin & (uint32_t)0x07) << 2;
	
	if( pin & (uint32_t)0x08)
	{
		GPIO->CRH &= ~((uint32_t)0x0F << offset);
		GPIO->CRH |= (mode << offset);
		
	}else{
	
		GPIO->CRL &= ~((uint32_t)0x0F << offset);
		GPIO->CRL |= (mode << offset);
	}
}	

/**
  ******************************************************************************
  * @function read_gpio_pin
  * @desc Reads and returns IDR value based on pin mask
  * @output Returns 1 if enabled, else 0
  ****************************************************************************** 
**/
//Should be an inline function
uint16_t read_gpio_pin(GPIO_generic * GPIO, uint32_t pin_mask)
{
	return (GPIO->IDR & pin_mask)?((uint16_t)0x0001):((uint16_t)0x0000);
}
/**
  ******************************************************************************
  * @function init_timer
  * @desc Inits a generic timer with ARR, PRR and Inerupt enable
  * @output Returns 1 if enabled, else 0
  ****************************************************************************** 
**/
void init_timer(TIM_Generic * timer, uint16_t auto_reload, uint16_t prescaler, uint32_t interupt_enable)
{
	timer->CR1 = (uint16_t) 0x0000;
	timer->ARR = auto_reload;
	timer->PSC = prescaler;
	timer->DIER |= (interupt_enable == ENABLE)?((uint16_t)0x0001):((uint16_t)0x0000);
	timer->CR1 |= (uint16_t)0x0001;
	
}
