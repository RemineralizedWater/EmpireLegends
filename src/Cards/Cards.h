#ifndef EMPIRELEGENDS_CARDS_H
#define EMPIRELEGENDS_CARDS_H

#include <string>

using namespace std;

class Cards {
private:
    string* name;

public:
    Cards();
    Cards(string* _name);
    string* GetName();

};


#endif //EMPIRELEGENDS_CARDS_H
