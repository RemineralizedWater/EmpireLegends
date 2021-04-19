#include "Player/Player.h"
#include "Game/Game.h"

void DemonstrateA3Part1(Map *modelMap, Game *game) {
    PlayerStrategies *greedy = new GreedyComputerStrategy();
    PlayerStrategies *human = new HumanStrategy();
    PlayerStrategies *moderate = new ModerateComputerStrategy();

    // Player 1 Setup
    Player *modelPlayer1(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       20,
                       "Player 1",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()
            ));

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
    modelPlayer1->SetMoney(20);
    modelPlayer1->SetArmiesTokens(0);
    modelPlayer1->SetCitiesDisks(0);

    modelPlayer1->SetStrategy(greedy);

    // Player 2 Setup
    Player *modelPlayer2(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       20,
                       "Player 2",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()
            ));

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
    modelPlayer2->SetMoney(20);
    modelPlayer2->SetArmiesTokens(0);
    modelPlayer2->SetCitiesDisks(0);

    modelPlayer2->SetStrategy(human);

    vector<Player *> players;
    players.push_back(modelPlayer1);
    players.push_back(modelPlayer2);

    Deck *modelDeck(game->CreateDeck());

    cout << "Populating Face Up Cards.." << endl;
    modelDeck->PopulateFaceUpCards();

    modelPlayer1->ExecuteStrategy(modelDeck);
    modelPlayer2->ExecuteStrategy(modelDeck);

    modelPlayer2->SetStrategy(moderate);
    modelPlayer2->ExecuteStrategy(modelDeck);

    // Memory clean up
    if (greedy != nullptr) {
        delete greedy;
        greedy = nullptr;
    }
    if (moderate != nullptr) {
        delete moderate;
        moderate = nullptr;
    }
    if (human != nullptr) {
        delete human;
        human = nullptr;
    }
    if (modelPlayer1 != nullptr) {
        delete modelPlayer1;
        modelPlayer1 = nullptr;
    }
    if (modelPlayer2 != nullptr) {
        delete modelPlayer2;
        modelPlayer2 = nullptr;
    }
    if (modelDeck != nullptr) {
        delete modelDeck;
        modelDeck = nullptr;
    }
}
