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

enum directions {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

class Trainer {
protected:
    const static int MAX_POKEMON = 6;   // max number of Pokémon per party
    const static int MAX_ITEMS = 100;   // max number of items per bag
    const static int MAX_ITEM_TYPES = 4;

    int numFainted;                     // number of fainted Pokémon
    int numPokemon;                     // current number of Pokémon in party

    int x;                              // x-coordinate on map
    int y;                              // y-coordinate on map
    int range;                          // line of sight
    int direction;                      // numerical representation of which way the trainer is facing
    char model;                         // visual representation of which way the trainer is facing

    Pokemon party[Trainer::MAX_POKEMON];
    //Item items[Trainer::MAX_ITEMS];
    Item* items[Trainer::MAX_ITEM_TYPES][Trainer::MAX_ITEMS];

public:
    Trainer();
    Trainer(const Trainer &toCopy);
    Trainer(const std::initializer_list<Pokemon> &pokemon, int x, int y);
    ~Trainer();

    int partySize() const;
    Item& getItem(int type, int item);

    void setItems(const std::vector<std::vector<Item*>> &v);

    void incFaintCount();
    void decFaintCount();

    virtual void defeat();

    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    Pokemon& operator[](int spot);
    const Pokemon& operator[](int spot) const;

    int getX() const;
    int getY() const;

    char getModel() const;

    bool canFight() const;

    bool isFacingNorth() const;
    bool isFacingEast() const;
    bool isFacingSouth() const;
    bool isFacingWest() const;

    bool hasVisionOf(const Trainer * t) const;
    void face(const Trainer * t);

    bool isNextTo(const Trainer * t) const;
};