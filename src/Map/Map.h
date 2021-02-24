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
    int* terrId;
    int* continentId;

public:
    Territory();
    Territory(int* terrId, int* continentId);
    Territory(const Territory& copy);
    //~Territory();     // Doesn't fix leak

    Territory& operator =(const Territory& t);
    friend std::ostream& operator << (std::ostream& out, const Territory& t);
    friend std::istream& operator >> (std::istream& in, Territory& t);

    int* getTerrId();
    int* getContinent();
};

class Adjacency {
private:
    int* adjId;
    bool* isLandRoute;

public:
    Adjacency();
    Adjacency(int* adjId, bool* isLandRoute);
    Adjacency(const Adjacency& copy);
    //~Adjacency();     // Doesn't fix leak

    Adjacency& operator =(const Adjacency& adj);
    friend std::ostream& operator << (std::ostream& out, const Adjacency& a);
    friend std::istream& operator >> (std::istream& in, Adjacency& a);

    int* getAdjId();
    bool* getIsLandRoute();
};

/*
class terrAndAdjs {
private:
    Territory* terrWithAdjs;
    vector<Adjacency>* adjsForTerr;
public:
    Map();
    Map(bool* rect);
    Map(const Map& copy);
    ~Map();

    Map& operator =(const Map& map);
    friend std::ostream& operator << (std::ostream& out, const Map& map);
    friend std::istream& operator >> (std::istream& in, Map& map);

    int* getAdjTerr();
    bool* getIsLandRoute();
};
 */


class Map {
private:
    bool* rect;
    typedef pair<Territory*, vector<Adjacency>*> terrInfo;     // typedef keyword allows new names for types, pair holds two & had constructor/destructor
    //struct terrInfo {Territory* terr; vector<Adjacency>* adj;};     // TODO Change typedef pair to struct? Need init?
    vector<terrInfo>* terrs;
    //vector<Territory*, vector<Adjacency>*>* terrs;
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
