#include <iostream>
#include <vector>
#include "Cards.h"
#include "../Player/Player.h"

using namespace std;

void DemonstrateCards(int numberOfPlayers) {
    std::unique_ptr<Player> player(
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
                       0));

    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(numberOfPlayers);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    player->MyHand->Exchange(deck);

    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    cout << "Cards in player MyHand:" << endl;
    deck->PrintCardsIn(player->MyHand->GetHand());

    // Memory clean up
    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }
}
