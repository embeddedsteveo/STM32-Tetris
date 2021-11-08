

/**
  ****************************************************************************
  * @file    input_pad.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief  	Functions to read joypad on devboard.
  ****************************************************************************** 
**/
#include "input_pad.h"

void init_inputs(void)
{
	rcc_apb2_clock_control((1<<2), ENABLE);
	rcc_apb2_clock_control((1<<4), ENABLE);
	set_gpio_pin_mode(GPIOC, GPIO_P1, GPIO_CR_INPUT_PULLUP);
	set_gpio_pin_mode(GPIOC, GPIO_P2, GPIO_CR_INPUT_PULLUP);
	set_gpio_pin_mode(GPIOC, GPIO_P3, GPIO_CR_INPUT_PULLUP);
	set_gpio_pin_mode(GPIOC, GPIO_P0, GPIO_CR_INPUT_PULLUP);
	
	set_gpio_pin_mode(GPIOA, GPIO_P0, GPIO_CR_INPUT_PULLUP);
	
	GPIOC->ODR = (1 << GPIO_P1) |(1 << GPIO_P2)|(1 << GPIO_P3)|(1 << GPIO_P0);
	GPIOA->ODR = (1 << GPIO_P0);
}


uint8_t get_button_press(void)
{
	//In this scenario it would be better to get the whole
	//register and mask the bits we want.
	//Although because of how the game is structured, if we mask
	//the whole register, that doesn't take into account
	//more than one button can be pressed at the same time and
	//the switch statment in the game will fail.
	
	if(!read_gpio_pin(GPIOC, UP_MASK)) return C_UP;
	if(!read_gpio_pin(GPIOC, DOWN_MASK)) return C_DOWN;
	if(!read_gpio_pin(GPIOC, LEFT_MASK)) return C_LEFT;
	if(!read_gpio_pin(GPIOC, LEFT_BTTN_MASK)) return C_LEFT_BUTTON;
	if(!read_gpio_pin(GPIOA, RIGHT_MASK)) return C_RIGHT;
	
	return C_NONE;
}