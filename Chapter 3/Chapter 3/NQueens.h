#ifndef NQUEENS_H
#define NQUEENS_H
#include <vector>

/*
Class: NQueens
Purpose: Interactive board where the user places/removes queens on an n×n board.
         The game ends when the user either backs out or successfully places n
         non-attacking queens.

PreCondition:
- play(): input helpers (inputInteger, inputChar) available; n in [4..12].

PostCondition:
- Displays the board each turn; validates moves; announces victory when n
  queens have been placed without conflicts; returns to caller on Back.
*/
class NQueens {
public:
    // Pre:  true
    // Post: runs the interactive session; returns to caller when user exits
    void play();

private:
    int n_{ 0 };                     // board size
    std::vector<int> col_;           // col_[r] = c (0..n-1) or -1 if empty row

    // Pre:  n in [4..12]
    // Post: n_ set; col_ = vector<int>(n,-1)
    void init(int n);

    // Pre:  0<=r,c<n
    // Post: true if placing a queen at (r,c) conflicts with existing queens
    bool conflict(int r, int c) const;

    // Pre:  0<=r<n and col_[r]==-1 and !conflict(r,c)
    // Post: places queen at (r,c), returns true; otherwise returns false
    bool placeQueen(int r, int c);

    // Pre:  0<=r<n and col_[r]!=-1
    // Post: removes queen from row r (if any); returns true if removed
    bool removeQueen(int r);

    // Pre:  true
    // Post: prints board with Q/. and row/col headers
    void printBoard() const;

    // Pre:  true
    // Post: number of queens currently on the board
    int  countQueens() const;

    // Pre:  true
    // Post: removes all queens
    void clearBoard();
};
#endif
