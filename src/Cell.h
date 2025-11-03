#ifndef FSP_MAZE_CELL_H
#define FSP_MAZE_CELL_H

#include <iostream>
#include <fstream>

enum class CellType {
    Empty, Wall, Coin, Monster, Trap, Start, Exit
};
enum class Direction {
    Up, Down, Left, Right
};


class Cell {
protected:
    CellType cell_type;
    //временно
    char image;
public:
    Cell();
    CellType getCellType();
    char getImage();
};

class Wall : public Cell {
private:
    Direction direction;
public:
    Wall();
    //Wall(Direction dir); скорее всего не понадобится
};

class Coin : public Cell {
public:
    Coin();
};

class Monster : public Cell {
private:
    int x, y;
public:
    Monster();
    Monster(int y, int x);
};

class Trap : public Cell {
public:
    Trap();
};
class Start: public Cell{
public:
    Start();
};
class Exit: public Cell{
public:
    Exit();
};

#endif //FSP_MAZE_CELL_H
