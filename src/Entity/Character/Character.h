//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Component/Intelligence/Intelligence.h"
#include "../../Entity/Entity.h"

class Character : public Entity {
public:
    enum class State : Uint8 {
        IDLE,
        WALKING,
        COLLIDING,
        IMMOBILE
    };

    enum : Uint8 {
        WALK_SPEED = Map::TILE_SIZE / 20,
        RUN_SPEED [[maybe_unused]] = Map::TILE_SIZE / 10
    };

    Character(const char *id, int x, int y, Direction direction, int vision);

    Character(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Character(const Character &) = delete;

    Character(Character &&toMove) noexcept = delete;

    Character &operator=(const Character &) = delete;

    Character &operator=(Character &&) noexcept = delete;

    ~Character() override = default;

    /// \brief Setter for name
    /// \param x the new name
    void setName(const char *x);

    /// \brief Getter for name
    /// \return the character's name
    [[nodiscard]] std::string getName() const;

    /// \brief Setter for dialogue
    /// \param text the new text
    void setDialogue(const std::vector<std::string> &text);

    /// \brief Setter for state
    /// \param x the new state
    void setState(State x);

    /// \brief Getter for state
    /// \return the character's state
    [[nodiscard]] State getState() const;

    /// \brief Fires the character's decision making thread
    /// \param map the map
    void gainAutonomy(Map &map);

    /// \brief Overrides Entity::getKey
    /// \return the respective sprite key
    [[nodiscard]] std::string getSpriteKey() const override;

    /// Getter for the initial battle message
    /// \return the initial send out message in battle
    [[nodiscard]] virtual std::string initMessage() const;

    /// \brief Handles specific faint protocol
    virtual void handleFaint();

    /// \brief Handles specific switch out protocol
    /// \param renderFlag will be set back to true after the switch out is made
    virtual void handleSwitchOut(bool &renderFlag);

    /// \brief Handles specific victory protocol
    virtual void handleVictory();

    /// \brief Getter for specific defeat message
    /// \return the victory message
    [[nodiscard]] virtual std::vector<std::string> getDefeatMessage() const;

    /// \brief Getter for the attacking Pokemon in a battle
    /// \return the attacking Pokemon
    virtual Pokemon *getAttacker();

    /// \brief Getter for the attacking Pokemon in a battle
    /// \return the attacking Pokemon
    [[nodiscard]] virtual const Pokemon *getAttacker() const;

    /// \brief Checker for if the character can fight
    /// \return true if the character can fight
    [[nodiscard]] virtual bool canFight() const;

    /// \brief Overrides Entity::update
    /// \param map the map
    void update(Map &map) override;

    /// \brief Overrides Entity::render
    /// \param sprite character sprite
    void render(SDL_Texture *sprite) const override;

protected:
    Character(const char *id, const char *name);

    /// \brief Getter for dialogue
    /// \return the character's dialogue
    [[nodiscard]] std::vector<std::string> getDialogue() const;

    /// \brief Moves the character one tile in the direction it's facing
    void moveForward();

    /// \brief Setter for direction
    /// \param x the new direction
    void setDirection(Direction x);

    /// \brief Getter for direction
    /// \return the character's direction
    [[nodiscard]] Direction getDirection() const;

    /// \brief Faces the character the opposite direction of the parameter character
    /// \details This function does not face the character the direction in relation to where the parameter character is on the map
    /// \param character the character to face
    void face(const Character *character);

    /// \brief Checker for direction
    /// \param x the direction
    /// \return true if the character's direction is the same as the parameter direction and false otherwise
    [[nodiscard]] bool isFacing(Direction x) const;

    /// \brief Checks to see if the character can move forward
    /// \details Checks if the player, other entities, or collisions and other miscellaneous tiles are present
    /// \param map the map
    /// \return true if the character can move forward and false otherwise
    [[nodiscard]] virtual bool canMoveForward(const Map &map) const;

    /// \brief Checks for if the character has vision of an entity
    /// \param entity the entity
    /// \return true if the character can see the entity and false otherwise
    bool hasVisionOf(const Entity *entity) const;

    /// \brief Ceases autonomous decision making of an entity
    void loseAutonomy();

    /// \brief Overrides Entity::interact
    /// \param map the map
    void interact(Map &map) override;

    /// \brief Handles the character's walking protocol
    /// \param map the map
    virtual void walk(Map &map);

    /// \brief Handles the character's idling protocol
    /// \param map the map
    virtual void idle(Map &map);

    /// \brief Updates the character's sprite
    void updateSprite();

    /// \brief Increments the character's pixel counter
    void incPixelCounter();

    /// \brief Resets the character's pixel counter back to zero
    void resetPixelCounter();

    /// \brief Getter for pixel counter
    /// \return the character's pixel counter
    [[nodiscard]] int getPixelCounter() const;

private:
    std::vector<std::string> dialogue;

    std::string name;

    std::uint32_t vision;                                                     // line of sight

    int pixelCounter{ 0 };                                                    // counts how many pixels this has moved
    int currentFrame{ 0 };                                                    // current frame of the sprite

    Direction currentDirection{ Direction::DOWN };                            // which way the entity is facing
    State currentState{ State::IDLE };                                        // dictates what the entity is doing

    std::unique_ptr<Component::Intelligence> intelligence{ nullptr };

    /// \brief Performs an action
    /// \param map the map
    void act(const Map &map);
};
