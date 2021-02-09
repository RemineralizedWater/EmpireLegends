#include "Player.h"

//Main driver for Ass1. to create and run desired functions of the player class
void DemonstratePlayers(){
    Player* playerSimon = new Player();
    playerSimon->BuildCity();
    playerSimon->DestroyArmy();
    playerSimon->MoveArmies();
    playerSimon->MoveOverLand();
    playerSimon->PayCoin();
    playerSimon->PlaceNewArmies();
    delete playerSimon;

}