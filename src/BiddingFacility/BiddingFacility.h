#ifndef EMPIRELEGENDS_BIDDINGFACILITY_H
#define EMPIRELEGENDS_BIDDINGFACILITY_H

#include <string>

using namespace std;

class BiddingFacility {
private:


    string* lastName;
    int* coins;
    int* bidAmount;

public:
    void ReceiveStartingCoins(int numberOfPlayers);
    void EnterBid();
    void RevealBid();
    void ResolveBid(bool hasWonBid);
    string* GetLastName();
    int* GetCoins();
    int* GetBidAmount();
    BiddingFacility();
    BiddingFacility(string name);
    ~BiddingFacility();
    BiddingFacility(const BiddingFacility &copy);
    BiddingFacility(string* _lastName, int* _coins, int* _bidAmount);
    BiddingFacility(string* _lastName, int* _coins);
    explicit BiddingFacility(string* _lastName);
    BiddingFacility & operator =(const BiddingFacility &bf);
    friend ostream & operator << (ostream &out, const BiddingFacility &bf);
    friend istream & operator >> (istream &in, BiddingFacility &bf);


    //void initializeCoins(BiddingFacility H);
};


#endif //EMPIRELEGENDS_BIDDINGFACILITY_H
