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
        rectangle=new bool{true};
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
            std::cout << "Please enter a valid number \n1) Rectangular \n2) L-shape \nEnter the number corresponding to your layout choice" << std::endl;
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
 * @param validMap
 * @return map object
 */
Map* MapLoader::loadMap(std::string file, bool &validMap) {
    mapFilePath=new std::string(file);
    std::cout << "***** Reading from map file "<<*mapFilePath<<std::endl;
    std::fstream input(file);
    std::string line;
    std::string adjacency;
    int mapBoardCount = 0;
    bool configuration=false;
    bool startingPointFound=false;

    if(!input){
        std::cout << "No file found!" << std::endl;
        validMap=false;
        return map;
    }

    //Go through map file line by line
    while(getline(input, line)) {
        int currentCharIndex = 0;
        if(!startingPointFound){
            int startingPoint=0;
            if(!verifyId(line, startingPoint, "Territory name must be a number", "Territory name is too long")){
                return map;
            }
            startingPointFound=true;
            map->setStartingPoint(startingPoint);
        }
            //checking if map file contains configuration for Rectangle or L-shape
        else if(line=="Rectangle(3){"&&*rectangle==true&&*numberOfBoardPieces==3){
            configuration=true;
            continue;
        }
        else if(line=="Rectangle(4){"&&*rectangle==true&&*numberOfBoardPieces==4){
            configuration=true;
            continue;
        }
        else if(line=="L-shape{"&&*rectangle==false){
            configuration=true;
            continue;
        }
        //stop reading file if end of specified map shape
        if(configuration==true&&line=="}"){
            break;
        }

        if(configuration){
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
            int continent=0;
            if(!verifyId(line.substr(currentCharIndex, line.find("|", currentCharIndex) - currentCharIndex), continent, "Continent name must be a number", "Continent name is too long")){
                validMap=false;
                return map;
            }

            if(!checkNextFieldExists(line, currentCharIndex)){
                validMap=false;
                return map;
            }

            //parse territory field
            int territory=0;
            if(!verifyId(line.substr(currentCharIndex, line.find("|", currentCharIndex) - currentCharIndex) , territory, "Territory name must be a number", "Territory name is too long")){
                validMap=false;
                return map;
            }
            const std::map<std::string, int> armySizeForPlayer;
            const std::map<std::string, bool> hasCity;
            if(!map->addTerritory(new Territory(territory,continent,armySizeForPlayer,hasCity))){
                validMap=false;
                return map;
            }
            if(!checkNextFieldExists(line, currentCharIndex)){
                validMap=false;
                return map;
            }

            //parse adjacency field
            //there must be ( after |
            if (line.at(currentCharIndex) != '(') {
                std::cout << "Invalid format" << std::endl;
                validMap=false;
                return map;
            }
            adjacency = line.substr(currentCharIndex, line.size() - 1);
            if(!parseAdjacency(adjacency,new Territory(territory,continent))){
                validMap=false;
                return map;
            }

        }

    }
    input.close();

    if(!configuration){
        cout<<"Invalid Map! There is no configuration for the shape of the map selected in map file"<<endl;
        validMap=false;
        return map;
    }
    if(mapBoardCount !=*numberOfBoardPieces){
        std::cout << "Invalid Map! Map must have "<< *numberOfBoardPieces<<" boards pieces" << std::endl;
        validMap=false;
        return map;
    }
    //validate the values in map
    if(!map->validate()){
        validMap=false;
        return map;
    }
    validMap=true;
    return map;
}


/**
 * Loops through each adjacency a territory has and checks it
 * @param adjacency
 */
bool MapLoader::parseAdjacency(std::string adjacency, Territory* territory) {

    bool land = false;
    int adjacentTerritory = 0;
    int currentIndex = 0;

    //going through each adjacent territory in parenthesis
    while (currentIndex < adjacency.size() - 1) {
        int openingParenthesisIndex = adjacency.find("(", currentIndex);
        int commaIndex = adjacency.find(",", currentIndex);
        int closingParenthesisIndex = adjacency.find(")", currentIndex);

        //duplicate closing brackets
        if (openingParenthesisIndex > closingParenthesisIndex) {
            std::cout << "Invalid format" << std::endl;
            return false;
        }
        //checks there is anything after opening parenthesis
        if (openingParenthesisIndex + 1 < adjacency.size()) {
            currentIndex = openingParenthesisIndex + 1;
        } else {
            std::cout << "Invalid format" << std::endl;
            return false;
        }

        //Checks whether a territory is connected to another by land or water, otherwise invalid
        if(!isLand(adjacency,commaIndex,currentIndex, land )){
            return false;
        }

        //parsing the adjacent territory
        if (commaIndex + 1 < adjacency.size()) {
            currentIndex = commaIndex + 1;

            if(!verifyId(adjacency.substr(currentIndex, closingParenthesisIndex - currentIndex),adjacentTerritory, "Territory name referred in adjacency must be a number",
                         "Territory name referred in adjacency is too long")){
                return false;
            }
        }
        currentIndex = closingParenthesisIndex + 1;

        Adjacency* adj =new Adjacency(adjacentTerritory,land);
        if(!map->addAdjacency(territory,adj)){
            return false;
        }
    }
    return true;
}


/**
 * checks if next field exists in the string and updates the current index accordingly
 * @param line
 * @param currentIndex
 * @return
 */
bool MapLoader::checkNextFieldExists(std::string line,int &currentIndex) {
    currentIndex = line.find("|", currentIndex);

    //check if there is a character after |
    if (currentIndex + 1 < line.size()) {
        currentIndex++;
    } else {
        std::cout << "invalid format" << std::endl;
        return false;
    }
    return true;
}

/**
 * verifies continents/terrs are numbers
 * @param string_id
 * @param int_id
 * @param argErrMsg
 * @param outRangeErrMsg
 * @return true of false
 */
bool MapLoader::verifyId(std::string string_id, int &int_id,std::string argErrMsg,
                         std::string outRangeErrMsg) {
    try {
        //casting string to int
        int_id = std::stoi(string_id);
        return true;
    }
    catch (std::invalid_argument const &e) {
        std::cout << argErrMsg << '\n';
        return false;
    }
    catch (std::out_of_range const &e) {
        std::cout << outRangeErrMsg << '\n';
        return false;
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
 * @param land
 * @return
 */
bool MapLoader::isLand(std::string adjacency, int commaIndex, int currentIndex, bool &land ) {
    //land
    if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "L") {
        land=true;
        return true;
    }
        //water
    else if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "W") {
        land=false;
        return true;
    }
    else{
        std::cout << "territory must be connected by L or W " << std::endl;
        return false;
    }
}