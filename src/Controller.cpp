/*! 
 *  \file       Controller.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */

#include "Controller.hpp"

Controller::Controller(Deck *deck, GenericView *view) {
    this->deck = deck;
    this->view = view;
    this->view->setController(this);
    this->command = new Command(deck);

    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();

    this->view->update(rp);
    stack_id_t stackId;
    stackId.type_stack = WORKING_STACK;
    for(int i = 0; i < 7; i++){
        stackId.id_stack = i;
        CardStacks::GenericCardStack gs = deck->get_pack(stackId);
        view->update(stackId.id_stack, gs);
    }
}

void Controller::findHelp(){
    try{
        cmd_t cmd = deck->get_help_command();
        int typeSource = cmd.source_stack.type_stack;
        int typeDest = cmd.destination_stack.type_stack;
        if(typeSource == REMAINING_STACK && typeDest == WORKING_STACK){
            view->highlightRemainingToWorking(cmd.destination_stack.id_stack);
        } else if(typeSource == REMAINING_STACK && typeDest == TARGET_STACK) {
            view->highlightRemainingToTarget(cmd.destination_stack.id_stack);
        } else if(typeSource == WORKING_STACK && typeDest == WORKING_STACK) {
            view->highlightWorkingToWorking(cmd.source_stack.id_stack, cmd.num_of_cards, cmd.destination_stack.id_stack);
        } else if(typeSource == WORKING_STACK && typeDest == TARGET_STACK) {
            view->highlightWorkingToTarget(cmd.source_stack.id_stack, cmd.destination_stack.id_stack);
        }
    }catch(ErrorException e) {

    }
}

void Controller::move_card(cmd_t cmd) {
    try{
        command->move_card(cmd);
    } catch(ErrorException e){}
    CardStacks::RemainingPack *rp;
    card::Card c;
    CardStacks::GenericCardStack wp;

    switch(cmd.source_stack.type_stack){
    case REMAINING_STACK:
        rp = deck->get_ptr_2_rem_pack();
        view->update(rp);
        break;
    case WORKING_STACK:
        wp = deck->get_pack(cmd.source_stack);
        view->update(cmd.source_stack.id_stack, wp);
        break;
    default:
        break;
    }

    switch (cmd.destination_stack.type_stack) {
    case TARGET_STACK:
        try{
            c = deck->get_top_card_from_target_pack(cmd.destination_stack.id_stack);
            view->update(cmd.destination_stack.id_stack, &c);
            if(deck->is_win()){
                view->finishGame();
            }
        } catch(ErrorException e){
            if(e.get_err_code() == E_POP_FROM_EMPTY_STACK){
                view->update(cmd.destination_stack.id_stack, nullptr);
            } else {
                throw e;
            }
        }
        break;
    case WORKING_STACK:
        wp = deck->get_pack(cmd.destination_stack);
        view->update(cmd.destination_stack.id_stack, wp);
        break;
    default:
        break;
    }
}

void Controller::turn_card(int id_stack) {
    command->turn_card(id_stack);
    CardStacks::GenericCardStack wp = deck->get_pack({WORKING_STACK, id_stack});
    view->update(id_stack, wp);
}

/**
 * Show next card in remaining pack.
 */
void Controller::get_next() {
    try{
        command->get_next();
    } catch(ErrorException e){}
    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();
    view->update(rp);


    // todo update
}

/**
 * If remaining pack is o the end, you can turn pack tiwh this function and go to
 * begining of pack.
 */
void Controller::roll_rem_pack() {
    try{
        command->roll_rem_pack();
    }  catch(ErrorException e){}
    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();
    view->update(rp);
}

/**
 * Revert previous commands.
 */
void Controller::undo_command() {
    try{
        command->undo_command();
    }  catch(ErrorException e){}
    updateAll();
}

void Controller::updateAll(){
    CardStacks::RemainingPack * rp;
    card::Card c;
    CardStacks::GenericCardStack wp;

    rp = deck->get_ptr_2_rem_pack();
    view->update(rp);
    for(int i = 0; i < 4; i++){
        try{
            c = deck->get_top_card_from_target_pack(i);
            view->update(i, &c);
        } catch(ErrorException e){
            if(e.get_err_code() == E_POP_FROM_EMPTY_STACK){
                view->update(i, nullptr);
            } else {
                throw e;
            }
        }
    }

    stack_id_t stack_id;
    stack_id.type_stack = WORKING_STACK;
    for(int i = 0; i < 7; i++){
        stack_id.id_stack = i;
        wp = deck->get_pack(stack_id);
        view->update(i, wp);
    }
}


void Controller::save(std::string output_file){
    std::string fn = output_file;
    std::string suffix = ".klondike";
    if(fn.rfind(suffix) != (fn.size()-suffix.size())){
        if(fn.back() == '.'){
            fn += "klondike";
        } else {
            fn += ".klondike";
        }
    }
    deck->save(fn);
}

void Controller::load(std::string input_file){
    Deck * newDeck;
    try{
        newDeck = new Deck(input_file);
        delete deck;
        delete command;
        deck = newDeck;
        command = new Command(newDeck);
    } catch (ErrorException e){
        std::cerr << e.get_message();
    }

    updateAll();
}

void Controller::finishGame() {
    view->finishGame();
}

void Controller::restartGame() {
    delete deck;
    delete command;
    deck = new Deck();
    deck->prepareDeck(13);
    command = new Command(deck);
    view->restartView();
    updateAll();
}

Controller::~Controller(){
    delete deck;
    delete command;
    delete view;
}
