#include <iostream>
#include <fstream>

#define input "{args}"
#define usertag {id}LL
#define getvar "{getchannel:game}"

#define ROWS 6
#define COLS 7
#define EMPTY '.'

char gboard[6][7]; // row, column
void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
	file << R"({"storage":{"server":{},"user":{},"channel":{"gamestate":")" << array << R"("}}})";
}

void clearArray() { writeVar(".........................................."); }

void printBoard() {
    for (int r = 0; r < 6; ++r) { // rows
        for (int c = 0; c < 7; ++c) { // columns
            printf("%c ", gboard[r][c]);
        }
        printf("\n");
    }
}

int dropCoin(int col, char coin) {
    for (int r = ROWS - 1; r >= 0; --r) {
        if (gboard[r][col] == EMPTY) {
            gboard[r][col] = coin;
            return 1;
        }
    }
    return 0;
}

int main() {
    //printf("test");
	
	writeVar("usertag"); // save state of the game as an array
	
	// is er een spel gaande? 
	// NEE -> user 1 of 2 | JA -> aan de beurt? NEE -> wacht op je beurt | JA -> maak beurt
	
	
	if(input[0] >= '1' && input[0] <= '7'){
		printf("correct input detected: %c", input[0]);
	}
	
    return 0;
}
