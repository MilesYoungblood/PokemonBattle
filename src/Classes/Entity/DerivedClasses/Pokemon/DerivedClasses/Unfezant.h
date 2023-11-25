//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Unfezant : public Pokemon {
    Unfezant() : Pokemon(32, 80, 115, 80, 65, 55, 93) {}

    Unfezant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Unfezant";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::UNFEZANT;
    }
};