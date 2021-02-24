//
// Created by RemineralizedWater on 2021-02-21.
//

#include <iostream>
#include <limits>

#include "Map.h"

using std::cin;
using std::streamsize;
using std::numeric_limits;

int DemonstrateMap(int numberOfPlayers) {
    int userInput = 0;

    while(true){
        cout << endl << "What map would you like to test:" << endl;
        cout << "1 - Valid Map" << endl;
        cout << "2 - Invalid Map - Map must be connected graph of adjacent territories" << endl;
        cout << "3 - Invalid Map - Continents must be connected subgraphs" << endl;
        cout << "4 - Invalid Map - Each territory must belong to one and only one continent" << endl;
        cout << "5 - Return to Main Menu" << endl;

        while(true){
            if(cin >> userInput && userInput >= 1 && userInput <= 6){
                break;
            }else{
                cout << "Please enter a valid selection (integer, no greater than 5 and no less than 1)" << endl << ">>";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        Map* map = new Map();
        switch (userInput) {
            case 1:
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)*/
                map->addTerritory(new Territory(new int{1}, new int{1}));
                map->addTerritory(new Territory(new int{2}, new int{1}));
                map->addTerritory(new Territory(new int{3}, new int{1}));
                map->addTerritory(new Territory(new int{4}, new int{1}));
                map->addTerritory(new Territory(new int{5}, new int{1}));

                map->addAdjacency(new Territory(new int{1}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{1}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{3}, new bool(true)));
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
                map->addTerritory(new Territory(new int{1}, new int{1}));
                map->addTerritory(new Territory(new int{2}, new int{1}));
                map->addTerritory(new Territory(new int{3}, new int{1}));
                map->addTerritory(new Territory(new int{4}, new int{1}));
                map->addTerritory(new Territory(new int{5}, new int{1}));
                map->addTerritory(new Territory(new int{6}, new int{1}));   // invalid

                map->addAdjacency(new Territory(new int{1}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{1}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                break;
            case 3:
                // TODO Make invalid map
                /* Stores the information below in the graph:
                 * Continent|Territory  |Adjacency
                 * 1        |1          |(L,2)
                 * 1        |2          |(L,1)(L,3)(L,4)(L,6)(L,7)   // invalid, Continent 2 is not a connected subgraph
                 * 1        |3          |(L,2)(L,5)
                 * 1        |4          |(L,2)(L,5)
                 * 1        |5          |(L,4)(L,3)
                 * 2        |6          |(L,2)
                 * 2        |7          |(L,2)*/                     // invalid, Continent 2 is not a connected subgraph
                map->addTerritory(new Territory(new int{1}, new int{1}));
                map->addTerritory(new Territory(new int{2}, new int{1}));
                map->addTerritory(new Territory(new int{3}, new int{1}));
                map->addTerritory(new Territory(new int{4}, new int{1}));
                map->addTerritory(new Territory(new int{5}, new int{1}));
                map->addTerritory(new Territory(new int{6}, new int{2}));
                map->addTerritory(new Territory(new int{7}, new int{2}));   // invalid

                map->addAdjacency(new Territory(new int{1}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{1}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{6}, new int{2}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{2}), new Adjacency(new int{6}, new bool(true)));
                map->addAdjacency(new Territory(new int{7}, new int{2}), new Adjacency(new int{2}, new bool(true)));   // invalid
                map->addAdjacency(new Territory(new int{2}, new int{2}), new Adjacency(new int{7}, new bool(true)));   // invalid
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
                map->addTerritory(new Territory(new int{1}, new int{1}));
                map->addTerritory(new Territory(new int{1}, new int{2}));   // invalid
                map->addTerritory(new Territory(new int{2}, new int{1}));
                map->addTerritory(new Territory(new int{3}, new int{1}));
                map->addTerritory(new Territory(new int{4}, new int{1}));
                map->addTerritory(new Territory(new int{5}, new int{1}));

                map->addAdjacency(new Territory(new int{1}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{1}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{2}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{3}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{2}, new bool(true)));
                map->addAdjacency(new Territory(new int{4}, new int{1}), new Adjacency(new int{5}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{4}, new bool(true)));
                map->addAdjacency(new Territory(new int{5}, new int{1}), new Adjacency(new int{3}, new bool(true)));
                map->addAdjacency(new Territory(new int{1}, new int{2}), new Adjacency(new int{2}, new bool(true)));   // invalid
                map->addAdjacency(new Territory(new int{2}, new int{2}), new Adjacency(new int{1}, new bool(true)));   // invalid
                break;
            case 5:
            default:
                delete map;
                map = nullptr;
                return 0;
        }
        map->display();
        map->validate();
        cout << "Valid Map!" << endl;
        delete map;
        map = nullptr;
    }
}
