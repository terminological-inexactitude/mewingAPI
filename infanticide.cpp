#include <cstdio>
#include <cstring>

// Define for retrieving input from Discord command
#define input "{args}"

// Define for setting and getting game state in Discord
#define setvar "{setuser:game_state|_________}"
#define getvar "{getuser:game_state}"

// Function prototypes
void print_board(char board[3][3]);
bool is_valid_move(int row, int col, char board[3][3]);
bool check_winner(char board[3][3], char player);
bool is_board_full(char board[3][3]);
void update_board(int row, int col, char player, char board[3][3]);

int main() {
    char board[3][3];
    char current_player = 'X';
    int row, col;

    // Initialize the board from saved state or set to underscores if no state
    const char* game_state = getvar;
    if (strlen(game_state) != 9) {
        // If game_state is not properly initialized, set to underscores
        #define setvar "{setuser:game_state|_________}"
        for (int i = 0; i < 9; ++i) {
            board[i / 3][i % 3] = '_';
        }
    } else {
        for (int i = 0; i < 9; ++i) {
            board[i / 3][i % 3] = game_state[i];
        }
    }

    // Parse input from Discord command
    if (input[0] >= '1' && input[0] <= '3' && input[2] >= '1' && input[2] <= '3') {
        row = input[0] - '1'; // Convert '1'-'3' to 0-2
        col = input[2] - '1'; // Convert '1'-'3' to 0-2
    } else {
        printf("Invalid input format! Please use the format: 1 2\n");
        return 1;
    }

    // Check if the move is valid
    if (is_valid_move(row, col, board)) {
        // Update the board
        update_board(row, col, current_player, board);

        // Print the updated board
        print_board(board);

        // Check if current player wins
        if (check_winner(board, current_player)) {
            printf("Player %c wins!\n", current_player);
        } else if (is_board_full(board)) {
            printf("It's a draw!\n");
        }

        // Save updated game state back to Discord
        char new_game_state[10];
        for (int i = 0; i < 9; ++i) {
            new_game_state[i] = board[i / 3][i % 3];
        }
        new_game_state[9] = '\0';
        printf("{setuser:game_state|%s}", new_game_state);
    } else {
        printf("Invalid move!! Please try again.\n");
    }

    return 0;
}

// Function definitions

void print_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

bool is_valid_move(int row, int col, char board[3][3]) {
    // Check if the chosen cell is empty and within bounds
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_');
}

bool check_winner(char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool is_board_full(char board[3][3]) {
    // Check if the board is full
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '_') {
                return false; // Found an empty space
            }
        }
    }
    return true;
}

void update_board(int row, int col, char player, char board[3][3]) {
    // Place the player's move on the board
    board[row][col] = player;
}
