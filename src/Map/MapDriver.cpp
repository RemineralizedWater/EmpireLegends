//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"
/* Stores the information below in the graph
 *
 * Continent|territory|adjacency
 * 1|1|(L,2)
 * 1|2|(L,1)(L,3)(L,4)
 * 1|3|(L,2)(L,5)
 * 1|4|(L,2)(L,5)
 * 1|5|(L,4)(L,3)*/
void DemonstrateMap() {
    Map* map = new Map();

    map->addTerritory(new Territory(new int{1},new int{1}));
    map->addTerritory(new Territory(new int{2},new int{1}));
    map->addTerritory(new Territory(new int{3},new int{1}));
    map->addTerritory(new Territory(new int{4},new int{1}));
    map->addTerritory(new Territory(new int{5},new int{1}));

    map->addAdjacency(new Territory(new int{1},new int{1}), new Adjacency(new int{2},new bool(true)));
    map->addAdjacency(new Territory(new int{2},new int{1}), new Adjacency(new int{1},new bool(true)));
    map->addAdjacency(new Territory(new int{2},new int{1}), new Adjacency(new int{3},new bool(true)));
    map->addAdjacency(new Territory(new int{2},new int{1}), new Adjacency(new int{4},new bool(true)));
    map->addAdjacency(new Territory(new int{3},new int{1}), new Adjacency(new int{2},new bool(true)));
    map->addAdjacency(new Territory(new int{3},new int{1}), new Adjacency(new int{5},new bool(true)));
    map->addAdjacency(new Territory(new int{4},new int{1}), new Adjacency(new int{2},new bool(true)));
    map->addAdjacency(new Territory(new int{4},new int{1}), new Adjacency(new int{5},new bool(true)));
    map->addAdjacency(new Territory(new int{5},new int{1}), new Adjacency(new int{4},new bool(true)));
    map->addAdjacency(new Territory(new int{5},new int{1}), new Adjacency(new int{3},new bool(true)));
    map->display();
    // cout << map << endl;     // TODO Line unreachable on second or third call (randomly alternates)
    delete map;
    map = nullptr;
}