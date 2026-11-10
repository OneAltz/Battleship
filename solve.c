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
    for(int i = 0; i < 12; ++i){for (int j = 0; j < 11; ++j){printf("%c", board[j][i]);} printf("\n");}
}
void select_who_starts_first()
{
    
}
void manually_place_ships_on_board()
{
    
}
void randomly_place_ships_on_board()
{
    
}
int check_shot()
{
    
}
bool is_winner()
{
    
}
void update_board()
{
    
}
void display_game_board()
{
    
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