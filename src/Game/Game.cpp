//
// Created by 06spa on 3/26/2021.
//
#include <iostream>
#include "Game.h"

/**
 * Default constructor
 */
Game::Game() {
    numberOfPlayers = 0;
}

/**
 * Parametric constructor
 */
Game::Game(int numberOfPlayers_) {
    cout << numberOfPlayers_ << " player game" << endl;
    this->numberOfPlayers = numberOfPlayers_;
    //TODO call methods here and create setters and getters
}

/**
 * Destructor
 */
Game::~Game() {

}

/**
 * Copy Constructor
 * @param copy
 */
Game::Game(const Game &copy) {
    this->numberOfPlayers = copy.numberOfPlayers;
}

/**
 * Assignment operator
 * @param gs
 * @return
 */
Game &Game::operator=(const Game &gs) {
    this->numberOfPlayers = gs.numberOfPlayers;
    return *this;
}

/**
 * Stream insertion operator
 * @param out
 * @param gs
 * @return
 */
std::ostream &operator<<(std::ostream &out, const Game &gs) {
    out << " number of players: "<< gs.numberOfPlayers  << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Game &gs) {
    std::cout << "Enter number of players" << std::endl;
    in >> gs.numberOfPlayers;
    return in;
}

vector<Player *> Game::CreatePlayers(int startingPoint) {
    vector<Player *> players;

    for (int i = 0; i < numberOfPlayers;i++) {
        Player *player(
                new Player(to_string(startingPoint),
                           new BiddingFacility(),
                           *(new Territory()),
                           *(new Cards()),
                           0,
                           1,
                           0,
                           new Hand(),
                           0,
                           "Player 1",
                           0,
                           3,
                           true,
                           0,
                           0,
                           new Map()));
        player->MyHand->SetOwningPlayer(player);
        player->GetBiddingFacility()->SetOwningPlayer(player);

        cout << "Providing player 18 coins.." << endl;
        player->SetMoney(18);
        players.push_back(player);
    }
    return players;
}

/**
 * Counts victory Points to check if ties or not
 * @param players
 * @return
 */
bool Game::Tied(vector<Player *> players, int &winner) {
    int maxVictoryPoint = -1;
    winner = 0;
    int ties = 0;

    for (int i = 0; i < numberOfPlayers; i++) {
        if (maxVictoryPoint == players[i]->GetVictoryPoints()) {
            ties++;
        }
        if (maxVictoryPoint<(players[i])->GetVictoryPoints()) {
            maxVictoryPoint = (players[i])->GetVictoryPoints();
            winner = i;
            ties = 0;
        }
    }
    if (ties != 0) {
        return true;
    }
    return false;
}

/**
 * Finds the max controlled regions by a player
 * @param players
 * @param map
 * @return
 */
bool Game::CountControlledTerritories(vector<Player *> players, Map *map) {
    int ties;
    int maxArmiesSize = -1;
    int playerWithMostArmies = 0;
    int winner = 0;
    std::map<int, int> playersAndControlledTerritoriesCount;

    for(int i = 1; i < (map->GetMapSize() + 1); i++) {
        Territory *temp = map->FindTerritory(i);

        //finds which player controls a territory by counting armies and cities
        for (int k = 0; k < numberOfPlayers; k++) {
            int currentArmiesSize = temp->GetArmySizeForPlayer()[players[k]->GetName()];
            if (temp->GetHasCity()[players[k]->GetName()]) {
                currentArmiesSize++;
            }
            if (maxArmiesSize == currentArmiesSize) {
                ties++;
            }
            if (maxArmiesSize < currentArmiesSize) {
                maxArmiesSize = currentArmiesSize;
                playerWithMostArmies = k;
                ties = 0;
            }
            maxArmiesSize = 0;
        }
        //if tied then no player owns the territory
        if (ties == 0) {
            if (playersAndControlledTerritoriesCount.find(playerWithMostArmies) != playersAndControlledTerritoriesCount.end()) {
                playersAndControlledTerritoriesCount[playerWithMostArmies] = (playersAndControlledTerritoriesCount[playerWithMostArmies] + 1);
            }
            else {
                playersAndControlledTerritoriesCount.insert(pair<int, int>(playerWithMostArmies, 1));
            }
        }
    }
    //compare which player controls the most territories
    int maxTerritories = -1;
    for (int i = 0; i < 2; i++) {
        if (maxTerritories < playersAndControlledTerritoriesCount[i]) {
            maxTerritories = playersAndControlledTerritoriesCount[i];
            winner = i;
        }
    }
    players[winner]->SetVictoryPoints(players[winner]->GetVictoryPoints() + 1);
    return false;
}

/**
 * Counts armies on board for each player to get player with max armies
 * @param players
 * @param map
 * @return
 */
bool Game::CountArmies(vector<Player *> players, Map *map) {
    int winner = 0;
    int ties = 0;
    int maxArmies = -1;

    //counting total armies for each player from board
    std::map<int, int> playersAndArmies;
    for (int i = 1; i < (map->GetMapSize() + 1); i++) {
        Territory *temp = map->FindTerritory(i);
        for (int k = 0; k < numberOfPlayers; k++) {
            if (playersAndArmies.find(k) != playersAndArmies.end()) {
                playersAndArmies[k] = (playersAndArmies[k] + temp->GetArmySizeForPlayer()[players[k]->GetName()]);
            }
            else {
                playersAndArmies.insert(pair<int, int>(k, temp->GetArmySizeForPlayer()[players[k]->GetName()]));
            }
        }
    }

    //comparing results or army counts on board for each player to get player with most armies
    std::map<int, int>::iterator playersAndArmiesIt;
    for (playersAndArmiesIt = playersAndArmies.begin(); playersAndArmiesIt != playersAndArmies.end(); playersAndArmiesIt++) {
        if (maxArmies == playersAndArmiesIt->second) {
            ties++;
        }
        if (maxArmies<playersAndArmiesIt->second) {
            maxArmies = playersAndArmiesIt->second;
            winner = playersAndArmiesIt->first;
            ties = 0;
        }
    }

    if (ties != 0) {
        return true;
    }
    players[winner]->SetVictoryPoints(players[winner]->GetVictoryPoints() + 1);
    return false;
}

/**
 * Returns check which players have more money if tied then return true else false
 * @param players
 * @param winner
 * @return
 */
bool Game::CountMoney(vector<Player *> players) {
    int maxMoney = -1;
    int winner = 0;
    int ties = 0;

    for (int i = 0; i < numberOfPlayers; i++) {
        if (maxMoney == players[i]->GetMoney()) {
            ties++;
        }
        if (maxMoney < (players[i])->GetMoney()) {
            maxMoney = (players[i])->GetMoney();
            winner = i;
            ties = 0;
        }
    }
    if (ties != 0) {
        return true;
    }
    players[winner]->SetVictoryPoints(players[winner]->GetVictoryPoints() + 1);
    return false;
}

Map *Game::SelectMap(bool &validMap) {
    std::string input;
    std::string file;

    std::cout << "\nChoose a map file to load \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt" << std::endl;
    std::cin >> input;

    while (true) {
        if (input == "1") {
            file = "../src/Map Boards/valid_map.txt";
            break;
        }
        else if (input == "2") {
            file = "../src/Map Boards/invalid1_map.txt";
            break;
        }
        else if (input == "3") {
            file = "../src/Map Boards/invalid2_map.txt";
            break;
        }
        else if (input == "4") {
            file = "../src/Map Boards/invalid3_map.txt";
            break;
        }
        else {
            std::cout << "Please enter a valid number \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt" << std::endl;
            std::cin >> input;
        }
    }

    MapLoader *mapLoader = new MapLoader(numberOfPlayers);
    Map *map = mapLoader->LoadMap(file, validMap);
    return map;
}

Deck *Game::CreateDeck() {
    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(numberOfPlayers);
    cout << "Shuffling deck.." << endl;
    deck->ShuffleDeck();
    return deck;
}
