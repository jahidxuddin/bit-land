//
// Created by jahid on 19.05.2024.
//
#include "../include/Player.h"

Player::Player(): position(0, 0), Entity("1") {}

Math::Vector::Vector2D Player::getPosition() const {
    return position;
}

void Player::setPosition(Math::Vector::Vector2D newPosition) {
    position = newPosition;
}

void Player::movePlayer(Player::Direction direction) {
    switch (direction) {
        case UP:
            position.y -= 1;
            break;
        case DOWN:
            position.y += 1;
            break;
        case LEFT:
            position.x -= 1;
            break;
        case RIGHT:
            position.x += 1;
            break;
    }
}
