#include <iostream>
#include <limits>
#include "Game/Game.h"
#include "GameObservers.h"
#include "Map/MapController.h"

using namespace std;

void DemonstrateA3Part1(Map *modelMap, Game *game);

void MainGameLoop(Game *game, Map *map, bool &validMap, bool &isTournament, int &numberOfPlayers);


void InitialGameConfig(Game *game, Map *modelMap, bool &validMap, bool &isTournament, int &numberOfPlayers,
                       PlayerStrategies *greedy, PlayerStrategies *human, PlayerStrategies *moderate, PlayerStrategies
                       *playerOneStrategy, PlayerStrategies *playerTwoStrategy, PlayerStrategies *playerThreeStrategy,
                       PlayerStrategies *playerFourStrategy);


void GameObservers(Map *map, Game *game);

//void DemonstrateA3Part4();

int main() {
    bool isTournament = false;
    int numberOfPlayers = 2;
    bool validMap = false;

    PlayerStrategies *playerOneStrategy = nullptr;
    PlayerStrategies *playerTwoStrategy = nullptr;
    PlayerStrategies *playerThreeStrategy = nullptr;
    PlayerStrategies *playerFourStrategy = nullptr;

    PlayerStrategies *human = new HumanStrategy();
    PlayerStrategies *greedy = new GreedyComputerStrategy();
    PlayerStrategies *moderate = new ModerateComputerStrategy();

    Map *modelMap = new Map();
    MapLoader *mapLoader = new MapLoader(modelMap, numberOfPlayers, true);
    mapLoader->LoadMap(modelMap, "../src/Map Boards/valid_map.txt", validMap);
    Game *game = new Game(numberOfPlayers, modelMap);

    InitialGameConfig(game, modelMap, validMap, isTournament, numberOfPlayers, greedy, human, moderate,
                      playerOneStrategy, playerTwoStrategy, playerThreeStrategy, playerFourStrategy);

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
        cout << endl << "What Part Driver would you like to execute:" << endl;
        cout << "1 - Part 1: Player Strategy Pattern " << endl;
        cout << "2 - Part 2: Phase Observer" << endl;
        cout << "3 - Part 3: Game Statistics Observer" << endl;
        cout << "4 - Part 4: Game Tournament" << endl;
        cout << "5 - Main Game Loop" << endl;
        cout << "6 - Exit" << endl;

        while (true) {
            if (cin >> userInput && userInput >= 1 && userInput <= 6) {
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
                exit(0);
                break;
            case 2:
                GameObservers(modelMap, game);
                break;
            case 3:
                GameObservers(modelMap, game);
                break;
            case 4:
                //DemonstrateA3Part4();
                break;
            case 5:
                break;
            case 6:
            default:
                return;
        }
    }
    return;
}

// Handles Configuration of Initial Game Settings
void InitialGameConfig(Game *game, Map *modelMap, bool &validMap, bool &isTournament, int &numberOfPlayers,
                       PlayerStrategies *human, PlayerStrategies *greedy, PlayerStrategies *moderate, PlayerStrategies
                       *playerOneStrategy, PlayerStrategies *playerTwoStrategy, PlayerStrategies *playerThreeStrategy,
                       PlayerStrategies *playerFourStrategy) {
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
    }

    // Determine each player's strategy
    for (int i = 0; i < numberOfPlayers; i++) {
        input = 0;
        cout << "Strategies:\n1) Human Player Strategy (requires user interaction to make decisions)" <<
             "\n2) Greedy Computer Strategy (automated, focuses on building cities or destroying opponents)" <<
             "\n3) Moderate Computer Strategy (automated, focuses on occupying regions with more armies than opponents)" << endl;
        cout << "Enter Player " << to_string(i + 1) << "\'s Strategy (1, 2, or 3):";
        while (true) {
            if (cin >> input && input >= 1 && input <= 3) {
                break;
            } else {
                cout << "Please enter a valid Strategy (1, 2, or 3):";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cout << "Player " << to_string(i + 1) << " selected Strategy: ";
        switch (input) {
            case 1:
                cout << "1) Human Player Strategy" << endl;
                if (i + 1 == 1) {
                    playerOneStrategy = human;
                }
                if (i + 1 == 2) {
                    playerTwoStrategy = human;
                }
                if (i + 1 == 3) {
                    playerThreeStrategy = human;
                }
                if (i + 1 == 4) {
                    playerFourStrategy = human;
                }
                break;
            case 2:
                cout << "2) Greedy Computer Strategy" << endl;
                if (i + 1 == 1) {
                    playerOneStrategy = greedy;
                }
                if (i + 1 == 2) {
                    playerTwoStrategy = greedy;
                }
                if (i + 1 == 3) {
                    playerThreeStrategy = greedy;
                }
                if (i + 1 == 4) {
                    playerFourStrategy = greedy;
                }
                break;
            case 3:
                cout << "3) Moderate Computer Strategy" << endl;
                if (i + 1 == 1) {
                    playerOneStrategy = moderate;
                }
                if (i + 1 == 2) {
                    playerTwoStrategy = moderate;
                }
                if (i + 1 == 3) {
                    playerThreeStrategy = moderate;
                }
                if (i + 1 == 4) {
                    playerFourStrategy = moderate;
                }
                break;
            default:
                break;
        }
        cout << endl;
    }
}