//
// Created by Keller3D on 01.11.2025.
//

#ifndef FSP_MAZE_PLAYER_H
#define FSP_MAZE_PLAYER_H
#include "Cell.h"

class Player{
private:
    int x, y;
    int coin_count;
    int move_count;
public:
    Player();
    Player(int x, int y);
    bool Up();
    bool Down();
    bool Left();
    bool Right();
    void setStartPosition(int y, int x);
    CellType checkCell();
    CellType checkCell(Direction);
};


#endif //FSP_MAZE_PLAYER_H
