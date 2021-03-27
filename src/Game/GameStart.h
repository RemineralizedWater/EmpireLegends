//
// Created by 06spa on 3/26/2021.
//

#ifndef EMPIRELEGENDS_GAMESTART_H
#define EMPIRELEGENDS_GAMESTART_H
#include <iostream>
#include "../Map/Map.h"
#include "../Map Loader/MapLoader.h"
#include "../Player/Player.h"

class GameStart {
public:
    GameStart();
    GameStart(int numberOfPlayers);
    GameStart(GameStart &copy);
    ~GameStart();
    vector<Player*> createPlayers();

    Map* selectMap(bool &validMap);
    GameStart & operator =(const GameStart &gs);
    friend std::ostream & operator << (std::ostream &out, const GameStart &gs);
    friend std::istream & operator >> (std::istream &in, GameStart &ml);
private:
    int* numberOfPlayers;
    /*std::string* mapFilePath;
   int* numberOfBoardPieces;
   bool* rectangle;
   Map* map;

   bool verifyId(std::string string_id, int &int_id, std::string argErrMsg,std::string outRangeErrMsg);
   bool isLand(std::string adjacency, int commaIndex, int currentIndex, bool &land );
   bool checkNextFieldExists(std::string line,int &currentIndex);
   bool isRectangle();
   bool parseAdjacency(std::string adjacency, Territory* territory);*/

};


#endif //EMPIRELEGENDS_GAMESTART_H
