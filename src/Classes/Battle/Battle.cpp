//
// Created by Miles on 10/1/2023.
//

#include "Battle.h"

static constexpr int NUM_TYPES = 18;

static constexpr std::array<std::array<double, NUM_TYPES>, NUM_TYPES> TYPE_CHART = {
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0 }, // normal
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0 }, // fire
        std::array<double, NUM_TYPES>{ 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, // water
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, // electric
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0 }, // grass
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // ice
        std::array<double, NUM_TYPES>{ 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5 }, // fighting
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0 }, // poison
        std::array<double, NUM_TYPES>{ 1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0 }, // ground
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 }, // flying
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0 }, // psychic
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5 }, // bug
        std::array<double, NUM_TYPES>{ 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0 }, // rock
        std::array<double, NUM_TYPES>{ 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0 }, // ghost
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0 }, // dragon
        std::array<double, NUM_TYPES>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5 }, // dark
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0 }, // steel
        std::array<double, NUM_TYPES>{ 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0 }  // fairy
};

void Battle::sendOutMessage(const Pokemon &pokemon, const bool isPlayer) {
    if (isPlayer) {
        printMessage("Go " + pokemon.getName() + "!\n");
    }
    else {
        printMessage("Your opponent sent out " + pokemon.getName() + "!\n");
    }
}

void Battle::returnMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + ", return! ");
}

void Battle::introMessage() {
    this->sendOutMessage((*this->opponent)[0], false);
    pressEnter();
    this->sendOutMessage((*this->player)[0], true);
    pressEnter();
}

void Battle::displayChoices(const int arrow, bool &print) {
    if (print) {
        printMessage("What will " + (*this->player)[0].getName() + " do?\n");
    }
    else {
        std::cout << "What will " << (*this->player)[0].getName() << " do?\n";
    }

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Bag\n" : std::cout << "\tBag\n";
    arrow == 2 ? std::cout << "   ->   Run\n" : std::cout << "\tRun\n";
    arrow == 3 ? std::cout << "   ->   Pokemon\n" : std::cout << "\tPokemon\n";

    std::cout.flush();

    print = false;
}

void Battle::displayPokemon(const int arrow, bool &print) {
    auto printOut = [this](const char *string, const int index) -> void {
        std::cout << string << (*this->player)[index].getName() << std::string(15 - (*this->player)[index].getName().length(), ' ')
                  << "(HP: " << (*this->player)[index].getHP() << std::string(3 - std::to_string((*this->player)[index].getHP()).length(), ' ')
                  << '/' << std::string(3 - std::to_string((*this->player)[index].getMaxHp()).length(), ' ') << (*this->player)[index].getMaxHp()
                  << ")\n";
    };

    if (print) {
        printMessage("Choose a Pokemon:\n");
    }
    else {
        std::cout << "Choose a Pokemon:\n";
    }

    for (int i = 0; i < this->player->partySize(); ++i) {
        if (arrow == i) {
            printOut("   ->   ", i);
        }
        else {
            printOut("        ", i);
        }
    }

    arrow == this->player->partySize() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayHpBar(const bool displayPokemon = true) {
    void (*printOut)(Trainer *) = [](Trainer *trainer) -> void {
        std::cout << "| " << (*trainer)[0].getName() << std::string(15 - (*trainer)[0].getName().length(), ' ')
                  << "| HP: " << (*trainer)[0].getHP()
                  << std::string(3 - std::to_string((*trainer)[0].getHP()).length(), ' ')
                  << '/' << (*trainer)[0].getMaxHp()
                  << std::string(3 - std::to_string((*trainer)[0].getMaxHp()).length(), ' ')
                  << " |\n";
    };

    system("cls");
    std::cout << "Turn " << this->turn << '\n';

    if (displayPokemon) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer
        printOut(this->player);

        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer
        printOut(this->opponent);
    }
    else {
        for (int i = 0; i < 2; ++i) {
            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n";
            std::cout << '|' << std::string(16, ' ') << "|" << std::string(13, ' ') << "|\n";
        }
    }

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void Battle::faintMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " fainted!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::forcedSwitchPrompt(const int arrow, bool &print) {
    if (print) {
        printMessage("Choose an option:\n");
    }
    else {
        std::cout << "Choose an option:\n";
    }

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Run" : std::cout << "\tRun";

    print = false;
    std::cout.flush();
}

bool Battle::run() {
    const int opponent_speed = ((*this->opponent)[0].getBaseSpeed() / 4) % 256;
    const int odds = (((*this->player)[0].getBaseSpeed() * 32) / opponent_speed) + 30;

    return opponent_speed == 0 or odds > 255 or generateInteger(0, 255) < odds;
}

void Battle::runMessage(const bool runStatus) {
    runStatus ? printMessage("Got away safely!\n") : printMessage("Couldn't getKey away!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::runErrorMessage() {
    printMessage("You can't run away from a trainer battle!");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::pokemonPrompt(const int arrow, bool &print) {
    if (print) {
        printMessage("Choose an option:\n");
    }
    else {
        std::cout << "Choose an option:\n";
    }

    arrow == 0 ? std::cout << "   ->   Check Moves\n" : std::cout << "\tCheck Moves\n";
    arrow == 1 ? std::cout << "   ->   Switch\n" : std::cout << "\tSwitch\n";
    arrow == 2 ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::switchOutMessage(const Trainer *trainer, const int pokemonSwitched) {
    Battle::returnMessage((*trainer)[pokemonSwitched]);
    pressEnter();
    Battle::sendOutMessage((*trainer)[0], true);
    pressEnter();
}

void Battle::inBattleMessage() {
    printMessage((*this->player)[0].getName() + " is already in battle!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::winMessage() {
    printMessage("Your opponent ran out of usable Pokemon! ");
    pressEnter();
    printMessage("You won!\n");
    pressEnter();
}

void Battle::loseMessage() {
    printMessage("You've run out of usable Pokemon! ");
    pressEnter();
    printMessage("You blacked out!\n");
    pressEnter();
}

void Battle::inflictedMessage(const Pokemon &pokemon) {
    switch (pokemon.getStatus()) {
        case Status::BURN:
            printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * 0.0625))) + " damage from it's burn!\n");
            break;
        case Status::PARALYSIS:
            printMessage(pokemon.getName() + " is paralyzed! It can't move!\n");
            break;
        case Status::FREEZE:
            printMessage(pokemon.getName() + " is frozen solid!\n");
            break;
        case Status::POISON:
            printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * 0.0625))) + " damage from it's poisoning!\n");
            break;
        case Status::SLEEP:
            printMessage(pokemon.getName() + " is fast asleep!\n");
            break;
        default:
            throw std::runtime_error("Unexpected error: function inflictedMessage");
    }

    pressEnter();
}

void Battle::displayMoves(const Pokemon &pokemon, const int arrow, bool &print) {
    const auto print_out = [&pokemon](const char *string, int index) -> void {
        std::cout << string << pokemon[index].getName() << std::string(15 - pokemon[index].getName().length(), ' ')
                  << " (PP: " << pokemon[index].getPP() << std::string(2 - std::to_string(pokemon[index].getPP()).length(), ' ')
                  << '/' << std::string(2 - std::to_string(pokemon[index].getMaxPP()).length(), ' ') << pokemon[index].getMaxPP()
                  << ")\n";
    };

    if (print) {
        printMessage("Choose a move:\n");
    }
    else {
        std::cout << "Choose a move:\n";
    }

    for (int i = 0; i < pokemon.numMoves(); ++i) {
        if (arrow == i) {
            print_out("   ->   ", i);
        }
        else {
            print_out("        ", i);
        }
    }

    arrow == pokemon.numMoves() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayMoveSummary(const Move &move) {
    std::cout << move.getName() << '\n';
    std::cout << "\tType:     " << getTypeAsString(static_cast<int>(move.getType())) << '\n';
    std::cout << "\tCategory: " << getCategoryAsString(static_cast<int>(move.getCategory())) << '\n';
    std::cout << "\tPower:    " << move.getPower() << '\n';
    std::cout << "\tAccuracy: " << move.getAccuracy() << '\n';
    std::cout << "\tPP:       " << move.getPP() << '/' << move.getMaxPP() << '\n';
    std::cout << "\n\tCancel (ENTER)\n";
    std::cout.flush();
}

void Battle::attackErrorMessage() {
    printMessage("That move is out of PP. Please select another move.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

// generates a random number between 1 and 16, inclusive
// returns true and 2.0 if that number is 1 and 1.0 and false otherwise
std::pair<double, bool> Battle::criticalHit() {
    return generateInteger(1, 16) == 1 ? std::make_pair(2.0, true) : std::make_pair(1.0, false);
}

// returns 1.5 if move is a STAB move, and 1.0 otherwise
double Battle::stabCheck(const Pokemon &pokemon, const Move &move) {
    return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5 : 1.0;
}

double Battle::checkType(const Move &move, const Pokemon &pokemon) {
    const int move_type = static_cast<int>(move.getType()) - 1;
    const double type_1 = TYPE_CHART.at(move_type).at(static_cast<int>(pokemon.getType(true)) - 1);

    double type2;
    if (pokemon.getType(false) == Type::NONE) {
        type2 = 1.0;
    }
    else {
        type2 = TYPE_CHART.at(move_type).at(static_cast<int>(pokemon.getType(false)) - 1);
    }

    return type_1 * type2;
}

int Battle::calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move, bool &crit) {
    int initialDamage = 0;

    const int level_calc = (2 * attackingPokemon.getLevel() / 5) + 2;
    if (move.getCategory() == Move::Category::PHYSICAL) {
        initialDamage = attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
    }
    else if (move.getCategory() == Move::Category::SPECIAL) {
        initialDamage = level_calc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
    }

    const int final_damage = (initialDamage / 50) + 2;
    const std::pair<double, bool> c = Battle::criticalHit();
    crit = c.second;

    //FIXME recalculate damage
    return static_cast<int>(final_damage * Battle::stabCheck(attackingPokemon, move) * Battle::checkType(move, defendingPokemon) * c.first);
}

void Battle::switchOut(Trainer *trainer, const bool isUser, bool &keepPlaying) {
    this->displayHpBar();
    int toSwitch = 0;

    if (isUser) {
        bool print = true;

        while (true) {
            Battle::forcedSwitchPrompt(toSwitch, print);
            if (chooseOption(toSwitch, 2)) {
                break;
            }
        }

        // player attempts to run
        //FIXME does not take into account trainer battle
        if (toSwitch == 1) {
            const bool run_success = run();
            Battle::runMessage(run_success);
            if (run_success) {
                keepPlaying = false;
                return;
            }
        }

        print = true;

        while (true) {
            this->displayPokemon(toSwitch, print);

            if (not chooseOption(toSwitch, this->player->partySize())) {
                continue;
            }

            if ((*trainer)[toSwitch].isFainted()) {
                (*trainer)[toSwitch - 1].hpEmptyMessage();
                pressEnter();
                continue;
            }

            break;
        }
    }

    else {
        toSwitch = generateInteger(0, trainer->partySize() - 1);
        while ((*trainer)[toSwitch].isFainted()) {
            toSwitch = generateInteger(0, trainer->partySize() - 1);
        }
    }

    trainer->swapPokemon(0, toSwitch);
}

void Battle::action(Trainer *attacker, Trainer *defender, const int move, bool &switched, const bool isUserAttacking, bool &keepPlaying) {
    bool &skip = isUserAttacking ? this->skipOpponentTurn : this->skipPlayerTurn;
    bool crit = false;
    const int dmg = Battle::calculateDamage((*attacker)[0], (*defender)[0], (*attacker)[0][move], crit);

    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], dmg, skip);
    (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], dmg, skip,
                                       crit, checkType((*attacker)[0][move], (*defender)[0]));

    if ((*defender)[0].isFainted()) {
        defender->incFaintCount();
        Battle::faintMessage((*defender)[0]);

        int toSwitch = 0;
        while (((*defender)[toSwitch].isFainted() and defender->partySize() - 1 != 0)) {
            toSwitch = generateInteger(0, defender->partySize() - 1);
        }

        // FIXME find a way to swap afterward because the HP Bar is inaccurate
        this->opponent->swapPokemon(0, toSwitch);
        this->opponent->removePokemon(toSwitch);

        if (not defender->canFight()) {
            this->displayHpBar(false);
            if (isUserAttacking) {
                for (int i = 0; i < this->player->partySize(); ++i) {
                    (*this->player)[i].resetStatMods();
                }
                this->winMessage();
            }
            else {
                this->loseMessage();
            }
            keepPlaying = false;
        }
        else {
            if (isUserAttacking) {
                int option = 0;
                bool print = true;

                reprint_1:
                this->displayHpBar();

                if (print) {
                    printMessage("Your opponent is about to send out " + (*this->opponent)[0].getName() + ".\n");
                }
                else {
                    std::cout << "Your opponent is about to send out " << (*this->opponent)[0].getName() << ".\n";
                }

                if (print) {
                    pressEnter();
                }

                if (print) {
                    printMessage("Would you like to swap out?\n");
                }
                else {
                    std::cout << "Would you like to swap out?\n";
                }

                option == 0 ? std::cout << "   ->   Yes\n" : std::cout << "\tYes\n";
                option == 1 ? std::cout << "   ->   No" : std::cout << "\tNo";

                print = false;

                if (not chooseOption(option, 1)) {
                    goto reprint_1;
                }

                print = true;
                if (option == 0) {
                    reprint_2:
                    this->displayHpBar();
                    this->displayPokemon(option, print);

                    if (not chooseOption(option, this->player->partySize())) {
                        goto reprint_2;
                    }

                    if (option == 0) {
                        this->displayHpBar();
                        this->inBattleMessage();
                        goto reprint_2;
                    }
                    if ((*this->player)[0].isFainted()) {
                        this->displayHpBar();
                        (*this->player)[option].hpEmptyMessage();
                        pressEnter();
                        goto reprint_2;
                    }

                    if (option < this->player->partySize()) {
                        this->displayHpBar();
                        this->player->swapPokemon(0, option);
                        Battle::switchOutMessage(this->player, option);
                        Battle::sendOutMessage((*this->opponent)[0], false);
                    }
                }
            }
            else {
                this->switchOut(defender, true, keepPlaying);
            }
            switched = true;
        }
    }
}

// This function commences attacking of each Pokémon and takes into account who is faster.
// If a Pokémon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
void Battle::preStatus(const int userMove, const int opponentMove, const bool isUserFaster, bool &keepPlaying) {
    bool (*hasStatusCondition)(const Status) = [](const Status status) -> bool {
        return status == Status::PARALYSIS ? generateInteger(1, 4) == 1 : status == Status::FREEZE or status == Status::SLEEP;
    };

    const auto user_action = [this, &userMove, &hasStatusCondition, &keepPlaying] -> void {
        if (userMove < (*this->player)[0].numMoves()) {
            if (not hasStatusCondition((*this->player)[0].getStatus())) {
                this->action(this->player, this->opponent, userMove, this->skipOpponentTurn, true, keepPlaying);
            }
            else {
                inflictedMessage((*this->player)[0]);
            }
        }
    };

    const auto opponent_action = [this, &opponentMove, &hasStatusCondition, &keepPlaying] -> void {
        if (not hasStatusCondition((*this->opponent)[0].getStatus())) {
            this->action(this->opponent, this->player, opponentMove, this->skipPlayerTurn, false, keepPlaying);
        }
        else {
            inflictedMessage((*this->opponent)[0]);
        }
    };

    if (isUserFaster) {
        user_action();

        if (not this->skipOpponentTurn and keepPlaying) {
            opponent_action();
        }

        this->skipOpponentTurn = false;

    }
    else {
        opponent_action();

        if (not this->skipPlayerTurn and keepPlaying) {
            user_action();
        }

        this->skipPlayerTurn = false;

    }
}

// If a Pokémon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
void Battle::postStatus(const bool isUserFaster, bool &keepPlaying) {
    if (not keepPlaying) {
        return;
    }

    bool (*hasStatusCondition)(Status) = [](Status status) -> bool {
        return status == Status::BURN or status == Status::POISON;
    };

    auto postStatus = [this, &keepPlaying](Trainer *trainer, bool isUser) {
        (*trainer)[0].takeDamage(static_cast<int>(lround((*trainer)[0].getMaxHp() * 0.0625)));
        Battle::inflictedMessage((*trainer)[0]);

        if ((*trainer)[0].isFainted()) {
            (*trainer).incFaintCount();
            Battle::faintMessage((*trainer)[0]);
        }

        if (not *trainer) {
            this->displayHpBar(false);
            if (isUser) {
                for (int i = 0; i < this->player->partySize(); ++i) {
                    (*this->player)[i].resetStatMods();
                }
                this->winMessage();
            }
            else {
                this->loseMessage();
            }
            keepPlaying = false;
        }
        if ((*trainer)[0].isFainted()) {
            isUser ? this->switchOut(trainer, true, keepPlaying) : this->switchOut(trainer, false, keepPlaying);
        }
    };

    if (isUserFaster) {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*this->player)[0].getStatus())) {
            postStatus(this->player, true);
        }

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*this->opponent)[0].getStatus())) {
            postStatus(this->opponent, false);
        }
    }
    else {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*this->opponent)[0].getStatus())) {
            postStatus(this->opponent, false);
        }

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*this->player)[0].getStatus())) {
            postStatus(this->player, true);
        }
    }
}

int Battle::chooseMove(bool &skip) {
    int move = 0;
    bool print = true;

    chooseMove:
    this->displayHpBar();
    this->displayMoves((*this->player)[0], move, print);

    if (not chooseOption(move, (*this->player)[0].numMoves())) {
        goto chooseMove;
    }

    // user chose to go back
    if (move == (*this->player)[0].numMoves()) {
        skip = true;
        return 0;
    }
    // if move chosen is out of PP...
    if (not (*this->player)[0][move]) {
        attackErrorMessage();
        goto chooseMove;
    }

    return move;

}

void Battle::chooseItem(bool &skip, const bool isTrainerBattle, bool &keepPlaying) {
    int userType = 0;
    int userItem = 0;
    bool print = true;

    const auto reset_variables = [&userType, &userItem, &print] -> void {
        userType = 0;
        userItem = 0;
        print = true;
    };

    chooseItemType:
    this->displayHpBar();
    displayBag(userType, print);

    if (not chooseOption(userType, 4)) {
        goto chooseItemType;
    }

    // trainer chose HP/PP items
    switch (userType) {
        case 0:
            print = true;

        chooseRestoreItem:
            this->displayHpBar();
            displayItems<RestoreItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<RestoreItem>())) {
                goto chooseRestoreItem;
            }

            if (userItem == this->player->getNumItems<RestoreItem>()) {
                reset_variables();
                goto chooseItemType;
            }
            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<RestoreItem>(userItem)) {
                int pokemon = 0;
                print = true;

                chooseRestorePokemon:
                this->displayHpBar();
                this->displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, this->player->partySize())) {
                    goto chooseRestorePokemon;
                }

                if (pokemon == this->player->partySize()) {
                    reset_variables();
                    goto chooseRestoreItem;
                }
                // Pokémon's HP is already full
                else if ((*this->player)[pokemon].isFullHP()) {
                    this->displayHpBar();
                    (*this->player)[pokemon].hpFullMessage();
                    pressEnter();
                    goto chooseRestorePokemon;
                }
                // Pokémon is fainted
                else if ((*this->player)[pokemon].isFainted()) {
                    this->displayHpBar();
                    (*this->player)[pokemon].hpEmptyMessage();
                    pressEnter();
                    goto chooseRestorePokemon;
                }
                // if Pokémon selected doesn't have full HP, but also isn't fainted...
                else {
                    // if item selected restores HP...
                    if (this->player->getItem<RestoreItem>(userItem).isHp()) {
                        this->displayHpBar();

                        this->player->getItem<RestoreItem>(userItem).use();
                        this->player->getItem<RestoreItem>(userItem).useMessage();

                        this->player->getItem<RestoreItem>(userItem).restore((*this->player)[pokemon]);
                        this->player->getItem<RestoreItem>(userItem).restoreMessage((*this->player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<RestoreItem>(userItem)) {
                            this->player->removeItem(userType, userItem);
                        }
                    }
                    // if item selected restores PP...
                    else {
                        int move = 0;
                        print = true;

                        choosePokemon:
                        this->displayHpBar();
                        this->displayMoves((*this->player)[pokemon], move, print);

                        if (not chooseOption(move, (*this->player)[0].numMoves())) {
                            goto choosePokemon;
                        }

                        if (move == (*this->player)[0].numMoves()) {
                            goto chooseRestorePokemon;
                        }
                        else {
                            this->displayHpBar();

                            this->player->getItem<RestoreItem>(userItem).use();
                            this->player->getItem<RestoreItem>(userItem).useMessage();

                            this->player->getItem<RestoreItem>(userItem).restore((*this->player)[pokemon][move]);
                            this->player->getItem<RestoreItem>(userItem).restoreMessage(
                                    (*this->player)[pokemon][move]);

                            // automatically removes the item if it's quantity is now 0
                            if (not this->player->getItem<RestoreItem>(userItem)) {
                                this->player->removeItem(userType, userItem);
                            }
                        }
                    }
                }
            }
            break;

        case 1:
            print = true;

        chooseStatusItem:
            this->displayHpBar();
            displayItems<StatusItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<StatusItem>())) {
                goto chooseStatusItem;
            }

            if (userItem == this->player->getNumItems<StatusItem>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<StatusItem>(userItem)) {
                int pokemon = 0;
                print = true;

                chooseStatusPokemon:
                this->displayHpBar();
                this->displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, this->player->partySize())) {
                    goto chooseStatusPokemon;
                }

                if (pokemon == this->player->partySize()) {
                    reset_variables();
                    goto chooseStatusItem;
                }

                // if Pokémon is not fainted...
                else if (not(*this->player)[pokemon].isFainted()) {
                    // if Pokémon has status condition...
                    if ((*this->player)[pokemon].isAfflicted()) {
                        this->displayHpBar();

                        this->player->getItem<StatusItem>(userItem).use();
                        this->player->getItem<StatusItem>(userItem).useMessage();
                        pressEnter();

                        this->player->getItem<StatusItem>(userItem).restore((*this->player)[pokemon]);
                        StatusItem::restoreMessage((*this->player)[pokemon]);
                        pressEnter();

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<StatusItem>(userItem)) {
                            this->player->removeItem(userType, userItem);
                        }
                    }
                    // Pokémon did not have a status condition
                    else {
                        this->displayHpBar();

                        this->player->getItem<StatusItem>(userItem).use();
                        noEffectMessage(this->player->getItem<StatusItem>(userItem), (*this->player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<StatusItem>(userItem)) {
                            this->player->removeItem(userType, userItem);
                        }
                    }
                }
                // Pokémon is fainted
                else {
                    this->displayHpBar();
                    (*this->player)[pokemon - 1].hpEmptyMessage();
                    pressEnter();
                    goto chooseStatusPokemon;
                }
            }
            break;

        case 2:
            print = true;

        choosePokeball:
            this->displayHpBar();
            displayItems<PokeBall>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<PokeBall>())) {
                goto choosePokeball;
            }

            if (userItem == this->player->getNumItems<PokeBall>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if a trainer has at least one of the items selected...
            else if (this->player->getItem<PokeBall>(userItem)) {
                if (isTrainerBattle) {
                    this->displayHpBar();
                    printMessage("You can't catch another trainer's Pokemon!");
                    pressEnter();
                    goto chooseItemType;
                }
                this->displayHpBar();

                this->player->getItem<PokeBall>(userItem).use();
                this->player->getItem<PokeBall>(userItem).useMessage();

                // automatically removes the item if it's quantity is now 0
                if (not this->player->getItem<PokeBall>(userItem)) {
                    this->player->removeItem(userType, userItem);
                }

                std::array<bool, 4> shakes{};
                const bool caught = this->player->getItem<PokeBall>(userItem).catchPokemon((*this->opponent)[0], shakes);
                catchPokemonMessage((*this->opponent)[0], shakes);
                if (caught) {
                    keepPlaying = false;
                    return;
                }
            }
            break;

        case 3:
            print = true;

        chooseBattleItem:
            this->displayHpBar();
            displayItems<BattleItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<BattleItem>())) {
                goto chooseBattleItem;
            }

            if (userItem == this->player->getNumItems<BattleItem>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<BattleItem>(userItem)) {
                this->displayHpBar();

                this->player->getItem<BattleItem>(userItem).use();
                this->player->getItem<BattleItem>(userItem).useMessage();

                bool limitReached = false;
                boostStat(this->player->getItem<BattleItem>(userItem), (*this->player)[0], 2, limitReached);
                boostMessage((*this->player)[0], this->player->getItem<BattleItem>(userItem).getStat(), 2, limitReached);

                // automatically removes the item if it's quantity is now 0
                if (not this->player->getItem<BattleItem>(userItem)) {
                    this->player->removeItem(userType, userItem);
                }
            }
            break;

        default:
            skip = true;
            return;
    }
}

bool Battle::runAway(bool &skip, const bool canRun) {
    this->displayHpBar();

    if (not canRun) {
        Battle::runErrorMessage();
        skip = true;
        return false;
    }
    //bool runAway = run();
    //FIXME commented out for testing purposes
    const bool run_away = true;
    this->runMessage(run_away);

    return run_away;
}

void Battle::choosePokemon(bool &skip) {
    int pokemon = 0;
    bool print = true;

    choosePokemon:
    this->displayHpBar();
    this->displayPokemon(pokemon, print);

    if (not chooseOption(pokemon, this->player->partySize())) {
        goto choosePokemon;
    }

    if (pokemon == this->player->partySize()) {
        skip = true;
        return;
    }

    int option = 0;
    print = true;

    chooseOption:
    this->displayHpBar();
    this->pokemonPrompt(option, print);

    if (not chooseOption(option, 2)) {
        goto chooseOption;
    }

    int userMove = 0;

    switch (option) {
        case 0:
            userMove = 0;
            print = true;

        chooseMove:
            this->displayHpBar();
            this->displayMoves((*this->player)[pokemon], userMove, print);

            if (not chooseOption(userMove, (*this->player)[pokemon].numMoves())) {
                goto chooseMove;
            }

            if (userMove == (*this->player)[pokemon].numMoves()) {
                option = 0;
                print = true;
                goto chooseOption;
            }

            this->displayHpBar();
            this->displayMoveSummary((*this->player)[pokemon][userMove]);
            pressEnter();

            userMove = 0;
            print = true;
            goto chooseMove;

        case 1:
            // trainer chose Pokémon currently in battle
            if (pokemon == 0) {
                this->displayHpBar();
                this->inBattleMessage();
                goto chooseOption;
            }
            else {
                // Pokémon chosen is not fainted
                if (not (*this->player)[pokemon].isFainted()) {
                    this->displayHpBar();
                    this->player->swapPokemon(0, pokemon);
                    Battle::switchOutMessage(this->player, pokemon);
                }
                // Pokémon chosen is fainted
                else {
                    this->displayHpBar();
                    (*this->player)[pokemon].hpEmptyMessage();
                    pressEnter();
                    goto chooseOption;
                }
            }
            break;

        default:
            print = true;
            pokemon = 0;
            goto choosePokemon;
    }
}

void Battle::fight(const int userMove, bool &keepPlaying) {
    this->displayHpBar();

    int opponentMove = 0;
    if (not (*this->opponent)[0].canAttack()) {
        // TODO add struggle
        throw std::runtime_error("Struggle not implemented yet");
    }
    // re-selects opponent move if it's out of PP
    opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    while (not(*this->opponent)[0][opponentMove]) {
        opponentMove = generateInteger(0, (*this->opponent)[0].numMoves() - 1);
    }

    // if the player is faster than the opponent or,
    // assuming the opponent isn't using a priority move,
    // the player is using a priority move...
    if ((*this->player)[0].isFasterThan((*this->opponent)[0]) or (*this->player)[0][userMove].isPriority() and not (*this->opponent)[0][opponentMove].isPriority()) {
        this->preStatus(userMove, opponentMove, true, keepPlaying);
        this->postStatus(true, keepPlaying);
    }
    // if the opponent is faster than the player or,
    // assuming the player isn't using a priority move,
    // the opponent is using a priority move...
    else if ((*this->opponent)[0].isFasterThan((*this->player)[0]) or (*this->opponent)[0][opponentMove].isPriority() and not (*this->player)[0][userMove].isPriority()) {
        this->preStatus(userMove, opponentMove, false, keepPlaying);
        this->postStatus(false, keepPlaying);
    }
    // if trainer and opponent rival in speed or both or neither are using a priority move, choose randomly
    else {
        if (coinFlip()) {
            this->preStatus(userMove, opponentMove, true, keepPlaying);
            this->postStatus(true, keepPlaying);
        }
        else {
            this->preStatus(userMove, opponentMove, false, keepPlaying);
            this->postStatus(false, keepPlaying);
        }
    }

    ++this->turn;
}

Battle::Battle(Player *trainer1, Trainer *trainer2) : player(trainer1), opponent(trainer2), turn(0ULL), skipPlayerTurn(false), skipOpponentTurn(false) {}

Battle &Battle::getInstance(Player *trainer1, Trainer *trainer2) {
    static Battle battle(trainer1, trainer2);
    return battle;
}

void Battle::engageBattle(const bool isTrainer) {
    this->displayHpBar(false);
    this->introMessage();

    ++this->turn;
    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        int option = 0;
        bool print = true;

        while (true) {
            this->displayHpBar();
            this->displayChoices(option, print);

            if (chooseOption(option, 3)) {
                break;
            }
        }

        int userMove = (*this->player)[0].numMoves();    // passed into the fight to determine move used
        bool cancel = false;                               // passed into core four functions to know if to return

        bool selecting = true;
        while (selecting) {
            switch (option) {
                case 0:
                    userMove = this->chooseMove(cancel);
                    selecting = false;
                    break;
                case 1:
                    this->chooseItem(cancel, isTrainer, keepPlaying);
                    selecting = false;
                    break;
                case 2:
                    if (this->runAway(cancel, not isTrainer)) {
                        this->opponent->clearParty();
                        for (int i = 0; i < this->player->partySize(); ++i) {
                            (*this->player)[i].resetStatMods();
                        }
                        return;
                    }
                    break;
                case 3:
                    this->choosePokemon(cancel);
                    selecting = false;
                    break;
                default:
                    continue;
            }
        }

        if (not cancel) {
            this->fight(userMove, keepPlaying);
        }
    }

    // cleanup
    this->turn = 0ULL;
    this->player = nullptr;
    this->opponent = nullptr;
    this->skipPlayerTurn = false;
    this->skipOpponentTurn = false;
}
