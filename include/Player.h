//
// Created by jahid on 19.05.2024.
//

#ifndef BIT_LAND_PLAYER_H
#define BIT_LAND_PLAYER_H
#pragma once

#include "Entity.h"
#include "Math.h"

class Player : public Entity {
    Math::Vector::Vector2D position{};

    public:
        Player();
        [[nodiscard]] Math::Vector::Vector2D getPosition() const;
        void setPosition(Math::Vector::Vector2D newPosition);
        enum Direction { UP, DOWN, LEFT, RIGHT };
        void movePlayer(Direction direction);
};

#endif //BIT_LAND_PLAYER_H
