//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once
#include <vector>
#include <iostream>

using std::vector;

// DONEDONE
class Territory {
private:
    vector<Territory*> adj;
    int army;
    int terrId;

public:
    Territory& Territory::operator=(const Territory& rightSide);
    friend std::ostream& operator<<(std::ostream& os, Territory& terr);

    Territory(int terrId);
    Territory(const Territory& rightSide);
    ~Territory();

    void setArmy(int army);
    void setAdj(Territory* terr);
    void setTerrId(int terrId);
    int getArmy();
    vector<Territory*> getAdj();
    int getTerrId();
};

// -------------------

class Continent {
private:
    int contId;

public:
    Continent& Continent::operator=(const Continent& rightSide);
    friend std::ostream& operator<<(std::ostream& os, Continent& cont);

    Continent(int contId);
    Continent(const Continent& rightSide);
    ~Continent();

    void setContId(int contId);
    int getContId();
};

class Map {
private:
    int mapId;

public:
    Map& Map::operator=(const Map& rightSide);
    friend std::ostream& operator<<(std::ostream& os, Map& map);

    Map(int mapId);
    Map(const Map& rightSide);
    ~Map();

    void setMapId(int mapId);
    int getMapId();
};