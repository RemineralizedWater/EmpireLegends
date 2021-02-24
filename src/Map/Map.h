//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once
#include <vector>
#include <iostream>

using std::vector;
using std::pair;
using std::cout;
using std::endl;

class Territory {
private:
    int* name;
    int* continent;

public:
    Territory();
    Territory(int* name, int* continent);
    Territory(const Territory& copy);
    //~Territory();     // Doesn't fix leak

    Territory& operator =(const Territory& terr);
    friend std::ostream& operator << (std::ostream& out, const Territory& terr);
    friend std::istream& operator >> (std::istream& in, Territory& terr);

    int* getName();
    int* getContinent();
};

class Adjacency {
private:
    int* terr;
    bool* isLandRoute;

public:
    Adjacency();
    Adjacency(int* territory, bool* isLandRoute);
    Adjacency(const Adjacency& copy);
    //~Adjacency();     // Doesn't fix leak

    Adjacency& operator =(const Adjacency& adj);
    friend std::ostream& operator << (std::ostream& out, const Adjacency& a);
    friend std::istream& operator >> (std::istream& in, Adjacency& a);

    bool* getIsLandRoute();
    int* getTerritory();
};


class Map {
private:
    bool* rect;
    typedef pair<Territory*, vector<Adjacency>*> terrInfo;     // TODO Type pair?
    vector<terrInfo>* terrs;
    bool territoryExists(int* terr);
    bool isConnected(int* terr);

public:
    Map();
    Map(bool* rect);
    Map(const Map& copy);
    ~Map();

    Map& operator =(const Map& map);
    friend std::ostream& operator << (std::ostream& out, const Map& map);
    friend std::istream& operator >> (std::istream& in, Map& map);

    void addTerritory(Territory* terr);
    void addAdjacency(Territory* terr, Adjacency* adj);
    void display();
    void validate();
    void removeAdjacency(int* terr);
    void removeUnUsedAdjacency();
};
