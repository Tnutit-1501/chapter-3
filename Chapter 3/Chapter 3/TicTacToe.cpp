// Minh Tran & Team
// 09-13-2025
// Chapter 3 – Games: Tic-Tac-Toe (CMPR style)

#include "TicTacToe.h"
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int  inputInteger(string prompt, int startRange, int endRange);
char inputChar(string prompt, string options);

static void cls() { system("cls"); }
static void pauseScreen() { cout << "Press any key to continue . . ." << endl; system("pause>nul"); }

TicTacToe::TicTacToe() { reset(); }

void TicTacToe::reset() {
    for (int i = 0;i < 9;++i) board_[i] = char('1' + i);
    moves_ = 0;
}
void TicTacToe::place(int idx, char mark) { board_[idx] = mark; ++moves_; }
bool TicTacToe::freeCell(int idx) const { return idx >= 0 && idx < 9 && isdigit(board_[idx]); }

char TicTacToe::status() const {
    static const int W[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
    for (auto& l : W) if (board_[l[0]] == board_[l[1]] && board_[l[1]] == board_[l[2]]) return board_[l[0]];
    return (moves_ == 9) ? 'D' : 0;
}
int TicTacToe::findWinningMove(char me) const {
    static const int W[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
    for (auto& l : W) {
        int a = l[0], b = l[1], c = l[2];
        if (board_[a] == me && board_[b] == me && isdigit(board_[c])) return c;
        if (board_[a] == me && board_[c] == me && isdigit(board_[b])) return b;
        if (board_[b] == me && board_[c] == me && isdigit(board_[a])) return a;
    }
    return -1;
}
int TicTacToe::aiDumb() const { for (int i = 0;i < 9;++i) if (freeCell(i)) return i; return -1; }
int TicTacToe::aiUnbeatable(char me) const {
    char opp = (me == 'X' ? 'O' : 'X');
    int m;
    if ((m = findWinningMove(me)) != -1)  return m;     // 1) win
    if ((m = findWinningMove(opp)) != -1) return m;     // 2) block
    if (freeCell(4)) return 4;                      // 3) center
    const int corners[4] = { 0,2,6,8 }, oppCorner[4] = { 8,6,2,0 };
    for (int i = 0;i < 4;++i) if (board_[corners[i]] == opp && freeCell(oppCorner[i])) return oppCorner[i];
    for (int i = 0;i < 4;++i) if (freeCell(corners[i])) return corners[i];
    const int sides[4] = { 1,3,5,7 }; for (int i = 0;i < 4;++i) if (freeCell(sides[i])) return sides[i];
    return -1;
}
int TicTacToe::readMoveHuman(char mark) {
    for (;;) {
        int cell = inputInteger(string(" Player ") + mark + " pick (1-9): ", 1, 9) - 1;
        if (freeCell(cell)) return cell;
        cout << "  That cell is taken. Try again.\n";
    }
}
void TicTacToe::draw() const {
    cout << "     " << board_[0] << " | " << board_[1] << " | " << board_[2] << "\n"
        << "    ---+---+---\n"
        << "     " << board_[3] << " | " << board_[4] << " | " << board_[5] << "\n"
        << "    ---+---+---\n"
        << "     " << board_[6] << " | " << board_[7] << " | " << board_[8] << "\n\n";
}
void TicTacToe::play() {
    for (;;) {
        cls();
        cout << "\n\t[Tic-Tac-Toe]";
        cout << "\n\t" << string(60, char(205));
        cout << "\n\t 1. Human vs Human";
        cout << "\n\t 2. Human vs Dumb AI";
        cout << "\n\t 3. Human vs Unbeatable AI";
        cout << "\n\t" << string(60, char(196));
        cout << "\n\t 0. Back";
        cout << "\n\t" << string(60, char(205)) << "\n";

        int opt = inputInteger("\t Option: ", 0, 3);
        if (opt == 0) return;

        reset();
        char turn = 'X', humanMark = 'X';
        if (opt >= 2) humanMark = inputChar("\t Play as (X/O): ", "XO");

        while (true) {
            cls();
            cout << "\n\tTic-Tac-Toe\n\n";
            draw();

            int move = -1;
            bool humanTurn = (opt == 1) ? true : (turn == humanMark);
            if (humanTurn) move = readMoveHuman(turn);
            else           move = (opt == 2) ? aiDumb() : aiUnbeatable(turn);

            place(move, turn);
            char s = status();
            if (s) {
                cls(); draw();
                if (s == 'D') cout << " Draw.\n";
                else         cout << " Player " << s << " wins!\n";
                pauseScreen();
                break;
            }
            turn = (turn == 'X') ? 'O' : 'X';
        }
    }
}
