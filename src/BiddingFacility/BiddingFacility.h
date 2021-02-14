#ifndef EMPIRELEGENDS_BIDDINGFACILITY_H
#define EMPIRELEGENDS_BIDDINGFACILITY_H

#include <string>

using namespace std;

class BiddingFacility {
public:
    //int numberOfPlayers;
    int coins;
    int bidAmount;
    string lastName;
    void ReceiveStartingCoins(int numberOfPlayers);
    void EnterBid();
    void RevealBid();
    void ResolveBid(bool hasWonBid);
};


#endif //EMPIRELEGENDS_BIDDINGFACILITY_H
