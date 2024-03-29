//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NetBall.h"

NetBall::NetBall(int n) : PokeBall(n) {}

NetBall::NetBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string NetBall::getName() const {
    return "Net Ball";
}

std::string NetBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on Water- and Bug-type Pokemon.";
}

double NetBall::getCatchRate(const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    if (pokemon.getType1() == Type::WATER or pokemon.getType1() == Type::BUG or
        pokemon.getType2() == Type::WATER or pokemon.getType2() == Type::BUG) {
        return 3.5;
    }
    return 1.0;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Net Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<NetBall>(n); };
    });
}
