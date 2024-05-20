//
// Created by jahid on 18.05.2024.
//

#ifndef BIT_LAND_TILE_H
#define BIT_LAND_TILE_H
#pragma once

#include "Entity.h"

class Tile {
    Entity entity;

    public:
        explicit Tile(Entity &entity);
        [[nodiscard]] Entity getEntity() const;
};

#endif //BIT_LAND_TILE_H
