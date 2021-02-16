#include <iostream>

using namespace std;

void DemonstratePlayers();

void DemonstrateBiddingFacility(int numberOfPlayers);

int main() {
    int numberOfPlayers = 0;

    // Determine the number of players
    cout << "Enter the number of players:";
    while(true){
        if(cin >> numberOfPlayers && numberOfPlayers >= 2 && numberOfPlayers <= 4){
            break;
        }else{
            cout << "Please enter a valid number of players (integer, no greater than 4 and no less than 2)" << endl << ">>";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    DemonstratePlayers();
  
    DemonstrateBiddingFacility(numberOfPlayers);

    return 0;
}
