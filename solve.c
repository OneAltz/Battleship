#include "solve.h"
    struct ship {
        char name[20];
        int size;
        int health;
    };
    struct ship ships[5] = {
        {"Carrier", 5, 5},
        {"Battleship", 4, 4},
        {"Cruiser", 3, 3},
        {"Submarine", 3, 3},
        {"Destroyer", 2, 2}
    };
void welcome_screen()
{
    puts("BBBBBBBBBB       AAAAAA     TTTTTTTTTTT TTTTTTTTTTT  LLLLL        EEEEEEEEEEE");
    puts("BBBBBBBBBBB     AAAAAAAA    TTTTTTTTTTT TTTTTTTTTTT  LLLLL        EEEEEEEEEEE");
    puts("BBBB    BBB    AAA    AAA       TTT         TTT      LLLLL        EEEE");
    puts("BBBBBBBBBBB    AAAAAAAAAA       TTT         TTT      LLLLL        EEEEEEEEEE");
    puts("BBBBBBBBBBB    AAAAAAAAAA       TTT         TTT      LLLLL        EEEEEEEEEE");
    puts("BBBB    BBB    AAA    AAA       TTT         TTT      LLLLL        EEEE");
    puts("BBBBBBBBBBB    AAA    AAA       TTT         TTT      LLLLLLLLLLL  EEEEEEEEEEE");
    puts("BBBBBBBBBB     AAA    AAA       TTT         TTT      LLLLLLLLLLL  EEEEEEEEEEE");
    puts("");
    puts(" SSSSSSSSS   HHHH    HHHH  IIIIIIIIIII  PPPPPPPPPP");
    puts("SSSSSSSSSSS  HHHH    HHHH  IIIIIIIIIII  PPPPPPPPPPP");
    puts("SSSS         HHHH    HHHH      III      PPPP    PPP");
    puts(" SSSSSSSSS   HHHHHHHHHHHH      III      PPPPPPPPPPP");
    puts("  SSSSSSSSS  HHHHHHHHHHHH      III      PPPPPPPPPP");
    puts("       SSSS  HHHH    HHHH      III      PPPP");
    puts("SSSSSSSSSSS  HHHH    HHHH  IIIIIIIIIII  PPPP");
    puts(" SSSSSSSSS   HHHH    HHHH  IIIIIIIIIII  PPPP");
    puts("");
    puts("Would you Like To Start: Press 1");
    puts("Would you Like To Print the Rules: Press 2");
    puts("Would you Like To Exit the Game: Press 3");

}
void initialize_game_board()
{
    const char *board[11][11] = {
    {"♡", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},
    {"A", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"B", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"C", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"D", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"E", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"F", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"G", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"H", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"I", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
    {"J", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"}
};
}
void select_who_starts_first(void)
{
    enum { tails = 1, heads = 2 };
    char choice;
    int coin_flip, current_player;

    printf("Player 1, choose Heads (H) or Tails (T): ");
    scanf(" %c", &choice);
    choice = tolower((unsigned char)choice);
    while (choice != 'h' && choice != 't'){printf("Invalid choice. Enter H or T: "); scanf(" %c", &choice); choice = tolower((unsigned char)choice);}
    coin_flip = (rand() % 2) + 1;
    if (coin_flip == heads){printf("The coin landed on Heads!\n");}
    else{printf("The coin landed on Tails!\n");}
    if ((choice == 'h' && coin_flip == heads) || (choice == 't' && coin_flip == tails)){current_player = 1;}
    else{current_player = 2;}
    printf("Player %d goes first!\n", current_player);
}

void manually_place_ships_on_board(char board[10][10])
{
    int ship_sizes[5] = {5, 4, 3, 3, 2};

    const char *ship_names[5] = {
        "Carrier",
        "Battleship",
        "Cruiser",
        "Submarine",
        "Destroyer"
    };

    char row_letter;
    char direction;
    int column;
    int row;
    int col;
    int valid;

    for (int ship = 0; ship < 5; ++ship)
    {
        valid = 0;
        while (valid == 0)
        {
            printf("\nPlace your %s (%d spaces)\n", ship_names[ship], ship_sizes[ship]);

            printf("Enter row (A-J): ");
            if (scanf(" %c", &row_letter) != 1) return;
            row_letter = toupper((unsigned char)row_letter);

            printf("Enter starting column (1-10): ");
            if (scanf("%d", &column) != 1) return;

            printf("Horizontal (H) or Vertical (V): ");
            if (scanf(" %c", &direction) != 1) return;

            direction = toupper((unsigned char)direction);

            row = row_letter - 'A';
            col = column - 1;

            if (row < 0 || row >= 10 || col < 0 || col >= 10 || (direction != 'H' && direction != 'V')){printf("Invalid input. Try again.\n");continue; }

            if ((direction == 'H' && col + ship_sizes[ship] > 10) || (direction == 'V' && row + ship_sizes[ship] > 10)){printf("Ship goes outside the board!\n"); continue;} valid = 1;

            for (int i = 0; i < ship_sizes[ship]; ++i)
            {
                int r = row;
                int c = col;
                if (direction == 'H') c += i;
                else r += i;
                if (board[r][c] != '~') {valid = 0; break;}
            }
            if (valid == 0) {printf("A ship is already there!\n");continue;}

            // Place ship
            for (int i = 0; i < ship_sizes[ship]; ++i)
            {
                int r = row;
                int c = col;
                if (direction == 'H') c += i;
                else r += i;
                board[r][c] = 'S';
            }
            printf("%s placed successfully!\n", ship_names[ship]);
        }
    }
}
void randomly_place_ships_on_board(char board[10][10])
{
    int ship_sizes[5] = {5, 4, 3, 3, 2};
    const char *ship_names[5] = {
        "Carrier",
        "Battleship",
        "Cruiser",
        "Submarine",
        "Destroyer"
    };
    char row_letter;
    char direction;
    int column;
    int row;
    int col;
    int valid;
    for (int ship = 0; ship < 5; ++ship)
    {
            row_letter = 'A' + (rand() % 10);
            column = (rand() % 10) + 1;
            direction = (rand() % 2) == 0 ? 'H' : 'V';
            row = row_letter - 'A';
            col = column - 1;

            if (row < 0 || row >= 10 || col < 0 || col >= 10 || (direction != 'H' && direction != 'V')){continue; }
            if ((direction == 'H' && col + ship_sizes[ship] > 10) || (direction == 'V' && row + ship_sizes[ship] > 10)){continue;} valid = 1;
            for (int i = 0; i < ship_sizes[ship]; ++i)
            {
                int r = row;
                int c = col;
                if (direction == 'H') c += i;
                else r += i;
                if (board[r][c] != '~') {valid = 0; break;}
            }
            if (valid == 0) {printf("A ship is already there!\n");continue;}

            // Place ship
            for (int i = 0; i < ship_sizes[ship]; ++i)
            {
                int r = row;
                int c = col;
                if (direction == 'H') c += i;
                else r += i;
                board[r][c] = 'S';
            }
}
}
int check_shot(char board[10][10])
{
    int row;
    char column;
    do{
    printf("Enter row (0-9): ");
    scanf("%d", &row);
    printf("Enter column (A-J): ");
    scanf(" %c", &column);
    column = toupper((unsigned char)column);
    int col = column - 'A';
    if (row < 0 || row >= 10 || col < 0 || col >= 10){printf("Invalid coordinates. Try again.\n");return -1;}
    if(board[row][col] == 'S'){board[row][col] = 'X';printf("Hit!\n");return 1;}
    else{board[row][col] = 'O';printf("Miss!\n");return 0;}
    }while (board[row][column - 'A'] == 'O');

}
bool is_winner(char board[10][10])
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (board[i][j] == 'S') return false;
        }
    }
    return true;
}
void display_game_board(char board[10][10])
{
     for(int i = 0; i < 12; ++i){for (int j = 0; j < 11; ++j){printf("%c", board[j][i]);} printf("\n");}
}
typedef struct {
    int row;
    int col;
} Shot;

// Add a valid ship placement to the heat map.
void score_placement(
    char shots[SIZE][SIZE],
    int heat[SIZE][SIZE],
    int row,
    int col,
    int length,
    int horizontal
) {
    int hits = 0;

    // First check whether the placement is possible.
    for (int i = 0; i < length; i++) {
        int r = row + (horizontal ? 0 : i);
        int c = col + (horizontal ? i : 0);

        if (r >= SIZE || c >= SIZE) {
            return;
        }

        if (shots[r][c] == 'O' ||
            shots[r][c] == 'S') {
            return;
        }

        if (shots[r][c] == 'X') {
            hits++;
        }
    }

    // Give extra weight to placements containing hits.
    int points = 1 + hits * HIT_BONUS;

    for (int i = 0; i < length; i++) {
        int r = row + (horizontal ? 0 : i);
        int c = col + (horizontal ? i : 0);

        // Only unknown squares can be targeted.
        if (shots[r][c] == '~') {
            heat[r][c] += points;
        }
    }
}

// Recalculate the entire heat map.
void calculate_heat_map(
    char shots[SIZE][SIZE],
    int heat[SIZE][SIZE],
    int ship_sizes[],
    int ship_count
) {
    // Reset the heat map.
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            heat[r][c] = 0;
        }
    }

    // Evaluate each remaining ship.
    for (int s = 0; s < ship_count; s++) {
        int length = ship_sizes[s];

        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {

                // Horizontal placement
                score_placement(
                    shots, heat, r, c, length, 1
                );

                // Vertical placement
                score_placement(
                    shots, heat, r, c, length, 0
                );
            }
        }
    }
}

// Choose randomly among the highest-scoring squares.
Shot find_best_shot(
    char shots[SIZE][SIZE],
    int heat[SIZE][SIZE]
) {
    Shot best = {-1, -1};
    int highest = -1;
    int ties = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {

            if (shots[r][c] != '~') {
                continue;
            }

            int score = heat[r][c];

            if (score > highest) {
                highest = score;
                best.row = r;
                best.col = c;
                ties = 1;
            }
            else if (score == highest) {
                ties++;

                // Reservoir sampling for random ties.
                if (rand() % ties == 0) {
                    best.row = r;
                    best.col = c;
                }
            }
        }
    }

    return best;
}
void print_heat_map(int heat[SIZE][SIZE]) {
    printf("\n              HEAT MAP\n\n");

    printf("      ");
    for (int c = 1; c <= SIZE; c++) {
        printf("%5d", c);
    }
    printf("\n");

    for (int r = 0; r < SIZE; r++) {
        printf("  %c   ", 'A' + r);

        for (int c = 0; c < SIZE; c++) {
            printf("%5d", heat[r][c]);
        }

        printf("\n");
    }
}

void output_current_move()
{
    
}
bool check_if_sunk_ship()
{
    
}
void output_stats()
{
    
}
void ai_move()
{
    
}
void ai_message()
{
    
}
void clean_up()
{
    
}
void print_game_rules()
{
    puts("\n========== BATTLESHIP RULES ==========\n");

    puts("OBJECTIVE:");
    puts("Sink all of your opponent's ships to win.\n");

    puts("SETUP:");
    puts("1. Each player has a 10x10 grid.");
    puts("2. Each player places 5 ships on their grid.");
    puts("3. Ships can be placed horizontally or vertically.");
    puts("4. Ships cannot overlap or go off the grid.");
    puts("5. Players cannot see the opponent's ships.\n");

    puts("SHIPS:");
    puts("Carrier:     5 spaces");
    puts("Battleship:  4 spaces");
    puts("Cruiser:     3 spaces");
    puts("Submarine:   3 spaces");
    puts("Destroyer:   2 spaces\n");

    puts("HOW TO PLAY:");
    puts("1. Players take turns firing one shot.");
    puts("2. Enter a coordinate such as A5.");
    puts("3. A HIT means a ship occupies that space.");
    puts("4. A MISS means the space is empty.");
    puts("5. Mark each hit and miss on the grid.");
    puts("6. A ship sinks when all its spaces are hit.");
    puts("7. Players cannot fire at the same space twice.\n");

    puts("WINNING:");
    puts("The first player to sink all 5 enemy ships wins!");

    puts("\n======================================\n");
}