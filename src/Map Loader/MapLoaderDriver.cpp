#include "MapLoader.h"
#include <iostream>
/**
 * main function that reads various files and creates a map object for valid map files, and rejects invalid map files of different kinds
 * @param numberOfPlayers
 */
void DemonstrateMapLoader(int numberOfPlayers) {
    //load valid map
    MapLoader *map = new MapLoader(numberOfPlayers);
    map->loadMap("../src/Map Boards/valid_map.txt");
    //load invalid maps
    map->loadMap("../src/Map Boards/invalid1_map.txt");
    map->loadMap("../src/Map Boards/invalid2_map.txt");
    map->loadMap("../src/Map Boards/invalid3_map.txt");
    delete map;
    map= nullptr;
}

