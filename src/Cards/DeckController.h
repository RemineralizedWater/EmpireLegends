#pragma once

#include "../GameObservers.h"
#include "Deck.h"

class DeckController {
private:
    DeckObserver *deckView;
    Deck *deckModel;

public:
    DeckController(DeckObserver *newView, Deck *newModel);

    void ControlDeck();
};
