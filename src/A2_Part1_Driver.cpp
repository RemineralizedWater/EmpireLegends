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
        cout << "Starting point token: " << map->GetStartingPoint() << endl;
        map->Display();
    }

    cout<<"\n\n\n\n"<<endl;
    vector<Player*> players= starter->CreatePlayers(map->GetStartingPoint());
    for (Player* p : players){
        cout <<p->GetName()<< ": "<<p->GetBiddingFacility()->GetLastName() <<" Money:"<<p->GetMoney()<< " Bid Amount:" <<p->GetBiddingFacility()->GetBidAmount()<<endl;
    }

    cout<<"\n\n\n\n"<<endl;
    Deck* deck= starter->CreateDeck();
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