//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Region {
private:
    int* name;
    int* continent;

public:
    Region(int* name,int* continent);
    Region();
    Region(Region &copy);
    int* getName();
    int* getContinent();
   Region & operator =(const Region &r);
    friend std::ostream & operator << (std::ostream &out, const Region &r);
    friend std::istream & operator >> (std::istream &in, Region &r);
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
    Adjacency & operator =(const Adjacency &a);
    friend std::ostream & operator << (std::ostream &out, const Adjacency &a);
    friend std::istream & operator >> (std::istream &in, Adjacency &a);
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
    Map(Map &copy);
    ~Map();
    void addRegion(Region* region);
    void addAdjacency(Region* region,Adjacency* adjacency);
    void display();
    void validate();
    void removeAdjacency(int* region);
    void removeUnUsedAdjacency();
    Map & operator =(const Map &m);
    friend std::ostream & operator << (std::ostream &out, const Map &m);
    friend std::istream & operator >> (std::istream &in, Map &m);
};