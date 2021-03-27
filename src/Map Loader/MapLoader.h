//
// Created by 06spa on 2/8/2021.
//
#ifndef EMPIRELEGENDS_MAPLOADER_H
#define EMPIRELEGENDS_MAPLOADER_H
#include <iostream>
#include "../Map/Map.h"
class MapLoader {
public:
    MapLoader();
    MapLoader(int numberOfPlayers);
    MapLoader(MapLoader &copy);
    ~MapLoader();

    Map* loadMap(std::string file,bool &validMap);
    MapLoader & operator =(const MapLoader &ml);
    friend std::ostream & operator << (std::ostream &out, const MapLoader &ml);
    friend std::istream & operator >> (std::istream &in, MapLoader &ml);
private:
    std::string* mapFilePath;
    int* numberOfBoardPieces;
    bool* rectangle;
    Map* map;

    bool verifyId(std::string string_id, int &int_id, std::string argErrMsg,std::string outRangeErrMsg);
    bool isLand(std::string adjacency, int commaIndex, int currentIndex, bool &land );
    bool checkNextFieldExists(std::string line,int &currentIndex);
    bool isRectangle();
    bool parseAdjacency(std::string adjacency, Territory* territory);

};
#endif //EMPIRELEGENDS_MAPLOADER_H
