//
// Created by Wayne on 3/8/2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include "Deck.h"

Deck::Deck() {
    Deck(2);
}

Deck::Deck(int numberOfPlayers) {

    deck = new vector<Cards>();
    faceUpCards = new vector<Cards>();

    if (numberOfPlayers > 4 || numberOfPlayers < 2) {
        cout << "Incorrect number of players." << endl;
        exit(0);
    }

    // 1: place i armies, 2: move i armies, 3: build 1 city, 4: destroy i armies
    Cards card1("Ancient Phoenix", "Wings|-|5cubeMoves", 0, 2, 5, "", 0, 0, 3, 1, "");
    deck->push_back(card1);

    Cards card2("Ancient Tree Spirit", "3Potions|-|4cubes", 0, 1, 4, "", 0, 0, 4, 3, "");
    deck->push_back(card2);

    Cards card3("Cursed Banshee", "2potions|-|6cubeMoves", 0, 2, 6, "", 0, 0, 4, 2, "");
    deck->push_back(card3);

    Cards card4("Cursed King", "1Potion|-|3cubes/4cubeMoves", 0, 1, 3, "OR", 2, 4, 4, 1, "");
    deck->push_back(card4);

    Cards card5("Cursed Tower", "+1VP per flying|-|settlement", 0, 3, 1, "", 0, 0, 6, 1, "fying");
    deck->push_back(card5);

    Cards card6("Dire Eye", "Wings|-|4cubes", 0, 1, 4, "", 0, 0, 3, 1, "");
    deck->push_back(card6);

    Cards card7("Dire Goblin", "1potion|-|5cubesMoves", 0, 2, 5, "", 0, 0, 4, 1, "");
    deck->push_back(card7);

    Cards card8("Forest Elf", "1cube|-|3cubes/2cubesMove", 0, 1, 3, "OR", 2, 2, 2, 1, "");
    deck->push_back(card8);

    Cards card9("Forest Pixie", "1cube|-|4cubeMoves", 0, 2, 4, "", 0, 0, 2, 1, "");
    deck->push_back(card9);

    Cards card10("Graveyard", "+1VP perCursedCard|-|2cubes", 0, 1, 2, "", 0, 0, 6, 1, "Crsed");
    deck->push_back(card10);

    Cards card11("Night Hydra", "1cube|-|5cubesMove+ destory1cube", 0, 2, 5, "AND", 4, 1, 2, 1, "");
    deck->push_back(card11);

    Cards card12("Night Wizard", "+1VP per NightCard|-|3cubes+destroy1cube", 0, 1, 3, "AND", 4, 1, 6, 1, "Nght");
    deck->push_back(card12);

    Cards card13("Noble Knight", "1cubeMove|-|4cubes+destroy1cube", 0, 1, 4, "OR", 4, 1, 1, 1, "");
    deck->push_back(card13);

    Cards card14("Stronghold", "+1VP per Dire Card|-|settlement", 0, 3, 1, "", 0, 0, 6, 1, "Dre");
    deck->push_back(card14);

    Cards card15("Ancient Sage", "+1VP per AncientCard|-|3cubeMoves", 0, 2, 3, "", 0, 0, 6, 1, "Ancient");
    deck->push_back(card15);

    Cards card16("Ancient Woods", "1cube|-|settlement+1cube", 0, 3, 1, "AND", 1, 1, 2, 1, "");
    deck->push_back(card16);

    Cards card17("Cursed Gargoyles", "Wings|-|5cubeMoves", 0, 2, 5, "", 0, 0, 3, 1, "");
    deck->push_back(card17);

    Cards card18("Cursed Mausoleum", "1cubeMove|-|settlement", 0, 3, 1, "", 0, 0, 1, 1, "");
    deck->push_back(card18);

    Cards card19("Dire Dragon", "Wings|-|3cubes+destroy1cube", 0, 1, 3, "AND", 4, 1, 3, 1, "");
    deck->push_back(card19);

    Cards card20("Dire Giant", "Immune to Attack|-|3cubes+destroy1cube", 0, 1, 3, "AND", 4, 1, 9, 0, "");
    deck->push_back(card20);

    Cards card21("Dire Ogre", "+1VP per 3 coins|-|2cubeMoves", 0, 2, 2, "", 0, 0, 8, 1, "");
    deck->push_back(card21);

    Cards card22("Forest Gnome", "3Potions|-|2cubeMoves", 0, 2, 2, "", 0, 0, 4, 3, "");
    deck->push_back(card22);

    Cards card23("Forest Tree Town", "1cubeMove|-|settlement", 0, 3, 1, "", 0, 0, 1, 1, "");
    deck->push_back(card23);

    Cards card24("Lake", "+1VP per forestCard|-|2cubes/3cubesMove", 0, 1, 2, "OR", 2, 3, 6, 1, "Frest");
    deck->push_back(card24);

    Cards card25("Night Village", "1cube|-|settlement", 0, 3, 1, "", 0, 0, 2, 1, "");
    deck->push_back(card25);

    Cards card26("Noble Hills", "threeNobleCards=4VP|-|3cubes", 0, 1, 3, "", 0, 0, 7, 4, "Nble");
    deck->push_back(card26);

    Cards card27("Noble Unicorn", "1cubeMove|-|4cubesMove+1cube", 0, 2, 4, "AND", 1, 1, 1, 1, "");
    deck->push_back(card27);

    if (numberOfPlayers > 2) {
        Cards card28("Arcane Manticore", "1cubeMove|-|4cubes+destroy1cube", 0, 1, 4, "AND", 4, 1, 1, 1, "");
        deck->push_back(card28);

        Cards card29("Arcane Temple", "+1VP per ArcaneCard|-|3cubeMoves", 0, 2, 3, "", 0, 0, 6, 1, "Acane");
        deck->push_back(card29);

        Cards card30("Mountain Treasury", "1Potion2BronzeCoins|-|3cubesMove", 0, 2, 3, "", 0, 0, 5, 2, "");
        deck->push_back(card30);

        Cards card31("Arcane Sphinx", "Wings|-|3cubes/4cubesMove", 0, 1, 3, "OR", 2, 4, 3, 1, "");
        deck->push_back(card31);

        Cards card32("Mountain Dwarf", "+3VP if you have 2 mountain cards|-|2cubes+destroy 1 cube", 0, 1, 2, "AND", 4,
                     1, 10, 3, "Mountain");
        deck->push_back(card32);


        if (numberOfPlayers > 3) {
            Cards card33("Castle", "Potion|-|3cubes/settlement", 0, 1, 3, "OR", 3, 1, 4, 1, "");
            deck->push_back(card33);

            Cards card34("Castle 2", "Potion|-|3cubesMove+settlement", 0, 2, 3, "AND", 3, 1, 4, 1, "");
            deck->push_back(card34);
        }
    }
}

void Deck::ShuffleDeck() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(deck->begin(), deck->end(), std::default_random_engine(seed));
}

// Accessors
vector<Cards> *Deck::GetDeck() {
    return deck;
}

vector<Cards> *Deck::GetFaceUpCards() {
    return faceUpCards;
}

void Deck::PopulateFaceUpCards() {
    for(int i = 0; i < 6; i++) {
        Cards drawnCard = deck->back();
        deck->pop_back();
        faceUpCards->push_back(drawnCard);
    }
        SetFaceUpCardsCost();
}

void Deck::PrintCardsIn(vector<Cards> *vectorOfCards) {

    for (int i = 0; i < vectorOfCards->size(); i++) {
        cout << (i + 1) << ". " << vectorOfCards->at(i);
    }
}

void Deck::SetFaceUpCardsCost() {
    int count = 0;
    int cost = 0;

    for (int i = 0; i < faceUpCards->size(); i++) {
        count++;
        switch (count) {
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

Deck::~Deck()
{

    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }


    if (faceUpCards != nullptr) {
        delete faceUpCards;
        faceUpCards = nullptr;
    }
}
