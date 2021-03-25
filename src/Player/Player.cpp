//Implementation class of Player class

#include "Player.h"
#include <iostream>
#include <utility>

int Player::supply = 0;

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
bool Player::PayCoin(const int &costOfCard) {
    if (costOfCard <= *money_) {
        *money_ -= costOfCard;
        supply += costOfCard;
        std::cout << "The transaction has been successful, we have removed: " << costOfCard << " coins" << std::endl;
        return true;
    } else {
        std::cout << "You do not have enough money to buy this card" << std::endl;
        return false;
    }
}

//Places armies for desired player
bool Player::PlaceNewArmies(const int &numberOfArmiesToPlace) {
    if (*tokenArmies_ >= numberOfArmiesToPlace && territory_->getHasCity()[*name_]) {
        *tokenArmies_ -= numberOfArmiesToPlace;
        territory_->getArmySizeForPlayer()[*name_] += numberOfArmiesToPlace;
        std::cout << "Your army has been successfully placed" << std::endl;
        return true;
    } else {
        return false;
        std::cout << "Your army has been unsuccessfully placed, because you have no more armies to place" << std::endl;
    }
}

void Player::AndOrAction(const std::string &goodAndActionFromCard) {
    std::cout << goodAndActionFromCard << std::endl;

}

//Moves army for desired player
bool Player::MoveArmies(Territory &territoryToMoveFrom, Territory &toMoveTo, const std::string &playerWhoWantsToMove,
                        const int &numberOfArmiesHeWantsToMove) {
    if (territoryToMoveFrom.getArmySizeForPlayer()[playerWhoWantsToMove] >= numberOfArmiesHeWantsToMove) {
        territoryToMoveFrom.getArmySizeForPlayer()[playerWhoWantsToMove] -= numberOfArmiesHeWantsToMove;
        toMoveTo.getArmySizeForPlayer()[playerWhoWantsToMove] += numberOfArmiesHeWantsToMove;
        std::cout << "Your army has been successfully moved" << std::endl;
        return true;
    } else {
        std::cout
                << "Your army has not been moved because the armies you want to move are bigger than the armies in that territory"
                << std::endl;
        return false;
    }
}

//Move over land for desired player
bool Player::MoveOverLand() {
    if (*totalMovementPointsForRound_ > 0) {
        (*totalMovementPointsForRound_)--;
        std::cout << "You have successfully moved over land" << std::endl;
        return true;
    } else {
        std::cout << "You have not successfully moved over land because your total movement points for round are at 0"
                  << std::endl;
        return false;

    }
}

bool Player::MoveOverWater() {
    if (*totalMovementPointsForRound_ > *costToMoveOverWater_) {
        (*totalMovementPointsForRound_) -= *costToMoveOverWater_;
        std::cout << "You have successfully moved over water" << std::endl;
        return true;
    } else {
        std::cout
                << "You have not successfully moved over water because your total movement points for round are at 0 or smaller than the amount you have"
                << std::endl;
        return false;

    }
}


//Builds city for desired player
bool Player::BuildCity(Territory &territory) {
    for (const std::pair<std::string, bool> &pair: territory.getHasCity()) {
        if (pair.second) {
            std::cout << "the player " << pair.first << "already built a city in this territory" << std::endl;
            return false;
        }
    }

    if (*disks_ > 0) {
        *disks_ -= 1;
        territory.getHasCity()[*name_] = true;
        std::cout << "You have successfully built the city" << std::endl;
        return true;
    } else {
        std::cout << "You cannot build a city" << std::endl;
        return false;
    }
}

//Destroys the army of the selected played
bool
Player::DestroyArmy(Territory &territory, const std::string &playerAttacking, const std::string &playerBeingAttacked,
                    const int &numberOfArmiesToDestroy) {
    if (territory.getArmySizeForPlayer()[playerAttacking] > 0) {
        territory.getArmySizeForPlayer()[playerBeingAttacked] -= numberOfArmiesToDestroy;
        std::cout << "Army successfully destroyed" << std::endl;
        if (territory.getArmySizeForPlayer()[playerBeingAttacked] < 0) {
            territory.getArmySizeForPlayer()[playerBeingAttacked] = 0;
        }
        return true;
    } else {
        std::cout << "Army not destroyed" << std::endl;
        return false;
    }
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
          name_(new std::string(*playerToCopy.name_)),
          totalMovementPointsForRound_(new int(*playerToCopy.totalMovementPointsForRound_)),
          costToMoveOverWater_(new int(*playerToCopy.costToMoveOverWater_)) {
    std::cout << "Calling the copy constructor" << std::endl;
}

//Constructor
Player::Player(const std::string &region, const BiddingFacility &biddingFacility, const Territory &territory,
               const Cards &cards, const int &tokenArmies,
               const int &cubes, const int &disks, const Hand &hand, const int &money, const std::string &name,
               const int &totalMovementPointsForRound,
               const int &costToMoveOverWater)
        : region_(new std::string(region)),
          biddingFacility_(new BiddingFacility(biddingFacility)),
          territory_(new Territory(territory)),
          cards_(new Cards(cards)),
          tokenArmies_(new int(18)),
          cubes_(new int(cubes)),
          disks_(new int(3)),
          hand_(new Hand(hand)),
          money_(new int(money)),
          totalMovementPointsForRound_(new int(0)),
          costToMoveOverWater_(new int(3)),
          name_(new std::string(name)) {
    std::cout << "Calling the default constructor" << std::endl;

}

//assignment operator
Player &Player::operator=(const Player &playerToCopy) {
    std::cout << "Calling the assignment operator" << std::endl;
    return *this;
}

//stream insertion operation
std::istream &operator>>(std::istream &is, Player &player) {
    is >> *player.region_;
    is >> *player.biddingFacility_;
    is >> *player.territory_;
    is >> *player.cards_;
    is >> *player.tokenArmies_;
    is >> *player.cubes_;
    is >> *player.disks_;
    is >> *player.totalMovementPointsForRound_;
    is >> *player.costToMoveOverWater_;
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

int &Player::getCostOverWater() {
    return *costToMoveOverWater_;
}

void Player::setCostOverWater(const int &costToMoveOverWater) {
    costToMoveOverWater_ = std::unique_ptr<int>(new int(costToMoveOverWater));
}

int &Player::getMoney() {
    return *money_;
}

void Player::setMoney(const int &money) {
    money_ = std::unique_ptr<int>(new int(money));
}

int &Player::getTotalMovementPointsForRound() {
    return *totalMovementPointsForRound_;
}

void Player::setTotalMovementPointsForRound(const int &totalMovementPointsForRound) {
    totalMovementPointsForRound_ = std::unique_ptr<int>(new int(totalMovementPointsForRound));
}

