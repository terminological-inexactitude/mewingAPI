#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

static const std::string kArgs  = "{args}";
static const std::string kSaved = "{getuser:myvar2}";
static const bool UNBEATABLE = false;

static char board[3][3];

static char& cell(int i) { return board[i / 3][i % 3]; }

static void save(const std::string& cells) {
    std::ofstream f("./output/__internals__.json");
    f << R"({"storage":{"server":{},"user":{"myvar2":")" << cells << R"("},"channel":{}}})";
}

static std::string encode() {
    std::string s;
    for (int i = 0; i < 9; ++i) s += (cell(i) == ' ' ? 'E' : cell(i));
    return s;
}

static bool decode(const std::string& s) {
    if (s.size() != 9) return false;
    for (char c : s)
        if (c != 'E' && c != 'X' && c != 'O') return false;
    for (int i = 0; i < 9; ++i) cell(i) = (s[i] == 'E' ? ' ' : s[i]);
    return true;
}

static void printBoard() {
    const char* nums[] = {"", "1️⃣", "2️⃣", "3️⃣"};

    printf("\n```\n   %s  %s  %s\n", nums[1], nums[2], nums[3]);
    for (int i = 0; i < 3; ++i) {
        printf("%s %c | %c | %c\n", nums[i + 1], board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("  ---+---+---\n");
    }
    printf("```");
}
static const int LINES[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                                {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

static bool wins(char p) {
    for (const auto& l : LINES)
        if (cell(l[0]) == p && cell(l[1]) == p && cell(l[2]) == p) return true;
    return false;
}

static bool full() {
    for (int i = 0; i < 9; ++i)
        if (cell(i) == ' ') return false;
    return true;
}

static int completingCell(char p) {
    for (int i = 0; i < 9; ++i) {
        if (cell(i) != ' ') continue;
        cell(i) = p;
        bool w = wins(p);
        cell(i) = ' ';
        if (w) return i;
    }
    return -1;
}

static int minimax(char turn, int depth) {
    if (wins('O')) return 10 - depth;
    if (wins('X')) return depth - 10;
    if (full()) return 0;
    int best = (turn == 'O') ? -100 : 100;
    for (int i = 0; i < 9; ++i) {
        if (cell(i) != ' ') continue;
        cell(i) = turn;
        int s = minimax(turn == 'O' ? 'X' : 'O', depth + 1);
        cell(i) = ' ';
        best = (turn == 'O') ? (s > best ? s : best) : (s < best ? s : best);
    }
    return best;
}

static int minimaxPick() {
    int bestCell = -1, bestScore = -100;
    for (int i = 0; i < 9; ++i) {
        if (cell(i) != ' ') continue;
        cell(i) = 'O';
        int s = minimax('X', 1);
        cell(i) = ' ';
        if (s > bestScore) { bestScore = s; bestCell = i; }
    }
    return bestCell;
}

static int heuristicPick() {
    int pick = completingCell('O');          // win
    if (pick < 0) pick = completingCell('X'); // block
    if (pick < 0 && cell(4) == ' ') pick = 4; // centre
    if (pick < 0) {                           // any free cell, picked uniformly
        std::vector<int> freeCells;
        for (int i = 0; i < 9; ++i)
            if (cell(i) == ' ') freeCells.push_back(i);
        if (!freeCells.empty()) pick = freeCells[rand() % freeCells.size()];
    }
    return pick;
}

static void botMove() {
    int pick = UNBEATABLE ? minimaxPick() : heuristicPick();
    if (pick >= 0) cell(pick) = 'O';
}

int main() {
    srand((unsigned)time(nullptr));

    if (kArgs == "clear") {
        printf("Board cleared!");
        save("EEEEEEEEE");
        return 1;
    }

    // exactly "row col", both 1..3, nothing after
    int row = 0, col = 0;
    char extra;
    int n = sscanf(kArgs.c_str(), "%d %d %c", &row, &col, &extra);
    if (n != 2 || row < 1 || row > 3 || col < 1 || col > 3) {
        printf("Invalid input format! Use 'row' 'column'");
        return 1;
    }
    --row; --col;

    if (!decode(kSaved)) memset(board, ' ', sizeof board);  // unset/corrupt => fresh game

    if (board[row][col] != ' ') {
        printf("That spot is already occupied by a %c!\n", board[row][col]);
        printBoard();
        return 2;
    }
    board[row][col] = 'X';

    if (wins('X')) {
        printBoard();
        printf("\nYOU WIN!");
        save("EEEEEEEEE");
        return 3;
    }

    botMove();
    printBoard();

    if (wins('O')) {
        printf("\nYOU LOSE!");
        save("EEEEEEEEE");
        return 3;
    }
    if (full()) {
        printf("\nIt's a tie!");
        save("EEEEEEEEE");
        return 3;
    }

    save(encode());
    return 0;
}
