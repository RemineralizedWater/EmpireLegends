#include "MapLoader.h"
#include <iostream>

/**
 * main function that reads various files and creates a map object for valid map files, and rejects invalid map files of different kinds
 * @param numberOfPlayers
 */
void DemonstrateMapLoader(int numberOfPlayers) {
    MapLoader *mapLoader = new MapLoader(numberOfPlayers);
    bool validMap = false;

    Map *map = mapLoader->LoadMap("../src/Map Boards/valid_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }

    mapLoader = new MapLoader(numberOfPlayers);
    mapLoader->LoadMap("../src/Map Boards/invalid1_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }

    mapLoader = new MapLoader(numberOfPlayers);
    mapLoader->LoadMap("../src/Map Boards/invalid2_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }
}
