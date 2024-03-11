//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct RestoreItem : public Item {
    explicit RestoreItem(int quantity);

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] virtual int getAmount() const = 0;

    [[nodiscard]] virtual bool isHp() const = 0;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    virtual void restore(Move &move) const;

    [[nodiscard]] std::string restoreMessage(const Pokemon &pokemon) const;

    [[nodiscard]] std::string restoreMessage(const Move &move) const;
};

inline std::mutex restoreItemMutex;
inline std::unordered_map<std::string, std::unique_ptr<RestoreItem>(*)(int)> restoreItems;