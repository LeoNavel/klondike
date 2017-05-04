/*! 
 *  \file       Command.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "Deck.hpp"
#include "Command.hpp"
#include "Error.hpp"

Command::Command(Deck *deck) {
    this->deck = deck;
}

void Command::turn_card(int id_stack) {
    inner_cmd_t inner_cmd;
    inner_cmd.type = CMD_TYPE_TURN;
    inner_cmd.command.destination_stack.type_stack = WORKING_STACK;
    inner_cmd.command.destination_stack.id_stack = id_stack;

    try {
        deck->turn_card(id_stack);
    }
    catch (ErrorException *error){
        throw error;
    }
    previous_commands.push_back(inner_cmd);
}

void Command::get_next() {
    inner_cmd_t inner_cmd;
    inner_cmd.type = CMD_TYPE_NEXT;
    try {
        deck->get_next_remmaining_card();
    }
    catch (ErrorException *error){
        throw error;
    }
    previous_commands.push_back(inner_cmd);
}

void Command::roll_rem_pack() {
    inner_cmd_t inner_cmd;
    inner_cmd.type = CMD_TYPE_ROLL;
    try{
        deck->roll_rem_pack();
    }
    catch (ErrorException *error){
        throw error;
    }
    previous_commands.push_back(inner_cmd);
}

void Command::move_card(cmd_t command) {
    inner_cmd_t inner_cmd;
    inner_cmd.type = CMD_TYPE_MOVE;
    inner_cmd.command = command;

    try {
        deck->move_from_to(command.source_stack, command.destination_stack, command.num_of_cards);
    }
    catch (ErrorException *error){
        throw error;
    }
    previous_commands.push_back(inner_cmd);
}

void Command::undo_command() {
    if(previous_commands.size() == 0)
        return;
    inner_cmd_t last_cmd;
    last_cmd = previous_commands.back();
    previous_commands.pop_back();

    switch (last_cmd.type){
        case CMD_TYPE_MOVE:
            deck->force_move_from_to(
                    last_cmd.command.destination_stack,
                    last_cmd.command.source_stack,
                    last_cmd.command.num_of_cards
            );
            break;
        case CMD_TYPE_TURN:
            deck->force_turn_card(last_cmd.command.destination_stack.id_stack);
            break;
        case CMD_TYPE_ROLL:
            deck->roll_back_rem_pack();
            break;
        case CMD_TYPE_NEXT:
            deck->get_previous_remaining_card();
            break;
        default:
            throw ErrorException(E_UNKNOWN_COMMAND,"Unknown command");
    }
}
