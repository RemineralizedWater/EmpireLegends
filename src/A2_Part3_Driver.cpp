#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

void DemonstrateA2Part3(){

    Player *player1(
            new Player("Montreal",
                       new BiddingFacility(),
                       Territory(),
                       Cards(),
                       new int(18),
                       1,
                       new int(3),
                       new Hand(),
                       0,
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
                       new int(18),
                       1,
                       new int(3),
                       new Hand(),
                       0,
                       "Player 2",
                       0,
                       3,
                       true));
    player2->hand_->SetOwningPlayer(player2);

    Player *players[2] = {player1, player2};

    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(2);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    int index = 0;
    while(true){
        cout << "======== " << players[index]->getName() << "'s TURN ========" << endl;
        players[index]->hand_->Exchange(deck);
        players[index]->ResolveActiveCard();

        cout << "Cards in deck: " << endl;
        deck->PrintCardsIn(deck->GetDeck());
        cout << "Cards in Face Up Pile:" << endl;
        deck->PrintCardsIn((deck->GetFaceUpCards()));
        cout << "Cards in " << players[index]->getName() << "'s hand:" << endl;
        deck->PrintCardsIn(players[index]->hand_->GetHand());

        if(index == 0) index = 1;
        else index = 0;

        string option;
        cout << "Enter 'X' to exit, or anything else to continue to next player turn." << endl;
        cin >> option;
        if(option.compare("X") == 0 || option.compare("x") == 0){
            break;
        }
    }

}