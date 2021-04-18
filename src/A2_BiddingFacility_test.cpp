#include <iostream>
#include "Player/Player.h"

void DemonstrateA2BiddingFacility() {

    int whiteLines = 100;

    Player *player1(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       0,
                       "Player 1",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()));
    player1->MyHand->SetOwningPlayer(player1);
    player1->GetBiddingFacility()->SetOwningPlayer(player1);
    player1->RequestPlayerName();

    Player *player2(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       0,
                       "Player 2",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()));
    player2->MyHand->SetOwningPlayer(player2);
    player2->GetBiddingFacility()->SetOwningPlayer(player2);
    player2->RequestPlayerName();

    Player *players[2] = {player1, player2};

    // enter bids
    for (int i = 0; i < 2; i++) {
        cout << "Bidding details for player " << players[i]->GetName() << endl;
        cout << "Providing 14 coins to " << players[i]->GetName() << endl;
        players[i]->SetMoney(14);
        players[i]->GetBiddingFacility()->EnterBid();

        for (int j = 0; j < whiteLines; j++) {
            cout << endl;
        }
    }

    // reveal bids
    for (int i = 0; i < 2; i++) {
        players[i]->GetBiddingFacility()->RevealBid();
    }

    // determine bid winner
    Player *winningBidPlayer;
    int highestBid = -1;
    for (int i = 0; i < 2; i++) {
        if (players[i]->GetBiddingFacility()->GetBidAmount() > highestBid) {
            highestBid = players[i]->GetBiddingFacility()->GetBidAmount();
            winningBidPlayer = players[i];
        }
    }

    for (int i = 0; i < 2; i++) {
        if (players[i]->GetBiddingFacility()->GetBidAmount() == highestBid &&
            players[i]->GetName().compare(winningBidPlayer->GetName()) < 0) {
            winningBidPlayer = players[i];
        }
    }

    for (int i = 0; i < 2; i++) {
        if (players[i] == winningBidPlayer) {
            players[i]->GetBiddingFacility()->ResolveBid(true);
        } else {
            players[i]->GetBiddingFacility()->ResolveBid(false);
        }
    }

    // Memory clean up
    if (winningBidPlayer != nullptr) {
        delete winningBidPlayer;
        winningBidPlayer = nullptr;
    }
    if (player1 != nullptr) {
        delete player1;
        player1 = nullptr;
    }
    if (player2 != nullptr) {
        delete player2;
        player2 = nullptr;
    }

    return;
}
