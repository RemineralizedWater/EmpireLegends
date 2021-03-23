//
// Created by Wayne on 3/8/2021.
//

#ifndef EMPIRELEGENDS_HAND_H
#define EMPIRELEGENDS_HAND_H

#include "Cards.h"
#include "Deck.h"
#include <vector>

class Hand{
private:
    vector<Cards>* hand;
public:
    Hand();
    ~Hand();
    void AddToHand(Cards* card);
    void Exchange(Deck* deck);
    vector<Cards>* GetHand();
};


#endif //EMPIRELEGENDS_HAND_H
