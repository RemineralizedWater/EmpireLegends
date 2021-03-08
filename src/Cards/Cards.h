#ifndef EMPIRELEGENDS_CARDS_H
#define EMPIRELEGENDS_CARDS_H

#include <string>
#include <vector>
#include "../Player/Player.h"

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
    static void Draw(vector<Cards> *deckPtr, vector<Cards> *faceUpCardsPtr);
    static void Exchange(vector<Cards> *faceUpCardsPtr, int position, vector<Cards> *playerHandPtr, vector<Cards> *deckPtr);
    static void ShuffleDeck(vector <Cards> deck);
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

class Deck{
private:
    static vector<Cards>* deck;
    static vector<Cards>* faceUpCards;
public:
    Deck();
    Deck(int numberOfPlayers);
    //~Deck();
    static vector<Cards>* GetDeck();
    static vector<Cards>* GetFaceUpCards();
    void PrintCardsIn(vector<Cards>* vectorOfCards);
    void PopulateFaceUpCards();
    void SetFaceUpCardsCost();
    //void ShuffleDeck();
    void Draw();
};

class Hand{
private:
    vector<Cards> hand;
public:
    Hand();
    //~Hand();
    void AddToHand(Cards::Cards card);
    void Exchange(int positionToPickUp, Player::Player player);
};

#endif //EMPIRELEGENDS_CARDS_H
