#include "MapLoader.h"
#include <iostream>
#include <fstream>
/**
 * Gets board shape type and number of board pieces based on player to load a map
 * @param mapFilePath
 * @param numberOfPlayers
 */
MapLoader::MapLoader(std::string mapFilePath, int numberOfPlayers) {
    std::cout <<"********Loading Map from "<< mapFilePath <<" *********"<< std::endl;
    int numberOfBoardPieces=0;
    bool rectangle=false;
    if(numberOfPlayers==2||numberOfPlayers==3){
        rectangle=isRectangle();
        numberOfBoardPieces=3;
    }
    else if(numberOfPlayers==4){
        numberOfBoardPieces=4;
        rectangle=true;
    }
    loadMap(mapFilePath, numberOfBoardPieces, rectangle);
}

/**
 * Gets board layout type from user to specify the arrangement of the board pieces
 * options: Rectangular, L-shape
 * @return
 */
bool MapLoader::isRectangle() {
    std::string input;
    std::cout << "Choose a Board Layout \n1) Rectangular \n2) L-shape \nEnter the number corresponding to your layout choice"<< std::endl;
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
MapLoader::MapLoader() {

}
MapLoader::~MapLoader() {

}
//TODO change return type/ input once Part1 completed
/**
 * reads map and validates format
 * @param mapFile
 * @param numberOfBoardPieces
 * @param rectangle
 */
void MapLoader::loadMap(std::string mapFile,int numberOfBoardPieces,bool rectangle) {
    std::fstream input(mapFile);
    std::string line;
    std::string adjacency;
    int mapBoardCount = 0;

    //Go through map file line by line
    while(std::getline(input, line)) {
        int currentIndex = 0;
        std::cout << line << std::endl;

        //check for board pieces
        if (line == "-") {
            mapBoardCount++;
            if(mapBoardCount==numberOfBoardPieces){
                break;
            }
            else{
                continue;
            }
        }

        //parse continent field
        //TODO store continent in graph
        verifyRegionName(line, currentIndex, line.find("|", currentIndex), "Continent name must be a number", "Continent name is too long");
        currentIndex = checkNextFieldExists(line, currentIndex);

        //parse region field
        //TODO store regions in graph
        verifyRegionName(line, currentIndex, line.find("|", currentIndex), "Region name must be a number", "Region name is too long");
        currentIndex = checkNextFieldExists(line, currentIndex);

        //TODO store adjacency in graph
        //parse adjacency field

        //there must be ( after |
        if (line.at(currentIndex) != '(') {
            std::cout << "Invalid format" << std::endl;
            exit(1);
        }
        adjacency = line.substr(currentIndex, line.size() - 1);
        parseAdjacency(adjacency);
    }
    input.close();

    if(mapBoardCount < numberOfBoardPieces){
        std::cout << "Invalid Map! Map must have at least "<< numberOfBoardPieces<<" boards pieces" << std::endl;
        exit(1);
    }
    //TODO if 3 board pieces then remove connections to 4th board
    //TODO call validate from map class
    //TODO display map
}
/**
 * Loops through each adjacency a region has
 * @param adjacency
 */
void MapLoader::parseAdjacency(std::string adjacency) {
    ///////////////////////////////////////////////////std::cout << adjacency << std::endl;

    bool land;
    int currentIndex = 0;

    //going through each adjacent region in parenthesis
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

        //TODO store whether edge is land or water in graph
        //Checks whether a region is connected to another by land or water, otherwise invalid
        land = isLand(adjacency, commaIndex, currentIndex);

        //parsing the adjacent region
        if (commaIndex + 1 < adjacency.size()) {
            currentIndex = commaIndex + 1;
            verifyRegionName(adjacency, currentIndex, closingParenthesisIndex,
                             "Region name referred in adjacency must be a number",
                             "Region name referred in adjacency is too long");
        }
        currentIndex = closingParenthesisIndex + 1;
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


//TODO change return type/ input once Part1 completed
/**
 * verifies continents/regions are numbers
 * @param line
 * @param currentIndex
 * @param charIndex
 * @param argErrMsg
 * @param outRangeErrMsg
 */
void MapLoader::verifyRegionName(std::string line, int currentIndex, int charIndex, std::string argErrMsg,
                                 std::string outRangeErrMsg) {
    int region = 0;
    try {
        //casting string to int
        region = std::stoi(line.substr(currentIndex, charIndex - currentIndex));
    }
    catch (std::invalid_argument const &e) {
        std::cout << argErrMsg << '\n';
        exit(1);
    }
    catch (std::out_of_range const &e) {
        std::cout << outRangeErrMsg << '\n';
        exit(1);
    }
    /////////////////////////////////////////////////////std::cout << region << std::endl;
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
        ///////////////////////////////////std::cout << adjacency.substr(currentIndex, commaIndex - currentIndex) << std::endl;
        return true;
    }
    //water
    else if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "W") {
        /////////////////////////std::cout << adjacency.substr(currentIndex, commaIndex - currentIndex) << std::endl;
        return false;
    }
    else{
        //////////////////////////////std::cout << adjacency.substr(currentIndex, commaIndex - currentIndex) << std::endl;
        std::cout << "region must be connected by L or W " << std::endl;
        exit(1);
    }
}