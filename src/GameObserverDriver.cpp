#include <memory>
#include <sstream>
#include <vector>
#include "Player/Player.h"
#include "Player/PlayerController.h"
#include "Cards/Deck.h"
#include "Cards/DeckController.h"
#include "Cards/Hand.h"
#include "Cards/HandController.h"
#include "GameObservers.h"
#include "Map/Map.h"
#include "Map/MapController.h"
#include "Game/Game.h"

void GameObservers(Map *modelMap, Game *game) {

    int const NUMBER_OF_ROUNDS_TO_PLAY = 5;

    // Player 1 Setup
    Player *modelPlayer1(new Player("Player1_name"));
    PlayerObserver *viewPlayer1 = new PlayerObserver(modelPlayer1);
    PlayerController *controllerPlayer1 = new PlayerController(viewPlayer1, modelPlayer1);

    Hand *modelPlayer1Hand(modelPlayer1->MyHand);
    HandObserver *viewPlayer1Hand = new HandObserver(modelPlayer1Hand);
    HandController *controllerPlayer1Hand = new HandController(viewPlayer1Hand, modelPlayer1Hand);

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    {
        vector<terrInfo>::iterator terrIt;
        for (terrIt = modelMap->GetTerrAndAdjsList()->begin();
             terrIt != modelMap->GetTerrAndAdjsList()->end(); ++terrIt) {
            (*terrIt).first->InsertNewArmyPlayerMapping(modelPlayer1->GetName());
            (*terrIt).first->InsertNewCityPlayerMapping(modelPlayer1->GetName());
            if ((*terrIt).first->GetTerrId() == 1)
                (*terrIt).first->AddCityForPlayer(modelPlayer1->GetName());
        }
    }
    modelPlayer1->SetMap(modelMap);
    modelPlayer1->MyHand->SetOwningPlayer(modelPlayer1);
    modelPlayer1->SetMoney(14);
    modelPlayer1->SetArmiesTokens(18);
    modelPlayer1->SetCitiesDisks(3);

    // Player 2 Setup
    Player *modelPlayer2(new Player("Player2_name"));
    PlayerObserver *viewPlayer2 = new PlayerObserver(modelPlayer2);
    PlayerController *controllerPlayer2 = new PlayerController(viewPlayer2, modelPlayer2);

    Hand *modelPlayer2Hand(modelPlayer2->MyHand);
    HandObserver *viewPlayer2Hand = new HandObserver(modelPlayer2Hand);
    HandController *controllerPlayer2Hand = new HandController(viewPlayer2Hand, modelPlayer2Hand);

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    {
        vector<terrInfo>::iterator terrIt;
        for (terrIt = modelMap->GetTerrAndAdjsList()->begin();
             terrIt != modelMap->GetTerrAndAdjsList()->end(); ++terrIt) {
            (*terrIt).first->InsertNewArmyPlayerMapping(modelPlayer2->GetName());
            (*terrIt).first->InsertNewCityPlayerMapping(modelPlayer2->GetName());
            if ((*terrIt).first->GetTerrId() == 1)
                (*terrIt).first->AddCityForPlayer(modelPlayer2->GetName());
        }
    }
    modelPlayer2->SetMap(modelMap);
    modelPlayer2->MyHand->SetOwningPlayer(modelPlayer2);
    modelPlayer2->SetMoney(14);
    modelPlayer2->SetArmiesTokens(18);
    modelPlayer2->SetCitiesDisks(3);

    vector<Player *> players;
    players.push_back(modelPlayer1);
    players.push_back(modelPlayer2);

    Deck *modelDeck(game->CreateDeck());
    DeckObserver *viewDeck = new DeckObserver(modelDeck);
    DeckController *controllerDeck = new DeckController(viewDeck, modelDeck);
    controllerDeck->ControlDeck();

    int index = 0;
    while (true) {
        if (players[0]->MyHand->GetNumberOfCardsInHand() >= (int)(NUMBER_OF_ROUNDS_TO_PLAY / 2) &&
                players[1]->MyHand->GetNumberOfCardsInHand() >= (int)(NUMBER_OF_ROUNDS_TO_PLAY / 2)) {
            cout << "GAME OVER! " << NUMBER_OF_ROUNDS_TO_PLAY << " Rounds have been played" << endl;

            // Score calculation
            int winner = 0;
            if (game->Tied(players, winner)) {
                //money
                game->CountMoney(players);
                if (game->Tied(players, winner)) {
                    //armies
                    game->CountArmies(players, modelMap);
                    if (game->Tied(players, winner)) {
                        game->CountControlledTerritories(players, modelMap);
                        game->Tied(players, winner);
                        cout << "Winner! After Counting Most Controlled Territories on the board" << endl;
                        cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName()
                             << endl;
                    } else {
                        cout << "Winner! After Counting Most Armies on the board" << endl;
                        cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName()
                             << endl;
                    }
                } else {
                    cout << "Winner! After Counting Money" << endl;
                    cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName() << endl;
                }
            } else {
                cout << "Winner!" << endl;
                cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName() << endl;
            }

            break;
        }

        cout << "--------------------------------------------------------------------------" << endl;
        cout << players[index]->GetName() << "'s TURN" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        modelDeck->PrintCardsIn(modelDeck->GetFaceUpCards());
        players[index]->MyHand->Exchange(modelDeck);
        players[index]->ResolveActiveCard();
        players[index]->ComputeScore(index, players, modelMap);

        if (index == 0) index = 1;
        else index = 0;

        string option;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "Enter 'X' to exit, or anything else to continue to next player turn." << endl;
        cin >> option;
        if (option.compare("X") == 0 || option.compare("x") == 0) {
            break;
        }
    }

    // Memory clean up
    if (controllerDeck != nullptr && viewDeck != nullptr && modelDeck != nullptr) {
        delete controllerDeck;
        controllerDeck = nullptr;
        viewDeck = nullptr;
        modelDeck = nullptr;
    }

    if(controllerPlayer1Hand != nullptr && viewPlayer1Hand != nullptr && modelPlayer1Hand != nullptr){
        delete controllerPlayer1Hand;
        controllerPlayer1Hand = nullptr;
        viewPlayer1Hand = nullptr;
        modelPlayer1Hand = nullptr;
    }

    if(controllerPlayer2Hand != nullptr && viewPlayer2Hand != nullptr && modelPlayer2Hand != nullptr){
        delete controllerPlayer2Hand;
        controllerPlayer2Hand = nullptr;
        viewPlayer2Hand = nullptr;
        modelPlayer2Hand = nullptr;
    }

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
}
