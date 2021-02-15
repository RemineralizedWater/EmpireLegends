// Implementation of Bidding Facility class

#include "BiddingFacility.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

int coins;
int bidAmount;
string lastName;

// Constructors
BiddingFacility::BiddingFacility() {
    cout << "Player last name:";
    cin >> lastName;
    coins = 0;
    bidAmount = 0;
}

BiddingFacility::BiddingFacility(BiddingFacility &copy){
    lastName = copy.lastName;
    coins = copy.coins;
    bidAmount = copy.bidAmount;
}

BiddingFacility::BiddingFacility(string _lastName, int _coins, int _bidAmount){
    lastName = move(_lastName);
    coins = _coins;
    bidAmount = _bidAmount;
}
BiddingFacility::BiddingFacility(string _lastName, int _coins){
    lastName = move(_lastName);
    coins = _coins;
    bidAmount = 0;
}
BiddingFacility::BiddingFacility(string _lastName){
    lastName = move(_lastName);
    coins = 0;
    bidAmount = 0;
}

// Accessors
string BiddingFacility::GetLastName(){
    return lastName;
}

int BiddingFacility::GetCoins(){
    return coins;
}

int BiddingFacility::GetBidAmount(){
    return bidAmount;
}

// Assignment Operator
BiddingFacility & BiddingFacility::operator =(const BiddingFacility &bf){
    lastName = bf.lastName;
    coins = bf.coins;
    bidAmount = bf.bidAmount;
}

// Stream Insertion Operators
ostream & operator << (ostream &out, const BiddingFacility &bf){
    out << "last name: " << bf.lastName << ", coins: " << bf.coins << ", bid amount: " << bf.bidAmount << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream & operator >> (istream &in, BiddingFacility &bf){
    cout << "Enter last name:";
    in >> bf.lastName;
    cout << "Enter coins:";
    in >> bf.coins;
    cout << "Enter bid amount:";
    in >> bf.bidAmount;
    return in;
}

// Enable the Player Object to pick up their coins
void BiddingFacility::ReceiveStartingCoins(int numberOfPlayers){
    coins = 0;
    if(numberOfPlayers == 2) coins = 14;
    else if(numberOfPlayers == 3 ) coins = 11;
    else if(numberOfPlayers == 4) coins = 9;
}

// Enable the Player Object to privately choose a number to bid
void BiddingFacility::EnterBid(){

    cout << "Enter starting bid (you have " << coins << " coins):";
    while(true){
        if(cin >> bidAmount && bidAmount <= coins && bidAmount >= 0){
            cout << "Bid amount of (" << bidAmount << ") received." << endl;
            break;
        }else{
            cout << "Please enter a valid bid (integer, no greater than " << coins << ")" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// All Players to reveal the amount they have chosen to bid at the same time
void BiddingFacility::RevealBid(){
    cout << lastName << " bid " << bidAmount << " coins." << endl;
}

// The Player who bids the most coins wins the bid and the coins are placed in the Supply
// If the bids are tied, or all the bids are zero, the player with the alphabetical last
// name order wins the bid and will go first (if coins are bid they are paid).
void BiddingFacility::ResolveBid(bool hasWonBid){
    if(hasWonBid){
        cout << lastName << " has won the bid! " << endl;
        cout << bidAmount << " has been added to the Supply." << endl;
        cout << lastName << " has lost " << bidAmount << " coins." << endl;
    }else{
        cout << lastName << " has lost the bid. They keep their coins." << endl;
    }
}

