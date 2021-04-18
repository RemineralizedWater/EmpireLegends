#include <iostream>
#include <limits>
#include "Game/Game.h"
#include "Map/Map.h"
#include "GameObservers.h"
#include "Map/MapController.h"

using namespace std;

void DemonstrateA2Part4();

void DemonstrateBiddingFacility(int numberOfPlayers);

void DemonstrateMapLoader(int numberOfPlayers);

void DemonstrateCards(int numberOfPlayers);

int DemonstrateMap(int numberOfPlayers);

void DemonstrateA2Part3();

void DemonstrateA2Part2();

void DemonstrateA2Part1();

void DemonstrateA2Part5();

void DemonstrateA2Part6();

void DemonstrateA2BiddingFacility();

void DemonstrateA3Part1(Map *modelMap, Game *game);

void MainGameLoop(Map *map, bool validMap, Game *game);

void GameObservers(Map *map, Game *game);

int main() {
    int numberOfPlayers = 2;
    bool validMap = false;

    Game *game = new Game(numberOfPlayers);

    Map *modelMap(game->SelectMap(validMap));
    MapObserver *viewMap = new MapObserver(modelMap);
    MapController *controllerMap = new MapController(viewMap, modelMap);

    while (!validMap) {
        modelMap = game->SelectMap(validMap);
        validMap = modelMap->Validate();
    }

    controllerMap->ControlMap();

    // Main Game Loop
    MainGameLoop(modelMap, validMap, game);

    // Memory clean up
    if(modelMap != nullptr){
        delete modelMap;
        modelMap = nullptr;
        viewMap = nullptr;
        controllerMap = nullptr;
    }
    if(game != nullptr){
        delete game;
        game = nullptr;
    }

    return 0;
}

void MainGameLoop(Map *modelMap, bool validMap, Game *game) {
    int userInput = 0;

    while (true) {
        cout << endl << "What would you like to test:" << endl;
        cout << "1 - Part 1: Player Strategy Pattern " << endl;
        cout << "2 - Part 2: Game play: startup phase" << endl;
        cout << "3 - Part 3: Game play: main game loop" << endl;
        cout << "4 - Part 4: Main game loop: The player actions" << endl;
        cout << "5 - Part 5: Main game loop: after the action" << endl;
        cout << "6 - Part 6: Main Game loop: Compute the game score" << endl;
        cout << "7 - A3 Part 3: GameObservers" << endl;
        cout << "8 - Exit" << endl;

        while (true) {
            if (cin >> userInput && userInput >= 1 && userInput <= 8) {
                break;
            } else {
                cout << "Please enter a valid selection (integer, no greater than 6 and no less than 1)" << endl
                     << ">>";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        switch (userInput) {
            case 1:
                if (validMap) {
                    cout << "Starting point token: " << modelMap->GetStartingPoint() << endl;
                    modelMap->Display();
                }
                DemonstrateA3Part1(modelMap, game);
                break;
            case 2:
                DemonstrateA2Part2();
                break;
            case 3:
                DemonstrateA2Part3();
                break;
            case 4:
                DemonstrateA2Part4();
                break;
            case 5:
                DemonstrateA2Part5();
                break;
            case 6:
                DemonstrateA2Part6();
                break;
            case 7:
                GameObservers(modelMap, game);
                break;
            case 8:
            default:
                return;
        }
    }
    return;
}
