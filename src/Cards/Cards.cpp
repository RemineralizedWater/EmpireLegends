#include "Cards.h"

using namespace std;

string name;
string GnA;

Cards::Cards() {
    name = new string("New Card");
    GnA = new string("empty");
}

Cards::Cards(string* _name) {
    name = new string(*(_name));
    GnA = new string("empty");
}

string* Cards::GetName() {
    return name;
}

string *Cards::GetGnA() {
    return GnA;
}

Cards::Cards(string *_name, string *_GnA) {
    name = new string(*(_name));
    GnA = new string(*(_GnA));
}


