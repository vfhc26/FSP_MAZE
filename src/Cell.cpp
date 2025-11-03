#include "Cell.h"

Cell::Cell() {
    cell_type = CellType::Empty;
    image = ' ';
}
CellType Cell::getCellType() { return cell_type; }
char Cell::getImage() { return image; }

Wall::Wall() {
    cell_type = CellType::Wall;
    image = '#';
}
Coin::Coin() {
    cell_type = CellType::Coin;
    image = 'C';
}
Monster::Monster() {
    cell_type = CellType::Monster;
    image = 'M';
}
Monster::Monster(int y, int x) {
    cell_type = CellType::Monster;
    image = 'M';
    this->x = x;
    this->y = y;
}
Trap::Trap() {
    cell_type = CellType::Trap;
    image = 'T';
}

Start::Start() {
    cell_type = CellType::Start;
    image = 'S';
}
Exit::Exit() {
    cell_type = CellType::Exit;
    image = 'E';
}