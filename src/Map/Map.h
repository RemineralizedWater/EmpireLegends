//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once

#include <vector>
#include <iostream>
#include <map>
#include "memory"

using std::vector;
using std::pair;
using std::cout;
using std::endl;

class Territory {
private:
    Territory(int *terrId, int *continent);

    int *terrId;
    int *continentId;
    std::unique_ptr<std::map<std::string, int>> armySizeForPlayer_;
    std::unique_ptr<std::map<std::string, bool>> hasCity;

public:
    Territory();

    Territory(int *terrId,
              int *continentId,
              const std::map<std::string, int> &armySizeForPlayer,
              const std::map<std::string, bool> &hasCity
    );

    Territory(const Territory &copy);

    ~Territory();

    Territory &operator=(const Territory &t);

    friend std::ostream &operator<<(std::ostream &out, const Territory &t);

    friend std::istream &operator>>(std::istream &in, Territory &t);

    int *getTerrId();

    int *getContinent();

     std::map<std::string, int> &getArmySizeForPlayer();
     std::map<std::string, bool> &getHasCity();


};

class Adjacency {
private:
    int *adjId;
    bool *isLandRoute;

public:
    Adjacency();

    Adjacency(int *adjId, bool *isLandRoute);

    Adjacency(const Adjacency &copy);

    ~Adjacency();

    Adjacency &operator=(const Adjacency &adj);

    friend std::ostream &operator<<(std::ostream &out, const Adjacency &a);

    friend std::istream &operator>>(std::istream &in, Adjacency &a);

    int *getAdjId();

    bool *getIsLandRoute();
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

    Territory* getTerrWithAdjs();
    vector<Adjacency>* getAdjsForTerr();
};
 */


class Map {
private:
    bool *rect;
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;     // typedef keyword allows new names for types, pair holds two & had constructor/destructor
    vector<terrInfo> *terrAndAdjsList;

    //struct terrInfo {Territory* terr; vector<Adjacency>* adj;};     // TODO Change typedef pair to struct? Need init?
    //vector<Territory*, vector<Adjacency>*>* terrs;
    bool territoryExists(int *adjId);

    bool continentExists(int *continent);

    bool isConnected(int *adjId);

public:
    Map();

    Map(bool *rect);

    Map(const Map &copy);

    ~Map();

    Map &operator=(const Map &m);

    friend std::ostream &operator<<(std::ostream &out, const Map &m);

    friend std::istream &operator>>(std::istream &in, Map &m);

    void addTerritory(Territory *t);

    void addAdjacency(Territory *t, Adjacency *a);

    void display();

    void validate();

    void removeAdjacency(int *adjId);

    void removeUnUsedAdjacency();
};
