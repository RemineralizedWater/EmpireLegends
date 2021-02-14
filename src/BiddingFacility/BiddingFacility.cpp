// Implementation of Bidding Facility class

#include "BiddingFacility.h"
#include <iostream>
#include <string>

using namespace std;

int coins;
int bidAmount;
string lastName;

// Enable the Player Object to pick up their coins
void BiddingFacility::ReceiveStartingCoins(int numberOfPlayers){
    coins = 0;
    if(numberOfPlayers == 2) coins = 14;
    else if(numberOfPlayers == 3 ) coins = 11;
    else if(numberOfPlayers == 4) coins = 9;
}

// Enable the Player Object to privately choose a number to bid
void BiddingFacility::EnterBid(){
    cout << "Player last name:";
    cin >> lastName;

    cout << "Enter starting bid (you have " << coins << " coins):";
    while(true){
        if(cin >> bidAmount && bidAmount <= coins){
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