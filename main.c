
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "MonteCarlo.h"

int main(void)
{
    int best_row = 0;
    int best_col = 0;
    int player_decision = 0;

    srand((unsigned int)time(NULL));

    while (player_decision != 3)
    {
        printf("\n===== BATTLESHIP =====\n");
        printf("Enter 1 for the rules\n");
        printf("Enter 2 for the game\n");
        printf("Enter 3 to quit\n");
        printf("Choice: ");

        if (scanf("%d", &player_decision) != 1)
        {
            printf("Invalid input!\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            player_decision = 0;
            continue;
        }

        if (player_decision == 1)
        {
            print_game_rules();
        }
        else if (player_decision == 2)
        {
            printf("\nStarting Monte Carlo simulation...\n");

            best_row = 0;
            best_col = 0;

            monte_carlo_simulation(&best_row, &best_col);

            printf("Best move: %c%d\n",
                   'A' + best_row, best_col + 1);
        }
        else if (player_decision == 3)
        {
            printf("Thanks for playing!\n");
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
