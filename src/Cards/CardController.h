#pragma once

#include "../GameObservers.h"
#include "Cards.h"

class CardController {
private:
    CardObserver *cardView;
    Cards *cardModel;

public:
    CardController(CardObserver *newView, Cards *newModel);

    void ControlCard();
};
