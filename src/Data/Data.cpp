//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

/// Pokemon

Pokemon Greninja("Greninja", "water", "dark", 50, 300, 95, 67, 103, 71, 122, { new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory });
Pokemon Charizard("Charizard", "fire", "flying", 50, 300, 84, 78, 109, 85, 100, { new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam });
Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50, 300, 105, 90, 125, 90, 98, { new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast });
Pokemon Pikachu("Pikachu", "electric", 50, 300, 55, 40, 50, 50, 90, { new Thunder, new QuickAttack, new IronTail, new VoltTackle });
Pokemon Lucario("Lucario", "fighting", "steel", 50, 300, 110, 70, 115, 70, 90, { new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse });

/// Player

Trainer Trainer_1({ &Greninja, &Charizard, &Hydreigon }, 1, 1);

/// Items

const RestoreItem potion(2, 20, "Potion", "HP");
const RestoreItem ether(2, 5, "Ether", "PP");

const StatusItem paralyzeHeal(2, "Paralysis Heal", "paralysis");
const StatusItem burnHeal(3, "Burn Heal", "burn");
const StatusItem IceHeal(2, "Ice Heal", "freeze");
const StatusItem Antidote(3, "Antidote", "poison");
const StatusItem Awakening(4, "Awakening", "sleep");

const PokeBall pokeBall(5, 1.0f, "Poke Ball");
const PokeBall GreatBall(5, 1.5f, "Great Ball");
const PokeBall UltraBall(5, 2.0f, "Ultra Ball");

const BattleItem XAttack(10, "X-Attack", "attack");
const BattleItem XSpeed(5, "X-Speed", "speed");

std::vector<RestoreItem> userRestoreItems = { potion, ether };
std::vector<StatusItem> userStatusItems = { paralyzeHeal, burnHeal, IceHeal, Antidote, Awakening };
std::vector<PokeBall> userPokeBalls = { pokeBall, GreatBall, UltraBall };
std::vector<BattleItem> userBattleItems = { XAttack, XSpeed };

/// Maps

Map Route_1("Route 1", 12, 10, { NPC({ &Pikachu, &Lucario }, 6, 6, 3) }, { { 5, 0, MapIDs::ROUTE_2, 10, 18 } });
Map Route_2("Route 2", 21, 20, { { 10, 19, MapIDs::ROUTE_1, 5, 1 }, { 0, 10, MapIDs::ROUTE_3, 19, 5 } });
Map Route_3("Route 3", 21, 11, { { 20, 5, MapIDs::ROUTE_2, 1, 10 } });