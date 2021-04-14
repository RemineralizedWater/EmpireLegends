#include <iostream>
#include "Player/Player.h"
#include "Cards/Deck.h"
#include "Map/Map.h"
#include "Map Loader/MapLoader.h"
#include "Game/Game.h"

/**
 *  //count the player with most elixers win 2 victory points.if tied then each receive 1
    //ability 1 extra victory point per card you own with the same name done
    //gain specified victory points if you own the specif set
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
    MapLoader *mapLoader = new MapLoader(numPlayers);
    Map *map = mapLoader->loadMap("../src/Map Boards/valid_map.txt", validMap);
    vector<Player *> players = starter->createPlayers(map->getStartingPoint());
    Deck *deck = starter->createDeck();


    for (int i = 0; i < players.size(); i++) {
        players[i]->Hands->SetOwningPlayer(players[i]);
    }
    //player1
    players[0]->Hands->AddToHand(Cards(new string("Forest Gnome"), new string("3Potions|-|2cubeMoves"), new int{0},
                                       new int{2}, new int{2}, new string(""),
                                       new int{0}, new int{0},
                                       new int{4}, new int{3}, new string{""}));
    players[0]->ApplyAbility();
    Territory *t = map->findTerritory(1);
    t->InsertNewArmyPlayerMapping(players[0]->GetName());
    t->InsertNewCityPlayerMapping(players[0]->GetName());
    t->getHasCity()[players[0]->GetName()] = true;
    t->getArmySizeForPlayer()[players[0]->GetName()] += 1;



    //player2
    players[1]->Hands->AddToHand(Cards(new string("Cursed Banshee"), new string("2potions|-|6cubeMoves"), new int{0},
                                       new int{2}, new int{6}, new string(""),
                                       new int{0}, new int{0},
                                       new int{4}, new int{2}, new string{""}));
    players[1]->ApplyAbility();

    players[1]->Hands->AddToHand(
            Cards(new string("Mountain Treasury"), new string("1Potion2BronzeCoins|-|3cubesMove"), new int{0},
                  new int{2}, new int{3}, new string(""),
                  new int{0}, new int{0},
                  new int{5}, new int{2}, new string{""}));
    players[1]->ApplyAbility();
    t->InsertNewArmyPlayerMapping(players[1]->GetName());
    t->InsertNewCityPlayerMapping(players[1]->GetName());
    t->getHasCity()[players[1]->GetName()] = true;
    t->getArmySizeForPlayer()[players[1]->GetName()] += 1;

    t = map->findTerritory(6);
    t->InsertNewArmyPlayerMapping(players[1]->GetName());
    t->InsertNewCityPlayerMapping(players[1]->GetName());
    t->getHasCity()[players[1]->GetName()] = false;
    t->getArmySizeForPlayer()[players[1]->GetName()] += 1;


    cout << "\n --------------PLayer 1 info-------------------" << endl;
    cout << players[0]->GetName() << ": " << players[0]->GetBiddingFacility()->GetLastName() << " Money:"
         << players[0]->GetMoney() << endl;

    cout << "--Armies--" << endl;
    for (int i = 1; i < (map->getMapSize() + 1); i++) {
        t = map->findTerritory(i);
        t->getContinent();
        cout << "army/armies:" << t->getArmySizeForPlayer()[players[0]->GetName()] << " city/cities:"
             << t->getHasCity()[players[0]->GetName()] << " Territory: " << t->getTerrId() << " Continent: "
             << t->getContinent() << endl;
    }

    cout << "\n--Owned Cards--" << endl;
    deck->PrintCardsIn(players[0]->Hands->GetHand());
    players[0]->ComputeScore(0, players, map);
    cout << "\nVictory Points: " << players[0]->GetVictoryPoints() << endl;
    cout << "---------------------------------------------------" << endl;

    cout << "\n --------------PLayer 2 info-------------------" << endl;
    cout << players[1]->GetName() << ": " << players[1]->GetBiddingFacility()->GetLastName() << " Money:"
         << players[1]->GetMoney() << endl;
    cout << "--Armies--" << endl;
    for (int i = 1; i < (map->getMapSize() + 1); i++) {
        t = map->findTerritory(i);
        t->getContinent();
        cout << "army/armies:" << t->getArmySizeForPlayer()[players[1]->GetName()] << " city/cities:"
             << t->getHasCity()[players[1]->GetName()] << " Territory: " << t->getTerrId() << " Continent: "
             << t->getContinent() << endl;
    }
    cout << "\n--Owned Cards--" << endl;
    deck->PrintCardsIn(players[1]->Hands->GetHand());
    players[1]->ComputeScore(1, players, map);
    cout << "\nVictory Points: " << players[1]->GetVictoryPoints() << "\n" << endl;
    cout << "---------------------------------------------------" << endl;

    /*players[0]->SetVictoryPoints(0);
    players[1]->SetVictoryPoints(0);
     */

    //tied
    int winner = 0;
    if (starter->tied(players, winner)) {
        //money
        starter->countMoney(players);
        if (starter->tied(players, winner)) {
            //armies
            starter->countArmies(players, map);
            if (starter->tied(players, winner)) {
                starter->countControlledTerritories(players, map);
                starter->tied(players, winner);
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