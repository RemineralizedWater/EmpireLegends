#include "Subject.h"
#include "Observer.h"
#include <iostream>
using namespace std;

Subject::Subject() {
    observers = new list<Observer *>;
}

Subject::~Subject() {
    if (observers != nullptr) {
        delete observers;
        observers = nullptr;
    }
}

void Subject::Attach(Observer *o) {
    observers->push_back(o);
}

void Subject::Detach(Observer *o) {
    observers->remove(o);
}

void Subject::Notify() {
    list<Observer *>::iterator i = observers->begin();
    for (; i != observers->end(); i++) {
        (*i)->Update(); // calls update on all observers
    }
}
