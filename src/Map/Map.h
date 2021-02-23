//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Territory {
private:
    int* name;
    int* continent;

public:
    Territory(int* name, int* continent);
    Territory();
    Territory(const Territory &copy);
    int* getName();
    int* getContinent();
   Territory & operator =(const Territory &r);
    friend std::ostream & operator << (std::ostream &out, const Territory &r);
    friend std::istream & operator >> (std::istream &in, Territory &r);
};

class Adjacency {
private:
    int* territory;
    bool* land;

public:
    Adjacency(int* territory,bool* land);
    Adjacency();
    bool* getLand();
    int* getTerritory();
    Adjacency & operator =(const Adjacency &a);
    friend std::ostream & operator << (std::ostream &out, const Adjacency &a);
    friend std::istream & operator >> (std::istream &in, Adjacency &a);
};


class Map {
private:
    typedef pair<Territory*, vector<Adjacency>*> territoryInfo;
    vector<territoryInfo> *terrs;
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