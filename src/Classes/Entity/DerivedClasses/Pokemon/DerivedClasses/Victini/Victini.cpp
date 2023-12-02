//
// Created by Miles Youngblood on 12/2/2023.
//

#include "Victini.h"

Victini::Victini() : Pokemon(Pokemon::Id::VICTINI, 15, 100, 100, 100, 100, 100, 100) {}

std::string Victini::getName() const {
    return "Victini";
}

std::string Victini::getSpecies() const {
    return "Victory";
}

Type Victini::getType(bool type1) const {
    return type1 ? Type::PSYCHIC : Type::FIRE;
}

double Victini::getHeight() const {
    return 0.4;
}

double Victini::getWeight() const {
    return 4.0;
}

int Victini::getCatchRate() const {
    return 3;
}