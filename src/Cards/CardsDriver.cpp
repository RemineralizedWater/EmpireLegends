#include "Cards.h"
#include <iostream>
#include <list>

list<Cards> GetDeck();

using namespace std;

void DemonstrateCards(){

    Cards card;
    list<Cards> deck = GetDeck();
    list<Cards> faceUpCards;
    list<Cards>::iterator it;

    cout << "Showing cards in deck." << endl;
    for(it = deck.begin(); it != deck.end(); ++it){
        cout << *(it->GetName()) << endl;
    }

    // popping from deck and pushing onto faceupcards.
    card = deck.front();
    deck.pop_front();
    faceUpCards.push_back(card);

    cout  << endl << "Showing cards remaining in deck." << endl;
    for(it = deck.begin(); it != deck.end(); ++it){
        cout << *(it->GetName()) << endl;
    }

    cout  << endl << "Showing cards in face up pile." << endl;
    for(it = faceUpCards.begin(); it != faceUpCards.end(); ++it){
        cout << *(it->GetName()) << endl;
    }
}

list<Cards> GetDeck(){

    list<Cards> deck;

    Cards card1(new string("test card1."));
    deck.push_back(card1);

    Cards card2(new string("test card2."));
    deck.push_back(card2);

    Cards card3(new string("test card3."));
    deck.push_back(card3);

    Cards card4(new string("test card4."));
    deck.push_back(card4);

    Cards card5(new string("test card5."));
    deck.push_back(card5);

    return deck;
}

