
#include <iostream>
#include <limits>
#include "BiddingFacility/BiddingFacility.h"


using namespace std;

void DemonstratePlayers();
void DemonstrateBiddingFacility(int numberOfPlayers);
void DemonstrateMapLoader(int numberOfPlayers);
void DemonstrateCards(int numberOfPlayers);
int DemonstrateMap(int numberOfPlayers);

int main() {

    int numberOfPlayers = 0;
    int userInput = 0;

    // Determine the number of players
    cout << "Enter the number of players:";
    while(true){
        if(cin >> numberOfPlayers && numberOfPlayers >= 2 && numberOfPlayers <= 4){
            cout<<numberOfPlayers<<endl;
            break;
        }else{
            cout << "Please enter a valid number of players (integer, no greater than 4 and no less than 2)" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }


    //  while(true){
        if (numberOfPlayers==2){
            cout << "Enter the name of players1:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;


            cout << "Enter the name of players2:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;
        }
        if (numberOfPlayers==3){
            cout << "Enter the name of players1:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;

            cout << "Enter the name of players2:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;

            cout << "Enter the name of players3:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;
        }
        if (numberOfPlayers==4){
            cout << "Enter the name of players1:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;

            cout << "Enter the name of players2:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;

            cout << "Enter the name of players3:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;

            cout << "Enter the name of players4:"<< endl;
            //cin>>Player.name;
            cout << "There are 4 colour armies and cities: Red,Blue,Green and Yellow. Please Select army and city colour:"<< endl;
            //cin>>Player.army;
            cout << "You are assigned 14 coins."<< endl;
        }
    //}

    while(true){
        cout << endl << "What would you like to test:" << endl;
        cout << "1 - Part 1: Map" << endl;
        cout << "2 - Part 2: Map Loader" << endl;
        cout << "3 - Part 3: Player" << endl;
        cout << "4 - Part 4: Cards" << endl;
        cout << "5 - Part 5: Bidding Facility" << endl;
        cout << "6 - Exit" << endl;

        while(true){
            if(cin >> userInput && userInput >= 1 && userInput <= 6){
                break;
            }else{
                cout << "Please enter a valid selection (integer, no greater than 6 and no less than 1)" << endl << ">>";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        switch (userInput) {
            case 1:
                DemonstrateMap(numberOfPlayers);
                break;
            case 2:
                DemonstrateMapLoader(numberOfPlayers);
                break;
            case 3:
                DemonstratePlayers();
                break;
            case 4:
                DemonstrateCards(numberOfPlayers);
                break;
            case 5:
                DemonstrateBiddingFacility(numberOfPlayers);
                break;
            case 6:
            default:
                exit(0);
        }
    }

    return 0;
}
