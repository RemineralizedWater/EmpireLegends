#include <iostream>
#include "Cards.h"

using namespace std;

// Constructors
Cards::Cards() {
    name = "New Card";
    goodsAndAction = "empty";
    cost = 0;

    actionOperation = "";
    actionOne = 0;
    actionOneValue = 0;
    actionTwo = 0;
    actionTwoValue = 0;

    goods = 0;
    goodsValue = 0;
    goodsSpecific = "";
}

Cards::Cards(string name_, string goodsAndAction_, int cost_,
             int actionOne_, int actionOneValue_, string actionOperation_,
             int actionTwo_, int actionTwoValue_,
             int goods_, int goodsValue_, string goodsSpecific_) {
    name = name_;
    goodsAndAction = goodsAndAction_;
    cost = cost_;

    actionOperation = actionOperation_;
    actionOne = actionOne_;
    actionOneValue = actionOneValue_;
    actionTwo = actionTwo_;
    actionTwoValue = actionTwoValue_;

    goods = goods_;
    goodsValue = goodsValue_;
    goodsSpecific = goodsSpecific_;
}

Cards::Cards(string *name_, string *goodsAndAction_, int *cost_, int *actionOne_, int *actionOneValue_,
             string *actionOperation_, int *actionTwo_, int *actionTwoValue_, int *goods_, int *goodsValue_,
             string *goodsSpecific_) {
    name = *name_;
    goodsAndAction = *goodsAndAction_;
    cost = *cost_;

    actionOperation = *actionOperation_;
    actionOne = *actionOne_;
    actionOneValue = *actionOneValue_;
    actionTwo = *actionTwo_;
    actionTwoValue = *actionTwoValue_;

    goods = *goods_;
    goodsValue = *goodsValue_;
    goodsSpecific = *goodsSpecific_;
}

Cards::Cards(const Cards &copy) {
    name = copy.name;
    goodsAndAction = copy.goodsAndAction;
    cost = cost = copy.cost;

    actionOperation = copy.actionOperation;
    actionOne = copy.actionOne;
    actionOneValue = copy.actionOneValue;
    actionTwo = copy.actionTwo;
    actionTwoValue = copy.actionTwoValue;

    goods = copy.goods;
    goodsValue = copy.goodsValue;
    goodsSpecific = copy.goodsSpecific;
}

// Destructor
Cards::~Cards() {

}

// Assignment Operator
Cards &Cards::operator=(const Cards &c) {
    name = c.name;
    goodsAndAction = c.goodsAndAction;
    cost = c.cost;

    actionOperation = c.actionOperation;
    actionOne = c.actionOne;
    actionOneValue = c.actionOneValue;
    actionTwo = c.actionTwo;
    actionTwoValue = c.actionTwoValue;

    goods = c.goods;
    goodsValue = c.goodsValue;
    goodsSpecific = c.goodsSpecific;
    return *this;
}

// Stream Insertion Operators
ostream &operator<<(ostream &out, Cards &c) {
    //out << "(cost: " << *(c.cost) << ") name: " << *(c.name) << ", goods and actions: " << *(c.goodsAndAction) << endl;
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};
    string goods[11] = {"", "+ to move armies", "+ to place armies", "- to move over water", "+ elixirs",
                        "+ coins and 1+ elixirs", "+ VP per card: ", "+ VP for card: Noble x3", "+ VP per 3 coins",
                        "immune to attack", "+ VP for card: Mountain x2"};

    out << "(cost: " << c.cost << ") name: " << c.name << ", actions = " << actions[c.actionOne] << c.actionOneValue;
    if (c.actionTwo != 0) {
        out << " " << c.actionOperation << " " << actions[c.actionTwo] << c.actionTwoValue;
    }
    if (c.goods == 6) {
        out << " goods = " << goods[6] << c.goodsSpecific;
    } else {
        out << " goods = " << to_string(c.goodsValue) << goods[c.goods];
    }

    out << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream &operator>>(istream &in, Cards &c) {
    in >> c.name;
    in >> c.goodsAndAction;
    in >> c.cost;
    return in;
}

// Accessors
string Cards::GetName() {
    return name;
}

string Cards::GetGoodsAndAction() {
    return goodsAndAction;
}

int Cards::GetCost() {
    return cost;
}

int Cards::GetActionOne() {
    return actionOne;
}

int Cards::GetActionTwo() {
    return actionTwo;
}

int Cards::GetActionOneValue() {
    return actionOneValue;
}

int Cards::GetActionTwoValue() {
    return actionTwoValue;
}

string Cards::GetActionOperator() {
    return actionOperation;
}

int Cards::GetGoods() {
    return goods;
}

int Cards::GetGoodsValue() {
    return goodsValue;
}

string Cards::GetGoodsSpecific() {
    return goodsSpecific;
}

// Mutators
void Cards::SetCost(int cost_) {
    cost = cost_;
}
