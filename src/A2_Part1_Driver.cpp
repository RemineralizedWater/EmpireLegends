#include <iostream>
#include "Player/Player.h"
#include "Cards/Deck.h"
#include "Map/Map.h"
#include "Map Loader/MapLoader.h"
#include "Game/Game.h"

void DemonstrateA2Part1(){

    Game* starter = new Game(2);
    bool validMap=false;
    Map* map=starter->selectMap(validMap);

    if(validMap){
        cout<<"Starting point token: "<<*(map->getStartingPoint())<<endl;
        map->display();
    }

    cout<<"\n\n\n\n"<<endl;
    vector<Player*> players=starter->createPlayers(*(map->getStartingPoint()));
    for (Player* p : players){
        cout << "LastName:"<<*(p->getBiddingFacility()->GetLastName()) <<" Money:"<<p->getMoney()<< " Bid Amount:" <<*(p->getBiddingFacility()->GetBidAmount())<<endl;
    }

    cout<<"\n\n\n\n"<<endl;
    Deck* deck=starter->createDeck();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());

    for (Player* p : players){
        delete p;
        p= nullptr;
    }

    delete map;
    map= nullptr;
    delete deck;
    deck = nullptr;
    delete starter;
    starter= nullptr;

    return;
}