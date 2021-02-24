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
    Territory(int* name, int* continent);
    Territory();
    Territory(const Territory& terr);
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
    Adjacency(int* territory, bool* land);
    Adjacency();
    //~Adjacency();     // Doesn't fix leak

    Adjacency& operator =(const Adjacency &a);
    friend std::ostream& operator << (std::ostream &out, const Adjacency& a);
    friend std::istream& operator >> (std::istream &in, Adjacency& a);

    bool* getIsLandRoute();
    int* getTerritory();
};


class Map {
private:
    typedef pair<Territory*, vector<Adjacency>*> terrInfo;     // TODO Type pair?
    vector<terrInfo> *terrs;
    bool territoryExists(int* territory);
    bool isConnected(int* territory);
    bool* rect;

public:
    Map(bool* rect);
    Map();
    Map(Map &copy);
    ~Map();

    Map & operator =(const Map &m);
    friend std::ostream & operator << (std::ostream &out, const Map &m);
    friend std::istream & operator >> (std::istream &in, Map &m);

    void addTerritory(Territory* territory);
    void addAdjacency(Territory* territory,Adjacency* adjacency);
    void display();
    void validate();
    void removeAdjacency(int* territory);
    void removeUnUsedAdjacency();
};