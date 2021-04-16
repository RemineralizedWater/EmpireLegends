#pragma once

class Observer {
protected:
    Observer();

public:
    ~Observer();
    virtual void Update() = 0; // pure virtual, needs to be implemented by the child
};
