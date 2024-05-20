//
// Created by jahid on 19.05.2024.
//

#ifndef BIT_LAND_ENTITY_H
#define BIT_LAND_ENTITY_H
#pragma once

#include <string>

class Entity {
    std::string appearance;

    public:
        Entity();
        explicit Entity(std::string appearance);
        [[nodiscard]] std::string getAppearance() const;
        void setAppearance(std::string newAppearance);
};

#endif //BIT_LAND_ENTITY_H
