#pragma once

#include "Observer.h"
#include "Player/Player.h"

class Player;
class Deck;
class Hand;

class PlayerObserver : public Observer {
private:
    Player *subject;

public:
    PlayerObserver(Player *subject_);

    ~PlayerObserver();

    void Update();

    void Display();
};

class DeckObserver : public Observer {
private:
    Deck *subject;

public:
    DeckObserver(Deck *subject_);

    ~DeckObserver();

    void Update();

    void Display();
};
