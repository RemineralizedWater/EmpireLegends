//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"

// DONEDONE
Territory& Territory::operator=(const Territory& rightSide) { // assignment operator // DONEDONE
    army = rightSide.army;
    terrId = rightSide.terrId;
    return *this;
}
std::ostream& operator<<(std::ostream& os, Territory& terr) { // output stream operator // DONEDONE
    os << "Territory ID: " << terr.getTerrId();
    return os;
}

Territory::Territory(int terrId) { // constructor // DONEDONE
    this->army = 0;
    this->adj.push_back(this);
    this->terrId = terrId;
}
Territory::Territory(const Territory& rightSide) { // copy constructor // DONEDONE
    terrId = rightSide.terrId;
}
Territory::~Territory() { // destructor // DONEDONE
    ; // delete pointers here
}

// Accessors // DONEDONE
void Territory::setArmy(int army) {
    this->army = army;
}
void Territory::setAdj(Territory* terr) { // DONEDONE
    terr->adj.push_back(this);
    this->adj.push_back(terr);
}
void Territory::setTerrId(int terrId) {
    this->terrId = terrId;
}
// Mutators // DONEDONE
int Territory::getArmy() {
    return army;
}
std::vector<Territory*> Territory::getAdj() {
    return this->adj;
}
int Territory::getTerrId() {
    return terrId;
}

// ------------------------

// DONEDONE
Continent& Continent::operator=(const Continent& rightSide) { // assignment operator // DONEDONE
    contId = rightSide.contId;
    return *this;
}
std::ostream& operator<<(std::ostream& os, Continent& cont) { // output stream operator // DONEDONE
    os << "Continent ID: " << cont.getContId();
    return os;
}

Continent::Continent(int contId) { // constructor // DONEDONE
    this->contId = contId;
}
Continent::Continent(const Continent& rightSide) { // copy constructor // DONEDONE
    contId = rightSide.contId;
}
Continent::~Continent() { // destructor // DONEDONE
    ; // delete pointers here
}

// Accessors // DONEDONE
void Continent::setContId(int contId) {
    this->contId = contId;
}
// Mutators // DONEDONE
int Continent::getContId() {
    return contId;
}


// ------------------

Map& Map::operator=(const Map& rightSide) { // assignment operator // DONEDONE
    adjList = rightSide.adjList;
    return *this;
}
std::ostream& operator<<(std::ostream& os, Map& map) { // output stream operator // DONEDONE
    os << "Map ID: " << map.getMapId();
    return os;
}

Map::Map(int mapId) { // constructor // DONEDONE
    this->mapId = mapId;
}
Map::Map(const Map& rightSide) { // copy constructor // DONEDONE
    mapId = rightSide.mapId;
}
Map::~Map() { // destructor // DONEDONE
    ; // delete pointers here
}

// Accessors // DONEDONE
void Map::setMapId(int mapId) {
    this->mapId = mapId;
}
// Mutators // DONEDONE
int Map::getMapId() {
    return mapId;
}