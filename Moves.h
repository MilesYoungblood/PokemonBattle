//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MOVES_H
#define POKEMON_BATTLE_MOVES_H

#include <string>
#include <random>

class Moves {
protected:
    int pp, maxPp, power, accuracy;
    std::string type, category, name;
public:
    Moves();
    Moves(const std::string& name, const std::string& type, const std::string& category, int pp, int power, int accuracy);
    Moves(const Moves& moveToCopy);
    virtual ~Moves() = default;

    virtual int getDamage();

    void setPP(int newPP);
    int getPP() const;

    int getMaxPP() const;

    int getPower() const;

    int getAccuracy() const;

    __attribute__((unused)) void setType(std::string& newType);
    __attribute__((unused)) std::string getType() const;

    std::string getCategory() const;

    std::string getName() const;
};

#endif //POKEMON_BATTLE_MOVES_H
