/**
  ******************************************************************************
  * @file    main.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Demo of implementing STM32F based Tetris game using no library 
						 functions and implemnting all hardware access structs from scratch.
  ****************************************************************************** 
**/
#include <stdio.h>
#include "stm32f10x.h"

#include "tetris.h"

uint16_t time_out = 0;
uint16_t total_ticks = 0;
uint16_t current_ticks = 0;
uint16_t bass_tick = 0;


uint16_t play_tetris_game(void);
void show_menu(void);
void setup_perh(void);
void init_wave_timers(void);
void init_dac_channels();
void update_game_timer(int16_t diff);


int main(void)
{
		//Setup all the I/O devies
		setup_perh();
		//Start a game of tetris
		show_menu();

		while(1)
		{
			delay_milli(1000);
			GPIOB->ODR |= 1 << 13;
			
			delay_milli(1000);
			GPIOB->ODR &= ~(1 << 13);
	
		}
}
void TIM2_IRQHandler(void)
{	
		//Set the timeout flag and clear the interupt
		time_out = 1;
		TIM2->SR &= ~(1 << 0);
}

void TIM3_IRQHandler(void)
{
		//Check if song is finished
		if(total_ticks == SONG_TRACK_A_LENGTH -1)
		{
			total_ticks = 0;
			current_ticks = 0;
			bass_tick = 0;
		}
		
		//Check the note duration and advance
		if (current_ticks == sequence[total_ticks])
		{
			total_ticks++;
			TIM5->ARR = song[total_ticks];
			current_ticks = 0;
		}
		
		TIM6->ARR = bass[bass_tick];
		bass_tick++;
		current_ticks++;
		
		//Clear the interupt
		TIM3->SR &= ~(1 << 0);
	
}


void init_wave_timers(void)
{
		//Enable Timer 5 - Setup timer output trigger
		init_timer(TIM5, 64, 0x0, ENABLE);
		TIM5->CR2 &= ~((uint16_t) 0x0070);
		TIM5->CR2 |= (uint16_t) 0x0020;
		
		//Enable Timer 6 - Setup timer output trigger
		init_timer(TIM6, 64, 0x0, ENABLE);
		TIM6->CR2 &= ~((uint16_t) 0x0070);
		TIM6->CR2 |= (uint16_t) 0x0020;
}

void init_dac_channels(void)
{
		//Set DAC output pinds PA4/5 as Analoge In.
		set_gpio_pin_mode(GPIOA, GPIO_P4, GPIO_CR_INPUT_ANAL);
		set_gpio_pin_mode(GPIOA, GPIO_P5, GPIO_CR_INPUT_ANAL);
		
		//DAC Channel 1 Triggers on Timer 3, generates a tringle wave
		uint32_t temp = ((uint32_t)0x0000001C) | ((uint32_t)0x00000080) | ((uint32_t)0x00000700) | ((uint32_t)0x00000002) ;
		DAC->CR &= ~((uint32_t)0x00000FFE);
		DAC->CR |= temp;
		
		//DAC Channel 2 Triggers on Timer 6, generates a tringle wave
		temp = ((uint32_t)0x00000004) | ((uint32_t)0x00000080) | ((uint32_t)0x00000700) | ((uint32_t)0x00000002) ;
		DAC->CR &= ~((uint32_t)0x00000FFE << 16);
		DAC->CR |= temp << 16;
		//
		//Enable Both DAC Channels
		DAC->CR |= ((uint32_t)0x0001 | ((uint32_t)(0x00001 << 16)));
	
	
}

void setup_perh(void)
{
	
		//Enable GPIOB12 and 13 for debugging
		RCC->APB2ENR |= (uint32_t)1 << 3;
		set_gpio_pin_mode(GPIOB, GPIO_P13, GPIO_CR_OUTPUT_50M_PUSH_PULL);
		set_gpio_pin_mode(GPIOB, GPIO_P14, GPIO_CR_OUTPUT_50M_PUSH_PULL);
		
		//Setup the LCD using FSMC
		lcd_init();
		lcd_clear(LCD_BLACK);
		
		//Game Timer
		rcc_apb1_clock_control(RCC_APB_TIM2, ENABLE);
		init_timer(TIM2, 4000, 8000, ENABLE);
		
		//Song Sequencer Timer
		rcc_apb1_clock_control(RCC_APB_TIM3, ENABLE);
		init_timer(TIM3, 2000, 8000, ENABLE);
		
		//Wave Timers
		rcc_apb1_clock_control(RCC_APB_TIM5, ENABLE);
		rcc_apb1_clock_control(RCC_APB_TIM6, ENABLE);
		init_wave_timers();
	
		rcc_apb1_clock_control(RCC_APB1_DAC, ENABLE);
		init_dac_channels();
		
		//Enable interupts for Timer 2 and Timer 3
		NVIC->ISER[0] |= (1 << (28));
		NVIC->ISER[0] |= (1 << (29));
		
		//Setup up joystick inputs
		init_inputs();
	
}
void draw_screen_frame()
{
	//Draw region around the playing field
	draw_block_rectangle(0,0, BLOCK_SIZE, LCD_HEIGHT, LCD_BLUE, 1, 1);
	draw_block_rectangle(0,0,(TET_GAME_WIDTH+2)*BLOCK_SIZE ,BLOCK_SIZE, LCD_BLUE,1, 1);
	draw_block_rectangle(0,(TET_GAME_HEIGHT+1)*BLOCK_SIZE,(TET_GAME_WIDTH+2)*BLOCK_SIZE  ,LCD_HEIGHT, LCD_BLUE,1, 1);
	draw_block_rectangle((TET_GAME_WIDTH+1)*BLOCK_SIZE,0,(TET_GAME_WIDTH+2)*BLOCK_SIZE, LCD_HEIGHT, LCD_BLUE,1, 1);
	
}

void draw_menu_screen(uint16_t best_score)
{
		uint8_t buffer[15];
		lcd_write_string(150,50,"Okay", LCD_RED, 4);
		lcd_write_string(50,80,"Tetris", LCD_RED, 5);
		lcd_write_string(100,150,"Best Score", LCD_YELLOW, 1);
		itoa(best_score, buffer, 10);
		lcd_write_string(200,150, buffer, LCD_YELLOW, 1);
		
		lcd_write_string(100,200,"Press Any Button", LCD_YELLOW, 1);
		lcd_write_string(120,210,"To Start", LCD_YELLOW, 1);
		
	
}

void update_game_timer(int16_t diff)
{
	int16_t current_reload_value = TIM2->ARR;
	TIM2->ARR = current_reload_value + diff;
}


void show_menu(void)
{
	uint16_t input = 0;
	uint16_t score = 0;
	uint16_t best_score = 100;
	
	lcd_clear(LCD_BLACK);
	draw_menu_screen(best_score);
	
	while(1)	
	{
		input = get_button_press();
		if(input)
		{
			score = play_tetris_game();
			best_score = (score > best_score)?(score):(best_score);
			lcd_clear(LCD_BLACK);
			draw_menu_screen(best_score);
		}
	}
}

uint16_t play_tetris_game(void)
{
		uint8_t string[15];
		uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH] = {0};
		uint16_t score = 0;
		
		uint8_t game_running = 1;
		int8_t input;
		uint8_t result = -1;
		
		Piece current;
		Piece temp;
		
		lcd_clear(LCD_BLACK);
		
		clear_game_area(game_area);
		
		get_new_shape(&current);
		draw_game_grid(game_area);
		draw_piece(&current);
		
		//Setup the screen layout and text
		draw_screen_frame();
		lcd_write_string(250,50,"Okay", LCD_RED, 2);
		lcd_write_string(150,80,"Tetris", LCD_RED, 3);
		lcd_write_string(150,120,"Current Score", LCD_YELLOW, 1);
		itoa(score, string, 10);
		lcd_write_string(150,140,string, LCD_YELLOW, 1);
		
		while(game_running)	
		{
			//Remove the last piece from the screen
			clear_piece_area(&current);
	
			//If Timer 2 expired, automatically advance piece down
			if(time_out == 1)
			{
				time_out = 0;
				result = advance(&current, game_area);
			}
			
			//Get input and apply action
			input = get_button_press();
			
			switch(input)
			{
				
				case C_DOWN:
					result = advance(&current, game_area);
				break;
				
				case C_RIGHT:
					 take_action(&current, game_area, 0, 1, 0);
				break;
				
				case C_LEFT:
						 take_action(&current, game_area, 0, -1, 0);
				break;
				
				case C_LEFT_BUTTON:
						take_action(&current, game_area, 0, 0, 1);
				break;
				
			}
			
			//Draw piece after action is applied
			draw_piece(&current);
		
			//If a piece was added to the gamegrid, redraw the grid.
			if(result == 1)
			{
				result = -1;
				score += check_for_tetris(game_area);
				draw_block_rectangle(150,140, 150 + 100, 140 + 20, LCD_BLACK, 1, 0);
				itoa(score, string, 10);
				lcd_write_string(150,140,string, LCD_YELLOW, 1);
				draw_game_grid(game_area);
				update_game_timer(-10);
			}else if(result == 0)
			{
				return score;
			}
			
			//Delay to limit user input.
			delay_milli(150);

	}
	
}