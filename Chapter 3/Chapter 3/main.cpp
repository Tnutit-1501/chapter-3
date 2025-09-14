// Minh Tran & Team
// 09-13-2025
// Chapter 3 – Games Applications using Container by Prof Q

#include <iostream>
#include <iomanip>
#include <string>
#include "input.h"      // CMPR helper (definitions live here)
#include "TicTacToe.h"
#include "TowerOfHanoi.h"
#include "NQueens.h"
using namespace std;

// ===== prototypes of project runners (menu actions) =====
void project_tictactoe();     // Pre: true. Post: runs TicTacToe.play()
void project_hanoi();         // Pre: n in [1..12]. Post: interactive session
void project_nqueens();       // Pre: n in [4..n]. Post: prints one solution
// ========================================================

int main() {
    cout << fixed << setprecision(4);
    do {
        system("cls");
        cout << "\n\tCMPR131 Chapter 3 - Games Applications using Container by Minh Tran";
        cout << "\n\t" << string(80, char(205)) << "\n";
        cout << "\t 1> Tic-Tac-Toe";
        cout << "\n\t 2> Tower of Hanoi";
        cout << "\n\t 3> n-Queens";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\t 0. Exit";
        cout << "\n\t" << string(80, char(205)) << "\n";

        try {
            switch (inputInteger("\t Option: ", 0, 3)) {
            case 0: exit(0);
            case 1: project_tictactoe(); break;
            case 2: project_hanoi();     break;
            case 3: project_nqueens();   break;
            }
        }
        catch (const exception& e) {
            cout << "\n\tException: " << e.what() << "\n";
        }
        system("pause");
    } while (true);
    return 0;
}

void project_tictactoe() {
    system("cls");
    cout << "\t[Tic-Tac-Toe]\n";
    TicTacToe g; g.play();
}
void project_hanoi() {
    system("cls");
    cout << "\t[Tower of Hanoi – Interactive]\n";
    TowerOfHanoi g; g.play();
}
void project_nqueens() {
    system("cls"); 
    cout << "\t[n-Queens – Iterative Solver]\n";
    NQueens g; g.play();
}
