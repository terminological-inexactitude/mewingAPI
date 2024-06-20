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

    // Initialize the board
    sscanf(getvar, "%c%c%c%c%c%c%c%c%c",
        &board[0][0], &board[0][1], &board[0][2],
        &board[1][0], &board[1][1], &board[1][2],
        &board[2][0], &board[2][1], &board[2][2]);

    // Parse input from Discord command
    sscanf(input, "%d %d", &row, &col);

    row--; // Adjust for 0-based index
    col--; // Adjust for 0-based index

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
        printf("%s", setvar);
    } else {
        printf("Invalid move! Please try again.\n");
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
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
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
            if (board[i][j] == ' ') {
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
