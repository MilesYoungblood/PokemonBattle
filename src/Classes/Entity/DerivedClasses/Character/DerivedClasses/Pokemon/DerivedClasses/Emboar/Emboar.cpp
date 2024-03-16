//
// Created by Miles on 12/2/2023.
//

#include "Emboar.h"

Emboar::Emboar() : Pokemon(Ability::Id::BLAZE, 87.5, 36, 110, 123, 65, 100, 65, 65) {}

std::string Emboar::getName() const {
    return "Emboar";
}

std::string Emboar::getSpecies() const {
    return "Mega Fire Pig";
}

Type Emboar::getType1() const {
    return Type::FIRE;
}

Type Emboar::getType2() const {
    return Type::FIGHTING;
}

double Emboar::getHeight() const {
    return 1.6;
}

double Emboar::getWeight() const {
    return 150.0;
}

int Emboar::getCatchRate() const {
    return 45;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Emboar"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Emboar>(); };
    });
}
