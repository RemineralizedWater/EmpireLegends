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

    void loadMap(std::string file);
    MapLoader & operator =(const MapLoader &ml);
    friend std::ostream & operator << (std::ostream &out, const MapLoader &ml);
    friend std::istream & operator >> (std::istream &in, MapLoader &ml);
private:
    std::string* mapFilePath;
    int* numberOfBoardPieces;
    bool* rectangle;
    Map* map;

    int verifyRegionName(std::string line,int currentIndex, int charIndex, std::string argErrMsg, std::string outRangeErrMsg);
    int checkNextFieldExists(std::string line,int currentIndex);
    bool isLand(std::string adjacency, int commaIndex, int currentIndex );
    bool isRectangle();
    void parseAdjacency(std::string adjacency,Region* reg);

};
#endif //EMPIRELEGENDS_MAPLOADER_H
