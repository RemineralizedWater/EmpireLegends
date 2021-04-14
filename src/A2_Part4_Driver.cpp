#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

//Main driver for Ass1. to create and run desired functions of the player class
void DemonstrateA2Part4() {

    std::unique_ptr<Player> playerSimon(new Player("Montreal",
                                                   new BiddingFacility(),
                                                   *(new Territory()),
                                                   *(new Cards()),
                                                   0,
                                                   1,
                                                   0,
                                                   new Hand(),
                                                   0,
                                                   "Player 1",
                                                   0,
                                                   3,
                                                   true,
                                                   0,
                                                   0));


    std::unique_ptr<std::map<std::string, int>> armySizeForPlayer(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> hasArmy(new std::map<std::string, bool>());
    Territory territoryToTest(rand(), rand(), *armySizeForPlayer, *hasArmy);

    std::unique_ptr<std::map<std::string, int>> map1(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> map2(new std::map<std::string, bool>());
    Territory territoryToTest2(rand(), rand(), *map1, *map2);


    playerSimon->BuildCityForPlayer();
    playerSimon->DestroysNumberOfArmyOfPlayer(rand());
    playerSimon->MoveArmiesForPlayer(2);
    playerSimon->MoveOverLandForPlayer();
    playerSimon->PaysCoinFromPlayer(1);
    playerSimon->PlaceNewArmies(1);
    playerSimon->MoveOverWaterForPlayer();
    playerSimon->MoveOverLandForPlayer();
    return;
}