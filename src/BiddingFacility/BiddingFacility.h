#ifndef EMPIRELEGENDS_BIDDINGFACILITY_H
#define EMPIRELEGENDS_BIDDINGFACILITY_H

#include <string>
#include "../Player/Player.h"

using namespace std;

class Player;

class BiddingFacility {
private:
    string* lastName;
    int* coins;
    int* bidAmount;
    Player* owningPlayer;
    bool* isStartingPlayer;
public:
    void ReceiveStartingCoins(int numberOfPlayers);
    void EnterBid();
    void RevealBid();
    void ResolveBid(bool hasWonBid);
    string* GetLastName();
    void SetLastName(string name);
    int* GetCoins();
    int* GetBidAmount();
    void SetOwningPlayer(Player *_owningPlayer);
    BiddingFacility();
    ~BiddingFacility();
    BiddingFacility(const BiddingFacility &copy);
    BiddingFacility(string* _lastName, int* _coins, int* _bidAmount, Player* _owningPlayer, bool* isStartingPlayer);
    BiddingFacility & operator =(const BiddingFacility &bf);
    friend ostream & operator << (ostream &out, const BiddingFacility &bf);
    friend istream & operator >> (istream &in, BiddingFacility &bf);
};


#endif //EMPIRELEGENDS_BIDDINGFACILITY_H
