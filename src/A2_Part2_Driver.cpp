//
// Created by Hsen on 2021-03-26.
//

#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

void DemonstrateA2Part2(){

    Player *player1(
            new Player("Montreal",
                       new BiddingFacility(),
                       Territory(),
                       Cards(),
                       new int(0),
                       1,
                       new int(0),
                       new Hand(),
                       new int(0),
                       "Player 1",
                       0,
                       3,
                       true));
    player1->hand_->SetOwningPlayer(player1);

    Player *player2(
            new Player("Montreal",
                       new BiddingFacility(),
                       Territory(),
                       Cards(),
                       new int(0),
                       1,
                       new int(0),
                       new Hand(),
                       new int(0),
                       "Player 2",
                       0,
                       3,
                       true));
    player2->hand_->SetOwningPlayer(player2);

    Player *players[2] = {player1, player2};

    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(2);
    cout<< "Shuffling deck.."<<endl;
    deck->ShuffleDeck();
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));


    cout<<player1->getName()<<" currently has "<<player1->GetArmiesTokens()<<" Armies."<<endl;
    cout<<"Assigning 18 armies to "<<player1->getName()<<endl;
    player1->SetArmiesTokens(18);
    cout<<player1->getName()<<" currently has "<<player1->GetArmiesTokens()<<" Armies."<<endl;
    cout<<"----------------------------------"<<endl;

    cout<<player1->getName()<<" currently has "<<player1->GetCitiesDisks()<<" Cities."<<endl;
    cout<<"Assigning 3 disks to "<<player1->getName()<<endl;
    player1->SetCitiesDisks(3);
    cout<<player1->getName()<<" currently has "<<player1->GetCitiesDisks()<<" Cities."<<endl;
    cout<<"----------------------------------"<<endl;

    cout<<"Placing 4 armies in starting Territories."<<endl;
    Territory *terr = new Territory();
    terr->InsertNewArmyPlayerMapping(player1->getName());
    terr->InsertNewCityPlayerMapping(player1->getName());

    terr->getHasCity()[player1->getName()]=true;
    player1->PlaceNewArmies(4);

    cout<<player1->getName()<<" Currently has "<<player1->getMoney()<<" Coins."<<endl;
    cout<<"Assigning 14 Coins to "<<player1->getName()<<endl;
    player1->setMoney(14);
    cout<<player1->getName()<<" Currently has "<<player1->getMoney()<<" Coins."<<endl;





}