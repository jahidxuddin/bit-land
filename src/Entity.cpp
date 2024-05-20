//
// Created by jahid on 19.05.2024.
//

#include <utility>

#include "../include/Entity.h"

Entity::Entity() = default;

Entity::Entity(std::string appearance): appearance(std::move(appearance)) {}

std::string Entity::getAppearance() const {
    return appearance;
}

void Entity::setAppearance(std::string newAppearance) {
    appearance = newAppearance;
}