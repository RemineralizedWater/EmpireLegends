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
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "PLAYER OBSERVER" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
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
            cout << " | Continent: " << (*terrIt).first->GetContinent();
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
    cout << "--------------------------------------------------------------------------" << endl;
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
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "DECK OBSERVER - DECK AND/OR FACE-UP PILE HAS CHANGED" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "CARDS REMAINING IN DECK" << endl;
    subject->PrintCardsIn(subject->GetDeck());
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "FACE-UP CARDS" << endl;
    subject->PrintCardsIn(subject->GetFaceUpCards());
    cout << "--------------------------------------------------------------------------" << endl;
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

// Card OBSERVER
// Constructor
CardObserver::CardObserver(Cards *subject_) {
    subject = subject_;
    subject_->Attach(this);
}

// Destructor
CardObserver::~CardObserver() {
    subject->Detach(this);
    if (subject != nullptr) {
        delete subject;
        subject = nullptr;
    }
}

void CardObserver::Update() {
    Display();
}

void CardObserver::Display() {


}

// HAND OBSERVER
// Constructor
HandObserver::HandObserver(Hand *subject_) {
    subject = subject_;
    subject_->Attach(this);
}

// Destructor
HandObserver::~HandObserver() {
    subject->Detach(this);
    if (subject != nullptr) {
        delete subject;
        subject = nullptr;
    }
}

void HandObserver::Update() {
    Display();
}

void HandObserver::Display() {

    string actions[5] = {"", "placed armies: ", "moved armies: ", "built city: ", "destroy armies: "};
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "PHASE OBSERVER" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << subject->GetOwningPlayerName() << " is Resolving their drawn card: " << subject->GetActiveCard()->GetName()
         <<
         " and has paid " << subject->GetActiveCard()->GetCost() << " coins." << endl;

    cout << subject->GetOwningPlayerName() << " has " << actions[subject->GetActiveCard()->GetActionOne()]
         << subject->GetActiveCard()->GetActionOneValue();
    if (subject->GetActiveCard()->GetActionTwo() != 0)
        cout << " and/or " << actions[subject->GetActiveCard()->GetActionTwo()]
             << subject->GetActiveCard()->GetActionTwoValue();
    cout << "." << endl;

    cout << "Their turn is now over." << endl;
    cout << "--------------------------------------------------------------------------" << endl;
}
