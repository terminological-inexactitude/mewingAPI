#include <iostream>
#include <fstream>
#include <random>

#define input "{args}"
#define getvar "{getuser:myvar2}"

bool check_winner(char player);
void bot_move();
void place_mark(int row, int col, char player);
void clear_board();
void write_var_new(const char array[]);

char gBoard[3][3];
char oneDArray[10];

int main ()
{
    oneDArray[9] = '\0';
    short row, col;
	bool boardFull = true;
	
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
                gBoard[i][j] = ' ';
            }
            else{
                gBoard[i][j] = getvar[i * 3 + j];
            }
        }
    }
	
	// PLAYER MOVE
	place_mark(row, col, 'X');
	
	// BOT MOVE
	bot_move();

    // PRINT BOARD
    printf("\n");
    printf("```");
    printf(" %c | %c | %c\n", gBoard[0][0], gBoard[0][1], gBoard[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gBoard[1][0], gBoard[1][1], gBoard[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gBoard[2][0], gBoard[2][1], gBoard[2][2]);
    printf("```");
    printf("\n");

	 if (check_winner('X')) {
		printf("YOU WIN!");
		clear_board();
		return 1;
	 }
	
	if (check_winner('O')) {
		printf("YOU LOSE!");
		clear_board();
		return 1;
	}

    // READ BOARD
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
			if(gBoard[i][j] == ' '){
				boardFull = false;
				oneDArray[i * 3 + j] = 'E';
			}
			else{
				oneDArray[i * 3 + j] = gBoard[i][j];
			}
		}
    }
	
	if(boardFull){
		printf("It's a tie!");
		clear_board; 
	}
	
    write_var_new(oneDArray);
	
    return 0;
}

bool check_winner(char player) {
    // check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && gBoard[i][1] == player && gBoard[i][2] == player) ||
            (board[0][i] == player && gBoard[1][i] == player && gBoard[2][i] == player)) {
            return true;
        }
    }

    // check diagonals
    if ((board[0][0] == player && gBoard[1][1] == player && gBoard[2][2] == player) ||
        (board[0][2] == player && gBoard[1][1] == player && gBoard[2][0] == player)) {
        return true;
    }

    return false;
}

void bot_move(){
	place_mark(2, 1, 'O');
}

void place_mark(int row, int col, char mark) {
    gBoard[row][col] = mark;
}

void clear_board(){
	char clear[10] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0'}; 
	write_var_new(clear);
}

void write_var_new(const char array[]) {
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"user":{"myvar2":")" << array << R"("},"channel":{}}})";
}
