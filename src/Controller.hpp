#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Deck.hpp"
#include "View.hpp"
#include "Command.hpp"
#include "QDebug"
#include "Error.hpp"

class Controller {
private:
    Deck *deck;
    Command *command;
    GenericView *view;

public:

    Controller(Deck *deck, GenericView *view);
    /**
     * Move 'num_of_cards' number of cards from 'source_stack' to 'destination_stack'
     * specified in command.
     * @param command
     */
    void move_card(cmd_t cmd);

    /**
     * Make card visible on working pack with id 'id_stack'.
     * Counting from 0.
     * @param id_stack
     */
    void turn_card(int id_stack);

    /**
     * Show next card in remaining pack.
     */
    void get_next();

    /**
     * If remaining pack is o the end, you can turn pack tiwh this function and go to
     * begining of pack.
     */
    void roll_rem_pack();

    /**
     * Revert previous commands.
     */
    void undo_command();

    void updateAll();

    void save(std::string output_file);

    void load(std::string input_file);

    void findHelp();

    ~Controller();

};

#endif //CONTROLLER_H
