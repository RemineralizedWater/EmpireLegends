#pragma once
#include "../GameObservers.h"
#include "Player.h"

class PlayerController {
private:
    PlayerObserver *playerView;
    Player *playerModel;
public:
    PlayerController(PlayerObserver *newView, Player *newModel);
    void ControlPlayer();
};
