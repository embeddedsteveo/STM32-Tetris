
#include "stm_drivers.h"

void set_gpio_mode(GPIO_generic * GPIO, uint32_t pin, uint32_t mode)
{
	if( pin & (uint32_t)0xF0)
	{
		GPIO->CRH &= ~((uint32_t)0x0F << pin);
		GPIO->CRH |= ~(mode << pin);
	}else{
		GPIO->CRL &= ~((uint32_t)0x0F << pin);
		GPIO->CRL |= ~(mode << pin);
	}
}	
