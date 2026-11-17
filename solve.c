#include "solve.h"
#include "MonteCarlo.h"
struct ship ships[5] = {
    {CARRIER,    "Carrier",    5, 5, {{0}}},
    {BATTLESHIP, "Battleship", 4, 4, {{0}}},
    {CRUISER,    "Cruiser",    3, 3, {{0}}},
    {SUBMARINE,  "Submarine",  3, 3, {{0}}},
    {DESTROYER,  "Destroyer",  2, 2, {{0}}}
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
ShipType game_board[10][10] = {WATER};
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

void manually_place_ships_on_board(char board[10][10], ShipType game_board[10][10])
{
    int ship_sizes[5] = {5, 4, 3, 3, 2};
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
            printf("\nPlace your %s (%d spaces)\n", ships[ship].name, ship_sizes[ship]);

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
            for (int i = 0; i < ship_sizes[ship]; i++)
            {
                int r = row;
                int c = col;

                if (direction == 'H')
                c += i;
                else
                r += i;

                // Store ship identity on the board
                board[r][c] = 's';
                game_board[r][c] = ships[ship].type;

                // Remember the ship's coordinates
                ships[ship].positions[i].row = r;
                ships[ship].positions[i].col = c;
}
        }
    }
}
void randomly_place_ships_on_board(char board[10][10], ShipType game_board[10][10])
{
    int ship_sizes[5] = {5, 4, 3, 3, 2};
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
            if (valid == 0) {continue;}

            // Place ship
            for (int i = 0; i < ship_sizes[ship]; ++i)
            {
                int r = row;
                int c = col;
                if (direction == 'H') c += i;
                else r += i;
                board[r][c] = ships[ship].type;
                game_board[r][c] = ships[ship].type;
            }
}
}
int check_shot(ShipType board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[5], int row, int col)
{
    int misses = 0, hits = 0, total_shots = 0;
    if (row < 0 || row >= SIZE ||col < 0 || col >= SIZE) {return -1;}
    if (attacked[row][col]) {printf("Already attacked this square!\n");return -1;}
    attacked[row][col] = true;
    ShipType target = board[row][col];
    if(target == WATER) {printf("Miss!\n");misses++;return 0;}
    if(game_board[row][col] == CARRIER || game_board[row][col] == BATTLESHIP || game_board[row][col] == CRUISER || game_board[row][col] == SUBMARINE || game_board[row][col] == DESTROYER)
    {printf("Hit! You hit the %s!\n", ships[target - 1].name);hits++; ships[target - 1].health--; board[row][col] = 'X'; game_board[row][col] = WATER;}
    if (ships[target - 1].health == 0) {printf("You sunk the %s!\n",ships[target - 1].name);}
    total_shots = misses + hits;
    return 1;
}
bool is_winner(char game_board[10][10])
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (game_board[i][j] == CARRIER || game_board[i][j] == BATTLESHIP || game_board[i][j] == CRUISER || game_board[i][j] == SUBMARINE || game_board[i][j] == DESTROYER) return false;
        }
    }
    return true;
}
void display_game_board(ShipType board[10][10])
{
    printf("    ");
    for (int col = 1; col <= 10; col++) {printf("%2d ", col);}
    printf("\n");
    for (int row = 0; row < 10; row++) {printf("%c   ", 'A' + row); for (int col = 0; col < 10; col++) {if (board[row][col] == WATER) {printf(" ~ ");}else {printf(" S ");}}printf("\n");}
}
/*
bool check_if_sunk_ship(char game_board[10][10])
{
    int sunk_carrier = 0, sunk_battleship = 0, sunk_cruiser = 0, sunk_submarine = 0, sunk_destroyer = 0;
     for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (game_board[i][j] == CARRIER) {sunk_carrier += 1; printf("Sunk Carrier: %d\n", sunk_carrier);}
            if (game_board[i][j] == BATTLESHIP) {sunk_battleship += 1; printf("Sunk Battleship: %d\n", sunk_battleship);}
            if (game_board[i][j] == CRUISER) {sunk_cruiser += 1; printf("Sunk Cruiser: %d\n", sunk_cruiser);}
            if (game_board[i][j] == SUBMARINE) {sunk_submarine += 1; printf("Sunk Submarine: %d\n", sunk_submarine);}
            if (game_board[i][j] == DESTROYER) {sunk_destroyer += 1; printf("Sunk Destroyer: %d\n", sunk_destroyer);}

        }
    }

}
*/
void output_stats(int *misses, int *hits, int *total_shots, int *Rec, bool *game_over)
{
    int accuracy = (*hits * 100) / *total_shots;
    FILE* file = fopen("stats.txt", "w");
    if(*Rec == 0){fprintf(file, "========== GAME STATS ==========\n");}
    *Rec += 1;
    fprintf(file, "Moves:");
    if(*game_over == true){fprintf(file, "Hit/Miss: %d/%d  Total Shots: %d  Accuracy: %d%%\n", *hits, *misses, *total_shots, accuracy);}
    if(*game_over == true){fprintf(file, "================================\n");}
    fclose(file);
}
void ai_move(char board[10][10])
{
    int best_row = 0, best_col = 0;
    monte_carlo_simulation(&best_row, &best_col);
    board[best_row][best_col] = 'X'; // Mark the hit on the board
    printf("AI fires at %c%d\n", 'A' + best_row, best_col + 1);
    if (board[best_row][best_col] == 'S'){ printf("AI hit a ship at %c%d!\n", 'A' + best_row, best_col + 1);} 
    else {printf("AI missed!\n");}
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