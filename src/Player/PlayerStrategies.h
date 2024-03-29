#pragma once

#include <iostream>
#include "../Cards/Deck.h"
#include "Player.h"

using namespace std;

class PlayerStrategies {
public:
    virtual string GetStrategyName() = 0;

    virtual void Execute(Deck *deck, Player *player, int numPlayer) = 0;
};

class HumanStrategy: public PlayerStrategies {
private:
    string strategyName;

public:
    HumanStrategy();

    ~HumanStrategy();

    void Execute(Deck *deck,Player *player,int numPlayer);

    string GetStrategyName() override;
};

class GreedyComputerStrategy: public PlayerStrategies {
private:
    string strategyName;

public:
    GreedyComputerStrategy();

    ~GreedyComputerStrategy();

    string GetStrategyName() override;

    void Execute(Deck *deck,Player *player, int numPlayer);
};

class ModerateComputerStrategy: public PlayerStrategies {
private:
    string strategyName;

public:
    ModerateComputerStrategy();

    ~ModerateComputerStrategy();

    void Execute(Deck *deck, Player *player,int numPlayer);

    string GetStrategyName() override;
};
