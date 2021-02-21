#ifndef EMPIRELEGENDS_CARDS_H
#define EMPIRELEGENDS_CARDS_H

#include <string>

using namespace std;

class Cards {
private:
    string* name;
    string* GnA;


public:
    Cards();
    Cards(string* _name);
    Cards(string* _name,string* _GnA);
    string* GetName();
    string* GetGnA();



};


#endif //EMPIRELEGENDS_CARDS_H
