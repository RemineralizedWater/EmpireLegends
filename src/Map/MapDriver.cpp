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
        cout << "3 - Invalid Map - Each territory must belong to one and only one continent" << endl;
        cout << "4 - Invalid Map - Continents must be connected subgraphs" << endl;
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
                /* Stores the information below in the graph
                 *
                 * Continent|territory|adjacency
                 * 1|1|(L,2)
                 * 1|2|(L,1)(L,3)(L,4)
                 * 1|3|(L,2)(L,5)
                 * 1|4|(L,2)(L,5)
                 * 1|5|(L,4)(L,3)*/
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
                // TODO Make invalid map
                break;
            case 3:
                /* Stores the information below in the graph
                 *
                 * Continent|territory|adjacency
                 * 1|1|(L,2)
                 * 1|2|(L,1)(L,3)(L,4)
                 * 1|3|(L,2)(L,5)
                 * 1|4|(L,2)(L,5)
                 * 1|5|(L,4)(L,3)
                 * 2|1|(L,2)*/
                map->addTerritory(new Territory(new int{1}, new int{1}));
                map->addTerritory(new Territory(new int{1}, new int{2}));
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
                //map->addAdjacency(new Territory(new int{1}, new int{2}), new Adjacency(new int{2}, new bool(true)));
                //map->addAdjacency(new Territory(new int{2}, new int{2}), new Adjacency(new int{1}, new bool(true)));
                break;
            case 4:
                // TODO Make invalid map
                break;
            case 5:
            default:
                delete map;
                map = nullptr;
                return 0;
        }
        //map->display();           // memory leak in display
        // cout << map << endl;     // TODO Line unreachable on second or third call (randomly alternates)
        map->validate();            // no memory leak, but not running yet
        delete map;
        map = nullptr;
    }
}
