/*! 
 *  \file       CardStacks.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
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
#include <random>
#include "CardStacks.hpp"
#include "Card.hpp"
#include "Error.hpp"

namespace CardStacks {

    /**
     * @brief Put card on top of stack.
     * @param card Play card object.
     */
    void GenericCardStack::push(card::Card card) {
        this->card_stack.push_back(card);
    }

    /**
     * @brief Remove card from top of stack.
     */
    void GenericCardStack::pop() {
        if (!this->isEmpty()) {
            this->card_stack.pop_back();
        }
    }

    /**
     * @brief Remove card from stack and return that object of card.
     * @return Card that is being removed from stack;
     */
    card::Card GenericCardStack::topAndPop() {
        card::Card poped_card = top();
        pop();
        return poped_card;
    }

    /**
     * @brief Check if stack is empty.
     * @return bool value, if stack is empty
     */
    bool GenericCardStack::isEmpty() {
        return !static_cast<bool>(this->card_stack.size());
    }

    /**
     * @brief Get number of cards in stack.
     * @return Number of cards of stack
     */
    unsigned long GenericCardStack::size() {
        return card_stack.size();
    }

    /**
     * @brief Print every card in stack.
     */
    void GenericCardStack::printContent() {
        for (auto &i:card_stack) {
            std::cout << "card-color:" << i.get_sign() << "  Number: " << i.get_number() <<
                      " visible : "<< i.isTurnedUp() << std::endl;
        }
    }

    /**
     * @brief Get card from top of stack.
     * @return card from top of stack
     */
    card::Card GenericCardStack::top() {
        if (!isEmpty()) {
            return this->card_stack[size() - 1];
        } else {
            throw ErrorException(E_POP_FROM_EMPTY_STACK, "Stack: is empty");
        }
    }

    card::Card GenericCardStack::operator[](int i) {
        return card_stack[i];
    }

    void GenericCardStack::force_push(card::Card card) {
        this->card_stack.push_back(card);
    }

    /**
     * @brief Add card to stack, if preconditions are OK
     * @param card Card to add
     * @pre Color of cards are same, top_card = add_card + 1
     */
    void TargetPack::push(card::Card card) {
        if (isEmpty()) {
            if(card.get_number() == card::ACE) {
                GenericCardStack::push(card);
            }
            else throw ErrorException(E_TARGET_PACK_PUSH, "On top might be ACE");
        } else {
            card::Card card_on_top = top();
            if (card_on_top.get_sign() == card.get_sign() &&
                    card_on_top.get_number() == card.get_number() - 1) {
                GenericCardStack::push(card);
            } else {
                throw ErrorException(E_TARGET_PACK_PUSH,"this is wrong push");
            }
        }
    }

    /**
     * @brief Adding new card to visible cards.
     * @param card New card
     * @pre Color_top != Color_new_card and top_card_num = new_card_num + 1
     */
    void WorkingPack::push(card::Card card) {
        if (GenericCardStack::isEmpty()) {
            if (card.get_number() == card::KING) {
                GenericCardStack::push(card);
            } else throw ErrorException(E_WORK_PACK_PUSH, "First card might be king");
        } else {
            int tmp;
            card::Card top_card = GenericCardStack::top();
            if (!GenericCardStack::top().isTurnedUp()){
                throw ErrorException(E_PUSH_ON_INVISIBLE, "You cannot push card on invisible");
            }
            if (card::get_card_color(top_card) != card::get_card_color(card) &&
                    (tmp=(card.get_number() + 1)) == top_card.get_number())
            {
                GenericCardStack::push(card);
            }
            else throw ErrorException(E_WORK_PACK_PUSH, "Color match or numbers of cards are not in order");
        }
    }

    bool WorkingPack::anyVisible() {
        if (card_stack.size() > 0){
            return card_stack[card_stack.size() -1].isTurnedUp();
        }
        return false;
    }

    /**
     * @brief Adding new card to invisible cards.
     * @param card Card
     */
    void WorkingPack::push_invisible(card::Card card) {
        card.turnDown();
        GenericCardStack::push(card);
    }

    /**
     * @brief Removing card from visible cards.
     */
    void WorkingPack::pop() {
        if (GenericCardStack::top().isTurnedUp()){
            return GenericCardStack::pop();
        }
        throw ErrorException(E_POP_INVISIBLE,"Poping invisible <WorkingPack::pop() >");
    }

    /**
     * @brief Remove card from invisible
     * @pre There are no visible cards.
     */
    void WorkingPack::popInvisible() {
        card::Card top_card = GenericCardStack::top();
        if (!top_card.isTurnedUp()){
            GenericCardStack::pop();
        }
        else throw ErrorException(E_WORK_PACK_POP, "popping invisible card over visible");
    }

    /**
     * @brief Get card from visibles.
     * @return Card
     */
    card::Card WorkingPack::topVisible() {
        card::Card top_card = GenericCardStack::top();
        if (top_card.isTurnedUp()){
            return top_card;
        }
        else throw ErrorException(E_NOT_VISIBLE, "There is no visible card");
    }

    /**
     * @rief Get card from invisible stack
     * @return Card
     */
    card::Card WorkingPack::topInvisible() {
        card::Card top_card = GenericCardStack::top();
        if (!top_card.isTurnedUp()){
            return top_card;
        }
        else throw ErrorException(E_NOT_INVISIBLE, "There is no invisible card");    }

    /**
     * @brief Get card from invisible and put it to visible.
     * @pre Visible card stack si empty
     */
    void WorkingPack::turn_invisible() {
        card::Card top_card = this->topAndPop();
        top_card.turnUp();
        GenericCardStack::push(top_card);
    }

    void WorkingPack::print() {
        std::cout << "Working pack : " << std::endl;
        GenericCardStack::printContent();
    }

    void WorkingPack::turn_back_invisible() {
        card::Card top_card = this->top();
        this->pop();
        top_card.turnDown();
        GenericCardStack::push(top_card);
    }

    /**
     * @brief Constructor
     */
    RemainingPack::RemainingPack() {
        current_card = -1;
    }

    /**
     * Get card where pointer current is pointing.
     * @return
     */
    card::Card RemainingPack::currentCard() {
        return card_stack[current_card];
    }

    /**
     * @brief Moving pointer to next card.
     */
    void RemainingPack::nextCard() {
        // casting because size() is unsigned type
        if (current_card < static_cast<long>(card_stack.size()) -1) current_card++;
        else throw ErrorException(E_OUT_OF_RANGE, "Remaining pack is in the end, no next4 card");
    }

    /**
     * @brief Moving pointer to previous card.
     */
    void RemainingPack::prevCard() {
        current_card--;
    }

    /**
     * @brief Set card pointer to 1 card befora start
     */
    void RemainingPack::turnPack() {
        current_card = -1;
    }

    void RemainingPack::turnBack() {
        current_card = static_cast<signed>(card_stack.size() -1);
    }

    /**
     * @brief all card are visible
     * @return bool if all card are visible
     */
    bool RemainingPack::allCardVisible() {
        return current_card == static_cast<signed>(card_stack.size()-1);
    }

    /**
     * @return bool if pinter is set
     */
    bool RemainingPack::isSetCurrent() {
        return (current_card >= 0);
    }

    void RemainingPack::insertCurrent(card::Card c) {
        current_card++;
        card_stack.insert(card_stack.begin() + current_card, c);

    }

    /**
     * @brief Pop card where pointer is pointing.
     */
    void RemainingPack::popCurrent() {
        if ((signed)card_stack.size() > current_card && current_card != -1){
            card_stack.erase(card_stack.begin() + current_card);
            current_card--;
        }
        else {
            throw ErrorException(E_REM_PACK_POP, "using popCurrent() with out set current pointer or out of range");
        }
    }

    /**
     * Get card current card a pop it out
     * @return poped card
     */
    card::Card RemainingPack::topAndPopCurrent() {
        card::Card poped_card = currentCard();
        popCurrent();
        return poped_card;
    }

    int RemainingPack::get_current_id() {
        return current_card;
    }

    void RemainingPack::set_current_id(int id) {
        current_card = id;
    }

    void RemainingPack::pushCurrent(card::Card card) {
        card_stack.insert(card_stack.begin() + ++current_card, card);
    }

    /**
     * @brief Crete a deck cards and fill it with cards.
     */
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

    /**
     * @brief Randomize order fo cards.
     */
    void CardDeck::shuffleCards() {
        std::mt19937 r{std::random_device{}()};
        std::shuffle(std::begin(card_stack), std::end(card_stack), r);
    }

}
