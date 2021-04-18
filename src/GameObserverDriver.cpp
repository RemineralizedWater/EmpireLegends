#include <memory>
#include <sstream>
#include <vector>
#include "Player/Player.h"
#include "Player/PlayerController.h"
#include "Cards/Deck.h"
#include "Cards/DeckController.h"
#include "GameObservers.h"
#include "Map/Map.h"
#include "Map/MapController.h"
#include "Game/Game.h"

void GameObservers(Map *modelMap, Game *game){

    int const NUMBER_OF_ROUNDS_TO_PLAY = 20;

    // Player 1 Setup
    Player *modelPlayer1(new Player("Player1_name"));
    PlayerObserver *viewPlayer1 = new PlayerObserver(modelPlayer1);
    PlayerController *controllerPlayer1 = new PlayerController(viewPlayer1, modelPlayer1);

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    {
        vector<terrInfo>::iterator terrIt;
        for (terrIt = modelMap->GetTerrAndAdjsList()->begin();
             terrIt != modelMap->GetTerrAndAdjsList()->end(); ++terrIt) {
            (*terrIt).first->InsertNewArmyPlayerMapping(modelPlayer1->GetName());
            (*terrIt).first->InsertNewCityPlayerMapping(modelPlayer1->GetName());
            if((*terrIt).first->GetTerrId() == 1)
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

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    {
        vector<terrInfo>::iterator terrIt;
        for (terrIt = modelMap->GetTerrAndAdjsList()->begin();
             terrIt != modelMap->GetTerrAndAdjsList()->end(); ++terrIt) {
            (*terrIt).first->InsertNewArmyPlayerMapping(modelPlayer2->GetName());
            (*terrIt).first->InsertNewCityPlayerMapping(modelPlayer2->GetName());
            if((*terrIt).first->GetTerrId() == 1)
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
        if(players[0]->MyHand->GetNumberOfCardsInHand() >= (int)(NUMBER_OF_ROUNDS_TO_PLAY / 2) &&
                players[1]->MyHand->GetNumberOfCardsInHand() >= (int)(NUMBER_OF_ROUNDS_TO_PLAY / 2)) {
            cout << "GAME OVER! " << NUMBER_OF_ROUNDS_TO_PLAY << " Rounds have been played" << endl;
            cout << "DISPLAY SCORES" << endl;
            break;
        }

        cout << "======== " << players[index]->GetName() << "'s TURN ========" << endl;
        players[index]->MyHand->Exchange(modelDeck);
        players[index]->ResolveActiveCard();
        players[index]->ComputeScore(index, players, modelMap);

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
    if (controllerDeck != nullptr && viewDeck != nullptr && modelDeck != nullptr) {
        delete controllerDeck;
        controllerDeck = nullptr;
        viewDeck = nullptr;
        modelDeck = nullptr;
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
