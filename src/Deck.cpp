/*! 
 *  \file       Deck.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "Error.hpp"
#include "Deck.hpp"
#include "Command.hpp"
#include <iostream>
#include <fstream>

using namespace CardStacks;

void Deck::prepareDeck(unsigned char shuffles) {
    CardDeck card_deck = CardDeck();

    for(int i = 0; i < shuffles; i++)
        card_deck.shuffleCards();

    for(int i = 0; i < 7; i++) {
        for (int j = 0; j < i; j++)
            workingPacks[i]->force_push(card_deck.topAndPop());

        workingPacks[i]->force_push(card_deck.topAndPop());
        workingPacks[i]->turn_invisible();
    }

    while (!card_deck.isEmpty()) remaining_pack->force_push(card_deck.topAndPop());
}

Deck::Deck() {
    init();
}

Deck::Deck(std::string input_file) {
    init();
    this->load(input_file);
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
    // GenericCardStack *src_stack, *dst_stack;

    int id_last;

    switch (src.type_stack){
        case TARGET_STACK:
            id_last = targetPacks[src.id_stack]->size() - 1;
            for (unsigned int i = 0; i < num_of_cards; i++){
                tmp_stack.push(targetPacks[src.id_stack]->operator[](id_last - i));
            }
            break;

        case WORKING_STACK:
            id_last = workingPacks[src.id_stack]->size() - 1;
            for (unsigned i = 0; i < num_of_cards; i++){
                tmp_stack.push(workingPacks[src.id_stack]->operator[](id_last - i));
            }

            break;
        case REMAINING_STACK:
            if (num_of_cards > 1) throw ErrorException(E_OUT_OF_RANGE, "Too many cards in move from REMAINING_STACK");
            card::Card c = remaining_pack->currentCard();
            c.turnUp();
            tmp_stack.push(c);
            break;


    }

    unsigned int already_pushed = 0;

    try {
        for (already_pushed = 0; already_pushed < num_of_cards; already_pushed++){
            switch (dst.type_stack){
                case WORKING_STACK:
                    workingPacks[dst.id_stack]->push(tmp_stack.topAndPop());
                    break;
                case REMAINING_STACK:
                    remaining_pack->push(tmp_stack.topAndPop());
                    break;
                case TARGET_STACK:
                    targetPacks[dst.id_stack]->push(tmp_stack.topAndPop());
                    break;
            }
        }
    }
    catch (ErrorException * error){
        for (unsigned i = 0 ; i <already_pushed; i++){
            switch (dst.type_stack){
                case WORKING_STACK:
                    workingPacks[dst.id_stack]->pop();
                    break;
                case REMAINING_STACK:
                    remaining_pack->pop();
                    break;
                case TARGET_STACK:
                    targetPacks[dst.id_stack]->pop();
                    break;
            }
        }
        throw error;
    }

    for (unsigned i = 0; i < num_of_cards; i++) {
        switch (src.type_stack) {
            case WORKING_STACK:
                workingPacks[src.id_stack]->pop();
                break;
            case REMAINING_STACK:
                remaining_pack->popCurrent();
                break;
            case TARGET_STACK:
                targetPacks[src.id_stack]->pop();
                break;
        }
    }
}

CardStacks::RemainingPack *Deck::get_ptr_2_rem_pack() {
    return remaining_pack;
}

card::Card Deck::get_top_card_from_target_pack(int id_pack) {
    return targetPacks[id_pack]->top();
}

CardStacks::GenericCardStack Deck::get_pack(stack_id_t stack) {
    GenericCardStack gen_stack = GenericCardStack();
    GenericCardStack *src_pack;
    switch (stack.type_stack) {
        case WORKING_STACK:
            src_pack = workingPacks[stack.id_stack];
            break;

        case TARGET_STACK:
            src_pack = targetPacks[stack.id_stack];
            break;

        case REMAINING_STACK:
            src_pack = remaining_pack;
            break;

        default:
            throw ErrorException(E_UNKNOWN_STACK_TYPE, "Unknown stack type in <CardStacks::GenericCardStack Deck::get_pack(stack_id_t stack)>");
            break;
    }

    for (unsigned int i = 0 ; i < src_pack->size(); i++) gen_stack.push((*src_pack)[i]);

    return gen_stack;
}

void Deck::init() {
    for (int i = 0; i < 7; ++i) {
        workingPacks.push_back(new CardStacks::WorkingPack());
    }

    for (int j = 0; j < 4; ++j) {
        targetPacks.push_back(new CardStacks::TargetPack());
    }

    remaining_pack = new RemainingPack();
}

void Deck::save(std::string output_file) {
    std::ofstream out_file;
    out_file.open(output_file);

    for (int i = 0 ; i < 7; i++){
        out_file << workingPacks[i]->size() << std::endl;
        for (int j = 0 ; j < static_cast<int>(workingPacks[i]->size()); j++){
            out_file << std::to_string(workingPacks[i]->operator[](j).get_number()) + " ";
            out_file << std::to_string(workingPacks[i]->operator[](j).get_sign()) + " ";
            out_file << std::to_string(workingPacks[i]->operator[](j).get_visibility());
            out_file << std::endl;
        }
    }

    for (int i = 0 ; i < 4; i++){
        out_file << targetPacks[i]->size() << std::endl;
        for (int j = 0 ; j < static_cast<int>(targetPacks[i]->size()); j++){
            out_file << std::to_string(targetPacks[i]->operator[](j).get_number()) + " ";
            out_file << std::to_string(targetPacks[i]->operator[](j).get_sign()) + " ";
            out_file << std::to_string(targetPacks[i]->operator[](j).get_visibility());
            out_file << std::endl;
        }
    }

    out_file << remaining_pack->size() << std::endl;
    for (int j = 0 ; j < static_cast<int>(remaining_pack->size()); j++){
        out_file << std::to_string(remaining_pack->operator[](j).get_number()) + " ";
        out_file << std::to_string(remaining_pack->operator[](j).get_sign()) + " ";
        out_file << std::to_string(remaining_pack->operator[](j).get_visibility());
        out_file << std::endl;
    }
    out_file << std::to_string(remaining_pack->get_current_id()) << std::endl;

    out_file.close();
}

void Deck::load(std::string input_file) {
    std::ifstream input_file_stream;
    input_file_stream.open(input_file);
    int num_of_cards, card_sign, card_num, card_vis, ptr_id;

    for (int i = 0 ; i < 7 ; i++){

        input_file_stream >> num_of_cards;
        for (int j = 0 ; j < num_of_cards ; j++) {
            input_file_stream >> card_num >> card_sign >> card_vis;
            workingPacks[i]->force_push(card::Card(card_num, static_cast<card::sign>(card_sign), card_vis));
        }
    }


    for (int i = 0 ; i < 4 ; i++){

        input_file_stream >> num_of_cards;
        for (int j = 0 ; j < num_of_cards ; j++) {
            input_file_stream >> card_num >> card_sign >> card_vis;
            targetPacks[i]->force_push(card::Card(card_num, static_cast<card::sign>(card_sign), card_vis));
        }
    }

    input_file_stream >> num_of_cards;
    for (int j = 0 ; j < num_of_cards ; j++) {
        input_file_stream >> card_num >> card_sign >> card_vis;
        remaining_pack->force_push(card::Card(card_num, static_cast<card::sign>(card_sign), card_vis));
    }

    input_file_stream >> ptr_id;
    remaining_pack->set_current_id(ptr_id);

    input_file_stream.close();
}

void Deck::force_move_from_to(stack_id_t src, stack_id_t dst, int num_of_cards) {
    CardStacks::GenericCardStack *src_pack, *dst_pack;

    switch (src.type_stack) {
        case WORKING_STACK:
            src_pack = workingPacks[src.id_stack];
            break;

        case REMAINING_STACK:
            src_pack = remaining_pack;
            break;

        case TARGET_STACK:
            src_pack = targetPacks[src.id_stack];
            break;

        default:
            throw ErrorException(E_UNKNOWN_STACK_TYPE, "error in <force_move_from_to>");
            break;
    }

    switch (dst.type_stack) {
        case WORKING_STACK:
            dst_pack = workingPacks[dst.id_stack];
            break;

        case REMAINING_STACK:
            break;

        case TARGET_STACK:
            dst_pack = targetPacks[dst.id_stack];
            break;

        default:
            throw ErrorException(E_UNKNOWN_STACK_TYPE, "error in <force_move_from_to>");
            break;
    }

    if (dst.type_stack == REMAINING_STACK){
        remaining_pack->pushCurrent(src_pack->topAndPop());
    }
    else {
        CardStacks::GenericCardStack gcs = CardStacks::GenericCardStack();
        for (int i = 0; i < num_of_cards; i++) {
            gcs.push(src_pack->topAndPop());
        }
        while(!gcs.isEmpty())
            dst_pack->force_push(gcs.topAndPop());
    }
}

cmd_t Deck::get_help_command() {
    cmd_t found_command;

    card::Card src_card, dst_card;

    //checking if -> from rem to target pack
    if (!remaining_pack->isEmpty()) {
        src_card = remaining_pack->currentCard();
        for (int i = 0; i < 4; i++) {
            if (!targetPacks[i]->isEmpty()) {
                dst_card = targetPacks[i]->top();
                if (src_card.get_sign() == dst_card.get_sign() && src_card.get_number() == dst_card.get_number() + 1) {
                    found_command.source_stack.type_stack = REMAINING_STACK;
                    found_command.destination_stack.type_stack = TARGET_STACK;
                    found_command.destination_stack.id_stack = i;
                    found_command.num_of_cards = 1;

                    return found_command;
                }
            } else {
                if (src_card.get_number() == 1) {
                    found_command.source_stack.type_stack = REMAINING_STACK;
                    found_command.destination_stack.type_stack = TARGET_STACK;
                    found_command.destination_stack.id_stack = i;
                    found_command.num_of_cards = 1;
                    return found_command;
                }
            }
        }
    }

    //checking -> rem to working
    for (int i = 0 ; i < 7 ; i++){
        if (!workingPacks[i]->isEmpty()){
            dst_card = workingPacks[i]->top();
            if (!dst_card.isTurnedUp()){
                continue;
            }
            if (src_card.get_color() != dst_card.get_color() and src_card.get_number() == dst_card.get_number() - 1){
                found_command.source_stack.type_stack = REMAINING_STACK;
                found_command.destination_stack.type_stack = WORKING_STACK;
                found_command.destination_stack.id_stack = i;
                found_command.num_of_cards = 1;

                return found_command;
            }
        } else if(src_card.get_number() == 13){
            found_command.source_stack.type_stack = REMAINING_STACK;
            found_command.destination_stack.type_stack = WORKING_STACK;
            found_command.destination_stack.id_stack = i;
            found_command.num_of_cards = 1;

            return found_command;
        }
    }


    // working pack -> target pack
    for (int i = 0 ; i < 7 ; i++){
        if (!workingPacks[i]->isEmpty()) {
            src_card = workingPacks[i]->top();
            for (int j = 0; j < 4; j++) {
                if (!targetPacks[j]->isEmpty()) {
                    dst_card = targetPacks[j]->top();
                    if (src_card.get_sign() == dst_card.get_sign() and
                        src_card.get_number() == dst_card.get_number() + 1) {
                        found_command.source_stack.id_stack = i;
                        found_command.source_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.type_stack = TARGET_STACK;
                        found_command.destination_stack.id_stack = j;
                        found_command.num_of_cards = 1;

                        return found_command;
                    }
                } else {
                    if (src_card.get_number() == card::ACE) {
                        found_command.source_stack.id_stack = i;
                        found_command.source_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.type_stack = TARGET_STACK;
                        found_command.destination_stack.id_stack = j;
                        found_command.num_of_cards = 1;

                        return found_command;
                    }
                }
            }
        }

    }




    // checking working -> working
    for (int i = 0 ; i < 7 ; i++){
        long size_of_pack = workingPacks[i]->size();
        for (long j = size_of_pack -1; j >= 0; j--) {
            src_card = (*workingPacks[i])[j];
            if (!src_card.isTurnedUp()){
                break;
            }

            for (int k = 0 ; k < 7 ; k++){
                if (k == i) continue;
                WorkingPack *wp = workingPacks[k];
                if(wp->isEmpty()){
                    if(src_card.get_number() == 13){
                        found_command.source_stack.id_stack = i;
                        found_command.source_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.id_stack = k;
                        found_command.num_of_cards = static_cast<int>(size_of_pack - j);
                        return found_command;
                    }
                } else {
                    dst_card = workingPacks[k]->top();
                    if (!dst_card.isTurnedUp()){
                        continue;
                    }

                    if (src_card.get_color() != dst_card.get_color() and src_card.get_number() == dst_card.get_number() - 1){
                        found_command.source_stack.id_stack = i;
                        found_command.source_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.type_stack = WORKING_STACK;
                        found_command.destination_stack.id_stack = k;
                        found_command.num_of_cards = static_cast<int>(size_of_pack - j);

                        return found_command;
                    }
                }
            }
        }
    }

    // if no help was found excpetion is raised
    throw ErrorException(E_NO_MORE_MOVE, "<get_help_command> didn't find any possible command");
}

bool Deck::is_win() {
    card::Card top_card;

    for (int i = 0 ; i < 4; i++){
        if (!targetPacks[i]->isEmpty()) {
            top_card = targetPacks[i]->top();
            if (top_card.get_number() != card::KING) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return true;
}
