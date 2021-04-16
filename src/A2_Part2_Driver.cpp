
#include "Player/Player.h"
#include <memory>
#include <sstream>
#include "Cards/Deck.h"

void DemonstrateA2Part2() {

    Player *player1(new Player("Montreal",
                               new BiddingFacility(),
                               *(new Territory()),
                               *(new Cards()),
                               0,
                               1,
                               0,
                               new Hand(),
                               0,
                               "Player 1",
                               0,
                               3,
                               true,
                               0,
                               0));
    player1->Hands->SetOwningPlayer(player1);
    player1->GetBiddingFacility()->SetOwningPlayer(player1);

    cout << "Enter Player 1 Name: " << endl;
    string temp = " ";
    cin >> temp;
    player1->GetBiddingFacility()->SetLastName(temp);

    Player *player2(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       0,
                       "Player 1",
                       0,
                       3,
                       true,
                       0,
                       0));
    player2->Hands->SetOwningPlayer(player2);
    player2->GetBiddingFacility()->SetOwningPlayer(player2);

    cout << "Enter Player 2 Name: " << endl;
    string temp2 = "";
    cin >> temp2;
    player2->GetBiddingFacility()->SetLastName(temp2);


    Player *players[2] = {player1, player2};

    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(2);
    cout << "Shuffling deck.." << endl;
    deck->ShuffleDeck();
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();
    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));

    cout << "Neutral Armies has Been Placed in PlaceHolder Territory." << endl;

    cout << endl;
    cout << "/////////////////////PLAYER1/////////////////////" << endl;
    cout << endl;
    //PLAYER#1//////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << player1->GetName() << " currently has " << player1->GetArmiesTokens() << " Armies." << endl;
    cout << "Assigning 18 armies to " << player1->GetName() << endl;
    player1->SetArmiesTokens(18);
    cout << player1->GetName() << " currently has " << player1->GetArmiesTokens() << " Armies." << endl;
    cout << "----------------------------------" << endl;

    cout << player1->GetName() << " currently has " << player1->GetCitiesDisks() << " Cities." << endl;
    cout << "Assigning 3 disks to " << player1->GetName() << endl;
    player1->SetCitiesDisks(3);
    cout << player1->GetName() << " currently has " << player1->GetCitiesDisks() << " Cities." << endl;
    cout << "----------------------------------" << endl;

    cout << "Placing 4 armies in starting Territories." << endl;
    Territory *terr = new Territory();
    terr->InsertNewArmyPlayerMapping(player1->GetName());
    terr->InsertNewCityPlayerMapping(player1->GetName());

    terr->GetHasCity()[player1->GetName()] = true;
    player1->PlaceNewArmies(4);
    cout << "----------------------------------" << endl;

    cout << player1->GetName() << " Currently has " << player1->GetMoney() << " Coins." << endl;
    cout << "Assigning 14 Coins to " << player1->GetName() << endl;
    player1->SetMoney(14);
    cout << player1->GetName() << " Currently has " << player1->GetMoney() << " Coins." << endl;
    cout << endl;
    cout << "/////////////////////PLAYER2/////////////////////" << endl;
    cout << endl;
    //PLAYER#2//////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << player2->GetName() << " currently has " << player2->GetArmiesTokens() << " Armies." << endl;
    cout << "Assigning 18 armies to " << player2->GetName() << endl;
    player2->SetArmiesTokens(18);
    cout << player2->GetName() << " currently has " << player2->GetArmiesTokens() << " Armies." << endl;
    cout << "----------------------------------" << endl;

    cout << player2->GetName() << " currently has " << player2->GetCitiesDisks() << " Cities." << endl;
    cout << "Assigning 3 disks to " << player2->GetName() << endl;
    player2->SetCitiesDisks(3);
    cout << player2->GetName() << " currently has " << player2->GetCitiesDisks() << " Cities." << endl;
    cout << "----------------------------------" << endl;

    cout << "Placing 4 armies in starting Territories." << endl;
    Territory *terr2 = new Territory();
    terr2->InsertNewArmyPlayerMapping(player2->GetName());
    terr2->InsertNewCityPlayerMapping(player2->GetName());

    terr2->GetHasCity()[player2->GetName()] = true;
    player2->PlaceNewArmies(4);
    cout << "----------------------------------" << endl;

    cout << player2->GetName() << " Currently has " << player2->GetMoney() << " Coins." << endl;
    cout << "Assigning 14 Coins to " << player2->GetName() << endl;
    player2->SetMoney(14);
    cout << player2->GetName() << " Currently has " << player2->GetMoney() << " Coins." << endl;

    cout << "/////////////////////////////////" << endl;

    // enter bids
    for (int i = 0; i < 2; i++) {
        cout << "Bidding details for player " << players[i]->GetName() << endl;


        players[i]->GetBiddingFacility()->EnterBid();

        for (int j = 0; j < 100; j++) {
            cout << endl;
        }
    }

    // reveal bids
    for (int i = 0; i < 2; i++) {
        players[i]->GetBiddingFacility()->RevealBid();
    }

    // determine bid winner
    Player *winningBidPlayer;
    int highestBid = -1;
    for (int i = 0; i < 2; i++) {

        if (players[i]->GetBiddingFacility()->GetBidAmount() > highestBid) {
            highestBid = players[i]->GetBiddingFacility()->GetBidAmount();
            winningBidPlayer = players[i];
        }
    }

    for (int i = 0; i < 2; i++) {

        if (players[i]->GetBiddingFacility()->GetBidAmount() == highestBid &&
            players[i]->GetName().compare(winningBidPlayer->GetName()) < 0) {
            winningBidPlayer = players[i];
        }
    }

    for (int i = 0; i < 2; i++) {
        if (players[i] == winningBidPlayer) {
            players[i]->GetBiddingFacility()->ResolveBid(true);
        } else {
            players[i]->GetBiddingFacility()->ResolveBid(false);
        }
    }
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
    delete deck;
    deck = nullptr;
    delete terr;
    terr = nullptr;

    return;
}