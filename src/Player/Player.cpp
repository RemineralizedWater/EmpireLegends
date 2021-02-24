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
          biddingFacility_(new BiddingFacility(*playerToCopy.biddingFacility_)),
          territory_(new Territory(*playerToCopy.territory_)),
          cards_(new Cards(*playerToCopy.cards_)),
          tokenArmies_(new int (*playerToCopy.tokenArmies_)),
          cubes_(new int(*playerToCopy.cubes_)),
          disks_(new int(*playerToCopy.disks_))
        {
    std::cout << "Calling the copy constructor" << std::endl;
}

//Constructor
Player::Player(const std::string &region, const BiddingFacility &biddingFacility, const Territory &territory,
               const Cards &cards, const int &tokenArmies,
               const int &cubes, const int &disks)
        : region_(new std::string(region)),
          biddingFacility_(new BiddingFacility(biddingFacility)),
          territory_(new Territory(territory)),
          cards_(new Cards(cards)),
          tokenArmies_(new int (tokenArmies)),
          cubes_(new int(cubes)),
          disks_(new int(disks)){
    std::cout << "Calling the default constructor" << std::endl;

}

//assignment operator
Player &Player::operator=(const Player &playerToCopy) {
    std::cout << "Calling the assignment operator" << std::endl;
    return *this;
}

//stream insertion operation
std::istream &operator>>(std::istream &is, Player &player) {//TODO update player.territory_
    is >> *player.region_;
    is >> *player.biddingFacility_;
//    is >> *player.territory_;
    is >> *player.cards_;
    is >> *player.tokenArmies_;
    is >> *player.cubes_;
    is >> *player.disks_;
    return is;
}

