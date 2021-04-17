#include "BiddingFacility.h"
#include <iostream>
#include <vector>

using namespace std;

// Driver for the Part 5 - Bidding Facility class
// Tests:
// 1. Show a player who bid the most coins wins
// 2. Show bids which are tied
// 3. Show if all bids are zero

void DemonstrateBiddingFacility(int numberOfPlayers) {

    int whiteLines = 100;

    cout << endl << "Beginning Bidding Phase!" << endl << endl;

    // Initialization of BiddingFacilities, each player must enter their last name and starting bid amount
    vector<BiddingFacility> biddingFacilities;
    for (int i = 0; i < numberOfPlayers; i++) {
        cout << "Bidding details for player #" << (i + 1) << endl;
        BiddingFacility newBiddingFacility;
        newBiddingFacility.ReceiveStartingCoins(numberOfPlayers);
        newBiddingFacility.EnterBid();
        biddingFacilities.push_back(newBiddingFacility);

        for (int j = 0; j < whiteLines; j++) {
            cout << endl;
        }
    }

    // Each player reveals their bid
    for (int i = 0; i < numberOfPlayers; i++) {
        biddingFacilities[i].RevealBid();
    }

    // Determine which player(s) placed the highest bid
    BiddingFacility *bidWinner;
    int highestBid = -1;
    for (int i = 0; i < numberOfPlayers; i++) {
        if (biddingFacilities[i].GetBidAmount() > highestBid) {
            highestBid = biddingFacilities[i].GetBidAmount();
            bidWinner = &biddingFacilities[i];
        }
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        if (biddingFacilities[i].GetBidAmount() == highestBid &&
            (biddingFacilities[i].GetLastName()).compare(bidWinner->GetLastName()) < 0) {
            bidWinner = &biddingFacilities[i];
        }
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        if (&biddingFacilities[i] == bidWinner) {
            biddingFacilities[i].ResolveBid(true);
        } else {
            biddingFacilities[i].ResolveBid(false);
        }
    }

    // Memory clean up
    if (bidWinner != nullptr) {
        delete bidWinner;
        bidWinner = nullptr;
    }
}
