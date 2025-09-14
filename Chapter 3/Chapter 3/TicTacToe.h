#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <utility>

/*
Class: TicTacToe
Purpose: Console Tic-Tac-Toe with Human vs Human, Dumb AI, and Unbeatable AI.

PreCondition:
- For play(): input helpers (inputInteger, inputChar) are available.

PostCondition:
- Runs a full game session and returns to caller when user backs out.
*/
class TicTacToe {
public:
    TicTacToe();

    // Pre:  true
    // Post: runs menu (H vs H, H vs Dumb, H vs Unbeatable); returns on Back
    void play();

private:
    char board_[9];
    int  moves_;

    // Pre:  none
    // Post: board contains '1'..'9', moves_=0
    void reset();

    // Pre:  0<=idx<=8 and cell free
    // Post: places 'mark' and ++moves_
    void place(int idx, char mark);

    // Pre:  none
    // Post: returns 'X' or 'O' if win, 'D' if draw, 0 otherwise
    char status() const;

    // Pre:  none
    // Post: true if idx is a free cell
    bool freeCell(int idx) const;

    // Pre:  mark in {'X','O'}
    // Post: returns chosen cell index [0..8]
    int readMoveHuman(char mark);

    // Pre:  true
    // Post: returns winning move for 'me' or -1
    int findWinningMove(char me) const;

    // Pre:  true
    // Post: first free cell (left->right) or -1
    int aiDumb() const;

    // Pre:  true
    // Post: unbeatable, rule-based move index or -1
    int aiUnbeatable(char me) const;

    // Pre:  none
    // Post: prints 3x3 board
    void draw() const;
};
#endif
