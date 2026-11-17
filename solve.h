
#ifndef SOLVE_H
#define SOLVE_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#define MAX_SHIPS 5
#define HIT_BONUS 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    WATER = 0,
    CARRIER = 1,
    BATTLESHIP = 2,
    CRUISER = 3,
    SUBMARINE = 4,
    DESTROYER = 5
} ShipType;

typedef struct {
    int row;
    int col;
} Coordinate;

struct ship {
    ShipType type;
    char name[20];
    int size;
    int health;
    Coordinate positions[5];
};

// This Funtion will display the welcome screen for the program: No.1
void welcome_screen(void);
// This funtion sets each cell of both boards to water: No.2
void initialize_game_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS]);
// This Funtion will Select who will start first in the game: No.3
int select_who_starts_first(void);
// This funtion asks for the ships location and places them on the board: No.4
void manually_place_ships_on_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], struct ship ships[MAX_SHIPS]);
// This Funtion will randomly place the ships on the game board: No.5
void randomly_place_ships_on_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], struct ship ships[MAX_SHIPS]);
// This Funtion checks hit or miss and updates the board: No.6
int check_shot(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS], int row, int col);
// This Funtion checks if a player has won the game: No.7
bool is_winner(struct ship ships[MAX_SHIPS]);
// This Funtion will update the visible board: No.8
void update_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE]);
void display_game_board(char board[SIZE][SIZE]);
// This Funtion will announce the current player: No.10
void output_current_move(int current_player);
// This Funtion will check a ship's health: No.11
bool check_if_sunk_ship(struct ship ships[MAX_SHIPS], ShipType target);
// This Funtion will save stats: No.12
void output_stats(int *misses, int *hits, int *total_shots, int *Rec, bool *game_over);
// This Funtion will make the AI move: No.13
int ai_move(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS], int *shot_row, int *shot_col);
// This Funtion will print the AI result: No.14
void ai_message(int result);
// This Funtion will clean up at the end of a game
void clean_up(void);
// This Funtion will print the game rules: No.15
void print_game_rules(void);
#endif
