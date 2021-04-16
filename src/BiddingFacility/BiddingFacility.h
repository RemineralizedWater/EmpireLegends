#pragma once

#include <string>
#include "../Player/Player.h"

using namespace std;

class Player;

class BiddingFacility {
private: // var camelCase
    string lastName;
    int coins;
    int bidAmount;
    bool isStartingPlayer;
    Player *owningPlayer;

public: // var PascalCase
    BiddingFacility();

    BiddingFacility(const BiddingFacility &copy);

    BiddingFacility(string lastName_, int coins_, int bidAmount_, Player *owningPlayer_, bool isStartingPlayer_);

    ~BiddingFacility();

    BiddingFacility &operator=(const BiddingFacility &bf);

    friend ostream &operator<<(ostream &out, const BiddingFacility &bf);

    friend istream &operator>>(istream &in, BiddingFacility &bf);

    string GetLastName();

    int GetCoins();

    int GetBidAmount();

    void SetLastName(string lastName_);

    void SetOwningPlayer(Player *owningPlayer_);

    void ReceiveStartingCoins(int numberOfPlayers);

    void EnterBid();

    void RevealBid();

    void ResolveBid(bool hasWonBid);
};
