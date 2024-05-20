//
// Created by jahid on 19.05.2024.
//

#include <random>

#ifndef BIT_LAND_MATH_H
#define BIT_LAND_MATH_H
#pragma once

namespace Math::Vector {
    struct Vector2D {
        int x;
        int y;

        bool operator==(const Vector2D& other) const {
            return x == other.x && y == other.y;
        }
    };
}

namespace std {
    template <>
    struct hash<Math::Vector::Vector2D> {
        std::size_t operator()(const Math::Vector::Vector2D& vec) const noexcept {
            return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
        }
    };
}

#endif //BIT_LAND_MATH_H
