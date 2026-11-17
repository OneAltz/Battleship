#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "MonteCarlo.h"

int main(void)
{
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Display welcome screen
    welcome_screen();

    // Run Monte Carlo simulation
    int best_row = 0;
    int best_col = 0;

    monte_carlo_simulation(&best_row, &best_col);

    printf("Best Shot: %c%d\n", 'A' + best_row, best_col + 1);

    return 0;
}
