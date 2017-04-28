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

    deck->targetPacks[0]->pop();

    deck->save("jj.conf");

    //creating cards and push them onstack to test move()
    card::Card card3 = card::Card(3, card::DIAMONDS, true);
    card::Card card4 = card::Card(4, card::CLUBS, true);
    card::Card card5 = card::Card(5, card::DIAMONDS, true);

    deck->workingPacks[0]->force_push(card5);
    deck->workingPacks[1]->force_push(card4);
    deck->workingPacks[1]->force_push(card3);

    stack_id_t w0, w1;
    w0.type_stack = WORKING_STACK;
    w0.id_stack = 0;
    w1.type_stack = WORKING_STACK;
    w1.id_stack = 1;

    std::cout << "before" << std::endl;
    std::cout << "w0" << std::endl;
    deck->workingPacks[0]->printContent();
    std::cout << "w1" << std::endl;
    deck->workingPacks[1]->printContent();

    deck->move_from_to(w1, w0,2);



    std::cout << "after" << std::endl;
    std::cout << "w0" << std::endl;
    deck->workingPacks[0]->printContent();
    std::cout << "w1" << std::endl;
    deck->workingPacks[1]->printContent();

    delete cmd;
    delete deck;
    return EXIT_SUCCESS;
}