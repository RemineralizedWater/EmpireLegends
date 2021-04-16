// Implementation of Bidding Facility class

#include "BiddingFacility.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Constructors
BiddingFacility::BiddingFacility() {
    lastName = "";
    coins = 0;
    bidAmount = 0;
    owningPlayer = nullptr;
    isStartingPlayer = false;
}

BiddingFacility::BiddingFacility(const BiddingFacility &copy) {
    lastName = copy.lastName;
    coins = copy.coins;
    bidAmount = copy.bidAmount;
    owningPlayer = new Player(*copy.owningPlayer);
    isStartingPlayer = copy.isStartingPlayer;
}

BiddingFacility::BiddingFacility(string lastName_, int coins_, int bidAmount_, Player* owningPlayer_, bool isStartingPlayer_) {
    lastName = lastName_;
    coins = coins_;
    bidAmount = bidAmount_;
    owningPlayer = owningPlayer_;
    isStartingPlayer = isStartingPlayer_;
}

// Destructor
BiddingFacility::~BiddingFacility() {
    delete owningPlayer;
    owningPlayer = nullptr;
}

// Assignment Operator
BiddingFacility& BiddingFacility::operator=(const BiddingFacility &bf) {
    lastName = bf.lastName;
    coins = bf.coins;
    bidAmount = bf.bidAmount;
    owningPlayer = new Player(*bf.owningPlayer);
    isStartingPlayer = bf.isStartingPlayer;
    return *this;
}

// Stream Insertion Operators
ostream& operator << (ostream &out, const BiddingFacility &bf) {
    out << "last name: " << bf.lastName << ", coins: " << bf.coins << ", bid amount: " << bf.bidAmount << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream& operator >> (istream &in, BiddingFacility &bf) {
    in >> bf.lastName;
    in >> bf.coins;
    in >> bf.bidAmount;
    in >> *bf.owningPlayer;
    in >> bf.isStartingPlayer;
    return in;
}

// Accessors
string BiddingFacility::GetLastName() {
    return lastName;
}

int BiddingFacility::GetCoins(){
    return coins;
}

int BiddingFacility::GetBidAmount() {
    return bidAmount;
}

// Mutators
void BiddingFacility::SetOwningPlayer(Player *owningPlayer_) {
    owningPlayer = owningPlayer_;
}

void BiddingFacility::SetLastName(string lastName_) {
    lastName = lastName_;
}

//Obsolete
void BiddingFacility::ReceiveStartingCoins(int numberOfPlayers) {
    coins = 0;
    if (numberOfPlayers == 2) coins = 14;
    else if (numberOfPlayers == 3 ) coins = 11;
    else if (numberOfPlayers == 4) coins = 9;
}

// Enable the Player Object to privately choose a number to bid
void BiddingFacility::EnterBid() {
    cout << "Enter starting bid (you have " << owningPlayer->GetMoney() << " coins):";
    while (true) {
        if (cin >> bidAmount && bidAmount <= owningPlayer->GetMoney() && bidAmount >= 0) {
            cout << "Bid amount of (" << bidAmount << ") received." << endl;
            break;
        } else {
            cout << "Please enter a valid bid (integer, no greater than " << owningPlayer->GetMoney() << ")" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// All Players to reveal the amount they have chosen to bid at the same time
void BiddingFacility::RevealBid() {
    cout << lastName << " bid " << bidAmount << " coins." << endl;
}

// The Player who bids the most coins wins the bid and the coins are placed in the Supply
// If the bids are tied, or all the bids are zero, the player with the alphabetical last
// name order wins the bid and will go first (if coins are bid they are paid).
void BiddingFacility::ResolveBid(bool hasWonBid) {
    if (hasWonBid) {
        cout << owningPlayer->GetName() << " has won the bid! " << endl;
        cout << owningPlayer->GetName() << " has lost " << bidAmount << " coins and has " << owningPlayer->GetMoney() << " coins left." << endl;
        owningPlayer->PaysCoinFromPlayer(bidAmount);
        owningPlayer->Supply += bidAmount;
        cout << bidAmount << " has been added to the Supply." << endl;
    } else {
        cout << owningPlayer->GetName() << " has lost the bid. They keep their coins." << endl;
    }
}
