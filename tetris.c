/**
  ******************************************************************************
  * @file    tetric.c
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Main Gameplay Functions for Tetris.
  ****************************************************************************** 
**/

#include "tetris.h"

/**
  ******************************************************************************
  * @function check_for_tetris
  * @desc Checks all lines to see if a tetris has been made and clears line
  * @output None.
  ****************************************************************************** 
**/

uint16_t check_for_tetris(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
	uint8_t col_count;
	uint8_t row_count = 0;
	
	for(uint8_t row = 0; row < TET_GAME_HEIGHT; row++)
	{
		col_count = 0;
		
		for(uint8_t col = 0; col < TET_GAME_WIDTH; col++)
		{
					if(game_area[row][col])
					{
						col_count++;
					}
		}
		
		if(col_count >= TET_GAME_WIDTH)
		{
			row_count++;
			
			for(uint8_t y = row; y > 0; y--)
			{
				for(uint8_t x = 0; x < TET_GAME_WIDTH; x++)
				{
					game_area[y][x] = game_area[y -1][x];
				}
			}
			
			for(uint8_t x = 0; x < TET_GAME_WIDTH; x++)
			{
				game_area[0][x] = 0;
			}
		}
		
		col_count = 0;
	}
	
	return (row_count)?(100 << row_count):(0);
	
}

/**
  ******************************************************************************
  * @function draw_block_rectangle
  * @desc Draws a rectangle block
  * @output None.
  ****************************************************************************** 
**/
void draw_block_rectangle(uint16_t x, uint16_t y, uint16_t end_x, uint16_t end_y, uint16_t color, uint8_t block_size, uint8_t border)
{
	
	if(border){
		lcd_fill_rect_with_border(x, y, end_x, end_y, color);
	}
	else {
		lcd_fill_rect(x, y, end_x, end_y, color);
	}

}	

/**
  ******************************************************************************
  * @function draw_block_rectangle
  * @desc  Copies a Piece Struct from SRC to DST, does not allocate memory
  * @output None.
  ****************************************************************************** 
**/
void copy_piece(Piece * dest, Piece * src)
{
	dest->shape_ref = src->shape_ref;
	dest->dim = src->dim;
	dest->row = src->row;
	dest->col = src->col;
	
	for(uint8_t y = 0; y < src->dim; y++)
	{
			for(uint8_t x = 0; x < src->dim; x++)
			{
				dest->shape[y][x] = src->shape[y][x];
			}
	}
	
}

/**
  ******************************************************************************
  * @function check_position
  * @desc  Checks if a piece is in a valid position
  * @output Returns 1 if valid, else 0.
  ****************************************************************************** 
**/
uint16_t check_position(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
	for(uint8_t y = 0; y < current->dim; y++)
	{
		for(uint8_t x = 0; x < current->dim; x++)
		{
				if ((current->shape[y][x])&&(current->col + x < 0 || current->col + x >= TET_GAME_WIDTH || current->row + y >= TET_GAME_HEIGHT))
				{
					return 0;
				
				}else if( game_area[current->row + y][current->col + x] && current->shape[y][x])
				{
					return 0;
				}
		}
		
	}
	return 1;
}

/**
  ******************************************************************************
  * @function draw_piece_on_board
  * @desc  Draws a given piece on the gamearea
  * @output None.
  ****************************************************************************** 
**/
void draw_piece_on_board(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
	for(uint8_t y = 0; y < current->dim; y++)
	{
		for(uint8_t x = 0; x < current->dim; x++)
		{
				if(current->shape[y][x])
				{
					game_area[current->row + y][current->col + x] = current->shape[y][x];
				}
		}
	}
}

/**
  ******************************************************************************
  * @function advance
  * @desc  Advances a piece down the screen, if a collision occours generates a new piece
  * @output Returns 0 to signify end game, returns 1 if a normal collision, 2 if no collision
  ****************************************************************************** 
**/
uint8_t advance(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
		Piece temp;
		copy_piece(&temp, current);
		
		temp.row++;
		
		if(!check_position(&temp, game_area))
		{
			draw_piece_on_board(current, game_area);
			get_new_shape(current);
			
			if(temp.row == 1)
				return 0;
			
			return 1;
		
		}else
		{
			current->row++;	
			return 2;
		}
}
/**
  ******************************************************************************
  * @function clear_piece_area
  * @desc  Removes the Piece from the screen
  * @output None.
  ****************************************************************************** 
**/
void clear_piece_area(Piece * current)
{
	 uint16_t x_offset = current->col * BLOCK_SIZE + 10;
	 uint16_t y_offset = current->row * BLOCK_SIZE  + 10;
	
	for(uint8_t y = 0; y < current->dim; y++)
	{
		for(uint8_t x = 0; x < current->dim; x++)
		{
				if( current->shape[y][x])
				{
						lcd_fill_rect(x_offset, y_offset, x_offset + BLOCK_SIZE, y_offset + BLOCK_SIZE, LCD_BLACK);
				}
				
				x_offset = x_offset + BLOCK_SIZE;
		}
		 x_offset = current->col * BLOCK_SIZE + 10  ;
		 y_offset = y_offset + BLOCK_SIZE;
	}
	
}

/**
  ******************************************************************************
  * @function take_action
  * @desc  Applies an action to a piece and tests if it is valid
  * @output Returns 1 if valid, 0 otherwise
  ****************************************************************************** 
**/
uint8_t take_action(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH], uint8_t y_tras,  int8_t x_tras, uint8_t rotate)
{	
		Piece temp;
		copy_piece(&temp, current);
		
		temp.row += y_tras;
		temp.col += x_tras;
		
		if(rotate)
		{
			rotate_piece(&temp);
		}

		if(check_position(&temp, game_area))
		{
			copy_piece(current, &temp);
			return 1;
		}
		
		return 0;
		
}
/**
  ******************************************************************************
  * @function get_new_shape
  * @desc  Generates a new shape and updates the current piece
  * @output 
  ****************************************************************************** 
**/
void get_new_shape(Piece * current)
{
	uint8_t random_index = (uint8_t)rand() & 0x06;
	
	current->shape_ref = GameShape[random_index].data;
	current->dim = GameShape[random_index].dim;
	current->row = 0;
	current->col = 0;
	
	for(uint8_t y = 0; y < current->dim; y++)
	{
			for(uint8_t x = 0; x < current->dim; x++)
			{
				current->shape[y][x] = GameShape[random_index].data[y][x];
			}
	}
}

/**
  ******************************************************************************
  * @function clear_game_area
  * @desc  Clears the gamearea array 
  * @output 
  ****************************************************************************** 
**/
void clear_game_area(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
	
	for(uint8_t y = 0; y < TET_GAME_HEIGHT; y++)
	{
		for(uint8_t x = 0; x < TET_GAME_WIDTH; x++)
		{
			game_area[y][x] = 0;
		}
	}
	
}

/**
  ******************************************************************************
  * @function rotate_piece
  * @desc  Performs a 90 Degree rotation of a given piece
  * @output 
  ****************************************************************************** 
**/

void rotate_piece(Piece * current)
{
		Piece temp;
		copy_piece(&temp, current);
		
		uint8_t w = 0;
		for(uint8_t y = 0; y < current->dim; y++)
		{
			for(uint8_t x = 0, w = current->dim -1; x < current->dim; w--, x++)
			{
					current->shape[y][x] = temp.shape[w][y];
			}
		}
	
}

/**
  ******************************************************************************
  * @function draw_piece
  * @desc  Draws a Piece to the screen
  * @output 
  ****************************************************************************** 
**/

void draw_piece(Piece * current)
{
	 uint16_t x_offset = current->col * BLOCK_SIZE + 10;
	 uint16_t y_offset = current->row * BLOCK_SIZE + 10;
	
	for(uint8_t y = 0; y < current->dim; y++)
	{
		for(uint8_t x = 0; x < current->dim; x++)
		{
				if( current->shape[y][x])
				{
						lcd_fill_rect_with_border(x_offset, y_offset, x_offset + BLOCK_SIZE, y_offset + BLOCK_SIZE, current->shape[y][x]);
				}
				
				x_offset = x_offset + BLOCK_SIZE;
		}
		 x_offset = current->col * BLOCK_SIZE + 10;
		 y_offset = y_offset + BLOCK_SIZE;
	}
	
}
void add_to_game_grid(void)
{
	
}

/**
  ******************************************************************************
  * @function draw_game_grid
  * @desc  Draws the gamearea to the screen
  * @output 
  ****************************************************************************** 
**/
void draw_game_grid(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH])
{
	
	uint16_t x_offset = 10;
	uint16_t y_offset  = 10;
	
	for(uint8_t y = 0; y < TET_GAME_HEIGHT; y++)
	{
		for(uint8_t x = 0; x < TET_GAME_WIDTH; x++)
		{

				lcd_fill_rect_with_border(x_offset, y_offset, x_offset + BLOCK_SIZE, y_offset + BLOCK_SIZE, game_area[y][x]);
				
				x_offset = x_offset + BLOCK_SIZE;
		}
		 x_offset = 10;
		 y_offset = y_offset + BLOCK_SIZE;
	}
	
}


