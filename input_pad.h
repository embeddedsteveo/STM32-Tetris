
/**
  ****************************************************************************
  * @file    input_pad.h
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief  	Header for functions to read joypad on devboard.
  ****************************************************************************** 
**/
#ifndef INPUT_PAD_H
#define INPUT_PAD_H

#include "lcd.h"

#define UP_MASK GPIO_P1_MASK
#define RIGHT_MASK GPIO_P0_MASK
#define DOWN_MASK GPIO_P3_MASK
#define LEFT_MASK GPIO_P2_MASK
#define LEFT_BTTN_MASK GPIO_P0_MASK

enum Controls {
	
	C_NONE,
	C_UP,
	C_RIGHT,
	C_DOWN,
	C_LEFT,
	C_CENTRE_BUTTON,
	C_LEFT_BUTTON

};

void init_inputs(void);
enum Controls get_button_press(void);
#endif