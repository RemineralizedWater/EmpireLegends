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

class Player {
public:
    static int supply;
    Hand *hand_;

    Player();

    ~Player();

    Player(const Player &playerToCopy);

    Player(const std::string &region, const BiddingFacility &biddingFacility, const Territory &territory,
           const Cards &cards, const int &tokenArmies,
           const int &cubes, const int &disks, Hand *hand, const int &money, const std::string &name,
           const int &totalMovementPointsForRound, const int &costToMoveOverWater, const bool &canBeAttacked);

    Player &operator=(const Player &playerToCopy);

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

    int &getMoney();

    void setMoney(const int &money);

    int &getTotalMovementPointsForRound();

    void setTotalMovementPointsForRound(const int &totalMovementPointsForRound);

    friend std::istream &operator>>(std::istream &is, Player &player);

    void ResolveActiveCard();

private:
    //just one attribute added for stream insertion operator
    std::unique_ptr<std::string> region_;
    std::unique_ptr<BiddingFacility> biddingFacility_;
    std::unique_ptr<Territory> territory_;
    std::unique_ptr<Cards> cards_;
    std::unique_ptr<int> tokenArmies_; //for now is an int, but maybe will change for class "Token"?
    std::unique_ptr<int> cubes_;//for now is an int, but maybe will change for class "Cubes"?
    std::unique_ptr<int> disks_;//for now is an int, but maybe will change for class "Disks"?
    std::unique_ptr<int> money_;
    std::unique_ptr<std::string> name_;
    std::unique_ptr<int> totalMovementPointsForRound_;
    std::unique_ptr<int> costToMoveOverWater_;
    std::unique_ptr<bool> canBeAttacked_;



    //TODO add terrs
    //TODO add hand of cards meaning cards class


};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H

