// Implementation of Bidding Facility class

#include "BiddingFacility.h"
#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace std;

int coins;
int bidAmount;
string lastName;

// Constructors
BiddingFacility::BiddingFacility() {
    lastName = new string("blank");
    coins = new int{0};
    bidAmount = new int{0};
    owningPlayer = nullptr;
    isStartingPlayer = new bool(false);
}

BiddingFacility::BiddingFacility(const BiddingFacility &copy){
    this->lastName = new string(*(copy.lastName));
    this->coins = new int(*(copy.coins));
    this->bidAmount = new int(*(copy.bidAmount));
    this->owningPlayer = copy.owningPlayer;
    this->isStartingPlayer = new bool(*(copy.isStartingPlayer));
}

BiddingFacility::BiddingFacility(string* _lastName, int* _coins, int* _bidAmount, Player* _owningPlayer, bool* _isStartingPlayer){
    lastName = new string(*_lastName);
    coins = new int(*_coins);
    bidAmount = new int(*_bidAmount);
    owningPlayer = _owningPlayer;
    isStartingPlayer = new bool(*_isStartingPlayer);
}

// Accessors
string* BiddingFacility::GetLastName(){
    return lastName;
}

int* BiddingFacility::GetCoins(){
    return coins;
}

int* BiddingFacility::GetBidAmount(){
    return bidAmount;
}

// Assignment Operator
BiddingFacility& BiddingFacility::operator =(const BiddingFacility &bf){
    this->lastName = new string(*(bf.lastName));
    this->coins = new int(*(bf.coins));
    this->bidAmount = new int(*(bf.bidAmount));
    this->owningPlayer = bf.owningPlayer;
    this->isStartingPlayer = new bool(*bf.isStartingPlayer);
    return *this;
}

// Stream Insertion Operators
ostream& operator << (ostream &out, const BiddingFacility &bf){
    out << "last name: " << *(bf.lastName) << ", coins: " << *(bf.coins) << ", bid amount: " << *(bf.bidAmount) << endl;
    return out;
}

// Note: obj needs to be dereferenced when using cout (ie, cout << *foo)
istream& operator >> (istream &in, BiddingFacility &bf){
    in >> *bf.lastName;
    in >> *bf.coins;
    in >> *bf.bidAmount;
    in >> *bf.owningPlayer;
    in >> *bf.isStartingPlayer;
    return in;
}

//Obsolete
void BiddingFacility::ReceiveStartingCoins(int numberOfPlayers){
    coins = new int{0};
    if(numberOfPlayers == 2) coins = new int{14};
    else if(numberOfPlayers == 3 ) coins = new int{11};
    else if(numberOfPlayers == 4) coins = new int{9};
}

// Enable the Player Object to privately choose a number to bid
void BiddingFacility::EnterBid(){

    cout << "Enter starting bid (you have " << owningPlayer->getMoney() << " coins):";
    while(true){
        if(cin >> *bidAmount && *bidAmount <= owningPlayer->getMoney() && *bidAmount >= 0){
            cout << "Bid amount of (" << *bidAmount << ") received." << endl;
            break;
        }else{
            cout << "Please enter a valid bid (integer, no greater than " << owningPlayer->getMoney() << ")" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// All Players to reveal the amount they have chosen to bid at the same time
void BiddingFacility::RevealBid(){
    cout << *lastName << " bid " << *bidAmount << " coins." << endl;
}

// The Player who bids the most coins wins the bid and the coins are placed in the Supply
// If the bids are tied, or all the bids are zero, the player with the alphabetical last
// name order wins the bid and will go first (if coins are bid they are paid).
void BiddingFacility::ResolveBid(bool hasWonBid){
    if(hasWonBid){
        cout << owningPlayer->getName() << " has won the bid! " << endl;
        cout << owningPlayer->getName() << " has lost " << *bidAmount << " coins and has " << owningPlayer->getMoney() << " coins left." << endl;
        owningPlayer->PayCoin(*bidAmount);
        owningPlayer->supply += *bidAmount;
        cout << *bidAmount << " has been added to the Supply." << endl;
    }else{
        cout << owningPlayer->getName() << " has lost the bid. They keep their coins." << endl;
    }
}

BiddingFacility::~BiddingFacility() {
    if(coins != nullptr){
        delete coins;
        coins = nullptr;
    }

    if(bidAmount != nullptr){
        delete bidAmount;
        bidAmount = nullptr;
    }

    if(lastName != nullptr){
        delete lastName;
        lastName = nullptr;
    }

    //if(owningPlayer != nullptr){
    //    delete owningPlayer;
    //    owningPlayer = nullptr;
    //}

    if(isStartingPlayer != nullptr){
        delete isStartingPlayer;
        isStartingPlayer = nullptr;
    }
}

void BiddingFacility::SetOwningPlayer(Player *_owningPlayer) {
    owningPlayer = _owningPlayer;
}

void BiddingFacility::SetLastName(string name) {
    lastName = new string(name);
}

