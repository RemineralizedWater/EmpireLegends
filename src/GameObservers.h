#pragma once
#include "Observer.h"
#include "Player/Player.h"

class Player;
class Deck;
class Hand;

class PlayerObserver : public Observer{
public:
    PlayerObserver(Player *subject_);
    ~PlayerObserver();
    void Update();
    void Display();
private:
    Player *subject;
};

class DeckObserver : public Observer{
public:
    DeckObserver(Deck *subject_);
    ~DeckObserver();
    void Update();
    void Display();
private:
    Deck *subject;
};