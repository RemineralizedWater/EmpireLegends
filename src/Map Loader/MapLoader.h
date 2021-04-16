//
// Created by 06spa on 2/8/2021.
//
#ifndef EMPIRELEGENDS_MAPLOADER_H
#define EMPIRELEGENDS_MAPLOADER_H

#include <iostream>
#include "../Map/Map.h"

using std::string;

class MapLoader {
private:
    string mapFilePath;
    int numberOfBoardPieces;
    bool rectangle;
    Map *map;

    bool VerifyId(string stringId, int &intId, string argErrMsg, string outRangeErrMsg);  // int &intId pass by reference

    bool IsLand(string adjacency, int commaIndex, int currentIndex, bool &land);  // bool &land pass by reference

    bool CheckNextFieldExists(string line, int &currentIndex);  // int &currentIndex pass by reference to correctly id valid map

    bool IsRectangle();

    bool ParseAdjacency(string adjacency, Territory* territory);

public:
    MapLoader();

    MapLoader(int numberOfPlayers);

    MapLoader(const MapLoader &copy);

    ~MapLoader();

    MapLoader &operator=(const MapLoader &ml);

    friend std::ostream &operator<<(std::ostream &out, const MapLoader &ml);

    friend std::istream &operator>>(std::istream &in, MapLoader &ml);

    Map *LoadMap(string file, bool &validMap);  // bool &validMap pass by reference
};

#endif //EMPIRELEGENDS_MAPLOADER_H
