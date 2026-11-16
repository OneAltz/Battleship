#ifndef MONTECARLO_H
#define MONTECARLO_H

#define BOARD_SIZE 10

int monte_carlo_target(
    const char shots[BOARD_SIZE][BOARD_SIZE],
    const int ship_lengths[],
    int ship_count,
    int *best_row,
    int *best_col
);

#endif