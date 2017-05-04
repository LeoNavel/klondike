/*! 
 *  \file       Command.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "struct_definitions.hpp"
#include "Deck.hpp"

#define CMD_TYPE_MOVE   0
#define CMD_TYPE_TURN   1
#define CMD_TYPE_NEXT   2
#define CMD_TYPE_ROLL   3


typedef struct {
    int type;
    cmd_t command;
} inner_cmd_t;

class Command {
private:
    Deck *deck;
    std::vector<inner_cmd_t> previous_commands;


public:
    Command(Deck *deck);

     /**
     * Move 'num_of_cards' number of cards from 'source_stack' to 'destination_stack'
     * specified in command.
     * @param command
      */
    void move_card(cmd_t command);

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

};

#endif //COMMAND_H