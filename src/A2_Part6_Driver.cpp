#include <iostream>
#include "Player/Player.h"
#include "Map Loader/MapLoader.h"
#include "Game/Game.h"

/**
 *  //count the player with most elixirs win 2 victory points.if tied then each receive 1
    //ability 1 extra victory point per card you own with the same name done
    //gain specified victory points if you own the specific set
    //gain specified victory point per amount of coins owned
    //one victory point for each region controlled by most armies and cities, if same number then noone controls it
    //one victory point for controlled continents, none if same amount

    //if tied most coins wins
    //if tied player with most armies on the board wins
    //if tied player with most controlled regions wins
 */

void DemonstrateA2Part6() {
    int numPlayers = 2;
    Game *starter = new Game(numPlayers);

    //setup
    bool validMap = false;
    Map *map = new Map();
    MapLoader *mapLoader = new MapLoader(map, numPlayers);
    mapLoader->LoadMap(map, "../src/Map Boards/valid_map.txt", validMap);
    vector<Player *> players = starter->CreatePlayers(map->GetStartingPoint());
    Deck *deck = starter->CreateDeck();

    for (int i = 0; i < players.size(); i++) {
        players[i]->MyHand->SetOwningPlayer(players[i]);
    }

    //player1
    players[0]->MyHand->AddToHand(Cards("Forest Gnome", "3Potions|-|2cubeMoves", 0, 2, 2, "", 0, 0, 4, 3, ""));
    players[0]->ApplyAbility();
    Territory *t = map->FindTerritory(1);
    t->InsertNewArmyPlayerMapping(players[0]->GetName());
    t->InsertNewCityPlayerMapping(players[0]->GetName());
    t->GetHasCity()[players[0]->GetName()] = true;
    t->GetArmySizeForPlayer()[players[0]->GetName()] += 1;

    //player2
    players[1]->MyHand->AddToHand(Cards("Cursed Banshee", "2potions|-|6cubeMoves", 0, 2, 6, "", 0, 0, 4, 2, ""));
    players[1]->ApplyAbility();

    players[1]->MyHand->AddToHand(
            Cards("Mountain Treasury", "1Potion2BronzeCoins|-|3cubesMove", 0, 2, 3, "", 0, 0, 5, 2, ""));
    players[1]->ApplyAbility();
    t->InsertNewArmyPlayerMapping(players[1]->GetName());
    t->InsertNewCityPlayerMapping(players[1]->GetName());
    t->GetHasCity()[players[1]->GetName()] = true;
    t->GetArmySizeForPlayer()[players[1]->GetName()] += 1;

    t = map->FindTerritory(6);
    t->InsertNewArmyPlayerMapping(players[1]->GetName());
    t->InsertNewCityPlayerMapping(players[1]->GetName());
    t->GetHasCity()[players[1]->GetName()] = false;
    t->GetArmySizeForPlayer()[players[1]->GetName()] += 1;


    cout << "\n --------------PLayer 1 info-------------------" << endl;
    cout << players[0]->GetName() << ": " << players[0]->GetBiddingFacility()->GetLastName() << " Money:"
         << players[0]->GetMoney() << endl;

    cout << "--Armies--" << endl;
    for (int i = 1; i < (map->GetMapSize() + 1); i++) {
        t = map->FindTerritory(i);
        t->GetContinent();
        cout << "army/armies:" << t->GetArmySizeForPlayer()[players[0]->GetName()] << " city/cities:"
             << t->GetHasCity()[players[0]->GetName()] << " Territory: " << t->GetTerrId() << " Continent: "
             << t->GetContinent() << endl;
    }

    cout << "\n--Owned Cards--" << endl;
    deck->PrintCardsIn(players[0]->MyHand->GetHand());
    players[0]->ComputeScore(0, players, map);
    cout << "\nVictory Points: " << players[0]->GetVictoryPoints() << endl;
    cout << "---------------------------------------------------" << endl;

    cout << "\n --------------PLayer 2 info-------------------" << endl;
    cout << players[1]->GetName() << ": " << players[1]->GetBiddingFacility()->GetLastName() << " Money:"
         << players[1]->GetMoney() << endl;
    cout << "--Armies--" << endl;
    for (int i = 1; i < (map->GetMapSize() + 1); i++) {
        t = map->FindTerritory(i);
        t->GetContinent();
        cout << "army/armies:" << t->GetArmySizeForPlayer()[players[1]->GetName()] << " city/cities:"
             << t->GetHasCity()[players[1]->GetName()] << " Territory: " << t->GetTerrId() << " Continent: "
             << t->GetContinent() << endl;
    }
    cout << "\n--Owned Cards--" << endl;
    deck->PrintCardsIn(players[1]->MyHand->GetHand());
    players[1]->ComputeScore(1, players, map);
    cout << "\nVictory Points: " << players[1]->GetVictoryPoints() << "\n" << endl;
    cout << "---------------------------------------------------" << endl;

    /*players[0]->SetVictoryPoints(0);
    players[1]->SetVictoryPoints(0);
     */

    //tied
    int winner = 0;
    if (starter->Tied(players, winner)) {
        //money
        starter->CountMoney(players);
        if (starter->Tied(players, winner)) {
            //armies
            starter->CountArmies(players, map);
            if (starter->Tied(players, winner)) {
                starter->CountControlledTerritories(players, map);
                starter->Tied(players, winner);
                cout << "Winner! After Counting Most Controlled Territories on the board" << endl;
                cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName()
                     << endl;
            } else {
                cout << "Winner! After Counting Most Armies on the board" << endl;
                cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName()
                     << endl;
            }
        } else {
            cout << "Winner! After Counting Money" << endl;
            cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName() << endl;
        }
    } else {
        cout << "Winner!" << endl;
        cout << players[winner]->GetName() << ": " << players[winner]->GetBiddingFacility()->GetLastName() << endl;
    }
}