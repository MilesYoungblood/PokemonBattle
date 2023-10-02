//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../Item/Item.h"
#include "../Item/RestoreItem.h"
#include "../Item/StatusItem.h"
#include "../Item/Pokeball.h"
#include "../Item/BattleItem.h"

class Trainer : public Entity {
protected:
    const static int MAX_POKEMON = 6;       // max number of Pokémon per party
    const static int MAX_ITEMS = 50;        // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;    // number of types of items

    int numFainted;                         // number of fainted Pokémon
    int numPokemon;                         // current number of Pokémon in party
    int numItems[Trainer::NUM_ITEM_TYPES];  // number of each type of item

    Pokemon* party[Trainer::MAX_POKEMON];
    Item* items[Trainer::NUM_ITEM_TYPES][Trainer::MAX_ITEMS];

public:
    Trainer(const std::vector<Pokemon*> &pokemon, int x, int y);
    Trainer(const Trainer &toCopy);
    ~Trainer();
    Trainer& operator=(const Trainer &rhs);

    int partySize() const;
    int getNumItems(int type);
    Item& getItem(int type, int item);

    __attribute__((unused)) void setItems(const std::vector<std::vector<Item*>> &inventory);
    void setRestoreItems(const std::vector<Item*> &inventory);
    void setStatusItems(const std::vector<Item*> &inventory);
    void setPokeBalls(const std::vector<Item*> &inventory);
    void setBattleItems(const std::vector<Item*> &inventory);

    void incFaintCount();
    __attribute__((unused)) void decFaintCount();

    void swapPokemon(int first, int second);

    virtual void defeat();

    Pokemon& operator[](int spot);
    const Pokemon& operator[](int spot) const;

    virtual bool canFight() const;
};