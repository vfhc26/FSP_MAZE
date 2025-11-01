//
// Created by Keller3D on 01.11.2025.
//

#ifndef FSP_MAZE_FIELD_H
#define FSP_MAZE_FIELD_H
#include "Cell.h"
#include <iostream>
class Field {
private:
    int width;
    int height;
    Cell** field;
public:
    Field();
    Field(int w, int h);
    bool setCell(int x, int y, Cell c);
    bool draw();
};


#endif //FSP_MAZE_FIELD_H
