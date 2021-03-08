
#include <iostream>
#include <vector>
#include "Cards.h"
#include "../Player/Player.h"

using namespace std;

void DemonstrateCards(const int numberOfPlayers){

    /*
    int cost;
    int count = 0;
    int position = 0;
    Cards card;
    vector <Cards> deck = Cards::GetDeck(numberOfPlayers);
    vector <Cards> *deckPtr = &deck;
    vector <Cards> faceUpCards;
    vector <Cards> *faceUpCardsPtr = &faceUpCards;
    vector <Cards>::iterator it;
    vector <Cards> playerHand;
    vector <Cards> *playerHandPtr = &playerHand;

    cout << "\nShowing cards in deck:" << endl;
    cout << "----------------------\n" << endl;
    for(it = deck.begin(); it != deck.end(); ++it){
        cout << ++count << ": " << *(it->GetName()) << " : " << *(it ->GetGoodsAndAction()) << endl;
    }
    count = 0;

    cout  << endl << "Placing cards in the face up pile...." << endl;
    for (int i = 0; i < 6; i++) {
        // popping from deck and pushing onto faceupcards.
        card = deck.back();
        deck.pop_back();
        faceUpCards.push_back(card);
    }

    //in the case the player exchanges coins for a Card
    if(faceUpCards.size()<6){
        card = deck.back();
        deck.pop_back();
        faceUpCards.push_back(card);
    }

    cout  << endl << "Showing cards remaining in deck:" << endl;
    cout  << "--------------------------------\n" << endl;
    for(it = deck.begin(); it != deck.end(); ++it){
        cout << ++count << ": " << *(it->GetName()) << " : " << *(it ->GetGoodsAndAction()) << endl;
    }
    count = 0;

    cout  << endl << "Showing cards in face up pile:" << endl;
    cout  << "------------------------------\n" << endl;
    for(it = faceUpCards.begin(); it != faceUpCards.end(); ++it){
        count++;
        switch(count) {
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
                cout << "Error in showing face up pile." << endl;
                exit(0);
        }
        cout << count << " - (cost " << cost << " coins) "<< ": " << *(it->GetName()) << " : " << *(it ->GetGoodsAndAction()) << endl;
    }

    while(true){
        cout << endl << "What card position would you like to pick up? Enter an integer 1 to 6 to pick up, otherwise exit." << endl;
        cin >> position;
        // TODO data validation
        if(position < 1 || position > 6){
            delete deckPtr;
            deckPtr = nullptr;

            delete faceUpCardsPtr;
            faceUpCardsPtr = nullptr;

            delete playerHandPtr;
            playerHandPtr = nullptr;

            exit(0);
        }

        // Exchange and Draw
        Cards::Exchange(faceUpCardsPtr, position, playerHandPtr, deckPtr);
        cout << endl;
        Cards::Draw(deckPtr, faceUpCardsPtr);
        cout << endl;

        count = 0;
        cout  << endl << "Showing cards in Player's hand:" << endl;
        cout  << "------------------------------\n" << endl;
        for(it = playerHand.begin(); it != playerHand.end(); ++it){
            cout << ++count << " - " << *(it->GetName()) << " : " << *(it ->GetGoodsAndAction()) << endl;
        }
    }*/

    std::unique_ptr<Player> player (new Player("Montreal", BiddingFacility(), Territory(), Cards(),
                                                    rand(), rand(), rand(), Hand()));

    Deck deck = Deck((int)numberOfPlayers);
    deck.PopulateFaceUpCards();
    deck.PrintCardsIn(deck.GetDeck());
    deck.PrintCardsIn((deck.GetFaceUpCards()));




}