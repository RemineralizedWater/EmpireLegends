//Implementation class of Player class

#include "Player.h"
#include <iostream>

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
void Player::PayCoin() {
    std::cout << "You have been successfully paid" << std::endl;
}

//Places armies for desired player
void Player::PlaceNewArmies() {
    std::cout << "Your army has been successfully placed" << std::endl;
}

//Moves army for desired player
void Player::MoveArmies() {
    std::cout << "Your army has been successfully moved" << std::endl;
}

//Move over land for desired player
void Player::MoveOverLand() {
    std::cout << "You have successfully moved over land" << std::endl;
}

//Builds city for desired player
void Player::BuildCity() {
    std::cout << "You have successfully built the city" << std::endl;
}

//Destroys the army of the selected played
void Player::DestroyArmy() {
    std::cout << "Army successfully destroyed" << std::endl;
}

//Copy constructor
Player::Player(const Player &playerToCopy)
        : region_(new std::string(*playerToCopy.region_)),
        biddingFacility(new BiddingFacility(*playerToCopy.biddingFacility)){ //TODO update with necessary objects
    std::cout << "Calling the copy constructor" << std::endl;
}

//Constructor
Player::Player(const std::string &region)
        : region_(new std::string (region)),
        biddingFacility(new BiddingFacility()){ //TODO update with necessary objects
    std::cout << "Calling the default constructor" << std::endl;

}

//assignment operator
Player &Player::operator=(const Player &playerToCopy) {
    std::cout << "Calling the assignment operator" << std::endl;
    return *this;
}

//stream insertion operation
std::istream &operator>>(std::istream &is, Player &player) {//TODO update with necessary players
    is >> *player.region_;
    is >> *player.biddingFacility;
    return is;
}

