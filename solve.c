#include "solve.h"
#include "MonteCarlo.h"

void welcome_screen(void)
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

void initialize_game_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS])
{
    const struct ship starting_ships[MAX_SHIPS] = {
        {CARRIER,    "Carrier",    5, 5, {{0}}},
        {BATTLESHIP, "Battleship", 4, 4, {{0}}},
        {CRUISER,    "Cruiser",    3, 3, {{0}}},
        {SUBMARINE,  "Submarine",  3, 3, {{0}}},
        {DESTROYER,  "Destroyer",  2, 2, {{0}}}
    };

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = '~';
            game_board[row][col] = WATER;
            attacked[row][col] = false;
        }
    }
    for (int ship = 0; ship < MAX_SHIPS; ship++) {ships[ship] = starting_ships[ship];}
}

int select_who_starts_first(void)
{
    enum { tails = 1, heads = 2 };
    char choice;
    int coin_flip, current_player;

    printf("Player 1, choose Heads (H) or Tails (T): ");
    if (scanf(" %c", &choice) != 1) {return 1;}
    choice = tolower((unsigned char)choice);
    while (choice != 'h' && choice != 't') {
        printf("Invalid choice. Enter H or T: ");
        if (scanf(" %c", &choice) != 1) {return 1;}
        choice = tolower((unsigned char)choice);
    }
    coin_flip = (rand() % 2) + 1;
    if (coin_flip == heads) {printf("The coin landed on Heads!\n");}
    else {printf("The coin landed on Tails!\n");}
    if ((choice == 'h' && coin_flip == heads) || (choice == 't' && coin_flip == tails)) {current_player = 1;}
    else {current_player = 2;}
    printf("Player %d goes first!\n", current_player);
    return current_player;
}

void manually_place_ships_on_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], struct ship ships[MAX_SHIPS])
{
    char row_letter, direction;
    int column, row, col, valid;

    for (int ship = 0; ship < MAX_SHIPS; ++ship)
    {
        valid = 0;
        while (valid == 0)
        {
            printf("\nPlace your %s (%d spaces)\n", ships[ship].name, ships[ship].size);
            printf("Enter row (A-J): ");
            if (scanf(" %c", &row_letter) != 1) {return;}
            row_letter = toupper((unsigned char)row_letter);
            printf("Enter starting column (1-10): ");
            if (scanf("%d", &column) != 1) {return;}
            printf("Horizontal (H) or Vertical (V): ");
            if (scanf(" %c", &direction) != 1) {return;}
            direction = toupper((unsigned char)direction);
            row = row_letter - 'A';
            col = column - 1;
            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || (direction != 'H' && direction != 'V')) {printf("Invalid input. Try again.\n");continue;}
            if ((direction == 'H' && col + ships[ship].size > SIZE) || (direction == 'V' && row + ships[ship].size > SIZE)) {printf("Ship goes outside the board!\n");continue;}
            valid = 1;
            for (int i = 0; i < ships[ship].size; ++i)
            {
                int r = row + (direction == 'V' ? i : 0);
                int c = col + (direction == 'H' ? i : 0);
                if (game_board[r][c] != WATER) {valid = 0;break;}
            }
            if (valid == 0) {printf("A ship is already there!\n");continue;}
            for (int i = 0; i < ships[ship].size; i++)
            {
                int r = row + (direction == 'V' ? i : 0);
                int c = col + (direction == 'H' ? i : 0);
                board[r][c] = 'S';
                game_board[r][c] = ships[ship].type;
                ships[ship].positions[i].row = r;
                ships[ship].positions[i].col = c;
            }
            printf("%s placed successfully!\n", ships[ship].name);
            display_game_board(board);
        }
    }
}

void randomly_place_ships_on_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], struct ship ships[MAX_SHIPS])
{
    for (int ship = 0; ship < MAX_SHIPS; ++ship)
    {
        int placed = 0;
        while (placed == 0)
        {
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            char direction = (rand() % 2) == 0 ? 'H' : 'V';
            int valid = 1;
            if ((direction == 'H' && col + ships[ship].size > SIZE) || (direction == 'V' && row + ships[ship].size > SIZE)) {continue;}
            for (int i = 0; i < ships[ship].size; ++i)
            {
                int r = row + (direction == 'V' ? i : 0);
                int c = col + (direction == 'H' ? i : 0);
                if (game_board[r][c] != WATER) {valid = 0;break;}
            }
            if (valid == 0) {continue;}
            for (int i = 0; i < ships[ship].size; ++i)
            {
                int r = row + (direction == 'V' ? i : 0);
                int c = col + (direction == 'H' ? i : 0);
                board[r][c] = 'S';
                game_board[r][c] = ships[ship].type;
                ships[ship].positions[i].row = r;
                ships[ship].positions[i].col = c;
            }
            placed = 1;
        }
    }
}

int check_shot(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS], int row, int col)
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {return -1;}
    if (attacked[row][col]) {printf("Already attacked this square!\n");return -1;}
    attacked[row][col] = true;
    ShipType target = game_board[row][col];
    if (target == WATER) {board[row][col] = 'O';printf("Miss!\n");return 0;}
    int index = target - 1;
    if (index < 0 || index >= MAX_SHIPS) {return -1;}
    ships[index].health--;
    board[row][col] = 'X';
    printf("Hit! You hit the %s!\n", ships[index].name);
    if (check_if_sunk_ship(ships, target)) {printf("You sunk the %s!\n", ships[index].name);}
    return 1;
}

bool is_winner(struct ship ships[MAX_SHIPS])
{
    for (int ship = 0; ship < MAX_SHIPS; ship++) {
        if (ships[ship].health > 0) {return false;}
    }
    return true;
}

void update_board(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (attacked[row][col]) {board[row][col] = game_board[row][col] == WATER ? 'O' : 'X';}
        }
    }
}

void display_game_board(char board[SIZE][SIZE])
{
    printf("\n♡  ");
    for (int col = 1; col <= SIZE; col++) {printf("%2d ", col);}
    printf("\n");
    for (int row = 0; row < SIZE; row++) {
        printf("%c  ", 'A' + row);
        for (int col = 0; col < SIZE; col++) {printf(" %c ", board[row][col]);}
        printf("\n");
    }
}

void output_current_move(int current_player)
{
    printf("\nPlayer %d's turn!\n", current_player);
}

bool check_if_sunk_ship(struct ship ships[MAX_SHIPS], ShipType target)
{
    if (target < CARRIER || target > DESTROYER) {return false;}
    return ships[target - 1].health == 0;
}

void output_stats(int *misses, int *hits, int *total_shots, int *Rec, bool *game_over)
{
    int accuracy = *total_shots > 0 ? (*hits * 100) / *total_shots : 0;
    FILE* file = fopen("stats.txt", *Rec == 0 ? "w" : "a");
    if (file == NULL) {printf("Could not open stats.txt\n");return;}
    if (*Rec == 0) {fprintf(file, "========== GAME STATS ==========\n");}
    *Rec += 1;
    fprintf(file, "Game %d: Hit/Miss: %d/%d  Total Shots: %d  Accuracy: %d%%  Finished: %s\n", *Rec, *hits, *misses, *total_shots, accuracy, *game_over ? "Yes" : "No");
    fprintf(file, "================================\n");
    fclose(file);
}

int ai_move(char board[SIZE][SIZE], ShipType game_board[SIZE][SIZE], bool attacked[SIZE][SIZE], struct ship ships[MAX_SHIPS])
{
    int best_row = 0, best_col = 0;
    monte_carlo_simulation(&best_row, &best_col);
    // The basic simulation does not track previous shots. Find an available square if necessary.
    if (attacked[best_row][best_col]) {
        int available = 0;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!attacked[row][col]) {available++;}
            }
        }
        if (available == 0) {return -1;}
        int choice = rand() % available;
        int found = 0;
        for (int row = 0; row < SIZE && !found; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!attacked[row][col]) {
                    if (choice == 0) {best_row = row;best_col = col;found = 1;break;}
                    choice--;
                }
            }
        }
    }
    printf("AI fires at %c%d\n", 'A' + best_row, best_col + 1);
    int result = check_shot(board, game_board, attacked, ships, best_row, best_col);
    ai_message(result);
    return result;
}

void ai_message(int result)
{
    if (result == 1) {printf("AI hit a ship!\n");}
    else if (result == 0) {printf("AI missed!\n");}
}

void clean_up(void)
{
    printf("\nReturning to the main menu.\n");
}

void print_game_rules(void)
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
    puts("Submarine:  3 spaces");
    puts("Destroyer:  2 spaces\n");
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
