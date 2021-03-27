//
// Created by 06spa on 3/26/2021.
//
#include <iostream>
#include "Game.h"
#include "../Map/Map.h"
#include "../Map Loader/MapLoader.h"
#include "../BiddingFacility/BiddingFacility.h"

int numberOfPlayers;
Game::Game(int numberOfPlayers) {
    cout<<numberOfPlayers<<" players game"<<endl;
    this->numberOfPlayers=new int{numberOfPlayers};
    //TODO call methods here and create setters and getters
}

/**
 * Default constructor
 */
Game::Game() {
    numberOfPlayers=new int{0};
}

Game::~Game() {
    delete numberOfPlayers;
    numberOfPlayers= nullptr;
}
/**
 * Copy Constructor
 * @param copy
 */
Game::Game(Game &copy){
    this->numberOfPlayers = new int(*(copy.numberOfPlayers));
}
/**
 * Assignment operator
 * @param gs
 * @return
 */
Game & Game::operator =(const Game &gs){
    this->numberOfPlayers = new int(*(gs.numberOfPlayers));
    return *this;
}
/**
 * Stream insertion operator
 * @param out
 * @param gs
 * @return
 */
std::ostream& operator << (std::ostream &out, const Game &gs){
    out << " number of players: "<< *(gs.numberOfPlayers)  <<std::endl;
    return out;
}
std::istream& operator >> (std::istream &in, Game &gs){
    std::cout << "Enter number of players"<<std::endl;
    in >> *(gs.numberOfPlayers);
    return in;
}

vector<Player*> Game::createPlayers(int startingPoint) {
    vector<Player*> players;
    Player* ptr;

    for(int i=0;i<*numberOfPlayers;i++){
        BiddingFacility *b =new BiddingFacility();
        b->ReceiveStartingCoins(*numberOfPlayers);
        Player *player(
                new Player(to_string(startingPoint),
                           *b,
                           Territory(),
                           Cards(),
                           new int(0),
                           1,
                           new int(0),
                           new Hand(),
                           b->GetCoins(),
                           *(b->GetLastName()),
                           0,
                           3,
                           true));
        players.push_back(player);
    }
    return players;
}


Map * Game::selectMap(bool &validMap) {

    std::string input;
    std::string file;
    std::cout << "\nChoose a map file to load \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt"<< std::endl;
    std::cin >> input;

    while(true){
        if( input == "1" ){
            file= "../src/Map Boards/valid_map.txt";
            break;
        }
        else if(input == "2"){
            file= "../src/Map Boards/invalid1_map.txt";
            break;
        }
        else if(input == "3"){
            file= "../src/Map Boards/invalid2_map.txt";
            break;
        }
        else if(input == "4"){
            file= "../src/Map Boards/invalid3_map.txt";
            break;
        }
        else{
            std::cout << "Please enter a valid number \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt"<< std::endl;
            std::cin >> input;
        }
    }

    MapLoader *mapLoader = new MapLoader(*numberOfPlayers);
    Map* map=mapLoader->loadMap(file, validMap);
    return map;

}
Deck * Game::createDeck() {
    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(*numberOfPlayers);
    cout<< "Shuffling deck.."<<endl;
    deck->ShuffleDeck();
    return deck;
}