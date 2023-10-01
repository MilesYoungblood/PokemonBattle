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

class Trainer {
protected:
    enum directions { NORTH, EAST, SOUTH, WEST };

    const static int MAX_POKEMON = 6;       // max number of Pokémon per party
    const static int MAX_ITEMS = 50;        // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;    // number of types of items

    int numFainted;                         // number of fainted Pokémon
    int numPokemon;                         // current number of Pokémon in party
    int numItems[Trainer::NUM_ITEM_TYPES];

    int x;                                  // x-coordinate on map
    int y;                                  // y-coordinate on map
    int range;                              // line of sight
    int direction;                          // numerical representation of which way the trainer is facing
    char model;                             // visual representation of which way the trainer is facing

    Pokemon* party[Trainer::MAX_POKEMON];
    Item* items[Trainer::NUM_ITEM_TYPES][Trainer::MAX_ITEMS];

public:
    Trainer();
    Trainer(const std::array<Pokemon*, Trainer::MAX_POKEMON> &pokemon, int x, int y);
    Trainer(const Trainer &toCopy);
    ~Trainer();
    Trainer& operator=(const Trainer &rhs);

    int partySize() const;
    int getNumItems(int type);
    int getNumRestoreItems() {
        return this->numItems[0];
    }
    Item& getItem(int type, int item);

    void setItems(const std::array<std::array<Item*, Trainer::MAX_ITEMS>, Trainer::NUM_ITEM_TYPES> &inventory);

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

    void setCoordinates(int newX, int newY);
    int getX() const;
    int getY() const;

    char getModel() const;

    bool canFight() const;

    bool isFacingNorth() const;
    bool isFacingEast() const;
    bool isFacingSouth() const;
    bool isFacingWest() const;

    bool hasVisionOf(const Trainer * t) const;
    void face(const Trainer * trainer);

    bool isNextTo(const Trainer * t) const;
};