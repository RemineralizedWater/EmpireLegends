//
// Created by Wayne on 3/8/2021.
//

#pragma once

#include <vector>
#include "Cards.h"
#include "../Subject.h"

class Deck : public Subject {
private:
    vector<Cards> *deck;
    vector<Cards> *faceUpCards;

public:
    Deck();

    Deck(int numberOfPlayers);

    ~Deck();

    vector<Cards> *GetDeck();

    vector<Cards> *GetFaceUpCards();

    void SetFaceUpCardsCost();

    void PrintCardsIn(vector<Cards> *vectorOfCards);

    void PopulateFaceUpCards();

    void ShuffleDeck();
};
