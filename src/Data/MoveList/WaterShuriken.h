//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class Pokemon;

static int numHits = 0;     // number of hits landed (from 2 to 5)

struct WaterShuriken : public Move {
    WaterShuriken() : Move("Water Shuriken", 20, 15, 100, Type::WATER, Category::SPECIAL) {}

    MoveID getID() override {
        return MoveID::WATER_SHURIKEN;
    }

    [[nodiscard]] int getDamage() const override {
        for (int i = 0; i < generateInteger(2, 5); ++i) { // determines hits and misses
            if (generateInteger(1, 100) <= this->accuracy) {
                ++numHits;
            }
        }

        return this->power * numHits;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool skipTurn, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Water Shuriken! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Water Shuriken did " + std::to_string(damage) + " damage! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (typeEff >= 2.0) {
                printMessage("It's super effective! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (typeEff <= 0.5) {
                printMessage("It's not very effective... ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            printMessage("It hit " + std::to_string(numHits) + " times! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (criticalHit) {
                printMessage('x' + std::to_string(numHits) + " critical hits!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            //printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        numHits = 0;
    }
};
