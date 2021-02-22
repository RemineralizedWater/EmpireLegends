
#include <iostream>
#include <limits>


using namespace std;

void DemonstratePlayers();
void DemonstrateBiddingFacility(int numberOfPlayers);
void DemonstrateMapLoader(int numberOfPlayers);
void DemonstrateCards(int numberOfPlayers);

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
                // TODO MAP
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
