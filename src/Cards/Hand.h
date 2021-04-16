//
// Created by Wayne on 3/8/2021.
//

#pragma once

#include <vector>
#include "Cards.h"
#include "Deck.h"
#include "../Player/Player.h"

class Player;

class Hand{
private:
    vector<Cards>* hand;
    Cards* activeCard;
    Player* owningPlayer;
public:
    Hand();
    ~Hand();
    void AddToHand(Cards card);
    void Exchange(Deck* deck);
    vector<Cards>* GetHand();
    Cards* GetActiveCard();
    void SetActiveCard(Cards* card);
    void SetOwningPlayer(Player* owningPlayer);
};
