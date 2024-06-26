#include <iostream>
#include <fstream>
#include <cstring>

#define input "{args}"
#define getvar "{getuser:myvar2}"

void update_board(int row, int col, char player, char board[3][3]);
void write_var(char array[]);

int main ()
{
    char board[3][3];
    char oneDArray[11]; 
    oneDArray[10] = '\0'; 
    int row, col;

    // READ USER INPUT
    if (input[0] >= '1' && input[0] <= '3' && input[2] >= '1' && input[2] <= '3')
	{
        row = input[0] - '1';
        col = input[2] - '1';
    } 
    else if(input == "restart" || input == "reset" || input == "stop")
	{
		printf("Board cleared! Start a new game :)"); 
		char clear[11] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '0', '\0'};
		write_var(clear);
        return 1;
    }
    else{
        printf("Invalid input format\n");
        return 1;
    }

    // READ ARRAY 
    for (int i = 0; i < 3; ++i)
	{
        for (int j = 0; j < 3; ++j) {
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
	
	// AI MOVE
	update_board(3, 3, 'O', board); // hardcoded move for now

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

    // READ BOARD
    for (int i = 0; i < 3; ++i)
	{
        for (int j = 0; j < 3; ++j)
		{
            oneDArray[i * 3 + j] = board[i][j];
        }
    }
	
    oneDArray[9] = '1';
	
	// WRITE TO JSON
    write_var(oneDArray);
	
    return 0;
}

void update_board(int row, int col, char mark, char board[3][3])
{
    board[row][col] = mark;
}

void write_var(char array[])
{
	std::string filename = "./output/__internals__.json";
	std::ofstream file(filename);
	std::string jsonString = std::string(R"({
        "storage":  {"server": {}, "user": {"myvar2": ")") + array + R"("}, "channel": {}}
    })";
	
	file << jsonString << std::endl;
	file.close();
}

{getuser:myvar2}
