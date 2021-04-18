#ifndef EMPIRELEGENDS_PLAYERSTRATEGIES_H
#define EMPIRELEGENDS_PLAYERSTRATEGIES_H

#include <iostream>
#include "../Cards/Deck.h"
#include "Player.h"

using namespace std;

class PlayerStrategies {
public:
    virtual string GetStrategyName()=0;
    virtual void Execute(Deck* deck,Player *player)=0;
};

class HumanStrategy: public PlayerStrategies{
private:
    string strategyName;
public:
    HumanStrategy();
    ~HumanStrategy();
    void Execute(Deck* deck,Player *player);
    string GetStrategyName() override;
};
class GreedyComputerStrategy:public PlayerStrategies{
private:
    string strategyName;
public:
    GreedyComputerStrategy();
    ~GreedyComputerStrategy();
    void Execute(Deck* deck,Player* player);
    string GetStrategyName() override;
};
class ModerateComputerStrategy:public PlayerStrategies{
private:
    string strategyName;
public:
    ModerateComputerStrategy();
    ~ModerateComputerStrategy();
    void Execute(Deck* deck,Player* player);
    string GetStrategyName() override;
};
#endif //EMPIRELEGENDS_PLAYERSTRATEGIES_H
