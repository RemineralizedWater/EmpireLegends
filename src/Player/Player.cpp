//Implementation class of Player class

#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

int Player::Supply = 0;

//Default constructor
Player::Player() {
    victoryPoints = 0;
    elixirs = 0;
    // TODO need to build default constructor
}

//Parametric constructor
Player::Player(string region_,
               BiddingFacility *biddingFacility_,
               Territory &territory_,
               Cards &cards_,
               int tokenArmies_,
               int cubes_,
               int disks_,
               Hand *hand_,
               int money_,
               string name_,
               int totalMovementPointsForRound_,
               int costToMoveOverWater_,
               bool canBeAttacked_,
               int victoryPoints_,
               int elixirs_)
        : region(region_),
          biddingFacility(biddingFacility_),
          territory(&territory_),
          cards(&cards_),
          tokenArmies(tokenArmies_),
          cubes(cubes_),
          disks(disks_),
          Hands(hand_),
          money(money_),
          totalMovementPointsForRound(totalMovementPointsForRound_),
          costToMoveOverWater(costToMoveOverWater_),
          name(name_),
          canBeAttacked(canBeAttacked_),
          victoryPoints(victoryPoints_),
          elixirs(elixirs_) {
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
          canBeAttacked(playerToCopy.canBeAttacked) {
}

//Destructor
Player::~Player() {
    if (Hands != nullptr) {
        delete Hands;
        Hands = nullptr;
    }
}

//assignment operator
Player &Player::operator=(const Player &playerToCopy) {
    //TODO?
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
    return is;
}

string Player::GetName() {
    return name;
}

void Player::SetName(string name_) {
    name = name_;
}

int Player::GetCostOverWater() {
    return costToMoveOverWater;
}

void Player::SetCostOverWater(int costToMoveOverWater_) {
    costToMoveOverWater = costToMoveOverWater_;
}

int Player::GetMoney() {
    return money;
}

BiddingFacility *Player::GetBiddingFacility() {
    return biddingFacility;
}

void Player::SetMoney(int money_) {
    money = money_;
}

int Player::GetElixirs() {
    return elixirs;
}

void Player::SetElixirs(int numberOfElixirs) {
    elixirs = numberOfElixirs;
}

int Player::GetVictoryPoints() {
    return victoryPoints;
}

void Player::SetVictoryPoints(int points) {
    victoryPoints = points;
}

int Player::GetTotalMovementPointsForRound() {
    return totalMovementPointsForRound;
}

void Player::SetTotalMovementPointsForRound(int totalMovementPointsForRound_) {
    totalMovementPointsForRound = totalMovementPointsForRound_;
}

void Player::SetArmiesTokens(int numberOfTokens) {
    tokenArmies = numberOfTokens;
}

int Player::GetArmiesTokens() {
    return tokenArmies;
}

int Player::GetCitiesDisks() {
    return disks;
}

void Player::SetCitiesDisks(int numberOfDisks) {
    disks = numberOfDisks;
}

//Successfully pays coin and withdraws money from said player account (for Ass1. just returns
void Player::PaysCoinFromPlayer(int amountToPay) {
    money -= amountToPay;
    Supply += amountToPay;
    std::cout << "The transaction has been successful, we have removed: " << amountToPay << " coins." << std::endl;
}

//Places armies for desired player
void Player::PlaceNewArmies(int numberOfArmiesToPlaced) {

    // TODO: "Which territory would you like to place armies in?" >> get territory id
    cout << "Which territory would you like to place armies in? " << endl;
    cout << "Using placeholder territory.." << endl;
    Territory *terr = new Territory();  // placeholder for testing
    terr->InsertNewArmyPlayerMapping(name); // placeholder for testing
    terr->InsertNewCityPlayerMapping(name); // placeholder for testing
    terr->GetHasCity()[name] = true; // placeholder for testing

    if (!terr->GetHasCity()[name]) {
        cout << "You do not have a city in this territory, please choose another territory." << endl;
        cout << "You have " << tokenArmies << " army tokens." << endl;
        //TODO LOOP
    }

    if (tokenArmies < numberOfArmiesToPlaced) {
        cout << "You do not have enough armies left to place." << endl;
    } else {
        terr->GetArmySizeForPlayer()[name] += numberOfArmiesToPlaced;
        tokenArmies -= numberOfArmiesToPlaced;
        cout << "Your army has been successfully placed." << endl;
    }

    delete terr;
    terr = nullptr;
}

void Player::AndOrAction() {
    Cards *activeCard = Hands->GetActiveCard();

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

    delete activeCard;
    activeCard = nullptr;
}

//Moves army for desired player
void Player::MoveArmiesForPlayer(int numberOfArmiesToMove) {

    // TODO: "Which territory would you like to move FROM? >> enter Territory.
    cout << "Which territory would you like to move armies FROM?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory *territoryToMoveFrom = new Territory(); // placeholder
    // TODO: "Which territory would you like to move TO? >> enter Territory.
    cout << "Which territory would you like to move armies TO?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory *territoryToMoveTo = new Territory(); // placeholder

    //TODO: needs to move one at a time, not the full amount passed.
    if (territoryToMoveFrom->GetArmySizeForPlayer()[name] >= numberOfArmiesToMove) {
        territoryToMoveFrom->GetArmySizeForPlayer()[name] -= numberOfArmiesToMove;
        territoryToMoveTo->GetArmySizeForPlayer()[name] += numberOfArmiesToMove;
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
void Player::MoveOverLandForPlayer() {
    if (totalMovementPointsForRound > 0) {
        (totalMovementPointsForRound)--;
        std::cout << "You have successfully moved over land" << std::endl;
    } else {
        std::cout << "You have not successfully moved over land because your total movement points for round are at 0"
                  << std::endl;
    }
}

void Player::MoveOverWaterForPlayer() {
    if (totalMovementPointsForRound > costToMoveOverWater) {
        (totalMovementPointsForRound) -= costToMoveOverWater;
        std::cout << "You have successfully moved over water" << std::endl;
    } else {
        std::cout
                << "You have not successfully moved over water because your total movement points for round are at 0 or smaller than the amount you have"
                << std::endl;
    }
}


//Builds city for desired player
void Player::BuildCityForPlayer() {

    //TODO: "Which territory would you like to build a city in?" >> enter city.
    cout << "Which territory would you like to build a city in?" << endl;
    cout << "Using placeholder city..." << endl;
    Territory *terr = new Territory(); // placeholder

    for (const std::pair<std::string, bool> &pair: terr->GetHasCity()) {
        if (pair.second) {
            cout << "The player " << pair.first << " has already built a city in this territory." << endl;
            //TODO: LOOP
        }
    }

    if (disks > 0) {
        disks -= 1;
        terr->GetHasCity()[name] = true;
        cout << "You have successfully built the city." << endl;
    } else {
        cout << "You cannot build a city in this territory because you do not have an available city token." << endl;
        // OK TO END, no need to loop
    }

    delete terr;
    terr = nullptr;
}

//Destroys the army of the selected played
void Player::DestroysNumberOfArmyOfPlayer(int numberOfArmiesToDestroy) {

    // TODO: "Which territory are you targeting? >> enter territory
    cout << "Which territory are you targeting?" << endl;
    cout << "Using placeholder territory..." << endl;
    Territory *targetTerritory = new Territory(); // placeholder

    if (targetTerritory->GetArmySizeForPlayer()[name] > 0) {
        cout << "You do not have an army in this territory and therefore can not attack anyone here. Please select"
                "another territory." << endl;
        //TODO LOOP
    }

    //TODO: "Which player would you like to attack?" >> list players who have armies on that territory
    cout << "Which player would you like to attach?" << endl;
    cout << "Using placeholder player..." << endl;
    string targetPlayer = "placeholder_name"; // placeholder

    //TODO: confirm player can be attacked
    targetTerritory->GetArmySizeForPlayer()[targetPlayer] -= numberOfArmiesToDestroy;
    std::cout << "Army successfully destroyed" << std::endl;
    if (targetTerritory->GetArmySizeForPlayer()[targetPlayer] < 0) {
        targetTerritory->GetArmySizeForPlayer()[targetPlayer] = 0;
    }

    delete targetTerritory;
    targetTerritory = nullptr;
}

void Player::ApplyAbility() {
    //+ to move armies
    if (Hands->GetActiveCard()->GetGoods() == 1) {
        //TODO 1 extra move each time player movesArmy
    }
        //"+ to place armies"
    else if (Hands->GetActiveCard()->GetGoods() == 2) {
        //TODO gain one more army when placeArmies performed
    }
        //"- to move over water"
    else if (Hands->GetActiveCard()->GetGoods() == 3) {
        //TODO reduce cost to move over water
    }
        //"+ elixirs"
    else if (Hands->GetActiveCard()->GetGoods() == 4) {
        elixirs += Hands->GetActiveCard()->GetGoodsValue();
    }
        //"+ coins and 1+ elixirs"
    else if (Hands->GetActiveCard()->GetGoods() == 5) {
        elixirs += 1;
        money += Hands->GetActiveCard()->GetGoodsValue();
    }
        // "immune to attack"
    else if (Hands->GetActiveCard()->GetGoods() == 9) {
        //TODO make immune to attack

    }
}

void Player::ResolveActiveCard() {
    ApplyAbility();
    if (Hands->GetActiveCard()->GetActionTwo() != 0) { // if a second action exists
        AndOrAction();
    } else {
        switch (Hands->GetActiveCard()->GetActionOne()) {
            case 1: //place i armies
                PlaceNewArmies(Hands->GetActiveCard()->GetActionOneValue());
                break;
            case 2: //move i armies
                MoveArmiesForPlayer(Hands->GetActiveCard()->GetActionOneValue());
                break;
            case 3: // build city
                BuildCityForPlayer();
                break;
            case 4: // destroy armies
                DestroysNumberOfArmyOfPlayer(Hands->GetActiveCard()->GetActionOneValue());
                break;
        }
    }
}

void Player::RequestPlayerName() {
    string tempName;
    cout << "Please enter player's name: ";
    cin >> tempName;
    SetName(tempName);
    biddingFacility->SetLastName(tempName);
}

void Player::ComputeVPFlying(Cards cards) {
    vector<Cards> *hand = Hands->GetHand();
    for (Cards c2:*hand) {
        std::string::size_type pos = (cards.GetName()).find(' ');
        if (cards.GetGoodsSpecific() == (cards.GetName()).substr(0, pos)) {
            victoryPoints += 1;
        }
    }
}

void Player::ComputeVPNoble(Cards cards) {
    int nobleCards = 0;
    vector<Cards> *hand = Hands->GetHand();
    for (Cards c2:*hand) {
        std::string::size_type pos = (cards.GetName()).find(' ');
        if ("Noble" == (cards.GetName()).substr(0, pos)) {
            nobleCards++;
        }
        if (nobleCards == 3) {
            victoryPoints += cards.GetGoodsValue();
        }
    }
}

void Player::ComputeVPMountain(Cards cards) {
    vector<Cards> *hand = Hands->GetHand();
    int mountainCards = 0;
    for (Cards c2:*hand) {
        std::string::size_type pos = (cards.GetName()).find(' ');
        if ("Mountain" == (cards.GetName()).substr(0, pos)) {
            mountainCards++;
        }
        if (mountainCards == 2) {
            victoryPoints += cards.GetGoodsValue();
        }
    }
}

void Player::ComputeCards() {
    vector<Cards> *hand = Hands->GetHand();
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
            victoryPoints += money * c.GetGoodsValue();
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
