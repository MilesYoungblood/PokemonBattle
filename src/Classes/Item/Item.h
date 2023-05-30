//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

class Item {
private:
    int quantity;
    std::string name;

public:
    Item();
    Item(const Item &copy);
    Item(int quantity, const std::string &name);
    virtual ~Item() = default;

    void setQuantity(int newQuantity);
    int getQuantity() const;

    std::string getName() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};