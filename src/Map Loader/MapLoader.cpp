#include "MapLoader.h"
#include "../Map/Map.h"
#include <iostream>
#include <fstream>
#include <string>

int numberOfBoardPieces;
bool rectangle;
Map map;
std::string mapFilePath;

/**
 * Gets board shape type and number of board pieces based on player to load a map
 * @param mapFilePath
 * @param numberOfPlayers
 */
MapLoader::MapLoader(int numberOfPlayers) {
    numberOfBoardPieces=new int{0};
    rectangle=new bool{false};
    if(numberOfPlayers==2||numberOfPlayers==3){
        rectangle=new bool{isRectangle()};
        numberOfBoardPieces=new int{3};
    }
    else if(numberOfPlayers==4){
        numberOfBoardPieces=new int{4};
        rectangle=new bool{false};
    }
    map=new Map(rectangle);
}

/**
 * Copy Constructor
 * @param copy
 */
MapLoader::MapLoader(MapLoader &copy){
    this->numberOfBoardPieces = new int(*(copy.numberOfBoardPieces));
    this->rectangle = new bool(*(copy.rectangle));
    this->mapFilePath = new std::string(*(copy.mapFilePath));
    this->map= new Map(*(copy.map));
}

/**
 * Gets board layout type from user to specify the arrangement of the board pieces
 * options: Rectangular, L-shape
 * @return
 */
bool MapLoader::isRectangle() {
    std::string input;
    std::cout << "\nChoose a Board Layout \n1) Rectangular \n2) L-shape \nEnter the number corresponding to your layout choice"<< std::endl;
    std::cin >> input;
    while(true){
        if( input == "1" ){
            return true;
        }
        else if(input == "2"){
            return false;
        }
        else{
            std::cout << "Please enter a valid number of players \n1) Rectangular \n2) L-shape \nEnter the number corresponding to your layout choice" << std::endl;
            std::cin >> input;
        }
    }
}
/**
 * Default constructor
 */
MapLoader::MapLoader() {
    numberOfBoardPieces=new int{0};
    rectangle=new bool{false};
    mapFilePath= new std::string {};
    map=new Map();
}
/**
 * destructor
 */
MapLoader::~MapLoader() {
    delete mapFilePath;
    delete rectangle;
    delete numberOfBoardPieces;
    delete map;
    mapFilePath= nullptr;
    rectangle= nullptr;
    numberOfBoardPieces= nullptr;
    map= nullptr;
}
/**
 * Assignment operator
 * @param ml
 * @return
 */
MapLoader & MapLoader::operator =(const MapLoader &ml){
    this->numberOfBoardPieces = new int(*(ml.numberOfBoardPieces));
    this->rectangle = new bool(*(ml.rectangle));
    this->map=new Map(*(ml.map));
    return *this;
}
/**
 * Stream insertion operator
 * @param out
 * @param ml
 * @return
 */
std::ostream& operator << (std::ostream &out, const MapLoader &ml){
    out << " Map File: "<< *(ml.mapFilePath) << " Board Pieces: " << *(ml.numberOfBoardPieces) << " Rectangular Board: " << *(ml.rectangle) <<std::endl;
    return out;
}
std::istream& operator >> (std::istream &in, MapLoader &ml){
    std::cout << "Enter map file path"<<std::endl;
    in >> *(ml.mapFilePath);

    return in;
}

/**
 * reads map and validates format
 * @param file
 * @param numberOfBoardPieces
 * @param rectangle
 */
void MapLoader::loadMap(std::string file) {
    mapFilePath=new std::string(file);
    std::cout << "***** Reading from map file "<<*mapFilePath<<std::endl;
    std::fstream input(file);
    std::string line;
    std::string adjacency;
    int mapBoardCount = 0;

    if(!input){
        std::cout << "No file found!" << std::endl;
        exit(1);
    }

    //Go through map file line by line
    while(getline(input, line)) {
        int currentIndex = 0;

        //check for board pieces
        if (line == "-") {
            mapBoardCount++;
            if(mapBoardCount==*numberOfBoardPieces){
                break;
            }
            else{
                continue;
            }
        }

        //parse continent field
        int continent=verifyTerritoryName(line, currentIndex, line.find("|", currentIndex), "Continent name must be a number", "Continent name is too long");
        currentIndex = checkNextFieldExists(line, currentIndex);

        //parse territory field
        int territory=verifyTerritoryName(line, currentIndex, line.find("|", currentIndex), "Territory name must be a number", "Territory name is too long");
        map->addTerritory(new Territory(new int {territory},new int {continent}));
        currentIndex = checkNextFieldExists(line, currentIndex);

        //parse adjacency field
        //there must be ( after |
        if (line.at(currentIndex) != '(') {
            std::cout << "Invalid format" << std::endl;
            exit(1);
        }
        adjacency = line.substr(currentIndex, line.size() - 1);
        parseAdjacency(adjacency,new Territory(new int {territory},new int {continent}));
    }
    input.close();

    if(mapBoardCount < *numberOfBoardPieces){
        std::cout << "Invalid Map! Map must have at least "<< *numberOfBoardPieces<<" boards pieces" << std::endl;
        exit(1);
    }
    //removes edges to terrs that are on boards not used
    map->removeUnUsedAdjacency();
    map->validate();
    map->display();
}
/**
 * Loops through each adjacency a territory has
 * @param adjacency
 */
void MapLoader::parseAdjacency(std::string adjacency, Territory* territory) {

    bool land;
    int adjacentTerritory;
    int currentIndex = 0;

    //going through each adjacent territory in parenthesis
    while (currentIndex < adjacency.size() - 1) {
        int openingParenthesisIndex = adjacency.find("(", currentIndex);
        int commaIndex = adjacency.find(",", currentIndex);
        int closingParenthesisIndex = adjacency.find(")", currentIndex);

        //duplicate closing brackets
        if (openingParenthesisIndex > closingParenthesisIndex) {
            std::cout << "Invalid format" << std::endl;
            exit(1);
        }
        //checks there is anything after opening parenthesis
        if (openingParenthesisIndex + 1 < adjacency.size()) {
            currentIndex = openingParenthesisIndex + 1;
        } else {
            std::cout << "Invalid format" << std::endl;
            exit(1);
        }

        //Checks whether a territory is connected to another by land or water, otherwise invalid
        land = isLand(adjacency, commaIndex, currentIndex);

        //parsing the adjacent territory
        if (commaIndex + 1 < adjacency.size()) {
            currentIndex = commaIndex + 1;
            adjacentTerritory=verifyTerritoryName(adjacency, currentIndex, closingParenthesisIndex,
                             "Territory name referred in adjacency must be a number",
                             "Territory name referred in adjacency is too long");

        }
        currentIndex = closingParenthesisIndex + 1;
        Adjacency* adj =new Adjacency(new int{adjacentTerritory},new bool{land});
        map->addAdjacency(territory,adj);
    }
}

/**
 * checks if next field exists in the string and updates the current index accordingly
 * @param line
 * @param currentIndex
 * @return
 */
int MapLoader::checkNextFieldExists(std::string line,int currentIndex) {
    currentIndex = line.find("|", currentIndex);

    //check if there is a character after |
    if (currentIndex + 1 < line.size()) {
        currentIndex++;
    } else {
        std::cout << "invalid format" << std::endl;
        exit(1);
    }
    return  currentIndex;
}

/**
 * verifies continents/terrs are numbers
 * @param line
 * @param currentIndex
 * @param charIndex
 * @param argErrMsg
 * @param outRangeErrMsg
 */
int MapLoader::verifyTerritoryName(std::string line, int currentIndex, int charIndex, std::string argErrMsg,
                                 std::string outRangeErrMsg) {
    int territory = 0;
    try {
        //casting string to int
        territory = std::stoi(line.substr(currentIndex, charIndex - currentIndex));
        return territory;
    }
    catch (std::invalid_argument const &e) {
        std::cout << argErrMsg << '\n';
        exit(1);
    }
    catch (std::out_of_range const &e) {
        std::cout << outRangeErrMsg << '\n';
        exit(1);
    }
}

/**
 * Checks connection type of an adjacency e.g. land or water
 * land--> L
 * water-->W
 * returns true if edge is L , false if edge is W,  and exits if neither L or W
 * @param adjacency
 * @param commaIndex
 * @param currentIndex
 * @return
 */
bool MapLoader::isLand(std::string adjacency, int commaIndex, int currentIndex ) {
    //land
    if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "L") {
        return true;
    }
    //water
    else if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "W") {
        return false;
    }
    else{
        std::cout << "territory must be connected by L or W " << std::endl;
        exit(1);
    }
}