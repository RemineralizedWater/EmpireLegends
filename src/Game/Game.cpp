#include <iostream>
#include "Game.h"

using namespace std;

/**
 * Default constructor
 */
Game::Game() {
    numberOfPlayers = 0;
}

/**
 * Parametric constructor
 */
Game::Game(int numberOfPlayers_, Map *modelMap) {
    numberOfPlayers = numberOfPlayers_;
    map=modelMap;
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
ostream &operator<<(ostream &out, const Game &gs) {
    out << " number of players: " << gs.numberOfPlayers << endl;
    return out;
}

istream &operator>>(istream &in, Game &gs) {
    cout << "Enter number of players" << endl;
    in >> gs.numberOfPlayers;
    return in;
}

/**
 * Accessor
 * @return numberOfPlayers
 */
int Game::GetNumberOfPlayers() {
    return numberOfPlayers;
}

/**
 * Mutator
 * @param numberOfPlayers_
 */
void Game::SetNumberOfPlayers(int numberOfPlayers_) {
    numberOfPlayers = numberOfPlayers_;
}
//TODO; remove starting point parameter
vector<Player *> Game::CreatePlayers(int startingPoint) {
    vector<Player *> players;
<<<<<<< HEAD
=======
    BiddingFacility *tempBiddingFacility;
    tempBiddingFacility->ReceiveStartingCoins(numberOfPlayers);

>>>>>>> 6b10c4f00012be31b4c638911e0d0cced5bfd041
    for (int i = 0; i < numberOfPlayers; i++) {
        Player *player(
                new Player(to_string(map->GetStartingPoint()),
                           new BiddingFacility(),
                           *(new Territory()),
                           *(new Cards()),
                           0,
                           1,
                           0,
                           new Hand(),
                           0,
                           "Player"+to_string(i+1),
                           0,
                           3,
                           true,
                           0,
                           0,
                           map,
                           0,
                           0));
        player->MyHand->SetOwningPlayer(player);
        player->GetBiddingFacility()->SetOwningPlayer(player);
        player->SetName("Player"+to_string(i+1));

        int coins = 0;
        if (numberOfPlayers == 2) coins = 14;
        else if (numberOfPlayers == 3) coins = 11;
        else if (numberOfPlayers == 4) coins = 9;
        player->SetMoney(coins);
        player->SetArmiesTokens(18);
        player->SetCitiesDisks(3);
        players.push_back(player);
    }
    return players;
}
void Game::Setup(vector<Player*> players) {

    //place armies on starting point
    int terrId;
    cout<<"Setting up armies on board"<<endl;
    for(int k=0;k<players.size();k++){
        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        {
            vector<terrInfo>::iterator terrIt;
            for (terrIt = map->GetTerrAndAdjsList()->begin();
                 terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {
                (*terrIt).first->InsertNewArmyPlayerMapping(players.at(k)->GetName());
                (*terrIt).first->InsertNewCityPlayerMapping(players.at(k)->GetName());
                if ((*terrIt).first->GetTerrId() == map->GetStartingPoint())
                    (*terrIt).first->AddCityForPlayer(players.at(k)->GetName());
            }
        }
    }

    if(numberOfPlayers==2){
        for(int i=0;i<10;i++){
            for(int k=0;k<players.size();k++){
                terrId=rand() % map->GetMapSize() + 1;
                cout<<players.at(k)->GetName()<<": ";
                players.at(k)->PlaceNewArmies(1, terrId, true, true);
            }
        }
    }
    else{
        for(int k=0;k<players.size();k++){
            cout<<players.at(k)->GetName()<<": ";
            players.at(k)->PlaceNewArmies(4, map->GetStartingPoint(), false, true);
        }
    }
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
        if (maxVictoryPoint < (players[i])->GetVictoryPoints()) {
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

    for (int i = 1; i < (map->GetMapSize() + 1); i++) {
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
            if (playersAndControlledTerritoriesCount.find(playerWithMostArmies) !=
                playersAndControlledTerritoriesCount.end()) {
                playersAndControlledTerritoriesCount[playerWithMostArmies] = (
                        playersAndControlledTerritoriesCount[playerWithMostArmies] + 1);
            } else {
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
            } else {
                playersAndArmies.insert(pair<int, int>(k, temp->GetArmySizeForPlayer()[players[k]->GetName()]));
            }
        }
    }

    //comparing results or army counts on board for each player to get player with most armies
    std::map<int, int>::iterator playersAndArmiesIt;
    for (playersAndArmiesIt = playersAndArmies.begin();
         playersAndArmiesIt != playersAndArmies.end(); playersAndArmiesIt++) {
        if (maxArmies == playersAndArmiesIt->second) {
            ties++;
        }
        if (maxArmies < playersAndArmiesIt->second) {
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

void Game::SelectMap(Map *map, bool &validMap) {
    string input;
    string file;
    cout << "\nGame Maps:\n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt" << endl;
    cout << "Enter the chosen Game Map (1, 2, 3 or 4):";
    cin >> input;

    while (true) {
        if (input == "1") {
            file = "../src/Map Boards/valid_map.txt";
            break;
        } else if (input == "2") {
            file = "../src/Map Boards/invalid1_map.txt";
            break;
        } else if (input == "3") {
            file = "../src/Map Boards/invalid2_map.txt";
            break;
        } else if (input == "4") {
            file = "../src/Map Boards/invalid3_map.txt";
            break;
        } else {
            cout << "Please enter a valid Game Map choice (1, 2, 3 or 4):";
            cin >> input;
        }
    }

    MapLoader *mapLoader = new MapLoader(map, numberOfPlayers);
    mapLoader->LoadMap(map, file, validMap);

    // Memory clean up
    if (mapLoader != nullptr) {
        delete mapLoader;
        mapLoader = nullptr;
    }

    return;
}

Deck *Game::CreateDeck() {
    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(numberOfPlayers);
    cout << "Shuffling deck.." << endl;
    deck->ShuffleDeck();
    return deck;
}
