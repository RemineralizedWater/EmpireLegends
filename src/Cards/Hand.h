//
// Created by Wayne on 3/8/2021.
//

#pragma once

#include <vector>
#include "Cards.h"
#include "Deck.h"
#include "../Player/Player.h"

class Player;

class Hand : public Subject {
private:
    vector<Cards> *hand;
    Cards *activeCard;
    Player *owningPlayer;

public:
    Hand();

    ~Hand();

    vector<Cards> *GetHand();

    Cards *GetActiveCard();

    int GetNumberOfCardsInHand();

    string GetOwningPlayerName();

    void SetActiveCard(Cards *card);

    void SetOwningPlayer(Player *owningPlayer);

    void AddToHand(Cards card);

    void Exchange(Deck *deck);

    bool ExchangeWithoutPrompt(Deck *deck, int positionToPickUp);
};
