//
// Created by Miles Youngblood on 6/7/2022.
//

#ifndef POKEMON_BATTLE_MOVE_LIST_H
#define POKEMON_BATTLE_MOVE_LIST_H

#include "Moves.h"
#include <random>
#include <iostream>
#include <unistd.h>

struct WaterShuriken : public Moves {
    WaterShuriken() : Moves("Water Shuriken", "water", "special", 20, 15, 100) {}
    int numHits = 0, trueHits = 0, trueDamage = 0;

    int getDamage() override {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(2, 5);
        std::uniform_int_distribution<int> hit(1, 100);

        numHits = dist(mt);
        std::cout << numHits << std::endl;

        for (int i = 0; i < numHits; ++i) { // determines hits and misses
            if (hit(mt) <= accuracy) {
                ++trueHits;
            }
        }

        return power * trueHits;
    }

    __attribute__((unused)) void attackMessage(Pokemon& attackingPokemon, Pokemon& defendingPokemon) {
        std::cout << attackingPokemon.getName() << " used " << name << "! ";
        sleep(1);

        std::cout << "It hit " << trueHits << " times!" << std::endl;
        sleep(1);

        std::cout << name << " did " << trueDamage << " damage!" << std::endl;
        sleep(2);
    }
};

struct DarkPulse : public Moves {
    DarkPulse() : Moves("Dark Pulse", "dark", "special", 15, 80, 100) {}
};

struct IceBeam : public Moves {
    IceBeam() : Moves("Ice Beam", "ice", "special", 10, 90, 100) {}
};

struct Extrasensory : public Moves {
    Extrasensory() : Moves("Extrasensory", "psychic", "special", 15, 90, 100) {}
};

#endif //POKEMON_BATTLE_MOVE_LIST_H
