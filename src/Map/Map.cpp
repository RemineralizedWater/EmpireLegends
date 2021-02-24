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
 * @param name
 * @param continent
 */
Territory::Territory(int* terr, int* continent) {
    this->terrId = terr;
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
 * @param r
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
 * @param r
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
 * get territory name
 * @return
 */
int* Territory::getTerrId() {
    return terrId;
}
/**
 * get continent name
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
 * @param territory
 * @param land
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
std::ostream& operator << (std::ostream& out, const Adjacency& adj){
    out << " Territory: "<< *(adj.adjId) << " Land: " << *(adj.isLandRoute) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Adjacency& adj){
    std::cout << "Enter territory name and land type"<< std::endl;
    in >> *(adj.adjId);
    in >> *(adj.isLandRoute);
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
    terrs = new vector<terrInfo>;
}
/**
 * constructor: takes board shape
 * @param rect
 */
Map::Map(bool* rect) {
    this->rect = rect;
    terrs = new vector<terrInfo>;
}
/**
 * copy constructor
 * @param copy
 */
Map::Map(const Map& copy){
    this->rect = new bool(*(copy.rect));
    this->terrs = new vector<terrInfo> (*(copy.terrs));
}
/**
 * destructor
 */
Map::~Map() {
    delete terrs;
    terrs = nullptr;
}
// Operators
/**
 * Assignment operator
 * @param m
 * @return
 */
Map& Map::operator =(const Map& map){
    this->rect = new bool(*(map.rect));
    this->terrs = new vector<terrInfo>(*(map.terrs));
    return *this;
}
/**
 * Stream operators
 * @param out
 * @param m
 * @return
 */
std::ostream& operator << (std::ostream& out, const Map& map){
    out << " Rectangle: " << *(map.rect) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Map& map){
    std::cout << "Is map shape rectangle?" << std::endl;
    in >> *(map.rect);
    return in;
}
// Private Methods
/**
 * Check if territory is currently in graph
 * @param territory
 * @return
 */
bool Map::territoryExists(int* terrId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        if (*(*terrIt).first->getTerrId() == *(terrId)) {
            return true;
        }
    }
    return false;
}
/**
 * Checks if a territory is connected to rest of graph by checking if any other territory has it listed as an adjacency
 * @param territory
 * @return
 */
bool Map::isConnected(int* terrId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getAdjId()) == *(terrId)){
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
 * @param territory
 */
void Map::addTerritory(Territory* t) {
    vector<Adjacency>* adj = new vector<Adjacency>();
    vector<terrInfo>::iterator i;
    for (i = (terrs)->begin(); i != (terrs)->end(); ++i) {
        if (*(*i).first->getTerrId() == *(t->getTerrId())) {
            cout << "Territory already exists" << endl;
            exit(1);
        }
    }
    terrs->push_back(make_pair(t, adj));
}
/**
 * Adds adjacency to connect a territory to other terrs
 * verifies there are not duplicate edges
 * verifies a territory is not connected to itself
 * @param territory
 * @param adjacency
 */
void Map::addAdjacency(Territory* t, Adjacency* a) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
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
 * @param territory
 */
void Map::removeAdjacency(int* terr) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = terrIt->second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getAdjId()) == *(terr)){
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
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
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
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
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
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
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
            cout << "Invalid Map! map does not connect territory " << *(*terrIt).first->getTerrId() << endl;
            exit(1);
        }
    }
}
