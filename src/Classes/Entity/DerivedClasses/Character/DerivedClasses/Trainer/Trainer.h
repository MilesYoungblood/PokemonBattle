//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../../../Item/DerivedClasses/Items.h"

class Trainer : public Character {
private:
    enum : Uint8 {
        MAX_POKEMON = 6,
        MAX_ITEMS = 50
    };

    bool keepLooping{ true };

    std::vector<std::unique_ptr<Pokemon>> party;
    std::unordered_map<std::size_t, std::vector<std::unique_ptr<Item>>> items;

    void init();

protected:
    Trainer(const char *id, int x, int y, Direction direction);

    [[nodiscard]] std::size_t partySize() const;

public:
    Trainer(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&toMove) noexcept = default;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) noexcept = delete;

    ~Trainer() override = default;

    void addPokemon(const char *id);

    void addPokemon(std::unique_ptr<Pokemon> toAdd);

    void removePokemon(long long int index);

    void swapPokemon(std::size_t a, std::size_t b);

    void clearParty();

    template<typename I>
    [[nodiscard]] std::size_t getNumItems() const {
        try {
            return this->items.at(typeid(I).hash_code()).size();
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    template<typename I>
    I &getItem(std::size_t index) {
        Item *ptr = this->items.at(typeid(I).hash_code())[index].get();
        return *dynamic_cast<I *>(ptr);
    }

    template<typename C, typename I>
    void addItem(std::unique_ptr<I> item) {
        try {
            if (this->items.at(typeid(C).hash_code()).size() == Trainer::MAX_ITEMS) {
                return;
            }

            for (std::size_t i = 0; i < this->items.at(typeid(C).hash_code()).size(); ++i) {
                // if item already exists within our inventory
                Item *ptr = this->items.at(typeid(C).hash_code()).at(i).get();
                const C *itm = dynamic_cast<C *>(ptr);

                if (item->getId() == itm->getId()) {
                    this->items.at(typeid(C).hash_code())[i]->add(item->getQuantity());
                    return;
                }
            }

            this->items.at(typeid(C).hash_code()).push_back(std::move(item));
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
        }
    }

    template<typename I>
    void removeItem(long long int index) {
        try {
            const std::size_t i = typeid(I).hash_code();
            this->items.at(i).erase(this->items.at(i).begin() + index);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    Pokemon &operator[](std::size_t index);

    std::vector<std::unique_ptr<Pokemon>>::iterator begin();

    std::vector<std::unique_ptr<Pokemon>>::iterator end();

    virtual void handleFaint();

    void idle() override;

    [[nodiscard]] bool canFight() const override;

    [[nodiscard]] virtual std::vector<std::string> winMessage() const;

    [[nodiscard]] bool isTrainer() const override;

    void interact() override;
};