//Implementation class of Player class

#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

int Player::supply = 0;

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
void Player::PayCoin(const int &amountToPay) {
    *money_ -= amountToPay;
    supply += amountToPay;
    std::cout << "The transaction has been successful, we have removed: " << amountToPay << " coins." << std::endl;
}

//Places armies for desired player
void Player::PlaceNewArmies(int numberOfArmiesToPlaced) {

    // TODO: "Which territory would you like to place armies in?" >> get territory id
    cout << "Which territory would you like to place armies in? " << endl;
    cout << "Using placeholder territory.." << endl;
    Territory* terr = new Territory();  // placeholder for testing
    terr->InsertNewArmyPlayerMapping(*name_); // placeholder for testing
    terr->InsertNewCityPlayerMapping(*name_); // placeholder for testing
    terr->getHasCity()[*name_] = true; // placeholder for testing

    if(!terr->getHasCity()[*name_]){
        cout << "You do not have a city in this territory, please choose another territory." << endl;
        cout << "You have " << *tokenArmies_ << " army tokens." << endl;
        //TODO LOOP
    }

    if(*tokenArmies_ < numberOfArmiesToPlaced){
        cout << "You do not have enough armies left to place." << endl;
    }else{
        terr->getArmySizeForPlayer()[*name_] += numberOfArmiesToPlaced;
        tokenArmies_-=numberOfArmiesToPlaced;
        cout << "Your army has been successfully placed." << endl;
    }
}

void Player::AndOrAction() {
    Cards* activeCard = hand_->GetActiveCard();

    string actionOneValue = to_string(*activeCard->GetActionOneValue());
    string actionTwoValue = to_string(*activeCard->GetActionTwoValue());
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};

    if(activeCard->GetActionOperator()->compare("OR") == 0){
        int option;
        cout << "Would you like to: " << endl;
        cout << to_string(*activeCard->GetActionOne()) + ": " + actions[*activeCard->GetActionOne()] + actionOneValue + ", OR" << endl;
        cout << to_string(*activeCard->GetActionTwo()) + ": " + actions[*activeCard->GetActionTwo()] + actionTwoValue << endl;
        cout << "Option: ";
        cin >> option;

        // TODO: data validation on option

        switch(option){
            case 1: //place i armies
                PlaceNewArmies(*(activeCard->GetActionOneValue()));
                break;
            case 2: //move i armies
                MoveArmies(*(activeCard->GetActionOneValue()));
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(*(activeCard->GetActionOneValue()));
                break;
        }
    }else if(activeCard->GetActionOperator()->compare("AND") == 0){
        switch(*activeCard->GetActionOne()){
            case 1: //place i armies
                PlaceNewArmies(*(activeCard->GetActionOneValue()));
                break;
            case 2: //move i armies
                MoveArmies(*(activeCard->GetActionOneValue()));
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(*(activeCard->GetActionOneValue()));
                break;
        }
        switch(*activeCard->GetActionTwo()){
            case 1: //place i armies
                PlaceNewArmies(*(activeCard->GetActionTwoValue()));
                break;
            case 2: //move i armies
                MoveArmies(*(activeCard->GetActionTwoValue()));
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(*(activeCard->GetActionTwoValue()));
                break;
        }
    }else{
        cout << "Error in Player.cpp.AndOrAction().";
        exit(0);
    }
}

//Moves army for desired player
void Player::MoveArmies(int numberOfArmiesHeWantsToMove) {

    // TODO: "Which territory would you like to move FROM? >> enter Territory.
    cout << "Which territory would you like to move armies FROM?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory* territoryToMoveFrom = new Territory(); // placeholder
    // TODO: "Which territory would you like to move TO? >> enter Territory.
    cout << "Which territory would you like to move armies TO?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory* territoryToMoveTo = new Territory(); // placeholder

    //TODO: needs to move one at a time, not the full amount passed.
    if (territoryToMoveFrom->getArmySizeForPlayer()[*name_] >= numberOfArmiesHeWantsToMove) {
        territoryToMoveFrom->getArmySizeForPlayer()[*name_] -= numberOfArmiesHeWantsToMove;
        territoryToMoveTo->getArmySizeForPlayer()[*name_] += numberOfArmiesHeWantsToMove;
        std::cout << "Your army has been successfully moved" << std::endl;
    } else {
        std::cout
                << "Your army has not been moved because the armies you want to move are bigger than the armies you own in your source territory"
                << std::endl;
    }
}

//Move over land for desired player
void Player::MoveOverLand() {
    if (*totalMovementPointsForRound_ > 0) {
        (*totalMovementPointsForRound_)--;
        std::cout << "You have successfully moved over land" << std::endl;
    } else {
        std::cout << "You have not successfully moved over land because your total movement points for round are at 0"
                  << std::endl;
    }
}

void Player::MoveOverWater() {
    if (*totalMovementPointsForRound_ > *costToMoveOverWater_) {
        (*totalMovementPointsForRound_) -= *costToMoveOverWater_;
        std::cout << "You have successfully moved over water" << std::endl;
    } else {
        std::cout
        << "You have not successfully moved over water because your total movement points for round are at 0 or smaller than the amount you have"
        << std::endl;
    }
}


//Builds city for desired player
void Player::BuildCity() {

    //TODO: "Which territory would you like to build a city in?" >> enter city.
    cout << "Which territory would you like to build a city in?" << endl;
    cout << "Using placeholder city..." << endl;
    Territory* terr = new Territory(); // placeholder

    for (const std::pair<std::string, bool> &pair: terr->getHasCity()) {
        if (pair.second) {
            cout << "The player " << pair.first << " has already built a city in this territory." << endl;
            //TODO: LOOP
        }
    }

    if (*disks_ > 0) {
        *disks_ -= 1;
        terr->getHasCity()[*name_] = true;
        cout << "You have successfully built the city." << endl;
    } else {
        cout << "You cannot build a city in this territory because you do not have an available city token." << endl;
        // OK TO END, no need to loop
    }
}

//Destroys the army of the selected played
void Player::DestroyArmy(int numberOfArmiesToDestroy) {

    // TODO: "Which territory are you targeting? >> enter territory
    cout << "Which territory are you targeting?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory* targetTerritory = new Territory(); // placeholder

    if(targetTerritory->getArmySizeForPlayer()[*name_] > 0){
        cout << "You do not have an army in this territory and therefore can not attack anyone here. Please select"
                "another territory." << endl;
        //TODO LOOP
    }

    //TODO: "Which player would you like to attack?" >> list players who have armies on that territory
    cout << "Which player would you like to attach?" << endl;
    cout << "Using placeholder player..." << endl;
    string targetPlayer = "placeholder_name"; // placeholder

    //TODO: confirm player can be attacked
    targetTerritory->getArmySizeForPlayer()[targetPlayer] -= numberOfArmiesToDestroy;
    std::cout << "Army successfully destroyed" << std::endl;
    if (targetTerritory->getArmySizeForPlayer()[targetPlayer] < 0) {
        targetTerritory->getArmySizeForPlayer()[targetPlayer] = 0;
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
          costToMoveOverWater_(new int(*playerToCopy.costToMoveOverWater_)),
          canBeAttacked_(new bool(*playerToCopy.canBeAttacked_)){
    std::cout << "Calling the copy constructor" << std::endl;
}

//Constructor
Player::Player(const std::string &region,
               BiddingFacility *biddingFacility,
               const Territory &territory,
               const Cards &cards,
               int *tokenArmies,
               const int &cubes,
               int *disks,
               Hand *hand,
               int *money,
               const std::string &name,
               const int &totalMovementPointsForRound,
               const int &costToMoveOverWater,
               const bool &canBeAttacked)
        : region_(new std::string(region)),
          biddingFacility_(new BiddingFacility()),
          territory_(new Territory(territory)),
          cards_(new Cards(cards)),
          tokenArmies_(new int(0)),
          cubes_(new int(cubes)),
          disks_(new int(0)),
          hand_(new Hand()),
          money_(new int(0)),
          totalMovementPointsForRound_(new int(0)),
          costToMoveOverWater_(new int(3)),
          name_(new std::string(name)),
          canBeAttacked_(new bool(canBeAttacked)){
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
    // TODO need to build default constructor
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

int Player::getMoney() {
    return *money_;
}

BiddingFacility * Player::getBiddingFacility() {
    return biddingFacility_;
}

void Player::setMoney(int money) {
    money_ = new int(money);
}

int &Player::getTotalMovementPointsForRound() {
    return *totalMovementPointsForRound_;
}

void Player::setTotalMovementPointsForRound(const int &totalMovementPointsForRound) {
    totalMovementPointsForRound_ = std::unique_ptr<int>(new int(totalMovementPointsForRound));
}

void Player::ResolveActiveCard() {
    Cards* activeCard = hand_->GetActiveCard();

    if(*activeCard->GetActionTwo() != 0){ // if a second action exists
        AndOrAction();
    }else{
        switch(*(activeCard->GetActionOne())){
            case 1: //place i armies
                PlaceNewArmies(*(activeCard->GetActionOneValue()));
                break;
            case 2: //move i armies
                MoveArmies(*(activeCard->GetActionOneValue()));
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(*(activeCard->GetActionOneValue()));
                break;
        }
    }

}

void Player::SetArmiesTokens(int numberOfTokens) {
    tokenArmies_= new int (numberOfTokens);
}

int Player::GetArmiesTokens() {
    return *tokenArmies_;
}

int Player::GetCitiesDisks() {
    return *disks_;
}

void Player::SetCitiesDisks(int numberOfDisks) {
    disks_=new int (numberOfDisks);
}

void Player::RequestPlayerName() {
    string tempName;
    cout << "Please enter player's name: ";
    cin >> tempName;
    setName(tempName);
    biddingFacility_->SetLastName(tempName);
}

