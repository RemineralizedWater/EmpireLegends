#include "Map.h"

// TERRITORY METHODS
// Constructors/Destructor
/**
 * default constructor
 */
Territory::Territory() {
    terrId = 0;
    continentId = 0;
}

/**
 * Parametric constructor
 * @param terrId
 * @param continent
 * @param armySizeForPlayer
 */
Territory::Territory(int terrId_, int continentId_,
                    std::map<std::string, int> armySizeForPlayer_,
                    std::map<std::string, bool> hasCityForPlayer_) {
    terrId = terrId_;
    continentId = continentId_;
    armySizeForPlayer = armySizeForPlayer_;
    hasCityForPlayer = hasCityForPlayer_;
}

Territory::Territory(int terrId_, int continentId_) {
    terrId = terrId_;
    continentId = continentId_;
}

/**
 * Copy Constructor
 * @param copy
 */
Territory::Territory(const Territory &copy) {
    terrId = copy.terrId;
    continentId = copy.continentId;
    armySizeForPlayer = copy.armySizeForPlayer;
    hasCityForPlayer = copy.hasCityForPlayer;
}

/**
 * Destructor
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
    terrId = t.terrId;
    continentId = t.continentId;
    armySizeForPlayer = t.armySizeForPlayer;
    hasCityForPlayer = t.hasCityForPlayer;
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

        t.armySizeForPlayer[playerName] = armySize;
    }
    for (int i = 0; i < 5; i++) {
        std::string playerName;
        bool hasCity;

        in >> playerName;
        in >> hasCity;

        t.hasCityForPlayer[playerName] = hasCity;
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

/**
 * get army size
 * @return
 */
std::map<std::string, int> &Territory::GetArmySizeForPlayer() {
    return armySizeForPlayer;
}

/**
 * get has city (true/false)
 * @return
 */
std::map<std::string, bool> &Territory::GetHasCity() {
    return hasCityForPlayer;
}

/**
 * get number of armies for player
 * @return
 */
int Territory::GetNumberOfArmies(string playerName) {
    return armySizeForPlayer[playerName];
}

// Public Methods
void Territory::InsertNewArmyPlayerMapping(string playerName) {
    armySizeForPlayer.insert({playerName, 0});
}

void Territory::InsertNewCityPlayerMapping(string playerName) {
    hasCityForPlayer.insert({playerName, false});
}

void Territory::AddArmySizeForPlayer(string playerName, int amount) {
    armySizeForPlayer[playerName] += amount;
}

void Territory::AddCityForPlayer(string playerName) {
    hasCityForPlayer[playerName] = true;
}

void Territory::RemoveArmySizeForPlayer(string playerName, int amount) {
    armySizeForPlayer[playerName] -= amount;
    if(armySizeForPlayer[playerName] < 0)
        armySizeForPlayer[playerName] = 0;
}

bool Territory::HasCity(string playerName) {
    return hasCityForPlayer[playerName];
}

bool Territory::HasArmies(string playerName) {
    return armySizeForPlayer.count(playerName) != 0; // this is 0 if not exist, 1 if exist, not a real count
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
Adjacency::Adjacency(int adjId_, bool isLandRoute_) {
    this->adjId = adjId_;
    this->isLandRoute = isLandRoute_;
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
    this->rectangle = false;
    this->terrAndAdjsList = new vector<terrInfo>;
    this->startingPoint = 0;
}

/**
 * constructor: takes board shape
 * @param rect
 */
Map::Map(bool rectangle_) {
    this->rectangle = rectangle_;
    this->terrAndAdjsList = new vector<terrInfo>;
    this->startingPoint = 0;
}

/**
 * copy constructor
 * @param copy
 */
Map::Map(const Map &copy) {
    this->rectangle = copy.rectangle;
    this->terrAndAdjsList = new vector<terrInfo>(*(copy.terrAndAdjsList));
    this->startingPoint = copy.startingPoint;
}

/**
 * destructor
 */
Map::~Map() {
    if (terrAndAdjsList != nullptr) {
        delete terrAndAdjsList;
        terrAndAdjsList = nullptr;
    }
}

// Operators
/**
 * Assignment operator
 * @param m
 * @return
 */
Map &Map::operator=(const Map &m) {
    this->rectangle = m.rectangle;
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
    out << " Rectangle: " << m.rectangle << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Map &m) {
    std::cout << "Is map shape rectangle?" << std::endl;
    in >> m.rectangle;
    return in;
}

// Accessors
/**
 * Get list of territories and adjacencies
 * @return
 */
int Map::GetMapSize() {
    return terrAndAdjsList->size();
}

/**
 * Get the starting point
 * @return
 */
int Map::GetStartingPoint() {
    return startingPoint;
}

/**
 * Get the list of territories and their adjacencies
 * @return
 */
typedef pair<Territory *, vector<Adjacency> *> terrInfo; // Need to redefine for return type in GetTerrAndAdjsList()
vector<terrInfo> *Map::GetTerrAndAdjsList() {
    return terrAndAdjsList;
}

// Mutators
/**
 * set the starting point
 * @param terrId_
 */
void Map::SetStartingPoint(int terrId_) {
    startingPoint = terrId_;
}

// Private Methods
/**
 * Check if territory is currently in graph
 * @param adjId_
 * @return
 */
bool Map::TerritoryExists(int adjId_) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetTerrId() == adjId_) {
            return true;
        }
    }
    return false;
}

/**
 * Check if continent is currently in graph
 * @param continentId_
 * @return
 */
bool Map::ContinentExists(int continentId_) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetContinent() == continentId_) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if a territory is connected to rest of graph by checking if any other territory has it listed as an adjacency
 * @param adjId_
 * @return
 */
bool Map::IsConnected(int adjId_) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if ((adjIt->GetAdjId()) == adjId_) {
                return true;
            }
        }
    }
    return false;
}

// Public Methods
/**
 * Adds a territory to a graph
 * Makes sure there is no duplicate territory eliminating need to Validate if a territory belongs to one continent
 * @param t
 */
bool Map::AddTerritory(Territory *t) {
    vector<Adjacency> *adj = new vector<Adjacency>();       // TODO: memory leak?
    if (TerritoryExists(t->GetTerrId()) == t->GetTerrId()) {
        cout << "Territory already exists. Territory belongs to more than one continent. Invalid Map!" << endl;
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
bool Map::AddAdjacency(Territory *t, Adjacency *a) {
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
 * @param adjId_
 */
void Map::RemoveAdjacency(int adjId_) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;
        for (adjIt = terrIt->second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (adjIt->GetAdjId() == adjId_) {
                terrIt->second->erase(adjIt);
                return;
            }
        }
    }
}

/**
 * Find a specific territory by id
 * @param terrId_
 * @return
 */
Territory *Map::FindTerritory(int terrId_) {
    vector<terrInfo>::iterator terrIt;
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        if ((*terrIt).first->GetTerrId() == terrId_) {
            return (*terrIt).first;
        }
    }
    return 0;
}

/**
 * displays contents in graph
 */
void Map::Display() {
    cout << "______________________________________________________________________________" << endl
         << "Displaying Board Map"
         << endl << "______________________________________________________________________________" << endl;
    if (rectangle) {
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
bool Map::Validate() {
    vector<terrInfo>::iterator terrIt;
    if (terrIt == (terrAndAdjsList)->end()) {
        return false;
    }
    for (terrIt = (terrAndAdjsList)->begin(); terrIt != (terrAndAdjsList)->end(); ++terrIt) {
        vector<Adjacency>::iterator adjIt;

        //check if all terrs listed in adjacency are also listed as terrs
        for (adjIt = (*terrIt).second->begin(); adjIt != (*terrIt).second->end(); ++adjIt) {
            if (!TerritoryExists(adjIt->GetAdjId())) {
                cout << "Invalid Map! Territory " << (*terrIt).first->GetTerrId()
                     << " connects to another territory that does not exist" << endl;
                return false;
            }
        }
        //check if territory is connected to rest of graph
        if (!IsConnected((*terrIt).first->GetTerrId())) {
            cout << "Invalid Map! Map does not connect territory " << (*terrIt).first->GetTerrId() << endl;
            return false;
        }
    }
    return true;
}
