
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "solve.h"
#include "MonteCarlo.h"

int main(void)
{
    int player_decision = 0, placement_choice = 0, current_player = 1;
    int player_hits, player_misses, player_total_shots;
    int computer_hits, computer_misses, computer_total_shots, Rec = 0;
    char move_history[SIZE * SIZE * 2][64];
    int move_count = 0;
    bool game_over;
    char player_board[SIZE][SIZE], computer_board[SIZE][SIZE], enemy_view[SIZE][SIZE];
    ShipType player_game_board[SIZE][SIZE], computer_game_board[SIZE][SIZE];
    bool player_attacked[SIZE][SIZE], computer_attacked[SIZE][SIZE];
    struct ship player_ships[MAX_SHIPS], computer_ships[MAX_SHIPS];

    srand((unsigned int)time(NULL)); // Seed random number generator

    while (player_decision != 3)
    {
        welcome_screen();
        printf("Enter your choice: ");
        if (scanf("%d", &player_decision) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            if (ch == EOF) {break;}
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (player_decision == 1)
        {
            // Initialize player and computer boards and ship data
            initialize_game_board(player_board, player_game_board, player_attacked, player_ships);
            initialize_game_board(computer_board, computer_game_board, computer_attacked, computer_ships);
            player_hits = 0; player_misses = 0; player_total_shots = 0;
            computer_hits = 0; computer_misses = 0; computer_total_shots = 0;
            game_over = false;
            move_count = 0;

            printf("\nEnter 1 to manually place ships, 2 to randomly place ships: ");
            if (scanf("%d", &placement_choice) != 1) {break;}
            if (placement_choice == 1) {manually_place_ships_on_board(player_board, player_game_board, player_ships);}
            else {randomly_place_ships_on_board(player_board, player_game_board, player_ships);}
            if (feof(stdin)) {break;}

            randomly_place_ships_on_board(computer_board, computer_game_board, computer_ships);
            printf("\nYour board:\n");
            display_game_board(player_board);
            current_player = select_who_starts_first();
            if (feof(stdin)) {break;}

            while (game_over == false)
            {
                output_current_move(current_player);
                if (current_player == 1)
                {
                    char row_letter;
                    int column, row, col, result;

                    // Hide enemy ships that have not been hit
                    for (int r = 0; r < SIZE; r++) {
                        for (int c = 0; c < SIZE; c++) {enemy_view[r][c] = computer_attacked[r][c] ? computer_board[r][c] : '~';}
                    }
                    printf("\nEnemy board:\n");
                    display_game_board(enemy_view);
                    printf("Enter shot (Example A5): ");
                    if (scanf(" %c%d", &row_letter, &column) != 2) {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {}
                        if (ch == EOF) {game_over = true; break;}
                        printf("Invalid coordinates. Try again.\n");
                        continue;
                    }
                    row = toupper((unsigned char)row_letter) - 'A';
                    col = column - 1;
                    result = check_shot(computer_board, computer_game_board, computer_attacked, computer_ships, row, col);
                    if (result == -1) {printf("Invalid or repeated shot. Try again.\n"); continue;}
                    player_total_shots++;
                    snprintf(move_history[move_count], sizeof(move_history[move_count]), "%3d. Player   %c%-2d %s", move_count + 1, 'A' + row, col + 1, result == 1 ? "HIT" : "MISS");
                    move_count++;
                    printf("%s\n", move_history[move_count - 1]);
                    if (result == 1) {player_hits++;}
                    else {player_misses++;}
                    update_board(computer_board, computer_game_board, computer_attacked);
                    if (is_winner(computer_ships)) {printf("\nYou won!\n"); game_over = true;}
                    else {current_player = 2;}
                }
                else
                {
                    int ai_row = -1, ai_col = -1;
                    int result = ai_move(player_board, player_game_board, player_attacked, player_ships, &ai_row, &ai_col);
                    if (result == -1) {game_over = true; break;}
                    computer_total_shots++;
                    snprintf(move_history[move_count], sizeof(move_history[move_count]), "%3d. Computer %c%-2d %s", move_count + 1, 'A' + ai_row, ai_col + 1, result == 1 ? "HIT" : "MISS");
                    move_count++;
                    printf("%s\n", move_history[move_count - 1]);
                    if (result == 1) {computer_hits++;}
                    else {computer_misses++;}
                    update_board(player_board, player_game_board, player_attacked);
                    printf("\nYour board:\n");
                    display_game_board(player_board);
                    if (is_winner(player_ships)) {printf("\nComputer won!\n"); game_over = true;}
                    else {current_player = 1;}
                }
            }

            if (is_winner(player_ships) || is_winner(computer_ships)) {
                printf("\nPlayer stats:\n");
                output_stats(&player_misses, &player_hits, &player_total_shots, &Rec, &game_over);
                printf("Hits: %d  Misses: %d  Shots: %d\n", player_hits, player_misses, player_total_shots);
                printf("Computer stats:\n");
                output_stats(&computer_misses, &computer_hits, &computer_total_shots, &Rec, &game_over);
                printf("Hits: %d  Misses: %d  Shots: %d\n", computer_hits, computer_misses, computer_total_shots);
            }
            printf("\n========== COMPLETE MOVE HISTORY ==========\n");
            for (int i = 0; i < move_count; i++) {printf("%s\n", move_history[i]);}
            printf("===========================================\n");

            // Save the complete turn-by-turn record, including each shot's result.
            FILE *history_file = fopen("stats.txt", "w");
            if (history_file != NULL) {
                for (int i = 0; i < move_count; i++) {fprintf(history_file, "%s\n", move_history[i]);}
                fclose(history_file);
                printf("\nAll %d moves saved to stats.txt\n", move_count);
            }
            clean_up();
        }
        else if (player_decision == 2) {print_game_rules();}
        else if (player_decision == 3) {printf("Thanks for playing Battleship!\n");}
        else {printf("Invalid choice. Try again.\n");}
    }
    return 0;
}
