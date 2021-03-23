//
// Created by Wayne on 3/8/2021.
//

#include <iostream>
#include <vector>
#include "Deck.h"


Deck::Deck() {
    Deck(2);
}

Deck::Deck(int numberOfPlayers) {

    deck = new vector<Cards>();
    faceUpCards  = new vector<Cards>();

    if(numberOfPlayers > 4 || numberOfPlayers < 2){
        cout << "Incorrect number of players." << endl;
        exit(0);
    }

    Cards card1(new string("Ancient Phoenix"), new string("Wings|-|5cubeMoves"));
    deck->push_back(card1);

    Cards card2(new string("Ancient Tree Spirit"), new string("3Potions|-|4cubes"));
    deck->push_back(card2);

    Cards card3(new string("Cursed Banshee"), new string("2potions|-|6cubeMoves"));
    deck->push_back(card3);

    Cards card4(new string("Cursed King"), new string("1Potion|-|3cubes/4cubeMoves"));
    deck->push_back(card4);

    Cards card5(new string("Cursed Tower"), new string("+1VP per flying|-|settlement"));
    deck->push_back(card5);

    Cards card6(new string("Dire Eye"), new string("Wings|-|4cubes"));
    deck->push_back(card6);

    Cards card7(new string("Dire Goblin"), new string("1potion|-|5cubesMoves"));
    deck->push_back(card7);

    Cards card8(new string("Forest Elf"), new string("1cube|-|3cubes/2cubesMove"));
    deck->push_back(card8);

    Cards card9(new string("Forest Pixie"), new string("1cube|-|4cubeMoves"));
    deck->push_back(card9);

    Cards card10(new string("Graveyard"), new string("+1VP perCursedCard|-|2cubes"));
    deck->push_back(card10);

    Cards card11(new string("Night Hydra"), new string("1cube|-|5cubesMove+ destory1cube"));
    deck->push_back(card11);

    Cards card12(new string("Night Wizard"), new string("+1VP per NightCard|-|3cubes+destroy1cube"));
    deck->push_back(card12);

    Cards card13(new string("Noble Knight"), new string("1cubeMove|-|4cubes+destroy1cube"));
    deck->push_back(card13);

    Cards card14(new string("Stronghold"), new string("+1VP per Dire Card|-|settlement"));
    deck->push_back(card14);

    Cards card15(new string("Ancient Sage"), new string("+1VP per AncientCard|-|3cubeMoves"));
    deck->push_back(card15);

    Cards card16(new string("Ancient Woods"), new string("1cube|-|settlement+1cube"));
    deck->push_back(card16);

    Cards card17(new string("Cursed Gargoyles"), new string("Wings|-|5cubeMoves"));
    deck->push_back(card17);

    Cards card18(new string("Cursed Mausoleum"), new string("1cubeMove|-|settlement"));
    deck->push_back(card18);

    Cards card19(new string("Dire Dragon"), new string("Wings|-|3cubes+destroy1cube"));
    deck->push_back(card19);

    Cards card20(new string("Dire Giant"), new string("Immune to Attack|-|3cubes+destroy1cube"));
    deck->push_back(card20);

    Cards card21(new string("Dire Ogre"), new string("+1VP per 3 coins|-|2cubeMoves"));
    deck->push_back(card21);

    Cards card22(new string("Forest Gnome"), new string("3Potions|-|2cubeMoves"));
    deck->push_back(card22);

    Cards card23(new string("Forest Tree Town"), new string("1cubeMove|-|settlement"));
    deck->push_back(card23);

    Cards card24(new string("Lake"), new string("+1VP per forestCard|-|2cubes/3cubesMove"));
    deck->push_back(card24);

    Cards card25(new string("Night Village"), new string("1cube|-|settlement"));
    deck->push_back(card25);

    Cards card26(new string("Noble Hills"), new string("threeNobleCards=4VP|-|3cubes"));
    deck->push_back(card26);

    Cards card27(new string("Noble Unicorn"), new string("1cubeMove|-|4cubesMove+1cube"));
    deck->push_back(card27);

    if(numberOfPlayers > 2){
        Cards card28(new string("Arcane Manticore"), new string("1cubeMove|-|4cubes+destroy1cube"));
        deck->push_back(card28);

        Cards card29(new string("Arcane Temple"), new string("+1VP per ArcaneCard|-|3cubeMoves"));
        deck->push_back(card29);

        Cards card30(new string("Mountain Treasury"), new string("1Potion2BronzeCoins|-|3cubesMove"));
        deck->push_back(card30);

        Cards card31(new string("Arcane Sphinx"), new string("Wings|-|3cubes/4cubesMove"));
        deck->push_back(card31);

        Cards card32(new string("Mountain Dwarf"), new string("+3VP if you have 2 mountain cards|-|2cubes+destroy 1 cube"));
        deck->push_back(card32);
    }

    if(numberOfPlayers > 3){
        Cards card33(new string("Castle"), new string("Potion|-|3cubes/settlement"));
        deck->push_back(card33);

        Cards card34(new string("Castle 2"), new string("Potion|-|3cubesMove+settlement"));
        deck->push_back(card34);
    }
}

// Accessors
vector<Cards> *Deck::GetDeck() {
    return deck;
}

vector<Cards> *Deck::GetFaceUpCards() {
    return faceUpCards;
}

void Deck::Draw() {
    //
}

void Deck::PopulateFaceUpCards() {
    for(int i = 0; i < 6; i++){
        Cards drawnCard = deck->back();
        deck->pop_back();
        faceUpCards->push_back(drawnCard);
    }
    SetFaceUpCardsCost();
}

void Deck::PrintCardsIn(vector<Cards> *vectorOfCards) {

    for(int i = 0; i < vectorOfCards->size(); i++){
        //cout << count << ". (cost: " << vectorOfCards->at(i).GetCost() << ") : " << vectorOfCards->at(i).GetName() << " : " << vectorOfCards->at(i).GetGoodsAndAction() << endl;
        cout << (i + 1) << ". " << vectorOfCards->at(i);
    }
}

void Deck::SetFaceUpCardsCost() {
    int count = 0;
    int cost = 0;

    for(int i = 0; i < faceUpCards->size(); i++){
        count++;
        switch(count){
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
                cout << "Error in SetFaceUpCardsCost." << endl;
                exit(0);
        }
        faceUpCards->at(i).SetCost(cost);
    }
}

Deck::~Deck() {
    if(deck != nullptr){
        delete deck;
        deck = nullptr;
    }

    if(faceUpCards != nullptr){
        delete faceUpCards;
        faceUpCards = nullptr;
    }
}
