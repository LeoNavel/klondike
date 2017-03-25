#include <cstdlib>
#include <iostream>
#include "CardStacks.hpp"
#include "Card.hpp"


int main(){

    Card::card_t my_card;
    my_card.card_sign = Card::HEART;
    CardStacks::TargetPack my_generic_stack;

    for (int i = 1; i < 17; i++){
        my_card.number = i;
        my_generic_stack.push(my_card);
    }
    my_generic_stack.printContent();

    std::cout << my_generic_stack.size();
    while (!my_generic_stack.isEmpty()) my_generic_stack.pop();
    std::cout << my_generic_stack.size();
    my_generic_stack.printContent();


    return EXIT_SUCCESS;
}