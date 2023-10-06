//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Data/Pokedex.h"

namespace PokemonFactory {
    Pokemon *getPokemon(PokemonID id) {
        switch (id) {
            case CHARIZARD:
                return new Charizard();
            case PIKACHU:
                return new Pikachu();
            case LUCARIO:
                return new Lucario();
            case HYDREIGON:
                return new Hydreigon();
            case GRENINJA:
                return new Greninja();
            default:
                return nullptr;
        }
    }
}
