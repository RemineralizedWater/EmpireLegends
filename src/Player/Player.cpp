//Implementation class of Player class

#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

int Player::Supply = 0;

//Default constructor
Player::Player() {
    region = "none";
    biddingFacility = new BiddingFacility();
    territory = unique_ptr<Territory>(new Territory());
    cards = unique_ptr<Cards>(new Cards());
    MyHand = new Hand();
    tokenArmies = 0;
    cubes = 0;
    victoryPoints = 0;
    elixirs = 0;
    disks = 0;
    money = 0;
    name = "none";
    totalMovementPointsForRound = 0;
    costToMoveOverWater = 3;
    canBeAttacked = true;
    map = new Map();
    extraArmyAbility=0;
    extraMoveAbility=0;
}

//Parametric constructor
Player::Player(string name_) {
    region = "none";
    biddingFacility = new BiddingFacility();
    territory = unique_ptr<Territory>(new Territory());
    cards = unique_ptr<Cards>(new Cards());
    MyHand = new Hand();
    tokenArmies = 0;
    cubes = 0;
    victoryPoints = 0;
    elixirs = 0;
    disks = 0;
    money = 0;
    name = name_;
    totalMovementPointsForRound = 0;
    costToMoveOverWater = 3;
    canBeAttacked = true;
    map = new Map();
    extraArmyAbility=0;
    extraMoveAbility=0;
}

//Parametric constructor
Player::Player(string region_, BiddingFacility *biddingFacility_, Territory &territory_, Cards &cards_,
               int tokenArmies_,
               int cubes_, int disks_, Hand *myHand_, int money_, string name_, int totalMovementPointsForRound_,
               int costToMoveOverWater_, bool canBeAttacked_, int victoryPoints_, int elixirs_, Map *map_,
               int extraMoveAbility_, int extraArmyAbility_)
        : region(region_),
          biddingFacility(biddingFacility_),
          territory(&territory_),
          cards(&cards_),
          tokenArmies(tokenArmies_),
          cubes(cubes_),
          disks(disks_),
          MyHand(myHand_),
          money(money_),
          totalMovementPointsForRound(totalMovementPointsForRound_),
          costToMoveOverWater(costToMoveOverWater_),
          name(name_),
          canBeAttacked(canBeAttacked_),
          victoryPoints(victoryPoints_),
          elixirs(elixirs_),
          map(map_),
          extraArmyAbility(extraArmyAbility_),
          extraMoveAbility(extraMoveAbility_){
    playerStrategies = new HumanStrategy();
}

//Copy constructor
Player::Player(const Player &playerToCopy)
        : region(playerToCopy.region),
          biddingFacility(new BiddingFacility(*playerToCopy.biddingFacility)),
          territory(new Territory(*playerToCopy.territory)),
          cards(new Cards(*playerToCopy.cards)),
          tokenArmies(playerToCopy.tokenArmies),
          cubes(playerToCopy.cubes),
          disks(playerToCopy.disks),
          money(playerToCopy.money),
          name(playerToCopy.name),
          totalMovementPointsForRound(playerToCopy.totalMovementPointsForRound),
          costToMoveOverWater(playerToCopy.costToMoveOverWater),
          victoryPoints(playerToCopy.victoryPoints),
          elixirs(playerToCopy.elixirs),
          canBeAttacked(playerToCopy.canBeAttacked),
          map(playerToCopy.map),
          extraMoveAbility(extraMoveAbility),
          extraArmyAbility(extraArmyAbility){
}

//Destructor
Player::~Player() {
    if (MyHand != nullptr) {
        delete MyHand;
        MyHand = nullptr;
    }
}

//assignment operator
Player &Player::operator=(Player &playerToCopy) {
    cards = move(playerToCopy.cards);
    region = move(playerToCopy.region);
    biddingFacility = playerToCopy.biddingFacility;
    MyHand = playerToCopy.MyHand;
    tokenArmies = playerToCopy.tokenArmies;
    cubes = playerToCopy.cubes;
    victoryPoints = playerToCopy.victoryPoints;
    elixirs = playerToCopy.elixirs;
    disks = playerToCopy.disks;
    money = playerToCopy.money;
    name = playerToCopy.name;
    totalMovementPointsForRound = playerToCopy.totalMovementPointsForRound;
    costToMoveOverWater = playerToCopy.costToMoveOverWater;
    canBeAttacked = playerToCopy.canBeAttacked;
    extraArmyAbility=playerToCopy.extraArmyAbility;
    extraMoveAbility=playerToCopy.extraMoveAbility;
    return *this;
}

//stream insertion operation
std::istream &operator>>(std::istream &is, Player &player) {
    is >> player.region;
    is >> *player.biddingFacility;
    is >> *player.territory;
    is >> *player.cards;
    is >> player.tokenArmies;
    is >> player.cubes;
    is >> player.disks;
    is >> player.money;
    is >> player.totalMovementPointsForRound;
    is >> player.costToMoveOverWater;
    is >> player.victoryPoints;
    is >> player.elixirs;
    is >> player.extraMoveAbility;
    is >> player.extraArmyAbility;
    return is;
}

// Accessors
string Player::GetName() {
    return name;
}

int Player::GetCostOverWater() {
    return costToMoveOverWater;
}

int Player::GetMoney() {
    return money;
}

BiddingFacility *Player::GetBiddingFacility() {
    return biddingFacility;
}

int Player::GetElixirs() {
    return elixirs;
}

int Player::GetVictoryPoints() {
    return victoryPoints;
}

int Player::GetTotalMovementPointsForRound() {
    return totalMovementPointsForRound;
}

Map *Player::GetMap() {
    return map;
}

int Player::GetArmiesTokens() {
    return tokenArmies;
}

int Player::GetCitiesDisks() {
    return disks;
}

// Mutators
void Player::SetCostOverWater(int costToMoveOverWater_) {
    costToMoveOverWater = costToMoveOverWater_;
}

void Player::SetName(string name_) {
    name = name_;
    Notify();
}

void Player::SetMoney(int money_) {
    money = money_;
    Notify();
}

void Player::SetElixirs(int numberOfElixirs) {
    elixirs = numberOfElixirs;
}

void Player::SetVictoryPoints(int points) {
    victoryPoints = points;
    Notify();
}

void Player::SetTotalMovementPointsForRound(int totalMovementPointsForRound_) {
    totalMovementPointsForRound = totalMovementPointsForRound_;
}

void Player::SetMap(Map *map_) {
    map = map_;
}

void Player::SetArmiesTokens(int numberOfTokens) {
    tokenArmies = numberOfTokens;
    Notify();
}

void Player::SetCitiesDisks(int numberOfDisks) {
    disks = numberOfDisks;
    Notify();
}

void Player::SetStrategy(PlayerStrategies *newPlayerStrategy) {
    this->playerStrategies = newPlayerStrategy;
}

PlayerStrategies * Player::GetStrategy() {
    return this->playerStrategies;
}

//Successfully pays coin and withdraws money from said player account
void Player::PaysCoinFromPlayer(int amountToPay) {
    money -= amountToPay;
    Supply += amountToPay;
    cout << "The transaction has been successful, we have removed: " << amountToPay << " coins." << endl;
}
void Player::PlaceNewArmies(int numberOfArmiesToPlace, int position, bool twoPlayerSetup, bool setup) {
    numberOfArmiesToPlace+=extraArmyAbility;
    int armiesToPlace = numberOfArmiesToPlace;
    bool placedCity = false;

    if(!twoPlayerSetup) {
        if (tokenArmies < armiesToPlace)
            armiesToPlace = tokenArmies;

        if (armiesToPlace == 0) {
            cout << "You do not have any armies left to place." << endl;
            return;
        }
    }

    while (!placedCity) {
        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == position) {
                if ((*terrIt).first->GetHasCity()[name]&&!setup) {
                    (*terrIt).first->AddArmySizeForPlayer(name, armiesToPlace);
                    cout << armiesToPlace << " armies have been added to territory "<< position<< endl;
                    tokenArmies -= armiesToPlace;
                    placedCity = true;
                }
                else if(setup&&twoPlayerSetup){
                    (*terrIt).first->AddArmySizeForPlayer(name, armiesToPlace);
                    cout << armiesToPlace << " armies have been added to territory "<< position<< endl;
                    placedCity = true;
                }
                else if(setup){
                    (*terrIt).first->AddArmySizeForPlayer(name, armiesToPlace);
                    cout << armiesToPlace << " armies have been added to territory "<< position<< endl;
                    tokenArmies -= armiesToPlace;
                    placedCity = true;
                }
                else {
                    cout << "You do not have a city in this territory, choose a different territory." << endl;
                }
                break;
            }
        }
    }
}
//Places armies for desired player
void Player::PlaceNewArmies(int numberOfArmiesToPlace) {
    numberOfArmiesToPlace+=extraArmyAbility;
    int armiesToPlace = numberOfArmiesToPlace;
    int position;
    bool placedCity = false;

    if (tokenArmies < armiesToPlace)
        armiesToPlace = tokenArmies;

    if (armiesToPlace == 0) {
        cout << "You do not have any armies left to place." << endl;
        return;
    }

    map->Display();

    while (!placedCity) {
        string tempPosition;
        cout << "Which territory would you like to place armies in?";
        cin >> tempPosition;
        position=stoi(tempPosition);
        cout<<position<<endl;

        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == position) {
                if ((*terrIt).first->GetHasCity()[name]) {
                    (*terrIt).first->AddArmySizeForPlayer(name, armiesToPlace);
                    cout << armiesToPlace << " armies have been added to the territory!" << endl;
                    tokenArmies -= armiesToPlace;
                    placedCity = true;
                } else {
                    cout << "You do not have a city in this territory, choose a different territory." << endl;
                }
                break;
            }
        }
    }
}

void Player::AndOrAction() {
    Cards *activeCard = MyHand->GetActiveCard();

    string actionOneValue = to_string(activeCard->GetActionOneValue());
    string actionTwoValue = to_string(activeCard->GetActionTwoValue());
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};

    if (activeCard->GetActionOperator().compare("OR") == 0) {
        int option;
        cout << "Would you like to: " << endl;
        cout << to_string(activeCard->GetActionOne()) + ": " + actions[activeCard->GetActionOne()] + actionOneValue +
                ", OR" << endl;
        cout << to_string(activeCard->GetActionTwo()) + ": " + actions[activeCard->GetActionTwo()] + actionTwoValue
             << endl;
        cout << "Option: ";
        cin >> option;

        // TODO: data validation on option

        switch (option) {
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmiesForPlayer(activeCard->GetActionOneValue());
                break;
            case 3: // build city
                BuildCityForPlayer();
                break;
            case 4: // destroy armies
                DestroysNumberOfArmyOfPlayer(activeCard->GetActionOneValue());
                break;
        }
    } else if (activeCard->GetActionOperator().compare("AND") == 0) {
        switch (activeCard->GetActionOne()) {
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmiesForPlayer(activeCard->GetActionOneValue());
                break;
            case 3: // build city
                BuildCityForPlayer();
                break;
            case 4: // destroy armies
                DestroysNumberOfArmyOfPlayer(activeCard->GetActionOneValue());
                break;
        }
        switch (activeCard->GetActionTwo()) {
            case 1: //place i armies
                PlaceNewArmies(activeCard->GetActionTwoValue());
                break;
            case 2: //move i armies
                MoveArmiesForPlayer(activeCard->GetActionTwoValue());
                break;
            case 3: // build city
                BuildCityForPlayer();
                break;
            case 4: // destroy armies
                DestroysNumberOfArmyOfPlayer(activeCard->GetActionTwoValue());
                break;
        }
    } else {
        cout << "Error in Player.cpp.AndOrAction().";
        exit(0);
    }

    // Memory clean up
    if (activeCard != nullptr) {
        delete activeCard;
        activeCard = nullptr;
    }
}

//Moves army for desired player
void Player::MoveArmiesForPlayer(int numberOfArmiesToMove) {
    numberOfArmiesToMove+=extraMoveAbility;
    int toID, fromID;
    bool movedArmies = false;

    map->Display();

    while (!movedArmies) {
        int armiesToMove = numberOfArmiesToMove;

        cout << "Which territory would you like to move armies FROM?";
        string tempFromID;
        cin >> tempFromID;
        fromID=stoi(tempFromID);
        cout<<fromID<<endl;
        cout << "Which territory would you like to move armies TO?";
        string tempToID;
        cin >> tempToID;
        tempToID=stoi(tempToID);
        cout<<tempToID<<endl;

        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == fromID) {
                if ((*terrIt).first->GetNumberOfArmies(name) > 0) {

                    if ((*terrIt).first->GetNumberOfArmies(name) < armiesToMove)
                        armiesToMove = (*terrIt).first->GetNumberOfArmies(name);

                    vector<terrInfo>::iterator terrIt2;
                    for (terrIt2 = map->GetTerrAndAdjsList()->begin();
                         terrIt2 != map->GetTerrAndAdjsList()->end(); ++terrIt2) {

                        if ((*terrIt2).first->GetTerrId() == toID) {
                            (*terrIt2).first->AddArmySizeForPlayer(name, armiesToMove);
                            (*terrIt).first->RemoveArmySizeForPlayer(name, armiesToMove);
                            movedArmies = true;
                        }
                    }
                } else {
                    cout << "You do not have enough armies to move, cannot move armies." << endl;
                    movedArmies = true;
                    break;
                }
            }
        }
    }
}
//Moves army for desired player
void Player::MoveArmiesForPlayer(int numberOfArmiesToMove, int toID, int fromID) {
    numberOfArmiesToMove+=extraMoveAbility;
    bool movedArmies = false;

    map->Display();

    while (!movedArmies) {
        int armiesToMove = numberOfArmiesToMove;

        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == fromID) {
                if ((*terrIt).first->GetNumberOfArmies(name) > 0) {

                    if ((*terrIt).first->GetNumberOfArmies(name) < armiesToMove)
                        armiesToMove = (*terrIt).first->GetNumberOfArmies(name);

                    vector<terrInfo>::iterator terrIt2;
                    for (terrIt2 = map->GetTerrAndAdjsList()->begin();
                         terrIt2 != map->GetTerrAndAdjsList()->end(); ++terrIt2) {

                        if ((*terrIt2).first->GetTerrId() == toID) {
                            (*terrIt2).first->AddArmySizeForPlayer(name, armiesToMove);
                            (*terrIt).first->RemoveArmySizeForPlayer(name, armiesToMove);
                            movedArmies = true;
                        }
                    }
                } else {
                    cout << "You do not have enough armies to move, cannot move armies." << endl;
                    movedArmies = true;
                    break;
                }
            }
        }
    }
}

//Move over land for desired player
void Player::MoveOverLandForPlayer() {
    if (totalMovementPointsForRound > 0) {
        (totalMovementPointsForRound)--;
        cout << "You have successfully moved over land" << endl;
    } else {
        cout << "You have not successfully moved over land because your total movement points for round are at 0" << endl;
    }
}

void Player::MoveOverWaterForPlayer() {
    if (totalMovementPointsForRound > costToMoveOverWater) {
        (totalMovementPointsForRound) -= costToMoveOverWater;
        cout << "You have successfully moved over water" << endl;
    } else {
        cout << "You have not successfully moved over water because your total movement points for round are at 0 or"
                   " smaller than the amount you have" << endl;
    }
}


//Builds city for desired player
void Player::BuildCityForPlayer() {
    bool builtCity = false;
    int cityTargetID;

    if (disks <= 0) {
        cout << "You do not have enough cities to build a new one." << endl;
        return;
    }

    while (!builtCity) {
        cout << "Which territory would you like to build a city in? (a city will be built regardless if you already have a city there)";
        string tempCityTargetID;
        cin >> tempCityTargetID;
        cityTargetID=stoi(tempCityTargetID);
        cout<<cityTargetID<<endl;

        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == cityTargetID) {
                (*terrIt).first->AddCityForPlayer(name);
                disks -= 1;
                builtCity = true;
                break;
            }
        }
        if (!builtCity)
            cout << "Enter a valid territory ID." << endl;
    }
}

//Destroys the army of the selected played
void Player::DestroysNumberOfArmyOfPlayer(int numberOfArmiesToDestroy) {
    int targetTerritoryID;
    bool hasAttacked = false;

    while (!hasAttacked) {
        int armiesToDestroy = numberOfArmiesToDestroy;
        string targetName;

        cout << "Who are you targeting?";
        cin >> targetName;
        cout<<targetName<<endl;
        cout << "Which territory are you targeting?";
        string tempTargetTerritoryID;
        cin >> tempTargetTerritoryID;
        targetTerritoryID=stoi(tempTargetTerritoryID);
        cout<<tempTargetTerritoryID<<endl;

        typedef pair<Territory *, vector<Adjacency> *> terrInfo;
        vector<terrInfo>::iterator terrIt;
        for (terrIt = map->GetTerrAndAdjsList()->begin();
             terrIt != map->GetTerrAndAdjsList()->end(); ++terrIt) {

            if ((*terrIt).first->GetTerrId() == targetTerritoryID && (*terrIt).first->HasArmies(name)) {
                if ((*terrIt).first->HasArmies(targetName)) {
                    if ((*terrIt).first->GetNumberOfArmies(targetName) < armiesToDestroy)
                        armiesToDestroy = (*terrIt).first->GetNumberOfArmies(targetName);

                    (*terrIt).first->RemoveArmySizeForPlayer(targetName, armiesToDestroy);
                    cout << armiesToDestroy << " armies have been removed from territory " << targetTerritoryID << endl;
                } else {
                    cout << "That player does not have armies in this territory to attack. No armies have been removed." << endl;
                }

                hasAttacked = true;
                break;
            }
        }
        if (!hasAttacked)
            cout << "Enter a valid territory ID that you have armies in." << endl;
    }
}

void Player::ApplyAbility() {
    //+ to move armies
    if (MyHand->GetActiveCard()->GetGoods() == 1) {
        extraMoveAbility+=MyHand->GetActiveCard()->GetGoodsValue();
    }
        //"+ to place armies"
    else if (MyHand->GetActiveCard()->GetGoods() == 2) {
        extraArmyAbility+=MyHand->GetActiveCard()->GetGoodsValue();
    }
        //"- to move over water"
    else if (MyHand->GetActiveCard()->GetGoods() == 3) {
        if(costToMoveOverWater>=MyHand->GetActiveCard()->GetGoodsValue()){
            costToMoveOverWater-=MyHand->GetActiveCard()->GetGoodsValue();
        }
    }
        //"+ elixirs"
    else if (MyHand->GetActiveCard()->GetGoods() == 4) {
        elixirs += MyHand->GetActiveCard()->GetGoodsValue();
    }
        //"+ coins and 1+ elixirs"
    else if (MyHand->GetActiveCard()->GetGoods() == 5) {
        elixirs += 1;
        money += MyHand->GetActiveCard()->GetGoodsValue();
    }
        // "immune to attack"
    else if (MyHand->GetActiveCard()->GetGoods() == 9) {
        canBeAttacked=false;

    }
}

void Player::ResolveActiveCard() {
    ApplyAbility();
    if (MyHand->GetActiveCard()->GetActionTwo() != 0) { // if a second action exists
        AndOrAction();
    } else {
        switch (MyHand->GetActiveCard()->GetActionOne()) {
            case 1: //place i armies
                PlaceNewArmies(MyHand->GetActiveCard()->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmiesForPlayer(MyHand->GetActiveCard()->GetActionOneValue());
                break;
            case 3: // build city
                BuildCityForPlayer();
                break;
            case 4: // destroy armies
                DestroysNumberOfArmyOfPlayer(MyHand->GetActiveCard()->GetActionOneValue());
                break;
        }
    }
    Notify();
}

void Player::RequestPlayerName() {
    string tempName;
    cout << "Please enter player's name: ";
    cin >> tempName;
    SetName(tempName);
    biddingFacility->SetLastName(tempName);
}

void Player::ComputeVPFlying(Cards cards) {
    vector<Cards> *tempHand = MyHand->GetHand();
    for (Cards c2:*tempHand) {
        string::size_type pos = (cards.GetName()).find(' ');
        if (cards.GetGoodsSpecific() == (cards.GetName()).substr(0, pos)) {
            victoryPoints += 1;
        }
    }
}

void Player::ComputeVPNoble(Cards cards) {
    int nobleCards = 0;
    vector<Cards> *hand = MyHand->GetHand();
    for (Cards c2:*hand) {
        string::size_type pos = (cards.GetName()).find(' ');
        if ("Noble" == (cards.GetName()).substr(0, pos)) {
            nobleCards++;
        }
        if (nobleCards == 3) {
            victoryPoints += cards.GetGoodsValue();
        }
    }
}

void Player::ComputeVPMountain(Cards cards) {
    vector<Cards> *hand = MyHand->GetHand();
    int mountainCards = 0;
    for (Cards c2:*hand) {
        string::size_type pos = (cards.GetName()).find(' ');
        if ("Mountain" == (cards.GetName()).substr(0, pos)) {
            mountainCards++;
        }
        if (mountainCards == 2) {
            victoryPoints += cards.GetGoodsValue();
        }
    }
}

void Player::ComputeCards() {
    vector<Cards> *hand = MyHand->GetHand();
    for (Cards c:*hand) {
        //+ VP per card: flying
        if (c.GetGoods() == 6) {
            ComputeVPFlying(c);
        }
            //+ VP for card: Noble x3
        else if (c.GetGoods() == 7) {
            ComputeVPNoble(c);
        }
            //+ VP per 3 coins
        else if (c.GetGoods() == 8) {
            victoryPoints += money *c.GetGoodsValue();
        }
            //+ VP for card: Mountain x2
        else if (c.GetGoods() == 10) {
            ComputeVPMountain(c);
        }
    }
}

void Player::CheckForMostElixirsForPlayer(int currentPlayerIndex, vector<Player *> players) {
    int maxElixirs = elixirs;
    vector<Player *> maxElixirPlayers;
    for (int i = 0; i < players.size(); i++) {
        if (currentPlayerIndex == i) {
            continue;
        }
        if (players[i]->GetElixirs() > maxElixirs) {
            maxElixirs = players[i]->GetElixirs();
            maxElixirPlayers.clear();
        }
        if (players[i]->GetElixirs() == maxElixirs) {
            maxElixirPlayers.push_back(players[i]);
        }
    }
    if (maxElixirs == elixirs && maxElixirPlayers.size() == 0) {
        victoryPoints += 2;
    } else if (maxElixirs == elixirs && maxElixirPlayers.size() != 0) {
        victoryPoints += 1;
    }
}

/**
 * Compute a players score by updating its victory points based on card abilites, territories and continents owned
 * @param currentPlayerIndex
 * @param players
 * @param map
 */
void Player::ComputeScore(int currentPlayerIndex, vector<Player *> players, Map *map) {
    //looks at abilities from some of the cards the user owns and update VP if possible
    ComputeCards();

    //compare if this player has the most elixirs and update victory points if it does
    CheckForMostElixirsForPlayer(currentPlayerIndex, players);

    //keeps track of all territories controlled by players in a continent
    std::map<int, string> territoriesAndOwners;
    for (int i = 1; i < (map->GetMapSize() + 1); i++) {
        vector<Player *> maxArmyPlayers;

        Territory *t = map->FindTerritory(i);
        //when the current territory belongs to a continent that is different from the continent of the territories stored in  territoriesAndOwners then find out who controls the continent in the map

        if (territoriesAndOwners.size() != 0 && to_string(t->GetContinent()) != territoriesAndOwners[0]) {

            //will keep track of the amount of territories each users owns in a continent
            std::map<string, int> playerControlledContinentTerritoriesCount;
            std::map<int, string>::iterator territoriesAndOwnersIt;

            for (territoriesAndOwnersIt = territoriesAndOwners.begin();
                 territoriesAndOwnersIt != territoriesAndOwners.end(); territoriesAndOwnersIt++) {
                if (territoriesAndOwnersIt->first == 0) {
                    continue;
                }
                //key exists so update the amount of territories the user owns to +1
                if (playerControlledContinentTerritoriesCount.find(territoriesAndOwnersIt->second) !=
                    playerControlledContinentTerritoriesCount.end()) {
                    playerControlledContinentTerritoriesCount[territoriesAndOwnersIt->second] = (
                            playerControlledContinentTerritoriesCount[territoriesAndOwnersIt->second] + 1);
                }
                    //key does not exist so create an entry for territoriesAndOwnersIt
                else {
                    playerControlledContinentTerritoriesCount.insert(
                            pair<string, int>(territoriesAndOwnersIt->second, 1));
                }
            }
            territoriesAndOwners.clear();

            int maxTerritoriesControlled = 0;
            vector<string> maxTerritoriesControlledPlayerNames;
            std::map<string, int>::iterator playerControlledContinentTerritoriesCountIt;

            for (playerControlledContinentTerritoriesCountIt = playerControlledContinentTerritoriesCount.begin();
                 playerControlledContinentTerritoriesCountIt !=
                 playerControlledContinentTerritoriesCount.end(); playerControlledContinentTerritoriesCountIt++) {
                if (maxTerritoriesControlled < playerControlledContinentTerritoriesCountIt->second) {
                    maxTerritoriesControlled = playerControlledContinentTerritoriesCountIt->second;
                    maxTerritoriesControlledPlayerNames.clear();
                }
                if (maxTerritoriesControlled == playerControlledContinentTerritoriesCountIt->second) {
                    maxTerritoriesControlledPlayerNames.push_back(playerControlledContinentTerritoriesCountIt->first);
                }
            }
            if (maxTerritoriesControlledPlayerNames.size() == 1 && maxTerritoriesControlledPlayerNames[0] == name) {
                victoryPoints += 1;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //TODO last and final run through

        int maxTerritoryArmySize = t->GetArmySizeForPlayer()[name];
        int currentPlayerTerritoryArmySize = t->GetArmySizeForPlayer()[name];
        if (t->GetHasCity()[name]) {
            currentPlayerTerritoryArmySize += 1;
            maxTerritoryArmySize += 1;
        }
        for (int l = 0; l < players.size(); l++) {
            if (l == currentPlayerIndex) {
                continue;
            }
            int territoryArmySize = t->GetArmySizeForPlayer()[players[l]->GetName()];
            if (t->GetHasCity()[players[l]->GetName()]) {
                territoryArmySize += 1;
            }
            if (maxTerritoryArmySize < territoryArmySize) {
                maxTerritoryArmySize = territoryArmySize;
                maxArmyPlayers.clear();
            }
            if (maxTerritoryArmySize == territoryArmySize) {
                maxArmyPlayers.push_back(players[l]);
            }

        }
        std::map<int, string>::iterator territoriesAndOwnersIt;

        //adding one entry in map to help during checking which continent's territories are being stored
        //key does not exist so create an entry for territoriesAndOwners

        if (territoriesAndOwners.find(0) == territoriesAndOwners.end()) {
            territoriesAndOwners.insert(pair<int, string>(0, to_string(t->GetContinent())));
        }
        if (maxTerritoryArmySize != currentPlayerTerritoryArmySize && maxArmyPlayers.size() == 1) {
            territoriesAndOwners.insert(pair<int, string>(t->GetTerrId(), maxArmyPlayers[0]->GetName()));
        }
        if (maxTerritoryArmySize == currentPlayerTerritoryArmySize && maxArmyPlayers.size() == 0) {
            territoriesAndOwners.insert(pair<int, string>(t->GetTerrId(), name));
            victoryPoints += 1;
        }
    }
}

void Player::ExecuteStrategy(Deck *deck, int numPlayer) {
    cout << "======== " << this->GetName() << "'s TURN ========" << endl;
    this->playerStrategies->Execute(deck, this, numPlayer);
}
