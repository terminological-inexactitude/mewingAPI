#include <iostream>
#include <vector>
using namespace std;

#define getvar "{getchannel:game}"

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = '.';

void writeVar(const char array[]){
    std::ofstream file("./output/__internals__.json");
    file << R"({"storage":{"server":{},"channel":{"game":")" << array << R"("},"channel":{}}})";
}

void printBoard(const vector<vector<char>>& board) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            cout << board[r][c] << ' ';
        }
        cout << endl;
    }
}

bool dropCoin(vector<vector<char>>& board, int col, char coin) {
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == EMPTY) {
            board[r][col] = coin;
            return true;
        }
    }
    return false;
}

bool checkWin(const vector<vector<char>>& board, char coin) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] == coin) {
                // Check horizontal
                if (c + 3 < COLS && board[r][c + 1] == coin && board[r][c + 2] == coin && board[r][c + 3] == coin) return true;
                // Check vertical
                if (r + 3 < ROWS && board[r + 1][c] == coin && board[r + 2][c] == coin && board[r + 3][c] == coin) return true;
                // Check diagonal /
                if (r + 3 < ROWS && c + 3 < COLS && board[r + 1][c + 1] == coin && board[r + 2][c + 2] == coin && board[r + 3][c + 3] == coin) return true;
                // Check diagonal '\'
                if (r - 3 >= 0 && c + 3 < COLS && board[r - 1][c + 1] == coin && board[r - 2][c + 2] == coin && board[r - 3][c + 3] == coin) return true;
            }
        }
    }
    return false;
}

int main() {
    vector<vector<char>> board(ROWS, vector<char>(COLS, EMPTY));
    char players[2] = {'X', 'O'};
    int currentPlayer = 0;
    int moves = 0;
    
    while (moves < ROWS * COLS) {
        printBoard(board);
        cout << "Player " << players[currentPlayer] << ", choose a column (0-6): ";
        int col;
        cin >> col;
        
        if (col >= 0 && col < COLS && dropCoin(board, col, players[currentPlayer])) {
            if (checkWin(board, players[currentPlayer])) {
                printBoard(board);
                cout << "Player " << players[currentPlayer] << " wins!" << endl;
                return 0;
            }
            currentPlayer = 1 - currentPlayer;
            moves++;
        } else {
            cout << "Invalid move, try again." << endl;
        }
    }
    
    printBoard(board);
    cout << "It's a draw!" << endl;
    return 0;
}
