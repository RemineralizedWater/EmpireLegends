#ifndef EMPIRELEGENDS_GAME_H
#define EMPIRELEGENDS_GAME_H


#include <iostream>
#include "../Map/Map.h"
#include "../Map Loader/MapLoader.h"
#include "../Player/Player.h"

class Game {
public:
    Game();
    Game(int numberOfPlayers);
    Game(Game &copy);
    ~Game();
    Deck* createDeck();
    vector<Player*> createPlayers(int startingPoint);

    Map* selectMap(bool &validMap);
    Game & operator =(const Game &gs);
    friend std::ostream & operator << (std::ostream &out, const Game &gs);
    friend std::istream & operator >> (std::istream &in, Game &ml);
private:
    int* numberOfPlayers;
};


#endif //EMPIRELEGENDS_GAME_H
