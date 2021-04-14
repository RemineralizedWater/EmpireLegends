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
public:
    static int Supply;
    Hand *Hands;

    Player();

    ~Player();

    Player(const Player &playerToCopy);

    Player(const std::string &region, BiddingFacility *biddingFacility, const Territory &territory,
           const Cards &cards, int *tokenArmies,
           const int &cubes, int *disks, Hand *hand, int *money, const std::string &name,
           const int &totalMovementPointsForRound, const int &costToMoveOverWater, const bool &canBeAttacked);

    Player &operator=(const Player &playerToCopy);

    void RequestPlayerName();

    void PaysCoinFromPlayer(const int &amountToPay);

    void PlaceNewArmies(int numberOfArmiesToPlaced);

    void MoveArmiesForPlayer(int numberOfArmiesHeWantsToMove);

    void MoveOverLandForPlayer();

    void MoveOverWaterForPlayer();

    void BuildCityForPlayer();

    void DestroysNumberOfArmyOfPlayer(int numberOfArmiesToDestroy);

    void AndOrAction();

    const std::string &GetName() const;

    void SetName(const std::string &name);

    int &GetCostOverWater();

    void SetCostOverWater(const int &costToMoveOverWater);

    int GetMoney();

    BiddingFacility *GetBiddingFacility();

    void SetMoney(int money);

    int &GetTotalMovementPointsForRound();

    void SetTotalMovementPointsForRound(const int &totalMovementPointsForRound);

    friend std::istream &operator>>(std::istream &is, Player &player);

    void ResolveActiveCard();

    void SetArmiesTokens(int numberOfTokens);

    int GetArmiesTokens();

    void SetCitiesDisks(int numberOfDisks);

    int GetCitiesDisks();

    int GetElixirs();

    void SetElixers(int numberOfElixirs);

    int GetVictoryPoints();

    void SetVictoryPoints(int points);

    void ComputeScore(int currentPlayerIndex, vector<Player *> players, Map *map);

    void ComputeVPFlying(Cards cards);

    void ComputeVPNoble(Cards cards);

    void ComputeVPMountain(Cards cards);

    void ComputeCards();

    void CheckForMostElixirsForPlayer(int currentPlayerIndex, vector<Player *> players);

    void ApplyAbility();

private:
    std::unique_ptr<std::string> region;
    BiddingFacility *biddingFacility;
    std::unique_ptr<Territory> territory;
    std::unique_ptr<Cards> cards;
    int tokenArmies;
    std::unique_ptr<int> cubes;
    int *victoryPoints;
    int *elixirs;
    int disks;
    int money;
    std::unique_ptr<std::string> name;
    std::unique_ptr<int> totalMovementPointsForRound;
    std::unique_ptr<int> costToMoveOverWater;
    std::unique_ptr<bool> canBeAttacked;

};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H

