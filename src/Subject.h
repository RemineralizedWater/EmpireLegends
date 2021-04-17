#pragma once

#include "Observer.h"
#include <list>

using namespace std;

// forward reference due to circular references
class Observer;

class Subject{
private:
    list<Observer *> *observers;

public:
    Subject();
    ~Subject();
    virtual void Attach(Observer *o);
    virtual void Detach(Observer *o);
    virtual void Notify(); // to be included in the child's method to notify all those who are observing it
};
