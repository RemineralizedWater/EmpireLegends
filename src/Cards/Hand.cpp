//
// Created by Wayne on 3/8/2021.
//

#include "Hand.h"
#include <vector>
#include <iostream>

void Hand::Exchange(Deck* deck) {

    int positionToPickUp;
    cout << "Which card from the Face Up Pile would you like to take: " ;
    cin >> positionToPickUp;
    int index = positionToPickUp - 1;

    while(true){
        if(owningPlayer->getMoney() >= *(deck->GetFaceUpCards()->at(index).GetCost())){
            break;
        }else{
            cout << "Player does not have enough money to buy this card. Please select another." << endl;
            cin >> positionToPickUp;
            index = positionToPickUp - 1;
        }
    }

    Cards drawnCard = deck->GetFaceUpCards()->at(index);
    AddToHand(drawnCard);

    cout << "Picked up " << *drawnCard.GetName() << " from position: " << positionToPickUp << endl;

    owningPlayer->PayCoin(*drawnCard.GetCost());

    //reorganize cards in faceup pile
    for(int i = index; i < deck->GetFaceUpCards()->size() - 1; i++){
        deck->GetFaceUpCards()->at(i) = deck->GetFaceUpCards()->at(i + 1);
    }
    // remove last card (is a duplicate)
    deck->GetFaceUpCards()->pop_back();

    Cards replacementCard = deck->GetDeck()->back();
    deck->GetDeck()->pop_back();
    deck->GetFaceUpCards()->push_back(replacementCard);

    deck->SetFaceUpCardsCost();
}

Hand::Hand() {
    hand = new vector<Cards>();
    activeCard = nullptr;
    owningPlayer = nullptr;
}

void Hand::SetOwningPlayer(Player* owningPlayer_){
    this->owningPlayer = owningPlayer_;
}

void Hand::AddToHand(Cards card) {
    hand->push_back(card);
    SetActiveCard(&card);
}

Hand::~Hand() {
    if(hand != nullptr){
        delete hand;
        hand = nullptr;
    }
    if(activeCard != nullptr){
        delete activeCard;
        activeCard = nullptr;
    }
}

vector<Cards> *Hand::GetHand() {
    return hand;
}

Cards *Hand::GetActiveCard() {
    return activeCard;
}

void Hand::SetActiveCard(Cards *card) {
    activeCard = new Cards(*card);
}
