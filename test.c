#include <iostream>
#include <fstream>
#include <cstdlib>

#define input "{args}"
#define getvar "{getuser:myvar2}"

char gBoard[3][3], oneDArray[10];

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"user":{"myvar2":")" << array << R"("},"channel":{}}})";
}

void clearArray() { writeVar("EEEEEEEEE"); }

void printBoard() {
    std::cout << "\n```\n";
    for (int i = 0; i < 3; ++i) {
        if (i > 0) std::cout << "---+---+---\n";
        for (int j = 0; j < 3; ++j) {
            if (j > 0) std::cout << " |";
            std::cout << " " << gBoard[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "```\n";
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

void botMove(){	
	 // Check for a winning or blocking move
     for (int mark = 0; mark < 2; ++mark) {
        char m = mark == 0 ? 'O' : 'X'; // BOT = 'O', PLAYER = 'X'
        for (int i = 0; i < 3; ++i) {
            // Check rows and columns
            for (int j = 0; j < 3; ++j) {
                if (gBoard[i][j] == ' ' && (
                        (gBoard[i][(j+1)%3] == m && gBoard[i][(j+2)%3] == m) || 
                        (gBoard[(i+1)%3][j] == m && gBoard[(i+2)%3][j] == m))) {
                    gBoard[i][j] = 'O'; return;
                }
            }
        }
        // Check diagonals
        if (gBoard[1][1] == ' ' && (
                (gBoard[0][0] == m && gBoard[2][2] == m) || 
                (gBoard[0][2] == m && gBoard[2][0] == m))) {
            gBoard[1][1] = 'O'; return;
        }
        for (int d = 0; d < 2; ++d) {
            if (gBoard[d*2][0] == ' ' && gBoard[1][1] == m && gBoard[(d+1)*2%3][2] == m) {
                gBoard[d*2][0] = 'O'; return;
            }
            if (gBoard[d*2][2] == ' ' && gBoard[1][1] == m && gBoard[(d+1)*2%3][0] == m) {
                gBoard[d*2][2] = 'O'; return;
            }
        }
    }
	
	if(gBoard[1][1] == ' '){
		gBoard[1][1] = 'O'; return;
	}
	
	int r, c, count = 0;
	
	do{
		r = rand() % 3;
		c = rand() % 3;
		if(++count >= 15 ) break;
	}
	while (gBoard[r][c] != ' ');
	if (count < 15) gBoard[r][c] = 'O';
}

int main () {
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
    for (int i = 0; i < 9; ++i)
        gBoard[i / 3][i % 3] = getvar[i] == 'E' ? ' ' : getvar[i];
	
	// PLAYER MOVE
	if(gBoard[row][col] != ' '){
		printf("That spot is already occupied by a %C!\n", gBoard[row][col]);
		printBoard();
		return 2;
	}
	gBoard[row][col] = 'X';
	
	if (checkWinner('X')) {
		printBoard();
		printf("YOU WIN!");
		clearArray();
		return 3;
	}
	
	botMove();
	printBoard();
	
	if (checkWinner('O')){
		printf("YOU LOSE!");
		clearArray();
		return 3;
	}

    for (int i = 0; i < 9; ++i) {
        if (gBoard[i / 3][i % 3] == ' ') {
            boardFull = false;
            oneDArray[i] = 'E';
        } else {
            oneDArray[i] = gBoard[i / 3][i % 3];
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
