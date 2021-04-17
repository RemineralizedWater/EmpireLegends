# pragma once

#include <string>
#include <vector>

using namespace std;

class Cards {
private:
    string name;
    string goodsAndAction;
    int cost;

    string actionOperation;
    int actionOne; // 1: place i armies, 2: move i armies, 3: build 1 city, 4: destroy i armies
    int actionOneValue;
    int actionTwo;
    int actionTwoValue;

    // 1: +i to move, 2: +i to place, 3: -i to water move, 4: +i elixirs, 5: +i coins, 6: +i VP goodsSpecific name,
    // 7: +i VP if goodsSpecific name x3, 8: +i VP per 3 coins, 9: immune to attack, 10: +i VP if goodsSpecific name x2
    int goods;
    int goodsValue;
    string goodsSpecific;

public:
    Cards();

    Cards(string name_, string goodsAndAction_, int cost_,
          int actionOne_, int actionOneValue_, string actionOperation_,
          int actionTwo_, int actionTwoValue_,
          int goods_, int goodsValue_, string goodsSpecific_);

    Cards(string *name_, string *goodsAndAction_, int *cost_,
          int *actionOne_, int *actionOneValue_, string *actionOperation_,
          int *actionTwo_, int *actionTwoValue_,
          int *goods_, int *goodsValue_, string *goodsSpecific_);

    Cards(const Cards &copy);

    ~Cards();

    Cards &operator=(const Cards &c);

    friend ostream &operator<<(ostream &out, const Cards &c);

    friend istream &operator>>(istream &in, Cards &c);

    string GetName();

    string GetGoodsAndAction();

    int GetCost();

    void SetCost(int cost_);

    int GetActionOne();

    int GetActionOneValue();

    int GetActionTwo();

    int GetActionTwoValue();

    string GetActionOperator();

    int GetGoods();

    int GetGoodsValue();

    string GetGoodsSpecific();
};
