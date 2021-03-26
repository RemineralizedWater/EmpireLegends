//
// Created by Hsen on 2021-03-25.
//

//
// Created by Hsen on 2021-03-24.
//


#include <iostream>
#include <vector>
#include "Cards.h"
#include "../Player/Player.h"
#include "../BiddingFacility/BiddingFacility.h"


void DemonstrateCards(int numberOfPlayers);
void DemonstrateBiddingFacility(int numberOfPlayers, string name);

void DemonstratePart2(int numberOfPlayers,string name) {




    // Determine the number of players


    //  while(true){
     if (numberOfPlayers==2){
         cout<<"------------"<<endl;
         cout << "Enter the name of player1:"<< endl;
         cout<<"------------"<<endl;
         Player P1;

         cin>>name;
         P1.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P1.getName()<<endl;
         cout<<"------------"<<endl;

         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;


         P1.setMoney(14);
         cout << "You are assigned "<<P1.getMoney() << " coins."<< endl;
         cout << "How much would you like to Bid?"<< endl;
        // cin>>BiddingFacility::bidAmount<<endl;


         cout<<"------------"<<endl;
         cout << "Enter the name of player2:"<< endl;
         cout<<"------------"<<endl;
         Player P2;

         cin>>name;
         P2.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P2.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P2.setMoney(14);
         cout << "You are assigned "<<P2.getMoney() << " coins."<< endl;
     }
     if (numberOfPlayers==3){
         cout<<"------------"<<endl;
         cout << "Enter the name of player1:"<< endl;
         cout<<"------------"<<endl;
         Player P1;

         cin>>name;
         P1.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P1.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P1.setMoney(14);
         cout << "You are assigned "<<P1.getMoney() << " coins."<< endl;

         cout<<"------------"<<endl;
         cout << "Enter the name of player2:"<< endl;
         cout<<"------------"<<endl;
         Player P2;

         cin>>name;
         P2.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P2.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P2.setMoney(14);
         cout << "You are assigned "<<P2.getMoney() << " coins."<< endl;

         cout<<"------------"<<endl;
         cout << "Enter the name of player3:"<< endl;
         cout<<"------------"<<endl;
         Player P3;

         cin>>name;
         P3.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P3.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P3.setMoney(14);
         cout << "You are assigned "<<P3.getMoney() << " coins."<< endl;
     }
     if (numberOfPlayers==4){
         cout<<"------------"<<endl;
         cout << "Enter the name of player1:"<< endl;
         cout<<"------------"<<endl;
         Player P1;

         cin>>name;
         P1.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P1.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P1.setMoney(14);
         cout << "You are assigned "<<P1.getMoney() << " coins."<< endl;

         cout<<"------------"<<endl;
         cout << "Enter the name of player2:"<< endl;
         cout<<"------------"<<endl;
         Player P2;

         cin>>name;
         P2.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P2.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P2.setMoney(14);
         cout << "You are assigned "<<P2.getMoney() << " coins."<< endl;

         cout<<"------------"<<endl;
         cout << "Enter the name of player3:"<< endl;
         cout<<"------------"<<endl;
         Player P3;

         cin>>name;
         P3.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P3.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P3.setMoney(14);
         cout << "You are assigned "<<P3.getMoney() << " coins."<< endl;

         cout<<"------------"<<endl;
         cout << "Enter the name of player4:"<< endl;
         cout<<"------------"<<endl;
         Player P4;

         cin>>name;
         P4.setName(name);
         cout<<"------------"<<endl;
         cout<<"Hello:"<<P4.getName()<<endl;
         cout<<"------------"<<endl;
         cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
         //cin>>Player.army;
         P4.setMoney(14);
         cout << "You are assigned "<<P4.getMoney() << " coins."<< endl;
     }
     //}

     DemonstrateCards(numberOfPlayers);

     DemonstrateBiddingFacility(numberOfPlayers,name);

}
