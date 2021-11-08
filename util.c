

#include "util.h"

static uint16_t seed = 0xACE3;
static uint16_t current_bit;

uint16_t rand()
{
	 current_bit  = ((seed >> 0) ^ (seed >> 2) ^ (seed >> 3) ^ (seed >> 5) ) & 1;
   return seed =  (seed >> 1) | (current_bit << 15);
}
void delay_milli(unsigned short int delay)    
{ 
	volatile unsigned short int i,j; 
	for( i = 0; i < delay; i++ )
	{ 
		for( j = 0; j < 1471; j++ );
	}
} 

//From github
uint8_t* itoa(int value, uint8_t* result, int base) {
    // check that the base if valid
    uint8_t* ptr = result, *ptr1 = result, tmp_char;
	  int tmp_value;
		if (base < 2 || base > 36) { *result = '\0'; return result; }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
