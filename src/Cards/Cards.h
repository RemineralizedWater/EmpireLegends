#ifndef EMPIRELEGENDS_CARDS_H
#define EMPIRELEGENDS_CARDS_H

#include <string>
#include <vector>

using namespace std;

class Cards {
private:
    string* name;
    string* goodsAndAction;
public:
    string* GetName();
    string* GetGoodsAndAction();
    static vector <Cards> GetDeck();
    static void Draw(vector<Cards> *deckPtr, vector<Cards> *faceUpCardsPtr);
    static void Exchange(vector<Cards> *faceUpCardsPtr, int position, vector<Cards> *playerHandPtr, vector<Cards> *deckPtr);
    static void ShuffleDeck(vector <Cards> deck);
    Cards();
    Cards(const Cards &copy);
    explicit Cards(string* _name);
    Cards(string* _name,string* _goodsAndAction);
    Cards & operator =(const Cards &c);
    friend ostream & operator << (ostream &out, const Cards &c);
    friend istream & operator >> (istream &in, Cards &c);
};


#endif //EMPIRELEGENDS_CARDS_H
