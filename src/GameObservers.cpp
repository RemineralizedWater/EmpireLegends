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

    cout << "Player: " + playerName + " has " +
        to_string(money) + " money left, " +
        to_string(tokenArmies) + " armies to place, " +
        to_string(cities) + " cities to place, and " +
        to_string(victoryPoints) + " total victory points." << endl;

    cout << playerName + "\'s hand: " << endl;
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
    cout << "- - - - - - - - - - - - CARDS IN DECK - - - - - - - - - - - -" << endl;
    subject->PrintCardsIn(subject->GetDeck());
    cout << "- - - - - - - - - - CARDS IN FACE UP PILE - - - - - - - - - -" << endl;
    subject->PrintCardsIn(subject->GetFaceUpCards());
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}
