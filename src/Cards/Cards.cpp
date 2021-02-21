#include "Cards.h"

using namespace std;

string name;

Cards::Cards() {
    name = new string("New Card");
}

Cards::Cards(string* _name) {
    name = new string(*(_name));
}

string* Cards::GetName() {
    return name;
}


