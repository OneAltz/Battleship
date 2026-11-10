#ifndef SOLVE_H
#define SOLVE_H
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//Micah Sandberg
// Nov 10 8:06

// This Funtion will display the welcome screen for the program: No.1
void welcome_screen();
// This funtion will that sets each cell in a game board to '-'. : No.2
void initialize_game_board();
// This Funtion will Select who will start first in the game : No.3
//lowkey Ptr Arith might be goat hear 
void select_who_starts_first();
// This funtion will ask for the Ships location and place them on the game board : No.4
void manually_place_ships_on_board();
// This Funtion will randomly place the ships on the game board : No.5
//lowkey AI type Beat
void randomly_place_ships_on_board();
// This Funtion will Check Hit or Miss and update the game board accordingly : No.6
int check_shot();
// This Funtion will Check if the player has won the game : No.7
bool is_winner();
// This Funtion will update the game board with the players shot : No.8
void update_board();
// This Funtion will display the game board to the player : No.9
void display_game_board();
//This Funtion will be the Current Main P1 P2 Move : No.10
void output_current_move();
//This Funtion will be if the shit has "Health" : No.11
bool check_if_sunk_ship();
//This Funtion will be the stats of the Games : No.12
void output_stats();
//This Funtion will be the AI moves for the game : No.13
void ai_move();
//This Funtion will be the AI messages for the game : No.14 
void ai_message();
//This Funtion Will be anything that needs to be cleaned up at the end of the game
void clean_up();
//This Funtion will Print the Game Rules for the game : No.15
void print_game_rules();
#endif