
#include <iostream>
#include <vector>
#include "Cards.h"
#include "../Player/Player.h"

using namespace std;

void DemonstrateCards(int numberOfPlayers){

    std::unique_ptr<Player> player (new Player("Montreal", BiddingFacility(), Territory(), Cards(),
                                                    rand(), rand(), rand(), *new Hand()));

    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(numberOfPlayers);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    player->hand_->Exchange(deck);

    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    cout << "Cards in player hand:" << endl;
    deck->PrintCardsIn(player->hand_->GetHand());

}