//
// Created by Wayne on 3/8/2021.
//

#ifndef EMPIRELEGENDS_DECK_H
#define EMPIRELEGENDS_DECK_H

#include <vector>
#include "Cards.h"

class Deck{
private:
    vector<Cards>* deck;
    vector<Cards>* faceUpCards;
public:
    Deck();
    Deck(int numberOfPlayers);
    ~Deck();
    vector<Cards>* GetDeck();
    vector<Cards>* GetFaceUpCards();
    void PrintCardsIn(vector<Cards>* vectorOfCards);
    void PopulateFaceUpCards();
    void SetFaceUpCardsCost();
    void ShuffleDeck();
    void Draw();
};



#endif //EMPIRELEGENDS_DECK_H
