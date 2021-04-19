#include "PlayerStrategies.h"
#include <sstream>


// HUMANSTRATEGY METHODS
// Constructor
HumanStrategy::HumanStrategy() {
    strategyName = "Human Player";
}

// Destructor
HumanStrategy::~HumanStrategy() {}

// Accessors
string HumanStrategy::GetStrategyName() {
    return strategyName;
}

void HumanStrategy::Execute(Deck *deck, Player *player,int numPlayer) {
    cout << "--------" << strategyName << "----------" << endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    player->MyHand->Exchange(deck);

    cout << "**Would you like to perform the action(s)?**\n1. YES\n2. NO " << endl;

    int playAction;
    cin >> playAction;
    while (playAction < 1 || playAction > 2) {
        cout << "Please pick a valid action to perform (1 or 2):";
        cin >> playAction;
    }
    if (playAction == 1) {
        player->ResolveActiveCard();
    }
}

// GREEDYCOMPUTERSTRATEGY METHODS
// Constructor
GreedyComputerStrategy::GreedyComputerStrategy() {
    strategyName = "Greedy Computer Player";
}

// Destructor
GreedyComputerStrategy::~GreedyComputerStrategy() {}

// Accessors
string GreedyComputerStrategy::GetStrategyName() {
    return strategyName;
}

void GreedyComputerStrategy::Execute(Deck *deck, Player *player, int numPlayers) {
    cout << "--------" << strategyName << "----------" << endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    cout << strategyName << " is picking a card from the Face Up Pile..." << endl;

    string input="";

    int positionToPickUp = 1;

    //picking cards
    for (int i = 0; i < deck->GetFaceUpCards()->size(); i++) {
        //build city action
        if ((deck->GetFaceUpCards()->at(i).GetActionOne() == 3 || deck->GetFaceUpCards()->at(i).GetActionTwo() == 3)&&deck->GetFaceUpCards()->at((i)).GetActionTwo() == 0){
            if(deck->GetFaceUpCards()->at(i).GetCost()<= player->GetMoney()){
                positionToPickUp = i + 1;
                break;
            }
            else{
                break;
            }
        }
    }
    input+=to_string(positionToPickUp);

    //picking where to place armies
    int terrArmyChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt1;
    for (terrIt1 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt1 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt1) {

        if ((*terrIt1).first->HasCity(player->GetName())) {
            terrArmyChoice=(*terrIt1).first->GetTerrId();
            break;
        }
        else{
            continue;
        }
    }

    //picking where to build city
    int terrCityChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt;
    for (terrIt = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt) {

        if ((*terrIt).first->GetNumberOfArmies(player->GetName()) > 0 && !(*terrIt).first->HasCity(player->GetName())) {
            terrCityChoice=(*terrIt).first->GetTerrId();
            break;
        }
        else if((*terrIt).first->GetNumberOfArmies(player->GetName()) > 0){
            terrCityChoice=(*terrIt).first->GetTerrId();
        }
        else{
            continue;
        }
    }

    //picking a player to destroy
    string playerChoice = player->GetName();
    while(playerChoice==player->GetName()){
        playerChoice = "Player"+to_string(rand() % numPlayers + 1);
    }
    int armyDestroyChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt2;
    for (terrIt2 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt2 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt2) {

        if ((*terrIt2).first->GetNumberOfArmies(player->GetName()) > 0 &&(*terrIt2).first->GetNumberOfArmies(playerChoice) > 0 ) {
            armyDestroyChoice=(*terrIt2).first->GetTerrId();
            break;
        }
        else if((*terrIt2).first->GetNumberOfArmies(player->GetName()) > 0){
            armyDestroyChoice=(*terrIt2).first->GetTerrId();
        }
        else{
            continue;
        }
    }


    //picking place to move armies to
    int fromID=player->GetMap()->GetStartingPoint();
    int toID=player->GetMap()->GetStartingPoint()+1;

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt3;
    for (terrIt3 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt3 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt3) {

        if ((*terrIt3).first->GetNumberOfArmies(player->GetName()) > 0) {
            fromID=(*terrIt3).first->GetTerrId();
            break;
        }
        else{
            continue;
        }
    }
    if(fromID>=player->GetMap()->GetMapSize()){
        toID=fromID-1;
    }
    else{
        toID=fromID+1;
    }


    if (deck->GetFaceUpCards()->at((positionToPickUp-1)).GetActionTwo() != 0) { // if a second action exists
        return;
    } else {
        switch (deck->GetFaceUpCards()->at((positionToPickUp-1)).GetActionOne()) {
            case 1: //place i armies
                if(player->GetArmiesTokens()!=0){
                    input+=(" "+to_string(terrArmyChoice));
                }
                break;
            case 2: //move i armies
                input+=(" "+to_string(fromID));
                input+=(" "+to_string(toID));
                break;
            case 3: // build city
                input+=(" "+to_string(terrCityChoice));
                break;
            case 4: // destroy armies
                input+=(" "+playerChoice);
                input+=(" "+to_string(armyDestroyChoice));
                break;
        }
    }
    istringstream inputItems(input);
    cin.rdbuf(inputItems.rdbuf());

    player->MyHand->Exchange(deck);
    player->ResolveActiveCard();

}

// MODERATECOMPUTERSTRATEGY METHODS
// Constructor
ModerateComputerStrategy::ModerateComputerStrategy() {
    this->strategyName="Moderate Computer Player";
}

// Destructor
ModerateComputerStrategy::~ModerateComputerStrategy() {}

// Accessors
string ModerateComputerStrategy::GetStrategyName() {
    return strategyName;
}

void ModerateComputerStrategy::Execute(Deck *deck, Player *player, int numPlayer) {

    cout << "--------" << strategyName << "----------" << endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    cout << strategyName << " is picking a card from the Face Up Pile..." << endl;

    string input="";

    int positionToPickUp = 1;

    //picking cards
    for (int i = 0; i < deck->GetFaceUpCards()->size(); i++) {
        //Place armies
        if ((deck->GetFaceUpCards()->at(i).GetActionOne() == 1&&deck->GetFaceUpCards()->at((i)).GetActionTwo() == 0)){
            if(deck->GetFaceUpCards()->at(i).GetCost()<= player->GetMoney()){
                positionToPickUp = i + 1;
                break;
            }
            else{
                break;
            }
        }
    }
    input+=to_string(positionToPickUp);

    //picking where to place armies
    int terrArmyChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt1;
    for (terrIt1 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt1 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt1) {
        //check for players with more armies in territory
        if ((*terrIt1).first->HasCity(player->GetName())) {
            for(int l=0;l<numPlayer;l++){
                if ("Player"+to_string(l+1)!= player->GetName()&&  (*terrIt1).first->GetNumberOfArmies("Player"+to_string(l+1))>(*terrIt1).first->GetNumberOfArmies(player->GetName())) {
                    terrArmyChoice=(*terrIt1).first->GetTerrId();
                    break;
                }
            }

        }
        else{
            continue;
        }
    }

    //picking where to build city
    int terrCityChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt;
    for (terrIt = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt) {

        if ((*terrIt).first->GetNumberOfArmies(player->GetName()) > 0 && !(*terrIt).first->HasCity(player->GetName())) {
            terrCityChoice=(*terrIt).first->GetTerrId();
            break;
        }
        else if((*terrIt).first->GetNumberOfArmies(player->GetName()) > 0){
            terrCityChoice=(*terrIt).first->GetTerrId();
        }
        else{
            continue;
        }
    }

    //picking a player to destroy
    string playerChoice = player->GetName();
    while(playerChoice==player->GetName()){
        playerChoice = "Player"+to_string(rand() % numPlayer + 1);
    }
    int armyDestroyChoice=player->GetMap()->GetStartingPoint();
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt2;
    for (terrIt2 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt2 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt2) {

        //choose territory if player chosen has more armies than current player in the Territory
        if ((*terrIt2).first->GetNumberOfArmies(player->GetName()) > 0 &&(*terrIt2).first->GetNumberOfArmies(playerChoice) > 0 && (*terrIt2).first->GetNumberOfArmies(player->GetName()) <(*terrIt2).first->GetNumberOfArmies(playerChoice)) {
            armyDestroyChoice=(*terrIt2).first->GetTerrId();
            break;
        }
        else if((*terrIt2).first->GetNumberOfArmies(player->GetName()) > 0){
            armyDestroyChoice=(*terrIt2).first->GetTerrId();
        }
        else{
            continue;
        }
    }


    //picking place to move armies to
    int fromID=player->GetMap()->GetStartingPoint();
    int toID=player->GetMap()->GetStartingPoint()+1;

    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt3;
    for (terrIt3 = player->GetMap()->GetTerrAndAdjsList()->begin();
         terrIt3 != player->GetMap()->GetTerrAndAdjsList()->end(); ++terrIt3) {

        if ((*terrIt3).first->GetNumberOfArmies(player->GetName()) > 0) {
            fromID=(*terrIt3).first->GetTerrId();
            break;
        }
        else{
            continue;
        }
    }
    if(fromID>=player->GetMap()->GetMapSize()){
        toID=fromID-1;
    }
    else{
        toID=fromID+1;
    }


    if (deck->GetFaceUpCards()->at((positionToPickUp-1)).GetActionTwo() != 0) { // if a second action exists
        return;
    } else {
        switch (deck->GetFaceUpCards()->at((positionToPickUp-1)).GetActionOne()) {
            case 1: //place i armies
                if(player->GetArmiesTokens()!=0){
                    input+=(" "+to_string(terrArmyChoice));
                }
                break;
            case 2: //move i armies
                input+=(" "+to_string(fromID));
                input+=(" "+to_string(toID));
                break;
            case 3: // build city
                input+=(" "+to_string(terrCityChoice));
                break;
            case 4: // destroy armies
                input+=(" "+playerChoice);
                input+=(" "+to_string(armyDestroyChoice));
                break;
        }
    }
    istringstream inputItems(input);
    cin.rdbuf(inputItems.rdbuf());

    player->MyHand->Exchange(deck);
    player->ResolveActiveCard();
}
