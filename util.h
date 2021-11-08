
/**
  ****************************************************************************
  * @file    util.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Utility Functions header.
  ****************************************************************************** 
**/

#ifndef UTIL_H
#define UTIL_H

typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

void delay_milli(unsigned short int delay); 
uint16_t rand(void);

//From github
uint8_t* itoa(int value, uint8_t* result, int base); 

#endif