#include "Player/Player.h"
#include "Player/PlayerStrategies.h"
#include "Map/Map.h"
#include "Game/Game.h"

void DemonstrateA3Part1(Map *modelMap, Game *game) {
    PlayerStrategies *greedy = new GreedyComputerStrategy();
    PlayerStrategies *human = new HumanStrategy();
    PlayerStrategies *moderate = new ModerateComputerStrategy();
    vector<Player*> players=game->CreatePlayers(10);

    players.at(0)->SetStrategy(human);
    players.at(1)->SetStrategy(greedy);

    Deck *modelDeck(game->CreateDeck());
    cout << "Populating Face Up Cards.." << endl;
    modelDeck->PopulateFaceUpCards();

    game->Setup(players);

    players.at(0)->ExecuteStrategy(modelDeck, game->GetNumberOfPlayers());
    players.at(1)->ExecuteStrategy(modelDeck,game->GetNumberOfPlayers());

    players.at(1)->SetStrategy(moderate);
    players.at(1)->ExecuteStrategy(modelDeck,game->GetNumberOfPlayers());

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
    if (players.at(0) != nullptr) {
        delete players.at(0);
        players.at(0) = nullptr;
    }
    if (players.at(1) != nullptr) {
        delete players.at(1);
        players.at(1) = nullptr;
    }
    if (modelDeck != nullptr) {
        delete modelDeck;
        modelDeck = nullptr;
    }
}
