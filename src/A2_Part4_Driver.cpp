#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

//Main driver for Ass1. to create and run desired functions of the player class
void DemonstrateA2Part4() {

    std::unique_ptr<Player> playerSimon(new Player("Montreal",
                                                   new BiddingFacility(),
                                                   Territory(),
                                                   Cards(),
                                                   new int(0),
                                                   1,
                                                   new int(0),
                                                   new Hand(),
                                                   0,
                                                   "Player 1",
                                                   0,
                                                   3,
                                                   true));


    std::unique_ptr<std::map<std::string, int>> armySizeForPlayer(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> hasArmy(new std::map<std::string, bool>());
    Territory territoryToTest(new int(rand()), new int(rand()), *armySizeForPlayer, *hasArmy);

    std::unique_ptr<std::map<std::string, int>> map1(new std::map<std::string, int>());
    std::unique_ptr<std::map<std::string, bool>> map2(new std::map<std::string, bool>());
    Territory territoryToTest2(new int(rand()), new int(rand()), *map1, *map2);


    playerSimon->BuildCity();
    playerSimon->DestroyArmy(rand());
    playerSimon->MoveArmies(2);
    playerSimon->MoveOverLand();
    playerSimon->PayCoin(1);
    playerSimon->PlaceNewArmies(1);
    playerSimon->MoveOverWater();
    playerSimon->MoveOverLand();
    //playerSimon->AndOrAction(); // needs a card to showcase - see part 3 demonstration

    /*
    std::unique_ptr<Player> copyPlayerConstructor(new Player(*playerSimon.get())); //copy constructor
    *copyPlayerConstructor = *playerSimon;//assignment operator

    std::istringstream istringstream("Another city");//creating stream of string
    istringstream >> *copyPlayerConstructor;//stream insertion operation
    */
    return;
}