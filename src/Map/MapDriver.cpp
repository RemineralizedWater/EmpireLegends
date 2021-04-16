//
// Created by RemineralizedWater on 2021-02-21.
//

#include <iostream>
#include <limits>

#include "Map.h"

using std::cin;
using std::string;
using std::streamsize;
using std::numeric_limits;

void cleanTerr(vector<Territory *> _terr);

void cleanAdj(vector<Adjacency *> _adj);

int DemonstrateMap(int numberOfPlayers) {
    int userInput = 0;

    while (true) {
        cout << endl << "What map would you like to test:" << endl;
        cout << "1 - Valid Map" << endl;
        cout << "2 - Invalid Map - Map must be connected graph of adjacent territories" << endl;
        cout << "3 - Invalid Map - Continents must be connected subgraphs" << endl;
        cout << "4 - Invalid Map - Each territory must belong to one and only one continent" << endl;
        cout << "5 - Return to Main Menu" << endl;

        while (true) {
            if (cin >> userInput && userInput >= 1 && userInput <= 6) {
                break;
            } else {
                cout << "Please enter a valid selection (integer, no greater than 5 and no less than 1)" << endl
                     << ">>";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        Map *map = new Map();
        vector<Territory *> terr;
        vector<Adjacency *> adj;
        std::unique_ptr<std::map<std::string, int>> armySizeForPlayer_(new std::map<string, int>());
        std::unique_ptr<std::map<std::string, bool>> hasCityForPlayer_(new std::map<string, bool>());


        switch (userInput) {
            case 1:
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)*/
                terr.push_back(new Territory(1, 1, *armySizeForPlayer_,*hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());

                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(1, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                break;
            case 2:
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)
                 * 1        |6          |(L, No Adjacency)*/   // invalid, Territory 6 is not connected to rest of graph
                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(6, 1, *armySizeForPlayer_, *hasCityForPlayer_));   // invalid
                map->AddTerritory(terr.back());

                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(1, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                break;
            case 3:
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)(L,6)(L,7)   // invalid, Continent 2 is not a connected subgraph
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)
                 * 2        |6          |(L,2)
                 * 2        |7          |(L,2)*/                     // invalid, Continent 2 is not a connected subgraph
                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(6, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(7, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());                                                 // invalid

                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(1, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(6, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(6, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(7, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());                                     // invalid
                terr.push_back(new Territory(2, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(7, true));
                map->AddAdjacency(terr.back(), adj.back());                                     // invalid
                break;
            case 4:
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)
                 * 2        |1          |(L,2)      // invalid, Territory 1 belongs to Continents 1 & 2
                 * 2        |2          |(L,1)*/    // invalid, Territory 1 belongs to Continents 1 & 2
                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(1, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());                                                // invalid
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                map->AddTerritory(terr.back());

                terr.push_back(new Territory(1, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(1, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(2, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(3, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(4, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(5, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(4, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(5, 1, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(3, true));
                map->AddAdjacency(terr.back(), adj.back());
                terr.push_back(new Territory(1, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(2, true));
                map->AddAdjacency(terr.back(), adj.back());                                        // invalid
                terr.push_back(new Territory(2, 2, *armySizeForPlayer_, *hasCityForPlayer_));
                adj.push_back(new Adjacency(1, true));
                map->AddAdjacency(terr.back(), adj.back());                                        // invalid
                break;
            case 5:
            default:
                cleanTerr(terr);
                cleanAdj(adj);
                delete map;
                map = nullptr;
                return 0;
        }
        map->Display();
        map->Validate();
        cout << "Valid Map!" << endl;
        cleanTerr(terr);
        cleanAdj(adj);
        delete map;
        map = nullptr;
    }
}

void cleanTerr(vector<Territory *> terr_) {
    while (!terr_.empty()) {
        delete terr_.back();
        terr_.back() = nullptr;
        terr_.pop_back();
    }
}

void cleanAdj(vector<Adjacency *> adj_) {
    while (!adj_.empty()) {
        delete adj_.back();
        adj_.back() = nullptr;
        adj_.pop_back();
    }
}
