#include "Player/Player.h"
#include <sstream>
#include "GameObservers.h"
#include "Player/PlayerController.h"

void DemonstrateA2Part3() {


    // Player 1 Setup
    Player *modelPlayer1(new Player());
    PlayerObserver *viewPlayer1 = new PlayerObserver(modelPlayer1);
    PlayerController *controllerPlayer1 = new PlayerController(viewPlayer1, modelPlayer1);

    modelPlayer1->MyHand->SetOwningPlayer(modelPlayer1);
    modelPlayer1->SetName("Player 1 name");
    modelPlayer1->SetMoney(14);
    modelPlayer1->SetArmiesTokens(18);
    modelPlayer1->SetCitiesDisks(3);

    // Player 2 Setup
    Player *modelPlayer2(new Player());
    PlayerObserver *viewPlayer2 = new PlayerObserver(modelPlayer2);
    PlayerController *controllerPlayer2 = new PlayerController(viewPlayer2, modelPlayer2);

    modelPlayer2->MyHand->SetOwningPlayer(modelPlayer2);
    modelPlayer2->SetName("Player 2 name");
    modelPlayer2->SetMoney(14);
    modelPlayer2->SetArmiesTokens(18);
    modelPlayer2->SetCitiesDisks(3);

    Player *players[2] = {modelPlayer1, modelPlayer2};

    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(2);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    int index = 0;
    while (true) {
        cout << "======== " << players[index]->GetName() << "'s TURN ========" << endl;
        players[index]->MyHand->Exchange(deck);
        players[index]->ResolveActiveCard();

        cout << "Cards in deck: " << endl;
        deck->PrintCardsIn(deck->GetDeck());
        cout << "Cards in Face Up Pile:" << endl;
        deck->PrintCardsIn((deck->GetFaceUpCards()));
        cout << "Cards in " << players[index]->GetName() << "'s MyHand:" << endl;
        deck->PrintCardsIn(players[index]->MyHand->GetHand());

        if (index == 0) index = 1;
        else index = 0;

        string option;
        cout << "Enter 'X' to exit, or anything else to continue to next player turn." << endl;
        cin >> option;
        if (option.compare("X") == 0 || option.compare("x") == 0) {
            break;
        }
    }

    // Memory clean up
    if (controllerPlayer1 != nullptr && viewPlayer1 != nullptr && modelPlayer1 != nullptr) {
        delete controllerPlayer1;
        controllerPlayer1 = nullptr;
        viewPlayer1 = nullptr;
        modelPlayer1 = nullptr;
    }
    if (controllerPlayer2 != nullptr && viewPlayer2 != nullptr && modelPlayer2 != nullptr) {
        delete controllerPlayer2;
        controllerPlayer2 = nullptr;
        viewPlayer2 = nullptr;
        modelPlayer2 = nullptr;
    }

    return;
}
