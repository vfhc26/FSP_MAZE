#ifndef FSP_MAZE_CELL_H
#define FSP_MAZE_CELL_H

enum class CellType {
    Empty, Wall, Coin, Monster, Trap, Start, Exit
};
enum class Direction {
    Up, Down, Left, Right
};


class Cell {
protected:
    CellType cell_type;
public:
    Cell() {
        cell_type = CellType::Empty;
    }

    CellType getCellType() {
        return cell_type;
    }
};

class Wall : public Cell {
private:
    Direction direction;
public:
    Wall() { cell_type = CellType::Wall; }

    Wall(Direction dir) {
        cell_type = CellType::Wall;
        direction = dir;
    }
};

class Coin : public Cell {
public:
    Coin() { cell_type = CellType::Coin; }
};

class Monster : public Cell {
private:
    int x, y;
public:
    Monster() { cell_type = CellType::Monster; }
    Monster(int x, int y) {
        cell_type = CellType::Monster;
        this->x = x;
        this->y = y;
    }
};

class Trap : public Cell {
public:
    Trap() { cell_type = CellType::Trap; }
};
class Start: public Cell{
public:
    Start(){
        cell_type = CellType::Start;
    }
};
class Exit: public Cell{
    Exit(){
        cell_type = CellType::Exit;
    }
};
#endif //FSP_MAZE_CELL_H
