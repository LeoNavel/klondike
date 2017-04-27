
#include "Controller.hpp"

Controller::Controller(Deck *deck, GenericView *view) {
    this->deck = deck;
    this->view = view;
    this->view->setController(this);
    this->command = new Command(deck);

    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();

    rp->push(card::Card(1, card::sign::HEART));
    for(int i = 0; i < 25; i++)
        get_next();
    view->update(rp);


}

void Controller::move_card(cmd_t cmd) {
    qDebug() << "Moving with cards";
    try{
        command->move_card(cmd);
    } catch(ErrorException e){
        qDebug() << e.get_message().c_str();
    }
    switch(cmd.source_stack.type_stack){
    case REMAINING_STACK:
        break;
    case TARGET_STACK:
        break;
    default:
        CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();
        view->update(rp);
        break;
    }

    switch (cmd.destination_stack.type_stack) {
    case REMAINING_STACK:

        break;
    case TARGET_STACK:

        break;
    default:
        break;
    }
}

void Controller::turn_card(int id_stack) {
    command->turn_card(id_stack);
    // todo update
}

/**
 * Show next card in remaining pack.
 */
void Controller::get_next() {
    try{
        command->get_next();
    } catch(ErrorException e){
        qDebug() << e.get_message().c_str();
    }
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
    }  catch(ErrorException e){
        qDebug() << e.get_message().c_str();
    }
    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();
    view->update(rp);
}

/**
 * Revert previous commands.
 */
void Controller::undo_command() {
    command->undo_command();
    // todo update
}


void Controller::save(std::string output_file){
}

void Controller::load(std::string input_file){
    // todo update
}

Controller::~Controller(){
    delete command;
}
