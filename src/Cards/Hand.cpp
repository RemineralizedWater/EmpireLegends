//
// Created by Wayne on 3/8/2021.
//

#include "Hand.h"
#include "Deck.h"
#include <vector>
#include <iostream>

void Hand::Exchange(Deck* deck) {

    int positionToPickUp;
    cout << "Which card from the Face Up Pile would you like to take: " ;
    cin >> positionToPickUp;
    int index = positionToPickUp - 1;

    // TODO check if player has enough coins
    /* if(player.coins > cost){
     cout << "Player does not have enough coins." << endl;
     return;
    }*/

    Cards* drawnCard = &deck->GetFaceUpCards()->at(index);
    AddToHand(drawnCard);

    cout << "Picked up " << *drawnCard->GetName() << " from position: " << positionToPickUp << endl;

    // TODO: remove coins from Player and add to Supply
    //player.coins = player.coins - cost;
    cout << *drawnCard->GetCost() << " coin(s) have been paid." << endl;

    //reorganize cards in faceup pile
    for(int i = index; i < deck->GetFaceUpCards()->size() - 1; i++){
        deck->GetFaceUpCards()->at(i) = deck->GetFaceUpCards()->at(i + 1);
    }

    // remove last card (is a duplicate)
    deck->GetFaceUpCards()->pop_back();
    Cards replacementCard = deck->GetDeck()->back();
    deck->GetDeck()->pop_back();
    deck->GetFaceUpCards()->push_back(replacementCard);
}

Hand::Hand() {
    hand = new vector<Cards>();
}

void Hand::AddToHand(Cards* card) {
    hand->push_back(*card);
}

Hand::~Hand() {
    if(hand != nullptr){
        delete hand;
        hand = nullptr;
    }
}

vector<Cards> *Hand::GetHand() {
    return hand;
}

Cards Hand::Draw(int coins, int index){
    //if(coins==)
};

//void BiddingFacility::initializeCoins(BiddingFacility H){
//
//}