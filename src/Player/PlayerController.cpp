#include "PlayerController.h"

PlayerController::PlayerController(PlayerObserver *newView, Player *newModel) {
    playerView = newView;
    playerModel = newModel;
}

void PlayerController::ControlPlayer() {


    // TODO: I think we should implement turns here

    /**
     * Testing Observer

    while(true){
        int command = 0;
        cout << "1. Set player name" << endl;
        cout << "2. Set number of armies" << endl;
        cout << "3. Set number of cities" << endl;
        cout << "4. Set total victory points" << endl;
        cout << "5. Set amount of money" << endl;
        cout << "6. Exit (<return>)" << endl;
        cout << "What would you like to do? : ";
        cin >> command;

        string name;
        int armies, cities, VP,money;

        switch (command) {
            case 1:
                cout << "Name: ";
                cin >> name;
                playerModel->SetName(name);
                break;
            case 2:
                cout << "# : ";
                cin >> armies;
                playerModel->SetArmiesTokens(armies);
                break;
            case 3:
                cout << "# : ";
                cin >> cities;
                playerModel->SetCitiesDisks(cities);
                break;
            case 4:
                cout << "# : ";
                cin >> VP;
                playerModel->SetVictoryPoints(VP);
                break;
            case 5:
                cout << "$ : ";
                cin >> money;
                playerModel->SetMoney(money);
                break;
            case 6:
            default:
                return;
        }
    }*/
}
