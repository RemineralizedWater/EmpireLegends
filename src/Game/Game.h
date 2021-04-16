#pragma once

#include <iostream>
#include "../Map/Map.h"
#include "../Map Loader/MapLoader.h"
#include "../Player/Player.h"

class Game {
private:
    int numberOfPlayers;

public:
    Game();

    Game(int numberOfPlayers_);

    Game(const Game &copy);

    ~Game();

    Game &operator=(const Game &gs);

    friend std::ostream &operator<<(std::ostream &out, const Game &gs);

    friend std::istream &operator>>(std::istream &in, Game &ml);

    Deck* CreateDeck();

    vector<Player*> CreatePlayers(int startingPoint);

    bool Tied(vector<Player *> players, int &winner);  // TODO, WHY int &winner?

    bool CountMoney(vector<Player *>players);

    bool CountArmies(vector<Player *>players, Map* map);

    bool CountControlledTerritories(vector<Player *> players, Map *map);

    Map* SelectMap(bool &validMap);  // bool &validMap pass by reference
};
