#ifndef EMPIRELEGENDS_PLAYER_H
#define EMPIRELEGENDS_PLAYER_H

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

    ~Player();

    Player(Player &playerToCopy);

    Player(string region_, BiddingFacility *biddingFacility_, Territory &territory_,
           Cards &cards_, int tokenArmies_,
           int cubes_, int disks_, Hand *hand_, int money_, string name_,
           int totalMovementPointsForRound_, int costToMoveOverWater_, bool canBeAttacked_, int victoryPoints_, int elixirs_);

    Player &operator=(const Player &playerToCopy);

    void RequestPlayerName();

    void PaysCoinFromPlayer(int amountToPay);

    void PlaceNewArmies(int numberOfArmiesToPlaced);

    void MoveArmiesForPlayer(int numberOfArmiesToMove);

    void MoveOverLandForPlayer();

    void MoveOverWaterForPlayer();

    void BuildCityForPlayer();

    void DestroysNumberOfArmyOfPlayer(int numberOfArmiesToDestroy);

    void AndOrAction();

    string GetName();

    void SetName(string name_);

    int GetCostOverWater();

    void SetCostOverWater(int costToMoveOverWater_);

    int GetMoney();

    BiddingFacility *GetBiddingFacility();

    void SetMoney(int money);

    int GetTotalMovementPointsForRound();

    void SetTotalMovementPointsForRound(int totalMovementPointsForRound);

    friend std::istream &operator>>(std::istream &is, Player &player);

    void ResolveActiveCard();

    void SetArmiesTokens(int numberOfTokens);

    int GetArmiesTokens();

    void SetCitiesDisks(int numberOfDisks);

    int GetCitiesDisks();

    int GetElixirs();

    void SetElixirs(int numberOfElixirs);

    int GetVictoryPoints();

    void SetVictoryPoints(int points);

    void ComputeScore(int currentPlayerIndex, vector<Player *> players, Map *map);

    void ComputeVPFlying(Cards cards);

    void ComputeVPNoble(Cards cards);

    void ComputeVPMountain(Cards cards);

    void ComputeCards();

    void CheckForMostElixirsForPlayer(int currentPlayerIndex, vector<Player *> players);

    void ApplyAbility();

};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H

