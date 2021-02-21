#include "Cards.h"
#include <iostream>
#include <list>
#include <vector>
//#include <bits/stdc++.h>

vector <Cards> GetDeck();

void Exchange(vector<Cards> vector, int i);

using namespace std;

void DemonstrateCards(){

    Cards card;
    vector <Cards> deck = GetDeck();
    vector <Cards> faceUpCards;
    vector <Cards>::iterator it;

    cout << "Showing cards in deck." << endl;
    for(it = deck.begin(); it != deck.end(); ++it){
        cout << *(it->GetName()) << *(it ->GetGnA()) << endl;
    }

    // popping from deck and pushing onto faceupcards.
    card = deck.front();
    deck.pop_back();
    faceUpCards.push_back(card);

    cout  << endl << "Showing cards remaining in deck." << endl;
    for(it = deck.begin(); it != deck.end(); ++it){

        cout << *(it->GetName()) << *(it ->GetGnA()) << endl;
    }

    cout  << endl << "Showing cards in face up pile." << endl;
    for(it = faceUpCards.begin(); it != faceUpCards.end(); ++it){
        cout << *(it->GetName()) << *(it ->GetGnA()) << endl;
    }
    Exchange(faceUpCards,0);
}



void ShuffleDeck(vector <Cards> Deck){

    //TODO
}

void Exchange(vector<Cards> FaceUpCards,int position){

  //  auto it = find(FaceUpCards.begin(), FaceUpCards.end(), position);
    //cout<< *it->GetName()<<endl;
    //FaceUpCards <position>






}
vector <Cards> GetDeck(){

    vector <Cards> deck;

    Cards card1(new string("test card1."),new string("H"));
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

