//
// Created by RemineralizedWater on 2021-02-21.
//

#include "Map.h"
int name;
int continent;
int region;
bool land;
bool rect;
/**
 * Region constructor
 * @param name
 * @param continent
 */
Region::Region(int* name,int* continent) {
    this->name = name;
    this->continent=continent;
}
/**
 * get region name
 * @return
 */
int * Region::getName() {
    return name;
}
/**
 * get continent name
 * @return
 */
int * Region::getContinent() {
    return continent;
}
 /**
  * default constructor
  */
Region::Region() {
     this->name = new int{0};
     this->continent= new int{0};
}
// ------------------------
/**
 * get adjacent region
 * @return
 */
int * Adjacency::getRegion() {
    return region;
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
    this->region=new int{0};
    this->land=new bool{false};
}
/**
 * constructor
 * @param region
 * @param land
 */
Adjacency::Adjacency(int *region, bool *land) {
    this->region=region;
    this->land=land;
}
/**
 * Check if region is currently in graph
 * @param region
 * @return
 */
bool Map::regionExists(int *region) {
    vector<regionInfo>::iterator regIt;
    for (regIt = (regions)->begin(); regIt != (regions)->end(); ++regIt) {
        if (*(*regIt).first->getName() == *(region)) {
            return true;
        }
    }
    return false;
}
/**
 * Checks if a region is connected to rest of graph by checking if any other region has it listed as an adjacency
 * @param region
 * @return
 */
bool Map::isConnected(int *region) {
    vector<regionInfo>::iterator regIt;
    for (regIt = (regions)->begin(); regIt != (regions)->end(); ++regIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*regIt).second->begin(); adjIt != (*regIt).second->end(); ++adjIt) {
            if(*(adjIt->getRegion())==*(region)){
                return true;
            }
        }
    }
    return false;
}
/**
 * checks the map is a connected graph and each region listed as an adjacency exists
 **/
void Map::validate() {
    vector<regionInfo>::iterator regIt;
    for (regIt = (regions)->begin(); regIt != (regions)->end(); ++regIt) {
        vector<Adjacency>::iterator adjIt;

        //check if all regions listed in adjacency are also listed as regions
        for(adjIt=(*regIt).second->begin(); adjIt != (*regIt).second->end(); ++adjIt){
            if(!regionExists(adjIt->getRegion())){
                cout<<"Invalid Map! Region "<<*(*regIt).first->getName()<< " connects to another region that does not exist"<<endl;
                exit(1);
            }
        }
        //check if region is connected to rest of graph
        if(!isConnected((*regIt).first->getName())){
            cout<<"Invalid Map! map does not connect region "<<*(*regIt).first->getName() <<endl;
            exit(1);
        }
    }
}
/**
 * Adds adjacency to connect a region to other regions
 * verifies there are not duplicate edges
 * verifies a region is not connected to itself
 * @param region
 * @param adjacency
 */
void Map::addAdjacency(Region *region, Adjacency *adjacency) {
    vector<regionInfo>::iterator regIt;
    for (regIt = (regions)->begin(); regIt != (regions)->end(); ++regIt) {
        if (*(*regIt).first->getName() == *(region->getName())) {
            vector<Adjacency>::iterator adjIt;
            for(adjIt=(*regIt).second->begin(); adjIt != (*regIt).second->end(); ++adjIt){
                if(*(adjIt->getRegion()) == *adjacency->getRegion() && *(adjIt->getLand()) == *adjacency->getLand()){
                    cout<<"Edge already exists for the region"<<endl;
                    exit(1);
                }
                if(*(adjIt->getRegion()) == *region->getName()){
                    cout<<*(adjIt->getRegion())<<*region->getName()<<endl;
                    cout<<"Edge cannot connect to itself"<<endl;
                    exit(1);
                }
            }
            (*regIt).second->push_back(*(adjacency));
            break;
        }
    }
}
/**
 * displays contents in graph
 */
void Map::display(){
    cout<<"______________________________________________________________________________"<<endl<<"Displaying Board Map"<<endl<<"______________________________________________________________________________"<<endl;
    if(rect){
        cout<<"Map shape: Rectangle"<<endl;
    }
    else{
        cout<<"Map shape: L-shape"<<endl;
    }
    vector<regionInfo>::iterator regIt;
    for (regIt = (regions)->begin(); regIt != (regions)->end(); ++regIt) {
        cout<<"region:"<<*(*regIt).first->getName()<<"  continent:"<<*(*regIt).first->getContinent()<<" adjacency:";
            vector<Adjacency>::iterator adjIt;
            for(adjIt=(*regIt).second->begin(); adjIt != (*regIt).second->end(); ++adjIt){
                cout<<"("<<*(adjIt->getRegion())<<",";
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
Adjacency::~Adjacency() {

}
Region::~Region() {
}
/**
 * deconstructor
 */
Map::~Map() {
    delete regions;
    regions= nullptr;
}
/**
 * Adds a region to a graph
 * Makes sure there is no duplicate region eliminating need to validate if a region belongs to one continent
 * @param region
 */
void Map::addRegion(Region *region) {
    vector<Adjacency>* adj = new vector<Adjacency>();
    vector<regionInfo>::iterator i;
    for (i = (regions)->begin(); i !=(regions)->end(); ++i) {
        if (*(*i).first->getName() == *(region->getName())) {
            cout<< "Region already exists"<<endl;
            exit(1);
        }
    }
    regions->push_back(make_pair(region, adj));
}
/**
 * Default constructor
 */
Map::Map() {
    regions= new vector<regionInfo>;
}
/**
 * Construtor that takes board shape
 * @param rect
 */
Map::Map(bool *rect) {
    this->rect=rect;
    regions= new vector<regionInfo>;
}