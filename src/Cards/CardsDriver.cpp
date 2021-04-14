
#include <iostream>
#include <vector>
#include "Cards.h"
#include "../Player/Player.h"

using namespace std;

void DemonstrateCards(int numberOfPlayers){


    std::unique_ptr<Player> player(
            new Player("Montreal",
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

    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(numberOfPlayers);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    player->Hands->Exchange(deck);

    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    cout << "Cards in player hand:" << endl;
    deck->PrintCardsIn(player->Hands->GetHand());

    delete deck;
    deck = nullptr;
}