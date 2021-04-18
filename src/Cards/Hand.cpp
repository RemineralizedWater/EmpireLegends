#include "Hand.h"
#include <vector>
#include <iostream>

// Constructor
Hand::Hand() {
    hand = new vector<Cards>();
    activeCard = nullptr;
    owningPlayer = nullptr;
}

// Destructor
Hand::~Hand() {
    if (hand != nullptr) {
        delete hand;
        hand = nullptr;
    }
}

// Accessors
vector<Cards> *Hand::GetHand() {
    return hand;
}

Cards *Hand::GetActiveCard() {
    return activeCard;
}

int Hand::GetNumberOfCardsInHand() {
    return hand->size();
}

// Mutators
void Hand::SetActiveCard(Cards *card) {
    activeCard = new Cards(*card);
}

void Hand::SetOwningPlayer(Player *owningPlayer_) {
    owningPlayer = owningPlayer_;
}

void Hand::AddToHand(Cards card) {
    hand->push_back(card);
    SetActiveCard(&card);
}

void Hand::Exchange(Deck *deck) {
    int positionToPickUp;
    cout << "Which card from the Face Up Pile would you like to take: " ;
    cin >> positionToPickUp;
    int index = positionToPickUp - 1;

    while (true) {
        if (owningPlayer->GetMoney() >= deck->GetFaceUpCards()->at(index).GetCost()) {
            break;
        } else {
            cout << "Player does not have enough money to buy this card. Please select another." << endl;
            cin >> positionToPickUp;
            index = positionToPickUp - 1;
        }
    }

    Cards drawnCard = deck->GetFaceUpCards()->at(index);
    AddToHand(drawnCard);

    cout << "Picked up " << drawnCard.GetName() << " from position: " << positionToPickUp << endl;

    owningPlayer->PaysCoinFromPlayer(drawnCard.GetCost());

    //reorganize cards in faceup pile
    for (int i = index; i < deck->GetFaceUpCards()->size() - 1; i++) {
        deck->GetFaceUpCards()->at(i) = deck->GetFaceUpCards()->at(i + 1);
    }
    // remove last card (is a duplicate)
    deck->GetFaceUpCards()->pop_back();

    Cards replacementCard = deck->GetDeck()->back();
    deck->GetDeck()->pop_back();
    deck->GetFaceUpCards()->push_back(replacementCard);

    deck->SetFaceUpCardsCost();
}
bool Hand::ExchangeWithoutPrompt(Deck *deck, int positionToPickUp) {
    int index = positionToPickUp - 1;

    while (true) {
        if (owningPlayer->GetMoney() >= deck->GetFaceUpCards()->at(index).GetCost()) {
            break;
        } else {
            return false;
        }
    }

    Cards drawnCard = deck->GetFaceUpCards()->at(index);
    AddToHand(drawnCard);
    cout << "----------------------------------------" << endl;
    cout << "Picked up " << drawnCard << " from position: " << positionToPickUp << endl;
    cout << "----------------------------------------" << endl;

    owningPlayer->PaysCoinFromPlayer(drawnCard.GetCost());

    //reorganize cards in faceup pile
    for (int i = index; i < deck->GetFaceUpCards()->size() - 1; i++) {
        deck->GetFaceUpCards()->at(i) = deck->GetFaceUpCards()->at(i + 1);
    }
    // remove last card (is a duplicate)
    deck->GetFaceUpCards()->pop_back();

    Cards replacementCard = deck->GetDeck()->back();
    deck->GetDeck()->pop_back();
    deck->GetFaceUpCards()->push_back(replacementCard);

    deck->SetFaceUpCardsCost();
    return true;
}

string Hand::GetOwningPlayerName() {
    return owningPlayer->GetName();
}
