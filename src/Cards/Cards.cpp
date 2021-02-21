#include "Cards.h"
#include <iostream>
#include <vector>

using namespace std;

string name;
string goodsAndAction;

// Constructors
Cards::Cards() {
    name = new string("New Card");
    goodsAndAction = new string("empty");
}

Cards::Cards(const Cards &copy){
    this->name = new string(*(copy.name));
    this->goodsAndAction = new string(*(copy.goodsAndAction));
}

Cards::Cards(string* _name) {
    name = new string(*(_name));
    goodsAndAction = new string("empty");
}

Cards::Cards(string *_name, string *_goodsAndAction) {
    name = new string(*(_name));
    goodsAndAction = new string(*(_goodsAndAction));
}

// Accessors
string* Cards::GetName() {
    return name;
}

string *Cards::GetGoodsAndAction() {
    return goodsAndAction;
}

// Assignment Operator
Cards & Cards::operator =(const Cards &c){
    this->name = new string(*(c.name));
    this->goodsAndAction = new string(*(c.goodsAndAction));
    return *this;
}

// Stream Insertion Operators
ostream& operator << (ostream &out, const Cards &c){
    out << "name: " << *(c.name) << ", goods and actions: " << *(c.goodsAndAction) << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream& operator >> (istream &in, Cards &c){
    cout << "Enter name:";
    in >> *(c.name);
    cout << "Enter goods and action:";
    in >> *(c.goodsAndAction);
    return in;
}

void Cards::Draw(vector<Cards> *deckPtr, vector<Cards> *faceUpCardsPtr) {

    int count = 0;
    Cards drawnCard;
    vector <Cards>::iterator it;

    drawnCard = deckPtr->back();
    deckPtr->pop_back();

    faceUpCardsPtr->push_back(drawnCard);

    cout  << endl << "Showing new cards in face up pile:" << endl;
    cout  << "------------------------------\n" << endl;
    for(it = faceUpCardsPtr->begin(); it != faceUpCardsPtr->end(); ++it){
        cout << ++count << ": " << *(it->GetName()) << " : " << *(it ->GetGoodsAndAction()) << endl;
    }
}

vector <Cards> Cards::GetDeck(){

    vector <Cards> deck;

    Cards card1(new string("Ancient Phoenix"),new string("Wings|-|5cubeMoves"));
    deck.push_back(card1);

    Cards card2(new string("Ancient Tree Spirit"),new string("3Potions|-|4cubes"));
    deck.push_back(card2);

    Cards card3(new string("Cursed Banshee"),new string("2potions|-|6cubeMoves"));
    deck.push_back(card3);

    Cards card4(new string("Cursed King"),new string("1Potion|-|3cubes/4cubeMoves"));
    deck.push_back(card4);

    Cards card5(new string("Cursed Tower"),new string("+1VP per flying|-|settlement"));
    deck.push_back(card5);

    Cards card6(new string("Dire Eye"),new string("Wings|-|4cubes"));
    deck.push_back(card6);

    Cards card7(new string("Dire Goblin"),new string("1potion|-|5cubesMoves"));
    deck.push_back(card7);

    Cards card8(new string("Forest Elf"),new string("1cube|-|3cubes/2cubesMove"));
    deck.push_back(card8);

    Cards card9(new string("Forest Pixie"),new string("1cube|-|4cubeMoves"));
    deck.push_back(card9);

    Cards card10(new string("Graveyard"),new string("+1VP perCursedCard|-|2cubes"));
    deck.push_back(card10);

    Cards card11(new string("Night Hydra"),new string("1cube|-|5cubesMove+ destory1cube"));
    deck.push_back(card11);

    Cards card12(new string("Night Wizard"),new string("+1VP per NightCard|-|3cubes+destroy1cube"));
    deck.push_back(card12);

    Cards card13(new string("Noble Knight"),new string("1cubeMove|-|4cubes+destroy1cube"));
    deck.push_back(card13);

    Cards card14(new string("Stronghold"),new string("+1VP per Dire Card|-|settlement"));
    deck.push_back(card14);

    Cards card15(new string("Ancient Sage"),new string("+1VP per AncientCard|-|3cubeMoves"));
    deck.push_back(card15);

    Cards card16(new string("Ancient Woods"),new string("1cube|-|settlement+1cube"));
    deck.push_back(card16);

    Cards card17(new string("Cursed Gargoyles"),new string("Wings|-|5cubeMoves"));
    deck.push_back(card17);

    Cards card18(new string("Cursed Mausoleum"),new string("1cubeMove|-|settlement"));
    deck.push_back(card18);

    Cards card19(new string("Dire Dragon"),new string("Wings|-|3cubes+destroy1cube"));
    deck.push_back(card19);

    Cards card20(new string("Dire Giant"),new string("Immune to Attack|-|3cubes+destroy1cube"));
    deck.push_back(card20);

    Cards card21(new string("Dire Ogre"),new string("+1VP per 3 coins|-|2cubeMoves"));
    deck.push_back(card21);

    Cards card22(new string("Forest Gnome"),new string("3Potions|-|2cubeMoves"));
    deck.push_back(card22);

    Cards card23(new string("Forest Tree Town"),new string("1cubeMove|-|settlement"));
    deck.push_back(card23);

    Cards card24(new string("Lake"),new string("+1VP per forestCard|-|2cubes/3cubesMove"));
    deck.push_back(card24);

    Cards card25(new string("Night Village"),new string("1cube|-|settlement"));
    deck.push_back(card25);

    Cards card26(new string("Noble Hills"),new string("threeNobleCards=4VP|-|3cubes"));
    deck.push_back(card26);

    Cards card27(new string("Noble Unicorn"),new string("1cubeMove|-|4cubesMove+1cube"));
    deck.push_back(card27);

    Cards card28(new string("Arcane Manticore"),new string("1cubeMove|-|4cubes+destroy1cube"));
    deck.push_back(card28);

    Cards card29(new string("Arcane Temple"),new string("+1VP per ArcaneCard|-|3cubeMoves"));
    deck.push_back(card29);

    Cards card30(new string("Mountain Treasury"),new string("1Potion2BronzeCoins|-|3cubesMove"));
    deck.push_back(card30);

    Cards card31(new string("Arcane Sphinx"),new string("Wings|-|3cubes/4cubesMove"));
    deck.push_back(card31);

    Cards card32(new string("Mountain Dwarf"),new string("+3VP if you have 2 mountain cards|-|2cubes+destroy 1 cube"));
    deck.push_back(card32);

    Cards card33(new string("Castle"),new string("Potion|-|3cubes/settlement"));
    deck.push_back(card33);

    Cards card34(new string("Castle 2"),new string("Potion|-|3cubesMove+settlement"));
    deck.push_back(card34);

    return deck;
}

void Cards::Exchange(vector<Cards> *faceUpCardsPtr, int position, vector<Cards> *playerHandPtr, vector<Cards> *deckPtr) {

    int index = position - 1;
    int cost;
    int count = 0;
    vector <Cards>::iterator it;

    cout << "Picking up card " << position << endl;
    // setting cost of the card based on the position
    switch(position){
        case 1:
            cost = 0;
            break;
        case 2:
        case 3:
            cost = 1;
            break;
        case 4:
        case 5:
            cost = 2;
            break;
        case 6:
            cost = 3;
            break;
        default:
            cout << "Position must be < 7." << endl;
            exit(0);
    }

    // TODO: check player coins
    /* if(player.coins > cost){
        cout << "Player does not have enough coins." << endl;
    }*/

    // TODO: remove coins from Player and add to Supply
    //player.coins = player.coins - cost;
    cout << cost << " coin(s) have been paid." << endl;

    // put card in players hand
    Cards & cardPickedUp = faceUpCardsPtr->at(index);
    cout << "Picked up: " << *cardPickedUp.GetName() << endl;
    playerHandPtr->push_back(cardPickedUp);


    // organize cards in face up pile
    for(int i = index; i < faceUpCardsPtr->size() - 1; i++){
        faceUpCardsPtr->at(i) = faceUpCardsPtr->at(i + 1);
    }

    // remove last card
    faceUpCardsPtr->pop_back();
}

void Cards::ShuffleDeck(vector <Cards> deck){
    //TODO
}

Cards::~Cards() {
    if(name != nullptr){
        delete name;
        name = nullptr;
    }

    if(goodsAndAction != nullptr){
        delete goodsAndAction;
        goodsAndAction = nullptr;
    }
}

