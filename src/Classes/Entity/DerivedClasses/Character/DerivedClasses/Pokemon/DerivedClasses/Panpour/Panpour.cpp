//
// Created by Miles on 12/16/2023.
//

#include "Panpour.h"

Panpour::Panpour() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 50, 53, 48, 53, 48, 64) {}

std::string Panpour::getName() const {
    return "Panpour";
}

std::string Panpour::getSpecies() const {
    return "Spray";
}

Type Panpour::getType1() const {
    return Type::WATER;
}

double Panpour::getHeight() const {
    return 0.6;
}

double Panpour::getWeight() const {
    return 13.5;
}

int Panpour::getCatchRate() const {
    return 190;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Panpour"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Panpour>(); };
    });
}
