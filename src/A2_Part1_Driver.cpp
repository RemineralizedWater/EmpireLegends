#include <iostream>
#include "Player/Player.h"
#include "Cards/Deck.h"
#include "Map/Map.h"
#include "Map Loader/MapLoader.h"

void DemonstrateA2Part1(){

    //map related
    std::string input;
    std::string file;
    std::cout << "\nChoose a map file to load \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt"<< std::endl;
    std::cin >> input;

    while(true){
        if( input == "1" ){
            file= "../src/Map Boards/valid_map.txt";
            break;
        }
        else if(input == "2"){
            file= "../src/Map Boards/invalid1_map.txt";
            break;
        }
        else if(input == "3"){
            file= "../src/Map Boards/invalid2_map.txt";
            break;
        }
        else if(input == "4"){
            file= "../src/Map Boards/invalid3_map.txt";
            break;
        }
        else{
            std::cout << "Please enter a valid number \n1) valid_map.txt \n2) invalid1_map.txt \n3) invalid2_map.txt \n4) invalid3_map.txt"<< std::endl;
            std::cin >> input;
        }
    }
    bool validMap=false;
    MapLoader *mapLoader = new MapLoader(2);
    Map* map=mapLoader->loadMap(file, validMap);

    if(validMap){
        map->display();
    }
    cout<<"\n\n\n\n"<<endl;

    //bidding facilities
    BiddingFacility *b1 =new BiddingFacility();
    BiddingFacility *b2 =new BiddingFacility();

    b1->ReceiveStartingCoins(2);
    b2->ReceiveStartingCoins(2);

    //players
    Player *player1(
            new Player("1",
                       *b1,
                       Territory(),
                       Cards(),
                       new int(0),
                       1,
                       new int(0),
                       new Hand(),
                       b1->GetCoins(),
                       *(b1->GetLastName()),
                       0,
                       3,
                       true));
    player1->hand_->SetOwningPlayer(player1);

    Player *player2(
            new Player("1",
                       *b2,
                       Territory(),
                       Cards(),
                       new int(0),
                       1,
                       new int(0),
                       new Hand(),
                       b2->GetCoins(),
                       *(b2->GetLastName()),
                       0,
                       3,
                       true));
    player2->hand_->SetOwningPlayer(player2);

    Player *players[2] = {player1, player2};
    for(int i=0;i<2;i++){
            cout << "LastName:"<<*(players[i]->getBiddingFacility().GetLastName()) <<" Money:"<<players[i]->getMoney()<< " Bid Amount:" <<*(players[i]->getBiddingFacility().GetBidAmount())<<endl;
    }

    cout<<"\n\n\n\n"<<endl;

    cout << "Creating deck.." << endl;
    Deck* deck = new Deck(2);
    cout<< "Shuffling deck.."<<endl;
    deck->ShuffleDeck();

    cout << "Cards in deck: " << endl;
    deck->PrintCardsIn(deck->GetDeck());
}