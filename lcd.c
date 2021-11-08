
/**
  ******************************************************************************
  * @file    lcd.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   IL9825 LCD Firmware Functions and Drawing Library.
  ****************************************************************************** 
**/
#include "lcd.h"


/**
  ******************************************************************************
  * @function lcd_draw_pixel
  * @desc Draw a pixel of color at X, Y
  * @output None.
  ****************************************************************************** 
**/
void lcd_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	lcd_set_cursor_pos(x, y);
	lcd_write_register(0x0022, color);
}

/**
  ******************************************************************************
  * @function lcd_fill_rect
  * @desc Draw a rectangle from X, Y to X_End, Y_End with color
  * @output None.
  ****************************************************************************** 
**/
void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t upper = (x2 > x)?(x2):(x);
	for(uint16_t i = (x < x2)?(x):(x2); i < upper; i++)
	{
		for(uint16_t j = y; j < y2; j++)
		{
			lcd_set_cursor_pos(i, j);
			lcd_write_register(0x0022, color);
		}
	}
}

/**
  ******************************************************************************
  * @function lcd_fill_rect
  * @desc Draw a rectangle from X, Y to X_End, Y_End with color
	*					with border of 1 pixel.
  * @output None.
  ****************************************************************************** 
**/
void lcd_fill_rect_with_border(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t color)
{
	for(uint16_t i = x + 1; i < x2 -1; i++)
	{
		for(uint16_t j = y + 1; j < y2 -1; j++)
		{
			lcd_set_cursor_pos(i, j);
			lcd_write_register(0x0022, color);
		}
	}
}

/**
  ******************************************************************************
  * @function lcd_clear
  * @desc Clear entire screen and fill with specified color
  * @output None.
  ****************************************************************************** 
**/
void lcd_clear(uint16_t color)
{
	lcd_set_cursor_pos(0,0);
	lcd_write_index(0x0022);
	
	for(uint32_t index = 0; index < LCD_WIDTH * LCD_HEIGHT; index++ )
	{
		lcd_write_data(color);
	}

}

/**
  ******************************************************************************
  * @function lcd_set_cursor_pos
  * @desc Set the LCD Cursor to X, Y
  * @output None.
  ****************************************************************************** 
**/
void lcd_set_cursor_pos(uint16_t x, uint16_t y)
{		
		uint16_t t;
		t = x;
		x = LCD_HEIGHT - y - 1;
		y = t;
	
		lcd_write_register(0x0020, x);    
		lcd_write_register(0x0021, y);  
	
}

/**
  ******************************************************************************
  * @function get_font_array
  * @desc Returns the required font array for a given character
  * @output Stored character grid array in buffer
  ****************************************************************************** 
**/
void get_font_array(uint8_t * buffer, uint8_t character)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		buffer[i] = font8x8_basic[character][i];
	}
}

/**
  ******************************************************************************
  * @function lcd_write_string
  * @desc Writes a string starting at the given x and y position using color
  * @output None
  ****************************************************************************** 
**/
void lcd_write_string(uint16_t x, uint16_t y, uint8_t * string, uint16_t color, uint8_t block_size)
{
	uint16_t curr_x = x;
	uint16_t curr_y = y;
	
	while(*string != '\0')
	{
			lcd_print_character_block(curr_x, curr_y, *string, color, block_size);
			string++;
			
			if (curr_x > (LCD_WIDTH - block_size*FONT_HEIGHT))
			{
				curr_x = 0;
				curr_y = curr_y + block_size*FONT_HEIGHT;
				
			}else if (curr_y > (LCD_HEIGHT - block_size*FONT_HEIGHT))
			{
				curr_x = 0;
				curr_y = 0;
				
			}else
			{
				curr_x += block_size*FONT_HEIGHT + 1;
			}
		
	}
	
}

/**
  ******************************************************************************
  * @function lcd_print_character
  * @desc Prints character in colour at position x, y
  * @output None
  ****************************************************************************** 
**/
void lcd_print_character(uint16_t x, uint16_t y, uint8_t character, uint16_t color)
{
	
	uint8_t buffer[8];
	uint8_t  temp;
	uint8_t j;
	get_font_array(buffer, character);
	
	for(uint8_t i = 0; i < FONT_HEIGHT; i++)
	{
		temp = buffer[i];
		j = 0;
		
		while(1)
		{
			if(j == FONT_WIDTH) break;
			if((temp >> j) & 0x01)
			{
				lcd_draw_pixel(x +j, y+i, color);
			}
			
			j++;
			
		}
	}
}

/**
  ******************************************************************************
  * @function lcd_print_character_block
  * @desc Print a Character of size block size starting at x,y 
  * @output None
  ****************************************************************************** 
**/
void lcd_print_character_block(uint16_t x, uint16_t y, uint8_t character, uint16_t color, uint8_t block_size)
{
	
	uint8_t buffer[8];
	uint8_t  temp;
	uint8_t j;
	get_font_array(buffer, character);
	
	uint16_t curr_x = x;
	uint16_t curr_y = y;
	
	for(uint8_t i = 0; i < FONT_HEIGHT; i++)
	{
		temp = buffer[i];
		j = 0;
		
		while(1)
		{
			if(j == FONT_WIDTH) break;
			if((temp >> j) & 0x01)
			{
				lcd_fill_rect(curr_x, curr_y, curr_x + block_size, curr_y + block_size, color);
			}
			
			j++;
			curr_x = curr_x + block_size;
			
		}
		curr_x = x;
		curr_y = curr_y + block_size;
	}
}

/**
  ******************************************************************************
  * @function lcd_init
  * @desc Required register settings for the IL9825
  * @output None
  ****************************************************************************** 
**/
void lcd_init(void)
{
	init_lcd_control_lines();
	uint16_t id = 0;
	lcd_fsmc_init();
	delay_milli(500);
	delay_milli(300);
	
	id = lcd_read_register(0x0000);	
	
	lcd_write_register(0xE5, 0x78F0); 
	lcd_write_register(0x01, 0x0100); 
	lcd_write_register(0x02, 0x0700);
	lcd_write_register(0x03, 0x1030); 
	lcd_write_register(0x04, 0x0000); 
	lcd_write_register(0x08, 0x0207); 
	lcd_write_register(0x09, 0x0000); 
	lcd_write_register(0x0A, 0x0000); 
	lcd_write_register(0x0C, 0x0000); 
	lcd_write_register(0x0D, 0x0000); 
	lcd_write_register(0x0F, 0x0000); 

	lcd_write_register(0x10, 0x0000); 
	lcd_write_register(0x11, 0x0007);
	lcd_write_register(0x12, 0x0000);
	lcd_write_register(0x13, 0x0000); 
	lcd_write_register(0x07, 0x0001);
	delay_milli(200); 

	lcd_write_register(0x10, 0x1090); 
	lcd_write_register(0x11, 0x0227);
	delay_milli(50); 					
	lcd_write_register(0x12, 0x001F); 
	delay_milli(50); 						
	lcd_write_register(0x13, 0x1500); 
	lcd_write_register(0x29, 0x0027); 
	lcd_write_register(0x2B, 0x000D); 
	delay_milli(50); 						
	lcd_write_register(0x20, 0x0000); 
	lcd_write_register(0x21, 0x0000); 

	lcd_write_register(0x30, 0x0000);
	lcd_write_register(0x31, 0x0707);
	lcd_write_register(0x32, 0x0307);
	lcd_write_register(0x35, 0x0200);
	lcd_write_register(0x36, 0x0008);
	lcd_write_register(0x37, 0x0004);
	lcd_write_register(0x38, 0x0000);
	lcd_write_register(0x39, 0x0707);
	lcd_write_register(0x3C, 0x0002);
	lcd_write_register(0x3D, 0x1D04);
	
	lcd_write_register(0x50, 0x0000); 
	lcd_write_register(0x51, 0x00EF); 
	lcd_write_register(0x52, 0x0000);
	lcd_write_register(0x53, 0x013F);
	lcd_write_register(0x60, 0xA700); 
	lcd_write_register(0x61, 0x0001); 
	lcd_write_register(0x6A, 0x0000); 

	lcd_write_register(0x80, 0x0000);
	lcd_write_register(0x81, 0x0000);
	lcd_write_register(0x82, 0x0000);
	lcd_write_register(0x83, 0x0000);
	lcd_write_register(0x84, 0x0000);
	lcd_write_register(0x85, 0x0000);

	lcd_write_register(0x90, 0x0010);
	lcd_write_register(0x92, 0x0600);
	lcd_write_register(0x07, 0x0133);  
	
  delay_milli(100);
	lcd_clear(LCD_BLACK);
}

/**
  ******************************************************************************
  * @function init_lcd_control_lines
  * @desc Enable the required I/O lines for the IL9825
  * @output None
  ****************************************************************************** 
**/
void init_lcd_control_lines(void)
{		
		//Too many function calls should just use a loop.
		rcc_ahb_clock_control(((uint32_t)0x00000100), ENABLE);
		rcc_apb2_clock_control(((uint32_t)0x00000020), ENABLE); //Port D
		rcc_apb2_clock_control(((uint32_t)0x00000040), ENABLE); //Port E
		rcc_apb2_clock_control(((uint32_t)0x00000001), ENABLE); //AF
	
		set_gpio_pin_mode(GPIOD, GPIO_P0, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P1, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P4, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P5, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P8, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P9, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P10, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P11, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P14, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P15, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		
		set_gpio_pin_mode(GPIOE, GPIO_P7, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P8, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);	
		set_gpio_pin_mode(GPIOE, GPIO_P9, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P10, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P11, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P12, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P13, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P14, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOE, GPIO_P15, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);

		set_gpio_pin_mode(GPIOD, GPIO_P7, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P13, GPIO_CR_OUTPUT_50M_ALT_PUSH_PULL);
		set_gpio_pin_mode(GPIOD, GPIO_P12, GPIO_CR_OUTPUT_50M_PUSH_PULL);
		
		lcd_reset();
		
}

/**
  ******************************************************************************
  * @function lcd_reset
  * @desc Rest the LCD by driving P12 Low then High
  * @output None
  ****************************************************************************** 
**/
void lcd_reset(void)
{
	GPIOD->ODR &= ~GPIO_P12_MASK;
	delay_milli(300);
	GPIOD->ODR |= GPIO_P12_MASK;
	delay_milli(300);
	
}

/**
  ******************************************************************************
  * @function lcd_fsmc_init
  * @desc Setup the FSMC registers to enable communication to the LCD
  * @output None
  ****************************************************************************** 
**/
void lcd_fsmc_init(void)
{
		FSMC_Init init_struct;
		FSMC_Timing_Init timing_struct;
		
	  init_struct.FSMC_Write_Timing = &timing_struct;
	
		init_struct.Bank = (uint32_t)0;
		init_struct.Data_Mux = (uint32_t)0;
		init_struct.Mem_Type = (uint32_t)0; //SRAM
		init_struct.Med_Width = (uint32_t)1<<4; //16 Bit Mode
		init_struct.Burst_Mode = (uint32_t)0;
		init_struct.Wait_Sig_Pol = (uint32_t)0;
		init_struct.Wrap = (uint32_t)0;
		init_struct.Wait_Sig_Active = (uint32_t)0;
		init_struct.Write_Op = ((uint32_t)0x00001000);
		init_struct.Wait_Sig = (uint32_t)0;
		init_struct.Async_Wait = (uint32_t)0;
		init_struct.Ext_Mode = (uint32_t)0;
		init_struct.Write_Burst = (uint32_t)0;
		
	
		timing_struct.Access_Mode = (uint32_t)0;
		timing_struct.Data_Setup_T = (uint32_t)10;
		timing_struct.Address_Setup_T = (uint32_t)5;
		timing_struct.Address_Hold_T = (uint32_t)0;
		timing_struct.CLK_Div = (uint32_t)0;
		timing_struct.Data_Latency = (uint32_t)0;
		timing_struct.Bus_TurnA_T = (uint32_t)0;
		
		init_struct.FSMC_Write_Timing = &timing_struct;
		
		fsmc_init(&init_struct);
		
		enable_disable_fsmc_bank((uint32_t)0, (uint32_t)1);
	
}