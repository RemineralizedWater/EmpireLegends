#include "MapLoader.h"
#include <iostream>

/**
 * main function that reads various files and creates a map object for valid map files, and rejects invalid map files of different kinds
 * @param numberOfPlayers
 */
void MapLoaderDriver(int numberOfPlayers) {
    Map *map = new Map();
    MapLoader *mapLoader = new MapLoader(map, numberOfPlayers);
    bool validMap = false;

    mapLoader->LoadMap(map, "../src/Map Boards/valid_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }

    map = new Map();
    mapLoader = new MapLoader(map, numberOfPlayers);
    mapLoader->LoadMap(map, "../src/Map Boards/invalid1_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }

    map = new Map();
    mapLoader = new MapLoader(map, numberOfPlayers);
    mapLoader->LoadMap(map, "../src/Map Boards/invalid2_map.txt", validMap);
    if (validMap) {
        map->Display();
    }
    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }
}
