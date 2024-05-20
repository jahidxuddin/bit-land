//
// Created by jahid on 18.05.2024.
//

#include <utility>

#include "../include/Tile.h"

Tile::Tile(Entity &entity): entity(std::move(entity)) {}

Entity Tile::getEntity() const {
    return entity;
}
