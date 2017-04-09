/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         Stack definitions
 *
 ***************************************/
#include <iostream>
#include <algorithm>
#include "CardStacks.hpp"
#include "Card.hpp"

namespace CardStacks {

    void GenericCardStack::push(card::Card card) {
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
        for (auto &i:card_stack) {
            std::cout << "card-color:" << i.get_sign() << "  Number:" << i.get_number() << std::endl;
        }
    }

    card::Card GenericCardStack::top() {
        if (!isEmpty()) {
            return this->card_stack[size() - 1];
        } else {
            throw "Stack: is empty";
        }
    }


    void TargetPack::push(card::Card card) {
        if (isEmpty()) {
            GenericCardStack::push(card);
        } else {
            card::Card card_on_top = top();
            if (card_on_top.get_sign() == card.get_sign() && card_on_top.get_number() == card.get_number() - 1) {
                GenericCardStack::push(card);
            } else {
                throw ; // TODO : talk about this with FITO
                // TODO creat nice errors
            }
        }
    }


    void WorkingPack::push(card::Card card) {
        if (visible_cards.isEmpty() && invisible_cards.isEmpty()) {
            if (card.get_number() == card::KING) {
                visible_cards.push(card);
            } else throw;
        } else {
            card::Card top_card = visible_cards.top();
            if (card::get_card_color(top_card) != card::get_card_color(card) &&
                card.get_number() < top_card.get_number()) {
                visible_cards.push(card);
            } else throw;
        }
    }

    void WorkingPack::pop() {
        if (!visible_cards.isEmpty()) {
            visible_cards.pop();
        }
    }

    void WorkingPack::popInvisivle() {
        if (!invisible_cards.isEmpty()) {
            invisible_cards.pop();
        }
    }

    card::Card WorkingPack::topVisivle() {
        return visible_cards.top();
    }

    card::Card WorkingPack::topInvisivle() {
        return invisible_cards.top();
    }


    RemainingPack::RemainingPack() {
        current_card = 0;
    }

    CardDeck::CardDeck() {
        card::Card new_card(1, card::SPADES);

        new_card.set_sign(card::SPADES);
        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::HEART);

        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::CLUBS);

        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::DIAMONDS);
        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }
    }

    void CardDeck::shuffleCards() {
        std::random_shuffle(card_stack.begin(), card_stack.end());
    }

    card::Card CardDeck::topAndPop() {
        card::Card poped_card = top();
        pop();
        return poped_card;
    }


}
