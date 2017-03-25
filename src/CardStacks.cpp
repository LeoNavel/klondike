/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb??,xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         Stack definitions
 *
 ***************************************/
#include <iostream>
#include "CardStacks.hpp"
#include "Card.hpp"

namespace CardStacks {

    void GenericCardStack::push(Card::card_t card){
        this->card_stack.push_back(card);
    }

    void GenericCardStack::pop() {
        if (!this->isEmpty()) {
            this->card_stack.pop_back();
        }
    }

    bool GenericCardStack::isEmpty() {
        return !static_cast<bool>(this->card_stack.size());
    }

    unsigned long GenericCardStack::size() {
        return card_stack.size();
    }

    void GenericCardStack::printContent() {
        for (auto &i:card_stack){
            std::cout << "Card-color:" << i.card_sign << "  Number:" << i.number << std::endl;
        }
    }

    Card::card_t GenericCardStack::top() {
        if (!isEmpty()){
            return this->card_stack[size()-1];
        }
        else {
            throw "Stack: is empty";
        }
    }


    void TargetPack::push(Card::card_t card) {
        if (isEmpty()){
            GenericCardStack::push(card);
        }
        else {
            Card::card_t card_on_top = top();
            if (card_on_top.card_sign == card.card_sign && card_on_top.number == card.number -1){
                GenericCardStack::push(card);
            }
            else {
                throw; // TODO : talk about this with FITO
            }
        }
    }


    void WorkingPack::push(Card::card_t card) {
        if (visible_cards.isEmpty() && invisible_cards.isEmpty()){
            if (card.number == Card::KING){
                visible_cards.push(card);
            }
            else throw;
        }
        else {
            Card::card_t top_card = visible_cards.top();
            if (Card::get_card_color(top_card) != Card::get_card_color(card) &&
                    card.number < top_card.number){
                visible_cards.push(card);
            } else throw;
        }
    }

    void WorkingPack::pop() {
        if(!visible_cards.isEmpty()){
            visible_cards.pop();
        }
    }

    void WorkingPack::pop_invisivle() {
        if (!invisible_cards.isEmpty()){
            invisible_cards.pop();
        }
    }

    Card::card_t WorkingPack::top_visivle() {
        return visible_cards.top();
    }

    Card::card_t WorkingPack::top_invisivle() {
        return invisible_cards.top();
    }


}
