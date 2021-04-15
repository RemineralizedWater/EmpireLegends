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
    this->terrId = 0;
    this->continentId = 0;
    this->armySizeForPlayer_ = std::unique_ptr<std::map<std::string, int>>(new std::map<std::string, int>);
    this->hasCity = std::unique_ptr<std::map<std::string, bool>>(new std::map<std::string, bool>);

}

/**
 * Parametric constructor
 * @param terrId
 * @param continent
 * @param armySizeForPlayer
 */
Territory::Territory(int terrId, int continent,
                     const std::map<std::string, int> &armySizeForPlayer,
                     const std::map<std::string, bool> &hasCity) { //it is better to manually create to initlaize with new int
    this->terrId = terrId;
    this->continentId = continent;
    this->armySizeForPlayer_ = std::unique_ptr<std::map<std::string, int>>(new std::map<std::string, int>(armySizeForPlayer));
    this->hasCity = std::unique_ptr<std::map<std::string, bool>>(new std::map<std::string, bool>(hasCity));
}

/**
 * Copy Constructor
 * @param copy
 */
Territory::Territory(const Territory &copy) {
    this->terrId = copy.terrId;
    this->continentId = copy.continentId;
    this->armySizeForPlayer_ = std::unique_ptr<std::map<std::string, int>>(new std::map<std::string, int>(*copy.armySizeForPlayer_));
    this->hasCity = std::unique_ptr<std::map<std::string, bool>>(new std::map<std::string, bool>(*copy.hasCity));
}

/**
 * destructor
 */
Territory::~Territory() {

}
// Operators
/**
 * Assignment operator
 * @param t
 * @return
 */
Territory &Territory::operator=(const Territory &t) {
    this->terrId = t.terrId;
    this->continentId = t.continentId;
    this->armySizeForPlayer_ = std::unique_ptr<std::map<std::string, int>>(
            new std::map<std::string, int>(*t.armySizeForPlayer_));
    this->hasCity = std::unique_ptr<std::map<std::string, bool>>(
            new std::map<std::string, bool>(*t.hasCity));
    return *this;
}

/**
 * Stream operator
 * @param out
 * @param t
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Territory &t) {
    out << " Territory name: " << t.terrId << " Continent: " << t.continentId << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Territory &t) {
    std::cout << "Territory name and Continent name" << std::endl;
    in >> t.terrId;
    in >> t.continentId;
    for (int i = 0; i < 5; i++) {
        std::string playerName;
        int armySize;

        in >> playerName;
        in >> armySize;

        (*t.armySizeForPlayer_)[playerName] = armySize;
    }
    for (int i = 0; i < 5; i++) {
        std::string playerName;
        bool hasCity;

        in >> playerName;
        in >> hasCity;

        (*t.hasCity)[playerName] = hasCity;
    }
    return in;
}
// Accessors
/**
 * get territory id
 * @return
 */
int Territory::GetTerrId() {
    return terrId;
}

/**
 * get continent id
 * @return
 */
int Territory::GetContinent() {
    return continentId;
}

std::map<std::string, int> &Territory::GetArmySizeForPlayer() {
    return *armySizeForPlayer_;
}

std::map<std::string, bool> &Territory::GetHasCity() {
    return *hasCity;
}

Territory::Territory(int terrId, int continent) {
    this->terrId = terrId;
    this->continentId = continent;
}

void Territory::InsertNewArmyPlayerMapping(string playerName) {
    armySizeForPlayer_->insert(std::pair<string, int>(playerName, 0));

}

void Territory::InsertNewCityPlayerMapping(string playerName) {
    hasCity->insert(std::pair<string, bool>(playerName, false));
}

// ------------------------
// ADJACENCY METHODS
// Constructors/Destructor
/**
 * Default constructor
 */
Adjacency::Adjacency() {
    this->adjId = 0;
    this->isLandRoute = false;
}

/**
 * constructor
 * @param adjId
 * @param isLandRoute
 */
Adjacency::Adjacency(int adjId, bool isLandRoute) {
    this->adjId = adjId;
    this->isLandRoute = isLandRoute;
}

/**
 * Copy Constructor
 * @param copy
 */
Adjacency::Adjacency(const Adjacency &copy) {
    this->adjId = copy.adjId;
    this->isLandRoute = copy.isLandRoute;
}

/**
 * destructor
 */
Adjacency::~Adjacency() {

}
// Operators
/**
 * Assignment operator
 * @param a
 * @return
 */
Adjacency &Adjacency::operator=(const Adjacency &a) {
    this->adjId = a.adjId;
    this->isLandRoute = a.isLandRoute;
    return *this;
}

/**
 * stream operators
 * @param out
 * @param a
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Adjacency &a) {
    out << " Territory: " << a.adjId << " Land: " << a.isLandRoute << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Adjacency &a) {
    std::cout << "Enter territory name and land type" << std::endl;
    in >> a.adjId;
    in >> a.isLandRoute;
    return in;
}
// Accessors
/**
 * get adjacent territory
 * @return
 */
int Adjacency::GetAdjId() {
    return adjId;
}

/**
 * get route type ex. land or water
 * @return
 */
bool Adjacency::GetIsLandRoute() {
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
    this->terrAndAdjsList = new vector<terrInfo>;       // memory leak
    this->startingPoint=0;
}

/**
 * constructor: takes board shape
 * @param rect
 */
Map::Map(bool rect) {
    this->rect = rect;
    this->terrAndAdjsList = new vector<terrInfo>;       // memory leak
    this->startingPoint=0;
}

/**
 * copy constructor
 * @param copy
 */
Map::Map(const Map &copy) {
    this->rect = copy.rect;
    this->terrAndAdjsList = new vector<terrInfo>(*(copy.terrAndAdjsList));       // memory leak?
    this->startingPoint = copy.startingPoint;
}

/**
 * destructor
 */
Map::~Map() {
    if(terrAndAdjsList != nullptr){
        delete terrAndAdjsList;
        terrAndAdjsList = nullptr;
    }

    //if(startingPoint != nullptr){
    //    delete startingPoint;
    //    startingPoint= nullptr;
    //}

    /*while(!terrAndAdjsList->empty()) {
        delete terrAndAdjsList->back();
        terrAndAdjsList->pop_back();
    }*/
}
// Operators
/**
 * Assignment operator
 * @param m
 * @return
 */
Map &Map::operator=(const Map &m) {
    this->rect = m.rect;
    this->terrAndAdjsList = new vector<terrInfo>(*(m.terrAndAdjsList));       // memory leak
    this->startingPoint = m.startingPoint;
    return *this;
}

/**
 * Stream operators
 * @param out
 * @param m
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Map &m) {
    out << " Rectangle: " << m.rect << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Map &m) {
    std::cout << "Is map shape rectangle?" << std::endl;
    in >> m.rect;
    return in;
}
/**
 * Find a specific territory by id
 * @param terrId
 * @return
 */
Territory * Map::findTerritory(int terrId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if((*terrIt).first->GetTerrId() == terrId){
            return (*terrIt).first;
        }
    }
    return 0;
}
// Private Methods
/**
 * Check if territory is currently in graph
 * @param adjId
 * @return
 */
bool Map::territoryExists(int adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetTerrId() == adjId) {
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
bool Map::continentExists(int continent) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetContinent() == continent) {
            return true;
        }
    }
    return false;
}
/**
 * Get list of territories and adjacencies
 * @return
 */
int Map::getMapSize() {
return terrAndAdjsList->size();
}
/**
 * Get the starting point
 * @return
 */
int Map::getStartingPoint() {
    return startingPoint;
}
/**
 * set the starting point
 * @param terrId
 */
void Map::setStartingPoint(int terrId) {
    startingPoint = terrId;
}

/**
 * Checks if a territory is connected to rest of graph by checking if any other territory has it listed as an adjacency
 * @param adjId
 * @return
 */
bool Map::isConnected(int adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if ((adjIt->GetAdjId()) == adjId) {
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
bool Map::addTerritory(Territory *t) {
    vector<Adjacency> *adj = new vector<Adjacency>();       // memory leak
    if (territoryExists(t->GetTerrId()) == t->GetTerrId()) {
        cout << "Territory already exists. Territory belongs to more than one continent. Invalid Map!" << endl;
        /*if (continentExists(t->getContinent()) == *(t->GetContinent())) {
            cout << "Territory belongs to more than one continent. Invalid Map!" << endl;
        }*/
        return false;
    }
    terrAndAdjsList->push_back(make_pair(t, adj));
    return true;
}




/**
 * Adds adjacency to connect a territory to other terrs
 * verifies there are not duplicate edges
 * verifies a territory is not connected to itself
 * @param t
 * @param a
 */
bool Map::addAdjacency(Territory *t, Adjacency *a) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetTerrId() == t->GetTerrId()) {
            vector<Adjacency>::iterator adjIt;
            for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
                if (adjIt->GetAdjId() == a->GetAdjId() && adjIt->GetIsLandRoute() == a->GetIsLandRoute()) {
                    cout << "Edge already exists for the territory" << endl;
                    return false;
                }
                if (adjIt->GetAdjId() == t->GetTerrId()) {
                    cout << adjIt->GetAdjId() << t->GetTerrId() << endl;
                    cout << "Edge cannot connect to itself" << endl;
                    return false;
                }
            }
            (*terrIt).second->push_back(*(a));
            return true;
        }
    }
    return false;
}

/**
 * removes any adjacency that contains the territory
 * @param adjId
 */
void Map::removeAdjacency(int adjId) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = terrIt->second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (adjIt->GetAdjId() == adjId) {
                terrIt->second->erase(adjIt);
                return;
            }
        }
    }
}
/**
 * displays contents in graph
 */
void Map::display() {
    cout << "______________________________________________________________________________" << endl
         << "Displaying Board Map"
         << endl << "______________________________________________________________________________" << endl;
    if (rect) {
        cout << " Map shape: Rectangle" << endl;
    } else {
        cout << "Map shape: L-shape" << endl;
    }
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        cout << "territory:" << (*terrIt).first->GetTerrId() << " continent:" << (*terrIt).first->GetContinent()
             << " adjacency:";
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            cout << "(" << (adjIt->GetAdjId()) << ",";
            if (!(adjIt->GetIsLandRoute())) {
                cout << "W" << ") ";
            } else if (adjIt->GetIsLandRoute()) {
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
bool Map::validate() {
    vector<terrInfo>::iterator terrIt;
    if (terrIt == (terrAndAdjsList)->end()) {
        return false;
    }
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;

        //check if all terrs listed in adjacency are also listed as terrs
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (!territoryExists(adjIt->GetAdjId())) {
                cout << "Invalid Map! Territory " << (*terrIt).first->GetTerrId()
                     << " connects to another territory that does not exist" << endl;
                return false;
            }
        }
        //check if territory is connected to rest of graph
        if (!isConnected((*terrIt).first->GetTerrId())) {
            cout << "Invalid Map! Map does not connect territory " << (*terrIt).first->GetTerrId() << endl;
            return false;
        }
    }
    return true;
}
