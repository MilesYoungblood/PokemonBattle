//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "Intimidate.h"

void Intimidate::action(Pokemon & /*attacker*/, Pokemon &defender) {
    defender.lowerStatMod(Pokemon::Stat::ATTACK, 1);
}

std::vector<std::string> Intimidate::actionMessage(const Pokemon & /*attacker*/, const Pokemon &defender) const {
    return std::vector<std::string>({ defender.getName() + "'s attack was lowered!" });
}

int Intimidate::getFlag() const {
    return -1;
}

Ability::Id Intimidate::getId() const {
    return Ability::Id::INTIMIDATE;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(abilityMutex);
        abilityMap.insert(std::make_pair(Ability::Id::INTIMIDATE,
                                         [] -> std::unique_ptr<Ability> { return std::make_unique<Intimidate>(); }));
    });
}
