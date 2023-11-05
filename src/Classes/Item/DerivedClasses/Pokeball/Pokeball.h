//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct PokeBall : public Item {
    explicit PokeBall(int n);

    [[nodiscard]] virtual double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const;

    [[nodiscard]] ItemType getType() const override;

    [[nodiscard]] ItemID getID() const override;

    [[nodiscard]] std::string getName() const override;

    void useMessage() override;

    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const;
};