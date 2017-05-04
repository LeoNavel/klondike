/*! 
 *  \file       test_card_stack.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include <cstdlib>
#include <iostream>
#include "CardStacks.hpp"
#include "Error.hpp"

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

    try{

        CardStacks::GenericCardStack generic_stack;
        card::Card new_card(1, card::HEART);

        if (!generic_stack.isEmpty()) throw "ma byt prazdny a nie je";
        generic_stack.push(new_card);
        if (generic_stack.isEmpty()) throw "ma byt prazdny a nie je";
        generic_stack.push(new_card);
        if (generic_stack.size() != 2 ) throw "zla velksot stacku";

        if (generic_stack.top() != new_card) throw "rozdielne karty";
        generic_stack.pop();
        if (generic_stack.size() != 1 ) throw "zla velksot stacku";

        std::cout << "Generic stack success" << std::endl;


        CardStacks::TargetPack target_pack_stack;
        if(!target_pack_stack.isEmpty()) throw "nie je pradzny";
        new_card.set_number(card::ACE);
        target_pack_stack.push(new_card);
        try {
            target_pack_stack.push(new_card);
            throw ErrorException(-4,"sadf");
        }
        catch (ErrorException error){
            if (error.get_err_code() == -4) throw "no error detect";
        }

        try { // right number but wrong color
            new_card.set_number(2);
            new_card.set_sign(card::SPADES);
            target_pack_stack.push(new_card);
            throw ErrorException(-4,"sadf");
        }
        catch (ErrorException error){
            if (error.get_err_code() == -4) throw "no error detect";
        }

        //corect push
        new_card.set_sign(card::HEART);
        target_pack_stack.push(new_card);
        target_pack_stack.pop();
        if(target_pack_stack.top() != card::Card(card::ACE, card::HEART)) throw "Wrong card on top";
        target_pack_stack.pop();

        std::cout << "target pack test OK" << std::endl;

        //working pack tests
        CardStacks::WorkingPack working_pack;
        CardStacks::CardDeck deck;
        deck.shuffleCards();
        for (int i = 0 ; i < 5 ; i++) working_pack.push_invisible(deck.topAndPop());
        //pushing correct order of cards
        card::Card card1(5, card::HEART);
        card::Card card2(4, card::SPADES);
        card::Card card3(3, card::DIAMONDS);

        working_pack.push_invisible(card1);
        working_pack.push_invisible(card1);
        working_pack.push_invisible(card1);
        working_pack.turn_invisible();
        card2.turnUp();
        working_pack.push(card2);
        card3.turnUp();
        working_pack.push(card3);

        //pushing picovinas
        try{
            card::Card card4(2, card::DIAMONDS);
            working_pack.push(card4);
            throw ErrorException(-4, "No error found");
        }
        catch (ErrorException error){
            if (error.get_err_code() == -4) throw error.get_message().c_str();
        }

        std::cout << "working pack test correct" << std::endl;

        CardStacks::RemainingPack rem_pack = CardStacks::RemainingPack();
        for (int i = 0; i < 10; i++) rem_pack.push(deck.topAndPop());

        if (rem_pack.isSetCurrent()) throw "Card is set";
        rem_pack.nextCard();
        if (!rem_pack.isSetCurrent()) throw "Card is not set";

        for (int i = 0 ; i < 20 ; i++) rem_pack.nextCard();
        if(!rem_pack.allCardVisible()) throw "All cards wasnt seen";

        rem_pack.turnPack();

        if (rem_pack.isSetCurrent()) throw "Card is set";
        rem_pack.nextCard();
        if (!rem_pack.isSetCurrent()) throw "Card is not set";




        std::cout << "Remaining pack tets OK" << std::endl;
    }
    catch (const char* error){
        std::cerr << error << std::endl;
        exit(1);
    }


    return EXIT_SUCCESS;
}