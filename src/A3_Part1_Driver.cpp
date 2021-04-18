#include "Player/Player.h";
#include "Player/PlayerStrategies.h";

void DemonstrateA3Part1() {
    PlayerStrategies *greedy = new GreedyComputerStrategy();
    PlayerStrategies *human = new HumanStrategy();
    PlayerStrategies *moderate = new ModerateComputerStrategy();

    Player *player1 (
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       20,
                       "Player 1",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()
            ));
    Player *player2(
            new Player("Montreal",
                       new BiddingFacility(),
                       *(new Territory()),
                       *(new Cards()),
                       0,
                       1,
                       0,
                       new Hand(),
                       20,
                       "Player 2",
                       0,
                       3,
                       true,
                       0,
                       0,
                       new Map()
            ));
    player1->MyHand->SetOwningPlayer(player1);
    player1->SetStrategy(greedy);

    player2->MyHand->SetOwningPlayer(player2);
    player2->SetStrategy(human);


    cout << "Creating deck.." << endl;
    Deck *deck = new Deck(2);
    cout << "Populating Face Up Cards.." << endl;
    deck->PopulateFaceUpCards();

    player1->ExecuteStrategy(deck);
    player2->ExecuteStrategy(deck);

    player2->SetStrategy(moderate);
    player2->ExecuteStrategy(deck);

    // Memory clean up
    if (greedy != nullptr) {
        delete greedy;
        greedy = nullptr;
    }
    if (moderate != nullptr) {
        delete moderate;
        moderate = nullptr;
    }
    if (human != nullptr) {
        delete human;
        human = nullptr;
    }
    if (player1 != nullptr) {
        delete player1;
        player1 = nullptr;
    }
    if (player2 != nullptr) {
        delete player2;
        player2 = nullptr;
    }
    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }
}
