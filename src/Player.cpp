//
// Created by Keller3D on 01.11.2025.
//

#include "Player.h"

Player::Player() { x = y = coin_count = move_count = 0; }

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;
    move_count = coin_count = 0;
}

bool Player::Up() {
    // надо сделать проверки на стенки и прочие штуки
    move_count++;
    y++;
    return true;
}

bool Player::Down() {
    move_count++;
    y--;
    return true;
}

bool Player::Left() {
    move_count++;
    x--;
    return true;
}

bool Player::Right() {
    move_count++;
    x++;
    return true;
}
void Player::setStartPosition(int y, int x) {
    this->x = x;
    this->y = y;
}

CellType Player::checkCell() {
    // Заглушка: пока нет доступа к полю, возвращаем пустую клетку
    return CellType::Empty;
}

CellType Player::checkCell(Direction /*dir*/) {
    // Заглушка: пока нет доступа к полю, возвращаем пустую клетку
    return CellType::Empty;
}