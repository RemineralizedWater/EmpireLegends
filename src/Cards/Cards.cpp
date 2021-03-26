
#include <iostream>
#include <vector>
#include "Cards.h"

using namespace std;


// Constructors
Cards::Cards() {
    name = new string{"New Card"};
    goodsAndAction = new string{"empty"};
    cost = new int{0};

    actionOperation = new string{""};
    actionOne = new int{0};
    actionOneValue = new int{0};
    actionTwo = new int{0};
    actionTwoValue = new int{0};

    goods = new int{0};
    goodsValue = new int{0};
    goodsSpecific = new string{""};
}

Cards::Cards(string *_name, string *_goodsAndAction, int* _cost,
             int* _actionOne, int* _actionOneValue, string* _actionOperation,
             int* _actionTwo, int* _actionTwoValue,
             int* _goods, int* _goodsValue, string* _goodsSpecific) {
    name = new string(*_name);
    goodsAndAction = new string(*_goodsAndAction);
    cost = new int(*_cost);

    actionOperation = new string{*_actionOperation};
    actionOne = new int{*_actionOne};
    actionOneValue = new int{*_actionOneValue};
    actionTwo = new int{*_actionTwo};
    actionTwoValue = new int{*_actionTwoValue};

    goods = new int{*_goods};
    goodsValue = new int{*_goodsValue};
    goodsSpecific = new string{*_goodsSpecific};
}

Cards::Cards(const Cards &copy){
    this->name = new string(*copy.name);
    this->goodsAndAction = new string(*copy.goodsAndAction);
    this->cost = cost = new int{*copy.cost};

    this->actionOperation = new string(*copy.actionOperation);
    this->actionOne = new int{*copy.actionOne};
    this->actionOneValue = new int{*copy.actionOneValue};
    this->actionTwo = new int{*copy.actionTwo};
    this->actionTwoValue = new int{*copy.actionTwoValue};

    this->goods = new int{*copy.goods};
    this->goodsValue = new int{*copy.goodsValue};
    this->goodsSpecific = new string{*copy.goodsSpecific};
}

// Accessors
string* Cards::GetName() {
    return name;
}

string *Cards::GetGoodsAndAction() {
    return goodsAndAction;
}

int* Cards::GetCost(){
    return cost;
}

// Mutators
void Cards::SetCost(int _cost){
    cost = new int{_cost};
}

// Assignment Operator
Cards & Cards::operator =(const Cards &c){
    this->name = new string(*(c.name));
    this->goodsAndAction = new string(*(c.goodsAndAction));
    this->cost = new int(*(c.cost));
    return *this;
}

// Stream Insertion Operators
ostream& operator << (ostream &out, const Cards &c){
    //out << "(cost: " << *(c.cost) << ") name: " << *(c.name) << ", goods and actions: " << *(c.goodsAndAction) << endl;
    string actions[5] = {"", "Place Armies: ", "Move Armies: ", "Build City: ", "Destroy Armies: "};
    string goods[11] = {"", "+ to move armies", "+ to place armies", "- to move over water", "+ elixirs",
                        "+ coins and 1+ elixirs", "+ VP per card: ", "+ VP for card: Noble x3", "+ VP per 3 coins",
                        "immune to attack", "+ VP for card: Mountain x2"};

    out << "(cost: " << *(c.cost) << ") name: " << *(c.name) << ", actions = " << actions[*c.actionOne] << *c.actionOneValue;
    if(*c.actionTwo != 0){
        out << " " << *c.actionOperation << " " << actions[*c.actionTwo] << *c.actionTwoValue;
    }
    if(*c.goods == 6){
        out << " goods = " << goods[6] << *c.goodsSpecific;
    }else{
        out<< " goods = " << to_string(*c.goodsValue) << goods[*c.goods];
    }

    out << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream& operator >> (istream &in, Cards &c){
    in >> *(c.name);
    in >> *(c.goodsAndAction);
    in >> *(c.cost);
    return in;
}

Cards::~Cards() {
    if(name != nullptr){
        delete name;
        name = nullptr;
    }

    if(goodsAndAction != nullptr){
        delete goodsAndAction;
        goodsAndAction = nullptr;
    }

    if(cost != nullptr){
        delete cost;
        cost = nullptr;
    }
}

int *Cards::GetActionOne() {
    return actionOne;
}

int *Cards::GetActionTwo() {
    return actionTwo;
}

int *Cards::GetActionOneValue() {
    return actionOneValue;
}

int *Cards::GetActionTwoValue() {
    return actionTwoValue;
}

string *Cards::GetActionOperator() {
    return actionOperation;
}

int *Cards::GetGoods() {
    return goods;
}

int *Cards::GetGoodsValue() {
    return goodsValue;
}

string *Cards::GetGoodsSpecific() {
    return goodsSpecific;
}


