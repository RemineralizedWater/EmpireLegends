
#include <iostream>
#include <vector>
#include "Cards.h"

using namespace std;


// Constructors
Cards::Cards() {
    name = new string("New Card");
    goodsAndAction = new string("empty");
    cost = new int{0};
}

Cards::Cards(const Cards &copy){
    this->name = new string(*copy.name);
    this->goodsAndAction = new string(*copy.goodsAndAction);
    this->cost = cost = new int{*copy.cost};
}

Cards::Cards(string* _name) {
    name = new string(*_name);
    goodsAndAction = new string("empty");
    cost = new int{0};
}

Cards::Cards(string *_name, string *_goodsAndAction) {
    name = new string(*_name);
    goodsAndAction = new string(*_goodsAndAction);
    cost = new int{0};
}

Cards::Cards(string *_name, string *_goodsAndAction, int* _cost) {
    name = new string(*_name);
    goodsAndAction = new string(*_goodsAndAction);
    cost = new int(*_cost);
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
    out << "(cost: " << *(c.cost) << ") name: " << *(c.name) << ", goods and actions: " << *(c.goodsAndAction) << endl;
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


