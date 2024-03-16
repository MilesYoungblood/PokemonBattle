//
// Created by Miles on 12/2/2023.
//

#include "Pignite.h"

Pignite::Pignite() : Pokemon(Ability::Id::BLAZE, 87.5, 17, 90, 93, 55, 70, 55, 55) {}

std::string Pignite::getName() const {
    return "Pignite";
}

std::string Pignite::getSpecies() const {
    return "Fire Pig";
}

Type Pignite::getType1() const {
    return Type::FIRE;
}

Type Pignite::getType2() const {
    return Type::FIGHTING;
}

double Pignite::getHeight() const {
    return 1.0;
}

double Pignite::getWeight() const {
    return 55.5;
}

int Pignite::getCatchRate() const {
    return 45;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Pignite"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Pignite>(); };
    });
}
