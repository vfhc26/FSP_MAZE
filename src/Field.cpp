//
// Created by Keller3D on 01.11.2025.
//

#include "Field.h"

Field::Field() {
    width = 0;
    height = 0;
    field = nullptr;
}

Field::Field(int w, int h) {
    width = w;
    height = h;
    field = new Cell *[h];
    for (int i = 0; i < h; ++i) {
        field[i] = new Cell[w];
    }
}

bool Field::setCell(int x, int y, Cell c) {
    if (x > width || y > height || x < 0 || y < 0) {
        return false;
    }
    field[y][x] = c;
    return true;
}

bool Field::draw() {
    if (width < 0 || height < 0) {
        return false;
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (field[y][x].getCellType() == CellType::Empty){
                std::cout << " ";
            }else{
                std::cout << "x";
            }
        }
        std::cout << std::endl;

    }
    return true;
}