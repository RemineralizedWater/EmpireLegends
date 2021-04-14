//Implementation class of Player class

#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

int Player::supply = 0;

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
void Player::PayCoin(const int &amountToPay) {
    money_ -= amountToPay;
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
        cout << "You have " << tokenArmies_ << " army tokens." << endl;
        //TODO LOOP
    }

    if(tokenArmies_ < numberOfArmiesToPlaced){
        cout << "You do not have enough armies left to place." << endl;
    }else{
        terr->getArmySizeForPlayer()[*name_] += numberOfArmiesToPlaced;
        tokenArmies_-=numberOfArmiesToPlaced;
        cout << "Your army has been successfully placed." << endl;
    }

    delete terr;
    terr = nullptr;
}

void Player::AndOrAction() {
    Cards* activeCard = hand_->GetActiveCard();

    string actionOneValue = to_string(activeCard->GetActionOneValue());
    string actionTwoValue = to_string(activeCard->GetActionTwoValue());
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};

    if(activeCard->GetActionOperator().compare("OR") == 0){
        int option;
        cout << "Would you like to: " << endl;
        cout << to_string(activeCard->GetActionOne()) + ": " + actions[activeCard->GetActionOne()] + actionOneValue + ", OR" << endl;
        cout << to_string(activeCard->GetActionTwo()) + ": " + actions[activeCard->GetActionTwo()] + actionTwoValue << endl;
        cout << "Option: ";
        cin >> option;

        // TODO: data validation on option

        switch(option){
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmies(activeCard->GetActionOneValue());
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(activeCard->GetActionOneValue());
                break;
        }
    }else if(activeCard->GetActionOperator().compare("AND") == 0){
        switch(activeCard->GetActionOne()){
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmies(activeCard->GetActionOneValue());
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(activeCard->GetActionOneValue());
                break;
        }
        switch(activeCard->GetActionTwo()){
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionTwoValue());
                break;
            case 2: //move i armies
                MoveArmies(activeCard->GetActionTwoValue());
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(activeCard->GetActionTwoValue());
                break;
        }
    }else{
        cout << "Error in Player.cpp.AndOrAction().";
        exit(0);
    }

    delete activeCard;
    activeCard = nullptr;
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

    delete territoryToMoveFrom;
    territoryToMoveFrom = nullptr;
    delete territoryToMoveTo;
    territoryToMoveTo = nullptr;
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

    if (disks_ > 0) {
        disks_ -= 1;
        terr->getHasCity()[*name_] = true;
        cout << "You have successfully built the city." << endl;
    } else {
        cout << "You cannot build a city in this territory because you do not have an available city token." << endl;
        // OK TO END, no need to loop
    }

    delete terr;
    terr = nullptr;
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

    delete targetTerritory;
    targetTerritory = nullptr;
}

//Copy constructor
Player::Player(const Player &playerToCopy)
        : region_(new std::string(*playerToCopy.region_)),
          biddingFacility_(new BiddingFacility(*playerToCopy.biddingFacility_)),
          territory_(new Territory(*playerToCopy.territory_)),
          cards_(new Cards(*playerToCopy.cards_)),
          tokenArmies_(playerToCopy.tokenArmies_),
          cubes_(new int(*playerToCopy.cubes_)),
          disks_(playerToCopy.disks_),
          money_(playerToCopy.money_),
          name_(new std::string(*playerToCopy.name_)),
          totalMovementPointsForRound_(new int(*playerToCopy.totalMovementPointsForRound_)),
          costToMoveOverWater_(new int(*playerToCopy.costToMoveOverWater_)),
          victoryPoints_(new int(*playerToCopy.victoryPoints_)),
          elixers_(new int(*playerToCopy.elixers_)),
          canBeAttacked_(new bool(*playerToCopy.canBeAttacked_))
          {
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
          tokenArmies_(0),
          cubes_(new int(cubes)),
          disks_(0),
          hand_(new Hand()),
          money_(0),
          totalMovementPointsForRound_(new int(0)),
          costToMoveOverWater_(new int(3)),
          name_(new std::string(name)),
          canBeAttacked_(new bool(canBeAttacked)),
          victoryPoints_(new int(0)),
          elixers_(new int(0)) {
}


//assignment operator
Player &Player::operator=(const Player &playerToCopy) {
    //TODO?
    return *this;
}

//stream insertion operation
std::istream &operator>>(std::istream &is, Player &player) {
    is >> *player.region_;
    is >> *player.biddingFacility_;
    is >> *player.territory_;
    is >> *player.cards_;
    is >> player.tokenArmies_;
    is >> *player.cubes_;
    is >> player.disks_;
    is >> player.money_;
    is >> *player.totalMovementPointsForRound_;
    is >> *player.costToMoveOverWater_;
    is >> *player.victoryPoints_;
    is >> *player.elixers_;
    return is;
}

Player::Player() {
    victoryPoints_=new int(0);
    elixers_=new int(0);
    // TODO need to build default constructor
}

Player::~Player() {
    if(hand_ != nullptr){
        delete hand_;
        hand_ = nullptr;
    }
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
    return money_;
}

BiddingFacility * Player::getBiddingFacility() {
    return biddingFacility_;
}

void Player::setMoney(int money) {
    money_ = money;
}

int Player::GetElixers() {
    return *elixers_;
}

void Player::SetElixers(int numElixers) {
    elixers_=new int{numElixers};
}

int Player::GetVictoryPoints(){
    return *victoryPoints_;
}
void Player::SetVictoryPoints(int points) {
    *victoryPoints_=points;
}

int &Player::getTotalMovementPointsForRound() {
    return *totalMovementPointsForRound_;
}

void Player::setTotalMovementPointsForRound(const int &totalMovementPointsForRound) {
    totalMovementPointsForRound_ = std::unique_ptr<int>(new int(totalMovementPointsForRound));
}

void Player::applyAbility() {
    //+ to move armies
    if(hand_->GetActiveCard()->GetGoods() == 1){
        //TODO 1 extra move each time player movesArmy
    }
        //"+ to place armies"
    else if(hand_->GetActiveCard()->GetGoods() == 2){
        //TODO gain one more army when placeArmies performed
    }
        //"- to move over water"
    else if(hand_->GetActiveCard()->GetGoods() == 3){
        //TODO reduce cost to move over water
    }
        //"+ elixirs"
    else if(hand_->GetActiveCard()->GetGoods() == 4){
        *elixers_+=hand_->GetActiveCard()->GetGoodsValue();
    }
        //"+ coins and 1+ elixirs"
    else if(hand_->GetActiveCard()->GetGoods() == 5){
        *elixers_+=1;
        money_+=hand_->GetActiveCard()->GetGoodsValue();
    }
        // "immune to attack"
    else if(hand_->GetActiveCard()->GetGoods() == 9){
        //TODO make immumne to attak

    }
}
void Player::ResolveActiveCard() {
    applyAbility();
    if(hand_->GetActiveCard()->GetActionTwo() != 0){ // if a second action exists
        AndOrAction();
    }else{
        switch(hand_->GetActiveCard()->GetActionOne()){
            case 1: //place i armies
                PlaceNewArmies(hand_->GetActiveCard()->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmies(hand_->GetActiveCard()->GetActionOneValue());
                break;
            case 3: // build city
                BuildCity();
                break;
            case 4: // destroy armies
                DestroyArmy(hand_->GetActiveCard()->GetActionOneValue());
                break;
        }
    }
}

void Player::SetArmiesTokens(int numberOfTokens) {
    tokenArmies_= numberOfTokens;
}

int Player::GetArmiesTokens() {
    return tokenArmies_;
}

int Player::GetCitiesDisks() {
    return disks_;
}

void Player::SetCitiesDisks(int numberOfDisks) {
    disks_= numberOfDisks;
}

void Player::RequestPlayerName() {
    string tempName;
    cout << "Please enter player's name: ";
    cin >> tempName;
    setName(tempName);
    biddingFacility_->SetLastName(tempName);
}
void Player::ComputeVPFlying(Cards c) {
    vector<Cards>* hand = hand_->GetHand();
    for(Cards c2:*hand){
        std::string::size_type pos = (c.GetName()).find(' ');
        if(c.GetGoodsSpecific()==(c.GetName()).substr(0, pos)){
            *victoryPoints_+=1;
        }
    }
}
void Player::ComputeVPNoble(Cards c) {
    int nobleCards=0;
    vector<Cards>* hand = hand_->GetHand();
    for(Cards c2:*hand){
        std::string::size_type pos = (c.GetName()).find(' ');
        if("Noble"==(c.GetName()).substr(0, pos)){
            nobleCards++;
        }
        if(nobleCards==3){
            *victoryPoints_+=c.GetGoodsValue();
        }
    }
}
void Player::ComputeVPMountain(Cards c) {
    vector<Cards>* hand = hand_->GetHand();
    int mountainCards=0;
    for(Cards c2:*hand){
        std::string::size_type pos = (c.GetName()).find(' ');
        if("Mountain"==(c.GetName()).substr(0, pos)){
            mountainCards++;
        }
        if(mountainCards==2){
            *victoryPoints_+=c.GetGoodsValue();
        }
    }

}
void Player::ComputeCards() {
    vector<Cards>* hand = hand_->GetHand();
    for(Cards c:*hand){
        //+ VP per card: flying
        if (c.GetGoods() == 6){
            ComputeVPFlying(c);
        }
            //+ VP for card: Noble x3
        else if(c.GetGoods() == 7){
            ComputeVPNoble(c);
        }
            //+ VP per 3 coins
        else if(c.GetGoods() == 8){
            *victoryPoints_+=money_*c.GetGoodsValue();
        }
            //+ VP for card: Mountain x2
        else if(c.GetGoods() == 10){
            ComputeVPMountain(c);

        }
    }
}
void Player::checkForMostElixers(int currentPlayerIndex,vector<Player*> players) {
    int maxElixers=*elixers_;
    vector<Player*> maxElixerPlayers;
    for(int i=0;i<players.size();i++){
        if(currentPlayerIndex==i){
            continue;
        }
        if(players[i]->GetElixers()>maxElixers){
            maxElixers=players[i]->GetElixers();
            maxElixerPlayers.clear();
        }
        if(players[i]->GetElixers()==maxElixers){
            maxElixerPlayers.push_back(players[i]);
        }
    }
    if(maxElixers==*elixers_&&maxElixerPlayers.size()==0){
        *victoryPoints_+=2;
    }
    else if (maxElixers==*elixers_&&maxElixerPlayers.size()!=0){
        *victoryPoints_+=1;
    }
}
/**
 * Compute a players score by updating its victory points based on card abilites, territories and continents owned
 * @param currentPlayerIndex
 * @param players
 * @param map
 */
void Player::ComputeScore(int currentPlayerIndex,vector<Player*> players,Map* map) {
    //looks at abilities from some of the cards the user owns and update VP if possible
    ComputeCards();

    //compare if this player has the most elixers and update victory points if it does
    checkForMostElixers(currentPlayerIndex,players);

    //keeps track of all territories controlled by players in a continent
    std::map<int,string> territoriesAndOwners;
    for(int i=1;i<(map->getMapSize()+1);i++){
        vector<Player*> maxArmyPlayers;

        Territory* t=map->findTerritory(i);
        //when the current territory belongs to a continent that is different from the continent of the territories stored in  territoriesAndOwners then find out who controls the continent in the map
        if(territoriesAndOwners.size() != 0 && to_string(t->getContinent()) != territoriesAndOwners[0]){

            //will keep track of the amount of territories each users owns in a continent
            std::map<string,int> playerControlledContinentTerritoriesCount;
            std::map<int, string>::iterator territoriesAndOwnersIt;

            for(territoriesAndOwnersIt = territoriesAndOwners.begin(); territoriesAndOwnersIt != territoriesAndOwners.end(); territoriesAndOwnersIt++){
                if(territoriesAndOwnersIt->first == 0){
                    continue;
                }
                //key exists so update the amount of territories the user owns to +1
                if(playerControlledContinentTerritoriesCount.find(territoriesAndOwnersIt->second) != playerControlledContinentTerritoriesCount.end()){
                    playerControlledContinentTerritoriesCount[territoriesAndOwnersIt->second]=(playerControlledContinentTerritoriesCount[territoriesAndOwnersIt->second] + 1);
                }
                //key does not exist so create an entry for territoriesAndOwnersIt
                else{
                    playerControlledContinentTerritoriesCount.insert(pair<string, int>(territoriesAndOwnersIt->second, 1));
                }
            }
            territoriesAndOwners.clear();

            int maxTerritoriesControlled=0;
            vector<string> maxTerritoriesControlledPlayerNames;
            std::map<string,int>::iterator playerControlledContinentTerritoriesCountIt;

            for(playerControlledContinentTerritoriesCountIt = playerControlledContinentTerritoriesCount.begin(); playerControlledContinentTerritoriesCountIt != playerControlledContinentTerritoriesCount.end(); playerControlledContinentTerritoriesCountIt++){
                if(maxTerritoriesControlled<playerControlledContinentTerritoriesCountIt->second){
                    maxTerritoriesControlled=playerControlledContinentTerritoriesCountIt->second;
                    maxTerritoriesControlledPlayerNames.clear();
                }
                if(maxTerritoriesControlled==playerControlledContinentTerritoriesCountIt->second){
                    maxTerritoriesControlledPlayerNames.push_back(playerControlledContinentTerritoriesCountIt->first);
                }
            }
            if(maxTerritoriesControlledPlayerNames.size()==1&&maxTerritoriesControlledPlayerNames[0]==*name_){
                *victoryPoints_+=1;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //TODO last and final run through

        int maxTerritoryArmySize=t->getArmySizeForPlayer()[*name_];
        int currentPlayerTerritoryArmySize=t->getArmySizeForPlayer()[*name_];
        if(t->getHasCity()[*name_]){
            currentPlayerTerritoryArmySize+=1;
            maxTerritoryArmySize+=1;
        }
        for(int l=0;l<players.size();l++){
             if(l==currentPlayerIndex){
                 continue;
             }
           int territoryArmySize=t->getArmySizeForPlayer()[players[l]->getName()];
             if(t->getHasCity()[players[l]->getName()]){
               territoryArmySize+=1;
           }
           if(maxTerritoryArmySize<territoryArmySize){
               maxTerritoryArmySize=territoryArmySize;
               maxArmyPlayers.clear();
           }
           if(maxTerritoryArmySize==territoryArmySize){
               maxArmyPlayers.push_back(players[l]);
           }

        }
        std::map<int, string>::iterator territoriesAndOwnersIt;

        //adding one entry in map to help during checking which continent's territories are being stored
        //key does not exist so create an entry for territoriesAndOwners
        if(territoriesAndOwners.find(0) == territoriesAndOwners.end()){
            territoriesAndOwners.insert(pair<int, string>(0, to_string(t->getContinent())));
        }
        if(maxTerritoryArmySize!=currentPlayerTerritoryArmySize&&maxArmyPlayers.size()==1){
            territoriesAndOwners.insert(pair<int, string>(t->getTerrId(), maxArmyPlayers[0]->getName()));
        }
         if(maxTerritoryArmySize==currentPlayerTerritoryArmySize&&maxArmyPlayers.size()==0){
             territoriesAndOwners.insert(pair<int, string>(t->getTerrId(), *name_));
             *victoryPoints_+=1;
         }


    }
}