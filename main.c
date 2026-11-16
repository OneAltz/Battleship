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
    monte_carlo_simulation();

    return 0;
}
