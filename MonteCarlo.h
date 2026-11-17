#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "solve.h"

// Finds an untried shot using known hits, misses, and remaining ship sizes.
void monte_carlo_simulation(ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS], int *best_row, int *best_col);
#endif
