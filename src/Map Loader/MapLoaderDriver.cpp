#include "MapLoader.h"
/**
 * main function that reads various files and creates a map object for valid map files, and rejects invalid map files of different kinds
 * @param numberOfPlayers
 */
void DemonstrateMapLoader(int numberOfPlayers) {
    //load valid map
    MapLoader *map = new MapLoader("../src/Map Boards/valid_map.txt", numberOfPlayers);

    //load invalid maps
    //MapLoader *map = new MapLoader("../src/Map Boards/invalid1_map.txt", numberOfPlayers);
    //MapLoader *map = new MapLoader("../src/Map Boards/invalid2_map.txt", numberOfPlayers);
    //MapLoader *map = new MapLoader("../src/Map Boards/invalid3_map.txt", numberOfPlayers);
    delete map;
}

