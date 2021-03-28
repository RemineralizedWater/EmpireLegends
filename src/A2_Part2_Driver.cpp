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
    player1->getBiddingFacility()->SetOwningPlayer(player1);

    cout<<"Enter Player 1 Name: "<<endl;
    string temp=" ";
    cin>>temp;
    player1->getBiddingFacility()->SetLastName(temp);

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
    player2->getBiddingFacility()->SetOwningPlayer(player2);

    cout<<"Enter Player 2 Name: "<<endl;
    cin>>temp;
    player2->getBiddingFacility()->SetLastName(temp);


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

    cout<<"Neutral Armies has Been Placed in PlaceHolder Territory."<<endl;

    cout<<endl;
    cout<<"/////////////////////PLAYER1/////////////////////"<<endl;
    cout<<endl;
    //PLAYER#1//////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    cout<<"----------------------------------"<<endl;

    cout<<player1->getName()<<" Currently has "<<player1->getMoney()<<" Coins."<<endl;
    cout<<"Assigning 14 Coins to "<<player1->getName()<<endl;
    player1->setMoney(14);
    cout<<player1->getName()<<" Currently has "<<player1->getMoney()<<" Coins."<<endl;
    cout<<endl;
    cout<<"/////////////////////PLAYER2/////////////////////"<<endl;
    cout<<endl;
    //PLAYER#2//////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout<<player2->getName()<<" currently has "<<player2->GetArmiesTokens()<<" Armies."<<endl;
    cout<<"Assigning 18 armies to "<<player2->getName()<<endl;
    player2->SetArmiesTokens(18);
    cout<<player2->getName()<<" currently has "<<player2->GetArmiesTokens()<<" Armies."<<endl;
    cout<<"----------------------------------"<<endl;

    cout<<player2->getName()<<" currently has "<<player2->GetCitiesDisks()<<" Cities."<<endl;
    cout<<"Assigning 3 disks to "<<player2->getName()<<endl;
    player2->SetCitiesDisks(3);
    cout<<player2->getName()<<" currently has "<<player2->GetCitiesDisks()<<" Cities."<<endl;
    cout<<"----------------------------------"<<endl;

    cout<<"Placing 4 armies in starting Territories."<<endl;

    terr->InsertNewArmyPlayerMapping(player2->getName());
    terr->InsertNewCityPlayerMapping(player2->getName());

    terr->getHasCity()[player2->getName()]=true;
    player2->PlaceNewArmies(4);
    cout<<"----------------------------------"<<endl;

    cout<<player2->getName()<<" Currently has "<<player2->getMoney()<<" Coins."<<endl;
    cout<<"Assigning 14 Coins to "<<player2->getName()<<endl;
    player2->setMoney(14);
    cout<<player2->getName()<<" Currently has "<<player2->getMoney()<<" Coins."<<endl;

    cout<<"/////////////////////////////////"<<endl;

    // enter bids
    for(int i = 0; i < 2; i++){
        cout << "Bidding details for player " << players[i]->getName() << endl;


        players[i]->getBiddingFacility()->EnterBid();

        for(int j = 0; j < 100; j++){
            cout << endl;
        }
    }

    // reveal bids
    for(int i = 0; i < 2; i++) {
        players[i]->getBiddingFacility()->RevealBid();
    }

    // determine bid winner
    Player * winningBidPlayer;
    int highestBid = -1;
    for(int i = 0; i < 2; i++) {
        if(*players[i]->getBiddingFacility()->GetBidAmount() > highestBid){
            highestBid = *players[i]->getBiddingFacility()->GetBidAmount();
            winningBidPlayer = players[i];
        }
    }

    for(int i = 0; i < 2; i++) {
        if(*players[i]->getBiddingFacility()->GetBidAmount() == highestBid &&
           players[i]->getName().compare(winningBidPlayer->getName()) < 0){
            winningBidPlayer = players[i];
        }
    }

    for(int i = 0; i < 2; i++) {
        if(players[i] == winningBidPlayer){
            players[i]->getBiddingFacility()->ResolveBid(true);
        }else{
            players[i]->getBiddingFacility()->ResolveBid(false);
        }
    }

    delete winningBidPlayer;
    winningBidPlayer = nullptr;
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
    delete players[0];
    players[0] = nullptr;
    delete players[1];
    players[1] = nullptr;
    delete deck;
    deck = nullptr;
    delete terr;
    terr = nullptr;


    return;

}