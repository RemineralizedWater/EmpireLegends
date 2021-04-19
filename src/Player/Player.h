# pragma once

#include <string>
#include <iostream>
#include <memory>
#include "../BiddingFacility/BiddingFacility.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Cards/Hand.h"
#include "../Cards/Deck.h"
#include "PlayerStrategies.h"
#include "../Subject.h"

using namespace std;

class Hand;

class PlayerStrategies;

class BiddingFacility;

class Player: public Subject {
private:
    string region;
    BiddingFacility *biddingFacility;
    PlayerStrategies *playerStrategies;
    std::unique_ptr<Territory> territory;
    std::unique_ptr<Cards> cards;
    int tokenArmies;
    int cubes;
    int victoryPoints;
    int elixirs;
    int disks;
    int money;
    string name;
    int totalMovementPointsForRound;
    int costToMoveOverWater;
    bool canBeAttacked;
    Map *map;
    int extraMoveAbility;
    int extraArmyAbility;

public:
    static int Supply;

    Hand *MyHand;

    Player();

    Player(string name_);

    Player(string region_, BiddingFacility *biddingFacility_, Territory &territory_, Cards &cards_, int tokenArmies_,
           int cubes_, int disks_, Hand *myHand_, int money_, string name_, int totalMovementPointsForRound_,
           int costToMoveOverWater_, bool canBeAttacked_, int victoryPoints_, int elixirs_, Map *map_,
           int extraMoveAbility_, int extraArmyAbility_);

    Player(const Player &playerToCopy);

    ~Player();

    Player &operator=(Player &playerToCopy);

    friend std::istream &operator>>(std::istream &is, Player &player);

    string GetName();

    int GetCostOverWater();

    int GetMoney();

    int GetCitiesDisks();

    int GetElixirs();

    BiddingFacility *GetBiddingFacility();

    int GetArmiesTokens();

    int GetTotalMovementPointsForRound();

    Map* GetMap();

    int GetVictoryPoints();

    void SetElixirs(int numberOfElixirs);

    void SetVictoryPoints(int points);

    void SetName(string name_); // Notify();

    void SetCostOverWater(int costToMoveOverWater_);

    void SetMoney(int money_);

    void SetArmiesTokens(int numberOfTokens);

    void SetCitiesDisks(int numberOfDisks);

    void SetTotalMovementPointsForRound(int totalMovementPointsForRound_);

    void SetMap(Map *map_);

    void SetStrategy(PlayerStrategies *newPlayerStrategy);

    PlayerStrategies* GetStrategy();

    void RequestPlayerName();

    void PaysCoinFromPlayer(int amountToPay);

    void PlaceNewArmies(int numberOfArmiesToPlace);

    void PlaceNewArmies(int numberOfArmiesToPlace, int position, bool twoPlayerSetup, bool setup);

    void MoveArmiesForPlayer(int numberOfArmiesToMove);

    void MoveArmiesForPlayer(int numberOfArmiesToMove, int toID, int fromID);

    void MoveOverLandForPlayer();

    void MoveOverWaterForPlayer();

    void BuildCityForPlayer();

    void DestroysNumberOfArmyOfPlayer(int numberOfArmiesToDestroy);

    void AndOrAction();

    void ResolveActiveCard();

    void ComputeScore(int currentPlayerIndex, vector<Player *> players, Map *map);

    void ComputeVPFlying(Cards cards_);

    void ComputeVPNoble(Cards cards_);

    void ComputeVPMountain(Cards cards_);

    void ComputeCards();

    void CheckForMostElixirsForPlayer(int currentPlayerIndex, vector<Player *> players);

    void ApplyAbility();

    void ExecuteStrategy(Deck* deck, int numPlayer);

};

std::istream &operator>>(std::istream &is, Player &player);
