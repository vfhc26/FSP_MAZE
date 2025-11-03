//
// Created by Keller3D on 01.11.2025.
//

#include "Field.h"

#include <string>

Field::Field() {
    width = 0;
    height = 0;
    field = nullptr;
    player = Player();
}

Field::Field(int w, int h) {
    width = w;
    height = h;
    field = new Cell*[h];
    for (int i = 0; i < h; ++i) {
        field[i] = new Cell[w];
    }
    player = Player();
}
Field::~Field() { clear(); }
Player& Field::getPlayer() { return player; }
bool Field::inputMapFromFile(std::ifstream& mapFile, Player& player) {
    if (!mapFile.is_open()) {
        return false;
    }
    std::string line;
    int y = 0;
    while (y < height) {
        if (!std::getline(mapFile, line)) {
            return false;
        }
        // проверка на возможный перевод строки
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        // пропуск возможных пустых строк
        if (line.empty()) {
            continue;
        }
        if (static_cast<int>(line.size()) < width) {
            return false;
        }
        // инициализация ячеек
        for (int x = 0; x < width; ++x) {
            char c = line[static_cast<size_t>(x)];
            if (!this->initCellObjects(x, y, c, player)) {
                this->initCellObjects(x, y, ' ', player);
            }
        }
        ++y;
    }
    return true;
}
bool Field::setCell(int x, int y, Cell c) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    field[y][x] = c;
    return true;
}
bool Field::initCellObjects(int x, int y, char cellChar, Player& player) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    switch (cellChar) {
        case '#':
            field[y][x] = Wall();
            break;
        case 'C':
            field[y][x] = Coin();
            break;
        case 'M':
            field[y][x] = Monster(y, x);
            break;
        case 'T':
            field[y][x] = Trap();
            break;
        case 'S':
            field[y][x] = Start();
            player.setStartPosition(y, x);
            break;
        case 'E':
            field[y][x] = Exit();
            break;
        case ' ':
            field[y][x] = Cell();
            break;
        default:
            return false;
    }
    return true;
}
bool Field::draw() {
    if (width < 0 || height < 0) {
        return false;
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << field[y][x].getImage();
        }
        std::cout << std::endl;
    }
    return true;
}
void Field::clear() {
    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;
}