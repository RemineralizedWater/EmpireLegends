#include "Player.h"
#include <memory>
#include <sstream>

//Main driver for Ass1. to create and run desired functions of the player class
void DemonstratePlayers(){
    std::unique_ptr<Player> playerSimon (new Player("Montreal", BiddingFacility(), Territory(), Cards(),
                                                    rand(), rand(), rand()));
    playerSimon->BuildCity();
    playerSimon->DestroyArmy();
    playerSimon->MoveArmies();
    playerSimon->MoveOverLand();
    playerSimon->PayCoin();
    playerSimon->PlaceNewArmies();

    std::unique_ptr<Player> copyPlayerConstructor(new Player(*playerSimon.get())); //copy constructor
    *copyPlayerConstructor = *playerSimon;//assignment operator

    std::istringstream istringstream("Another city");//creating stream of string
    istringstream>>*copyPlayerConstructor;//stream insertion operation
}