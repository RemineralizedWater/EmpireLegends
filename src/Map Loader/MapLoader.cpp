#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>

Map map;

/**
 * Default constructor
 */
MapLoader::MapLoader() {
    numberOfBoardPieces = 0;
    rectangle = false;
    mapFilePath = "";
}

/**
 * Gets board shape type and number of board pieces based on player to load a map
 * @param mapFilePath
 * @param numberOfPlayers
 */
MapLoader::MapLoader(Map *map, int numberOfPlayers) {
    numberOfBoardPieces = 0;
    rectangle = false;
    if (numberOfPlayers == 2 || numberOfPlayers == 3) {
        rectangle = IsRectangle();
        numberOfBoardPieces = 3;
    } else if (numberOfPlayers == 4) {
        numberOfBoardPieces = 4;
        rectangle = true;
    }
    map->SetIsRectangle(rectangle);
}

/**
 * Copy Constructor
 * @param copy
 */
MapLoader::MapLoader(const MapLoader &copy) {
    this->numberOfBoardPieces = copy.numberOfBoardPieces;
    this->rectangle = copy.rectangle;
    this->mapFilePath = copy.mapFilePath;
}

/**
 * destructor
 */
MapLoader::~MapLoader() {

}

/**
 * Assignment operator
 * @param ml
 * @return
 */
MapLoader &MapLoader::operator=(const MapLoader &ml) {
    this->numberOfBoardPieces = ml.numberOfBoardPieces;
    this->rectangle = ml.rectangle;
    return *this;
}

/**
 * Stream insertion operator
 * @param out
 * @param ml
 * @return
 */
std::ostream &operator<<(std::ostream &out, const MapLoader &ml) {
    out << " Map File: " << ml.mapFilePath << " Board Pieces: " << ml.numberOfBoardPieces << " Rectangular Board: "
        << ml.rectangle << endl;
    return out;
}

std::istream &operator>>(std::istream &in, MapLoader &ml) {
    cout << "Enter map file path" << endl;
    in >> ml.mapFilePath;
    return in;
}

/**
 * Gets board layout type from user to specify the arrangement of the board pieces
 * options: Rectangular, L-shape
 * @return
 */
bool MapLoader::IsRectangle() {
    string input = "";
    cout << "Board Layouts:\n1) Rectangular \n2) L-Shape \nEnter the chosen Board Layout (1 or 2):";
    cin >> input;
    while (true) {
        if (input == "1") {
            cout << "Board Layout Rectangular selected" << endl;
            return true;
        } else if (input == "2") {
            cout << "Board Layout L-Shape selected" << endl;
            return false;
        } else {
            cout << "Board Layouts:\n1) Rectangular \n2) L-Shape \nPlease enter a valid Board Layout choice (1 or 2):";
            cin >> input;
        }
    }
}

/**
 * reads map and validates format
 * @param file
 * @param validMap
 * @return map object
 */
void MapLoader::LoadMap(Map *map, string file, bool &validMap) {  // bool &validMap pass by reference
    mapFilePath = file;
    cout << "***** Reading from map file " << mapFilePath << endl;
    fstream input(file);
    string line = "";
    string adjacency = "";
    int mapBoardCount = 0;
    bool isConfigured = false;
    bool startingPointFound = false;

    if (!input) {
        cout << "No file found!" << endl;
        validMap = false;
        fstream close(file);
        return;
    }

    //Go through map file line by line
    while (getline(input, line)) {
        int currentCharIndex = 0;
        if (!startingPointFound) {
            int startingPoint = 0;
            if (!VerifyId(line, startingPoint, "Territory name must be a number", "Territory name is too long")) {
                fstream close(file);
                return;
            }
            startingPointFound = true;
            map->SetStartingPoint(startingPoint);
        }
            //checking if map file contains isConfigured for Rectangle or L-shape
        else if (line == "Rectangle(3){" && rectangle && numberOfBoardPieces == 3) {
            isConfigured = true;
            continue;
        } else if (line == "Rectangle(4){" && rectangle && numberOfBoardPieces == 4) {
            isConfigured = true;
            continue;
        } else if (line == "L-shape{" && !rectangle) {
            isConfigured = true;
            continue;
        }
        //stop reading file if end of specified map shape
        if (isConfigured && line == "}") {
            fstream close(file);
            break;
        }

        if (isConfigured) {
            //check for board pieces
            if (line == "-") {
                mapBoardCount++;
                if (mapBoardCount == numberOfBoardPieces) {
                    fstream close(file);
                    break;
                } else {
                    continue;
                }
            }

            //parse continentId field
            int continentId = 0;
            if (!VerifyId(line.substr(currentCharIndex, line.find("|", currentCharIndex) - currentCharIndex),
                          continentId,
                          "Continent name must be a number", "Continent name is too long")) {
                validMap = false;
                fstream close(file);
                return;
            }

            if (!CheckNextFieldExists(line, currentCharIndex)) {
                validMap = false;
                return;
            }

            //parse terrId field
            int terrId = 0;
            if (!VerifyId(line.substr(currentCharIndex, line.find("|", currentCharIndex) - currentCharIndex), terrId,
                          "Territory name must be a number", "Territory name is too long")) {
                validMap = false;
                fstream close(file);
                return;
            }
            const std::map<string, int> armySizeForPlayer;
            const std::map<string, bool> hasCityForPlayer;
            if (!map->AddTerritory(terrId, continentId)) { // TODO SEGFAULT
                validMap = false;
                fstream close(file);
                return;
            }
            if (!CheckNextFieldExists(line, currentCharIndex)) {
                validMap = false;
                fstream close(file);
                return;
            }

            //parse adjacency field
            //there must be ( after |
            if (line.at(currentCharIndex) != '(') {
                cout << "Invalid format" << endl;
                validMap = false;
                fstream close(file);
                return;
            }
            adjacency = line.substr(currentCharIndex, line.size() - 1);
            if (!ParseAdjacency(map, adjacency, terrId, continentId)) {
                validMap = false;
                fstream close(file);
                return;
            }
        }
    }
    input.close();

    if (!isConfigured) {
        cout << "Invalid Map! There is no isConfigured for the shape of the map selected in map file" << endl;
        validMap = false;
        fstream close(file);
        return;
    }
    if (mapBoardCount != numberOfBoardPieces) {
        cout << "Invalid Map! Map must have " << numberOfBoardPieces << " boards pieces" << endl;
        validMap = false;
        fstream close(file);
        return;
    }
    //Validate the values in map
    if (!map->Validate()) {
        validMap = false;
        fstream close(file);
        return;
    }
    validMap = true;
    fstream close(file);
    return;
}

/**
 * Loops through each adjacency a territory has and checks it
 * @param adjacency
 */
bool MapLoader::ParseAdjacency(Map *map, string adjacency, int terrId, int continentId) {
    bool isLandRoute_ = false;
    int adjId_ = 0;
    int currentIndex = 0;

    //going through each adjacent territory in parenthesis
    while (currentIndex < adjacency.size() - 1) {
        int openingParenthesisIndex = adjacency.find("(", currentIndex);
        int commaIndex = adjacency.find(",", currentIndex);
        int closingParenthesisIndex = adjacency.find(")", currentIndex);

        //duplicate closing brackets
        if (openingParenthesisIndex > closingParenthesisIndex) {
            cout << "Invalid format" << endl;
            return false;
        }
        //checks there is anything after opening parenthesis
        if (openingParenthesisIndex + 1 < adjacency.size()) {
            currentIndex = openingParenthesisIndex + 1;
        } else {
            cout << "Invalid format" << endl;
            return false;
        }

        //Checks whether a territory is connected to another by isLandRoute_ or water, otherwise invalid
        if (!IsLand(adjacency, commaIndex, currentIndex, isLandRoute_)) {
            return false;
        }

        //parsing the adjacent territory
        if (commaIndex + 1 < adjacency.size()) {
            currentIndex = commaIndex + 1;

            if (!VerifyId(adjacency.substr(currentIndex, closingParenthesisIndex - currentIndex), adjId_,
                          "Territory name referred in adjacency must be a number",
                          "Territory name referred in adjacency is too long")) {
                return false;
            }
        }
        currentIndex = closingParenthesisIndex + 1;

        if (!map->AddAdjacency(terrId, adjId_, isLandRoute_)) {
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
bool MapLoader::CheckNextFieldExists(string line,
                                     int &currentIndex) {  // int &currentIndex pass by reference to correctly id valid map
    currentIndex = line.find("|", currentIndex);

    //check if there is a character after |
    if (currentIndex + 1 < line.size()) {
        currentIndex++;
    } else {
        cout << "invalid format" << endl;
        return false;
    }
    return true;
}

/**
 * verifies continents/terrs are numbers
 * @param stringId
 * @param intId
 * @param argErrMsg
 * @param outRangeErrMsg
 * @return true of false
 */
bool MapLoader::VerifyId(string stringId, int &intId, string argErrMsg,
                         string outRangeErrMsg) {  // int &intId pass by reference
    try {
        //casting string to int
        intId = std::stoi(stringId);
        return true;
    }
    catch (std::invalid_argument const &e) {
        cout << argErrMsg << '\n';
        return false;
    }
    catch (std::out_of_range const &e) {
        cout << outRangeErrMsg << '\n';
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
bool
MapLoader::IsLand(string adjacency, int commaIndex, int currentIndex, bool &land) {  // bool &land pass by reference
    //land
    if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "L") {
        land = true;
        return true;
    }
        //water
    else if (adjacency.substr(currentIndex, commaIndex - currentIndex) == "W") {
        land = false;
        return true;
    } else {
        cout << "territory must be connected by L or W " << endl;
        return false;
    }
}
