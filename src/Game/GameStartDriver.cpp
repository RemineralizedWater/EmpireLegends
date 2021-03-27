
#include "GameStart.h"
#include "../Player/Player.h"
#include <iostream>

void DemonstrateGameStart() {
    GameStart* starter = new GameStart(2);
    bool validMap=false;
    Map* map=starter->selectMap(validMap);

    if(validMap){
        map->display();
    }

    cout<<"\n\n\n\n"<<endl;

    vector<Player*> players=starter->createPlayers();
    for (Player* p : players){
        cout << "LastName:"<<*(p->getBiddingFacility().GetLastName()) <<" Money:"<<p->getMoney()<< " Bid Amount:" <<*(p->getBiddingFacility().GetBidAmount())<<endl;
    }

    cout<<"\n\n\n\n"<<endl;

    Deck* deck = new Deck(2);
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    delete deck;
    deck = nullptr;

}

