#pragma once

#include "../GameObservers.h"

class HandController {
private:
    HandObserver *handView;
    Hand *handModel;

public:
    HandController(HandObserver *newView, Hand *newModel);

    void ControlHand();
};
