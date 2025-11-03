//
// Created by Keller3D on 01.11.2025.
//

#ifndef FSP_MAZE_FIELD_H
#define FSP_MAZE_FIELD_H
#include "Cell.h"
#include "Player.h"
#include <iostream>
class Field {
private:
    int width;
    int height;
    Cell** field;
    Player player;
public:
    Field();
    Field(int w, int h);
    ~Field();
    Player& getPlayer();

    bool inputMapFromFile(std::ifstream& mapFile, Player& player);
    bool setCell(int x, int y, Cell c);
    bool initCellObjects(int x, int y, char cellChar, Player& player);
    bool draw();
    void clear();
};


#endif //FSP_MAZE_FIELD_H
