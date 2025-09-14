// Minh Tran
// 09-13-2025
// Chapter 3 – Games: Tower of Hanoi 

#include "TowerOfHanoi.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

/*
Function: TowerOfHanoi::play
PreCondition:
- inputInteger() helper is available.
PostCondition:
- Interactive Tower of Hanoi game with styled ASCII display.
*/

int  inputInteger(string prompt, int startRange, int endRange); 

// Utility functions
static void cls() { system("cls"); }
static void pauseScreen() { cout << "Press any key to continue . . ." << endl; system("pause>nul"); }

// Convert stack<int> to vector<int> (bottom to top)
static vector<int> toVectorBottomTop(stack<int> s) {
    vector<int> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    reverse(v.begin(), v.end());
    return v;
}

static string centerText(const string& s, int width) {
    if ((int)s.size() >= width) return s;
    string out(width, ' ');
    int start = (width - (int)s.size()) / 2;
    for (int i = 0; i < (int)s.size(); ++i) out[start + i] = s[i];
    return out;
}

// For size ≤9 draw wide disk with '=' and number; for ≥10 draw just "[##]"
static string makeDisk(int size, int maxSize, bool bars) {
    int visualMax = min(maxSize, 9);
    int width = 2 * visualMax + 1;
    string line(width, ' ');
    if (size <= 0) return line;

    if (bars) {
        string body(2 * size + 1, '=');
        string num = to_string(size);
        int mid = (int)body.size() / 2;
        int start = mid - (int)num.size() / 2;
        for (int i = 0; i < (int)num.size() && start + i < (int)body.size(); ++i)
            body[start + i] = num[i];
        int pad = (width - (int)body.size()) / 2;
        for (int i = 0; i < (int)body.size(); ++i)
            line[pad + i] = body[i];
    }
    else {
        string label = to_string(size);
        int pad = (width - (int)label.size()) / 2;
        for (int i = 0; i < (int)label.size(); ++i)
            line[pad + i] = label[i];
    }
    return line;
}

static int diskAtLevel(const vector<int>& tower, int levelFromTop, int n) {
    int k = (int)tower.size();     // #disks on this peg (bottom->top)
    int firstDiskRow = n - k;      // visual row where the TOP disk starts
    if (levelFromTop < firstDiskRow) return 0;          // post only
    int idxFromTop = levelFromTop - firstDiskRow;       // 0..k-1
    return tower[k - 1 - idxFromTop];                   // top -> bottom
}

// Draw three towers A,B,C in nice ASCII
static void drawScene(const stack<int>& A, const stack<int>& B,
    const stack<int>& C, int n) {
    vector<int> va = toVectorBottomTop(A);
    vector<int> vb = toVectorBottomTop(B);
    vector<int> vc = toVectorBottomTop(C);

    int maxSize = n;                  // total disks
    int visualMax = min(maxSize, 9);   // keep width capped at 9
    int cellW = 2 * visualMax + 1; // width of each column
    int gapW = 6;
    string gap(gapW, ' ');
    bool bars = (maxSize <= 9);    // draw bars if <=9, else plain numbers

    auto postLine = [&](int w) {
        string s(w, ' ');
        s[w / 2] = '|';
        return s;
        };

    cout << "\n\tTower of Hanoi\n\n";
    for (int row = 0; row < n; ++row) {
        int da = diskAtLevel(va, row, n);
        int db = diskAtLevel(vb, row, n);
        int dc = diskAtLevel(vc, row, n);
        string ca = (da == 0 ? postLine(cellW) : makeDisk(da, maxSize, bars));
        string cb = (db == 0 ? postLine(cellW) : makeDisk(db, maxSize, bars));
        string cc = (dc == 0 ? postLine(cellW) : makeDisk(dc, maxSize, bars));
        cout << "\t  " << ca << gap << cb << gap << cc << "\n";
    }
    string base(cellW, char(205));
    cout << "\t  " << base << gap << base << gap << base << "\n";
    cout << "\t  " << centerText("A", cellW) << gap
        << centerText("B", cellW) << gap
        << centerText("C", cellW) << "\n\n";
}

void TowerOfHanoi::play() {
    cls();
    cout << "\n\t[Tower of Hanoi] Interactive\n";
    cout << "\t  Move all disks from A to C.\n";
    int n = inputInteger("\t Enter the number of rings (1..64): ", 1, 64);

    stack<int> A, B, C;
    for (int i = n;i >= 1;--i) A.push(i);

    auto peg = [&](char p)->stack<int>*{
        switch (toupper(p)) { case 'A': return &A; case 'B': return &B; case 'C': return &C; default: return nullptr; }
        };
    auto move = [&](char f, char t) {
        stack<int>* F = peg(f), * T = peg(t);
        if (!F || !T) { cout << "\n\t Invalid peg.\n"; return false; }
        if (F->empty()) { cout << "\n\t No disk on peg " << char(toupper(f)) << ".\n"; return false; }
        if (!T->empty() && T->top() < F->top()) { cout << "\n\t Cannot place bigger on smaller.\n"; return false; }
        T->push(F->top()); F->pop(); return true;
        };
    auto win = [&]() { return A.empty() && B.empty() && (int)C.size() == n; };

    for (;;) {
        cls();
        drawScene(A, B, C, n);
        if (win()) { cout << "\t  Nice! You solved it.\n\n"; pauseScreen(); break; }

        cout << "\t  Enter move like AB, AC, BA...  (X = Back)\n";
        cout << "\t  Move: ";
        string mv; cin >> mv;
        if (mv.size() == 1 && (mv[0] == 'x' || mv[0] == 'X')) break;
        if (mv.size() != 2) { cout << "\n\t Invalid input.\n"; system("pause"); continue; }
        if (!move(mv[0], mv[1])) { system("pause"); }
    }
}
