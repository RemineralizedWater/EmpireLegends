# pragma once
#include <string>
#include <vector>

using namespace std;

class Cards {
private:
    string* name;
    string* goodsAndAction;
    int* cost;
public:
    string* GetName();
    string* GetGoodsAndAction();
    int* GetCost();
    void SetCost(int _cost);
    Cards();
    ~Cards();
    Cards(const Cards &copy);
    explicit Cards(string* _name);
    Cards(string* _name,string* _goodsAndAction);
    Cards(string* _name,string* _goodsAndAction, int* _cost);
    Cards & operator =(const Cards &c);
    friend ostream & operator << (ostream &out, const Cards &c);
    friend istream & operator >> (istream &in, Cards &c);
};

