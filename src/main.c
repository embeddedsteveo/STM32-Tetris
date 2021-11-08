
#include <stdio.h>
#include "stm32f10x.h"
#include "stm_drivers.h"



void delay(uint32_t delay)
{
	volatile counter = 0;
	
	for(int i = 0; i < delay; i++)
	{
		counter = i;
	}
	
}
int main(void)
{
		//Enable Clock to GPIOB
		RCC->APB2ENR |= 1 << 3;
		
		set_gpio_mode(GPIOB, 13, GPIO_CR_OUTPUT_10M_PUSH_PULL);
	
		while(1)
		{
			delay(1000000)
			GPIOB->ODR = 1 << 13;
			delay(1000000)
			GPIOB->ODR &= ~(1 << 13);
		}
		
	
}