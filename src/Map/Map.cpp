//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"
// int name;
// int continent;
// int territory;   // Why were these included?
// bool land;
// bool rect;

// TERRITORY METHODS
// Constructors/Destructor
/**
 * default constructor
 */
Territory::Territory() {
    this->terr = new int{0};
    this->continent = new int{0};
}
/**
 * Territory constructor
 * @param name
 * @param continent
 */
Territory::Territory(int* terr, int* continent) {
    this->terr = terr;
    this->continent = continent;
}
/**
 * Copy Constructor
 * @param copy
 */
Territory::Territory(const Territory& copy) {
    this->terr = new int(*(copy.terr));
    this->continent = new int(*(copy.continent));
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
    this->terr = new int(*(t.terr));
    this->continent = new int(*(t.continent));
    return *this;
}
/**
 * Stream operator
 * @param out
 * @param r
 * @return
 */
std::ostream& operator << (std::ostream& out, const Territory& t){
    out << " Territory name: "<< *(t.terr) << " Continent: " << *(t.continent) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Territory& t){
    std::cout << "Territory name and Continent name"<< std::endl;
    in >> *(t.terr);
    in >> *(t.continent);
    return in;
}
// Accessors
/**
 * get territory name
 * @return
 */
int* Territory::getTerr() {
    return terr;
}
/**
 * get continent name
 * @return
 */
int* Territory::getContinent() {
    return continent;
}

// ------------------------
// ADJACENCY METHODS
// Constructors/Destructor
/**
 * Default constructor
 */
Adjacency::Adjacency() {
    this->adjTerr = new int{0};
    this->isLandRoute = new bool{false};
}
/**
 * constructor
 * @param territory
 * @param land
 */
Adjacency::Adjacency(int* territory, bool* isLandRoute) {
    this->adjTerr = territory;
    this->isLandRoute = isLandRoute;
}
/**
 * Copy Constructor
 * @param copy
 */
Adjacency::Adjacency(const Adjacency& copy) {
    this->adjTerr = new int(*(copy.adjTerr));
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
Adjacency& Adjacency::operator =(const Adjacency& adj){
    this->adjTerr = new int(*(adj.adjTerr));
    this->isLandRoute = new bool(*(adj.isLandRoute));
    return *this;
}
/**
 * stream operators
 * @param out
 * @param a
 * @return
 */
std::ostream& operator << (std::ostream& out, const Adjacency& adj){
    out << " Territory: "<< *(adj.adjTerr) << " Land: " << *(adj.isLandRoute) << std::endl;
    return out;
}
std::istream& operator >> (std::istream& in, Adjacency& adj){
    std::cout << "Enter territory name and land type"<< std::endl;
    in >> *(adj.adjTerr);
    in >> *(adj.isLandRoute);
    return in;
}
// Accessors
/**
 * get adjacent territory
 * @return
 */
int* Adjacency::getAdjTerr() {
    return adjTerr;
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
bool Map::territoryExists(int* terr) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        if (*(*terrIt).first->getTerr() == *(terr)) {
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
bool Map::isConnected(int* terr) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getAdjTerr()) == *(terr)){
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
void Map::addTerritory(Territory* terr) {
    vector<Adjacency>* adj = new vector<Adjacency>();
    vector<terrInfo>::iterator i;
    for (i = (terrs)->begin(); i != (terrs)->end(); ++i) {
        if (*(*i).first->getTerr() == *(terr->getTerr())) {
            cout << "Territory already exists" << endl;
            exit(1);
        }
    }
    terrs->push_back(make_pair(terr, adj));
}
/**
 * Adds adjacency to connect a territory to other terrs
 * verifies there are not duplicate edges
 * verifies a territory is not connected to itself
 * @param territory
 * @param adjacency
 */
void Map::addAdjacency(Territory* terr, Adjacency* adj) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        if (*(*terrIt).first->getTerr() == *(terr->getTerr())) {
            vector<Adjacency>::iterator adjIt;
            for(adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                if(*(adjIt->getAdjTerr()) == *adj->getAdjTerr() && *(adjIt->getIsLandRoute()) == *adj->getIsLandRoute()){
                    cout << "Edge already exists for the territory" << endl;
                    exit(1);
                }
                if(*(adjIt->getAdjTerr()) == *terr->getTerr()){
                    cout << *(adjIt->getAdjTerr()) << *terr->getTerr() << endl;
                    cout << "Edge cannot connect to itself" << endl;
                    exit(1);
                }
            }
            (*terrIt).second->push_back(*(adj));
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
            if(*(adjIt->getAdjTerr()) == *(terr)){
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
            if (!territoryExists(adjIt->getAdjTerr())) {
                removeAdjacency(adjIt->getAdjTerr());
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
        cout << "territory:" << *(*terrIt).first->getTerr() << " continent:" << *(*terrIt).first->getContinent() << " adjacency:";
            vector<Adjacency>::iterator adjIt;
            for(adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                cout << "(" << *(adjIt->getAdjTerr()) << ",";
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
            if(!territoryExists(adjIt->getAdjTerr())){
                cout << "Invalid Map! Territory " << *(*terrIt).first->getTerr()
                << " connects to another territory that does not exist" << endl;
                exit(1);
            }
        }
        //check if territory is connected to rest of graph
        if(!isConnected((*terrIt).first->getTerr())){
            cout << "Invalid Map! map does not connect territory " << *(*terrIt).first->getTerr() << endl;
            exit(1);
        }
    }
}
