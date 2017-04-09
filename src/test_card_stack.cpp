#include <cstdlib>
#include <iostream>
#include "CardStacks.hpp"


int main(){
/*
    card::Card my_card(1, card::HEART);
    CardStacks::TargetPack my_generic_stack;

    for (int i = 1; i < 17; i++){
        my_card.set_number(i);
        my_generic_stack.push(my_card);
    }
    my_generic_stack.printContent();

    std::cout << my_generic_stack.size();
    while (!my_generic_stack.isEmpty()) my_generic_stack.pop();
    std::cout << my_generic_stack.size();
    my_generic_stack.printContent();

    std::cout << std::endl << std::endl;

    CardStacks::CardDeck deck;

    deck.printContent();
    deck.shuffleCards();
    std::cout << std::endl << std::endl;
    deck.printContent();
    std::cout << std::endl << std::endl;

    for (int i = 0 ; i < 50 ; i++) deck.topAndPop();
    deck.printContent();
*/

    //test generic card tack

    CardStacks::GenericCardStack generic_stack;

    try{

    }
    catch (const char* error){
        std::cerr << error << std::endl;
        exit(1);
    }

    return EXIT_SUCCESS;
}