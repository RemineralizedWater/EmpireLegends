//
// Created by Wayne on 4/17/2021.
//

#include "DeckController.h"

DeckController::DeckController(DeckObserver *newView, Deck *newModel) {
    deckView = newView;
    deckModel = newModel;
}

void DeckController::ControlDeck() {
    cout << "- - - - - - - - - - - - POPULATING FACE UP CARDS - - - - - - - - - - - -" << endl;
    deckModel->PopulateFaceUpCards();
}
