#include "Deck.hpp"


int main(){

    Deck deck = Deck();

    deck.prepareDeck(6);

    for (auto &&workingPack :deck.workingPacks) {
        workingPack->print();
    }

    return EXIT_SUCCESS;
}