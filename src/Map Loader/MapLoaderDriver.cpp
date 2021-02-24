#include "MapLoader.h"
#include <iostream>
/**
 * main function that reads various files and creates a map object for valid map files, and rejects invalid map files of different kinds
 * @param numberOfPlayers
 */
void DemonstrateMapLoader(int numberOfPlayers) {
    MapLoader *map = new MapLoader(numberOfPlayers);
    map->loadMap("../src/Map Boards/valid_map.txt");
    delete map;
    map = new MapLoader(numberOfPlayers);
    map->loadMap("../src/Map Boards/invalid_map.txt");
    delete map;
    map = new MapLoader(numberOfPlayers);
    map->loadMap("../src/Map Boards/invalid1_map.txt");
    delete map;
    map= nullptr;
}

