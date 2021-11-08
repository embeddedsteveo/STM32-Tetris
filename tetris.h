/**
  ******************************************************************************
  * @file    tetris.h
  * @author  steveriono
  * @version V1.0.0
  * @date    10-Novemeber-2021
  * @brief   Main Gameplay Functions for Tetris.
  ****************************************************************************** 
**/

#ifndef TETRIS_H
#define TETRIS_H
#include "input_pad.h"

#define TET_GAME_WIDTH 10
#define TET_GAME_HEIGHT 20

#define BLOCK_SIZE 9
#define SONG_TRACK_A_LENGTH 55

typedef struct {
	
	uint16_t ** shape_ref;
	uint16_t shape[4][4];
	uint8_t row;
	int8_t col;
	uint8_t dim;
	
} Piece;

typedef struct {
	
	uint16_t ** data;
	uint8_t dim;
	
} Shape;

static const Shape GameShape[7] = 
{
	{(uint16_t *[]){(uint16_t[]){LCD_BLUE,LCD_BLUE,LCD_BLUE}, (uint16_t []){LCD_BLUE, 0,0}, (uint16_t []){0,0,0}},3}, //L
	{(uint16_t *[]){(uint16_t[]){LCD_MAG,LCD_MAG,LCD_MAG}, (uint16_t []){0, 0,LCD_MAG}, (uint16_t []){0,0,0}},3},//J
	{(uint16_t *[]){(uint16_t[]){LCD_GREEN,LCD_GREEN,LCD_GREEN}, (uint16_t []){0, LCD_GREEN,0}, (uint16_t []){0,0,0}},3}, //T
	{(uint16_t *[]){(uint16_t[]){LCD_YELLOW,LCD_YELLOW,LCD_YELLOW, LCD_YELLOW}, (uint16_t []){0, 0,0,0}, (uint16_t []){0,0,0,0}, (uint16_t []){0,0,0,0}},4}, //Bar
	{(uint16_t *[]){(uint16_t[]){0,LCD_RED,LCD_RED}, (uint16_t []){LCD_RED, LCD_RED,0}, (uint16_t []){0,0,0}},3}, //S pience
	{(uint16_t *[]){(uint16_t[]){LCD_CYAN,LCD_CYAN,0}, (uint16_t []){0, LCD_CYAN,LCD_CYAN}, (uint16_t []){0,0,0}},3}, //Z pience
	{(uint16_t *[]){(uint16_t[]){LCD_WHITE,LCD_WHITE}, (uint16_t []){LCD_WHITE, LCD_WHITE}, (uint16_t []){0,0}},2} //Square
	
};

enum Moves{
	
	LEFT,
	RIGHT,
	DOWN,
	DROP,
	TIME_DOWN,
	ROTATE
};

void draw_game_grid(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);
void clear_game_area(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);
void draw_piece(Piece * current);
void get_new_shape(Piece * current);
void copy_piece(Piece * dest, Piece * src);
uint16_t check_position(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);
void draw_piece_on_board(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);
uint8_t advance(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);
uint8_t take_action(Piece * current, uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH], uint8_t y_tras,  int8_t x_tras, uint8_t rotate);
void clear_piece_area(Piece * current);
void draw_block_rectangle(uint16_t x, uint16_t y, uint16_t end_x, uint16_t end_y, uint16_t color, uint8_t block_size, uint8_t border);
void draw_block_rectangle_b(uint16_t x, uint16_t y, uint16_t end_x, uint16_t end_y, uint16_t color, uint8_t block_size);
void draw_block_rectangle_nb(uint16_t x, uint16_t y, uint16_t end_x, uint16_t end_y, uint16_t color, uint8_t block_size);
void rotate_piece(Piece * current);
uint16_t check_for_tetris(uint16_t game_area[TET_GAME_HEIGHT][TET_GAME_WIDTH]);

static const uint16_t song[] = {389, 519, 490, 437, 490, 519, 583, 583, 490, 389, 437, 490, 519, 519, 490, 437, 389, 490, 583, 437, 367, 291, 327, 367, 389, 490, 389, 437, 490, 519, 519, 490, 437, 389, 490, 583, 583, 778, 980, 873, 1039, 980, 1166, 1235, 1039, 778, 980, 873, 1039, 980, 778, 583, 583, 618};
static const uint8_t sequence[] = {2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1,1, 2, 2, 2, 2, 4, 3, 1, 2, 1, 1, 3, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4};
static const uint16_t bass[] = {3112, 1556, 3112, 1556, 3112, 1556, 3112, 1556, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 3112, 1556, 3112, 1556, 1166, 2332, 1166, 2332, 1166, 1747, 873, 1747, 873, 1747, 873, 1747, 873, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 3112, 1556, 3112, 1556, 3112, 1556, 3112, 1556, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1166, 2332, 1556, 1961, 1556, 2332, 1556, 1961, 1556, 2077, 1235, 1556, 1235, 2077, 1235, 1556, 1235, 2332, 1556, 1961, 1556, 2332, 1556, 1961, 1556, 2077, 1235, 1556, 1235, 2077, 1235, 1556, 1235, 2332, 1556, 1961, 1556, 2332, 1556, 1961, 1556, 2077, 1235, 1556, 1235, 2077, 1235, 1556, 1235, 2332, 1556, 1961, 
1556, 2332, 1556, 1961, 1556, 2077, 1235, 1556, 1235, 2077, 1235, 1556, 1235};

#endif