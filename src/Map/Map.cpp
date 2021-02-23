//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"
int name;
int continent;
int territory;
bool land;
bool rect;
/**
 * Territory constructor
 * @param name
 * @param continent
 */
Territory::Territory(int* name,int* continent) {
    this->name = name;
    this->continent=continent;
}
/**
 * get territory name
 * @return
 */
int * Territory::getName() {
    return name;
}
/**
 * get continent name
 * @return
 */
int * Territory::getContinent() {
    return continent;
}
 /**
  * default constructor
  */
Territory::Territory() {
     this->name = new int{0};
     this->continent= new int{0};
}
// ------------------------
/**
 * get adjacent territory
 * @return
 */
int * Adjacency::getTerritory() {
    return territory;
}
/**
 * get route type ex. land or water
 * @return
 */
bool * Adjacency::getLand() {
    return land;
}
/**
 * Default constructor
 */
Adjacency::Adjacency() {
    this->territory=new int{0};
    this->land=new bool{false};
}
/**
 * constructor
 * @param territory
 * @param land
 */
Adjacency::Adjacency(int *territory, bool *land) {
    this->territory=territory;
    this->land=land;
}
/**
 * Check if territory is currently in graph
 * @param territory
 * @return
 */
bool Map::territoryExists(int *territory) {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        if (*(*terrIt).first->getName() == *(territory)) {
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
bool Map::isConnected(int *territory) {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getTerritory())==*(territory)){
                return true;
            }
        }
    }
    return false;
}
/**
 * removes unused adjacency
 */
void Map::removeUnUsedAdjacency() {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        //check if all terrs listed in adjacency are also listed as terrs
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (!territoryExists(adjIt->getTerritory())) {
                removeAdjacency(adjIt->getTerritory());
                return;
            }
        }
    }
}
/**
 * removes any adjacency that contains the territory
 * @param territory
 */
void Map::removeAdjacency(int *territory) {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = terrIt->second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if(*(adjIt->getTerritory())==*(territory)){
                terrIt->second->erase(adjIt);
                return;
            }
        }
    }
}
/**
 * checks the map is a connected graph and each territory listed as an adjacency exists
 **/
void Map::validate() {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;

        //check if all terrs listed in adjacency are also listed as terrs
        for(adjIt=(*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
            if(!territoryExists(adjIt->getTerritory())){
                cout<<"Invalid Map! Territory "<<*(*terrIt).first->getName()<< " connects to another territory that does not exist"<<endl;
                exit(1);
            }
        }
        //check if territory is connected to rest of graph
        if(!isConnected((*terrIt).first->getName())){
            cout<<"Invalid Map! map does not connect territory "<<*(*terrIt).first->getName() <<endl;
            exit(1);
        }
    }
}
/**
 * Adds adjacency to connect a territory to other terrs
 * verifies there are not duplicate edges
 * verifies a territory is not connected to itself
 * @param territory
 * @param adjacency
 */
void Map::addAdjacency(Territory *territory, Adjacency *adjacency) {
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        if (*(*terrIt).first->getName() == *(territory->getName())) {
            vector<Adjacency>::iterator adjIt;
            for(adjIt=(*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                if(*(adjIt->getTerritory()) == *adjacency->getTerritory() && *(adjIt->getLand()) == *adjacency->getLand()){
                    cout<<"Edge already exists for the territory"<<endl;
                    exit(1);
                }
                if(*(adjIt->getTerritory()) == *territory->getName()){
                    cout<<*(adjIt->getTerritory())<<*territory->getName()<<endl;
                    cout<<"Edge cannot connect to itself"<<endl;
                    exit(1);
                }
            }
            (*terrIt).second->push_back(*(adjacency));
            break;
        }
    }
}
/**
 * displays contents in graph
 */
void Map::display(){
    cout<<"______________________________________________________________________________"<<endl<<"Displaying Board Map"<<endl<<"______________________________________________________________________________"<<endl;
    if(*(rect)){
        cout<<"Map shape: Rectangle"<<endl;
    }
    else{
        cout<<"Map shape: L-shape"<<endl;
    }
    vector<territoryInfo>::iterator terrIt;
    for (terrIt = (terrs)->begin(); terrIt != (terrs)->end(); ++terrIt) {
        cout<<"territory:"<<*(*terrIt).first->getName()<<"  continent:"<<*(*terrIt).first->getContinent()<<" adjacency:";
            vector<Adjacency>::iterator adjIt;
            for(adjIt=(*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt){
                cout<<"("<<*(adjIt->getTerritory())<<",";
                if(*(adjIt->getLand())== false){
                    cout<<"W"<<") ";
                }
                else if(*(adjIt->getLand())== true){
                    cout<<"L"<<") ";
                }
            }
        cout<<endl;
    }
    cout<<"__________________________________________________________________________"<<endl;

}
/**
 * Assignment operator
 * @param a
 * @return
 */

Adjacency & Adjacency::operator =(const Adjacency &a){
    this->territory = new int(*(a.territory));
    this->land = new bool(*(a.land));
    return *this;
}
/**
 * stream operators
 * @param out
 * @param a
 * @return
 */
std::ostream& operator << (std::ostream &out, const Adjacency &a){
    out << " Territory: "<< *(a.territory) << " Land: " << *(a.land) <<std::endl;
    return out;
}
std::istream& operator >> (std::istream &in, Adjacency &a){
   std::cout << "Enter territory name and land type"<<std::endl;
   in >> *(a.territory);
   in >> *(a.land);
   return in;
}
/**
 * Copy Constructor
 * @param copy
 */
Territory::Territory(const Territory &copy) {
    this->name=new int(*(copy.name));
    this->continent = new int(*(copy.continent));
}
/**
 * Assignment operator
 * @param r
 * @return
 */
Territory & Territory::operator =(const Territory &r){
    this->name = new int(*(r.name));
    this->continent = new int(*(r.continent));
    return *this;
}
/**
 * Stream operator
 * @param out
 * @param r
 * @return
 */
std::ostream& operator << (std::ostream &out, const Territory &r){
    out << " Territory name: "<< *(r.name) << " Continent: " << *(r.continent) <<std::endl;
    return out;
}
std::istream& operator >> (std::istream &in, Territory &r){
    std::cout << "Territory name and Continent name"<<std::endl;
    in >> *(r.name);
    in >> *(r.continent);
    return in;
}
/**
 * deconstructor
 */
Map::~Map() {
    delete terrs;
    terrs= nullptr;
}
/**
 * Adds a territory to a graph
 * Makes sure there is no duplicate territory eliminating need to validate if a territory belongs to one continent
 * @param territory
 */
void Map::addTerritory(Territory *territory) {
    vector<Adjacency>* adj = new vector<Adjacency>();
    vector<territoryInfo>::iterator i;
    for (i = (terrs)->begin(); i !=(terrs)->end(); ++i) {
        if (*(*i).first->getName() == *(territory->getName())) {
            cout<< "Territory already exists"<<endl;
            exit(1);
        }
    }
    terrs->push_back(make_pair(territory, adj));
}
/**
 * default constructor
 */
Map::Map() {
    terrs= new vector<territoryInfo>;
}
/**
 * takes board shape
 * @param rect
 */
Map::Map(bool *rect) {
    this->rect=rect;
    terrs= new vector<territoryInfo>;
}
/**
 * copy constructor
 * @param copy
 */
Map::Map(Map &copy){
    this->rect = new bool(*(copy.rect));
    this->terrs = new vector<territoryInfo> (*(copy.terrs));
}
/**
 * Assignment operator
 * @param m
 * @return
 */
Map & Map::operator =(const Map &m){
    this->rect = new bool(*(m.rect));
    this->terrs = new vector<territoryInfo>(*(m.terrs));
    return *this;
}
/**
 * Stream operators
 * @param out
 * @param m
 * @return
 */
std::ostream& operator << (std::ostream &out, const Map &m){
    out << " Rectangle: "<< *(m.rect) <<std::endl;
    return out;
}
std::istream& operator >> (std::istream &in, Map &m){
    std::cout << "Is map shape rectangle?"<<std::endl;
    in >> *(m.rect);
    return in;
}