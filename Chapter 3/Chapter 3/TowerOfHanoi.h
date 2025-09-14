#ifndef TOWEROFHANOI_H
#define TOWEROFHANOI_H

/*
Class: TowerOfHanoi
Purpose: Interactive play (no auto-solver). User moves disks between A, B, C.

PreCondition:
- For play(): n in [1..12] read via input helpers.

PostCondition:
- Shows pegs each turn; validates moves; ends when all disks on C or user exits.
*/
class TowerOfHanoi {
public:
    // Pre:  true
    // Post: interactive session; returns to caller when done
    void play();
};
#endif
