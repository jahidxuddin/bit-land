//
// Created by jahid on 19.05.2024.
//

#ifndef BIT_LAND_GAMESTATE_H
#define BIT_LAND_GAMESTATE_H
#pragma once

#include <unordered_map>
#include "Tile.h"
#include "Player.h"

class Player;

struct GameState {
    std::unordered_map<Math::Vector::Vector2D, Tile> world;
    int worldWidth;
    int worldHeight;
    Player player{};
    int score;
    bool isRunning = false;
};

#endif //BIT_LAND_GAMESTATE_H
