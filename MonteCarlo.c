#include <stdio.h>
#include <stdlib.h>
#include "MonteCarlo.h"

#define SIMULATIONS 1000

void monte_carlo_simulation(ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS], int *best_row, int *best_col)
{
    int heatmap[SIZE][SIZE] = {0};
    int hit_rows[MAX_SHIPS][5] = {{0}}, hit_cols[MAX_SHIPS][5] = {{0}}, hit_count[MAX_SHIPS] = {0};
    int ship_order[MAX_SHIPS], order_count = 0, valid_simulations = 0;
    *best_row = -1; *best_col = -1;

    // Only inspect ship IDs at locations already hit. Never read hidden cells to predict a move.
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (!attacked[row][col] || game_board[row][col] == WATER) {continue;}
            int index = game_board[row][col] - 1;
            if (index >= 0 && index < MAX_SHIPS && ships[index].health > 0 && hit_count[index] < 5) {
                hit_rows[index][hit_count[index]] = row;
                hit_cols[index][hit_count[index]] = col;
                hit_count[index]++;
            }
        }
    }

    // Place partially discovered ships first, so simulations honor known hits.
    for (int ship = 0; ship < MAX_SHIPS; ship++) {if (ships[ship].health > 0 && hit_count[ship] > 0) {ship_order[order_count++] = ship;}}
    for (int ship = 0; ship < MAX_SHIPS; ship++) {if (ships[ship].health > 0 && hit_count[ship] == 0) {ship_order[order_count++] = ship;}}

    for (int sim = 0; sim < SIMULATIONS; sim++)
    {
        bool simulated[SIZE][SIZE] = {{false}};
        int complete = 1;

        // Keep already sunk ships out of the remaining fleet's placements.
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!attacked[row][col] || game_board[row][col] == WATER) {continue;}
                int index = game_board[row][col] - 1;
                if (index >= 0 && index < MAX_SHIPS && ships[index].health == 0) {simulated[row][col] = true;}
            }
        }

        for (int order = 0; order < order_count; order++)
        {
            int ship = ship_order[order], size = ships[ship].size;
            int choices = 0, chosen_row = -1, chosen_col = -1, chosen_direction = 0;

            // Reservoir sampling randomly chooses one possible position, without bias.
            for (int direction = 0; direction < 2; direction++) {
                for (int row = 0; row < SIZE; row++) {
                    for (int col = 0; col < SIZE; col++) {
                        if ((direction == 0 && col + size > SIZE) || (direction == 1 && row + size > SIZE)) {continue;}
                        int valid = 1;
                        for (int i = 0; i < size; i++) {
                            int r = row + (direction == 1 ? i : 0), c = col + (direction == 0 ? i : 0);
                            if (simulated[r][c]) {valid = 0;break;}
                            if (attacked[r][c] && game_board[r][c] != ships[ship].type) {valid = 0;break;}
                        }
                        if (!valid) {continue;}
                        for (int h = 0; h < hit_count[ship]; h++) {
                            int hr = hit_rows[ship][h], hc = hit_cols[ship][h];
                            int matches = direction == 0 ? (hr == row && hc >= col && hc < col + size) : (hc == col && hr >= row && hr < row + size);
                            if (!matches) {valid = 0;break;}
                        }
                        if (!valid) {continue;}
                        choices++;
                        if (rand() % choices == 0) {chosen_row = row;chosen_col = col;chosen_direction = direction;}
                    }
                }
            }
            if (choices == 0) {complete = 0;break;}
            for (int i = 0; i < size; i++) {
                int r = chosen_row + (chosen_direction == 1 ? i : 0), c = chosen_col + (chosen_direction == 0 ? i : 0);
                simulated[r][c] = true;
            }
        }
        if (!complete) {continue;}
        valid_simulations++;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {if (!attacked[row][col] && simulated[row][col]) {heatmap[row][col]++;}}
        }
    }

    int high_score = -1, ties = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (attacked[row][col]) {continue;}
            if (heatmap[row][col] > high_score) {high_score = heatmap[row][col];*best_row = row;*best_col = col;ties = 1;}
            else if (heatmap[row][col] == high_score && rand() % ++ties == 0) {*best_row = row;*best_col = col;}
        }
    }
    printf("Monte Carlo: %d valid fleet simulations of %d attempts.\n", valid_simulations, SIMULATIONS);
    if (*best_row >= 0) {printf("Recommended shot: %c%d (score %d)\n", 'A' + *best_row, *best_col + 1, high_score);}
}
