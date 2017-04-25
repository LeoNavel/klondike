#include "Error.hpp"
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

void Deck::turn_card(int id_work_pack) {
    if (!(id_work_pack < 7) and (id_work_pack >= 0)) throw ErrorException(E_OUT_OF_RANGE, "id work pack is not in stacks <Deck::turn_card(int id_work_pack)>");
    workingPacks[id_work_pack]->turn_invisible();
}

void Deck::force_turn_card(int id_work_pack) {
    workingPacks[id_work_pack]->turn_back_invisible();
}

void Deck::get_next_remmaining_card() {
    remaining_pack->nextCard();
}

void Deck::get_previous_remaining_card() {
    remaining_pack->prevCard();
}

void Deck::roll_rem_pack() {
    remaining_pack->turnPack();
}

void Deck::roll_back_rem_pack() {
    remaining_pack->turnBack();
}

void Deck::move_from_to(stack_id_t src, stack_id_t dst, unsigned num_of_cards) {
    GenericCardStack tmp_stack = GenericCardStack();

    switch (src.type_stack){
        case TARGET_STACK:

            break;
        case WORKING_STACK:

            break;
        case REMAINING_STACK:
            if (num_of_cards < 2) throw ErrorException(E_OUT_OF_RANGE, "Too many cards in move from TARGET_STACK");
            tmp_stack.push(remaining_pack->currentCard());
            break;


    }


}
