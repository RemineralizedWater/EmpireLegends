#include "GameObservers.h"

// PLAYER OBSERVER
// Constructor
PlayerObserver::PlayerObserver(Player *subject_) {
    subject = subject_;
    subject_->Attach(this);
}

// Destructor
PlayerObserver::~PlayerObserver() {
    subject->Detach(this);
    if (subject != nullptr) {
        delete subject;
        subject = nullptr;
    }
}

void PlayerObserver::Update() {
    Display();
}

void PlayerObserver::Display() {

    string playerName = subject->GetName();
    int tokenArmies = subject->GetArmiesTokens();
    int victoryPoints = subject->GetVictoryPoints();
    int cities = subject->GetCitiesDisks(); // disks
    int money = subject->GetMoney();
    int elixirs = subject->GetElixirs();

    Map *modelMap = subject->GetMap();
    cout << "__________________________________________________________________________" << endl;
    cout << "Player: " + playerName + " has " +
        to_string(money) + " money left, " +
        to_string(elixirs) + " elixirs, and " +
        to_string(victoryPoints) + " total victory points." << endl;
    cout << to_string(tokenArmies) + " : Armies can be placed" << endl;
    cout << to_string(cities) + " : Cities can be placed" << endl;

    int terrCount = 0;
    typedef pair<Territory *, vector<Adjacency> *> terrInfo;
    vector<terrInfo>::iterator terrIt;
    for (terrIt = modelMap->GetTerrAndAdjsList()->begin();
         terrIt != modelMap->GetTerrAndAdjsList()->end(); ++terrIt) {

        if ((*terrIt).first->GetArmySizeForPlayer()[playerName] != 0 || (*terrIt).first->HasCity(playerName)) {
            terrCount += 1;
            cout << "Territory: " << (*terrIt).first->GetTerrId();
            cout <<" | Continent: " << (*terrIt).first->GetContinent();
            cout << " | Cities: " << (*terrIt).first->GetHasCity()[playerName];
            cout << " | Armies: " << (*terrIt).first->GetArmySizeForPlayer()[playerName] << endl;
        }
    }

    if (terrCount == 0) {
        cout << "No armies in any territory." << endl;
    }

    cout << playerName + "\'s Hand: " << endl;
    if (!subject->MyHand->GetHand()->empty()) {
        for (int i = 0; i < subject->MyHand->GetHand()->size(); i++)
            cout << (i + 1) << ". " << subject->MyHand->GetHand()->at(i);
    } else {
        cout << "Empty." << endl;
    }
}

// ------------------------
// DECK OBSERVER
// Constructor
DeckObserver::DeckObserver(Deck *subject_) {
    subject = subject_;
    subject_->Attach(this);
}

// Destructor
DeckObserver::~DeckObserver() {
    subject->Detach(this);
    if (subject != nullptr) {
        delete subject;
        subject = nullptr;
    }
}

void DeckObserver::Update() {
    Display();
}

void DeckObserver::Display() {
    subject->ShuffleDeck();
    cout << "- - - - - - - - - - CARDS LEFT IN DECK - - - - - - - - - - - -" << endl;
    subject->PrintCardsIn(subject->GetDeck());
    cout << "- - - - - - - - - - CARDS IN FACE UP PILE - - - - - - - - - -" << endl;
    subject->PrintCardsIn(subject->GetFaceUpCards());
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}

// MAP OBSERVER
// Constructor
MapObserver::MapObserver(Map *subject_) {
    subject = subject_;
    subject_->Attach(this);
}

// Destructor
MapObserver::~MapObserver() {
    subject->Detach(this);
    if (subject != nullptr) {
        delete subject;
        subject = nullptr;
    }
}

void MapObserver::Update() {
    Display();
}

void MapObserver::Display() {
    subject->Display();
}
