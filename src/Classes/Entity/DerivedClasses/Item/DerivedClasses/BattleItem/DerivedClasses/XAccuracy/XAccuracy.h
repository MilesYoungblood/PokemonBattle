//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../BattleItem.h"

struct XAccuracy : public BattleItem {
    explicit XAccuracy(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] Pokemon::Stat getStat() const override;
};
