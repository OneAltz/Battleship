
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "solve.h"
#include "MonteCarlo.h"

int main(void)
{
    int player_decision = 0;
    int best_row = 0;
    int best_col = 0;

    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // Display welcome screen
    welcome_screen();

    // Main menu
    while (player_decision != 3)
    {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Start Game\n");
        printf("2. Game Rules\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &player_decision) != 1)
        {
            int ch;

            printf("Invalid input!\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            if (ch == EOF)
            {
                break;
            }

            player_decision = 0;
            continue;
        }

        switch (player_decision)
        {
            case 1:
                printf("\nStarting Battleship...\n");

                // Reset coordinates
                best_row = 0;
                best_col = 0;

                // Run Monte Carlo simulation
                monte_carlo_simulation(
                    &best_row,
                    &best_col
                );

                printf("\nBest Shot: %c%d\n",
                       'A' + best_row,
                       best_col + 1);

                break;

            case 2:
                print_game_rules();
                break;

            case 3:
                printf("\nExiting Battleship...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
