#include "Command.hpp"
#include "Deck.hpp"

using namespace std;

int main(){

    Deck *deck = new Deck();
    Command *cmd = new Command(deck);

    deck->prepareDeck(6);

    for (auto &&workingPack :deck->workingPacks) {
        workingPack->print();
    }

    cout << "Getting and prinitng last working stack" << std::endl;
    stack_id_t last_work_stack_id;
    last_work_stack_id.id_stack = 6;
    last_work_stack_id.type_stack = WORKING_STACK;
    CardStacks::GenericCardStack last_work_cpy = deck->get_pack(last_work_stack_id);
    last_work_cpy.printContent();
    cout << endl;

    cout << "printing remaining packs" << endl;
    deck->remaining_pack->printContent();
    CardStacks::RemainingPack *ptr_rem_pac = deck->get_ptr_2_rem_pack();
    cout << "printing remaining packs from <get_ptr_2_rem_pack>" << endl;
    ptr_rem_pac->printContent();

    deck->targetPacks[0]->push(card::Card(1));

    cout << "get top card of 0 target pack directly"<< endl;
    cout << deck->targetPacks[0]->top().print_card() << endl;
    cout << "get top card of 0 target <get_top_card_from_target_pack()>"<< endl;
    cout << deck->get_top_card_from_target_pack(0).print_card() << endl;
    delete cmd;
    delete deck;
    return EXIT_SUCCESS;
}