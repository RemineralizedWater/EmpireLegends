#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

void DemonstrateA2Part5() {

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
                       new Map(), 0, 0));
    player1->MyHand->SetOwningPlayer(player1);

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
                       "Player 1",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map(), 0, 0));
    player2->MyHand->SetOwningPlayer(player2);

    Player *players[2] = {player1, player2};

    //cout << "Creating deck.." << endl;
    Deck *deck = new Deck(2);
    //cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    //cout << "Cards in deck: " << endl;
    //deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    int index = 0;
    while (true) {
        cout << "======== " << players[index]->GetName() << "'s TURN ========" << endl;
        players[index]->MyHand->Exchange(deck);
        cout << "=======================================================================" << endl;
        cout << "Sliding of remaining cards to the left to fill in the empty card space." << endl;
        cout << "Drawing new card and placing it in the right-most space." << endl;
        cout << "=======================================================================" << endl;
        players[index]->ResolveActiveCard();

        /*cout << "Cards in deck: " << endl;
        deck->PrintCardsIn(deck->GetDeck());*/
        cout << "Cards in Face Up Pile:" << endl;
        deck->PrintCardsIn((deck->GetFaceUpCards()));
        /*cout << "Cards in " << players[index]->GetName() << "'s MyHand:" << endl;
        deck->PrintCardsIn(players[index]->MyHand->GetHand());*/

        if (index == 0) index = 1;
        else index = 0;

        string option;
        cout << "Enter 'X' to exit, or anything else to continue to next player turn." << endl;
        cin >> option;
        if (option.compare("X") == 0 || option.compare("x") == 0) {
            break;
        }
        cout << "=======================================================================" << endl;
        cout << "Passing turn to the next player." << endl;
        cout << "=======================================================================" << endl;
    }

    // Memory clean up
    if (player1 != nullptr) {
        delete player1;
        player1 = nullptr;
    }
    if (player2 != nullptr) {
        delete player2;
        player2 = nullptr;
    }
    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }

    return;
}
