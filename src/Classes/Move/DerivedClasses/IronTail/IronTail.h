//
// Created by Miles Youngblood on 6/15/2023.
//

#pragma once

#include "../../Move.h"

class IronTail : public Move {
private:
    static const int MAX_PP{ 24 };
    bool loweredFlag{ false };

public:
    IronTail();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                         bool skip) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;

    [[nodiscard]] int getAccuracy() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};

namespace {
    inline AutoThread init([] -> void {
        moveMap.insert(std::make_pair(Move::Id::IRON_TAIL,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<IronTail>(); }));
    });
}