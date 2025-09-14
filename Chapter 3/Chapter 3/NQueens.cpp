// Minh Tran & Team
// 09-13-2025
// Chapter 3 – Games: n-Queens (interactive play, no auto-solver)

#include "NQueens.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int  inputInteger(string prompt, int startRange, int endRange);
char inputChar(string prompt, string options);

static void cls() { system("cls"); }
static void pauseScreen() { cout << "Press any key to continue . . ." << "\n"; system("pause>nul"); }

void NQueens::init(int n) {
    n_ = n;
    col_.assign(n_, -1);
}
int NQueens::countQueens() const {
    int k = 0;
    for (int r = 0; r < n_; ++r) if (col_[r] != -1) ++k;
    return k;
}
void NQueens::clearBoard() { for (int r = 0; r < n_; ++r) col_[r] = -1; }

bool NQueens::conflict(int r, int c) const {
    for (int rr = 0; rr < n_; ++rr) {
        int cc = col_[rr];
        if (cc == -1) continue;
        if (rr == r) return true;                 // same row occupied
        if (cc == c) return true;                 // same column
        if (abs(rr - r) == abs(cc - c)) return true; // same diagonal
    }
    return false;
}
bool NQueens::placeQueen(int r, int c) {
    if (r < 0 || r >= n_ || c < 0 || c >= n_) return false;
    if (col_[r] != -1) return false;     // row already has a queen
    if (conflict(r, c)) return false;
    col_[r] = c;
    return true;
}
bool NQueens::removeQueen(int r) {
    if (r < 0 || r >= n_) return false;
    if (col_[r] == -1)    return false;
    col_[r] = -1;
    return true;
}
void NQueens::printBoard() const {
    // dynamic widths so 10, 11, 12... align nicely
    int digits = (int)to_string(n_).size();     // e.g., n_=13 -> 2
    int cellW = max(2, digits + 1);            // width for each cell/column header
    int rowW = digits;                        // width for row labels on the left

    // Column headers
    cout << "\n\t" << string(rowW + 1, ' ');    // left margin under row numbers + '|'
    for (int c = 1; c <= n_; ++c)
        cout << setw(cellW) << c;

    // Top rule line
    cout << "\n\t " << string(rowW + cellW * n_, char(205)) << "\n";

    // Board body
    for (int r = 0; r < n_; ++r) {
        cout << "\t" << setw(rowW) << (r + 1) << '|';
        for (int c = 0; c < n_; ++c) {
            const char* cell = (col_[r] == c) ? "Q" : ".";
            cout << setw(cellW) << cell;       // use the same width everywhere
        }
        cout << '\n';
    }
}

void NQueens::play() {
    cls();
    cout << "\n\t[n-Queens] Interactive Play\n";
    int n = inputInteger("\t Board size n (4-n): ", 4, 999999);
    init(n);

    for (;;) {
        cls();
        cout << "\n\t[n-Queens] Place all " << n_ << " queens without conflicts.";
        cout << "\n\t" << string(70, char(205));
        printBoard();
        cout << "\n\tQueens placed: " << countQueens() << " / " << n_;
        cout << "\n\t" << string(70, char(196));
        cout << "\n\t A) Add queen    R) Remove queen    C) Clear    X) Back";
        cout << "\n\t" << string(70, char(205)) << "\n";

        char op = inputChar("\t Option: ", "ARCX");
        if (op == 'X') return;

        try {
            if (op == 'A') {
                int r = inputInteger("\t  Row (1..n): ", 1, n_) - 1;
                int c = inputInteger("\t  Col (1..n): ", 1, n_) - 1;
                if (placeQueen(r, c)) {
                    if (countQueens() == n_) {
                        cls(); printBoard();
                        cout << "\n\tCongratulations! You placed all " << n_ << " queens.\n";
                        pauseScreen();
                        return;
                    }
                }
                else {
                    cout << "\n\tIllegal placement (row taken, same col/diagonal conflict, or out of range).\n";
                    system("pause");
                }
            }
            else if (op == 'R') {
                int r = inputInteger("\t  Row to remove (1..n): ", 1, n_) - 1;
                if (!removeQueen(r)) {
                    cout << "\n\tNo queen on that row.\n";
                    system("pause");
                }
            }
            else if (op == 'C') {
                clearBoard();
            }
        }
        catch (const exception& e) {
            cout << "\n\tException: " << e.what() << "\n";
            system("pause");
        }
    }
}
