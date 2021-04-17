//
// Created by RemineralizedWater on 2021-02-21.
//

#pragma once

#include <vector>
#include <iostream>
#include <map>
#include "memory"
#include "../Subject.h"

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::string;

class Territory {
private:
    int terrId;
    int continentId;
    std::map<string, int> armySizeForPlayer;  // <player, armySize>
    std::map<string, bool> hasCityForPlayer;  // <player, hasCity>

public:
    Territory();

    Territory(int terrId_,
              int continentId_,
              std::map<string, int> armySizeForPlayer_,
              std::map<string, bool> hasCityForPlayer_
    );

    Territory(int terrId_, int continentId_);

    Territory(const Territory &copy);

    ~Territory();

    Territory &operator=(const Territory &t);

    friend std::ostream &operator<<(std::ostream &out, const Territory &t);

    friend std::istream &operator>>(std::istream &in, Territory &t);

    int GetTerrId();

    int GetContinent();

    int GetNumberOfArmies(string playerName);

    bool HasCity(string playerName);

    bool HasArmies(string playerName);

    std::map<string, int> &GetArmySizeForPlayer();

    void AddArmySizeForPlayer(string playerName, int amount);

    void RemoveArmySizeForPlayer(string playerName, int amount);

    void AddCityForPlayer(string playerName);

    std::map<string, bool> &GetHasCity();

    void InsertNewArmyPlayerMapping(string playerName);

    void InsertNewCityPlayerMapping(string playerName);
};

class Adjacency {
private:
    int adjId;
    bool isLandRoute;

public:
    Adjacency();

    Adjacency(int adjId_, bool isLandRoute_);

    Adjacency(const Adjacency &copy);

    ~Adjacency();

    Adjacency &operator=(const Adjacency &adj);

    friend std::ostream &operator<<(std::ostream &out, const Adjacency &a);

    friend std::istream &operator>>(std::istream &in, Adjacency &a);

    int GetAdjId();

    bool GetIsLandRoute();
};


class Map : public Subject {
private:
    bool rectangle;
    // typedef keyword allows new names for types; pair holds two variables & has auto constructor/destructor
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo> *terrAndAdjsList;
    int startingPoint;

    bool TerritoryExists(int adjId_);

    bool ContinentExists(int continentId_);

    bool IsConnected(int adjId_);

public:
    Map();

    Map(bool rectangle_);

    Map(const Map &copy);

    ~Map();

    Map &operator=(const Map &m);

    friend std::ostream &operator<<(std::ostream &out, const Map &m);

    friend std::istream &operator>>(std::istream &in, Map &m);

    int GetStartingPoint();

    int GetMapSize();

    vector<terrInfo>* GetTerrAndAdjsList();

    void SetStartingPoint(int terrId_);

    bool AddTerritory(Territory *t);

    bool AddAdjacency(Territory *t, Adjacency *a);

    void RemoveAdjacency(int adjId_);

    Territory *FindTerritory(int terrId_);

    void Display();

    bool Validate();
};
