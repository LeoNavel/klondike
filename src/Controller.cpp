
#include "Controller.hpp"

Controller::Controller(Deck *deck, GenericView *view) {
    this->deck = deck;
    this->view = view;
    this->view->setController(this);
    this->command = new Command(deck);

    CardStacks::RemainingPack *rp = deck->get_ptr_2_rem_pack();
    qDebug() << "blaha";
    for(int i = 0; i < 22; i++)
        get_next();
    view->update(rp);


}

void Controller::move_card(cmd_t cmd) {
    command->move_card(cmd);
    // todo update
}

void Controller::turn_card(int id_stack) {
    command->turn_card(id_stack);
    // todo update
}

/**
 * Show next card in remaining pack.
 */
void Controller::get_next() {
    qDebug() << "Getting next card...";
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
    qDebug() << "Rolling rem pack";
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
