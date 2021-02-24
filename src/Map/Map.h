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
    Territory(const Territory &rightSide);
    //~Territory();     // Doesn't fix leak

   Territory& operator =(const Territory &r);
    friend std::ostream& operator << (std::ostream &out, const Territory &r);
    friend std::istream& operator >> (std::istream &in, Territory &r);

    int* getName();
    int* getContinent();
};

class Adjacency {
private:
    int* territory;
    bool* land;

public:
    Adjacency(int* territory,bool* land);
    Adjacency();
    //~Adjacency();     // Doesn't fix leak

    Adjacency& operator =(const Adjacency &a);
    friend std::ostream& operator << (std::ostream &out, const Adjacency &a);
    friend std::istream& operator >> (std::istream &in, Adjacency &a);

    bool* getLand();
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

    void addTerritory(Territory* territory);
    void addAdjacency(Territory* territory,Adjacency* adjacency);
    void display();
    void validate();
    void removeAdjacency(int* territory);
    void removeUnUsedAdjacency();
    Map & operator =(const Map &m);
    friend std::ostream & operator << (std::ostream &out, const Map &m);
    friend std::istream & operator >> (std::istream &in, Map &m);
};