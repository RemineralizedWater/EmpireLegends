//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"

// TERRITORY METHODS
// Constructors/Destructor
/**
 * default constructor
 */
Territory::Territory() {
    this->terrId = new int{0};
    this->continentId = new int{0};
}
/**
 * Territory constructor
 * @param terrId
 * @param continent
 */
Territory::Territory(int* terrId, int* continent) {
    this->terrId = terrId;
    this->continentId = continent;
}
/**
 * Copy Constructor
 * @param copy
 */
Territory::Territory(const Territory& copy) {
    this->terrId = new int(*(copy.terrId));
    this->continentId = new int(*(copy.continentId));
}
/**
 * destructor
 */
/*Territory::~Territory() {     // Doesn't fix leak
    delete name;
    name = nullptr;
    delete continent;
    continent = nullptr;
}*/
// Operators
/**
 * Assignment operator
 * @param t
 * @return
 */
Territory& Territory::operator =(const Territory& t){
    this->terrId = new int(*(t.terrId));
    this->continentId = new int(*(t.continentId));
    return *this;
}
/**
 * Stream operator
 * @param out
 * @param t
 * @return
 */
std::ostream& operator << (std::ostream& out, const Territory& t){
    out << " Territory name: "<< *(t.terrId) << " Continent: " << *(t.continentId) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Territory& t){
    std::cout << "Territory name and Continent name"<< std::endl;
    in >> *(t.terrId);
    in >> *(t.continentId);
    return in;
}
// Accessors
/**
 * get territory id
 * @return
 */
int* Territory::getTerrId() {
    return terrId;
}
/**
 * get continent id
 * @return
 */
int* Territory::getContinent() {
    return continentId;
}

// ------------------------
// ADJACENCY METHODS
// Constructors/Destructor
/**
 * Default constructor
 */
Adjacency::Adjacency() {
    this->adjId = new int{0};
    this->isLandRoute = new bool{false};
}
/**
 * constructor
 * @param adjId
 * @param isLandRoute
 */
Adjacency::Adjacency(int* adjId, bool* isLandRoute) {
    this->adjId = adjId;
    this->isLandRoute = isLandRoute;
}
/**
 * Copy Constructor
 * @param copy
 */
Adjacency::Adjacency(const Adjacency& copy) {
    this->adjId = new int(*(copy.adjId));
    this->isLandRoute = new bool(*(copy.isLandRoute));
}
/**
 * destructor
 */
/*Adjacency::~Adjacency() {     // Doesn't fix leak
    delete territory;
    territory = nullptr;
    delete land;
    land = nullptr;
}*/
// Operators
/**
 * Assignment operator
 * @param a
 * @return
 */
Adjacency& Adjacency::operator =(const Adjacency& a){
    this->adjId = new int(*(a.adjId));
    this->isLandRoute = new bool(*(a.isLandRoute));
    return *this;
}
/**
 * stream operators
 * @param out
 * @param a
 * @return
 */
std::ostream& operator << (std::ostream& out, const Adjacency& a){
    out << " Territory: "<< *(a.adjId) << " Land: " << *(a.isLandRoute) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Adjacency& a){
    std::cout << "Enter territory name and land type"<< std::endl;
    in >> *(a.adjId);
    in >> *(a.isLandRoute);
    return in;
}
// Accessors
/**
 * get adjacent territory
 * @return
 */
int* Adjacency::getAdjId() {
    return adjId;
}
/**
 * get route type ex. land or water
 * @return
 */
bool* Adjacency::getIsLandRoute() {
    return isLandRoute;
}

// ------------------------
// MAP METHODS
// Constructors/Destructors
/**
 * default constructor
 */
Map::Map() {
    this->rect = new bool{false};
    terrAndAdjsList = new vector<terrInfo>;
}
/**
 * constructor: takes board shape
 * @param rect
 */
Map::Map(bool* rect) {
    this->rect = rect;
    terrAndAdjsList = new vector<terrInfo>;
}
/**
 * copy constructor
 * @param copy
 */
Map::Map(const Map& copy){
    this->rect = new bool(*(copy.rect));
    this->terrAndAdjsList = new vector<terrInfo> (*(copy.terrAndAdjsList));
}
/**
 * destructor
 */
Map::~Map() {
    delete terrAndAdjsList;
    terrAndAdjsList = nullptr;
}
// Operators
/**
 * Assignment operator
 * @param m
 * @return
 */
Map& Map::operator =(const Map& m){
    this->rect = new bool(*(m.rect));
    this->terrAndAdjsList = new vector<terrInfo>(*(m.terrAndAdjsList));
    return *this;
}
/**
 * Stream operators
 * @param out
 * @param m
 * @return
 */
std::ostream& operator << (std::ostream& out, const Map& m){
    out << " Rectangle: " << *(m.rect) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Map& m){
    std::cout << "Is map shape rectangle?" << std::endl;
    in >> *(m.rect);
    return in;
}
// Private Methods
/**
 * Check if territory is currently in graph
 * @param adjId
 * @return
 */
bool Map::territoryExists(int* adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if (*(*terrIt).first->getTerrId() == *(adjId)) {
            return true;
        }
    }
    return false;
}
/**
 * Check if continent is currently in graph
 * @param continent
 * @return
 */
bool Map::continentExists(int* continent) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if (*(*terrIt).first->getContinent() == *(continent)) {
            return true;
        }
    }
    return false;
}
/**
 * Checks if a territory is connected to rest of graph by checking if any other territory has it listed as an adjacency
 * @param adjId
 * @return
 */
bool Map::isConnected(int* adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getAdjId()) == *(adjId)){
                return true;
            }
        }
    }
    return false;
}
// Public Methods
/**
 * Adds a territory to a graph
 * Makes sure there is no duplicate territory eliminating need to validate if a territory belongs to one continent
 * @param t
 */
void Map::addTerritory(Territory* t) {
    vector<Adjacency>* adj = new vector<Adjacency>();
    if (territoryExists(t->getTerrId()) == *(t->getTerrId())) {
        cout << "Territory already exists. Territory belongs to more than one continent. Invalid Map!" << endl;
        /*if (continentExists(t->getContinent()) == *(t->getContinent())) {
            cout << "Territory belongs to more than one continent. Invalid Map!" << endl;
        }*/
        exit(1);
    }
    terrAndAdjsList->push_back(make_pair(t, adj));
}
/**
 * Adds adjacency to connect a territory to other terrs
 * verifies there are not duplicate edges
 * verifies a territory is not connected to itself
 * @param t
 * @param a
 */
void Map::addAdjacency(Territory* t, Adjacency* a) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if (*(*terrIt).first->getTerrId() == *(t->getTerrId())) {
            vector<Adjacency>::iterator adjIt;
            for(adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                if(*(adjIt->getAdjId()) == *a->getAdjId() && *(adjIt->getIsLandRoute()) == *a->getIsLandRoute()){
                    cout << "Edge already exists for the territory" << endl;
                    exit(1);
                }
                if(*(adjIt->getAdjId()) == *t->getTerrId()){
                    cout << *(adjIt->getAdjId()) << *t->getTerrId() << endl;
                    cout << "Edge cannot connect to itself" << endl;
                    exit(1);
                }
            }
            (*terrIt).second->push_back(*(a));
            break;
        }
    }
}
/**
 * removes any adjacency that contains the territory
 * @param adjId
 */
void Map::removeAdjacency(int* adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = terrIt->second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getAdjId()) == *(adjId)){
                terrIt->second->erase(adjIt);
                return;
            }
        }
    }
}
/**
 * removes unused adjacency
 */
void Map::removeUnUsedAdjacency() {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        //check if all terrs listed in adjacency are also listed as terrs
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (!territoryExists(adjIt->getAdjId())) {
                removeAdjacency(adjIt->getAdjId());
                return;
            }
        }
    }
}
/**
 * displays contents in graph
 */
void Map::display(){
    cout << "______________________________________________________________________________" << endl << "Displaying Board Map"
    << endl << "______________________________________________________________________________" << endl;
    if(*(rect)){
        cout << " Map shape: Rectangle" << endl;
    }
    else{
        cout << "Map shape: L-shape" << endl;
    }
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        cout << "territory:" << *(*terrIt).first->getTerrId() << " continent:" << *(*terrIt).first->getContinent() << " adjacency:";
            vector<Adjacency>::iterator adjIt;
            for(adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                cout << "(" << *(adjIt->getAdjId()) << ",";
                if(!*(adjIt->getIsLandRoute())){
                    cout << "W" << ") ";
                }
                else if(*(adjIt->getIsLandRoute())){
                    cout << "L" << ") ";
                }
            }
        cout << endl;
    }
    cout << "__________________________________________________________________________" << endl;
}
/**
 * checks the map is a connected graph and each territory listed as an adjacency exists
 **/
void Map::validate() {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;

        //check if all terrs listed in adjacency are also listed as terrs
        for(adjIt=(*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
            if(!territoryExists(adjIt->getAdjId())){
                cout << "Invalid Map! Territory " << *(*terrIt).first->getTerrId()
                << " connects to another territory that does not exist" << endl;
                exit(1);
            }
        }
        //check if territory is connected to rest of graph
        if(!isConnected((*terrIt).first->getTerrId())){
            cout << "Invalid Map! Map does not connect territory " << *(*terrIt).first->getTerrId() << endl;
            exit(1);
        }
    }
}
