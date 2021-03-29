
#include <iostream>
#include <limits>
#include "Game/Game.h"
#include "Map/Map.h"


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
void mainGameLoop(Map* map, bool validMap);

int main() {

    Game *starter;
    Map *map;
    int numberOfPlayers = 0;

    // Determine the number of players
    cout << "Enter the number of players:";
    while(true){
        if(cin >> numberOfPlayers && numberOfPlayers >= 2 && numberOfPlayers <= 4){
            //cout<<numberOfPlayers<<endl;
            break;
        }else{
            cout << "Please enter a valid number of players (integer, no greater than 4 and no less than 2)" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    bool validMap=false;
    starter = new Game(numberOfPlayers);

    while(!validMap) {
        map = starter->selectMap(validMap);
        validMap = map->validate();
    }

    // Main Game Loop
    mainGameLoop(map, validMap);

    delete map;
    map = nullptr;
    delete starter;
    starter = nullptr;

    return 0;
}

void mainGameLoop(Map *map, bool validMap) {
    int userInput = 0;

    while(true){
        cout << endl << "What would you like to test:" << endl;
        cout << "1 - Part 1: Game start " << endl;
        cout << "2 - Part 2: Game play: startup phase" << endl;
        cout << "3 - Part 3: Game play: main game loop" << endl;
        cout << "4 - Part 4: Main game loop: The player actions" << endl;
        cout << "5 - Part 5: Main game loop: after the action" << endl;
        cout << "6 - Part 6: Main Game loop: Compute the game score" << endl;
        cout << "7 - Exit" << endl;

        while(true){
            if(cin >> userInput && userInput >= 1 && userInput <= 7){
                break;
            }else{
                cout << "Please enter a valid selection (integer, no greater than 6 and no less than 1)" << endl << ">>";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        switch (userInput) {
            case 1:
                if(validMap){
                    cout<<"Starting point token: "<<*(map->getStartingPoint())<<endl;
                    map->display();
                }
                DemonstrateA2Part1();
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
            default:
                return;
        }
    }
    return;
}
