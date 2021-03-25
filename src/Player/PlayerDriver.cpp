#include "Player.h"
#include <memory>
#include <sstream>

//Main driver for Ass1. to create and run desired functions of the player class
void DemonstratePlayers() {
    std::unique_ptr<Player> playerSimon(new Player("Montreal", BiddingFacility(), Territory(), Cards(),
                                                   rand(), rand(), rand(), Hand(), rand(), "Player 1", rand(), rand()));


    std::unique_ptr<std::map<std::string, int>> armySizeForPlayer(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> hasArmy(new std::map<std::string, bool>());
    Territory territoryToTest(new int(rand()), new int(rand()), *armySizeForPlayer, *hasArmy);

    std::unique_ptr<std::map<std::string, int>> map1(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> map2(new std::map<std::string, bool>());
    Territory territoryToTest2(new int(rand()), new int(rand()), *map1, *map2);


    playerSimon->BuildCity(territoryToTest);
    playerSimon->DestroyArmy(territoryToTest, "PlayerAttacking", "PlayerBeingAttacked", rand());
    playerSimon->MoveArmies(territoryToTest, territoryToTest2, "PlayerWhoWantsToMove", 2);
    playerSimon->MoveOverLand();
    playerSimon->PayCoin(1);
    playerSimon->PlaceNewArmies(1);
    playerSimon->MoveOverWater();
    playerSimon->MoveOverLand();
    playerSimon->AndOrAction("GoodAndAction");

    std::unique_ptr<Player> copyPlayerConstructor(new Player(*playerSimon.get())); //copy constructor
    *copyPlayerConstructor = *playerSimon;//assignment operator

    std::istringstream istringstream("Another city");//creating stream of string
    istringstream >> *copyPlayerConstructor;//stream insertion operation
}