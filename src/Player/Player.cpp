//Implementation class of Player class

#include "Player.h"
#include <iostream>

int Player::bankOfCoins = 0;

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
void Player::PayCoin(int costOfCard) {
    if (costOfCard <= *money_) {
        *money_ -= costOfCard;
        bankOfCoins += costOfCard;
        std::cout << "The transaction has been successful, we have removed: " << costOfCard << " coins" << std::endl;
    } else {
        std::cout << "You do not have enough money to buy this card" << std::endl;
    }
}

//Places armies for desired player
void Player::PlaceNewArmies(int numberOfArmiesToPlace) {
    if (*tokenArmies_ >= numberOfArmiesToPlace && territory_->getHasCity()[*name_]) {
        *tokenArmies_ -= numberOfArmiesToPlace;
        territory_ -> getArmySizeForPlayer()[*name_] += numberOfArmiesToPlace;
        std::cout << "Your army has been successfully placed" << std::endl;
    } else {
        std::cout << "Your army has been unsuccessfully placed, because you have no more armies to place" << std::endl;
    }
}

void Player::AndOrAction(const std::string &goodAndActionFromCard) {
    std::cout << goodAndActionFromCard << std::endl;

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
          tokenArmies_(new int(*playerToCopy.tokenArmies_)),
          cubes_(new int(*playerToCopy.cubes_)),
          disks_(new int(*playerToCopy.disks_)),
          money_(new int(*playerToCopy.money_)),
          name_(new std::string(*playerToCopy.name_)) {
    std::cout << "Calling the copy constructor" << std::endl;
}

//Constructor
Player::Player(const std::string &region, const BiddingFacility &biddingFacility, const Territory &territory,
               const Cards &cards, const int &tokenArmies,
               const int &cubes, const int &disks, const Hand &hand, const int &money, const std::string &name)
        : region_(new std::string(region)),
          biddingFacility_(new BiddingFacility(biddingFacility)),
          territory_(new Territory(territory)),
          cards_(new Cards(cards)),
          tokenArmies_(new int(18)),
          cubes_(new int(cubes)),
          disks_(new int(disks)),
          hand_(new Hand(hand)),
          money_(new int(money)),
          name_(new std::string(name)) {
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
    is >> *player.territory_;
    is >> *player.cards_;
    is >> *player.tokenArmies_;
    is >> *player.cubes_;
    is >> *player.disks_;
    return is;
}

Player::Player() {

}

Player::~Player() {

}

const std::string &Player::getName() const {
    return *name_;
}

void Player::setName(const string &name) {
    name_ = std::unique_ptr<std::string>(new std::string(name));
}

