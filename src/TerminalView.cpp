#include "TerminalView.hpp"
#include "Controller.hpp"
#include "Command.hpp"
#include "Deck.hpp"

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

    std::string user_input;
    std::string command , from , to, rest;


    getline(std::cin, user_input);
    while (user_input != "quit"){
        //parsing first word
        command = user_input.substr(0,user_input.find(' '));
        if (user_input.length() > 5) {
            rest = user_input.substr(user_input.find(' ')+1);
        }
        if (command == "next"){
            controller->get_next();
        }
        else if (command == "move"){
            from = rest.substr(0, rest.find(' '));
            rest = rest.substr(rest.find(' ') +1);
            to = rest.substr(0, rest.find(' '));
            rest = rest.substr(rest.find(' ') +1);

            cmd_t cmd;

            if (from[0] == 'r') {
                cmd.source_stack.type_stack = REMAINING_STACK;
            }
            else if (from[0] == 'w'){
                cmd.source_stack.type_stack = WORKING_STACK;
                cmd.source_stack.id_stack = atoi(&from[1]);
            }

            if (to[0] == 't'){
                cmd.destination_stack.type_stack = TARGET_STACK;
                cmd.destination_stack.id_stack = atoi(&to[1]);
            }
            else if (to[0] == 'w'){
                cmd.destination_stack.type_stack = WORKING_STACK;
                cmd.destination_stack.id_stack = atoi(&to[1]);
            }

            if (rest == to){
                cmd.num_of_cards = 1 ;
            }
            else {
                cmd.num_of_cards = atoi(rest.c_str());
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
                controller->turn_card(atoi(rest.c_str()));
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



        getline(std::cin, user_input);
    }

    return 0;
}
