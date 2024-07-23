#include <iostream>
#include <fstream>
#include <cstdlib>

#define input "{args}"
#define getvar "{getuser:myvar2}"

void botMove();
void printBoard();
void clearArray();
bool checkWinner(char player);
void writeVar(const char array[]);

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
		printf("Board cleared!");
		clearArray();
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
	if(gBoard[row][col] == ' '){
		gBoard[row][col] = 'X';
	}
	else{
		printf("That spot is already occupied by a %C!\n", gBoard[row][col]);
		printBoard();
		return 2;
	}
	
	if (checkWinner('X')) {
		printBoard();
		printf("YOU WIN!");
		clearArray();
		return 3;
	}
	
	// BOT MOVE
	botMove();
	
    // PRINT BOARD
	printBoard();
	
	if (checkWinner('O')){
		printf("YOU LOSE!");
		clearArray();
		return 3;
	}

    // READ BOARD
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
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
		clearArray();		
		return 3;
	}
	
    writeVar(oneDArray);
	
    return 0;
}

void botMove(){
	int r, c, count = 0;
	if(gBoard[1][1] == ' '){
		gBoard[1][1] = 'O'; return;
	}
	
	do{
		r = rand() % 3;
		c = rand() % 3;
		if(++count >= 10 ) break;
	}
	while (gBoard[r][c] != ' ');
	if(count < 10) gBoard[r][c] = 'O';
}

void printBoard(){
    printf("\n```");
    printf(" %c | %c | %c\n", gBoard[0][0], gBoard[0][1], gBoard[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gBoard[1][0], gBoard[1][1], gBoard[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gBoard[2][0], gBoard[2][1], gBoard[2][2]);
    printf("```\n");
}

void clearArray(){
	char clear[10] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0'}; 
	writeVar(clear);
}

bool checkWinner(char player){
    // check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((gBoard[i][0] == player && gBoard[i][1] == player && gBoard[i][2] == player) ||
            (gBoard[0][i] == player && gBoard[1][i] == player && gBoard[2][i] == player)) {
            return true;
        }
    }

    // check diagonals
    if ((gBoard[0][0] == player && gBoard[1][1] == player && gBoard[2][2] == player) ||
        (gBoard[0][2] == player && gBoard[1][1] == player && gBoard[2][0] == player)) {
        return true;
    }

    return false;
}

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"user":{"myvar2":")" << array << R"("},"channel":{}}})";
}
