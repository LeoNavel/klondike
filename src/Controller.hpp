/*! 
 *  \file       Controller.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Deck.hpp"
#include "View.hpp"
#include "Command.hpp"
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

    /**
     * update all view
     */
    void updateAll();

    /**
     * save gard state to file
     *
     * @param output_file file name
     */
    void save(std::string output_file);

    /**
     * load game
     *
     * @param input_file file with game
     */
    void load(std::string input_file);

    /**
     * find next move
     */
    void findHelp();

    /**
     * finish game when game is won
     */
    void finishGame();

    /**
     * restart game
     */
    void restartGame();

    ~Controller();
};

#endif //CONTROLLER_H
