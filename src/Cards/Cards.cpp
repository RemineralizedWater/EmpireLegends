
#include <iostream>
#include <vector>
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

Cards::Cards(string _name, string _goodsAndAction, int _cost,
             int _actionOne, int _actionOneValue, string _actionOperation,
             int _actionTwo, int _actionTwoValue,
             int _goods, int _goodsValue, string _goodsSpecific) {
    name = _name;
    goodsAndAction = _goodsAndAction;
    cost = _cost;

    actionOperation = _actionOperation;
    actionOne = _actionOne;
    actionOneValue = _actionOneValue;
    actionTwo = _actionTwo;
    actionTwoValue = _actionTwoValue;

    goods = _goods;
    goodsValue = _goodsValue;
    goodsSpecific = _goodsSpecific;
}

Cards::Cards(string *_name, string *_goodsAndAction, int *_cost, int *_actionOne, int *_actionOneValue,
             string *_actionOperation, int *_actionTwo, int *_actionTwoValue, int *_goods, int *_goodsValue,
             string *_goodsSpecific) {
    name = *_name;
    goodsAndAction = *_goodsAndAction;
    cost = *_cost;

    actionOperation = *_actionOperation;
    actionOne = *_actionOne;
    actionOneValue = *_actionOneValue;
    actionTwo = *_actionTwo;
    actionTwoValue = *_actionTwoValue;

    goods = *_goods;
    goodsValue = *_goodsValue;
    goodsSpecific = *_goodsSpecific;
}

Cards::Cards(const Cards &copy){
    this->name = copy.name;
    this->goodsAndAction = copy.goodsAndAction;
    this->cost = cost = copy.cost;

    this->actionOperation = copy.actionOperation;
    this->actionOne = copy.actionOne;
    this->actionOneValue = copy.actionOneValue;
    this->actionTwo = copy.actionTwo;
    this->actionTwoValue = copy.actionTwoValue;

    this->goods = copy.goods;
    this->goodsValue = copy.goodsValue;
    this->goodsSpecific = copy.goodsSpecific;
}

// Accessors
string Cards::GetName() {
    return name;
}

string Cards::GetGoodsAndAction() {
    return goodsAndAction;
}

int Cards::GetCost(){
    return cost;
}

// Mutators
void Cards::SetCost(int _cost){
    cost = _cost;
}

// Assignment Operator
Cards & Cards::operator =(const Cards &c){
    this->name = c.name;
    this->goodsAndAction = c.goodsAndAction;
    this->cost = c.cost;
    return *this;
}

// Stream Insertion Operators
ostream& operator << (ostream &out, const Cards &c){
    //out << "(cost: " << *(c.cost) << ") name: " << *(c.name) << ", goods and actions: " << *(c.goodsAndAction) << endl;
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};
    string goods[11] = {"", "+ to move armies", "+ to place armies", "- to move over water", "+ elixirs",
                        "+ coins and 1+ elixirs", "+ VP per card: ", "+ VP for card: Noble x3", "+ VP per 3 coins",
                        "immune to attack", "+ VP for card: Mountain x2"};

    out << "(cost: " << c.cost << ") name: " << c.name << ", actions = " << actions[c.actionOne] << c.actionOneValue;
    if(c.actionTwo != 0){
        out << " " << c.actionOperation << " " << actions[c.actionTwo] << c.actionTwoValue;
    }
    if(c.goods == 6){
        out << " goods = " << goods[6] << c.goodsSpecific;
    }else{
        out<< " goods = " << to_string(c.goodsValue) << goods[c.goods];
    }

    out << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream& operator >> (istream &in, Cards &c){
    in >> c.name;
    in >> c.goodsAndAction;
    in >> c.cost;
    return in;
}

Cards::~Cards() {

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




