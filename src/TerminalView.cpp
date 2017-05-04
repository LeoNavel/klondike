/*! 
 *  \file       TerminalView.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include <unistd.h>
#include "TerminalView.hpp"
#include "Controller.hpp"
#include "Command.hpp"
#include "Deck.hpp"
#include "struct_definitions.hpp"


TerminalView::TerminalView() {
    canvas = TerminalCanvas();
}

void TerminalView::refresh() {
    canvas.print();
}

void TerminalView::update(int id, card::Card *topTargetCard) {
    canvas.update(id, topTargetCard);
    refresh();
}

void TerminalView::update(int id, CardStacks::GenericCardStack workingPack) {
    canvas.update(id, workingPack);
    refresh();
}

void TerminalView::update(CardStacks::RemainingPack *remainigPack) {
    canvas.update(remainigPack);
    refresh();
}

void TerminalView::highlightNextCardCommand() {
    GenericView::highlightNextCardCommand();
}

void TerminalView::highlightRemainingToWorking(unsigned int id) {
    GenericView::highlightRemainingToWorking(id);
}

void TerminalView::highlightRemainingToTarget(unsigned int id) {
    GenericView::highlightRemainingToTarget(id);
}

void TerminalView::highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID){

}


void TerminalView::highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID){

}

int TerminalView::run() {

    std::string user_input = "";
    std::string command , from , to, rest;


    help();
    while (user_input != "quit"){
        getline(std::cin, user_input);
        //parsing first word
        command = user_input.substr(0,user_input.find(' '));
        if (user_input.length() > 5) {
            rest = user_input.substr(user_input.find(' ')+1);
        }
        if (command == "next"){
            controller->get_next();
        }
        else if (command == "move"){
            cmd_t cmd;

            try {
                from = rest.substr(0, rest.find(' '));
                rest = rest.substr(rest.find(' ') + 1);
                to = rest.substr(0, rest.find(' '));
                rest = rest.substr(rest.find(' ') + 1);

                if (
                    from.length() < 1 or
                    to.length() < 2 or
                    from == to
                        ){
                    continue;
                }

                if (from[0] == 'r') {
                    cmd.source_stack.type_stack = REMAINING_STACK;
                } else if (from[0] == 'w') {
                    cmd.source_stack.type_stack = WORKING_STACK;
                    if (from.length() == 2) {
                        cmd.source_stack.id_stack = std::stoi(&from[1]) - 1;
                    }
                    else {
                        continue;
                    }
                }

                if (to[0] == 't') {
                    cmd.destination_stack.type_stack = TARGET_STACK;
                    cmd.destination_stack.id_stack = std::stoi(&to[1]) -1;
                } else if (to[0] == 'w') {
                    cmd.destination_stack.type_stack = WORKING_STACK;
                    cmd.destination_stack.id_stack = std::stoi(&to[1]) -1;
                }

                if (rest == to) {
                    cmd.num_of_cards = 1;
                } else {
                    cmd.num_of_cards = std::stoi(rest.c_str()) - 1;
                }

                if (
                    cmd.source_stack.id_stack < 0 or
                    cmd.source_stack.id_stack >= 7 or
                    cmd.destination_stack.id_stack < 0 or
                    cmd.destination_stack.id_stack >= 7
                        ){
                    continue;
                }

            }
            catch (void *){
                continue;
            }

            controller->move_card(cmd);
        }
        else if (command == "undo"){
            controller->undo_command();
        }
        else if (command == "turn"){
            if (!rest.length()){
                std::cout << "what you want to turn card/pack ? >>";
                std::cin >> rest;
            }

            to = rest.substr(0,rest.find(' '));
            rest = rest.substr(rest.find(' ') + 1);
            if (to == "pack"){
                controller->roll_rem_pack();
            }
            else if (to == "card"){
                try {
                    controller->turn_card(std::stoi(rest.c_str()) - 1);
                }
                catch (void *){
                    continue;
                }
            }
            else {
                std::cout << "Unknown object"<< std::endl;
            }

        }
        else if (command == "save"){
            if (rest.length()) {
                controller->save(rest.substr(0, rest.find(' ')));
                refresh();
            }
            else {
                std::cout << "Please specify output file >> ";
                std::cin >> rest;
                if (rest.length()){
                    controller->save(rest.substr(0, rest.find(' ')));
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
        }
        else if (command == "load") {
            if (rest.length()){
                controller->load(rest.substr(0, rest.find(' ')));
                refresh();
            }
            else {
                std::cout << "Please specify input file >> ";
                std::cin >> rest;
                if (rest.length()){
                    controller->load(rest.substr(0, rest.find(' ')));
                }
                else {
                    std::cout << "error" << std::endl;
                }
            }
        }
        else if (command == "hint"){

        }


        help();
    }

    return 0;
}

void TerminalView::help() {
    std::cout << "This is manual for controling this game." << std::endl;
    std::cout << "\tload <filename> - load game from file" << std::endl;
    std::cout << "\tsave <filename> - save game to file" << std::endl;
    std::cout << "\tquit - exit game" << std::endl;
    std::cout << "\tturn <pack|card <id working pack>> - turn remaining pack to beginning or turn top invisible card" << std::endl;
    std::cout << "\tundo - revert previous commands" << std::endl;
    std::cout << "\tnext - next card in remaining pack" << std::endl;
    std::cout << "\tmove <src> <dst> [number of cards] - move cards from pack \"src\" to pack \"dest\"" << std::endl;
}
