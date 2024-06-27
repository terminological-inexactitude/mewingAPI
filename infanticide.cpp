
#include <iostream>
#include <fstream>
#include <cstring>

#define input "{args}"
#define getvar "{getuser:myvar2}"

bool check_winner(char board[3][3], char player);
void bot_move(char board[3][3]);
void update_board(int row, int col, char player, char board[3][3]);
void clear_board();
void write_var(char array[]);

int main ()
{
    char board[3][3];		// playing board
    char oneDArray[11];		// playing board in 1D format to write to JSON
    oneDArray[10] = '\0'; 	// null terminator 
    int row, col;
	
    // READ USER INPUT
    if (input[0] >= '1' && input[0] <= '3' && input[2] >= '1' && input[2] <= '3'){
        row = input[0] - '1';
        col = input[2] - '1';
    } 
    else if(input == "restart" || input == "reset" || input == "clear" || input == "new"){
		clear_board();
        return 1;
    }
    else{
        printf("Invalid input format:bangbang:\nUse .t tictactoe 1 3 for example\n");
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

    // PRINT BOARD TO DISPLAY
    printf("\n");
    printf("```");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("```");
    printf("\n");

	// CHECK WINNER 
	 if (check_winner(board, 'X')) {
		printf("\nYOU WIN!\n");
		clear_board();
		return 1;
	 }
	
	if (check_winner(board, 'O')) {
		printf("\nYOU LOSE!\n");
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
	
    oneDArray[9] = '1';
	
	// WRITE TO JSON
    write_var(oneDArray);
	
    return 0;
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

void bot_move(char board[3][3]){
	update_board(2, 1, 'O', board); // hardcoded move for now
}

void update_board(int row, int col, char mark, char board[3][3]) {
    board[row][col] = mark;
}

void clear_board(){
	// clear the board and write emtpy board to JSON
	printf("\nBoard cleared! Start a new game :interrobang:"); // 🕹
	char clear[11] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '0', '\0'}; 
	write_var(clear);
}

void write_var(char array[]){
	std::string filename = "./output/__internals__.json";
	std::ofstream file(filename);
	std::string jsonString = std::string(R"({
        "storage":  {"server": {}, "user": {"myvar2": ")") + array + R"("}, "channel": {}}
    })";
	
	file << jsonString << std::endl;
	file.close();
}


