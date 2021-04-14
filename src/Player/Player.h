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
    static int supply;
    Hand *hand_;

    Player();

    ~Player();

    Player(const Player &playerToCopy);

    Player(const std::string &region, BiddingFacility *biddingFacility, const Territory &territory,
           const Cards &cards, int *tokenArmies,
           const int &cubes, int *disks, Hand *hand, int *money, const std::string &name,
           const int &totalMovementPointsForRound, const int &costToMoveOverWater, const bool &canBeAttacked);

    Player &operator=(const Player &playerToCopy);

    void RequestPlayerName();

    void PayCoin(const int &amountToPay);

    void PlaceNewArmies(int numberOfArmiesToPlaced);

    void MoveArmies(int numberOfArmiesHeWantsToMove);

    void MoveOverLand();

    void MoveOverWater();

    void BuildCity();

    void DestroyArmy(int numberOfArmiesToDestroy);

    void AndOrAction();

    const std::string &getName() const;

    void setName(const std::string &name);

    int &getCostOverWater();

    void setCostOverWater(const int &costToMoveOverWater);

    int getMoney();

    BiddingFacility *getBiddingFacility();

    void setMoney(int money);

    int &getTotalMovementPointsForRound();

    void setTotalMovementPointsForRound(const int &totalMovementPointsForRound);

    friend std::istream &operator>>(std::istream &is, Player &player);

    void ResolveActiveCard();

    void SetArmiesTokens(int numberOfTokens);

    int GetArmiesTokens();

    void SetCitiesDisks(int numberOfDisks);

    int GetCitiesDisks();

    int GetElixers();

    void SetElixers(int numElixers);

    int GetVictoryPoints();

    void SetVictoryPoints(int points);

    void ComputeScore(int currentPlayerIndex,vector<Player*> players,Map* map);

    void ComputeVPFlying(Cards c);

    void ComputeVPNoble(Cards c);

    void ComputeVPMountain(Cards c);

    void ComputeCards();

    void checkForMostElixers(int currentPlayerIndex,vector<Player*> players);

    void applyAbility();

private:
    //just one attribute added for stream insertion operator
    std::unique_ptr<std::string> region_;
    BiddingFacility* biddingFacility_;
    std::unique_ptr<Territory> territory_;
    std::unique_ptr<Cards> cards_;
    int tokenArmies_; //for now is an int, but maybe will change for class "Token"?
    std::unique_ptr<int> cubes_;//for now is an int, but maybe will change for class "Cubes"?
    int *victoryPoints_;
    int *elixers_;
    int disks_;//for now is an int, but maybe will change for class "Disks"?
    int money_;
    std::unique_ptr<std::string> name_;
    std::unique_ptr<int> totalMovementPointsForRound_;
    std::unique_ptr<int> costToMoveOverWater_;
    std::unique_ptr<bool> canBeAttacked_;



    //TODO add terrs
    //TODO add hand of cards meaning cards class


};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H

