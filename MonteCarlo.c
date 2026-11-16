
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 10
#define SIMULATIONS 1000
#define SHIPS 5

void monte_carlo_simulation(void)
{
    int ship_sizes[SHIPS] = {5, 4, 3, 3, 2};
    int heatmap[SIZE][SIZE] = {0};

    // Run 1000 simulations
    for (int sim = 0; sim < SIMULATIONS; sim++)
    {
        int board[SIZE][SIZE] = {0};

        // Place all five ships randomly
        for (int ship = 0; ship < SHIPS; ship++)
        {
            int placed = 0;

            while (!placed)
            {
                int row = rand() % SIZE;
                int col = rand() % SIZE;
                int direction = rand() % 2;
                int length = ship_sizes[ship];
                int valid = 1;

                // Check board boundaries
                if (direction == 0 && col + length > SIZE)
                    continue;

                if (direction == 1 && row + length > SIZE)
                    continue;

                // Check for overlapping ships
                for (int i = 0; i < length; i++)
                {
                    int r = row + (direction == 1 ? i : 0);
                    int c = col + (direction == 0 ? i : 0);

                    if (board[r][c] == 1)
                    {
                        valid = 0;
                        break;
                    }
                }

                if (!valid)
                    continue;

                // Place the ship
                for (int i = 0; i < length; i++)
                {
                    int r = row + (direction == 1 ? i : 0);
                    int c = col + (direction == 0 ? i : 0);

                    board[r][c] = 1;
                }

                placed = 1;
            }
        }

        // Update the heatmap
        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                heatmap[row][col] += board[row][col];
            }
        }
    }

    // Find the highest scoring square
    int best_row = 0;
    int best_col = 0;

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (heatmap[row][col] >
                heatmap[best_row][best_col])
            {
                best_row = row;
                best_col = col;
            }
        }
    }

    printf("\nMonte Carlo Simulation Complete!\n");
    printf("Simulations: %d\n", SIMULATIONS);

    printf("Best Shot: %c%d\n",
           'A' + best_row, best_col + 1);

    printf("Estimated Probability: %.2f%%\n",
           heatmap[best_row][best_col] * 100.0
           / SIMULATIONS);
}
