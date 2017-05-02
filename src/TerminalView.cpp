#include "TerminalView.hpp"
#include "Controller.hpp"

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
            std::cout << "addd";
        }
        else if (command == "undo"){
            controller->undo_command();
        }
        else if (command == "turn"){
            controller->roll_rem_pack();
        }
        else if (command == "save"){
            controller->save(rest.substr(0,rest.find(' ')));
        }
        else if (command == "load") {
            controller->load(rest.substr(0, rest.find(' ')));
        }



        getline(std::cin, user_input);
    }

    return 0;
}
