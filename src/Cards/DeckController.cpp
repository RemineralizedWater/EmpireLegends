#include "DeckController.h"

DeckController::DeckController(DeckObserver *newView, Deck *newModel) {
    deckView = newView;
    deckModel = newModel;
}

void DeckController::ControlDeck() {
    cout << "Populating Face-Up Cards.." << endl;
    deckModel->PopulateFaceUpCards();
}
