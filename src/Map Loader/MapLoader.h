//
// Created by 06spa on 2/8/2021.
//
#ifndef EMPIRELEGENDS_MAPLOADER_H
#define EMPIRELEGENDS_MAPLOADER_H
#include <iostream>
class MapLoader {
public:
    MapLoader();
    MapLoader(std::string mapFilePath, int numberOfPlayers);
    ~MapLoader();
    void loadMap(std::string mapFile,int numberOfBoardPieces,bool rectangle);
private:
    void verifyRegionName(std::string line,int currentIndex, int charIndex, std::string argErrMsg, std::string outRangeErrMsg);
    int checkNextFieldExists(std::string line,int currentIndex);
    bool isLand(std::string adjacency, int commaIndex, int currentIndex );
    bool isRectangle();
    void parseAdjacency(std::string adjacency);

};
#endif //EMPIRELEGENDS_MAPLOADER_H
