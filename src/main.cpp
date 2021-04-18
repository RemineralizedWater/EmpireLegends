#include <iostream>
#include <limits>
#include "Game/Game.h"
#include "Map/Map.h"
#include "GameObservers.h"
#include "Map/MapController.h"

using namespace std;

void DemonstrateA2Part4();

void DemonstrateBiddingFacility(int numberOfPlayers);

void MapLoaderDriver(int numberOfPlayers);

void DemonstrateCards(int numberOfPlayers);

int DemonstrateMap(int numberOfPlayers);

void DemonstrateA2Part3();

void DemonstrateA2Part2();

void DemonstrateA2Part1();

void DemonstrateA2Part5();

void DemonstrateA2Part6();

void DemonstrateA2BiddingFacility();

void DemonstrateA3Part1(Map *modelMap, Game *game);

void MainGameLoop(Game *game, Map *map, bool &validMap, bool &isTournament, int &numberOfPlayers);

void InitialGameConfig(Game *game, Map *map, bool &validMap, bool &isTournament, int &numberOfPlayers,
                       int &stratOne, int &stratTwo, int &stratThree, int &stratFour);

void GameObservers(Map *map, Game *game);

int main() {
    bool isTournament = false;
    int numberOfPlayers = 2;
    bool validMap = false;
    int playerOneStrategy = 0;
    int playerTwoStrategy = 0;
    int playerThreeStrategy = 0;
    int playerFourStrategy = 0;

    Game *game = new Game(numberOfPlayers);
    Map *modelMap = new Map();

    InitialGameConfig(game, modelMap, validMap, isTournament, numberOfPlayers, playerOneStrategy, playerTwoStrategy, playerThreeStrategy, playerFourStrategy);

    MapObserver *viewMap = new MapObserver(modelMap);
    MapController *controllerMap = new MapController(viewMap, modelMap);

    controllerMap->ControlMap();

    // Main Game Loop
    MainGameLoop(game, modelMap, validMap, isTournament, numberOfPlayers);

    // Memory clean up
    if (modelMap != nullptr) {
        delete modelMap;
        modelMap = nullptr;
        viewMap = nullptr;
        controllerMap = nullptr;
    }
    if (game != nullptr) {
        delete game;
        game = nullptr;
    }

    return 0;
}

void MainGameLoop(Game *game, Map *modelMap, bool &validMap, bool &isTournament, int &numberOfPlayers) {
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
                cout << "Please enter a valid selection (integer, no greater than 8 and no less than 1)" << endl
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
                //DemonstrateA2Part2(); //broken, discard or adapt for A3
                break;
            case 3:
                //DemonstrateA2Part3(); //broken, discard or adapt for A3
                break;
            case 4:
                //DemonstrateA2Part4(); //broken, discard or adapt for A3
                break;
            case 5:
                //DemonstrateA2Part5(); //broken, discard or adapt for A3
                break;
            case 6:
                //DemonstrateA2Part6(); //broken, discard or adapt for A3
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

// Handles Configuration of Initial Game Settings
void InitialGameConfig(Game *game, Map *modelMap, bool &validMap, bool &isTournament, int &numberOfPlayers,
                       int &stratOne, int &stratTwo, int &stratThree, int &stratFour) {
    int input = 0;

    // Determine the game mode
    cout << "Enter the Game Mode (1 = Single Game, 2 = Tournament):";
    while (true) {
        if (cin >> input && input >= 1 && input <= 2) {
            break;
        } else {
            cout << "Please enter a valid Game Mode (1 or 2):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    if (input == 1) {
        isTournament = false;
    }
    else if (input == 2) {
        isTournament = true;
    }
    else {
        cout << "Error, exiting!" << endl;
        exit(-1);
    }

    // Determine the number of players
    if (isTournament) {
        cout << "Tournament Mode selected" << endl << endl;
        numberOfPlayers = 2;
    }
    else {
        cout << "Single Game Mode selected" << endl << endl;
        numberOfPlayers = 2;
        cout << "Enter the Number of Players (2, 3 or 4):";
        while (true) {
            if (cin >> numberOfPlayers && numberOfPlayers >= 2 && numberOfPlayers <= 4) {
                break;
            } else {
                cout << "Please enter a valid Number of Players (2, 3 or 4):";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    cout << numberOfPlayers << " Players selected" << endl << endl;
    game->SetNumberOfPlayers(numberOfPlayers);

    // Determine if the map is valid
    cout << "Map Validity Check initiated";
    while (!validMap) {
        game->SelectMap(modelMap, validMap);
        //validMap = modelMap->Validate();
    }
}
