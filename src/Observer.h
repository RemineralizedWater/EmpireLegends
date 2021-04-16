#ifndef EMPIRELEGENDS_OBSERVER_H
#define EMPIRELEGENDS_OBSERVER_H

#pragma once

class Observer{
public:
    ~Observer();
    virtual void Update() = 0; // pure virtual, needs to be implemented by the child
protected:
    Observer();
};



#endif //EMPIRELEGENDS_OBSERVER_H
