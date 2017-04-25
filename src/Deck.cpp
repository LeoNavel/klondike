
#include "Deck.hpp"

using namespace CardStacks;

void Deck::prepareDeck(unsigned char shuffles) {
    CardDeck card_deck = CardDeck();

    for(int i = 0; i < shuffles; i++)
        card_deck.shuffleCards();

    for(int i = 0; i < 7; i++) {
        for (int j = 0; j < i; j++)
            workingPacks[i]->push_invisible(card_deck.topAndPop());

        workingPacks[i]->push_invisible(card_deck.topAndPop());
        workingPacks[i]->turn_invisible();
    }

    while (!card_deck.isEmpty()) remaining_pack->push(card_deck.topAndPop());
}

Deck::Deck() {
    for (int i = 0; i < 7; ++i) {
        workingPacks.push_back(new CardStacks::WorkingPack());
    }

    for (int j = 0; j < 4; ++j) {
        targetPacks.push_back(new CardStacks::TargetPack());
    }

    remaining_pack = new RemainingPack();
}

Deck::~Deck() {
    delete remaining_pack;

    for (int i = workingPacks.size() - 1; i >= 0; i--){
        delete workingPacks[i];
        workingPacks.pop_back();
    }

    for (int  i = targetPacks.size() -1; i >= 0; i--){
        delete targetPacks[i];
        targetPacks.pop_back();
    }

}
