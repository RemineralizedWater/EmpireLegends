//
// Created by 06spa on 2/8/2021.
//

#pragma once

#include <iostream>
#include "../Map/Map.h"

using namespace std;

class MapLoader {
private:
    string mapFilePath;
    int numberOfBoardPieces;
    bool rectangle;

    bool VerifyId(string stringId, int &intId, string argErrMsg, string outRangeErrMsg);  // int &intId pass by reference

    bool IsLand(string adjacency, int commaIndex, int currentIndex, bool &land);  // bool &land pass by reference

    bool CheckNextFieldExists(string line, int &currentIndex);  // int &currentIndex pass by reference to correctly id valid map

    bool IsRectangle();

    bool ParseAdjacency(Map *map, string adjacency, int terrId, int continentId);

public:
    MapLoader();

    MapLoader(Map *Map, int numberOfPlayers);

    MapLoader(Map *Map, int numberOfPlayers, bool shapeRectangle);

    MapLoader(const MapLoader &copy);

    ~MapLoader();

    MapLoader &operator=(const MapLoader &ml);

    friend std::ostream &operator<<(std::ostream &out, const MapLoader &ml);

    friend std::istream &operator>>(std::istream &in, MapLoader &ml);

    void LoadMap(Map *map, string file, bool &validMap);  // bool &validMap pass by reference
};
