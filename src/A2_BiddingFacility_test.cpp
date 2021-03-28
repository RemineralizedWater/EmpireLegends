#include <iostream>
#include "Player/Player.h"
#include "Cards/Deck.h"
#include "Map/Map.h"
#include "Map Loader/MapLoader.h"
#include "Game/Game.h"

void DemonstrateA2BiddingFacility(){

    int whiteLines = 100;

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
    player1->RequestPlayerName();

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
    player2->RequestPlayerName();

    Player *players[2] = {player1, player2};

    // enter bids
    for(int i = 0; i < 2; i++){
        cout << "Bidding details for player " << players[i]->getName() << endl;
        cout << "Providing 14 coins to " << players[i]->getName() << endl;
        players[i]->setMoney(14);
        players[i]->getBiddingFacility()->EnterBid();

        for(int j = 0; j < whiteLines; j++){
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

    return;
}