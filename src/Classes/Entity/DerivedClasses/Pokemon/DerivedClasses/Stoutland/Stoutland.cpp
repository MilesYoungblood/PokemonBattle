//
// Created by Miles on 12/2/2023.
//

#include "Stoutland.h"

Stoutland::Stoutland() : Pokemon(0.5, 32, 85, 110, 90, 45, 90, 80) {}

std::string Stoutland::getName() const {
    return "Stoutland";
}

std::string Stoutland::getSpecies() const {
    return "Big-Hearted";
}

Type Stoutland::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

double Stoutland::getHeight() const {
    return 1.2;
}

double Stoutland::getWeight() const {
    return 61.0;
}

int Stoutland::getCatchRate() const {
    return 45;
}

Pokemon::Id Stoutland::getId() const {
    return Pokemon::Id::STOUTLAND;
}
