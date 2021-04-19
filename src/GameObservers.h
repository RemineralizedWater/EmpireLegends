#pragma once

#include "Observer.h"
#include "Player/Player.h"

class Player;
class Deck;
class Hand;
class Cards;

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

class MapObserver : public Observer {
private:
    Map *subject;

public:
    MapObserver(Map *subject_);

    ~MapObserver();

    void Update();

    void Display();
};

class CardObserver : public Observer {
private:
    Cards *subject;

public:
    CardObserver(Cards *subject_);

    ~CardObserver();

    void Update();

    void Display();

};

class HandObserver : public Observer {
private:
    Hand *subject;

public:
    HandObserver(Hand *subject_);

    ~HandObserver();

    void Update();

    void Display();

};