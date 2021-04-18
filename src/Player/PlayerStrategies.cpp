#include "PlayerStrategies.h"
//HumanStrategy
HumanStrategy::HumanStrategy() {
    this->strategyName="Human Player";
}
HumanStrategy::~HumanStrategy() {}
string HumanStrategy::GetStrategyName() {return strategyName;}

void HumanStrategy::Execute(Deck* deck,Player* player) {
    cout<<"--------"<<this->strategyName<<"----------"<<endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));
    int positionToPickUp;

    cout << "Which card from the Face Up Pile would you like to take: " ;
    cin >> positionToPickUp;
    bool enoughMoney=false;
    while(positionToPickUp>deck->GetFaceUpCards()->size()||!enoughMoney){
        if(positionToPickUp>deck->GetFaceUpCards()->size()){
            cout << "Please pick a valid card number" << endl;
            cin >> positionToPickUp;
            continue;
        }
        enoughMoney=player->MyHand->ExchangeWithoutPrompt(deck,positionToPickUp);
        if(!enoughMoney){
            cout << "Player does not have enough money to buy this card. Please select another." << endl;
            cin >> positionToPickUp;
            continue;
        }
    }
    cout << "**Would you like to perform the action(s)?**\n1. YES\n2. NO "<< endl;
    int playAction;
    cin >>playAction;
    while(playAction<1||playAction>2){
        cout<<"Please pick a valid option"<<endl;
        cin >>playAction;
    }
    //TODO: allow to pick action
    if(playAction==1){
        player->ResolveActiveCard();
    }

}

//GreedyComputerStrategy
GreedyComputerStrategy::GreedyComputerStrategy() {
    this->strategyName="Greedy Computer Player";
}
GreedyComputerStrategy::~GreedyComputerStrategy() {}
string GreedyComputerStrategy::GetStrategyName() {return strategyName;}

void GreedyComputerStrategy::Execute(Deck* deck,Player* player) {
    cout<<"--------"<<this->strategyName<<"----------"<<endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));


    cout << this->strategyName<<" is picking a card from the Face Up Pile..." <<endl;

    int positionToPickUp=1;

    for(int i=0;i<deck->GetFaceUpCards()->size();i++){
        //build city action
        if(deck->GetFaceUpCards()->at(i).GetActionOne()==3||deck->GetFaceUpCards()->at(i).GetActionTwo()==3||deck->GetFaceUpCards()->at(i).GetActionOne()==4||deck->GetFaceUpCards()->at(i).GetActionTwo()==4){
            positionToPickUp=i+1;
            break;
        }
    }

    bool enoughMoney=false;
    while(!enoughMoney){
        enoughMoney=player->MyHand->ExchangeWithoutPrompt(deck,positionToPickUp);
        if(!enoughMoney){
            positionToPickUp=rand() % deck->GetFaceUpCards()->size() + 1; ;
            continue;
        }
    }
    //TODO: build city or destroy army
    player->ResolveActiveCard();

}

//ModerateComputerStrategy
ModerateComputerStrategy::ModerateComputerStrategy() {
    this->strategyName="Moderate Computer Player";
}
ModerateComputerStrategy::~ModerateComputerStrategy() {}
string ModerateComputerStrategy::GetStrategyName() {return strategyName;}

void ModerateComputerStrategy::Execute(Deck* deck,Player* player) {
    cout<<"--------"<<this->strategyName<<"----------"<<endl;
    cout << "Cards in Face Up Pile:" << endl;
    deck->PrintCardsIn((deck->GetFaceUpCards()));


    cout << this->strategyName<<" is picking a card from the Face Up Pile..." <<endl;

    int positionToPickUp=1;

    for(int i=0;i<deck->GetFaceUpCards()->size();i++){
        //place army
        if(deck->GetFaceUpCards()->at(i).GetActionOne()==1||deck->GetFaceUpCards()->at(i).GetActionTwo()==1){
            positionToPickUp=i+1;
            break;
        }
    }

    bool enoughMoney=false;
    while(!enoughMoney){
        enoughMoney=player->MyHand->ExchangeWithoutPrompt(deck,positionToPickUp);
        if(!enoughMoney){
            positionToPickUp=rand() % deck->GetFaceUpCards()->size() + 1; ;
            continue;
        }
    }
    //TODO: try to control regions by placing its armies
    player->ResolveActiveCard();

}