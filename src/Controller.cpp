
#include "Controller.hpp"


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
    command->get_next();
    // todo update
}

/**
 * If remaining pack is o the end, you can turn pack tiwh this function and go to
 * begining of pack.
 */
void Controller::roll_rem_pack() {
    command->roll_rem_pack();
    // todo update
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

