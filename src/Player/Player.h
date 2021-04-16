# pragma once

#include <string>
#include <iostream>
#include <memory>
#include "../BiddingFacility/BiddingFacility.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Cards/Hand.h"
#include "../Cards/Deck.h"

using namespace std;

class Hand;

class BiddingFacility;

class Player {
private:
    string region;
    BiddingFacility *biddingFacility;
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

public:
    static int Supply;

    Hand *Hands;

    Player();

    Player(string region_, BiddingFacility *biddingFacility_, Territory &territory_,
           Cards &cards_, int tokenArmies_,
           int cubes_, int disks_, Hand *hand_, int money_, string name_,
           int totalMovementPointsForRound_, int costToMoveOverWater_, bool canBeAttacked_, int victoryPoints_, int elixirs_);

    Player(const Player &playerToCopy);

    ~Player();

    Player &operator=(const Player &playerToCopy);

    friend std::istream &operator>>(std::istream &is, Player &player);

    string GetName();

    int GetCostOverWater();

    int GetMoney();

    int GetCitiesDisks();

    int GetElixirs();

    BiddingFacility *GetBiddingFacility();

    int GetArmiesTokens();

    int GetTotalMovementPointsForRound();

    int GetVictoryPoints();

    void SetElixirs(int numberOfElixirs);

    void SetVictoryPoints(int points);

    void SetName(string name_);

    void SetCostOverWater(int costToMoveOverWater_);

    void SetMoney(int money_);

    void SetArmiesTokens(int numberOfTokens);

    void SetCitiesDisks(int numberOfDisks);

    void SetTotalMovementPointsForRound(int totalMovementPointsForRound_);

    void RequestPlayerName();

    void PaysCoinFromPlayer(int amountToPay);

    void PlaceNewArmies(int numberOfArmiesToPlaced);

    void MoveArmiesForPlayer(int numberOfArmiesToMove);

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

};

std::istream &operator>>(std::istream &is, Player &player);
