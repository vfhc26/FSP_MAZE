#include <fstream>
#include <iostream>

#include "Field.h"
int main() {
    std::ifstream mapFile("src/maps/map-1.txt");
    int width, height;
    mapFile >> width >> height;
    Field gameField(width, height);
    bool readed = gameField.inputMapFromFile(mapFile, gameField.getPlayer());
    mapFile.close();
    if (readed) {
        gameField.draw();
    } else {
        std::cout << "Error reading map file!" << std::endl;
    }

    return 0;
}