cmake_minimum_required(VERSION 3.28)
project(bit_land)

set(CMAKE_CXX_STANDARD 20)

add_executable(bit_land src/main.cpp
        src/Tile.cpp
        include/Tile.h
        include/Math.h
        src/Entity.cpp
        include/Entity.h
        src/Player.cpp
        include/Player.h
        include/GameState.h
)
