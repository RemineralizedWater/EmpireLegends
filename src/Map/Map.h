//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once
#include <vector>
#include <iostream>

using namespace std;

// DONEDONE
class Region {
private:
    int* name;
    int* continent;

public:
    Region(int* name,int* continent);
    Region();
    int* getName();
    int* getContinent();
    ~Region();
};

class Adjacency {
private:
    int* region;
    bool* land;

public:
    Adjacency(int* region,bool* land);
    Adjacency();
    bool* getLand();
    int* getRegion();
    ~Adjacency();
};


class Map {
private:
    typedef pair<Region*, vector<Adjacency>*> regionInfo;
    vector<regionInfo> *regions;
    bool regionExists(int* region);
    bool isConnected(int* region);
    bool* rect;
public:
    Map(bool* rect);
    Map();
    ~Map();
    void addRegion(Region* region);
    void addAdjacency(Region* region,Adjacency* adjacency);
    void display();
    void validate();
};