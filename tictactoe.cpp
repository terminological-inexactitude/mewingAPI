#include <iostream>
#include <fstream>

#define input "{args}"
#define getvar "{getuser:myvar2}"

bool check_winner(char board[3][3], char player);
bool is_board_full(char board[3][3]);
void bot_move(char board[3][3]);
void update_board(int row, int col, char player, char board[3][3]);
void clear_board();
void write_var_new(const char array[]);

int main ()
{
    char board[3][3];
    char oneDArray[10];
    oneDArray[9] = '\0';
    short row, col;
	
    if (input[0] >= '1' && input[0] <= '3' && input[2] >= '1' && input[2] <= '3'){
		row = input[0] - '1';
        col = input[2] - '1';
    } 
    else if(input == "clear"){	
		printf("\nBoard cleared!");
		clear_board();
        return 1;
    }
    else{
        printf("Invalid input format! Use 'row' 'column'");
        return 1;
    }

    // READ ARRAY 
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if(getvar[i * 3 + j] == 'E'){
                board[i][j] = ' ';
            }
            else{
                board[i][j] = getvar[i * 3 + j];
            }
        }
    }
	
	// PLAYER MOVE
	update_board(row, col, 'X', board);
	
	// BOT MOVE
	bot_move(board);

    // PRINT BOARD
    printf("\n");
    printf("```");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("```");
    printf("\n");

	 if (check_winner(board, 'X')) {
		printf("\nYOU WIN!");
		clear_board();
		return 1;
	 }
	
	if (check_winner(board, 'O')) {
		printf("\nYOU LOSE!");
		clear_board();
		return 1;
	}
	
	if (is_board_full(board)){
		printf("\nIt's a tie!");
		clear_board();
		return 1;
	}

    // READ BOARD
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
			if(board[i][j] == ' '){
				oneDArray[i * 3 + j] = 'E';
			}
			else{
				oneDArray[i * 3 + j] = board[i][j];
			}
		}
    }
	
    write_var_new(oneDArray);
	
    return 0;
}

bool check_winner(char board[3][3], char player) {
    // check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool is_board_full(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ' || board[i][j] == 'E') {
                return false; // found an empty space
            }
        }
    }
    return true;
}

void bot_move(char board[3][3]){
	update_board(2, 1, 'O', board);
}

void update_board(int row, int col, char mark, char board[3][3]) {
    board[row][col] = mark;
}

void clear_board(){
	char clear[10] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0'}; 
	write_var_new(clear);
}

void write_var_new(const char array[]) {
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"user":{"myvar2":")" << array << R"("},"channel":{}}})";
}
